extern char igNamedObject_GetPublishedMetaObject[];
extern char thunk_igSemaphore_GetMetaObject[];
extern char igNamedObject_Register[];
extern char igSemaphore_className[];
extern char g_igSemaphore_metaObject[];
/* Run-once guard shared by the registrars: sets a gp-relative flag byte. */
int FUN_002b5d50();
int igMetaObject_RegisterClass();
/* Code in the gap after this function: the class's no-argument field adder (10th registration argument). */
extern int igSemaphore_InitFields_002ba7c0[4];
void igSemaphore_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igSemaphore_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igSemaphore_GetMetaObject,
        igSemaphore_className,
        0xC, /* instance size */
        0,
        &igSemaphore_InitFields_002ba7c0[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}
