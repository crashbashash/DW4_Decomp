int FUN_00460be0();
int ObjectList_AppendRetained();
int ObjectList_RemoveFirstRetained();

void FUN_00460d90(void *arg0, void *arg1, int arg2) {
    int sp4C;
    int temp_v0;

    temp_v0 = FUN_00460be0(arg2, arg0);
    if (temp_v0 != 0) {
        ObjectList_RemoveFirstRetained(&sp4C, *(int *)((char *)(arg0) + 32), temp_v0, 0);
        ObjectList_AppendRetained(*(int *)((char *)(arg1) + 32), temp_v0);
    }
}
