#ifndef __USER_REVERSION_H
#define __USER_REVERSION_H	

typedef unsigned	int          uint32_t;
typedef unsigned short     int uint16_t;
typedef unsigned short     int u16;
typedef unsigned	char         uint8_t;


/* ��ѯͨ�ò��� *//* �豸��Ϣ *//* 0x0101 */
typedef struct
{
	uint8_t Equipment_Model[12];          /* �豸�ͺ� *///device
	uint8_t Equipment_ID[6];              /* �豸ID�� */
	uint8_t Hardware_number[2];           /* Ӳ���汾�� */
	uint8_t Hardware_Date[3];             /* Ӳ���汾���� */
	uint8_t Software_Number[4];           /* ����汾�� */
	uint8_t Software_Date[3];             /* ����汾���� */    
	uint8_t Battery_Capacity[4];          /* ������� */
	uint8_t Functional_Config[4];         /* �������� */   
	uint8_t Response_Time[2];             /* ����ģ����Ӧ���豸ʱ�� */
	uint8_t ESAM_Number[5];               /* ESAM�汾�� */ 
	uint8_t ESAM_sNumber[8];              /* ESAM���к� */
	uint8_t Symmetric_Key[16];            /* �Գ���Կ�汾 */
	uint8_t Conversational_Threshold[4];  /* �ỰʱЧ���� */ 
	uint8_t Residual_Time[4];             /* �ỰʱЧʣ��ʱ�� */ 
	uint8_t ASCTR_Count[4];               /* ASCTR����ַӦ��Э�̼����� */ 
	uint8_t AMRCTR_Count[4];              /* AMRCTR���������ϱ������� */
	uint8_t AGSEQ_Number[4];              /* AGSEQӦ�ù㲥ͨ�����к� */
	uint8_t ESAM_Information[40];         /* ESAM������Ϣ */ 
	uint8_t Peripheral_Type;              /* �������� */
	uint8_t Security_Date[3];             /* ��ȫ�����汾���� */
	uint8_t Security_Number;              /* ��ȫ�����汾�� */
  uint8_t Safety_Rating;                /* ��ȫ�ȼ� */
	uint8_t Keep[4];                      /* Ԥ�� */
}Equipment_Information;	

/* ��ѯͨ�ò��� *//* �豸״̬ *//* 0x0102 */
typedef struct
{
	uint8_t Battery_Charge[2];            /* ��ص��� */
	uint8_t Percentage_Electricity;       /* �����ٷֱ� */
	uint8_t Keep[4];                      /* Ԥ�� */
}Equipment_Status;

/* ��ѯͨ�ò��� *//* ���ϼ�� *//* 0x0103 */
typedef struct
{
	uint8_t Equipment_fault[2];           /* �豸������ */
}Fault_Finding;

/* ��ȡ�������� *//* ��ȡ�¶� *//* 0x0801 */
typedef struct
{
	uint8_t Temp[2];                      /* �¶� */
}Ambient_Temperature;

/* ��ȡ�������� *//* ��ȡʪ�� *//* 0x0802 */
typedef struct
{
	uint8_t Humi[2];                      /* ʪ�� */
}Ambient_Humidity;

/* ��ǿ��� *//* ��ǿ��� *//* 0x2601 */
typedef struct
{
	uint8_t Constant_Field[3];            /* �㶨��ǿ */
	uint8_t Frequency_Field[3];           /* ��Ƶ��ǿ */
	uint8_t High_Frequency_Field[3];      /* ��Ƶ�ų�ǿ�� */
}Field_Strength;


#define POWER_MAX        602						/* �����ߵ�ѹ */
#define POWER_MIN        482            /* �����͵�ѹ */
#define POWER_STANDARD   329            /* �ɼ���׼��ѹ */

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


