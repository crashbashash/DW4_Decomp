/* iopheap.c - libkernl's client of the IOP heap server: allocates and frees IOP memory and loads files
 * into it. Every call is one RPC with its arguments in a small send buffer and its answer in the
 * first word of the receive buffer. */
#include "dw4/sony/sif.h"

/* the IOP heap server's RPC functions */
#define IH_ALLOC_HEAP 1
#define IH_FREE 2
#define IH_LOAD_HEAP 3
#define IH_ALLOC_SYSMEM 4
#define IH_QUERY_MEM_SIZE 5
#define IH_QUERY_MAX_FREE 6
#define IH_QUERY_TOTAL_FREE 7
#define IH_QUERY_BLOCK_TOP 8
#define IH_QUERY_BLOCK_SIZE 9

#define IH_PATH_MAX 252

typedef struct {
    void *addr;
    char path[IH_PATH_MAX];
} IhLoadRequest;

/* the IOP heap server's RPC id */
#define IH_SERVER 0x80000003

/* negative until sceSifInitIopHeap has bound the server */
static int _bind = -1;
static sceSifClientData cd;
static unsigned int rdata[16] __attribute__((aligned(64)));
static unsigned int sdata[16];
static IhLoadRequest _lih_data __attribute__((aligned(64)));

/* Binds the IOP heap server, retrying until it is registered; negative when the bind fails. */
int sceSifInitIopHeap(void)
{
    int i;

    while (1) {
        if (sceSifBindRpc(&cd, IH_SERVER, 0) < 0) {
            return -1;
        }
        if (cd.serve != 0) {
            _bind = 0;
            break;
        }
        i = 0x100000;
        while (i--)
            ;
    }
    return 0;
}

void *sceSifAllocIopHeap(unsigned int size)
{
    if (_bind < 0) {
        return 0;
    }
    sdata[0] = size;
    if (sceSifCallRpc(&cd, IH_ALLOC_HEAP, 0, sdata, 4, rdata, 4, 0, 0) < 0) {
        return 0;
    }
    return (void *)rdata[0];
}

void *sceSifAllocSysMemory(int type, unsigned int size, void *addr)
{
    if (_bind < 0) {
        return 0;
    }
    sdata[0] = size;
    sdata[1] = type;
    sdata[2] = (unsigned int)addr;
    if (sceSifCallRpc(&cd, IH_ALLOC_SYSMEM, 0, sdata, 12, rdata, 4, 0, 0) < 0) {
        return 0;
    }
    return (void *)rdata[0];
}

int sceSifFreeSysMemory(void *addr)
{
    if (_bind < 0) {
        return 0;
    }
    sdata[0] = (unsigned int)addr;
    if (sceSifCallRpc(&cd, IH_FREE, 0, sdata, 4, rdata, 4, 0, 0) < 0) {
        return -1;
    }
    return rdata[0];
}

int sceSifFreeIopHeap(void *addr)
{
    return sceSifFreeSysMemory(addr);
}

int sceSifLoadIopHeap(const char *path, void *addr)
{
    int i;
    if (_bind < 0) {
        return 0;
    }
    for (i = 0; i < IH_PATH_MAX; i++) {
        if ((_lih_data.path[i] = path[i]) == 0) {
            break;
        }
    }
    if (i == IH_PATH_MAX) {
        i = IH_PATH_MAX - 1;
        _lih_data.path[IH_PATH_MAX - 1] = 0;
    }
    _lih_data.addr = addr;
    _lih_data.path[IH_PATH_MAX - 1] = 0;
    if (sceSifCallRpc(&cd, IH_LOAD_HEAP, 0, &_lih_data, i + 5, rdata, 4, 0, 0) < 0) {
        return -1;
    }
    return rdata[0];
}

unsigned int sceSifQueryMemSize(void)
{
    if (_bind < 0) {
        return 0;
    }
    if (sceSifCallRpc(&cd, IH_QUERY_MEM_SIZE, 0, 0, 0, rdata, 4, 0, 0) < 0) {
        return 0xFFFFFFFF;
    }
    return rdata[0];
}

unsigned int sceSifQueryMaxFreeMemSize(void)
{
    if (_bind < 0) {
        return 0;
    }
    if (sceSifCallRpc(&cd, IH_QUERY_MAX_FREE, 0, 0, 0, rdata, 4, 0, 0) < 0) {
        return 0xFFFFFFFF;
    }
    return rdata[0];
}

unsigned int sceSifQueryTotalFreeMemSize(void)
{
    if (_bind < 0) {
        return 0;
    }
    if (sceSifCallRpc(&cd, IH_QUERY_TOTAL_FREE, 0, 0, 0, rdata, 4, 0, 0) < 0) {
        return 0xFFFFFFFF;
    }
    return rdata[0];
}

unsigned int sceSifQueryBlockTopAddress(void *addr)
{
    if (_bind < 0) {
        return 0;
    }
    sdata[0] = (unsigned int)addr;
    if (sceSifCallRpc(&cd, IH_QUERY_BLOCK_TOP, 0, sdata, 4, rdata, 4, 0, 0) < 0) {
        return 0xFFFFFFFF;
    }
    return rdata[0];
}

unsigned int sceSifQueryBlockSize(void *addr)
{
    if (_bind < 0) {
        return 0;
    }
    sdata[0] = (unsigned int)addr;
    if (sceSifCallRpc(&cd, IH_QUERY_BLOCK_SIZE, 0, sdata, 4, rdata, 4, 0, 0) < 0) {
        return 0xFFFFFFFF;
    }
    return rdata[0];
}
