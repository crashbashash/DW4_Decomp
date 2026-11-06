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
extern igMetaObject *g_beNDMWListCtrl_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWListCtrl_GetMetaObject(void);
extern const char beNDMWListCtrl_className[];
void beNDMWListCtrl_InitFields(void);
void *beNDMWListCtrl_Register(void);
}

void *beNDMWListCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWListCtrl_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWListCtrl_GetMetaObject,
        beNDMWListCtrl_className,
        0x60, /* instance size */
        0,
        beNDMWListCtrl_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
