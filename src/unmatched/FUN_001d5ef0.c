int FUN_001e04c0();
struct L { char pad[8]; int count; char pad1[4]; int *data; };
struct S60 { char pad[60]; struct L *f60; };

void FUN_001d5ef0(struct S60 *arg0, int arg1) {
    int n;
    int i;

    n = arg0->f60->count;
    for (i = 0; i < n; i++) {
        FUN_001e04c0(arg1, arg0->f60->data[i]);
    }
}
