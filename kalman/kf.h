// Copyright 2023 watson.wang

#include "kf_base.h"


class kalmanFilter:public kfBase
{
public:
   explicit kalmanFilter(Eigen::MatrixXd M_state, Eigen::MatrixXd M_control, Eigen::MatrixXd M_pnoise, Eigen::MatrixXd M_mnoise)
   :kfBase(M_state, M_control, M_pnoise, M_mnoise){};

   virtual ~kalmanFilter() = default;

   kalmanFilter (kalmanFilter&) = default;
   kalmanFilter& operator = (const kalmanFilter&) = default;

   kalmanFilter(kalmanFilter&&) noexcept = default;
   kalmanFilter& operator = (kalmanFilter&&) = default;

protected:
   void ExtrapolateState() override;
   void ExtrapolateUncertainty() override;
   void ComplteGain() override;
   void UpdateEstimate() override;
   void UpdateUncertainty() override;


};
