extern "C" {
void igObject_Destroy(void *);
void *memset(void *, int, unsigned int);
int FUN_001f6f50(...);
int FUN_00204840(int index);
}

class StatAllocator {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();
    virtual void *v52(int);
    virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
    virtual int vX(void *);
};

extern "C" StatAllocator *FUN_00165d00(...);

class igPsx2VisualContextSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
    virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
    virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71();
    virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79();
    virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87();
    virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95();
    virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103();
    virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111();
    virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119();
    virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127();
    virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135();
    virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143();
    virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151();
    virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159();
    virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167();
    virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175();
    virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183();
    virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191();
    virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199();
    virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void d206(); virtual void d207();
    virtual void d208(); virtual void d209(); virtual void d210(); virtual void d211(); virtual void d212(); virtual void d213(); virtual void d214(); virtual void d215();
    virtual void d216(); virtual void d217(); virtual void d218(); virtual void d219(); virtual void d220(); virtual void d221(); virtual void d222(); virtual void d223();
    virtual void d224(); virtual void d225(); virtual void d226(); virtual void d227(); virtual void d228(); virtual void d229(); virtual void d230(); virtual void d231();
    virtual void d232(); virtual void d233(); virtual void d234(); virtual void d235(); virtual void d236(); virtual void d237(); virtual void d238(); virtual void d239();
    virtual void d240(); virtual void d241(); virtual void d242(); virtual void d243(); virtual void d244(); virtual void d245(); virtual void d246(); virtual void d247();
    virtual void d248(); virtual void d249(); virtual void d250(); virtual void d251(); virtual void d252(); virtual void d253(); virtual void d254();
    virtual void vfunc_255();
};

extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_256(igPsx2VisualContextSlots *self)
{
    self->vfunc_255();
}

extern "C" bool Gap__Gfx__igPsx2VisualContext__vfunc_257(void *context, unsigned int capability);

bool Gap__Gfx__igPsx2VisualContext__vfunc_257(void *context, unsigned int capability) {
    bool supported = false;
    switch (capability) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 16:
    case 17:
    case 20:
    case 23:
    case 24:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    case 69:
    case 70:
    case 71:
    case 72:
    case 73:
    case 74:
    case 75:
    case 76:
    case 77:
    case 78:
    case 79:
    case 80:
    case 81:
    case 82:
    case 83:
    case 84:
    case 85:
    case 86:
    case 87:
    case 88:
    case 89:
    case 90:
    case 91:
    case 92:
    case 93:
    case 94:
    case 95:
    case 96:
    case 97:
    case 98:
    case 99:
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:
    case 107:
    case 108:
    case 109:
    case 110:
    case 111:
    case 112:
    case 113:
    case 114:
    case 115:
    case 116:
    case 117:
    case 118:
    case 119:
    case 120:
    case 121:
    case 122:
    case 123:
    case 124:
    case 125:
    case 126:
    case 127:
    case 128:
    case 129:
    case 130:
    case 131:
    case 132:
    case 133:
    case 134:
    case 135:
    case 136:
    case 137:
    case 138:
    case 139:
    case 140:
    case 141:
    case 142:
    case 143:
    case 144:
    case 145:
    case 146:
    case 147:
    case 148:
    case 149:
    case 150:
    case 151:
    case 152:
    case 153:
    case 154:
    case 155:
    case 156:
    case 157:
    case 158:
    case 159:
    case 160:
    case 161:
    case 162:
    case 163:
    case 164:
    case 165:
    case 166:
    case 167:
    case 168:
    case 169:
    case 170:
    case 171:
    case 172:
    case 173:
    case 174:
    case 175:
    case 176:
    case 177:
    case 178:
    case 179:
    case 180:
    case 181:
    case 182:
    case 183:
    case 184:
    case 185:
    case 186:
    case 187:
    case 188:
    case 190:
        supported = true;
        break;
    }
    return supported;
}

extern "C" {
extern unsigned char DAT_00554b70;
extern unsigned char DAT_00554b74;
}

struct StatNodeView {
    char pad0[8];
    int f8;
    char pad12[4];
    unsigned char f16;
    char pad17[935];
    StatNodeView *next;
};

