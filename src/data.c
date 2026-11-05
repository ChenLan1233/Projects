#include <stdio.h>
#include <stdlib.h>
#include "data.h"
void initList(SensorList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
void addNode(SensorList *list, SensorData data) {
    SensorNode *newNode = (SensorNode*)malloc(sizeof(SensorNode));
    if (newNode == NULL) {
        printf("Error\n");
        return;
    }
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->data = data;
    if(list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}
void printForward(SensorList *list) {
    SensorNode *current = list->head;
    while (current != NULL) {
        printf("编号：%d, 温度：%.2f, 湿度：%.2f, 气压：%.2f\n",
                current->data.id,
                current->data.temperature,
                current->data.humidity,
                current->data.pressure);
        current = current->next;
    }
}
void printBackward(SensorList *list) {
    SensorNode *current = list->tail;
    while (current != NULL) {
        printf("编号：%d, 温度：%.2f, 湿度：%.2f, 气压：%.2f\n",
                current->data.id,
                current->data.temperature,
                current->data.humidity,
                current->data.pressure);
        current = current->prev;
    }
}
void freeList(SensorList *list) {
    SensorNode *current = list->head;
    while (current != NULL) {
        SensorNode *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
SensorNode *searchNode(SensorList *list, int id) {
    SensorNode *current = list->head;
    while(current != NULL) {
        if(current->data.id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
int deleteNode(SensorList *list, int id) {
    SensorNode *target = searchNode(list, id);
    if(target == NULL) {
        return 0;
    } else if (target == list->head) {
        list->head = target->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        } else {
            list->tail = NULL;
        }
    } else if (target == list->tail) {
        list->tail = target->prev;
        target->prev->next = NULL;
    } else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }
    free(target);
    list->size--;
    return 1;
}