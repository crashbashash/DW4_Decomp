namespace Gap {
namespace Attrs {

/* Setter for the material's reflected _shininess field. */
void igMaterialAttr::setShininess(float sh)
{
    _shininess = sh;
}

void igMaterialAttr::setDiffuse(const igVec4f &d)
{
    _diffuse = d;
    _diffuse.makeMax(g_vec4Zero);
    _diffuse.makeMin(g_vec4One);
}

void igMaterialAttr::setSpecular(const igVec4f &s)
{
    _specular = s;
    _specular.makeMax(g_vec4Zero);
    _specular.makeMin(g_vec4One);
}

void igMaterialAttr::setAmbient(const igVec4f &a)
{
    _ambient = a;
    _ambient.makeMax(g_vec4Zero);
    _ambient.makeMin(g_vec4One);
}

void igMaterialAttr::setEmissive(const igVec4f &e)
{
    _emission = e;
    _emission.makeMax(g_vec4Zero);
    _emission.makeMin(g_vec4One);
}

void igMaterialAttr::apply(igVisualContext *rc)
{
    igPsx2VisualContext_SetMaterial((igPsx2VisualContext *)rc, _ambient.vec, _diffuse.vec, _specular.vec, _emission.vec, _shininess);
}

void igMaterialAttr::synchronizeDefault(igVisualContext *vc)
{
    igVec4f color;

    ((igVisualContextDispatchView *)vc)->getMaterialAmbient(color);
    setAmbient(color);
    ((igVisualContextDispatchView *)vc)->getMaterialDiffuse(color);
    setDiffuse(color);
    ((igVisualContextDispatchView *)vc)->getMaterialSpecular(color);
    setSpecular(color);
    ((igVisualContextDispatchView *)vc)->getMaterialEmissive(color);
    setEmissive(color);
    setShininess(((igVisualContextDispatchView *)vc)->getMaterialShininess());
}
}
}

