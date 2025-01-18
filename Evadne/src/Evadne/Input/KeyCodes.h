#pragma once

namespace Evadne {

	typedef enum class KeyCode : uint16_t
	{

		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
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
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
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
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}

}

#define EV_KEY_SPACE           ::Evadne::Key::Space
#define EV_KEY_APOSTROPHE      ::Evadne::Key::Apostrophe    /* ' */
#define EV_KEY_COMMA           ::Evadne::Key::Comma         /* , */
#define EV_KEY_MINUS           ::Evadne::Key::Minus         /* - */
#define EV_KEY_PERIOD          ::Evadne::Key::Period        /* . */
#define EV_KEY_SLASH           ::Evadne::Key::Slash         /* / */
#define EV_KEY_0               ::Evadne::Key::D0
#define EV_KEY_1               ::Evadne::Key::D1
#define EV_KEY_2               ::Evadne::Key::D2
#define EV_KEY_3               ::Evadne::Key::D3
#define EV_KEY_4               ::Evadne::Key::D4
#define EV_KEY_5               ::Evadne::Key::D5
#define EV_KEY_6               ::Evadne::Key::D6
#define EV_KEY_7               ::Evadne::Key::D7
#define EV_KEY_8               ::Evadne::Key::D8
#define EV_KEY_9               ::Evadne::Key::D9
#define EV_KEY_SEMICOLON       ::Evadne::Key::Semicolon     /* ; */
#define EV_KEY_EQUAL           ::Evadne::Key::Equal         /* = */
#define EV_KEY_A               ::Evadne::Key::A
#define EV_KEY_B               ::Evadne::Key::B
#define EV_KEY_C               ::Evadne::Key::C
#define EV_KEY_D               ::Evadne::Key::D
#define EV_KEY_E               ::Evadne::Key::E
#define EV_KEY_F               ::Evadne::Key::F
#define EV_KEY_G               ::Evadne::Key::G
#define EV_KEY_H               ::Evadne::Key::H
#define EV_KEY_I               ::Evadne::Key::I
#define EV_KEY_J               ::Evadne::Key::J
#define EV_KEY_K               ::Evadne::Key::K
#define EV_KEY_L               ::Evadne::Key::L
#define EV_KEY_M               ::Evadne::Key::M
#define EV_KEY_N               ::Evadne::Key::N
#define EV_KEY_O               ::Evadne::Key::O
#define EV_KEY_P               ::Evadne::Key::P
#define EV_KEY_Q               ::Evadne::Key::Q
#define EV_KEY_R               ::Evadne::Key::R
#define EV_KEY_S               ::Evadne::Key::S
#define EV_KEY_T               ::Evadne::Key::T
#define EV_KEY_U               ::Evadne::Key::U
#define EV_KEY_V               ::Evadne::Key::V
#define EV_KEY_W               ::Evadne::Key::W
#define EV_KEY_X               ::Evadne::Key::X
#define EV_KEY_Y               ::Evadne::Key::Y
#define EV_KEY_Z               ::Evadne::Key::Z
#define EV_KEY_LEFT_BRACKET    ::Evadne::Key::LeftBracket   /* [ */
#define EV_KEY_BACKSLASH       ::Evadne::Key::Backslash     /* \ */
#define EV_KEY_RIGHT_BRACKET   ::Evadne::Key::RightBracket  /* ] */
#define EV_KEY_GRAVE_ACCENT    ::Evadne::Key::GraveAccent   /* ` */
#define EV_KEY_WORLD_1         ::Evadne::Key::World1        /* non-US #1 */
#define EV_KEY_WORLD_2         ::Evadne::Key::World2        /* non-US #2 */

