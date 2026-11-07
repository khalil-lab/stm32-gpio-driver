#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>


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
} gpio_pupd_t ;

typedef enum {
	GPIO_PIN_RESET ,
	GPIO_PIN_SET
}pin_state_t ;


typedef enum {
	GPIO_OK,
	GPIO_ERROR_INVALID_PORT,
	GPIO_ERROR_INVALID_PIN,
	GPIO_ERROR_WRONG_MODE,
	GPIO_ERROR_INVALID_MODE,
	GPIO_ERROR_NULL_POINTER,
	GPIO_ERROR_INVALID_POINTER,
	GPIO_ERROR_INVALID_AF,
	GPIO_ERROR_INVALID_OUTPUT_TYPE,
	GPIO_ERROR_INVALID_SPEED,
	GPIO_ERROR_INVALID_PULL,
	GPIO_ERROR_INVALID_STATE
}gpio_status_t;

typedef enum {
	AF0,    //0000
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
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




typedef struct {
	gpio_port_t port;
	uint8_t pinNumber;
	gpio_mode_t mode;
	gpio_af_t	af;
	gpio_otype_t outpType;
	gpio_ospeed_t outpSpeed;
	gpio_pupd_t   pupd;
}pin_config_t;





gpio_status_t GPIO_Configure(
    gpio_port_t port,
    uint8_t pinNumber,
    gpio_mode_t mode,
    gpio_af_t af,
    gpio_otype_t outpType,
    gpio_ospeed_t outpSpeed,
    gpio_pupd_t pupd) ;



gpio_status_t read_pin(gpio_port_t gpio, uint8_t pin, uint32_t *value) ;


gpio_status_t GPIO_WritePin(gpio_port_t port,
                            uint8_t pin,
                            pin_state_t state);










#endif



