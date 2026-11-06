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
extern igMetaObject *g_beNDMWWindowCtrl_metaObject[];
void *beNDMWWindow_Register(void);
igMetaObject *beNDMWWindow_GetPublishedMetaObject(void);
igMetaObject *beNDMWWindowCtrl_GetMetaObject(void);
extern const char beNDMWWindowCtrl_className[];
void beNDMWWindowCtrl_InitFields(void);
void *beNDMWWindowCtrl_Register(void);
}

void *beNDMWWindowCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWWindowCtrl_metaObject,
        beNDMWWindow_Register,
        beNDMWWindow_GetPublishedMetaObject,
        beNDMWWindowCtrl_GetMetaObject,
        beNDMWWindowCtrl_className,
        0x54, /* instance size */
        0,
        beNDMWWindowCtrl_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
