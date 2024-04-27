#ifndef LEAF_NET_CLIENT_H
#define LEAF_NET_CLIENT_H

#include <cstdint>
#include <vector>
#include <memory>
#include <boost/asio.hpp>

namespace leaf
{
class net_client : public std::enable_shared_from_this<net_client>
{
   public:
    net_client() = default;
    virtual ~net_client() = default;

   protected:
    // 读数据回调
    // ec 错误码
    // data 数据指针
    // length 数据长度
    using read_cb = std::function<void(boost::system::error_code ec, const uint8_t* data, std::size_t length)>;
    // 对方地址回调
    // ip
    // port
    using read_cb_addr = std::function<void(const std::string& ip, uint16_t port)>;
    // 写入回调
    // ec 错误码
    // length 数据长度
    using write_cb = std::function<void(boost::system::error_code, std::size_t length)>;
    // 高水位回调
    // 当有太多数据堆积在写缓冲区待发送时
    // cache_size 缓冲区大小临界值，达到此值时，触发高水位回调
    using high_water_mark_cb = std::function<void(uint32_t cache_size)>;
    // 高水位完成回调
    // 高水位回调后，缓冲区数据写入完成后，调用水位完成回调
    using write_complete_cb = std::function<void(void)>;

   public:
    virtual void start() = 0;
    virtual void shutdown() = 0;
    // 停止读数据
    virtual void stop_read() = 0;
    // 开始读取数据
    virtual void start_read() = 0;
    // 设置待写缓存大小，当待写的数据超过指定的大小时，调用回调， 一般在回调中停止写入数据
    virtual void set_high_water_mark_callback(uint32_t high_water_mark, const high_water_mark_cb& cb) = 0;
    // 当待写入的数据减少到指定的大小并且当前停止写入时，调用回调，一般在回调中重新开启写入数据
    virtual void set_write_complete_callback(uint32_t low_water_mark, const write_complete_cb& cb) = 0;
    // 设置读到数据时的回调
    virtual void set_read_cb(const read_cb& cb) = 0;
    // 设置获取到对方地址信息时的回调
    virtual void set_read_addr_cb(const read_cb_addr& cb) = 0;
    // 设置写回调
    virtual void set_write_cb(const write_cb& cb) = 0;
    // 根据数据指针和数据长度发送数据
    virtual void write(const uint8_t* data, uint32_t size) = 0;
    // 发送数据块
    virtual void write(const std::vector<uint8_t>& buff) = 0;
    // 发送数据块指针
    virtual void write(const std::shared_ptr<std::vector<uint8_t>>& buff) = 0;
};
}    // namespace leaf
#endif
