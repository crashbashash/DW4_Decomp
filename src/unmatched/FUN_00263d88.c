/* Calls FUN_00263c78 with the values of DAT_0049da30 and DAT_0049d9ac. */
/* Volatile: each read goes through a full address (lui/addiu/lw 0). */
extern volatile int DAT_0049da30;
extern int DAT_0049d9ac;
void FUN_00263c78(int a, int b);

void FUN_00263d88(void) {
    FUN_00263c78(DAT_0049da30, DAT_0049d9ac);
}
