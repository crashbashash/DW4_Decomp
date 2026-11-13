igMetaObject *FUN_00233480(void) {
    if (g_igInfoManagerOrderedList_metaObject[0] == 0) {
        g_igInfoManagerOrderedList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igInfoManagerOrderedList_metaObject[0];
}

igMetaObject *igInfoManagerOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManagerOrderedList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002336b0();
    return g_igInfoManagerOrderedList_metaObject[0];
}

int igInfoManagerOrderedList_GetVTable(void) {
    Obj_233520 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[2] = 0;
    o.w[3] = 0;
    o.w[4] = 0;
    o.vt = &DAT_0052cb60[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_0052cb60[0];
    FUN_00233610((int **)&o, 0);
    return r;
}

ObjectRefWord *FUN_00233590(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

int **FUN_00233610(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_0052cbc0[0];
        if (arg0 != 0) {
            *arg0 = &DAT_0052cc20[0];
            ObjectRef_Destruct_001c6460((int **)((char *)arg0 + 0x14), -1);
            FUN_00135430((int **)((char *)arg0 + 0x10), -1);
            FUN_00233590((ObjectRefWord *)((char *)arg0 + 0xC), -1);
            FUN_0014aa70((int **)((char *)arg0 + 8), -1);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void FUN_002336b0(void)
{
    igMetaObject_RunStaticInit(igInfoManagerOrderedList_Register);
}

void igInfoManagerOrderedList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInfoManagerOrderedList_metaObject,
        igDependencyOrderedList_Register,
        igDependencyOrderedList_GetPublishedMetaObject,
        thunk_igInfoManagerOrderedList_GetMetaObject,
        igInfoManagerOrderedList_className,
        0x1C, /* instance size */
        igInfoManagerOrderedList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInfoManagerOrderedList_callbackList /* callback list */
    );
}

void thunk_igInfoManagerOrderedList_GetMetaObject(void) {
    igInfoManagerOrderedList_GetMetaObject();
}

int FUN_00233740(void) {
    return g_igDependencyOrderedList_metaObject[0];
}