class igPsx2VisualContextStats {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
    virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
    virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71();
    virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79();
    virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87();
    virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95();
    virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103();
    virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111();
    virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119();
    virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127();
    virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135();
    virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143();
    virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151();
    virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159();
    virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167();
    virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175();
    virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183();
    virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191();
    virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199();
    virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void d206(); virtual void d207();
    virtual void d208(); virtual void d209(); virtual void d210(); virtual void d211(); virtual void d212(); virtual void d213(); virtual void d214(); virtual void d215();
    virtual void d216(); virtual void d217(); virtual void d218(); virtual void d219(); virtual void d220(); virtual void d221(); virtual void d222(); virtual void d223();
    virtual void d224(); virtual void d225(); virtual void d226(); virtual void d227(); virtual void d228(); virtual void d229(); virtual void d230(); virtual void d231();
    virtual void d232(); virtual void d233(); virtual void d234(); virtual void d235(); virtual void d236(); virtual void d237(); virtual void d238(); virtual void d239();
    virtual void d240(); virtual void d241(); virtual void d242(); virtual void d243(); virtual void d244(); virtual void d245(); virtual void d246(); virtual void d247();
    virtual void d248(); virtual void d249(); virtual void d250(); virtual void d251(); virtual void d252(); virtual void d253(); virtual void d254();  

    virtual bool supports(unsigned int capability);
    char pad4[1548];
    StatNodeView *nodes;
};

extern "C" bool Gap__Gfx__igPsx2VisualContext__vfunc_255(igPsx2VisualContextStats *self, unsigned int capability, unsigned char enabled)
{
    StatNodeView *node;

    bool supported = self->supports(capability);
    if (supported) {
        if (capability == 31) {
            DAT_00554b70 = enabled;
        }
        if (capability == 34) {
            DAT_00554b74 = enabled;
        }
        if (capability == 31) {
        } else if (capability == 34) {
        } else if (capability == 57) {
            for (node = self->nodes; node != 0; node = node->next) {
                node->f16 = 1;
                node->f8 = 0;
            }
        }
    }
    return supported;
}

