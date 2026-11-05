#include "dw4/reflected.h"

extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectReceivers(int, int *, int, int);
extern int DAT_00518700[4];
extern int DAT_00518708[4];
extern int DAT_00518710[4];
extern int DAT_00518718[4];
extern int DAT_00518720[4];
extern void *DAT_00586f20[4];
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at p[-2]):
 * releases the token on scope exit.  The out-of-line copy the exception table names is the retail
 * body StringRef_Destruct_00130720 (config/SLUS-20836/unit-objects.json, duplicate __dt__9StringRefFv). */
class StringRef {
public:
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, StringRef *);
/* intern `text` (the pool singleton is created on first use) and append the token to `field` */
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
extern "C" void FUN_003f5410(beNDMWWindow *arg0, int *arg1, int *arg2, int *arg3, int *arg4) {
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00518700, 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, arg2);
    beMessenger_AppendString(arg0->_messenger, arg4);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00518708);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00518700, 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, arg2);
    beMessenger_AppendString(arg0->_messenger, arg3);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00518710);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00518700, 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, arg2);
    beMessenger_AppendString(arg0->_messenger, DAT_00518718);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00518720);
    INTERN_APPEND(arg0->_textCloseTypeList, arg1)
    INTERN_APPEND(arg0->_textCloseNameList, arg2)
}
