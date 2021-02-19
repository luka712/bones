#pragma once

#ifndef IENTITY_H

#define IENTITY_H

#include "core_types.h"
#include "EventHandler.hpp"

namespace Bones
{

	/// <summary>
	/// Every resource is an entity. Meaning it has some default interface actions.
	/// It has id by default.
	/// </summary>
	class IEntity
	{
	public:
		// -- interface variables

		// the id
		const Guid m_id;

		// the bane 
		std::string m_name = "";

		// resource current state.
		State m_state = State::New;

		// -- events

		// Event handler which is fired after entity is loaded.
		Bones::EventHandler<> m_onLoadedEventHandler;

		// Event handler which is fired after the entity is initialized.
		Bones::EventHandler<> m_onInitializedEventHandler;

		// Event handler which is fired when destroy of entity is called.
		Bones::EventHandler<> m_onDestroyEventHandler;

		// -- interface methods

		/// <summary>
		/// Very first method called, right after resource constructor.
		/// </summary>
		virtual void Load() = 0;

		/// <summary>
		/// After asset as are Loaded ( Load ), Initialize is called.
		/// </summary>
		virtual void Initialize() = 0;

		/// <summary>
		/// Called before destruction of Entity. Resources should be released in destroy.
		/// </summary>
		virtual void Destroy() = 0;

		/// <summary>
		/// Return resource as string. Every resource should have identifier.
		/// </summary>
		/// <returns>Constant string.</returns>
		virtual const std::string Type() const = 0;
	};

}

#endif // !IENTITY_H
