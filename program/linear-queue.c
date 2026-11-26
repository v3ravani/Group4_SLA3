#include <stdio.h>
#include <string.h>
#include "linear-queue.h"
#include "linked-list.h"
#include "hash-table.h"

static int linear_id[MAX];        // Ticket IDs
static char linear_name[MAX][30]; // Customer names
static int front = -1;            // Points to first element
static int rear = -1;             // Points to last element

// Returns 1 if full, 0 otherwise
int isLinearFull(void) {
    if (rear == MAX - 1) { // Last index reached
        return 1;
    }
    return 0;
}

// Returns 1 if empty, 0 otherwise
int isLinearEmpty(void) {
    if (front == -1 || front > rear) { // Uninitialized or all served
        return 1;
    }
    return 0;
}

// Add regular booking at rear
void enqueueLinear(int id, char name[]) {
    if (isLinearFull()) {
        printf("\n[Overflow] Regular Booking Queue is Full! Cannot add %s.\n", name);
        return;
    }
    if (front == -1) {
        front = 0; // First element inserted
    }
    rear++;
    linear_id[rear] = id;
    strcpy(linear_name[rear], name); // Store customer string
    printf("\n[Success] Booking ID %d for %s added to Regular Queue.\n", id, name);
}

// Process booking from front, transfer to Linked List and Gate Hash Table
void dequeueLinear(void) {
    if (isLinearEmpty()) {
        printf("\n[Underflow] Regular Booking Queue is Empty! No tickets to process.\n");
        return;
    }
    printf("\n[Confirmed] Regular Ticket Processed: ID %d, Customer: %s\n", 
           linear_id[front], linear_name[front]);

    // Add to dynamic confirmed customer list (CO2)
    addConfirmedTicket(linear_id[front], linear_name[front], "Regular");

    // Register into gate lookup hash table (CO4)
    insertHashTable(linear_id[front], linear_name[front]);

    front++; // Advance to next customer

    // Reset pointers once all items are dequeued
    if (front > rear) {
        front = -1;
        rear = -1;
    }
}

// Display active regular bookings
void displayLinear(void) {
    if (isLinearEmpty()) {
        printf("\nRegular Booking Queue is Empty.\n");
        return;
    }
    printf("\n--- Regular Booking Queue (Linear Queue) ---\n");
    for (int i = front; i <= rear; i++) {
        printf("Position %d -> ID: %d | Name: %s\n", (i - front + 1), linear_id[i], linear_name[i]);
    }
}
