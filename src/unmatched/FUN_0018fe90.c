struct IndexedWordTable { char pad[8]; int count; char pad2[4]; int *data; };
struct IndexedWordKey { char pad[8]; int idx; };
extern struct IndexedWordTable *DAT_00561160[4];
static inline void setEntry(struct IndexedWordTable *g, int idx, int v) {
    if (g->count != 0 && idx >= 0 && idx < g->count) {
        g->data[idx] = v;
    }
}
void FUN_0018fe90(struct IndexedWordKey *arg0, int arg1) {
    setEntry(DAT_00561160[0], arg0->idx, arg1);
}
