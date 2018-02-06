#include "include.h"


uint8_t DMA_Rx_Data[500];
Sendbuff Sendbuff1;

extern u8 Rx_BuffLen;
extern uint8_t Rx_Buff[SENDBUFF_SIZE];
extern uint8_t Achieve_Flg;
uint16_t Data_RxLen;
uint16_t Bluetooth_CMD;
uint8_t  setdata[SENDBUFF_SIZE];
getbuff* rx_buff = (getbuff*)setdata;

uint8_t Count;
							 
uint8_t Information_Change_Flg = 0;

void senddata(getbuff *rx_buf,uint8_t *WANT_SEND,uint16_t Data_TxLen)
{
	
	/* ֡��ʼ�� */
	Sendbuff1.send_start1=0x97;
	
	/* �豸���� */
	Sendbuff1.send_type[0]=rx_buf->get_type[0];
	Sendbuff1.send_type[1]=rx_buf->get_type[1];
	Sendbuff1.send_type[2]=rx_buf->get_type[2];
	Sendbuff1.send_type[3]=rx_buf->get_type[3];
	
	/* ����ģ���ַ */
	Sendbuff1.send_address[0]=rx_buff->get_address[0];
	Sendbuff1.send_address[1]=rx_buff->get_address[1];
	Sendbuff1.send_address[2]=rx_buff->get_address[2];
	Sendbuff1.send_address[3]=rx_buff->get_address[3];
	Sendbuff1.send_address[4]=rx_buff->get_address[4];
	Sendbuff1.send_address[5]=rx_buff->get_address[5];
	
	/* ֡��ʼ�� */
	Sendbuff1.send_start2=0x97;
	
	/* �����򳤶� */
	Sendbuff1.send_datalen[0]=(int8_t)(Data_TxLen&0x00ff);
	Sendbuff1.send_datalen[1]=((Data_TxLen&0xff00)>>8);
	
	/* ֡��� */
	Sendbuff1.send_SEQ=rx_buf->get_SEQ;
	
	/* ������ */
	Sendbuff1.send_C=0x80;
	
	/* ������ */
	Sendbuff1.send_Fn[0]=rx_buf->get_Fn[0];
	Sendbuff1.send_Fn[1]=rx_buf->get_Fn[1];
	
	/* У���� */
	//Sendbuff1.send_CS=0x97;
	
	/* ������ */
	Sendbuff1.send_END=0xE9;
	send(WANT_SEND,&Sendbuff1,DMA_Rx_Data);
	
}

