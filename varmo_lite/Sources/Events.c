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
**         LEVER_DIR1_OnInterrupt       - void LEVER_DIR1_OnInterrupt(void);
**         LEVER_DIR2_OnInterrupt       - void LEVER_DIR2_OnInterrupt(void);
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

#include "protocol.h"
#include "encoder_variable.h"
#include "send.h"
#include "display.h"

//#include "ENCODER.h"
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
  FLAG_REC = 1;
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
  FLAG_SEND = 1;
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
    counter_100ms += 1;
    if (counter_100ms == 5){
        FLAG_PUSH_LONG = 1;
        FLAG_PUSH_SHORT = 0;
        T_100ms_Disable(T_100ms_DeviceData);
    }
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
	FLAG_SENS = 1;
    if (LEVER_DIR1_GetVal() == 0) {
    	FLAG_SENS_2 = 1;
    }
    else{
    	FLAG_SENS_2 = 0;
    	FLAG_STOP = 1;
    }

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
	FLAG_SENS = 1;
    if (LEVER_DIR2_GetVal() == 0) {
    	FLAG_SENS_1 = 1;
    }
    else{
    	FLAG_SENS_1 = 0;
    	FLAG_STOP = 1;
    }
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
	WAIT1_Waitms(5);
	bool encoder_value = ENCODER_PUSH_GetVal();
    if (encoder_value == 0 && FLAG_PUSH_LONG == 0 && FLAG_PUSH_SHORT == 0){ //Encoder Pushed
    	counter_100ms = 0;
        FLAG_PUSH_SHORT = 0;
        FLAG_PUSH_LONG = 0;
        T_100ms_Enable(T_100ms_DeviceData);

    }
    else if (encoder_value == 1 && counter_100ms < 5 && FLAG_PUSH_LONG == 0 && FLAG_PUSH_SHORT == 0){
        T_100ms_Disable(T_100ms_DeviceData);
        counter_100ms = 5;
        FLAG_PUSH_SHORT = 1;
        FLAG_PUSH_LONG = 0;
    }
    else if (ENCODER_PUSH_GetVal() == 1){
    	T_100ms_Disable(T_100ms_DeviceData);
    }

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
    if (FLAG_DEBOUNCE == 1){
    	TU1_Disable(TU1_DeviceData);
    	WAIT1_Waitms(2.5);
		uint8_t ENC_A = ENCODER_GetFieldValue(&UserDataPtr, ENCODER_A);
		uint8_t ENC_B = ENCODER_GetFieldValue(&UserDataPtr, ENCODER_B);
		if ( ENC_B == 1){
			if (ENC_A == 0){
				FLAG_DEBOUNCE = 0;
				encoder -= 1;
				TU1_Enable(TU1_DeviceData);
				FLAG_ENCODER = 1;
			}
			else if (ENC_A == 1){
				FLAG_DEBOUNCE = 0;
				encoder += 1;
				TU1_Enable(TU1_DeviceData);
				FLAG_ENCODER = 1;
			}
		}
	}
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
	LED_MOTOR_MOVE_SetVal();
	if (FLAG_MENU == 0){
		FLAG_UPDATE_MENU = 1;
	}

	if (FLAG_SET_HOME == 1){
		counter_2s += 1;
	}
	if(counter_2s == 4){
		FLAG_SET_HOME = 0;
	}

	if (FLAG_CUE_SELECTED == 1){
		counter_2s += 1;
	}
	if(counter_2s == 4){
		FLAG_CUE_SELECTED = 0;
		FLAG_UPDATE_CUE = 1;
		counter_2s = 0;
	}

	if (FLAG_STOP == 1){
		FLAG_SEND_STOP = 1;
	}

	if (FLAG_UPDATE == 0){
		FLAG_UPDATE = 1;
	}


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
  //I2C0_SendStop();
}

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
void AS1_OnTxComplete(void)
{
	LED_STATUS_3_ClrVal();
	/* Write your code here ... */
}

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
void AS1_OnError(void)
{
  /* Write your code here ... */
}

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
void AS1_OnRxChar(void)
{
  /* Write your code here ... */
}

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
void AS1_OnRxCharExt(AS1_TComData Chr)
{
	LED_STATUS_3_SetVal();
	if (cnt > 0){
		if (Chr == '\n' && in_buffer[cnt-1] == '\r'){
			//End of a message
			in_buffer[cnt] = Chr;
			FLAG_MSG_RCV = 1;
			AS1_ClearRxBuf();
		}
		else{
			if (Chr == '\0'){
				in_buffer[cnt] = '\0';
			}
			else {
				in_buffer[cnt]= Chr;
			}
			cnt ++;
		}
	}
	else if(cnt>512){
		AS1_ClearRxBuf();
	}
	else{
		in_buffer[cnt]= Chr;
		cnt ++;
	}

}

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
void AS1_OnTxChar(void)
{
	/* Write your code here ... */
}

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
void AS1_OnFullRxBuf(void)
{
	AS1_ClearRxBuf();
	FLAG_MSG_ERR = 1;
}

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
void AS1_OnFreeTxBuf(void)
{

}

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
void TU1_OnCounterRestart(LDD_TUserData *UserDataPtr)
{

	FLAG_DEBOUNCE = 1;
	//TU1_Disable(TU1_DeviceData);
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
