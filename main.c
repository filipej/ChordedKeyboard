#include <Windows.h>

static unsigned int keyCode;
static int pressed;

// The hex codes correspond to å, ä and ö when using a Swedish input method
static unsigned short keys[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	0xDD, 0xDE, 0xC0, VK_SPACE, VK_OEM_PERIOD
};

static LRESULT CALLBACK hookProc(int code, WPARAM wParam, LPARAM lParam);

int main()
{
	HHOOK kbHook = SetWindowsHookExW(WH_KEYBOARD_LL, hookProc, NULL, 0);

	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	UnhookWindowsHookEx(kbHook);
	return 0;
}

static unsigned int filterKey(unsigned int code)
{
	switch (code) {
	case 'F':
		return 16;
	case 'G':
		return 8;
	case 'H':
		return 4;
	case 'J':
		return 2;
	case VK_SPACE:
		return 1;
	default:
		return 0;
	}
}

static void buildInput(INPUT *inputs)
{
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = keys[keyCode - 1];
	inputs[0].ki.wScan = 0;
	inputs[0].ki.dwFlags = 0;
	inputs[0].ki.time = 0;
	inputs[0].ki.dwExtraInfo = GetMessageExtraInfo();

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = keys[keyCode - 1];
	inputs[1].ki.wScan = 0;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
	inputs[1].ki.time = 0;
	inputs[1].ki.dwExtraInfo = GetMessageExtraInfo();
}

static LRESULT CALLBACK hookProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
		return CallNextHookEx(NULL, code, wParam, lParam);

	KBDLLHOOKSTRUCT *kbData = (KBDLLHOOKSTRUCT *)lParam;

	// The "scancode != 0" check is a hack to get around the fact that sent keys
	// also get intercepted by the keyboard hook
	unsigned int key = filterKey(kbData->vkCode);
	if (key != 0 && kbData->scanCode != 0) {
		if (wParam == WM_KEYDOWN) {
			if (!(keyCode & key)) {
				keyCode |= key;
				pressed = TRUE;
			}
		} else if (wParam == WM_KEYUP) {
			if (pressed) {
				if (keyCode - 1 < sizeof(keys) / sizeof(keys[0])) {
					INPUT inputs[2];
					buildInput(inputs);
					SendInput(2, inputs, sizeof(inputs[0]));
				} else {
					// Bad key, shoud this send anything?
				}
			}

			keyCode &= ~key;
			pressed = FALSE;
		}

		return 1;
	} else {
		return 0;
	}
}