extern "C" {
extern int DAT_0048ac30[4];
extern long long DAT_00560b50[4];
extern long long DAT_00560b58[4];
extern long long DAT_00560b60[4];
extern long long DAT_00560b68[4];
extern long long DAT_00560b70[4];
extern long long DAT_00560b78[4];
extern long long DAT_00560b80[4];
extern long long DAT_00560b88[4];
extern long long DAT_00560b90[4];
extern long long DAT_00560b98[4];
extern long long DAT_00560ba0[4];
extern long long DAT_00560ba8[4];
extern long long DAT_00560bb0[4];
extern long long DAT_00560bb8[4];
extern long long DAT_00560bc0[4];
extern long long DAT_00560bc8[4];
extern long long DAT_00560bd0[4];
extern long long DAT_00560bd8[4];
extern long long DAT_00560be0[4];
extern long long DAT_00560be8[4];
extern long long DAT_00560bf0[4];
extern long long DAT_00560bf8[4];
extern long long DAT_00560c00[4];
extern long long DAT_00560c08[4];
extern long long DAT_00560c10[4];
extern long long DAT_00560c18[4];
extern long long DAT_00560c20[4];
extern long long DAT_00560c28[4];
extern long long DAT_00560c30[4];
extern long long DAT_00560c38[4];
extern long long DAT_00560c40[4];
extern long long DAT_00560c48[4];
extern long long DAT_00560c50[4];
extern long long DAT_00560c58[4];
extern long long DAT_00560c60[4];
extern long long DAT_00560c68[4];
extern long long DAT_00560c70[4];
extern long long DAT_00560c78[4];
extern long long DAT_00560c80[4];
extern long long DAT_00560c88[4];
extern long long DAT_00560c90[4];
extern long long DAT_00560c98[4];
extern long long DAT_00560ca0[4];
extern long long DAT_00560ca8[4];
extern long long DAT_00560cb0[4];
extern long long DAT_00560cb8[4];
extern long long DAT_00560cc0[4];
extern long long DAT_00560cc8[4];
extern long long DAT_00560cd0[4];
extern long long DAT_00560cd8[4];
extern long long DAT_00560ce0[4];
extern long long DAT_00560ce8[4];
extern long long DAT_00560cf0[4];
extern long long DAT_00560cf8[4];
extern long long DAT_00560d00[4];
extern long long DAT_00560d08[4];
extern long long DAT_00560d10[4];
extern long long DAT_00560d20[4];
extern long long DAT_00560d28[4];
extern long long DAT_00560d30[4];
extern long long DAT_00560d38[4];
extern long long DAT_00560d40[4];
extern long long DAT_00560d48[4];
extern long long DAT_00560d50[4];
extern long long DAT_00560d58[4];
extern long long DAT_00560d60[4];
extern long long DAT_00560d68[4];
extern long long DAT_00560d70[4];
extern long long DAT_00560d78[4];
extern long long DAT_00560d80[4];
extern long long DAT_00560d88[4];
extern long long DAT_00560d90[4];
extern long long DAT_00560d98[4];
extern long long DAT_00560da0[4];
extern long long DAT_00560da8[4];
extern long long DAT_00560db0[4];
extern long long DAT_00560db8[4];
extern long long DAT_00560dc0[4];
extern long long DAT_00560dc8[4];
extern long long DAT_00560dd0[4];
extern long long DAT_00560dd8[4];
extern long long DAT_00560de0[4];
extern long long DAT_00560de8[4];
extern long long DAT_00560df0[4];
extern long long DAT_00560df8[4];
extern long long DAT_00560e00[4];
extern long long DAT_00560e08[4];
extern long long DAT_00560e10[4];
extern long long DAT_00560e18[4];
extern long long DAT_00560e20[4];
extern long long DAT_00560e28[4];
extern long long DAT_00560e30[4];
extern long long DAT_00560e38[4];
extern long long DAT_00560e40[4];
extern long long DAT_00560e48[4];
extern long long DAT_00560e50[4];
extern long long DAT_00560e58[4];
extern long long DAT_00560e60[4];
extern long long DAT_00560e68[4];
extern long long DAT_00560e70[4];
extern long long DAT_00560e78[4];
extern long long DAT_00560e80[4];
extern long long DAT_00560e88[4];
extern long long DAT_00560e90[4];
extern long long DAT_00560e98[4];
extern long long DAT_00560ea0[4];
extern long long DAT_00560ea8[4];
extern long long DAT_00560eb0[4];
extern long long DAT_00560eb8[4];
extern long long DAT_00560ec0[4];
extern long long DAT_00560ec8[4];
extern long long DAT_00560ed0[4];
extern long long DAT_00560ed8[4];
extern long long DAT_00560ee0[4];
extern long long DAT_00560ee8[4];
extern long long DAT_00560ef0[4];
}
extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_258(void) {
    if (DAT_0048ac30[0] != 0) {
        memset(&DAT_00560d20[0], 0, 0x1C8);
        DAT_00560ee8[0] = 0;
        DAT_0048ac30[0] = 0;
    }
    DAT_00560ef0[0] = DAT_00560ee8[0];
    DAT_00560b50[0] = DAT_00560d20[0];
    DAT_00560b58[0] = DAT_00560d28[0];
    DAT_00560b60[0] = DAT_00560d30[0];
    DAT_00560b68[0] = DAT_00560d38[0];
    DAT_00560b70[0] = DAT_00560d40[0];
    DAT_00560b78[0] = DAT_00560d48[0];
    DAT_00560b80[0] = DAT_00560d50[0];
    DAT_00560b88[0] = DAT_00560d58[0];
    DAT_00560b90[0] = DAT_00560d60[0];
    DAT_00560b98[0] = DAT_00560d68[0];
    DAT_00560ba0[0] = DAT_00560d70[0];
    DAT_00560ba8[0] = DAT_00560d78[0];
    DAT_00560bb0[0] = DAT_00560d80[0];
    DAT_00560bb8[0] = DAT_00560d88[0];
    DAT_00560bc0[0] = DAT_00560d90[0];
    DAT_00560bc8[0] = DAT_00560d98[0];
    DAT_00560bd0[0] = DAT_00560da0[0];
    DAT_00560bd8[0] = DAT_00560da8[0];
    DAT_00560be0[0] = DAT_00560db0[0];
    DAT_00560be8[0] = DAT_00560db8[0];
    DAT_00560bf0[0] = DAT_00560dc0[0];
    DAT_00560bf8[0] = DAT_00560dc8[0];
    DAT_00560c00[0] = DAT_00560dd0[0];
    DAT_00560c08[0] = DAT_00560dd8[0];
    DAT_00560c10[0] = DAT_00560de0[0];
    DAT_00560c18[0] = DAT_00560de8[0];
    DAT_00560c20[0] = DAT_00560df0[0];
    DAT_00560c28[0] = DAT_00560df8[0];
    DAT_00560c30[0] = DAT_00560e00[0];
    DAT_00560c38[0] = DAT_00560e08[0];
    DAT_00560c40[0] = DAT_00560e10[0];
    DAT_00560c48[0] = DAT_00560e18[0];
    DAT_00560c50[0] = DAT_00560e20[0];
    DAT_00560c58[0] = DAT_00560e28[0];
    DAT_00560c60[0] = DAT_00560e30[0];
    DAT_00560c68[0] = DAT_00560e38[0];
    DAT_00560c70[0] = DAT_00560e40[0];
    DAT_00560c78[0] = DAT_00560e48[0];
    DAT_00560c80[0] = DAT_00560e50[0];
    DAT_00560c88[0] = DAT_00560e58[0];
    DAT_00560c90[0] = DAT_00560e60[0];
    DAT_00560c98[0] = DAT_00560e68[0];
    DAT_00560ca0[0] = DAT_00560e70[0];
    DAT_00560ca8[0] = DAT_00560e78[0];
    DAT_00560cb0[0] = DAT_00560e80[0];
    DAT_00560cb8[0] = DAT_00560e88[0];
    DAT_00560cc0[0] = DAT_00560e90[0];
    DAT_00560cc8[0] = DAT_00560e98[0];
    DAT_00560cd0[0] = DAT_00560ea0[0];
    DAT_00560cd8[0] = DAT_00560ea8[0];
    DAT_00560ce0[0] = DAT_00560eb0[0];
    DAT_00560ce8[0] = DAT_00560eb8[0];
    DAT_00560cf0[0] = DAT_00560ec0[0];
    DAT_00560cf8[0] = DAT_00560ec8[0];
    DAT_00560d00[0] = DAT_00560ed0[0];
    DAT_00560d08[0] = DAT_00560ed8[0];
    DAT_00560d10[0] = DAT_00560ee0[0];
    FUN_001f6f50(&DAT_00560d20[0], DAT_00560ed0[0], DAT_00560ec8[0], DAT_00560ea0[0]);
}

