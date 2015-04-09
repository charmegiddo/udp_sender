#ifndef __ETHFRAME_H__
#define __ETHFRAME_H__
#include <iostream>

#define SIZE_ETHERNET 14 // Todo:ARPとかを作る
#define ETHER_ADDR_LEN  6

class CEthFrame {
public:

//	u_char 1byte
//	u_short 2byte
	std::string to_string();

	// Ethernet header
	#pragma pack(1)
	struct ethernet {
	    u_char ether_dhost[ETHER_ADDR_LEN]; // Destination host address
	    u_char ether_shost[ETHER_ADDR_LEN]; // Source host address
	    u_short ether_type; // IP? ARP? RARP? etc
	};
	#pragma pack()

	// IP header v4
	#pragma pack(1)
	struct ipv4 {
		u_char ip_ihl:4, ip_ver:4;
	    u_char ip_tos;      // type of service
	    u_short ip_len;     // total length
	    u_short ip_id;      // identification
	    u_short ip_off;     // fragment offset field
		#define IP_RF 0x8000        // reserved fragment flag
		#define IP_DF 0x4000        // dont fragment flag
		#define IP_MF 0x2000        // more fragments flag
		#define IP_OFFMASK 0x1fff   // mask for fragmenting bits
	    u_char ip_ttl;      // time to live 
	    u_char ip_p;        // protocol
	    u_short ip_sum;     // checksum
	    u_int32_t ip_src;
	    u_int32_t ip_dst;
	};
	#pragma pack()


	// ICMP
	#pragma pack(1)
	struct icmp {
		u_char type;
		u_char code;
		u_short checksum;
		u_short idnum;
		u_short sqnum;
		u_int64_t time_stamp;
	};
	#pragma pack()

	// IP header v6
	#pragma pack(1)
	struct ipv6 {
	};
	#pragma pack()

	// UDP header
	#pragma pack(1)
	struct udpheader {
		u_short udp_srcport;
		u_short udp_destport;
		u_short udp_len;
		u_short udp_chksum;
	};
	#pragma pack(0)

	// TCP header 
	#pragma pack(1)
	struct tcp {
	    u_short tcp_sport;   // source port
	    u_short tcp_dport;   // destination port
	    u_int32_t tcp_seq;       // sequence number
	    u_int32_t tcp_ack;       // acknowledgement number
	    u_char tcp_offx2;    // data offset, rsvd 
		#define TCP_OFF(tcp)  (((tcp)->tcp_offx2 & 0xf0) >> 4)
	    u_char tcp_flags;
		#define TCP_FIN 0x01
		#define TCP_SYN 0x02
		#define TCP_RST 0x04
		#define TCP_PUSH 0x08
		#define TCP_ACK 0x10
		#define TCP_URG 0x20
		#define TCP_ECE 0x40
		#define TCP_CWR 0x80
		#define TCP_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
	    u_short tcp_win;     // window
	    u_short tcp_sum;     // checksum
	    u_short tcp_urp;     // urgent pointer
	};
	#pragma pack()


};

#endif
