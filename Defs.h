#pragma once

#include "lua.hpp"
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
#define LUCE_REG(L, t)		luce::LUCE_Adapter<t>::__open(L, LUCE_NAME(t))

/**
 * @brief		Register a C function to the luce table in the Lua state.
 *
 * @param L		The Lua state which you want to register the class into.
 * @param f		The function which you want to register.
 */
#define LUCE_REGF(L, f) \
	{ \
		lua_getglobal(L, "luce"); \
		lua_pushfunction(L, f); \
		lua_setfield(L, -2, LUCE_NAME(f)); \
		lua_pop(L, 1); \
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
#define LUCE_METHOD_LIST(t, ...)				luaL_Reg luce::LUCE_Adapter<t>::__methodList[] = {LUCE_MAKE_REG_LIST(__VA_ARGS__) LUCE_NULL_LUA_REG()}
/**
 * @brief		Make a static method list of the object class.
 * @attention	50 methods max.
 *
 * @param t		The name of the adapter class.
 * @param ...	The method list.
 */
#define LUCE_STATIC_METHOD_LIST(t, ...)				luaL_Reg luce::LUCE_Adapter<t>::__staticMethodList[] = {LUCE_MAKE_REG_LIST(__VA_ARGS__) LUCE_NULL_LUA_REG()}

/**
 * @brief		Create a Lua userdata and push it on the top of the stack.
 * 
 * @param L		The Lua state.
 * @param t		The userdata type.
 * 
 * @return		The lvalue reference of the userdata memory.
 */
#define LUCE_CREATE_USERDATA(L, t) \
	reinterpret_cast<luce::LUCE_FullContainer<t>&>( \
		*reinterpret_cast<luce::LUCE_FullContainer<t>*>(lua_newuserdata(L, sizeof(luce::LUCE_FullContainer<t>))))

/**
 * @brief		Check the param at ud if it is an userdata.
 *
 * @param L		The Lua state.
 * @param ud	The index of the arg on stack.
 * @param t		The userdata type.
 *
 * @return		The lvalue reference of the userdata.
 */
#define LUCE_CHECK_USERDATA(L, ud, t) \
	reinterpret_cast<luce::LUCE_Container<t>&>( \
		*reinterpret_cast<luce::LUCE_Container<t>*>(luaL_checkudata(L, ud, LUCE_NAME(t))))
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
 * @return		The lvalue reference of the userdata memory.
 */
#define LUCE_CREATE_USERDATA_WITH_METATABLE(L, t)		LUCE_CREATE_USERDATA(L, t); LUCE_SET_METATABLE(L, t)
/**
 * @brief		Construct the object object.
 * @attention	The type of the point must match the true type of the object.
 * 
 * @param p		The reference varible name of the object.
 * @param ...	The arg list when the constructor function called.
 */
#define LUCE_INIT(p, ...) \
	new(&p) std::remove_reference<decltype(p)>::type(__VA_ARGS__)
/**
 * @brief		Create a Lua userdata and push it on the top of the stack,
 *				then set the metatable as which has the same name of the type.
 *				Then call the constructor of the object.
 *
 * @param L		The Lua state.
 * @param t		The userdata type.
 * @param p		The reference varible name of the object.
 * @param ...	The arg list when the constructor function called.
 */
#define LUCE_CREATE_USERDATA_WITH_METATABLE_THEN_INIT(L, t, p, ...) \
	auto& p = LUCE_CREATE_USERDATA_WITH_METATABLE(L, t); \
	LUCE_INIT(p, __VA_ARGS__)
/**
 * @brief		Push a C++ object on the top of the stack.
 *
 * @param L		The Lua state.
 * @param t		The userdata type.
 * @param p		The reference varible name of the object.
 * @param o		The object.
 */
#define LUCE_PUSH_USERDATA(L, t, p, o) \
	auto& p = reinterpret_cast<luce::LUCE_LightContainer<t>&>( \
		*reinterpret_cast<luce::LUCE_LightContainer<t>*>(lua_newuserdata(L, sizeof(luce::LUCE_LightContainer<t>)))); \
	LUCE_SET_METATABLE(L, t); \
	LUCE_INIT(p, &o)

/**
 * @brief		Create a Lua data table for object.
 *
 * @param L		The Lua state.
 * @param ud	The index of the object.
 */
#define LUCE_CREATE_DATA(L, ud) \
		lua_getglobal(L, "luce"); \
		lua_getfield(L, -1, "__datas"); \
		 \
		lua_pushvalue(L, (ud > 0) ? ud : ((ud) - 2)); \
		lua_newtable(L); \
		lua_settable(L, -3); \
		 \
		lua_pop(L, 2)

/**
 * @brief		Push the Lua data table for object on the stack.
 *
 * @param L		The Lua state.
 * @param ud	The index of the object.
 */
#define LUCE_PUSH_DATA(L, ud) \
		lua_getglobal(L, "luce"); \
		lua_getfield(L, -1, "__datas"); \
		 \
		lua_pushvalue(L, ((ud) > 0) ? (ud) : ((ud) - 2)); \
		lua_gettable(L, -2); \
		 \
		lua_remove(L, -2); \
		lua_remove(L, -2)

/**
 * @brief		Create a Lua type object create function.
 * 
 * @param t		The type of the object.
 */
#define LUCE_NEW(t) \
	lua_State* luce::LUCE_Adapter<t>::__lState = nullptr; \
	const char* luce::LUCE_Adapter<t>::__name = nullptr; \
	int luce::LUCE_Adapter<t>::__new(lua_State* L)

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
		lua_pushvalue(L, (udx > 0) ? udx : (udx - 2)); \
		int result = luaL_ref(L, -2); \
		 \
		lua_pop(L, 2); \
		return result; \
	}()

