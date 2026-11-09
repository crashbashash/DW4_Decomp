#include "dw4/igSmartPointer.h"

extern "C" {
struct Instance : public igObject { };
int igInsightPlugin_GetMetaObject();
int igMetaObject_CountTree(int);
int FUN_002fe300(int, int);
int igObject_GetAllocator(int);
int FUN_00236dd0(int, Instance *);
igSmartPointer<Instance> FUN_002fd6e0(int, int);
}

extern "C" void FUN_00236ca0(int self) {
    int meta;
    int count;
    int i;
    count = igMetaObject_CountTree(meta = igInsightPlugin_GetMetaObject());
    for (i = 0; i < count; i++) {
        int type = FUN_002fe300(meta, i);
        igSmartPointer<Instance> plugin(FUN_002fd6e0(type, igObject_GetAllocator(self)).get(), kRetainReference);
        if (plugin.get()) {
            FUN_00236dd0(self, plugin.get());
        }
    }
}