/* Function keys */
#define EV_KEY_ESCAPE          ::Evadne::Key::Escape
#define EV_KEY_ENTER           ::Evadne::Key::Enter
#define EV_KEY_TAB             ::Evadne::Key::Tab
#define EV_KEY_BACKSPACE       ::Evadne::Key::Backspace
#define EV_KEY_INSERT          ::Evadne::Key::Insert
#define EV_KEY_DELETE          ::Evadne::Key::Delete
#define EV_KEY_RIGHT           ::Evadne::Key::Right
#define EV_KEY_LEFT            ::Evadne::Key::Left
#define EV_KEY_DOWN            ::Evadne::Key::Down
#define EV_KEY_UP              ::Evadne::Key::Up
#define EV_KEY_PAGE_UP         ::Evadne::Key::PageUp
#define EV_KEY_PAGE_DOWN       ::Evadne::Key::PageDown
#define EV_KEY_HOME            ::Evadne::Key::Home
#define EV_KEY_END             ::Evadne::Key::End
#define EV_KEY_CAPS_LOCK       ::Evadne::Key::CapsLock
#define EV_KEY_SCROLL_LOCK     ::Evadne::Key::ScrollLock
#define EV_KEY_NUM_LOCK        ::Evadne::Key::NumLock
#define EV_KEY_PRINT_SCREEN    ::Evadne::Key::PrintScreen
#define EV_KEY_PAUSE           ::Evadne::Key::Pause
#define EV_KEY_F1              ::Evadne::Key::F1
#define EV_KEY_F2              ::Evadne::Key::F2
#define EV_KEY_F3              ::Evadne::Key::F3
#define EV_KEY_F4              ::Evadne::Key::F4
#define EV_KEY_F5              ::Evadne::Key::F5
#define EV_KEY_F6              ::Evadne::Key::F6
#define EV_KEY_F7              ::Evadne::Key::F7
#define EV_KEY_F8              ::Evadne::Key::F8
#define EV_KEY_F9              ::Evadne::Key::F9
#define EV_KEY_F10             ::Evadne::Key::F10
#define EV_KEY_F11             ::Evadne::Key::F11
#define EV_KEY_F12             ::Evadne::Key::F12
#define EV_KEY_F13             ::Evadne::Key::F13
#define EV_KEY_F14             ::Evadne::Key::F14
#define EV_KEY_F15             ::Evadne::Key::F15
#define EV_KEY_F16             ::Evadne::Key::F16
#define EV_KEY_F17             ::Evadne::Key::F17
#define EV_KEY_F18             ::Evadne::Key::F18
#define EV_KEY_F19             ::Evadne::Key::F19
#define EV_KEY_F20             ::Evadne::Key::F20
#define EV_KEY_F21             ::Evadne::Key::F21
#define EV_KEY_F22             ::Evadne::Key::F22
#define EV_KEY_F23             ::Evadne::Key::F23
#define EV_KEY_F24             ::Evadne::Key::F24
#define EV_KEY_F25             ::Evadne::Key::F25

/* Keypad */
#define EV_KEY_KP_0            ::Evadne::Key::KP0
#define EV_KEY_KP_1            ::Evadne::Key::KP1
#define EV_KEY_KP_2            ::Evadne::Key::KP2
#define EV_KEY_KP_3            ::Evadne::Key::KP3
#define EV_KEY_KP_4            ::Evadne::Key::KP4
#define EV_KEY_KP_5            ::Evadne::Key::KP5
#define EV_KEY_KP_6            ::Evadne::Key::KP6
#define EV_KEY_KP_7            ::Evadne::Key::KP7
#define EV_KEY_KP_8            ::Evadne::Key::KP8
#define EV_KEY_KP_9            ::Evadne::Key::KP9
#define EV_KEY_KP_DECIMAL      ::Evadne::Key::KPDecimal
#define EV_KEY_KP_DIVIDE       ::Evadne::Key::KPDivide
#define EV_KEY_KP_MULTIPLY     ::Evadne::Key::KPMultiply
#define EV_KEY_KP_SUBTRACT     ::Evadne::Key::KPSubtract
#define EV_KEY_KP_ADD          ::Evadne::Key::KPAdd
#define EV_KEY_KP_ENTER        ::Evadne::Key::KPEnter
#define EV_KEY_KP_EQUAL        ::Evadne::Key::KPEqual

#define EV_KEY_LEFT_SHIFT      ::Evadne::Key::LeftShift
#define EV_KEY_LEFT_CONTROL    ::Evadne::Key::LeftControl
#define EV_KEY_LEFT_ALT        ::Evadne::Key::LeftAlt
#define EV_KEY_LEFT_SUPER      ::Evadne::Key::LeftSuper
#define EV_KEY_RIGHT_SHIFT     ::Evadne::Key::RightShift
#define EV_KEY_RIGHT_CONTROL   ::Evadne::Key::RightControl
#define EV_KEY_RIGHT_ALT       ::Evadne::Key::RightAlt
#define EV_KEY_RIGHT_SUPER     ::Evadne::Key::RightSuper
#define EV_KEY_MENU            ::Evadne::Key::Menu
