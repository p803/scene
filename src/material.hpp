#ifndef MATERIAL_HPP
#define MATERIAL_HPP

class Point;
class Vector;

#include "color.hpp"
#include "texture.hpp"

class Material
{
public:
    Material(Color const &emission, Texture<Color> const &diffusionMap, Texture<Vector> const &normalMap);
    Material(Color const &diffusion, Color const &reflection, Color const &transmition, float indexOfRefraction, Texture<Color> const &diffusionMap, Texture<Vector> const &normalMap);

    bool isEmissive() const;
    bool isDiffusive() const;
    bool isReflective() const;
    bool isTransmissive() const;

    bool hasDiffusionMap() const;
    bool hasNormalMap() const;

    Color const &getEmission() const;
    Color const &getDiffusion() const;
    Color const &getReflection() const;
    Color const &getTransmition() const;

    Color getDiffusion(Point const &texturePoint) const;
    Vector getNormal(Point const &texturePoint) const;

    float getIndexOfRefraction() const;

protected:
    Color _emission;
    Color _diffusion;
    Color _reflection;
    Color _transmition;
    float _indexOfRefraction;
    Texture<Color> _diffusionMap;
    Texture<Vector> _normalMap;
};

#endif
