/* Setter for the material's reflected _shininess field. */
void igMaterialAttr_SetShininess(igMaterialAttr *self, float shininess) {
    self->_shininess = shininess;
}

void igMaterialAttr_SetDiffuse(igMaterialAttr *self, const igVec4f *color) {
    self->_diffuse = *color;
    self->_diffuse.makeMax(g_vec4Zero);
    self->_diffuse.makeMin(g_vec4One);
}

void igMaterialAttr_SetSpecular(igMaterialAttr *self, const igVec4f *color) {
    self->_specular = *color;
    self->_specular.makeMax(g_vec4Zero);
    self->_specular.makeMin(g_vec4One);
}

void igMaterialAttr_SetAmbient(igMaterialAttr *self, const igVec4f *color) {
    self->_ambient = *color;
    self->_ambient.makeMax(g_vec4Zero);
    self->_ambient.makeMin(g_vec4One);
}

void igMaterialAttr_SetEmission(igMaterialAttr *self, const igVec4f *color) {
    self->_emission = *color;
    self->_emission.makeMax(g_vec4Zero);
    self->_emission.makeMin(g_vec4One);
}

void igMaterialAttr_apply(igMaterialAttr *self, igObject *context) {
    igPsx2VisualContext_SetMaterial((igPsx2VisualContext *)context, self->_ambient.vec, self->_diffuse.vec, self->_specular.vec, self->_emission.vec, self->_shininess);
}

void igMaterialAttr_SynchronizeDefault(MaterialAttrView *material, MaterialContextView *context) {
    igVec4f color;

    context->getMaterialDiffuse(&color);
    material->setDiffuse(&color);
    context->getMaterialAmbient(&color);
    material->setAmbient(&color);
    context->getMaterialSpecular(&color);
    material->setSpecular(&color);
    context->getMaterialEmission(&color);
    material->setEmission(&color);
    material->setShininess(context->getMaterialShininess());
}

