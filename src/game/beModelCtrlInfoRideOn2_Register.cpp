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
extern igMetaObject *g_beModelCtrlInfoRideOn2_metaObject[];
void *beModelCtrlInfoRideOn_Register(void);
igMetaObject *beModelCtrlInfoRideOn_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlInfoRideOn2_GetMetaObject(void);
extern const char beModelCtrlInfoRideOn2_className[];
int beModelCtrlInfoRideOn2_GetVTable(void);
void beModelCtrlInfoRideOn2_InitFields(void);
void *beModelCtrlInfoRideOn2_Register(void);
}

void *beModelCtrlInfoRideOn2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoRideOn2_metaObject,
        beModelCtrlInfoRideOn_Register,
        beModelCtrlInfoRideOn_GetPublishedMetaObject,
        beModelCtrlInfoRideOn2_GetMetaObject,
        beModelCtrlInfoRideOn2_className,
        0x60, /* instance size */
        beModelCtrlInfoRideOn2_GetVTable,
        beModelCtrlInfoRideOn2_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
