/* Calls FUN_00269da8(0, 0, 0, a0) for a second argument below 256, else FUN_00269e80(0, 0, 0, a0). */
void FUN_00269da8(int a0, int a1, int a2, int a3);
void FUN_00269e80(int a0, int a1, int a2, int a3);

/* matching construct: manual — declared int with no return statement; retail makes plain calls (no tail call), which ee-gcc emits only when an int function falls off its end */
int ADXSTM_Create(int value, int size) {
    if (size < 256) {
        FUN_00269da8(0, 0, 0, value);
    } else {
        FUN_00269e80(0, 0, 0, value);
    }
}
