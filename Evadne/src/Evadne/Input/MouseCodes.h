#pragma once


namespace Evadne
{
	typedef enum class MouseCode : uint16_t
	{

		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}
#define EV_MOUSE_BUTTON_0      ::Evadne::Mouse::Button0
#define EV_MOUSE_BUTTON_1      ::Evadne::Mouse::Button1
#define EV_MOUSE_BUTTON_2      ::Evadne::Mouse::Button2
#define EV_MOUSE_BUTTON_3      ::Evadne::Mouse::Button3
#define EV_MOUSE_BUTTON_4      ::Evadne::Mouse::Button4
#define EV_MOUSE_BUTTON_5      ::Evadne::Mouse::Button5
#define EV_MOUSE_BUTTON_6      ::Evadne::Mouse::Button6
#define EV_MOUSE_BUTTON_7      ::Evadne::Mouse::Button7
#define EV_MOUSE_BUTTON_LAST   ::Evadne::Mouse::ButtonLast
#define EV_MOUSE_BUTTON_LEFT   ::Evadne::Mouse::ButtonLeft
#define EV_MOUSE_BUTTON_RIGHT  ::Evadne::Mouse::ButtonRight
#define EV_MOUSE_BUTTON_MIDDLE ::Evadne::Mouse::ButtonMiddle