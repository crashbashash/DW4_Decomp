/* Opens the file in `mode` (0-3 text, 4-7 binary: read, write, append, read-write; 8 the mode it
 * was last opened in). A relative name is tried under each entry of the search path list in turn.
 * A text file is read whole into the buffer. */
void Gap__Core__igPsx2File__vfunc_23(int *result, igPsx2FileView *file, unsigned int mode) {
    char *searchPaths;
    char path[512];
    bool absolute;
    int flags;
    unsigned char more;
    int attempt;
    int retries;
    char *devicePath;
    int hasDirectory;
    int fd;
    char *p;
    unsigned int n;
    int size;
    flags = 0;
    if (mode == 8) mode = file->_openMode;
    if (file->_isOpen == 1 && file->_openMode == mode) {
        *result = g_statusSucceeded.v;
    } else {
        switch (mode) {
        case 0: case 1: case 2: case 3: case 8:
            file->_isBinary = 0;
            break;
        case 4: case 5: case 6: case 7:
            file->_isBinary = 1;
            break;
        }
        switch (mode) {
        case 1: case 5: flags = SCE_TRUNC | SCE_CREAT | SCE_WRONLY; break;
        case 2: case 6: flags = SCE_CREAT | SCE_APPEND; break;
        case 3: case 7: flags = SCE_CREAT | SCE_RDWR; break;
        case 0: case 4: case 8: flags = SCE_RDONLY; break;
        }
        file->_bufSize = 0;
        p = path;
        file->_bufPos = 0;
        n = sizeof(path);
        file->_isOpen = 0;
        if (p != 0) {
            do {
                *p = 0;
                n -= 1;
                p += 1;
            } while (n != 0);
        }
        more = 1;
        absolute = FilePath_IsAbsolute(file->_fileName);
        hasDirectory = FilePath_HasDirectory(file->_fileName);
        searchPaths = (char *)FUN_002e34a0();
        attempt = 0;
        while (more && attempt < 0x100) {
            if (absolute) {
                path[0] = 0;
                more = 0;
                goto open;
            }
            if (hasDirectory != 0) {
                path[0] = 0;
                hasDirectory = 0;
                goto open;
            }
            more = FUN_002e34d0(&searchPaths, path, sizeof(path));
            if (more) {
open:
                strcat(path, file->_fileName);
                devicePath = file->makeCompleteFilename(path);
                if (*devicePath == 'c') {
                    retries = 10;
                    while ((fd = sceOpen(devicePath, flags)) < 0 && retries != 0) {
                        retries -= 1;
                    }
                } else {
                    fd = sceOpen(devicePath, flags, 0666);
                }
                file->_fileHandle = fd;
                if (!(0 > fd)) break;
            }
            attempt += 1;
        }
        if (file->_fileHandle < 0) {
            *result = g_allocatorFailureStatus.v;
        } else {
            if (mode == 6) sceLseek(file->_fileHandle, 0, SCE_SEEK_END);
            if (file->_isBinary == 0) {
                size = sceLseek(file->_fileHandle, 0, SCE_SEEK_END);
                FUN_0032b5b0((struct S_32b5b0 *)file, size);
                sceLseek(file->_fileHandle, 0, SCE_SEEK_SET);
                if (size > 0) {
                    fd = sceRead(file->_fileHandle, file->_fBuf, size);
                    if (fd != size) FUN_0032b5b0((struct S_32b5b0 *)file, fd);
                }
                if (mode == 2) file->_bufPos = size;
                else file->_bufPos = 0;
            }
            file->_openMode = mode;
            file->_isOpen = 1;
            *result = g_statusSucceeded.v;
        }
    }
}

void Gap__Core__igPsx2File__vfunc_24(int *arg0) {
    if (arg0[6] >= 0) {
        ((Obj_32b2e0 *)arg0)->vX();
        sceClose(arg0[6]);
        arg0[6] = -1;
        if (arg0[11] != 0) {
            FUN_00300f50((int)arg0, arg0[11]);
        }
        arg0[11] = 0;
        arg0[12] = 0;
        arg0[13] = 0;
        arg0[16] = 0;
    }
}

