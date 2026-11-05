/* 0x00420230 FUN_00420230 - MATCH (verify.py).
 * Build: alternate compiler local/mwcps2/combat/mwccps2.exe, flags "-O3,p -Iinclude"
 * (also matches with "-O3,p -Cpp_exceptions off -Iinclude"); no unit-objects entry.
 * Matching constructs:
 *  - char *text (an int local lets the alternate compiler hoist the two string constants out of the loop)
 *  - declaration order list,row,name,font,offs,text (alternate compiler: later declared = lower s-register)
 *  - offs = index * 4 kept as a separate local (CSE'd record offset in s0)
 *  - page digits: 'pg = n; pg += 0x31; page[0] = pg' (a single expression narrows the load to lb)
 *  - index = nowPage << 3; index += retCode (operand order of the addu)
 */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
void sprintf(char *, int *, int);
int FUN_00236f80(int, int);
int beDataBase_GetRecordString(int, int, int *);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, const char *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, int *);
int beMessenger_SendNamed(int, int *, int *, int, int *);
int beNDMWItemBase_GetRecordString(int, int, int *);
int beNDMWWindow_RunMessageScript(beNDMWStatusCtrlSkill *, int *, int);
int igProperty_GetRecordFolder(int, int *);
extern char *DAT_004cf670[];
extern char *DAT_004cf674[4];
extern int DAT_00519b00[4];
extern int DAT_00519b08[4];
extern const char DAT_00519b50[];
extern int DAT_00519b78[4];
extern int DAT_00519b90[4];
extern int DAT_00519ba0[4];
extern int DAT_00519ba8[4];
extern int DAT_00519c28[4];
extern int DAT_00519f30[4];
extern int DAT_00519f40[4];
extern const char DAT_0051a060[];
extern int DAT_0051a128[4];
extern int DAT_0051a140[4];
extern int DAT_0051a2d0[4];
extern const char DAT_0051a370[];
extern const char DAT_0051a380[];
extern const char DAT_0051a390[];
extern int DAT_0051a3a0[4];
extern const char DAT_0051a3c0[];
extern int DAT_0051a3c8[4];
extern int DAT_0051a3d0[4];
extern int DAT_0058b028[4];
void FUN_00420230(beNDMWStatusCtrlSkill *self, int refreshRows, int refreshText) {
    igObjectList *list;
    int row;
    int name;
    char **font;
    int offs;
    char *text;
    beNDMWShinkaObject *item;
    int index;
    char cost[28];
    char page[4];
    int pg;
    int pg2;
    if (self->_retCode != -1) {
        if (refreshRows != 0) {
            row = 0;
            font = DAT_004cf670;
            list = (igObjectList *)((beNDMWShinkaCtrl *)self->_shinkaCtrl)->_list;
            do {
                index = row + self->_nowPage * 8;
                if (list->_count > 0 && index < list->_count) {
                    offs = index * 4;
                    item = ((beNDMWShinkaObject **)list->_data)[index];
                    name = item->_name;
                    beMessenger_SelectGroup(self->_messenger, &DAT_00519c28[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051a060[0]);
                    beMessenger_AppendString(self->_messenger, *font);
                    beMessenger_AppendString(self->_messenger, (const char *)name);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_00519f30[0]);
                    beMessenger_SelectGroup(self->_messenger, &DAT_00519c28[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051a380[0]);
                    beMessenger_AppendString(self->_messenger, *font);
                    beMessenger_AppendString(self->_messenger, &DAT_0051a3c0[0]);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_00519f30[0]);
                    sprintf(cost, &DAT_0051a2d0[0], ((beNDMWShinkaObject **)list->_data)[index]->_level);
                    beMessenger_SelectGroup(self->_messenger, &DAT_00519c28[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051a390[0]);
                    beMessenger_AppendString(self->_messenger, *font);
                    beMessenger_AppendString(self->_messenger, cost);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_00519f30[0]);
                    text = (char *)&DAT_00519b78[0];
                } else {
                    text = (char *)&DAT_00519b00[0];
                }
                beMessenger_SelectGroup(self->_messenger, &DAT_00519c28[0]);
                beMessenger_AppendString(self->_messenger, &DAT_0051a060[0]);
                beMessenger_AppendString(self->_messenger, *font);
                beMessenger_AppendString(self->_messenger, text);
                beMessenger_DispatchSelected(self->_messenger, &DAT_00519b08[0]);
                beMessenger_SelectGroup(self->_messenger, &DAT_00519c28[0]);
                beMessenger_AppendString(self->_messenger, &DAT_0051a380[0]);
                beMessenger_AppendString(self->_messenger, *font);
                beMessenger_AppendString(self->_messenger, text);
                beMessenger_DispatchSelected(self->_messenger, &DAT_00519b08[0]);
                beMessenger_SelectGroup(self->_messenger, &DAT_00519c28[0]);
                beMessenger_AppendString(self->_messenger, &DAT_0051a390[0]);
                beMessenger_AppendString(self->_messenger, *font);
                beMessenger_AppendString(self->_messenger, text);
                beMessenger_DispatchSelected(self->_messenger, &DAT_00519b08[0]);
                row++;
                font++;
            } while (row < 8);
            if (self->_maxPage > 1) {
                page[1] = 0;
                pg = self->_nowPage; pg += 0x31; page[0] = pg;
                beMessenger_SelectGroup(self->_messenger, &DAT_00519c28[0]);
                beMessenger_AppendString(self->_messenger, &DAT_0051a370[0]);
                beMessenger_AppendString(self->_messenger, DAT_004cf670[0]);
                beMessenger_AppendString(self->_messenger, page);
                beMessenger_DispatchSelected(self->_messenger, &DAT_00519f30[0]);
                pg2 = self->_maxPage; pg2 += 0x30; page[0] = pg2;
                beMessenger_SelectGroup(self->_messenger, &DAT_00519c28[0]);
                beMessenger_AppendString(self->_messenger, &DAT_0051a370[0]);
                beMessenger_AppendString(self->_messenger, DAT_004cf674[0]);
                beMessenger_AppendString(self->_messenger, page);
                beMessenger_DispatchSelected(self->_messenger, &DAT_00519f30[0]);
            }
        }
        if (refreshText != 0) {
            switch (self->_skillMenu) {
            case 0:
                beMessenger_SendNamed(self->_messenger, &DAT_0051a128[0], &DAT_0051a3c8[0], 0, &DAT_0051a140[0]);
                name = beMessenger_GetObject(self->_messenger, 0);
                list = (igObjectList *)((beNDMWShinkaCtrl *)self->_shinkaCtrl)->_list;
                index = self->_nowPage << 3; index += self->_retCode;
                if (list->_count > 0 && index < list->_count) {
                    text = (char *)beDataBase_GetRecordString(name, ((beNDMWShinkaObject **)list->_data)[index]->_id, &DAT_0051a3d0[0]);
                    beMessenger_SelectGroup(self->_messenger, &DAT_00519c28[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_00519b50[0]);
                    beMessenger_AppendString(self->_messenger, DAT_004cf670[0]);
                    beMessenger_AppendString(self->_messenger, text);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_00519f30[0]);
                }
                break;
            case 1:
                beNDMWWindow_RunMessageScript(self, &DAT_00519b90[0], self->_retCode + 111);
                break;
            case 2:
                beMessenger_SelectGroup(self->_messenger, &DAT_00519ba0[0]);
                beMessenger_AppendInt(self->_messenger, self->_playerNo);
                beMessenger_DispatchSelected(self->_messenger, &DAT_00519ba8[0]);
                name = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), &DAT_0051a3a0[0]);
                list = (igObjectList *)*(int *)((char *)name + 12);
                text = (char *)beNDMWItemBase_GetRecordString(((int *)list->_data)[self->_retCode], FUN_00236f80(self->_insight, DAT_0058b028[0]), &DAT_00519f40[0]);
                beMessenger_SelectGroup(self->_messenger, &DAT_00519c28[0]);
                beMessenger_AppendString(self->_messenger, &DAT_00519b50[0]);
                beMessenger_AppendString(self->_messenger, DAT_004cf670[0]);
                beMessenger_AppendString(self->_messenger, text);
                beMessenger_DispatchSelected(self->_messenger, &DAT_00519f30[0]);
                break;
            }
        }
    }
}
} /* extern "C" */
