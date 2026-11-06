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
extern igMetaObject *g_beModelCtrlNode2_metaObject[];
void *igTransform_Register(void);
igMetaObject *igTransform_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlNode2_GetMetaObject(void);
extern const char beModelCtrlNode2_className[];
int beModelCtrlNode2_GetVTable(void);
void beModelCtrlNode2_InitFields(void);
void FUN_00350000(void);
extern char g_beModelCtrlNode2_callbackList[];
void *beModelCtrlNode2_Register(void);
}

void *beModelCtrlNode2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlNode2_metaObject,
        igTransform_Register,
        igTransform_GetPublishedMetaObject,
        beModelCtrlNode2_GetMetaObject,
        beModelCtrlNode2_className,
        0x90, /* instance size */
        beModelCtrlNode2_GetVTable,
        beModelCtrlNode2_InitFields,
        FUN_00350000, /* extra callback item */
        g_beModelCtrlNode2_callbackList /* callback list */
    );
}
