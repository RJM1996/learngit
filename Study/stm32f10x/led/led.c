
void GPIO_Configuration()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |
                                  GPIO_Pin_1 |
                                  GPIO_Pin_2 |
                                  GPIO_Pin_3 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void LED_Init()
{
    SystemInit();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_Configuration();
}

#define LED_0 (*((u32*)0x42210180))
#define LED_1 (*((u32*)0x42210184))
#define LED_2 (*((u32*)0x42210188))
#define LED_3 (*((u32*)0x4221018c))

int main()
{
    LED_Init();
    delay_init();
    while(1)
    {
        LED_0 = 0;
        delay_ms(300);
        LED_0 = 1;
        delay_ms(300);
        LED_1 = 0;
        delay_ms(300);
        LED_1 = 1;
        delay_ms(300);
        LED_2 = 0;
        delay_ms(300);
        LED_2 = 1;
        delay_ms(300);
        LED_3 = 0;
        delay_ms(300);
        LED_3 = 1;
        delay_ms(300);
    }
    return 0;
}
