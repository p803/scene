#ifndef CAMERA_HPP
#define CAMERA_HPP

class Point;
class Ray;
class Vector;

#include <cstddef>

#include "object.hpp"

class Camera : public Object
{
public:
    Camera(size_t width, size_t height, Material const &material, Point origin);

    size_t getWidth() const;
    size_t getHeight() const;

    virtual float intersectDistance(Ray const &ray) const;
    virtual Point mapTexturePointFromSurfacePoint(Point const &surfacePoint) const;
    virtual Point mapSurfacePointFromTexturePoint(Point const &texturePoint) const;

protected:
    virtual Vector normalAt(Point const &surfacePoint) const;

    size_t _width;
    size_t _height;
};

#endif
