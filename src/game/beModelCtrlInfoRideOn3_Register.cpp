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
extern igMetaObject *g_beModelCtrlInfoRideOn3_metaObject[];
void *beModelCtrlInfoRideOn_Register(void);
igMetaObject *beModelCtrlInfoRideOn_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlInfoRideOn3_GetMetaObject(void);
extern const char beModelCtrlInfoRideOn3_className[];
int beModelCtrlInfoRideOn3_GetVTable(void);
void beModelCtrlInfoRideOn3_InitFields(void);
void *beModelCtrlInfoRideOn3_Register(void);
}

void *beModelCtrlInfoRideOn3_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoRideOn3_metaObject,
        beModelCtrlInfoRideOn_Register,
        beModelCtrlInfoRideOn_GetPublishedMetaObject,
        beModelCtrlInfoRideOn3_GetMetaObject,
        beModelCtrlInfoRideOn3_className,
        0x70, /* instance size */
        beModelCtrlInfoRideOn3_GetVTable,
        beModelCtrlInfoRideOn3_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
