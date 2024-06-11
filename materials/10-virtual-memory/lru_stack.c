#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100

typedef struct Node {
    int pageNumber;
    struct Node* prev;
    struct Node* next;
} Node;

Node* head = NULL;
Node* tail = NULL;

void moveToTop(Node* node) {
    if (node == head) return;

    if (node == tail) {
        tail = node->prev;
        tail->next = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    node->next = head;
    head->prev = node;
    node->prev = NULL;
    head = node;
}

void insertAtTop(int pageNumber) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->pageNumber = pageNumber;
    newNode->next = head;
    newNode->prev = NULL;
    
    if (head != NULL) {
        head->prev = newNode;
    }
    head = newNode;

    if (tail == NULL) {
        tail = newNode;
    }
}

Node* findPage(int pageNumber) {
    Node* current = head;
    while (current != NULL) {
        if (current->pageNumber == pageNumber) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void deleteTail() {
    if (tail == NULL) return;
    
    if (tail == head) {
        free(tail);
        head = tail = NULL;
    } else {
        Node* temp = tail;
        tail = tail->prev;
        tail->next = NULL;
        free(temp);
    }
}

void printFrames(int frameCount) {
    Node* current = head;
    for (int i = 0; i < frameCount; i++) {
        if (current != NULL) {
            printf("%d ", current->pageNumber);
            current = current->next;
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

int main() {
    int frameCount, pageCount, pageFaults = 0;
    int pages[MAX_PAGES];

    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    printf("Enter number of pages: ");
    scanf("%d", &pageCount);

    printf("Enter page references:\n");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]);
    }

    for (int i = 0; i < pageCount; i++) {
        Node* pageNode = findPage(pages[i]);
        if (pageNode != NULL) {
            moveToTop(pageNode);
        } else {
            if (frameCount == 0) {
                deleteTail();
            } else {
                frameCount--;
            }
            insertAtTop(pages[i]);
            pageFaults++;
        }
        printFrames(frameCount);
    }

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}
