/* Calls FUN_00263c78 with the values of DAT_0049da2c and DAT_0049d9a8. */
/* Volatile: each read goes through a full address (lui/addiu/lw 0). */
extern volatile int DAT_0049da2c;
extern int DAT_0049d9a8;
void FUN_00263c78(int a, int b);

void FUN_00263d60(void) {
    FUN_00263c78(DAT_0049da2c, DAT_0049d9a8);
}
