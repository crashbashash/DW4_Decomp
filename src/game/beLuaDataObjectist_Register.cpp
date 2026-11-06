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
extern igMetaObject *g_beLuaDataObjectist_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beLuaDataObjectist_GetMetaObject(void);
extern const char beLuaDataObjectist_className[];
int beLuaDataObjectist_GetVTable(void);
extern char g_beLuaDataObjectist_callbackList[];
void *beLuaDataObjectist_Register(void);
}

void *beLuaDataObjectist_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLuaDataObjectist_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beLuaDataObjectist_GetMetaObject,
        beLuaDataObjectist_className,
        0x14, /* instance size */
        beLuaDataObjectist_GetVTable,
        0,
        0, /* extra callback item */
        g_beLuaDataObjectist_callbackList /* callback list */
    );
}
