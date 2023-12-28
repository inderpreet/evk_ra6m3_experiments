/******************************************************************************
 * @file app.c
 *
 * @brief Application for testing Development Kit
 *
 * NOTES:
 *
 * @author Inderpreet Singh(ip_v1)
 *
 *****************************************************************************/

/******************************************************************************
 * Global Includes
 *****************************************************************************/
#include "hal_data.h"
#include "app.h"

/******************************************************************************
 * Global Variable Declarations
 *****************************************************************************/
volatile uint32_t g_systick_counter = 0;
extern bsp_leds_t g_bsp_leds;
volatile const uint8_t str1[] = "Hello, World\n\r"; // 14 len

/******************************************************************************
 *
 * FUNCTION NAME: mon_init
 *
 * DESCRIPTION:
 * Initialization code for the test application.
 *
 * CREATED BY:
 * Inderpreet Singh
 *
 * PARAMETERS:  None.
 *
 * RETURN VALUE:  None.
 *
 * Notes:  None.
 *
 *****************************************************************************/
inline void mon_init(void) {
	R_SCI_UART_Open(&uart_one_ctrl, &uart_one_cfg);
	R_AGT_Open(&g_timer0_ctrl, &g_timer0_cfg);
	R_AGT_Start(&g_timer0_ctrl);
}

/******************************************************************************
 *
 * FUNCTION NAME: mon_send
 *
 * DESCRIPTION:
 * Function to send out a fixed string over USART
 *
 * CREATED BY:
 * Inderpreet Singh
 *
 * PARAMETERS:  None.
 *
 * RETURN VALUE:  None.
 *
 * Notes:  None.
 *
 *****************************************************************************/
void mon_send(void) {
	R_SCI_UART_Write(&uart_one_ctrl, (uint8_t*) str1, 14);
}

/******************************************************************************
 *
 * FUNCTION NAME: tmr0_callback
 *
 * DESCRIPTION:
 * - Callback function for Timer 0. Function is called every 1ms as
 * 		per setting in BSP/FSP. Global variable g_systick_counter is incremented
 * 		everytime there is a call.
 * - Also toggles GPIO at P207 at 1ms
 *
 * CREATED BY:
 * Inderpreet Singh
 *
 * PARAMETERS:
 *
 * RETURN VALUE:  None.
 *
 * Notes:  None.
 *
 *****************************************************************************/
void tmr0_callback(timer_callback_args_t *p_args) {
	static uint8_t level = 0;
//    __NOP();
	g_systick_counter++;

	// Toggle GPIO P207
	R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_02_PIN_07, level);
	if (level == 0) {
		level = 1;
	} else {
		level = 0;
	}
}

/******************************************************************************
 *
 * FUNCTION NAME: task1
 *
 * DESCRIPTION:
 * - Simple task to blink the BSP LEDs every 500ms. Task monitors systick counter
 * 		and toggled all LEDs.
 * - Also send out Hello World by calling mon_send()
 *
 * CREATED BY:
 * Inderpreet Singh
 *
 * PARAMETERS:  None.
 *
 * RETURN VALUE:  None.
 *
 * Notes:  None.
 *
 *****************************************************************************/
void task1(void) {
	bsp_leds_t leds = g_bsp_leds;
	static bsp_io_level_t pin_level = BSP_IO_LEVEL_LOW;

	static uint32_t cnt = 0;
	uint32_t temp = g_systick_counter;

	if (temp - cnt > 500) {
		cnt = temp;
		R_BSP_PinAccessEnable();

		/* Update all board LEDs */
		for (uint32_t i = 0; i < leds.led_count; i++) {
			/* Get pin to toggle */
			uint32_t pin = leds.p_leds[i];

			/* Write to this pin */
			R_BSP_PinWrite((bsp_io_port_pin_t) pin, pin_level);
		}

		/* Protect PFS registers */
		R_BSP_PinAccessDisable();

		/* Toggle level for next write */
		if (BSP_IO_LEVEL_LOW == pin_level) {
			pin_level = BSP_IO_LEVEL_HIGH;
		} else {
			pin_level = BSP_IO_LEVEL_LOW;
		}

		mon_send();
	} // end if
}
