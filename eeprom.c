#include "gpio.h"
#include "eeprom.h"
#include "stdiox.h"


/*-------------- private function --------------*/
static void EepromShow(void)
{
	I2CShow(I2C1);
}
static void EepromStop(void)
{
	I2CStop(I2C1);
}
static int EepromStartRead(uint8_t device)
{
	int ret = I2CStartRead(I2C1, device);
	if( ret < 0 )
	{
		printf("%s = %d, \n", __func__, ret);
	}
	return ret;
}
static int EepromStartWrite(uint8_t device)
{
	int ret = I2CStartWrite(I2C1, device);
	if( ret < 0 )
	{
		printf("%s = %d, \n", __func__, ret);
	}
	return ret;
}
static int EepromReadBuffer(uint8_t *buf, uint32_t len)
{
	int ret = I2CRead(I2C1, buf, len);
	if( ret < 0 )
	{
		printf("%s = %d, \n", __func__, ret);
	}
	return ret;
}
static int EepromWriteBuffer(uint8_t *buf, uint32_t len)
{
	int ret = I2CWrite(I2C1, buf, len);
	if( ret < 0 )
	{
		printf("%s = %d, \n", __func__, ret);
	}
	return ret;
}
/*--------------- end of private ---------------*/

/*--------------- public function ---------------*/
void EepromConfig(void)
{
	GpioInit(PB6, GPIO_Mode_AF_OD, GPIO_Speed_50MHz);
	GpioInit(PB7, GPIO_Mode_AF_OD, GPIO_Speed_50MHz);
	I2CConfig(I2C1, 0x0B, 400*1000);
}
int EepromRead(uint32_t offset, uint8_t *buf, uint32_t len)
{
	uint8_t ofs[2] = {EEPROM_OFFSET2(offset), EEPROM_OFFSET3(offset)};

	if( EepromStartWrite(EEPROM_OFFSET1(offset)) < 0 )
	{
		printf("EepromStartWrite(%02X) failed:\n",EEPROM_OFFSET1(offset));
		EepromShow();
		return 0;
	}
	if( EepromWriteBuffer(ofs, 2) < 0 )
	{
		printf("EepromWriteBuffer failed: \n");
		EepromShow();
		EepromStop();
		return 0;
	}
	EepromStop();
	if( EepromStartRead(EEPROM_OFFSET1(offset)) < 0 )
	{
		printf("EepromStartRead(%02X) failed:\n",EEPROM_OFFSET1(offset));
		EepromShow();
		return 0;
	}
	if(  EepromReadBuffer(buf, len) < 0 )
	{
		printf("EepromReadBuffer failed:  \n");
		EepromShow();
		EepromStop();
		return 0;
	}
	EepromStop();
	printf("EepromRead[%05X]: \n", offset);
	for(int i = 0; i < len; i++)
	{
		printf("%02X ", buf[i]);
		if( (i+1)%16 == 0 )
		{
			printf("\n");
		}
	}
	printf("\n");
	return len; 
}
int EepromWrite(uint32_t offset, uint8_t *buf, uint32_t len)
{
	uint8_t ofs[2] = {EEPROM_OFFSET2(offset), EEPROM_OFFSET3(offset)};

	if( EepromStartWrite(EEPROM_OFFSET1(offset)) < 0 )
	{
		printf("EepromStartWrite(%02X) failed:  \n", EEPROM_OFFSET1(offset));
		EepromShow();
		return 0;
	}
	if( EepromWriteBuffer(ofs, sizeof(ofs)) < 0 )
	{
		printf("EepromWriteBuffer(ofs) failed:  \n");
		EepromShow();
		EepromStop();
		return 0;
	}
	if( EepromWriteBuffer(buf, len) < 0 )
	{
		printf("EepromWriteBuffer(buf) failed:  \n");
		EepromShow();
		EepromStop();
		return 0;
	}
	EepromStop();
	printf("EepromWrite[%05X]: \n", offset);
	for(int i = 0; i < len; i++)
	{
		printf("%02X ", buf[i]);
		if( (i+1)%16 == 0 )
		{
			printf("\n");
		}
	}
	printf("\n");
	return len;
}
/*--------------- end of public ---------------*/
