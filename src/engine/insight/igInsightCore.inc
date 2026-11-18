igMetaObject *g_igInsightCore_metaObject;
igMetaField *g_igInsightCore_managerListMetaField;
igMetaField *g_igInsightCore_schedulerMetaField;
igMetaField *g_igInsightCore_infoListMetaField;
igMetaField *g_igInsightCore_windowMetaField;
igMetaField *g_igInsightCore_visualContextMetaField;
igMetaField *g_igInsightCore_rendererListMetaField;
igMetaField *g_igInsightCore_dispatcherMetaField;
igMetaField *g_igInsightCore_windowResizeReceiverMetaField;
igMetaField *g_igInsightCore_messengerMetaField;
igMetaField *g_igInsightCore_clearRendererMetaField;
igMetaField *g_igInsightCore_timerMetaField;
igMetaField *g_igInsightCore_framesMetaField;
igMetaField *g_igInsightCore_currentTimeMetaField;
igMetaField *g_igInsightCore_frameTimeMetaField;
igMetaField *g_igInsightCore_currentToWorldTimeFactorMetaField;
igMetaField *g_igInsightCore_worldTimeMetaField;
igMetaField *g_igInsightCore_traversalTimeMetaField;
igMetaField *g_igInsightCore_outputTimeMetaField;
igMetaField *g_igInsightCore_pluginsMetaField;

igInsightCore *igInsightCore_CreateInstance(int allocator) {
    igInsightCore_EnsureRegistered();
    return (igInsightCore *)igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x56DB60), (igMemoryPoolView *)allocator);
}

igMetaObject *igInsightCore_GetOrCreateMetaObject(void) {
    if (g_igInsightCore_metaObject == 0) {
        g_igInsightCore_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igInsightCore_metaObject;
}

igMetaObject *igInsightCore_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightCore_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igInsightCore_EnsureRegistered();
    return g_igInsightCore_metaObject;
}

int igInsightCore_GetVTable(void) {
    struct Obj_2328e0 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igInsightCore_vtable[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w26 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igInsightCore_vtable[0];
    igSmartPointer_igInsightPluginList_Destruct((struct R **)&obj.w26, -1);
    igSmartPointer_igTimer_Destruct((igSmartPointer<igObject> *)&obj.w12, -1);
    igSmartPointer_igClearRenderer_Destruct((ObjectRefWord *)&obj.w11, -1);
    igSmartPointer_igMessenger_Destruct((void **)&obj.w10, -1);
    igSmartPointer_igWindowResizeEventReceiver_Destruct((ObjectRefWord *)&obj.w9, -1);
    igSmartPointer_igEventDispatcher_Destruct((void **)&obj.w8, -1);
    igSmartPointer_igRendererOrderedList_Destruct((igSmartPointer<igObject> *)&obj.w7, -1);
    igSmartPointer_igVisualContext_Destruct((igSmartPointer<igObject> *)&obj.w6, -1);
    igSmartPointer_igWindow_Destruct((igSmartPointer<igObject> *)&obj.w5, -1);
    igSmartPointer_igInfoList_Destruct((igSmartPointer<igObject> *)&obj.w4, -1);
    igSmartPointer_igInsightScheduler_Destruct((O *)&obj.w3, -1);
    igSmartPointer_igInfoManagerOrderedList_Destruct((void **)&obj.w2, -1);
    return t;
}

O *igSmartPointer_igInsightScheduler_Destruct(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        if (arg1 > 0) operator delete(arg0);
    }
    return arg0;
}

igSmartPointer<igObject> *igSmartPointer_igRendererOrderedList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

void **igSmartPointer_igEventDispatcher_Destruct(void **arg0, short arg1) {
    S_temp_a0_232b60 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_232b60 *)(*arg0);
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

