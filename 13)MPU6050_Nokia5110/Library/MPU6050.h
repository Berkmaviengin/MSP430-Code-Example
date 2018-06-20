/////////////////////////////////////////////////////////////////////////////
// ChUONG TRINH CHINH
// VIET BOI : PHAM VAN THUAN	DTVT07-K55
// Email:	terran991992@gmail.com
// Blog :	http://thuanbk55.blogspot.com/
// .................................................................
// AP DUNG CHO MACH UNG DUNG MSP430
//******************************************************************/

#ifdef USE_MPU6050

long GYRO_XFilter[4],GYRO_YFilter[4],GYRO_ZFilter[4];
long ACCEL_XFilter[4],ACCEL_YFilter[4],ACCEL_ZFilter[4];
long G_Filter[4];

//Gia tri sai so tinh cua cam bien
unsigned int	TEMP_OUT = 0;
int				GYRO_XOUT = 0,
				GYRO_YOUT = 0,
				GYRO_ZOUT = 0,
				GYRO_XOUT_OFFSET = 250,//-237,//104,
				GYRO_YOUT_OFFSET = -170,//-9,
				GYRO_ZOUT_OFFSET = 8,//-197,
				GYRO_XRATE = 0,
				GYRO_YRATE = 0,
				GYRO_ZRATE = 0,
				GYRO_XANGLE = 0,
				GYRO_YANGLE = 0,
				GYRO_ZANGLE = 0,
				gyro_ratio = 4;

char	dt=1;	//Dao ham cua thoi gian => Chu ky lay mau
int				ACCEL_XOUT = 0,
				ACCEL_YOUT = 0,
				ACCEL_ZOUT = 0,
				ACCEL_XOUT_PAST=0,			//
				ACCEL_YOUT_PAST=0,
				ACCEL_ZOUT_PAST=0,
				ACCEL_XA    =0,
				ACCEL_YA    =0,
				ACCEL_ZA    =0,
				ACCEL_XV    = 0,
				ACCEL_YV    = 0,
				ACCEL_ZV    = 0,
				ACCEL_XDECAC=0,
				ACCEL_YDECAC=0,
				ACCEL_ZDECAC=0;

float			ACCEL_XANGLE =0,
				ACCEL_YANGLE =0,
				ACCEL_ZANGLE =0;


long	Decac_X0=0,
				Decac_X1=0,
				Decac_Y0=0,
				Decac_Y1=0,
				Decac_Z0=0,
				Decac_Z1=0;

/******************************************************************************\
*					Dia chi MPU6050                           *
\******************************************************************************/

#define MPU6050_ADDRESS 0x68 // Address MPU6050	0b01101000		0b10100100

