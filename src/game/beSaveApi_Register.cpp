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
extern igMetaObject *g_beSaveApi_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beSaveApi_GetMetaObject(void);
extern const char beSaveApi_className[];
void beSaveApi_InitFields(void);
extern char g_beSaveApi_callbackList[];
void *beSaveApi_Register(void);
}

void *beSaveApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beSaveApi_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveApi_GetMetaObject,
        beSaveApi_className,
        0x40, /* instance size */
        0,
        beSaveApi_InitFields,
        0, /* extra callback item */
        g_beSaveApi_callbackList /* callback list */
    );
}
