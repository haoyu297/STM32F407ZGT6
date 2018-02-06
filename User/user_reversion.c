#include "include.h" 

/* 设备信息 *//* 0x0101  */
uint8_t  Equipment_Information_Tmp[139];
Equipment_Information* Equipment_Information_Temp = (Equipment_Information*)Equipment_Information_Tmp;

/* 设备状态 *//* 0x0102 */
uint8_t  Equipment_Status_Tmp[7];
Equipment_Status* Equipment_Status_Temp = (Equipment_Status*)Equipment_Status_Tmp;

/* 故障检测 *//* 0x0103 */
uint8_t  Fault_Finding_Tmp[2];
Fault_Finding* Fault_Finding_Temp = (Fault_Finding*)Fault_Finding_Tmp;

/* 环境温度 *//* 0x0801 */
uint8_t  Ambient_Temperature_Tmp[2];
Ambient_Temperature* Ambient_Temperature_Temp = (Ambient_Temperature*)Ambient_Temperature_Tmp;

/* 环境湿度 *//* 0x0802 */
uint8_t  Ambient_Humidity_Tmp[2];
Ambient_Humidity* Ambient_Humidity_Temp = (Ambient_Humidity*)Ambient_Humidity_Tmp; 

/* 场强检测 *//* 0x2601 */
uint8_t  Field_Strength_Tmp[9]; 
Field_Strength* Field_Strength_Temp = (Field_Strength*)Field_Strength_Tmp; 

u16 PA5_Adc_Data;//电池电量ad值
u16 Power_Now;//电池电量

