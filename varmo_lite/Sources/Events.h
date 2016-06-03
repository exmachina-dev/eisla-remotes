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
#include "DIRECTION_1.h"
#include "ExtIntLdd2.h"
#include "DIRECTION_2.h"
#include "ExtIntLdd3.h"
#include "T_100ms.h"
#include "LCD.h"
#include "IntI2cLdd1.h"
#include "PUSH_BUTTON_SEND.h"
#include "ExtIntLdd4.h"
#include "PUSH_BUTTON_REC.h"
#include "ExtIntLdd5.h"
#include "ESW3.h"
#include "ASerialLdd1.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK20DX256MC7]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


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

void DIRECTION_2_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  DIRECTION_2_OnInterrupt (module Events)
**
**     Component   :  DIRECTION_2 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void DIRECTION_1_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  DIRECTION_1_OnInterrupt (module Events)
**
**     Component   :  DIRECTION_1 [ExtInt]
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
**     Event       :  LCD_OnReceiveData (module Events)
**
**     Component   :  LCD [InternalI2C]
**     Description :
**         This event is invoked when I2C finishes the reception of the
**         data successfully. This event is not available for the SLAVE
**         mode and if both RecvChar and RecvBlock are disabled. This
**         event is enabled only if interrupts/events are enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LCD_OnReceiveData(void);

/*
** ===================================================================
**     Event       :  LCD_OnTransmitData (module Events)
**
**     Component   :  LCD [InternalI2C]
**     Description :
**         This event is invoked when I2C finishes the transmission of
**         the data successfully. This event is not available for the
**         SLAVE mode and if both SendChar and SendBlock are disabled.
**         This event is enabled only if interrupts/events are enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LCD_OnTransmitData(void);

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
**     Event       :  ESW3_OnError (module Events)
**
**     Component   :  ESW3 [AsynchroSerial]
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
