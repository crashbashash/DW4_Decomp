igMetaObject *g_igPluginHelper_metaObject;
igMetaField *g_igPluginHelper_pluginExtensionMetaField;
igMetaField *g_igPluginHelper_repositoryListMetaField;
igMetaField *g_igPluginHelper_libraryLoaderMetaField;
igMetaField *g_igPluginHelper_loadedPluginsMetaField;

void *igPluginHelper_Create(int pool) {
    igPluginHelper_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance(g_igPluginHelper_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igPluginHelper_GetMetaObject(void)
{
    igMetaObject *g = g_igPluginHelper_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPluginHelper_EnsureRegistered();
    return g_igPluginHelper_metaObject;
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
    vtable = *(int *)((char *)&helper + g_objectSystem->vtableProbeOffset);
    helper._vtable = (int)&g_igPluginHelper_vtable[0];
    igSmartPointer_igLibraryList_Destruct((igSmartPointer<igObject> *)(&helper._loadedPlugins), -1);
    igSmartPointer_igLibraryLoader_Destruct((void **)(&helper._libraryLoader), (short)(-1));
    igSmartPointer_igPluginRepositoryList_Destruct((void **)(&helper._repositoryList), (long long)(-1));
    igStringRef_Destruct((igStringRef *)&helper._pluginExtension, -1);
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
            operator delete(pointer);
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
            operator delete(pointer);
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
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

void igPluginHelper_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPluginHelper_Register);
}

static igMetaObjectCallback g_igPluginHelper_callbackList[] = { igPluginRepositoryList_EnsureRegistered, igLibraryLoader_EnsureRegistered, igLibraryList_EnsureRegistered, 0 };

CallbackArray *igPluginHelper_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igPluginHelper_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igPluginHelper_GetMetaObjectFunction,
        "igPluginHelper",
        0x18,
        igPluginHelper_GetVTable,
        igPluginHelper_InitFields,
        0,
        g_igPluginHelper_callbackList
    );
}

void igPluginHelper_GetMetaObjectFunction(void) {
    igPluginHelper_GetMetaObject();
}

static FieldFactory g_igPluginHelper_ctorTable[] = {
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igPluginHelper_fieldTable[] = {
    "_pluginExtension",
    "_repositoryList",
    "_libraryLoader",
    "_loadedPlugins",
};
static igMetaField **g_igPluginHelper_fieldDescriptors[] = {
    &g_igPluginHelper_pluginExtensionMetaField,
    &g_igPluginHelper_repositoryListMetaField,
    &g_igPluginHelper_libraryLoaderMetaField,
    &g_igPluginHelper_loadedPluginsMetaField,
};
static int g_igPluginHelper_fieldOffsets[] = {
    8,
    12,
    16,
    20,
};

void igPluginHelper_InitFields(void) {
    int first;
    void *pluginsField;
    void *loaderField;
    void *repositoryField;
    void *meta;

    meta = (void *)g_igPluginHelper_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igPluginHelper_ctorTable, 4);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt((igMetaObject *)meta, first), ".so");
    repositoryField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 1)));
    ((igObjectRefMetaField *)repositoryField)->_metaObject = (int)igPluginRepositoryList_GetOrCreateMetaObject();
    ((igRefMetaField *)repositoryField)->_construct = 1;
    loaderField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2)));
    ((igObjectRefMetaField *)loaderField)->_metaObject = (int)igLibraryLoader_GetOrCreateMetaObject();
    ((igRefMetaField *)loaderField)->_construct = 1;
    pluginsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 3)));
    ((igObjectRefMetaField *)pluginsField)->_metaObject = (int)igLibraryList_GetOrCreateMetaObject();
    ((igRefMetaField *)pluginsField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igPluginHelper_fieldTable, g_igPluginHelper_fieldDescriptors, g_igPluginHelper_fieldOffsets, first);
}

