void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();

int FUN_002fe730(int arg0) {
    int i;
    int n = 0;

    for (i = 0; i < igMetaObject_GetFieldCount(arg0); i++) {
        if (*(unsigned char *)((char *)(igMetaObject_GetFieldAt(arg0, i)) + 37) == 0) {
            n += 1;
        }
    }
    return n;
}
