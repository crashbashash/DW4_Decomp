/* Forwards its three arguments to _sceSifLoadModuleBuffer together with a 16-byte scratch block on the stack. */
void _sceSifLoadModuleBuffer(int a, int b, int c, void *scratch);

void FUN_00112dd0(int a, int b, int c) {
    char scratch[16];

    _sceSifLoadModuleBuffer(a, b, c, scratch);
}
