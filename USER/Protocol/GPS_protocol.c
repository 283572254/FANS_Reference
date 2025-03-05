#include "../USER/Protocol/GPS_protocol.h"
#include "stdbool.h"
#include "string.h"
#include "../BSP/Driver.h"
_SaveData Save_Data;
#define MAX_BUFFER_SIZE 80



void errorLog(int num)
{
	
	while (1)
	{
	  	printf("ERROR%d\r\n",num);
	}
}

void parseGpsBuffer()
{
	char *subString;
	char *subStringNext;
	char i = 0;

	if (Save_Data.isGetData)////�Ƿ��ȡ��GPS����
	{
		Save_Data.isGetData = false;
		printf("**************\r\n");
		printf(Save_Data.GPS_Buffer);
		for (i = 0 ; i <= 6 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1);	//��������
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)//��������н������
				{
					char usefullBuffer[2]; 
					switch(i)
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//��ȡUTCʱ��
					  	case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//��ȡUTCʱ��
						case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//��ȡγ����Ϣ
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//��ȡN/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//��ȡ������Ϣ
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//��ȡE/W

						default:break;
					}

					subString = subStringNext;
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')//��Ч��λ
						Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')//��Ч��λ
						Save_Data.isUsefull = false;

				}
				else
				{
					errorLog(2);	//��������
				}
			}


		}
	}
}


void process_uart_data(void) 
{
	uint8_t data;
	uint8_t buffer[MAX_BUFFER_SIZE] = {0}; 
	size_t index = 0;
    if(g_data_ready_flag == 1)
    {
        HAL_NVIC_DisableIRQ(USART1_IRQn);
        while (!ringbuffer_is_empty(&husart_rx_rb)) 
        {
            ringbuffer_read(&husart_rx_rb, &data);
            // ������յ�֡β'!'�����Խ�������
            if (data == '$') 
                index = 0;

			buffer[index++] = data;
			if(buffer[0] == '$' && buffer[4] == 'M' && buffer[5] == 'C')
			{
				if(data == '\n')
				{
					memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);
					memcpy(Save_Data.GPS_Buffer, buffer, index);
					Save_Data.isGetData = true;
					parseGpsBuffer();
					index = 0;
					g_data_ready_flag = 0;
				}
			}

        }
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }

}





