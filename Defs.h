#pragma once
#include "Macros.h"
#include <lua.hpp>
#include <JuceHeader.h>

#include "Defs-internal.h"

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
#define LUCE_ADAPTER_REG(L, t)		t::__open(L, LUCE_NAME(t))

/**
 * @brief		Try to run the script. If Lua throws an error, then print the message, close the state and return -1.
 * 
 * @param L		The Lua state which you want to run on.
 * @param s		The script file.
 */
#define LUCE_RUN(L, s) \
	if (luaL_dofile(L, s)) { \
		printf(luaL_checkstring(L, -1)); \
		lua_close(L); \
		return -1; \
	}

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
 * @param t		The name of the adapter class.
 * @param f		The name of the method.
 * 
 * @return		A luaL_Reg value.
 */
#define LUCE_TO_LUA_REG(t, f)			{LUCE_NAME(f), t::f}
/**
 * @brief		Make a empty luaL_Reg value as the end of the list.
 * 
 * @return		A luaL_Reg value has NULL value.
 */
#define LUCE_NULL_LUA_REG()				{NULL, NULL}

/**
 * @brief		Make a luaL_Reg value list if method list exists.
 * @attention	50 methods max.
 * 
 * @param t		The name of the adapter class.
 * @param ...	The method list.
 * 
 * @return		A list of luaL_Reg values.
 */
#define LUCE_MAKE_REG_LIST(t, ...)					__VA_OPT__(LUCE_MAKE_REG_LIST_INTERNAL(t, __VA_ARGS__))
/**
 * @brief		Make a method list of the adapter class.
 * @attention	50 methods max.
 *
 * @param t		The name of the adapter class.
 * @param ...	The method list.
 */
#define LUCE_MAKE_ADAPTER_FUNCTION_LIST(t, ...)		luaL_Reg t::__funcList[] = {LUCE_MAKE_REG_LIST(t, __VA_ARGS__) LUCE_NULL_LUA_REG()}

/**
 * @brief		Get the Lua state.
 */
#define LUCE_ADAPTER_GET_STATE()						this->__lState
/**
 * @brief		Get the adapter name.
 */
#define LUCE_ADAPTER_GET_NAME()							this->__name
/**
 * @brief		Get the Lua obj ref.
 */
#define LUCE_ADAPTER_GET_OBJ_REF()						this->__objRef

/**
 * @brief		Push current Lua adapter object on stack top.
 * 
 * @param L		The Lua state.
 * @param n		The name of the adapter.
 * @param r		The obj reference.
 */
#define LUCE_PUSH_OBJ(L, n, r) \
	lua_getglobal(L, "luce"); \
	lua_getfield(L, -1, "refs"); \
	lua_getfield(L, -1, n); \
	 \
	lua_rawgeti(L, -1, r); \
	 \
	lua_remove(L, -2); \
	lua_remove(L, -2); \
	lua_remove(L, -2)
/**
 * @brief		Push current Lua adapter object on stack top.
 */
#define LUCE_ADAPTER_PUSH_OBJ() \
	LUCE_PUSH_OBJ(LUCE_ADAPTER_GET_STATE(), LUCE_ADAPTER_GET_NAME(), LUCE_ADAPTER_GET_OBJ_REF())

/**
 * @brief		Create Lua state pointer instance for adapter.
 * 
 * @param t		The name of the adapter class.
 */
#define LUCE_ADAPTER_CREATE_STATE_INSTANCE(t)			lua_State* luce::LUCE_Adapter<t>::__lState = nullptr
/**
 * @brief		Create Lua state pointer instance for adapter.
 * 
 * @param t		The name of the adapter class.
 */
#define LUCE_ADAPTER_CREATE_NAME_INSTANCE(t)			const char* luce::LUCE_Adapter<t>::__name = nullptr
/**
 * @brief		Create static instances for adapter.
 * 
 * @param t		The name of the adapter class.
 */
#define LUCE_ADAPTER_CREATE_STANDARD_INSTANCES(t) \
	LUCE_ADAPTER_CREATE_STATE_INSTANCE(t); \
	LUCE_ADAPTER_CREATE_NAME_INSTANCE(t)

/**
 * @brief		Adapter class with JUCE_API export flag.
 * 
 * @param t		The name of the adapter class.
 */
#define LUCE_ADAPTER_WITH_API(t)					class LUCE_API t : public luce::LUCE_Adapter<t>

/**
 * @brief	The list of methods in metatable.
 */
#define LUCE_ADAPTER_METHOD_LIST					static luaL_Reg __funcList[];
/**
 * @brief	The method to create Lua object.
 */
#define LUCE_ADAPTER_NEW_METHOD						static int __new(lua_State* L);

/**
 * @brief	Some standard properties of adapter class.
 */
#define LUCE_ADAPTER_STANDARD_PROPERTIES \
	public: \
		LUCE_ADAPTER_METHOD_LIST \
		LUCE_ADAPTER_NEW_METHOD

/**
 * @brief		Create the instance of the __new method of the adapter class.
 * 
 * @param t		The name of the adapter class.
 */
#define LUCE_ADAPTER_NEW(t)						int t::__new(lua_State* L)
/**
 * @brief		Create the instance of the __new method of the adapter class with static instances.
 *
 * @param t		The name of the adapter class.
 */
