int List_Reserve();

void Gap__Sg__igTraversalFunctionList__vfunc_18(void *arg0) {
    int temp_a1;

    temp_a1 = *(int *)((char *)arg0 + 8);
    if (temp_a1 < *(int *)((char *)arg0 + 12)) {
        List_Reserve(arg0, temp_a1, 4);
    }
}
