#include <Eigen/Core>
#include <Eigen/Geometry>
#include <utility>

class kfBase
{
public:
   explicit kfBase(Eigen::MatrixXd M_state, Eigen::MatrixXd M_control, Eigen::MatrixXd M_pnoise, Eigen::MatrixXd M_mnoise)
      :F(M_state), G(M_control), Q(M_pnoise), R(M_mnoise)
   {
      auto row = M_state.rows();
      auto col = M_mnoise.rows();

      P = Eigen::MatrixXd::Identity(row, row);
      I = Eigen::MatrixXd::Identity(row, row);
      H = Eigen::MatrixXd::Identity(col, row);
      x.resize(row, 1); x.setZero();
      u.resize(row, 1); u.setZero();

   };

   virtual ~kfBase() = default;

   kfBase(const kfBase&) = default;
   kfBase& operator = (const kfBase&) = default;

   kfBase(kfBase &&) noexcept = default;
   kfBase& operator = (kfBase&&) = default;

   void init(Eigen::MatrixXd& Observation)
   {
      z = Observation;
      x(0, 0) = z(0, 0);
      x(1, 0) = z(1, 0);

   }

   std::pair<Eigen::MatrixXd, Eigen::MatrixXd> run(Eigen::MatrixXd &Observation)
   {
      ExtrapolateState();
      ExtrapolateUncertainty();
      ComplteGain();
      UpdateEstimate();
      UpdateUncertainty();

      z = Observation;

      return std::make_pair( x, P );
   };

   std::pair<Eigen::MatrixXd, Eigen::MatrixXd> getResult(void) 
   {
      return std::make_pair(x, P);
   }

protected:

   Eigen::MatrixXd F;
   Eigen::MatrixXd G;
   Eigen::MatrixXd H;
   Eigen::MatrixXd K;
   Eigen::MatrixXd x;
   Eigen::MatrixXd u;
   Eigen::MatrixXd P;
   Eigen::MatrixXd Q;
   Eigen::MatrixXd R;
   Eigen::MatrixXd z;
   Eigen::MatrixXd I;


   virtual void ExtrapolateState() = 0;
   virtual void ExtrapolateUncertainty() = 0;
   virtual void ComplteGain() = 0;
   virtual void UpdateEstimate() = 0;
   virtual void UpdateUncertainty() = 0;

};