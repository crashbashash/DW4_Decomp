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
extern igMetaObject *g_beSvPlatDataGC_metaObject[];
void *beSvPlatBaseData_Register(void);
igMetaObject *beSvPlatBaseData_GetPublishedMetaObject(void);
igMetaObject *beSvPlatDataGC_GetMetaObject(void);
extern const char beSvPlatDataGC_className[];
int beSvPlatDataGC_GetVTable(void);
void beSvPlatDataGC_InitFields(void);
void *beSvPlatDataGC_Register(void);
}

void *beSvPlatDataGC_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvPlatDataGC_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataGC_GetMetaObject,
        beSvPlatDataGC_className,
        0x8c, /* instance size */
        beSvPlatDataGC_GetVTable,
        beSvPlatDataGC_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
