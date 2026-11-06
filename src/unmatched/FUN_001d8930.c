typedef struct S0 { char pad20[20]; int f14; } S0;
int ObjectList_ClearRetainedPreserveCount();
int ObjectList_ResizeRetained();
int Gap__Core__igObject__vfunc_15();

void FUN_001d8930(S0 *arg0) {
    int temp_a1;
    void *temp_a0;

    Gap__Core__igObject__vfunc_15();
    temp_a0 = (void *)(arg0->f14);
    temp_a1 = *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 8);
    if (temp_a1 != *(int *)((char *)(temp_a0) + 8)) {
        ObjectList_ResizeRetained(temp_a0, temp_a1);
        ObjectList_ClearRetainedPreserveCount(arg0->f14);
    }
}
