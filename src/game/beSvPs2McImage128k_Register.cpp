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
extern igMetaObject *g_beSvPs2McImage128k_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beSvPs2McImage128k_GetMetaObject(void);
extern const char beSvPs2McImage128k_className[];
int beSvPs2McImage128k_GetVTable(void);
void beSvPs2McImage128k_InitFields(void);
void *beSvPs2McImage128k_Register(void);
}

void *beSvPs2McImage128k_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvPs2McImage128k_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSvPs2McImage128k_GetMetaObject,
        beSvPs2McImage128k_className,
        0x10, /* instance size */
        beSvPs2McImage128k_GetVTable,
        beSvPs2McImage128k_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
