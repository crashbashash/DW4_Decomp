void *beNDMWMcSlot_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMcSlot_metaObject[0];
    bool ready;
    if (g) {
        /* matching construct: the bool compared against false keeps the retail sltu normalisation under the
         * unit profile (3.0 -O3, exceptions on); a member-function spelling matched only under the combat -O3,p override */
        ready = g->_validity & 4;
        if (ready != false) goto end;
    }
    FUN_003c60b0();
end:
    return g_beNDMWMcSlot_metaObject[0];
}

void FUN_003c60b0(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlot_Register);
}

void *beNDMWMcSlot_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWMcSlot_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWMcSlot_GetMetaObject,
        beNDMWMcSlot_className,
        0x18, /* instance size */
        0,
        beNDMWMcSlot_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMcSlot_GetMetaObject(void)
{
    beNDMWMcSlot_GetReadyMetaObject();
}

void beNDMWMcSlot_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWMcSlot_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cbba0[0], 5);
    igMetaObject_NameFields(temp_s0, &DAT_004cbbc0[0], &DAT_004cbbe0[0], &DAT_004cbc00[0], temp_s1);
}

