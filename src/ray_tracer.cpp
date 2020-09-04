#include "ray_tracer.hpp"

#include <iostream>

#include "camera.hpp"
#include "color.hpp"
#include "fp.hpp"
#include "hit.hpp"
#include "light_source.hpp"
#include "object_manager.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "vector.hpp"

RayTracer::RayTracer(int maxDepth, int antialiasing, bool scattering, ObjectManager const &objectManager) : _maxDepth(maxDepth), _antialiasing(antialiasing), _scattering(scattering), _objectManager(objectManager)
{
}

Color *RayTracer::render(size_t width, size_t height) const
{
    std::cout << "rendering... " << std::flush;

    Color *image = std::allocator<Color>().allocate(width * height);

    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            try
            {
                image[i * height + j] = renderPixel(i, j);
            }
            catch (char const *e)
            {
                std::cout << e << std::endl;

                // Set pixel to red.
                image[i * height + j] = Color(1, 0, 0);
            }
        }
    }

    std::cout << "done." << std::endl;

    return image;
}

Color RayTracer::renderPixel(size_t i, size_t j) const
{
    Camera const &camera = _objectManager.getObject<Camera>();

    // Return black if pixel out of camera.
    if (i > camera.getWidth() || j > camera.getHeight())
    {
        return Color(0, 0, 0);
    }

    // Render pixel.
    Color color(0, 0, 0);

    for (int t = 0; t < _antialiasing; t++)
    {
        float ti = i - .5 + Fp::rand();
        float tj = j - .5 + Fp::rand();

        color += traceRay(createPrimaryRay(ti, tj), 0);
    }

    color /= _antialiasing;

    return color.trim();
}

Ray RayTracer::createPrimaryRay(float i, float j) const
{
    Camera const &camera = _objectManager.getObject<Camera>();

    float xDeviation = 2 * i / camera.getWidth() - 1;
    float yDeviation = 2 * j / camera.getHeight() - 1;

    Vector ahead = Vector(camera.getFront() + camera.getRight() * xDeviation + camera.getUp() * yDeviation).unitise();

    return Ray(camera.getOrigin(), ahead);
}

Color RayTracer::traceRay(Ray const &ray, int depth) const
{
    if (depth == _maxDepth)
    {
        return Scene::COLOR_SPACE;
    }

    Hit hit = findNearestHit(ray);

    if (hit.isUndefined())
    {
        return Scene::COLOR_SPACE;
    }

    Color final(0, 0, 0);

    Material const &material = hit.getObject()->getMaterial();

    if (material.isEmissive())
    {
        return material.getEmission();
    }

    if (material.isDiffusive())
    {
        Color color = _scattering ? traceRay(ray.scatter(hit.getObject(), hit.getSurfacePoint()), depth + 1) : calculateLightIntensity(hit.getObject(), hit.getSurfacePoint());
        Color diffusion = material.getDiffusion();

        if (material.hasDiffusionMap())
        {
            diffusion *= material.getDiffusion(hit.getTexturePoint());
        }

        final += color * diffusion;
    }

    if (material.isReflective())
    {
        Ray reflected = ray.reflect(hit.getObject(), hit.getSurfacePoint());

        Color color = traceRay(reflected, depth + 1);
        Color reflection = material.getReflection();

        final += color * reflection;
    }

    if (material.isTransmissive())
    {
        Ray transmitted = ray.transmit(hit.getObject(), hit.getSurfacePoint());

        Color color = traceRay(transmitted, depth + 1);
        Color transmition = material.getTransmition();

        final += color * transmition;
    }

    return final;
}

Hit RayTracer::findNearestHit(Ray const &ray, bool allowLightSource) const
{
    float hitDistance = INFINITY;
    Object *hitObject = NULL;

    for (auto object : _objectManager.getObjects())
    {
        if (!allowLightSource && dynamic_cast<LightSource *>(object) != NULL)
        {
            continue;
        }

        if (dynamic_cast<Camera *>(object) != NULL)
        {
            continue;
        }

        float distance = ray.distanceTo(object);

        if (Fp::lt(distance, hitDistance))
        {
            hitDistance = distance;
            hitObject = object;
        }
    }

    return Hit(ray, hitDistance, hitObject);
}

Color RayTracer::calculateLightIntensity(Object const *object, Point const &surfacePoint) const
{
    LightSource const &lightSource = _objectManager.getObject<LightSource>();

    // In shadow if faced against the light source.
    Vector toLightSource = surfacePoint.directionTo(lightSource.getOrigin());
    Vector normal = object->mappedNormalAt(surfacePoint);
    float cos = toLightSource.dot(normal);

    if (Fp::lt(cos, 0))
    {
        return lightSource.getAmbient();
    }

    // In shadow if light source behind obstacle.
    Ray shadow = surfacePoint.rayTo(lightSource.getOrigin());
    Hit hit = findNearestHit(shadow, true);

    if (!hit.is(&lightSource))
    {
        return lightSource.getAmbient();
    }

    return lightSource.getAmbient() + lightSource.getIntensity() * cos;
}
