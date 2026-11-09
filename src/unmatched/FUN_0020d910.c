typedef struct Viewport {
    float x;
    float y;
    float width;
    float height;
    float nearZ;
    float farZ;
} Viewport;

void FUN_0020dba0(int x, int y, int width, int height, float nearZ, float farZ);
extern Viewport DAT_0056c2c0;
extern int DAT_0056c2e0;
extern short DAT_00568e0c[8];
extern short DAT_00568e0e[8];
extern int DAT_00568e28[4];

void FUN_0020d910(int mode) {
    DAT_0056c2e0 = mode;
    if (DAT_00568e0e[0] == 0 && DAT_00568e0c[0] > 0 && DAT_00568e28[0] == -1) {
        DAT_0056c2c0.y = DAT_0056c2c0.y * 2.0f;
        DAT_0056c2c0.height = DAT_0056c2c0.height * 2.0f;
    }
    FUN_0020dba0((int)DAT_0056c2c0.x, (int)DAT_0056c2c0.y, (int)DAT_0056c2c0.width, (int)DAT_0056c2c0.height,
                 DAT_0056c2c0.nearZ, DAT_0056c2c0.farZ);
}
