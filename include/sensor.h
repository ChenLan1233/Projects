#ifndef SENSOR_H
#define SENSOR_H
    typedef struct {
        int id;
        float temperature;
        float humidity;
        float pressure;
        char time[20];
        int alarmFlag;
    } SensorData;

    typedef struct SensorNode {
        SensorData data;
        struct SensorNode *next;
        struct SensorNode *prev;
    } SensorNode;
#endif