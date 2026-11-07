int ObjectList_AppendRetained();

void Gap__Sg__igShaderData__vfunc_24(void *arg0, int dummy1, int arg2, int arg3) {
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 8));
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 12), arg2);
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 20), arg3);
}
