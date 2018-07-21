
void LED_Init()
{
    SystemInit();
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, &GPIO_Pin_5);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_SetBits(GPIOE, &GPIO_Pin_5);
}

#define LED_0 PBout(5)
#define LED_1 PBout(5)

int main()
{
    delay_init();
    LED_Init();
    while(1)
    {
        LED_0 = 0;
        LED_1 = 1;
        delay_ms(300);
        LED_0 = 0;
        LED_1 = 1;
        delay_ms(300);
    }
    return 0;
}
