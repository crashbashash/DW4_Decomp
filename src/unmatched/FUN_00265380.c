extern char DAT_0049da98[];
int FUN_00262950();
int FUN_0026cbd8();

int FUN_00265380(void) {
    if (*(int *)DAT_0049da98 == 0) {
        *(int *)DAT_0049da98 = 1;
        FUN_0026cbd8();
        FUN_00262950();
        *(int *)DAT_0049da98 = 0;
    }
    return 0;
}