/* Reads one GS/frame statistic as a per-frame rate. The game keeps the current statistics block
 * (58 long long, 0x1d0 bytes) and the block taken at the last reset. `id` selects the number:
 * elapsed = current[5] - previous[5] (frame-length counter), nothing is computed when it is not
 * positive; most ids return (current[k] - previous[k]) / elapsed, some scaled to milliseconds (x
 * 1000 / 9216000 ticks per second) or by 16; ids 44..56 return a small-integer query
 * FUN_00204840(n); ids 58, 59, 16, 17, 20, 24 consume a free-running accumulator and clear it; ids
 * 60..186 consume the per-id event counters (unsigned) and clear them; ids 42 and 43 take a fresh
 * snapshot and return one raw field of it. The result is -1.0f for an unknown id. */
typedef struct GsStatBlock { long long c[58]; } GsStatBlock;

extern "C" {
extern GsStatBlock g_gsStatCurrent;
extern GsStatBlock g_gsStatPrevious;
extern unsigned int g_gsEventCount[];
extern long long g_gsAccumulator_005608a0[4];
extern long long g_gsAccumulator_00560660[4];
extern long long g_gsAccumulator_00560668[4];
extern long long g_gsRawCounter[4];
}

#define CUR g_gsStatCurrent.c
#define PREV g_gsStatPrevious.c
#define DELTA(k) ((float)(CUR[k] - PREV[k]))
#define TICKS_PER_SECOND 9216000

