igMetaObject *FUN_0044c250(void) {
    if (g_igClearRenderer_metaObject[0] == 0) {
        g_igClearRenderer_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igClearRenderer_metaObject[0];
}

igMetaObject *igClearRenderer_GetMetaObject(void)
{
    igMetaObject *g = g_igClearRenderer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igClearRenderer_EnsureRegistered();
    return g_igClearRenderer_metaObject[0];
}

int igClearRenderer_GetVTable(void) {
    union U_44c2f0 u;
    int temp_s0;
    S_ref *q0;

    igObject_InitHeader(u.b);
    q0 = (S_ref *)&u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_0052d060[0];
    u.vt = (int)&DAT_00540c80[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0052d060[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s0;
}

void igClearRenderer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igClearRenderer_Register);
}

void igClearRenderer_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igClearRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igClearRenderer_GetMetaObject,
        igClearRenderer_className,
        0x10, /* instance size */
        igClearRenderer_GetVTable,
        &igClearRenderer_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igClearRenderer_GetMetaObject(void) {
    igClearRenderer_GetMetaObject();
}

void igClearRenderer_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igClearRenderer_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igClearRenderer_ctorTable[0], 1);
    igMetaObject_NameFields(temp_s0, &g_igClearRenderer_fieldTable[0], &DAT_004cff78[0], &DAT_004cff80[0], temp_s1);
}

