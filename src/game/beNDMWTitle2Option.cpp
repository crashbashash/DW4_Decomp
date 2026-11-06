/* src/game/beNDMWTitle2Option.c — beNDMWTitle2Option methods and settings initialization
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
extern int g_beNDMWTitle2Option_metaObject[4];
#include "dw4/reflected.h"
int beMessenger_SendGroup(int, int *, int *);
int beMessenger_GetObject(int, int);
void *igProperty_GetRecord(int, int *);
extern int GAMERAM_3[4];
extern int GETCOMMON_2[4];
extern int CAMERAMODE_2[4];
extern int LIGHTMODE_2[4];
/* Set once the title settings are valid (docs/engine/title-menu-controller.md,
 * "Options"; finding #729): InitSettings restores the saved modes only then. */
extern unsigned char g_commonSettingsValid;

/* 0x003cc6f0 */
int Gap__Bec__beNDMWTitle2Option__vfunc_20(void)
{
    return g_beNDMWTitle2Option_metaObject[0];
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
    if (g_commonSettingsValid == 1) {
        beMessenger_SendGroup(self->_messenger, &GAMERAM_3[0], &GETCOMMON_2[0]);
        commonSettings = beMessenger_GetObject(self->_messenger, 0);
        self->_comConf = (int)((int) *(int *)((char *)(igProperty_GetRecord(commonSettings, &CAMERAMODE_2[0])) + 12));
        self->_lightConf = (int)((int) *(int *)((char *)(igProperty_GetRecord(commonSettings, &LIGHTMODE_2[0])) + 12));
        self->_selLang = 0;
        return;
    }
    self->_comConf = 0;
    self->_lightConf = 1;
    self->_selLang = 0;
    asm { nop }  /* retail has one extra nop here, ahead of the epilogue (003f2de4) */
}
} /* extern "C" */
