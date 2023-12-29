/******************************************************************************
 * @file task2.c
 *
 * @brief Serial Communication protocol task
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
#include "task2.h"

/******************************************************************************
 * Global Variable Declarations
 *****************************************************************************/
extern uint32_t g_rx_flag;
extern uint32_t g_rx_data;

/******************************************************************************
 *
 * FUNCTION NAME: task2
 *
 * DESCRIPTION:
 * Function monitors global data queue for data from USART and
 * toggles LED based on data
 *
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
void task2(void){
	volatile uint32_t temp;
	if(g_rx_flag == 1){
		temp = g_rx_data;
		temp++;
		g_rx_flag = 0;
	}
}


