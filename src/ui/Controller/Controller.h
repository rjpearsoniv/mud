//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#include <ctx/KeyCode.h>
#include <ctx/InputDispatcher.h>
#endif
#include <ui/Forward.h>

#ifndef MUD_CPP_20
#include <map>
#include <functional>
#endif

namespace mud
{
	export_ struct MUD_UI_EXPORT KeyCombo
	{
		KeyCombo(KeyCode key) : m_modifier(InputModifier::Any), m_key(key) {}
		KeyCombo(InputModifier modifier, KeyCode key) : m_modifier(modifier), m_key(key) {}
		InputModifier m_modifier;
		KeyCode m_key;
		uint64_t value() const { return (uint64_t)m_modifier << 32 | m_key; }
		friend bool operator<(const KeyCombo& lhs, const KeyCombo& rhs) { return lhs.value() < rhs.value(); }
	};

	export_ class MUD_UI_EXPORT EventDispatch
	{
	public:
		EventDispatch();

		virtual void process(Widget& widget);
		
		typedef std::function<void()> KeyHandler;
		//EventMap<KeyHandler> m_handlers;

		std::map<KeyCombo, KeyHandler> m_key_down_handlers;
		std::map<KeyCombo, KeyHandler> m_key_up_handlers;
	};
}
