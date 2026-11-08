/* Redraws the chip shop's text windows through the messenger (TEXTCTL group, TEXTSET / SWITCH
 * messages). `refreshRows`: for each of the 12 rows of the current page, show the chip's NAME and
 * its NEXTX value (printed with "%d", or "----" when it is not positive) and switch the row on, or
 * switch it off when the row has no chip; then print the current and last page numbers.
 * `refreshDescription`: show the TXT description of the chip under the cursor (index _nowPage * 12
 * + _retCode) and switch its window on. */
#include "dw4/reflected.h"
extern "C" {
#define CHIPS_PER_PAGE 12  /* rows shown per page: the row loop bound and the page stride */
/* Unspecified argument lists keep the original call setup. Observed result widths are explicit;
 * these are call-site projections, not recovered callee types. */
int sprintf(char *, const char *, ...);  /* sprintf(dest, format, ...) */
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
struct ChipPriceText { char text[5]; } __attribute__((aligned(16)));
extern struct ChipPriceText DAT_0051bdc0;  /* "----" */

void beNDMWShopCtrlXdataChip_RefreshText(beNDMWShopCtrlXdataChip *self, long long refreshRows,
                                         long long refreshDescription) {
    char page[4];
    ChipPriceText priceText;
    long long status;
    int row;
    int index;
    char *name;
    int item;
    long long nextX;
    char *visibility;
    char **font;
    int selectedIndex;
    int selectedItem;
    char *description;

    /* Status is captured even when neither refresh flag is set. */
    status = FUN_00236f80(self->_insight, g_beNDMWStatus_metaObject[0]);
    if (refreshRows != 0) {
        font = (char **)(&g_fontNames[0]);
        for (row = 0; row < CHIPS_PER_PAGE; row++, font++) {
            index = row + self->_nowPage * CHIPS_PER_PAGE;
            if (index < ((beNDMWItemBaseList *)self->_itemBaseList)->_count) {
                item = *(int *)(((beNDMWItemBaseList *)self->_itemBaseList)->_data + (index * 4));
                if (item == 0) {
                    continue;
                }
                name = beNDMWItemBase_GetRecordString(item, status, &NAME_2[0]);
                nextX = beNDMWItemBase_GetRecordInt(item, status, &NEXTX[0]);
                beMessenger_SelectGroup(self->_messenger, &TEXTCTL_3[0]);
                beMessenger_AppendString(self->_messenger, &STWINFONT14[0]);
                beMessenger_AppendString(self->_messenger, *font);
                beMessenger_AppendString(self->_messenger, name);
                beMessenger_DispatchSelected(self->_messenger, &TEXTSET[0]);
                if (nextX > 0) {
                    sprintf((char *)&priceText, &percent_d[0], nextX);
                } else {
                    priceText = DAT_0051bdc0;
                }
                beMessenger_SelectGroup(self->_messenger, &TEXTCTL_3[0]);
                beMessenger_AppendString(self->_messenger, &STWINFONT17[0]);
                beMessenger_AppendString(self->_messenger, *font);
                beMessenger_AppendString(self->_messenger, (char *)&priceText);
                beMessenger_DispatchSelected(self->_messenger, &TEXTSET[0]);
                visibility = &DISPON[0];
            } else {
                visibility = &DISPOFF[0];
            }
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
        page[1] = 0;
        page[0] = self->_nowPage + '1';
        beMessenger_SelectGroup(self->_messenger, &TEXTCTL_3[0]);
        beMessenger_AppendString(self->_messenger, &STWINFONT30[0]);
        beMessenger_AppendString(self->_messenger, g_fontNames[0]);
        beMessenger_AppendString(self->_messenger, page);
        beMessenger_DispatchSelected(self->_messenger, &TEXTSET[0]);
        page[0] = self->_maxPage + '0';
        beMessenger_SelectGroup(self->_messenger, &TEXTCTL_3[0]);
        beMessenger_AppendString(self->_messenger, &STWINFONT30[0]);
        beMessenger_AppendString(self->_messenger, g_fontName1[0]);
        beMessenger_AppendString(self->_messenger, page);
        beMessenger_DispatchSelected(self->_messenger, &TEXTSET[0]);
    }
    if (refreshDescription != 0) {
        /* matching construct: hand sweep — the subtraction of a negation keeps the retail addu operand order */
        selectedIndex = self->_nowPage * CHIPS_PER_PAGE - -self->_retCode;
        if (selectedIndex < ((beNDMWItemBaseList *)self->_itemBaseList)->_count) {
            selectedItem = *(int *)(((beNDMWItemBaseList *)self->_itemBaseList)->_data + (selectedIndex * 4));
            if (selectedItem != 0) {
                description = beNDMWItemBase_GetRecordString(selectedItem, status, &TXT[0]);
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
            }
        }
    }
}
}
