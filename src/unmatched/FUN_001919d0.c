float FUN_00122d90(float);
float FUN_001234c0(float);
void FUN_00191910(int, float, float, float, float, float, float);

void FUN_001919d0(int arg0, float a, float b, float c, float d, float e) {
    float t23;
    float t14;

    if (a < 0.0f) {
        a = 2.0f * FUN_00122d90((c * (d * FUN_001234c0(0.5f * b))) / d);
    } else {
        b = 2.0f * FUN_00122d90(((d * FUN_001234c0(0.5f * a)) / c) / d);
    }
    t23 = d * -FUN_001234c0(0.5f * a);
    t14 = d * -FUN_001234c0(0.5f * b);
    FUN_00191910(arg0, t23, -t23, t14, -t14, d, e);
}
