#include <stdio.h>
#include <stdlib.h>
#include "analysis.h"
int listToArray(SensorList *list, SensorData **array) {
    if(list == NULL || array == NULL) {
        return 0;
    }
    if(list->size == 0) {
        *array = NULL;
        return 0;
    }
    *array = (SensorData *)malloc(list->size * sizeof(SensorData));
    if(*array == NULL) {
        return 0;
    }
    SensorNode *current = list->head;
    for(int i = 0; i < list->size; i++) {
        (*array)[i] = current->data;
        current = current->next;
    }
    return list->size;
}
void freeArray(SensorData *array) {
    free(array);
}
float getTemperature(SensorData *data) {
    return data->temperature;
}
float getHumidity(SensorData *data) {
    return data->humidity;
}
float getPressure(SensorData *data) {
    return data->pressure;
}
float getMaxValue(SensorData *array, int count, GetValueFunc getValue) {
    if (array == NULL || count <= 0 || getValue == NULL) {
        return 0.0f;
    }
    float max = getValue(array);
    for(int i = 1; i < count; i++) {
        if(max < getValue(array + i)) {
            max = getValue(array + i);
        }
    }
    return max;
}
float getMinValue(SensorData *array, int count, GetValueFunc getValue) {
    if (array == NULL || count <= 0 || getValue == NULL) {
        return 0.0f;
    }
    float min = getValue(array);
    for(int i = 1; i < count; i++) {
        if(min > getValue(array + i)) {
            min = getValue(array + i);
        }
    }
    return min;
}
float getAverageValue(SensorData *array, int count, GetValueFunc getValue) {
    if (array == NULL || count <= 0 || getValue == NULL) {
        return 0.0f;
    }
    float sum = 0.0;
    for(int i = 0; i < count; i++) {
        sum = sum + getValue(array + i);
    }
    return sum / count;
}
void sortData(SensorData *data, int count, GetValueFunc getValue, int ascending) {
    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            if (ascending == 0) {
                if(getValue(data + j) < getValue(data + j + 1)) {
                    SensorData temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            } else {
                if(getValue(data + j) > getValue(data + j + 1)) {
                    SensorData temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }
}
int filterData(SensorData *src, int count, GetValueFunc getValue, float threshold, int greater,SensorData *dest) {
    if (src == NULL || getValue == NULL || dest == NULL || count <= 0) {
        return 0;
    }
    int n = 0;
    for(int i = 0; i < count; i++) {
        if(greater == 0) {
            if (getValue(src + i) <= threshold) {
            int l = -1, r = n, mid;
            while(r - l != 1) {
                mid = (r + l) / 2;
                if(getValue(dest + mid) < getValue(src + i)) {
                    r = mid;
                } else {
                    l = mid;
                }
            }
            for(int j = n; j > r; j--) {
                dest[j] = dest[j - 1];
            }
            dest[r] = src[i];
            n++;
            }
        } else {
            if (getValue(src + i) >= threshold) {
            int l = -1, r = n, mid;
            while(r - l != 1) {
                mid = (r + l) / 2;
                if(getValue(dest + mid) < getValue(src + i)) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            for(int j = n; j > r; j--) {
                dest[j] = dest[j - 1];
            }
            dest[r] = src[i];
            n++;
            }
        }
    }
    return n;
}