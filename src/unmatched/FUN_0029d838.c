typedef struct {
    char pad0[16];
    int f16;
    int f20;
    int f24;
    int f28;
    void *f32;
    char pad36[80];
} Chan29d838;

void FUN_0029da68(Chan29d838 *, int, int);

void FUN_0029d838(char *obj, Chan29d838 *chans, int *a, int *b, int idx) {
    int *pa = &a[idx];
    int *pb = &b[idx];
    Chan29d838 *ch = &chans[idx];
    int *p;
    int i;

    FUN_0029da68(ch, 1, *pb != 0);
    ch = (Chan29d838 *)((char *)ch + 16);
    {
        int va = *pa;
        int vb = *pb;

        *(int *)((char *)ch + 0) = va;
        *(int *)((char *)ch + 4) = vb;
    }
    *(int *)((char *)ch + 8) = 0;
    *(int *)((char *)ch + 12) = 0;
    *(void **)((char *)ch + 16) = obj + 5800;
    p = (int *)(obj + 7840);
    for (i = 15; i >= 0; i--) {
        *p = 0;
        p -= 34;
    }
}
