#include "../../CMSIS/Devices/stm32f4xx.h"    // CMSIS 系统头文件
#include "../../CMSIS/Devices/stm32f429xx.h"  // 针对 STM32F429 设备的头文件

// RCC 寄存器与 GPIO 时钟使能
#define RCC_GPIO_EN                 (*(volatile uint32_t*)(0x40023800UL + 0x30UL))  // RCC AHB1 外设时钟使能寄存器
#define RCC_GPIOB_EN                0x02UL    // GPIOB 时钟使能位
#define RCC_GPIOA_EN                0x01UL    // GPIOA 时钟使能位

// GPIOB 寄存器定义
#define GPIOB_MODER                 (*(volatile uint32_t*)(0x40020400UL + 0x00UL))  // GPIOB 模式寄存器
#define GPIOB_OTYPER                (*(volatile uint32_t*)(0x40020400UL + 0x04UL))  // GPIOB 输出类型寄存器
#define GPIOB_OSPEEDR               (*(volatile uint32_t*)(0x40020400UL + 0x08UL))  // GPIOB 输出速度寄存器
#define GPIOB_PUPDR                 (*(volatile uint32_t*)(0x40020400UL + 0x0CUL))  // GPIOB 上下拉寄存器
#define GPIOB_BSRR                  (*(volatile uint32_t*)(0x40020400UL + 0x18UL))  // GPIOB 位设置/复位寄存器

// GPIOA 寄存器定义
#define GPIOA_IDR                   (*(volatile uint32_t*)(0x40020000UL + 0x10UL))  // GPIOA 输入数据寄存器

// GPIOB 配置常量
#define GPIOB_MODE_PIN0_OUT         0x00000001UL  // GPIOB 引脚 0 输出模式
#define GPIOB_MODE_PIN7_OUT         0x00400000UL  // GPIOB 引脚 7 输出模式
#define GPIOB_MODE_PIN14_OUT        0x40000000UL  // GPIOB 引脚 14 输出模式

#define GPIOB_OTYPE_PIN0_PP         0x00000000UL  // GPIOB 引脚 0 推挽输出
#define GPIOB_OTYPE_PIN7_PP         0x00000000UL  // GPIOB 引脚 7 推挽输出
#define GPIOB_OTYPE_PIN14_PP        0x00000000UL  // GPIOB 引脚 14 推挽输出

#define GPIOB_OSPEED_PIN0_MID       0x00000040UL  // GPIOB 引脚 0 中速输出
#define GPIOB_OSPEED_PIN7_MID       0x00400000UL  // GPIOB 引脚 7 中速输出
#define GPIOB_OSPEED_PIN14_MID      0x40000000UL  // GPIOB 引脚 14 中速输出

#define GPIOB_PUPDR_PIN0_NOPUPD     0x00000000UL  // GPIOB 引脚 0 无上下拉电阻
#define GPIOB_PUPDR_PIN7_NOPUPD     0x00000000UL  // GPIOB 引脚 7 无上下拉电阻
#define GPIOB_PUPDR_PIN14_NOPUPD    0x00000000UL  // GPIOB 引脚 14 无上下拉电阻

#define GPIOB_BSRR_PIN0_SET         0x00000001UL  // GPIOB 引脚 0 设置（高电平）
#define GPIOB_BSRR_PIN0_RESET       0x00010000UL  // GPIOB 引脚 0 复位（低电平）
#define GPIOB_BSRR_PIN7_SET         0x00000080UL  // GPIOB 引脚 7 设置（高电平）
#define GPIOB_BSRR_PIN7_RESET       0x00800000UL  // GPIOB 引脚 7 复位（低电平）
#define GPIOB_BSRR_PIN14_SET        0x40000000UL  // GPIOB 引脚 14 设置（高电平）
#define GPIOB_BSRR_PIN14_RESET      0x40000000UL  // GPIOB 引脚 14 复位（低电平）

// 按钮引脚定义
#define BUTTON1_PIN 6  // PA6 (按钮1)
#define BUTTON2_PIN 7  // PA7 (按钮2)

// LED状态
#define LED1_PIN    0  // PB0 (绿色LED)
#define LED2_PIN    7  // PB7 (蓝色LED)
#define LED3_PIN    14 // PB14 (红色LED)

#define LED_STATE_1  0 // LED1点亮
#define LED_STATE_2  1 // LED2点亮
#define LED_STATE_3  2 // LED3点亮
#define LED_STATE_ALL 3 // 所有LED点亮
#define LED_STATE_NONE 4 // 所有LED熄灭

// 常见的操作宏
#define READ_BIT(REG, BIT)          (REG & BIT)  // 读取特定位
#define SET_BIT(REG, BIT)           (REG |= BIT) // 设置特定位
#define CLEAR_BIT(REG, BIT)         (REG &= ~BIT) // 清除特定位
void GPIO_Init(void);