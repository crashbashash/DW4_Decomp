int ADXCRS_Lock();
int ADXCRS_Unlock();
int memset();

void ADXAMP_Destroy(int arg0) {
    if (arg0 != 0) {
        ADXCRS_Lock();
        memset(arg0, 0, 0x30);
        ADXCRS_Unlock();
    }
}
