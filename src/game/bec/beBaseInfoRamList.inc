int beBaseInfoRamList_GetOrCreateMetaObject(void) {
    if (((int *)DAT_00589d20)[0] == 0) {
        ((int *)DAT_00589d20)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589d20)[0];
}

void *beBaseInfoRamList_GetReadyMetaObject(void) {
    igMetaObject *g = DAT_00589d20[0];
    int ready;
    if (g) {
        /* matching construct: the readiness test materialised as an int (`sltu`) before
         * the branch; a bool or a direct `if` folds it into the branch under -O3,p */
        ready = (g->_validity & 4) != 0;
        if (ready) goto end;
    }
    beBaseInfoRamList_EnsureRegistered();
end:
    return DAT_00589d20[0];
}

int beBaseInfoRamList_GetVTable(void) {
    union U_36a140 u;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00534890[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}

void beBaseInfoRamList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBaseInfoRamList_Register);
}

void *beBaseInfoRamList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBaseInfoRamList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beBaseInfoRamList_GetMetaObject,
        beBaseInfoRamList_className,
        0x14, /* instance size */
        beBaseInfoRamList_GetVTable,
        0,
        0, /* extra callback item */
        g_beBaseInfoRamList_callbackList /* callback list */
    );
}

void *beBaseInfoRamList_GetMetaObject(void)
{
    return beBaseInfoRamList_GetReadyMetaObject();
}

