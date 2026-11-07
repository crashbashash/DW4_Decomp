int strlen();
int FUN_002da770();
int FUN_002dada0();
int FUN_0030b460();
void FUN_002dab80(void *arg0, int arg1) {
    char buf[4096];
    char *s2;
    int s1;
    char *p;
    int c;
    FUN_002da770(arg0);
    while (FUN_002dada0(arg0, &arg1, buf, 0x1000) != 0) {
        p = buf;
        while ((c = *p) != 0) {
            if (c == 0x3B) {
                *p = 0xA;
                p[1] = 0;
                break;
            }
            p++;
        }
        s2 = (char *)(*(int *)((char *)(arg0) + 40));
        s1 = *(int *)(s2 + 12);
        FUN_0030b460(s2, buf, s1, strlen(buf));
    }
}
