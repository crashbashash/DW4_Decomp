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
extern igMetaObject *g_beDataBase_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beDataBase_GetMetaObject(void);
extern const char beDataBase_className[];
int beDataBase_GetVTable(void);
void beDataBase_InitFields(void);
extern char g_beDataBase_callbackList[];
void *beDataBase_Register(void);
}

void *beDataBase_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataBase_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beDataBase_GetMetaObject,
        beDataBase_className,
        0x38, /* instance size */
        beDataBase_GetVTable,
        beDataBase_InitFields,
        0, /* extra callback item */
        g_beDataBase_callbackList /* callback list */
    );
}