/* 设备信息 *//* 0x0101 */
void Send_Equipment_Information(void)
{
  
    Equipment_Information_Temp->Equipment_Model[0]  = 0x31; /* 设备型号 *//* 57 47 59 57 30 31 2D   */
    Equipment_Information_Temp->Equipment_Model[1]  = 0x31;//HGCJ40-11111
    Equipment_Information_Temp->Equipment_Model[2]  = 0x31;
    Equipment_Information_Temp->Equipment_Model[3]  = 0x31;
    Equipment_Information_Temp->Equipment_Model[4]  = 0x31;
    Equipment_Information_Temp->Equipment_Model[5]  = 0x2D;
    Equipment_Information_Temp->Equipment_Model[6]  = 0x30;
    Equipment_Information_Temp->Equipment_Model[7]  = 0x34;
    Equipment_Information_Temp->Equipment_Model[8]  = 'J';
    Equipment_Information_Temp->Equipment_Model[9]  = 'C';
    Equipment_Information_Temp->Equipment_Model[10] = 'G';
    Equipment_Information_Temp->Equipment_Model[11] = 'H';

    Equipment_Information_Temp->Equipment_ID[0] = 0x11;/* 设备ID号 *//* 11 11 11 11 11 10 */          
    Equipment_Information_Temp->Equipment_ID[1] = 0x11;
    Equipment_Information_Temp->Equipment_ID[2] = 0x11;
    Equipment_Information_Temp->Equipment_ID[3] = 0x11;
    Equipment_Information_Temp->Equipment_ID[4] = 0x11;
    Equipment_Information_Temp->Equipment_ID[5] = 0x11;	

    Equipment_Information_Temp->Hardware_number[0]=0x02;/* 硬件版本号 *//* 01.01 */       
    Equipment_Information_Temp->Hardware_number[1]=0x00;

    Equipment_Information_Temp->Hardware_Date[0] = 0x01;/* 硬件版本日期 *//* 18 02 01 */
    Equipment_Information_Temp->Hardware_Date[1] = 0x02;
    Equipment_Information_Temp->Hardware_Date[2] = 0x18;

    Equipment_Information_Temp->Software_Number[0]=0x01;/* 软件版本号 *//* 01 00 00 01 */
    Equipment_Information_Temp->Software_Number[1]=0x00;
    Equipment_Information_Temp->Software_Number[2]=0x00;
    Equipment_Information_Temp->Software_Number[3]=0x01;

    Equipment_Information_Temp->Software_Date[0] = 0x01;/* 软件版本日期 *//* 18 02 01 */
    Equipment_Information_Temp->Software_Date[1] = 0x02;
    Equipment_Information_Temp->Software_Date[2] = 0x18;

    Equipment_Information_Temp->Battery_Capacity[0] = 0x00;/* 电池容量 *//* 0mAH */
    Equipment_Information_Temp->Battery_Capacity[1] = 0x30;
    Equipment_Information_Temp->Battery_Capacity[2] = 0;
    Equipment_Information_Temp->Battery_Capacity[3] = 0;

    Equipment_Information_Temp->Functional_Config[0] = 0x02;/* 功能配置 */  /* FF FF 00 00 */
    Equipment_Information_Temp->Functional_Config[1] = 0x06;
    Equipment_Information_Temp->Functional_Config[2] = 0x00;
    Equipment_Information_Temp->Functional_Config[3] = 0x00;

    Equipment_Information_Temp->Response_Time[0] = 0x01;/* 外设模块响应主设备时间 *//* 002.3 */
    Equipment_Information_Temp->Response_Time[1] = 0x00;

    Equipment_Information_Temp->ESAM_Number[0] = 0x00;/* ESAM版本号 */ /* 00 00 00 00 01*/
    Equipment_Information_Temp->ESAM_Number[1] = 0x00;
    Equipment_Information_Temp->ESAM_Number[2] = 0x00;
    Equipment_Information_Temp->ESAM_Number[3] = 0x00;
    Equipment_Information_Temp->ESAM_Number[4] = 0x00;

    Equipment_Information_Temp->ESAM_sNumber[0] = 0x01;/* ESAM序列号 */
    Equipment_Information_Temp->ESAM_sNumber[1] = 0x01;
    Equipment_Information_Temp->ESAM_sNumber[2] = 0x01;
    Equipment_Information_Temp->ESAM_sNumber[3] = 0x00;
    Equipment_Information_Temp->ESAM_sNumber[4] = 0x00;
    Equipment_Information_Temp->ESAM_sNumber[5] = 0x00;
    Equipment_Information_Temp->ESAM_sNumber[6] = 0x00;
    Equipment_Information_Temp->ESAM_sNumber[7] = 0x00;

    Equipment_Information_Temp->Symmetric_Key[0]  = 0x11;/* 对称密钥版本 */
    Equipment_Information_Temp->Symmetric_Key[1]  = 0x11;
    Equipment_Information_Temp->Symmetric_Key[2]  = 0x11;
    Equipment_Information_Temp->Symmetric_Key[3]  = 0x11;
    Equipment_Information_Temp->Symmetric_Key[4]  = 0x11;
    Equipment_Information_Temp->Symmetric_Key[5]  = 0x11;
    Equipment_Information_Temp->Symmetric_Key[6]  = 0x11;
    Equipment_Information_Temp->Symmetric_Key[7]  = 0x11;
    Equipment_Information_Temp->Symmetric_Key[8]  = 0x11;
    Equipment_Information_Temp->Symmetric_Key[9]  = 0x11;
    Equipment_Information_Temp->Symmetric_Key[10] = 0x11;
    Equipment_Information_Temp->Symmetric_Key[11] = 0x11;
    Equipment_Information_Temp->Symmetric_Key[12] = 0x11;
    Equipment_Information_Temp->Symmetric_Key[13] = 0x11;
    Equipment_Information_Temp->Symmetric_Key[14] = 0x11;
    Equipment_Information_Temp->Symmetric_Key[15] = 0x11;
     
    Equipment_Information_Temp->Conversational_Threshold[0] = 0x05;/* 会话时效门限 */
    Equipment_Information_Temp->Conversational_Threshold[1] = 0x00;
    Equipment_Information_Temp->Conversational_Threshold[2] = 0x00;
    Equipment_Information_Temp->Conversational_Threshold[3] = 0x00;

    Equipment_Information_Temp->Residual_Time[0] = 0x12;/* 会话时效剩余时间 */ 
    Equipment_Information_Temp->Residual_Time[1] = 0x00;
    Equipment_Information_Temp->Residual_Time[2] = 0x00;
    Equipment_Information_Temp->Residual_Time[3] = 0x00;

    Equipment_Information_Temp->ASCTR_Count[0] = 0x01;/* ASCTR单地址应用协商计数器 */ 
    Equipment_Information_Temp->ASCTR_Count[1] = 0x00;
    Equipment_Information_Temp->ASCTR_Count[2] = 0x00;
    Equipment_Information_Temp->ASCTR_Count[3] = 0x00;

    Equipment_Information_Temp->AMRCTR_Count[0] = 0x01;/* AMRCTR外设主动上报计数器 */
    Equipment_Information_Temp->AMRCTR_Count[1] = 0x00;
    Equipment_Information_Temp->AMRCTR_Count[2] = 0x00;
    Equipment_Information_Temp->AMRCTR_Count[3] = 0x00;

    Equipment_Information_Temp->AGSEQ_Number[0] = 0x01;/* AGSEQ应用广播通信序列号 */
    Equipment_Information_Temp->AGSEQ_Number[1] = 0x00;
    Equipment_Information_Temp->AGSEQ_Number[2] = 0x00;
    Equipment_Information_Temp->AGSEQ_Number[3] = 0x00;

    Equipment_Information_Temp->ESAM_Information[0]  = 0xFF;/* ESAM发行信息 */ 
    Equipment_Information_Temp->ESAM_Information[1]  = 0xFF;
    Equipment_Information_Temp->ESAM_Information[2]  = 0xFF;
    Equipment_Information_Temp->ESAM_Information[3]  = 0xFF;
    Equipment_Information_Temp->ESAM_Information[4]  = 0xFF;
    Equipment_Information_Temp->ESAM_Information[5]  = 0xFF;
    Equipment_Information_Temp->ESAM_Information[6]  = 0xFF;
    Equipment_Information_Temp->ESAM_Information[7]  = 0xFF;
    Equipment_Information_Temp->ESAM_Information[8]  = 0xFF;
    Equipment_Information_Temp->ESAM_Information[9]  = 0xFF;
    Equipment_Information_Temp->ESAM_Information[10] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[11] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[12] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[13] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[14] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[15] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[16] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[17] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[18] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[19] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[20] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[21] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[22] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[23] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[24] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[25] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[26] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[27] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[28] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[29] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[30] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[31] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[32] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[33] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[34] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[35] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[36] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[37] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[38] = 0xFF;
    Equipment_Information_Temp->ESAM_Information[39] = 0xFF;

    Equipment_Information_Temp->Peripheral_Type = 0x02;/* 外设类型 */

    Equipment_Information_Temp->Security_Date[0] = 0x12;/* 安全参数版本日期 */
    Equipment_Information_Temp->Security_Date[1] = 0x01;
    Equipment_Information_Temp->Security_Date[2] = 0x18;

    Equipment_Information_Temp->Security_Number = 0x01;/* 安全参数版本号 */

    Equipment_Information_Temp->Safety_Rating = 0x01;/* 安全等级 */

    Equipment_Information_Temp->Keep[0] = 0x00;/* 预留 */
    Equipment_Information_Temp->Keep[1] = 0x00;
    Equipment_Information_Temp->Keep[2] = 0x00;
    Equipment_Information_Temp->Keep[3] = 0x00;
}

