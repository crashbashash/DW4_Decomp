/* libcdvd.h - libcdvd's EE side (Sony libcdvd.h and the library's shared state): the RPC channels to
 * cdvdman, the buffers they use and the semaphores that guard them. The N-command channel carries disc
 * commands, the S-command channel drive commands. */
#ifndef DW4_SONY_LIBCDVD_H
#define DW4_SONY_LIBCDVD_H

#include "dw4/sony/sif.h"
#include "dw4/libkernl.h"

#define UNCACHED(p) ((void *)((unsigned int)(p) | 0x20000000))
#define UNCACHED_WORD(p) (*(int *)UNCACHED(p))

typedef void (*CdCallback)(int reason);
typedef void (*CdPowerOffCallback)(void *data);

/* A file's directory record as cdvdman returns it. */
typedef struct {
    unsigned int lsn;
    unsigned int size;
    char name[16];
    unsigned char date[8];
    unsigned int flag;
} sceCdlFILE;

/* How a read is done: retries, spindle speed and the sector size (SCECdSecS*). */
typedef struct {
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
} sceCdRMode;

#define SCECdSecS2048 0
#define SCECdSecS2328 1
#define SCECdSecS2340 2

/* sceCdInit modes */
#define SCECdINIT 0x00
#define SCECdINoD 0x01
#define SCECdEXIT 0x05

/* Callback reasons: the command in flight (sceCdCbfunc_num), which the IOP reports back when it ends. */
#define SCECdFuncRead 1
#define SCECdFuncSeek 4
#define SCECdFuncBreak 8
#define CD_FUNC_EXIT 11

/* The head and tail of a read that are not sector aligned: the IOP leaves them here, and the interrupt
 * handler copies them to the caller's buffer. */
typedef struct {
    int headSize;
    int tailSize;
    unsigned char *headDest;
    unsigned char *tailDest;
    unsigned char head[64];
    unsigned char tail[64];
} CdReadIntrData;

/* cdvdman's RPC servers */
#define CD_INIT_SERVER 0x80000592
#define CD_SCMD_SERVER 0x80000593
#define CD_NCMD_SERVER 0x80000595
#define CD_SEARCH_SERVER 0x80000597
#define CD_DISK_READY_OLD_SERVER 0x8000059a
#define CD_DISK_READY_SERVER 0x8000059c

/* the RPC functions of the N-command server */
#define CD_NCMD_SEARCH 0
#define CD_NCMD_READ 1
#define CD_NCMD_SEEK 5
#define CD_NCMD_DISK_READY 14

/* the RPC functions of the S-command server */
#define CD_SCMD_GET_ERROR 4
#define CD_SCMD_BREAK 22

/* The command numbers callers pass to _sceCd_*_prechk, kept to report which command holds the channel. */
#define CD_PRECHK_NCMD_DISK_READY 2
#define CD_PRECHK_GET_ERROR 3
#define CD_PRECHK_READ 4
#define CD_PRECHK_SEEK 9
#define CD_PRECHK_BREAK 30
#define CD_PRECHK_MMODE 34

/* The channel semaphores, the command in flight and the busy flag are shared with
 * _sceCd_cd_callback, which runs at interrupt time as the commands' end function. */
extern int SCE_CD_debug;
extern volatile int _sceCd_ee_read_mode;
extern volatile int _sceCd_ncmd_semid;
extern volatile int _sceCd_scmd_semid;
extern volatile int _sceCd_rcmd_semid;
extern volatile int _sceCd_c_cb_sem;
extern volatile int sceCdCbfunc_num;
extern volatile int sceCdCbfunc_number;
extern int _sceCd_ncmdrdata[24];
extern int _sceCd_ncmdsdata[1024];
extern CdReadIntrData _sceCd_rd_intr_data;
extern int _sceCd_Read_cur_pos[4];
extern sceSifClientData _sceCd_cd_ncmd;
extern int _sceCd_scmdrdata[264];
extern int _sceCd_scmdsdata[258];
extern int _sceCd_rcmdrdata[64];
extern sceSifClientData _sceCd_cd_scmd;


int sceCdSync(int mode);
int sceCdSyncS(int mode);
int sceCdNcmdDiskReady(void);
int sceCdDiskReady_old(int mode);
int sceCdLayerSearchFile(sceCdlFILE *fp, const char *name, int layer);
int _sceCd_ncmd_prechk(int cmd);
int _sceCd_scmd_prechk(int cmd);
void _sceCd_cd_callback(void *reason);
void _sceCd_cd_read_intr(void *param);

#endif
