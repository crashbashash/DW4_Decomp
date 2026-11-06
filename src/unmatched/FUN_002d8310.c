int ObjectList_AppendRetained();

void FUN_002d8310(void *arg0, void *arg1) {
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 28));
    *(int *)((char *)(arg1) + 12) = (int)(arg0);
}
