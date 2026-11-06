int ObjectList_AppendUniqueRetained();

void FUN_00237ce0(void *arg0, void *arg1, void *arg2) {
    ObjectList_AppendUniqueRetained(*(int *)((char *)(arg2) + 12));
    ObjectList_AppendUniqueRetained(*(int *)((char *)(arg0) + 12), arg2);
}
