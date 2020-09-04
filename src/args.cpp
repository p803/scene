#include "args.hpp"

Args::Args(int argc, char *argv[]) : _map()
{
    store(parse_command_line(argc, argv, getDescription()), _map);
    notify(_map);
}

options_description Args::getDescription()
{
    options_description description("Allowed options");

    description.add_options()("depth", value<int>()->default_value(5), "Set max depth")("antialiasing", value<int>()->default_value(1), "Set antialiasing")("scattering", value<bool>()->default_value(false), "Set scattering")("width", value<int>()->default_value(512), "Set width")("height", value<int>()->default_value(512), "Set height")("help", "Display this help");

    return description;
}

int Args::depth() const
{
    return _map["depth"].as<int>();
}

int Args::antialiasing() const
{
    return _map["antialiasing"].as<int>();
}

bool Args::scattering() const
{
    return _map["scattering"].as<bool>();
}

int Args::width() const
{
    return _map["width"].as<int>();
}

int Args::height() const
{
    return _map["height"].as<int>();
}

bool Args::help() const
{
    return _map.count("help");
}