ObjectRefWord *igSmartPointer_igWindowResizeEventReceiver_Destruct(ObjectRefWord *self,int delete_storage) {
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

void **igSmartPointer_igMessenger_Destruct(void **arg0, short arg1) {
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

ObjectRefWord *igSmartPointer_igClearRenderer_Destruct(ObjectRefWord *self,int delete_storage) {
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

struct R **igSmartPointer_igInsightPluginList_Destruct(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void igInsightCore_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igInsightCore_Register);
}

static igMetaObjectCallback g_igInsightCore_callbackList[] = { igInfoManagerOrderedList_EnsureRegistered, igInsightScheduler_EnsureRegistered, igInfoList_EnsureRegistered, igWindow_EnsureRegistered, igVisualContext_EnsureRegistered, igRendererOrderedList_EnsureRegistered, igEventDispatcher_EnsureRegistered, igWindowResizeEventReceiver_EnsureRegistered, igMessenger_EnsureRegistered, igClearRenderer_EnsureRegistered, igTimer_EnsureRegistered, igInsightPluginList_EnsureRegistered, 0 };

CallbackArray *igInsightCore_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igInsightCore_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igInsightCore_GetMetaObjectFunction,
        "igInsightCore",
        0x70, /* instance size */
        igInsightCore_GetVTable,
        &igInsightCore_InitFields,
        igInsightCore_UserRegisterFunction, /* extra callback item */
        g_igInsightCore_callbackList /* callback list */
    );
}

void igInsightCore_GetMetaObjectFunction(void) {
    igInsightCore_GetMetaObject();
}

static FieldFactory g_igInsightCore_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igIntMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igInsightCore_fieldTable[] = {
    "_managerList",
    "_scheduler",
    "_infoList",
    "_window",
    "_visualContext",
    "_rendererList",
    "_dispatcher",
    "_windowResizeReceiver",
    "_messenger",
    "_clearRenderer",
    "_timer",
    "_frames",
    "_currentTime",
    "_frameTime",
    "_currentToWorldTimeFactor",
    "_worldTime",
    "_traversalTime",
    "_outputTime",
    "_plugins",
};
static igMetaField **g_igInsightCore_fieldHandles[] = {
    &g_igInsightCore_managerListMetaField,
    &g_igInsightCore_schedulerMetaField,
    &g_igInsightCore_infoListMetaField,
    &g_igInsightCore_windowMetaField,
    &g_igInsightCore_visualContextMetaField,
    &g_igInsightCore_rendererListMetaField,
    &g_igInsightCore_dispatcherMetaField,
    &g_igInsightCore_windowResizeReceiverMetaField,
    &g_igInsightCore_messengerMetaField,
    &g_igInsightCore_clearRendererMetaField,
    &g_igInsightCore_timerMetaField,
    &g_igInsightCore_framesMetaField,
    &g_igInsightCore_currentTimeMetaField,
    &g_igInsightCore_frameTimeMetaField,
    &g_igInsightCore_currentToWorldTimeFactorMetaField,
    &g_igInsightCore_worldTimeMetaField,
    &g_igInsightCore_traversalTimeMetaField,
    &g_igInsightCore_outputTimeMetaField,
    &g_igInsightCore_pluginsMetaField,
};
static int g_igInsightCore_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    64,
    72,
    80,
    88,
    96,
    104,
};

void igInsightCore_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_11;
    void *temp_s2_12;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    igMetaObject *temp_s0;

    temp_s0 = g_igInsightCore_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igInsightCore_ctorTable, 0x13);
    temp_s2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igInfoManagerOrderedList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igInsightScheduler_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)(igInfoList_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igWindow_GetOrCreateMetaObject();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)(igVisualContext_GetOrCreateMetaObject());
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)(igRendererOrderedList_GetOrCreateMetaObject());
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)igEventDispatcher_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = (int)igWindowResizeEventReceiver_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = (int)igMessenger_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = (int)igClearRenderer_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    temp_s2_11 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = (int)igTimer_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_12 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x12));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = (int)igInsightPluginList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_12)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igInsightCore_fieldTable, g_igInsightCore_fieldHandles, g_igInsightCore_fieldOffsets, temp_s1);
}

void igInsightCore_UserRegisterFunction(void) {
    igInsightCore_UserRegister();
}

