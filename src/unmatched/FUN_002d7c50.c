typedef struct L { char pad0[8]; int n; char pad1[4]; unsigned *data; } L;
typedef struct O { char pad[44]; L *l; } O;
int FUN_002d7e90(O *, int, unsigned);
int igProperty_FindBySortedKey(O *, int, unsigned);
extern int DAT_00586730[4];
int FUN_002d7c50(O *arg0, unsigned key) {
    L *l = arg0->l;
    int lo, hi, mid, idx, n;
    unsigned v;
    int r;
    if (l != 0) {
        n = l->n;
        lo = 0;
        hi = n - 1;
        while (lo < hi) {
            mid = (lo + hi) >> 1;
            v = l->data[mid];
            if (v < key) {
                lo = mid + 1;
            } else if (key < v) {
                hi = mid - 1;
            } else {
                idx = mid;
                goto found;
            }
        }
        if (n == 0) {
            idx = -1;
        } else {
            v = l->data[lo];
            if (key < v || v < key) {
                idx = -1;
            } else {
                idx = lo;
            }
        }
found:
        v = l->data[idx];
        if (v == key) {
            return FUN_002d7e90(arg0, idx, key);
        }
        return 0;
    }
    return igProperty_FindBySortedKey(arg0, DAT_00586730[0], key);
}
