#include <gtkmm.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "args.hpp"
#include "bilinear_filter.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "light_source.hpp"
#include "object_manager.hpp"
#include "ray_tracer.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "texture.hpp"
#include "triangle.hpp"
#include "unary_filter.hpp"
#include "window.hpp"

/**
 * @todo Make material optional object component.
 * @todo Extract from object location component.
 * @todo Make objects points relative to origin.
 * @todo Make objects prefabricates.
 * @todo Set origin when adding prefabricate to scene.
 * @todo Use scene facade.
 * @todo Refactor filters into non-template.
 * @todo Move camera code from renderer to camera.
 * @todo Refactor: hit, surface point, texture point.
 * @todo Add transformations on objects and camera move.
 * @todo Compare callable in matrix.
 * @todo Extract transmissive, diffusive and emissive materials.
 * @todo Decorate texture with filterable texture.
 */
int main(int argc, char *argv[])
{
    srand(time(NULL));

    // Parse command line arguments.
    Args args(argc, argv);

    if (args.help())
    {
        std::cout << args.getDescription() << std::endl;

        return 0;
    }

    // Create scene.
    Color colorBlack(0, 0, 0);
    Color colorBlue(.19, .77, .98);
    Color colorBlueDark(.04, .42, .5);
    Color colorGray(.9, .9, .9);
    Color colorGreen(.71, .89, .1);
    Color colorRed(.95, .32, .23);
    Color colorWhite(1, 1, 1);
    Color colorYellow(1.0, .98, .74);

    BilinearFilter<Vector> filterNormals;
    BilinearFilter<Color> filterColor;

    Texture<Vector> normalsNone("assets/color-black.jpg", filterNormals);
    Texture<Color> textureNone("assets/color-black.jpg", filterColor);
    Material materialNone(colorBlack, colorBlack, colorBlack, 0, textureNone, normalsNone);

    Texture<Vector> normalsBrick("assets/normals-brick.jpg", filterNormals);
    Texture<Vector> normalsWater("assets/normals-water.jpg", filterNormals);

    Texture<Color> textureIce("assets/texture-ice.png", filterColor);
    Texture<Color> textureMarble("assets/texture-marble.png", filterColor);

    Material materialGlassPure(colorBlack, colorBlack, colorWhite, 1.08, textureNone, normalsNone);        // glass pure
    Material materialGlassBlueDark(colorBlueDark, colorBlueDark, colorBlack, 0, textureNone, normalsNone); // glass blue dark
    Material materialLampWhite(colorWhite, textureNone, normalsNone);                                      // lamp
    Material materialLampYellow(colorYellow, textureNone, normalsNone);                                    // lamp
    Material materialStoneBlue(colorBlue, colorBlack, colorBlack, 0, textureIce, normalsNone);             // stone blue
    Material materialStoneGreen(colorGreen, colorBlack, colorBlack, 0, textureIce, normalsNone);           // stone green
    Material materialStoneRed(colorRed, colorBlack, colorBlack, 0, textureIce, normalsNone);               // stone red
    Material materialMarble1(colorYellow, colorBlack, colorBlack, 0, textureMarble, normalsNone);          // marble 1
    Material materialMarble2(colorYellow, colorBlack, colorBlack, 0, textureMarble, normalsBrick);         // marble 2
    Material materialWater(colorBlueDark, colorBlueDark, colorBlack, 0, textureNone, normalsWater);        // water

    ObjectManager objectManager;

    objectManager.addObject(new Camera(args.width(), args.height(), materialNone, Point(0, .5, -1.5)));                                 // camera
    objectManager.addObject(new LightSource(colorYellow, materialNone, Point(0, 2, -2)));                                               // light source
    objectManager.addObject(new Sphere(.5, materialStoneRed, Point(-1, .5, 0)));                                                        // left sphere
    objectManager.addObject(new Sphere(.5, materialStoneGreen, Point(0, .5, 0)));                                                       // middle sphere
    objectManager.addObject(new Sphere(.5, materialStoneBlue, Point(1, .5, 0)));                                                        // right sphere
    objectManager.addObject(new Sphere(.5, materialMarble1, Point(-.5, 1.3, .2)));                                                      // upper left sphere
    objectManager.addObject(new Sphere(.5, materialMarble2, Point(.5, 1.3, .2)));                                                       // upper right sphere
    objectManager.addObject(new Sphere(.2, materialGlassPure, Point(-.3, .65, -.8)));                                                   // left glass
    objectManager.addObject(new Sphere(.2, materialGlassPure, Point(.3, .45, -.8)));                                                    // right glass
    objectManager.addObject(new Triangle(Point(-4, 0, -2), Point(4, 0, -2), Point(0, 0, 4), materialWater, Point(0, 0, 0)));            // ground
    objectManager.addObject(new Triangle(Point(-.5, .1, -1), Point(.1, .1, -1), Point(-.2, .4, -.8), materialMarble2, Point(0, 0, 0))); // wall
    // objectManager.addObject(new Sphere(5, materialLampWhite, Point(0, 0, 0)));                                                       // sun
    // objectManager.addObject(new Sphere(.6, materialLampYellow, Point(1, .5, 0)));                                                    // lamp

    RayTracer rayTracer(args.depth(), args.antialiasing(), args.scattering(), objectManager);

    // Create GTK application.
    auto app = Gtk::Application::create("p803.scene");

    App::Window window(rayTracer, args.width(), args.height());

    app->run(window);

    return 0;
}
