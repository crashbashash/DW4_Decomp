void * FUN_002c37e0(int arg0) {
    FUN_002c3de0();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586140), (MemoryPool *)arg0));
}

int FUN_002c3820(void) {
    if (((int *)g_igIGBFile_metaObject)[0] == 0) {
        ((int *)g_igIGBFile_metaObject)[0] = (int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    }
    return ((int *)g_igIGBFile_metaObject)[0];
}

igMetaObject *igIGBFile_GetMetaObject(void)
{
    igMetaObject *g = g_igIGBFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c3de0();
    return g_igIGBFile_metaObject[0];
}

int igIGBFile_GetVTable(void) {
    union U_2c38c0 u;
    int temp_s5;

    
    
    FUN_002c3d60((igIGBFile *)&u.w[0]);
    u.w[0] = (int)(&DAT_0052fe50[0]);
    FUN_002c3d50(&u.w[23]);
    FUN_002c3d40(&u.w[26]);
    FUN_002c3d30(&u.w[47]);
    FUN_001a4510(&u.w[48]);
    FUN_002c3d20(&u.w[51]);
    FUN_002c3d20(&u.w[52]);
    FUN_00229270(&u.w[58]);
    FUN_001510d0(&u.w[61]);
    FUN_002c3d10(&u.w[70]);
    FUN_002c3d10(&u.w[71]);
    FUN_002c3d10(&u.w[72]);
    FUN_001510d0(&u.w[76]);
    temp_s5 = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.w[0] = (int)(&DAT_0052fe40[4]);
    ObjectRef_Destruct_00150eb0(&u.w[76], -1);
    FUN_001509f0(&u.w[72], -1);
    FUN_001509f0(&u.w[71], -1);
    FUN_001509f0(&u.w[70], -1);
    ObjectRef_Destruct_00150eb0(&u.w[61], -1);
    StringRef_Destruct_00130720(&u.w[58], -1);
    FUN_0014ec50(&u.w[52], -1);
    FUN_0014ec50(&u.w[51], -1);
    FUN_0013a880(&u.w[48], -1);
    FUN_0014e420(&u.w[47], -1);
    FUN_00150180(&u.w[26], -1);
    FUN_0014aa70(&u.w[23], -1);
    FUN_002c3b00((Obj_2c3b00 *)&u.w[0], 0);
    return temp_s5;
}

ObjectRefWord *FUN_002c3a80(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

Obj_2c3b00 *FUN_002c3b00(Obj_2c3b00 *p, short n) {
    if (p) {
        p->vt = (int)&DAT_00530890[0];
        p->f44.release();
        p->f3c.release();
        p->f2c.release();
        p->f28.release();
        p->f1c.release();
        p->f18.release();
        p->f14.release();
        if (n > 0) thunk_FUN_002ed460__002ff810((int)p);
    }
    return p;
}

int *FUN_002c3d10(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_002c3d20(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_002c3d30(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_002c3d40(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_002c3d50(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void *FUN_002c3d60(igIGBFile *arg0) {
    igObject_InitHeader((struct ObjectHeader *)arg0);
    arg0->_vtable = (int)(&DAT_005309b0[0]);
    arg0->_vtable = (int)(&DAT_00524a20[0]);
    arg0->_vtable = (int)(&DAT_005249b0[0]);
    arg0->_vtable = (int)(&DAT_00532590[0]);
    arg0->_vtable = (int)(&DAT_00530890[0]);
    arg0->_name = 0;
    arg0->_externalDirectoryList = 0;
    arg0->_infoList = 0;
    arg0->_uniqueEntryList = 0;
    arg0->_refList = 0;
    arg0->_metaFieldPerObjectIndices = 0;
    arg0->_loadingSemaphore = 0;
    return arg0;
}

void FUN_002c3de0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igIGBFile_Register);
}

void igIGBFile_Register(void) {
    FUN_002b5d50();  /* First-use initializer: sets a gp byte flag, then runs five one-time init calls. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igIGBFile_metaObject),
        igDirectory_Register,
        igDirectory_GetPublishedMetaObject,
        thunk_igIGBFile_GetMetaObject,
        igIGBFile_className,
        sizeof(igIGBFile),                           /* Instance size. */
        igIGBFile_GetVTable,
        &igIGBFile_InitFields,
        FUN_002c43a0, /* extra callback item */
        g_igIGBFile_callbackList /* callback list */
    );
}

void thunk_igIGBFile_GetMetaObject(void) {
    igIGBFile_GetMetaObject();
}

igMetaObject *FUN_002c3e80(void) {
    return g_igDirectory_metaObject[0];
}

void igIGBFile_InitFields(void) {
    igMetaObject *meta = g_igIGBFile_metaObject[0];
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    igMetaField *clone;
    int index;
    igMetaObject_CreateFields(meta, (igMetaField * (**)(void *))DAT_004c0660, 0x41);
    field = ((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)data));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    clone = ((DescriptorCloneView_2c3e90 *)field)->Clone(1);
    clone->_persistent = 0;
    clone->_externalEnumStorage = (int)DAT_00586148;
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    releaseField(clone);
    field = ((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)DAT_004f6de8));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    clone = ((DescriptorCloneView_2c3e90 *)field)->Clone(1);
    clone->_persistent = 0;
    clone->_externalEnumStorage = (int)DAT_00586150;
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    releaseField(clone);
    field = ((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)DAT_004f5d80));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    clone = ((DescriptorCloneView_2c3e90 *)field)->Clone(1);
    clone->_persistent = 0;
    clone->_externalEnumStorage = (int)DAT_00586158;
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    releaseField(clone);
    FUN_002ea4b0((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base))), 0xFADA);
    FUN_002ea4b0((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 1))), 6);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)field)->_metaObject = (int)FUN_002c4ce0();
    ((igMetaField *)field)->_persistent = 0;
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 8));
    ((igMemoryRefMetaField *)field)->_memType = FUN_002cc2c0();
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x12))->_persistent = 0;
    FUN_002ea4b0((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x13))), -1);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x15));
    ((igMemoryRefMetaField *)field)->_memType = FUN_002cc2c0();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x16));
    ((igMemoryRefMetaField *)field)->_memType = FUN_002cc2c0();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x17));
    ((igMemoryRefMetaField *)field)->_memType = FUN_002cc2c0();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x18));
    ((igMemoryRefMetaField *)field)->_memType = FUN_002cc2c0();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x19));
    ((igObjectRefMetaField *)field)->_metaObject = (int)FUN_002c8b30();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x1A));
    ((igObjectRefMetaField *)field)->_metaObject = (int)FUN_002c8e50();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x1C));
    ((igMemoryRefMetaField *)field)->_memType = FUN_002cc2c0();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x1D));
    ((igObjectRefMetaField *)field)->_metaObject = (int)FUN_002beca0();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x1E));
    ((igObjectRefMetaField *)field)->_metaObject = (int)FUN_002beca0();
    FUN_002ea4b0((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x24))), -1);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x25));
    ((igMemoryRefMetaField *)field)->_memType = FUN_002cc2c0();
    igStringMetaField_SetDefaultText((int *)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x27))), 0);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x28));
    ((igMemoryRefMetaField *)field)->_memType = FUN_002cc2c0();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x2A));
    ((igObjectRefMetaField *)field)->_metaObject = igIntList_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x2C));
    ((igMemoryRefMetaField *)field)->_memType = FUN_002cc2c0();
    FUN_002ea4b0((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x2E))), -1);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x2F));
    ((igMemoryRefMetaField *)field)->_memType = FUN_002cc2c0();
    FUN_002ea4b0((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x32))), -1);
    FUN_002d3890((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x36))), 1);
    FUN_002d3890((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x37))), 1);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x39));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x3A));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x3B));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x3C));
    ((igObjectRefMetaField *)field)->_metaObject = igObjectList_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x3F));
    ((igMemoryRefMetaField *)field)->_memType = FUN_002cc2c0();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x40));
    ((igObjectRefMetaField *)field)->_metaObject = igIntList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, (const char **)&DAT_004c0770[0], (igMetaField ***)&DAT_004c0880[0], &DAT_004c0990[0], base);
}

void FUN_002c43a0(void) {
    FUN_002e7000();
}

