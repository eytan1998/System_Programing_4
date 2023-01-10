

#include "nodes.h"

pnode addNode(pnode *head, pnode newNode) {

    newNode->next = (*head)->next;
    (*head)->next = newNode;
    return newNode;
}

pnode getNode(pnode *head, int index) {
    pnode ans = (*head)->next;
    while (ans != NULL) {
        if (ans->node_id == index) return ans;
        ans = ans->next;
    }
    return NULL;
}

void deleteNode(pnode *nodes, int key) {
    pnode temp;
    pnode prev;
    temp = *nodes;
    prev = *nodes;
    while (temp != NULL) {
        if (temp == *nodes && key == prev->node_id) {
            *nodes = (*nodes)->next;
            free(temp);
            break;
        } else {
            if (temp->node_id == key) {
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

