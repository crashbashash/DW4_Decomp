/* sifcmd.c - libkernl's SIF command layer (libkernl.a sifcmd.o): the handler tables the IOP's
 * commands are dispatched through, the software registers, and sending commands over SIF0/SIF1. */
#include "dw4/sony/sif.h"
#include "dw4/eekernel_gp.h"
#include "dw4/libkernl.h"

#define DMAC_SIF0 5

/* sceSifSendCmd modes: wait-free (interrupt-level) send, and write back the extra data first */
#define SIF_CMD_M_INTR 0x1
#define SIF_CMD_M_WBDC 0x4
/* the sizes a command packet may have */
#define SIF_CMD_PACKET_MIN 16
#define SIF_CMD_PACKET_MAX 112
/* the transfer attributes of the packet's own DMA: end-of-transfer, interrupt on the IOP */
#define SIF_DMA_PACKET 0x44

typedef struct {
    unsigned int data;
    unsigned int addr;
    unsigned int size;
    unsigned int mode;
} sceSifDmaData;

/* the SIF registers sceSifInitCmd hands the receive buffer and the command data over in */
#define SIF_SYSREG_SUBADDR 0x80000000
#define SIF_SYSREG_MAINADDR 0x80000001
#define SIF_REG_SUBADDR 2
#define SIF_REG_SMFLAG 4
#define SIF_STAT_CMDINIT 0x20000
/* the system commands' handler table */
#define SIF_SYS_CMD_MAX 32

#define D_STAT (*(volatile unsigned int *)0x1000E010)
#define D_STAT_CIS_SIF0 (1 << DMAC_SIF0)
#define D5_CHCR (*(volatile unsigned int *)0x1000C000)
#define D_CHCR_STR 0x100

#define UNCACHED(p) ((void *)((unsigned int)(p) | 0x20000000))

int AddDmacHandler(int channel, int (*handler)(int), int next);
int RemoveDmacHandler(int channel, int id);
unsigned int sceSifGetReg(unsigned int reg);
int sceSifSetReg(unsigned int reg, unsigned int value);
int sceSifSetDChain(void);

static int _cmd_init_check = 0;
static char _pckt_buffer[128] __attribute__((aligned(64)));
static char _send_buffer[64];
static sceSifCmdChangeAddr _csdata;
static int sif0_handleid;
static sceSifCmdState _data_table;
static sceSifCmdData _sys_buffer[SIF_SYS_CMD_MAX] __attribute__((aligned(64)));
static unsigned int soft_reg[32];

unsigned int sceSifSetDma(sceSifDmaData *transfers, int count);
unsigned int isceSifSetDma(sceSifDmaData *transfers, int count);
unsigned int sceSifSendCmd(unsigned int cid, void *packet, int size, void *src, void *dest, int len);
static int _sceSifCmdIntrHdlr(int channel);
int isceSifSetDChain(void);

typedef int quadword __attribute__((mode(TI)));

static void _set_sreg(sceSifCmdSRegData *packet, sceSifCmdState *state)
{
    state->sregs[packet->index] = packet->value;
}

static void _change_addr(sceSifCmdChangeAddr *packet, sceSifCmdState *state)
{
    state->iopbuf = packet->iopbuf;
}

unsigned int sceSifGetSreg(int reg)
{
    return soft_reg[reg];
}

unsigned int sceSifSetSreg(int reg, unsigned int value)
{
    soft_reg[reg] = value;
    return value;
}

sceSifCmdState *sceSifGetDataTable(void)
{
    return &_data_table;
}

