/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : PUSH_BUTTON_REC.c
**     Project     : varmo_lite
**     Processor   : MK20DX256VLH7
**     Component   : GPIO_LDD
**     Version     : Component 01.128, Driver 01.08, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-05-31, 01:57, # CodeGen: 38
**     Abstract    :
**         The HAL GPIO component will provide a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL GPIO API will be simpler and more
**         portable to various microprocessors.
**     Settings    :
**          Component name                                 : PUSH_BUTTON_REC
**          Port                                           : PTC
**          Port width                                     : 32 bits
**          Mask of allocated pins                         : 0x4
**          Interrupt service/event                        : Enabled
**            Interrupt                                    : INT_PORTC
**            Interrupt priority                           : medium priority
**          Bit fields                                     : 1
**            Bit field                                    : 
**              Field name                                 : REC
**              Pins                                       : 1
**                Pin                                      : 
**                  Pin                                    : ADC0_SE4b/CMP1_IN0/TSI0_CH15/PTC2/SPI0_PCS2/UART1_CTS_b/FTM0_CH1/I2S0_TX_FS
**                  Pin signal                             : 
**                  Initial pin direction                  : Input
**                  Initial pin event                      : Rising edge
**                  Lock initialization function           : no
**          Initialization                                 : 
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnPortEvent                                : Enabled
**     Contents    :
**         Init            - LDD_TDeviceData* PUSH_BUTTON_REC_Init(LDD_TUserData *UserDataPtr);
**         SetFieldValue   - void PUSH_BUTTON_REC_SetFieldValue(LDD_TDeviceData *DeviceDataPtr,...
**         GetFieldValue   - PUSH_BUTTON_REC_TFieldValue PUSH_BUTTON_REC_GetFieldValue(LDD_TDeviceData...
**         ClearFieldBits  - void PUSH_BUTTON_REC_ClearFieldBits(LDD_TDeviceData *DeviceDataPtr,...
**         SetFieldBits    - void PUSH_BUTTON_REC_SetFieldBits(LDD_TDeviceData *DeviceDataPtr,...
**         ToggleFieldBits - void PUSH_BUTTON_REC_ToggleFieldBits(LDD_TDeviceData *DeviceDataPtr,...
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
** @file PUSH_BUTTON_REC.c
** @version 01.08
** @brief
**         The HAL GPIO component will provide a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL GPIO API will be simpler and more
**         portable to various microprocessors.
*/         
/*!
**  @addtogroup PUSH_BUTTON_REC_module PUSH_BUTTON_REC module documentation
**  @{
*/         

/* MODULE PUSH_BUTTON_REC. */

#include "Events.h"
#include "PUSH_BUTTON_REC.h"
/* {Default RTOS Adapter} No RTOS includes */
#include "IO_Map.h"

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct {
  PUSH_BUTTON_REC_TPortValue EventFlags; /* Holds event flags */
  LDD_TUserData *UserData;             /* RTOS device data structure */
} PUSH_BUTTON_REC_TDeviceData, *PUSH_BUTTON_REC_TDeviceDataPtr; /* Device data structure type */
/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static PUSH_BUTTON_REC_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static PUSH_BUTTON_REC_TDeviceData * INT_PORTC__DEFAULT_RTOS_ISRPARAM;
/*
** ===================================================================
**     Method      :  PUSH_BUTTON_REC_Init (component GPIO_LDD)
*/
/*!
**     @brief
**         This method initializes the associated peripheral(s) and the
**         component internal variables. The method is called
**         automatically as a part of the application initialization
**         code.
**     @param
**         UserDataPtr     - Pointer to the RTOS device
**                           structure. This pointer will be passed to
**                           all events as parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* PUSH_BUTTON_REC_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate LDD device structure */
  PUSH_BUTTON_REC_TDeviceData *DeviceDataPrv;

  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  /* Save RTOS Device structure */
  DeviceDataPrv->EventFlags = 0x00U;   /* Clears stored events */
  DeviceDataPrv->UserData = UserDataPtr; /* Store the RTOS device structure */
  /* Interrupt vector(s) allocation */
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_PORTC__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  /* GPIOC_PDDR: PDD&=~4 */
  GPIOC_PDDR &= (uint32_t)~(uint32_t)(GPIO_PDDR_PDD(0x04));
  /* Initialization of Port Control registers */
  /* PORTC_PCR2: ISF=0,LK=0,MUX=1 */
  PORTC_PCR2 = (uint32_t)((PORTC_PCR2 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_LK_MASK |
                PORT_PCR_MUX(0x06)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x01)
               ));
  /* PORTC_PCR2: ISF=1,IRQC=9 */
  PORTC_PCR2 = (uint32_t)((PORTC_PCR2 & (uint32_t)~(uint32_t)(
                PORT_PCR_IRQC(0x06)
               )) | (uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_IRQC(0x09)
               ));
  /* NVICIP89: PRI89=0x80 */
  NVICIP89 = NVIC_IP_PRI89(0x80);
  /* NVICISER2: SETENA|=0x02000000 */
  NVICISER2 |= NVIC_ISER_SETENA(0x02000000);
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_PUSH_BUTTON_REC_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv);
}

/*
** ===================================================================
**     Method      :  PUSH_BUTTON_REC_SetFieldValue (component GPIO_LDD)
*/
/*!
**     @brief
**         This method sets the output data value of the specified bit
**         field.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to write. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @param
**         Value           - Aligned data value to writting to the
**                           specified bit field. The bit 0 corresponds
**                           with the pin which has index 0 within the
**                           given bit field, the bit 1 corresponds with
**                           the pin which has index 1 within the given
**                           bit field, etc.
*/
/* ===================================================================*/
void PUSH_BUTTON_REC_SetFieldValue(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, PUSH_BUTTON_REC_TFieldValue Value)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case REC: {                        /* bit field #0 */
      GPIO_PDD_SetPortDataOutput(PUSH_BUTTON_REC_MODULE_BASE_ADDRESS,
        (
          GPIO_PDD_GetPortDataOutput(PUSH_BUTTON_REC_MODULE_BASE_ADDRESS)
          & ((PUSH_BUTTON_REC_TPortValue)(~((PUSH_BUTTON_REC_TPortValue)PUSH_BUTTON_REC_REC_MASK)))
        )
        | (
          ((PUSH_BUTTON_REC_TPortValue)(Value << PUSH_BUTTON_REC_REC_START_BIT))
          & ((PUSH_BUTTON_REC_TPortValue)PUSH_BUTTON_REC_REC_MASK)
        )
      );
      break;
    }
    default:
      break;                           /* Invalid Field is not treated, result is undefined */
  } /* switch (Field) */
}

