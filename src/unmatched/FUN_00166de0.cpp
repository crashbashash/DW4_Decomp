#include "dw4/igSmartPointer.h"

struct ShaderSetup {
    char pad[56];
    void *registry;
    void *builder;
};

extern "C" {
void *FUN_00165ce0(void);
igIntList *FUN_002cba00(void *allocator);
void FUN_00306e50(void *registry, int kind, const char *name, bool *found, int a, int b);
void List_Resize(igIntList *list, int count, int size);
void FUN_002da010(void *builder, igIntList *list);
int FUN_00305cf0(void);
int FUN_002da1c0(void *builder, const char *a, const char *b);
void FUN_002da990(void *builder, void *registry, int kind, int flags);
void FUN_002daab0(void *builder, void *registry, int kind, int flags);
extern ShaderSetup *DAT_00586dc8;
extern char DAT_004df150[];
extern char DAT_004dc870[];
}

static inline int countOf(const igIntList *list) { return list->_count; }

extern "C" void FUN_00166de0(int value)
{
    int count;
    void *registry = DAT_00586dc8->registry;
    void *builder = DAT_00586dc8->builder;
    igSmartPointer<igIntList> list(FUN_002cba00(FUN_00165ce0()));
    bool found = false;

    FUN_00306e50(registry, 4, DAT_004df150, &found, 0, 1);
    if (found) return;
    igIntList *l = list;
    count = l->_count;
    if (count < l->_capacity) {
        l->_count = countOf(l) + 1;
    } else {
        List_Resize(l, count + 1, 4);
    }
    ((int *)l->_data)[count] = value;
    FUN_002da010(builder, list);
    if (FUN_00305cf0() != 0) {
        if (FUN_002da1c0(builder, DAT_004dc870, DAT_004dc870) != 0) FUN_002da990(builder, registry, 4, 0);
    }
    FUN_002daab0(builder, registry, 4, 0);
}
