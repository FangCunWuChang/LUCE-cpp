﻿#pragma once
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

			bool moreThanOneInstanceAllowed() override;
			void anotherInstanceStarted(const juce::String& commandLine) override;

			void suspended() override;
			void resumed() override;
			void memoryWarningReceived() override;
			bool backButtonPressed() override;

		public:
			static lua_State* appState;
			static int appAdapterRef;
		};
	}
}