#include "usr_general.h"

_io S_ACC_PARAMETERS g_Acc;

float xAxis, yAxis, zAxis = 0;
char char_count[50] = {0};

_io void UsrAccInitial(void);
_io void UsrAccelometerGeneral(void);


uint32_t g_globaltimercount;
bool g_accelometerinterruptdetectedflag = false;
bool g_accelometerchipokflag = false;
bool g_accelometerchipflag = false;
bool g_accelometrehardwareokflag = false;
bool g_accelometerfabricationokflag = false;
bool g_chiperrorflag = false;
bool g_accelometererroropenledflag = false;
bool g_accsensorisreadyflag = false;
bool g_accelometerfabricationinitflag = false;

uint8_t address_buf[16] = {0};
uint8_t address = 0;

_io void UsrAccInitial(void)
{
    UL_AccelInitial(&g_Acc);
    g_accelometerchipokflag = UL_AccCheckChip();
    if(g_accelometerchipokflag)
    {
        g_accelometrehardwareokflag = true;
        // Save eeprom
    }

    else
    {
        g_chiperrorflag = false;
    }

    if(g_accelometerchipokflag)
    {
        g_accelometerfabricationinitflag = UL_AccFabrication();
        if(g_accelometerfabricationinitflag)
        {
            g_accelometerfabricationokflag = true;
        }
        else
        {
            g_accelometerfabricationokflag = false;
        }
    }

}


_io void UsrAccelometerGeneral(void)
{
    _io uint32_t acctimercount = 0;

    if(!g_accelometerchipokflag)
    {
        if(acctimercount > g_globaltimercount)
            acctimercount = g_globaltimercount;

        if((g_globaltimercount - acctimercount) > 5000)
        {
            acctimercount = g_globaltimercount;
            UsrAccInitial();
            if(!UL_AccChipOk())
                g_accelometererroropenledflag = true;
            
            g_accelometerchipflag = g_accelometerchipokflag;
        }
    }
    else
        acctimercount = g_globaltimercount;

    UL_AccelometerClearFlag();
}


void UsrI2CScan(void)
{    
    for (address = 0; address < 128; address++)
    {
        if (HAL_I2C_IsDeviceReady(&ACC_I2C_CHANNEL, (uint16_t)(address << 1), 5, 10) == HAL_OK)
        {
            g_accsensorisreadyflag = true;
            HAL_GPIO_WritePin(BLUE_GPIO_Port, BLUE_Pin, GPIO_PIN_RESET);    // Rgb led blue pwm pin
            sprintf((char*)address_buf, "iste adres: 0x%X\r\n", address);
        }
    }    
}


void UsrSystemInitial(void)
{
    UsrAccInitial();
    UsrI2CScan();
}


void UsrSystemGeneral(void)
{
    UsrAccelometerGeneral();
    UL_ReadAccelData(&xAxis, &yAxis, &zAxis);
    sprintf(char_count, "x_axis: %.3f, y_axis: %.3f, z_axis: %.3f\r\n", xAxis, yAxis, zAxis);
}
