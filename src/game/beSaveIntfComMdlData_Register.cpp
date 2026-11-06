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
extern igMetaObject *g_beSaveIntfComMdlData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beSaveIntfComMdlData_GetMetaObject(void);
extern const char beSaveIntfComMdlData_className[];
int beSaveIntfComMdlData_GetVTable(void);
void beSaveIntfComMdlData_InitFields(void);
void *beSaveIntfComMdlData_Register(void);
}

void *beSaveIntfComMdlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSaveIntfComMdlData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveIntfComMdlData_GetMetaObject,
        beSaveIntfComMdlData_className,
        0x14, /* instance size */
        beSaveIntfComMdlData_GetVTable,
        beSaveIntfComMdlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
