struct IndexedSlotList { char pad[8]; int n; char pad2[4]; int *data; };
extern struct IndexedSlotList *DAT_00561158[4];
struct IndexedSlotKey { char pad[8]; int idx; };
void FUN_0018fe50(struct IndexedSlotKey *arg0, int arg1) {
    int i;
    struct IndexedSlotList *g;
    i = arg0->idx;
    g = DAT_00561158[0];
    if ((g->n != 0) && (i >= 0) && (i < g->n)) {
        g->data[i] = arg1;
    }
}
