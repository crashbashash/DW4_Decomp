#define ADXSTM_MAX_OBJ 40

extern int adxstmf_rtim_ofst;
extern int adxstmf_rtim_num;

/* Reserves the last `num` handles of the table for real-time streams. */
void ADXSTMF_SetRtimNum(int num)
{
    adxstmf_rtim_ofst = ADXSTM_MAX_OBJ - num;
    adxstmf_rtim_num = num;
}
