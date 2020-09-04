#ifndef HIT_HPP
#define HIT_HPP

class Object;
class Point;
class Ray;
class Vector;

class Hit
{
public:
    Hit(Ray const &ray, float distance, Object const *object);

    bool isUndefined() const;
    Point getSurfacePoint() const;
    Point getTexturePoint() const;
    Object const *getObject() const;
    bool is(Object const *object) const;

protected:
    Ray const &_ray;
    float _distance;
    Object const *_object;
};

#endif