void send(uint8_t *data,Sendbuff* Sendbuff,uint8_t *DMA_send)
{
	uint32_t length,i,j;
	uint8_t cs=0;
	DMA_send[0]=Sendbuff->send_start1;
	
	DMA_send[1] = Sendbuff->send_type[0];
	DMA_send[2] = Sendbuff->send_type[1];
	DMA_send[3] = Sendbuff->send_type[2];
	DMA_send[4] = Sendbuff->send_type[3];
	
	DMA_send[5]  = Sendbuff->send_address[0];
	DMA_send[6]  = Sendbuff->send_address[1];
	DMA_send[7]  = Sendbuff->send_address[2];
	DMA_send[8]  = Sendbuff->send_address[3];
	DMA_send[9]  = Sendbuff->send_address[4];
	DMA_send[10] = Sendbuff->send_address[5];
	
	DMA_send[11]=Sendbuff->send_start2;
	

	DMA_send[12]=Sendbuff->send_datalen[0];
	DMA_send[13]=Sendbuff->send_datalen[1];
	
	length=DMA_send[12] +(DMA_send[13]<<8);
	Print ("���������򳤶�Ϊ%uλ\n",length);
	DMA_send[14]=Sendbuff->send_SEQ;
	
	DMA_send[15]=Sendbuff->send_C;

	DMA_send[16]=Sendbuff->send_Fn[0];
	DMA_send[17]=Sendbuff->send_Fn[1];
	if(length != 0)
	{
		for(i=18,j=0;i<length+18;i++,j++)
	  {
			DMA_send[i] = data[j];
	  }
	}
	
	for(i=0;i<length+18;i++)
	{
		cs+=DMA_send[i];
	}
	DMA_send[length+18]=cs;
	DMA_send[length+19]=Sendbuff->send_END;
	
	USART_DMA_SENDMORE(length+20,DMA_send);
}
void Hand_Rx_Buff(void)
{
	uint16_t i;	
	if(Achieve_Flg) 
	{
		Achieve_Flg=0;
		Rx_BuffLen=0;
		
		rx_buff->get_start1=Rx_Buff[0];
		
		rx_buff->get_type[0]=Rx_Buff[1];
		rx_buff->get_type[1]=Rx_Buff[2];
		rx_buff->get_type[2]=Rx_Buff[3];
		rx_buff->get_type[3]=Rx_Buff[4];		
		rx_buff->get_address[0]=Rx_Buff[5];
		rx_buff->get_address[1]=Rx_Buff[6];
		rx_buff->get_address[2]=Rx_Buff[7];
		rx_buff->get_address[3]=Rx_Buff[8];
		rx_buff->get_address[4]=Rx_Buff[9];
		rx_buff->get_address[5]=Rx_Buff[10];		
		rx_buff->get_start2=Rx_Buff[11];
		rx_buff->get_datalen[0]=Rx_Buff[12];
		rx_buff->get_datalen[1]=Rx_Buff[13];
		Data_RxLen=((Rx_Buff[12]<<8)+Rx_Buff[13]);
		rx_buff->get_SEQ=Rx_Buff[14];
		rx_buff->get_C=Rx_Buff[15];
		rx_buff->get_Fn[0]=Rx_Buff[16];
		rx_buff->get_Fn[1]=Rx_Buff[17];
		
		Bluetooth_CMD=((Rx_Buff[16]<<8)+Rx_Buff[17]);
		
		if(Data_RxLen !=0 )
		{
			for(i=0;i<Data_RxLen;i++)
			{
				rx_buff->get_Data[i] = Rx_Buff[18+i];
			}	
		}
		rx_buff->get_CS  = Rx_Buff[18 + Data_RxLen];
		rx_buff->get_END = Rx_Buff[19 + Data_RxLen];
		for(i=0;i<SENDBUFF_SIZE;i++)
		{
			Rx_Buff[i] = 0;
		}
		Bluetooth(Bluetooth_CMD);	
	}
}
void Bluetooth(uint16_t CMD)
{
	//uint16_t i;
	Print ("������Ϊ0x%04x\n",CMD);
	switch(CMD)
	{
		case 0x0101://��ѯͨ�ò���//�豸��Ϣ
		{
			Send_Equipment_Information();
			senddata(rx_buff,Equipment_Information_Tmp,139);
			Print ("0x%04X�������%u\n",CMD,Count++);
			break;
		}
		case 0x0102://��ѯͨ�ò���//�豸״̬
		{
			Send_Equipment_Status();
			senddata(rx_buff,Equipment_Status_Tmp,7);
			Print ("0x%04X�������%u\n",CMD,Count++);
			break;
		}
		case 0x0103://��ѯͨ�ò���//���ϼ��
		{
			Send_Fault_Finding();
			senddata( rx_buff,Fault_Finding_Tmp,2);
			Print ("0x%04X�������%u\n",CMD,Count++);
			break;
		}
		case 0x0201://����ͨ�ò���//����ģ���ַ
		{
			break;
		}
		case 0x0202://����ͨ�ò���//��ȫ���ò���
		{
			break;
		}
		case 0x0301://��λ����//Ӳ����ʼ��
		{
			break;
		}
		case 0x0302://��λ����//��������ʼ��
		{
			break;
		}
		case 0x0303://��λ����//������ȫ����������ʼ��
		{
			break;
		}
		case 0x0401://����͸��	
		{
			break;
		}
		case 0x0501://�����֤	//������֤
		{
			break;
		}
		case 0x0502://�����֤//�����֤
		{
			break;
		}
		case 0x0503://�����֤//��ԿЭ��
		{
			break;
		}
		case 0x0504://�����֤//��Կ����
		{
			break;
		}
		case 0x0601://��Ϣ����	//������Ϣ����
		{
			Information_Change_Flg = 1;
			senddata( rx_buff,0,0);
			Print ( "0x%04X�������%u\n",CMD,Count++ );
			Print ( "������Ϣ����\n" );
			break;
		}
		case 0x0602://��Ϣ����//�ر���Ϣ����
		{
			Information_Change_Flg = 0;
			senddata( rx_buff,0,0);
			Print ("0x%04X�������%u\n",CMD,Count++);
			Print ("�ر���Ϣ����\n");
			break;
		}
		case 0x0603://��Ϣ����//��ӡ��Ϣ
		{
			if(Information_Change_Flg)
			{
				Print ("��ӡ��ϢΪ\n");
				Print ("\n");
				Print ("��ӡ���\n");
			}
			else
			{
				Print ("δ������Ϣ����\n");
			}
			senddata( rx_buff,0,0);
			Print ("0x%04X�������%u\n",CMD,Count++);
			break;
		}
		case 0x0604://��Ϣ����//��Ϣѡ��
		{
			break;
		}
		case 0x0605://��Ϣ����//����Զ�̼��
		{
			break;
		}
		case 0x0606://��Ϣ����//���ƽ���
		{
			break;
		}
		case 0x0607://��Ϣ����//�������
		{
			break;
		}
		case 0x0608://��Ϣ����//�����趨
		{
			break;
		}
		case 0x0609://��Ϣ����//��ť�¼���
		{
			break;
		}
		case 0x060a://��Ϣ����//����
		{
			break;
		}
		case 0x060b://��Ϣ����//�ر�Զ�̼��
		{
			break;
		}
		case 0x0701://��ȡ�����ļ�	//��ȡ����ģ������ļ�
		{
			break;
		}
		case 0x0702://��ȡ�����ļ�//��ȡ����ģ��˵���ļ�
		{
			break;
		}
		case 0x0801://��ȡ��������//��ȡ�¶�
		{
			Send_Ambient_Temperature();
            senddata( rx_buff,Ambient_Temperature_Tmp,2);	 
            Print ("0x%04X�������%u\n",CMD,Count++);		
			break;
		}
		case 0x0802://��ȡ��������//��ȡʪ��
		{
			Send_Ambient_Humidity();
            senddata( rx_buff,Ambient_Humidity_Tmp,2);	 
            Print ("0x%04X�������%u\n",CMD,Count++);		
			break;
		}
		case 0x0F01://��������//��������
		{
			break;
		}
		case 0x0F02://��������//�ļ�����
		{
			break;
		}
		case 0x0F03://��������//��ʼ����
		{
			break;
		}
		case 0x2001://����Ƶ//RFID������ѯ����
		{
			break;
		}
		case 0x2002://����Ƶ//RFID�����趨����
		{
			break;
		}
		case 0x2003://����Ƶ//ֹͣRFID����
		{
			break;
		}
		case 0x2004://����Ƶ//����ȫ��Ԫ֧��
		{
			break;
		}
		case 0x2005://����Ƶ//EPC�̴�
		{
			break;
		}
		case 0x2006://����Ƶ//EPCѡ���ǩ
		{
			break;
		}
		case 0x2007://����Ƶ//EPC���ѡ�����
		{
			break;
		}
		
		case 0x2008://����Ƶ//EPC����ǩ����
		{
			break;
		}
		case 0x2009://����Ƶ//EPCд��ǩ����
		{
			break;
		}
		case 0x200A://����Ƶ//EPC����ǩ
		{
			break;
		}		
		case 0x200B://����Ƶ//EPC����ǩ
		{
			break;
		}
		case 0x200C://����Ƶ//GB�̴�
		{
			break;
		}
		case 0x200D://����Ƶ//GBѡ���ǩ
		{
			break;
		}
		case 0x200E://����Ƶ//GB���ѡ�����
		{
			break;
		}
		case 0x200F://����Ƶ//GB����ǩ����
		{
			break;
		}
		case 0x2010://����Ƶ//GBд��ǩ����
		{
			break;
		}
		case 0x2011://����Ƶ//GB����ǩ
		{
			break;
		}
		case 0x2012://����Ƶ//GB����ǩ
		{
			break;
		}
		case 0x2101://�ز����//���ܱ������ز����
		{
			break;
		}
		case 0x2102://�ز����//�ɼ��������ز����
		{
			break;
		}
		case 0x2103://�ز����//�����������ز����
		{
			break;
		}
		case 0x2104://�ز����//���ܱ��ز�ģ����
		{
			break;
		}
		case 0x2105://�ز����//�ɼ����ز�ģ����
		{
			break;
		}
		case 0x2106://�ز����//�������ز�ģ����
		{
			break;
		}
		case 0x2107://�ز����//���ܱ��������
		{
			break;
		}
		case 0x2108://�ز����//�ɼ����������
		{
			break;
		}
		case 0x2109://�ز����//�������������
		{
			break;
		}
		case 0x210A://�ز����//��·���
		{
			break;
		}
		case 0x210B://�ز����//�·��ӽڵ�̶��м�·��
		{
			break;
		}
		case 0x210C://�ز����//��ȡ�ӽڵ��м�·��
		{
			break;
		}
		case 0x2201://SIM�����//��ȡSIM����Ϣ
		{
			break;
		}
		case 0x2202://SIM�����//�·�SIM������
		{
			break;
		}
		case 0x2203://SIM�����//��ȡSIM�����
		{
			break;
		}
		case 0x2204://SIM�����//����GPRSģ��
		{
			break;
		}
		case 0x2205://SIM�����//�ر�GPRSģ��
		{
			break;
		}
		case 0x2301://�ֳ�У��//��ȡ���ܱ��������
		{
			break;
		}
		case 0x2302://�ֳ�У��//��ȡ���ܱ�г������
		{
			break;
		}
		case 0x2303://�ֳ�У��//��ȡ���ܱ���ߴ�������
		{
			break;
		}
		case 0x2401://΢��������//���ܱ�����΢�������߼��
		{
			break;
		}
		case 0x2402://΢��������//�ɼ�������΢�������߼��
		{
			break;
		}
		case 0x2403://΢��������//����������΢�������߼��
		{
			break;
		}
		case 0x2404://΢��������//���ܱ�΢��������ģ����
		{
			break;
		}
		case 0x2405://΢��������//�ɼ���΢��������ģ����
		{
			break;
		}
		case 0x2406://΢��������//������΢��������ģ����
		{
			break;
		}
		case 0x2407://΢��������//���ܱ��������
		{
			break;
		}
		case 0x2408://΢��������//�ɼ����������
		{
			break;
		}
		case 0x2409://΢��������//�������������
		{
			break;
		}
		case 0x240A://΢��������//��·���
		{
			break;
		}
		case 0x2501://�������̨��ʶ��//�������
		{
			break;
		}
		case 0x2502://�������̨��ʶ��//̨�����
		{
			break;
		}
		case 0x2503://�������̨��ʶ��//��ȡ̨��ʶ����
		{
			break;
		}
		case 0x2504://�������̨��ʶ��//���÷�֧���
		{
			break;
		}
		case 0x2601://��ǿ���
		{
			Send_Field_Strength(); 
			senddata( rx_buff,Field_Strength_Tmp,9);	 
            Print ("0x%04X�������%u\n",CMD,Count++);
			break;
		}
		case 0x2701://���翨
		{
			break;
		}
		case 0x2801://RS485//RS485������ѯ
		{
			break;
		}
		case 0x2802://RS485//RS485��������
		{
			break;
		}
		case 0x2901://RS232//RS232������ѯ
		{
			break;
		}
		case 0x2902://RS232//RS232��������
		{
			break;
		}
		case 0x2B01://�˳���������
		{
			break;
		}
		case 0x5001://����������
		{
			break;
		}
		case 0x5101://��ȡ������
		{
			break;
		}
		case 0x5201://���ܱ�ͨ�ù���
		{
			break;
		}
		default:
		{
			break;
		}
	}		
}






