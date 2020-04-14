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
#include <pthread.h>

#include "Msg.pb.h"

#define PPORT 8000

using namespace std;

char* server_ip = "192.168.1.10";
int myport;

queue<Msg> events;
u_int cur_clock = 0;
u_int mypid;


int safe_push(Msg m){
    int status = 0;
    
    return status;
}


Msg safe_pop(){

}


void print_events(queue<Msg> es){
    cout<<"Process "<<mypid<<" "<<"print clock: ";
    while(!es.empty()){
        cout<<es.front().clock<<" ";
        es.pop();
    }
    cout<<endl;
}



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
   
    // Assign process id
    cout << "Process id: ";
    cin >> mypid;
    
    // Build a TCP socket connecting with the network process
    myport = PPORT + mypid;
    struct sockaddr_in server_address;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed.\n");
        exit(0);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server_ip);
    server_address.sin_port = htons(myport);

    if (connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) != 0) {
        printf("Error number: %d\n", errno);
        printf("The error message is %s\n", strerror(errno));
        printf("Connection with the server failed.\n");
        exit(0);
    }

    // Open communication thread and processing thread
    pthread_t comm, proc;

    pthread_create(&comm, NULL, &commThread, NULL);

    pthread_create(&proc, NULL, &procThread, NULL);

    // A while loop taking the user input
    int type;
    string txt;
    Msg m;
    u_int pid_dest;

    cout<<"Choose  0)add local event  1)add send event  2)print clock  3)quit :";
    cin>>type;

    while(type != 3){

        // If print events
        if(type == 2){
            print_events(events);
            continue;
        }

        // Keep taking user input, creating events
        cout<<"Input event name/message: ";
        cin>>txt;

        // Create Message
        m.type = type;
        m.text = txt;

        // If input a send event
        if(type == 1){
            cout<<"Input receiver Process id: ";
            cin>>pid_dest;
            m.dst = pid_dest;
            m.src = mypid;
        }
        safe_push(m);

        // clear buf
        m.Clear();
        txt.clear();

        cout<<"Choose  0)add local event  1)add send event  2)print clock  3)quit :";
        cin>>type;
    }

    // Kill/Join proc and comm
    pthread_kill(comm,SIGKILL);
    pthread_kill(proc,SIGKILL);

    return 0;
}