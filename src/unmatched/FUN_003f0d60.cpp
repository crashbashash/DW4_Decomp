/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
typedef struct E { char pad28[28]; int a28; char pad36[4]; int a36; } E;
typedef struct L { char pad8[8]; int n; char pad12[4]; E **data; } L;
typedef struct O { char pad12[12]; L *list; } O;
int memcpy(int, int, int);
void FUN_003f0d60(O *arg0, int arg1, int arg2, E *arg3) {
    int idx = arg2;
    E *rec = arg3;
    int pos = arg1;
    L *l = arg0->list;
    int i = 0;
    int a, w;
    E *e;
    while (i < l->n) {
        if (i == idx) {
            a = rec->a28;
            w = rec->a36;
        } else {
            e = l->data[i];
            a = e->a28;
            w = e->a36;
        }
        memcpy(pos, a, w);
        l = arg0->list;
        i++;
        pos += w;
    }
}
} /* extern "C" */