/* 设备状态 *//* 0x0102 */
u16 AD_Data[1][13];
void Send_Equipment_Status(void)
{
	u8 power_percent;
	u8 i;
	for(i=0;i<10;i++)
	{
		AD_Data[0][i] = Get_Adc(ADC_Channel_5);
	}
	Get_ValueAVG(1,10); 
	Print ("AD采集为%u  ADC采集完成\n",PA5_Adc_Data); 
	Power_Now = (u16)((PA5_Adc_Data*1.0/1024)*POWER_STANDARD*2); 
	Print ("电压为%u.%uV  \n",Power_Now/100,Power_Now%100); 
	 
	power_percent = (Power_Now-POWER_MIN)*100/(POWER_MAX-POWER_MIN); 
	power_percent = (((power_percent/10)<<4) + (power_percent%10)); 
	Print ("电量百分比为0x%2X \n",power_percent); 
	
	Equipment_Status_Temp->Battery_Charge[0] = ((Power_Now%100/10)<<4)+(Power_Now%100%10);
	Equipment_Status_Temp->Battery_Charge[1] = Power_Now/100;
	Equipment_Status_Temp->Percentage_Electricity = power_percent;
	Equipment_Status_Temp->Keep[0] = 0x00;
	Equipment_Status_Temp->Keep[1] = 0x00;
	Equipment_Status_Temp->Keep[2] = 0x00;
	Equipment_Status_Temp->Keep[3] = 0x00;
}

/* 故障检测 *//* 0x0103 */
void Send_Fault_Finding(void)
{
	Fault_Finding_Temp->Equipment_fault[0] = 0x00;
	Fault_Finding_Temp->Equipment_fault[1] = 0x00;
}

/* 环境温度 *//* 0x0801 */
extern u8 suiji;
void Send_Ambient_Temperature(void)
{
	Ambient_Temperature_Temp->Temp[0] = 0x30 | suiji;//0x00;
	Ambient_Temperature_Temp->Temp[1] = 0x01;
}

/* 环境湿度 *//* 0x0802 */
void Send_Ambient_Humidity(void)
{
	Ambient_Humidity_Temp->Humi[0] = suiji;//0x00;
	Ambient_Humidity_Temp->Humi[1] = 0x42;
}
/* 场强检测 *//* 0x2601 */
void Send_Field_Strength(void)
{
	Field_Strength_Temp->Constant_Field[0] = 0x00;
	Field_Strength_Temp->Constant_Field[1] = 0x00;
	Field_Strength_Temp->Constant_Field[2] = 0x00;
	
	Field_Strength_Temp->Frequency_Field[0] = 0x00;
	Field_Strength_Temp->Frequency_Field[1] = 0x00;
	Field_Strength_Temp->Frequency_Field[2] = 0x00;
	
	Field_Strength_Temp->High_Frequency_Field[0] = 0x00;
	Field_Strength_Temp->High_Frequency_Field[1] = 0x00;
	Field_Strength_Temp->High_Frequency_Field[2] = 0x00;
}

void Get_ValueAVG(unsigned char N,unsigned char M)  
{
    unsigned int max,min;
    unsigned int i=0,j;
    u32 k;
    for(j=0;j<N;j++)
    {        
        max=AD_Data[j][0];
        for(i=1;i<M;i++)
        {
            if(AD_Data[j][i]>max)
                max=AD_Data[j][i];
        }
        AD_Data[j][M+1]=max;

        min=AD_Data[j][0];
        for(i=1;i<M;i++)
        {
            if(AD_Data[j][i]<min)
                min=AD_Data[j][i];
        }
        AD_Data[j][M+2]=min;
            
        k=0;
        for(i=0;i<M;i++)
        {
            k+=AD_Data[j][i];
        }

        AD_Data[j][M]=(k-max-min)/(M-2);
    }
    PA5_Adc_Data=AD_Data[0][M];
 }
