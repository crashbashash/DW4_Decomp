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
extern igMetaObject *g_beNDMWDegiData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNDMWDegiData_GetMetaObject(void);
extern const char beNDMWDegiData_className[];
int beNDMWDegiData_GetVTable(void);
void beNDMWDegiData_InitFields(void);
extern char g_beNDMWDegiData_callbackList[];
void *beNDMWDegiData_Register(void);
}

void *beNDMWDegiData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWDegiData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWDegiData_GetMetaObject,
        beNDMWDegiData_className,
        0x4c, /* instance size */
        beNDMWDegiData_GetVTable,
        beNDMWDegiData_InitFields,
        0, /* extra callback item */
        g_beNDMWDegiData_callbackList /* callback list */
    );
}
