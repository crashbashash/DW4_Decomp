extern unsigned DAT_00562c70[];
extern int DAT_00569330[4];
extern int DAT_0056b058[4];
extern int DAT_0056c080[];
int FUN_001fc510(int f) {
    int i;
    int n;
    n = 0;
    if ((DAT_00562c70[DAT_00569330[0]] >> 23) & 1) {
        n = DAT_0056b058[0];
    }
    for (i = 0; n >= i; i++) {
        int off = i * 4;
        int b = (*(unsigned *)((char *)DAT_00562c70 + off) >> 1) & 1;
        if ((b == 0 || *(int *)((char *)DAT_0056c080 + off) != 1) && f != 0) {
            f = 0;
            break;
        } else if (b != 0 && *(int *)((char *)DAT_0056c080 + off) != 1 && f == 0) {
            f = 1;
            break;
        }
    }
    return f;
}
