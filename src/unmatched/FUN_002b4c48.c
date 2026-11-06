/* Calls FUN_002b50c8(obj, 32), then tail-calls FUN_002b4c98(obj, arg1, 32, arg2). */
int FUN_002b4c98();
int FUN_002b50c8();

void FUN_002b4c48(int obj, int arg1, int arg2) {
    FUN_002b50c8(obj, 32);
    FUN_002b4c98(obj, arg1, 32, arg2);
}
