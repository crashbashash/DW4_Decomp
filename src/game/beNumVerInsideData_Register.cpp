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
extern igMetaObject *g_beNumVerInsideData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNumVerInsideData_GetMetaObject(void);
extern const char beNumVerInsideData_className[];
int beNumVerInsideData_GetVTable(void);
void beNumVerInsideData_InitFields(void);
void *beNumVerInsideData_Register(void);
}

void *beNumVerInsideData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumVerInsideData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNumVerInsideData_GetMetaObject,
        beNumVerInsideData_className,
        0x10, /* instance size */
        beNumVerInsideData_GetVTable,
        beNumVerInsideData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
