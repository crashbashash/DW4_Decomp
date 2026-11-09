#include "dw4/igSmartPointer.h"

struct InterfaceItem : public igObject { };
extern "C" {

int FUN_002295b0(int, InterfaceItem *);
int StringChunk_ReleaseHeader(int, int *);
}
struct StringRef {
    char *s;
    StringRef(const StringRef &other) : s(other.s) {
        if (s != 0) {
            *(int *)(s - 4) = *(int *)(s - 4) + 1;
        }
    }
    ~StringRef() {
        if (s != 0) {
            int *header = (int *)(s - 8);
            if (--header[1] == 0) {
                StringChunk_ReleaseHeader(header[0], header);
            }
        }
    }
};

extern "C" igSmartPointer<igObject> FUN_002fd610(int);
extern "C" int FUN_0022a040(int, StringRef, int);
extern "C" igSmartPointer<InterfaceItem> Gap__igItemInterface__vfunc_27(int self, const StringRef &name, int kind) {
    int key = FUN_0022a040(self, name, kind);
    if (key == 0) {
        return igSmartPointer<InterfaceItem>((InterfaceItem *)0, kRetainReference);
    }
    igSmartPointer<InterfaceItem> item(FUN_002fd610(key));
    if (item.get() != 0) {
        FUN_002295b0(self, item.get());
    }
    return item;
}
