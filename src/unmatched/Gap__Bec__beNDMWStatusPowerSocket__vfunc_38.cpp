struct Item { char p[16]; char f16; };
struct Lst { char p[8]; int count; int pad; Item **items; };
struct Obj { char p[112]; Lst *list; };
extern "C" int ObjectList_FillRetained(Lst *, int);
extern "C" void Gap__Bec__beNDMWStatusPowerSocket__vfunc_38(Obj *arg0) {
    int off;
    int i = 0;
    if (0 < arg0->list->count) {
        off = 0;
        do {
            Item *it = *(Item **)((char *)arg0->list->items + off);
            if (it != 0) {
                it->f16 = 0;
                asm { nop }
            }
            i++;
            off += 4;
        } while (i < arg0->list->count);
    }
    ObjectList_FillRetained(arg0->list, 0);
}
