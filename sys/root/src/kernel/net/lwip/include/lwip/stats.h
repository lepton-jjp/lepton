/*
The contents of this file are subject to the Mozilla Public License Version 1.1 
(the "License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis, 
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for the 
specific language governing rights and limitations under the License.

The Original Code is ______________________________________.

The Initial Developer of the Original Code is ________________________.
Portions created by ______________________ are Copyright (C) ______ _______________________.
All Rights Reserved.

Contributor(s): ______________________________________.

Alternatively, the contents of this file may be used under the terms of the eCos GPL license 
(the  [eCos GPL] License), in which case the provisions of [eCos GPL] License are applicable 
instead of those above. If you wish to allow use of your version of this file only under the
terms of the [eCos GPL] License and not to allow others to use your version of this file under 
the MPL, indicate your decision by deleting  the provisions above and replace 
them with the notice and other provisions required by the [eCos GPL] License. 
If you do not delete the provisions above, a recipient may use your version of this file under 
either the MPL or the [eCos GPL] License."
*/
#ifndef __LWIP_STATS_H__
#define __LWIP_STATS_H__

#include "lwip/opt.h"

#include "lwip/mem.h"
#include "lwip/memp.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_STATS

#ifndef LWIP_STATS_LARGE
#define LWIP_STATS_LARGE 0
#endif

#if LWIP_STATS_LARGE
#define STAT_COUNTER     u32_t
#define STAT_COUNTER_F   U32_F
#else
#define STAT_COUNTER     u16_t
#define STAT_COUNTER_F   U16_F
#endif 

struct stats_proto {
  STAT_COUNTER xmit;             /* Transmitted packets. */
  STAT_COUNTER recv;             /* Received packets. */
  STAT_COUNTER fw;               /* Forwarded packets. */
  STAT_COUNTER drop;             /* Dropped packets. */
  STAT_COUNTER chkerr;           /* Checksum error. */
  STAT_COUNTER lenerr;           /* Invalid length error. */
  STAT_COUNTER memerr;           /* Out of memory error. */
  STAT_COUNTER rterr;            /* Routing error. */
  STAT_COUNTER proterr;          /* Protocol error. */
  STAT_COUNTER opterr;           /* Error in options. */
  STAT_COUNTER err;              /* Misc error. */
  STAT_COUNTER cachehit;
};

struct stats_igmp {
  STAT_COUNTER lenerr;           /* Invalid length error. */
  STAT_COUNTER chkerr;           /* Checksum error. */
  STAT_COUNTER v1_rxed;          /* */
  STAT_COUNTER join_sent;        /* */
  STAT_COUNTER leave_sent;       /* */
  STAT_COUNTER unicast_query;    /* */
  STAT_COUNTER report_sent;      /* */
  STAT_COUNTER report_rxed;      /* */
  STAT_COUNTER group_query_rxed; /* */
};

struct stats_mem {
  mem_size_t avail;
  mem_size_t used;
  mem_size_t max;
  STAT_COUNTER err;
  STAT_COUNTER illegal;
};

struct stats_syselem {
  STAT_COUNTER used;
  STAT_COUNTER max;
  STAT_COUNTER err;
};

struct stats_sys {
  struct stats_syselem sem;
  struct stats_syselem mbox;
};

struct stats_ {
#if LINK_STATS
  struct stats_proto link;
#endif
#if ETHARP_STATS
  struct stats_proto etharp;
#endif
#if IPFRAG_STATS
  struct stats_proto ip_frag;
#endif
#if IP_STATS
  struct stats_proto ip;
#endif
#if ICMP_STATS
  struct stats_proto icmp;
#endif
#if IGMP_STATS
  struct stats_igmp igmp;
#endif
#if UDP_STATS
  struct stats_proto udp;
#endif
#if TCP_STATS
  struct stats_proto tcp;
#endif
#if MEM_STATS
  struct stats_mem mem;
#endif
#if MEMP_STATS
  struct stats_mem memp[MEMP_MAX];
#endif
#if SYS_STATS
  struct stats_sys sys;
#endif
};

extern struct stats_ lwip_stats;

#define stats_init() /* Compatibility define, not init needed. */

#define STATS_INC(x) ++lwip_stats.x
#define STATS_DEC(x) --lwip_stats.x
#else
#define stats_init()
#define STATS_INC(x)
#define STATS_DEC(x)
#endif /* LWIP_STATS */

#if TCP_STATS
#define TCP_STATS_INC(x) STATS_INC(x)
#define TCP_STATS_DISPLAY() stats_display_proto(&lwip_stats.tcp, "TCP")
#else
#define TCP_STATS_INC(x)
#define TCP_STATS_DISPLAY()
#endif

#if UDP_STATS
#define UDP_STATS_INC(x) STATS_INC(x)
#define UDP_STATS_DISPLAY() stats_display_proto(&lwip_stats.udp, "UDP")
#else
#define UDP_STATS_INC(x)
#define UDP_STATS_DISPLAY()
#endif