void **Gap__Core__igPsx2File__vfunc_25(void **arg0, int arg1, int arg2) {
    DW4SR4 sp4C;
    DW4SR4 sp48;
    DW4SR4 sp44;
    DW4SR4 sp40;
    DW4SR4 sp3C;
    DW4SR4 sp38;
    DW4SR4 sp34;
    DW4SR4 sp30;
    int var_v1;

    FUN_002e30b0((int *)arg0, arg1);
    if (strcmp(arg2, &DAT_004f96a8[0]) == 0) {
        sp4C = ((DW4VCSR_92_1 *)(arg0))->vX((int)(0));
        var_v1 = sp4C.w0;
        goto block_21;
    }
    if (strcmp(arg2, (int *)DAT_004f9c48) == 0) {
        sp48 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(4));
        var_v1 = sp48.w0;
        goto block_21;
    }
    if (strcmp(arg2, (int *)((char *)DAT_004f92f0)) == 0) {
        sp44 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(1));
        var_v1 = sp44.w0;
        goto block_21;
    }
    if (strcmp(arg2, (int *)((char *)DAT_004f9c50)) == 0) {
        sp40 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(5));
        var_v1 = sp40.w0;
        goto block_21;
    }
    if ((strcmp(arg2, (int *)DAT_004f9c58) == 0) || (strcmp(arg2, &DAT_004f9c60[0]) == 0)) {
        sp3C = ((DW4VCSR_92_1 *)(arg0))->vX((int)(3));
        var_v1 = sp3C.w0;
        goto block_21;
    }
    if ((strcmp(arg2, (int *)DAT_004f9c68) == 0) || (strcmp(arg2, &DAT_004f9c70[0]) == 0)) {
        sp38 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(7));
        var_v1 = sp38.w0;
        goto block_21;
    }
    if ((strcmp(arg2, (int *)DAT_004f9c78) == 0) || (strcmp(arg2, &DAT_004f9c80[0]) == 0)) {
        sp34 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(2));
        var_v1 = sp34.w0;
        goto block_21;
    }
    if ((strcmp(arg2, (int *)DAT_004f9c88) == 0) || (strcmp(arg2, &DAT_004f9c90[0]) == 0)) {
        sp30 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(6));
        var_v1 = sp30.w0;
        goto block_21;
    }
    return 0;
block_21:
    return (var_v1 == g_allocatorFailureStatus.v) ? (void **)0 : arg0;
}

void Gap__Core__igPsx2File__vfunc_26(igPsx2FileView *self)
{
    self->vfunc_22();
}

void FUN_0032b5b0(struct S_32b5b0 *arg0, int arg1) {
    int n;
    if (arg0->cap < arg1) {
        if (arg1 > 0x100000) {
            n = arg1 + 0x100000;
        } else {
            n = arg1 * 2;
        }
        if (arg0->p != 0) {
            arg0->p = FUN_00300e50((int)arg0, arg0->p, n);
        } else {
            arg0->p = igObject_AllocateStorage((int)arg0, n);
        }
        arg0->cap = n;
    }
    arg0->len = arg1;
}

int Gap__Core__igPsx2File__vfunc_27(A_32b640 *arg0, int arg1, int arg2, int arg3) {
    int base;
    int r;
    int q;
    int bytes;
    int a1;
    int lim;
    if (arg0->f18 < 0) {
        return -1;
    }
    base = arg0->vX();
    if (arg0->f3c == 1) {
        r = sceRead(arg0->f18, arg1, arg3 * arg2);
        arg3 = r / arg2;
        q = arg3 * arg2;
        if (r != q) {
            sceLseek(arg0->f18, base + q, 0);
        }
        return arg3;
    }
    a1 = arg0->f34;
    bytes = arg2 * arg3;
    lim = arg0->f38;
    if (lim < a1 + bytes) {
        arg3 = (lim - a1) / arg2;
        bytes = arg3 * arg2;
    }
    memcpy(arg1, *(int *)((char *)arg0 + 44) + a1, bytes);
    arg0->f34 = arg0->f34 + bytes;
    return arg3;
}