#define MPU6050_RA_XG_OFFS_TC 0x00 //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_YG_OFFS_TC 0x01 //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_ZG_OFFS_TC 0x02 //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_X_FINE_GAIN 0x03 //[7:0] X_FINE_GAIN
#define MPU6050_RA_Y_FINE_GAIN 0x04 //[7:0] Y_FINE_GAIN
#define MPU6050_RA_Z_FINE_GAIN 0x05 //[7:0] Z_FINE_GAIN
#define MPU6050_RA_XA_OFFS_H 0x06 //[15:0] XA_OFFS
#define MPU6050_RA_XA_OFFS_L_TC 0x07
#define MPU6050_RA_YA_OFFS_H 0x08 //[15:0] YA_OFFS
#define MPU6050_RA_YA_OFFS_L_TC 0x09
#define MPU6050_RA_ZA_OFFS_H 0x0A //[15:0] ZA_OFFS
#define MPU6050_RA_ZA_OFFS_L_TC 0x0B
#define MPU6050_RA_XG_OFFS_USRH 0x13 //[15:0] XG_OFFS_USR
#define MPU6050_RA_XG_OFFS_USRL 0x14
#define MPU6050_RA_YG_OFFS_USRH 0x15 //[15:0] YG_OFFS_USR
#define MPU6050_RA_YG_OFFS_USRL 0x16
#define MPU6050_RA_ZG_OFFS_USRH 0x17 //[15:0] ZG_OFFS_USR
#define MPU6050_RA_ZG_OFFS_USRL 0x18
#define MPU6050_RA_SMPLRT_DIV 0x19
#define MPU6050_RA_CONFIG 0x1A
#define MPU6050_RA_GYRO_CONFIG 0x1B
#define MPU6050_RA_ACCEL_CONFIG 0x1C
#define MPU6050_RA_FF_THR 0x1D
#define MPU6050_RA_FF_DUR 0x1E
#define MPU6050_RA_MOT_THR 0x1F
#define MPU6050_RA_MOT_DUR 0x20
#define MPU6050_RA_ZRMOT_THR 0x21
#define MPU6050_RA_ZRMOT_DUR 0x22
#define MPU6050_RA_FIFO_EN 0x23
#define MPU6050_RA_I2C_MST_CTRL 0x24
#define MPU6050_RA_I2C_SLV0_ADDR 0x25
#define MPU6050_RA_I2C_SLV0_REG 0x26
#define MPU6050_RA_I2C_SLV0_CTRL 0x27
#define MPU6050_RA_I2C_SLV1_ADDR 0x28
#define MPU6050_RA_I2C_SLV1_REG 0x29
#define MPU6050_RA_I2C_SLV1_CTRL 0x2A
#define MPU6050_RA_I2C_SLV2_ADDR 0x2B
#define MPU6050_RA_I2C_SLV2_REG 0x2C
#define MPU6050_RA_I2C_SLV2_CTRL 0x2D
#define MPU6050_RA_I2C_SLV3_ADDR 0x2E
#define MPU6050_RA_I2C_SLV3_REG 0x2F
#define MPU6050_RA_I2C_SLV3_CTRL 0x30
#define MPU6050_RA_I2C_SLV4_ADDR 0x31
#define MPU6050_RA_I2C_SLV4_REG 0x32
#define MPU6050_RA_I2C_SLV4_DO 0x33
#define MPU6050_RA_I2C_SLV4_CTRL 0x34
#define MPU6050_RA_I2C_SLV4_DI 0x35
#define MPU6050_RA_I2C_MST_STATUS 0x36
#define MPU6050_RA_INT_PIN_CFG 0x37
#define MPU6050_RA_INT_ENABLE 0x38
#define MPU6050_RA_DMP_INT_STATUS 0x39
#define MPU6050_RA_INT_STATUS 0x3A
#define MPU6050_RA_ACCEL_XOUT_H 0x3B
#define MPU6050_RA_ACCEL_XOUT_L 0x3C
#define MPU6050_RA_ACCEL_YOUT_H 0x3D
#define MPU6050_RA_ACCEL_YOUT_L 0x3E
#define MPU6050_RA_ACCEL_ZOUT_H 0x3F
#define MPU6050_RA_ACCEL_ZOUT_L 0x40
#define MPU6050_RA_TEMP_OUT_H 0x41
#define MPU6050_RA_TEMP_OUT_L 0x42
#define MPU6050_RA_GYRO_XOUT_H 0x43
#define MPU6050_RA_GYRO_XOUT_L 0x44
#define MPU6050_RA_GYRO_YOUT_H 0x45
#define MPU6050_RA_GYRO_YOUT_L 0x46
#define MPU6050_RA_GYRO_ZOUT_H 0x47
#define MPU6050_RA_GYRO_ZOUT_L 0x48
#define MPU6050_RA_EXT_SENS_DATA_00 0x49
#define MPU6050_RA_EXT_SENS_DATA_01 0x4A
#define MPU6050_RA_EXT_SENS_DATA_02 0x4B
#define MPU6050_RA_EXT_SENS_DATA_03 0x4C
#define MPU6050_RA_EXT_SENS_DATA_04 0x4D
#define MPU6050_RA_EXT_SENS_DATA_05 0x4E
#define MPU6050_RA_EXT_SENS_DATA_06 0x4F
#define MPU6050_RA_EXT_SENS_DATA_07 0x50
#define MPU6050_RA_EXT_SENS_DATA_08 0x51
#define MPU6050_RA_EXT_SENS_DATA_09 0x52
#define MPU6050_RA_EXT_SENS_DATA_10 0x53
#define MPU6050_RA_EXT_SENS_DATA_11 0x54
#define MPU6050_RA_EXT_SENS_DATA_12 0x55
#define MPU6050_RA_EXT_SENS_DATA_13 0x56
#define MPU6050_RA_EXT_SENS_DATA_14 0x57
#define MPU6050_RA_EXT_SENS_DATA_15 0x58
#define MPU6050_RA_EXT_SENS_DATA_16 0x59
#define MPU6050_RA_EXT_SENS_DATA_17 0x5A
#define MPU6050_RA_EXT_SENS_DATA_18 0x5B
#define MPU6050_RA_EXT_SENS_DATA_19 0x5C
#define MPU6050_RA_EXT_SENS_DATA_20 0x5D
#define MPU6050_RA_EXT_SENS_DATA_21 0x5E
#define MPU6050_RA_EXT_SENS_DATA_22 0x5F
#define MPU6050_RA_EXT_SENS_DATA_23 0x60
#define MPU6050_RA_MOT_DETECT_STATUS 0x61
#define MPU6050_RA_I2C_SLV0_DO 0x63
#define MPU6050_RA_I2C_SLV1_DO 0x64
#define MPU6050_RA_I2C_SLV2_DO 0x65
#define MPU6050_RA_I2C_SLV3_DO 0x66
#define MPU6050_RA_I2C_MST_DELAY_CTRL 0x67
#define MPU6050_RA_SIGNAL_PATH_RESET 0x68
#define MPU6050_RA_MOT_DETECT_CTRL 0x69
#define MPU6050_RA_USER_CTRL 0x6A
#define MPU6050_RA_PWR_MGMT_1 0x6B
#define MPU6050_RA_PWR_MGMT_2 0x6C
#define MPU6050_RA_BANK_SEL 0x6D
#define MPU6050_RA_MEM_START_ADDR 0x6E
#define MPU6050_RA_MEM_R_W 0x6F
#define MPU6050_RA_DMP_CFG_1 0x70
#define MPU6050_RA_DMP_CFG_2 0x71
#define MPU6050_RA_FIFO_COUNTH 0x72
#define MPU6050_RA_FIFO_COUNTL 0x73
#define MPU6050_RA_FIFO_R_W 0x74
#define MPU6050_RA_WHO_AM_I 0x75


