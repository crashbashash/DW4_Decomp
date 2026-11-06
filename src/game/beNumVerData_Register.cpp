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
extern igMetaObject *g_beNumVerData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNumVerData_GetMetaObject(void);
extern const char beNumVerData_className[];
int beNumVerData_GetVTable(void);
void beNumVerData_InitFields(void);
extern char g_beNumVerData_callbackList[];
void *beNumVerData_Register(void);
}

void *beNumVerData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumVerData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNumVerData_GetMetaObject,
        beNumVerData_className,
        0x10, /* instance size */
        beNumVerData_GetVTable,
        beNumVerData_InitFields,
        0, /* extra callback item */
        g_beNumVerData_callbackList /* callback list */
    );
}
