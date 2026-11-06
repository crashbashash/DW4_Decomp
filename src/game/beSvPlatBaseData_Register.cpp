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
extern igMetaObject *g_beSvPlatBaseData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beSvPlatBaseData_GetMetaObject(void);
extern const char beSvPlatBaseData_className[];
int beSvPlatBaseData_GetVTable(void);
void beSvPlatBaseData_InitFields(void);
extern char g_beSvPlatBaseData_callbackList[];
void *beSvPlatBaseData_Register(void);
}

void *beSvPlatBaseData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvPlatBaseData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSvPlatBaseData_GetMetaObject,
        beSvPlatBaseData_className,
        0x18, /* instance size */
        beSvPlatBaseData_GetVTable,
        beSvPlatBaseData_InitFields,
        0, /* extra callback item */
        g_beSvPlatBaseData_callbackList /* callback list */
    );
}
