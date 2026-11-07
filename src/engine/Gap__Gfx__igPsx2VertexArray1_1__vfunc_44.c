typedef struct VertexArrayStore { char pad[8]; unsigned int *data; } VertexArrayStore;
typedef struct VertexArrayView { char pad[8]; VertexArrayStore *b; } VertexArrayView;
void Gap__Gfx__igPsx2VertexArray1_1__vfunc_44(VertexArrayView *arg0, int arg1, float *arg2) {
    unsigned int c = arg0->b->data[arg1];
    unsigned int t;
    float f, s;
    t = c >> 24;
    s = (t > 128) ? 0.007843138f : 0.0078125f;
    f = (float)(t & 0xFF);
    arg2[3] = f * s;
    t = (c >> 16) & 0xFF;
    f = (float)t;
    arg2[2] = 0.003921568f * f;
    t = (c >> 8) & 0xFF;
    f = (float)t;
    arg2[1] = 0.003921568f * f;
    t = c & 0xFF;
    f = (float)t;
    arg2[0] = 0.003921568f * f;
}
