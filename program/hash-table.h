#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define HASH_SIZE 10 // Fixed table size for gate verification

// Entry representing a ticket record in the hash table
struct HashEntry {
    int ticket_id;           // Ticket ID key (-1 if empty)
    char customer_name[30];  // Customer name
    int is_occupied;         // 1 if slot has a ticket, 0 if empty
};

// Function prototypes
void initHashTable(void);
int hashFunction(int ticket_id);
int insertHashTable(int ticket_id, char name[]);
int searchHashTable(int ticket_id);
int deleteHashTable(int ticket_id);
void displayHashTable(void);

#endif
