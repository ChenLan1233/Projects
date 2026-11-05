#ifndef ANALYSIS_H
#define ANALYSIS_H
#include "data.h"

int listToArray(SensorList *list, SensorData **array);
void freeArray(SensorData *array);
float getTemperature(SensorData *data);
float getHumidity(SensorData *data);
float getPressure(SensorData *data);
typedef float (*GetValueFunc)(SensorData *data);
float getMaxValue(SensorData *array, int count, GetValueFunc getValue);
float getMinValue(SensorData *array, int count, GetValueFunc getValue);
float getAverageValue(SensorData *array, int count, GetValueFunc getValue);
void sortData(SensorData *data, int count, GetValueFunc getvalue, int ascending);
int filterData(SensorData *data, int count, GetValueFunc getValue, float threshold, int greater, SensorData *dest);

#endif