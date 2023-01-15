#include "algo.h"

int dijkstra(pnode head, int src, int dest) {
    //initialize -1 to all and 0 to s
    pnode p = (head)->next;
    pnode minDis;
    while (p != NULL) {
        p->isFinished = 0;
        p->distance = INF;
        if (p->node_id == src) {
            p->distance = 0;
            minDis = p;
        }
        p = p->next;
    }

    while (minDis != NULL) {
        pedge neighbor = minDis->edges;
        while (neighbor != NULL) {
            if (!(neighbor->endpoint->isFinished) && //if not finished
                minDis->distance != INF && // if not inf
                (neighbor->endpoint->distance == INF || // if neighbor distinction is inf
                 neighbor->endpoint->distance > minDis->distance + neighbor->weight)) { //or better path by minDis
                neighbor->endpoint->distance = minDis->distance + neighbor->weight;
            }
            neighbor = neighbor->next;
        }
        minDis->isFinished = 1;
        if (minDis->node_id == dest) return minDis->distance;

        pnode temp = (head)->next;//get first node
        minDis = NULL;
        while (temp != NULL) { //find the minimum node that not finished
            if (temp->distance == -1) {}
            else if ((minDis == NULL || minDis->distance > temp->distance) && !temp->isFinished) {
                minDis = temp;
            }
            temp = temp->next;
        }
    }
    return INF;
}