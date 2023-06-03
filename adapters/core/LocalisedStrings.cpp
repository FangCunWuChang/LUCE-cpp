#include "../Defs.h"

namespace luce {
	using juce::LocalisedStrings;
	using juce::String;

	LUCE_METHOD_LIST(LocalisedStrings);

	LUCE_METHOD(loadData) {
		juce::String dirPath = juce::String::fromUTF8(luaL_checkstring(L, 1));

		juce::File dir = juce::File::getCurrentWorkingDirectory().getChildFile(dirPath);
		auto list = dir.findChildFiles(juce::File::findFiles, true, "*.txt");

		if (list.size() > 0) {
			auto trans = new juce::LocalisedStrings(list.getReference(0), true);

			for (int i = 1; i < list.size(); i++) {
				trans->addStrings(juce::LocalisedStrings(list.getReference(i), true));
			}

			juce::LocalisedStrings::setCurrentMappings(trans);
		}

		return 0;
	}

	LUCE_STATIC_METHOD_LIST(LocalisedStrings,
		loadData,
		);

	LUCE_NEW(LocalisedStrings) {
		return 0;
	}
}