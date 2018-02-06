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
	
	/* 帧起始符 */
	Sendbuff1.send_start1=0x97;
	
	/* 设备类型 */
	Sendbuff1.send_type[0]=rx_buf->get_type[0];
	Sendbuff1.send_type[1]=rx_buf->get_type[1];
	Sendbuff1.send_type[2]=rx_buf->get_type[2];
	Sendbuff1.send_type[3]=rx_buf->get_type[3];
	
	/* 外设模块地址 */
	Sendbuff1.send_address[0]=rx_buff->get_address[0];
	Sendbuff1.send_address[1]=rx_buff->get_address[1];
	Sendbuff1.send_address[2]=rx_buff->get_address[2];
	Sendbuff1.send_address[3]=rx_buff->get_address[3];
	Sendbuff1.send_address[4]=rx_buff->get_address[4];
	Sendbuff1.send_address[5]=rx_buff->get_address[5];
	
	/* 帧起始符 */
	Sendbuff1.send_start2=0x97;
	
	/* 数据域长度 */
	Sendbuff1.send_datalen[0]=(int8_t)(Data_TxLen&0x00ff);
	Sendbuff1.send_datalen[1]=((Data_TxLen&0xff00)>>8);
	
	/* 帧序号 */
	Sendbuff1.send_SEQ=rx_buf->get_SEQ;
	
	/* 控制码 */
	Sendbuff1.send_C=0x80;
	
	/* 功能码 */
	Sendbuff1.send_Fn[0]=rx_buf->get_Fn[0];
	Sendbuff1.send_Fn[1]=rx_buf->get_Fn[1];
	
	/* 校验码 */
	//Sendbuff1.send_CS=0x97;
	
	/* 结束符 */
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
	Print ("发送数据域长度为%u位\n",length);
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
	Print ("功能码为0x%04x\n",CMD);
	switch(CMD)
	{
		case 0x0101://查询通用参数//设备信息
		{
			Send_Equipment_Information();
			senddata(rx_buff,Equipment_Information_Tmp,139);
			Print ("0x%04X发送完成%u\n",CMD,Count++);
			break;
		}
		case 0x0102://查询通用参数//设备状态
		{
			Send_Equipment_Status();
			senddata(rx_buff,Equipment_Status_Tmp,7);
			Print ("0x%04X发送完成%u\n",CMD,Count++);
			break;
		}
		case 0x0103://查询通用参数//故障检测
		{
			Send_Fault_Finding();
			senddata( rx_buff,Fault_Finding_Tmp,2);
			Print ("0x%04X发送完成%u\n",CMD,Count++);
			break;
		}
		case 0x0201://设置通用参数//外设模块地址
		{
			break;
		}
		case 0x0202://设置通用参数//安全配置参数
		{
			break;
		}
		case 0x0301://复位命令//硬件初始化
		{
			break;
		}
		case 0x0302://复位命令//参数区初始化
		{
			break;
		}
		case 0x0303://复位命令//参数及全体数据区初始化
		{
			break;
		}
		case 0x0401://数据透传	
		{
			break;
		}
		case 0x0501://身份认证	//发起认证
		{
			break;
		}
		case 0x0502://身份认证//身份认证
		{
			break;
		}
		case 0x0503://身份认证//密钥协商
		{
			break;
		}
		case 0x0504://身份认证//密钥更新
		{
			break;
		}
		case 0x0601://信息交互	//开启信息交互
		{
			Information_Change_Flg = 1;
			senddata( rx_buff,0,0);
			Print ( "0x%04X发送完成%u\n",CMD,Count++ );
			Print ( "开启信息交互\n" );
			break;
		}
		case 0x0602://信息交互//关闭信息交互
		{
			Information_Change_Flg = 0;
			senddata( rx_buff,0,0);
			Print ("0x%04X发送完成%u\n",CMD,Count++);
			Print ("关闭信息交互\n");
			break;
		}
		case 0x0603://信息交互//打印信息
		{
			if(Information_Change_Flg)
			{
				Print ("打印信息为\n");
				Print ("\n");
				Print ("打印完成\n");
			}
			else
			{
				Print ("未开启信息交互\n");
			}
			senddata( rx_buff,0,0);
			Print ("0x%04X发送完成%u\n",CMD,Count++);
			break;
		}
		case 0x0604://信息交互//信息选择
		{
			break;
		}
		case 0x0605://信息交互//开启远程监控
		{
			break;
		}
		case 0x0606://信息交互//绘制界面
		{
			break;
		}
		case 0x0607://信息交互//界面更新
		{
			break;
		}
		case 0x0608://信息交互//参数设定
		{
			break;
		}
		case 0x0609://信息交互//按钮事件绑定
		{
			break;
		}
		case 0x060a://信息交互//清屏
		{
			break;
		}
		case 0x060b://信息交互//关闭远程监控
		{
			break;
		}
		case 0x0701://获取帮助文件	//获取外设模块帮助文件
		{
			break;
		}
		case 0x0702://获取帮助文件//获取外设模块说明文件
		{
			break;
		}
		case 0x0801://获取环境参数//获取温度
		{
			Send_Ambient_Temperature();
            senddata( rx_buff,Ambient_Temperature_Tmp,2);	 
            Print ("0x%04X发送完成%u\n",CMD,Count++);		
			break;
		}
		case 0x0802://获取环境参数//获取湿度
		{
			Send_Ambient_Humidity();
            senddata( rx_buff,Ambient_Humidity_Tmp,2);	 
            Print ("0x%04X发送完成%u\n",CMD,Count++);		
			break;
		}
		case 0x0F01://在线升级//请求升级
		{
			break;
		}
		case 0x0F02://在线升级//文件传输
		{
			break;
		}
		case 0x0F03://在线升级//开始升级
		{
			break;
		}
		case 0x2001://超高频//RFID参数查询命令
		{
			break;
		}
		case 0x2002://超高频//RFID参数设定命令
		{
			break;
		}
		case 0x2003://超高频//停止RFID操作
		{
			break;
		}
		case 0x2004://超高频//请求安全单元支持
		{
			break;
		}
		case 0x2005://超高频//EPC盘存
		{
			break;
		}
		case 0x2006://超高频//EPC选择标签
		{
			break;
		}
		case 0x2007://超高频//EPC清空选择参数
		{
			break;
		}
		
		case 0x2008://超高频//EPC读标签数据
		{
			break;
		}
		case 0x2009://超高频//EPC写标签数据
		{
			break;
		}
		case 0x200A://超高频//EPC锁标签
		{
			break;
		}		
		case 0x200B://超高频//EPC灭活标签
		{
			break;
		}
		case 0x200C://超高频//GB盘存
		{
			break;
		}
		case 0x200D://超高频//GB选择标签
		{
			break;
		}
		case 0x200E://超高频//GB清空选择参数
		{
			break;
		}
		case 0x200F://超高频//GB读标签数据
		{
			break;
		}
		case 0x2010://超高频//GB写标签数据
		{
			break;
		}
		case 0x2011://超高频//GB锁标签
		{
			break;
		}
		case 0x2012://超高频//GB灭活标签
		{
			break;
		}
		case 0x2101://载波检测//电能表整机载波检测
		{
			break;
		}
		case 0x2102://载波检测//采集器整机载波检测
		{
			break;
		}
		case 0x2103://载波检测//集中器整机载波检测
		{
			break;
		}
		case 0x2104://载波检测//电能表载波模块检测
		{
			break;
		}
		case 0x2105://载波检测//采集器载波模块检测
		{
			break;
		}
		case 0x2106://载波检测//集中器载波模块检测
		{
			break;
		}
		case 0x2107://载波检测//电能表主机检测
		{
			break;
		}
		case 0x2108://载波检测//采集器主机检测
		{
			break;
		}
		case 0x2109://载波检测//集中器主机检测
		{
			break;
		}
		case 0x210A://载波检测//链路检测
		{
			break;
		}
		case 0x210B://载波检测//下发从节点固定中继路径
		{
			break;
		}
		case 0x210C://载波检测//获取从节点中继路径
		{
			break;
		}
		case 0x2201://SIM卡检测//获取SIM卡信息
		{
			break;
		}
		case 0x2202://SIM卡检测//下发SIM检测参数
		{
			break;
		}
		case 0x2203://SIM卡检测//获取SIM检测结果
		{
			break;
		}
		case 0x2204://SIM卡检测//启动GPRS模块
		{
			break;
		}
		case 0x2205://SIM卡检测//关闭GPRS模块
		{
			break;
		}
		case 0x2301://现场校验//获取电能表误差数据
		{
			break;
		}
		case 0x2302://现场校验//获取电能表谐波数据
		{
			break;
		}
		case 0x2303://现场校验//获取电能表接线错误数据
		{
			break;
		}
		case 0x2401://微功率无线//电能表整机微功率无线检测
		{
			break;
		}
		case 0x2402://微功率无线//采集器整机微功率无线检测
		{
			break;
		}
		case 0x2403://微功率无线//集中器整机微功率无线检测
		{
			break;
		}
		case 0x2404://微功率无线//电能表微功率无线模块检测
		{
			break;
		}
		case 0x2405://微功率无线//采集器微功率无线模块检测
		{
			break;
		}
		case 0x2406://微功率无线//集中器微功率无线模块检测
		{
			break;
		}
		case 0x2407://微功率无线//电能表主机检测
		{
			break;
		}
		case 0x2408://微功率无线//采集器主机检测
		{
			break;
		}
		case 0x2409://微功率无线//集中器主机检测
		{
			break;
		}
		case 0x240A://微功率无线//链路检测
		{
			break;
		}
		case 0x2501://串户检测台区识别//串户检测
		{
			break;
		}
		case 0x2502://串户检测台区识别//台区检测
		{
			break;
		}
		case 0x2503://串户检测台区识别//获取台区识别结果
		{
			break;
		}
		case 0x2504://串户检测台区识别//设置分支编号
		{
			break;
		}
		case 0x2601://场强检测
		{
			Send_Field_Strength(); 
			senddata( rx_buff,Field_Strength_Tmp,9);	 
            Print ("0x%04X发送完成%u\n",CMD,Count++);
			break;
		}
		case 0x2701://购电卡
		{
			break;
		}
		case 0x2801://RS485//RS485参数查询
		{
			break;
		}
		case 0x2802://RS485//RS485参数设置
		{
			break;
		}
		case 0x2901://RS232//RS232参数查询
		{
			break;
		}
		case 0x2902://RS232//RS232参数设置
		{
			break;
		}
		case 0x2B01://退出任务命令
		{
			break;
		}
		case 0x5001://设置误差参数
		{
			break;
		}
		case 0x5101://获取误差参数
		{
			break;
		}
		case 0x5201://电能表通用故障
		{
			break;
		}
		default:
		{
			break;
		}
	}		
}






