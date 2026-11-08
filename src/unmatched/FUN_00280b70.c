/* Drops the first argument and tail-calls with the other two; C mode rather than C++ gives the
 * direct jump. */
int realloc();
void FUN_00280b70(int unused, int a, int b) {
    realloc(a, b);
}
