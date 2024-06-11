#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TLB_SIZE 4  // Size of the TLB (for simplicity, using a small size)
#define PAGE_TABLE_SIZE 8  // Size of the page table

typedef struct {
    int page_number;
    int frame_number;
    int asid;  // Address Space Identifier
    bool valid;
} TLBEntry;

typedef struct {
    int frame_number;
    bool valid;
} PageTableEntry;

TLBEntry tlb[TLB_SIZE];
PageTableEntry page_table[PAGE_TABLE_SIZE];

// Function to initialize the TLB
void initialize_tlb() {
    for (int i = 0; i < TLB_SIZE; i++) {
        tlb[i].valid = false;
    }
}

// Function to initialize the page table
void initialize_page_table() {
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i].frame_number = i;
        page_table[i].valid = true;
    }
}

// Function to check TLB for a page number and ASID
int tlb_lookup(int page_number, int asid) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb[i].valid && tlb[i].page_number == page_number && tlb[i].asid == asid) {
            return tlb[i].frame_number;
        }
    }
    return -1; // TLB miss
}

// Function to handle a TLB miss
void handle_tlb_miss(int page_number, int asid) {
    // Find a free entry or use a replacement policy (e.g., FIFO)
    static int next_free_entry = 0;
    int entry_index = next_free_entry % TLB_SIZE;

    // Load the page table entry into the TLB
    tlb[entry_index].page_number = page_number;
    tlb[entry_index].frame_number = page_table[page_number].frame_number;
    tlb[entry_index].asid = asid;
    tlb[entry_index].valid = true;

    next_free_entry++;
}

// Function to access a memory address (simulated)
void access_memory(int page_number, int asid) {
    int frame_number = tlb_lookup(page_number, asid);
    if (frame_number != -1) {
        printf("TLB hit: Page %d -> Frame %d\n", page_number, frame_number);
    } else {
        printf("TLB miss: Page %d\n", page_number);
        handle_tlb_miss(page_number, asid);
        frame_number = tlb_lookup(page_number, asid);
        printf("Loaded into TLB: Page %d -> Frame %d\n", page_number, frame_number);
    }
}

int main() {
    initialize_tlb();
    initialize_page_table();

    // Simulate memory accesses
    access_memory(0, 1); // TLB miss, load into TLB
    access_memory(1, 1); // TLB miss, load into TLB
    access_memory(0, 1); // TLB hit
    access_memory(2, 1); // TLB miss, load into TLB
    access_memory(3, 1); // TLB miss, load into TLB
    access_memory(1, 1); // TLB hit
    access_memory(4, 1); // TLB miss, load into TLB (replace entry)

    return 0;
}
