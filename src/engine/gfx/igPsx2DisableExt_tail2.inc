void Gap__Gfx__igPsx2DisableExt__vfunc_29(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 20) = arg1;
}

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

void Gap__Gfx__igPsx2DisableExt__vfunc_31(int arg0, unsigned int arg1, char arg2) {
    switch (arg1) {
    case 0:
        GPR_00554b78 = arg2;
        return;
    case 1:
        GPR_00554b44 = arg2;
        return;
    case 2:
        GPR_00554b48 = arg2;
        return;
    case 4:
        GPR_00554b60 = arg2;
        return;
    case 5:
        GPR_00554b5c = arg2;
        return;
    case 6:
        GPR_00554b4c = arg2;
        return;
    case 7:
        GPR_00554b50 = arg2;
        return;
    case 8:
        GPR_00554b54 = arg2;
        return;
    case 9:
        GPR_00554b58 = arg2;
        return;
    case 10:
        GPR_00554b6c = arg2;
        return;
    case 11:
        GPR_00554b64 = arg2;
        return;
    case 12:
        GPR_00554b68 = arg2;
        
    default:
        return;
    }
}