extern "C" float Gap__Gfx__igPsx2VisualContext__vfunc_259(void *unused, int id) {
    float result = -1.0f;
    float elapsed = DELTA(5);
    if (!(elapsed <= 0.0f)) {
        switch (id) {
        case 4: result = elapsed; break;
        case 5: result = DELTA(6); break;
        case 0: result = DELTA(0) / elapsed; break;
        case 1: result = DELTA(1) / elapsed; break;
        case 6: result = (1000.0f * (DELTA(36) / (float)TICKS_PER_SECOND)) / elapsed; break;
        case 7: result = 1000.0f * ((float)CUR[37] / (float)TICKS_PER_SECOND); break;
        case 8: result = 1000.0f * ((float)CUR[38] / (float)TICKS_PER_SECOND); break;
        case 2: result = DELTA(2) / elapsed; break;
        case 36: result = DELTA(26) / elapsed; break;
        case 37: result = DELTA(25) / elapsed; break;
        case 3: result = (float)g_gsRawCounter[0]; break;
        case 30: result = (1000.0f * (DELTA(30) / (float)TICKS_PER_SECOND)) / elapsed; break;
        case 31: result = (16.0f * DELTA(29)) / elapsed; break;
        case 32: result = DELTA(27) / elapsed; break;
        case 33: result = (1000.0f * (DELTA(34) / (float)TICKS_PER_SECOND)) / elapsed; break;
        case 34: result = (16.0f * DELTA(33)) / elapsed; break;
        case 35: result = DELTA(31) / elapsed; break;
        case 39: result = 1000.0f * ((DELTA(43) / elapsed) / (float)TICKS_PER_SECOND); break;
        case 38: {
            float sum = DELTA(39) / elapsed;
            sum = sum + DELTA(40) / elapsed;
            sum = sum + DELTA(41) / elapsed;
            sum = sum + DELTA(42) / elapsed;
            sum = sum + DELTA(44) / elapsed;
            sum = sum + DELTA(45) / elapsed;
            sum = sum + DELTA(46) / elapsed;
            result = 1000.0f * (sum / (float)TICKS_PER_SECOND);
            break;
        }
        case 40: result = DELTA(24) / elapsed; break;
        case 41: result = DELTA(7) / elapsed; break;
        case 44: result = (float)FUN_00204840(3); break;
        case 45: result = (float)FUN_00204840(7); break;
        case 46: result = (float)FUN_00204840(8); break;
        case 47: result = (float)FUN_00204840(9); break;
        case 48: result = (float)FUN_00204840(10); break;
        case 49: result = (float)FUN_00204840(0); break;
        case 50: result = (float)FUN_00204840(1); break;
        case 51: result = (float)FUN_00204840(2); break;
        case 52: result = (float)FUN_00204840(4); break;
        case 53: result = (float)FUN_00204840(5); break;
        case 54: result = (float)FUN_00204840(6); break;
        case 55: result = (float)FUN_00204840(11); break;
        case 56: result = (float)FUN_00204840(12); break;
        case 58: result = (float)g_gsAccumulator_00560668[0] / elapsed; g_gsAccumulator_00560668[0] = 0; break;
        case 59: result = (float)g_gsAccumulator_00560660[0] / elapsed; g_gsAccumulator_00560660[0] = 0; break;
        case 16: result = (float)g_gsAccumulator_005608a0[0] / elapsed; g_gsAccumulator_005608a0[0] = 0; break;
        case 17: result = (float)g_gsAccumulator_005608a0[0] / elapsed; g_gsAccumulator_005608a0[0] = 0; break;
        case 20: result = (float)g_gsAccumulator_005608a0[0] / elapsed; g_gsAccumulator_005608a0[0] = 0; break;
        case 24: result = (float)g_gsAccumulator_005608a0[0] / elapsed; g_gsAccumulator_005608a0[0] = 0; break;
        case 187: result = DELTA(48) / elapsed; break;
        case 188: result = DELTA(49) / elapsed; break;
        case 190: result = DELTA(56) / elapsed; break;
        }
        if (id >= 60 && id < 187) {
            result = (float)g_gsEventCount[id] / elapsed;
            g_gsEventCount[id] = 0;
        }
    }
    if (result == -1.0f) {
        if (id == 42) {
            GsStatBlock snapshot;
            FUN_001f6f50(&snapshot);
            result = (float)snapshot.c[3];
        } else if (id == 43) {
            GsStatBlock snapshot;
            FUN_001f6f50(&snapshot);
            result = (float)snapshot.c[4];
        }
    }
    return result;
}

extern "C" int DAT_005608c0[0x7E];
extern "C" void FUN_001788a0(void *arg0) {
    int i;
    *(int *)((char *)(arg0) + 1552) = 0;
    i = 0;
    do {
        DAT_005608c0[i] = 0;
    } while (++i < 0x7E);
}

