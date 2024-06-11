#include <stdio.h>
#include <limits.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

typedef struct {
    int pageNumber;
    int lastUsed;
} Page;

int findLRU(Page pages[], int frameCount) {
    int i, min = pages[0].lastUsed, pos = 0;
    for (i = 1; i < frameCount; i++) {
        if (pages[i].lastUsed < min) {
            min = pages[i].lastUsed;
            pos = i;
        }
    }
    return pos;
}

int main() {
    int frames[MAX_FRAMES], pages[MAX_PAGES];
    int frameCount, pageCount, counter = 0, pageFaults = 0;
    Page pageTable[MAX_FRAMES];

    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    printf("Enter number of pages: ");
    scanf("%d", &pageCount);

    printf("Enter page references:\n");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]);
    }

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        pageTable[i].pageNumber = -1;
        pageTable[i].lastUsed = INT_MAX;
    }

    for (int i = 0; i < pageCount; i++) {
        int found = 0;
        for (int j = 0; j < frameCount; j++) {
            if (pageTable[j].pageNumber == pages[i]) {
                pageTable[j].lastUsed = counter++;
                found = 1;
                break;
            }
        }
        if (!found) {
            int pos = findLRU(pageTable, frameCount);
            pageTable[pos].pageNumber = pages[i];
            pageTable[pos].lastUsed = counter++;
            pageFaults++;
        }

        printf("Frames: ");
        for (int j = 0; j < frameCount; j++) {
            if (pageTable[j].pageNumber != -1)
                printf("%d ", pageTable[j].pageNumber);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}
