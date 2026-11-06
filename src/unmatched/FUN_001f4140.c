/* The condition reads the word through a different type so the load is not reused. */
extern int DAT_004e5100[4];
void FUN_001f4140(int *arg0) {
    int *p;
    while (*(unsigned *)arg0 & 0xF) {
        p = *(int **)arg0;
        *(int **)arg0 = p + 1;
        *p = DAT_004e5100[0];
    }
}
