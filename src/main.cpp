#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include "ethframe.h"
#include "udpsender.h"
using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 6)
    {
        cout << "Oops!! Invalid parameters!!!\n"; 
        printf("Usage: sudo %s <src hostname/IP> <source port> <dst hostname/IP> <dst port> <data>\n", argv[0]);
        return 0;
    }

    printf("Start Udp Sender\n");

    UDP_Sender *udps = new UDP_Sender(argv[1], atoi(argv[2]), argv[3], atoi(argv[4]), argv[5]);
    udps->prepare_udp();
    udps->display();

    udps->send_udp();

    udps->close_udp();
    return 0;
}