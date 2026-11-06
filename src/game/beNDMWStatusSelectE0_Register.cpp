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
extern igMetaObject *g_beNDMWStatusSelectE0_metaObject[];
void *beNDMWWindowSelect_Register(void);
igMetaObject *beNDMWWindowSelect_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusSelectE0_GetMetaObject(void);
extern const char beNDMWStatusSelectE0_className[];
int beNDMWStatusSelectE0_GetVTable(void);
void *beNDMWStatusSelectE0_Register(void);
}

void *beNDMWStatusSelectE0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusSelectE0_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelectE0_GetMetaObject,
        beNDMWStatusSelectE0_className,
        0x70, /* instance size */
        beNDMWStatusSelectE0_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
