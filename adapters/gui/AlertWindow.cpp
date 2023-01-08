#include "../Defs.h"

namespace luce {
	using juce::AlertWindow;

	LUCE_METHOD_LIST(AlertWindow);
	LUCE_STATIC_METHOD_LIST(AlertWindow);

	LUCE_NEW(AlertWindow) {
		return 0;
	}
}