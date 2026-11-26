#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#define CMAX 10  // Maximum capacity for last-minute bookings

int isCircularFull(void);                  // Check if circular queue is full
int isCircularEmpty(void);                 // Check if circular queue is empty
void enqueueCircular(int id, char name[]); // Add last-minute booking
void dequeueCircular(void);                // Process next last-minute booking
void displayCircular(void);                // Display all active bookings

#endif
