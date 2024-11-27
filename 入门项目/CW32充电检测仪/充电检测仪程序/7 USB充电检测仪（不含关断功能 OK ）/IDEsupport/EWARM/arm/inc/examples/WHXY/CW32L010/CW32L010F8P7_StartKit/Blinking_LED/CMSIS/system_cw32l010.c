/******************************************************************************
* Include files                                                              *
******************************************************************************/
#include "system_cw32l010.h"

/* #define USER_VECT_TAB_ADDRESS */

#if defined(USER_VECT_TAB_ADDRESS)
/*!< Uncomment the following line if you need to relocate your vector Table
     in Sram else user remap will be done in Flash. */
/* #define VECT_TAB_SRAM */
#if defined(VECT_TAB_SRAM)
#define VECT_TAB_BASE_ADDRESS   0x20000000U       /*!< Vector Table base address field.
                                                     This value must be a multiple of 0x200. */
#define VECT_TAB_OFFSET         0x00000000U     /*!< Vector Table base offset field.
                                                     This value must be a multiple of 0x200. */
#else
#define VECT_TAB_BASE_ADDRESS   0x00000000U      /*!< Vector Table base address field.
                                                     This value must be a multiple of 0x200. */
#define VECT_TAB_OFFSET         0x00000000U     /*!< Vector Table base offset field.
                                                     This value must be a multiple of 0x200. */
#endif /* VECT_TAB_SRAM */
#endif /* USER_VECT_TAB_ADDRESS */
/******************************************************************************
 ** System Clock Frequency (Core Clock) Variable according CMSIS
 ******************************************************************************/

uint32_t SystemCoreClock = 4000000;

void SystemCoreClockUpdate(void) // Update SystemCoreClock variable
{
    SystemCoreClock = 4000000;
}

/**
 ******************************************************************************
 ** \brief  Setup the microcontroller system. Initialize the System and update
 ** the SystemCoreClock variable.
 **
 ** \param  none
 ** \return none
 ******************************************************************************/
void SystemInit(void)
{
/* Configure the Vector Table location add offset address ------------------*/
#if defined(USER_VECT_TAB_ADDRESS)
    SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#endif /* USER_VECT_TAB_ADDRESS */

    //Load TrimCode in this.
    CW_SYSCTRL->HSI_f.TRIM = *((volatile uint16_t *)SYSCTRL_HSI_TRIMCODEADDR);
    CW_SYSCTRL->LSI_f.TRIM = *((volatile uint16_t *)SYSCTRL_LSI_TRIMCODEADDR);
   
    SystemCoreClockUpdate();

    //Init Hide thing.
    //...
}

void FirmwareDelay(uint32_t DlyCnt)
{
    volatile uint32_t thisCnt = DlyCnt;
    while( thisCnt-- )
    {
        ;
    }
}
