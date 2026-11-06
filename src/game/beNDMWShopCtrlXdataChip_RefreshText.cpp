/* 0x0043c7f0..0x0043cc20 — beNDMWShopCtrlXdataChip::RefreshText.  Finding #923.
 *
 * Redraws the chip shop's text windows through the messenger (TEXTCTL group,
 * TEXTSET / SWITCH messages).  `refreshRows`: for each of the 12 rows of the
 * current page, show the chip's NAME and its NEXTX value (printed with "%d", or
 * "----" when it is not positive) and switch the row on, or switch it off when
 * the row has no chip; then print the current and last page numbers.
 * `refreshDescription`: show the TXT description of the chip under the
 * cursor (index _nowPage * 12 + _retCode) and switch its window on.
 *
 * All messages, field reads, index decisions and formatting are C. Original
 * joins/NOPs and three address-high instructions preserve retail scheduling.
 * Register-binding dmove pseudos coalesce without adding instructions.
 * Explicit target words: two joins, eleven NOPs, three LUIs (64 bytes);
 * the remaining 1,008 bytes are generated from C. This is an ABI/codegen
 * projection, not a claim about original declaration or source spelling.
 */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
#define CHIPS_PER_PAGE 12  /* rows shown per page: the row loop bound and the page stride */
/* Unspecified argument lists retain retail call setup. Observed result widths
 * are explicit; these are call-site projections, not recovered callee types. */
int sprintf(char *, const char *, ...);  /* sprintf(dest, format, ...) (docs/engine/material-contact.md) */
long long FUN_00236f80(int, int);
long long beNDMWItemBase_GetRecordInt(int, long long, char *);
char *beNDMWItemBase_GetRecordString(int, long long, char *);
void beMessenger_AppendString(int, char *); /* matching construct: a char * (not const char *) parameter keeps the retail argument load order */
void beMessenger_DispatchSelected(int, char *);
void beMessenger_SelectGroup(int, char *);
extern char *g_fontNames[];   /* "font000".."font011" row fonts, then font000, font030 */
extern char *g_fontName1[];   /* the same table at +4: "font001" */
extern char TEXTCTL_3[];
extern char STWINFONT14[];
extern char percent_d[];
extern char STWINFONT29[];
extern char DISPOFF[];
extern char SWITCH_2[];
extern char NAME_2[];
extern char STWINFONT17[];
extern char TXT[];
extern char TEXTSET[];
extern char DISPON[];
extern char STWINFONT30[];
extern char NEXTX[];
extern int g_beNDMWStatus_metaObject[];

