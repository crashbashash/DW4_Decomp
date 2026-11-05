typedef struct Ctl { char pad[76]; float a; float b; float c; char pad2[40]; float scale; unsigned char flag; } Ctl;
void FUN_004658c0(void);
void FUN_004655a0(Ctl *s, int key, int down) {
    float f;
    switch (key) {
    case 0x9C:
        if (down) s->scale *= 1.5f;
        break;    case 0x9D:
        if (down) s->scale /= 1.5f;
        break;
    case 0x98:
        if (down) f = 1.0f; else f = -1.0f;
        s->c += f;
        break;
    case 0x92:
        if (down) f = 1.0f; else f = -1.0f;
        s->c -= f;
        break;
    case 0x88:
        if (down) f = 1.0f; else f = -1.0f;
        s->b -= f;
        break;
    case 0x89:
        if (down) f = 1.0f; else f = -1.0f;
        s->b += f;
        break;
    case 0x94:
        if (down) f = 1.0f; else f = -1.0f;
        s->a += f;
        break;
    case 0x96:
        if (down) f = 1.0f; else f = -1.0f;
        s->a -= f;
        break;
    case 0x5A:
        if (down) s->flag = !s->flag;
        FUN_004658c0();
        break;
    }
}
