#include "dw4/reflected.h"
extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
int beNDMWWindow_RunMessageScript(void *, int *, int);
extern int DAT_0051c4a0[4];
extern int DAT_0051c488[4];
extern int DAT_0051c498[4];
extern int DAT_0051c4c0[4];
extern int DAT_0051c4c8[4];
extern int DAT_0051c4d0[4];
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
extern "C" void Gap__Bec__beNDMWShopSelect01__vfunc_22(beNDMWShopSelect01 *arg0) {
    const char *sp4C;
    const char *sp48;
    const char *u1, *u2, *u3, *u4;
    const char *t4C, *t48;
    const char *old;
    const char *n;
    switch (arg0->_entCode) {
    case 0x48B: case 0x48E: case 0x493: case 0x4E7: case 0x4EA: case 0x4F8: case 0x54B:
    case 0x614: case 0x678: case 0x6DC: case 0x740: case 0x61A: case 0x5AD: case 0x7AA:
        INTERN_APPEND(arg0->_textCloseTypeList, DAT_0051c488)
        INTERN_APPEND(arg0->_textCloseNameList, DAT_0051c498)
        INTERN_APPEND(arg0->_textCloseTypeList, DAT_0051c488)
        INTERN_APPEND(arg0->_textCloseNameList, DAT_0051c4c0)
        beNDMWWindow_RunMessageScript(arg0, DAT_0051c4a0, arg0->_entCode);
        arg0->_selectMax = 2;
        break;
    case 0x47E: case 0x546: case 0x60E: case 0x672: case 0x6D6: case 0x73A: case 0x79E:
        INTERN_APPEND(arg0->_textCloseTypeList, DAT_0051c488)
        INTERN_APPEND(arg0->_textCloseNameList, DAT_0051c498)
        INTERN_APPEND(arg0->_textCloseTypeList, DAT_0051c488)
        INTERN_APPEND(arg0->_textCloseNameList, DAT_0051c4c0)
        INTERN_APPEND(arg0->_textCloseTypeList, DAT_0051c488)
        INTERN_APPEND(arg0->_textCloseNameList, DAT_0051c4c8)
        beNDMWWindow_RunMessageScript(arg0, DAT_0051c4a0, arg0->_entCode);
        arg0->_selectMax = 3;
        break;
    }
    if (DAT_00586f20[0] == 0) {
        void *pool = FUN_002eb010(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    n = StringPool_Intern(DAT_00586f20[0], (const char *)DAT_0051c4d0);
    old = (const char *)arg0->_infoName;
    if (old != 0) {
        int *hd = (int *)old - 2;
        int cnt = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = cnt;
        if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    arg0->_infoName = (int)n;
    arg0->_offsetPos[0] = 0;
    arg0->_offsetPos[1] = 0;
    arg0->_offsetPos[2] = 0;
    arg0->_isNoCancel = 0;
}
