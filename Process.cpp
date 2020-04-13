#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h> 
#include <errno.h>

// An event struct which is inserted in the queue
struct Event{
    // The type of events, 0 for send event, 1 for receive event, 2 for other events
    u_int type;
    // For send and receive event, set the message. Else, set it to ""
    std::string message;
};

void *procThread(void* arg) {
    // parameters: *arg: 1. contains a queue pointer.
    // functionality: check if the queue is empty. If not, pop the events, print them, and calculate the new clock value.
}

void *commThread(void* arg) {
    // parameters: *arg: 1. should contain a queue pointer. Insert the receive event to this queue
                      // 2. a pointer of sockfd built in main thread
    // functionality: listen and receive from the socket. Add a receive event to the queue if received
}

int main() {
    // Create a new queue for events and a clock
    std::queue<Event> events;
    u_int clock = 0;

    // Assign process id
    std::cout << "Process #: ";
    std::string pid;
    std::cin >> pid;
    pid = "Process " + pid;

    // Build a TCP socket connecting with the network process to send and receive

    // Open communication thread and processing thread
    pthread_t comm, proc;
    // Assign the corresponging arg and open the threads

    // A while loop taking the user input

    return 0;
}