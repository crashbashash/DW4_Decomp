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
extern igMetaObject *g_beCameraDemoData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beCameraDemoData_GetMetaObject(void);
extern const char beCameraDemoData_className[];
int beCameraDemoData_GetVTable(void);
void beCameraDemoData_InitFields(void);
extern char g_beCameraDemoData_callbackList[];
void *beCameraDemoData_Register(void);
}

void *beCameraDemoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCameraDemoData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCameraDemoData_GetMetaObject,
        beCameraDemoData_className,
        0x20, /* instance size */
        beCameraDemoData_GetVTable,
        beCameraDemoData_InitFields,
        0, /* extra callback item */
        g_beCameraDemoData_callbackList /* callback list */
    );
}
