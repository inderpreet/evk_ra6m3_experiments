# Experiments with the Renesas RA6M3G kit

This respository is essentially me messing around with the RA6M3 Dev Kit. 

# Notes

- reset vector is where code starts to boot.
- hal_entry is called from within main()
- app.c is where I have most of my code.

## Hardware Config

I have the Ra6M3 dev kit with an oscilloscope and a Mikro UART Click board.

- UART7 is used for the serial data at 115200. 
- P0207 is used as a GPIO. I connected a Scope here
- Timer 0 is used to generate an interrupt and I have a global variable to count up.

## Interrupts

There are two interrupts setup for this system. 
```tmr0_callback()``` is called everytime the timer expires.
```uart_callback()``` is called everytime data is transmitted or received on the UART.

## mon

```mon_init()``` and ```mon_send()``` are functions to send out stuff over usart. ```mon_send()``` sends out a Hello, World over the click board usart.

## task1

Task1 is essentially a non-blocking Blinking LED with mon_send being called as well.


# Author 

ip_v1