namespace luce {
	namespace utils {
		/**
		 * @brief		The base class of all LUCE_Container classes.
		 */
		class LUCE_API LUCE_ContainerBase {
		public:
			virtual ~LUCE_ContainerBase() = default;
		};
		/**
		 * @brief		The base class of all LUCE_Adapter classes.
		 */
		class LUCE_API LUCE_AdapterBase {
		public:
			virtual ~LUCE_AdapterBase() = default;
		};
	}


	/**
	 * @brief		The base class of all LUCE_Container classes of type T.
	 *
	 * @tparam T	The LUCE object class which you want to register as Lua userdata.
	 */	 
	template<class T>
	class LUCE_API LUCE_Container : public utils::LUCE_ContainerBase {
	public:
		virtual ~LUCE_Container() override = default;

		virtual T* get() const = 0;
		operator T* () const {
			return get();
		};
		T* operator->() const {
			return get();
		};
	};
	/**
	 * @brief		The class contains the fulluserdata.
	 *
	 * @tparam T	The LUCE object class which you want to register as Lua userdata.
	 *
	 * @see			LUCE_AdapterBase
	 */
	template<class T>
	class LUCE_API LUCE_FullContainer : public LUCE_Container<T> {
		std::unique_ptr<T> __data = nullptr;

	public:
		template<class ...A>
		LUCE_FullContainer(A&&... args) {
			this->__data = std::make_unique<T>(std::forward<A>(args)...);
		};

		T* get() const override {
			return this->__data.get();
		};
	};
	/**
	 * @brief		The class contains the lightuserdata.
	 *
	 * @tparam T	The LUCE object class which you want to register as Lua userdata.
	 *
	 * @see			LUCE_AdapterBase
	 */
	template<class T>
	class LUCE_API LUCE_LightContainer : public LUCE_Container<T> {
		T* __data = nullptr;

	public:
		LUCE_LightContainer() = delete;
		explicit LUCE_LightContainer(T* ptr) {
			this->__data = ptr;
		};
		~LUCE_LightContainer() {
			this->__data = nullptr;
		}

		T* get() const override {
			return this->__data;
		};
	};

