#include "IconManager.h"

namespace luce {
	namespace utils {
		JUCE_IMPLEMENT_SINGLETON(IconManager);

		std::unique_ptr<juce::Drawable> IconManager::getSVG(const juce::String& path) {
			auto instance = IconManager::getInstance();
			juce::GenericScopedLock<juce::CriticalSection> locker(instance->lock);

			/** If Hit Temp */
			auto it = instance->temp.find(path);
			if (it != instance->temp.end()) {
				return std::move(it->second->createCopy());
			}

			/** Load File */
			juce::File file(path);
			auto str = file.loadFileAsString();

			/** Parse File */
			auto ptrXml = juce::XmlDocument::parse(str);
			if (!ptrXml) { return nullptr; }
			auto svgData = juce::Drawable::createFromSVG(*ptrXml);
			if (!svgData) { return nullptr; }

			/** Save Temp */
			auto ptrData = svgData.release();
			instance->temp.insert(std::make_pair(path, std::shared_ptr<juce::Drawable>(ptrData)));
			return std::move(ptrData->createCopy());
		}
	}
}
