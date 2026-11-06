/* Sets the flag DAT_0049d9dc and calls FUN_00264350. */
/* Volatile: the store materialises the full address (lui/addiu/sw 0). */
extern volatile int DAT_0049d9dc;
void FUN_00264350(void);

void FUN_00265308(void) {
    DAT_0049d9dc = 1;
    FUN_00264350();
}
