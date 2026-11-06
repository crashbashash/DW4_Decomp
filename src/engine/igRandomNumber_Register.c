extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igRandomNumber_GetMetaObject[];
extern char igObject_Register[];
extern char igRandomNumber_className[];
extern char g_igRandomNumber_metaObject[];
/* Run-once guard shared by the registrars: sets a gp-relative flag byte. */
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
/* Code in the gap after this function: the class's no-argument field adder (10th registration argument). */
extern int igRandomNumber_InitFields_001e4370[4];
void igRandomNumber_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igRandomNumber_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRandomNumber_GetMetaObject,
        igRandomNumber_className,
        8, /* instance size */
        0,
        &igRandomNumber_InitFields_001e4370[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}
