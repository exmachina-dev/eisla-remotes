/* ###################################################################
**     Filename    : Events.c
**     Project     : varmo_lite
**     Processor   : MK20DX256VLH7
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-06-03, 16:50, # CodeGen: 62
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         PUSH_BUTTON_REC_OnInterrupt  - void PUSH_BUTTON_REC_OnInterrupt(void);
**         PUSH_BUTTON_SEND_OnInterrupt - void PUSH_BUTTON_SEND_OnInterrupt(void);
**         I2C0_OnReceiveData           - void I2C0_OnReceiveData(void);
**         I2C0_OnTransmitData          - void I2C0_OnTransmitData(void);
**         T_100ms_OnCounterRestart     - void T_100ms_OnCounterRestart(LDD_TUserData *UserDataPtr);
**         LEVER_DIR2_OnInterrupt       - void LEVER_DIR2_OnInterrupt(void);
**         LEVER_DIR1_OnInterrupt       - void LEVER_DIR1_OnInterrupt(void);
**         ENCODER_PUSH_OnInterrupt     - void ENCODER_PUSH_OnInterrupt(void);
**         ENCODER_OnPortEvent          - void ENCODER_OnPortEvent(LDD_TUserData *UserDataPtr);
**         T_500ms_OnCounterRestart     - void T_500ms_OnCounterRestart(LDD_TUserData *UserDataPtr);
**         Cpu_OnNMIINT                 - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  PUSH_BUTTON_REC_OnInterrupt (module Events)
**
**     Component   :  PUSH_BUTTON_REC [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PUSH_BUTTON_REC_OnInterrupt(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  PUSH_BUTTON_SEND_OnInterrupt (module Events)
**
**     Component   :  PUSH_BUTTON_SEND [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PUSH_BUTTON_SEND_OnInterrupt(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  I2C0_OnReceiveData (module Events)
**
**     Component   :  I2C0 [InternalI2C]
**     Description :
**         This event is invoked when I2C finishes the reception of the
**         data successfully. This event is not available for the SLAVE
**         mode and if both RecvChar and RecvBlock are disabled. This
**         event is enabled only if interrupts/events are enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void I2C0_OnReceiveData(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  I2C0_OnTransmitData (module Events)
**
**     Component   :  I2C0 [InternalI2C]
**     Description :
**         This event is invoked when I2C finishes the transmission of
**         the data successfully. This event is not available for the
**         SLAVE mode and if both SendChar and SendBlock are disabled.
**         This event is enabled only if interrupts/events are enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void I2C0_OnTransmitData(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  T_100ms_OnCounterRestart (module Events)
**
**     Component   :  T_100ms [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void T_100ms_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  LEVER_DIR2_OnInterrupt (module Events)
**
**     Component   :  LEVER_DIR2 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LEVER_DIR2_OnInterrupt(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  LEVER_DIR1_OnInterrupt (module Events)
**
**     Component   :  LEVER_DIR1 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LEVER_DIR1_OnInterrupt(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  ENCODER_PUSH_OnInterrupt (module Events)
**
**     Component   :  ENCODER_PUSH [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ENCODER_PUSH_OnInterrupt(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  ENCODER_OnPortEvent (module Events)
**
**     Component   :  ENCODER [GPIO_LDD]
*/
/*!
**     @brief
**         Called if defined event on any pin of the port occured.
**         OnPortEvent event and GPIO interrupt must be enabled. See
**         SetEventMask() and GetEventMask() methods. This event is
**         enabled if [Interrupt service/event] is Enabled and disabled
**         if [Interrupt service/event] is Disabled.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void ENCODER_OnPortEvent(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  T_500ms_OnCounterRestart (module Events)
**
**     Component   :  T_500ms [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void T_500ms_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK20DX256LH7]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  I2C0_OnArbitLost (module Events)
**
**     Component   :  I2C0 [InternalI2C]
**     Description :
**         This event is called when the master lost the bus
**         arbitration or the device detects an error on the bus. This
**         event is enabled only if interrupts/events are enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void I2C0_OnArbitLost(void)
{
  I2C0_SendStop();
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
