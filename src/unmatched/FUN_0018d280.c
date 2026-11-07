void FUN_0018d280(void *arg0, void *arg1) {
    float temp_f1;

    temp_f1 = *(float *)((char *)(arg0) + 20);
    *(float *)((char *)(arg1) + 0) = (float) (temp_f1 * *(float *)((char *)(arg0) + 8));
    *(float *)((char *)(arg1) + 4) = (float) (temp_f1 * *(float *)((char *)(arg0) + 12));
    *(float *)((char *)(arg1) + 8) = (float) (temp_f1 * *(float *)((char *)(arg0) + 16));
}
