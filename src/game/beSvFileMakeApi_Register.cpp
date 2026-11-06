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
extern igMetaObject *g_beSvFileMakeApi_metaObject[];
void *beSaveApi_Register(void);
igMetaObject *beSaveApi_GetPublishedMetaObject(void);
igMetaObject *beSvFileMakeApi_GetMetaObject(void);
extern const char beSvFileMakeApi_className[];
int beSvFileMakeApi_GetVTable(void);
void beSvFileMakeApi_InitFields(void);
extern char g_beSvFileMakeApi_callbackList[];
void *beSvFileMakeApi_Register(void);
}

void *beSvFileMakeApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvFileMakeApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvFileMakeApi_GetMetaObject,
        beSvFileMakeApi_className,
        0x418, /* instance size */
        beSvFileMakeApi_GetVTable,
        beSvFileMakeApi_InitFields,
        0, /* extra callback item */
        g_beSvFileMakeApi_callbackList /* callback list */
    );
}
