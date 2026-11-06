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
extern igMetaObject *g_beCriFxXbData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beCriFxXbData_GetMetaObject(void);
extern const char beCriFxXbData_className[];
int beCriFxXbData_GetVTable(void);
void beCriFxXbData_InitFields(void);
void *beCriFxXbData_Register(void);
}

void *beCriFxXbData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriFxXbData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCriFxXbData_GetMetaObject,
        beCriFxXbData_className,
        0x38, /* instance size */
        beCriFxXbData_GetVTable,
        beCriFxXbData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
