int FUN_00171690();
extern int DAT_005608e4[4];
struct Item { char pad[92]; float f92; char pad2[12]; unsigned int f108; char pad3[40]; int f152; char pad4[4]; };
struct List { char pad[16]; struct Item *data; };
struct Ctx { char pad[1336]; struct List *list; };
void FUN_00171220(struct Ctx *arg0, int arg1, float fparg0) {
    struct Item *it;
    unsigned int old;

    it = &arg0->list->data[arg1];
    if (it != 0) {
        old = it->f108;
        if (it->f92 == fparg0) {
            DAT_005608e4[0] += 1;
        }
        it->f92 = fparg0;
        if (it->f152 == 2 && fparg0 != 180.0f) {
            it->f108 = it->f108 | 4;
        } else {
            it->f108 = it->f108 & ~4;
        }
        if (old != it->f108) {
            it->f108 = it->f108 | 8;
        }
        FUN_00171690(arg0, it, old);
    }
}
