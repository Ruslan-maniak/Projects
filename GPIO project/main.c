
#include "GPIO\GPIO.h"

//==============================================================================
//                          Глобальные переменные
//==============================================================================

    // внешне определенные переменные
    extern sGpio        gpioKey1, 
                        gpioLed1;
    
//==============================================================================
//              Переключение состояния светодиода
//------------------------------------------------------------------------------
//  gpioLed    - пин управления светодиодом
//==============================================================================    
    
void LedToggle (void* gpioLed)
{   
    GPIOToggle((sGpio*)gpioLed);
}

//==============================================================================
//                         Основная программа
//==============================================================================

int main(void)
{   
    // инициализация пинов
    GPIOInit(&gpioKey1);
    GPIOInit(&gpioLed1);
   
    // конфигурация внешнего прерывания
    GPIOExtiConfig(2, LedToggle, (void*)&gpioLed1, &gpioKey1);
    
    // включение внешнего прерывания
    GPIOExtiEnable (eGpioTriger_FALL, &gpioKey1);

    while(1) 
    {
      
    }
}
