extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igEventProducer_GetMetaObject[];
extern char igObject_Register[];
extern char igEventProducer_className[];
extern char g_igEventProducer_metaObject[];
int WindowInputLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igEventProducer_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igEventProducer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEventProducer_GetMetaObject,
        igEventProducer_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
