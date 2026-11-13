void ADXAMP_SetSfreq(int a0, int a1)
{
    *(int *)((char *)a0 + 32) = a1;
}
