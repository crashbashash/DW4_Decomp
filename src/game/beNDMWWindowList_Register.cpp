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
extern igMetaObject *g_beNDMWWindowList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beNDMWWindowList_GetMetaObject(void);
extern const char beNDMWWindowList_className[];
int beNDMWWindowList_GetVTable(void);
extern char g_beNDMWWindowList_callbackList[];
void *beNDMWWindowList_Register(void);
}

void *beNDMWWindowList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWWindowList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWWindowList_GetMetaObject,
        beNDMWWindowList_className,
        0x14, /* instance size */
        beNDMWWindowList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWWindowList_callbackList /* callback list */
    );
}
