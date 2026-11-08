void *sceSifGetNextRequest(void *);
void sceSifExecRequest(void *);
void FUN_0010ae00(void);
void FUN_0010e990(void *l) {
    void *n;
    for (;;) {
        while ((n = sceSifGetNextRequest(l)) != 0) {
            sceSifExecRequest(n);
        }
        FUN_0010ae00();
    }
}
