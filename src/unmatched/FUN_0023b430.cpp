#include "dw4/igSmartPointer.h"
extern "C" {
igCollisionCell *FUN_0023a6e0(int pool);
void FUN_0023b430(igCollisionGrid *grid);
}

static inline float minOf(float a, float b) { return a < b ? a : b; }

struct CellList : public igObjectList {
    void set(int index, const igSmartPointer<igCollisionCell> &cell) {
        igCollisionCell *entry = cell.p;
        if (entry != 0) entry->_refCount = entry->_refCount + 1;
        igObject *old = ((igObject **)_data)[index];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (_count != 0 && index >= 0 && index < _count) {
            ((igCollisionCell **)_data)[index] = entry;
        }
    }
};

static inline void setVec3(float *v, float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}
extern "C" void FUN_0023b430(igCollisionGrid *grid) {
    igAABox *bound = (igAABox *)grid->_bound;
    float &stepY = grid->_deltas[1];
    float &stepZ = grid->_deltas[2];
    grid->_deltas[0] = bound->_max[0] - bound->_min[0];
    grid->_deltas[1] = bound->_max[1] - bound->_min[1];
    grid->_deltas[2] = bound->_max[2] - bound->_min[2];
    grid->_deltas[0] = grid->_deltas[0] / (float)grid->_sizeX;
    grid->_deltas[1] = grid->_deltas[1] / (float)grid->_sizeY;
    grid->_deltas[2] = grid->_deltas[2] / (float)grid->_sizeZ;
    grid->_maxRadius = minOf(grid->_deltas[0], grid->_deltas[1]);
    grid->_maxRadius = minOf(grid->_maxRadius, stepZ);
    grid->_maxRadius = grid->_maxRadius * 0.5f;
    int index = 0;
    const float *origin = ((igAABox *)grid->_bound)->_min;
    float x = origin[0];
    float y = origin[1];
    float z = origin[2];
    for (int k = 0; k < grid->_sizeZ; k++) {
        for (int j = 0; j < grid->_sizeY; j++) {
            for (int i = 0; i < grid->_sizeX; i++) {
                igSmartPointer<igCollisionCell> cell(FUN_0023a6e0(0), AdoptReference());
                float maxX = x + grid->_deltas[0];
                float maxY = y + grid->_deltas[1];
                float maxZ = z + grid->_deltas[2];
                cell->_grid = (int)grid;
                igCollisionCell *c = cell.p;
                setVec3(((igAABox *)c->_box)->_min, x, y, z);
                setVec3(((igAABox *)c->_box)->_max, maxX, maxY, maxZ);
                ((CellList *)grid->_cells)->set(index, cell);
                index++;
                x += grid->_deltas[0];
            }
            origin = ((igAABox *)grid->_bound)->_min;
            x = origin[0];
            y += stepY;
        }
        y = origin[1];
        z += stepZ;
    }
}
