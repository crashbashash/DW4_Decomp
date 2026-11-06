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
extern igMetaObject *g_beFontGeomAttrPair_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beFontGeomAttrPair_GetMetaObject(void);
extern const char beFontGeomAttrPair_className[];
int beFontGeomAttrPair_GetVTable(void);
void beFontGeomAttrPair_InitFields(void);
extern char g_beFontGeomAttrPair_callbackList[];
void *beFontGeomAttrPair_Register(void);
}

void *beFontGeomAttrPair_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFontGeomAttrPair_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beFontGeomAttrPair_GetMetaObject,
        beFontGeomAttrPair_className,
        0x14, /* instance size */
        beFontGeomAttrPair_GetVTable,
        beFontGeomAttrPair_InitFields,
        0, /* extra callback item */
        g_beFontGeomAttrPair_callbackList /* callback list */
    );
}
