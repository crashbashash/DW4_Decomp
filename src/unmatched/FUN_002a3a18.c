int FUN_002a8500(void *);

int FUN_002a3a18(char *obj) {
    int limit = *(int *)(obj + 2656);
    int size = *(int *)(obj + 44);

    if (limit == -1) {
        limit = size;
    }
    if (size < limit) {
        limit = size;
    }
    if (FUN_002a8500(obj) < limit) {
        return 0;
    }
    return 1;
}
