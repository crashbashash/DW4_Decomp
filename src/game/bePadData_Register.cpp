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
extern igMetaObject *g_bePadData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *bePadData_GetMetaObject(void);
extern const char bePadData_className[];
int bePadData_GetVTable(void);
void bePadData_InitFields(void);
void *bePadData_Register(void);
}

void *bePadData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_bePadData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        bePadData_GetMetaObject,
        bePadData_className,
        0x68, /* instance size */
        bePadData_GetVTable,
        bePadData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
