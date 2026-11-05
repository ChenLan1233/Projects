#include <stdio.h>
#include "data.h"
#include "analysis.h"

int main(void)
{
    SensorList list;
    initList(&list);

    SensorData data1 = {1, 25.5, 60.0, 101.3, "2026-11-02", 0};
    SensorData data2 = {2, 28.0, 55.0, 100.8, "2026-11-02", 0};
    SensorData data3 = {3, 22.5, 65.0, 102.1, "2026-11-02", 0};

    addNode(&list, data1);
    addNode(&list, data2);
    addNode(&list, data3);

    SensorData *array = NULL;
    int count = listToArray(&list, &array);

    if (count > 0)
    {
        printf("温度最大值：%.2f\n",
               getMaxValue(array, count, getTemperature));

        printf("温度最小值：%.2f\n",
               getMinValue(array, count, getTemperature));

        printf("温度平均值：%.2f\n",
               getAverageValue(array, count, getTemperature));

        printf("湿度平均值：%.2f\n",
               getAverageValue(array, count, getHumidity));

        printf("气压平均值：%.2f\n",
               getAverageValue(array, count, getPressure));
    }     

    freeArray(array);
    freeList(&list);

    return 0;
}