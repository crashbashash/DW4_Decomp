#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_00236b10(int, int);

void Gap__Bec__libNdmwRuntimePlugin__vfunc_22(libNdmwRuntimePlugin *arg0, int arg1) {
    int temp_a1;
    int temp_a1_10;
    int temp_a1_11;
    int temp_a1_12;
    int temp_a1_13;
    int temp_a1_14;
    int temp_a1_15;
    int temp_a1_16;
    int temp_a1_17;
    int temp_a1_18;
    int temp_a1_19;
    int temp_a1_20;
    int temp_a1_21;
    int temp_a1_2;
    int temp_a1_3;
    int temp_a1_4;
    int temp_a1_5;
    int temp_a1_6;
    int temp_a1_7;
    int temp_a1_8;
    int temp_a1_9;

    temp_a1 = arg0->_mdlMapCursor;
    if (temp_a1 != 0) {
        FUN_00236b10(arg1, temp_a1);
    }
    temp_a1_2 = arg0->_mdlMapBase;
    if (temp_a1_2 != 0) {
        FUN_00236b10(arg1, temp_a1_2);
    }
    temp_a1_3 = arg0->_mdlEffect;
    if (temp_a1_3 != 0) {
        FUN_00236b10(arg1, temp_a1_3);
    }
    temp_a1_4 = arg0->_mdlItem;
    if (temp_a1_4 != 0) {
        FUN_00236b10(arg1, temp_a1_4);
    }
    temp_a1_5 = arg0->_mdlObject;
    if (temp_a1_5 != 0) {
        FUN_00236b10(arg1, temp_a1_5);
    }
    temp_a1_6 = arg0->_mdlEBullet;
    if (temp_a1_6 != 0) {
        FUN_00236b10(arg1, temp_a1_6);
    }
    temp_a1_7 = arg0->_mdlEnemy;
    if (temp_a1_7 != 0) {
        FUN_00236b10(arg1, temp_a1_7);
    }
    temp_a1_8 = arg0->_mdlPBullet;
    if (temp_a1_8 != 0) {
        FUN_00236b10(arg1, temp_a1_8);
    }
    temp_a1_9 = arg0->_mdlPlayer2;
    if (temp_a1_9 != 0) {
        FUN_00236b10(arg1, temp_a1_9);
    }
    temp_a1_10 = arg0->_mdlPlayer;
    if (temp_a1_10 != 0) {
        FUN_00236b10(arg1, temp_a1_10);
    }
    temp_a1_11 = arg0->_status;
    if (temp_a1_11 != 0) {
        FUN_00236b10(arg1, temp_a1_11);
    }
    temp_a1_12 = arg0->_gameRam;
    if (temp_a1_12 != 0) {
        FUN_00236b10(arg1, temp_a1_12);
    }
    temp_a1_13 = arg0->_saveCtrl;
    if (temp_a1_13 != 0) {
        FUN_00236b10(arg1, temp_a1_13);
    }
    temp_a1_14 = arg0->_saveIntf;
    if (temp_a1_14 != 0) {
        FUN_00236b10(arg1, temp_a1_14);
    }
    temp_a1_15 = arg0->_loadIntf2;
    if (temp_a1_15 != 0) {
        FUN_00236b10(arg1, temp_a1_15);
    }
    temp_a1_16 = arg0->_loadCtrl2;
    if (temp_a1_16 != 0) {
        FUN_00236b10(arg1, temp_a1_16);
    }
    temp_a1_17 = arg0->_title2;
    if (temp_a1_17 != 0) {
        FUN_00236b10(arg1, temp_a1_17);
    }
    temp_a1_18 = arg0->_logo;
    if (temp_a1_18 != 0) {
        FUN_00236b10(arg1, temp_a1_18);
    }
    temp_a1_19 = arg0->_panelWaza;
    if (temp_a1_19 != 0) {
        FUN_00236b10(arg1, temp_a1_19);
    }
    temp_a1_20 = arg0->_afsSetup;
    if (temp_a1_20 != 0) {
        FUN_00236b10(arg1, temp_a1_20);
    }
    temp_a1_21 = arg0->_stageCtl;
    if (temp_a1_21 != 0) {
        FUN_00236b10(arg1, temp_a1_21);
    }
}
} /* extern "C" */
