#ifndef __DMA_USART_SEND_H
#define __DMA_USART_SEND_H

typedef unsigned	int uint32_t;
typedef unsigned short     int uint16_t;
typedef unsigned	char uint8_t;

typedef struct
{
	uint8_t send_start1;         /* ֡��ʼ�� *****/
	uint8_t send_type[4];        /* �豸���� *****/
	uint8_t send_address[6];     /* ����ģ���ַ */
	uint8_t send_start2;         /* ֡��ʼ�� *****/
	uint8_t send_datalen[2];     /* �����򳤶� ***/
	uint8_t send_SEQ;            /* ֡��� *******/
	uint8_t send_C;              /* ������ *******/
	uint8_t send_Fn[2];          /* ������ *******/
	//uint8_t send_Data[];       /* ������ *******/
	uint8_t send_CS;             /* У���� *******/
	uint8_t send_END;            /* ������ *******/
}Sendbuff;

typedef struct
{
	uint8_t get_start1;          /* ֡��ʼ�� *****/
	uint8_t get_type[4];         /* �豸���� *****/
	uint8_t get_address[6];      /* ����ģ���ַ */
	uint8_t get_start2;          /* ֡��ʼ�� *****/
	uint8_t get_datalen[2];      /* �����򳤶� ***/
	uint8_t get_SEQ;             /* ֡��� *******/
	uint8_t get_C;               /* ������ *******/
	uint8_t get_Fn[2];           /* ������ *******/
	uint8_t get_CS;              /* У���� *******/
	uint8_t get_END;             /* ������ *******/
	uint8_t get_Data[];          /* ������ *******/
}getbuff;	

void send(uint8_t *data,Sendbuff* Sendbuff,uint8_t *asd);
void senddata(getbuff *rx_buf,uint8_t *WANT_SEND,uint16_t Data_TxLen);

void Hand_Rx_Buff(void);
void Bluetooth(uint16_t CMD);

#endif 


