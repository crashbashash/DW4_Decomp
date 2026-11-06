/* Reports error 0xFF000601 for the handle through FUN_002a0bb8. */
int FUN_002a0bb8();

void FUN_002b1388(int handle) {
    FUN_002a0bb8(handle, 0xFF000601);
}