/******************************************************************************\
*					Duong chuyen    						       *
\******************************************************************************/
#ifndef cbi
	#define cbi(port, bit) 	   (port) &= ~(1 << (bit))
#endif
#ifndef sbi
	#define sbi(port, bit) 	   (port) |=  (1 << (bit))
#endif	

/******************************************************************************\
*					Prototype (nguyen mau ham)    						       *
\******************************************************************************/

void Setup_MPU6050();
void MPU6050_Test_I2C();				//Kiem tra dia chi Module
unsigned char MPU6050_Check_Registers();
void Get_Temp_Values();
void Calibrate_Gyros();					//Lay sai lech tinh cua Gyro
void Get_Gyro_Values();					//Lay Gia tri Gyro
void Get_Gyro_Rates();					//Lay gia tri goc quay
void Get_Accel_Values();
void Get_Accel_Decac();					//Lay gia toc dai
void Get_Accel_Angles();				//Lay goc tu gia toc trong truong
void Test_Gyro_Value();					//Test gia tri 
void Test_Gyro_Rates();
void Test_Accel_Value();

/******************************************************************************\
*					Function (noi dung ham)	                           *
\******************************************************************************/
 
void Filter_G()
{
	G_Filter[3] = G_Filter[2];
	G_Filter[2] = G_Filter[1];
	G_Filter[1] = G_Filter[0];
	G_Filter[0] = ACCEL_ZDECAC;
	ACCEL_ZDECAC = (G_Filter[3]+G_Filter[2]+G_Filter[1]+G_Filter[0])/4;
}

void Filters_Gyro()
{
	GYRO_XFilter[3] = GYRO_XFilter[2];
	GYRO_XFilter[2] = GYRO_XFilter[1];
	GYRO_XFilter[1] = GYRO_XFilter[0];
	GYRO_XFilter[0] = GYRO_XOUT;

	GYRO_XOUT = 	 ((long)GYRO_XFilter[3]
					+GYRO_XFilter[2]
					+GYRO_XFilter[1]
					+GYRO_XFilter[0])>>2;

	GYRO_YFilter[3] = GYRO_YFilter[2];
	GYRO_YFilter[2] = GYRO_YFilter[1];
	GYRO_YFilter[1] = GYRO_YFilter[0];
	GYRO_YFilter[0] = GYRO_YOUT;

	GYRO_YOUT = 	 ((long)GYRO_YFilter[3]
					+GYRO_YFilter[2]
					+GYRO_YFilter[1]
					+GYRO_YFilter[0])>>2;

	GYRO_ZFilter[3] = GYRO_ZFilter[2];
	GYRO_ZFilter[2] = GYRO_ZFilter[1];
	GYRO_ZFilter[1] = GYRO_ZFilter[0];
	GYRO_ZFilter[0] = GYRO_ZOUT;

	GYRO_ZOUT = 	 ((long)GYRO_ZFilter[3]
					+GYRO_ZFilter[2]
					+GYRO_ZFilter[1]
					+GYRO_ZFilter[0])>>2;
}
void Filters_Accel()
{
	ACCEL_XFilter[3] = ACCEL_XFilter[2];
	ACCEL_XFilter[2] = ACCEL_XFilter[1];
	ACCEL_XFilter[1] = ACCEL_XFilter[0];
	ACCEL_XFilter[0] = ACCEL_XOUT;
	ACCEL_XOUT = 	(ACCEL_XFilter[3]
	                +ACCEL_XFilter[2]
	                +ACCEL_XFilter[1]
	                +ACCEL_XFilter[0])/4;

	ACCEL_YFilter[3] = ACCEL_YFilter[2];
	ACCEL_YFilter[2] = ACCEL_YFilter[1];
	ACCEL_YFilter[1] = ACCEL_YFilter[0];
	ACCEL_YFilter[0] = ACCEL_YOUT;
	ACCEL_YOUT = (ACCEL_YFilter[3]+ACCEL_YFilter[2]+ACCEL_YFilter[1]+ACCEL_YFilter[0])/4;

	ACCEL_ZFilter[3] = ACCEL_ZFilter[2];
	ACCEL_ZFilter[2] = ACCEL_ZFilter[1];
	ACCEL_ZFilter[1] = ACCEL_ZFilter[0];
	ACCEL_ZFilter[0] = ACCEL_ZOUT;
	ACCEL_ZOUT = (ACCEL_ZFilter[3]+ACCEL_ZFilter[2]+ACCEL_ZFilter[1]+ACCEL_ZFilter[0])/4;
}

