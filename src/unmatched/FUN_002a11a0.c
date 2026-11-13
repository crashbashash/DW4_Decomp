void FUN_0028b660(int, int, int);
int SFD_GetCond(void *, int);

void FUN_002a11a0(void *obj) {
    int a = **(int **)((char *)obj + 8052);
    int b = SFD_GetCond(obj, 85);
    FUN_0028b660(a, b, SFD_GetCond(obj, 86));
}
