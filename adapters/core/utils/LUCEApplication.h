#pragma once
#include "../../Defs.h"

namespace luce {
	namespace utils {
		class LUCEApplication {};

		class ApplicationHelper : public juce::JUCEApplication {
		public:
			ApplicationHelper();

			const juce::String getApplicationName() override;
			const juce::String getApplicationVersion() override;

			void initialise(const juce::String& commandLineParameters) override;
			void shutdown() override;

			bool moreThanOneInstanceAllowed() override;
			void anotherInstanceStarted(const juce::String& commandLine) override;

			void suspended() override;
			void resumed() override;
			void memoryWarningReceived() override;
			bool backButtonPressed() override;

		private:
			static lua_State* __LUCEState;
			static int __LUCERef;

		public:
			static lua_State*& LUCE_state() { return ApplicationHelper::__LUCEState; };
			static int& LUCE_ref() { return ApplicationHelper::__LUCERef; };
		};
	}
}
