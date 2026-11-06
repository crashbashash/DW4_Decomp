/* Calls FUN_00272228 with a byte value and then stores that value, sign-extended, in DAT_004a92c8. */
/* The store materialises the full address (lui/addiu/sw 0): the word is volatile. */
extern volatile int DAT_004a92c8;
void FUN_00272228(int value);

void FUN_00272290(int value) {
    FUN_00272228(value);
    DAT_004a92c8 = (signed char)value;
}
