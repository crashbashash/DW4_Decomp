int ADXSJD_GetNumChan();
int FUN_0026c468();

void adxt_set_outpan(void *arg0) {
    if (ADXSJD_GetNumChan(*(int *)((char *)(arg0) + 4)) == 1) {
        FUN_0026c468(arg0, 0, *(short *)((char *)(arg0) + 66));
        return;
    }
    FUN_0026c468(arg0, 0, *(short *)((char *)(arg0) + 66));
    FUN_0026c468(arg0, 1, *(short *)((char *)(arg0) + 68));
}
