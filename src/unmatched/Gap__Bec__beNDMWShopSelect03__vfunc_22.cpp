#include "dw4/reflected.h"
extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
int beNDMWWindow_RunMessageScript(void *, int *, int);
extern int DAT_0051c4a0[4];
extern int DAT_0051c530[4];
extern int DAT_0051c5a8[4];
extern int DAT_0051c5b0[4];
extern void *DAT_00586f20[4];
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, StringRef *);
#define INTERN_APPEND(field, text) { \
    const char *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (DAT_00586f20[0] == 0) { \
            void *pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            DAT_00586f20[0] = pool; \
        } \
        tok = StringPool_Intern(DAT_00586f20[0], (const char *)(text)); \
    } \
    StringRef held(tok); \
    StringList_AppendRetained(field, &held); }
extern "C" void Gap__Bec__beNDMWShopSelect03__vfunc_22(beNDMWShopSelect03 *arg0) {
    const char *old;
    const char *n;
    if (arg0->_entCode > 0) {
        INTERN_APPEND(arg0->_textCloseTypeList, DAT_0051c530)
        INTERN_APPEND(arg0->_textCloseNameList, DAT_0051c5a8)
        beNDMWWindow_RunMessageScript(arg0, DAT_0051c4a0, arg0->_entCode);
    }
    if (DAT_00586f20[0] == 0) {
        void *pool = FUN_002eb010(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    n = StringPool_Intern(DAT_00586f20[0], (const char *)DAT_0051c5b0);
    old = (const char *)arg0->_infoName;
    if (old != 0) {
        int *hd = (int *)old - 2;
        int cnt = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = cnt;
        if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    arg0->_infoName = (int)n;
    arg0->_selectMax = 1;
    arg0->_offsetPos[0] = 0;
    arg0->_offsetPos[1] = 0;
    arg0->_offsetPos[2] = 0;
    arg0->_startPoint = 0;
    arg0->_isNoCancel = 0;
}
