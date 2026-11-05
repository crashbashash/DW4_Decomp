#include "dw4/reflected.h"

void FUN_003ee190(beNDMWLoadCtrl2CommonIntf *self, int idx) {
    int i;
    int off;
    beNDMWLoadSavePlWork *e;
    beNDMWLoadSavePlWork *e2;
    i = 0;
    off = 0;
    for (; i < 4; i++) {
        e = ((beNDMWLoadSavePlWork **)((char *)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data + off))[0];
        e->_sysStat0 = 1;
        e->_sysStat3 = 0;
        e->_sysStat2 = 0;
        e->_sysStat1 = 0;
        (((beNDMWLoadSavePlWork **)((char *)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data + off))[0])->_isCtrl = 0;
        (((beNDMWLoadSavePlWork **)((char *)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data + off))[0])->_sysCount0 = 60;
        off += 4;
    }
    e = ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[idx];
    e->_sysStat0 = 0;
    e->_sysStat3 = 0;
    e->_sysStat2 = 0;
    e->_sysStat1 = 0;
    ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[idx]->_isCtrl = 1;
    e2 = ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[idx];
    e2->_sysCount0 = 0;
}
