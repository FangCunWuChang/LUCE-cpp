#pragma once

#include "../../../Defs.h"

namespace luce {
	namespace utils {
		class LUCE_API IconManager final : private juce::DeletedAtShutdown {
		public:
			IconManager() = default;

			static std::unique_ptr<juce::Drawable> getSVG(const juce::String& path);

		private:
			std::map<juce::String, std::shared_ptr<juce::Drawable>> temp;
			juce::CriticalSection lock;

		private:
			static IconManager* getInstance();
			static IconManager* instance;
		};
	}
}
