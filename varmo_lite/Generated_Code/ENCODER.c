/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : ENCODER.c
**     Project     : varmo_lite
**     Processor   : MK20DX256VLH7
**     Component   : GPIO_LDD
**     Version     : Component 01.128, Driver 01.08, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-08-18, 16:20, # CodeGen: 194
**     Abstract    :
**         The HAL GPIO component will provide a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL GPIO API will be simpler and more
**         portable to various microprocessors.
**     Settings    :
**          Component name                                 : ENCODER
**          Port                                           : PTC
**          Port width                                     : 32 bits
**          Mask of allocated pins                         : 0x180
**          Interrupt service/event                        : Enabled
**            Interrupt                                    : INT_PORTC
**            Interrupt priority                           : medium priority
**          Bit fields                                     : 2
**            Bit field                                    : 
**              Field name                                 : ENCODER_B
**              Pins                                       : 1
**                Pin                                      : 
**                  Pin                                    : CMP0_IN1/PTC7/SPI0_SIN/USB_SOF_OUT/I2S0_RX_FS
**                  Pin signal                             : 
**                  Initial pin direction                  : Input
**                  Initial pin event                      : Rising edge
**                  Lock initialization function           : no
**            Bit field                                    : 
**              Field name                                 : ENCODER_A
**              Pins                                       : 1
**                Pin                                      : 
**                  Pin                                    : ADC1_SE4b/CMP0_IN2/PTC8/I2S0_MCLK
**                  Pin signal                             : 
**                  Initial pin direction                  : Input
**                  Initial pin event                      : Disabled
**                  Lock initialization function           : no
**          Initialization                                 : 
**            Auto initialization                          : yes
**            Event mask                                   : 
**              OnPortEvent                                : Enabled
**     Contents    :
**         Init               - LDD_TDeviceData* ENCODER_Init(LDD_TUserData *UserDataPtr);
**         GetPortEventStatus - ENCODER_TPortValue ENCODER_GetPortEventStatus(LDD_TDeviceData *DeviceDataPtr);
**         SetFieldValue      - void ENCODER_SetFieldValue(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField...
**         GetFieldValue      - ENCODER_TFieldValue ENCODER_GetFieldValue(LDD_TDeviceData *DeviceDataPtr,...
**         ClearFieldBits     - void ENCODER_ClearFieldBits(LDD_TDeviceData *DeviceDataPtr,...
**         SetFieldBits       - void ENCODER_SetFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField...
**         ToggleFieldBits    - void ENCODER_ToggleFieldBits(LDD_TDeviceData *DeviceDataPtr,...
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
** @file ENCODER.c
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
**  @addtogroup ENCODER_module ENCODER module documentation
**  @{
*/         

/* MODULE ENCODER. */

#include "Events.h"
#include "ENCODER.h"
/* {Default RTOS Adapter} No RTOS includes */
#include "IO_Map.h"

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct {
  ENCODER_TPortValue EventFlags;       /* Holds event flags */
  LDD_TUserData *UserData;             /* RTOS device data structure */
} ENCODER_TDeviceData, *ENCODER_TDeviceDataPtr; /* Device data structure type */
/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static ENCODER_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static ENCODER_TDeviceData * INT_PORTC__DEFAULT_RTOS_ISRPARAM;
/*
** ===================================================================
**     Method      :  ENCODER_Init (component GPIO_LDD)
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
LDD_TDeviceData* ENCODER_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate LDD device structure */
  ENCODER_TDeviceData *DeviceDataPrv;

  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  /* Save RTOS Device structure */
  DeviceDataPrv->EventFlags = 0x00U;   /* Clears stored events */
  DeviceDataPrv->UserData = UserDataPtr; /* Store the RTOS device structure */
  /* Interrupt vector(s) allocation */
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_PORTC__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  /* GPIOC_PDDR: PDD&=~0x0180 */
  GPIOC_PDDR &= (uint32_t)~(uint32_t)(GPIO_PDDR_PDD(0x0180));
  /* Initialization of Port Control registers */
  /* PORTC_PCR7: ISF=0,LK=0,MUX=1 */
  PORTC_PCR7 = (uint32_t)((PORTC_PCR7 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_LK_MASK |
                PORT_PCR_MUX(0x06)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x01)
               ));
  /* PORTC_PCR8: ISF=0,LK=0,MUX=1 */
  PORTC_PCR8 = (uint32_t)((PORTC_PCR8 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_LK_MASK |
                PORT_PCR_MUX(0x06)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x01)
               ));
  /* PORTC_PCR7: ISF=1,IRQC=9 */
  PORTC_PCR7 = (uint32_t)((PORTC_PCR7 & (uint32_t)~(uint32_t)(
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
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_ENCODER_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv);
}

/*
** ===================================================================
**     Method      :  ENCODER_GetPortEventStatus (component GPIO_LDD)
*/
/*!
**     @brief
**         Returns a set of asserted flags. The flags are accumulated
**         in the set. After calling this method the set is returned
**         and cleared.
**         Note: Some type of "Port" device requires enabling
**         "Interrupt service/event" property for a pin edge detect
**         function.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Current status flags. Each port pin has
**                           corresponding bit in the mask. Bit value 0
**                           means condition didn't occur on
**                           corresponding pin, bit value 1 means
**                           condition occured on corresponding pin. The
**                           bit 0 corresponds with the pin which has
**                           index 0 within the port, the bit 1
**                           corresponds with the pin which has index 1
**                           within the port, etc.
*/
/* ===================================================================*/
ENCODER_TPortValue ENCODER_GetPortEventStatus(LDD_TDeviceData *DeviceDataPtr)
{
  ENCODER_TPortValue RetrievedFlags;   /* Contains flags */
  ENCODER_TDeviceData *DeviceDataPrv = (ENCODER_TDeviceData *)DeviceDataPtr;

  /* {Default RTOS Adapter} Critical section begin, general PE function is used */
  EnterCritical();
  RetrievedFlags = DeviceDataPrv->EventFlags; /* Temporary saved flags */
  DeviceDataPrv->EventFlags = 0U;      /* Clear flags */
  /* {Default RTOS Adapter} Critical section end, general PE function is used */
  ExitCritical();
  return RetrievedFlags;
}

/*
** ===================================================================
**     Method      :  ENCODER_SetFieldValue (component GPIO_LDD)
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
void ENCODER_SetFieldValue(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, ENCODER_TFieldValue Value)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case ENCODER_B: {                  /* bit field #0 */
      GPIO_PDD_SetPortDataOutput(ENCODER_MODULE_BASE_ADDRESS,
        (
          GPIO_PDD_GetPortDataOutput(ENCODER_MODULE_BASE_ADDRESS)
          & ((ENCODER_TPortValue)(~((ENCODER_TPortValue)ENCODER_ENCODER_B_MASK)))
        )
        | (
          ((ENCODER_TPortValue)(Value << ENCODER_ENCODER_B_START_BIT))
          & ((ENCODER_TPortValue)ENCODER_ENCODER_B_MASK)
        )
      );
      break;
    }
    case ENCODER_A: {                  /* bit field #1 */
      GPIO_PDD_SetPortDataOutput(ENCODER_MODULE_BASE_ADDRESS,
        (
          GPIO_PDD_GetPortDataOutput(ENCODER_MODULE_BASE_ADDRESS)
          & ((ENCODER_TPortValue)(~((ENCODER_TPortValue)ENCODER_ENCODER_A_MASK)))
        )
        | (
          ((ENCODER_TPortValue)(Value << ENCODER_ENCODER_A_START_BIT))
          & ((ENCODER_TPortValue)ENCODER_ENCODER_A_MASK)
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
**     Method      :  ENCODER_GetFieldValue (component GPIO_LDD)
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
ENCODER_TFieldValue ENCODER_GetFieldValue(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case ENCODER_B: {                  /* bit field #0 */
      return
        (ENCODER_TFieldValue)(
          (
            GPIO_PDD_GetPortDataInput(ENCODER_MODULE_BASE_ADDRESS)
            & (ENCODER_TPortValue)ENCODER_ENCODER_B_MASK
          )
          >> ENCODER_ENCODER_B_START_BIT
        );
    }
    case ENCODER_A: {                  /* bit field #1 */
      return
        (ENCODER_TFieldValue)(
          (
            GPIO_PDD_GetPortDataInput(ENCODER_MODULE_BASE_ADDRESS)
            & (ENCODER_TPortValue)ENCODER_ENCODER_A_MASK
          )
          >> ENCODER_ENCODER_A_START_BIT
        );
    }
    default:
      break;                           /* Invalid BitField is not treated, result is undefined */
  } /* switch (Field) */
  return (ENCODER_TFieldValue)0U;
}

/*
** ===================================================================
**     Method      :  ENCODER_ClearFieldBits (component GPIO_LDD)
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
void ENCODER_ClearFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, ENCODER_TFieldValue Mask)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case ENCODER_B: {                  /* bit field #0 */
      GPIO_PDD_ClearPortDataOutputMask(ENCODER_MODULE_BASE_ADDRESS,
        ((ENCODER_TPortValue)ENCODER_ENCODER_B_MASK)
        & ((ENCODER_TPortValue)(Mask << ENCODER_ENCODER_B_START_BIT))
      );
      break;
    }
    case ENCODER_A: {                  /* bit field #1 */
      GPIO_PDD_ClearPortDataOutputMask(ENCODER_MODULE_BASE_ADDRESS,
        ((ENCODER_TPortValue)ENCODER_ENCODER_A_MASK)
        & ((ENCODER_TPortValue)(Mask << ENCODER_ENCODER_A_START_BIT))
      );
      break;
    }
    default:
      break;                           /* Invalid Field is not treated, result is undefined */
  } /* switch (Field) */
}

/*
** ===================================================================
**     Method      :  ENCODER_SetFieldBits (component GPIO_LDD)
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
void ENCODER_SetFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, ENCODER_TFieldValue Mask)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case ENCODER_B: {                  /* bit field #0 */
      GPIO_PDD_SetPortDataOutputMask(ENCODER_MODULE_BASE_ADDRESS,
        ((ENCODER_TPortValue)ENCODER_ENCODER_B_MASK)
        & ((ENCODER_TPortValue)(Mask << ENCODER_ENCODER_B_START_BIT))
      );
      break;
    }
    case ENCODER_A: {                  /* bit field #1 */
      GPIO_PDD_SetPortDataOutputMask(ENCODER_MODULE_BASE_ADDRESS,
        ((ENCODER_TPortValue)ENCODER_ENCODER_A_MASK)
        & ((ENCODER_TPortValue)(Mask << ENCODER_ENCODER_A_START_BIT))
      );
      break;
    }
    default:
      break;                           /* Invalid Field is not treated, result is undefined */
  } /* switch (Field) */
}

