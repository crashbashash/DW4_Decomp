void Gap__Core__igMediaFile__vfunc_24(igMediaFileView *arg0) {
    igMediaView *t;

    if (arg0->_isOpen != 0) {
        arg0->vfunc_32();
        arg0->_media->vfunc_26(arg0->_fileHandle);
        arg0->_media->vfunc_24(arg0->_fileHandle);
        t = arg0->_media;
        REL(t)
        arg0->_media = 0;
        arg0->_fileHandle = -1;
        FUN_00300f50((int)arg0, (int)arg0->_fBuf);
        arg0->_fBuf = 0;
        arg0->_bufSize = 0;
        arg0->_bufPos = 0;
        arg0->_isOpen = 0;
    }
}

void **Gap__Core__igMediaFile__vfunc_25(void **arg0, const char *fileName, int arg2) {
    igResult sp4C;
    igResult sp48;
    igResult sp44;
    igResult sp40;
    igResult sp3C;
    igResult sp38;
    igResult sp34;
    igResult sp30;
    int var_v1;

    FUN_002e30b0((int *)arg0, fileName);
    if (strcmp(arg2, &DAT_004f96a8[0]) == 0) {
        sp4C = ((igFileView *)(arg0))->vfunc_23((int)(0));
        var_v1 = sp4C.v;
        goto block_21;
    }
    if (strcmp(arg2, (int *)DAT_004f9c48) == 0) {
        sp48 = ((igFileView *)(arg0))->vfunc_23((int)(4));
        var_v1 = sp48.v;
        goto block_21;
    }
    if (strcmp(arg2, (int *)((char *)DAT_004f92f0)) == 0) {
        sp44 = ((igFileView *)(arg0))->vfunc_23((int)(1));
        var_v1 = sp44.v;
        goto block_21;
    }
    if (strcmp(arg2, (int *)((char *)DAT_004f9c50)) == 0) {
        sp40 = ((igFileView *)(arg0))->vfunc_23((int)(5));
        var_v1 = sp40.v;
        goto block_21;
    }
    if ((strcmp(arg2, (int *)DAT_004f9c58) == 0) || (strcmp(arg2, &DAT_004f9c60[0]) == 0)) {
        sp3C = ((igFileView *)(arg0))->vfunc_23((int)(3));
        var_v1 = sp3C.v;
        goto block_21;
    }
    if ((strcmp(arg2, (int *)DAT_004f9c68) == 0) || (strcmp(arg2, &DAT_004f9c70[0]) == 0)) {
        sp38 = ((igFileView *)(arg0))->vfunc_23((int)(7));
        var_v1 = sp38.v;
        goto block_21;
    }
    if ((strcmp(arg2, (int *)DAT_004f9c78) == 0) || (strcmp(arg2, &DAT_004f9c80[0]) == 0)) {
        sp34 = ((igFileView *)(arg0))->vfunc_23((int)(2));
        var_v1 = sp34.v;
        goto block_21;
    }
    if ((strcmp(arg2, (int *)DAT_004f9c88) == 0) || (strcmp(arg2, &DAT_004f9c90[0]) == 0)) {
        sp30 = ((igFileView *)(arg0))->vfunc_23((int)(6));
        var_v1 = sp30.v;
        goto block_21;
    }
    return 0;
block_21:
    return var_v1 == g_resultFailure.v ? 0 : arg0;
}

void Gap__Core__igMediaFile__vfunc_26(igMediaFileView *self)
{
    self->vfunc_24();
}

void FUN_002ec570(igMediaFileView *arg0, int arg1) {
    int temp_a1;
    int var_s0;
    int var_v0;
    if (arg0->_bufSize < arg1) {
        var_s0 = arg1 * 2;
        if (arg1 > 0x100000) {
            var_s0 = arg1 + 0x100000;
        }
        temp_a1 = (int)arg0->_fBuf;
        if (temp_a1 != 0) {
            var_v0 = FUN_00300e50((int)arg0, temp_a1, var_s0);
        } else {
            var_v0 = igObject_AllocateStorage((int)arg0, var_s0);
        }
        arg0->_fBuf = (unsigned char *)var_v0;
        arg0->_bufSize = var_s0;
    }
    arg0->_fileSize = arg1;
}

