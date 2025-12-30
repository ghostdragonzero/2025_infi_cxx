#include "../exercise.h"

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>

struct Fibonacci {
    int numbers[11];
    // TODO: 修改方法签名和实现，使测试通过
    int get(int i) const {
        return numbers[i];
    }
    //一定要加const修饰符 非 const 成员函数不能被 const 对象调用。
};

int main(int argc, char **argv) {
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};
    //是结构体的一种声明方式
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}

/*
struct Point {
    int x;
    int y;
};

int main() {
    constexpr Point p{3, 4};          // ✅ 聚合初始化
    // 或者更明确一点：
    constexpr Point q = {10, 20};     // ✅ 等价写法

    std::cout << p.x << ", " << p.y << std::endl; // 输出: 3, 4
}
看起来也是跟python类似的结构体初始化

*/