void Setup_MPU6050()
{
	while(ByteWrite_I2C_USCI(MPU6050_RA_SIGNAL_PATH_RESET,0x07));
	//LCD_Clear();
	//LCD_Home();
	//LCD_PrintString("Start Setup");
	_delay_ms(1000);
	//Sets sample rate to 1000/1+1 = 500Hz
	while(ByteWrite_I2C_USCI(MPU6050_RA_SMPLRT_DIV,9));
	//Disable FSync, 48Hz DLPF
	while(ByteWrite_I2C_USCI(MPU6050_RA_CONFIG, 0x03));
	//Disable gyro self tests, scale of 500 degrees/s
	while(ByteWrite_I2C_USCI(MPU6050_RA_GYRO_CONFIG, 0x18));
	//Disable accel self tests, scale of +-4g, no DHPF
	while(ByteWrite_I2C_USCI(MPU6050_RA_ACCEL_CONFIG, 0x18));
	
	while(ByteWrite_I2C_USCI(MPU6050_RA_TEMP_OUT_H,0x00));
	while(ByteWrite_I2C_USCI(MPU6050_RA_TEMP_OUT_L,0x00));
	while(ByteWrite_I2C_USCI(MPU6050_RA_GYRO_XOUT_H,0x00));
	while(ByteWrite_I2C_USCI(MPU6050_RA_GYRO_XOUT_L,0x00));
	while(ByteWrite_I2C_USCI(MPU6050_RA_GYRO_YOUT_H,0x00));
	while(ByteWrite_I2C_USCI(MPU6050_RA_GYRO_YOUT_L,0x00));
	while(ByteWrite_I2C_USCI(MPU6050_RA_GYRO_ZOUT_H,0x00));
	while(ByteWrite_I2C_USCI(MPU6050_RA_GYRO_ZOUT_L,0x00));

	while(ByteWrite_I2C_USCI(MPU6050_RA_ACCEL_XOUT_H,0x00));
	while(ByteWrite_I2C_USCI(MPU6050_RA_ACCEL_XOUT_L,0x00));
	while(ByteWrite_I2C_USCI(MPU6050_RA_ACCEL_YOUT_H,0x00));
	while(ByteWrite_I2C_USCI(MPU6050_RA_ACCEL_YOUT_L,0x00));
	while(ByteWrite_I2C_USCI(MPU6050_RA_ACCEL_ZOUT_H,0x00));
	while(ByteWrite_I2C_USCI(MPU6050_RA_ACCEL_ZOUT_L,0x00));
	//Freefall threshold of <|0mg|
	while(ByteWrite_I2C_USCI( MPU6050_RA_FF_THR, 0x00));
	//Freefall duration limit of 0
	while(ByteWrite_I2C_USCI( MPU6050_RA_FF_DUR, 0x00));
	//Motion threshold of >0mg
	while(ByteWrite_I2C_USCI( MPU6050_RA_MOT_THR, 0x00));
	//Motion duration of >0s
	while(ByteWrite_I2C_USCI( MPU6050_RA_MOT_DUR, 0x00));
	//Zero motion threshold
	while(ByteWrite_I2C_USCI(MPU6050_RA_ZRMOT_THR, 0x00));
	//Zero motion duration threshold
	while(ByteWrite_I2C_USCI( MPU6050_RA_ZRMOT_DUR, 0x00));
	//Disable sensor output to FIFO buffer
	while(ByteWrite_I2C_USCI( MPU6050_RA_FIFO_EN, 0x00));
	
	//AUX I2C setup
	//Sets AUX I2C to single master control, plus other config
	while(ByteWrite_I2C_USCI( MPU6050_RA_I2C_MST_CTRL, 0x00));
	//Setup AUX I2C slaves	
 	while(ByteWrite_I2C_USCI( MPU6050_RA_I2C_SLV0_ADDR, 0x00));
 	while(ByteWrite_I2C_USCI( MPU6050_RA_I2C_SLV0_REG, 0x00));
 	while(ByteWrite_I2C_USCI( MPU6050_RA_I2C_SLV0_CTRL, 0x00));
 	while(ByteWrite_I2C_USCI(MPU6050_RA_I2C_SLV1_ADDR, 0x00));
 	while(ByteWrite_I2C_USCI( MPU6050_RA_I2C_SLV1_REG, 0x00));
 	while(ByteWrite_I2C_USCI( MPU6050_RA_I2C_SLV1_CTRL, 0x00));
 	while(ByteWrite_I2C_USCI(MPU6050_RA_I2C_SLV2_ADDR, 0x00));
 	while(ByteWrite_I2C_USCI( MPU6050_RA_I2C_SLV2_REG, 0x00));
 	while(ByteWrite_I2C_USCI( MPU6050_RA_I2C_SLV2_CTRL, 0x00));
 	while(ByteWrite_I2C_USCI(MPU6050_RA_I2C_SLV3_ADDR, 0x00));
 	while(ByteWrite_I2C_USCI(MPU6050_RA_I2C_SLV3_REG, 0x00));
 	while(ByteWrite_I2C_USCI( MPU6050_RA_I2C_SLV3_CTRL, 0x00));
 	while(ByteWrite_I2C_USCI( MPU6050_RA_I2C_SLV4_ADDR, 0x00));
 	while(ByteWrite_I2C_USCI(MPU6050_RA_I2C_SLV4_REG, 0x00));
 	while(ByteWrite_I2C_USCI(MPU6050_RA_I2C_SLV4_DO, 0x00));
 	while(ByteWrite_I2C_USCI(MPU6050_RA_I2C_SLV4_CTRL, 0x00));
 	while(ByteWrite_I2C_USCI( MPU6050_RA_I2C_SLV4_DI, 0x00));
 
 
 	//MPU6050_RA_I2C_MST_STATUS //Read-only
 	//Setup INT pin and AUX I2C pass through
	while(ByteWrite_I2C_USCI( MPU6050_RA_INT_PIN_CFG, 0x00));
	//Enable data ready interrupt
	while(ByteWrite_I2C_USCI(MPU6050_RA_INT_ENABLE, 0x01));
	
	//MPU6050_RA_DMP_INT_STATUS		//Read-only
	//MPU6050_RA_INT_STATUS 3A		//Read-only
    //MPU6050_RA_ACCEL_XOUT_H 		//Read-only
    //MPU6050_RA_ACCEL_XOUT_L 		//Read-only
    //MPU6050_RA_ACCEL_YOUT_H 		//Read-only
    //MPU6050_RA_ACCEL_YOUT_L 		//Read-only
    //MPU6050_RA_ACCEL_ZOUT_H 		//Read-only
    //MPU6050_RA_ACCEL_ZOUT_L 		//Read-only
    //MPU6050_RA_TEMP_OUT_H 		//Read-only
    //MPU6050_RA_TEMP_OUT_L 		//Read-only
    //MPU6050_RA_GYRO_XOUT_H 		//Read-only
    //MPU6050_RA_GYRO_XOUT_L 		//Read-only
    //MPU6050_RA_GYRO_YOUT_H 		//Read-only
    //MPU6050_RA_GYRO_YOUT_L 		//Read-only
    //MPU6050_RA_GYRO_ZOUT_H 		//Read-only
    //MPU6050_RA_GYRO_ZOUT_L 		//Read-only
    //MPU6050_RA_EXT_SENS_DATA_00 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_01 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_02 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_03 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_04 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_05 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_06 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_07 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_08 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_09 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_10 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_11 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_12 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_13 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_14 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_15 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_16 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_17 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_18 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_19 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_20 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_21 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_22 	//Read-only
    //MPU6050_RA_EXT_SENS_DATA_23 	//Read-only
    //MPU6050_RA_MOT_DETECT_STATUS 	//Read-only
	
	//Slave out, dont care
	while(ByteWrite_I2C_USCI( MPU6050_RA_I2C_SLV0_DO, 0x00));
	while(ByteWrite_I2C_USCI( MPU6050_RA_I2C_SLV1_DO, 0x00));
	while(ByteWrite_I2C_USCI(MPU6050_RA_I2C_SLV2_DO, 0x00));
	while(ByteWrite_I2C_USCI(MPU6050_RA_I2C_SLV3_DO, 0x00));
	//More slave config
	while(ByteWrite_I2C_USCI( MPU6050_RA_I2C_MST_DELAY_CTRL, 0x00));
	//Reset sensor signal paths
	while(ByteWrite_I2C_USCI(MPU6050_RA_SIGNAL_PATH_RESET, 0x00));
	//Motion detection control
	while(ByteWrite_I2C_USCI(MPU6050_RA_MOT_DETECT_CTRL, 0x00));
	//Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
	while(ByteWrite_I2C_USCI(MPU6050_RA_USER_CTRL, 0x00));
	//Sets clock source to gyro reference w/ PLL
	while(ByteWrite_I2C_USCI(MPU6050_RA_PWR_MGMT_1, 0x00));
	//Controls frequency of wakeups in accel low power mode plus the sensor standby modes
	while(ByteWrite_I2C_USCI(MPU6050_RA_PWR_MGMT_2, 0x00));
    //MPU6050_RA_BANK_SEL			//Not in datasheet
    //MPU6050_RA_MEM_START_ADDR		//Not in datasheet
    //MPU6050_RA_MEM_R_W			//Not in datasheet
    //MPU6050_RA_DMP_CFG_1			//Not in datasheet
    //MPU6050_RA_DMP_CFG_2			//Not in datasheet
    //MPU6050_RA_FIFO_COUNTH		//Read-only
    //MPU6050_RA_FIFO_COUNTL		//Read-only
	//Data transfer to and from the FIFO buffer
	//while(ByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_FIFO_R_W, 0x00));
    //MPU6050_RA_WHO_AM_I 			//Read-only, I2C address
	
	//LCD_Clear();
	//LCD_Home();
	//LCD_PrintString("End Setup");
	_delay_ms(1000);
}