struct StatRefObject { char pad4[4]; int refs; };
struct StatNode88 { char pad12[12]; StatRefObject *f0c; char pad16[936]; StatNode88 *f3b8; };
struct StatContext88 { char pad[1552]; StatNode88 *f610; };
extern "C" {
void FUN_001788e0(StatContext88 *arg0);
}
void FUN_001788e0(StatContext88 *arg0) {
    StatNode88 *temp_s1;
    StatNode88 *temp_s0;
    StatRefObject *temp_a0;

    temp_s1 = arg0->f610;
    if (temp_s1 != 0) {
        do {
            temp_a0 = temp_s1->f0c;
            temp_s0 = temp_s1->f3b8;
            temp_a0->refs = temp_a0->refs - 1;
            if ((temp_a0->refs & 0x7fffff) == 0) {
                igObject_Destroy(temp_a0);
            }
            FUN_00165d00(arg0)->vX(temp_s1);
        } while (temp_s0 != 0);
    }
    arg0->f610 = 0;
}

struct O { int p0; int refs; int f8; int f12; };
extern "C" struct Ref { O *p; Ref(O *q) : p(q) {} ~Ref() { O *q = p; if (q != 0) { q->refs = q->refs - 1; if (((unsigned long long)(long long)q->refs & 0x7fffffULL) == 0) igObject_Destroy(q); } } operator O *() { return p; } O *operator->() { return p; } };
struct StatNode { int f0; int f4; int f8; O *f12; char f16; char pad[935]; StatNode *f952; };
struct StatContext { char pad[1552]; StatNode *f1552; };
struct G { char pad[56]; int f56; };
extern "C" {
O *FUN_002b9500(StatAllocator *);
void FUN_0030b3c0(O *, void *);
void FUN_0030b720(O *, int, void *);
void FUN_0030b460(O *, int, int, int);
int FUN_00306360(int, int, int);
int thunk_FUN_003065f0(int, int, void *, void *, int, int);
int thunk_FUN_00306770(int, int, void *, void *, void *, int);
extern int DAT_004c22f0[4];
extern int DAT_004dc870[4];
extern int DAT_004de6a8[4];
extern int DAT_004e07b0[4];
extern int DAT_004e07c8[4];
extern int DAT_004e07d8[4];
extern int DAT_004e07e8[4];
extern G *DAT_00586dc8[4];
void FUN_00179e00(StatContext *arg0);
}
void FUN_00179e00(StatContext *arg0) {
    int s3;
    int s2;
    int idx;
    StatNode *n;
    int a1;
    Ref sp6C(FUN_002b9500(FUN_00165d00(arg0)));
    Ref sp68(FUN_002b9500(FUN_00165d00(arg0)));
    s3 = DAT_00586dc8[0]->f56;
    s2 = 0;
    FUN_0030b3c0(sp6C, DAT_004e07b0);
    FUN_0030b720(sp68, 0, DAT_004de6a8);
    { int y = sp68->f12; int x = sp6C->f12;
    a1 = sp68->f8;
    if (a1 == 0) a1 = DAT_004c22f0[0];
    FUN_0030b460(sp6C, a1, x, y); }
    while ((idx = FUN_00306360(s3, sp6C->f8 == 0 ? DAT_004c22f0[0] : sp6C->f8, 0)) != -1) {
        n = (StatNode *)FUN_00165d00(arg0)->v52(960);
        if (n == 0) break;
        n->f16 = 1;
        n->f0 = s2;
        thunk_FUN_003065f0(s3, idx, DAT_004e07c8, &n->f4, 1, 0);
        thunk_FUN_003065f0(s3, idx, DAT_004e07d8, &n->f8, -1 - n->f4, 0);
        n->f12 = FUN_002b9500(FUN_00165d00(arg0));
        thunk_FUN_00306770(s3, idx, DAT_004e07e8, &n->f12, DAT_004dc870, 0);
        s2 += 1;
        n->f952 = arg0->f1552;
        arg0->f1552 = n;
        FUN_0030b720(sp68, s2, DAT_004de6a8);
        FUN_0030b3c0(sp6C, DAT_004e07b0);
        { int y = sp68->f12; int x = sp6C->f12;
        a1 = sp68->f8;
        if (a1 == 0) a1 = DAT_004c22f0[0];
        FUN_0030b460(sp6C, a1, x, y); }
    }
}
