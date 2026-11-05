/* src/game/beNDMWTitle2Option.c — beNDMWTitle2Option methods and settings initialization
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
extern int g_beNDMWTitle2Option_metaObject_0058aa58[4];
#include "dw4/reflected.h"
int beMessenger_SendGroup(int, int *, int *);
int beMessenger_GetObject(int, int);
void *igProperty_GetRecord(int, int *);
extern int s_GAMERAM_00518310[4];
extern int s_GETCOMMON_00518318[4];
extern int s_CAMERAMODE_00518328[4];
extern int s_LIGHTMODE_00518338[4];
/* Set once the title settings are valid (docs/engine/title-menu-controller.md,
 * "Options"; finding #729): InitSettings restores the saved modes only then. */
extern unsigned char g_titleSettingsValid_00554e70;

/* 0x003cc6f0 */
int Gap__Bec__beNDMWTitle2Option__vfunc_20(void)
{
    return g_beNDMWTitle2Option_metaObject_0058aa58[0];
}

/* 0x003f2d50
 * Bind the messenger and load the Options settings (finding #729).  Once the
 * title settings are valid, the saved camera and light modes are read back from
 * the GAMERAM GETCOMMON property group (property record value at +12);
 * otherwise the defaults are camera 0 and light 1.  The language selector
 * always starts at 0. */
void beNDMWTitle2Option_InitSettings(beNDMWTitle2Option *self, int messenger) {
    int commonSettings;

    self->_messenger = messenger;
    if (g_titleSettingsValid_00554e70 == 1) {
        beMessenger_SendGroup(self->_messenger, &s_GAMERAM_00518310[0], &s_GETCOMMON_00518318[0]);
        commonSettings = beMessenger_GetObject(self->_messenger, 0);
        self->_comConf = (int)((int) *(int *)((char *)(igProperty_GetRecord(commonSettings, &s_CAMERAMODE_00518328[0])) + 12));
        self->_lightConf = (int)((int) *(int *)((char *)(igProperty_GetRecord(commonSettings, &s_LIGHTMODE_00518338[0])) + 12));
        self->_selLang = 0;
        return;
    }
    self->_comConf = 0;
    self->_lightConf = 1;
    self->_selLang = 0;
    asm { nop }  /* retail has one extra nop here, ahead of the epilogue (003f2de4) */
}
} /* extern "C" */
