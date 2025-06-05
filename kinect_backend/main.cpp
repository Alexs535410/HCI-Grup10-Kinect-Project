#include <thread>
#include <chrono>
#include "CommandExecutor.h"
#include<iostream>

int main() {
    CommandExecutor executor;

    // ���û���ʱ���л��� PPT ��ӳģʽ
    std::cout << "10s��ʼ�Զ����� PowerPoint..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));


    while (true) {
        // ���ҷ�ҳ����һҳ��
        executor.ExecuteAction(ActionType::NextSlide);  
        std::cout << "��һҳ" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));

        // ����ҳ����һҳ��
        executor.ExecuteAction(ActionType::PreviousSlide);
        std::cout << "��һҳ" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(6));
    }

    return 0;
}
