/*
    This file comes from the source code of Red Viper:
    see https://github.com/skyfloogle/red-viper/blob/master/include/extrapad.h
*/

#pragma once
#include <3ds/types.h>

typedef struct
{
    s32 _data1[0x10];
    bool recalibrated;
    s32 _data2[0xf];
} extraPadConf;

void extraPadInit(extraPadConf *conf);

bool extraPadLaunch(extraPadConf *conf);
