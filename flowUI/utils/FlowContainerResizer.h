#pragma once

#include "../../Defs.h"

namespace luce {
	namespace utils{
		class FlowWindow;
		class FlowContainer;

		class FlowContainerResizer final : public juce::Component {
		public:
			enum class ResizerPlace;
			FlowContainerResizer(ResizerPlace place, FlowWindow* window, FlowContainer* container);

			enum class ResizerPlace {
				Left = 1,
				Right = 2,
				Top = 4,
				Bottom = 8,

				TopLeft = Left | Top,
				TopRight = Right | Top,
				BottomLeft = Left | Bottom,
				BottomRight = Right | Bottom
			};

		public:
			void mouseDrag(const juce::MouseEvent& event) override;

		private:
			const ResizerPlace place;
			FlowWindow* const window = nullptr;
			FlowContainer* const container = nullptr;
			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlowContainerResizer)
		};
	}
}
