/* Drops the first argument and tail-calls with the other two; C mode rather than C++ gives the
 * direct jump. */
int calloc();
void FUN_00328f70(int unused, int a, int b) {
    calloc(a, b);
}