int Gap__Core__igMediaFile__vfunc_27(igMediaFileView *arg0, int arg1, int arg2, int arg3) {
    int bytes;
    int got;
    int n;
    int cnt;
    int back;
    if (arg0->_isOpen == 0) {
        return -1;
    }
    bytes = arg2 * arg3;
    if (arg0->_isBinary == 1) {
        got = arg0->_media->vfunc_28(arg0->_fileHandle, (void *)arg1, (unsigned)arg3 * arg2);
        n = got / arg2;
        back = n * arg2;
        if (got != back) {
            arg0->_media->vfunc_30(arg0->_fileHandle, back - got, 1);
        }
        return n;
    }
    cnt = arg3;
    if (arg0->_fileSize < arg0->_bufPos + bytes) {
        cnt = (arg0->_fileSize - arg0->_bufPos) / arg2;
        bytes = cnt * arg2;
    }
    memcpy(arg1, arg0->_fBuf + arg0->_bufPos, bytes, arg0->_bufPos);
    arg0->_bufPos = arg0->_bufPos + bytes;
    return cnt;
}

void Gap__Core__igMediaFile__vfunc_28(igMediaFileView *arg0, int arg1, int arg2, int (*arg3)(int, int), int arg4) {
    if (arg0->_isOpen == 0) {
        arg3(arg4, -1);
    }
    if (arg0->_isBinary == 1) {
        arg0->_media->vfunc_29(arg0->_fileHandle, (void *)arg1, arg2, arg3, arg4);
    }
    arg3(arg4, arg0->Read((void *)arg1, 1, arg2));
}

int Gap__Core__igMediaFile__vfunc_29(igMediaFileView *arg0, int arg1, int arg2, int arg3) {
    int s0;
    if (arg0->_isOpen == 0) {
        return -1;
    }
    if (arg2 == 0) {
        return 0;
    }
    if (arg0->_isBinary == 1) {
        if (arg0->_openMode == 6) {
            arg0->_media->vfunc_30(arg0->_fileHandle, 0, 2);
        }
        return arg0->_media->vfunc_27(arg0->_fileHandle, (const void *)arg1, arg3 * arg2) / arg2;
    }
    s0 = arg2 * arg3;
    if (arg0->_openMode == 2) {
        arg0->_bufPos = arg0->_fileSize;
    }
    FUN_002ec570(arg0, arg0->_bufPos + s0);
    memcpy(arg0->_fBuf + arg0->_bufPos, arg1, s0);
    arg0->_bufPos = arg0->_bufPos + s0;
    return s0 / arg2;
}

int Gap__Core__igMediaFile__vfunc_32(igMediaFileView *arg0) {
    if (arg0->_isBinary != 0) {
        return 0;
    }
    if (arg0->_write != 0) {
        arg0->_media->vfunc_30(arg0->_fileHandle, 0, 0);
        arg0->_media->vfunc_27(arg0->_fileHandle, arg0->_fBuf, arg0->_fileSize);
    }
    return 0;
}

int Gap__Core__igMediaFile__vfunc_31(igMediaFileView *self, int fmt, ...) {
    char buf[16384];
    int n;
    int off;
    int len;
    int pos;
    if (self->_isBinary != 0) {
        return -1;
    }
    n = __builtin_args_info(2);
    if (n >= 8) {
        off = 0;
    } else {
        off = (8 - n) * 8;
    }
    len = vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - off);
    pos = self->_bufPos + len;
    if (pos >= self->_fileSize) {
        FUN_002ec570(self, pos);
    }
    memcpy(self->_fBuf + self->_bufPos, buf, len);
    self->_bufPos = self->_bufPos + len;
    return len;
}

