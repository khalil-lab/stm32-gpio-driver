

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

#include <stdint.h>





#define GPIOA ((gpio_port_reg_t *)0x40020000)
#define GPIOB ((gpio_port_reg_t *)0x40020400)
#define GPIOC ((gpio_port_reg_t *)0x40020800)
#define GPIOD ((gpio_port_reg_t *)0x40020C00)
#define GPIOE ((gpio_port_reg_t *)0x40021000)
#define GPIOF ((gpio_port_reg_t *)0x40021400)
#define GPIOG ((gpio_port_reg_t *)0x40021800)
#define GPIOH ((gpio_port_reg_t *)0x40021C00)

#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830UL)



typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} gpio_port_reg_t;




#endif
