#pragma once

#include <lua.hpp>
#include <JuceHeader.h>

#include "Macros.h"
#include "Defs-internal.h"
#include "Debug.h"

/**
 * @brief		Get the name of the type or function.
 * 
 * @param t		The type or function which you want to get name.
 * 
 * @return		The name of the type or function as a const char pointer.
 */
#define LUCE_NAME(t)				#t

/**
 * @brief		Register the LUCE class to Lua state as full userdata.
 * 
 * @param L		The Lua state which you want to register the class into.
 * @param t		The class which you want to register.
 */
#define LUCE_REG(L, t)		LUCE_Adapter<t>::__open(L, LUCE_NAME(t))

/**
 * @brief		Try.
 */
#define LUCE_TRY try
/**
 * @brief		Catch execptions then print the message, close the state and return -1.
 * 
 * @param L		The Lua state which you want to close when exection caught.
 */
#define LUCE_CATCH_EXCEPTION(L) \
	catch (const std::exception& e) { printf("%s\n", e.what()); lua_close(L); return -1; } \
	catch (...)                     { printf("catch(...)\n"); lua_close(L); return -1; }

/**
 * @brief		Make a luaL_Reg value.
 * 
 * @param f		The name of the method.
 * 
 * @return		A luaL_Reg value.
 */
#define LUCE_TO_LUA_REG(f)						{LUCE_NAME(f), f}
/**
 * @brief		Make a empty luaL_Reg value as the end of the list.
 * 
 * @return		A luaL_Reg value has NULL value.
 */
#define LUCE_NULL_LUA_REG()						{NULL, NULL}

/**
 * @brief		Make a luaL_Reg value list if method list exists.
 * @attention	50 methods max.
 * 
 * @param ...	The method list.
 * 
 * @return		A list of luaL_Reg values.
 */
#define LUCE_MAKE_REG_LIST(...)					__VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL(__VA_ARGS__))
/**
 * @brief		Make a method list of the object class.
 * @attention	50 methods max.
 *
 * @param t		The name of the adapter class.
 * @param ...	The method list.
 */
#define LUCE_FUNCTION_LIST(t, ...)				luaL_Reg LUCE_Adapter<t>::__funcList[] = {LUCE_MAKE_REG_LIST(__VA_ARGS__) LUCE_NULL_LUA_REG()}

/**
 * @brief		Create a Lua userdata and push it on the top of the stack.
 * 
 * @param L		The Lua state.
 * @param t		The userdata type.
 * 
 * @return		The pointer of the userdata memory.
 */
#define LUCE_CREATE_USERDATA(L, t)						reinterpret_cast<t*>(lua_newuserdata(L, sizeof(t)))
/**
 * @brief		Check the param at ud if it is an userdata.
 *
 * @param L		The Lua state.
 * @param ud	The index of the arg on stack.
 * @param t		The userdata type.
 *
 * @return		The pointer of the userdata.
 */
#define LUCE_CHECK_USERDATA(L, ud, t)					reinterpret_cast<t*>(luaL_checkudata(L, ud, LUCE_NAME(t)))
/**
 * @brief		Get the metatable which has the same name of the type, 
 *				then set for the table or userdata on the top of the stack.
 * 
 * @param L		The Lua state whitch has a table or userdata on the top of the stack.
 * @param t		The userdata type.
 */
#define LUCE_SET_METATABLE(L, t) \
	luaL_getmetatable(L, LUCE_NAME(t)); \
	lua_setmetatable(L, -2);
/**
 * @brief		Create a Lua userdata and push it on the top of the stack, 
 *				then set the metatable as which has the same name of the type.
 *
 * @param L		The Lua state.
 * @param t		The userdata type.
 *
 * @return		The pointer of the userdata memory.
 */
#define LUCE_CREATE_USERDATA_WITH_METATABLE(L, t)		LUCE_CREATE_USERDATA(L, t); LUCE_SET_METATABLE(L, t)
/**
 * @brief		Construct the object object.
 * @attention	The type of the point must match the true type of the object.
 * 
 * @param p		The pointer of the object object.
 * @param ...	The arg list when the constructor function called.
 */
#define LUCE_INIT(p, ...) \
	new(p) std::remove_reference<decltype(*p)>::type(__VA_ARGS__)
/**
 * @brief		Create a Lua userdata and push it on the top of the stack,
 *				then set the metatable as which has the same name of the type.
 *				Then call the constructor of the object.
 *
 * @param L		The Lua state.
 * @param t		The userdata type.
 * @param p		The pointer of the object object.
 * @param ...	The arg list when the constructor function called.
 */
#define LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, t, p, ...) \
	auto p = LUCE_CREATE_USERDATA_WITH_METATABLE(L, t); \
	LUCE_INIT(p, __VA_ARGS__)

/**
 * @brief		Create a Lua type object create function.
 * 
 * @param t		The type of the object.
 */
#define LUCE_NEW_FUNCTION(t) \
	lua_State* LUCE_Adapter<t>::__lState = nullptr; \
	const char* LUCE_Adapter<t>::__name = nullptr; \
	int LUCE_Adapter<t>::__new(lua_State* L)

/**
 * @breif		Create a Lua CFunction.
 * 
 * @param n		Function name.
 */
