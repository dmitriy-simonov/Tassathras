#pragma once
#include <cstdint>

namespace Tassathras
{
	using KeyCode = uint16_t;

	namespace Keyboard
	{
		enum : KeyCode
		{
			Q = 81,
			E = 69,
			W = 87,
			A = 65,
			S = 83,
			D = 68,
			G = 71,


			Key_0 = 48,
			Key_1 = 49,
			Key_2 = 50,
			Key_3 = 51,
			Key_4 = 52,
			Key_5 = 53,
			Key_6 = 54,
			Key_7 = 55,
			Key_8 = 56,
			Key_9 = 57,

			Space = 32,
			Escape = 256,
			Enter = 257,
			Tab = 258,
			Backspace = 259,
			Insert = 260,
			Delete = 261,
			Right = 262,
			Left = 263,
			Down = 264,
			Up = 265,

			F1 = 290,
			F2 = 291,
			F3 = 292,
			F4 = 293,
			F5 = 294,
			F6 = 295,
			F7 = 296,
			F8 = 297,
			F9 = 298,
			F10 = 299,
			F11 = 300,
			F12 = 301,

			LeftShift = 340,
			LeftControl = 341,
			LeftAlt = 342,
			LeftSuper = 343,
			RightShift = 344,
			RightControl = 345,
			RightAlt = 346,
			RightSuper = 347
		};
	}

	namespace Mouse
	{
		enum : KeyCode
		{
			ButtonLeft = 0,
			ButtonRight = 1,
			ButtonMiddle = 2,
			Button4 = 3,
			Button5 = 4,
			Button6 = 5,
			Button7 = 6,
			Button8 = 7
		};
	}
}