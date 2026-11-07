struct IndexedWordTable { char pad[8]; int count; char pad2[4]; int *data; };
struct IndexedWordKey { char pad[8]; unsigned int idx; };
extern struct IndexedWordTable *DAT_00561120;
static inline void setEntry(struct IndexedWordTable *g, int idx, int v) {
    if (g->count != 0 && idx >= 0 && idx < g->count) {
        g->data[idx] = v;
    }
}
void FUN_0018fc30(struct IndexedWordKey *arg0, struct IndexedWordKey *arg1, int arg2) {
    unsigned int a = arg0->idx;
    unsigned int b = arg1->idx;
    int i;
    if (a < b) {
        i = b * (b + 2) - a;
    } else {
        i = b + a * a;
    }
    setEntry(DAT_00561120, i, arg2);
}
