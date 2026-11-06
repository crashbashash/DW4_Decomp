/* Sets six 64-bit flags (DAT_0049da38 … DAT_0049da88, 16 bytes apart) to 1. */
/* Volatile: each store materialises the full address (lui/addiu/sd 0). */
extern volatile long long DAT_0049da38;
extern volatile long long DAT_0049da48;
extern volatile long long DAT_0049da58;
extern volatile long long DAT_0049da68;
extern volatile long long DAT_0049da78;
extern volatile long long DAT_0049da88;

void FUN_00264aa0(void) {
    DAT_0049da38 = 1;
    DAT_0049da48 = 1;
    DAT_0049da58 = 1;
    DAT_0049da68 = 1;
    DAT_0049da78 = 1;
    DAT_0049da88 = 1;
}
