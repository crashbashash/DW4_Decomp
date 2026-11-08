float logf(float);
void FUN_0026cfd0(int, int, int);

void FUN_0029b4c8(char *obj, int volume) {
    int h = **(int **)(obj + 8188);
    int hi;
    int lo;
    float t;

    if (h == 0) {
        return;
    }
    if (volume == 1000) {
        hi = 0;
        lo = 0;
    } else {
        t = (logf(volume) - 6.907755f) * 1731.23401f;
        hi = t * 0.01f;
        lo = (int)t - hi * 100;
    }
    FUN_0026cfd0(h, hi, lo);
    return;
}
