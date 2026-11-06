int ObjectList_AppendRetained();

void FUN_001d8470(void *arg0, int dummy1, int arg2, int arg3) {
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 8));
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 12), arg2);
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 20), arg3);
}
