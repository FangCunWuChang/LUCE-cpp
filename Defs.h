#pragma once
#include "Macros.h"
#include <lua.hpp>
#include <JuceHeader.h>

/**
 * @brief		Register the LUCE class to Lua state as full userdata.
 * 
 * @param L		The Lua state which you want to register the class into.
 * @param t		The class which you want to register.
 */
#define LUCE_REG(L, t) t::__open(L, #t);

namespace luce {
	namespace utils {
		/**
		 * @brief		The base class of all LUCE_UserData classes.
		 */
		class LUCE_API LUCE_UserDataBase {
		public:
			virtual ~LUCE_UserDataBase() = default;
		};
	}

	/**
	 * @brief		The base class of all LUCE adapter classes which you want to register as Lua userdata.			\n
	 *				Some important methods about Lua userdata are defined in this class.
	 * 
	 * @tparam T	The LUCE adapter class which you want to register as Lua userdata.
	 * 
	 * @see			LUCE_UserDataBase
	 */
	template<class T>
	class LUCE_API LUCE_UserData : public utils::LUCE_UserDataBase {
	public:
		/**
		 * @brief		An lua_CFunction type method which will be called before userdata memory GC.		\n
		 *				In this method, the destructor of the userdata class will be called.				\n
		 *				This method will be registered in the metatable of the userdata.
		 */
		static int __gc(lua_State* L) {
			auto pInstance = reinterpret_cast<LUCE_UserDataBase*>(lua_touserdata(L, 1));
			pInstance->~LUCE_UserDataBase();
			return 0;
		};
		/**
		 * @brief		Register the LUCE adapter class to Lua state as full userdata.
		 * 
		 * @param L		The Lua state which you want to register the LUCE adapter class into.
		 * @param s		The name of the userdata you want to register the LUCE adapter class as.
		 */
		static int __open(lua_State* L, const char* s) {
			lua_getglobal(L, "luce");

			lua_getfield(L, -1, "adapters");

			lua_pushstring(L, s);
			reinterpret_cast<T*>(lua_newuserdata(L, sizeof(T)));

			lua_newtable(L);

			lua_pushcfunction(L, T::__new);
			lua_setfield(L, -2, "new");

			lua_pushvalue(L, -1);
			lua_setfield(L, -2, "__index");

			lua_setmetatable(L, -2);

			lua_settable(L, -3);

			return 0;
		};

	public:
		virtual ~LUCE_UserData() override = default;
	};
}