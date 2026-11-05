extern unsigned DAT_00562c70[];
extern int DAT_00569330[4];
extern int DAT_0056b058[4];
extern int DAT_0056c020[];
int FUN_001fc680(void) {
    int i;
    int n;
    int r;
    r = -1;
    if ((DAT_00562c70[DAT_00569330[0]] >> 23) & 1) {
        n = DAT_0056b058[0];
    } else {
        n = 0;
    }
    for (i = 0; n >= i; i++) {
        int off = i * 4;
        unsigned w = *(unsigned *)((char *)DAT_00562c70 + off);
        unsigned b1 = (w >> 1) & 1;
        unsigned b10 = (w >> 10) & 1;
        if (b1 && b10) {
            volatile int *p = (volatile int *)((char *)DAT_0056c020 + off);
            switch (*p) {
            case 0:
            case 1:
            case 2:
            case 3:
                if (r != 4) r = *p;
                break;
            case 4:
                r = 4;
                break;
            }
        }
    }
    return r;
}
