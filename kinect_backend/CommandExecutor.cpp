// CommandExecutor.cpp
#include "CommandExecutor.h"
#include <Windows.h>

void CommandExecutor::ExecuteAction(ActionType action) {
    switch (action) {
    case ActionType::NextSlide:  // 模拟按右键
        keybd_event(VK_RIGHT, 0, 0, 0);
        keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
        break;

    case ActionType::PreviousSlide:  // 模拟按左键
        keybd_event(VK_LEFT, 0, 0, 0);
        keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
        break;

    default:
        break;
    }
}
