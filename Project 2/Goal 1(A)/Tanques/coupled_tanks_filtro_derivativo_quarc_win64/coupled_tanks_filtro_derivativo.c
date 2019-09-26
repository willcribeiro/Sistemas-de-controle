/*
 * coupled_tanks_filtro_derivativo.c
 *
 * Code generation for model "coupled_tanks_filtro_derivativo".
 *
 * Model version              : 1.282
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Fri Sep 13 15:59:22 2019
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "coupled_tanks_filtro_derivativo.h"
#include "coupled_tanks_filtro_derivativo_private.h"
#include "coupled_tanks_filtro_derivativo_dt.h"

/* Block signals (auto storage) */
B_coupled_tanks_filtro_deriva_T coupled_tanks_filtro_derivati_B;

/* Continuous states */
X_coupled_tanks_filtro_deriva_T coupled_tanks_filtro_derivati_X;

/* Block states (auto storage) */
DW_coupled_tanks_filtro_deriv_T coupled_tanks_filtro_derivat_DW;

/* Real-time model */
RT_MODEL_coupled_tanks_filtro_T coupled_tanks_filtro_derivat_M_;
RT_MODEL_coupled_tanks_filtro_T *const coupled_tanks_filtro_derivat_M =
  &coupled_tanks_filtro_derivat_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  coupled_tanks_filtro_derivativo_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void coupled_tanks_filtro_derivativo_output(void)
{
  /* local block i/o variables */
  real_T rtb_HILReadAnalog_o2;
  real_T rtb_HILReadAnalog_o1;
  real_T *lastU;
  real_T rtb_Derivative;
  if (rtmIsMajorTimeStep(coupled_tanks_filtro_derivat_M)) {
    /* set solver stop time */
    if (!(coupled_tanks_filtro_derivat_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&coupled_tanks_filtro_derivat_M->solverInfo,
                            ((coupled_tanks_filtro_derivat_M->Timing.clockTickH0
        + 1) * coupled_tanks_filtro_derivat_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&coupled_tanks_filtro_derivat_M->solverInfo,
                            ((coupled_tanks_filtro_derivat_M->Timing.clockTick0
        + 1) * coupled_tanks_filtro_derivat_M->Timing.stepSize0 +
        coupled_tanks_filtro_derivat_M->Timing.clockTickH0 *
        coupled_tanks_filtro_derivat_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(coupled_tanks_filtro_derivat_M)) {
    coupled_tanks_filtro_derivat_M->Timing.t[0] = rtsiGetT
      (&coupled_tanks_filtro_derivat_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(coupled_tanks_filtro_derivat_M)) {
    /* S-Function (hil_read_analog_block): '<S1>/HIL Read Analog' */

    /* S-Function Block: coupled_tanks_filtro_derivativo/PLANTA/HIL Read Analog (hil_read_analog_block) */
    {
      t_error result = hil_read_analog
        (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
         coupled_tanks_filtro_derivati_P.HILReadAnalog_channels, 2,
         &coupled_tanks_filtro_derivat_DW.HILReadAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
      }

      rtb_HILReadAnalog_o1 =
        coupled_tanks_filtro_derivat_DW.HILReadAnalog_Buffer[0];
      rtb_HILReadAnalog_o2 =
        coupled_tanks_filtro_derivat_DW.HILReadAnalog_Buffer[1];
    }

    /* Gain: '<S1>/Volts to cm Tank 1 ' */
    coupled_tanks_filtro_derivati_B.VoltstocmTank1 =
      coupled_tanks_filtro_derivati_P.VoltstocmTank1_Gain * rtb_HILReadAnalog_o1;

    /* Constant: '<Root>/Constant' */
    coupled_tanks_filtro_derivati_B.Constant =
      coupled_tanks_filtro_derivati_P.Constant_Value;

    /* Sum: '<Root>/Sum' */
    coupled_tanks_filtro_derivati_B.Sum =
      coupled_tanks_filtro_derivati_B.Constant -
      coupled_tanks_filtro_derivati_B.VoltstocmTank1;

    /* Gain: '<Root>/Kp ' */
    coupled_tanks_filtro_derivati_B.Kp = coupled_tanks_filtro_derivati_P.Kp_Gain
      * coupled_tanks_filtro_derivati_B.Sum;
  }

  /* Derivative: '<Root>/Derivative' */
  if ((coupled_tanks_filtro_derivat_DW.TimeStampA >=
       coupled_tanks_filtro_derivat_M->Timing.t[0]) &&
      (coupled_tanks_filtro_derivat_DW.TimeStampB >=
       coupled_tanks_filtro_derivat_M->Timing.t[0])) {
    rtb_Derivative = 0.0;
  } else {
    rtb_Derivative = coupled_tanks_filtro_derivat_DW.TimeStampA;
    lastU = &coupled_tanks_filtro_derivat_DW.LastUAtTimeA;
    if (coupled_tanks_filtro_derivat_DW.TimeStampA <
        coupled_tanks_filtro_derivat_DW.TimeStampB) {
      if (coupled_tanks_filtro_derivat_DW.TimeStampB <
          coupled_tanks_filtro_derivat_M->Timing.t[0]) {
        rtb_Derivative = coupled_tanks_filtro_derivat_DW.TimeStampB;
        lastU = &coupled_tanks_filtro_derivat_DW.LastUAtTimeB;
      }
    } else {
      if (coupled_tanks_filtro_derivat_DW.TimeStampA >=
          coupled_tanks_filtro_derivat_M->Timing.t[0]) {
        rtb_Derivative = coupled_tanks_filtro_derivat_DW.TimeStampB;
        lastU = &coupled_tanks_filtro_derivat_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (coupled_tanks_filtro_derivati_B.Sum - *lastU) /
      (coupled_tanks_filtro_derivat_M->Timing.t[0] - rtb_Derivative);
  }

  /* End of Derivative: '<Root>/Derivative' */

  /* Gain: '<Root>/Kd ' */
  coupled_tanks_filtro_derivati_B.Kd = coupled_tanks_filtro_derivati_P.Kd_Gain *
    rtb_Derivative;

  /* Integrator: '<Root>/Integrator' */
  coupled_tanks_filtro_derivati_B.Integrator =
    coupled_tanks_filtro_derivati_X.Integrator_CSTATE;

  /* Sum: '<Root>/Add' */
  coupled_tanks_filtro_derivati_B.Add = (coupled_tanks_filtro_derivati_B.Kp +
    coupled_tanks_filtro_derivati_B.Kd) +
    coupled_tanks_filtro_derivati_B.Integrator;

  /* Saturate: '<Root>/Saturation' */
  if (coupled_tanks_filtro_derivati_B.Add >
      coupled_tanks_filtro_derivati_P.Saturation_UpperSat) {
    coupled_tanks_filtro_derivati_B.Saturation =
      coupled_tanks_filtro_derivati_P.Saturation_UpperSat;
  } else if (coupled_tanks_filtro_derivati_B.Add <
             coupled_tanks_filtro_derivati_P.Saturation_LowerSat) {
    coupled_tanks_filtro_derivati_B.Saturation =
      coupled_tanks_filtro_derivati_P.Saturation_LowerSat;
  } else {
    coupled_tanks_filtro_derivati_B.Saturation =
      coupled_tanks_filtro_derivati_B.Add;
  }

  /* End of Saturate: '<Root>/Saturation' */
  if (rtmIsMajorTimeStep(coupled_tanks_filtro_derivat_M)) {
    /* S-Function (hil_write_analog_block): '<S1>/HIL Write Analog' */

    /* S-Function Block: coupled_tanks_filtro_derivativo/PLANTA/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog
        (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
         &coupled_tanks_filtro_derivati_P.HILWriteAnalog_channels, 1,
         &coupled_tanks_filtro_derivati_B.Saturation);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
      }
    }

    /* Gain: '<Root>/Ki  ' */
    coupled_tanks_filtro_derivati_B.Ki = coupled_tanks_filtro_derivati_P.Ki_Gain
      * coupled_tanks_filtro_derivati_B.Sum;
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<Root>/Kaw '
   *  Sum: '<Root>/Sum1'
   */
  coupled_tanks_filtro_derivati_B.Sum2 =
    (coupled_tanks_filtro_derivati_B.Saturation -
     coupled_tanks_filtro_derivati_B.Add) *
    coupled_tanks_filtro_derivati_P.Kaw_Gain +
    coupled_tanks_filtro_derivati_B.Ki;
}

/* Model update function */
void coupled_tanks_filtro_derivativo_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<Root>/Derivative' */
  if (coupled_tanks_filtro_derivat_DW.TimeStampA == (rtInf)) {
    coupled_tanks_filtro_derivat_DW.TimeStampA =
      coupled_tanks_filtro_derivat_M->Timing.t[0];
    lastU = &coupled_tanks_filtro_derivat_DW.LastUAtTimeA;
  } else if (coupled_tanks_filtro_derivat_DW.TimeStampB == (rtInf)) {
    coupled_tanks_filtro_derivat_DW.TimeStampB =
      coupled_tanks_filtro_derivat_M->Timing.t[0];
    lastU = &coupled_tanks_filtro_derivat_DW.LastUAtTimeB;
  } else if (coupled_tanks_filtro_derivat_DW.TimeStampA <
             coupled_tanks_filtro_derivat_DW.TimeStampB) {
    coupled_tanks_filtro_derivat_DW.TimeStampA =
      coupled_tanks_filtro_derivat_M->Timing.t[0];
    lastU = &coupled_tanks_filtro_derivat_DW.LastUAtTimeA;
  } else {
    coupled_tanks_filtro_derivat_DW.TimeStampB =
      coupled_tanks_filtro_derivat_M->Timing.t[0];
    lastU = &coupled_tanks_filtro_derivat_DW.LastUAtTimeB;
  }

  *lastU = coupled_tanks_filtro_derivati_B.Sum;

  /* End of Update for Derivative: '<Root>/Derivative' */
  if (rtmIsMajorTimeStep(coupled_tanks_filtro_derivat_M)) {
    rt_ertODEUpdateContinuousStates(&coupled_tanks_filtro_derivat_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++coupled_tanks_filtro_derivat_M->Timing.clockTick0)) {
    ++coupled_tanks_filtro_derivat_M->Timing.clockTickH0;
  }

  coupled_tanks_filtro_derivat_M->Timing.t[0] = rtsiGetSolverStopTime
    (&coupled_tanks_filtro_derivat_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++coupled_tanks_filtro_derivat_M->Timing.clockTick1)) {
      ++coupled_tanks_filtro_derivat_M->Timing.clockTickH1;
    }

    coupled_tanks_filtro_derivat_M->Timing.t[1] =
      coupled_tanks_filtro_derivat_M->Timing.clockTick1 *
      coupled_tanks_filtro_derivat_M->Timing.stepSize1 +
      coupled_tanks_filtro_derivat_M->Timing.clockTickH1 *
      coupled_tanks_filtro_derivat_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void coupled_tanks_filtro_derivativo_derivatives(void)
{
  XDot_coupled_tanks_filtro_der_T *_rtXdot;
  _rtXdot = ((XDot_coupled_tanks_filtro_der_T *)
             coupled_tanks_filtro_derivat_M->ModelData.derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = coupled_tanks_filtro_derivati_B.Sum2;

  /* Derivatives for Integrator: '<Root>/Integrator ' */
  _rtXdot->Integrator_CSTATE_p = 0.0;
}

/* Model initialize function */
void coupled_tanks_filtro_derivativo_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<S1>/HIL Initialize' */

  /* S-Function Block: coupled_tanks_filtro_derivativo/PLANTA/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0",
                      &coupled_tanks_filtro_derivat_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
       "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear
      (coupled_tanks_filtro_derivat_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
      return;
    }

    if ((coupled_tanks_filtro_derivati_P.HILInitialize_set_analog_input_ &&
         !is_switching) ||
        (coupled_tanks_filtro_derivati_P.HILInitialize_set_analog_inpu_h &&
         is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges
        (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
         coupled_tanks_filtro_derivati_P.HILInitialize_analog_input_chan, 8U,
         &coupled_tanks_filtro_derivat_DW.HILInitialize_AIMinimums[0],
         &coupled_tanks_filtro_derivat_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
        return;
      }
    }

    if ((coupled_tanks_filtro_derivati_P.HILInitialize_set_analog_output &&
         !is_switching) ||
        (coupled_tanks_filtro_derivati_P.HILInitialize_set_analog_outp_c &&
         is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges
        (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
         coupled_tanks_filtro_derivati_P.HILInitialize_analog_output_cha, 8U,
         &coupled_tanks_filtro_derivat_DW.HILInitialize_AOMinimums[0],
         &coupled_tanks_filtro_derivat_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
        return;
      }
    }

    if ((coupled_tanks_filtro_derivati_P.HILInitialize_set_analog_outp_o &&
         !is_switching) ||
        (coupled_tanks_filtro_derivati_P.HILInitialize_set_analog_outp_e &&
         is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog
        (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
         coupled_tanks_filtro_derivati_P.HILInitialize_analog_output_cha, 8U,
         &coupled_tanks_filtro_derivat_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
        return;
      }
    }

    if (coupled_tanks_filtro_derivati_P.HILInitialize_set_analog_out_bm) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
         coupled_tanks_filtro_derivati_P.HILInitialize_analog_output_cha, 8U,
         &coupled_tanks_filtro_derivat_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
        return;
      }
    }

    if ((coupled_tanks_filtro_derivati_P.HILInitialize_set_encoder_param &&
         !is_switching) ||
        (coupled_tanks_filtro_derivati_P.HILInitialize_set_encoder_par_a &&
         is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
         coupled_tanks_filtro_derivati_P.HILInitialize_encoder_channels, 8U,
         (t_encoder_quadrature_mode *)
         &coupled_tanks_filtro_derivat_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
        return;
      }
    }

    if ((coupled_tanks_filtro_derivati_P.HILInitialize_set_encoder_count &&
         !is_switching) ||
        (coupled_tanks_filtro_derivati_P.HILInitialize_set_encoder_cou_e &&
         is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts
        (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
         coupled_tanks_filtro_derivati_P.HILInitialize_encoder_channels, 8U,
         &coupled_tanks_filtro_derivat_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
        return;
      }
    }

    if ((coupled_tanks_filtro_derivati_P.HILInitialize_set_pwm_params_at &&
         !is_switching) ||
        (coupled_tanks_filtro_derivati_P.HILInitialize_set_pwm_params__e &&
         is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode
        (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
         coupled_tanks_filtro_derivati_P.HILInitialize_pwm_channels, 8U,
         (t_pwm_mode *)
         &coupled_tanks_filtro_derivat_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          coupled_tanks_filtro_derivati_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            coupled_tanks_filtro_derivat_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = p_HILInitialize_pwm_channels[i1];
            coupled_tanks_filtro_derivat_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = coupled_tanks_filtro_derivati_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            coupled_tanks_filtro_derivat_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = p_HILInitialize_pwm_channels[i1];
            coupled_tanks_filtro_derivat_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              coupled_tanks_filtro_derivati_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency
          (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
           &coupled_tanks_filtro_derivat_DW.HILInitialize_POSortedChans[0],
           num_duty_cycle_modes,
           &coupled_tanks_filtro_derivat_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle
          (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
           &coupled_tanks_filtro_derivat_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
           num_frequency_modes,
           &coupled_tanks_filtro_derivat_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration
        (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
         coupled_tanks_filtro_derivati_P.HILInitialize_pwm_channels, 8U,
         (t_pwm_configuration *)
         &coupled_tanks_filtro_derivat_DW.HILInitialize_POModeValues[0],
         (t_pwm_alignment *)
         &coupled_tanks_filtro_derivat_DW.HILInitialize_POAlignValues[0],
         (t_pwm_polarity *)
         &coupled_tanks_filtro_derivat_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband
        (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
         coupled_tanks_filtro_derivati_P.HILInitialize_pwm_channels, 8U,
         &coupled_tanks_filtro_derivat_DW.HILInitialize_POSortedFreqs[0],
         &coupled_tanks_filtro_derivat_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
        return;
      }
    }

    if ((coupled_tanks_filtro_derivati_P.HILInitialize_set_pwm_outputs_a &&
         !is_switching) ||
        (coupled_tanks_filtro_derivati_P.HILInitialize_set_pwm_outputs_i &&
         is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
        coupled_tanks_filtro_derivati_P.HILInitialize_pwm_channels, 8U,
        &coupled_tanks_filtro_derivat_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
        return;
      }
    }

    if (coupled_tanks_filtro_derivati_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
         coupled_tanks_filtro_derivati_P.HILInitialize_pwm_channels, 8U,
         &coupled_tanks_filtro_derivat_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
        return;
      }
    }
  }

  /* InitializeConditions for Derivative: '<Root>/Derivative' */
  coupled_tanks_filtro_derivat_DW.TimeStampA = (rtInf);
  coupled_tanks_filtro_derivat_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  coupled_tanks_filtro_derivati_X.Integrator_CSTATE =
    coupled_tanks_filtro_derivati_P.Integrator_IC;

  /* InitializeConditions for Integrator: '<Root>/Integrator ' */
  coupled_tanks_filtro_derivati_X.Integrator_CSTATE_p =
    coupled_tanks_filtro_derivati_P.Integrator_IC_h;
}

/* Model terminate function */
void coupled_tanks_filtro_derivativo_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<S1>/HIL Initialize' */

  /* S-Function Block: coupled_tanks_filtro_derivativo/PLANTA/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(coupled_tanks_filtro_derivat_DW.HILInitialize_Card);
    hil_monitor_stop_all(coupled_tanks_filtro_derivat_DW.HILInitialize_Card);
    is_switching = false;
    if ((coupled_tanks_filtro_derivati_P.HILInitialize_set_analog_outp_h &&
         !is_switching) ||
        (coupled_tanks_filtro_derivati_P.HILInitialize_set_analog_outp_b &&
         is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((coupled_tanks_filtro_derivati_P.HILInitialize_set_pwm_outputs_b &&
         !is_switching) ||
        (coupled_tanks_filtro_derivati_P.HILInitialize_set_pwm_outputs_j &&
         is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues =
          &coupled_tanks_filtro_derivat_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            coupled_tanks_filtro_derivati_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(coupled_tanks_filtro_derivat_DW.HILInitialize_Card
                         ,
                         coupled_tanks_filtro_derivati_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         ,
                         coupled_tanks_filtro_derivati_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         ,
                         &coupled_tanks_filtro_derivat_DW.HILInitialize_AOVoltages
                         [0]
                         ,
                         &coupled_tanks_filtro_derivat_DW.HILInitialize_POValues[
                         0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
             coupled_tanks_filtro_derivati_P.HILInitialize_analog_output_cha,
             num_final_analog_outputs,
             &coupled_tanks_filtro_derivat_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm
            (coupled_tanks_filtro_derivat_DW.HILInitialize_Card,
             coupled_tanks_filtro_derivati_P.HILInitialize_pwm_channels,
             num_final_pwm_outputs,
             &coupled_tanks_filtro_derivat_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(coupled_tanks_filtro_derivat_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(coupled_tanks_filtro_derivat_DW.HILInitialize_Card);
    hil_monitor_delete_all(coupled_tanks_filtro_derivat_DW.HILInitialize_Card);
    hil_close(coupled_tanks_filtro_derivat_DW.HILInitialize_Card);
    coupled_tanks_filtro_derivat_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  coupled_tanks_filtro_derivativo_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  coupled_tanks_filtro_derivativo_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  coupled_tanks_filtro_derivativo_initialize();
}

void MdlTerminate(void)
{
  coupled_tanks_filtro_derivativo_terminate();
}

/* Registration function */
RT_MODEL_coupled_tanks_filtro_T *coupled_tanks_filtro_derivativo(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)coupled_tanks_filtro_derivat_M, 0,
                sizeof(RT_MODEL_coupled_tanks_filtro_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&coupled_tanks_filtro_derivat_M->solverInfo,
                          &coupled_tanks_filtro_derivat_M->Timing.simTimeStep);
    rtsiSetTPtr(&coupled_tanks_filtro_derivat_M->solverInfo, &rtmGetTPtr
                (coupled_tanks_filtro_derivat_M));
    rtsiSetStepSizePtr(&coupled_tanks_filtro_derivat_M->solverInfo,
                       &coupled_tanks_filtro_derivat_M->Timing.stepSize0);
    rtsiSetdXPtr(&coupled_tanks_filtro_derivat_M->solverInfo,
                 &coupled_tanks_filtro_derivat_M->ModelData.derivs);
    rtsiSetContStatesPtr(&coupled_tanks_filtro_derivat_M->solverInfo, (real_T **)
                         &coupled_tanks_filtro_derivat_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&coupled_tanks_filtro_derivat_M->solverInfo,
      &coupled_tanks_filtro_derivat_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&coupled_tanks_filtro_derivat_M->solverInfo,
      &coupled_tanks_filtro_derivat_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr
      (&coupled_tanks_filtro_derivat_M->solverInfo,
       &coupled_tanks_filtro_derivat_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr
      (&coupled_tanks_filtro_derivat_M->solverInfo,
       &coupled_tanks_filtro_derivat_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&coupled_tanks_filtro_derivat_M->solverInfo,
                          (&rtmGetErrorStatus(coupled_tanks_filtro_derivat_M)));
    rtsiSetRTModelPtr(&coupled_tanks_filtro_derivat_M->solverInfo,
                      coupled_tanks_filtro_derivat_M);
  }

  rtsiSetSimTimeStep(&coupled_tanks_filtro_derivat_M->solverInfo,
                     MAJOR_TIME_STEP);
  coupled_tanks_filtro_derivat_M->ModelData.intgData.f[0] =
    coupled_tanks_filtro_derivat_M->ModelData.odeF[0];
  coupled_tanks_filtro_derivat_M->ModelData.contStates = ((real_T *)
    &coupled_tanks_filtro_derivati_X);
  rtsiSetSolverData(&coupled_tanks_filtro_derivat_M->solverInfo, (void *)
                    &coupled_tanks_filtro_derivat_M->ModelData.intgData);
  rtsiSetSolverName(&coupled_tanks_filtro_derivat_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap =
      coupled_tanks_filtro_derivat_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    coupled_tanks_filtro_derivat_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    coupled_tanks_filtro_derivat_M->Timing.sampleTimes =
      (&coupled_tanks_filtro_derivat_M->Timing.sampleTimesArray[0]);
    coupled_tanks_filtro_derivat_M->Timing.offsetTimes =
      (&coupled_tanks_filtro_derivat_M->Timing.offsetTimesArray[0]);

    /* task periods */
    coupled_tanks_filtro_derivat_M->Timing.sampleTimes[0] = (0.0);
    coupled_tanks_filtro_derivat_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    coupled_tanks_filtro_derivat_M->Timing.offsetTimes[0] = (0.0);
    coupled_tanks_filtro_derivat_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(coupled_tanks_filtro_derivat_M,
             &coupled_tanks_filtro_derivat_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = coupled_tanks_filtro_derivat_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    coupled_tanks_filtro_derivat_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(coupled_tanks_filtro_derivat_M, 100.0);
  coupled_tanks_filtro_derivat_M->Timing.stepSize0 = 0.002;
  coupled_tanks_filtro_derivat_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  coupled_tanks_filtro_derivat_M->Sizes.checksums[0] = (1983567428U);
  coupled_tanks_filtro_derivat_M->Sizes.checksums[1] = (2667853829U);
  coupled_tanks_filtro_derivat_M->Sizes.checksums[2] = (130250874U);
  coupled_tanks_filtro_derivat_M->Sizes.checksums[3] = (3570107119U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    coupled_tanks_filtro_derivat_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(coupled_tanks_filtro_derivat_M->extModeInfo,
      &coupled_tanks_filtro_derivat_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(coupled_tanks_filtro_derivat_M->extModeInfo,
                        coupled_tanks_filtro_derivat_M->Sizes.checksums);
    rteiSetTPtr(coupled_tanks_filtro_derivat_M->extModeInfo, rtmGetTPtr
                (coupled_tanks_filtro_derivat_M));
  }

  coupled_tanks_filtro_derivat_M->solverInfoPtr =
    (&coupled_tanks_filtro_derivat_M->solverInfo);
  coupled_tanks_filtro_derivat_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&coupled_tanks_filtro_derivat_M->solverInfo, 0.002);
  rtsiSetSolverMode(&coupled_tanks_filtro_derivat_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  coupled_tanks_filtro_derivat_M->ModelData.blockIO = ((void *)
    &coupled_tanks_filtro_derivati_B);

  {
    coupled_tanks_filtro_derivati_B.VoltstocmTank1 = 0.0;
    coupled_tanks_filtro_derivati_B.Constant = 0.0;
    coupled_tanks_filtro_derivati_B.Sum = 0.0;
    coupled_tanks_filtro_derivati_B.Kp = 0.0;
    coupled_tanks_filtro_derivati_B.Kd = 0.0;
    coupled_tanks_filtro_derivati_B.Integrator = 0.0;
    coupled_tanks_filtro_derivati_B.Add = 0.0;
    coupled_tanks_filtro_derivati_B.Saturation = 0.0;
    coupled_tanks_filtro_derivati_B.Ki = 0.0;
    coupled_tanks_filtro_derivati_B.Sum2 = 0.0;
  }

  /* parameters */
  coupled_tanks_filtro_derivat_M->ModelData.defaultParam = ((real_T *)
    &coupled_tanks_filtro_derivati_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &coupled_tanks_filtro_derivati_X;
    coupled_tanks_filtro_derivat_M->ModelData.contStates = (x);
    (void) memset((void *)&coupled_tanks_filtro_derivati_X, 0,
                  sizeof(X_coupled_tanks_filtro_deriva_T));
  }

  /* states (dwork) */
  coupled_tanks_filtro_derivat_M->ModelData.dwork = ((void *)
    &coupled_tanks_filtro_derivat_DW);
  (void) memset((void *)&coupled_tanks_filtro_derivat_DW, 0,
                sizeof(DW_coupled_tanks_filtro_deriv_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      coupled_tanks_filtro_derivat_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      coupled_tanks_filtro_derivat_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      coupled_tanks_filtro_derivat_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      coupled_tanks_filtro_derivat_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      coupled_tanks_filtro_derivat_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      coupled_tanks_filtro_derivat_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      coupled_tanks_filtro_derivat_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      coupled_tanks_filtro_derivat_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  coupled_tanks_filtro_derivat_DW.HILReadAnalog_Buffer[0] = 0.0;
  coupled_tanks_filtro_derivat_DW.HILReadAnalog_Buffer[1] = 0.0;
  coupled_tanks_filtro_derivat_DW.TimeStampA = 0.0;
  coupled_tanks_filtro_derivat_DW.LastUAtTimeA = 0.0;
  coupled_tanks_filtro_derivat_DW.TimeStampB = 0.0;
  coupled_tanks_filtro_derivat_DW.LastUAtTimeB = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    coupled_tanks_filtro_derivat_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 15;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  coupled_tanks_filtro_derivat_M->Sizes.numContStates = (2);/* Number of continuous states */
  coupled_tanks_filtro_derivat_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  coupled_tanks_filtro_derivat_M->Sizes.numY = (0);/* Number of model outputs */
  coupled_tanks_filtro_derivat_M->Sizes.numU = (0);/* Number of model inputs */
  coupled_tanks_filtro_derivat_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  coupled_tanks_filtro_derivat_M->Sizes.numSampTimes = (2);/* Number of sample times */
  coupled_tanks_filtro_derivat_M->Sizes.numBlocks = (21);/* Number of blocks */
  coupled_tanks_filtro_derivat_M->Sizes.numBlockIO = (10);/* Number of block outputs */
  coupled_tanks_filtro_derivat_M->Sizes.numBlockPrms = (109);/* Sum of parameter "widths" */
  return coupled_tanks_filtro_derivat_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
