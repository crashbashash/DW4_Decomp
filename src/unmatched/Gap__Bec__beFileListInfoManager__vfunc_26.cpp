#include "dw4/reflected.h"
/* Release every retained object of a list and reset its count; the reference
 * count is the low 23 bits of igObject::_refCount. */
#define CLEAR(T, src) { \
    T *l = (T *)(src); \
    int n = l->_count; \
    int i; \
    int m; \
    int j; \
    igObject *o; \
    for (i = 0; i < n; i++) { \
        o = ((igObject **)l->_data)[i]; \
        if (o != 0) { \
            o->_refCount = (int)o->_refCount - 1; \
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o); \
        } \
    } \
    m = l->_count; \
    for (j = 0; j < m; j++) { \
        ((igObject **)l->_data)[j] = 0; \
    } \
    l->_count = 0; }

extern "C" {
extern int DAT_00586f20[4];
int FUN_002eb010(int);
int List_Reserve(void *, int, int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int igObject_Destroy(igObject *);
void Gap__Bec__beFileListInfoManager__vfunc_26(beFileListInfoManager *arg0);
}

void Gap__Bec__beFileListInfoManager__vfunc_26(beFileListInfoManager *arg0) {
    igStringRefList *s5;
    int s4;
    int i;
    int **slot;
    int *s1;
    int off;
    int *old;
    int v;
    CLEAR(igInfoList, arg0->_infoList)
    CLEAR(igDirectoryList, arg0->_dirList)
    s5 = (igStringRefList *)arg0->_fnames;
    s4 = s5->_count;
    i = 0;
    if (0 < s4) {
        off = 0;
        do {
            slot = (int **)((char *)s5->_data + off);
            if (DAT_00586f20[0] == 0) {
                v = FUN_002eb010(0x10);
                if (v != 0) {
                    v = StringPool_Construct(v);
                }
                DAT_00586f20[0] = v;
            }
            s1 = (int *)StringPool_Intern(DAT_00586f20[0], 0);
            old = *slot;
            if (old != 0) {
                int *hdr = old - 2;
                int r = old[-1] - 1;
                old[-1] = r;
                if (r == 0) {
                    StringChunk_ReleaseHeader(*hdr, hdr);
                }
            }
            i += 1;
            *slot = s1;
            off += 4;
        } while (i < s4);
    }
    s5->_count = 0;
    CLEAR(igInfoList, arg0->_importantInfoList)
    CLEAR(igInfoList, arg0->_readInfoList)
    {
        igInfoList *l2 = (igInfoList *)arg0->_infoList;
        if (!(0 < l2->_count)) {
            List_Reserve(l2, 0, 4);
        }
    }
    {
        igDirectoryList *l2 = (igDirectoryList *)arg0->_dirList;
        if (!(0 < l2->_count)) {
            List_Reserve(l2, 0, 4);
        }
    }
    {
        igInfoList *l2 = (igInfoList *)arg0->_importantInfoList;
        if (!(0 < l2->_count)) {
            List_Reserve(l2, 0, 4);
        }
    }
    {
        igInfoList *l2 = (igInfoList *)arg0->_readInfoList;
        if (!(0 < l2->_count)) {
            List_Reserve(l2, 0, 4);
        }
    }
    arg0->_loaded = 0;
}
