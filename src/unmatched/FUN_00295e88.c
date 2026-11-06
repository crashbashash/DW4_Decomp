extern char DAT_004be898[];
int FUN_00295fc8();
int FUN_00296050();
int FUN_00296070();
int FUN_00296150();
int FUN_00296248();
extern int DAT_00577980[4];
extern int DAT_0057b980[4];
void FUN_00295e88(void) {
    int temp_v0;

    temp_v0 = FUN_00295fc8();
    if ((temp_v0 == 1) && (*(int *)DAT_004be898 != temp_v0)) {
        FUN_00296050();
        FUN_00296070(0, 0x4000, &DAT_00577980[0]);
        FUN_00296248(8);
        FUN_00296150(&DAT_0057b980[0], 0x4000, 0);
        FUN_00296248(9);
        *(int *)DAT_004be898 = temp_v0;
    }
}
