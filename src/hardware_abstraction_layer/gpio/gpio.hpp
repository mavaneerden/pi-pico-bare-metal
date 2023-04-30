#pragma once

#include <stdint.h>

namespace gpio
{
    constexpr uint8_t NUMBER_OF_GPIO_PINS = 30u;

    struct gpio_interrupt_events_t
    {
        bool level_low;
        bool level_high;
        bool edge_low;
        bool edge_high;
    };

    /**
     *
     */
    class gpio_t
    {
    private:
        static uint8_t number_of_gpio_t_instances;
        const uint8_t m_pin_number;
        const uint32_t m_pin_mask;
    public:
        gpio_t(const uint8_t pin_number);

        void set_function(const uint32_t function);

        // TODO: for interrupts, use CPUID register to get current processor
        void enable_interrupt(const bool trigger_on_level_low, const bool trigger_on_level_high, const bool trigger_on_edge_low, const bool trigger_on_edge_high);
        void trigger_interrupt(const bool trigger_on_level_low, const bool trigger_on_level_high, const bool trigger_on_edge_low, const bool trigger_on_edge_high);
        void disable_interrupt();
        gpio_interrupt_events_t& get_interrupt_status() const;
        bool get_interrupt_signal_before_override() const;
        bool get_interrupt_signal_after_override() const;
        void force_interrupt_default();
        void force_interrupt_inverted();
        void force_interrupt_low();
        void force_interrupt_high();

        void enable_dormant_wake_interrupt(const bool trigger_on_level_low, const bool trigger_on_level_high, const bool trigger_on_edge_low, const bool trigger_on_edge_high);
        void trigger_dormant_wake_interrupt(const bool trigger_on_level_low, const bool trigger_on_level_high, const bool trigger_on_edge_low, const bool trigger_on_edge_high);
        void disable_dormant_wake_interrupt();
        gpio_interrupt_events_t& get_dormant_wake_interrupt_status() const;

        void set_output(const bool value);
        void toggle_output();
        bool get_output_signal_before_override() const;
        bool get_output_signal_after_override() const;
        void force_output_default();
        void force_output_inverted();
        void force_output_low();
        void force_output_high();

        bool get_input() const;
        bool get_input_signal_before_override() const;
        bool get_input_signal_after_override() const;
        void force_input_default();
        void force_input_inverted();
        void force_input_low();
        void force_input_high();

        void enable_output();
        void disable_output();
        bool get_output_enable_signal_before_override() const;
        bool get_output_enable_signal_after_override() const;
        void force_output_enable_default();
        void force_output_enable_inverted();
        void force_output_disabled();
        void force_output_enabled();
    };

    gpio_t& get_gpio(const uint8_t pin_number);
}
