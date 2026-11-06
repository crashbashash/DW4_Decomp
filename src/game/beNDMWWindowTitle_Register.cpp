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
extern igMetaObject *g_beNDMWWindowTitle_metaObject[];
void *beNDMWWindow_Register(void);
igMetaObject *beNDMWWindow_GetPublishedMetaObject(void);
igMetaObject *beNDMWWindowTitle_GetMetaObject(void);
extern const char beNDMWWindowTitle_className[];
void *beNDMWWindowTitle_Register(void);
}

void *beNDMWWindowTitle_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWWindowTitle_metaObject,
        beNDMWWindow_Register,
        beNDMWWindow_GetPublishedMetaObject,
        beNDMWWindowTitle_GetMetaObject,
        beNDMWWindowTitle_className,
        0x50, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