void MPU6050_Test_I2C()
{
	unsigned char i;
	TEST:
	LCD_Clear();
	LCD_Home();
	LCD_PrintString("Test_I2C");
	_delay_ms(1000);
	i = ByteRead_I2C_USCI(MPU6050_RA_WHO_AM_I);
	if(i == MPU6050_ADDRESS)
	{
		LCD_Clear();
		LCD_Home();
		LCD_PrintString("Pass Test I2C");
		LCD_Goto(2,0);
		LCD_PrintDecimal(i,8);
		_delay_ms(1000);
	}
	else
	{
		LCD_Clear();
		LCD_Home();		
		LCD_PrintString("ERROR");
		LCD_Goto(2,0);
		LCD_PrintDecimal(i,8);
		_delay_cycles(1000000);
		goto TEST;
	}	
	_delay_ms(1000);		
}	

unsigned char MPU6050_Check_Registers()
{
	unsigned char Data;
	unsigned char Failed = 0;
	
	SETUP:
	Failed =0;
	Setup_MPU6050();
	_delay_ms(1000);
	//LCD_Clear();
	//LCD_Home();
	//LCD_PrintString("Check REG");
	_delay_ms(1000);
	Data = ByteRead_I2C_USCI(MPU6050_RA_SMPLRT_DIV);
	if(Data != 0x01)  Failed ++;
	_delay_cycles(1000000);
	Data = ByteRead_I2C_USCI(MPU6050_RA_CONFIG);
	if(Data != 0x03)  Failed ++;
	_delay_cycles(1000000);
	Data = ByteRead_I2C_USCI(MPU6050_RA_GYRO_CONFIG);
	if(Data != 0x18)  Failed ++;
	_delay_cycles(100000);
	Data = ByteRead_I2C_USCI(MPU6050_RA_ACCEL_CONFIG);
	if(Data != 0x18)  Failed ++;
	_delay_cycles(1000000);
	
	/*
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_FF_THR, &Data));
	if(Data != 0x00) Failed ++; 
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_FF_DUR, &Data));
	if(Data != 0x00)  Failed ++; 
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_MOT_THR, &Data));
	if(Data != 0x00) Failed ++; 
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_MOT_DUR, &Data));
	if(Data != 0x00)  Failed ++; 
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_THR, &Data));
	if(Data != 0x00)  Failed ++; 
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_DUR, &Data));
	if(Data != 0x00)  Failed = 1; 
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, &Data));
	if(Data != 0x00)  Failed ++; 
	//AUX I2C Setup
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, &Data));
	if(Data != 0x00)  Failed ++; 
	//Setup AUX I2C Slaves
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_ADDR, &Data));
	if(Data != 0x00)  Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_REG, &Data));
	if(Data != 0x00) Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL, &Data));
	if(Data != 0x00)  Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_ADDR, &Data));
	if(Data != 0x00)  Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_REG, &Data));
	if(Data != 0x00)  Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_CTRL, &Data));
	if(Data != 0x00)  Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_ADDR, &Data));
	if(Data != 0x00)  Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_REG, &Data));
	if(Data != 0x00)  Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_CTRL, &Data));
	if(Data != 0x00)  Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_ADDR, &Data));
	if(Data != 0x00) Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_REG, &Data));
	if(Data != 0x00)  Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_CTRL, &Data));
	if(Data != 0x00)  Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_ADDR, &Data));
	if(Data != 0x00) Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_REG, &Data));
	if(Data != 0x00) Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_DO, &Data));
	if(Data != 0x00) Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_CTRL, &Data));
	if(Data != 0x00) Failed ++; 
 	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_DI, &Data));
	 
 	//MPU6050_RA_I2C_MST_STATUS //Read-only
 	//Setup INT pin and AUX I2C pass through 
	if(Data != 0x00) Failed ++; 
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, &Data));
	if(Data != 0x00)  Failed ++; 
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, &Data));
	if(Data != 0x00)  Failed ++; 
	
	//Slave out, dont care
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_DO, &Data));
	if(Data != 0x00)  Failed ++; 
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_DO, &Data)); 	
	if(Data != 0x00)  Failed ++; 
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_DO, &Data)); 	
	if(Data != 0x00)  Failed ++; 
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_DO, &Data)); 	
	if(Data != 0x00)  Failed ++;
	
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_DELAY_CTRL, &Data));
	if(Data != 0x00)  Failed ++;
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_SIGNAL_PATH_RESET, &Data)); 
	if(Data != 0x00)  Failed ++;
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_CTRL, &Data)); 	
	if(Data != 0x00)  Failed ++;
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, &Data));
	if(Data != 0x00) Failed ++;
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &Data));
	if(Data != 0x02)  Failed ++; 
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, &Data));
	if(Data != 0x00)  Failed ++;
	while(ByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_FIFO_R_W, &Data));
	if(Data != 0x00)  Failed ++;
	*/

	if (Failed == 0) 
	{
		LCD_Clear();
		LCD_Home();
		LCD_PrintString("Complete");
	}
	else 
	{
		LCD_Clear();
		LCD_Home();
		LCD_PrintDecimal(Failed,5);
		LCD_PrintString(" Loi");
		_delay_ms(2000);
		goto SETUP;
	}
	_delay_ms(1000);
	
	return(Failed);
}


