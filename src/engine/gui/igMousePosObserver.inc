int FUN_0044ecb0(int arg0) {
    igMousePosObserver_RunStaticInit();
    return igMetaObject_CreateInstance(*(int *)0x58C380, arg0);
}

igMetaObject *igMousePosObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igMousePosObserver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMousePosObserver_RunStaticInit();
    return g_igMousePosObserver_metaObject[0];
}

int igMousePosObserver_GetVTable(void) {
    igMousePosObserver s; igMousePosObserver *o = &s; igObject *a; int t; int *p2; int *p1; int *p0;
    igObject_InitHeader(o);
    o->_vtable = (int)&DAT_00541090[0];
    p0 = &o->_intersectTraversal; p1 = &o->_ray; p2 = &o->_hitPath;
    *p0 = 0; *p1 = 0; *p2 = 0;
    igMatrix44f_SetIdentity(o->_inverseProjectionMatrix);
    t = *(int *)((char *)o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o->_vtable = (int)&D_00541090[0];
    if (p2 != 0) {
        a = *(igObject **)p2;
        if (a != 0) {
            *(int *)&a->_refCount = (int)((int) (*(int *)&a->_refCount - 1));
            if (((unsigned long long) ((long long) *(int *)&a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (p1 != 0) {
        a = *(igObject **)p1;
        if (a != 0) {
            *(int *)&a->_refCount = (int)((int) (*(int *)&a->_refCount - 1));
            if (((unsigned long long) ((long long) *(int *)&a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (p0 != 0) {
        a = *(igObject **)p0;
        if (a != 0) {
            *(int *)&a->_refCount = (int)((int) (*(int *)&a->_refCount - 1));
            if (((unsigned long long) ((long long) *(int *)&a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    return t;
}

ObjectRefWord *FUN_0044ee80(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void igMousePosObserver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igMousePosObserver_Register);
}

void igMousePosObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMousePosObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igMousePosObserver_GetMetaObject,
        igMousePosObserver_className,
        0x64, /* instance size */
        igMousePosObserver_GetVTable,
        &igMousePosObserver_InitFields,
        0, /* extra callback item */
        g_igMousePosObserver_callbackList /* callback list */
    );
}

void thunk_igMousePosObserver_GetMetaObject(void) {
    igMousePosObserver_GetMetaObject();
}

void igMousePosObserver_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_igMousePosObserver_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d0330[0], 7);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0044ded0();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0019dfd0();
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00188260();
    ((igObjectRefMetaField *)temp_s2_3)->_construct = 1;
    FUN_002e3810((int)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3), 0.0f);
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0019f670();
    igMetaObject_NameFields(temp_s1, &DAT_004d0350[0], &DAT_004d0370[0], &DAT_004d0390[0], temp_s0);
}

