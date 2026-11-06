struct igMetaObject;
extern "C" {
void BecLibrary_MarkRegistered(void);
void *igMetaObject_RegisterClass(
        int abstractState,
        igMetaObject **slot,
        void *(*baseRegister)(void),
        igMetaObject *(*baseMetaObject)(void),
        igMetaObject *(*getMetaObject)(void),
        const char *className,
        int instanceSize,
        int (*getVTable)(void),
        void (*initFields)(void),
        void (*callbackItem)(void),
        void *callbackList);
extern igMetaObject *g_beLuaDataObject_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beLuaDataObject_GetMetaObject(void);
extern const char beLuaDataObject_className[];
int beLuaDataObject_GetVTable(void);
void beLuaDataObject_InitFields(void);
void *beLuaDataObject_Register(void);
}

void *beLuaDataObject_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLuaDataObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beLuaDataObject_GetMetaObject,
        beLuaDataObject_className,
        0x10, /* instance size */
        beLuaDataObject_GetVTable,
        beLuaDataObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
