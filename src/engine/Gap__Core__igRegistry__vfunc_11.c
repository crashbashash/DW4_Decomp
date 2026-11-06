int ObjectList_ResizeRetained(int, int);
int Gap__Core__igObject__vfunc_09();

void Gap__Core__igRegistry__vfunc_11(void *arg0) {
    Gap__Core__igObject__vfunc_09();
    ObjectList_ResizeRetained(*(int *)((char *)arg0 + 8), 0x100);
}
