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
extern igMetaObject *g_beNDMWShinkaObject_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNDMWShinkaObject_GetMetaObject(void);
extern const char beNDMWShinkaObject_className[];
int beNDMWShinkaObject_GetVTable(void);
void beNDMWShinkaObject_InitFields(void);
void *beNDMWShinkaObject_Register(void);
}

void *beNDMWShinkaObject_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShinkaObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWShinkaObject_GetMetaObject,
        beNDMWShinkaObject_className,
        0x54, /* instance size */
        beNDMWShinkaObject_GetVTable,
        beNDMWShinkaObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
