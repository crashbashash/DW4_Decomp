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
extern igMetaObject *g_beSvGetFreeSizeApi_metaObject[];
void *beSaveApi_Register(void);
igMetaObject *beSaveApi_GetPublishedMetaObject(void);
igMetaObject *beSvGetFreeSizeApi_GetMetaObject(void);
extern const char beSvGetFreeSizeApi_className[];
int beSvGetFreeSizeApi_GetVTable(void);
void beSvGetFreeSizeApi_InitFields(void);
void *beSvGetFreeSizeApi_Register(void);
}

void *beSvGetFreeSizeApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvGetFreeSizeApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvGetFreeSizeApi_GetMetaObject,
        beSvGetFreeSizeApi_className,
        0x58, /* instance size */
        beSvGetFreeSizeApi_GetVTable,
        beSvGetFreeSizeApi_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
