#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
int beNDMWWindow_RunMessageScript(...);
int beNDMWWindow_PresentModelAtOrigin(...);
int FUN_003f5410(...);
extern int DAT_0051c800[4];
extern int DAT_0051c810[4];
extern int DAT_0051c5e8[4];
extern int DAT_0051c818[4];
extern int DAT_0051c4c0[4];
extern int DAT_0051c828[4];
extern int DAT_0051c660[4];
extern int DAT_0051c730[4];
extern int DAT_0051c838[4];
extern int DAT_0051c488[4];
extern int DAT_0051c498[4];
extern int DAT_0051c4a0[4];
extern int DAT_0051c4b0[4];
extern int DAT_00586f20[4];
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]): releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(int s) : p((char *)s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
struct StringRefHelpers { static inline int intern(int *s) {
    int ref;
    int pool;
    if (s == 0) {
        ref = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool)
                pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        ref = StringPool_Intern(DAT_00586f20[0], s);
    }
    return ref;
}
static inline void release(int ref) {
    int *header;
    int count;
    if (ref) {
        header = (int *)(ref - 8);
        count = *(int *)(ref - 4) - 1;
        *(int *)(ref - 4) = count;
        if (!count)
            StringChunk_ReleaseHeader(*header, header);
    }
} };
extern "C" void Gap__Bec__beNDMWShopSelectA0__vfunc_22(beNDMWShopSelectA0 *arg0);
void Gap__Bec__beNDMWShopSelectA0__vfunc_22(beNDMWShopSelectA0 *arg0) {
    int pool;
    int ref;
    int old;
    beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051c800[0], 0, &DAT_0051c810[0], &DAT_0051c5e8[0]);
    { int tok = StringRefHelpers::intern(&DAT_0051c818[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c498[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c818[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c4c0[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], 0x7D1);
    FUN_003f5410(arg0, &DAT_0051c828[0], &DAT_0051c498[0], &DAT_0051c660[0], &DAT_0051c730[0]);
    FUN_003f5410(arg0, &DAT_0051c828[0], &DAT_0051c4c0[0], &DAT_0051c660[0], &DAT_0051c730[0]);
    if (DAT_00586f20[0] == 0) {
        pool = FUN_002eb010(16);
        if (pool)
            pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    ref = StringPool_Intern(DAT_00586f20[0], &DAT_0051c838[0]);
    old = arg0->_infoName;
    StringRefHelpers::release(old);
    arg0->_infoName = ref;
    arg0->_selectMax = 9;
    arg0->_offsetPos[0] = 0;
    arg0->_offsetPos[1] = 0;
    arg0->_offsetPos[2] = 0;
    arg0->_startPoint = 0;
    arg0->_isNoCancel = 0;
}
