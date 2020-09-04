#include "light_source.hpp"

#include "ray.hpp"

int LightSource::AMBIENT_INTENSITY = 4;

LightSource::LightSource(Color const &intensity, Material const &material, Point const &origin) : Object(material, origin), _intensity(intensity)
{
}

Color const LightSource::getAmbient() const
{
    return _intensity / AMBIENT_INTENSITY;
}

Color const &LightSource::getIntensity() const
{
    return _intensity;
}

float LightSource::intersectDistance(Ray const &ray) const
{
    return ray.getOrigin().distanceTo(_origin);
}

Vector LightSource::normalAt(Point const &surfacePoint) const
{
    throw "Exception in LightSource::normalAt(): Light source has no normal vector.\n";
}

Point LightSource::mapTexturePointFromSurfacePoint(Point const &surfacePoint) const
{
    throw "Exception in LightSource::mapTexturePointFromSurfacePoint(): Light source has no texture.\n";
}

Point LightSource::mapSurfacePointFromTexturePoint(Point const &texturePoint) const
{
    throw "Exception in LightSource::mapSurfacePointFromTexturePoint(): Light source has no texture.\n";
}
