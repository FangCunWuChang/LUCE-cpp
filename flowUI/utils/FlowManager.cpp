#include "FlowManager.h"
#include "FlowWindow.h"

namespace luce {
	namespace utils {
		FlowManager::FlowManager(FlowWindow* window)
			: window(window) {

		}

		void FlowManager::moveProgressing(
			const juce::Point<int> currentPoint,
			const juce::Point<int> topLeftDistance,
			FlowContainer* container) {

		}

		void FlowManager::moveEnd(
			const juce::Point<int> endPoint,
			const juce::Point<int> topLeftDistance) {

		}
	}
}
