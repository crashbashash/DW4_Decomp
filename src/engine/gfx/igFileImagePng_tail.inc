/* matching construct: sweep of about 30 spellings — the combined null test */
void FUN_001673a0(void *png_ptr, void *row_info, unsigned char *data) {
    if (png_ptr == 0 || row_info == 0) {
        return;
    }
}

void thunk_FUN_001592c0(LongListStorageView *self) {
    FUN_001592c0(self);
}

void Gap__Gfx__igFileImagePng__vfunc_23(int dummy0, void **arg1) {
    FUN_001563b0();
    ((DW4VC_88_0 *)(arg1))->vX();
}

int FUN_00167400(void) {
    return DAT_0055fd80[0];
}

int FUN_00167410(Owner_167410 *arg0, int arg1, int arg2, int arg3, void *arg4, void *arg5, int arg6, int arg7) {
    int sp5C;
    int sp58;
    int sp54;
    Obj_167410 *o;

    sp54 = arg1;
    sp58 = arg2;
    sp5C = arg3;
    if (arg4 != 0) {
        FUN_00300f50(arg0, arg4);
    }
    if (arg5 != 0) {
        FUN_00300f50(arg0, arg5);
    }
    if (sp54 != 0) {
        if (arg7 != 0) {
            png_destroy_read_struct(&sp54, &sp58, &sp5C);
        } else {
            png_destroy_info_struct(sp54, &sp5C);
            png_destroy_write_struct(&sp54, &sp58);
        }
    }
    o = arg0->f92;
    if (o != 0) {
        o->vX();
        o = arg0->f92;
        ((igObject *)o)->_refCount = (int)((int) (((igObject *)o)->_refCount - 1));
        if (((unsigned long long) ((long long) (int) ((igObject *)o)->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    o = arg0->f92;
    if (o != 0) {
        ((igObject *)o)->_refCount = (int)((int) (((igObject *)o)->_refCount - 1));
        if (((unsigned long long) ((long long) (int) ((igObject *)o)->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->f92 = 0;
    return arg6;
}

int FUN_00167540(void *png, int bitDepth, int colorType, PngSignificantBits *bits, int *format) {
    int result = -1;
    *format = result;
    switch (colorType) {
    case 0:
        switch (bitDepth) {
        case 1:
        case 2:
        case 4:
        case 8:
        case 16:
            *format = 0;
            result = *format;
            break;
        }
        break;
    case 2:
        switch (bitDepth) {
        case 8:
        case 16:
            *format = 5;
            result = *format;
            if (bits != 0) {
                if (bits->red == 3 && bits->green == 3 && bits->blue == 2) {
                    result = 4;
                } else if (bits->red == 5 && bits->green == 6 && bits->blue == 5) {
                    result = 10;
                } else if (bits->red == 8 && bits->green == 8 && bits->blue == 8) {
                    result = 5;
                }
            }
        }
        break;
    case 3:
        switch (bitDepth) {
        case 8:
            *format = 0x10000;
            result = *format;
            break;
        case 4:
        case 2:
        case 1:
            *format = 0x10000;
            result = 0x10001;
            break;
        }
        break;
    case 4:
        switch (bitDepth) {
        case 8:
        case 16:
            *format = 3;
            result = *format;
            if (bits != 0) {
                if (bits->gray == 4 && bits->alpha == 4) {
                    result = 2;
                } else if (bits->gray == 8 && bits->alpha == 8) {
                    result = 3;
                }
            }
        }
        break;
    case 6:
        switch (bitDepth) {
        case 8:
        case 16:
            *format = 7;
            result = *format;
            if (bits != 0) {
                if (bits->red == 5 && bits->green == 5 && bits->blue == 5 && bits->alpha == 1) {
                    result = 8;
                } else if (bits->red == 2 && bits->green == 2 && bits->blue == 2 && bits->alpha == 2) {
                    result = 6;
                } else if (bits->red == 4 && bits->green == 4 && bits->blue == 4 && bits->alpha == 4) {
                    result = 9;
                } else if (bits->red == 8 && bits->green == 8 && bits->blue == 8 && bits->alpha == 8) {
                    result = 7;
                }
            }
        }
        break;
    }
    return result;
}

int FUN_001681c0(int arg0, int arg1, int arg2) {
    int sp5C;
    int sp58;
    int sp54;
    int sp50;
    int sp4C;
    int sp48;
    int sp44;

    png_get_IHDR(arg1, arg2, &sp5C, &sp58, &sp54, &sp50, &sp4C, &sp48, &sp44);
    png_set_strip_16(arg1);
    if ((sp54 < 8) && (sp50 == 3)) {
        png_set_packing(arg1);
    }
    if (sp54 < 8) {
        if (sp50 == 0) {
            png_set_gray_1_2_4_to_8(arg1);
        }
    }
    if ((png_get_valid(arg1, arg2, 0x10) != 0) && !(sp50 & 4) && !(sp50 & 1)) {
        png_set_tRNS_to_alpha(arg1);
    }
    png_set_read_user_transform_fn(arg1, FUN_001673a0);
    return 1;
}

int Gap__Gfx__igFileImagePng__vfunc_45(void) {
    return 1;
}

