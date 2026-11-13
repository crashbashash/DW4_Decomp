char ADXSTM_GetStatRead(void *arg0) {
    return *(int *)((char *)(arg0) + 2);
}
