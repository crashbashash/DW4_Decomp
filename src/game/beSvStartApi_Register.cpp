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
extern igMetaObject *g_beSvStartApi_metaObject[];
void *beSaveApi_Register(void);
igMetaObject *beSaveApi_GetPublishedMetaObject(void);
igMetaObject *beSvStartApi_GetMetaObject(void);
extern const char beSvStartApi_className[];
int beSvStartApi_GetVTable(void);
void beSvStartApi_InitFields(void);
void *beSvStartApi_Register(void);
}

void *beSvStartApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvStartApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvStartApi_GetMetaObject,
        beSvStartApi_className,
        0x40, /* instance size */
        beSvStartApi_GetVTable,
        beSvStartApi_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
