#include "dw4/reflected.h"
extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
int List_Resize(void *, int, int);
int beMessenger_AppendString(int, const char *);
int beMessenger_AppendVec3(int, float *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetBool(int, int);
int beMessenger_SelectReceivers(int, int *, const char *, int);
int beMessenger_SendNamed(int, int *, const char *, int, const char *);
extern int DAT_00518738[4];
extern int DAT_00518748[4];
extern int DAT_00518750[4];
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
extern "C" void beNDMWWindow_PresentModel(beNDMWWindow *arg0, const char *arg1, int arg2, const char *arg3, const char *arg4, float *arg5);
void beNDMWWindow_PresentModel(beNDMWWindow *arg0, const char *arg1, int arg2, const char *arg3, const char *arg4, float *arg5) {
    float v[3];
    beMessenger_SendNamed(arg0->_messenger, DAT_00518738, arg1, arg2, (const char *)DAT_00518748);
    if (beMessenger_GetBool(arg0->_messenger, 0) != 0) {
        beMessenger_SendNamed(arg0->_messenger, DAT_00518738, arg1, arg2, arg3);
    } else {
        beMessenger_SelectReceivers(arg0->_messenger, DAT_00518738, arg1, arg2);
        beMessenger_AppendString(arg0->_messenger, arg3);
        v[0] = arg5[0];
        v[1] = arg5[1];
        v[2] = arg5[2];
        beMessenger_AppendVec3(arg0->_messenger, v);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_00518750);
    }
    if (arg4 != 0) {
        INTERN_APPEND(arg0->_modelCloseInfoNameList, arg1)
        {
            int n; igDataList *l = (igDataList *)arg0->_modelCloseRamNoList;
            n = l->_count;
            if (n < l->_capacity) l->_count = /* matching construct: volatile reload of _count */ *(volatile int *)&l->_count + 1; else List_Resize(l, n + 1, 4);
            ((int *)l->_data)[n] = arg2;
        }
        INTERN_APPEND(arg0->_modelCloseSeqNameList, arg4)
    }
}
