extern char igContextExt_GetPublishedMetaObject[];
extern char thunk_igScissorExt_GetMetaObject[];
extern char igContextExt_Register[];
extern char igScissorExt_className[];
extern char g_igScissorExt_metaObject[];
/* Run-once guard shared by the registrars: sets a gp-relative flag byte. */
int FUN_00149bc0();
int igMetaObject_RegisterClass();
/* Code in the gap after this function: the class's no-argument field adder (10th registration argument). */
extern int igScissorExt_InitFields_0014bdb0[4];
void igScissorExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igScissorExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igScissorExt_GetMetaObject,
        igScissorExt_className,
        0x14, /* instance size */
        0,
        &igScissorExt_InitFields_0014bdb0[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}
