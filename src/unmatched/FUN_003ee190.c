#include "dw4/reflected.h"

void FUN_003ee190(beNDMWLoadCtrl2CommonIntf *self, int idx) {
    int i;
    beNDMWLoadSavePlWork *e;
    i = 0;
    do {
        e = ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[i];
        e->_sysStat0 = 1;
        e->_sysStat3 = 0;
        e->_sysStat2 = 0;
        e->_sysStat1 = 0;
        ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[i]->_isCtrl = 0;
        ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[i]->_sysCount0 = 60;
        i++;
    } while (i < 4);
    e = ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[idx];
    e->_sysStat0 = 0;
    e->_sysStat3 = 0;
    e->_sysStat2 = 0;
    e->_sysStat1 = 0;
    ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[idx]->_isCtrl = 1;
    ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[idx]->_sysCount0 = 0;
}
