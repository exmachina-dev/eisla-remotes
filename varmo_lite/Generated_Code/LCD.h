/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : LCD.h
**     Project     : varmo_lite
**     Processor   : MK20DX256VLH7
**     Component   : InternalI2C
**     Version     : Component 01.287, Driver 01.01, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-06-02, 00:17, # CodeGen: 55
**     Abstract    :
**          This component encapsulates the internal I2C communication 
**          interface. The implementation of the interface is based 
**          on the Philips I2C-bus specification version 2.0. 
**          Interface features:
**          MASTER mode
**            - Multi master communication
**            - The combined format of communication possible 
**              (see "Automatic stop condition" property)
**            - 7-bit slave addressing (10-bit addressing can be made as well)
**            - Acknowledge polling provided
**            - No wait state initiated when a slave device holds the SCL line low
**            - Holding of the SCL line low by slave device recognized as 'not available bus'
**            - Invalid start/stop condition detection provided
**          SLAVE mode
**            - 7-bit slave addressing
**            - General call address detection provided
**     Settings    :
**          Component name                                 : LCD
**          I2C_LDD                                        : I2C_LDD
**          I2C channel                                    : I2C0
**          Mode selection                                 : MASTER
**          Interrupt service/event                        : Enabled
**            Interrupt                                    : INT_I2C0
**            Interrupt priority                           : medium priority
**            Buffers for SLAVE mode                       : Disabled
**          MASTER mode                                    : Enabled
**            Polling trials                               : 2000
**            Automatic stop condition                     : yes
**            Initialization                               : 
**              Address mode                               : 7-bit addressing
**              Target slave address init                  : 0x70
**          SLAVE mode                                     : Disabled
**          Data and Clock                                 : 
**            SDA pin                                      : ADC0_SE9/ADC1_SE9/TSI0_CH6/PTB1/I2C0_SDA/FTM1_CH1/FTM1_QD_PHB
**            SDA pin signal                               : 
**            SCL pin                                      : ADC0_SE8/ADC1_SE8/TSI0_CH0/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/FTM1_QD_PHA
**            SCL pin signal                               : 
**            High drive select                            : Enabled
**          Internal frequency (multiplier factor)         : 47.988736 MHz
**          Bits 0-2 of Frequency divider register         : 111
**          Bits 3-5 of Frequency divider register         : 100
**          SCL frequency                                  : 99.977 kHz
**          SDA Hold                                       : 1.354 us
**          Noise (glitch) filter                          : 0
**          Low timeout                                    : Disabled
**          Wake-up                                        : Disabled
**          Initialization                                 : 
**            Enabled in init code                         : yes
**            Events enabled in init.                      : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : Enabled
**            Low speed mode                               : Disabled
**            Slow speed mode                              : Disabled
**     Contents    :
**         SendChar        - byte LCD_SendChar(byte Chr);
**         RecvChar        - byte LCD_RecvChar(byte *Chr);
**         SendBlock       - byte LCD_SendBlock(void* Ptr, word Siz, word *Snt);
**         RecvBlock       - byte LCD_RecvBlock(void* Ptr, word Siz, word *Rcv);
**         GetCharsInTxBuf - word LCD_GetCharsInTxBuf(void);
**         GetCharsInRxBuf - word LCD_GetCharsInRxBuf(void);
**         SelectSlave     - byte LCD_SelectSlave(byte Slv);
**         GetMode         - bool LCD_GetMode(void);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file LCD.h
** @version 01.01
** @brief
**          This component encapsulates the internal I2C communication 
**          interface. The implementation of the interface is based 
**          on the Philips I2C-bus specification version 2.0. 
**          Interface features:
**          MASTER mode
**            - Multi master communication
**            - The combined format of communication possible 
**              (see "Automatic stop condition" property)
**            - 7-bit slave addressing (10-bit addressing can be made as well)
**            - Acknowledge polling provided
**            - No wait state initiated when a slave device holds the SCL line low
**            - Holding of the SCL line low by slave device recognized as 'not available bus'
**            - Invalid start/stop condition detection provided
**          SLAVE mode
**            - 7-bit slave addressing
**            - General call address detection provided
*/         
/*!
**  @addtogroup LCD_module LCD module documentation
**  @{
*/         

#ifndef __LCD
#define __LCD

/* MODULE LCD. */

/* Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited components */
#include "IntI2cLdd1.h"
#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* MODULE LCD. */

extern word LCD_SndRcvTemp;

