# STM32F411 Bare-Metal Drivers

Register-level GPIO and SPI drivers for the STM32F411, written in C without STM32 HAL or LL libraries.

## Features

### GPIO

- Configure pins as input, output, alternate function, or analog
- Configure output type, speed, and pull-up/pull-down resistors
- Configure alternate function selection through the AFR registers
- Read and write individual pins or full ports
- Configure external interrupts (EXTI)
- Enable, disable, and set priorities for interrupts through the NVIC
- Handle and clear pending GPIO interrupts

### SPI

- Configure the SPI peripheral, including device mode, bus configuration, clock prescaler, data frame format, CPOL, CPHA, and software slave management
- Send and receive data using blocking functions
- Send and receive data using interrupt-based functions
- Handle TXE, RXNE, and overrun (OVR) interrupt events
- Report transfer completion and errors through an application callback
- Control the SPI peripheral, SSI, and SSOE
- Clear the OVR flag by reading the data register followed by the status register

## Architecture

Peripheral registers are accessed through C register structures mapped to their hardware base addresses. The project does not use a vendor driver abstraction.

GPIO pin configuration, EXTI configuration, NVIC configuration, and interrupt handling are implemented as separate operations. The SPI driver provides both blocking and interrupt-based transfer functions.

## Examples

The `Src/` directory contains GPIO and SPI examples, including:

- LED toggle and button input
- Button-triggered GPIO interrupt
- SPI transmit-only communication with Arduino
- SPI command and response handling with Arduino
- SPI transmit and receive using interrupts with Arduino

The SPI examples configure SPI1 pins on GPIOA using alternate function AF5.

## Hardware

- Board: STM32 NUCLEO-F411RE
- Microcontroller: STM32F411RE

## Known Limitations

- Button debounce is handled by the application rather than the GPIO driver.

## Debugging History

See [DEBUG_LOG.md](./DEBUG_LOG.md) for debugging notes.