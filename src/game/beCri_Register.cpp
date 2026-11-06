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
extern igMetaObject *g_beCri_metaObject[];
void *igInfoManager_Register(void);
igMetaObject *igInfoManager_GetPublishedMetaObject(void);
igMetaObject *beCri_GetMetaObject(void);
extern const char beCri_className[];
int beCri_GetVTable(void);
void beCri_InitFields(void);
extern char g_beCri_callbackList[];
void *beCri_Register(void);
}

void *beCri_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCri_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beCri_GetMetaObject,
        beCri_className,
        0x48, /* instance size */
        beCri_GetVTable,
        beCri_InitFields,
        0, /* extra callback item */
        g_beCri_callbackList /* callback list */
    );
}
