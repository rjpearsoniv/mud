//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.tool;
#else
#include <obj/Any.h>
#include <pool/ObjectPool.h>
#include <lang/Lua.h>
#include <lang/VisualScript.h>
#include <ui/Edit/Console.h>
#include <uio/Edit/Inspector.h>
#include <uio/Edit/UiEdit.h>
#include <tool/Types.h>
#include <tool/EditContext.h>
#include <gfx-ui/GfxEdit.h>
#include <tool/Brush.h>
#endif

namespace mud
{
	EditContext::EditContext(GfxSystem& gfx_system)
		: m_gfx_system(gfx_system)
		, m_undo_tool(m_tool_context)
		, m_redo_tool(m_tool_context)
		, m_work_plane() //vec3(0.f, 10.f, 0.f), Entity::FrontVector, Entity::RightVector)
		, m_translate_tool(m_tool_context)
		, m_rotate_tool(m_tool_context)
		, m_scale_tool(m_tool_context)
		//, m_place_brush(m_tool_context)
	{
		m_tool_context.m_action_stack = &m_action_stack;
	}

	EditContext::~EditContext()
	{}

	void EditContext::set_tool(ViewportTool& tool, Viewer& viewer)
	{
		UNUSED(viewer);
		m_tool = &tool;
		m_spatial_tool = try_as<SpatialTool>(tool);
	}

	void brush_preview(Widget& parent, Brush& brush)
	{
		UNUSED(brush);
		Widget& self = ui::stack(parent);
		UNUSED(self);
	}

	void brush_options(Widget& parent, Brush& brush)
	{
		brush_preview(parent, brush);
		object_edit(parent, Ref(&brush));
	}

	void current_brush_edit(Widget& parent, EditContext& context)
	{
		Widget& self = section(parent, "Current Brush");
		if(context.m_brush)
			brush_options(self, *context.m_brush);
	}

	bool edit_tool(Widget& parent, Tool& tool, cstring icon)
	{
		Widget& self = ui::toolbutton(parent, icon);
		self.set_state(ACTIVE, tool.m_state == ToolState::Active);
		return self.activated();
	}
		
	void tools_transform(Widget& toolbar, EditContext& context)
	{
		//if(edit_tool(toolbar, "(empty)"))
		//	context.m_tool = nullptr;
		if(edit_tool(toolbar, context.m_undo_tool, "(undo)"))
			context.m_undo_tool.activate();
		if(edit_tool(toolbar, context.m_redo_tool, "(redo)"))
			context.m_redo_tool.activate();
		if(edit_tool(toolbar, context.m_translate_tool, "(translate)"))
			context.set_tool(context.m_translate_tool, *context.m_viewer);
		if(edit_tool(toolbar, context.m_rotate_tool, "(rotate)"))
			context.set_tool(context.m_rotate_tool, *context.m_viewer);
		if(edit_tool(toolbar, context.m_scale_tool, "(scale)"))
			context.set_tool(context.m_scale_tool, *context.m_viewer);

		for(auto& brush : context.m_custom_brushes)
			if(edit_tool(toolbar, *brush, brush->m_name.c_str()))
			{
				context.set_tool(*brush, *context.m_viewer);
				context.m_brush = brush.get();
			}
	}

	void edit_transform(Widget& parent, EditContext& context)
	{
		Widget& self = ui::toolbar(parent);
		tools_transform(self, context);

		if(context.m_brush)
			brush_options(parent, *context.m_brush);
	}

	void console_view(Widget& parent, LuaInterpreter& lua)
	{
		static string feed = "console v0.1";
		static string line = "type lua code here";
		static string command = "";

		ui::console(parent, feed, line, command, 18);
		if(command != "")
		{
			lua.call(command.c_str());
			feed += "\n<< " + lua.flush();
			command = "";
		}
	}

	void object_editor(Widget& parent, const std::vector<Ref>& selection)
	{
		Widget& self = section(parent, "Inspector");

		if(!selection.empty() && selection[0])
		{
			Ref selected = selection[0];
			Widget& sheet = ui::widget(*self.m_body, styles().sheet, (void*)selected.m_value);
			object_edit(sheet, selected);
		}
	}

	void edit_tools(Widget& screen, Docker& docker, EditContext& context)
	{
		context.m_tool_context.m_action_stack = &context.m_action_stack;
		context.m_tool_context.m_work_plane = &context.m_work_plane;

		//if(Widget* dock = ui::dockitem(dockbar, "Library", { 0 }))
		//	library_section(section, { &type<World>(), &type<Entity>() }, game.m_selection);
		if(Widget* dock = ui::dockitem(docker, "Inspect", carray<uint16_t, 1>{ 2U }))
			object_editor(*dock, context.m_selection);
		if(Widget* dock = ui::dockitem(docker, "Edit", carray<uint16_t, 1>{ 3U }))
			edit_transform(*dock, context);
		if(Widget* dock = ui::dockitem(docker, "Script", carray<uint16_t, 1>{ 4U }))
			script_editor(*dock, context.m_script_editor);
		//if(Widget* dock = ui::dockitem(*context.m_dockbar, "VisualScript", carray<uint16_t, 1>{ 5U }))
		//	visual_script_edit(self, shell.m_editor.m_script_editor);
		if(Widget* dock = ui::dockitem(docker, "Gfx", carray<uint16_t, 1>{ 6U }))
			edit_gfx_system(*dock, context.m_gfx_system);
		if(Widget* dock = ui::dockitem(docker, "Ui", carray<uint16_t, 1>{ 7U }))
			ui_debug(*dock, screen);

		if(context.m_spatial_tool && context.m_viewer)
			context.m_spatial_tool->process(*context.m_viewer, context.m_selection);
	}

	void edit_tools(Widget& screen, EditContext& context)
	{
		edit_tools(screen, *context.m_dockbar, context);
	}

	void edit_context(Widget& parent, EditContext& context, bool tools)
	{
		Widget& board = ui::board(parent);
		context.m_screen = &ui::board(board);
		context.m_dockbar = &ui::dockbar(board, context.m_docksystem);

		if(tools)
			edit_tools(*context.m_screen, context);
	}
}
