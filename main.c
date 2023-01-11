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
    deleteAllEdges(getNode(head, nodeID)->edges);
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

    int sourceNode, endNode;
    scanf(" %d", &sourceNode);
    scanf(" %d", &endNode);
    int ans = dijkstra(head, sourceNode, endNode);
    printf("Dijsktra shortest path: %d \n", ans);

}

void TSP_cmd(pnode head) {

    //TODO promition
    int numStations;
    scanf(" %d", &numStations);
    int *stations = malloc(numStations * sizeof(int));

    int allMin = -1;
    int currentMin = -1;
    int i, j, k, temp;
    for (i = 0; i < numStations; i++)
        scanf(" %d", &stations[i]);
    for (j = 1; j <= numStations; j++) {
        for (i = 0; i < numStations - 1; i++) {
            temp = stations[i];
            stations[i] = stations[i + 1];
            stations[i + 1] = temp;

            for (k = 0; k < numStations - 1; k++){
                int ans = dijkstra(head, stations[k], stations[k + 1]);
                if (ans == -1){
                    currentMin = -1;
                    break;
                }
                currentMin += ans;
            }
            if(currentMin != -1 && (allMin == -1 ||currentMin < allMin)){
                allMin = currentMin;
            }
        }
    }
    free(stations);
    printf("TSP shortest path: %d \n", ((allMin == -1) ? allMin : allMin + 1));

}






