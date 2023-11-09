#include "FlowWindowContent.h"

namespace luce {
	namespace utils {
		FlowWindowContent::FlowWindowContent(FlowWindow* parent) {
			this->manager = std::make_unique<FlowManager>(parent);
			this->addAndMakeVisible(this->manager.get());
		}

		FlowManager* FlowWindowContent::getManager() const {
			return this->manager.get();
		}

		void FlowWindowContent::resized() {
			this->manager->setBounds(this->getLocalBounds());
		}
	}
}
