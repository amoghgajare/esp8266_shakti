/***************************************************************************
  * 5. Change the SSID and Password

*/

#include "uart.h"//Includes the definitions of uart communication protocol//
#include "string.h"
#include "pinmux.h"
#define API_KEY   "CXDZFGD1QQ8HYVTG"
#define ESP_UART uart_instance[1]
/**
  * @fn int write_to_esp8266(char *data)
  * @brief sends data to esp8266 using UART
  * @param data data that has to be sent to cloud
*/

int write_to_esp8266(char *data) {
	while (*data != '\0') {
		write_uart_character(ESP_UART, *data);
		data++;
	}
	write_uart_character(ESP_UART,'\r');
	write_uart_character(ESP_UART,'\n');

}

/**
  * @fn int write_enter_to_esp8266()
  * @brief sends carriage return and new line charector to esp8266
  * @detail sends carriage return and new line charector to esp8266
  *         this method is neeed to indicate end to data transmission
*/

int write_enter_to_esp8266(){
	write_uart_character(ESP_UART,'\r');
	write_uart_character(ESP_UART,'\n');
}

/**
  * @fn int read_from_esp8266(char *data)
  * @brief Reads data sent by esp8266
  * @details Reads data sent by esp8266 until one of the key word is found
  * @param data responses read from esp8266, mainly used for logging
*/
int read_from_esp8266(char *data) {
	int ch;
	char *str = data;
	char *test = data;
	for(int i=0;i<198;i++) {
		read_uart_character(ESP_UART,&ch);
		printf("read from esp %c  \n",ch);
		*str = ch;
		str++; 
		*str = '\0';
		printf("read  %c\n",ch);
		if(strstr(test,"OK") != NULL)  {
			printf("read from esp8266 %s\n",test);
			return;
		}
		if(strstr(test,"ERROR") != NULL) {
			printf("read from esp8266 %s\n",test);
			return;
		}
		if(strstr(test,">") != NULL) {
			printf("read from esp8266 %s\n",test);
			return;
		}
		if(strstr(test,"RECV") != NULL) {
			printf("read from esp8266 %s\n",test);
			return;
		}
		if(strstr(test,"IP") != NULL) {
			printf("read from esp8266 %s\n",test);
			return;
		}
	}
	*str = '\0';
	return 1;
}

/**
  * @fn void setup_esp8266 ()
  * @brief setup esp8266
  * @details set up esp8266 to send data
*/
void setup_esp8266(){
	char data[200];
	write_to_esp8266("AT+RST"); //Restarts the Module
	delay(1);
	read_from_esp8266(data);

	printf(" Connect esp8266 to AP \n");
	write_to_esp8266("AT+CWMODE=1"); //Setting up ESP8266 as a STA
	delay(3);
	read_from_esp8266(data);
	write_to_esp8266("AT+CWJAP_DEF=\"SSID\",\"PASSWORD\""); //Edit the SSID and Password 
	delay(3);
	read_from_esp8266(data);

	printf(" sending AT Echo on command to esp\n");
	write_to_esp8266("ATE1"); //Turning Echo On
	delay(1);
	read_from_esp8266(data);
	printf(" write AT+CIPMUX\n");
	write_to_esp8266("AT+CIPMUX=0"); //Establishes Single TCP Connection
	delay(1);
	read_from_esp8266(data);
}
/**
  * @fn void transmit_data (int temperature )
  * @brief transmit temperature value to thingspeak.com using esp8266
  * @details Open http connection to thingspeak.com, using GET method send data and close the connection
  * @param temperature value that has to eb transmitted.
*/
void transmit_data(int cell1_voltage) {
/***************************************************
    AT – response OK
    AT+CWLAP – list nearby available WiFi networks
    AT+CIPMUX=0
    AT+CIPSTART="TCP","api.thingspeak.com",80
    AT+CIPSEND=75
    GET https://api.thingspeak.com/update?api_key=CXDZFGD1QQ8HYVTG&field1=45

**************************************************/

	char data[200];
	char sendData1[76];
	sprintf(sendData1,"GET https://api.thingspeak.com/update?api_key=%s&field1=%d",API_KEY,cell1_voltage);
	printf("\n send data %s\n",sendData1);
	// Connect to Wifi using esp8266

		// Connect to Wifi using esp8266
		//printf(" Open connection to thingspeak.com\n",data);
		flush_uart(ESP_UART);
		write_to_esp8266("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80");
		read_from_esp8266(data);
		printf(" data from esp :%s\n",data);
	
		//delay_loop(2000,2000);
		printf(" write AT+CIPSEND\n");
		flush_uart(ESP_UART);
		write_to_esp8266("AT+CIPSEND=75");
		read_from_esp8266(data);
		printf(" data from esp :%s\n",data);
	
		printf(" write Data\n");
		flush_uart(ESP_UART);
		write_to_esp8266(sendData1);
	write_enter_to_esp8266();
		delay_loop(1000,1000);
		read_from_esp8266(data);
		printf(" data from esp :%s\n",data);
	
		//flush_uart(ESP_UART);
		write_enter_to_esp8266();
		delay_loop(1000,1000);
		read_from_esp8266(data);
		printf(" data from esp :%s\n",data);
	
		// disconnect from link
		printf(" write AT+CIPCLOSE\n");
		flush_uart(ESP_UART);
		write_to_esp8266("AT+CIPCLOSE");
		read_from_esp8266(data);
		printf(" data from esp :%s\n",data);

}

/**
  * @fn void main()
  * @brief Entry point for the program
  * @detail sets the pinmux to select UART1 to communicate with esp8266
  *      Set desired baudrate, get temperature from lm75 
  *      transmit data to thingspeak.com
*/
void main()
{	
	int i=0;
	//int baudrate = 9600;
	int baudrate = 115200;
	int cell1_voltage=0;
	int transmit_count = 0;
	char data[200];
   	printf("\n setting PIN MUX config to 2 .... \n");
    	*pinmux_config_reg = 0x5;
   	printf("\n set PIN MUX config to 2 .... \n");
	set_baud_rate(ESP_UART,baudrate);	
	printf("\n Sending temperature data to cloud server!....\n");
	printf("\n Baud rate set to %d \n",baudrate);
	printf("\n Waiting to ESP8266 to initialize \n");
	delay(3);
	setup_esp8266();
	while (1) {
 	cell1_voltage=10; //data
	transmit_data(cell1_voltage); 
	delay(60);
	}
}
