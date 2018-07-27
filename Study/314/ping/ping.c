#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <linux/if_ether.h>
#include <netdb.h>

#if 0
struct ip
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    unsigned int ip_hl:4;       /* header length */
    unsigned int ip_v:4;        /* version */
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
    unsigned int ip_v:4;        /* version */
    unsigned int ip_hl:4;       /* header length */
#endif
    u_int8_t ip_tos;            /* type of service */
    u_short ip_len;         /* total length */
    u_short ip_id;          /* identification */
    u_short ip_off;         /* fragment offset field */
#define IP_RF 0x8000            /* reserved fragment flag */
#define IP_DF 0x4000            /* dont fragment flag */
#define IP_MF 0x2000            /* more fragments flag */
#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
    u_int8_t ip_ttl;            /* time to live */
    u_int8_t ip_p;          /* protocol */
    u_short ip_sum;         /* checksum */
    struct in_addr ip_src, ip_dst;  /* source and dest address */
};


struct ethhdr {
	unsigned char	h_dest[ETH_ALEN];	/* destination eth addr	*/
	unsigned char	h_source[ETH_ALEN];	/* source ether addr	*/
	__be16		h_proto;		/* packet type ID field	*/
} __attribute__((packed));
#endif

int main()
{
    struct hostent* p= gethostbyname("www.sust.xin");
    printf("%s\n", inet_ntoa(*(struct in_addr*)(p->h_addr)));
    struct timeval tv;
    struct timezone tz;
    int time_begin = gettimeofday(&tv, &tz);
    



    // int sfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    // int sfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    // if(sfd == -1)
    // {
    //     perror("socket");
    //     exit(1);
    // }
    // char buf[1500];
    // while(1)
    // {
    //     sleep(1);
    //     memset(buf, 0, sizeof(buf));
    //     if(read(sfd, buf, sizeof(buf)) < 0) break;
    //     struct ethhdr* pe = (struct ethhdr*)(buf);
    //     printf("%02x:%02x:%02x:%02x:%02x:%02x <--> ", 
    //            pe->h_source[0],
    //            pe->h_source[1],
    //            pe->h_source[2],
    //            pe->h_source[3],
    //            pe->h_source[4],
    //            pe->h_source[5]);
    //     printf("%02x:%02x:%02x:%02x:%02x:%02x  \n", 
    //            pe->h_dest[0],
    //            pe->h_dest[1],
    //            pe->h_dest[2],
    //            pe->h_dest[3],
    //            pe->h_dest[4],
    //            pe->h_dest[5]);

    //     if(ntohs(pe->h_proto) == 0x0800)
    //     {
    //         printf("\tIP\n");
    //     }
    //     if(ntohs(pe->h_proto) == 0x0806)
    //     {
    //         printf("\tARP\n");
    //     }
    // }

    // int op = 1;
    // setsockopt(sfd, IPPROTO_IP, IP_HDRINCL, &op, sizeof(op));
    // char buf[1500] = {};
    // while(1)
    // {
    //     sleep(1);
    //     memset(buf, 0x00, sizeof(buf));
    //     if(read(sfd, buf, 1500) < 0) break;
    //     struct ip* pip = (struct ip*)(buf);
    //     printf("%s <----> %s ", inet_ntoa(pip->ip_dst), inet_ntoa(pip->ip_src));
    //     struct tcphdr* ptcp = (struct tcphdr*)(buf + (pip->ip_hl << 2));
    //     printf("%hu : %hu\n", ntohs(ptcp->dest) , ntohs(ptcp->source));
    // }
}

