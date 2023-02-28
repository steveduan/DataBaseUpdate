/*
 * File: Calibration_stations.h
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

#ifndef RTW_HEADER_Calibration_stations_h_
#define RTW_HEADER_Calibration_stations_h_
#include <float.h>
#include <math.h>
#ifndef Calibration_stations_COMMON_INCLUDES_
#define Calibration_stations_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                               /* Calibration_stations_COMMON_INCLUDES_ */

#include "Calibration_stations_types.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T RwyLat;                       /* '<Root>/RwyLat' */
  real_T RwyLon;                       /* '<Root>/RwyLon' */
  real_T RwyAlt;                       /* '<Root>/RwyAlt' */
  real_T Distance;                     /* '<Root>/Distance' */
  real_T Angle;                        /* '<Root>/Angle' */
  real_T Altitute;                     /* '<Root>/Altitute' */
} ExtU_Calibration_stations_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Station_latitude;             /* '<Root>/Station_latitude' */
  real_T Station_longitude;            /* '<Root>/Station_longitude' */
  real_T Station_altitude;             /* '<Root>/Station_altitude' */
} ExtY_Calibration_stations_T;

/* Real-time Model Data Structure */
struct tag_RTM_Calibration_stations_T {
  const char_T * volatile errorStatus;
};

/* External inputs (root inport signals with default storage) */
extern ExtU_Calibration_stations_T Calibration_stations_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Calibration_stations_T Calibration_stations_Y;

/* Model entry point functions */
extern void Calibration_stations_initialize(void);
extern void Calibration_stations_step(void);
extern void Calibration_stations_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Calibration_stations_T *const Calibration_stations_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Calibration_stations'
 * '<S1>'   : 'Calibration_stations/Cali_Stations'
 * '<S2>'   : 'Calibration_stations/Cali_Stations/Cal_ENU_Coor'
 * '<S3>'   : 'Calibration_stations/Cali_Stations/ENU2ECEF'
 */
#endif                                 /* RTW_HEADER_Calibration_stations_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
