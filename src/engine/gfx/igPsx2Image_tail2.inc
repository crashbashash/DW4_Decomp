void Gap__Gfx__igPsx2Image__vfunc_19(void *arg0) {
    FUN_0015a380((S_15a380 *)arg0);
    if (*(int *)((char *)(arg0) + 24) == 0x66) {
        ((DW4VC_136_0 *)(((char *)(arg0) + 0)))->vX();
    }
}

void Gap__Gfx__igPsx2Image__vfunc_20(void *arg0) {
    C_16e320 *c = (C_16e320 *)arg0;
    int temp_v1 = c->st;
    if ((temp_v1 == 0x64) || (temp_v1 == 0)) {
        c->st = 0x64;
        c->vX();
    }
    FUN_0015a600((T_15a600 *)arg0);
}

void Gap__Gfx__igPsx2Image__vfunc_11(void) {
    Gap__Core__igObject__vfunc_09();
}

void thunk_FUN_001592c0__0016e390(LongListStorageView *self) {
    FUN_001592c0(self);
}

void Gap__Gfx__igPsx2Image__vfunc_23(int dummy0, void **arg1) {
    FUN_001563b0();
    ((DW4VC_88_0 *)(arg1))->vX();
}

unsigned char Gap__Gfx__igPsx2Image__vfunc_42(igPsx2Image *self, int format, igPsx2Image *source) {
    unsigned char supported = 0;
    switch (source->_pfmt) {
    case 0:
        switch (format) {
        case 0x10000:
            supported = 1;
            break;
        case 1:
        case 0:
            supported = 1;
            break;
        }
        break;
    case 1:
        switch (format) {
        case 0x10000:
            supported = 1;
            break;
        case 0:
        case 1:
            supported = 1;
            break;
        }
        break;
    case 3:
        break;
    case 2:
        switch (format) {
        case 0x10000:
            supported = 1;
            break;
        case 2:
            break;
        }
        break;
    }
    if (supported) {
        if (self != source || !self->_localImage) {
            ((ImageCalls *)self)->copyFrom(source, 1);
        }
        switch (source->_pfmt) {
        case 0:
            switch (format) {
            case 0x10000:
                ((ImageCalls *)self)->setFormat(0x10000);
                self->_bitsInt = 0;
                self->_bitsIdx = 8;
                supported = 1;
                break;
            case 1:
                ((ImageCalls *)self)->setFormat(1);
                self->_bitsInt = 0;
                self->_bitsAlpha = 8;
                break;
            case 0:
                break;
            }
            break;
        case 1:
            switch (format) {
            case 0x10000:
                ((ImageCalls *)self)->setFormat(0x10000);
                self->_bitsAlpha = 0;
                self->_bitsIdx = 8;
                supported = 1;
                break;
            case 0:
                ((ImageCalls *)self)->setFormat(0);
                self->_bitsAlpha = 0;
                self->_bitsInt = 8;
                break;
            case 1:
                break;
            }
            break;
        case 3:
            break;
        case 2:
            switch (format) {
            case 0x10000:
                ((ImageCalls *)self)->setFormat(0x10000);
                self->_bitsInt = 0;
                self->_bitsAlpha = 0;
                self->_bitsIdx = 8;
                supported = 1;
                self->_pz = 1;
                break;
            case 2:
                break;
            }
            break;
        }
    }
    return supported;
}

int Gap__Gfx__igPsx2Image__vfunc_39(G *arg0, int arg1)
{
  int var_s0 = 0;
  int s;
  s = FUN_0015ad50((char *)arg1);
  if (s != 0) {
    if (strcmp(s, &DAT_004df5b8[0]) != 0) {
      if (strcmp(s, &DAT_004df5c0[0]) == 0) goto block_4;
      goto block_22;
    }
block_4:
    {
      igSmartPointer<O0> name((O0 *)FUN_002b9500(igObject_GetAllocator(arg0)));
      FUN_0030b3c0(name.p, arg1);
      LoaderRef loader((O1 *)FUN_00150060(igObject_GetAllocator(arg0)));
      var_s0 = loader.p->v21(name.p, arg0) & 0xFF;
      FUN_00156340((S0_156340 *)arg0, (void **)&PathText(arg1).text);
    }
    return var_s0;
  }
block_22:
  if (s != 0) {
    if (strcmp(s, &DAT_004df5c8[0]) != 0) {
      if (strcmp(s, &DAT_004df5d0[0]) == 0) goto block_26;
    } else {
block_26:
      ReaderRef reader((O2 *)FUN_00150390(igObject_GetAllocator(arg0)));
      var_s0 = reader.p->v31(arg1) & 0xFF;
      if (var_s0 != 0) {
        arg0->v21(reader.p, 1);
      }
    }
  }
  return var_s0;
}

