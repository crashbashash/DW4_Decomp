void FUN_0028b660(int, int, int);
int FUN_002adc40(void *, int);

void FUN_002a11a0(void *obj) {
    int a = **(int **)((char *)obj + 8052);
    int b = FUN_002adc40(obj, 85);
    FUN_0028b660(a, b, FUN_002adc40(obj, 86));
}
