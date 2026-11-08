int FUN_0029db60(int);
void FUN_002a0bb8(int, int);
int FUN_002b03e8(int, int);
void FUN_0029dba8(int, int, int);

void FUN_0029dab8(int h, int stream) {
    int mode;

    if (FUN_0029db60(stream) != 0) {
        FUN_002a0bb8(h, 0xff000408);
        return;
    }
    if (FUN_002b03e8(h, 1) != 0) {
        mode = 0;
    } else if (FUN_002b03e8(h, 2) != 0) {
        mode = 1;
    } else if (FUN_002b03e8(h, 3) != 0) {
        mode = 2;
    } else {
        mode = 0;
    }
    FUN_0029dba8(h, stream, mode);
}
