class SphereMapAllocator {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual unsigned char *alloc(int);
    virtual void w53();
    virtual void w54();
    virtual void w55();
    virtual void w56();
    virtual void w57();
    virtual void w58();
    virtual void w59();
    virtual void w60();
    virtual void w61();
    virtual void w62();
    virtual void w63();
    virtual void release(void *);
};
extern "C" {
extern float sqrtf(float);
extern void *memset(void *, int, unsigned int);
extern SphereMapAllocator *Memory_GetAllocatorBySelector(int);
extern int FUN_001c3fd0(float *);
extern void FUN_001c4140(float *, void *, int *, unsigned char *);
extern int DAT_00587028[4];
extern int DAT_00587060[4];
extern unsigned char GPR_00554c14;
}

extern "C" void FUN_001c3ab0(int width, int height, int bpp, void *face1, void *face0, void *face3, void *face2, void *face5, void *face4, unsigned char *out) {
    SphereMapAllocator *a;
    unsigned char *mask;
    int total;
    int y;
    int x;
    int row;
    int face;
    float n[3];
    float dir[3];
    int nb[4];
    float acc[4];
    total = bpp * (width * height);
    if (GPR_00554c14 != 0) {
        a = Memory_GetAllocatorBySelector(DAT_00587028[0]);
    } else {
        a = Memory_GetAllocatorBySelector(DAT_00587060[0]);
    }
    mask = a->alloc(width * height);
    memset(mask, 0, width * height);
    for (y = 0; y < height; y++) {
        float fy = 2.0f * ((float)y / (float)(height - 1) - 0.5f);
        float fy2 = fy * fy;
        row = y * width;
        for (x = 0; x < width; x++) {
            float fx = 2.0f * ((float)x / (float)(width - 1) - 0.5f);
            float fx2 = fx * fx;
            if (fx2 + fy2 <= 1.0f) {
                int i;
                void *color;
                unsigned char *dst;
                n[0] = fx;
                n[1] = fy;
                n[2] = sqrtf(1.0f - fx2 - fy2);
                for (i = 0; i < 3; i++) {
                    dir[i] = 2.0f * (n[2] * n[i]);
                }
                dir[2] -= 1.0f;
                dst = out + bpp * (x + row);
                face = FUN_001c3fd0(dir);
                color = 0;
                if (face == 1) {
                    color = face1;
                } else if (face == 0) {
                    color = face0;
                } else if (face == 3) {
                    color = face3;
                } else if (face == 2) {
                    color = face2;
                } else if (face == 5) {
                    color = face5;
                } else if (face == 4) {
                    color = face4;
                }
                if (color == 0) {
                    mask[x + row] = 1;
                } else {
                    FUN_001c4140(dir, color, &face, dst);
                }
            }
        }
    }
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            int at = x + y * width;
            int dstOffset = bpp * at;
            if (mask[y * width + x] == 1) {
                int count;
                int i;
                nb[0] = bpp * (x + (y - 1) * width);
                nb[1] = bpp * (x + (y + 1) * width);
                nb[2] = bpp * (at - 1);
                nb[3] = bpp * (at + 1);
                memset(acc, 0, 16);
                count = 0;
                for (i = 0; i < 4; i++) {
                    if (nb[i] >= 0 && nb[i] <= total - bpp && mask[nb[i] % bpp] == 0) {
                        int k;
                        count++;
                        for (k = 0; k < bpp; k++) {
                            acc[k] += (float)(unsigned int)out[nb[i] + k];
                        }
                    }
                }
                if (count != 0) {
                    int k;
                    unsigned char *dst;
                    for (i = 0; i < 4; i++) {
                        acc[i] /= (float)count;
                    }
                    dst = out + dstOffset;
                    for (k = 0; k < bpp; k++) {
                        dst[k] = (unsigned int)acc[k];
                    }
                }
            }
        }
    }
    if (GPR_00554c14 != 0) {
        a = Memory_GetAllocatorBySelector(DAT_00587028[0]);
    } else {
        a = Memory_GetAllocatorBySelector(DAT_00587060[0]);
    }
    a->release(mask);
}
