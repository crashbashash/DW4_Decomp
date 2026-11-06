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
extern igMetaObject *g_beLua_metaObject[];
void *igInfoManager_Register(void);
igMetaObject *igInfoManager_GetPublishedMetaObject(void);
igMetaObject *beLua_GetMetaObject(void);
extern const char beLua_className[];
int beLua_GetVTable(void);
void beLua_InitFields(void);
extern char g_beLua_callbackList[];
void *beLua_Register(void);
}

void *beLua_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLua_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beLua_GetMetaObject,
        beLua_className,
        0x20, /* instance size */
        beLua_GetVTable,
        beLua_InitFields,
        0, /* extra callback item */
        g_beLua_callbackList /* callback list */
    );
}
