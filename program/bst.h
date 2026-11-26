#ifndef BST_H
#define BST_H

// Node structure for venue seating section
struct BSTNode {
    int section_id;           // Section ID key (e.g. 10, 20, 30)
    char section_name[30];    // Section name (e.g. "VIP Lounge", "Stall")
    int seats;                // Total available seats
    int price;                // Ticket price in INR
    struct BSTNode *left;     // Left child (smaller section IDs)
    struct BSTNode *right;    // Right child (larger section IDs)
};

// Function prototypes
struct BSTNode* insertSection(struct BSTNode *root, int section_id, char name[], int seats, int price);
struct BSTNode* searchSection(struct BSTNode *root, int section_id);
void inorderSections(struct BSTNode *root);
struct BSTNode* initDefaultVenue(void);

#endif
