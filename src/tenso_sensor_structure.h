#ifndef __TENSO_SENSOR_STRUCTURE_v3_H_
#define __TENSO_SENSOR_STRUCTURE_v3_H_
/*==================================================================================*/
//Файл описания структур данных, передаваемых датчиком, количество каналов АЦП
/*==================================================================================*/
#include <stdint.h>
#pragma pack(push, 1)
/*==================================================================================*/
#define TENSO_SENSOR_TO_MACHINE_V3_magic 0x14141414
#define TENSO_SENSOR_TO_MACHINE_V3_magic_id 0x14

enum ChannelsADC{
    ADC_CHANNEL_0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,

    NUMBER_CHANNELS_ADC
};

typedef struct
{
    uint32_t magic;
    uint32_t time_tick_ms;

    int32_t tenso_sensor_channel_0;
    int32_t tenso_sensor_channel_1;
    int32_t tenso_sensor_channel_2;
    int32_t tenso_sensor_channel_3;
} TTensoSensorStateSendToMachine_V3;

/*==================================================================================*/
#pragma pack(pop)

#endif
