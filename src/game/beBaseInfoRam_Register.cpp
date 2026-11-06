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
extern igMetaObject *g_beBaseInfoRam_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beBaseInfoRam_GetMetaObject(void);
extern const char beBaseInfoRam_className[];
int beBaseInfoRam_GetVTable(void);
void beBaseInfoRam_InitFields(void);
extern char g_beBaseInfoRam_callbackList[];
void *beBaseInfoRam_Register(void);
}

void *beBaseInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBaseInfoRam_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beBaseInfoRam_GetMetaObject,
        beBaseInfoRam_className,
        0x2c, /* instance size */
        beBaseInfoRam_GetVTable,
        beBaseInfoRam_InitFields,
        0, /* extra callback item */
        g_beBaseInfoRam_callbackList /* callback list */
    );
}
