//Gabriel Espinosa
#include "list.h"

void add(LIST **head, LIST **tail, void *data) {
    if (*tail == NULL) {
        *head = *tail = (LIST *) malloc(sizeof(LIST));
        (*head)->data = data;
        (*head)->next = NULL;
    } else {
        (*tail)->next = (LIST *) malloc(sizeof(LIST));
        *tail = (*tail)->next;
        (*tail)->data = data;
        (*tail)->next = NULL;
    }
}

void clearIteratively(LIST **head, LIST **tail) {
    if (*head == NULL)
        return;

    LIST *currNode = *head;
    LIST *nextNode = NULL;
    do {
        nextNode = currNode->next;

        if (currNode->data != NULL)
            free(currNode->data);

        free(currNode);

        currNode = nextNode;

    } while (currNode != NULL);

    *head = NULL;
    *tail = NULL;
}

void clearRecursively(LIST **currNode, LIST **tail) {
    if (*currNode == NULL)
        return;


    LIST *nextNode;

    // TODO Complete this function

    nextNode = (*currNode)->next;

    if ((*currNode)->data != NULL) { // If there are elements to traverse to free them
        free((*currNode)->data);
    }
    free(*currNode);

    clearRecursively(&nextNode, tail);
    //clearIteratively(&nextNode, tail);

    *currNode = NULL;
    *tail = NULL;

}

void delete(LIST **head, LIST **tail, void *data) {
    if (*head == NULL)
        return;

    if (data == NULL)
        return;

    if ((*head)->data == data) {
        LIST *newHead = (*head)->next;
        free((*head)->data);
        free(*head);
        *head = newHead;

        if (*head == NULL)
            *tail = NULL;

        return;
    }

    LIST *prevNode, *currNode;

    prevNode = (*head);
    currNode = (*head)->next;
    // TODO Complete this function
    while (currNode != NULL) {
        // Checking if the current node contains
        // the same data as the one we're looking for
        // If it does free it
        if (currNode->data == data) {
            //free(currNode->data);
            prevNode->next = currNode->next;
            // This one checks if that node we're deleting is the last node
            // If it is point the tail to the node behind it
            if (currNode->next == NULL) {
                *tail = prevNode;
            }
            free(currNode->data);
            free(currNode);
            break;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
}