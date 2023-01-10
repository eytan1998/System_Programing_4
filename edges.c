#include "edges.h"


pedge addEdge(pnode *mNode) {
    pedge newEdge = malloc(sizeof(struct edge_));
    newEdge->weight = 0;
    newEdge->endpoint = NULL;
    newEdge->next = (*mNode)->edges;
    (*mNode)->edges = newEdge;
    return newEdge;
}
pedge getEdge(pedge *edges, int nodeId) {
    pedge ans = (*edges)->next;
    while (ans != NULL) {
        if (ans->endpoint->node_id == nodeId) return ans;
        ans = ans->next;
    }
    return NULL;
}

void deleteEdge(pedge *edges, pnode destNode) {
    pedge temp;
    pedge prev;
    temp = *edges;
    prev = *edges;
    while (temp != NULL) {
        if (temp == *edges && destNode == prev->endpoint) {
            *edges = (*edges)->next;
            free(temp);
            break;
        } else {
            if (temp->endpoint == destNode) {
                prev->next = temp->next;
                free(temp);
                break;
            } else {
                prev = temp;

                if (prev == NULL)
                    break;
                temp = temp->next;
            }
        }
    }
}

void deleteAllEdges(pedge  e) {
    while (e != NULL) {
        pedge temp = e;
        e = e->next;
        free(temp);
    }
}
