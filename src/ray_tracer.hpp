#ifndef RAY_TRACER_HPP
#define RAY_TRACER_HPP

class Color;
class Hit;
class Object;
class Point;
class Ray;
class ObjectManager;

#include "renderer.hpp"

class RayTracer : public Renderer
{
public:
    RayTracer(int maxDepth, int antialiasing, bool scattering, ObjectManager const &objectManager);

    Color *render(size_t width, size_t height) const;
    Color traceRay(Ray const &ray, int depth) const;

protected:
    Color renderPixel(size_t i, size_t j) const;
    Ray createPrimaryRay(float i, float j) const;
    Hit findNearestHit(Ray const &ray, bool allowLightSource = false) const;
    Color calculateLightIntensity(Object const *object, Point const &surfacePoint) const;

    int _maxDepth;
    int _antialiasing;
    bool _scattering;
    ObjectManager const &_objectManager;
};

#endif
