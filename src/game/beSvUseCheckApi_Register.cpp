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
extern igMetaObject *g_beSvUseCheckApi_metaObject[];
void *beSaveApi_Register(void);
igMetaObject *beSaveApi_GetPublishedMetaObject(void);
igMetaObject *beSvUseCheckApi_GetMetaObject(void);
extern const char beSvUseCheckApi_className[];
int beSvUseCheckApi_GetVTable(void);
void *beSvUseCheckApi_Register(void);
}

void *beSvUseCheckApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvUseCheckApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvUseCheckApi_GetMetaObject,
        beSvUseCheckApi_className,
        0x4c, /* instance size */
        beSvUseCheckApi_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
