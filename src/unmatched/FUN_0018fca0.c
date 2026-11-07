typedef struct ValueTable { int pad0[2]; int count; int capacity; int *data; } ValueTable;
typedef struct PairKeyedItem { int pad0[2]; unsigned int key; } PairKeyedItem;
extern ValueTable *DAT_00561128;
static inline void setAt(ValueTable *t, int i, int v) {
    if (t->count != 0 && i >= 0 && i < t->count) { t->data[i] = v; }
}
void FUN_0018fca0(PairKeyedItem *a, PairKeyedItem *b, int v) {
    unsigned int x = a->key;
    unsigned int y = b->key;
    int i;
    if (x < y) {
        i = y * (y + 2) - x;
    } else {
        i = x * x + y;
    }
    setAt(DAT_00561128, i, v);
}
