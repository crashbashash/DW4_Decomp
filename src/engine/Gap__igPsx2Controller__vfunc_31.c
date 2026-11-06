void Gap__igPsx2Controller__vfunc_31(void *arg0, int arg1, float *arg2, float *arg3) {
    int temp_a1;
    int idx;
    int temp_v1;
    temp_a1 = arg1 & 0xFFFF;
    if (temp_a1 < (int) *(unsigned short *)((char *)(arg0) + 28)) {
        idx = temp_a1 * 4;
        temp_v1 = idx + (int)arg0;
        *arg2 = *(float *)(temp_v1 + 36);
        *arg3 = *(float *)(temp_v1 + 44);
    }
}
