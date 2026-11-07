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



gpio_status_t GPIO_Configure(
    gpio_port_t port,
    uint8_t pinNumber,
    gpio_mode_t mode,
    gpio_af_t af,
    gpio_otype_t outpType,
    gpio_ospeed_t outpSpeed,
    gpio_pupd_t pupd)
{
    /* Validate port */
    if (GPIO_GetPort(port) == NULL)
        return GPIO_ERROR_INVALID_PORT;

    /* Validate pin number */
    if (pinNumber > 15U)
        return GPIO_ERROR_INVALID_PIN;

    /* Validate mode */
    if (mode > GPIO_MODE_ANALOG)
        return GPIO_ERROR_INVALID_MODE;

    /* Validate alternate function when applicable */
    if ((mode == GPIO_MODE_AF) && (af > GPIO_AF15))
        return GPIO_ERROR_INVALID_AF;

    /* Validate output type */
    if (outpType > OPEN_DRAIN)
        return GPIO_ERROR_INVALID_OUTPUT_TYPE;

    /* Validate output speed */
    if (outpSpeed > HIGH_SPEED)
        return GPIO_ERROR_INVALID_SPEED;

    /* Validate pull configuration */
    if (pupd > PULL_DOWN)
        return GPIO_ERROR_INVALID_PULL;

    /* Prepare internal configuration */
    pin_config_t pin_config =
    {
        .port = port,
        .pinNumber = pinNumber,
        .mode = mode,
        .af = af,
        .outpType = outpType,
        .outpSpeed = outpSpeed,
        .pupd = pupd
    };

    return gpio_reg_configure(&pin_config);
}

static void enable_RCCAHB1(gpio_port_t GPIOx)
{
	RCC_AHB1ENR |=(1U<<(uint32_t)GPIOx);

}

static gpio_status_t gpio_reg_configure(const pin_config_t *config)
{
    gpio_port_reg_t *GPIOx = GPIO_GetPort(config->port);

    if (GPIOx == NULL)
        return GPIO_ERROR_INVALID_PORT;

    enable_RCCAHB1(config->port);

    uint32_t pin = config->pinNumber;
    uint32_t shift_2 = pin * 2U;
    uint32_t mask_2 = 3U << shift_2;

    /* Configure output type */
    GPIOx->OTYPER &= ~(1U << pin);
    GPIOx->OTYPER |= ((uint32_t)config->outpType << pin);

    /* Configure output speed */
    GPIOx->OSPEEDR &= ~mask_2;
    GPIOx->OSPEEDR |= ((uint32_t)config->outpSpeed << shift_2);

    /* Configure pull-up / pull-down */
    GPIOx->PUPDR &= ~mask_2;
    GPIOx->PUPDR |= ((uint32_t)config->pupd << shift_2);

    /* Configure alternate function */
    if (config->mode == GPIO_MODE_AF)
    {
        if (pin < 8U)
        {
            GPIOx->AFR[0] &= ~(15U << (pin * 4U));
            GPIOx->AFR[0] |= ((uint32_t)config->af << (pin * 4U));
        }
        else
        {
            GPIOx->AFR[1] &= ~(15U << ((pin - 8U) * 4U));
            GPIOx->AFR[1] |= ((uint32_t)config->af << ((pin - 8U) * 4U));
        }
    }

    /* Configure mode LAST */
    GPIOx->MODER &= ~mask_2;
    GPIOx->MODER |= ((uint32_t)config->mode << shift_2);

    return GPIO_OK;
}




gpio_status_t read_pin(gpio_port_t gpio, uint8_t pin, uint32_t *value)
{
    if (verify_gpio_pointer(gpio) != GPIO_OK)
        return GPIO_ERROR_INVALID_PORT;

    if (pin > 15U)
        return GPIO_ERROR_INVALID_PIN;

    if (value == NULL)
        return GPIO_ERROR_INVALID_POINTER;

    if (checkPinMode(gpio, pin) != GPIO_MODE_INPUT)
        return GPIO_ERROR_WRONG_MODE;

    *value = gpio_reg_read_pin(gpio, pin);

    return GPIO_OK;
}

static gpio_status_t verify_gpio_pointer (gpio_port_t gpio)
{
	if (GPIO_GetPort(gpio) != NULL)
		{
				return GPIO_OK ;


			}

			return GPIO_ERROR_INVALID_PORT ;


}
static uint32_t gpio_reg_read_pin (gpio_port_t gpio , uint8_t pin)
		{

			return (uint32_t)((GPIOx->IDR)>>pin)&1u ;
		}



gpio_status_t GPIO_WritePin(gpio_port_t port,
                            uint8_t pin,
                            pin_state_t state)
{
    if (GPIO_GetPort(port) == NULL)
        return GPIO_ERROR_INVALID_PORT;

    if (pin > 15U)
        return GPIO_ERROR_INVALID_PIN;

    if ((state != GPIO_PIN_SET) && (state != GPIO_PIN_RESET))
        return GPIO_ERROR_INVALID_STATE;

    gpio_reg_write_pin(port, pin, state);

    return GPIO_OK;
}



static void gpio_reg_write_pin(gpio_port_t port,
                               uint8_t pin,
                               pin_state_t state)
{

	gpio_port_reg_t *GPIOx = GPIO_GetPort(port);
    if (state == GPIO_PIN_SET)
        GPIOx->BSRR = (1U << pin);
    else
        GPIOx->BSRR = (1U << (pin + 16U));
}



static gpio_mode_t checkPinMode(gpio_port__t gpio , uint8_t pin )
{
			gpio_port_reg_t *GPIOx = GPIO_GetPort(gpio);
			uint32_t mode=(GPIOx->MODER>>(2u*pin)) & 3u ;
			return (gpio_mode_t)mode ;

}
