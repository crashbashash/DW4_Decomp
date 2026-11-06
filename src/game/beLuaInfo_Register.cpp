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
extern igMetaObject *g_beLuaInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beLuaInfo_GetMetaObject(void);
extern const char beLuaInfo_className[];
int beLuaInfo_GetVTable(void);
void beLuaInfo_InitFields(void);
extern char g_beLuaInfo_callbackList[];
void *beLuaInfo_Register(void);
}

void *beLuaInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLuaInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beLuaInfo_GetMetaObject,
        beLuaInfo_className,
        0x20, /* instance size */
        beLuaInfo_GetVTable,
        beLuaInfo_InitFields,
        0, /* extra callback item */
        g_beLuaInfo_callbackList /* callback list */
    );
}
