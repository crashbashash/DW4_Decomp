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
extern igMetaObject *g_beGenerater_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beGenerater_GetMetaObject(void);
extern const char beGenerater_className[];
int beGenerater_GetVTable(void);
void beGenerater_InitFields(void);
extern char g_beGenerater_callbackList[];
void *beGenerater_Register(void);
}

void *beGenerater_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGenerater_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beGenerater_GetMetaObject,
        beGenerater_className,
        0x28, /* instance size */
        beGenerater_GetVTable,
        beGenerater_InitFields,
        0, /* extra callback item */
        g_beGenerater_callbackList /* callback list */
    );
}
