extern char DAT_004ba48c[];
int FUN_001122d8();
int FUN_002734d0();
int FUN_002737a8();
extern int DAT_004ba484[4];
extern int DAT_004ba718[4];
void FUN_0027df08(void) {
    int temp_v0;
    int temp_v1;

    temp_v0 = DAT_004ba484[0] - 1;
    DAT_004ba484[0] = temp_v0;
    if (temp_v0 == 0) {
        FUN_002734d0(DAT_004ba718[0]);
        DAT_004ba718[0] = 0;
        temp_v1 = *(int *)DAT_004ba48c;
        if (temp_v1 != 0) {
            FUN_001122d8(temp_v1);
            *(int *)DAT_004ba48c = 0;
        }
        FUN_002737a8();
    }
}
