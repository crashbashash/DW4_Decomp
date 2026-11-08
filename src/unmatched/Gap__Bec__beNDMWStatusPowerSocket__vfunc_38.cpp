struct PowerSocketItem { char p[16]; char f16; };
struct PowerSocketList { char p[8]; int count; int pad; PowerSocketItem **items; };
struct PowerSocketView { char p[112]; PowerSocketList *volatile list; };
extern "C" int ObjectList_FillRetained(PowerSocketList *, int);
extern "C" void Gap__Bec__beNDMWStatusPowerSocket__vfunc_38(PowerSocketView *self) {
    int i;
    for (i = 0; i < self->list->count; i++) {
        PowerSocketItem *it = self->list->items[i];
        if (it != 0) {
            it->f16 = 0;
        }
    }
    ObjectList_FillRetained(self->list, 0);
}
