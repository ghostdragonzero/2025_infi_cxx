#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};
    //共享指针  三个指针共享一个10个int的数组

    std::weak_ptr<int> observer = shared;
    //弱引用不增加引用计数
    ASSERT(observer.use_count() == 4, "");
    //三个指针共享一个10个int的数组 所以引用计数为3

    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "");
    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared);
    //会析构原来的引用让计数-1 
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 3, "");
    if (ptrs[0] == nullptr) {
        std::cout << "ptrs[0] is nullptr" << std::endl;
    } else {
        std::cout << "ptrs[0] is not nullptr" << std::endl;
    }

    std::cout << observer.use_count() << std::endl;
    std::ignore = std::move(ptrs[0]);
    //auto temp = std::move(ptrs[0]);
        if (ptrs[0] == nullptr) {
        std::cout << "ptrs[0] is nullptr" << std::endl;
    } else {
        std::cout << "ptrs[0] is not nullptr" << std::endl;
    }
    //从打印看这个ignore并没有改变 甚至没有让ptrs[0]变成nullptr
    std::cout << observer.use_count() << std::endl;
    ptrs[1] = std::move(ptrs[1]);
    std::cout << observer.use_count() << std::endl;
    ptrs[1] = std::move(ptrs[2]);
    std::cout << observer.use_count() << std::endl;
    ASSERT(observer.use_count() == 2, "");

    shared = observer.lock();
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");

    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "");

    return 0;
}
