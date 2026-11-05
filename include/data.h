#ifndef DATA_H
#define DATA_H
#include "sensor.h"

typedef struct {
    SensorNode *head;
    SensorNode *tail;
    int size;
} SensorList;

void initList(SensorList *list);
void addNode(SensorList *list, SensorData data);
void printForward(SensorList *list);
void printBackward(SensorList *list);
void freeList(SensorList *list);
SensorNode *searchNode(SensorList *list, int id);
int deleteNode(SensorList *list, int id);

#endif