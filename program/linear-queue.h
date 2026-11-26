#ifndef LINEAR_QUEUE_H
#define LINEAR_QUEUE_H

#define MAX 10  // Maximum capacity for regular bookings

int isLinearFull(void);                  // Check if queue is full
int isLinearEmpty(void);                 // Check if queue is empty
void enqueueLinear(int id, char name[]); // Add booking to regular queue
void dequeueLinear(void);                // Process next booking in queue
void displayLinear(void);                // Display all active bookings

#endif
