void igLightAttr_apply(igLightAttr *self, igObject *context) {
    if (self->_lightId == -1) {
        igObject *old;
        self->_lightId = igPsx2VisualContext_CreateLight((igPsx2VisualContext *)context, self->_lightType);
        igObject::ref(context);
        old = (igObject *)self->_vc;
        igObject::release(old);
        self->_vc = (int)context;
        self->_changed = 1;
    }
    if (!self->_cacheable || self->_changed) {
        igPsx2VisualContext_SetLightAmbient((igPsx2VisualContext *)context, self->_lightId, self->_ambient.vec);
        igPsx2VisualContext_SetLightDiffuse((igPsx2VisualContext *)context, self->_lightId, self->_diffuse.vec);
        igPsx2VisualContext_SetLightSpecular((igPsx2VisualContext *)context, self->_lightId, self->_specular.vec);
        switch (self->_lightType) {
        case 1:
            igPsx2VisualContext_SetLightAttenuation(context, self->_lightId, self->_attenuation.vec);
            break;
        case 2:
            igPsx2VisualContext_SetLightCutoffAngle((igPsx2VisualContext *)context, self->_lightId, self->_cutoff);
            igPsx2VisualContext_SetLightFalloffRate((igPsx2VisualContext *)context, self->_lightId, self->_falloff);
            igPsx2VisualContext_SetLightAttenuation(context, self->_lightId, self->_attenuation.vec);
            break;
        }
        self->_changed = 0;
    }
    switch (self->_lightType) {
    case 0:
        igPsx2VisualContext_SetLightDirection(context, self->_lightId, self->_direction.vec);
        break;
    case 1:
        igPsx2VisualContext_SetLightPosition((igPsx2VisualContext *)context, self->_lightId, self->_position.vec);
        break;
    case 2:
        igPsx2VisualContext_SetLightDirection(context, self->_lightId, self->_direction.vec);
        igPsx2VisualContext_SetLightPosition((igPsx2VisualContext *)context, self->_lightId, self->_position.vec);
        break;
    }
}

void igLightAttr_Reset(A_13ece0 *arg0) {
    int temp_a1;
    L_13ece0 *temp_a0;

    temp_a1 = arg0->f16;
    if (temp_a1 != -1) {
        temp_a0 = arg0->f140;
        if (temp_a0 != 0) {
            temp_a0->vX(temp_a1);
        }
    }
    arg0->f16 = -1;
    temp_a0 = arg0->f140;
    if (temp_a0 != 0) {
        temp_a0->references = temp_a0->references - 1;
        if (((unsigned long long)((long long)temp_a0->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)temp_a0);
        }
    }
    arg0->f140 = 0;
    arg0->f144 = 1;
    arg0->f145 = 1;
}

void igLightAttr_ReleaseDefaults(void **arg0) {
    ((DW4VC_112_0 *)(arg0))->vX();
    igObject_ReleaseDefaults((igObject *)arg0);
}

/* Reset a light attribute to its unassigned state: no hardware light id (-1), flagged changed and
 * cacheable so the next apply re-uploads it. */

void igLightAttr_SynchronizeDefault(igLightAttr *self) {
    self->_lightId = -1;
    self->_changed = 1;
    self->_cacheable = 1;
}

/* Copy a four-float colour into the light's diffuse colour and mark the attribute changed so the
 * renderer re-applies it. _diffuse is reflected as int[4] (igVec4fMetaField) but holds floats. */

void igLightAttr_SetDiffuse(igLightAttr *self, float *color) {
    *(float *)&self->_diffuse[0] = color[0];
    *(float *)&self->_diffuse[1] = color[1];
    *(float *)&self->_diffuse[2] = color[2];
    *(float *)&self->_diffuse[3] = color[3];
    self->_changed = 1;
}

/* Copy a four-float colour into the light's ambient colour and mark the attribute changed (sibling
 * of vfunc_32 for _diffuse and vfunc_34 for _specular). _ambient is reflected as int[4]
 * (igVec4fMetaField) but holds floats. */

void igLightAttr_SetAmbient(igLightAttr *self, float *color) {
    *(float *)&self->_ambient[0] = color[0];
    *(float *)&self->_ambient[1] = color[1];
    *(float *)&self->_ambient[2] = color[2];
    *(float *)&self->_ambient[3] = color[3];
    self->_changed = 1;
}

/* Copy a four-float colour into the light's specular colour and mark the attribute changed
 * (sibling of vfunc_32 for _diffuse and vfunc_33 for _ambient). _specular is reflected as int[4]
 * (igVec4fMetaField) but holds floats. */

void igLightAttr_SetSpecular(igLightAttr *self, float *color) {
    *(float *)&self->_specular[0] = color[0];
    *(float *)&self->_specular[1] = color[1];
    *(float *)&self->_specular[2] = color[2];
    *(float *)&self->_specular[3] = color[3];
    self->_changed = 1;
}

/* IgLightAttr setter for the light's position. Copies the caller's three floats into `_position`
 * and raises `_changed` (the flag the light-attribute users check before re-uploading the light;
 * the matching direction setter is vfunc_36). */

void igLightAttr_SetPosition(igLightAttr *self, float *position) {
    /* _position is reflected as int[3] (igVec3fMetaField); the code moves floats */
    *(float *)&self->_position[0] = (float) position[0];
    *(float *)&self->_position[1] = (float) position[1];
    *(float *)&self->_position[2] = (float) position[2];
    self->_changed = 1;
}

/* IgLightAttr setter for the light's direction. Copies the caller's three floats into `_direction`
 * and raises `_changed` (the matching position setter is vfunc_35). */

void igLightAttr_SetDirection(igLightAttr *self, float *direction) {
    /* _direction is reflected as int[3] (igVec3fMetaField); the code moves floats */
    *(float *)&self->_direction[0] = (float) direction[0];
    *(float *)&self->_direction[1] = (float) direction[1];
    *(float *)&self->_direction[2] = (float) direction[2];
    self->_changed = 1;
}

/* Setter for the spot-light _cutoff (+96); raises _changed (+144) so the cached light state is
 * rebuilt before the next draw. */

void igLightAttr_SetCutoffAngle(igLightAttr *self, float cutoff) {
    self->_cutoff = cutoff;
    self->_changed = 1;
}

/* Setter for the spot-light _falloff (+92); raises _changed (+144) so the cached light state is
 * rebuilt before the next draw. */

void igLightAttr_SetFalloffRate(igLightAttr *self, float falloff) {
    self->_falloff = falloff;
    self->_changed = 1;
}

void igLightAttr_SetAttenuation(igLightAttr *self, void *arg1) {
    self->_attenuation[0] = (float) *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(self) + 104) = (float) *(float *)((char *)(arg1) + 4);
    *(float *)((char *)(self) + 108) = (float) *(float *)((char *)(arg1) + 8);
    self->_changed = 1;
}

void igLightAttr_MarkChanged(igLightAttr *self) {
    self->_changed = 1;
}

