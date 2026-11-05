struct S { char pad[60]; int n; };
int igStringMetaField_WriteRawValue();
int Gap__Core__igStringArrayMetaField__vfunc_50(struct S *arg0, void *parg1, void *parg2, int arg3, int arg4) {
    int arg1 = (int)parg1;
    int arg2 = (int)parg2;
    int start = arg2;
    int i;
    for (i = 0; i < arg0->n; i++) {
        arg2 = arg2 + igStringMetaField_WriteRawValue(arg0, arg1, arg2, arg3, arg4);
        arg1 += 4;
    }
    return ((arg2 - start) + 3) & ~3;
}
