int igObject_Destroy(void *);
int ObjectList_AppendRetained(int);

void FUN_002f8a80(void *arg0, void *arg1) {
    if (arg1 != 0) {
        ObjectList_AppendRetained(*(int *)((char *)arg0 + 20));
        *(int *)((char *)arg1 + 4) = (int) (*(int *)((char *)arg1 + 4) - 1);
        if (((unsigned long long) ((long long) *(int *)((char *)arg1 + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy(arg1);
        }
    }
}
