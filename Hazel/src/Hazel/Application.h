#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "hzpch.h"
#include <stdio.h>

namespace Hazel {
	class  HAZEL_API  Application
	{
	public:
		Application();
		
		virtual~Application();

		void Run();

	};
	//TO be define in client
	Application* CreateApplication();

}

