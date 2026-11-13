int Gap__Gui__igOnOffColorChanger__vfunc_23(int arg0, OnOffColorState *s) { int n; bool t, f; if (!s->enabled) return arg0 + 0x48; t = s->on; n = 0; if (t) n += 1; f = s->hilite && t; if (s->current ^ f) n += 2; return arg0 + n * 0x10 + 8; }

void igOnOffColorChanger_SetColor(igBasicColorChanger *arg0, int arg1, int arg2, int arg3, void *arg4)
{
    igBasicColorChanger_SetColor(arg0, arg1, arg2, arg3, arg4);
}

igVec3f FUN_00453b90(A *a) {
    B *b = a->b;
    float z0 = 0.0f, two = 2.0f; float dx = a->dx, dy = a->dy; float x = b->x, y = b->y, z = b->z; x += two * dx; y += two * dy; z += z0;
    return igVec3f(x, y, z);
}

/* Places the element's geometry inside the aspect's area according to its fit mode. */
void igDefaultAspectElement_PlaceGeometry(igDefaultAspectElement *self, const igVec3f *size) {
    float m[16];
    B *geom;
    float y;
    float width;

    igMatrix44f_SetIdentity(m);
    geom = (B *)self->_geometryElement;
    width = geom->x;
    y = (size->y - geom->y) / 2.0f;
    switch (self->_fitMode) {
    case 0: {
        igMatrix44f_SetIdentity(m);
        igVec3f t(self->_hMargin, y, 0.0f);
        igMatrix44f_SetTranslation(m, &t);
        ((Obj_456b80 *)self->_transform)->vX(m);
        break;
    }
    case 2: {
        igMatrix44f_SetIdentity(m);
        igVec3f t(size->x - width, y, 0.0f);
        igMatrix44f_SetTranslation(m, &t);
        ((Obj_456b80 *)self->_transform)->vX(m);
        break;
    }
    case 1: {
        igMatrix44f_SetIdentity(m);
        igVec3f t((size->x - width) / 2.0f, y, 0.0f);
        igMatrix44f_SetTranslation(m, &t);
        ((Obj_456b80 *)self->_transform)->vX(m);
        break;
    }
    case 3: {
        igMatrix44f_SetIdentity(m);
        igVec3f t(self->_hMargin, self->_vMargin, 0.0f);
        igMatrix44f_SetTranslation(m, &t);
        ((Obj_456b80 *)self->_transform)->vX(m);
        /* matching construct: hand variant — reading the width into a local first gives retail's register choice. */
        float areaWidth = size->x;
        igVec3f s(areaWidth - 2.0f * self->_hMargin, size->y - 2.0f * self->_vMargin, size->z);
        ((igGeometryElementSizeView *)self->_geometryElement)->setSize(&s);
        break;
    }
    }
}
