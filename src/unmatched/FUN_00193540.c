/* 0x00193540 - unpack a packed 32-bit colour into a 4-float vector, selected by pixel format.
 * Evidence: a 7-entry jump table at 0x4e11f0; each case converts the four bytes of arg2 with
 * (float)(byte) / 255.0f (unsigned int-to-float with the sign-bit fix-up) and stores x,y,z,w at
 * +0,+4,+8,+12. The format order below is read from which byte lands in which component:
 * 0 RGBA, 1 ABGR, 2 BGRA, 3 RGB (w=0), 4 BGR (w=0), 6 ARGB; 5 is not handled (no-op). */
typedef struct Color4f { float x, y, z, w; } Color4f;
#define BYTE_TO_UNIT(packed, mask, shift) ((float)(((packed) & (mask)) >> (shift)) / 255.0f)
void FUN_00193540(Color4f *out, unsigned int format, unsigned int packed)
{
    switch (format) {
    case 2:
        out->z = BYTE_TO_UNIT(packed, 0xFF000000, 24);
        out->y = BYTE_TO_UNIT(packed, 0x00FF0000, 16);
        out->x = BYTE_TO_UNIT(packed, 0x0000FF00, 8);
        out->w = BYTE_TO_UNIT(packed, 0x000000FF, 0);
        break;
    case 0:
        out->x = BYTE_TO_UNIT(packed, 0xFF000000, 24);
        out->y = BYTE_TO_UNIT(packed, 0x00FF0000, 16);
        out->z = BYTE_TO_UNIT(packed, 0x0000FF00, 8);
        out->w = BYTE_TO_UNIT(packed, 0x000000FF, 0);
        break;
    case 3:
        out->w = 0.0f;
        out->x = BYTE_TO_UNIT(packed, 0x00FF0000, 16);
        out->y = BYTE_TO_UNIT(packed, 0x0000FF00, 8);
        out->z = BYTE_TO_UNIT(packed, 0x000000FF, 0);
        break;
    case 4:
        out->w = 0.0f;
        out->z = BYTE_TO_UNIT(packed, 0x00FF0000, 16);
        out->y = BYTE_TO_UNIT(packed, 0x0000FF00, 8);
        out->x = BYTE_TO_UNIT(packed, 0x000000FF, 0);
        break;
    case 1:
        out->w = BYTE_TO_UNIT(packed, 0xFF000000, 24);
        out->z = BYTE_TO_UNIT(packed, 0x00FF0000, 16);
        out->y = BYTE_TO_UNIT(packed, 0x0000FF00, 8);
        out->x = BYTE_TO_UNIT(packed, 0x000000FF, 0);
        break;
    case 6:
        out->w = BYTE_TO_UNIT(packed, 0xFF000000, 24);
        out->x = BYTE_TO_UNIT(packed, 0x00FF0000, 16);
        out->y = BYTE_TO_UNIT(packed, 0x0000FF00, 8);
        out->z = BYTE_TO_UNIT(packed, 0x000000FF, 0);
        break;
    default:
        break;
    }
}
