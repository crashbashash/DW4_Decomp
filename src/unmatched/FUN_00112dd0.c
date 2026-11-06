/* Forwards its three arguments to FUN_00112800 together with a 16-byte scratch block on the stack. */
void FUN_00112800(int a, int b, int c, void *scratch);

void FUN_00112dd0(int a, int b, int c) {
    char scratch[16];

    FUN_00112800(a, b, c, scratch);
}
