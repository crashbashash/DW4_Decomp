#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
int igObject_GetAllocator(...);
igContextExtInfoList *FUN_002cb4b0(int);
igContextExtInfo *FUN_002cb660(int);
int FUN_002eb010(int);
int List_Reserve(igContextExtInfoList *, int, int);
int ObjectList_ResizeRetained(igContextExtInfoList *, int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int igMetaObject_CountTree(int);
int igObjectSystem_FindMetaByNameDefault(void *);
igMetaObject *FUN_002fe300(int, int);
extern int DAT_004f86f8[4];
extern int DAT_00586f20[4];
}
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset 88 */
struct DummyVirtualContext { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void vX(); };
struct Util {
    static inline void rel(igObject *o) { if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void FUN_002d60b0(igContext *arg0) {
    if (arg0->_pExtList == 0) {
        igContextExtInfoList *l;
        int meta;
        int i;
        l = FUN_002cb4b0(igObject_GetAllocator());
        if (l != 0) ++l->_refCount;
        Util::rel((igObject *)arg0->_pExtList);
        arg0->_pExtList = (int)l;
        {
            igContextExtInfoList *o = (igContextExtInfoList *)arg0->_pExtList;
            --o->_refCount;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((igObject *)o);
        }
        ((DummyVirtualContext *)arg0)->vX();
        meta = igObjectSystem_FindMetaByNameDefault(&DAT_004f86f8[0]);
        arg0->_iNumExts = igMetaObject_CountTree(meta) - 1;
        if (arg0->_iNumExts >= ((igContextExtInfoList *)arg0->_pExtList)->_count) List_Reserve((igContextExtInfoList *)arg0->_pExtList, arg0->_iNumExts, 4);
        ObjectList_ResizeRetained((igContextExtInfoList *)arg0->_pExtList, arg0->_iNumExts);
        for (i = 0; i < arg0->_iNumExts; i++) {
            int nm;
            igMetaObject *nd;
            igContextExtInfo *it;
            igContextExtInfoList *lst;
            nd = FUN_002fe300(meta, i + 1);
            it = FUN_002cb660(igObject_GetAllocator(arg0));
            if (nd != 0) ++nd->_refCount;
            Util::rel((igObject *)it->_pMeta);
            it->_pMeta = (int)nd;
            nm = nd->_name;
            if (DAT_00586f20[0] == 0) {
                int al = FUN_002eb010(16);
                if (al != 0) al = StringPool_Construct(al);
                DAT_00586f20[0] = al;
            }
            {
                int sv = StringPool_Intern(DAT_00586f20[0], nm);
                int old = it->_pName;
                if (old != 0) {
                    int *h = (int *)(old - 8);
                    int c = *(int *)(old - 4) - 1;
                    *(int *)(old - 4) = c;
                    if (c == 0) StringChunk_ReleaseHeader(*h, h);
                }
                it->_pName = sv;
            }
            it->_pVendorName = 0;
            lst = (igContextExtInfoList *)arg0->_pExtList;
            if (it != 0) ++it->_refCount;
            Util::rel(((igObject **)lst->_data)[i]);
            if (lst->_count != 0 && i >= 0 && i < lst->_count) ((igContextExtInfo **)lst->_data)[i] = it;
            --it->_refCount;
            if ((it->_refCount & 0x7fffff) == 0) igObject_Destroy((igObject *)it);
        }
    }
}
