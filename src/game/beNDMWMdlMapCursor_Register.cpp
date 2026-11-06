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
extern igMetaObject *g_beNDMWMdlMapCursor_metaObject[];
void *beModelCtrl_Register(void);
igMetaObject *beModelCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWMdlMapCursor_GetMetaObject(void);
extern const char beNDMWMdlMapCursor_className[];
int beNDMWMdlMapCursor_GetVTable(void);
void *beNDMWMdlMapCursor_Register(void);
}

void *beNDMWMdlMapCursor_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlMapCursor_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlMapCursor_GetMetaObject,
        beNDMWMdlMapCursor_className,
        0x2c, /* instance size */
        beNDMWMdlMapCursor_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
