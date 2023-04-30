#include <stdint.h>
// #include <assert.h>

#include "gpio.hpp"
#include "registers.hpp"

using namespace gpio;

/* gpio_t instances are stored here. */
static gpio_t gpio_vector[NUMBER_OF_GPIO_PINS] = {
    gpio_t(0),  gpio_t(1),  gpio_t(2),  gpio_t(3),  gpio_t(4),
    gpio_t(5),  gpio_t(6),  gpio_t(7),  gpio_t(8),  gpio_t(9),
    gpio_t(10), gpio_t(11), gpio_t(12), gpio_t(13), gpio_t(14),
    gpio_t(15), gpio_t(16), gpio_t(17), gpio_t(18), gpio_t(19),
    gpio_t(20), gpio_t(21), gpio_t(22), gpio_t(23), gpio_t(24),
    gpio_t(25), gpio_t(26), gpio_t(27), gpio_t(28), gpio_t(29)
};

gpio_t& gpio::get_gpio(const uint8_t pin_number)
{
    // assert(pin_number < NUMBER_OF_GPIO_PINS);

    return gpio_vector[pin_number];
}

/* Initialize number of instances to 0. */
uint8_t gpio_t::number_of_gpio_t_instances = 0;

gpio_t::gpio_t(const uint8_t pin_number) :
    m_pin_number(pin_number),
    m_pin_mask(1 << pin_number)
{
    // assert(number_of_gpio_t_instances + 1 <= NUMBER_OF_GPIO_PINS);

    number_of_gpio_t_instances++;
}

void gpio_t::set_function(const uint32_t function)
{
    // TODO: use enum here?
    // assert(function <= 9u);

    IO_BANK0.GPIO[this->m_pin_number].CTRL.FUNCSEL = function;
}

void gpio_t::enable_interrupt(const bool trigger_on_level_low, const bool trigger_on_level_high, const bool trigger_on_edge_low, const bool trigger_on_edge_high)
{

}

void gpio_t::trigger_interrupt(const bool trigger_on_level_low, const bool trigger_on_level_high, const bool trigger_on_edge_low, const bool trigger_on_edge_high)
{

}

void gpio_t::disable_interrupt()
{

}

gpio_interrupt_events_t& gpio_t::get_interrupt_status() const
{

}

bool gpio_t::get_interrupt_signal_before_override() const
{
    return IO_BANK0.GPIO[this->m_pin_number].STATUS.IRQFROMPAD;
}

bool gpio_t::get_interrupt_signal_after_override() const
{
    return IO_BANK0.GPIO[this->m_pin_number].STATUS.IRQTOPROC;
}

void gpio_t::force_interrupt_default()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.IRQOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_USE_DEFAULT;
}

void gpio_t::force_interrupt_inverted()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.IRQOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_INVERT;
}

void gpio_t::force_interrupt_low()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.IRQOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_DRIVE_LOW_OR_DISABLE;
}

void gpio_t::force_interrupt_high()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.IRQOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_DRIVE_HIGH_OR_ENABLE;
}


void gpio_t::enable_dormant_wake_interrupt(const bool trigger_on_level_low, const bool trigger_on_level_high, const bool trigger_on_edge_low, const bool trigger_on_edge_high)
{

}

void gpio_t::trigger_dormant_wake_interrupt(const bool trigger_on_level_low, const bool trigger_on_level_high, const bool trigger_on_edge_low, const bool trigger_on_edge_high)
{

}

void gpio_t::disable_dormant_wake_interrupt()
{

}

gpio_interrupt_events_t& gpio_t::get_dormant_wake_interrupt_status() const
{

}


void gpio_t::set_output(const bool value)
{
    value ? (SIO.GPIO_OUT_SET = this->m_pin_mask) : (SIO.GPIO_OUT_CLR = this->m_pin_mask);
}

void gpio_t::toggle_output()
{
    // SIO.GPIO_OUT_XOR = this->m_pin_mask;
    SIO.GPIO_OUT_XOR = 1 << this->m_pin_number;
    // SIO.GPIO_OUT_XOR = 1 << 25u;
}

bool gpio_t::get_output_signal_before_override() const
{
    return IO_BANK0.GPIO[this->m_pin_number].STATUS.OUTFROMPERI;
}

bool gpio_t::get_output_signal_after_override() const
{
    return IO_BANK0.GPIO[this->m_pin_number].STATUS.OUTTOPAD;
}

void gpio_t::force_output_default()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.OUTOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_USE_DEFAULT;
}

void gpio_t::force_output_inverted()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.OUTOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_INVERT;
}

void gpio_t::force_output_low()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.OUTOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_DRIVE_LOW_OR_DISABLE;
}

void gpio_t::force_output_high()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.OUTOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_DRIVE_HIGH_OR_ENABLE;
}


bool gpio_t::get_input() const
{
    return (SIO.GPIO_IN & m_pin_mask) != 0;
}

bool gpio_t::get_input_signal_before_override() const
{
    return IO_BANK0.GPIO[this->m_pin_number].STATUS.INFROMPAD;
}

bool gpio_t::get_input_signal_after_override() const
{
    return IO_BANK0.GPIO[this->m_pin_number].STATUS.INTOPERI;
}

void gpio_t::force_input_default()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.INOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_USE_DEFAULT;
}

void gpio_t::force_input_inverted()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.INOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_INVERT;
}

void gpio_t::force_input_low()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.INOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_DRIVE_LOW_OR_DISABLE;
}

void gpio_t::force_input_high()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.INOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_DRIVE_HIGH_OR_ENABLE;
}


void gpio_t::enable_output()
{
    SIO.GPIO_OE_SET = m_pin_mask;
}

void gpio_t::disable_output()
{
    SIO.GPIO_OE_CLR = m_pin_mask;
}

bool gpio_t::get_output_enable_signal_before_override() const
{
    return IO_BANK0.GPIO[this->m_pin_number].STATUS.OEFROMPERI;
}

bool gpio_t::get_output_enable_signal_after_override() const
{
    return IO_BANK0.GPIO[this->m_pin_number].STATUS.OETOPAD;
}

void gpio_t::force_output_enable_default()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.OEOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_USE_DEFAULT;
}

void gpio_t::force_output_enable_inverted()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.OEOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_INVERT;
}

void gpio_t::force_output_disabled()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.OEOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_DRIVE_LOW_OR_DISABLE;
}

void gpio_t::force_output_enabled()
{
    IO_BANK0.GPIO[this->m_pin_number].CTRL.OEOVER = IOBANK0_GPIOx_CTRL_OVERRIDE_DRIVE_HIGH_OR_ENABLE;
}


// TODO: define IRQ handler
