#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

// Insert a section into the BST (allocates new node directly when root is NULL)
struct BSTNode* insertSection(struct BSTNode *root, int section_id, char name[], int seats, int price) {
    // If current tree or subtree is empty, allocate and return new node directly
    if (root == NULL) {
        struct BSTNode *newNode = (struct BSTNode *)malloc(sizeof(struct BSTNode));
        if (newNode == NULL) {
            printf("\n[Error] Memory allocation failed for BST Node!\n");
            return NULL;
        }

        newNode->section_id = section_id;
        strcpy(newNode->section_name, name);
        newNode->seats = seats;
        newNode->price = price;
        newNode->left = NULL;
        newNode->right = NULL;
        printf("\n[Success] Section %d (%s) inserted into BST.\n", section_id, name);
        return newNode;
    }

    // Go left if key is smaller
    if (section_id < root->section_id) {
        root->left = insertSection(root->left, section_id, name, seats, price);
    }
    // Go right if key is larger
    else if (section_id > root->section_id) {
        root->right = insertSection(root->right, section_id, name, seats, price);
    }
    // Duplicate key check
    else {
        printf("\n[Warning] Section ID %d already exists! Cannot insert duplicate.\n", section_id);
    }

    return root;
}

// Search for a section by section_id in O(log n) average time
struct BSTNode* searchSection(struct BSTNode *root, int section_id) {
    // Base cases: root is null or key is present at root
    if (root == NULL || root->section_id == section_id) {
        return root;
    }

    // Key is smaller than root's key: search left
    if (section_id < root->section_id) {
        return searchSection(root->left, section_id);
    }

    // Key is greater than root's key: search right
    return searchSection(root->right, section_id);
}

// In-order traversal displays sections sorted by Section ID
void inorderSections(struct BSTNode *root) {
    if (root == NULL) {
        return;
    }

    inorderSections(root->left); // Visit left subtree
    printf("Section %-3d | Name: %-15s | Seats: %-4d | Price: Rs %d\n", 
           root->section_id, root->section_name, root->seats, root->price);
    inorderSections(root->right); // Visit right subtree
}

// Pre-load default stadium / hall sections
struct BSTNode* initDefaultVenue(void) {
    struct BSTNode *root = NULL;
    // Insert root first (Section 20: Stall)
    root = insertSection(root, 20, "Stall", 50, 300);
    // Insert left subtree (Section 10: VIP Lounge)
    root = insertSection(root, 10, "VIP Lounge", 20, 1200);
    // Insert right subtree (Section 30: Balcony)
    root = insertSection(root, 30, "Balcony", 40, 500);
    // Insert farther right (Section 40: General Stands)
    root = insertSection(root, 40, "General Stands", 100, 150);
    return root;
}
