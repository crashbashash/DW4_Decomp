void FUN_002bc300(int arg0) {
    FUN_002bc5c0();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585AB8), (igMemoryPoolView *)arg0);
}

igMetaObject *igPluginHelper_GetMetaObject(void)
{
    igMetaObject *g = g_igPluginHelper_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bc5c0();
    return g_igPluginHelper_metaObject[0];
}

int igPluginHelper_GetVTable(void) {
    igPluginHelper helper;
    int t;
    igObject_InitHeader((igObject *)&helper);
    helper._vtable = (int)&DAT_0052eee0[0];
    helper._pluginExtension = 0;
    helper._repositoryList = 0;
    helper._libraryLoader = 0;
    helper._loadedPlugins = 0;
    t = *(int *)((char *)&helper + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    helper._vtable = (int)&DAT_0052eee0[0];
    FUN_002bc540((igSmartPointer<igObject> *)(&helper._loadedPlugins), -1);
    FUN_002bc4c0((void **)(&helper._libraryLoader), (short)(-1));
    FUN_002bc440((void **)(&helper._repositoryList), (long long)(-1));
    StringRef_Destruct_00130720(&helper._pluginExtension, -1);
    return t;
}

void **FUN_002bc440(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_002bc4c0(void **arg0, short arg1) {
    igLibraryLoaderView *loader;

    if (arg0 != 0) {
        loader = (igLibraryLoaderView *)*arg0;
        if (loader != 0) {
            loader->_refCount = loader->_refCount - 1;
            if ((loader->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(loader);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *FUN_002bc540(igSmartPointer<igObject> *self,int delete_storage) {
    if(self) {
        igObject *object=self->p;
        if(object) {
            --object->_refCount;
            if(((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void FUN_002bc5c0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPluginHelper_Register);
}

void igPluginHelper_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPluginHelper_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igPluginHelper_GetMetaObject,
        igPluginHelper_className,
        0x18, /* instance size */
        igPluginHelper_GetVTable,
        &igPluginHelper_InitFields,
        0, /* extra callback item */
        g_igPluginHelper_callbackList /* callback list */
    );
}

void thunk_igPluginHelper_GetMetaObject(void) {
    igPluginHelper_GetMetaObject();
}

void igPluginHelper_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igPluginHelper_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igPluginHelper_ctorTable[0], 4);
    igStringMetaField_SetDefaultText((int *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2))), (int)&DAT_004f6340[0]);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002bc760();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_002c2290();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3)));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_002c23b0();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igPluginHelper_fieldTable[0], (igMetaField ***)&DAT_004bfa10[0], &DAT_004bfa20[0], temp_s2);
}