int Gap__Core__igMediaFile__vfunc_33(igMediaFileView *arg0) {
    int sp1C;
    int t;
    if (arg0->_isBinary != 0) {
        unsigned int a = arg0->_fileHandle;
        igMediaView *v = arg0->_media;
        if (v->vfunc_28(a, &sp1C, 1) != 0) {
            return sp1C;
        }
        return -1;
    }
    t = arg0->_bufPos;
    if (t >= arg0->_fileSize) {
        return -1;
    }
    arg0->_bufPos = t + 1;
    return arg0->_fBuf[arg0->_bufPos - 1];
}

int Gap__Core__igMediaFile__vfunc_34(igMediaFileView *a, int c) {
    int n;
    if (a->_isBinary != 0) return -1;
    n = a->_bufPos;
    if (n == 0) return -1;
    a->_bufPos = n - 1;
    if ((c & 0xff) != a->_fBuf[a->_bufPos]) c = -1;
    return c;
}

int Gap__Core__igMediaFile__vfunc_35(igMediaFileView *arg0, unsigned char arg1) {
    int temp_a1;

    if (arg0->_isBinary != 0) {
        return -1;
    }
    temp_a1 = arg0->_bufPos + 1;
    if (temp_a1 >= arg0->_fileSize) {
        FUN_002ec570(arg0, temp_a1);
    }
    arg0->_fBuf[arg0->_bufPos] = arg1;
    arg0->_bufPos = arg0->_bufPos + 1;
    return arg1;
}

char *Gap__Core__igMediaFile__vfunc_36(igMediaFileView *arg0, char *arg1, int arg2) {
    if (arg1 == 0) return 0;
    if (arg0->_isBinary != 0) return 0;
    if (arg0->_bufPos >= arg0->_fileSize) return 0;
    int i = 0;
    arg2 = arg2 - 1;
    if (arg2 + arg0->_bufPos >= arg0->_fileSize) arg2 = arg0->_fileSize - arg0->_bufPos;
    while (i < arg2) {
        unsigned char c = arg0->_fBuf[arg0->_bufPos];
        arg1[i] = c;
        i++;
        arg0->_bufPos = arg0->_bufPos + 1;
        if (c == 10) break;
    }
    arg1[i] = 0;
    return arg1;
}

int Gap__Core__igMediaFile__vfunc_37(igMediaFileView *arg0, int arg1) {
    int temp_a1;
    int temp_v0;

    if (arg1 == 0) {
        return -1;
    }
    if (arg0->_isBinary != 0) {
        return -1;
    }
    temp_v0 = strlen(arg1);
    temp_a1 = arg0->_bufPos + temp_v0;
    if (temp_a1 >= arg0->_fileSize) {
        FUN_002ec570(arg0, temp_a1);
    }
    memcpy(arg0->_fBuf + arg0->_bufPos, arg1, temp_v0);
    arg0->_bufPos = arg0->_bufPos + temp_v0;
    return temp_v0;
}

int Gap__Core__igMediaFile__vfunc_38(igMediaFileView *arg0, int arg1, int arg2) {
    int base;
    int cur;
    if (arg0->_isBinary != 0) {
        base = arg0->vfunc_39();
        if (arg0->_media->vfunc_30(arg0->_fileHandle, arg1, arg2) != 0) {
            return 0;
        }
        cur = arg0->vfunc_39();
        switch (arg2) {
        case 0:
            return -(cur != arg1);
        case 1:
            return -(arg1 != cur - base);
        case 2:
            return 0;
        default:
            return -1;
        }
    } else {
        switch (arg2) {
        case 0:
            arg0->_bufPos = arg1;
            break;
        case 1:
            arg0->_bufPos = arg0->_bufPos + arg1;
            break;
        case 2:
            arg0->_bufPos = arg0->_fileSize + arg1;
            break;
        default:
            return -1;
        }
        if (arg0->_bufPos > arg0->_fileSize) {
            arg0->_bufPos = arg0->_fileSize;
        } else if (arg0->_bufPos < 0) {
            arg0->_bufPos = 0;
        }
        return 0;
    }
}

int Gap__Core__igMediaFile__vfunc_39(igMediaFileView *p) { if (p->_isBinary) { unsigned int a = p->_fileHandle; igMediaView *o = p->_media; return o->vfunc_31(a); } return p->_bufPos; }
