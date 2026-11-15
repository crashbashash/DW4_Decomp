igMetaObject *g_igTextureBindAttr_metaObject;
igMetaField *g_igTextureBindAttr_textureMetaField;
igMetaField *g_igTextureBindAttr_unitIDMetaField;

void FUN_00132810(int arg0) {
    FUN_00132a00();
    igMetaObject_CreateInstance(*(int *)0x55ED88, arg0);
}

igMetaObject *FUN_00132850(void) {
    if (g_igTextureBindAttr_metaObject == 0) {
        g_igTextureBindAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTextureBindAttr_metaObject;
}

igMetaObject *igTextureBindAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureBindAttr_metaObject != 0) {
        ready = (g_igTextureBindAttr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00132a00();
done:
    return g_igTextureBindAttr_metaObject;
}

int igTextureBindAttr_GetVTable(void) {
    struct Obj_1328f0 obj;
    char *o;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00522bd0[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00522bd0[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

ObjectRefWord *FUN_00132980(ObjectRefWord *self,int delete_storage) {
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

void FUN_00132a00(void)
{
    igMetaObject_RunStaticInit(igTextureBindAttr_Register);
}

static igMetaObjectCallback g_igTextureBindAttr_callbackList[] = { FUN_00132cf0, 0 };

void igTextureBindAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureBindAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureBindAttr_GetMetaObject,
        "igTextureBindAttr",
        0x14, /* instance size */
        igTextureBindAttr_GetVTable,
        &igTextureBindAttr_InitFields,
        thunk_FUN_00140f40, /* extra callback item */
        g_igTextureBindAttr_callbackList /* callback list */
    );
}

void thunk_igTextureBindAttr_GetMetaObject(void) {
    igTextureBindAttr_GetMetaObject();
}

static FieldFactory g_igTextureBindAttr_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_igTextureBindAttr_fieldTable[] = {
    "_texture",
    "_unitID",
};
static igMetaField **g_igTextureBindAttr_fieldHandles[] = {
    &g_igTextureBindAttr_textureMetaField,
    &g_igTextureBindAttr_unitIDMetaField,
};
static int g_igTextureBindAttr_fieldOffsets[] = {
    12,
    16,
};

void igTextureBindAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;
    temp_s0 = g_igTextureBindAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igTextureBindAttr_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_00132ba0();
    temp_s1 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    *(int *)((char *)temp_s1 + 48) = (int)FUN_00140e40;
    igMetaObject_NameFields(temp_s0, g_igTextureBindAttr_fieldTable, g_igTextureBindAttr_fieldHandles, g_igTextureBindAttr_fieldOffsets, temp_s2);
}

void thunk_FUN_00140f40(void) {
    FUN_00140f40();
}

