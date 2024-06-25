/*
 * card_data_com.c
 *
 *  Created on: May 23, 2024
 *      Author: Ludovic
 */

#include "card_data_com.h"
#include "usbd_cdc_if.h"
#include "string.h"

char receive_buffer[64]={0};

uint8_t send_data_with_vcm(char* data)
{
	CDC_Transmit_FS((uint8_t *)data, strlen(data));

	return 0;
}

void receive_data_with_vcp(char* data, uint8_t len)
{
	//memset(receive_buffer, '\0', 64);

	memcpy(receive_buffer, data, len);

	send_data_with_vcm(receive_buffer);
}
