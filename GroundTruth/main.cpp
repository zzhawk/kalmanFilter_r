#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include "bezier.hpp"

/*

// Create a cubic bezier with 4 points. Visualized at https://www.desmos.com/calculator/fivneeogmh
bezier::Bezier<3> cubicBezier({ {120, 160}, {35, 200}, {220, 260}, {220, 40} });

// Get coordinates on the curve from a value between 0 and 1 (values outside this range are also valid because of the way bezier curves are defined).
bezier::Point p;
p = cubicBezier.valueAt(0);   // (120, 160)
p = cubicBezier.valueAt(0.5); // (138.125, 197.5)

// Get coordinate values for a single axis. Currently only supports 2D.
double value;
value = cubicBezier.valueAt(1, 0);    // 220 (x-coordinate at t = 1)
value = cubicBezier.valueAt(0.75, 1); // 157.1875 (y-coordinate at t = 0.75)
value = cubicBezier.length();         // 272.85 (Arc length of the bezier curve)

// Translate and rotate bezier curves.
bezier::Bezier<3> copy = cubicBezier;
copy.translate(10, 15);      // Translate 10 in x-direction, 15 in y-direction
copy.rotate(0.5);            // Rotate 0.5 radians around the origin
copy.rotate(3.14, {-5, 20}); // Rotate 3.14 radians around (-5, 20)

// Get normals along the bezier curve.
bezier::Normal normal = cubicBezier.normalAt(0.75); // Get normalized normal at t = 0.75. Add false as second argument to disable normalization.
double angle = normal.angle();       // Angle in radians
double angleDeg = normal.angleDeg(); // Angle in degrees

// Get tangents along the bezier curve.
bezier::Tangent tangent = cubicBezier.tangentAt(0.25); // Get normalized tangent at t = 0.25. Add false as second argument to disable normalization.
angle = tangent.angle();       // Angle in radians
angleDeg = tangent.angleDeg(); // Angle in degrees

// Get derivatives of the bezier curve, resulting in a bezier curve of one order less.
bezier::Bezier<2> db  = cubicBezier.derivative(); // First derivative
bezier::Bezier<1> ddb = db.derivative();          // Second derivative

// Get extreme values of the bezier curves.
bezier::ExtremeValues xVals = cubicBezier.derivativeZero();  // Contains 3 extreme value locations: t = 0.186811984, t = 1.0 and t = 0.437850952
bezier::ExtremeValue const& xVal = xVals[0];                 // Contains t value and axis for the first extreme value
bezier::Point xValCoord = cubicBezier.valueAt(xVal.t);       // Get the coordinates for the first extreme value (97.6645355, 182.55565)
bezier::ExtremePoints xPoints = cubicBezier.extremePoints(); // Or get all the extreme points directly (includes 0 and 1)

// Get bounding boxes of the bezier curves.
bezier::AABB aabb = cubicBezier.aabb();            // Axis Aligned Bounding Box
aabb = cubicBezier.aabb(xPoints);                  // Or get from extreme points (if you already have them) to reduce calculation time
bezier::TightBoundingBox tbb = cubicBezier.tbb();  // Tight bounding box

// Split the bezier curve at desired points. The left and right parts are new bezier curves
// of the same order as the original curve.
auto split = cubicBezier.split(0.5);
auto &left  = split.left;  // Left part of the split
auto &right = split.right; // Right part of the split

// Find the mid point on the curve by arch length.
double tAtMidPoint = cubicBezier.archMidPoint();           // 0.70718
bezier::Point midPoint = cubicBezier.valueAt(tAtMidPoint); // (183.837, 168.768)


*/

using namespace std;
using json = nlohmann::json;

int main()
{

   int total = 40;
   json j;

   ofstream file("../spinline.json");
   bezier::Bezier<3> cubicBezier({ {120, 160}, {35, 200}, {220, 260}, {220, 40} });

   j["total"] = total;
   for (int i = 0; i <= total; ++i) {
      auto p = cubicBezier.valueAt((double)i/(double)total);
      //cout << p.x << " " << p.y << " " << endl;
      j["wp"+ to_string(i)] = { {"x", p.x}, {"y", p.y} };
   }
   file << j << endl;

   ifstream t("../spinline.json");
   json b;
   t >> b;
   for (int i = 0; i <= b.at("total"); ++i) {
      cout << b.at("wp" + to_string(i)) << endl;
   }
   return 0;
}
