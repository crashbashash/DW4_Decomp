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
extern igMetaObject *g_beModelCtrlACTION_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlACTION_GetMetaObject(void);
extern const char beModelCtrlACTION_className[];
int beModelCtrlACTION_GetVTable(void);
void *beModelCtrlACTION_Register(void);
}

void *beModelCtrlACTION_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlACTION_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlACTION_GetMetaObject,
        beModelCtrlACTION_className,
        0xc, /* instance size */
        beModelCtrlACTION_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
