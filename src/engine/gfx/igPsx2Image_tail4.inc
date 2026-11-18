int igPsx2Image_GetMeta(void) {
    return (int)g_igPsx2Image_metaObject;
}

void FUN_00180ca0(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 16) = (int) (arg1 & 0xFFFF);
}

