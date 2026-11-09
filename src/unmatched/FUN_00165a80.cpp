#include "dw4/igTDataList.h"

struct VisualContextCapabilityManager;

struct PropertyRoot {
    char pad0[56];
    void *properties;
};

struct VisualContextCapabilityManager {
    int _vtable;
    unsigned int _refCount;
    char pad8[12];
    int index;
    char pad24[36];
    unsigned char showFrameRate;
    unsigned char commandLineFrame;
};

typedef igTDataList<VisualContextCapabilityManager *> ManagerList;

extern "C" {
void Gap__Core__igObject__vfunc_07(VisualContextCapabilityManager *self);
void *Memory_GetAllocatorBySelector(int selector);
ManagerList *FUN_00149ea0(void *allocator);
int thunk_FUN_00306e50(void *properties, int group, const char *name, unsigned char *value, int fallback, int load);
extern ManagerList *DAT_00560758;
extern int DAT_00587038;
extern PropertyRoot *DAT_00586dc8;
extern char DAT_004df0a0[];
extern char DAT_004df0b0[];
void FUN_00165a80(VisualContextCapabilityManager *self);
}

void FUN_00165a80(VisualContextCapabilityManager *self) {
    unsigned char showFrameRate;
    unsigned char commandLineFrame;
    void *properties;
    ManagerList *list;
    int count;

    Gap__Core__igObject__vfunc_07(self);
    if (DAT_00560758 == 0) {
        DAT_00560758 = FUN_00149ea0(Memory_GetAllocatorBySelector(DAT_00587038));
    }
    self->index = DAT_00560758->_count;
    list = DAT_00560758;
    count = list->count();
    if (count < list->_capacity) {
        list->_count = list->_count + 1;
    } else {
        List_Resize(list, count + 1, 4);
    }
    list->_data[count] = self;
    properties = DAT_00586dc8->properties;
    showFrameRate = self->showFrameRate;
    commandLineFrame = self->commandLineFrame;
    thunk_FUN_00306e50(properties, 4, DAT_004df0a0, &showFrameRate, showFrameRate, 1);
    thunk_FUN_00306e50(properties, 4, DAT_004df0b0, &commandLineFrame, commandLineFrame, 1);
    self->showFrameRate = showFrameRate;
    self->commandLineFrame = commandLineFrame;
}
