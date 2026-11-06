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
extern igMetaObject *g_beMovie_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beMovie_GetMetaObject(void);
extern const char beMovie_className[];
int beMovie_GetVTable(void);
void beMovie_InitFields(void);
extern char g_beMovie_callbackList[];
void *beMovie_Register(void);
}

void *beMovie_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMovie_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beMovie_GetMetaObject,
        beMovie_className,
        0x28, /* instance size */
        beMovie_GetVTable,
        beMovie_InitFields,
        0, /* extra callback item */
        g_beMovie_callbackList /* callback list */
    );
}
