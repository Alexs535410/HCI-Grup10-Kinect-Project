// CommandExecutor.cpp
#include "CommandExecutor.h"
#include <Windows.h>

void CommandExecutor::ExecuteAction(ActionType action) {
    switch (action) {
    case ActionType::NextSlide:  // ģ�ⰴ�Ҽ�
        keybd_event(VK_RIGHT, 0, 0, 0);
        keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
        break;

    case ActionType::PreviousSlide:  // ģ�ⰴ���
        keybd_event(VK_LEFT, 0, 0, 0);
        keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
        break;

    default:
        break;
    }
}
