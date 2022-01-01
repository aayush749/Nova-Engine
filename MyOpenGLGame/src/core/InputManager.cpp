#include "InputManager.h"

namespace InputManager {
	bool KeyBoard::s_IsKeyBoardSetUp = false;
	bool KeyBoard::s_Keys[];
	
	bool Mouse::s_IsMouseSetUp = false;
	bool Mouse::s_Buttons[];
	
	bool MouseCursor::s_IsMouseCursorSetUp = false;
	double MouseCursor::s_XPos = 0.0;
	double MouseCursor::s_YPos = 0.0;
}