

#pragma once

#ifndef MUD_MODULES
#include <meta/gfx-ui/Module.h>

#include <obj/Any.h>
#include <obj/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_gfx_ui_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    
    // Sequences
    
    
    
    
    
    
    
    
    
        
    // mud::ViewerController
    {
        static Meta meta = { type<mud::ViewerController>(), &namspc({ "mud" }), "ViewerController", sizeof(mud::ViewerController), TypeClass::Object };
        static Class cls = { type<mud::ViewerController>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::ViewerController>();
    }
    
    
    
        
    // mud::SpaceSheet
    {
        static Meta meta = { type<mud::SpaceSheet>(), &namspc({ "mud" }), "SpaceSheet", sizeof(mud::SpaceSheet), TypeClass::Object };
        static Class cls = { type<mud::SpaceSheet>(),
            // bases
            { &type<mud::Ui>() },
            { base_offset<mud::SpaceSheet, mud::Ui>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::SpaceSheet>();
    }
    
    
        
    // mud::Viewer
    {
        static Meta meta = { type<mud::Viewer>(), &namspc({ "mud" }), "Viewer", sizeof(mud::Viewer), TypeClass::Object };
        static Class cls = { type<mud::Viewer>(),
            // bases
            { &type<mud::Widget>() },
            { base_offset<mud::Viewer, mud::Widget>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_scene), type<mud::Scene>(), "scene", Ref(type<mud::Scene>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_viewport), type<mud::Viewport>(), "viewport", Ref(type<mud::Viewport>()), Member::None, nullptr },
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_position), type<mud::vec2>(), "position", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::Viewer>(), member_address(&mud::Viewer::m_size), type<mud::vec2>(), "size", var(mud::vec2()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Viewer>();
    }
    
    
        
    // mud::SceneViewer
    {
        static Meta meta = { type<mud::SceneViewer>(), &namspc({ "mud" }), "SceneViewer", sizeof(mud::SceneViewer), TypeClass::Object };
        static Class cls = { type<mud::SceneViewer>(),
            // bases
            { &type<mud::Scene>(), &type<mud::Viewer>() },
            { base_offset<mud::SceneViewer, mud::Scene>(), base_offset<mud::SceneViewer, mud::Viewer>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::SceneViewer>();
    }
    
    
    
        
    // mud::FreeOrbitController
    {
        static Meta meta = { type<mud::FreeOrbitController>(), &namspc({ "mud" }), "FreeOrbitController", sizeof(mud::FreeOrbitController), TypeClass::Object };
        static Class cls = { type<mud::FreeOrbitController>(),
            // bases
            { &type<mud::OrbitController>() },
            { base_offset<mud::FreeOrbitController, mud::OrbitController>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::FreeOrbitController>();
    }
    
    
        
    // mud::OrbitController
    {
        static Meta meta = { type<mud::OrbitController>(), &namspc({ "mud" }), "OrbitController", sizeof(mud::OrbitController), TypeClass::Object };
        static Class cls = { type<mud::OrbitController>(),
            // bases
            { &type<mud::ViewerController>() },
            { base_offset<mud::OrbitController, mud::ViewerController>() },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::OrbitController>();
    }
    

    
        m.m_types.push_back(&type<mud::ViewerController>());
        m.m_types.push_back(&type<mud::SpaceSheet>());
        m.m_types.push_back(&type<mud::Viewer>());
        m.m_types.push_back(&type<mud::SceneViewer>());
        m.m_types.push_back(&type<mud::FreeOrbitController>());
        m.m_types.push_back(&type<mud::OrbitController>());
    
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::viewer(val<mud::Widget>(args[0]), val<mud::Scene>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "scene", Ref(type<mud::Scene>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "viewer", function_id<mud::Viewer&(*)(mud::Widget&, mud::Scene&)>(&mud::ui::viewer), func, params, Ref(type<mud::Viewer>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::scene_viewer(val<mud::Widget>(args[0]), val<mud::vec2>(args[1]))); };
            std::vector<Param> params = { { "parent", Ref(type<mud::Widget>()) }, { "size", var(mud::vec2()), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "scene_viewer", function_id<mud::SceneViewer&(*)(mud::Widget&, const mud::vec2&)>(&mud::ui::scene_viewer), func, params, Ref(type<mud::SceneViewer>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::orbit_controller(val<mud::Viewer>(args[0]), val<float>(args[1]), val<float>(args[2]), val<float>(args[3]))); };
            std::vector<Param> params = { { "viewer", Ref(type<mud::Viewer>()) }, { "yaw", var(float(0.f)), Param::Default }, { "pitch", var(float(0.f)), Param::Default }, { "distance", var(float(1.f)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "orbit_controller", function_id<mud::OrbitController&(*)(mud::Viewer&, float, float, float)>(&mud::ui::orbit_controller), func, params, Ref(type<mud::OrbitController>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::free_orbit_controller(val<mud::Viewer>(args[0]))); };
            std::vector<Param> params = { { "viewer", Ref(type<mud::Viewer>()) } };
            static Function f = { &namspc({ "mud", "ui" }), "free_orbit_controller", function_id<mud::FreeOrbitController&(*)(mud::Viewer&)>(&mud::ui::free_orbit_controller), func, params, Ref(type<mud::FreeOrbitController>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::isometric_controller(val<mud::Viewer>(args[0]), val<bool>(args[1]))); };
            std::vector<Param> params = { { "viewer", Ref(type<mud::Viewer>()) }, { "topdown", var(bool(false)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "isometric_controller", function_id<mud::OrbitController&(*)(mud::Viewer&, bool)>(&mud::ui::isometric_controller), func, params, Ref(type<mud::OrbitController>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::ui::hybrid_controller(val<mud::Viewer>(args[0]), val<mud::ui::OrbitMode>(args[1]), val<mud::Transform>(args[2]), val<bool>(args[3]), val<float>(args[4]))); };
            std::vector<Param> params = { { "viewer", Ref(type<mud::Viewer>()) }, { "mode", var(mud::ui::OrbitMode()) }, { "entity", var(mud::Transform()) }, { "aiming", var(bool()) }, { "pitch", var(float()) } };
            static Function f = { &namspc({ "mud", "ui" }), "hybrid_controller", function_id<mud::OrbitController&(*)(mud::Viewer&, mud::ui::OrbitMode, mud::Transform&, bool&, float&)>(&mud::ui::hybrid_controller), func, params, Ref(type<mud::OrbitController>()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::ui::velocity_controller(val<mud::Viewer>(args[0]), val<mud::vec3>(args[1]), val<mud::vec3>(args[2]), val<float>(args[3])); };
            std::vector<Param> params = { { "viewer", Ref(type<mud::Viewer>()) }, { "linear", var(mud::vec3()) }, { "angular", var(mud::vec3()) }, { "speed", var(float(1.f)), Param::Default } };
            static Function f = { &namspc({ "mud", "ui" }), "velocity_controller", function_id<void(*)(mud::Viewer&, mud::vec3&, mud::vec3&, float)>(&mud::ui::velocity_controller), func, params, Var() };
            m.m_functions.push_back(&f);
        }
    }
}
