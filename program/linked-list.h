#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// Node structure for confirmed customer tickets
struct TicketNode {
    int id;                   // Unique ticket ID
    char name[30];            // Customer name
    char booking_type[15];    // "Regular" or "Last-Minute"
    struct TicketNode *next;  // Pointer to next ticket
};

// Function prototypes
void addConfirmedTicket(int id, char name[], char booking_type[]);
void displayConfirmedTickets(void);
int searchConfirmedTicket(int id);
void cancelTicket(int id);
int countConfirmedTickets(void);

#endif
