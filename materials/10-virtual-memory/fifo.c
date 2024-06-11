#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_REFERENCES 100

void printFrames(int frames[], int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == -1) {
            printf(" - ");
        } else {
            printf(" %d ", frames[i]);
        }
    }
    printf("\n");
}

int isPageInFrames(int frames[], int num_frames, int page) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int reference_string[MAX_REFERENCES] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int num_references = 22;
    int num_frames = 3;
    
    int frames[MAX_FRAMES];
    int page_faults = 0;
    int next_replace = 0;  // Points to the next frame to replace
    
    // Initialize frames with -1 indicating empty frame
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }
    
    printf("Reference String: ");
    for (int i = 0; i < num_references; i++) {
        printf("%d ", reference_string[i]);
    }
    printf("\n\nFrames:\n");

    for (int i = 0; i < num_references; i++) {
        int current_page = reference_string[i];
        printf("Ref: %d => ", current_page);
        
        if (!isPageInFrames(frames, num_frames, current_page)) {
            frames[next_replace] = current_page;
            next_replace = (next_replace + 1) % num_frames;
            page_faults++;
        }
        
        printFrames(frames, num_frames);
    }
    
    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}
