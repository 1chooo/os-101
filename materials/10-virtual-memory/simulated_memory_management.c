#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Define the size of the page table and memory
#define PAGE_TABLE_SIZE 8
#define MEMORY_SIZE 4

// Simulated page table entry
typedef struct {
    int frame_number;
    bool valid;
} PageTableEntry;

// Simulated memory structure
int memory[MEMORY_SIZE];

// Simulated page table
PageTableEntry page_table[PAGE_TABLE_SIZE];

// Function to initialize the page table
void initialize_page_table() {
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i].frame_number = -1;  // -1 indicates the page is not in memory
        page_table[i].valid = false;
    }
}

// Function to simulate fetching a page into memory
void fetch_page(int page_number) {
    if (page_table[page_number].valid) {
        printf("Page %d is already in memory.\n", page_number);
        return;
    }
    // Simulate bringing the page into memory
    int frame_number = rand() % MEMORY_SIZE;
    page_table[page_number].frame_number = frame_number;
    page_table[page_number].valid = true;
    memory[frame_number] = page_number;  // Simulate the content
    printf("Page %d loaded into frame %d.\n", page_number, frame_number);
}

// Function to fetch the value at a given page
int fetch_value(int page_number) {
    if (!page_table[page_number].valid) {
        fetch_page(page_number);  // Handle page fault
    }
    int frame_number = page_table[page_number].frame_number;
    return memory[frame_number];  // Return the value from memory
}

// Function to add values and handle a page fault on store
void add_and_store(int pageA, int pageB, int pageC) {
    printf("Fetching instruction: ADD\n");
    printf("Fetching A from page %d.\n", pageA);
    int A = fetch_value(pageA);

    printf("Fetching B from page %d.\n", pageB);
    int B = fetch_value(pageB);

    int sum = A + B;
    printf("Adding A and B to get %d.\n", sum);

    if (!page_table[pageC].valid) {
        printf("Page fault when trying to store in page %d.\n", pageC);
        fetch_page(pageC);  // Handle page fault
    }

    int frame_number = page_table[pageC].frame_number;
    memory[frame_number] = sum;
    printf("Stored %d in page %d (frame %d).\n", sum, pageC, frame_number);
}

int main() {
    initialize_page_table();

    // Simulate pages containing values
    fetch_page(0);  // Assume page 0 has value 10
    fetch_page(1);  // Assume page 1 has value 20
    memory[page_table[0].frame_number] = 10;
    memory[page_table[1].frame_number] = 20;

    // Add values from page 0 and page 1, store result in page 2
    add_and_store(0, 1, 2);

    return 0;
}
