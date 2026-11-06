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
extern igMetaObject *g_beModelCtrlSubComBase_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beModelCtrlSubComBase_GetMetaObject(void);
extern const char beModelCtrlSubComBase_className[];
void beModelCtrlSubComBase_InitFields(void);
void *beModelCtrlSubComBase_Register(void);
}

void *beModelCtrlSubComBase_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beModelCtrlSubComBase_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlSubComBase_GetMetaObject,
        beModelCtrlSubComBase_className,
        0x14, /* instance size */
        0,
        beModelCtrlSubComBase_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
