int main(void) {
    uint8_t led_state = LED_STATE_1;  // 初始点亮 LED1
    uint8_t button2_state = 0;        // 按钮2的状态（用于跟踪开关）

    // 初始化 GPIO
    GPIO_Init();

    while (1) {
        // 检测按钮1（PA6）的状态，用于切换 LED
        if (READ_BIT(GPIOA->IDR, (1 << BUTTON1_PIN))) {
            // 按钮按下时切换 LED
            led_state++;
            if (led_state > LED_STATE_3) {
                led_state = LED_STATE_1;  // 循环切换 LED
            }

            // 控制 LED 点亮
            // 熄灭所有LED
            CLEAR_BIT(GPIOB_BSRR, GPIOB_BSRR_PIN0_RESET);
            CLEAR_BIT(GPIOB_BSRR, GPIOB_BSRR_PIN7_RESET);
            CLEAR_BIT(GPIOB_BSRR, GPIOB_BSRR_PIN14_RESET);
            
            // 控制对应的 LED 点亮
            switch(led_state) {
                case LED_STATE_1:
                    SET_BIT(GPIOB_BSRR, GPIOB_BSRR_PIN0_SET);   // 点亮 LED1 (高电平)
                    break;
                case LED_STATE_2:
                    SET_BIT(GPIOB_BSRR, GPIOB_BSRR_PIN7_SET);    // 点亮 LED2 (高电平)
                    break;
                case LED_STATE_3:
                    SET_BIT(GPIOB_BSRR, GPIOB_BSRR_PIN14_SET);    // 点亮 LED3 (高电平)
                    break;
                default:
                    break;
            }

            while (READ_BIT(GPIOA->IDR, (1 << BUTTON1_PIN))); // 等待按钮释放
        }

        // 检测按钮2（PA7）的状态，用于打开或关闭未点亮的 LED
        if (READ_BIT(GPIOA->IDR, (1 << BUTTON2_PIN))) {
            // 第二个按钮的状态切换（控制打开关闭LED）
            if (button2_state == 0) {
                // 打开所有 LED
                SET_BIT(GPIOB_BSRR, GPIOB_BSRR_PIN0_SET);
                SET_BIT(GPIOB_BSRR, GPIOB_BSRR_PIN7_SET);
                SET_BIT(GPIOB_BSRR, GPIOB_BSRR_PIN14_SET);
                button2_state = 1;
            } else {
                // 关闭所有 LED
                CLEAR_BIT(GPIOB_BSRR, GPIOB_BSRR_PIN0_RESET);
                CLEAR_BIT(GPIOB_BSRR, GPIOB_BSRR_PIN7_RESET);
                CLEAR_BIT(GPIOB_BSRR, GPIOB_BSRR_PIN14_RESET);
                button2_state = 0;
            }
            while (READ_BIT(GPIOA->IDR, (1 << BUTTON2_PIN))); // 等待按钮释放
        }
    }
}
