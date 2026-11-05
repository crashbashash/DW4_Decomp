struct L { char pad[8]; int count; int cap; };
struct D { char pad[12]; int fc; struct L *list; int f14; };
int List_Reserve();
int List_Resize();

void Gap__Core__igMemoryDictionary__vfunc_26(struct D *arg0) {
    struct L *temp_a0;
    struct L *temp_a0_2;

    temp_a0 = arg0->list;
    if (0 <= temp_a0->cap) {
        temp_a0->count = 0;
    } else {
        List_Resize(temp_a0, 0, 4);
    }
    temp_a0_2 = arg0->list;
    if (!(0 < temp_a0_2->count)) {
        List_Reserve(temp_a0_2, 0, 4);
    }
    arg0->fc = 0;
    arg0->f14 = 0;
}
