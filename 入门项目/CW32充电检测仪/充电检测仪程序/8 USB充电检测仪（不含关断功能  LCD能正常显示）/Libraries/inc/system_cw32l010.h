/**
  ******************************************************************************
  * @file    system_cw32l010.h
  * @author  WHXY Application Team
  * @brief
  ******************************************************************************
  */

#ifndef __SYSTEM_CW32l010_H
#define __SYSTEM_CW32l010_H

#define SYSCTRL_HSI_TRIMCODEADDR                       (0x001007C0U)   //
#define SYSCTRL_LSI_TRIMCODEADDR                       (0x001007C2U)     //

#ifdef __cplusplus
extern "C" {
#endif
/** @addtogroup Includes
  * @{
  */

#include "cw32l010.h"
#include "base_types.h"
/**
  * @}
  */

/** @addtogroup Exported_Variables
  * @{
  */
extern uint32_t SystemCoreClock;          // System Clock Frequency (Core Clock)

/**
  * @}
  */

/** @addtogroup Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup Exported_Macros
  * @{
  */
#define HWWD_DISABLE        (1)
/**
 ******************************************************************************
 ** \brief Clock Setup macro definition
 **
 ** - 0: CLOCK_SETTING_NONE  - User provides own clock setting in application
 ** - 1: CLOCK_SETTING_CMSIS -
 ******************************************************************************/
#define CLOCK_SETTING_NONE  0u
#define CLOCK_SETTING_CMSIS 1u
/**
  * @}
  */

/** @addtogroup Exported_Functions
  * @{
  */

extern void SystemInit (void);            // Initialize the system
extern void SystemCoreClockUpdate (void); // Update SystemCoreClock variable
extern void FirmwareDelay(uint32_t DlyCnt);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_CW32l010_H__ */







