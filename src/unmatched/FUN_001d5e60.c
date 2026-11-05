struct L { char pad[8]; int count; char pad2[4]; int *data; };
struct A { char pad[28]; struct L *f28; };
int FUN_001e04c0();
void FUN_001d5e60(struct A *arg0, int arg1) {
    int i;
    int n;
    if (arg0->f28 != 0) {
        n = arg0->f28->count;
    } else {
        n = 0;
    }
    for (i = 0; i < n; i++) {
        FUN_001e04c0(arg1, arg0->f28->data[i]);
    }
}