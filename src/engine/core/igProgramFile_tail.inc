void Gap__Core__igProgramFile__vfunc_23(igProgramFile *arg0) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    char *temp_a0;
    T_327140 *temp_a0_2;
    char *temp_s1;

    if (g_stringPool[0] == 0) {
        var_v0 = ((int)StringPool_Allocate(0x10));
        if (var_v0 != 0) {
            var_v0 = ((int)StringPool_Construct((struct S_2eadf0 *)var_v0));
        }
        g_stringPool[0] = var_v0;
    }
    temp_s1 = (char *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)0);
    temp_a0 = (char *)arg0->_fileName;
    if (temp_a0 != 0) {
        temp_a1 = (int *)(temp_a0 - 8);
        temp_v1 = *(int *)(temp_a0 - 4) - 1;
        *(int *)(temp_a0 - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
    arg0->_fileName = (int)temp_s1;
    temp_a0_2 = (T_327140 *)arg0->_file;
    if (temp_a0_2 != 0) {
        --temp_a0_2->references;
        if (((unsigned long long)(long long)temp_a0_2->references & 0x7fffffULL) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
    arg0->_file = 0;
}

void Gap__Core__igProgramFile__vfunc_25(int *arg0, void *arg1) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg1) + 12));
    ((DW4VC_96_0 *)(temp_a0))->vX();
    ((DW4VC_92_0 *)(((char *)(arg1) + 0)))->vX();
    *arg0 = (*(R_327140 *)&g_statusSucceeded).v;
}

void Gap__Core__igProgramFile__vfunc_26(int *arg0, OF *arg1, int arg2, int arg3, int *arg4) {
    SR4 sp6C;
    SR4 sp68;
    SR4 sp64;
    Strm *s;
    s = arg1->f12;
    if (s->v38(arg2, 0) == -1) {
        FUN_00304430(DAT_004ff510, arg2, arg1->f8);
        FUN_00304680();
        sp6C = ((Obj_327140 *)arg1)->v25();
        *arg0 = (*(R_327140 *)&g_allocatorFailureStatus).v;
        return;
    }
    if (*arg4 == 0) {
        *arg4 = igObject_AllocateStorage((int)arg1, arg3);
        if (*arg4 == 0) {
            FUN_00304430(DAT_004ff540, arg3, arg1->f8);
            FUN_00304680();
            sp68 = ((Obj_327140 *)arg1)->v25();
            *arg0 = (*(R_327140 *)&g_allocatorFailureStatus).v;
            return;
        }
    }
    memset(*arg4, 0, arg3);
    s = arg1->f12;
    if (s->v27(*arg4, arg3, 1) != 1) {
        FUN_00304430(DAT_004fdda0, arg1->f8);
        FUN_00304680();
        sp64 = ((Obj_327140 *)arg1)->v25();
        *arg0 = (*(R_327140 *)&g_allocatorFailureStatus).v;
        return;
    }
    *arg0 = (*(R_327140 *)&g_statusSucceeded).v;
}

/* igProgramFile vtable slot 27: status leaf. Ignores the object and writes the engine's current
 * failure-status word (the one an allocation failure publishes) through the output-first argument;
 * the same leaf as igPsx2Window slot 40. */
void Gap__Core__igProgramFile__vfunc_27(int *status_out) {
    *status_out = g_allocatorFailureStatus.v;
}

/* igProgramFile vtable slot 28: status leaf, the same body as slot 27. */
void Gap__Core__igProgramFile__vfunc_28(int *status_out) {
    *status_out = g_allocatorFailureStatus.v;
}

/* igProgramFile vtable slot 29: status leaf, the same body as slot 27. */
void Gap__Core__igProgramFile__vfunc_29(int *status_out) {
    *status_out = g_allocatorFailureStatus.v;
}

void Gap__Core__igProgramFile__vfunc_30(igProgramFile *self) {
}

void Gap__Core__igProgramFile__vfunc_31(igProgramFile *self) {
}

void Gap__Core__igProgramFile__vfunc_32(igProgramFile *self) {
}

