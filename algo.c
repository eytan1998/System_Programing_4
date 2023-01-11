#include "algo.h"

int dijkstra(pnode head, int src, int dest) {
    pnode p = (head)->next;
    pnode minDis;
    while (p != NULL) {
        p->isFinished = 0;
        p->distance = -1;
        if (p->node_id == src) {
            p->distance = 0;
            minDis = p;
        }
        p = p->next;
    }
    while (1) {
        pedge neber = NULL;
        neber= minDis->edges;
        while (neber != NULL) {
            if (!(neber->endpoint->isFinished) && neber->endpoint->distance != -1 && neber->endpoint->distance > minDis->distance + neber->weight) {
                neber->endpoint->distance = minDis->distance + neber->weight;
            }
            neber = neber->next;
        }
        minDis->isFinished = 1;
        if (minDis->node_id == dest) return minDis->distance;

        pnode temp = (head)->next;
        minDis = NULL;
        while (temp != NULL) {
            if ((minDis == NULL || minDis->distance > temp->distance) && !temp->isFinished) {
                minDis = temp;
            }
            temp = temp->next;
        }
        if (minDis == NULL)break;

    }
    return -1;
}