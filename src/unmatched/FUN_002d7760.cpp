extern "C" {
int FUN_002d7130(void *);
int FUN_002d7280(void *);
int List_RemoveAt(void *, int, int);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
}
struct E { int a; int b; };
struct L {
    int x, y; int n; int z; E *items;
    int Find(int k1, int k2) { int i; for (i = 0; i < n; i++) { E *p = &items[i]; int v = (k1 == p->a); if (v) { v = (k2 == p->b); } if (v) { return i; } } return -1; }
};
struct O { char pad[12]; L *list; char pad2[8]; unsigned char f24; };
extern "C" void FUN_002d7760(int *arg0, O *arg1, int arg2, int arg3) {
    L *temp_a0 = arg1->list;
    int idx = temp_a0->Find(arg2, arg3);
    int var_s2;
    if (idx >= 0) {
        List_RemoveAt(temp_a0, idx, 8);
        var_s2 = DAT_004fb410[0];
    } else {
        var_s2 = DAT_004fb418[0];
    }
    if (arg1->f24 != 0) {
        FUN_002d7280(arg1);
        FUN_002d7130(arg1);
    }
    *arg0 = var_s2;
}
