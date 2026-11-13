igMetaObject *FUN_00187010(void)
{
    igMetaObject *meta = g_igVec4ucMetaField_metaObject[0];
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_001870f0();
end:
    return g_igVec4ucMetaField_metaObject[0];
}

int igVec4ucMetaField_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init(u.b);
    u.vt = (int)&DAT_005271e0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igMetaField_vtable[0];
    ps = &u.b[12];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_001870f0(void)
{
    igMetaObject_RunStaticInit(igVec4ucMetaField_Register);
}

void igVec4ucMetaField_Register(void) {
    FUN_00186a40();  /* one-shot static-init guard (byte flag), chaining to sibling init stubs */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec4ucMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igVec4ucMetaField_GetMetaObject_00187170,
        igVec4ucMetaField_className,
        0x34, /* instance size */
        igVec4ucMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igVec4ucMetaField_callbackList /* callback list */
    );
}

void thunk_FUN_00187010(void) {
    FUN_00187010();
}

int FUN_00187180(void) {
    return g_igMetaField_metaObject[0];
}

void FUN_00187190(void) {
    M *temp_s0;
    M *p;
    int len;

    if (DAT_00560f30[0] == 0) {
        DAT_00560f30[0] = igMetaObject_CreateInstance(g_igVec4ucMetaField_metaObject[0], Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
        temp_s0 = DAT_00560f30[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            p = DAT_00560f30[0];
            p->f4 = p->f4 - 1;
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            len = FUN_002fc250()->f12;
            DAT_00560f30[0]->f18 = len - 1;
            igMetaField_FinalizeDescriptor(DAT_00560f30[0]);
        }
    }
}

int FUN_00187260(void) {
    if (DAT_00560f30[0] == 0) {
        FUN_001870f0();
    }
    return (int)DAT_00560f30[0];
}

