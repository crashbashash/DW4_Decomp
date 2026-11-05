int FUN_00164d60(void *, void *);
int igObject_IsKindOf(void *, int);
int ObjectList_AppendRetained(int, void *);
int ObjectList_ResizeRetained(int, int);
extern int DAT_0055fa58[4];
void FUN_0015f660(void *arg0, int *arg1) {
    int i;
    void *x;
    void *r;
    ObjectList_ResizeRetained(*arg1, 0);
    for (i = 0; i < *(int *)(*(int *)((char *)arg0 + 16) + 8); i++) {
        x = (void *)*(int *)(*(int *)(*(int *)((char *)arg0 + 16) + 16) + i * 4);
        if (x != 0 && igObject_IsKindOf(x, DAT_0055fa58[0]) != 0) {
            r = x;
        } else {
            r = 0;
        }
        if (r != 0 && FUN_00164d60(arg0, r) != 0) {
            ObjectList_AppendRetained(*arg1, r);
        }
    }
}
