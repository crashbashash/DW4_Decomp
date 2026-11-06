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
extern igMetaObject *g_beLOA_metaObject[];
void *igGroup_Register(void);
igMetaObject *igGroup_GetPublishedMetaObject(void);
igMetaObject *beLOA_GetMetaObject(void);
extern const char beLOA_className[];
int beLOA_GetVTable(void);
void beLOA_InitFields(void);
void FUN_0035d050(void);
extern char g_beLOA_callbackList[];
void *beLOA_Register(void);
}

void *beLOA_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLOA_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beLOA_GetMetaObject,
        beLOA_className,
        0x60, /* instance size */
        beLOA_GetVTable,
        beLOA_InitFields,
        FUN_0035d050, /* extra callback item */
        g_beLOA_callbackList /* callback list */
    );
}
