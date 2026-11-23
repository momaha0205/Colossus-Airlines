# Colossus Airlines Reservation System

## Problem Statement
Colossus Airlines needs a reservation system to manage seating for four daily flights. Each flight has 128 seats. The program must allow users to view available seats, assign passengers, delete reservations, and display passengers alphabetically.

## Describe Solution
I developed a reservation system in C using structures, arrays, functions, and menus.

The program manages four flights: 101, 102, 201, and 202. Each flight has its own 128 seats.

Each seat stores its seat number, assignment status, passenger first name, and passenger last name.

The system allows users to:
- Select outbound or inbound flights
- Choose a flight number
- Count available seats
- Display available seat numbers
- View passengers alphabetically
- Assign customers to seats
- Delete seat assignments
- Cancel reservation operations

The program also checks for invalid seat numbers and prevents duplicate reservations.

## Pros and Cons

### Pros
- Simple menu-based interface
- Supports four independent flights
- Prevents duplicate seat assignments
- Allows reservation cancellations
- Organizes code into separate functions
- Displays passengers alphabetically

### Cons
- Reservations are not saved after the program closes
- Flight numbers and seat counts are fixed
- Passenger names have a limited length
- No graphical interface

## How to Run

Compile:

gcc -Wall -Wextra solution.c -o solution

Run:

./solution

## Screenshots
Screenshots of the program are stored in the screenshots folder.
