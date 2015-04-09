#ifndef __ETHFRAME_H__
#define __ETHFRAME_H__
#include <iostream>

#define SIZE_ETHERNET 14
#define ETHER_ADDR_LEN  6

class CEthFrame {
public:

	std::string to_string();

	#pragma pack(1)
	struct ethernet {
	    u_char ether_dhost[ETHER_ADDR_LEN];
	    u_char ether_shost[ETHER_ADDR_LEN];
	    u_short ether_type;
	};
	#pragma pack()


	#pragma pack(1)
	struct ipv4 {
		u_char ip_ihl:4, ip_ver:4;
	    u_char ip_tos;
	    u_short ip_len;
	    u_short ip_id;
	    u_short ip_off;
		#define IP_RF 0x8000
		#define IP_DF 0x4000
		#define IP_MF 0x2000
		#define IP_OFFMASK 0x1fff
	    u_char ip_ttl;
	    u_char ip_p;
	    u_short ip_sum;
	    u_int32_t ip_src;
	    u_int32_t ip_dst;
	};
	#pragma pack()



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


	#pragma pack(1)
	struct ipv6 {
	};
	#pragma pack()


	#pragma pack(1)
	struct udpheader {
		u_short udp_srcport;
		u_short udp_destport;
		u_short udp_len;
		u_short udp_chksum;
	};
	#pragma pack(0)


	#pragma pack(1)
	struct tcp {
	    u_short tcp_sport;
	    u_short tcp_dport;
	    u_int32_t tcp_seq;
	    u_int32_t tcp_ack;
	    u_char tcp_offx2;
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
	    u_short tcp_win;
	    u_short tcp_sum;
	    u_short tcp_urp;
	};
	#pragma pack()

};

#endif
