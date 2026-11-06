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
extern igMetaObject *g_beDemoKeepMes_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beDemoKeepMes_GetMetaObject(void);
extern const char beDemoKeepMes_className[];
int beDemoKeepMes_GetVTable(void);
void beDemoKeepMes_InitFields(void);
void *beDemoKeepMes_Register(void);
}

void *beDemoKeepMes_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDemoKeepMes_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beDemoKeepMes_GetMetaObject,
        beDemoKeepMes_className,
        0x30, /* instance size */
        beDemoKeepMes_GetVTable,
        beDemoKeepMes_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
