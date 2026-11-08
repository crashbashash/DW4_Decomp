typedef struct { int pad; int w; int h; int mbw; int mbh; } V;
int FUN_00109c68(V *v, int w, int h) {
    v->w = w;
    v->mbw = w >> 4;
    v->h = h;
    v->mbh = h >> 4;
    return 1;
}
