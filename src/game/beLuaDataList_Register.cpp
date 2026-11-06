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
extern igMetaObject *g_beLuaDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beLuaDataList_GetMetaObject(void);
extern const char beLuaDataList_className[];
int beLuaDataList_GetVTable(void);
extern char g_beLuaDataList_callbackList[];
void *beLuaDataList_Register(void);
}

void *beLuaDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLuaDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beLuaDataList_GetMetaObject,
        beLuaDataList_className,
        0x14, /* instance size */
        beLuaDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beLuaDataList_callbackList /* callback list */
    );
}
