// Copyright 2023 watson.wang

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "nlohmann/json.hpp"
#include "kf.h"

using namespace std;
using json = nlohmann::json;

typedef struct {
   double x;
   double y;
}wp;

int main()
{
   ifstream t("../spinline.json");
   ofstream o("../ans.csv");
   vector<vector<double>> out;

   json b;
   t >> b;

   random_device seed;
   ranlux48 engine(seed());
   uniform_int_distribution<> distrib(-100, 100);

   auto getwp = [&]()->vector<wp> {
      vector<wp> wps;

      for (int i = 0; i <= b.at("total"); ++i) {
         wp waypoint;
         double raw_x = b.at("wp" + to_string(i)).at("x");
         double raw_y = b.at("wp" + to_string(i)).at("y");

         waypoint.x = raw_x + (double)distrib(engine)/40.0;
         waypoint.y = raw_y + (double)distrib(engine)/40.0;
         
         out.push_back({ raw_x, raw_y, waypoint.x, waypoint.y });
         wps.push_back(waypoint);
      }

      return wps;
   };

   vector<wp> waypoints = getwp();

   Eigen::MatrixXd M_state{
      {1.0, 0.0, 1.0, 0.0},
      {0.0, 1.0, 0.0, 1.0},
      {0.0, 0.0, 1.0, 0.0},
      {0.0, 0.0, 0.0, 1.0}
   };

   Eigen::MatrixXd M_control{
      {0.0, 0.0, 0.0, 0.0},
      {0.0, 0.0, 0.0, 0.0},
      {0.0, 0.0, 0.0, 0.0},
      {0.0, 0.0, 0.0, 0.0}
   };


   unique_ptr<kfBase> kalman = make_unique<kalmanFilter>(M_state, M_control, 0.01 * Eigen::MatrixXd::Identity(4, 4), 0.01 * Eigen::MatrixXd::Identity(2, 2));

   Eigen::MatrixXd first{
      { waypoints[0].x },
      { waypoints[0].y }
   };
   kalman->init(first);
;
   // cout << waypoints[0].x << "," << waypoints[0].y << "," << waypoints[0].x << "," << waypoints[0].y << endl;

   for (int i = 1; i < waypoints.size(); ++i) {
      Eigen::MatrixXd M_x;
      Eigen::MatrixXd M_P;

      Eigen::MatrixXd M_meas{
         {waypoints[i].x},
         {waypoints[i].y},
      };

      tie(M_x, M_P) = kalman->run(M_meas);

      out[i-1].push_back(M_x(0, 0));
      out[i-1].push_back(M_x(1, 0));
      // cout << waypoints[i].x << "," << waypoints[i].y << "," << M_x(0, 0) << "," << M_x(1, 0) << "," << endl;
      // cout << "x:" + to_string(M_x(0, 0)) << " y:" + to_string(M_x(1, 0)) << endl;
   }

   Eigen::MatrixXd M_x;
   Eigen::MatrixXd M_P;
   tie(M_x, M_P) = kalman->getResult();
   out[waypoints.size()-1].push_back(M_x(0, 0));
   out[waypoints.size()-1].push_back(M_x(1, 0));

   for (auto rec : out) {
      for (auto item : rec) {
         o << item << ",";
      }
      o << endl;
   }

   return 0;
}