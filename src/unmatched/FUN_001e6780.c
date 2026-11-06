int ObjectList_AppendRetained(int);

int FUN_001e6780(void *arg0) {
    ObjectList_AppendRetained(*(int *)((char *)arg0 + 20));
    return 1;
}
