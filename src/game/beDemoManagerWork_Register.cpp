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
extern igMetaObject *g_beDemoManagerWork_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beDemoManagerWork_GetMetaObject(void);
extern const char beDemoManagerWork_className[];
int beDemoManagerWork_GetVTable(void);
void beDemoManagerWork_InitFields(void);
extern char g_beDemoManagerWork_callbackList[];
void *beDemoManagerWork_Register(void);
}

void *beDemoManagerWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDemoManagerWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beDemoManagerWork_GetMetaObject,
        beDemoManagerWork_className,
        0x10, /* instance size */
        beDemoManagerWork_GetVTable,
        beDemoManagerWork_InitFields,
        0, /* extra callback item */
        g_beDemoManagerWork_callbackList /* callback list */
    );
}
