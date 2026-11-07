typedef struct ValueTable { int pad0[2]; int count; int capacity; int *data; } ValueTable;
extern ValueTable *DAT_00561148;
static inline void setAt(ValueTable *t, int i, int v) {
    if (t->count != 0 && i >= 0 && i < t->count) { t->data[i] = v; }
}
void FUN_0018fdd0(int arg0, int arg1) {
    setAt(DAT_00561148, *(int *)(arg0 + 8), arg1);
}