int Gap__Gfx__igPsx2Image__vfunc_40(Img_16e8f0 *p, Strm *s) {
    unsigned int b;
    unsigned int a;
    s->Read(&p->f48, 4, 1);
    s->Read(&p->f8, 4, 1);
    s->Read(&p->f12, 4, 1);
    s->Read(&p->f16, 4, 1);
    s->Read(&p->f20, 4, 1);
    s->Read(&a, 4, 1);
    p->f28 = (a >> 24) & 0xFF;
    p->f32 = (a >> 16) & 0xFF;
    p->f36 = (a >> 8) & 0xFF;
    p->f40 = (unsigned char)a;
    p->f72 = 0;
    p->f64 = 0;
    p->f84 = 0;
    s->Read(&b, 4, 1);
    s->Read(&b, 4, 1);
    p->f52 = FUN_00300db0(p, p->f48, 0x80);
    p->f60 = 1;
    s->Read((void *)p->f52, 1, p->f48);
    s->d24();
    p->f44 = FUN_00159f00(p->f16);
    p->f24 = 0x66;
    FUN_0015a600((T_15a600 *)p);
    return 1;
}

int Gap__Gfx__igPsx2Image__vfunc_41(igPsx2Image *image, Stream *stream) {
    igSmartPointer<ConvertedImage> converted((ConvertedImage *)FUN_0014df70(igObject_GetAllocator(image)));
    int word;
    int masks;
    converted->convert(image, 1);
    FUN_0015a380((S_15a380 *)converted.p);
    word = 0x312A57F2;
    stream->write(&word, 4, 1);
    stream->write(&image->_imageSize, 4, 1);
    stream->write(&image->_px, 4, 1);
    stream->write(&image->_py, 4, 1);
    stream->write(&image->_pz, 4, 1);
    stream->write(&image->_ps, 4, 1);
    masks = (image->_bitsRed << 24) | (image->_bitsGrn << 16) | (image->_bitsBlu << 8) | image->_bitsAlpha;
    stream->write(&masks, 4, 1);
    word = 0;
    stream->write(&word, 4, 1);
    stream->write(&word, 4, 1);
    stream->write(converted->pixels, 1, image->_imageSize);
    stream->close();
    stream->release();
    return 1;
}

int Gap__Gfx__igPsx2Image__vfunc_44(Img_16ece0 *arg0, Strm_16ece0 *arg1) {
    int sp6C;
    int sp68;
    int sp64;
    int sp60;
    int sp5C;
    int sp58;
    int sp54;
    int sp50;
    int sp4C;
    int sp48;
    int temp_s2;
    arg1->v25((char *)arg0 + 48, 4, 1);
    arg1->v25((char *)arg0 + 16, 4, 1);
    arg1->v25((char *)arg0 + 8, 4, 1);
    arg1->v25((char *)arg0 + 12, 4, 1);
    arg0->f20 = 1;
    arg0->f52 = FUN_00300db0(arg0, arg0->f48, 0x80);
    arg0->f60 = 1;
    arg1->v25((void *)arg0->f52, 1, arg0->f48);
    arg1->v24();
    arg0->f44 = FUN_00159f00(arg0->f16);
    FUN_0015a600((T_15a600 *)arg0);
    temp_s2 = arg0->f44;
    FUN_00159320(arg0, temp_s2, arg0->f8, arg0->f12, &sp6C, &sp68, &sp64);
    arg0->f76 = sp64;
    FUN_00159a80(temp_s2, &sp60, &sp5C, &sp58, &sp54, &sp50, &sp4C, &sp48);
    arg0->f64 = sp60;
    arg0->f72 = sp5C;
    arg0->f28 = sp58;
    arg0->f32 = sp54;
    arg0->f36 = sp50;
    arg0->f40 = sp4C;
    arg0->f84 = sp48;
    arg0->f24 = 0x66;
    *(int *)((char *)arg1 + 4) = *(int *)((char *)arg1 + 4) - 1;
    if ((*(int *)((char *)arg1 + 4) & 0x7FFFFF) == 0) {
        igObject_Destroy(arg1);
    }
    return 1;
}

static inline unsigned imageSize(const ImageBuffer *i) { return i->size; }

void Gap__Gfx__igPsx2Image__vfunc_37(ImageBuffer *arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    ((DW4VC_120_1 *)(((char *)(arg0) + 0)))->vX((int)(arg2));
    ((DW4VC_112_1 *)(((char *)(arg0) + 0)))->vX((int)(arg4));
    ((DW4VC_116_1 *)(((char *)(arg0) + 0)))->vX((int)(arg5));
    ((DW4VC_128_1 *)(((char *)(arg0) + 0)))->vX((int)(arg3));
    ((DW4VC_124_0 *)(((char *)(arg0) + 0)))->vX();
    memcpy(arg0->data, arg1, imageSize(arg0));
}

