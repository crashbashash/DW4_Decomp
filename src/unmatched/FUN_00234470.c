int StringChunk_ReleaseHeader();
int StringList_CopyRetained();
int igStrCmp();

int FUN_00234470(int arg0, int *arg1, int arg2) {
    void *sp3C;
    int *temp_a1;
    int temp_s1;
    int temp_v0;

    if (arg2 != 0) {
        StringList_CopyRetained(&sp3C, arg0, *arg1);
        temp_s1 = igStrCmp(sp3C, arg2) == 0;
        if (sp3C != 0) {
            temp_a1 = (int *)((char *)sp3C - 8);
            temp_v0 = *(int *)((char *)(sp3C) - 4) - 1;
            *(int *)((char *)(sp3C) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
        if (temp_s1 != 0) {
            *arg1 += 1;
            return 1;
        }
    }
    return 0;
}
