/*
 * app.c
 *
 *  Created on: Dec. 27, 2023
 *      Author: Ip_v1
 */
#include "hal_data.h"
#include "app.h"

volatile uint32_t g_systick_counter = 0;
extern bsp_leds_t g_bsp_leds;

volatile const uint8_t str1[] = "Hello, World\n\r"; // 14 len
//    const uint8_t index = 0;

inline void mon_init(void)
{
    R_SCI_UART_Open (&uart_one_ctrl, &uart_one_cfg);
    R_AGT_Open (&g_timer0_ctrl, &g_timer0_cfg);
    R_AGT_Start (&g_timer0_ctrl);
}

void mon_send(void)
{
    R_SCI_UART_Write (&uart_one_ctrl, (uint8_t*) str1, 14);
}

void tmr0_callback(timer_callback_args_t *p_args)
{
    static uint8_t level = 0;
//    __NOP();
    g_systick_counter++;

    // Toggle GPIO P207
    R_IOPORT_PinWrite (&g_ioport_ctrl, BSP_IO_PORT_02_PIN_07, level);
    if (level == 0)
    {
        level = 1;
    }
    else
    {
        level = 0;
    }
}

void task1(void)
{
    volatile static uint8_t st = 0;
    bsp_leds_t leds = g_bsp_leds;
    static bsp_io_level_t pin_level = BSP_IO_LEVEL_LOW;

    static uint32_t cnt = 0;
    uint32_t temp = g_systick_counter;

    if (temp - cnt > 100)
    {
        cnt = temp;
        R_BSP_PinAccessEnable ();

        /* Update all board LEDs */
        for (uint32_t i = 0; i < leds.led_count; i++)
        {
            /* Get pin to toggle */
            uint32_t pin = leds.p_leds[i];

            /* Write to this pin */
            R_BSP_PinWrite ((bsp_io_port_pin_t) pin, pin_level);
        }

        /* Protect PFS registers */
        R_BSP_PinAccessDisable ();

        mon_send ();

        /* Toggle level for next write */
        if (BSP_IO_LEVEL_LOW == pin_level)
        {
            pin_level = BSP_IO_LEVEL_HIGH;
        }
        else
        {
            pin_level = BSP_IO_LEVEL_LOW;
        }
    }
}
