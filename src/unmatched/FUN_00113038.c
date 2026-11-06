/* Forwards its three arguments to FUN_00112e10 together with a 16-byte scratch block on the stack
 * and a zero fifth argument. */
void FUN_00112e10(int a, int b, int c, void *scratch, int e);

void FUN_00113038(int a, int b, int c) {
    char scratch[16];

    FUN_00112e10(a, b, c, scratch, 0);
}
