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
extern igMetaObject *g_bePoint01_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *bePoint01_GetMetaObject(void);
extern const char bePoint01_className[];
int bePoint01_GetVTable(void);
void bePoint01_InitFields(void);
void *bePoint01_Register(void);
}

void *bePoint01_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_bePoint01_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        bePoint01_GetMetaObject,
        bePoint01_className,
        0x24, /* instance size */
        bePoint01_GetVTable,
        bePoint01_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
