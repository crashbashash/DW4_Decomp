extern int DAT_0056090c[4];
struct P { char pad[80]; int f; };
struct O { char pad[1344]; struct P *p; };
void FUN_001720d0(struct O *arg0, int arg1) {
    if (arg0->p->f == arg1) {
        DAT_0056090c[0] += 1;
    }
    arg0->p->f = arg1;
}