/*
** ===================================================================
**     Method      :  ENCODER_ToggleFieldBits (component GPIO_LDD)
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
void ENCODER_ToggleFieldBits(LDD_TDeviceData *DeviceDataPtr, LDD_GPIO_TBitField Field, ENCODER_TFieldValue Mask)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  switch (Field) {                     /* no break */
    case ENCODER_B: {                  /* bit field #0 */
      GPIO_PDD_TogglePortDataOutputMask(ENCODER_MODULE_BASE_ADDRESS,
        ((ENCODER_TPortValue)ENCODER_ENCODER_B_MASK)
        & ((ENCODER_TPortValue)(Mask << ENCODER_ENCODER_B_START_BIT))
      );
      break;
    }
    case ENCODER_A: {                  /* bit field #1 */
      GPIO_PDD_TogglePortDataOutputMask(ENCODER_MODULE_BASE_ADDRESS,
        ((ENCODER_TPortValue)ENCODER_ENCODER_A_MASK)
        & ((ENCODER_TPortValue)(Mask << ENCODER_ENCODER_A_START_BIT))
      );
      break;
    }
    default:
      break;                           /* Invalid Field is not treated, result is undefined */
  } /* switch (Field) */
}

/*
** ===================================================================
**     Method      :  ENCODER_Interrupt (component GPIO_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ENCODER_Interrupt(void)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  ENCODER_TDeviceDataPtr DeviceDataPrv = INT_PORTC__DEFAULT_RTOS_ISRPARAM;
  ENCODER_TPortValue State;

  State = (ENCODER_TPortValue)(PORT_PDD_GetInterruptFlags(ENCODER_PORTCONTROL_BASE_ADDRESS)
          & ((ENCODER_TPortValue)ENCODER_ALLOCATED_PINS_MASK)); /* Retrieve flags */
  DeviceDataPrv->EventFlags |= State;
  if (State) {
    PORT_PDD_ClearInterruptFlags(ENCODER_PORTCONTROL_BASE_ADDRESS, State); /* Clears flags */
    ENCODER_OnPortEvent(DeviceDataPrv->UserData); /* Call OnPortEvent event */
  }
}

/* END ENCODER. */

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
