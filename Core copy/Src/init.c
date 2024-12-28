void GPIO_Init(void) {
    // 使能 GPIOA 和 GPIOB 时钟
    RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN);  // 使能 GPIOA 和 GPIOB 的时钟

    // 配置 PA6 和 PA7 为输入模式（按钮1 和 按钮2）
    GPIOA->MODER &= ~((3UL << (BUTTON1_PIN * 2)) | (3UL << (BUTTON2_PIN * 2))); // 清除 PA6 和 PA7 的模式位
    GPIOA->PUPDR |= ((1UL << (BUTTON1_PIN * 2)) | (1UL << (BUTTON2_PIN * 2))); // 设置 PA6 和 PA7 为上拉电阻

    // 配置 PB0 (LED1) 为输出模式
    GPIOB->MODER &= ~GPIO_MODER_MODE0;         // 清除 PB0 的模式位
    GPIOB->MODER |= GPIO_MODER_MODE0_0;        // 设置 PB0 为输出模式
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_0;        // 设置 PB0 为推挽输出
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED0;    // 设置 PB0 输出速度为中速
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR0;        // 设置 PB0 为无上下拉电阻

    // 配置 PB7 (LED2) 为输出模式
    GPIOB->MODER &= ~GPIO_MODER_MODE7;         // 清除 PB7 的模式位
    GPIOB->MODER |= GPIO_MODER_MODE7_0;        // 设置 PB7 为输出模式
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_7;        // 设置 PB7 为推挽输出
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED7;    // 设置 PB7 输出速度为中速
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR7;        // 设置 PB7 为无上下拉电阻

    // 配置 PB14 (LED3) 为输出模式
    GPIOB->MODER &= ~GPIO_MODER_MODE14;        // 清除 PB14 的模式位
    GPIOB->MODER |= GPIO_MODER_MODE14_0;       // 设置 PB14 为输出模式
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_14;       // 设置 PB14 为推挽输出
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED14;   // 设置 PB14 输出速度为中速
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR14;       // 设置 PB14 为无上下拉电阻
}
