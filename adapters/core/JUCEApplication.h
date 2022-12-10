#pragma once
#include "../../Defs.h"
#include "../../Macros.h"

namespace luce {
	namespace utils {
		class LUCEApplication : public juce::JUCEApplication {
		public:
			explicit LUCEApplication(const juce::String& appName, const juce::String& appVersion);

			const juce::String getApplicationName() override;
			const juce::String getApplicationVersion() override;

		private:
			const juce::String& appName;
			const juce::String& appVersion;
		};
	}

	class LUCE_API LUCEApplication : public LUCE_UserData<LUCEApplication> {
	public:
		static luaL_Reg __funcList[];
		static int __new(lua_State* L);

	public:
		static int test(lua_State* L);

	public:
		LUCEApplication();
		~LUCEApplication();

		void test(const char* m);
	};
}