int Gap__Core__igPsx2File__vfunc_29(F_32b760 *arg0, int arg1, int arg2, int arg3) {
    int s0;
    if (arg0->f24 < 0) return -1;
    if (arg2 == 0) return 0;
    if (arg0->f60 == 1) {
        if (arg0->f20 == 6) {
            sceLseek(arg0->f24, 0, 2);
        }
        return sceWrite(arg0->f24, arg1, arg3 * arg2) / arg2;
    }
    s0 = arg2 * arg3;
    if (arg0->f20 == 2) {
        arg0->f52 = arg0->f56;
    }
    FUN_0032b5b0((S_32b5b0 *)arg0, arg0->f52 + s0);
    memcpy(arg0->f44 + arg0->f52, arg1, s0);
    arg0->f52 = arg0->f52 + s0;
    return s0 / arg2;
}

int Gap__Core__igPsx2File__vfunc_32(S_32b870 *arg0) {
    if (arg0->d != 0) return 0; sceLseek(arg0->a, 0, 0); sceWrite(arg0->a, arg0->b, arg0->c); return 0;
}

int Gap__Core__igPsx2File__vfunc_31(struct S_32bba0 *arg0, int arg1, ...) {
    char buf[16384];
    int n;
    int off;
    int len;
    int cur;
    if (arg0->f60 != 0) {
        return -1;
    }
    n = __builtin_args_info(2);
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    len = vsprintf(buf, arg1, (char *)__builtin_next_arg(arg1) - off);
    cur = arg0->f52 + len;
    if (cur >= arg0->f56) {
        FUN_0032b5b0((S_32b5b0 *)arg0, cur);
    }
    memcpy(arg0->f44 + arg0->f52, buf, len);
    arg0->f52 = arg0->f52 + len;
    return len;
}

int Gap__Core__igPsx2File__vfunc_33(S0_32bc80 *arg0) {
    int sp1C;
    int i;

    if (arg0->f60 != 0) {
        sceRead(arg0->f24, &sp1C, 1);
        return sp1C;
    }
    i = arg0->f52;
    if (i >= arg0->f56) {
        return -1;
    }
    arg0->f52 = i + 1;
    return arg0->f44[arg0->f52 - 1];
}

int Gap__Core__igPsx2File__vfunc_34(struct F_32bcf0 *arg0, int arg1) {
    int temp_v0;
    int var_a1;

    var_a1 = arg1;
    if (arg0->err != 0) {
        return -1;
    }
    temp_v0 = arg0->pos;
    if (temp_v0 == 0) {
        return -1;
    }
    arg0->pos = temp_v0 - 1;
    if ((var_a1 & 0xFF) != arg0->buf[arg0->pos]) {
        var_a1 = -1;
    }
    return var_a1;
}

int Gap__Core__igPsx2File__vfunc_35(F_32bd50 *arg0, unsigned char arg1) {
    int temp_a1;

    if (arg0->f60 != 0) {
        return -1;
    }
    temp_a1 = arg0->f52 + 1;
    if (temp_a1 >= arg0->f56) {
        FUN_0032b5b0((S_32b5b0 *)arg0, temp_a1);
    }
    arg0->f44[arg0->f52] = arg1;
    arg0->f52 = arg0->f52 + 1;
    return arg1;
}

