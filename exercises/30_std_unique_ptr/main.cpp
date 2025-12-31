#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records);
    }
    //析构时会把recards记录下来
};

using Unique = std::unique_ptr<Resource>;
Unique reset(Unique ptr) {
    if (ptr) ptr->record('r');
    //会调用析构
    return std::make_unique<Resource>();
}
Unique drop(Unique ptr) {
    if (ptr) ptr->record('d');
    //会调用析构
    return nullptr;
}
Unique forward(Unique ptr) {
    if (ptr) ptr->record('f');
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    drop(forward(reset(nullptr)));
    // reset（nullptr)不会记录r 因为时空 之后析构  之后forword记录f 最后drop记录d 记 fd
    problems[0] = std::move(RECORDS);

    forward(drop(reset(forward(forward(reset(nullptr))))));
    //reset 空指针不记录r 两次forwar 记录 ff reset记录 ffr 就会写入因为rest会重新创建  d
    problems[1] = std::move(RECORDS);

    drop(drop(reset(drop(reset(reset(nullptr))))));
    //reset 空指针不记录r  第二次的reset不是空记录记录 r 析构 d 就会d
    problems[2] = std::move(RECORDS);

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},
        // TODO: 分析 problems[1] 中资源的生命周期，将记录填入 `std::vector`
        // NOTICE: 此题结果依赖对象析构逻辑，平台相关，提交时以 CI 实际运行平台为准
        {"d", "ffr"},
        {"d", "d", "r"},
    };

    // ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            // NOTICE: 这里使用 std::
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}
