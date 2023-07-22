#include "rp2040_registers.hpp"

namespace rp2040::registers
{

extern "C" {
volatile XIP_CTRL_Type* XIP = reinterpret_cast<XIP_CTRL_Type*>(XIP_CTRL_BASE);
volatile XIP_CTRL_Type* XIP_XOR =  reinterpret_cast<XIP_CTRL_Type*>(XIP_CTRL_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile XIP_CTRL_Type* XIP_SET =  reinterpret_cast<XIP_CTRL_Type*>(XIP_CTRL_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile XIP_CTRL_Type* XIP_CLEAR =  reinterpret_cast<XIP_CTRL_Type*>(XIP_CTRL_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile XIP_SSI_Type* XIP_SSI = reinterpret_cast<XIP_SSI_Type*>(XIP_SSI_BASE );
volatile XIP_SSI_Type* XIP_SSI_XOR =  reinterpret_cast<XIP_SSI_Type*>(XIP_SSI_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile XIP_SSI_Type* XIP_SSI_SET =  reinterpret_cast<XIP_SSI_Type*>(XIP_SSI_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile XIP_SSI_Type* XIP_SSI_CLEAR =  reinterpret_cast<XIP_SSI_Type*>(XIP_SSI_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile SYSINFO_Type* SYSINFO = reinterpret_cast<SYSINFO_Type*>(SYSINFO_BASE );
volatile SYSINFO_Type* SYSINFO_XOR =  reinterpret_cast<SYSINFO_Type*>(SYSINFO_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile SYSINFO_Type* SYSINFO_SET =  reinterpret_cast<SYSINFO_Type*>(SYSINFO_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile SYSINFO_Type* SYSINFO_CLEAR =  reinterpret_cast<SYSINFO_Type*>(SYSINFO_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile SYSCFG_Type* SYSCFG = reinterpret_cast<SYSCFG_Type*>(SYSCFG_BASE );
volatile SYSCFG_Type* SYSCFG_XOR =  reinterpret_cast<SYSCFG_Type*>(SYSCFG_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile SYSCFG_Type* SYSCFG_SET =  reinterpret_cast<SYSCFG_Type*>(SYSCFG_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile SYSCFG_Type* SYSCFG_CLEAR =  reinterpret_cast<SYSCFG_Type*>(SYSCFG_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile CLOCKS_Type* CLOCKS = reinterpret_cast<CLOCKS_Type*>(CLOCKS_BASE );
volatile CLOCKS_Type* CLOCKS_XOR =  reinterpret_cast<CLOCKS_Type*>(CLOCKS_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile CLOCKS_Type* CLOCKS_SET =  reinterpret_cast<CLOCKS_Type*>(CLOCKS_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile CLOCKS_Type* CLOCKS_CLEAR =  reinterpret_cast<CLOCKS_Type*>(CLOCKS_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile RESETS_Type* RESETS = reinterpret_cast<RESETS_Type*>(RESETS_BASE );
volatile RESETS_Type* RESETS_XOR =  reinterpret_cast<RESETS_Type*>(RESETS_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile RESETS_Type* RESETS_SET =  reinterpret_cast<RESETS_Type*>(RESETS_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile RESETS_Type* RESETS_CLEAR =  reinterpret_cast<RESETS_Type*>(RESETS_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile PSM_Type* PSM = reinterpret_cast<PSM_Type*>(PSM_BASE );
volatile PSM_Type* PSM_XOR =  reinterpret_cast<PSM_Type*>(PSM_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile PSM_Type* PSM_SET =  reinterpret_cast<PSM_Type*>(PSM_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile PSM_Type* PSM_CLEAR =  reinterpret_cast<PSM_Type*>(PSM_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile IO_BANK0_Type* IO_BANK0 = reinterpret_cast<IO_BANK0_Type*>(IO_BANK0_BASE );
volatile IO_BANK0_Type* IO_BANK0_XOR =  reinterpret_cast<IO_BANK0_Type*>(IO_BANK0_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile IO_BANK0_Type* IO_BANK0_SET =  reinterpret_cast<IO_BANK0_Type*>(IO_BANK0_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile IO_BANK0_Type* IO_BANK0_CLEAR =  reinterpret_cast<IO_BANK0_Type*>(IO_BANK0_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile IO_QSPI_Type* IO_QSPI = reinterpret_cast<IO_QSPI_Type*>(IO_QSPI_BASE );
volatile IO_QSPI_Type* IO_QSPI_XOR =  reinterpret_cast<IO_QSPI_Type*>(IO_QSPI_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile IO_QSPI_Type* IO_QSPI_SET =  reinterpret_cast<IO_QSPI_Type*>(IO_QSPI_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile IO_QSPI_Type* IO_QSPI_CLEAR =  reinterpret_cast<IO_QSPI_Type*>(IO_QSPI_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile PADS_BANK0_Type* PADS_BANK0 = reinterpret_cast<PADS_BANK0_Type*>(PADS_BANK0_BASE );
volatile PADS_BANK0_Type* PADS_BANK0_XOR =  reinterpret_cast<PADS_BANK0_Type*>(PADS_BANK0_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile PADS_BANK0_Type* PADS_BANK0_SET =  reinterpret_cast<PADS_BANK0_Type*>(PADS_BANK0_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile PADS_BANK0_Type* PADS_BANK0_CLEAR =  reinterpret_cast<PADS_BANK0_Type*>(PADS_BANK0_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile PADS_QSPI_Type* PADS_QSPI = reinterpret_cast<PADS_QSPI_Type*>(PADS_QSPI_BASE );
volatile PADS_QSPI_Type* PADS_QSPI_XOR =  reinterpret_cast<PADS_QSPI_Type*>(PADS_QSPI_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile PADS_QSPI_Type* PADS_QSPI_SET =  reinterpret_cast<PADS_QSPI_Type*>(PADS_QSPI_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile PADS_QSPI_Type* PADS_QSPI_CLEAR =  reinterpret_cast<PADS_QSPI_Type*>(PADS_QSPI_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile XOSC_Type* XOSC = reinterpret_cast<XOSC_Type*>(XOSC_BASE );
volatile XOSC_Type* XOSC_XOR =  reinterpret_cast<XOSC_Type*>(XOSC_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile XOSC_Type* XOSC_SET =  reinterpret_cast<XOSC_Type*>(XOSC_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile XOSC_Type* XOSC_CLEAR =  reinterpret_cast<XOSC_Type*>(XOSC_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile PLL_SYS_Type* PLL_SYS = reinterpret_cast<PLL_SYS_Type*>(PLL_SYS_BASE );
volatile PLL_SYS_Type* PLL_SYS_XOR =  reinterpret_cast<PLL_SYS_Type*>(PLL_SYS_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile PLL_SYS_Type* PLL_SYS_SET =  reinterpret_cast<PLL_SYS_Type*>(PLL_SYS_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile PLL_SYS_Type* PLL_SYS_CLEAR =  reinterpret_cast<PLL_SYS_Type*>(PLL_SYS_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile PLL_SYS_Type* PLL_USB = reinterpret_cast<PLL_SYS_Type*>(PLL_USB_BASE );
volatile PLL_SYS_Type* PLL_USB_XOR =  reinterpret_cast<PLL_SYS_Type*>(PLL_USB_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile PLL_SYS_Type* PLL_USB_SET =  reinterpret_cast<PLL_SYS_Type*>(PLL_USB_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile PLL_SYS_Type* PLL_USB_CLEAR =  reinterpret_cast<PLL_SYS_Type*>(PLL_USB_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile BUSCTRL_Type* BUSCTRL = reinterpret_cast<BUSCTRL_Type*>(BUSCTRL_BASE );
volatile BUSCTRL_Type* BUSCTRL_XOR =  reinterpret_cast<BUSCTRL_Type*>(BUSCTRL_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile BUSCTRL_Type* BUSCTRL_SET =  reinterpret_cast<BUSCTRL_Type*>(BUSCTRL_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile BUSCTRL_Type* BUSCTRL_CLEAR =  reinterpret_cast<BUSCTRL_Type*>(BUSCTRL_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile UART0_Type* UART0 = reinterpret_cast<UART0_Type*>(UART0_BASE );
volatile UART0_Type* UART0_XOR =  reinterpret_cast<UART0_Type*>(UART0_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile UART0_Type* UART0_SET =  reinterpret_cast<UART0_Type*>(UART0_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile UART0_Type* UART0_CLEAR =  reinterpret_cast<UART0_Type*>(UART0_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile UART0_Type* UART1 = reinterpret_cast<UART0_Type*>(UART1_BASE );
volatile UART0_Type* UART1_XOR =  reinterpret_cast<UART0_Type*>(UART1_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile UART0_Type* UART1_SET =  reinterpret_cast<UART0_Type*>(UART1_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile UART0_Type* UART1_CLEAR =  reinterpret_cast<UART0_Type*>(UART1_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile SPI0_Type* SPI0 = reinterpret_cast<SPI0_Type*>(SPI0_BASE );
volatile SPI0_Type* SPI0_XOR =  reinterpret_cast<SPI0_Type*>(SPI0_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile SPI0_Type* SPI0_SET =  reinterpret_cast<SPI0_Type*>(SPI0_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile SPI0_Type* SPI0_CLEAR =  reinterpret_cast<SPI0_Type*>(SPI0_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile SPI0_Type* SPI1 = reinterpret_cast<SPI0_Type*>(SPI1_BASE );
volatile SPI0_Type* SPI1_XOR =  reinterpret_cast<SPI0_Type*>(SPI1_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile SPI0_Type* SPI1_SET =  reinterpret_cast<SPI0_Type*>(SPI1_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile SPI0_Type* SPI1_CLEAR =  reinterpret_cast<SPI0_Type*>(SPI1_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile I2C0_Type* I2C0 = reinterpret_cast<I2C0_Type*>(I2C0_BASE );
volatile I2C0_Type* I2C0_XOR =  reinterpret_cast<I2C0_Type*>(I2C0_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile I2C0_Type* I2C0_SET =  reinterpret_cast<I2C0_Type*>(I2C0_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile I2C0_Type* I2C0_CLEAR =  reinterpret_cast<I2C0_Type*>(I2C0_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile I2C0_Type* I2C1 = reinterpret_cast<I2C0_Type*>(I2C1_BASE );
volatile I2C0_Type* I2C1_XOR =  reinterpret_cast<I2C0_Type*>(I2C1_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile I2C0_Type* I2C1_SET =  reinterpret_cast<I2C0_Type*>(I2C1_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile I2C0_Type* I2C1_CLEAR =  reinterpret_cast<I2C0_Type*>(I2C1_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile ADC_Type* ADC = reinterpret_cast<ADC_Type*>(ADC_BASE );
volatile ADC_Type* ADC_XOR =  reinterpret_cast<ADC_Type*>(ADC_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile ADC_Type* ADC_SET =  reinterpret_cast<ADC_Type*>(ADC_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile ADC_Type* ADC_CLEAR =  reinterpret_cast<ADC_Type*>(ADC_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile PWM_Type* PWM = reinterpret_cast<PWM_Type*>(PWM_BASE );
volatile PWM_Type* PWM_XOR =  reinterpret_cast<PWM_Type*>(PWM_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile PWM_Type* PWM_SET =  reinterpret_cast<PWM_Type*>(PWM_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile PWM_Type* PWM_CLEAR =  reinterpret_cast<PWM_Type*>(PWM_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile TIMER_Type* TIMER = reinterpret_cast<TIMER_Type*>(TIMER_BASE );
volatile TIMER_Type* TIMER_XOR =  reinterpret_cast<TIMER_Type*>(TIMER_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile TIMER_Type* TIMER_SET =  reinterpret_cast<TIMER_Type*>(TIMER_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile TIMER_Type* TIMER_CLEAR =  reinterpret_cast<TIMER_Type*>(TIMER_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile WATCHDOG_Type* WATCHDOG = reinterpret_cast<WATCHDOG_Type*>(WATCHDOG_BASE );
volatile WATCHDOG_Type* WATCHDOG_XOR =  reinterpret_cast<WATCHDOG_Type*>(WATCHDOG_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile WATCHDOG_Type* WATCHDOG_SET =  reinterpret_cast<WATCHDOG_Type*>(WATCHDOG_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile WATCHDOG_Type* WATCHDOG_CLEAR =  reinterpret_cast<WATCHDOG_Type*>(WATCHDOG_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile RTC_Type* RTC = reinterpret_cast<RTC_Type*>(RTC_BASE );
volatile RTC_Type* RTC_XOR =  reinterpret_cast<RTC_Type*>(RTC_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile RTC_Type* RTC_SET =  reinterpret_cast<RTC_Type*>(RTC_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile RTC_Type* RTC_CLEAR =  reinterpret_cast<RTC_Type*>(RTC_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile ROSC_Type* ROSC = reinterpret_cast<ROSC_Type*>(ROSC_BASE );
volatile ROSC_Type* ROSC_XOR =  reinterpret_cast<ROSC_Type*>(ROSC_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile ROSC_Type* ROSC_SET =  reinterpret_cast<ROSC_Type*>(ROSC_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile ROSC_Type* ROSC_CLEAR =  reinterpret_cast<ROSC_Type*>(ROSC_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile VREG_AND_CHIP_RESET_Type* VREG_AND_CHIP_RESET = reinterpret_cast<VREG_AND_CHIP_RESET_Type*>(VREG_AND_CHIP_RESET_BASE );
volatile VREG_AND_CHIP_RESET_Type* VREG_AND_CHIP_RESET_XOR =  reinterpret_cast<VREG_AND_CHIP_RESET_Type*>(VREG_AND_CHIP_RESET_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile VREG_AND_CHIP_RESET_Type* VREG_AND_CHIP_RESET_SET =  reinterpret_cast<VREG_AND_CHIP_RESET_Type*>(VREG_AND_CHIP_RESET_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile VREG_AND_CHIP_RESET_Type* VREG_AND_CHIP_RESET_CLEAR =  reinterpret_cast<VREG_AND_CHIP_RESET_Type*>(VREG_AND_CHIP_RESET_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile TBMAN_Type* TBMAN = reinterpret_cast<TBMAN_Type*>(TBMAN_BASE );
volatile TBMAN_Type* TBMAN_XOR =  reinterpret_cast<TBMAN_Type*>(TBMAN_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile TBMAN_Type* TBMAN_SET =  reinterpret_cast<TBMAN_Type*>(TBMAN_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile TBMAN_Type* TBMAN_CLEAR =  reinterpret_cast<TBMAN_Type*>(TBMAN_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile DMA_Type* DMA = reinterpret_cast<DMA_Type*>(DMA_BASE );
volatile DMA_Type* DMA_XOR =  reinterpret_cast<DMA_Type*>(DMA_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile DMA_Type* DMA_SET =  reinterpret_cast<DMA_Type*>(DMA_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile DMA_Type* DMA_CLEAR =  reinterpret_cast<DMA_Type*>(DMA_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile USBCTRL_DPRAM_Type* USBCTRL_DPRAM = reinterpret_cast<USBCTRL_DPRAM_Type*>(USBCTRL_DPRAM_BASE );
volatile USBCTRL_DPRAM_Type* USBCTRL_DPRAM_XOR =  reinterpret_cast<USBCTRL_DPRAM_Type*>(USBCTRL_DPRAM_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile USBCTRL_DPRAM_Type* USBCTRL_DPRAM_SET =  reinterpret_cast<USBCTRL_DPRAM_Type*>(USBCTRL_DPRAM_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile USBCTRL_DPRAM_Type* USBCTRL_DPRAM_CLEAR =  reinterpret_cast<USBCTRL_DPRAM_Type*>(USBCTRL_DPRAM_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile USBCTRL_REGS_Type* USBCTRL_REGS = reinterpret_cast<USBCTRL_REGS_Type*>(USBCTRL_REGS_BASE );
volatile USBCTRL_REGS_Type* USBCTRL_REGS_XOR =  reinterpret_cast<USBCTRL_REGS_Type*>(USBCTRL_REGS_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile USBCTRL_REGS_Type* USBCTRL_REGS_SET =  reinterpret_cast<USBCTRL_REGS_Type*>(USBCTRL_REGS_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile USBCTRL_REGS_Type* USBCTRL_REGS_CLEAR =  reinterpret_cast<USBCTRL_REGS_Type*>(USBCTRL_REGS_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile PIO0_Type* PIO0 = reinterpret_cast<PIO0_Type*>(PIO0_BASE );
volatile PIO0_Type* PIO0_XOR =  reinterpret_cast<PIO0_Type*>(PIO0_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile PIO0_Type* PIO0_SET =  reinterpret_cast<PIO0_Type*>(PIO0_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile PIO0_Type* PIO0_CLEAR =  reinterpret_cast<PIO0_Type*>(PIO0_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile PIO0_Type* PIO1 = reinterpret_cast<PIO0_Type*>(PIO1_BASE );
volatile PIO0_Type* PIO1_XOR =  reinterpret_cast<PIO0_Type*>(PIO1_BASE + REGISTER_ATOMIC_XOR_OFFSET);
volatile PIO0_Type* PIO1_SET =  reinterpret_cast<PIO0_Type*>(PIO1_BASE + REGISTER_ATOMIC_SET_OFFSET);
volatile PIO0_Type* PIO1_CLEAR =  reinterpret_cast<PIO0_Type*>(PIO1_BASE + REGISTER_ATOMIC_CLEAR_OFFSET);

volatile SIO_Type* SIO = reinterpret_cast<SIO_Type*>(SIO_BASE );

volatile PPB_Type* PPB = reinterpret_cast<PPB_Type*>(PPB_BASE );
}
} // namespace rp2040::registers

