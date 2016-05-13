//******************************************************************************
// Имя файла    :  'SysTick.c'
// заголовок    :  Постоянный глобальный таймер
// Автор        :  Маньянов Р.Р.
// Контакты     :  
// Дата         :  13.05.2014 
//******************************************************************************

#include "SysTick.h"

//==============================================================================
//                  Константы и макросы
//==============================================================================
    
    // приоритет прерывания глобального таймера (0..15) 
    #define SYSTICK_PRIORITY    0x01

//==============================================================================
//                      Глобальные переменные
//==============================================================================
    
    // Глобальный счётчик миллисекунд
    uint32_t globalTimer;

//==============================================================================
//                      Прототипы функций
//==============================================================================
    
    // Инициализация микросекундного счётчика
    void InitDWTCounter (void);

//==============================================================================
//                    Инициализация глобального таймера
//------------------------------------------------------------------------------
// frequence    - частота глобального таймера
// uSTimer      - управление микросекундным таймером (0 - выкл, 1 - вкл)                      
//==============================================================================

void SysTickInit(uint16_t frequence, uint8_t uSTimer)
{
    if(SysTick_Config(SystemCoreClock / frequence))    
        while (1);
    NVIC_SetPriority(SysTick_IRQn, 0x1);
    
    if(uSTimer)
    {
        InitDWTCounter();
    }    
}

//==============================================================================
//                  Деинициализация глобального таймера
//==============================================================================

void SysTickDeinit (void)
{
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE;
}

//==============================================================================
//                 Инициализация микросекундного счётчика
//==============================================================================

static void InitDWTCounter (void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT       = 0;
    DWT->CTRL        |= DWT_CTRL_CYCCNTENA_Msk;    
}

//==============================================================================
//                   Итерация отсчёта глобального таймера 
//==============================================================================

void SysTick_Handler(void) 
{     
    globalTimer++;
}   

//==============================================================================
//                    Пауза в отсчётах глобального таймера  
//------------------------------------------------------------------------------
// delay    - длительность паузы в отсчётах глобального таймера
//==============================================================================

void SysTickDelay (uint16_t delay)
{
    uint32_t timer = globalTimer;
    while(globalTimer - timer <= delay);
}

//==============================================================================
//                      Микросекундная пауза
//------------------------------------------------------------------------------
// delay    - время паузы (мкс)
//==============================================================================

void SysTickDelayuS (uint16_t delay)
{   
    DWT->CYCCNT = 0;
    uint32_t delayClockCount = (SystemCoreClock / 1000000) * delay; 
    while(DWT->CYCCNT < delayClockCount);
}