#define LUCE_ADAPTER_NEW_WITH_STANDARD_INSTANCES(t) \
	LUCE_ADAPTER_CREATE_STANDARD_INSTANCES(t); \
	LUCE_ADAPTER_NEW(t)

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
	lua_setmetatable(L, -2)
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
 * @brief		Construct the adapter object.
 * @attention	The type of the point must match the true type of the adapter.
 * 
 * @param p		The pointer of the adapter object.
 * @param ...	The arg list when the constructor function called.
 */
#define LUCE_ADAPTER_INIT(p, ...) \
	new(p) std::remove_reference<decltype(*p)>::type(__VA_ARGS__)
/**
 * @brief		Create a Lua userdata and push it on the top of the stack,
 *				then set the metatable as which has the same name of the type.
 *				Then call the constructor of the object.
 *
 * @param L		The Lua state.
 * @param t		The userdata type.
 * @param p		The pointer of the adapter object.
 * @param ...	The arg list when the constructor function called.
 */
#define LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, t, p, ...) \
	auto p = LUCE_CREATE_USERDATA_WITH_METATABLE(L, t); \
	LUCE_ADAPTER_INIT(p, __VA_ARGS__)

/**
 * @brief		Create a Lua interface of the adapter method.
 * 
 * @param n		The name of the method.
 */
#define LUCE_CREATE_ADAPTER_METHOD_INTERFACE(n)			static int n(lua_State * L)
/**
 * @brief		Create an adapter method.
 * 
 * @param n		The name of the method.
 * @param r		The return type of the method.
 * @param ...	The arg list of the method.
 */
#define LUCE_CREATE_ADAPTER_METHOD(n, r, ...)			r n(__VA_ARGS__)
/**
 * @brief		Create an adapter method with Lua interface.
 * 
 * @param n		The name of the method.
 * @param r		The return type of the method.
 * @param ...	The arg list of the method.
 */
#define LUCE_CREATE_ADAPTER_METHOD_WITH_INTERFACE(n, r, ...) \
	public: \
		LUCE_CREATE_ADAPTER_METHOD_INTERFACE(n); \
		LUCE_CREATE_ADAPTER_METHOD(n, r, __VA_ARGS__)

/**
 * @brief		Create the instance of Lua interface of the adapter method.
 * 
 * @param t		The name of the adapter class.
 * @param n		The name of the method.
 */
#define LUCE_ADAPTER_METHOD_INTERFACE(t, n)				int t::n(lua_State * L)
/**
 * @brief		Create the instance of adapter method.
 *
 * @param t		The name of the adapter class.
 * @param n		The name of the method.
 * @param r		The return type of the method.
 * @param ...	The arg list of the method.
 */
#define LUCE_ADAPTER_METHOD(t, n, r, ...)				r t::n(__VA_ARGS__)

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
			auto pInstance = reinterpret_cast<LUCE_AdapterBase*>(lua_touserdata(L, 1));
			pInstance->~LUCE_AdapterBase();
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
			lua_getfield(L, -1, "adapters");

			/** Create factory userdata */
			lua_pushstring(L, s);
			lua_newuserdata(L, 0);

			/** Create factory metatable */
			lua_newtable(L);
			lua_pushcfunction(L, T::__new);
			lua_setfield(L, -2, "new");
			lua_pushvalue(L, -1);
			lua_setfield(L, -2, "__index");
			lua_setmetatable(L, -2);

			/** Add factory userdata */
			lua_settable(L, -3);

			/** Leave adapters table */
			lua_pop(L, 1);

			/** Create weak refs table */
			lua_getfield(L, -1, "refs");

			/** Create factory userdata ref table */
			lua_pushstring(L, s);
			lua_newtable(L);

			/** Create refs table metatable */
			lua_newtable(L);
			lua_pushstring(L, "v");
			lua_setfield(L, -2, "__mode");
			lua_setmetatable(L, -2);

			/** Add factory userdata ref table */
			lua_settable(L, -3);

			/** Leave refs table */
			lua_pop(L, 1);

			/** Leave luce table */
			lua_pop(L, 1);

			/** Create object metatable */
			luaL_newmetatable(L, s);
			luaL_setfuncs(L, T::__funcList, 0);
			lua_pushcfunction(L, T::__gc);
			lua_setfield(L, -2, "__gc");
			lua_pushvalue(L, -1);
			lua_setfield(L, -2, "__index");
			lua_pop(L, 1);

			return 0;
		};

	public:
		LUCE_Adapter() {
			lua_getglobal(LUCE_ADAPTER_GET_STATE(), "luce");
			lua_getfield(LUCE_ADAPTER_GET_STATE(), -1, "refs");
			lua_getfield(LUCE_ADAPTER_GET_STATE(), -1, LUCE_ADAPTER_GET_NAME());

			lua_pushvalue(LUCE_ADAPTER_GET_STATE(), -4);
			LUCE_ADAPTER_GET_OBJ_REF() = luaL_ref(LUCE_ADAPTER_GET_STATE(), -2);

			lua_pop(LUCE_ADAPTER_GET_STATE(), 3);
		};
		virtual ~LUCE_Adapter() {
			lua_getglobal(LUCE_ADAPTER_GET_STATE(), "luce");
			lua_getfield(LUCE_ADAPTER_GET_STATE(), -1, "refs");
			lua_getfield(LUCE_ADAPTER_GET_STATE(), -1, LUCE_ADAPTER_GET_NAME());

			luaL_unref(LUCE_ADAPTER_GET_STATE(), -1, LUCE_ADAPTER_GET_OBJ_REF());

			lua_pop(LUCE_ADAPTER_GET_STATE(), 3);
		};

	protected:
		static lua_State* __lState;
		static const char* __name;

	protected:
		int __objRef = 0;
	};
}