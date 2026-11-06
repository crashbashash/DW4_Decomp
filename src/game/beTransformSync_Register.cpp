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
extern igMetaObject *g_beTransformSync_metaObject[];
void *igTransform_Register(void);
igMetaObject *igTransform_GetPublishedMetaObject(void);
igMetaObject *beTransformSync_GetMetaObject(void);
extern const char beTransformSync_className[];
int beTransformSync_GetVTable(void);
void beTransformSync_InitFields(void);
extern char g_beTransformSync_callbackList[];
void *beTransformSync_Register(void);
}

void *beTransformSync_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTransformSync_metaObject,
        igTransform_Register,
        igTransform_GetPublishedMetaObject,
        beTransformSync_GetMetaObject,
        beTransformSync_className,
        0x70, /* instance size */
        beTransformSync_GetVTable,
        beTransformSync_InitFields,
        0, /* extra callback item */
        g_beTransformSync_callbackList /* callback list */
    );
}
