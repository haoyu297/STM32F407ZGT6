#ifndef __USER_REVERSION_H
#define __USER_REVERSION_H	

typedef unsigned	int          uint32_t;
typedef unsigned short     int uint16_t;
typedef unsigned short     int u16;
typedef unsigned	char         uint8_t;


/* 查询通用参数 *//* 设备信息 *//* 0x0101 */
typedef struct
{
	uint8_t Equipment_Model[12];          /* 设备型号 *///device
	uint8_t Equipment_ID[6];              /* 设备ID号 */
	uint8_t Hardware_number[2];           /* 硬件版本号 */
	uint8_t Hardware_Date[3];             /* 硬件版本日期 */
	uint8_t Software_Number[4];           /* 软件版本号 */
	uint8_t Software_Date[3];             /* 软件版本日期 */    
	uint8_t Battery_Capacity[4];          /* 电池容量 */
	uint8_t Functional_Config[4];         /* 功能配置 */   
	uint8_t Response_Time[2];             /* 外设模块响应主设备时间 */
	uint8_t ESAM_Number[5];               /* ESAM版本号 */ 
	uint8_t ESAM_sNumber[8];              /* ESAM序列号 */
	uint8_t Symmetric_Key[16];            /* 对称密钥版本 */
	uint8_t Conversational_Threshold[4];  /* 会话时效门限 */ 
	uint8_t Residual_Time[4];             /* 会话时效剩余时间 */ 
	uint8_t ASCTR_Count[4];               /* ASCTR单地址应用协商计数器 */ 
	uint8_t AMRCTR_Count[4];              /* AMRCTR外设主动上报计数器 */
	uint8_t AGSEQ_Number[4];              /* AGSEQ应用广播通信序列号 */
	uint8_t ESAM_Information[40];         /* ESAM发行信息 */ 
	uint8_t Peripheral_Type;              /* 外设类型 */
	uint8_t Security_Date[3];             /* 安全参数版本日期 */
	uint8_t Security_Number;              /* 安全参数版本号 */
  uint8_t Safety_Rating;                /* 安全等级 */
	uint8_t Keep[4];                      /* 预留 */
}Equipment_Information;	

/* 查询通用参数 *//* 设备状态 *//* 0x0102 */
typedef struct
{
	uint8_t Battery_Charge[2];            /* 电池电量 */
	uint8_t Percentage_Electricity;       /* 电量百分比 */
	uint8_t Keep[4];                      /* 预留 */
}Equipment_Status;

/* 查询通用参数 *//* 故障检测 *//* 0x0103 */
typedef struct
{
	uint8_t Equipment_fault[2];           /* 设备故障码 */
}Fault_Finding;

/* 获取环境参数 *//* 获取温度 *//* 0x0801 */
typedef struct
{
	uint8_t Temp[2];                      /* 温度 */
}Ambient_Temperature;

/* 获取环境参数 *//* 获取湿度 *//* 0x0802 */
typedef struct
{
	uint8_t Humi[2];                      /* 湿度 */
}Ambient_Humidity;

/* 场强检测 *//* 场强检测 *//* 0x2601 */
typedef struct
{
	uint8_t Constant_Field[3];            /* 恒定场强 */
	uint8_t Frequency_Field[3];           /* 工频场强 */
	uint8_t High_Frequency_Field[3];      /* 高频磁场强度 */
}Field_Strength;


#define POWER_MAX        602						/* 电池最高电压 */
#define POWER_MIN        482            /* 电池最低电压 */
#define POWER_STANDARD   329            /* 采集基准电压 */

extern uint8_t  Equipment_Information_Tmp[139];
extern uint8_t  Equipment_Status_Tmp[7];
extern uint8_t  Fault_Finding_Tmp[2];
extern uint8_t  Ambient_Temperature_Tmp[2];
extern uint8_t  Ambient_Humidity_Tmp[2];
extern uint8_t  Field_Strength_Tmp[9];

void Send_Equipment_Information(void);
void Send_Equipment_Status(void);
void Send_Fault_Finding(void);
void Send_Ambient_Temperature(void);
void Send_Ambient_Humidity(void);
void Send_Field_Strength(void);

void Get_ValueAVG(unsigned char N,unsigned char M);

#endif 


