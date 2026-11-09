#include "dw4/igSmartPointer.h"

struct Ref : public igObject { char *str; int len; };
extern "C" {
Ref *FUN_002b9500(...);
int FUN_002eb010(...);
int FUN_0030b3c0(...);
int FUN_0030b5c0(...);
int FUN_0030bbf0(...);
int Memory_GetAllocatorBySelector(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
extern char *DAT_004c22f0[4];
extern int DAT_00586f20[4];
extern int DAT_00587048[4];
}

extern "C" int FUN_001554a0(int *arg0, int arg1) {
    int i;
    char *s;
    int r;
    igSmartPointer<Ref> text(FUN_002b9500(Memory_GetAllocatorBySelector(DAT_00587048[0])));
    FUN_0030b3c0(text.get(), arg1);
    FUN_0030b5c0(text.get());
    for (i = text.get()->len - 1; i >= 0; i--) {
        if (text.get()->str[i] == 0x5F) {
            FUN_0030bbf0(text.get(), i, 1);
        }
    }
    s = text.get()->str;
    if (s == 0) {
        s = DAT_004c22f0[0];
    }
    if (s == 0) {
        r = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            r = FUN_002eb010(0x10);
            if (r != 0) {
                r = StringPool_Construct(r);
            }
            DAT_00586f20[0] = r;
        }
        r = StringPool_Intern(DAT_00586f20[0], s);
    }
    *arg0 = r;
    return 0;
}
