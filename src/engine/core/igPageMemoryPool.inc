int Gap__Core__igPageMemoryPool__vfunc_21(int arg0, int arg1) {
    int temp_v0;

    if (*g_objectSystem[0] != 0) {
        FUN_002cd7c0();
        return igObject_CloneViaMetadata((void **)arg0, arg1);
    }
    temp_v0 = ((int)FUN_002f0040(0x110, 0, ((int)Memory_GetDefaultAllocator())));
    if (temp_v0 != 0) {
        temp_v0 = ((int)FUN_00325810((igPageMemoryPool *)temp_v0, arg0));
    }
    return temp_v0;
}

igMetaObject *igPageMemoryPool_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igPageMemoryPool_metaObject[0] != 0) {
        ready = (g_igPageMemoryPool_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_002cd7c0();
done:
    return g_igPageMemoryPool_metaObject[0];
}

int igPageMemoryPool_GetVTable(void) {
    igPageMemoryPool pool;
    int temp_s0;
    igObject *q0;
    igObject *q1;
    FUN_003257d0(&pool);
    temp_s0 = *(int *)((char *)&pool + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    pool._vtable = (int)&DAT_005311f0[0];
    q0 = (igObject *)&pool._eventTracker;
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)((int) (q0->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    q1 = (igObject *)&pool._allocationLock;
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        if (q1 != 0) {
            q1->_refCount = (int)((int) (q1->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }

    return temp_s0;
}

void FUN_002cd7c0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPageMemoryPool_Register);
}

void igPageMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPageMemoryPool_metaObject),
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        thunk_igPageMemoryPool_GetMetaObject,
        igPageMemoryPool_className,
        0x110, /* instance size */
        igPageMemoryPool_GetVTable,
        &igPageMemoryPool_InitFields,
        0, /* extra callback item */
        g_igPageMemoryPool_callbackList /* callback list */
    );
}

void thunk_igPageMemoryPool_GetMetaObject(void) {
    igPageMemoryPool_GetMetaObject();
}

void igPageMemoryPool_InitFields(void) {
    igMetaObject *meta = g_igPageMemoryPool_metaObject[0];
    int base = igMetaObject_GetFieldCount(meta);
    int defaultMessageLevel;
    igObjectRefMetaField *eventTracker;
    igObjectRefMetaField *allocationLock;
    igEnumMetaField *messageLevel;
    igMetaObject_CreateFields(meta, (FieldFactory *)g_igPageMemoryPool_ctorTable, 7);
    FUN_0030ec10((void **)igMetaObject_GetFieldAt(meta, base), 0xFFFFFFFFFFFFFFFFULL);
    eventTracker = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 1);
    eventTracker->_metaObject = (int)FUN_002c57c0();
    allocationLock = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 3);
    allocationLock->_metaObject = (int)FUN_002ba690();
    FUN_002ea4b0((void **)igMetaObject_GetFieldAt(meta, base + 4), -1);
    messageLevel = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 5);
    defaultMessageLevel = DAT_004c2600[0];
    FUN_002dc7a0((igMetaFieldView *)messageLevel, &defaultMessageLevel);
    messageLevel->_getMetaEnumFunction = (int)FUN_002cd5c0;
    FUN_002ea4b0((void **)igMetaObject_GetFieldAt(meta, base + 6), g_igPageMemoryPool_defaultPoolOptionFlags[0]);
    igMetaObject_NameFields(meta, (const char **)g_igPageMemoryPool_fieldTable, (igMetaField ***)DAT_004c1720, DAT_004c1740, base);
    g_igPageMemoryPool_metaObject[0]->_writeProxy = (int)thunk_igMemoryPool_GetMetaObject;
}

int FUN_002cd990(void) {
    if (DAT_00586a70[0] == 0) {
        DAT_00586a70[0] = ((int)igMetaEnum_Create((char *)&text_ArenaMemoryPoolFlags[0], (char **)&DAT_004c1760[0], &DAT_004c1790[0], 0xA));
    }
    return DAT_00586a70[0];
}

int FUN_002cd9f0(void) {
    if (DAT_00586a78[0] == 0) {
        DAT_00586a78[0] = ((int)igMetaEnum_Create((char *)&text_MessageLevel[0], (char **)&DAT_004c17c0[0], &DAT_004c17d0[0], 4));
    }
    return DAT_00586a78[0];
}

int FUN_002cda50(void) {
    if (DAT_00586a80[0] == 0) {
        DAT_00586a80[0] = ((int)igMetaEnum_Create((char *)&text_HeapIntegrityCheckLevel[0], (char **)&DAT_004c17e0[0], &DAT_004c17f0[0], 4));
    }
    return DAT_00586a80[0];
}

