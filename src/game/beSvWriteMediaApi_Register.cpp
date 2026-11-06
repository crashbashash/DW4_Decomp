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
extern igMetaObject *g_beSvWriteMediaApi_metaObject[];
void *beSaveApi_Register(void);
igMetaObject *beSaveApi_GetPublishedMetaObject(void);
igMetaObject *beSvWriteMediaApi_GetMetaObject(void);
extern const char beSvWriteMediaApi_className[];
int beSvWriteMediaApi_GetVTable(void);
void beSvWriteMediaApi_InitFields(void);
extern char g_beSvWriteMediaApi_callbackList[];
void *beSvWriteMediaApi_Register(void);
}

void *beSvWriteMediaApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvWriteMediaApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvWriteMediaApi_GetMetaObject,
        beSvWriteMediaApi_className,
        0x4c, /* instance size */
        beSvWriteMediaApi_GetVTable,
        beSvWriteMediaApi_InitFields,
        0, /* extra callback item */
        g_beSvWriteMediaApi_callbackList /* callback list */
    );
}
