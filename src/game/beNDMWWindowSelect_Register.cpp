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
extern igMetaObject *g_beNDMWWindowSelect_metaObject[];
void *beNDMWWindow_Register(void);
igMetaObject *beNDMWWindow_GetPublishedMetaObject(void);
igMetaObject *beNDMWWindowSelect_GetMetaObject(void);
extern const char beNDMWWindowSelect_className[];
void beNDMWWindowSelect_InitFields(void);
extern char g_beNDMWWindowSelect_callbackList[];
void *beNDMWWindowSelect_Register(void);
}

void *beNDMWWindowSelect_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWWindowSelect_metaObject,
        beNDMWWindow_Register,
        beNDMWWindow_GetPublishedMetaObject,
        beNDMWWindowSelect_GetMetaObject,
        beNDMWWindowSelect_className,
        0x70, /* instance size */
        0,
        beNDMWWindowSelect_InitFields,
        0, /* extra callback item */
        g_beNDMWWindowSelect_callbackList /* callback list */
    );
}
