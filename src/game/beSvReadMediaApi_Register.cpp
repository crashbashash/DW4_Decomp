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
extern igMetaObject *g_beSvReadMediaApi_metaObject[];
void *beSaveApi_Register(void);
igMetaObject *beSaveApi_GetPublishedMetaObject(void);
igMetaObject *beSvReadMediaApi_GetMetaObject(void);
extern const char beSvReadMediaApi_className[];
int beSvReadMediaApi_GetVTable(void);
void beSvReadMediaApi_InitFields(void);
extern char g_beSvReadMediaApi_callbackList[];
void *beSvReadMediaApi_Register(void);
}

void *beSvReadMediaApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvReadMediaApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvReadMediaApi_GetMetaObject,
        beSvReadMediaApi_className,
        0x58, /* instance size */
        beSvReadMediaApi_GetVTable,
        beSvReadMediaApi_InitFields,
        0, /* extra callback item */
        g_beSvReadMediaApi_callbackList /* callback list */
    );
}
