#ifndef LEAF_SCOPED_EXIT_H
#define LEAF_SCOPED_EXIT_H

#include <utility>

namespace leaf
{
template <typename Callback>
class scoped_exit
{
   public:
    explicit scoped_exit(Callback &&c) : callback(c) {}

    scoped_exit(scoped_exit &&mv) noexcept : callback(std::move(mv.callback)), canceled(mv.canceled) { mv.canceled = true; }

    scoped_exit(const scoped_exit &) = delete;
    scoped_exit &operator=(const scoped_exit &) = delete;

    ~scoped_exit()
    {
        if (!canceled)
        {
            callback();
        }
    }
    scoped_exit &operator=(scoped_exit &&mv) = delete;

    void cancel() { canceled = true; }

   private:
    Callback callback;
    bool canceled = false;
};

template <typename Callback>
scoped_exit<Callback> make_scoped_exit(Callback &&c)
{
    return scoped_exit<Callback>(std::forward<Callback>(c));
}
#define SCOPED_CONCAT_(x, y) x##y
#define SCOPED_CONCAT(x, y) SCOPED_CONCAT_(x, y)
#define SCOPED_UNIQUE_NAME(prefix) SCOPED_CONCAT(prefix, __LINE__)
#define DEFER(code) auto SCOPED_UNIQUE_NAME(scoped) = ::ScopedExit::make_scoped_exit([&]() { code; })
}    // namespace leaf
#endif