void Get_Temp_Values()
{
	unsigned char rData[2];

	WordRead_I2C_USCI(MPU6050_RA_TEMP_OUT_H, rData, 2);
	TEMP_OUT = ((rData[1]<<8)|rData[0]);
}

void Calibrate_Gyros()
{
	int i = 0;
	char buff1[10];
	unsigned char rData[6];
	long	GYRO_XOUT_OFFSET_4096SUM=0,
			GYRO_YOUT_OFFSET_4096SUM=0,
			GYRO_ZOUT_OFFSET_4096SUM=0,		 
			GYRO_XOFFSET = 0,
			GYRO_YOFFSET = 0,
			GYRO_ZOFFSET = 0;
	
	_delay_ms(1000);
	//LCD_Clear();
	//LCD_Home();
	//LCD_PrintString("CHECK GYRO");
	_delay_ms(1000);
	for(i = 0; i<4096; i++)
	{
		while(WordRead_I2C_USCI(MPU6050_RA_GYRO_XOUT_H, rData, 6));
		
		GYRO_XOUT_OFFSET_4096SUM += ((rData[1]<<8)|rData[0]);
		GYRO_YOUT_OFFSET_4096SUM += ((rData[3]<<8)|rData[2]);
		GYRO_ZOUT_OFFSET_4096SUM += ((rData[5]<<8)|rData[4]);
		GYRO_XOUT_OFFSET_4096SUM += GYRO_XOUT;
		GYRO_YOUT_OFFSET_4096SUM += GYRO_YOUT;
		GYRO_ZOUT_OFFSET_4096SUM += GYRO_ZOUT;
		
		UART_Write_Char('1');
		sprintf(buff1,"%d",i);
		UART_Write_String(buff1);
		UART_Write_Char(' ');
		_delay_cycles(160000);
	//	LCD_Goto(2,0);
	//	LCD_PrintUnDecimal(i,4);
	}	
	GYRO_XOFFSET = GYRO_XOUT_OFFSET_4096SUM>>12;
	GYRO_YOFFSET = GYRO_YOUT_OFFSET_4096SUM>>12;
	GYRO_ZOFFSET = GYRO_ZOUT_OFFSET_4096SUM>>12;
	//LCD_Clear();
	//LCD_Home();
	//LCD_PrintString("OFFSET X:");
	//LCD_PrintDecimal(GYRO_XOFFSET,6);
	//LCD_Goto(2,0);
	//LCD_PrintString("Y:");
	//LCD_PrintDecimal(GYRO_YOFFSET,6);
	//LCD_PrintString("Z:");
	//LCD_PrintDecimal(GYRO_ZOFFSET,6);
	_delay_cycles(10000000);
}	