#if ICMP_STATS
#define ICMP_STATS_INC(x) STATS_INC(x)
#define ICMP_STATS_DISPLAY() stats_display_proto(&lwip_stats.icmp, "ICMP")
#else
#define ICMP_STATS_INC(x)
#define ICMP_STATS_DISPLAY()
#endif

#if IGMP_STATS
#define IGMP_STATS_INC(x) STATS_INC(x)
#define IGMP_STATS_DISPLAY() stats_display_igmp(&lwip_stats.igmp)
#else
#define IGMP_STATS_INC(x)
#define IGMP_STATS_DISPLAY()
#endif

#if IP_STATS
#define IP_STATS_INC(x) STATS_INC(x)
#define IP_STATS_DISPLAY() stats_display_proto(&lwip_stats.ip, "IP")
#else
#define IP_STATS_INC(x)
#define IP_STATS_DISPLAY()
#endif

#if IPFRAG_STATS
#define IPFRAG_STATS_INC(x) STATS_INC(x)
#define IPFRAG_STATS_DISPLAY() stats_display_proto(&lwip_stats.ip_frag, "IP_FRAG")
#else
#define IPFRAG_STATS_INC(x)
#define IPFRAG_STATS_DISPLAY()
#endif

#if ETHARP_STATS
#define ETHARP_STATS_INC(x) STATS_INC(x)
#define ETHARP_STATS_DISPLAY() stats_display_proto(&lwip_stats.etharp, "ETHARP")
#else
#define ETHARP_STATS_INC(x)
#define ETHARP_STATS_DISPLAY()
#endif

#if LINK_STATS
#define LINK_STATS_INC(x) STATS_INC(x)
#define LINK_STATS_DISPLAY() stats_display_proto(&lwip_stats.link, "LINK")
#else
#define LINK_STATS_INC(x)
#define LINK_STATS_DISPLAY()
#endif

#if MEM_STATS
#define MEM_STATS_AVAIL(x, y) lwip_stats.mem.x = y
#define MEM_STATS_INC(x) STATS_INC(mem.x)
#define MEM_STATS_INC_USED(x, y) do { lwip_stats.mem.used += y; \
                                    if (lwip_stats.mem.max < lwip_stats.mem.used) { \
                                        lwip_stats.mem.max = lwip_stats.mem.used; \
                                    } \
                                 } while(0)
#define MEM_STATS_DEC_USED(x, y) lwip_stats.mem.x -= y
#define MEM_STATS_DISPLAY() stats_display_mem(&lwip_stats.mem, "HEAP")
#else
#define MEM_STATS_AVAIL(x, y)
#define MEM_STATS_INC(x)
#define MEM_STATS_INC_USED(x, y)
#define MEM_STATS_DEC_USED(x, y)
#define MEM_STATS_DISPLAY()
#endif

#if MEMP_STATS
#define MEMP_STATS_AVAIL(x, i, y) lwip_stats.memp[i].x = y
#define MEMP_STATS_INC(x, i) STATS_INC(memp[i].x)
#define MEMP_STATS_DEC(x, i) STATS_DEC(memp[i].x)
#define MEMP_STATS_INC_USED(x, i) do { ++lwip_stats.memp[i].used; \
                                    if (lwip_stats.memp[i].max < lwip_stats.memp[i].used) { \
                                        lwip_stats.memp[i].max = lwip_stats.memp[i].used; \
                                    } \
                                 } while(0)
#define MEMP_STATS_DISPLAY(i) stats_display_memp(&lwip_stats.memp[i], i)
#else
#define MEMP_STATS_AVAIL(x, i, y)
#define MEMP_STATS_INC(x, i)
#define MEMP_STATS_DEC(x, i)
#define MEMP_STATS_INC_USED(x, i)
#define MEMP_STATS_DISPLAY(i)
#endif

#if SYS_STATS
#define SYS_STATS_INC(x) STATS_INC(sys.x)
#define SYS_STATS_DEC(x) STATS_DEC(sys.x)
#define SYS_STATS_DISPLAY() stats_display_sys(&lwip_stats.sys)
#else
#define SYS_STATS_INC(x)
#define SYS_STATS_DEC(x)
#define SYS_STATS_DISPLAY()
#endif

/* Display of statistics */
#if LWIP_STATS_DISPLAY
void stats_display(void);
void stats_display_proto(struct stats_proto *proto, char *name);
void stats_display_igmp(struct stats_igmp *igmp);
void stats_display_mem(struct stats_mem *mem, char *name);
void stats_display_memp(struct stats_mem *mem, int index);
void stats_display_sys(struct stats_sys *sys);
#else
#define stats_display()
#define stats_display_proto(proto, name)
#define stats_display_igmp(igmp)
#define stats_display_mem(mem, name)
#define stats_display_memp(mem, index)
#define stats_display_sys(sys)
#endif /* LWIP_STATS_DISPLAY */

#ifdef __cplusplus
}
#endif

#endif /* __LWIP_STATS_H__ */
