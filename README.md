# Computer Networks | CS425

This repository contains my Computer Networks coursework, covering error detection, IPv4 packet analysis, routing algorithms, and UDP client-server communication using C++.

## Assignments

### Homework 1: Error Detection and Data Link Layer
- Implemented **Cyclic Redundancy Check (CRC)** in C++ for error detection.
- Studied CRC calculations, Go-Back-N and Selective Repeat ARQ, Stop-and-Wait efficiency, and frame-error probability.

### Homework 2: IPv4 Packet Analysis
- Studied IPv4 header fields, including protocol numbers, header length, total length, TTL, and fragmentation.
- Analyzed packet identification, fragmentation flags, and fragment offsets.

### Homework 3: Routing Algorithms and Socket Programming
- Implemented **Dijkstra's algorithm** for link-state routing and **Bellman-Ford** for distance-vector routing.
- Developed a **UDP client-server application** in C++ for message exchange and acknowledgements.

## Technologies
- **Language:** C++
- **Networking:** CRC, IPv4, routing algorithms, UDP sockets
- **Tools:** g++, Linux/Unix socket APIs

## Repository Structure

```text
Computer-Networks/
├── Networks Homework-1/
├── Networks Homework-2/
├── Networks Homework-3/
└── README.md
```

## Running the Programs

Compile the C++ source files using `g++`. For example:

```bash
g++ -std=c++17 CRC.cpp -o crc
./crc
```

For the routing and UDP programs, navigate to the corresponding assignment and source-code folder before compiling.

The UDP client and server should be started in separate terminals. The server should be running before the client sends messages.
