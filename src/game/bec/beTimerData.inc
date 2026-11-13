igMetaObject *FUN_00341840(void)
{
    igMetaObject *g = g_beTimerData_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00341950();
    return g_beTimerData_metaObject[0];
}

int beTimerData_GetVTable(void) {
    beTimerData obj;
    int *q1;
    int *q2;
    char *o;
    int *a1;
    int v0;
    int t;

    igObject_InitHeader(&obj);
    q1 = &obj._resetCondition;
    q2 = &obj._callLuaFile;
    obj._vtable = (int)&DAT_00539700[0];
    obj._resetCondition = 0;
    obj._callLuaFile = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&DAT_00539700[0];
    if (q2 != 0) {
        o = (char *)*q2;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (q1 != 0) {
        o = (char *)*q1;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void FUN_00341950(void)
{
    igMetaObject_RunStaticInit(beTimerData_Register);
}

void *beTimerData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTimerData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beTimerData_GetMetaObject,
        beTimerData_className,
        0x20, /* instance size */
        beTimerData_GetVTable,
        beTimerData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beTimerData_GetMetaObject(void)
{
    FUN_00341840();
}

void beTimerData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beTimerData_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beTimerData_ctorTable[0], 4);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)), 0);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)), 0);
    igMetaObject_NameFields(temp_s0, &g_beTimerData_fieldTable[0], &DAT_004c3440[0], &DAT_004c3450[0], temp_s1);
}

