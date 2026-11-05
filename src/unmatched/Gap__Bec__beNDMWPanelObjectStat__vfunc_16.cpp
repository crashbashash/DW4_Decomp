#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
extern void *DAT_00586f20[4];
}
/* matching construct: inline release helper reproduces the retail inlined refcount release */
struct RefRelease { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void Gap__Bec__beNDMWPanelObjectStat__vfunc_16(beNDMWPanelObjectStat *arg0);
void Gap__Bec__beNDMWPanelObjectStat__vfunc_16(beNDMWPanelObjectStat *arg0) {
/* matching construct: locals zero-initialised and declared in the order that reproduces retail register assignment */
    igDataList *l = 0;
    int n = 0;
    int i = 0;
    const char *held = 0;
    const char **slot = 0;
    const char *tok = 0;
    int off = 0;
    RefRelease::go((igObject *)arg0->_playerDataList);
    arg0->_playerDataList = 0;
    RefRelease::go((igObject *)arg0->_playerWork);
    arg0->_playerWork = 0;
    l = (igDataList *)arg0->_listFolder;
    n = l->_count;
    i = 0;
    if (0 < n) {
        off = 0;
        do {
            slot = (const char **)((char *)l->_data + off);
            if (DAT_00586f20[0] == 0) {
                void *pool = FUN_002eb010(0x10);
                if (pool != 0) pool = StringPool_Construct(pool);
                DAT_00586f20[0] = pool;
            }
            tok = StringPool_Intern(DAT_00586f20[0], 0);
            held = *slot;
            if (held != 0) {
                int *hd = (int *)held - 2;
                int cnt = ((int *)held)[-1] - 1;
                ((int *)held)[-1] = cnt;
                if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd);
            }
            i++;
            *slot = tok;
            off += 4;
        } while (i < n);
    }
    l->_count = 0;
    ((igDataList *)arg0->_listColor)->_count = 0;
}
