/*
 * File: Calibration_stations.c
 *
 * Code generated for Simulink model 'Calibration_stations'.
 *
 * Model version                  : 3.3
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Tue Feb 28 22:13:24 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Calibration_stations.h"
#include "Calibration_stations_private.h"

/* External inputs (root inport signals with default storage) */
ExtU_Calibration_stations_T Calibration_stations_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Calibration_stations_T Calibration_stations_Y;

/* Real-time model */
static RT_MODEL_Calibration_stations_T Calibration_stations_M_;
RT_MODEL_Calibration_stations_T *const Calibration_stations_M =
  &Calibration_stations_M_;
real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T q;
  real_T y;
  boolean_T yEq;
  y = u0;
  if (u1 == 0.0) {
    if (u0 == 0.0) {
      y = u1;
    }
  } else if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (u0 == 0.0) {
    y = 0.0 / u1;
  } else if (rtIsInf(u1)) {
    if ((u1 < 0.0) != (u0 < 0.0)) {
      y = u1;
    }
  } else {
    y = fmod(u0, u1);
    yEq = (y == 0.0);
    if ((!yEq) && (u1 > floor(u1))) {
      q = fabs(u0 / u1);
      yEq = !(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q);
    }

    if (yEq) {
      y = u1 * 0.0;
    } else {
      if ((u0 < 0.0) != (u1 < 0.0)) {
        y += u1;
      }
    }
  }

  return y;
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T q;
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (rtIsInf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != trunc(u1))) {
    q = fabs(u0 / u1);
    if (!(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = fmod(u0, u1);
    }
  } else {
    y = fmod(u0, u1);
  }

  return y;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model step function */
void Calibration_stations_step(void)
{
  real_T rtb_ECEF_coor_tmp[9];
  real_T rtb_ECEF_coor[3];
  real_T rtb_LLAtoECEF[3];
  real_T flat;
  real_T flat_tmp;
  real_T latNew;
  real_T lonNew;
  real_T lonNew_tmp;
  int32_T count;

  /* LLA2ECEF: '<S1>/LLA to ECEF' incorporates:
   *  Inport: '<Root>/RwyAlt'
   *  Inport: '<Root>/RwyLat'
   *  Inport: '<Root>/RwyLon'
   *  MATLAB Function: '<S1>/ENU2ECEF'
   */
  flat_tmp = Calibration_stations_U.RwyLat * 3.1415926535897931 / 180.0;
  flat = fabs(flat_tmp);
  latNew = flat_tmp;
  lonNew_tmp = Calibration_stations_U.RwyLon * 3.1415926535897931 / 180.0;
  lonNew = lonNew_tmp;
  if (flat > 3.1415926535897931) {
    latNew = rt_modd_snf(flat_tmp + 3.1415926535897931, 6.2831853071795862) -
      3.1415926535897931;
    flat = fabs(latNew);
  }

  if (flat > 1.5707963267948966) {
    lonNew = lonNew_tmp + 3.1415926535897931;
    if (latNew < 0.0) {
      latNew = -1.0;
    } else if (latNew > 0.0) {
      latNew = 1.0;
    } else if (latNew == 0.0) {
      latNew = 0.0;
    } else {
      latNew = (rtNaN);
    }

    latNew *= 1.5707963267948966 - (flat - 1.5707963267948966);
  }

  if (fabs(lonNew) > 3.1415926535897931) {
    lonNew = rt_remd_snf(lonNew, 6.2831853071795862);
    lonNew -= trunc(lonNew / 3.1415926535897931) * 6.2831853071795862;
  }

  flat = sin(latNew);
  rtb_LLAtoECEF[0] = (6.378137E+6 / sqrt(1.0 - flat * flat *
    0.0066943799901413165) + Calibration_stations_U.RwyAlt) * cos(latNew) * cos
    (lonNew);
  rtb_LLAtoECEF[1] = (6.378137E+6 / sqrt(1.0 - sin(latNew) * sin(latNew) *
    0.0066943799901413165) + Calibration_stations_U.RwyAlt) * cos(latNew) * sin
    (lonNew);
  rtb_LLAtoECEF[2] = (6.378137E+6 / sqrt(1.0 - sin(latNew) * sin(latNew) *
    0.0066943799901413165) * 0.99330562000985867 + Calibration_stations_U.RwyAlt)
    * flat;

  /* End of LLA2ECEF: '<S1>/LLA to ECEF' */

  /* MATLAB Function: '<S1>/ENU2ECEF' incorporates:
   *  Inport: '<Root>/RwyLat'
   */
  lonNew = cos(lonNew_tmp);
  lonNew_tmp = sin(lonNew_tmp);
  latNew = cos(flat_tmp);
  flat_tmp = sin(flat_tmp);
  rtb_ECEF_coor_tmp[0] = -lonNew_tmp;
  rtb_ECEF_coor_tmp[3] = -flat_tmp * lonNew;
  rtb_ECEF_coor_tmp[6] = latNew * lonNew;
  rtb_ECEF_coor_tmp[1] = lonNew;
  rtb_ECEF_coor_tmp[4] = -sin(Calibration_stations_U.RwyLat * 3.1415926535897931
    / 180.0) * lonNew_tmp;
  rtb_ECEF_coor_tmp[7] = latNew * lonNew_tmp;
  rtb_ECEF_coor_tmp[2] = 0.0;
  rtb_ECEF_coor_tmp[5] = latNew;
  rtb_ECEF_coor_tmp[8] = flat_tmp;

  /* MATLAB Function: '<S1>/Cal_ENU_Coor' incorporates:
   *  Inport: '<Root>/Angle'
   *  Inport: '<Root>/Distance'
   */
  lonNew_tmp = Calibration_stations_U.Angle * 3.1415926535897931 / 180.0;
  flat_tmp = sin(lonNew_tmp) * Calibration_stations_U.Distance;
  lonNew_tmp = cos(lonNew_tmp) * Calibration_stations_U.Distance;

  /* MATLAB Function: '<S1>/ENU2ECEF' incorporates:
   *  Inport: '<Root>/Altitute'
   */
  for (count = 0; count < 3; count++) {
    rtb_ECEF_coor[count] = rtb_LLAtoECEF[count] + (rtb_ECEF_coor_tmp[count + 6] *
      Calibration_stations_U.Altitute + (rtb_ECEF_coor_tmp[count + 3] *
      lonNew_tmp + rtb_ECEF_coor_tmp[count] * flat_tmp));
  }

  /* ECEF2LLA: '<S1>/ECEF to LLA' */
  flat_tmp = sqrt(rtb_ECEF_coor[0] * rtb_ECEF_coor[0] + rtb_ECEF_coor[1] *
                  rtb_ECEF_coor[1]);
  lonNew_tmp = rt_atan2d_snf(rtb_ECEF_coor[2], 0.99664718933525254 * flat_tmp);
  lonNew = sin(lonNew_tmp);
  latNew = cos(lonNew_tmp);
  lonNew = rt_atan2d_snf(42841.311513313573 * lonNew * lonNew * lonNew +
    rtb_ECEF_coor[2], flat_tmp - 42697.672707179969 * latNew * latNew * latNew);
  latNew = rt_atan2d_snf(0.99664718933525254 * sin(lonNew), cos(lonNew));
  count = 0;
  while ((lonNew_tmp != latNew) && (count < 5)) {
    lonNew_tmp = latNew;
    lonNew = sin(latNew);
    latNew = cos(latNew);
    lonNew = rt_atan2d_snf(42841.311513313573 * lonNew * lonNew * lonNew +
      rtb_ECEF_coor[2], flat_tmp - 42697.672707179969 * latNew * latNew * latNew);
    latNew = rt_atan2d_snf(0.99664718933525254 * sin(lonNew), cos(lonNew));
    count++;
  }

  flat = fabs(lonNew);
  latNew = lonNew;
  lonNew_tmp = rt_atan2d_snf(rtb_ECEF_coor[1], rtb_ECEF_coor[0]);
  if (flat > 3.1415926535897931) {
    latNew = rt_modd_snf(lonNew + 3.1415926535897931, 6.2831853071795862) -
      3.1415926535897931;
    flat = fabs(latNew);
  }

  if (flat > 1.5707963267948966) {
    lonNew_tmp += 3.1415926535897931;
    if (latNew < 0.0) {
      latNew = -1.0;
    } else if (latNew > 0.0) {
      latNew = 1.0;
    } else if (latNew == 0.0) {
      latNew = 0.0;
    } else {
      latNew = (rtNaN);
    }

    latNew *= 1.5707963267948966 - (flat - 1.5707963267948966);
  }

  if (fabs(lonNew_tmp) > 3.1415926535897931) {
    lonNew_tmp = rt_remd_snf(lonNew_tmp, 6.2831853071795862);
    lonNew_tmp -= trunc(lonNew_tmp / 3.1415926535897931) * 6.2831853071795862;
  }

  /* Outport: '<Root>/Station_latitude' incorporates:
   *  ECEF2LLA: '<S1>/ECEF to LLA'
   */
  Calibration_stations_Y.Station_latitude = latNew * 180.0 / 3.1415926535897931;

  /* Outport: '<Root>/Station_longitude' incorporates:
   *  ECEF2LLA: '<S1>/ECEF to LLA'
   */
  Calibration_stations_Y.Station_longitude = lonNew_tmp * 180.0 /
    3.1415926535897931;

  /* ECEF2LLA: '<S1>/ECEF to LLA' */
  lonNew_tmp = sin(lonNew);

  /* Outport: '<Root>/Station_altitude' incorporates:
   *  ECEF2LLA: '<S1>/ECEF to LLA'
   */
  Calibration_stations_Y.Station_altitude = ((6.378137E+6 / sqrt(1.0 -
    lonNew_tmp * lonNew_tmp * 0.0066943799901413165) * 0.0066943799901413165 *
    lonNew_tmp + rtb_ECEF_coor[2]) * lonNew_tmp + flat_tmp * cos(lonNew)) -
    6.378137E+6 / sqrt(1.0 - sin(lonNew) * sin(lonNew) * 0.0066943799901413165);
}

/* Model initialize function */
void Calibration_stations_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
}

/* Model terminate function */
void Calibration_stations_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
