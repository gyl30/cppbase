#ifndef LEAF_ENV_H
#define LEAF_ENV_H

#include <string>
#include <cstdint>
#include <map>
#include "singleton.h"

namespace leaf
{
class environment
{
   public:
    environment() = default;
    ~environment() = default;

   public:
    /**
     * @brief 加载环境变量
     */
    void load();

    /**
     * @brief 获取环境变量
     *
     * @param key 环境变量名称
     *
     * @return 环境变量
     */
    std::string value(const std::string& key);

    /**
     * @brief 打印环境变量
     */
    void dump();

    /**
     * @brief 获取日志级别
     *
     * @return 日志级别
     */
    std::string log_level();

    /**
     * @brief 设置CPU亲和度
     *
     * @return CPU 区间
     */
    std::pair<uint32_t, uint32_t> cpu_affinity();

   private:
    std::map<std::string, std::string> env_map_;
};
using env = leaf::singleton<environment>;
}    // namespace leaf

#endif
