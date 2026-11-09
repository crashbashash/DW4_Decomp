extern unsigned char GPR_00554b44;
extern unsigned char GPR_00554b48;
extern unsigned char GPR_00554b4c;
extern unsigned char GPR_00554b50;
extern unsigned char GPR_00554b54;
extern unsigned char GPR_00554b58;
extern unsigned char GPR_00554b5c;
extern unsigned char GPR_00554b60;
extern unsigned char GPR_00554b64;
extern unsigned char GPR_00554b68;
extern unsigned char GPR_00554b6c;
extern unsigned char GPR_00554b78;

int Gap__Gfx__igPsx2DisableExt__vfunc_30(void *self, unsigned int ext)
{
    int enabled = -1;

    switch (ext) {
    case 0:
        enabled = GPR_00554b78;
        break;
    case 1:
        enabled = GPR_00554b44;
        break;
    case 2:
        enabled = GPR_00554b48;
        break;
    case 4:
        enabled = GPR_00554b60;
        break;
    case 5:
        enabled = GPR_00554b5c;
        break;
    case 6:
        enabled = GPR_00554b4c;
        break;
    case 7:
        enabled = GPR_00554b50;
        break;
    case 8:
        enabled = GPR_00554b54;
        break;
    case 9:
        enabled = GPR_00554b58;
        break;
    case 10:
        enabled = GPR_00554b6c;
        break;
    case 11:
        enabled = GPR_00554b64;
        break;
    case 12:
        enabled = GPR_00554b68;
        break;
    }
    return enabled;
}
