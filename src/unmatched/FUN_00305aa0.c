typedef struct E { char p[24]; int v; } E;
typedef struct Lst { int a, b, n; } Lst;
extern int FUN_003057b0(int s, int c);
extern int sscanf(int s, int *tbl, int *out);
extern E *FUN_002d7e90(Lst *l, int i);
extern int DAT_004f95c0[4];
int FUN_00305aa0(int self, int str, int *out, int n, Lst *list) {
    int idx;
    int s = str;
    int *o = out;
    int i;
    for (i = 0; i < n; i++) {
        E *e;
        s = FUN_003057b0(s, 0x7b);
        if (list != 0) {
            s = FUN_003057b0(s, 0x5b);
            if (sscanf(s, &DAT_004f95c0[0], &idx) == 0) idx = -1;
            if (idx >= 0 && idx < list->n) {
                e = FUN_002d7e90(list, idx);
                if (e != 0) o[i] = e->v;
                else o[i] = 0;
            } else o[i] = 0;
        } else o[i] = 0;
    }
    return s - str;
}
