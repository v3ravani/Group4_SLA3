#include <stdio.h>
#include "linear-queue.h"
#include "circular-queue.h"
#include "linked-list.h"
#include "bst.h"
#include "hash-table.h"

/*
 * Smart Event Ticket Booking System (Review 3: Final Implementation)
 * Group 4: Viraj Ravani (64), Disha Mahabdi (65), Mayuri Pawar (66)
 * Complete Course Outcomes:
 * CO1: Queues (Linear Queue & Circular Queue)
 * CO2: Linked List (Customer Confirmed Tickets)
 * CO3: Binary Search Tree (Venue Seating Sections)
 * CO4: Hash Table with Linear Probing (Gate Ticket ID Verification)
 */

int main(void) {
    int choice;              // User menu selection
    int id = 101;            // Auto-incremented ticket ID
    char name[30];           // Customer name buffer
    int search_id;           // Target ID for search, verification or cancellation
    int sec_id, seats, price;// Venue section parameters
    char sec_name[30];       // Venue section name buffer

    // Initialize BST venue sections
    struct BSTNode *venueRoot = initDefaultVenue();

    // Initialize Gate Lookup Hash Table
    initHashTable();

    while (1) {
        printf("\n======================================================\n");
        printf("    Smart Event Ticket Booking System (Review 3)       \n");
        printf("======================================================\n");
        printf("[Advance Bookings: Linear Queue (CO1)]\n");
        printf("  1. Add Regular Booking\n");
        printf("  2. Process Regular Booking (Transfers to List & Hash Table)\n");
        printf("  3. Display Regular Booking Queue\n");
        printf("\n[Rush Bookings: Circular Queue (CO1)]\n");
        printf("  4. Add Last-Minute Booking\n");
        printf("  5. Process Last-Minute Booking (Transfers to List & Hash Table)\n");
        printf("  6. Display Last-Minute Booking Queue\n");
        printf("\n[Confirmed Customer Records: Linked List (CO2)]\n");
        printf("  7. Display All Confirmed Tickets\n");
        printf("  8. Search Confirmed Ticket by ID\n");
        printf("  9. Cancel / Refund Ticket by ID\n");
        printf("\n[Venue Seating Sections: Binary Search Tree (CO3)]\n");
        printf(" 10. Display Venue Sections (In-Order by ID)\n");
        printf(" 11. Search Venue Section by ID\n");
        printf(" 12. Add New Venue Section\n");
        printf("\n[Gate Ticket ID Verification: Hash Table with Linear Probing (CO4)]\n");
        printf(" 13. Verify Ticket ID at Venue Gate (Instant Hash Lookup)\n");
        printf(" 14. Display Gate Hash Table Buckets (Shows Linear Probing)\n");
        printf(" 15. Register Ticket into Hash Table Directly\n");
        printf(" 16. Void / Remove Ticket from Hash Table\n");
        printf("\n 17. Exit Program\n");
        printf("------------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Customer Name: ");
                scanf("%s", name);
                enqueueLinear(id++, name); // Add to linear queue
                break;

            case 2:
                dequeueLinear(); // Dequeue, save to linked list, register in hash table
                break;

            case 3:
                displayLinear(); // Show regular queue
                break;

            case 4:
                printf("Enter Customer Name: ");
                scanf("%s", name);
                enqueueCircular(id++, name); // Add to circular queue
                break;

            case 5:
                dequeueCircular(); // Dequeue, save to linked list, register in hash table
                break;

            case 6:
                displayCircular(); // Show circular queue
                break;

            case 7:
                displayConfirmedTickets(); // Traverse linked list
                break;

            case 8:
                printf("Enter Ticket ID to search: ");
                scanf("%d", &search_id);
                searchConfirmedTicket(search_id); // Search linked list
                break;

            case 9:
                printf("Enter Ticket ID to cancel: ");
                scanf("%d", &search_id);
                cancelTicket(search_id); // Unlink from list and void from hash table
                break;

            case 10:
                printf("\n--- Venue Seating Hierarchy (BST In-Order) ---\n");
                inorderSections(venueRoot); // Display BST in ascending key order
                break;

            case 11:
                printf("Enter Section ID to search: ");
                scanf("%d", &sec_id);
                {
                    struct BSTNode *found = searchSection(venueRoot, sec_id);
                    if (found != NULL) {
                        printf("\n[Found] Section %d: %s | Seats: %d | Price: Rs %d\n", 
                               found->section_id, found->section_name, found->seats, found->price);
                    } else {
                        printf("\n[Not Found] Section ID %d does not exist in the venue.\n", sec_id);
                    }
                }
                break;

            case 12:
                printf("Enter Section ID: ");
                scanf("%d", &sec_id);
                printf("Enter Section Name: ");
                scanf("%s", sec_name);
                printf("Enter Seat Capacity: ");
                scanf("%d", &seats);
                printf("Enter Ticket Price (INR): ");
                scanf("%d", &price);
                venueRoot = insertSection(venueRoot, sec_id, sec_name, seats, price);
                break;

            case 13:
                printf("Scan Ticket ID at Gate: ");
                scanf("%d", &search_id);
                searchHashTable(search_id); // O(1) gate verification via linear probing
                break;

            case 14:
                displayHashTable(); // Display all buckets to inspect linear probing
                break;

            case 15:
                printf("Enter Ticket ID to register: ");
                scanf("%d", &search_id);
                printf("Enter Customer Name: ");
                scanf("%s", name);
                insertHashTable(search_id, name); // Manual insertion into hash table
                break;

            case 16:
                printf("Enter Ticket ID to void: ");
                scanf("%d", &search_id);
                deleteHashTable(search_id); // Remove from hash table
                break;

            case 17:
                printf("\nExiting system. Thank you!\n");
                return 0; // Clean exit

            default:
                printf("\nInvalid choice! Please enter a number between 1 and 17.\n");
                break;
        }
    }

    return 0;
}
