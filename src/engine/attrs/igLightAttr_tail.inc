namespace Gap {
namespace Attrs {

void igLightAttr::apply(igVisualContext *vc)
{
    if (_lightId == -1) {
        _lightId = ((igPsx2VisualContext *)vc)->igPsx2VisualContext::createLight((IG_GFX_LIGHT_TYPE)_lightType);
        _vc = vc;
        _changed = true;
    }
    if (!_cacheable || _changed) {
        ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setLightAmbient(_lightId, _ambient);
        ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setLightDiffuse(_lightId, _diffuse);
        ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setLightSpecular(_lightId, _specular);
        switch (_lightType) {
        case IG_GFX_LIGHT_TYPE_POINT:
            ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setLightAttenuation(_lightId, _attenuation);
            break;
        case IG_GFX_LIGHT_TYPE_SPOT:
            ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setLightCutoffAngle(_lightId, _cutoff);
            ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setLightFalloffRate(_lightId, _falloff);
            ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setLightAttenuation(_lightId, _attenuation);
            break;
        }
        _changed = false;
    }
    switch (_lightType) {
    case IG_GFX_LIGHT_TYPE_DIRECTIONAL:
        ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setLightDirection(_lightId, _direction);
        break;
    case IG_GFX_LIGHT_TYPE_POINT:
        ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setLightPosition(_lightId, _position);
        break;
    case IG_GFX_LIGHT_TYPE_SPOT:
        ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setLightDirection(_lightId, _direction);
        ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setLightPosition(_lightId, _position);
        break;
    }
}

void igLightAttr::reset()
{
    if (_lightId != -1 && _vc != 0)
        _vc->deleteLight(_lightId);
    _lightId = -1;
    _vc = 0;
    _changed = true;
    _cacheable = true;
}

void igLightAttr::releaseDefaults()
{
    reset();
    igVisualAttribute::releaseDefaults();
}

/* Reset a light attribute to its unassigned state: no hardware light id (-1), flagged changed and
 * cacheable so the next apply re-uploads it. */

void igLightAttr::synchronizeDefault(igVisualContext *vc)
{
    _lightId = -1;
    _changed = true;
    _cacheable = true;
}

/* Copy a four-float colour into the light's diffuse colour and mark the attribute changed so the
 * renderer re-applies it. _diffuse is reflected as int[4] (igVec4fMetaField) but holds floats. */

void igLightAttr::setDiffuse(const igVec4f &d)
{
    _diffuse = d;
    _changed = true;
}

/* Copy a four-float colour into the light's ambient colour and mark the attribute changed (sibling
 * of vfunc_32 for _diffuse and vfunc_34 for _specular). _ambient is reflected as int[4]
 * (igVec4fMetaField) but holds floats. */

void igLightAttr::setAmbient(const igVec4f &a)
{
    _ambient = a;
    _changed = true;
}

/* Copy a four-float colour into the light's specular colour and mark the attribute changed
 * (sibling of vfunc_32 for _diffuse and vfunc_33 for _ambient). _specular is reflected as int[4]
 * (igVec4fMetaField) but holds floats. */

void igLightAttr::setSpecular(const igVec4f &s)
{
    _specular = s;
    _changed = true;
}

/* IgLightAttr setter for the light's position. Copies the caller's three floats into `_position`
 * and raises `_changed` (the flag the light-attribute users check before re-uploading the light;
 * the matching direction setter is vfunc_36). */

void igLightAttr::setPosition(const igVec3f &p)
{
    _position = p;
    _changed = true;
}

/* IgLightAttr setter for the light's direction. Copies the caller's three floats into `_direction`
 * and raises `_changed` (the matching position setter is vfunc_35). */

void igLightAttr::setDirection(const igVec3f &d)
{
    _direction = d;
    _changed = true;
}

/* Setter for the spot-light _cutoff (+96); raises _changed (+144) so the cached light state is
 * rebuilt before the next draw. */

void igLightAttr::setCutoffAngle(float c)
{
    _cutoff = c;
    _changed = true;
}

/* Setter for the spot-light _falloff (+92); raises _changed (+144) so the cached light state is
 * rebuilt before the next draw. */

void igLightAttr::setFalloffRate(float e)
{
    _falloff = e;
    _changed = true;
}

void igLightAttr::setAttenuation(const igVec3f &a)
{
    _attenuation = a;
    _changed = true;
}

void igLightAttr::lightChanged(igObject *obj)
{
    ((igLightAttr *)obj)->_changed = true;
}
}
}

