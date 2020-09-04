#ifndef ARGS_HPP
#define ARGS_HPP

#include <boost/program_options.hpp>

using namespace boost::program_options;

class Args
{
public:
    Args(int argc, char *argv[]);

    static options_description getDescription();

    int depth() const;
    int antialiasing() const;
    bool scattering() const;
    int width() const;
    int height() const;
    bool help() const;

private:
    variables_map _map;
};

#endif
