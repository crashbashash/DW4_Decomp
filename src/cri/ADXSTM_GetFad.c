/* PS2 discs have no frame address to report. */
int ADXSTM_GetFad(void *stm, int *fad)
{
    *fad = 0;
    return 1;
}