void Get_Gyro_Values()
{
	unsigned char rData[6];

	WordRead_I2C_USCI(MPU6050_RA_GYRO_XOUT_H, rData, 6);
	GYRO_XOUT = ((rData[1]<<8)|rData[0]) + GYRO_XOUT_OFFSET;
	GYRO_YOUT = ((rData[3]<<8)|rData[2]) + GYRO_YOUT_OFFSET;
	GYRO_ZOUT = ((rData[5]<<8)|rData[4]) + GYRO_ZOUT_OFFSET;
	Filters_Gyro();
}


//Gets raw accelerometer data, performs no processing
void Get_Accel_Values()
{
	unsigned char rData[6];
	WordRead_I2C_USCI(MPU6050_RA_ACCEL_XOUT_H, rData, 6);
	ACCEL_XOUT = ((rData[1]<<8)|rData[0]);
	ACCEL_YOUT = ((rData[3]<<8)|rData[2]);
	ACCEL_ZOUT = ((rData[5]<<8)|rData[4]);
	Filters_Accel();
}	


//Function to read the gyroscope rate data and convert it into degrees/s
void Get_Gyro_Rates()
{
	unsigned char rData[6];	
	
	WordRead_I2C_USCI(MPU6050_RA_GYRO_XOUT_H, rData, 6);

	GYRO_XOUT = ((rData[1]<<8)|rData[0]) + GYRO_XOUT_OFFSET;
	GYRO_YOUT = ((rData[3]<<8)|rData[2]) + GYRO_YOUT_OFFSET;
	GYRO_ZOUT = ((rData[5]<<8)|rData[4]) + GYRO_ZOUT_OFFSET;
	Filters_Gyro();


	if(GYRO_XOUT>0)GYRO_XRATE += (GYRO_XOUT/48);
	else GYRO_XRATE += (GYRO_XOUT>>5);
	GYRO_YRATE += (GYRO_YOUT>>5);
	GYRO_ZRATE += (GYRO_ZOUT>>5);
}


