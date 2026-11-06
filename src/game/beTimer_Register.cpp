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
extern igMetaObject *g_beTimer_metaObject[];
void *igInfoManager_Register(void);
igMetaObject *igInfoManager_GetPublishedMetaObject(void);
igMetaObject *beTimer_GetMetaObject(void);
extern const char beTimer_className[];
int beTimer_GetVTable(void);
void beTimer_InitFields(void);
extern char g_beTimer_callbackList[];
void *beTimer_Register(void);
}

void *beTimer_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTimer_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beTimer_GetMetaObject,
        beTimer_className,
        0x28, /* instance size */
        beTimer_GetVTable,
        beTimer_InitFields,
        0, /* extra callback item */
        g_beTimer_callbackList /* callback list */
    );
}
