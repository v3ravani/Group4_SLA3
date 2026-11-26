#include <stdio.h>
#include <string.h>
#include "circular-queue.h"
#include "linked-list.h"
#include "hash-table.h"

static int circular_id[CMAX];        // Ticket IDs
static char circular_name[CMAX][30]; // Customer names
static int cfront = -1;              // Points to first active slot
static int crear = -1;               // Points to last occupied slot

// Check if next slot hits front
int isCircularFull(void) {
    if ((crear + 1) % CMAX == cfront) { // Next rear would collide with front
        return 1;
    }
    return 0;
}

// Returns 1 if empty, 0 otherwise
int isCircularEmpty(void) {
    if (cfront == -1) { // No active elements
        return 1;
    }
    return 0;
}

// Add last-minute booking with wrap-around
void enqueueCircular(int id, char name[]) {
    if (isCircularFull()) {
        printf("\n[Overflow] Last-Minute Queue is Full! Cannot add %s.\n", name);
        return;
    }
    if (cfront == -1) {
        cfront = 0; // Initialize front on first entry
        crear = 0;  // Initialize rear on first entry
    } else {
        crear = (crear + 1) % CMAX; // Circular increment
    }
    circular_id[crear] = id;
    strcpy(circular_name[crear], name); // Store customer string
    printf("\n[Success] Last-Minute Booking ID %d for %s added at Slot %d.\n", id, name, crear);
}

// Process booking, transfer to Linked List and Gate Hash Table
void dequeueCircular(void) {
    if (isCircularEmpty()) {
        printf("\n[Underflow] Last-Minute Queue is Empty! No express tickets to process.\n");
        return;
    }
    printf("\n[Confirmed] Last-Minute Ticket Processed: ID %d, Customer: %s (from Slot %d)\n", 
           circular_id[cfront], circular_name[cfront], cfront);

    // Add to dynamic confirmed customer list (CO2)
    addConfirmedTicket(circular_id[cfront], circular_name[cfront], "Last-Minute");

    // Register into gate lookup hash table (CO4)
    insertHashTable(circular_id[cfront], circular_name[cfront]);

    if (cfront == crear) {
        // Last element served, reset queue
        cfront = -1;
        crear = -1;
    } else {
        cfront = (cfront + 1) % CMAX; // Advance front circularly
    }
}

// Display bookings in FIFO order
void displayCircular(void) {
    if (isCircularEmpty()) {
        printf("\nLast-Minute Booking Queue is Empty.\n");
        return;
    }
    printf("\n--- Last-Minute Booking Queue (Circular Queue) ---\n");
    int i = cfront;
    while (1) {
        printf("Slot %d -> ID: %d | Name: %s\n", i, circular_id[i], circular_name[i]);
        if (i == crear) { // Reached last element
            break;
        }
        i = (i + 1) % CMAX; // Wrap around to next slot
    }
}
