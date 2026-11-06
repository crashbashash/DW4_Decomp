struct igMetaObject;
extern "C" {
void NdmwLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beNDMWWindow_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNDMWWindow_GetMetaObject(void);
extern const char beNDMWWindow_className[];
void beNDMWWindow_InitFields(void);
extern char g_beNDMWWindow_callbackList[];
void *beNDMWWindow_Register(void);
}

void *beNDMWWindow_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWWindow_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWWindow_GetMetaObject,
        beNDMWWindow_className,
        0x50, /* instance size */
        0,
        beNDMWWindow_InitFields,
        0, /* extra callback item */
        g_beNDMWWindow_callbackList /* callback list */
    );
}