/*
** ===================================================================
**     Method      :  PUSH_BUTTON_REC_GetFieldValue (component GPIO_LDD)
*/
/*!
**     @brief
**         This method returns the current input data of the specified
**         field.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to reading. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @return
**                         - Aligned current port input value masked for
**                           allocated pins of the field. The bit 0
**                           corresponds with the pin which has index 0
**                           within the given bit field, the bit 1
**                           corresponds with the pin which has index 1
**                           within the given bit field, etc.
*/
/* ===================================================================*/
PUSH_BUTTON_REC_TFieldValue PUSH_BUTTON_REC_GetFieldValue(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case REC: {                        /* bit field #0 */
      return
        (PUSH_BUTTON_REC_TFieldValue)(
          (
            GPIO_PDD_GetPortDataInput(PUSH_BUTTON_REC_MODULE_BASE_ADDRESS)
            & (PUSH_BUTTON_REC_TPortValue)PUSH_BUTTON_REC_REC_MASK
          )
          >> PUSH_BUTTON_REC_REC_START_BIT
        );
    }
    default:
      break;                           /* Invalid BitField is not treated, result is undefined */
  } /* switch (Field) */
  return (PUSH_BUTTON_REC_TFieldValue)0U;
}

/*
** ===================================================================
**     Method      :  PUSH_BUTTON_REC_ClearFieldBits (component GPIO_LDD)
*/
/*!
**     @brief
**         This method drives the specified bits of the specified bit
**         field to the inactive level.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to write. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @param
**         Mask            - Aligned mask of bits to setting the
**                           inactive level. Each field pin has
**                           corresponding bit in the mask. Bit value 0
**                           means not selected bit, bit value 1 means
**                           selected bit. The bit 0 corresponds with
**                           the pin which has index 0 within the given
**                           bit field, the bit 1 corresponds with the
**                           pin which has index 1 within the given bit
**                           field, etc.
*/
/* ===================================================================*/
void PUSH_BUTTON_REC_ClearFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, PUSH_BUTTON_REC_TFieldValue Mask)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case REC: {                        /* bit field #0 */
      GPIO_PDD_ClearPortDataOutputMask(PUSH_BUTTON_REC_MODULE_BASE_ADDRESS,
        ((PUSH_BUTTON_REC_TPortValue)PUSH_BUTTON_REC_REC_MASK)
        & ((PUSH_BUTTON_REC_TPortValue)(Mask << PUSH_BUTTON_REC_REC_START_BIT))
      );
      break;
    }
    default:
      break;                           /* Invalid Field is not treated, result is undefined */
  } /* switch (Field) */
}

