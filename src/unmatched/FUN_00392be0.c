#include "dw4/reflected.h"
/* Movement query on the work's beModelCtrlMoveObjectList (_moveObjectList, +200): the list is
 * enabled when _count != 0 and _data holds four beModelCtrlMoveObject handles (0 move, 1 rotation,
 * 2 turn-Y/landing, 3 fourth channel); selector 5 also clears entry 1 (_isRun and _speed). _data
 * is an array of arena handles, so entries are reached via casts. */
unsigned char FUN_00392be0(int unused0, int unused1, beModelCtrlInfoWork *owner, unsigned int sel) {
    beModelCtrlMoveObjectList *p;
    beModelCtrlMoveObject **l;
    beModelCtrlMoveObject *r;
    p = (beModelCtrlMoveObjectList *)owner->_moveObjectList;
    if (p->_count == 0) {
        return 0;
    }
    switch (sel) {
    case 0:
        l = (beModelCtrlMoveObject **)p->_data;
        if (l[0]->_isRun != 0) {
            return 1;
        }
        if (l[1]->_isRun != 0) {
            return 1;
        }
        r = l[2];
        if (r->_isRun) {
            return r->_isRun;
        }
        return r->_isRun;
    case 1:
        return ((beModelCtrlMoveObject **)p->_data)[3]->_isRun;
    case 2:
        return ((beModelCtrlMoveObject **)p->_data)[1]->_isRun;
    case 3:
        r = ((beModelCtrlMoveObject **)p->_data)[1];
        if (r->_isRun != 0 && r->_mode == 4) {
            return 1;
        }
        return 0;
    case 4:
        r = ((beModelCtrlMoveObject **)p->_data)[1];
        if (r->_isRun != 0 && r->_mode == 1) {
            return 1;
        }
        return 0;
    case 5:
        r = ((beModelCtrlMoveObject **)p->_data)[1];
        r->_isRun = 0;
        r->_speed = 0;
    default:
        return 1;
    }
}
