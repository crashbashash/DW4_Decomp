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
extern igMetaObject *g_beGeneraterItemDataOne_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beGeneraterItemDataOne_GetMetaObject(void);
extern const char beGeneraterItemDataOne_className[];
int beGeneraterItemDataOne_GetVTable(void);
void beGeneraterItemDataOne_InitFields(void);
void *beGeneraterItemDataOne_Register(void);
}

void *beGeneraterItemDataOne_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterItemDataOne_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beGeneraterItemDataOne_GetMetaObject,
        beGeneraterItemDataOne_className,
        0x18, /* instance size */
        beGeneraterItemDataOne_GetVTable,
        beGeneraterItemDataOne_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