void Get_Accel_Decac()
{
	unsigned char rData[6];
	WordRead_I2C_USCI(MPU6050_RA_ACCEL_XOUT_H, rData, 6);
	
	ACCEL_XOUT = ((rData[1]<<8)|rData[0]);
	ACCEL_YOUT = ((rData[3]<<8)|rData[2]);
	ACCEL_ZOUT = ((rData[5]<<8)|rData[4]);
	Filters_Accel();
	ACCEL_XA = ACCEL_XOUT - ACCEL_XOUT_PAST;
	ACCEL_YA = ACCEL_XOUT - ACCEL_YOUT_PAST;
	ACCEL_ZA = ACCEL_XOUT - ACCEL_ZOUT_PAST;

	ACCEL_XV += ACCEL_XA;
	ACCEL_YV += ACCEL_YA;
	ACCEL_ZV += ACCEL_ZA;

	ACCEL_XDECAC += (ACCEL_XV>>8);
	ACCEL_YDECAC += (ACCEL_YV>>8);
	ACCEL_ZDECAC += (ACCEL_ZV>>8);

	ACCEL_XOUT_PAST = ACCEL_XOUT;	
	ACCEL_YOUT_PAST = ACCEL_YOUT;
	ACCEL_ZOUT_PAST = ACCEL_ZOUT;
}



//Converts the already acquired accelerometer data into 3D euler angles
void Get_Accel_Angles()
{
	ACCEL_XANGLE =(int)( 57.296 * (float)atan((float)ACCEL_YOUT/(float)ACCEL_ZOUT));
	//ACCEL_YANGLE = 57.296*atan((float)- ACCEL_XOUT/ sqrt(pow((float)ACCEL_ZOUT,2)+pow((float)ACCEL_YOUT,2)));
}	

#endif