// clang-format off
void beNDMWShopCtrlXdataChip_RefreshText(beNDMWShopCtrlXdataChip *self, long long refreshRows,
                                         long long refreshDescription) {
    int pageValue;
    const char *textGroup;
    char page[4];
    char priceText[28];
    int selectedIndex;
    int selectedItem;
    int item;
    long long nextX;
    long long status;
    int index;
    int row;
    char **font;
    char *description;
    char *name;
    char *visibility;

    /* Status is captured even when neither refresh flag is set. */
    status = FUN_00236f80(self->_insight, g_beNDMWStatus_metaObject[0]);
    asm {
        dmove s4,status
    }
    if (refreshRows != 0) {
        row = 0;

        font = (char **)(&g_fontNames[0]);
        asm {
            dmove s3,row
        }
        asm {
            dmove s0,font
            nop
        }
        do {
            asm {
                .set noreorder
            }
            if ((index = (int)((unsigned)row + (unsigned)self->_nowPage * CHIPS_PER_PAGE)) <
                ((beNDMWItemBaseList *)self->_itemBaseList)->_count) {
                asm {
                    nop
                    .set reorder
                }
                item = *(int *)(((beNDMWItemBaseList *)self->_itemBaseList)->_data + (index * 4));
                asm {
                    dmove s1,item
                }
                if (item != 0) {
                    name = (char *)(beNDMWItemBase_GetRecordString(item, status, &NAME_2[0]));

                    nextX = beNDMWItemBase_GetRecordInt(item, status, &NEXTX[0]);
                    beMessenger_SelectGroup(self->_messenger, &TEXTCTL_3[0]);
                    asm {
                        dmove s2,name
                    }
                    beMessenger_AppendString(self->_messenger, &STWINFONT14[0]);
                    beMessenger_AppendString(self->_messenger, *font);
                    beMessenger_AppendString(self->_messenger, name);
                    beMessenger_DispatchSelected(self->_messenger, &TEXTSET[0]);
                    if (nextX > 0) {
                        sprintf(priceText, &percent_d[0], nextX);
                        asm {
                            .set noreorder
                            b price_done
                            nop
                            nop
                            .set reorder
                        }
                    } else {
                        /* Copy exactly five bytes of "----", preserving load/store
                         * order. High/low halves identify 0x51bdc0. */
                        const char *src;
                        char *dst;
                        float value;
                        unsigned char tail;
                        asm {
                            lui v0,0x52
                        }

                        asm {
                            dmove src,v0
                        }
                        src -= 16960;
                        dst = priceText;
                        asm {
                            dmove v0,src
                            dmove v1,dst
                        }
                        value = *(volatile float *)src;
                        tail = *((volatile unsigned char *)src + 4);
                        *(volatile float *)dst = value;
                        *((volatile unsigned char *)dst + 4) = tail;
                        asm {
                            nop
                        }
                    }
                price_done: /* Keep each font/messenger read live across callbacks. */
                    beMessenger_SelectGroup(self->_messenger, &TEXTCTL_3[0]);
                    beMessenger_AppendString(self->_messenger, &STWINFONT17[0]);
                    beMessenger_AppendString(self->_messenger, *font);
                    beMessenger_AppendString(self->_messenger, priceText);
                    beMessenger_DispatchSelected(self->_messenger, &TEXTSET[0]);
                    visibility = (char *)(&DISPON[0]);
                    asm {
                        b row_visibility
                        .set noreorder
                        nop
                        .set reorder
                    }
                }
            }
            else {
                visibility = (char *)(&DISPOFF[0]);
            row_visibility:
                beMessenger_SelectGroup(self->_messenger, &TEXTCTL_3[0]);
                beMessenger_AppendString(self->_messenger, &STWINFONT14[0]);
                beMessenger_AppendString(self->_messenger, *font);
                beMessenger_AppendString(self->_messenger, visibility);
                beMessenger_DispatchSelected(self->_messenger, &SWITCH_2[0]);
                beMessenger_SelectGroup(self->_messenger, &TEXTCTL_3[0]);
                beMessenger_AppendString(self->_messenger, &STWINFONT17[0]);
                beMessenger_AppendString(self->_messenger, *font);
                beMessenger_AppendString(self->_messenger, visibility);
                beMessenger_DispatchSelected(self->_messenger, &SWITCH_2[0]);
            }
            row += 1;
            font += 1;
        } while (row < CHIPS_PER_PAGE);
        page[1] = 0;
        /* Word-wide page reads; page text remains a single wrapped byte.
         * 0x520000-19520 = TEXTCTL at0x51b3c0. */
        asm {
            lui a1,0x52
        }

        asm {
            dmove textGroup,a1
        }
        pageValue = (int)((unsigned)self->_nowPage + '1');
        asm {
            dmove pageValue,pageValue
        }

        page[0] = pageValue;
        beMessenger_SelectGroup(self->_messenger, (char *)(textGroup - 19520));
        beMessenger_AppendString(self->_messenger, &STWINFONT30[0]);
        beMessenger_AppendString(self->_messenger, g_fontNames[0]);
        beMessenger_AppendString(self->_messenger, page);
        beMessenger_DispatchSelected(self->_messenger, &TEXTSET[0]);
        pageValue = self->_maxPage;
        asm {
            lui a1,0x52
            dmove textGroup,a1
            dmove pageValue,pageValue
        }
        page[0] = pageValue + '0';
        beMessenger_SelectGroup(self->_messenger, (char *)(textGroup - 19520));
        beMessenger_AppendString(self->_messenger, &STWINFONT30[0]);
        beMessenger_AppendString(self->_messenger, g_fontName1[0]);
        beMessenger_AppendString(self->_messenger, page);
        beMessenger_DispatchSelected(self->_messenger, &TEXTSET[0]);
        asm {
            nop
        }
    }
    asm {
        .set noreorder
    }
    if (refreshDescription != 0) {
        asm {
            nop
            .set reorder
            .set noreorder
        }
        /* Grouped unsigned subtraction keeps word wrapping and retail ADDU order. */
        if ((selectedIndex =
                 (int)((unsigned)self->_nowPage * CHIPS_PER_PAGE - (0U - (unsigned)self->_retCode))) <
            ((beNDMWItemBaseList *)self->_itemBaseList)->_count) {
            asm {
                nop
                .set reorder
            }

            asm {
                .set noreorder
            }
            selectedItem = *(int *)(((beNDMWItemBaseList *)self->_itemBaseList)->_data + (selectedIndex * 4));
            if (selectedItem != 0) {
                asm {
                    nop
                    .set reorder
                }
                description = (char *)(beNDMWItemBase_GetRecordString(selectedItem, status, &TXT[0]));

                beMessenger_SelectGroup(self->_messenger, &TEXTCTL_3[0]);
                beMessenger_AppendString(self->_messenger, &STWINFONT29[0]);
                beMessenger_AppendString(self->_messenger, g_fontNames[0]);
                beMessenger_AppendString(self->_messenger, description);
                beMessenger_DispatchSelected(self->_messenger, &TEXTSET[0]);
                beMessenger_SelectGroup(self->_messenger, &TEXTCTL_3[0]);
                beMessenger_AppendString(self->_messenger, &STWINFONT29[0]);
                beMessenger_AppendString(self->_messenger, g_fontNames[0]);
                beMessenger_AppendString(self->_messenger, &DISPON[0]);
                beMessenger_DispatchSelected(self->_messenger, &SWITCH_2[0]);
                asm {
                    nop
                }
            }
        }
    }
}

// clang-format on
} /* extern "C" */
