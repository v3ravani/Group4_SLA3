# Smart Event Ticket Booking System (Review 3)

Data Structures Micro-Project for Course Outcome verification (CO1, CO2, CO3, CO4).

## Team Members (Group 4)
* Viraj Ravani (Roll No. 64, PRN: 126BTCM2004)
* Disha Mahabdi (Roll No. 65, PRN: 126BTCM2011)
* Mayuri Pawar (Roll No. 66, PRN: 126BTCM2014)

## Architecture Overview
* **CO1 (Queues)**: Linear queue for advance bookings and circular queue for rush bookings.
* **CO2 (Linked List)**: Singly linked list for confirmed customer records and dynamic cancellations.
* **CO3 (Binary Search Tree)**: Hierarchical venue seating sections with in-order sorted traversal.
* **CO4 (Hash Table)**: Fast ticket verification at entrance gates using linear probing.

## Project Structure
* `program/`: C source code, headers, and compiled executable.
* `pdf report/`: Complete 37-page project documentation report.

## How to Compile and Run
Navigate into the `program` folder and run:
```bash
gcc -Wall -Wextra -O2 main.c linear-queue.c circular-queue.c linked-list.c bst.c hash-table.c -o ticket_system.exe
./ticket_system.exe
```
