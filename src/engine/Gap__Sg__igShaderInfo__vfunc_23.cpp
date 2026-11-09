struct ShaderFieldRecord { char pad[8]; int *name; char pad2[8]; int kind; };
extern "C" {
int FUN_002e2d30(int, void *, int *, ShaderFieldRecord *, int, void *, void *);
extern int DAT_004e0858[4];
}
#include "dw4/igTDataList.h"
struct ShaderFieldTable { char pad[20]; igTDataList<ShaderFieldRecord *> *list; };
extern "C" int Gap__Sg__igShaderInfo__vfunc_23(ShaderFieldTable *self, int arg1, ShaderFieldRecord *key) {
    igTDataList<ShaderFieldRecord *> *list = self->list;
    int idx = list->find(key);
    ShaderFieldRecord *e;
    int *name;
    if (idx == -1) {
        return 0;
    }
    e = self->list->_data[idx];
    if (e->kind == 2) {
        return 0;
    }
    name = e->name;
    name = name != 0 ? name : &DAT_004e0858[0];
    FUN_002e2d30(arg1, self, name, key, idx, list, self);
    return 1;
}
