#pragma once

#include <mud/Forward.h>
#include <mud/mud.h>

namespace mud
{
	using Selection = std::vector<Ref>;

	class Shell : public NonCopy
	{
	public:
		Shell(array<cstring> resource_paths, int argc, char *argv[]);
		~Shell();

		void init();
		void run(const std::function<void(Shell&)>& func, size_t iterations = 0U);
		bool pump();

	public:
		string m_exec_path;
		string m_resource_path;

		User m_user;

		GfxSystem m_gfx_system;
		LuaInterpreter m_lua;
		WrenInterpreter m_wren;
		EditContext m_editor;

		unique_ptr<Context> m_context = nullptr;
		unique_ptr<Vg> m_vg = nullptr;
		unique_ptr<UiWindow> m_ui_window = nullptr;
		Ui* m_ui = nullptr;

		std::function<void(Shell&)> m_pump;
	};
}

