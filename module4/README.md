# Colossus Airlines Reservation System - Module 4

## Problem Statement

The Module 3 airline reservation system stored passenger
information only while the program was running. Once the
program closed, all reservations were lost.

Module 4 extends the program using File I/O so reservations
remain available after the program terminates.

## Describe the Solution

The program uses C structures and arrays to manage 128
seats across four flights: 101, 102, 201, and 202.

The program allows users to:
- Select outbound and inbound flights
- View available seats
- Assign passengers to seats
- Delete reservations
- Display passengers alphabetically
- Cancel reservation operations

File I/O was added using fopen(), fwrite(), fread(),
and fclose().

Reservations are stored in a binary file named
reservations.dat.

When the program starts, it loads existing reservations
from the file. When a reservation is assigned or deleted,
the updated information is saved automatically.

## Pros and Cons

### Pros
- Reservations persist after restarting the program
- Supports four independent flights
- Automatically saves reservation changes
- Prevents duplicate seat assignments
- Uses functions to organize the program
- Provides a simple menu-based interface

### Cons
- Uses a fixed number of flights and seats
- Passenger names have a limited length
- Binary data is not human-readable
- No graphical user interface

## How to Run

Compile:

gcc -Wall -Wextra solution.c -o solution

Run:

./solution

Run the program from the module4 directory so it can
find or create reservations.dat.

## Testing

The program was tested by assigning John Smith to seat
10 on Flight 101 and closing the program.

After restarting, the program successfully loaded the
saved reservation and displayed 127 empty seats.

This confirms that reservation information persists
between program executions.

## Screenshots

Screenshots demonstrating the program's inputs and
outputs are included in the screenshots folder.
