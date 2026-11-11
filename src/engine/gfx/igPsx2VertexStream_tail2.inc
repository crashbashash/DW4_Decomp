static inline int cast0(int o) { if (o != 0 && igObject_IsKindOf(o, DAT_00585d80[0]) != 0) { return o; } return 0; }

void FUN_0017f5a0(void) {
    int var_s0;

    FUN_00308860(DAT_00586dd0[0], &DAT_004e0848[0], 0x10);
    var_s0 = (int)igMetaObject_FindFieldByName(DAT_00560420[0], &DAT_004ddf18[0]);
    var_s0 = cast0(var_s0);
    igMemoryRefMetaField_SetAlignmentType(var_s0, &DAT_004e0848[0]);
}

void Gap__Gfx__igPsx2VertexStream__vfunc_15(S0_17f630 *arg0) {
    int temp_a0;
    int temp_a1;

    if (arg0->f10 != 0) {
        temp_a0 = arg0->f80;
        if ((temp_a0 != 0) && ((temp_a1 = arg0->f18, (temp_a1 == 3)) || (temp_a1 == 2)) && (arg0->f84 == 0)) {
            arg0->f84 = FUN_00300db0(arg0, FUN_001eedf0(temp_a0, temp_a1), 0x10);
            FUN_001eee40(arg0->f80, arg0->f84);
            arg0->f88 = FUN_001eeed0(arg0->f80);
        }
    }
}

void Gap__Gfx__igPsx2VertexStream__vfunc_17(S0_17f6c0 *arg0) {
    Gap__Core__igObject__vfunc_15();
    if ((arg0->f84 != 0) && (arg0->f88 != 0)) {
        arg0->f10 = 1;
        arg0->f80 = FUN_001eef20(arg0->f84, arg0->f88);
        arg0->fC = FUN_001eee30(arg0->f80);
    }
}

