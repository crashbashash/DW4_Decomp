typedef struct E { long long a; long long b; } E;
typedef struct Img { char pad[8]; int w; int h; char pad2[36]; E *data; } Img;
void FUN_0015a6a0(Img *arg0, E *out) {
    int w;
    int h;
    E *r0;
    E *r1;
    int x;
    int y;
    w = arg0->w >> 2;
    h = arg0->h >> 2;
    r0 = arg0->data;
    r1 = r0 + w;
    for (y = 0; y < h; y += 2) {
        for (x = 0; x < w; x += 2) {
            out[0] = r0[0];
            out[1] = r0[1];
            { long long t = r1[0].b; long long u = r1[0].a; out[2].a = u; out[2].b = t;}
            { long long t = r1[1].b; long long u = r1[1].a; out[3].a = u; out[3].b = t;}
            r0 += 2;
            r1 += 2;
            out += 4;
        }
        r0 += w;
        r1 += w;
    }
}
