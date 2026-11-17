void FUN_001e02e0(int arg0) {
    FUN_001e02f0(((int)DAT_00562a38[0]), arg0);
}

void FUN_001e02f0(int arg0, int arg1) {
    if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)(((int)igNode_GetMetaObject()))) != 0) {
        if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)(((int)igGroup_GetMetaObject()))) != 0) {
            igTraversal_RegisterFunction((igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (void *)&igTraversal_TraverseChildren);
            return;
        }
        igTraversal_RegisterFunction((igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (void *)((int *)FUN_001e0790));
    }
}

void Gap__Sg__igTraversal__vfunc_09(A_1e0380 *arg0, int arg1) {
    T_1e0380 *temp_a0;
    T_1e0380 *temp_s0;

    Gap__Core__igObject__userConstruct((igObject *)arg0);
    if (arg1 == 0) {
        temp_s0 = DAT_00562a38[0];
        if (temp_s0 != 0) {
            temp_s0->refs = temp_s0->refs + 1;
        }
        temp_a0 = arg0->f1c;
        if (temp_a0 != 0) {
            temp_a0->refs = temp_a0->refs - 1;
            if (((unsigned long long) ((long long) temp_a0->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        arg0->f1c = temp_s0;
    }
}

unsigned char g_useScratchPadForTraversal;

void FUN_001e0410(void) {
    ((int *)DAT_00562a38)[0] = FUN_0019a6e0((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    igRegistry_GetValueBool((igRegistry *)(*(int *)((char *)g_objectSystem + 56)), 7, "useScratchPadForTraversal", &g_useScratchPadForTraversal, g_useScratchPadForTraversal, 1);
}

void FUN_001e0470(void) {
    void *temp_a0;

    temp_a0 = *(void **)0x562A38;
    if (temp_a0 != 0) {
        *(int *)((char *)temp_a0 + 4) = (int) (*(int *)((char *)temp_a0 + 4) - 1);
        if (((unsigned long long) ((long long) *(int *)((char *)temp_a0 + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)temp_a0);
        }
    }
}

int igTraversal_TraverseNode(igTraversal *traversal, igNode *node) {
    S_1e04c0 *arg0 = (S_1e04c0 *)traversal;
    V_1e04c0 *arg1 = (V_1e04c0 *)node;
    int temp_v0;
    int temp_s0;
    if (arg0->f8 != 0) {
        temp_v0 = arg0->f12();
        if (temp_v0 != 0) {
            if (temp_v0 == 2) {
                temp_s0 = (int)g_igNode_metaObject;
                int rr = arg1->vX();
                if (rr != temp_s0) {
                    if (igTraversal_TraverseChildren((igTraversal *)arg0, (igNode *)arg1) == 2) {
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

/* Traverses {node} between the pre- and post-traversal hooks. With useScratchPadForTraversal set, the
 * outermost traversal runs on a stack at the top of the scratchpad and restores the caller's stack after. */
void Gap__Bec__beHitLandModelTraversal__vfunc_23(TraversalHooksView *self, V_1e04c0 *node) {
    if (g_useScratchPadForTraversal) {
        DAT_00562a50 = node;
        if (DAT_00562a40 == 0) {
            long long *savedStack = &DAT_00562a48;
            unsigned int scratchPadTop = 0x70003fe0;
            __asm__("sd $sp, 0(%0)\n\tmove $sp, %1" : : "r"(savedStack), "r"(scratchPadTop));
        }
        DAT_00562a40 = DAT_00562a40 + 1;
        self->preTraverse(node);
        igTraversal_TraverseNode((igTraversal *)self, (igNode *)DAT_00562a50);
        self->postTraverse(DAT_00562a50);
        DAT_00562a40 = DAT_00562a40 - 1;
        if (DAT_00562a40 == 0) {
            __asm__("ld $sp, 0(%0)" : : "r"(&DAT_00562a48));
        }
    } else {
        self->preTraverse(node);
        igTraversal_TraverseNode((igTraversal *)self, (igNode *)node);
        self->postTraverse(node);
    }
}

void igTraversal_RegisterFunction(igTraversalFunctionList *table, igMetaObject *meta, void *function) {
    int a1;
    int v1;
    int s2;

    if (igMetaObject_IsOfType(meta, g_igNode_metaObject) != 0) {
        s2 = meta->_id;
        if (s2 < 0) {
            s2 = table->_count;
            meta->_id = s2;
        }
        a1 = s2 + 1;
        if (s2 >= table->_count && a1 >= 0) {
            if (a1 <= table->_capacity) {
                table->_count = a1;
            } else {
                List_Resize((void *)table, a1, 4);
            }
        }
        v1 = table->_count;
        if (v1 != 0 && s2 >= 0 && s2 < v1) {
            ((void **)table->_data)[s2] = function;
        }
    }
}

int FUN_001e0790(void) {
    return 0;
}

int igTraversal_TraverseChildren(igTraversal *traversal, igNode *node) {
    S_1e07a0 *arg1 = (S_1e07a0 *)node;
    L_1e07a0 *temp_v0 = arg1->f28;
    int *var_s0;
    int *temp_s2;
    int r;
    if (temp_v0 != 0) {
        var_s0 = temp_v0->arr;
        temp_s2 = var_s0 + temp_v0->n;
        for (; var_s0 < temp_s2; var_s0++) {
            r = igTraversal_TraverseNode(traversal, (igNode *)(*var_s0));
            if (r == 1) return 0;
            if (r == 2) return 2;
        }
    }
    return 0;
}

void thunk_FUN_001c1c50(void **self, int flag) {
    FUN_001c1c50((void * *)self, flag);
}

