static inline int cast0(int o) { if (o != 0 && igObject_IsKindOf(o, g_igMemoryRefMetaField_metaObject[0]) != 0) { return o; } return 0; }

void FUN_0017f5a0(void) {
    int var_s0;

    FUN_00308860(g_globalContext[0], &text_DMABuffer_PS2[0], 0x10);
    var_s0 = (int)igMetaObject_FindFieldByName(g_igPsx2VertexStream_metaObject[0], &text_dmaBuffer[0]);
    var_s0 = cast0(var_s0);
    igMemoryRefMetaField_SetAlignmentType(var_s0, &text_DMABuffer_PS2[0]);
}

void Gap__Gfx__igPsx2VertexStream__vfunc_15(S0_17f630 *arg0) {
    int temp_a0;
    int temp_a1;

    if (arg0->f10 != 0) {
        temp_a0 = arg0->f80;
        if ((temp_a0 != 0) && ((temp_a1 = arg0->f18, (temp_a1 == 3)) || (temp_a1 == 2)) && (arg0->f84 == 0)) {
            arg0->f84 = FUN_00300db0(arg0, p2GetDisplayListSize(temp_a0, temp_a1), 0x10);
            p2CopyDisplayListData(arg0->f80, arg0->f84);
            arg0->f88 = p2CopyDisplayList(arg0->f80);
        }
    }
}

void Gap__Gfx__igPsx2VertexStream__vfunc_17(S0_17f6c0 *arg0) {
    Gap__Core__igObject__vfunc_15();
    if ((arg0->f84 != 0) && (arg0->f88 != 0)) {
        arg0->f10 = 1;
        arg0->f80 = p2RebaseDisplayList(arg0->f84, arg0->f88);
        arg0->fC = p2GetDisplayListData(arg0->f80);
    }
}

