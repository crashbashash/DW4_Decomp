void FUN_00129e60(char *);
int FUN_00109b10(void *, char *);
int FUN_00109ad8(void *a) {
    char buf[256];
    FUN_00129e60(buf);
    return FUN_00109b10(a, buf);
}
