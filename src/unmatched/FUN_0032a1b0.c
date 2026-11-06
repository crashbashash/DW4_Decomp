/* Second argument forwarded to the callee (a1 untouched), byte store at +167. */
int strncpy();

void FUN_0032a1b0(char *arg0, int arg1) {
    strncpy(arg0 + 0x58, arg1, 0x4F);
    arg0[167] = 0;
}
