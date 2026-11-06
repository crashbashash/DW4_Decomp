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
extern igMetaObject *g_beLoadIntf2ComMdlData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beLoadIntf2ComMdlData_GetMetaObject(void);
extern const char beLoadIntf2ComMdlData_className[];
int beLoadIntf2ComMdlData_GetVTable(void);
void beLoadIntf2ComMdlData_InitFields(void);
void *beLoadIntf2ComMdlData_Register(void);
}

void *beLoadIntf2ComMdlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLoadIntf2ComMdlData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beLoadIntf2ComMdlData_GetMetaObject,
        beLoadIntf2ComMdlData_className,
        0x14, /* instance size */
        beLoadIntf2ComMdlData_GetVTable,
        beLoadIntf2ComMdlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
