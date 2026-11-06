/* True when FUN_002adc40(obj, 15) is clear, else whether FUN_002afb00(obj) is set. */
int FUN_002adc40();
int FUN_002afb00();

int FUN_002b14f8(int obj) {
    if (FUN_002adc40(obj, 15) == 0) {
        return 1;
    }
    return FUN_002afb00(obj) != 0;
}