/*
** ===================================================================
**     Method      :  LCD_Interrupt (component InternalI2C)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(LCD_Interrupt);

/*
** ===================================================================
**     Method      :  LCD_SendChar (component InternalI2C)
**     Description :
**         When working as a MASTER, this method writes one (7-bit
**         addressing) or two (10-bit addressing) slave address bytes
**         inclusive of R/W bit = 0 to the I2C bus and then writes one
**         character (byte) to the bus. The slave address must be
**         specified before, by the "SelectSlave" or "SelectSlave10"
**         method or in the component initialization section, "Target
**         slave address init" property. If interrupt service is
**         enabled and the method returns ERR_OK, it doesn't mean that
**         transmission was successful. The state of transmission is
**         obtainable from (OnTransmitData, OnError or OnArbitLost)
**         events. 
**         When working as a SLAVE, this method writes a character to
**         the internal output slave buffer and, after the master
**         starts the communication, to the I2C bus. If no character is
**         ready for a transmission (internal output slave buffer is
**         empty), the Empty character will be sent (see "Empty
**         character" property).
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  Device is disabled
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by an acknowledge (only in
**                           master mode and when interrupt service is
**                           disabled)
**                           ERR_BUSOFF - Clock timeout elapsed or
**                           device cannot transmit data
**                           ERR_TXFULL - Transmitter is full (slave
**                           mode only)
**                           ERR_ARBITR - Arbitration lost (only when
**                           interrupt service is disabled and in master
**                           mode)
** ===================================================================
*/
byte LCD_SendChar(byte Chr);

/*
** ===================================================================
**     Method      :  LCD_RecvChar (component InternalI2C)
**     Description :
**         When working as a MASTER, this method writes one (7-bit
**         addressing) or two (10-bit addressing) slave address bytes
**         inclusive of R/W bit = 1 to the I2C bus, then reads one
**         character (byte) from the bus and then sends the stop
**         condition. The slave address must be specified before, by
**         the "SelectSlave" or "SelectSlave10" method or in component
**         initialization section, property "Target slave address init".
**         If interrupt service is enabled and the method returns
**         ERR_OK, it doesn't mean that transmission was finished
**         successfully. The state of transmission must be tested by
**         means of events (OnReceiveData, OnError or OnArbitLost). In
**         case of successful transmission, received data is ready
**         after OnReceiveData event is called. 
**         When working as a SLAVE, this method reads a character from
**         the input slave buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Received character.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  Device is disabled
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledge (only
**                           in master mode and when interrupt service
**                           is disabled)
**                           ERR_BUSOFF - Clock timeout elapsed or
**                           device cannot receive data
**                           ERR_RXEMPTY - No data in receiver (slave
**                           mode only)
**                           ERR_OVERRUN - Overrun error was detected
**                           from the last character or block received
**                           (slave mode only)
**                           ERR_ARBITR - Arbitration lost (only when
**                           interrupt service is disabled and in master
**                           mode)
**                           ERR_NOTAVAIL - Method is not available in
**                           current mode - see the comment in the
**                           generated code
** ===================================================================
*/
#define LCD_RecvChar(Chr) LCD_RecvBlock((Chr), 1U, &LCD_SndRcvTemp)

/*
** ===================================================================
**     Method      :  LCD_SendBlock (component InternalI2C)
**     Description :
**         When working as a MASTER, this method writes one (7-bit
**         addressing) or two (10-bit addressing) slave address bytes
**         inclusive of R/W bit = 0 to the I2C bus and then writes the
**         block of characters to the bus. The slave address must be
**         specified before, by the "SelectSlave" or "SlaveSelect10"
**         method or in component initialization section, "Target slave
**         address init" property. If interrupt service is enabled and
**         the method returns ERR_OK, it doesn't mean that transmission
**         was successful. The state of transmission is detectable by
**         means of events (OnTransmitData, OnError or OnArbitLost).
**         Data to be send is not copied to an internal buffer and
**         remains in the original location. Therefore the content of
**         the buffer should not be changed until the transmission is
**         complete. Event OnTransmitData can be used to detect the end
**         of the transmission.
**         When working as a SLAVE, this method writes a block of
**         characters to the internal output slave buffer and then,
**         after the master starts the communication, to the I2C bus.
**         If no character is ready for a transmission (internal output
**         slave buffer is empty), the "Empty character" will be sent
**         (see "Empty character" property). In SLAVE mode the data are
**         copied to an internal buffer, if specified by "Output buffer
**         size" property.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - Pointer to the block of data to send.
**         Siz             - Size of the block.
**       * Snt             - Amount of data sent (moved to a buffer).
**                           In master mode, if interrupt support is
**                           enabled, the parameter always returns the
**                           same value as the parameter 'Siz' of this
**                           method.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  Device is disabled
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledge (only
**                           in master mode and when interrupt service
**                           is disabled)
**                           ERR_BUSOFF - Clock timeout elapsed or
**                           device cannot transmit data
**                           ERR_TXFULL - Transmitter is full. Some data
**                           has not been sent. (slave mode only)
**                           ERR_ARBITR - Arbitration lost (only when
**                           interrupt service is disabled and in master
**                           mode)
** ===================================================================
*/
byte LCD_SendBlock(void *Ptr,word Siz,word *Snt);

