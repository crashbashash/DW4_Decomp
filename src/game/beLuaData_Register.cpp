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
extern igMetaObject *g_beLuaData_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beLuaData_GetMetaObject(void);
extern const char beLuaData_className[];
int beLuaData_GetVTable(void);
void beLuaData_InitFields(void);
extern char g_beLuaData_callbackList[];
void *beLuaData_Register(void);
}

void *beLuaData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLuaData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beLuaData_GetMetaObject,
        beLuaData_className,
        0x10, /* instance size */
        beLuaData_GetVTable,
        beLuaData_InitFields,
        0, /* extra callback item */
        g_beLuaData_callbackList /* callback list */
    );
}
