int strcpy();
int strlen();
int FUN_00330730();
typedef struct { char b[64]; } DW4S64;
extern DW4S64 DAT_00562dcc[];
void FUN_001eb310(int arg0, int arg1) {
    int *temp_s0;
    int temp_a0;

    temp_s0 = (int *)&DAT_00562dcc[arg0];
    *temp_s0 = FUN_00330730(strlen(arg1) + 1, 6);
    temp_a0 = *temp_s0;
    if (temp_a0 != 0) {
        strcpy(temp_a0, arg1);
    }
}
