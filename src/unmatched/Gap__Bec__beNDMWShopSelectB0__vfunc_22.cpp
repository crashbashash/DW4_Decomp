#include "dw4/reflected.h"
/* _decideList target: count at +8, byte flags at +16. */
typedef struct DecideFlagList { char p0[8]; int count; char p12[4]; unsigned char *data; } DecideFlagList;
extern "C" {
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int *);
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
int beNDMWWindow_RunMessageScript(beNDMWShopSelectB0 *, int *, int);
typedef struct { int lo; int hi; } IntPair;
extern IntPair DAT_004cfb30[4];
extern int DAT_0051c488[4];
extern int DAT_0051c498[4];
extern int DAT_0051c4a0[4];
extern int DAT_0051c4c0[4];
extern int DAT_0051c4d0[4];
extern int DAT_0051c5f8[4];
extern int DAT_0051c6e8[4];
extern int DAT_0051c700[4];
extern int DAT_0051c848[4];
extern int DAT_00586f20[4];
void Gap__Bec__beNDMWShopSelectB0__vfunc_22(beNDMWShopSelectB0 *arg0);
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    void *p;
    StringRef(void *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
#define INTERN_APPEND(field, text) { \
    void *tok; \
    if ((text) == 0) { tok = (void *)0; } else { \
        if (DAT_00586f20[0] == 0) { int pool = FUN_002eb010(0x10); if (pool != 0) { pool = StringPool_Construct(pool); } DAT_00586f20[0] = pool; } \
        tok = StringPool_Intern(DAT_00586f20[0], (text)); } \
    StringList_AppendRetained(field, StringRef(tok)); }
/* matching construct: every (DecideFlagList * volatile *)&arg0->_decideList read keeps the field volatile so each use reloads it, as retail does */
void Gap__Bec__beNDMWShopSelectB0__vfunc_22(beNDMWShopSelectB0 *arg0) {
    int tv1;
    int s1;
    int *a1;
    int *s0;
    void *a0;
    int t;
    int *s3;
    void *s0b;
    INTERN_APPEND(arg0->_textCloseTypeList, &DAT_0051c488[0])
    INTERN_APPEND(arg0->_textCloseNameList, &DAT_0051c5f8[0])
    INTERN_APPEND(arg0->_textCloseTypeList, &DAT_0051c488[0])
    INTERN_APPEND(arg0->_textCloseNameList, &DAT_0051c498[0])
    INTERN_APPEND(arg0->_textCloseTypeList, &DAT_0051c488[0])
    INTERN_APPEND(arg0->_textCloseNameList, &DAT_0051c4c0[0])
    beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], 0x625);
    if (*(DecideFlagList * volatile *)&arg0->_decideList != 0) {
        IntPair labels = DAT_004cfb30[0];
        s0 = (int *)&labels;
        s1 = 0;
        if (0 < (*(DecideFlagList * volatile *)&arg0->_decideList)->count) {
            do {
                if ((*(DecideFlagList * volatile *)&arg0->_decideList)->data[s1] != 0) {
                    s3 = &DAT_0051c700[0];
                } else {
                    s3 = &DAT_0051c848[0];
                }
                beMessenger_SelectGroup(arg0->_messenger, &DAT_0051c6e8[0]);
                beMessenger_AppendString(arg0->_messenger, &DAT_0051c488[0]);
                beMessenger_AppendString(arg0->_messenger, (int *)*s0);
                beMessenger_DispatchSelected(arg0->_messenger, s3);
                s1 = s1 + 1;
                s0 = s0 + 1;
            } while (s1 < (*(DecideFlagList * volatile *)&arg0->_decideList)->count);
        }
    }
    if (DAT_00586f20[0] == 0) {
        t = FUN_002eb010(0x10);
        if (t != 0) {
            t = StringPool_Construct(t);
        }
        DAT_00586f20[0] = t;
    }
    s0b = StringPool_Intern(DAT_00586f20[0], &DAT_0051c4d0[0]);
    a0 = (void *)arg0->_infoName;
    if (a0 != 0) {
        a1 = (int *)((char *)a0 - 8);
        tv1 = *(int *)((char *)a0 - 4) - 1;
        *(int *)((char *)a0 - 4) = tv1;
        if (tv1 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    arg0->_infoName = (int)s0b;
    arg0->_selectMax = 2;
    arg0->_offsetPos[0] = 0;
    arg0->_offsetPos[1] = 0;
    arg0->_offsetPos[2] = 0;
    arg0->_startPoint = 0;
    arg0->_isNoCancel = 0;
}
