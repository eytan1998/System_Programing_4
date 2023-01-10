#include <stdio.h>


#include "algo.h"
#include "graph.h"
#include "nodes.h"
#include "edges.h"


int main() {

    pnode head = malloc(sizeof(struct GRAPH_NODE_));
    (head)->node_id = -1;
    (head)->next = NULL;
    head->edges = NULL;

    char choice;
    int flag = 1;
    while (flag && scanf(" %c", &choice) != EOF) {
        switch (choice) {
            case 'A':
                build_graph_cmd(&head);
                break;
            case 'B':
                insert_node_cmd(&head);
                break;
            case 'D':
                delete_node_cmd(&head);
                break;
            case 'S':
                shortsPath_cmd(head);
                break;
            case 'T':
                TSP_cmd(head);
                break;
            default:
                flag = 0;
                break;
        }
    }
    printGraph_cmd(head);
    deleteGraph_cmd(&head);
    return 0;
}

void build_graph_cmd(pnode *head) {
    int nodesNum;
    scanf(" %d", &nodesNum);


    for (int i = 0; i < nodesNum; ++i) {
        pnode newNode = malloc(sizeof(struct GRAPH_NODE_));
        newNode->next = NULL;
        newNode->edges = NULL;
        newNode->node_id = i;
        addNode(head, newNode);
    }

    for (int j = 0; j < nodesNum; ++j) {
        char n = 0;
        scanf(" %c", &n);
        insert_node_cmd(head);
    }
}

void insert_node_cmd(pnode *head) {
    int sourceNode = 0, endNode = 0, weight = 0;
    scanf(" %d", &sourceNode);

    pnode newNode = getNode(head, sourceNode);
    if (newNode == NULL) {
        newNode = malloc(sizeof(struct GRAPH_NODE_));
        newNode->node_id = sourceNode;
        newNode->edges = NULL;
        newNode->next = NULL;
        addNode(head, newNode);
    } else {
        deleteAllEdges(newNode->edges);
        newNode->edges = NULL;
    }


    while (1) {
        if (scanf(" %d", &endNode) != 1) break;

        scanf(" %d", &weight);
        pedge newEdge = addEdge(&(newNode));

        newEdge->endpoint = getNode(head, endNode);
        newEdge->weight = weight;
    }

}

void delete_node_cmd(pnode *head) {
    int nodeID;
    scanf(" %d", &nodeID);
    pnode p = (*head)->next;
    while (p != NULL) {
        deleteEdge(&(p->edges), getNode(head, nodeID));
        p = p->next;
    }
    deleteAllEdges(getNode(head,nodeID)->edges);
    deleteNode(head, nodeID);

}

void printGraph_cmd(pnode head) {
    pnode nTmp = head->next;
    while (nTmp != NULL) {
        printf("node#%d (%p):\n", nTmp->node_id, nTmp);
        pedge eTmp = nTmp->edges;
        while (eTmp != NULL) {
            printf("\tedge: from: %d to :%d weight:%d\n", nTmp->node_id, eTmp->endpoint->node_id, eTmp->weight);
            eTmp = eTmp->next;
        }
        nTmp = nTmp->next;
    }

}

void deleteGraph_cmd(pnode *head) {
    pnode p = NULL;
    p = (*head)->next;
    while (p != NULL) {
        pedge e = p->edges;
        while (e != NULL) {
            pedge temp = e;
            e = e->next;
            free(temp);
        }
        pnode temp = p;
        p = p->next;
        free(temp);
    }
    free(*head);

}

void shortsPath_cmd(pnode head) {
    int length = head->node_id;
    int *graphMatrix = malloc(length * length * sizeof(int));
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            graphMatrix[i * length + j] = INT_MAX;
        }
    }
    pnode pN = head->next;
    while (pN != NULL) {
        pedge pE = pN->edges;
        while (pE != NULL) {
            graphMatrix[(pN->node_id * length) + pE->endpoint->node_id] = pE->weight;
            pE = pE->next;
        }
        pN = pN->next;
    }
    int sourceNode, endNode;
    scanf(" %d", &sourceNode);
    scanf(" %d", &endNode);
    int ans = dijkstra(graphMatrix, sourceNode, endNode, length);
    printf("Dijsktra shortest path: %d \n", ans);

    free(graphMatrix);
}

void TSP_cmd(pnode head) {
    int length = head->node_id;
    int *graphMatrix = malloc(length * length * sizeof(int));
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            graphMatrix[i * length + j] = INT_MAX;
        }
    }
    pnode pN = head->next;
    while (pN != NULL) {
        pedge pE = pN->edges;
        while (pE != NULL) {
            graphMatrix[(pN->node_id * (length - 1)) + pE->endpoint->node_id] = pE->weight;
            pE = pE->next;
        }
        pN = pN->next;
    }

    //TODO promition
    int minDis = -1;
    int times, sourceNode, endNode;
    scanf(" %d", &times);
    scanf(" %d", &sourceNode);
    for (int i = 0; i < times - 1; ++i) {
        scanf(" %d", &endNode);
        int ans = dijkstra(graphMatrix, sourceNode, endNode, length);
        if (ans == INT_MAX) {
            minDis = -1;
            break;
        }
        minDis += ans;
        sourceNode = endNode;
    }
    printf("TSP shortest path: %d \n", ((minDis == -1) ? minDis : minDis + 1));
    free(graphMatrix);

}






