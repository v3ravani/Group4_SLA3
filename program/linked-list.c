#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked-list.h"
#include "hash-table.h"

// Head pointer for confirmed customer ticket list
static struct TicketNode *head = NULL;

// Add confirmed ticket at the end of the list
void addConfirmedTicket(int id, char name[], char booking_type[]) {
    struct TicketNode *newNode = (struct TicketNode *)malloc(sizeof(struct TicketNode));
    if (newNode == NULL) {
        printf("\n[Error] Memory allocation failed!\n");
        return;
    }

    newNode->id = id;
    strcpy(newNode->name, name);
    strcpy(newNode->booking_type, booking_type);
    newNode->next = NULL;

    // If list is empty, new node becomes head
    if (head == NULL) {
        head = newNode;
    } else {
        // Traverse to the last node
        struct TicketNode *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    printf("\n[Confirmed List] Ticket ID %d for %s (%s) saved.\n", id, name, booking_type);
}

// Display all confirmed tickets in linked list
void displayConfirmedTickets(void) {
    if (head == NULL) {
        printf("\nConfirmed Ticket List is Empty.\n");
        return;
    }

    printf("\n--- Confirmed Customer Tickets (Linked List) ---\n");
    struct TicketNode *temp = head;
    int count = 1;
    while (temp != NULL) {
        printf("Record %d -> ID: %d | Customer: %s | Type: %s\n", 
               count, temp->id, temp->name, temp->booking_type);
        temp = temp->next;
        count++;
    }
}

// Search for a confirmed ticket by ID
int searchConfirmedTicket(int id) {
    if (head == NULL) {
        printf("\nConfirmed Ticket List is Empty.\n");
        return 0;
    }

    struct TicketNode *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("\n[Found] Ticket ID %d belongs to %s (%s Booking).\n", 
                   temp->id, temp->name, temp->booking_type);
            return 1;
        }
        temp = temp->next;
    }

    printf("\n[Not Found] Ticket ID %d does not exist in confirmed list.\n", id);
    return 0;
}

// Cancel a ticket by deleting its node from the linked list and voiding hash entry
void cancelTicket(int id) {
    if (head == NULL) {
        printf("\n[Error] Confirmed Ticket List is Empty! Nothing to cancel.\n");
        return;
    }

    struct TicketNode *temp = head;
    struct TicketNode *prev = NULL;

    // Case 1: First node needs to be deleted
    if (temp != NULL && temp->id == id) {
        head = temp->next; // Move head to next node
        printf("\n[Cancelled] Ticket ID %d for %s has been refunded and removed.\n", 
               temp->id, temp->name);
        free(temp); // Free allocated memory
        deleteHashTable(id); // Void gate pass from hash table
        return;
    }

    // Case 2: Search for the node to delete
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If ticket was not found
    if (temp == NULL) {
        printf("\n[Not Found] Cannot cancel! Ticket ID %d is not in the list.\n", id);
        return;
    }

    // Unlink the node and free memory
    prev->next = temp->next;
    printf("\n[Cancelled] Ticket ID %d for %s has been refunded and removed.\n", 
           temp->id, temp->name);
    free(temp);
    deleteHashTable(id); // Void gate pass from hash table
}

// Return total number of confirmed tickets
int countConfirmedTickets(void) {
    int count = 0;
    struct TicketNode *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}
