#ifndef GPIO_H
#define GPIO_H

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






struct {
	gpio_port_t port;
	uint8_t pinNumber;
	gpio_mode_t mode;
	gpio_af_t	af;
	gpio_otype_t outpType;
	gpio_ospeed_t outpSpeed;
	gpio_pupd_t   pupd;
} 	pin_config_t ;

typedef enum {    //Bits 31:16 Reserved
	PUSH_PULL ,   //0 reset state
	OPEN_DRAIN
} gpio_otype_t ;

typedef enum {    //Bits 2y:2y+1
	LOW_SPEED ,    //00
	MEDIUM_SPEED ,
	FAST_SPEED ,
	HIGH_SPEED
}gpio_ospeed_t;

typedef enum {

	NO_PULL_UP_PULL_DOWN ,
	PULL_UP ,
	PULL_DOWN

};

typedef enum {
	GPIO_PIN_RESET ,
	GPIO_PIN_SET
}pin_state_t ;


typedef enum {
	GPIO_OK,
	GPIO_ERROR_INVALID_PORT,
	GPIO_ERROR_INVALID_PIN,
	GPIO_ERROR_WRONG_MODE,
	GPIO_ERROR_NULL_POINTER,
	GPIO_ERROR_INVALID_AF,
	GPIO_ERROR_INVALID_OUTPUT_TYPE,
	GPIO_ERROR_INVALID_SPEED,
	GPIO_ERROR_INVALID_PULL,
	GPIO_ERROR_INVALID_STATE
}gpio_statut_t;

typedef enum {
	AF0,    //0000
	AF1,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF8,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}gpio_af_t;

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
    GPIO_MODE_OUTPUT ,
    GPIO_MODE_AF     ,
    GPIO_MODE_ANALOG

} gpio_mode_t;


struct {
	volatile uint32_t MODER ;
	volatile uint32_t OTYPER;
	volatile uint32_t PUPDR;
	volatile uint32_t OSPEEDER;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];

} gpio_port_reg_t;






static gpio_port_reg_t *GPIO_GetPort(gpio_port_t port);

gpio_status_t GPIO_Configure(
    gpio_port_t port,
    uint8_t pinNumber,
    gpio_mode_t mode,
    gpio_af_t af,
    gpio_otype_t outpType,
    gpio_ospeed_t outpSpeed,
    gpio_pupd_t pupd) ;

static void enable_RCCAHB1(gpio_port_t GPIOx);

static void gpio_reg_write_pin(gpio_port_t port,
                               uint8_t pin,
                               pin_state_t state) ;


static gpio_mode_t checkPinMode(gpio_port__t gpio , uint8_t pin );


static gpio_status_t gpio_reg_configure(const pin_config_t *config);

gpio_status_t read_pin(gpio_port_t gpio, uint8_t pin, uint32_t *value) ;

static gpio_status_t verify_gpio_pointer (gpio_port_t gpio) ;

static uint32_t gpio_reg_read_pin (gpio_port_t gpio , uint8_t pin) ;

gpio_status_t GPIO_WritePin(gpio_port_t port,
                            uint8_t pin,
                            pin_state_t state);

static void gpio_reg_write_pin(gpio_port_t port,
                               uint8_t pin,
                               pin_state_t state) ;








#endif