/*
** ===================================================================
**     Method      :  LCD_RecvBlock (component InternalI2C)
**     Description :
**         When working as a MASTER, this method writes one (7-bit
**         addressing) or two (10-bit addressing) slave address bytes
**         inclusive of R/W bit = 1 to the I2C bus, then reads the
**         block of characters from the bus and then sends the stop
**         condition. The slave address must be specified before, by
**         the "SelectSlave" or "SelectSlave10" method or in component
**         initialization section, "Target slave address init" property.
**         If interrupt service is enabled and the method returns
**         ERR_OK, it doesn't mean that transmission was finished
**         successfully. The state of transmission must be tested by
**         means of events (OnReceiveData, OnError or OnArbitLost). In
**         case of successful transmission, received data is ready
**         after OnReceiveData event is called. 
**         When working as a SLAVE, this method reads a block of
**         characters from the input slave buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - A pointer to the block space for received
**                           data.
**         Siz             - The size of the block.
**       * Rcv             - Amount of received data. In master mode,
**                           if interrupt support is enabled, the
**                           parameter always returns the same value as
**                           the parameter 'Siz' of this method.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  Device is disabled
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by an acknowledge (only in
**                           master mode and when interrupt service is
**                           disabled)
**                           ERR_BUSOFF - Clock timeout elapsed or
**                           device cannot receive data
**                           ERR_RXEMPTY - The receive buffer didn't
**                           contain the requested number of data. Only
**                           available data (or no data) has been
**                           returned  (slave mode only).
**                           ERR_OVERRUN - Overrun error was detected
**                           from last character or block receiving
**                           (slave mode only)
**                           ERR_ARBITR - Arbitration lost (only when
**                           interrupt service is disabled and in master
**                           mode)
**                           ERR_NOTAVAIL - Method is not available in
**                           current mode - see the comment in the
**                           generated code.
** ===================================================================
*/
byte LCD_RecvBlock(void* Ptr,word Siz,word *Rcv);

/*
** ===================================================================
**     Method      :  LCD_GetCharsInTxBuf (component InternalI2C)
**     Description :
**         Returns number of characters in the output buffer. In SLAVE
**         mode returns the number of characters in the internal slave
**         output buffer. In MASTER mode returns number of characters
**         to be sent from the user buffer (passed by SendBlock method).
**         This method is not supported in polling mode.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the output buffer.
** ===================================================================
*/
word LCD_GetCharsInTxBuf(void);

/*
** ===================================================================
**     Method      :  LCD_GetCharsInRxBuf (component InternalI2C)
**     Description :
**         Returns number of characters in the input buffer. In SLAVE
**         mode returns the number of characters in the internal slave
**         input buffer. In MASTER mode returns number of characters to
**         be received into a user buffer (passed by RecvChar or
**         RecvBlock method).
**         This method is not supported in polling mode.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the input buffer.
** ===================================================================
*/
word LCD_GetCharsInRxBuf(void);

/*
** ===================================================================
**     Method      :  LCD_SelectSlave (component InternalI2C)
**     Description :
**         This method selects a new slave for communication by its
**         7-bit slave address value. Any send or receive method
**         directs to or from selected device, until a new slave device
**         is selected by this method. This method is not available for
**         the SLAVE mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Slv             - 7-bit slave address value.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_BUSY - The device is busy, wait until
**                           the current operation is finished.
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  The device is disabled
** ===================================================================
*/
byte LCD_SelectSlave(byte Slv);

/*
** ===================================================================
**     Method      :  LCD_GetMode (component InternalI2C)
**     Description :
**         This method returns the actual operating mode of this
**         component.
**     Parameters  : None
**     Returns     :
**         ---             - Actual operating mode value <true> -
**                           Master <false> - Slave
** ===================================================================
*/
#define LCD_GetMode() ((bool)0x80)

/*
** ===================================================================
**     Method      :  LCD_Init (component InternalI2C)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void LCD_Init(void);

/*
** ===================================================================
**     Method      :  LCD_IntI2cLdd1_OnMasterBlockSent (component InternalI2C)
**
**     Description :
**         This event is called when I2C in master mode finishes the 
**         transmission of the data successfully. This event is not 
**         available for the SLAVE mode and if MasterSendBlock is 
**         disabled.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void IntI2cLdd1_OnMasterBlockSent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  LCD_IntI2cLdd1_OnMasterBlockReceived (component InternalI2C)
**
**     Description :
**         This event is called when I2C is in master mode and finishes 
**         the reception of the data successfully. This event is not 
**         available for the SLAVE mode and if MasterReceiveBlock is 
**         disabled.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void IntI2cLdd1_OnMasterBlockReceived(LDD_TUserData *UserDataPtr);


/* END LCD. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif /* ifndef __LCD */
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
