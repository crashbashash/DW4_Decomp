#include "dw4/reflected.h"
extern "C" {

typedef struct PropertyRecord {
    char pad[12];
    int value;
} PropertyRecord;
PropertyRecord *igProperty_GetRecord(int, const char *);
void beMessenger_SelectGroup(int, const char *);
void beMessenger_AppendInt(int, int);
void beMessenger_AppendString(int, const char *);
void beMessenger_AppendVec3(int, int *);
void beMessenger_DispatchSelected(int, const char *);
int beMessenger_GetObject(int, int);
void sprintf(char *, const char *, int);
extern const char DAT_0051c500[]; /* GAMERAM */
extern const char DAT_0051c508[]; /* GETPLAYER */
extern const char DAT_0051c620[]; /* STWINFONT14 */
extern const char DAT_0051c650[]; /* STWINFONT19 */
extern const char DAT_0051c6d8[]; /* ---- */
extern const char DAT_0051c6e0[]; /* %d */
extern const char DAT_0051c6e8[]; /* TEXTCTL */
extern const char DAT_0051c6f0[]; /* TEXTSET */
extern const char DAT_0051c6f8[]; /* COLOR */
extern const char DAT_0051c700[]; /* DEFAULTCOLOR */

typedef struct NameTab { const char *a[7]; } NameTab;
typedef struct LimitTab { int a[7]; } LimitTab;
extern const NameTab DAT_004cfad0;
extern const LimitTab DAT_004cfaf0;
extern const NameTab DAT_004cfb10;

void beNDMWShopSelect11_RefreshStatCosts(beNDMWShopSelect11 *self)
{
    int col[3];
    char buf[16];
    NameTab props;
    LimitTab limits;
    NameTab fonts;
    int *c1;
    int *c2;
    int obj;
    int i;
    int cur;
    const char **pp;
    int *pl;
    const char **pf;

    beMessenger_SelectGroup(self->_messenger, DAT_0051c500);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, DAT_0051c508);
    obj = beMessenger_GetObject(self->_messenger, 0);
    props = DAT_004cfad0;
    limits = DAT_004cfaf0;
    fonts = DAT_004cfb10;
    pp = props.a;
    pl = limits.a;
    pf = fonts.a;
    i = 0;
    c1 = &col[1];
    c2 = &col[2];
    do {
        cur = igProperty_GetRecord(obj, *pp)->value;
        {
        int r = (cur - 45) % 5;
        int q = (cur - 45 - r) / 5 + (r ? 1 : 0);
        if (q > 400)
            q = 400;
        else if (q < 0)
            q = 1;
        else
            q = (int)q;
        if (cur >= *pl)
            sprintf(buf, DAT_0051c6d8, q);
        else
            sprintf(buf, DAT_0051c6e0, q);
        }
        beMessenger_SelectGroup(self->_messenger, DAT_0051c6e8);
        beMessenger_AppendString(self->_messenger, DAT_0051c650);
        beMessenger_AppendString(self->_messenger, *pf);
        beMessenger_AppendString(self->_messenger, buf);
        beMessenger_DispatchSelected(self->_messenger, DAT_0051c6f0);
        beMessenger_SelectGroup(self->_messenger, DAT_0051c6e8);
        beMessenger_AppendString(self->_messenger, DAT_0051c620);
        beMessenger_AppendString(self->_messenger, *pf);
        if (cur >= *pl) {
            col[0] = 0x3F666666;
            *c1 = 0x3ECCCCCD;
            *c2 = 0x3E4CCCCD;
            beMessenger_AppendVec3(self->_messenger, col);
            beMessenger_DispatchSelected(self->_messenger, DAT_0051c6f8);
        } else {
            beMessenger_DispatchSelected(self->_messenger, DAT_0051c700);
        }
        i++; pp++; pl++; pf++;
    } while (i < 7);
}
}
