int ObjectList_RemoveAllRetained();

int FUN_001af7b0(void *arg0, int arg1) {
    return ObjectList_RemoveAllRetained(*(int *)((char *)(arg0) + 20), arg1, 0) > 0;
}