void sceSifInitCmd(void)
{
    int i;

    DIntr();
    if (_cmd_init_check) {
        EIntr();
        return;
    }
    _cmd_init_check = 1;
    /* matching construct: permutation search — field store order */
    _data_table.pktbuf = UNCACHED(_pckt_buffer);
    _data_table.unused = UNCACHED(_send_buffer);
    _data_table.sysCount = SIF_SYS_CMD_MAX;
    _data_table.iopbuf = 0;
    _data_table.sysTable = _sys_buffer;
    _data_table.userTable = 0;
    _data_table.userCount = 0;
    _data_table.sregs = soft_reg;
    for (i = 0; i < SIF_SYS_CMD_MAX; i++) {
        _sys_buffer[i].func = 0;
        _sys_buffer[i].data = 0;
    }
    for (i = 0; i < 32; i++) {
        soft_reg[i] = 0;
    }
    _sys_buffer[0].func = (sceSifCmdHandler)_change_addr;
    _sys_buffer[0].data = &_data_table;
    _sys_buffer[1].func = (sceSifCmdHandler)_set_sreg;
    _sys_buffer[1].data = &_data_table;
    EIntr();
    FlushCache(0);
    if (D_STAT & D_STAT_CIS_SIF0) {
        D_STAT = D_STAT_CIS_SIF0;
    }
    if (!(D5_CHCR & D_CHCR_STR)) {
        sceSifSetDChain();
    }
    sif0_handleid = AddDmacHandler(DMAC_SIF0, _sceSifCmdIntrHdlr, 0);
    EnableDmac(DMAC_SIF0);
    _data_table.iopbuf = (void *)sceSifGetReg(SIF_SYSREG_SUBADDR);
    if (_data_table.iopbuf) {
        _csdata.iopbuf = _pckt_buffer;
        sceSifSendCmd(SIF_CMD_SYSTEM, &_csdata, sizeof(_csdata), 0, 0, 0);
        return;
    }
    while (!(sceSifGetReg(SIF_REG_SMFLAG) & SIF_STAT_CMDINIT));
    _data_table.iopbuf = (void *)sceSifGetReg(SIF_REG_SUBADDR);
    sceSifSetReg(SIF_SYSREG_SUBADDR, (unsigned int)_data_table.iopbuf);
    sceSifSetReg(SIF_SYSREG_MAINADDR, (unsigned int)&_data_table);
    _csdata.iopbuf = _pckt_buffer;
    _csdata.hdr.opt = 0;
    sceSifSendCmd(SIF_CMD_INIT_CMD, &_csdata, sizeof(_csdata), 0, 0, 0);
}

void sceSifExitCmd(void)
{
    DisableDmac(DMAC_SIF0);
    RemoveDmacHandler(DMAC_SIF0, sif0_handleid);
    _cmd_init_check = 0;
}

sceSifCmdData *sceSifSetCmdBuffer(sceSifCmdData *table, int count)
{
    sceSifCmdData *old = _data_table.userTable;
    _data_table.userTable = table;
    _data_table.userCount = count;
    return old;
}

sceSifCmdData *sceSifSetSysCmdBuffer(sceSifCmdData *table, int count)
{
    sceSifCmdData *old = _data_table.sysTable;
    _data_table.sysTable = table;
    _data_table.sysCount = count;
    return old;
}

void sceSifAddCmdHandler(unsigned int cid, sceSifCmdHandler func, void *data)
{
    if ((int)cid < 0) {
        _data_table.sysTable[cid & ~SIF_CMD_SYSTEM].func = func;
        _data_table.sysTable[cid & ~SIF_CMD_SYSTEM].data = data;
        _data_table.sysTable[cid & ~SIF_CMD_SYSTEM].gp = GetGp();
    } else {
        _data_table.userTable[cid].func = func;
        _data_table.userTable[cid].data = data;
        _data_table.userTable[cid].gp = GetGp();
    }
}

void sceSifRemoveCmdHandler(unsigned int cid)
{
    if ((int)cid < 0) {
        _data_table.sysTable[cid & ~SIF_CMD_SYSTEM].func = 0;
        return;
    }
    _data_table.userTable[cid].func = 0;
}

static unsigned int _sceSifSendCmd(unsigned int cid, int mode, void *packet, int size, void *src,
                                   void *dest, int len)
{
    sceSifDmaData transfers[2];
    sceSifCmdHdr *hdr = packet;
    int count;

    if (size < SIF_CMD_PACKET_MIN || size > SIF_CMD_PACKET_MAX) {
        return 0;
    }
    count = 0;
    if (len > 0) {
        hdr->dsize = len;
        transfers[0].data = (unsigned int)src;
        transfers[0].addr = (unsigned int)dest;
        hdr->dest = (unsigned int)dest;
        transfers[0].size = len;
        transfers[0].mode = 0;
        count = 1;
        if (mode & SIF_CMD_M_WBDC) {
            sceSifWriteBackDCache(src, len);
        }
    } else {
        hdr->dsize = 0;
        hdr->dest = 0;
    }
    transfers[count].data = (unsigned int)packet;
    transfers[count].addr = (unsigned int)_data_table.iopbuf;
    transfers[count].size = size;
    hdr->cid = cid;
    hdr->psize = size;
    transfers[count].mode = SIF_DMA_PACKET;
    sceSifWriteBackDCache(packet, size);
    count++;
    if (mode & SIF_CMD_M_INTR) {
        return isceSifSetDma(transfers, count);
    }
    return sceSifSetDma(transfers, count);
}

