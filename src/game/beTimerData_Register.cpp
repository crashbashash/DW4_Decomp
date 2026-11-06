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
extern igMetaObject *g_beTimerData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beTimerData_GetMetaObject(void);
extern const char beTimerData_className[];
int beTimerData_GetVTable(void);
void beTimerData_InitFields(void);
void *beTimerData_Register(void);
}

void *beTimerData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTimerData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beTimerData_GetMetaObject,
        beTimerData_className,
        0x20, /* instance size */
        beTimerData_GetVTable,
        beTimerData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
