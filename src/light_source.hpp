#ifndef LIGHT_SOURCE_HPP
#define LIGHT_SOURCE_HPP

class Point;
class Ray;
class Vector;

#include "color.hpp"
#include "object.hpp"

class LightSource : public Object
{
public:
    LightSource(Color const &intensity, Material const &material, Point const &origin);

    Color const getAmbient() const;
    Color const &getIntensity() const;

    virtual float intersectDistance(Ray const &ray) const;
    virtual Point mapTexturePointFromSurfacePoint(Point const &surfacePoint) const;
    virtual Point mapSurfacePointFromTexturePoint(Point const &texturePoint) const;

protected:
    static int AMBIENT_INTENSITY;

    virtual Vector normalAt(Point const &surfacePoint) const;

    Color _intensity;
};

#endif