unsigned int sceSifSendCmd(unsigned int cid, void *packet, int size, void *src, void *dest, int len)
{
    return _sceSifSendCmd(cid, 0, packet, size, src, dest, len);
}

unsigned int isceSifSendCmd(unsigned int cid, void *packet, int size, void *src, void *dest, int len)
{
    return _sceSifSendCmd(cid, 1, packet, size, src, dest, len);
}

/* The SIF0 DMA-completion handler: copies the command the IOP left in the receive buffer, re-arms the
 * channel and runs the command's handler on the $gp it was registered with. */
static int _sceSifCmdIntrHdlr(int channel)
{
    quadword packet[SIF_CMD_PACKET_MAX / sizeof(quadword)];
    sceSifCmdState *state = &_data_table;
    volatile sceSifCmdHdr *hdr = _data_table.pktbuf;
    quadword *src;
    sceSifCmdHandler func;
    /* matching construct: global-alloc trace — one int holds the packet size, its quadword count and
     * the command index */
    int n, i;

    if ((n = hdr->psize) == 0) {
        return 0;
    }
    n = (n + 15) / 16;
    hdr->psize = 0;
    src = (quadword *)hdr;
    for (i = 0; i < n; i++) {
        packet[i] = *src++;
    }
    isceSifSetDChain();
    hdr = (sceSifCmdHdr *)packet;
    if (hdr->cid & SIF_CMD_SYSTEM) {
        n = hdr->cid & ~SIF_CMD_SYSTEM;
        if (n < state->sysCount && (func = state->sysTable[n].func)) {
            void *gp = SetGp(state->sysTable[n].gp);

            func(packet, state->sysTable[n].data);
            SetGp(gp);
        }
    } else {
        n = hdr->cid;
        if (n < state->userCount && (func = state->userTable[n].func)) {
            void *gp = SetGp(state->userTable[n].gp);

            func(packet, state->userTable[n].data);
            SetGp(gp);
        }
    }
    __asm__("sync.l; ei");
    return 0;
}

/* Writes back the data cache lines of [ptr, ptr + size), eight lines a pass: Sony's own assembly. */
void sceSifWriteBackDCache(void *ptr, int size)
{
    __asm__(
        ".set noreorder\n"
        "lui     $25, 0xffff\n"
        "ori     $25, $25, 0xffc0\n"
        "blez    $5, 9f\n"
        "addu    $10, $4, $5\n"
        "and     $8, $4, $25\n"
        "addiu   $10, $10, -1\n"
        "and     $9, $10, $25\n"
        "subu    $10, $9, $8\n"
        "srl     $11, $10, 6\n"
        "addiu   $11, $11, 1\n"
        "andi    $9, $11, 7\n"
        "beqz    $9, 2f\n"
        "srl     $10, $11, 3\n"
        "1:  sync\n"
        "cache   0x18, 0($8)\n"
        "sync\n"
        "nop\n"
        "addiu   $9, $9, -1\n"
        "bgtz    $9, 1b\n"
        "addiu   $8, $8, 64\n"
        "2:  beqz    $10, 9f\n"
        "3:  addiu   $10, $10, -1\n"
        "sync\n"
        "cache   0x18, 0($8)\n"
        "sync\n"
        "cache   0x18, 64($8)\n"
        "sync\n"
        "cache   0x18, 128($8)\n"
        "sync\n"
        "cache   0x18, 192($8)\n"
        "sync\n"
        "cache   0x18, 256($8)\n"
        "sync\n"
        "cache   0x18, 320($8)\n"
        "sync\n"
        "cache   0x18, 384($8)\n"
        "sync\n"
        "cache   0x18, 448($8)\n"
        "sync\n"
        "bgtz    $10, 3b\n"
        "addiu   $8, $8, 512\n"
        "9:  jr      $31\n"
        "nop\n"
    );
}
