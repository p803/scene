#include "window.hpp"

#include "color.hpp"
#include "renderer.hpp"

App::Window::Window(Renderer const &renderer, size_t width, size_t height) : Gtk::Window(), _renderer(renderer)
{
    set_title("Scene");
    set_default_size(width, height);
    set_position(Gtk::WIN_POS_CENTER);

    signal_draw().connect(sigc::mem_fun1(*this, &Window::onDrawSignal));
}

bool App::Window::onDrawSignal(const Cairo::RefPtr<Cairo::Context> &cairo)
{
    Color *image = _renderer.render(get_width(), get_height());

    cairo->set_line_width(1);

    for (int i = 0; i < get_width(); i++)
    {
        for (int j = 0; j < get_height(); j++)
        {
            Color &pixel = image[i * get_height() + j];

            cairo->set_source_rgb(pixel.red(), pixel.green(), pixel.blue());
            cairo->rectangle(i, get_height() - j - 1, 1, 1);
            cairo->fill();
        }
    }

    delete image;

    return false;
}
