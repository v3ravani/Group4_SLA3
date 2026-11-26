#include <stdio.h>
#include <string.h>
#include "hash-table.h"

// Static hash table storage
static struct HashEntry hashTable[HASH_SIZE];

// Initialize all slots in the hash table to empty
void initHashTable(void) {
    for (int i = 0; i < HASH_SIZE; i++) {
        hashTable[i].ticket_id = -1;
        hashTable[i].customer_name[0] = '\0';
        hashTable[i].is_occupied = 0;
    }
}

// Hash function using simple modulo division
int hashFunction(int ticket_id) {
    return ticket_id % HASH_SIZE;
}

// Insert ticket ID using linear probing for collision resolution
int insertHashTable(int ticket_id, char name[]) {
    int index = hashFunction(ticket_id);
    int start_index = index;

    // Linear probing if current slot is occupied
    while (hashTable[index].is_occupied) {
        // Check for duplicate key
        if (hashTable[index].ticket_id == ticket_id) {
            printf("\n[Warning] Ticket ID %d is already registered at Gate!\n", ticket_id);
            return 0;
        }

        // Move to next slot circularly
        index = (index + 1) % HASH_SIZE;

        // If we circled back to starting slot, table is full
        if (index == start_index) {
            printf("\n[Overflow] Gate Hash Table is Full! Cannot insert ticket %d.\n", ticket_id);
            return 0;
        }
    }

    // Place ticket into the found empty slot
    hashTable[index].ticket_id = ticket_id;
    strcpy(hashTable[index].customer_name, name);
    hashTable[index].is_occupied = 1;

    printf("\n[Gate Registered] Ticket ID %d for %s mapped to Hash Slot %d.\n", 
           ticket_id, name, index);
    return 1;
}

// Search and authenticate ticket ID at venue gate in O(1) average time
int searchHashTable(int ticket_id) {
    int index = hashFunction(ticket_id);
    int start_index = index;
    int probes = 1;

    // Linear probe through occupied slots
    while (hashTable[index].is_occupied) {
        if (hashTable[index].ticket_id == ticket_id) {
            printf("\n==============================================\n");
            printf("   GATE ENTRY VERIFICATION: TICKET VALID      \n");
            printf("==============================================\n");
            printf(" Ticket ID      : %d\n", hashTable[index].ticket_id);
            printf(" Customer Name  : %s\n", hashTable[index].customer_name);
            printf(" Hash Bucket    : Slot %d (Total Probes: %d)\n", index, probes);
            printf(" Gate Status    : ACCESS GRANTED\n");
            printf("==============================================\n");
            return 1;
        }

        index = (index + 1) % HASH_SIZE;
        probes++;

        // Stop if we have probed the entire table
        if (index == start_index) {
            break;
        }
    }

    // Ticket ID not found
    printf("\n[Gate Entry: INVALID] Ticket ID %d not found in Hash Table! Access Denied.\n", ticket_id);
    return 0;
}

// Remove or void a ticket from the gate lookup table
int deleteHashTable(int ticket_id) {
    int index = hashFunction(ticket_id);
    int start_index = index;

    while (hashTable[index].is_occupied) {
        if (hashTable[index].ticket_id == ticket_id) {
            printf("\n[Hash Table] Ticket ID %d for %s removed from Gate Slot %d.\n", 
                   ticket_id, hashTable[index].customer_name, index);
            hashTable[index].ticket_id = -1;
            hashTable[index].customer_name[0] = '\0';
            hashTable[index].is_occupied = 0;
            return 1;
        }

        index = (index + 1) % HASH_SIZE;
        if (index == start_index) {
            break;
        }
    }

    printf("\n[Not Found] Ticket ID %d is not present in Gate Hash Table.\n", ticket_id);
    return 0;
}

// Display all hash buckets showing keys and occupied slots
void displayHashTable(void) {
    printf("\n--- Gate Ticket ID Lookup Table (Hash Table with Linear Probing) ---\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hashTable[i].is_occupied) {
            printf("Bucket [%d] -> Ticket ID: %-4d | Customer: %-15s [Active Pass]\n", 
                   i, hashTable[i].ticket_id, hashTable[i].customer_name);
        } else {
            printf("Bucket [%d] -> [Empty Slot]\n", i);
        }
    }
}
