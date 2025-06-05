#include <thread>
#include <chrono>
#include "CommandExecutor.h"
#include<iostream>

int main() {
    CommandExecutor executor;

    // 让用户有时间切换到 PPT 放映模式
    std::cout << "10s开始自动控制 PowerPoint..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));


    while (true) {
        // 向右翻页（下一页）
        executor.ExecuteAction(ActionType::NextSlide);  
        std::cout << "下一页" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));

        // 向左翻页（上一页）
        executor.ExecuteAction(ActionType::PreviousSlide);
        std::cout << "上一页" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(6));
    }

    return 0;
}
