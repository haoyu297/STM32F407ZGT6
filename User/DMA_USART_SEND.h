#ifndef __DMA_USART_SEND_H
#define __DMA_USART_SEND_H

typedef unsigned	int uint32_t;
typedef unsigned short     int uint16_t;
typedef unsigned	char uint8_t;

typedef struct
{
	uint8_t send_start1;         /* 帧起始符 *****/
	uint8_t send_type[4];        /* 设备类型 *****/
	uint8_t send_address[6];     /* 外设模块地址 */
	uint8_t send_start2;         /* 帧起始符 *****/
	uint8_t send_datalen[2];     /* 数据域长度 ***/
	uint8_t send_SEQ;            /* 帧序号 *******/
	uint8_t send_C;              /* 控制码 *******/
	uint8_t send_Fn[2];          /* 功能码 *******/
	//uint8_t send_Data[];       /* 数据域 *******/
	uint8_t send_CS;             /* 校验码 *******/
	uint8_t send_END;            /* 结束符 *******/
}Sendbuff;

typedef struct
{
	uint8_t get_start1;          /* 帧起始符 *****/
	uint8_t get_type[4];         /* 设备类型 *****/
	uint8_t get_address[6];      /* 外设模块地址 */
	uint8_t get_start2;          /* 帧起始符 *****/
	uint8_t get_datalen[2];      /* 数据域长度 ***/
	uint8_t get_SEQ;             /* 帧序号 *******/
	uint8_t get_C;               /* 控制码 *******/
	uint8_t get_Fn[2];           /* 功能码 *******/
	uint8_t get_CS;              /* 校验码 *******/
	uint8_t get_END;             /* 结束符 *******/
	uint8_t get_Data[];          /* 数据域 *******/
}getbuff;	

void send(uint8_t *data,Sendbuff* Sendbuff,uint8_t *asd);
void senddata(getbuff *rx_buf,uint8_t *WANT_SEND,uint16_t Data_TxLen);

void Hand_Rx_Buff(void);
void Bluetooth(uint16_t CMD);

#endif 


