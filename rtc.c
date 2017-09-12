#include "rtc.h"
#include "gpio.h"
#include "stdiox.h"

/*-------------- private function --------------*/
static void RtcShow(void)
{
	I2CShow(I2C2);
}
static void RtcStop(void)
{
	I2CStop(I2C2);
}
static int RtcStartRead(uint8_t device)
{
	int ret = I2CStartRead(I2C2, device);
	if( ret < 0 )
	{
		printf("%s = %d, \n", __func__, ret);
	}
	return ret;
}
static int RtcStartWrite(uint8_t device)
{
	int ret = I2CStartWrite(I2C2, device);
	if( ret < 0 )
	{
		printf("%s = %d, \n", __func__, ret);
	}
	return ret;
}
static int RtcReadBuffer(uint8_t *buf, uint32_t len)
{
	int ret = I2CRead(I2C2, buf, len);
	if( ret < 0 )
	{
		printf("%s = %d, \n", __func__, ret);
	}
	return ret;
}
static int RtcWriteBuffer(uint8_t *buf, uint32_t len)
{
	int ret = I2CWrite(I2C2, buf, len);
	if( ret < 0 )
	{
		printf("%s = %d, \n", __func__, ret);
	}
	return ret;
}
/*--------------- end of private ---------------*/


void RtcConfig(void)
{
	GpioInit(PB10, GPIO_Mode_AF_OD, GPIO_Speed_50MHz);
	GpioInit(PB11, GPIO_Mode_AF_OD, GPIO_Speed_50MHz);
	I2CConfig(I2C2, 0x0A, 400*1000);
}
int RtcGet(RtcType_t *time)
{
	uint8_t buf[0x11] = {0};

	if( RtcStartRead(RTC_ADDRESS) < 0 )
	{
		printf("RtcStartRead(%02X) failed \n", RTC_ADDRESS);
		RtcShow();
		return 0;
	}
	if( RtcReadBuffer(buf, sizeof(buf)) < 0 )
	{
		printf("I2CRead failed \n");
		RtcShow();
		RtcStop();
		return 0;
	}
	RtcStop();
	printf("\nRTC[0]: ");
	for(int i = 0; i < sizeof(buf); i++)
	{
		printf("%02X ", buf[i]);
	}
	printf("\n");
	return 0;
}
int RtcSet(RtcType_t *time)
{
	RtcStartWrite(RTC_ADDRESS);
	RtcWriteBuffer((uint8_t*)time, sizeof(RtcType_t));
	return 0;
}
