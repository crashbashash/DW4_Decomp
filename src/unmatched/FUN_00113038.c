/* Forwards its three arguments to _sceSifLoadModule together with a 16-byte scratch block on the stack
 * and a zero fifth argument. */
void _sceSifLoadModule(int a, int b, int c, void *scratch, int e);

void FUN_00113038(int a, int b, int c) {
    char scratch[16];

    _sceSifLoadModule(a, b, c, scratch, 0);
}