#define LUCE_METHOD(n)									static int n(lua_State* L)

/**
 * @brief		Create LUCE object attributes and methods.
 */
#define LUCE_REF_DATA \
	private: \
		lua_State* __LUCEState = nullptr; \
		int __LUCERef = -1; \
	 \
	public: \
		lua_State*& LUCE_state() { return this->__LUCEState; }; \
		int& LUCE_ref() { return this->__LUCERef; }

/**
 * @brief		Get LUCE object reference of the object.
 * 
 * @param p		The object pointer.
 */
#define LUCE_OBJ_REF(p)									p->LUCE_ref()
/**
 * @brief		Get Lua state of the object.
 *
 * @param p		The object pointer.
 */
#define LUCE_OBJ_STATE(p)								p->LUCE_state()

/**
 * @brief		Get LUCE object reference.
 */
#define LUCE_GET_REF()									LUCE_OBJ_REF(this)
/**
 * @brief		Get Lua state.
 */
#define LUCE_GET_STATE()								LUCE_OBJ_STATE(this)


 /**
  * @brief		Push current Lua adapter object on stack top.
  *
  * @param L	The Lua state.
  * @param r	The obj reference.
  */
#define LUCE_PUSH_OBJ(L, r) \
	lua_getglobal(L, "luce"); \
	lua_getfield(L, -1, "__refs"); \
	 \
	lua_rawgeti(L, -1, r); \
	 \
	lua_remove(L, -2); \
	lua_remove(L, -2)

/**
 * @brief		Reference the object on stack and return the ref value.
 * 
 * @param L		The Lua state.
 * @param ud	The object index on stack.
 */
#define LUCE_REF(L, ud) \
	[L, udx = ud] { \
		lua_getglobal(L, "luce"); \
		lua_getfield(L, -1, "__refs"); \
		 \
		lua_pushvalue(L, udx - 2); \
		int result = luaL_ref(L, -2); \
		 \
		lua_pop(L, 2); \
		return result; \
	}()

namespace luce {
	namespace utils {
		/**
		 * @brief		The base class of all LUCE_UserData classes.
		 */
		class LUCE_API LUCE_AdapterBase {
		public:
			virtual ~LUCE_AdapterBase() = default;
		};
	}

	/**
	 * @brief		The base class of all LUCE adapter classes which you want to register as Lua userdata.			\n
	 *				Some important methods about Lua userdata are defined in this class.
	 *
	 * @tparam T	The LUCE adapter class which you want to register as Lua userdata.
	 *
	 * @see			LUCE_AdapterBase
	 */
	template<class T>
	class LUCE_API LUCE_Adapter : public utils::LUCE_AdapterBase {
	public:
		/**
		 * @brief		An lua_CFunction type method which will be called before userdata memory GC.		\n
		 *				In this method, the destructor of the adapter class will be called.				\n
		 *				This method will be registered in the metatable of the userdata.
		 */
		static int __gc(lua_State* L) {
			auto pInstance = reinterpret_cast<T*>(lua_touserdata(L, 1));
			pInstance->~T();
			return 0;
		};
		/**
		 * @brief		Register the LUCE adapter class to Lua state as full userdata.
		 *
		 * @param L		The Lua state which you want to register the LUCE adapter class into.
		 * @param s		The name of the userdata you want to register the LUCE adapter class as.
		 */
		static int __open(lua_State* L, const char* s) {
			/** Set static type */
			LUCE_Adapter<T>::__lState = L;
			LUCE_Adapter<T>::__name = s;

			/** Get global adapters table */
			lua_getglobal(L, "luce");

			/** Create factory userdata */
			lua_pushstring(L, s);
			lua_newuserdata(L, 0);

			/** Create factory metatable */
			lua_newtable(L);
			lua_pushcfunction(L, LUCE_Adapter<T>::__new);
			lua_setfield(L, -2, "new");
			lua_pushcfunction(L, LUCE_Adapter<T>::__bind);
			lua_setfield(L, -2, "bind");
			lua_pushvalue(L, -1);
			lua_setfield(L, -2, "__index");
			lua_setmetatable(L, -2);

			/** Add factory userdata */
			lua_settable(L, -3);

			/** Leave luce table */
			lua_pop(L, 1);

			/** Create object metatable */
			luaL_newmetatable(L, s);
			
			luaL_setfuncs(L, LUCE_Adapter<T>::__funcList, 0);
			lua_pushcfunction(L, LUCE_Adapter<T>::__gc);
			lua_setfield(L, -2, "__gc");
			lua_pushvalue(L, -1);
			lua_setfield(L, -2, "__index");
			
			/** Leave metatable */
			lua_pop(L, 1);

			return 0;
		};
		/**
		 * @brief		Create object.
		 */
		static int __new(lua_State* L);
		/**
		 * @brief		Bind a function to object.
		 */
		static int __bind(lua_State* L) {
			/** Get metatable */
			luaL_getmetatable(L, LUCE_Adapter<T>::__name);

			lua_pushvalue(L, 1);
			lua_pushvalue(L, 2);
			lua_settable(L, -3);

			/** Leave metatable */
			lua_pop(L, 1);
			return 0;
		}

	private:
		static luaL_Reg __funcList[];

		static lua_State* __lState;
		static const char* __name;
	};
}