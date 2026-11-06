struct igMetaObject;
extern "C" {
void BecLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beLayerGroup_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beLayerGroup_GetMetaObject(void);
extern const char beLayerGroup_className[];
int beLayerGroup_GetVTable(void);
void *beLayerGroup_Register(void);
}

void *beLayerGroup_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLayerGroup_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beLayerGroup_GetMetaObject,
        beLayerGroup_className,
        0xc, /* instance size */
        beLayerGroup_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