/*
** ===================================================================
**     Method      :  PUSH_BUTTON_REC_SetFieldBits (component GPIO_LDD)
*/
/*!
**     @brief
**         This method drives the specified bits of the specified bit
**         field to the active level.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to write. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @param
**         Mask            - Aligned mask of bits to setting the
**                           active level. Each field pin has
**                           corresponding bit in the mask. Bit value 0
**                           means not selected bit, bit value 1 means
**                           selected bit. The bit 0 corresponds with
**                           the pin which has index 0 within the given
**                           bit field, the bit 1 corresponds with the
**                           pin which has index 1 within the given bit
**                           field, etc.
*/
/* ===================================================================*/
void PUSH_BUTTON_REC_SetFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, PUSH_BUTTON_REC_TFieldValue Mask)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case REC: {                        /* bit field #0 */
      GPIO_PDD_SetPortDataOutputMask(PUSH_BUTTON_REC_MODULE_BASE_ADDRESS,
        ((PUSH_BUTTON_REC_TPortValue)PUSH_BUTTON_REC_REC_MASK)
        & ((PUSH_BUTTON_REC_TPortValue)(Mask << PUSH_BUTTON_REC_REC_START_BIT))
      );
      break;
    }
    default:
      break;                           /* Invalid Field is not treated, result is undefined */
  } /* switch (Field) */
}

/*
** ===================================================================
**     Method      :  PUSH_BUTTON_REC_ToggleFieldBits (component GPIO_LDD)
*/
/*!
**     @brief
**         This method inverts the specified bits of the specified bit
**         field to other level.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Field           - Bit field to write. Bit fields are
**                           defined during design time and for each bit
**                           field there is a generated constant.
**     @param
**         Mask            - Aligned mask of bits to inverting the
**                           current level. Each field pin has
**                           corresponding bit in the mask. Bit value 0
**                           means not selected bit, bit value 1 means
**                           selected bit. The bit 0 corresponds with
**                           the pin which has index 0 within the given
**                           bit field, the bit 1 corresponds with the
**                           pin which has index 1 within the given bit
**                           field, etc.
*/
/* ===================================================================*/
void PUSH_BUTTON_REC_ToggleFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, PUSH_BUTTON_REC_TFieldValue Mask)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case REC: {                        /* bit field #0 */
      GPIO_PDD_TogglePortDataOutputMask(PUSH_BUTTON_REC_MODULE_BASE_ADDRESS,
        ((PUSH_BUTTON_REC_TPortValue)PUSH_BUTTON_REC_REC_MASK)
        & ((PUSH_BUTTON_REC_TPortValue)(Mask << PUSH_BUTTON_REC_REC_START_BIT))
      );
      break;
    }
    default:
      break;                           /* Invalid Field is not treated, result is undefined */
  } /* switch (Field) */
}

/*
** ===================================================================
**     Method      :  PUSH_BUTTON_REC_Interrupt (component GPIO_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PUSH_BUTTON_REC_Interrupt(void)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  PUSH_BUTTON_REC_TDeviceDataPtr DeviceDataPrv = INT_PORTC__DEFAULT_RTOS_ISRPARAM;
  PUSH_BUTTON_REC_TPortValue State;

  State = (PUSH_BUTTON_REC_TPortValue)(PORT_PDD_GetInterruptFlags(PUSH_BUTTON_REC_PORTCONTROL_BASE_ADDRESS)
          & ((PUSH_BUTTON_REC_TPortValue)PUSH_BUTTON_REC_ALLOCATED_PINS_MASK)); /* Retrieve flags */
  DeviceDataPrv->EventFlags |= State;
  if (State) {
    PORT_PDD_ClearInterruptFlags(PUSH_BUTTON_REC_PORTCONTROL_BASE_ADDRESS, State); /* Clears flags */
    PUSH_BUTTON_REC_OnPortEvent(DeviceDataPrv->UserData); /* Call OnPortEvent event */
  }
}

/* END PUSH_BUTTON_REC. */

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
