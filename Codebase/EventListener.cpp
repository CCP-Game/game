#include "EventListener.h"

// Static variable to store the pressed key
int EventListener::pressedKey = -1;

void EventListener::MainLoop() {
    MSG msg;
	std::cout << "pressedKey mainloop : " << pressedKey << std::endl;
    while (GetMessage(&msg, NULL, 0, 0)) {
		std::cout << "Message received: " << msg.message << std::endl;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
		std::cout << "Current pressedKey: " << pressedKey << std::endl;

        if (pressedKey != -1) {
            std::cout << "Breaking MainLoop with key: " << pressedKey << std::endl;
            break;
        }
    }
	std::cout << "after loop: " << pressedKey << std::endl;
}

LRESULT CALLBACK EventListener::CaptureKeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam) {
    // Log nCode for debugging purposes


    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;

        // if (GetForegroundWindow() == GetConsoleWindow()) {
        //     std::cout << "Console window in focus." << std::endl;
			
            // Log wParam to see if we are catching the key down event
            std::cout << "Inside CaptureKeyboardEvent: nCode: " << nCode << ", wParam: " << wParam << std::endl;

            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                // Capture the key that was pressed and store it
                pressedKey = pKeyboard->vkCode;
                std::cout << "pressedKey: " << pressedKey << std::endl;
				

                // If ESC is pressed, exit program
                if (pKeyboard->vkCode == VK_ESCAPE) {
                    PostQuitMessage(0);
                }

                // Stop further hook processing once a key is captured
                return 1;
            }
       // }
    }
    // Return from event and pass to next hook in the chain
    //std::cout << "Return from event: " << nCode << std::endl;
	//std::cout << "pressedKey: " << pressedKey << std::endl;
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// Method to get the pressed key
int EventListener::getPressedKey()
{
    int key = pressedKey;
    pressedKey = -1;  // Reset after returning key
	std::cout << "getPressedKey: " << key << std::endl;
    return key;
}





// #include "EventListener.h"

// void EventListener::MainLoop()
// {
// 	MSG msg;
// 	while (GetMessage(&msg, NULL, 0, 0)) {
// 		TranslateMessage(&msg);
// 		DispatchMessage(&msg);
// 	}
// }

// LRESULT CALLBACK EventListener::CaptureKeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam) {
// 	if (nCode == HC_ACTION) {
// 		KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;

// 		if (GetForegroundWindow() == GetConsoleWindow()) {


// 			if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
// 				// if key press, pass the vkcall on
// 				callback(pKeyboard->vkCode);

// 				// Exit program
// 				if (pKeyboard->vkCode == VK_ESCAPE) {
// 					PostQuitMessage(0);
// 				}
// 			}
// 		}
// 	}
	
// 	return CallNextHookEx(NULL, nCode, wParam, lParam);
// }



// std::function<void(int)> EventListener::callback;