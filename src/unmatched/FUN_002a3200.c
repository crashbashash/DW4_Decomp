int FUN_002a0dd8(void *);
void FUN_002a0bb8(void *, int);
int FUN_00291250(int, int, int);

void FUN_002a3200(char *obj, int mode, int value) {
    int h = 0;

    if (obj != 0) {
        if (FUN_002a0dd8(obj) != 0) {
            FUN_002a0bb8(0, 0xff000181);
            return;
        }
        h = **(int **)(obj + 8120);
    }
    if (FUN_00291250(h, mode, mode != 5 ? value : 0) != 0) {
        FUN_002a0bb8(obj, 0xff000f12);
        return;
    }
}
