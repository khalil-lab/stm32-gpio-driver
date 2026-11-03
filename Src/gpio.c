#include gpio.h
#include stdio.h


static gpio_port_reg_t *GPIO_GetPort(gpio_port_t port)
{
    switch (port) {
        case GPIO_PORT_A: return GPIOA;
        case GPIO_PORT_B: return GPIOB;
        case GPIO_PORT_C: return GPIOC;
        case GPIO_PORT_D: return GPIOD;
        case GPIO_PORT_E: return GPIOE;
        case GPIO_PORT_F: return GPIOF;
        case GPIO_PORT_G: return GPIOG;
        case GPIO_PORT_H: return GPIOH;
        default: return NULL;
    }
}



int GPIO_Configure(gpio_port_t GPIO,uint8_t pin,gpio_mode_t mode)

{	gpio_port_reg_t *GPIOx = GPIO_GetPort(GPIO);
	enable_RCCAHB1(GPIO) ;
	GPIOx->MODER &=~(3<<(2U*pin)); /*reset the the mode of the selected bits in the  register mode */
	GPIOx->MODER |=(mode<<(2u*pin)); /*set the specifed bits to the selected mode */
	return 0 ;

}

int enable_RCCAHB1(gpio_port_t GPIOx)
{
	RCC_AHB1ENR |=(1U<<(uint32_t)GPIOx);
	return 0 ;
}
