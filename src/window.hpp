#ifndef WINDOW_HPP
#define WINDOW_HPP

class Renderer;

#include <cairo/cairo.h>
#include <gtkmm/window.h>

namespace App
{

    class Window : public Gtk::Window
    {
    public:
        Window(Renderer const &renderer, size_t width, size_t height);

        bool onDrawSignal(Cairo::RefPtr<Cairo::Context> const &cairo);

    protected:
        Renderer const &_renderer;
    };

} // namespace App

#endif
