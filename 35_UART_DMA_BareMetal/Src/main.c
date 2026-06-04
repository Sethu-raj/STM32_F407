#include "stm32f407xx.h"
#include <string.h>

/* Buffers */
uint8_t tx_data[] = "Sethu\r\n";
uint8_t rx_buffer[50];

int main(void)
{
    // Init UART + D
	USART2_DMA_Init();

    while(1)
    {

        // Transmit data
         USART2_DMA_TX(tx_data, strlen((char*)tx_data));
        // Start RX first
         USART2_DMA_RX(rx_buffer, strlen((char*)tx_data));

        // Small delay (just to observe clearly)
        for(volatile int i = 0; i < 1000000; i++);

        // Now rx_buffer should contain same data (loopback)
    }
}
