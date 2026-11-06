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
extern igMetaObject *g_beSvFileFindApi_metaObject[];
void *beSaveApi_Register(void);
igMetaObject *beSaveApi_GetPublishedMetaObject(void);
igMetaObject *beSvFileFindApi_GetMetaObject(void);
extern const char beSvFileFindApi_className[];
int beSvFileFindApi_GetVTable(void);
void *beSvFileFindApi_Register(void);
}

void *beSvFileFindApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvFileFindApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvFileFindApi_GetMetaObject,
        beSvFileFindApi_className,
        0x54, /* instance size */
        beSvFileFindApi_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
