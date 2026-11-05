int FUN_00330770();
extern void *DAT_0056b460[8];
void FUN_00203500(void) {
    int i;
    void *p;
    void *next;

    i = 0;
    do {
        p = DAT_0056b460[i];
        while (p != 0) {
            next = *(void **)((char *)p + 20);
            FUN_00330770(p, 0x14);
            p = next;
        }
        DAT_0056b460[i] = 0;
        i += 1;
    } while (i < 6);
}
