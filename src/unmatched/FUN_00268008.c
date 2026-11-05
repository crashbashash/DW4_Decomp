/* 0x00268008 — FUN_00268008. Stores a byte at +88 of the record addressed by the sum of the first two
 * arguments. The second argument is spelled as the base: the unit compiler (Sony EE GCC 2.96 -O2 -G0)
 * emits the add with the operands in retail's order (a1 + a0) only that way; which argument is the
 * pointer is not known from this function alone. */
void FUN_00268008(int arg0, char *arg1, char arg2) {
    arg1[arg0 + 88] = arg2;
}
