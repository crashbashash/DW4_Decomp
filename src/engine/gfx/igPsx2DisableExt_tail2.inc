void Gap__Gfx__igPsx2DisableExt__vfunc_29(igPsx2DisableExt *self, int arg1) {
    self->_context = arg1;
}

unsigned char g_igPsx2DisableExt_ext1Enabled;

unsigned char g_igPsx2DisableExt_ext2Enabled;

unsigned char g_igPsx2DisableExt_ext6Enabled;

unsigned char g_igPsx2DisableExt_ext7Enabled;

unsigned char g_igPsx2DisableExt_ext8Enabled;

unsigned char g_igPsx2DisableExt_ext9Enabled;

unsigned char g_igPsx2DisableExt_ext5Enabled;

unsigned char g_igPsx2DisableExt_ext4Enabled;

unsigned char g_igPsx2DisableExt_ext11Enabled;

unsigned char g_igPsx2DisableExt_ext12Enabled;

unsigned char g_igPsx2DisableExt_ext10Enabled;

unsigned char g_igPsx2DisableExt_ext0Enabled;

int Gap__Gfx__igPsx2DisableExt__vfunc_30(void *self, unsigned int ext)
{
    int enabled = -1;

    switch (ext) {
    case 0:
        enabled = g_igPsx2DisableExt_ext0Enabled;
        break;
    case 1:
        enabled = g_igPsx2DisableExt_ext1Enabled;
        break;
    case 2:
        enabled = g_igPsx2DisableExt_ext2Enabled;
        break;
    case 4:
        enabled = g_igPsx2DisableExt_ext4Enabled;
        break;
    case 5:
        enabled = g_igPsx2DisableExt_ext5Enabled;
        break;
    case 6:
        enabled = g_igPsx2DisableExt_ext6Enabled;
        break;
    case 7:
        enabled = g_igPsx2DisableExt_ext7Enabled;
        break;
    case 8:
        enabled = g_igPsx2DisableExt_ext8Enabled;
        break;
    case 9:
        enabled = g_igPsx2DisableExt_ext9Enabled;
        break;
    case 10:
        enabled = g_igPsx2DisableExt_ext10Enabled;
        break;
    case 11:
        enabled = g_igPsx2DisableExt_ext11Enabled;
        break;
    case 12:
        enabled = g_igPsx2DisableExt_ext12Enabled;
        break;
    }
    return enabled;
}

void Gap__Gfx__igPsx2DisableExt__vfunc_31(int arg0, unsigned int arg1, char arg2) {
    switch (arg1) {
    case 0:
        g_igPsx2DisableExt_ext0Enabled = arg2;
        return;
    case 1:
        g_igPsx2DisableExt_ext1Enabled = arg2;
        return;
    case 2:
        g_igPsx2DisableExt_ext2Enabled = arg2;
        return;
    case 4:
        g_igPsx2DisableExt_ext4Enabled = arg2;
        return;
    case 5:
        g_igPsx2DisableExt_ext5Enabled = arg2;
        return;
    case 6:
        g_igPsx2DisableExt_ext6Enabled = arg2;
        return;
    case 7:
        g_igPsx2DisableExt_ext7Enabled = arg2;
        return;
    case 8:
        g_igPsx2DisableExt_ext8Enabled = arg2;
        return;
    case 9:
        g_igPsx2DisableExt_ext9Enabled = arg2;
        return;
    case 10:
        g_igPsx2DisableExt_ext10Enabled = arg2;
        return;
    case 11:
        g_igPsx2DisableExt_ext11Enabled = arg2;
        return;
    case 12:
        g_igPsx2DisableExt_ext12Enabled = arg2;
        
    default:
        return;
    }
}

