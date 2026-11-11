int FUN_002cc7e0(void) {
    if (DAT_00586960[0] == 0) {
        DAT_00586960[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_00586960[0];
}

igMetaObject *igCallStackTable_GetMetaObject(void)
{
    igMetaObject *g = g_igCallStackTable_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cc960();
    return g_igCallStackTable_metaObject[0];
}

int igCallStackTable_GetVTable(void) {
    union U_2cc880 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;

    igObject_InitHeader((ObjectHeader *)u.b);
    u.vt = (int)&DAT_00530c00[0];
    q1 = (S_ref *)&u.b[16];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[20];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916)];
    u.vt = (int)&DAT_00530c00[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}

void FUN_002cc960(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCallStackTable_Register);
}

void igCallStackTable_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igCallStackTable_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCallStackTable_GetMetaObject,
        igCallStackTable_className,
        0x18, /* instance size */
        igCallStackTable_GetVTable,
        &igCallStackTable_InitFields,
        0, /* extra callback item */
        g_igCallStackTable_callbackList /* callback list */
    );
}

void thunk_igCallStackTable_GetMetaObject(void) {
    igCallStackTable_GetMetaObject();
}

void igCallStackTable_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00586960[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c1530[0], 4);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002ca2a0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002ca8f0();
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c1540[0], (igMetaField ***)&DAT_004c1550[0], &DAT_004c1560[0], temp_s2);
}

