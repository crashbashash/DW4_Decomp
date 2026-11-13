void FUN_001e02e0(int arg0) {
    FUN_001e02f0(((int)DAT_00562a38[0]), arg0);
}

void FUN_001e02f0(int arg0, int arg1) {
    if (FUN_002fe290(arg1, ((int)igNode_GetMetaObject())) != 0) {
        if (FUN_002fe290(arg1, ((int)igGroup_GetMetaObject())) != 0) {
            igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)&igTraversal_TraverseChildren);
            return;
        }
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)((int *)FUN_001e0790));
    }
}

void Gap__Sg__igTraversal__vfunc_09(A_1e0380 *arg0, int arg1) {
    T_1e0380 *temp_a0;
    T_1e0380 *temp_s0;

    Gap__Core__igObject__userConstruct();
    if (arg1 == 0) {
        temp_s0 = DAT_00562a38[0];
        if (temp_s0 != 0) {
            temp_s0->refs = temp_s0->refs + 1;
        }
        temp_a0 = arg0->f1c;
        if (temp_a0 != 0) {
            temp_a0->refs = temp_a0->refs - 1;
            if (((unsigned long long) ((long long) temp_a0->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        arg0->f1c = temp_s0;
    }
}

void FUN_001e0410(void) {
    ((int *)DAT_00562a38)[0] = FUN_0019a6e0(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    FUN_00306e50(*(int *)((char *)g_objectSystem[0] + 56), 7, text_useScratchPadForTraversal, &GPR_00554bac, GPR_00554bac, 1);
}

void FUN_001e0470(void) {
    void *temp_a0;

    temp_a0 = *(void **)0x562A38;
    if (temp_a0 != 0) {
        *(int *)((char *)temp_a0 + 4) = (int) (*(int *)((char *)temp_a0 + 4) - 1);
        if (((unsigned long long) ((long long) *(int *)((char *)temp_a0 + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
}

int FUN_001e04c0(S_1e04c0 *arg0, V_1e04c0 *arg1) {
    int temp_v0;
    int temp_s0;
    if (arg0->f8 != 0) {
        temp_v0 = arg0->f12();
        if (temp_v0 != 0) {
            if (temp_v0 == 2) {
                temp_s0 = (int)g_igNode_metaObject[0];
                int rr = arg1->vX();
                if (rr != temp_s0) {
                    if (igTraversal_TraverseChildren((int)arg0, (S_1e07a0 *)arg1) == 2) {
                        temp_v0 = 2;
                    } else {
                        temp_v0 = 0;
                    }
                    return temp_v0;
                }
                goto block_9;
            }
            return 0;
        }
    }
block_9:
    return arg0->f28->tab[((W_1e04c0 *)arg1)->f24](arg0, arg1);
}

void Gap__Sg__igTraversal__vfunc_23(void *, int)
{
}

void Gap__Sg__igTraversal__vfunc_24(void *, int)
{
}

void igTraversal_RegisterFunction(struct L_1e06c0 *arg0, struct X_1e06c0 *arg1, void *arg2) {
    int a1;
    int v1;
    int s2;

    if (FUN_002fe290(arg1, g_igNode_metaObject[0]) != 0) {
        s2 = arg1->f8;
        if (s2 < 0) {
            s2 = arg0->n;
            arg1->f8 = s2;
        }
        a1 = s2 + 1;
        if (s2 >= arg0->n && a1 >= 0) {
            if (a1 <= arg0->cap) {
                arg0->n = a1;
            } else {
                List_Resize((void *)arg0, a1, 4);
            }
        }
        v1 = arg0->n;
        if (v1 != 0 && s2 >= 0 && s2 < v1) {
            arg0->arr[s2] = arg2;
        }
    }
}

int FUN_001e0790(void) {
    return 0;
}

int igTraversal_TraverseChildren(int arg0, S_1e07a0 *arg1) {
    L_1e07a0 *temp_v0 = arg1->f28;
    int *var_s0;
    int *temp_s2;
    int r;
    if (temp_v0 != 0) {
        var_s0 = temp_v0->arr;
        temp_s2 = var_s0 + temp_v0->n;
        for (; var_s0 < temp_s2; var_s0++) {
            r = FUN_001e04c0((S_1e04c0 *)arg0, (V_1e04c0 *)(*var_s0));
            if (r == 1) return 0;
            if (r == 2) return 2;
        }
    }
    return 0;
}

void thunk_FUN_001c1c50(void **self, int flag) {
    FUN_001c1c50((void * *)self, flag);
}

