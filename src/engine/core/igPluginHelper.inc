void *igPluginHelper_Create(int pool) {
    igPluginHelper_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585AB8), (igMemoryPoolView *)pool);
}

igMetaObject *igPluginHelper_GetMetaObject(void)
{
    igMetaObject *g = g_igPluginHelper_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igPluginHelper_EnsureRegistered();
    return g_igPluginHelper_metaObject[0];
}

int igPluginHelper_GetVTable(void) {
    igPluginHelper helper;
    int vtable;
    igObject_InitHeader((igObject *)&helper);
    helper._vtable = (int)&g_igPluginHelper_vtable[0];
    helper._pluginExtension = 0;
    helper._repositoryList = 0;
    helper._libraryLoader = 0;
    helper._loadedPlugins = 0;
    vtable = *(int *)((char *)&helper + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    helper._vtable = (int)&g_igPluginHelper_vtable[0];
    igSmartPointer_igLibraryList_Destruct((igSmartPointer<igObject> *)(&helper._loadedPlugins), -1);
    igSmartPointer_igLibraryLoader_Destruct((void **)(&helper._libraryLoader), (short)(-1));
    igSmartPointer_igPluginRepositoryList_Destruct((void **)(&helper._repositoryList), (long long)(-1));
    igStringRef_Destruct(&helper._pluginExtension, -1);
    return vtable;
}

void **igSmartPointer_igPluginRepositoryList_Destruct(void **pointer, long long flags) {
    igObject *list;

    if (pointer != 0) {
        list = (igObject *)*pointer;
        if (list != 0) {
            list->_refCount = list->_refCount - 1;
            if ((list->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(list);
            }
        }
        if ((short)flags > 0) {
            __dl__FPv(pointer);
        }
    }
    return pointer;
}

void **igSmartPointer_igLibraryLoader_Destruct(void **pointer, short flags) {
    igLibraryLoaderView *loader;

    if (pointer != 0) {
        loader = (igLibraryLoaderView *)*pointer;
        if (loader != 0) {
            loader->_refCount = loader->_refCount - 1;
            if ((loader->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(loader);
            }
        }
        if (flags > 0) {
            __dl__FPv(pointer);
        }
    }
    return pointer;
}

igSmartPointer<igObject> *igSmartPointer_igLibraryList_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
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

void igPluginHelper_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPluginHelper_Register);
}

void igPluginHelper_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igPluginHelper_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igPluginHelper_GetMetaObjectFunction,
        igPluginHelper_className,
        0x18,
        igPluginHelper_GetVTable,
        igPluginHelper_InitFields,
        0,
        (igMetaObjectCallback *)g_igPluginHelper_callbackList
    );
}

void igPluginHelper_GetMetaObjectFunction(void) {
    igPluginHelper_GetMetaObject();
}

void igPluginHelper_InitFields(void) {
    int first;
    void *pluginsField;
    void *loaderField;
    void *repositoryField;
    void *meta;

    meta = (void *)g_igPluginHelper_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igPluginHelper_ctorTable[0], 4);
    igStringMetaField_SetDefaultText((int *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first))), (int)&text_dot_so[0]);
    repositoryField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 1)));
    ((igObjectRefMetaField *)repositoryField)->_metaObject = (int)igPluginRepositoryList_GetOrCreateMetaObject();
    ((igRefMetaField *)repositoryField)->_construct = 1;
    loaderField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2)));
    ((igObjectRefMetaField *)loaderField)->_metaObject = (int)igLibraryLoader_GetOrCreateMetaObject();
    ((igRefMetaField *)loaderField)->_construct = 1;
    pluginsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 3)));
    ((igObjectRefMetaField *)pluginsField)->_metaObject = (int)igLibraryList_GetOrCreateMetaObject();
    ((igRefMetaField *)pluginsField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igPluginHelper_fieldTable[0], (igMetaField ***)&g_igPluginHelper_fieldDescriptors[0], &g_igPluginHelper_fieldOffsets[0], first);
}

