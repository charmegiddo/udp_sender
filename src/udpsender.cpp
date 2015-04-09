#include "udpsender.h"
#include <iomanip>

std::string UDP_Sender::to_string(){
    return "UDP Sender";
}

void UDP_Sender::prepare_udp(){
    create_socket();
    create_packet();

}

void UDP_Sender::create_socket(){
    // Create a raw socket with UDP protocol
    sd = socket(PF_INET, SOCK_RAW, IPPROTO_UDP);
    if(sd < 0)
    {
        perror("socket() error");
        // If something wrong just exit
        return;
    }else{
        printf("socket() - Using SOCK_RAW socket and UDP protocol is OK.\n");
    }

    // The source is redundant, may be used later if needed
    // The address family
    sin.sin_family = AF_INET;
    din.sin_family = AF_INET;
    
    // Port numbers
    sin.sin_port = htons(src_port);
    din.sin_port = htons(dst_port);
    
    // IP addresses
    sin.sin_addr.s_addr = inet_addr(src_ip.c_str());
    din.sin_addr.s_addr = inet_addr(dst_ip.c_str());

    //BSD
    sin.sin_len = sizeof(sin);
    din.sin_len = sizeof(din);

}

void UDP_Sender::close_udp(){
    close(sd);
}

void UDP_Sender::send_udp(){
    // Inform the kernel do not fill up the packet structure. we will build our own...
    if(setsockopt(sd, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0)
    {
        perror("setsockopt() error");
        return;
    }

    // Verify
    if(sendto(sd, buffer, ip->ip_len, 0, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("sendto() error");
    }
    else
    {
        cout << "udp sent\n";
    }
}

void UDP_Sender::create_packet(){
    data_len = data.size();
   // Fabricate the IP header or we can use the
    // standard header structures but assign our own values.
    ip->ip_ihl = 5;
    ip->ip_ver = 4;
    ip->ip_tos = 16; // Low delay
    ip->ip_len = sizeof(struct ipv4) + sizeof(struct udpheader) + data_len;
    ip->ip_id = htons(54321);
    ip->ip_ttl = 64; // hops
    ip->ip_p = 17; // UDP
    // Source IP address, can use spoofed address here!!!
    ip->ip_src = inet_addr(src_ip.c_str());
    // The destination IP address
    ip->ip_dst = inet_addr(dst_ip.c_str());
    // Fabricate the UDP header. Source port number, redundant
    udp->udp_srcport = htons(src_port);
    // Destination port number
    udp->udp_destport = htons(dst_port);
    udp->udp_len = htons(sizeof(struct udpheader) + data_len);
    // Calculate the checksum for integrity
    ip->ip_sum = csum((u_short *)buffer, sizeof(struct ipv4) + sizeof(struct udpheader) + data_len);
    memcpy(buffer + sizeof(struct ipv4) + sizeof(struct udpheader), data.c_str(), data_len * sizeof (char));
}

UDP_Sender::UDP_Sender(string _src_ip, int _src_port, string _dst_ip, int _dst_port, string _data){
    src_ip = _src_ip;
    dst_ip = _dst_ip;
    src_port = _src_port;
    dst_port = _dst_port;
    data = _data;
    memset(buffer, 0, PCKT_LEN);
    ip = (struct ipv4 *) buffer;
    udp = (struct udpheader *) (buffer + sizeof(struct ipv4));
    one = 1;
    val = &one;
}

void UDP_Sender::display(){
    cout << "\n--\nsrc IP: " << src_ip << ":" << src_port << "\ndst IP: " << dst_ip << ":" << dst_port << "\ndata: " << data << "\n";

    cout << "PacketData(bin): ";
    // 送信バイナリ列
    for(u_long i = 0; i < (sizeof(struct ipv4) + sizeof(struct udpheader) + data_len); i++){
        printf("%x", buffer[i]); 
        // %.2x??
    }
    
    cout << "\n--\n";

}

u_short UDP_Sender::csum(u_short *buf, int nwords)
{
    u_long sum;
    for(sum=0; nwords>0; nwords--)
    {
        sum += *buf++;
    }
    sum = (sum >> 16) + (sum &0xffff);
    sum += (sum >> 16);
    return (u_short)(~sum);
}
