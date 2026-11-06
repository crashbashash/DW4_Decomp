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
extern igMetaObject *g_beFont_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beFont_GetMetaObject(void);
extern const char beFont_className[];
int beFont_GetVTable(void);
void beFont_InitFields(void);
extern char g_beFont_callbackList[];
void *beFont_Register(void);
}

void *beFont_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFont_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beFont_GetMetaObject,
        beFont_className,
        0x48, /* instance size */
        beFont_GetVTable,
        beFont_InitFields,
        0, /* extra callback item */
        g_beFont_callbackList /* callback list */
    );
}
