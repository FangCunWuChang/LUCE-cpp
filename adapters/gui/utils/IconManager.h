#pragma once

#include "../../../Defs.h"

namespace luce {
	namespace utils {
		class LUCE_API IconManager final {
		public:
			IconManager() = default;

			static std::unique_ptr<juce::Drawable> getSVG(const juce::String& path);

		private:
			std::map<juce::String, std::shared_ptr<juce::Drawable>> temp;
			juce::CriticalSection lock;

			JUCE_DECLARE_SINGLETON(IconManager, false)
		};
	}
}
