#include "dw4/reflected.h"
typedef struct Obj { int pad0[4]; unsigned char flag; } Obj;
typedef struct Folder { int pad0[2]; int count; int pad1; Obj **items; } Folder;
extern "C" {
int FUN_00236f80(...);
int FUN_00447ed0(...);
int List_Resize(...);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
void *beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
char *igProperty_GetRecordFolder(...);
extern int DAT_0051b398[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b528[4];
extern int DAT_0051bd70[4];
extern int DAT_0058b028[4];
}
extern "C" int FUN_004367c0(beNDMWShopCtrlDeviceSell *self);
int FUN_004367c0(beNDMWShopCtrlDeviceSell *self) {
    Folder *fold; int n; int v; int rem; int rows; int i; int idx; int c; Obj *o; bool mark; int k; igCharList *l;
    beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
    fold = *(Folder **)(igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), &DAT_0051b528[0]) + 12);
    n = fold->count;
    if (n % 12 != 0) v = n / 12 + 1; else v = n / 12;
    self->_maxPage = v;
    rem = n - self->_nowPage * 12;
    rows = (rem >= 12) ? 12 : rem % 12;
    i = 0;
    ((igCharList *)self->_decideList)->_count = 0;
    do {
        idx = i + self->_nowPage * 12;
        if (idx < n) {
            c = FUN_00236f80(self->_insight, DAT_0058b028[0]);
            o = fold->items[idx];
            mark = true;
            if (o->flag != 0) mark = false;
            else if (FUN_00447ed0(o, c, &DAT_0051bd70[0]) <= 0) mark = false;
            l = (igCharList *)self->_decideList;
            k = l->_count;
            if (k < l->_capacity) l->_count = k + 1; else List_Resize(l, k + 1, 1);
            *(char *)(k + (int)l->_data) = mark;
        }
        i++;
    } while (i < 12);
    return rows;
}
