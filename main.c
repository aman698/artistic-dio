#include "stm8s.h"
#include "dio.h"

void main(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

    DIO_Init();

    while(1)
    {
        /* Mirror Inputs to Relays */

        Relay1_Set(Input1_Read());
        Relay2_Set(Input2_Read());
        Relay3_Set(Input3_Read());
        Relay4_Set(Input4_Read());

        Relay5_Set(1);
        Relay6_Set(0);
    }
}