char *Gap__Core__igPsx2File__vfunc_36(S_32bdd0 *arg0, char *arg1, int arg2) {
    /* matching construct: variant search — decl order [2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int var_a5;
    int temp_a3;
    int temp_v1;

    if (arg1 == 0) {
        return 0;
    }
    if (arg0->f3c != 0) {
        return 0;
    }
    temp_v1 = arg0->f38;
    temp_a3 = arg0->f34;
    if (temp_a3 >= temp_v1) {
        return 0;
    }
    arg2 = arg2 - 1;
    var_a5 = 0;
    if ((arg2 + temp_a3) >= temp_v1) {
        arg2 = temp_v1 - temp_a3;
    }
    while (var_a5 < arg2) {
        temp_a3 = arg0->f2c[arg0->f34];
        arg1[var_a5] = temp_a3;
        var_a5 += 1;
        arg0->f34 = arg0->f34 + 1;
        if (temp_a3 == 0xA) {
            break;
        }
    }
    arg1[var_a5] = 0;
    return arg1;
}

int Gap__Core__igPsx2File__vfunc_37(struct S_32be80 *arg0, char *arg1) {
    int temp_a1;
    int temp_v0;

    if (arg1 == 0) {
        return -1;
    }
    if (arg0->f60 != 0) {
        return -1;
    }
    temp_v0 = strlen(arg1);
    temp_a1 = arg0->f52 + temp_v0;
    if (temp_a1 >= arg0->f56) {
        FUN_0032b5b0((S_32b5b0 *)arg0, temp_a1);
    }
    memcpy(arg0->f44 + arg0->f52, arg1, temp_v0);
    arg0->f52 = arg0->f52 + temp_v0;
    return temp_v0;
}

int Gap__Core__igPsx2File__vfunc_38(int *arg0, int arg1, int arg2) {
    int s;
    if (arg0[15] != 0) {
        switch (arg2) {
        case 0:
            s = sceLseek(arg0[6], arg1, 0);
            return -(s != arg1);
        case 1:
            s = ((Obj_32bf30 *)arg0)->vX();
            return -(arg1 != sceLseek(arg0[6], arg1, 1) - s);
        case 2:
            sceLseek(arg0[6], arg1, 2);
            return 0;
        default:
            return -1;
        }
    } else {
        switch (arg2) {
        case 0:
            arg0[13] = arg1;
            break;
        case 1:
            arg0[13] = arg0[13] + arg1;
            break;
        case 2:
            arg0[13] = arg0[14] + arg1;
            break;
        default:
            return -1;
        }
        {int v1 = arg0[14]; int v0 = arg0[13];
        if (v1 < v0) arg0[13] = v1;
        else if (v0 < 0) arg0[13] = 0;}
        return 0;
    }
}

int Gap__Core__igPsx2File__vfunc_39(igPsx2File *arg0) {
    if (arg0->_isBinary != 0) {
        return sceLseek(arg0->_fileHandle, 0, 1);
    }
    return arg0->_bufPos;
}

void FUN_0032c0c0(void) {
    if (DAT_00587338[0] == 0) {
        if (((int * *)DAT_00587330)[0] == 0) {
            ((int * *)DAT_00587330)[0] = (int *)(&text_host0[0]);
        }
    } else {
        ((int * *)DAT_00587330)[0] = (int *)text_cdrom0;
    }
}

static inline void append_32c240(const igSmartPointer<Text> &ref, char *chars) {
    Text *text = ref.p;
    int length = text->length;
    igStringObj_Insert((IniStringView *)text, chars, (unsigned int)length, (unsigned int)(strlen(chars)));
}

StringRef_32c240 FUN_0032c240(char *prefix, char *path, int extra2) {
    char *chars;
    int limit, i;
    char c;
    igSmartPointer<Text> text(((Text *)FUN_002b9500(((int)Memory_GetAllocatorBySelector(DAT_00587048[0])))));
    if (prefix == 0) {
        igStringObj_Set((int)(text.get()), (int)path);
    } else if (*prefix == 0x63) {
        igStringObj_Set((int)(text.get()), (int)prefix);
        c = *path;
        if (c != 0x5C && c != 0x2F) {
            append_32c240(text, DAT_004ffbe8);
        }
        append_32c240(text, path);
        append_32c240(text, DAT_004ffbf0);
        limit = strlen(path) + 8;
        for (i = 7; i < limit; i++) {
            chars = text.get()->chars + i;
            if (*chars == 0x2F) {
                *chars = 0x5C;
            } else {
                *chars = _toupper(*chars);
            }
        }
    } else {
        igStringObj_Set((int)(text.get()), (int)prefix);
        append_32c240(text, path);
    }
    chars = text.get()->chars;
    if (chars == 0) {
        chars = g_stringObjEmptyText[0];
    }
    StringRef_32c240 result(chars);
    return result;
}

