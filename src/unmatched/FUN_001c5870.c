void *FUN_001c5990();
int ObjectList_AppendRetained();

void FUN_001c5870(void *arg0, int arg1) {
    int idx, tbl;
    tbl = *(int *)(*(int *)((char *)FUN_001c5990() + 28) + 16);
    idx = arg1 * 4;
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 8), *(int *)(tbl + idx));
}
