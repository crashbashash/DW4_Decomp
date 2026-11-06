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
extern igMetaObject *g_beNumberCtrlInfoWork_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNumberCtrlInfoWork_GetMetaObject(void);
extern const char beNumberCtrlInfoWork_className[];
int beNumberCtrlInfoWork_GetVTable(void);
void beNumberCtrlInfoWork_InitFields(void);
void *beNumberCtrlInfoWork_Register(void);
}

void *beNumberCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumberCtrlInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNumberCtrlInfoWork_GetMetaObject,
        beNumberCtrlInfoWork_className,
        0x14, /* instance size */
        beNumberCtrlInfoWork_GetVTable,
        beNumberCtrlInfoWork_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
