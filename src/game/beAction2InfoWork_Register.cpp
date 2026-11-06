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
extern igMetaObject *g_beAction2InfoWork_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beAction2InfoWork_GetMetaObject(void);
extern const char beAction2InfoWork_className[];
int beAction2InfoWork_GetVTable(void);
void beAction2InfoWork_InitFields(void);
extern char g_beAction2InfoWork_callbackList[];
void *beAction2InfoWork_Register(void);
}

void *beAction2InfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2InfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beAction2InfoWork_GetMetaObject,
        beAction2InfoWork_className,
        0x60, /* instance size */
        beAction2InfoWork_GetVTable,
        beAction2InfoWork_InitFields,
        0, /* extra callback item */
        g_beAction2InfoWork_callbackList /* callback list */
    );
}
