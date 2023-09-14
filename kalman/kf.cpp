// Copyright 2023 watson.wang

#include "kf.h"
#include <iostream>

void kalmanFilter::ExtrapolateState()
{
   Eigen::MatrixXd xt = F * x + G * u;
   x = xt;
}

void kalmanFilter::ExtrapolateUncertainty()
{
   Eigen::MatrixXd Pt = F * P * F.transpose() + Q;
   P = Pt;
}

void kalmanFilter::ComplteGain()
{
   K = P * H.transpose() * (H * P * H.transpose() + R).inverse();
}

void kalmanFilter::UpdateEstimate()
{
   Eigen::MatrixXd y = z - H * x;
   Eigen::MatrixXd xt = x + K * y;
   x = xt;
}

void kalmanFilter::UpdateUncertainty()
{
   Eigen::MatrixXd S = H * P * H.transpose() + R;
   Eigen::MatrixXd pt = (I - K * H) * P;
   P = pt;
}

