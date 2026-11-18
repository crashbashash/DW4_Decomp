igMetaObject *g_igGuiComponent_metaObject;
igMetaField *g_igGuiComponent_controllerMetaField;
igMetaField *g_igGuiComponent_modelMetaField;
igMetaField *g_igGuiComponent_aspectMetaField;
igMetaField *g_igGuiComponent_parentMetaField;
igMetaField *g_igGuiComponent_guiSystemMetaField;
igMetaField *g_igGuiComponent_nodeMetaField;
igMetaField *g_igGuiComponent_linkedMetaField;

igMetaObject *igGuiComponent_GetOrCreateMetaObject(void) {
    if (g_igGuiComponent_metaObject == 0) {
        g_igGuiComponent_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGuiComponent_metaObject;
}

igMetaObject *igGuiComponent_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponent_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponent_EnsureRegistered();
    return g_igGuiComponent_metaObject;
}

int igGuiComponent_GetVTable(void) {
    struct Obj_44ffe0 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igGuiComponent_vtable[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igGuiComponent_vtable[0];
    FUN_00450370((ObjectRefWord *)&obj.w7, -1);
    FUN_004502f0((void **)&obj.w5, -1);
    FUN_00450270((ObjectRefWord *)&obj.w4, -1);
    FUN_004501f0((void **)&obj.w3, -1);
    return t;
}

O_450090 *FUN_00450090(O_450090 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &g_igGuiComponent_vtable[0];
        if (&arg0->m28) {
            S1 *t = arg0->m28;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        }
        if (&arg0->m20) {
            S1 *t = arg0->m20;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        }
        if (&arg0->m16) {
            S1 *t = arg0->m16;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        }
        if (&arg0->m12) {
            S1 *t = arg0->m12;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        }
        if (arg1 > 0) Memory_FreeBufferAliasC(arg0);
    }
    return arg0;
}

void **FUN_004501f0(void **arg0, short arg1) {
    S_temp_a0_4501f0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_4501f0 *)(*arg0);
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

ObjectRefWord *FUN_00450270(ObjectRefWord *self,int delete_storage) {
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

void **FUN_004502f0(void **arg0, short arg1) {
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

ObjectRefWord *FUN_00450370(ObjectRefWord *self,int delete_storage) {
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

void igGuiComponent_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponent_Register);
}

static igMetaObjectCallback g_igGuiComponent_callbackList[] = { igGuiComponentController_EnsureRegistered, igGuiComponentModel_RunStaticInit, igGuiComponentAspect_EnsureRegistered, igGuiSystem_RunStaticInit, igGuiComponentNode_RunStaticInit, 0 };

CallbackArray *igGuiComponent_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGuiComponent_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igGuiComponent_GetMetaObjectFunction,
        "igGuiComponent",
        0x24, /* instance size */
        igGuiComponent_GetVTable,
        &igGuiComponent_InitFields,
        0, /* extra callback item */
        g_igGuiComponent_callbackList /* callback list */
    );
}

void igGuiComponent_GetMetaObjectFunction(void) {
    igGuiComponent_GetMetaObject();
}

static FieldFactory g_igGuiComponent_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_igGuiComponent_fieldTable[] = {
    "_controller",
    "_model",
    "_aspect",
    "_parent",
    "_guiSystem",
    "_node",
    "_linked",
};
static igMetaField **g_igGuiComponent_fieldHandles[] = {
    &g_igGuiComponent_controllerMetaField,
    &g_igGuiComponent_modelMetaField,
    &g_igGuiComponent_aspectMetaField,
    &g_igGuiComponent_parentMetaField,
    &g_igGuiComponent_guiSystemMetaField,
    &g_igGuiComponent_nodeMetaField,
    &g_igGuiComponent_linkedMetaField,
};
static int g_igGuiComponent_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    8,
    28,
    32,
};

void igGuiComponent_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s1;

    temp_s1 = (void *)g_igGuiComponent_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igGuiComponent_ctorTable, 7);
    temp_s2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igGuiComponentController_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igGuiComponentModel_GetOrCreateMetaObject();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igGuiComponentAspect_GetOrCreateMetaObject();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igGuiComponent_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_4)->_refCounted = 0;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igGuiSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_5)->_refCounted = 0;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)igGuiComponentNode_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igGuiComponent_fieldTable, g_igGuiComponent_fieldHandles, g_igGuiComponent_fieldOffsets, temp_s0);
}

