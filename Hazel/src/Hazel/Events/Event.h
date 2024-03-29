#pragma once

#include "Hazel/Core.h"
#include "hzpch.h"

namespace Hazel {

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{

		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return EventType::##type; }\
																virtual EventType GetEventType() const override {return GetStaticType();}\
																virtual const char* GetName() const override {return #type;}	
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


	class  Event
	{
		

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	
		bool m_Handled = false;
	};

	// Class Event Dispatcher
	class EventDispatcher
	{
		// Define EventFunc() Template
		// With T& input and return bool
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		// Bind the event to this Dispatcher,
		// Each Dispatcher can only Dispatch 1 Event
		EventDispatcher(Event& event)
			:m_Event(event) {}

		// Make a template function to Dispatch the event
		// The input parameter is a Function
		template<typename T>
		bool Dispatch(EventFunc<T> Func) {
			// Check if the Event Type of the Event bond to this dispatcher
			// matches with the function we are using.
			// Because if they are not the same type, then we cannot guarantee
			// that the function is actually valid.
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// Whatever it is, this certain function of this Event will be called,
				// And the function will decide whether to consume the event or not.
				m_Event.m_Handled = Func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}



}