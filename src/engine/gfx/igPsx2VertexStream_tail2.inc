static inline int cast0(int o) { if (o != 0 && ((Gap::Core::igObject *)o)->isOfType((igMetaObject *)g_igMemoryRefMetaField_metaObject) != 0) { return o; } return 0; }

void FUN_0017f5a0(void) {
    int var_s0;

    igResource_AddAlignment((igResource *)g_globalContext, "DMABuffer_PS2", 0x10);
    var_s0 = (int)igMetaObject_FindFieldByName(g_igPsx2VertexStream_metaObject, "_dmaBuffer");
    var_s0 = cast0(var_s0);
    igMemoryRefMetaField_SetAlignmentType((igMemoryRefMetaField *)var_s0, "DMABuffer_PS2");
}

void igPsx2VertexStream_UserWriteFilePreProcess(S0_17f630 *arg0) {
    int temp_a0;
    int temp_a1;

    if (arg0->f10 != 0) {
        temp_a0 = arg0->f80;
        if ((temp_a0 != 0) && ((temp_a1 = arg0->f18, (temp_a1 == 3)) || (temp_a1 == 2)) && (arg0->f84 == 0)) {
            arg0->f84 = (int)((Gap::Core::igObject *)arg0)->mallocAligned(p2GetDisplayListSize((p2DisplayList *)temp_a0), 0x10);
            p2CopyDisplayListData((p2DisplayList *)arg0->f80, (char *)arg0->f84);
            arg0->f88 = (int)p2CopyDisplayList((p2DisplayList *)arg0->f80);
        }
    }
}

void igPsx2VertexStream_UserPostLoad(S0_17f6c0 *arg0) {
    igObject_UserPostLoad();
    if ((arg0->f84 != 0) && (arg0->f88 != 0)) {
        arg0->f10 = 1;
        arg0->f80 = (int)p2RebaseDisplayList(arg0->f84, (p2DisplayList *)arg0->f88);
        arg0->fC = p2GetDisplayListData((p2DisplayList *)arg0->f80);
    }
}

