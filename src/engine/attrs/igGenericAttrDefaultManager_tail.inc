igSmartPointer<igAttr> igGenericAttrDefaultManager_createDefault(igObject *self, igMetaObject *meta) {
    igMetaObject_IsOfType(meta, g_igAttr_metaObject);
    return igMetaObject_CreateInstanceDefaultRef(meta);
}

void FUN_0013cf70(void) {

}

void FUN_0013cf80(void **arg0, int a1, int a2, int a3, int a4) {
    int sp1C;
    int sp18;

    sp1C = -1;
    sp18 = -1;
    ((DW4VC_144_4 *)(arg0))->vX(a1, a2, a3, (int)(&sp1C), (int)(&sp18), a4, 0);
}

void igGeometryAttr1_5_Reset(void *arg0) {
    void **temp_a0;
    void **temp_a0_2;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 12));
    if (temp_a0 != 0) {
        ((DW4VC_236_0 *)(temp_a0))->vX();
    }
    temp_a0_2 = (void **)(*(int *)((char *)(arg0) + 16));
    if (temp_a0_2 != 0) {
        ((DW4VC_140_0 *)(temp_a0_2))->vX();
    }
}

/* Empty override (a bare return) in vtable slot 35 of Gap::Core::igPsx2IndexArray, next to slot
 * 36, which is also empty. */
void FUN_0013d020(void) {
}

