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
extern igMetaObject *g_beModelCtrlInfoHitBody_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beModelCtrlInfoHitBody_GetMetaObject(void);
extern const char beModelCtrlInfoHitBody_className[];
int beModelCtrlInfoHitBody_GetVTable(void);
void beModelCtrlInfoHitBody_InitFields(void);
extern char g_beModelCtrlInfoHitBody_callbackList[];
void *beModelCtrlInfoHitBody_Register(void);
}

void *beModelCtrlInfoHitBody_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoHitBody_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlInfoHitBody_GetMetaObject,
        beModelCtrlInfoHitBody_className,
        0x30, /* instance size */
        beModelCtrlInfoHitBody_GetVTable,
        beModelCtrlInfoHitBody_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoHitBody_callbackList /* callback list */
    );
}
