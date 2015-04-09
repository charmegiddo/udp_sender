#ifndef __UDPSENDER_H__
#define __UDPSENDER_H__
#include <iostream>
#include <ethframe.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

// The packet length
#define PCKT_LEN 8192
using namespace std;
class UDP_Sender : public CEthFrame{

public:
    void display();
    void create_socket();
    void create_packet();
    void send_udp();
    void prepare_udp();
    void close_udp();
    UDP_Sender(string _src_ip, int _src_port, string _dst_ip, int _dst_port, string _data);

    //
    std::string to_string();

    // Function for checksum calculation. From the RFC,
    u_short csum(unsigned short *buf, int nwords);

    private:
    // FIELD
    char buffer[PCKT_LEN];
    string src_ip;
    string dst_ip; 
    string data;
    int src_port;
    int dst_port; 

    int data_len;
    int sd;

    int one;
    int *val;
    
    // Source and destination addresses: IP and port
    struct sockaddr_in sin, din;

    // Our own headers' structures
    struct ipv4 *ip;
    struct udpheader *udp;

};

#endif