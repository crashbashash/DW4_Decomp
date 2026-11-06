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
extern igMetaObject *g_beNDMWStatusTitle03_metaObject[];
void *beNDMWWindowTitle_Register(void);
igMetaObject *beNDMWWindowTitle_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusTitle03_GetMetaObject(void);
extern const char beNDMWStatusTitle03_className[];
int beNDMWStatusTitle03_GetVTable(void);
void *beNDMWStatusTitle03_Register(void);
}

void *beNDMWStatusTitle03_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusTitle03_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle03_GetMetaObject,
        beNDMWStatusTitle03_className,
        0x50, /* instance size */
        beNDMWStatusTitle03_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
