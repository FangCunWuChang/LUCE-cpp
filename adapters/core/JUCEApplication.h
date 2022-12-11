#pragma once
#include "../../Defs.h"
#include "../../Macros.h"

namespace luce {
	namespace utils {
		class LUCEApplication : public juce::JUCEApplication {
		public:
			LUCEApplication();

			const juce::String getApplicationName() override;
			const juce::String getApplicationVersion() override;

			void initialise(const juce::String& commandLineParameters) override;
			void shutdown() override;

		public:
			static juce::String appName;
			static juce::String appVersion;
		};
	}


	LUCE_ADAPTER_WITH_API(LUCEApplication) {
	public:
		static int exec(lua_State * L);
		int exec();

	public:
		LUCEApplication(const juce::String & appName, const juce::String & appVersion);
		~LUCEApplication() override = default;

		LUCE_ADAPTER_STANDARD_PROPERTIES
	};
}