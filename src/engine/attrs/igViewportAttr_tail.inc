void Gap__Attrs__igViewportAttr__vfunc_24(int *arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_185(arg1, arg0[3], arg0[4], arg0[5], arg0[6], *(float *)&arg0[8], *(float *)&arg0[9]);
}

void Gap__Attrs__igViewportAttr__vfunc_26(igViewportAttr *arg0, void **arg1) {
    int sp3C;
    int sp38;
    int sp34;
    int sp30;
    float sp2C;
    float sp28;

    ((DW4VC_748_6 *)(arg1))->vX(&sp3C, &sp38, &sp34, &sp30, &sp2C, &sp28);
    arg0->_x = sp3C;
    arg0->_y = sp38;
    arg0->_w = sp34;
    arg0->_h = sp30;
    arg0->_nearZ = sp2C;
    arg0->_farZ = sp28;
}

/* igAttr seen through its vptr: slot 25 sets the unit (stage) the attribute applies to, slot 26
 * reads the attribute's current state back from a visual context. */
class igAttrStateView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual void setUnitID(short unitID);
    virtual void getFromContext(igObject *context);
};

extern "C" igObjectPointer igMetaObject_CreateInstanceRef(igMetaObject *meta, int allocator);

/* The object when it is an igAttr, otherwise none. */
static inline igObject *asAttr(igObject *object) {
    if (object != 0 && igObject_IsKindOf((Item *)object, (int)g_igAttr_metaObject[0]) != 0) {
        return object;
    }
    return 0;
}

/* createDefault: instantiate `meta`, and when it is an igAttr seed it from the managed context. */
extern "C" igObjectPointer Gap__Attrs__igVisualContextAttrDefaultManager__createDefault(
    igVisualContextAttrDefaultManager *self, igMetaObject *meta, int unitID) {
    if (meta == 0 || self->_visualContext == 0) {
        return igObjectPointer(0, kRetainReference);
    }
    igObjectPointer created = igMetaObject_CreateInstanceRef(meta, igObject_GetAllocator(self));
    igObject *object = asAttr(created.get());
    igObjectPointer attr(object, kRetainReference);
    if (attr != 0) {
        ((igAttrStateView *)attr.get())->setUnitID(unitID);
        ((igAttrStateView *)attr.get())->getFromContext((igObject *)self->_visualContext);
    }
    return attr;
}

