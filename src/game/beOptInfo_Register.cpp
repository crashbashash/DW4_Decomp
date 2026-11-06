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
extern igMetaObject *g_beOptInfo_metaObject[];
void *igInfo_Register(void);
igMetaObject *igInfo_GetPublishedMetaObject(void);
igMetaObject *beOptInfo_GetMetaObject(void);
extern const char beOptInfo_className[];
int beOptInfo_GetVTable(void);
void beOptInfo_InitFields(void);
void *beOptInfo_Register(void);
}

void *beOptInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beOptInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beOptInfo_GetMetaObject,
        beOptInfo_className,
        0x24, /* instance size */
        beOptInfo_GetVTable,
        beOptInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
