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
extern igMetaObject *g_beFileChkObj_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beFileChkObj_GetMetaObject(void);
extern const char beFileChkObj_className[];
int beFileChkObj_GetVTable(void);
void beFileChkObj_InitFields(void);
extern char g_beFileChkObj_callbackList[];
void *beFileChkObj_Register(void);
}

void *beFileChkObj_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFileChkObj_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beFileChkObj_GetMetaObject,
        beFileChkObj_className,
        0xc, /* instance size */
        beFileChkObj_GetVTable,
        beFileChkObj_InitFields,
        0, /* extra callback item */
        g_beFileChkObj_callbackList /* callback list */
    );
}