	/**
	 * @brief		The LUCE adapter classes which you controls the Lua userdata.			\n
	 *				Some important methods about Lua userdata are defined in this class.
	 *
	 * @tparam T	The LUCE object class which you want to register as Lua userdata.
	 *
	 * @see			LUCE_AdapterBase
	 */
	template<class T>
	class LUCE_API LUCE_Adapter : public utils::LUCE_AdapterBase {
	public:
		LUCE_Adapter() = delete;
		/**
		 * @brief		An lua_CFunction type method which will be called before userdata memory GC.		\n
		 *				In this method, the destructor of the container class will be called.				\n
		 *				This method will be registered in the metatable of the userdata.
		 */
		static int __gc(lua_State* L) {
			auto pInstance = reinterpret_cast<LUCE_Container<T>*>(luaL_checkudata(L, 1, LUCE_Adapter<T>::__name));
			pInstance->~LUCE_Container();
			return 0;
		};
		/**
		 * @brief		Get the data table of the object.
		 */
		static int __data(lua_State* L) {
			luaL_checkudata(L, 1, LUCE_Adapter<T>::__name);

			LUCE_PUSH_DATA(L, 1);

			if (lua_isnil(L, -1)) {
				lua_pop(L, 1);
				LUCE_CREATE_DATA(L, 1);
				LUCE_PUSH_DATA(L, 1);
			}

			return 1;
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

			/** Get luce table */
			lua_getglobal(L, "luce");

			/** Create factory userdata */
			lua_pushstring(L, s);
			lua_newuserdata(L, 0);

			/** Create factory metatable */
			lua_newtable(L);
			luaL_setfuncs(L, LUCE_Adapter<T>::__staticMethodList, 0);
			lua_pushcfunction(L, LUCE_Adapter<T>::__new);
			lua_setfield(L, -2, "new");
			lua_pushcfunction(L, LUCE_Adapter<T>::__bind);
			lua_setfield(L, -2, "bind");
			lua_pushcfunction(L, LUCE_Adapter<T>::__set);
			lua_setfield(L, -2, "set");
			lua_pushcfunction(L, LUCE_Adapter<T>::__cast);
			lua_setfield(L, -2, "cast");
			lua_pushvalue(L, -1);
			lua_setfield(L, -2, "__index");
			lua_setmetatable(L, -2);

			/** Add factory userdata */
			lua_settable(L, -3);

			/** Leave luce table */
			lua_pop(L, 1);

			/** Create object metatable */
			luaL_newmetatable(L, s);

			luaL_setfuncs(L, LUCE_Adapter<T>::__staticMethodList, 0);
			luaL_setfuncs(L, LUCE_Adapter<T>::__methodList, 0);
			lua_pushcfunction(L, LUCE_Adapter<T>::__data);
			lua_setfield(L, -2, "data");
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
		 * @brief		Bind a Lua value to object.
		 */
		static int __bind(lua_State* L) {
			/** Check name */
			if (lua_isstring(L, 1)) {
				const char* name = lua_tostring(L, 1);
				if (!(strcmp(name, "__gc") &&
					strcmp(name, "__index") &&
					strcmp(name, "data"))) {
					luaL_argerror(L, 1, "Bad name!");
					return 0;
				}
			}

			/** Get metatable */
			luaL_getmetatable(L, LUCE_Adapter<T>::__name);

			lua_pushvalue(L, 1);
			lua_pushvalue(L, 2);
			lua_settable(L, -3);

			/** Leave metatable */
			lua_pop(L, 1);
			return 0;
		}
		/**
		 * @brief		Set a Lua value to object factory.
		 */
		static int __set(lua_State* L) {
			/** Check name */
			if (lua_isstring(L, 1)) {
				const char* name = lua_tostring(L, 1);
				if (!(strcmp(name, "__index") &&
					strcmp(name, "__gc") &&
					strcmp(name, "data") &&
					strcmp(name, "new") &&
					strcmp(name, "bind") &&
					strcmp(name, "set") &&
					strcmp(name, "cast"))) {
					luaL_argerror(L, 1, "Bad name!");
					return 0;
				}
			}

			/** Get luce table */
			lua_getglobal(L, "luce");

			/** Get factory userdata */
			lua_getfield(L, -1, LUCE_Adapter<T>::__name);

			/** Get factory metatable */
			lua_getmetatable(L, -1);

			/** Add object to metatable */
			lua_pushvalue(L, 1);
			lua_pushvalue(L, 2);
			lua_settable(L, -3);

			/** Leave tables */
			lua_pop(L, 3);

			/** Get metatable */
			luaL_getmetatable(L, LUCE_Adapter<T>::__name);

			lua_pushvalue(L, 1);
			lua_pushvalue(L, 2);
			lua_settable(L, -3);

			/** Leave metatable */
			lua_pop(L, 1);
			return 0;
		}
		/**
		 * @brief		Change a userdata to current type.
		 */
		static int __cast(lua_State* L) {
			/** Check userdata */
			if (!lua_isuserdata(L, 1)) {
				luaL_argerror(L, 1, "Isn't an userdata!");
			}
			/** Check function */
			if (!lua_isfunction(L, 2)) {
				luaL_argerror(L, 2, "Isn't a function!");
			}

			/** Get current metatable */
			lua_getmetatable(L, 1);

			/** Get target metatable */
			luaL_getmetatable(L, LUCE_Adapter<T>::__name);

			/** Set target metatable for userdata */
			lua_setmetatable(L, 1);

			/** Call function */
			lua_pushvalue(L, 2);
			lua_pcall(L, 0, 0, 0);

			/** Reset metatable */
			lua_setmetatable(L, 1);

			return 0;
		}

	private:
		static luaL_Reg __methodList[];
		static luaL_Reg __staticMethodList[];

		static lua_State* __lState;
		static const char* __name;
	};
}