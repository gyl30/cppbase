#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

#include "log.h"
#include "env.h"

using leaf::environment;

void environment::load()
{
    for (char** current = environ; *current != nullptr; current++)
    {
        std::vector<std::string> tokens;
        boost::split(tokens, *current, boost::is_any_of("="));
        if (tokens.size() != 2)
        {
            continue;
        }
        env_map_[tokens[0]] = tokens[1];
    }
}
std::string environment::value(const std::string& key)
{
    auto it = env_map_.find(key);
    if (it == env_map_.end())
    {
        return {};
    }
    return it->second;
}

void environment::dump()
{
    for (const auto& kv : env_map_)
    {
        LOG_TRACE("{} {}", kv.first, kv.second);
    }
}

std::pair<uint32_t, uint32_t> environment::cpu_affinity()
{
    std::string cpu = value("CPU");
    if (cpu.empty())
    {
        return {0, 0};
    }
    auto pos = cpu.find_first_of('-');
    if (pos == std::string::npos)
    {
        return {0, 0};
    }
    return {std::stoul(cpu.substr(0, pos)), std::stoul(cpu.substr(pos + 1))};
}
std::string environment::log_level()
{
    std::string level = value("LOG_LEVEL");
    if (level.empty())
    {
        return "debug";
    }
    return level;
}
