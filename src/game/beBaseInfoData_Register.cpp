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
extern igMetaObject *g_beBaseInfoData_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beBaseInfoData_GetMetaObject(void);
extern const char beBaseInfoData_className[];
void beBaseInfoData_InitFields(void);
void *beBaseInfoData_Register(void);
}

void *beBaseInfoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beBaseInfoData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beBaseInfoData_GetMetaObject,
        beBaseInfoData_className,
        0x10, /* instance size */
        0,
        beBaseInfoData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
