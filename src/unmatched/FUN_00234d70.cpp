#include "dw4/igSmartPointer.h"

extern "C" {
struct InternedStringList : public igObject { };
int FUN_00235370(int, InternedStringList *);
InternedStringList *FUN_002b90e0(int);
int FUN_002eb010(int);
int Memory_GetAllocatorBySelector(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
char *StringPool_Intern(int, int);
extern int DAT_00586f20[4];
extern int DAT_00587028[4];
extern int DAT_00587060[4];
extern unsigned char GPR_00554c14;
struct StringRef {
    char *p;
    StringRef(int text) {
        char *interned;
        if (text == 0) {
            interned = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                int pool = FUN_002eb010(0x10);
                if (pool != 0) {
                    pool = StringPool_Construct(pool);
                }
                DAT_00586f20[0] = pool;
            }
            interned = StringPool_Intern(DAT_00586f20[0], text);
        }
        p = interned;
    }
    ~StringRef() {
        if (p != 0) {
            int *header = (int *)(p - 8);
            int left = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = left;
            if (left == 0) {
                StringChunk_ReleaseHeader(*header, header);
            }
        }
    }
};
int StringList_AppendRetained(InternedStringList *, StringRef *);

void FUN_00234d70(int self, int count, int *names) {
    int allocator;
    int i;
    if (GPR_00554c14 != 0) {
        allocator = Memory_GetAllocatorBySelector(DAT_00587028[0]);
    } else {
        allocator = Memory_GetAllocatorBySelector(DAT_00587060[0]);
    }
    igSmartPointer<InternedStringList> list(FUN_002b90e0(allocator));
    for (i = 0; i < count; i++) {
        int text = names[i];
        StringRef name(text);
        StringList_AppendRetained(list.get(), &name);
    }
    FUN_00235370(self, list.get());
}
}
