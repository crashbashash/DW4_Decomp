struct V { char pad[16]; float f16; float f20; float f24; };
unsigned FUN_00145960(int arg0, struct V *arg1) {
    int k = 0x3FFF;
    float s = (float)k * arg1->f24;
    unsigned x = (unsigned)(s * arg1->f16);
    unsigned y = (unsigned)(s * arg1->f20);
    return (x << 16) | y;
}
