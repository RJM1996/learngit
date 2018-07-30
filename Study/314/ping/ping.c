#include <netdb.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <net/ethernet.h>
#include <linux/if_ether.h>
#include <netinet/ip_icmp.h>
#include <netpacket/packet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_LEN 56

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
	__be16		    h_proto;		    /* packet type ID field	*/
} __attribute__((packed));
#endif

int sendnum = 0;    // 发送数据包的编号
int recvnum = 0;    // 接收数据包的编号
char sendbuf[1024]; // 发送数据包
char recvbuf[1024]; // 接收数据包

#if 0
struct icmp
{
  u_int8_t  icmp_type;	/* type of message, see below */
  u_int8_t  icmp_code;	/* type sub code */
  u_int16_t icmp_cksum;	/* ones complement checksum of struct */
  union
  {
    u_char ih_pptr;		/* ICMP_PARAMPROB */
    struct in_addr ih_gwaddr;	/* gateway address */
    struct ih_idseq		/* echo datagram */
    {
      u_int16_t icd_id;
      u_int16_t icd_seq;
    } ih_idseq;
    u_int32_t ih_void;

    /* ICMP_UNREACH_NEEDFRAG -- Path MTU Discovery (RFC1191) */
    struct ih_pmtu
    {
      u_int16_t ipm_void;
      u_int16_t ipm_nextmtu;
    } ih_pmtu;

    struct ih_rtradv
    {
      u_int8_t irt_num_addrs;
      u_int8_t irt_wpa;
      u_int16_t irt_lifetime;
    } ih_rtradv;
  } icmp_hun;
#define	icmp_pptr	icmp_hun.ih_pptr
#define	icmp_gwaddr	icmp_hun.ih_gwaddr
#define	icmp_id		icmp_hun.ih_idseq.icd_id
#define	icmp_seq	icmp_hun.ih_idseq.icd_seq
#define	icmp_void	icmp_hun.ih_void
#define	icmp_pmvoid	icmp_hun.ih_pmtu.ipm_void
#define	icmp_nextmtu	icmp_hun.ih_pmtu.ipm_nextmtu
#define	icmp_num_addrs	icmp_hun.ih_rtradv.irt_num_addrs
#define	icmp_wpa	icmp_hun.ih_rtradv.irt_wpa
#define	icmp_lifetime	icmp_hun.ih_rtradv.irt_lifetime
  union
  {
    struct
    {
      u_int32_t its_otime;
      u_int32_t its_rtime;
      u_int32_t its_ttime;
    } id_ts;
    struct
    {
      struct ip idi_ip;
      /* options and then 64 bits of data */
    } id_ip;
    struct icmp_ra_addr id_radv;
    u_int32_t   id_mask;
    u_int8_t    id_data[1];
  } icmp_dun;
#define	icmp_otime	icmp_dun.id_ts.its_otime
#define	icmp_rtime	icmp_dun.id_ts.its_rtime
#define	icmp_ttime	icmp_dun.id_ts.its_ttime
#define	icmp_ip		icmp_dun.id_ip.idi_ip
#define	icmp_radv	icmp_dun.id_radv
#define	icmp_mask	icmp_dun.id_mask
#define	icmp_data	icmp_dun.id_data
};
#endif

// 组包
// num: ICMP 报文序号
// pid: 组icmp报文的标识符字段
int pack(int num, pid_t pid)
{
    struct icmp* picmp = (struct icmp*)sendbuf;
    picmp->icmp_type = ICMP_ECHO;
    picmp->icmp_code = 0;
    picmp->icmp_cksum = 0;
    picmp->icmp_id = pid;
    picmp->icmp_seq = htons(num);
    gettimeofday((struct timeval*)picmp->icmp_data, NULL);
    return DATA_LEN + 8;
}

// 发送数据包
// sfd: 套接字描述符
// pid: 组icmp报文的标识符字段
// addr: 发送的目标机器
void send_packet(int sfd, pid_t pid, struct sockaddr_in addr)
{
    sendnum++;
    int ret = pack(sendnum, pid); // 组包
    sendto(sfd, sendbuf, ret, 0, (struct sockaddr*)&addr, sizeof(addr));
}
// 接收数据包
void recv_packet(int sfd, pid_t pid)
{

}

// 校验和的算法
// addr: 需要计算校验和的数据起始地址
// len:  数据大小, 单位字节
unsigned short chksum(unsigned short* addr, int len)
{
    unsigned int ret = 0;
    while(len > 1)
    {
        ret += *addr;
        addr++;
        len -= sizeof(unsigned short);
    }

    if(len == 1)
    {
        ret += *(unsigned char*)addr;
    }

    ret = (ret >> 16) + (ret & 0xffff);
    ret = (ret >> 16) + (ret);

    return (unsigned short)~ret;
}

// 往返时间差
float dirtime(struct timeval* end, struct timeval* begin)
{
    // end->tv_sec
    // end->tv_usec
    return (end->tv_sec - begin->tv_sec) * 1000.0 +
           (end->tv_usec - begin->tv_usec) / 1000.0;
}



int main(int argc, char* argv[])
{
    // struct hostent* p= gethostbyname("www.sust.xin");
    // printf("%s\n", inet_ntoa(*(struct in_addr*)(p->h_addr)));
    // struct timeval tv;
    // struct timezone tz;
    // int time_begin = gettimeofday(&tv, &tz);
    // (void) time_begin;

    if(argc != 2)
    {
        fprintf(stderr, "usage: ./ping ip/域名\n");
        exit(1);
    }

    struct sockaddr_in addr;
    struct hostent* phost;

    addr.sin_addr.s_addr = inet_addr(argv[1]);
    if(addr.sin_addr.s_addr == INADDR_NONE)
    {
        // 出错, ip不对, 可能是域名, 进行域名解析
        phost = gethostbyname(argv[1]);
        if(phost == NULL) // 域名解析出错
        {
            perror("gethostbyname");
            exit(1);
        }
        // 把解析出的ip地址拷贝进addr中
        memcpy((void*)&addr.sin_addr, (void*)phost->h_addr, phost->h_length);
    }
    // 到这里就把用户 ping 的 IP 地址得到了
    
    // 1. 先发送第一句
    printf("PING %s (%s) %d bytes of data.\n", argv[1], inet_ntoa(addr.sin_addr), DATA_LEN);

    int sfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if(sfd == -1)
    {
        perror("socket"), exit(1);
    }

    pid_t pid = getpid();
    while(1)
    {
        // 循环发送接收数据
        send_packet(sfd, pid, addr);
        recv_packet(sfd, pid);
        sleep(1);
    }
    
    



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
