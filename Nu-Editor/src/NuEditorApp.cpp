#include <Nu.h>
#include <Nu/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Nu {

	class NuEditor : public Application
	{
	public:
		NuEditor()
			:Application("Nu Editor")
		{
			PushLayer(new EditorLayer());
		}

		~NuEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new NuEditor();
	}

}