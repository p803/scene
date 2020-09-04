#include "material.hpp"

#include "point.hpp"
#include "vector.hpp"

Material::Material(Color const &emission, Texture<Color> const &diffusionMap, Texture<Vector> const &normalMap) : _emission(emission), _diffusion(0, 0, 0), _reflection(0, 0, 0), _transmition(0, 0, 0), _indexOfRefraction(0), _diffusionMap(diffusionMap), _normalMap(normalMap)
{
}

Material::Material(Color const &diffusion, Color const &reflection, Color const &transmition, float indexOfRefraction, Texture<Color> const &diffusionMap, Texture<Vector> const &normalMap) : _emission(0, 0, 0), _diffusion(diffusion), _reflection(reflection), _transmition(transmition), _indexOfRefraction(indexOfRefraction), _diffusionMap(diffusionMap), _normalMap(normalMap)
{
}

bool Material::isEmissive() const
{
    return !_emission.isBlack();
}

bool Material::isDiffusive() const
{
    return !_diffusion.isBlack();
}

bool Material::isReflective() const
{
    return !_reflection.isBlack();
}

bool Material::isTransmissive() const
{
    return !_transmition.isBlack();
}

bool Material::hasDiffusionMap() const
{
    return !_diffusionMap.isEmpty();
}

bool Material::hasNormalMap() const
{
    return !_normalMap.isEmpty();
}

Color const &Material::getEmission() const
{
    return _emission;
}

Color const &Material::getDiffusion() const
{
    return _diffusion;
}

Color const &Material::getReflection() const
{
    return _reflection;
}

Color const &Material::getTransmition() const
{
    return _transmition;
}

Color Material::getDiffusion(Point const &texturePoint) const
{
    return _diffusionMap.getTexel(texturePoint.x(), texturePoint.y());
}

Vector Material::getNormal(Point const &texturePoint) const
{
    Vector u = _normalMap.getTexel(texturePoint.x(), texturePoint.y());

    return Vector(2 * u.x() - 1, u.z(), 2 * u.y() - 1).unitise();
}

float Material::getIndexOfRefraction() const
{
    return _indexOfRefraction;
}
