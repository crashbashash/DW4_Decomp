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
extern igMetaObject *g_beNDMWStatusTitle04_metaObject[];
void *beNDMWWindowTitle_Register(void);
igMetaObject *beNDMWWindowTitle_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusTitle04_GetMetaObject(void);
extern const char beNDMWStatusTitle04_className[];
int beNDMWStatusTitle04_GetVTable(void);
void *beNDMWStatusTitle04_Register(void);
}

void *beNDMWStatusTitle04_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusTitle04_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle04_GetMetaObject,
        beNDMWStatusTitle04_className,
        0x50, /* instance size */
        beNDMWStatusTitle04_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
