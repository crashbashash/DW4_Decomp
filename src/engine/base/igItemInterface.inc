igMetaObject *g_igItemInterface_metaObject;
igMetaField *g_igItemInterface_itemDataBaseListMetaField;
igMetaField *g_igItemInterface_metaListMetaField;
igMetaField *g_igItemInterface_itemListMetaField;
igMetaField *g_igItemInterface_itemNameListMetaField;
igMetaField *g_igItemInterface_currentKnownItemMetaField;

igMetaObject *FUN_00227c20(void) {
    if (g_igItemInterface_metaObject == 0) {
        g_igItemInterface_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igItemInterface_metaObject;
}

igMetaObject *igItemInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igItemInterface_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00227ef0();
    return g_igItemInterface_metaObject;
}

int igItemInterface_GetVTable(void) {
    struct Obj_7 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igItemInterface_vtable[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj.vt = &g_igItemInterface_vtable[0];
    igSmartPointer_igStringRefListList_Destruct((void **)&obj.w11, -1);
    FUN_00227df0((ObjectRefWord *)&obj.w10, -1);
    igSmartPointer_igMetaObjectList_Destruct(&obj.w9, -1);
    FUN_00227d70((void **)&obj.w8, -1);
    return t;
}

void **FUN_00227d70(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

/* Deleting destructor; the deletion flag is a signed short. */
ObjectRefWord *FUN_00227df0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

void **igSmartPointer_igStringRefListList_Destruct(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)r);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void FUN_00227ef0(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igItemInterface_Register);
}

static igMetaObjectCallback g_igItemInterface_callbackList[] = { FUN_00228190, igMetaObjectList_EnsureRegistered, igMetaObjectListList_EnsureRegistered, igStringRefListList_EnsureRegistered, 0 };

CallbackArray *igItemInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igItemInterface_metaObject,
        (igMetaObjectRegisterFunction)igInterface_Register,
        (igMetaObjectGetFunction)igInterface_GetPublishedMetaObject,
        thunk_igItemInterface_GetMetaObject,
        "igItemInterface",
        0x34, /* instance size */
        igItemInterface_GetVTable,
        &igItemInterface_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igItemInterface_callbackList /* callback list */
    );
}

void thunk_igItemInterface_GetMetaObject(void) {
    igItemInterface_GetMetaObject();
}

static FieldFactory g_igItemInterface_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igItemInterface_fieldTable[] = {
    "_itemDataBaseList",
    "_metaList",
    "_itemList",
    "_itemNameList",
    "_currentKnownItem",
};
static igMetaField **g_igItemInterface_fieldHandles[] = {
    &g_igItemInterface_itemDataBaseListMetaField,
    &g_igItemInterface_metaListMetaField,
    &g_igItemInterface_itemListMetaField,
    &g_igItemInterface_itemNameListMetaField,
    &g_igItemInterface_currentKnownItemMetaField,
};
static int g_igItemInterface_fieldOffsets[] = {
    32,
    36,
    40,
    44,
    48,
};

void igItemInterface_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    igMetaObject *temp_s1;

    temp_s1 = g_igItemInterface_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_igItemInterface_ctorTable, 5);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_002280b0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igMetaObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igMetaObjectListList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igStringRefListList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s1, g_igItemInterface_fieldTable, g_igItemInterface_fieldHandles, g_igItemInterface_fieldOffsets, temp_s0);
    igMetaObject_AddExitCallback((int)FUN_002280a0);
}

void FUN_002280a0(void) {
    FUN_00229980();
}

