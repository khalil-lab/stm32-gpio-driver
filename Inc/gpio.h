#ifndef
#define

#include <stdio.h>





#define GPIOA ((gpio_port_reg_t *)0x40020000UL)
#define GPIOB ((gpio_port_reg_t *)0x40020400UL)
#define GPIOC ((gpio_port_reg_t *)0x40020800UL)
#define GPIOD ((gpio_port_reg_t *)0x40020C00UL)
#define GPIOE ((gpio_port_reg_t *)0x40020C00)
#define GPIOF ((gpio_port_reg_t *)0x40021400)
#define GPIOG ((gpio_port_reg_t *)0x40021800)
#define GPIOH ((gpio_port_re_t *)0x40021800)

#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830UL)


#define MAX_GPIO_PINS 20

typedef enum {
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_G,
    GPIO_PORT_H
} gpio_port_t;



typedef enum
{
    GPIO_MODE_INPUT  = 0U,
    GPIO_MODE_OUTPUT = 1U,
    GPIO_MODE_AF     = 2U,
    GPIO_MODE_ANALOG = 3U
} gpio_mode_t;


struct {
	volatile uint32_t MODER
	volatile uint32_t OTYPER
	volatile uint32_t PUPDR
	volatile uint32_t OSPEEDER
	volatile uint32_t IDR
	volatile uint32_t ODR
	volatile uint32_t BSRR
	volatile uint32_t LCKR
	volatile uint32_t AFR[2]

} gpio_port_reg_t;


typedef struct {
	gpio_port_reg_t *port;
    uint8_t pin;
    gpio_mode_t mode;
} PIN_Config_t;

static GPIO_Config_t gpio_registry[MAX_GPIO_PINS];


int GPIO_Configure(gpio_port_t port, uint8_t pin, gpio_mode_t mode);

int GPIO_Configure(gpio_port_reg_t *GPIOx,
                    uint8_t pin,
                    gpio_mode_t mode);

int read_pin(gpio_port_t gpio , uint8_t pin);

int write_to_pin()





#endif


