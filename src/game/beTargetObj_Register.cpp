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
extern igMetaObject *g_beTargetObj_metaObject[];
void *igInfoManager_Register(void);
igMetaObject *igInfoManager_GetPublishedMetaObject(void);
igMetaObject *beTargetObj_GetMetaObject(void);
extern const char beTargetObj_className[];
int beTargetObj_GetVTable(void);
void beTargetObj_InitFields(void);
extern char g_beTargetObj_callbackList[];
void *beTargetObj_Register(void);
}

void *beTargetObj_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTargetObj_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beTargetObj_GetMetaObject,
        beTargetObj_className,
        0x1c, /* instance size */
        beTargetObj_GetVTable,
        beTargetObj_InitFields,
        0, /* extra callback item */
        g_beTargetObj_callbackList /* callback list */
    );
}
