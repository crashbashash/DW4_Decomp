/* CRI ADXCRS: the critical section the ADX libraries take around shared state. */

void FUN_0027e1c0(void);
void FUN_0027e1d8(void);

extern int adxcrs_lock_cnt;

void ADXCRS_Init(void)
{
    adxcrs_lock_cnt = 0;
}

void FUN_0025f2d0(void)
{
    FUN_0027e1c0();
}

void FUN_0025f2e8(void)
{
    FUN_0027e1d8();
}
