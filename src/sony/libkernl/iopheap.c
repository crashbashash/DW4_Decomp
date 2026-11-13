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

/* negative until sceSifInitIopHeap has bound the server */
extern int _ih_bind;
extern sceSifClientData _ih_cd;
extern unsigned int _ih_rdata[16];
extern unsigned int _ih_sdata[16];
extern IhLoadRequest _lih_data;

void *sceSifAllocIopHeap(unsigned int size)
{
    if (_ih_bind < 0) {
        return 0;
    }
    _ih_sdata[0] = size;
    if (sceSifCallRpc(&_ih_cd, IH_ALLOC_HEAP, 0, _ih_sdata, 4, _ih_rdata, 4, 0, 0) < 0) {
        return 0;
    }
    return (void *)_ih_rdata[0];
}

void *sceSifAllocSysMemory(int type, unsigned int size, void *addr)
{
    if (_ih_bind < 0) {
        return 0;
    }
    _ih_sdata[0] = size;
    _ih_sdata[1] = type;
    _ih_sdata[2] = (unsigned int)addr;
    if (sceSifCallRpc(&_ih_cd, IH_ALLOC_SYSMEM, 0, _ih_sdata, 12, _ih_rdata, 4, 0, 0) < 0) {
        return 0;
    }
    return (void *)_ih_rdata[0];
}

int sceSifFreeSysMemory(void *addr)
{
    if (_ih_bind < 0) {
        return 0;
    }
    _ih_sdata[0] = (unsigned int)addr;
    if (sceSifCallRpc(&_ih_cd, IH_FREE, 0, _ih_sdata, 4, _ih_rdata, 4, 0, 0) < 0) {
        return -1;
    }
    return _ih_rdata[0];
}

int sceSifFreeIopHeap(void *addr)
{
    return sceSifFreeSysMemory(addr);
}

int sceSifLoadIopHeap(const char *path, void *addr)
{
    int i;
    if (_ih_bind < 0) {
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
    if (sceSifCallRpc(&_ih_cd, IH_LOAD_HEAP, 0, &_lih_data, i + 5, _ih_rdata, 4, 0, 0) < 0) {
        return -1;
    }
    return _ih_rdata[0];
}

unsigned int sceSifQueryMemSize(void)
{
    if (_ih_bind < 0) {
        return 0;
    }
    if (sceSifCallRpc(&_ih_cd, IH_QUERY_MEM_SIZE, 0, 0, 0, _ih_rdata, 4, 0, 0) < 0) {
        return 0xFFFFFFFF;
    }
    return _ih_rdata[0];
}

unsigned int sceSifQueryMaxFreeMemSize(void)
{
    if (_ih_bind < 0) {
        return 0;
    }
    if (sceSifCallRpc(&_ih_cd, IH_QUERY_MAX_FREE, 0, 0, 0, _ih_rdata, 4, 0, 0) < 0) {
        return 0xFFFFFFFF;
    }
    return _ih_rdata[0];
}

unsigned int sceSifQueryTotalFreeMemSize(void)
{
    if (_ih_bind < 0) {
        return 0;
    }
    if (sceSifCallRpc(&_ih_cd, IH_QUERY_TOTAL_FREE, 0, 0, 0, _ih_rdata, 4, 0, 0) < 0) {
        return 0xFFFFFFFF;
    }
    return _ih_rdata[0];
}

unsigned int sceSifQueryBlockTopAddress(void *addr)
{
    if (_ih_bind < 0) {
        return 0;
    }
    _ih_sdata[0] = (unsigned int)addr;
    if (sceSifCallRpc(&_ih_cd, IH_QUERY_BLOCK_TOP, 0, _ih_sdata, 4, _ih_rdata, 4, 0, 0) < 0) {
        return 0xFFFFFFFF;
    }
    return _ih_rdata[0];
}

unsigned int sceSifQueryBlockSize(void *addr)
{
    if (_ih_bind < 0) {
        return 0;
    }
    _ih_sdata[0] = (unsigned int)addr;
    if (sceSifCallRpc(&_ih_cd, IH_QUERY_BLOCK_SIZE, 0, _ih_sdata, 4, _ih_rdata, 4, 0, 0) < 0) {
        return 0xFFFFFFFF;
    }
    return _ih_rdata[0];
}
