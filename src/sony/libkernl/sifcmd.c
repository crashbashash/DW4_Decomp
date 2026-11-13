/* sifcmd.c - libkernl's SIF command layer (libkernl.a sifcmd.o): the handler tables the IOP's
 * commands are dispatched through, the software registers, and sending commands over SIF0/SIF1. */
#include "dw4/sony/sif.h"
#include "dw4/eekernel_gp.h"

#define DMAC_SIF0 5

int DIntr(void);
int EIntr(void);
int DisableDmac(int channel);
int RemoveDmacHandler(int channel, int id);

extern int _cmd_init_check;
extern int sif0_handleid;
extern sceSifCmdState _sif_cmd_data;
extern unsigned int sifSregs[32];

unsigned int _sceSifSendCmd(unsigned int cid, int mode, void *packet, int size, void *src, void *dest,
                            int len);

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
    return sifSregs[reg];
}

unsigned int sceSifSetSreg(int reg, unsigned int value)
{
    sifSregs[reg] = value;
    return value;
}

sceSifCmdState *sceSifGetDataTable(void)
{
    return &_sif_cmd_data;
}

void sceSifExitCmd(void)
{
    DisableDmac(DMAC_SIF0);
    RemoveDmacHandler(DMAC_SIF0, sif0_handleid);
    _cmd_init_check = 0;
}

sceSifCmdData *sceSifSetCmdBuffer(sceSifCmdData *table, int count)
{
    sceSifCmdData *old = _sif_cmd_data.userTable;
    _sif_cmd_data.userTable = table;
    _sif_cmd_data.userCount = count;
    return old;
}

sceSifCmdData *sceSifSetSysCmdBuffer(sceSifCmdData *table, int count)
{
    sceSifCmdData *old = _sif_cmd_data.sysTable;
    _sif_cmd_data.sysTable = table;
    _sif_cmd_data.sysCount = count;
    return old;
}

void sceSifAddCmdHandler(unsigned int cid, sceSifCmdHandler func, void *data)
{
    if ((int)cid < 0) {
        _sif_cmd_data.sysTable[cid & ~SIF_CMD_SYSTEM].func = func;
        _sif_cmd_data.sysTable[cid & ~SIF_CMD_SYSTEM].data = data;
        _sif_cmd_data.sysTable[cid & ~SIF_CMD_SYSTEM].gp = GetGp();
    } else {
        _sif_cmd_data.userTable[cid].func = func;
        _sif_cmd_data.userTable[cid].data = data;
        _sif_cmd_data.userTable[cid].gp = GetGp();
    }
}

void sceSifRemoveCmdHandler(unsigned int cid)
{
    if ((int)cid < 0) {
        _sif_cmd_data.sysTable[cid & ~SIF_CMD_SYSTEM].func = 0;
        return;
    }
    _sif_cmd_data.userTable[cid].func = 0;
}

unsigned int sceSifSendCmd(unsigned int cid, void *packet, int size, void *src, void *dest, int len)
{
    return _sceSifSendCmd(cid, 0, packet, size, src, dest, len);
}

unsigned int isceSifSendCmd(unsigned int cid, void *packet, int size, void *src, void *dest, int len)
{
    return _sceSifSendCmd(cid, 1, packet, size, src, dest, len);
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
