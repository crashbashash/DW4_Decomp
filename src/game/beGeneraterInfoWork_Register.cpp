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
extern igMetaObject *g_beGeneraterInfoWork_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beGeneraterInfoWork_GetMetaObject(void);
extern const char beGeneraterInfoWork_className[];
int beGeneraterInfoWork_GetVTable(void);
void beGeneraterInfoWork_InitFields(void);
extern char g_beGeneraterInfoWork_callbackList[];
void *beGeneraterInfoWork_Register(void);
}

void *beGeneraterInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beGeneraterInfoWork_GetMetaObject,
        beGeneraterInfoWork_className,
        0x28, /* instance size */
        beGeneraterInfoWork_GetVTable,
        beGeneraterInfoWork_InitFields,
        0, /* extra callback item */
        g_beGeneraterInfoWork_callbackList /* callback list */
    );
}
