int FUN_00269ff0();
int FUN_0026a0a0();
int ADXSTM_SetEos();

void FUN_0029b258(int arg0, int arg1) {
    FUN_0026a0a0();
    FUN_00269ff0(arg0, arg1, 0, 0, 0xFFFFF);
    ADXSTM_SetEos(arg0, 0xFFFFF);
}
