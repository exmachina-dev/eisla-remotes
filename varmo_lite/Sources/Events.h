/* ###################################################################
**     Filename    : Events.h
**     Project     : varmo_lite
**     Processor   : MK20DX256VLH7
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-05-30, 15:08, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "LED_DEBUG.h"
#include "BitIoLdd1.h"
#include "T_500ms.h"
#include "LED_STATUS_1.h"
#include "BitIoLdd2.h"
#include "LED_STATUS_2.h"
#include "BitIoLdd3.h"
#include "LED_STATUS_3.h"
#include "BitIoLdd4.h"
#include "LED_STATUS_4.h"
#include "BitIoLdd5.h"
#include "ENCODER.h"
#include "ENCODER_PUSH.h"
#include "ExtIntLdd1.h"
#include "LEVER_DIR2.h"
#include "ExtIntLdd2.h"
#include "LEVER_DIR1.h"
#include "ExtIntLdd3.h"
#include "T_100ms.h"
#include "I2C0.h"
#include "IntI2cLdd1.h"
#include "PUSH_BUTTON_SEND.h"
#include "ExtIntLdd4.h"
#include "PUSH_BUTTON_REC.h"
#include "ExtIntLdd5.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "LCD_CTR.h"
#include "BitIoLdd6.h"
#include "WAIT1.h"
#include "LCD_EN.h"
#include "BitIoLdd7.h"
#include "TU1.h"
#include "IFsh1.h"
#include "IntFlashLdd1.h"
#include "LED_MOTOR_MOVE.h"
#include "BitIoLdd8.h"
#include "KSDK1.h"
#include "CS1.h"

#ifdef __cplusplus
extern "C" {
#endif 

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
void T_500ms_OnCounterRestart(LDD_TUserData *UserDataPtr);

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
void ENCODER_OnPortEvent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  DIRECTION_OnPortEvent (module Events)
**
**     Component   :  DIRECTION [GPIO_LDD]
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
void DIRECTION_OnPortEvent(LDD_TUserData *UserDataPtr);

void ENCODER_PUSH_OnInterrupt(void);
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

void LEVER_DIR1_OnInterrupt(void);
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

void LEVER_DIR2_OnInterrupt(void);
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
void T_100ms_OnCounterRestart(LDD_TUserData *UserDataPtr);

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
void I2C0_OnReceiveData(void);

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
void I2C0_OnTransmitData(void);

void PUSH_BUTTON_SEND_OnInterrupt(void);
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

void PUSH_BUTTON_REC_OnInterrupt(void);
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

/*
** ===================================================================
<<<<<<< HEAD
**     Event       :  ESW3_OnError (module Events)
**
**     Component   :  ESW3 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
=======
**     Event       :  I2C0_OnArbitLost (module Events)
**
**     Component   :  I2C0 [InternalI2C]
**     Description :
**         This event is called when the master lost the bus
**         arbitration or the device detects an error on the bus. This
**         event is enabled only if interrupts/events are enabled.
>>>>>>> BR
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
<<<<<<< HEAD
void ESW3_OnError(void);

/*
** ===================================================================
**     Event       :  ESW3_OnRxChar (module Events)
**
**     Component   :  ESW3 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ESW3_OnRxChar(void);

/*
** ===================================================================
**     Event       :  ESW3_OnTxChar (module Events)
**
**     Component   :  ESW3 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ESW3_OnTxChar(void);

/*
** ===================================================================
**     Event       :  ESW3_OnFullRxBuf (module Events)
**
**     Component   :  ESW3 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ESW3_OnFullRxBuf(void);

/*
** ===================================================================
**     Event       :  ESW3_OnFreeTxBuf (module Events)
**
**     Component   :  ESW3 [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ESW3_OnFreeTxBuf(void);
=======
void I2C0_OnArbitLost(void);
>>>>>>> BR

/*
** ===================================================================
**     Event       :  AS1_OnTxComplete (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event indicates that the transmitter is finished
**         transmitting all data, preamble, and break characters and is
**         idle. It can be used to determine when it is safe to switch
**         a line driver (e.g. in RS-485 applications).
**         The event is available only when both <Interrupt
**         service/event> and <Transmitter> properties are enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnTxComplete(void);

/*
** ===================================================================
**     Event       :  AS1_OnError (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnError(void);

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnRxChar(void);

/*
** ===================================================================
**     Event       :  AS1_OnRxCharExt (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The last received character is passed as a parameter of the
**         event function.
**         Nevertheless, the last received character is placed in the
**         external buffer of the component.
**         This event is identical in function with the <OnRxChar>
**         event with a parameter added. It is not recommended to use
**         both <OnRxChar> and OnRxCharExt events at the same time.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - The last character correctly received.
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnRxCharExt(AS1_TComData Chr);

/*
** ===================================================================
**     Event       :  AS1_OnTxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnTxChar(void);

/*
** ===================================================================
**     Event       :  AS1_OnFullRxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnFullRxBuf(void);

/*
** ===================================================================
**     Event       :  AS1_OnFreeTxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnFreeTxBuf(void);

/*
** ===================================================================
**     Event       :  TU1_OnCounterRestart (module Events)
**
**     Component   :  TU1 [TimerUnit_LDD]
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
void TU1_OnCounterRestart(LDD_TUserData *UserDataPtr);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
