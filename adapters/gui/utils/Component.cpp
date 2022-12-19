#include "Component.h"

namespace luce {
	namespace utils {
		using juce::Graphics;
		using juce::MouseEvent;
		using juce::MouseWheelDetails;

		Component::Component(const juce::String& name)
			: juce::Component(name) {}

		void Component::paint(juce::Graphics& g) {
			if (!LUCE_GET_STATE()) {
				this->juce::Component::paint(g);
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "paint");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::Component::paint(g);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			LUCE_PUSH_USERDATA(LUCE_GET_STATE(), Graphics, pg, g);
			lua_call(LUCE_GET_STATE(), 2, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void Component::paintOverChildren(juce::Graphics& g) {
			if (!LUCE_GET_STATE()) {
				this->juce::Component::paintOverChildren(g);
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "paintOverChildren");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::Component::paintOverChildren(g);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			LUCE_PUSH_USERDATA(LUCE_GET_STATE(), Graphics, pg, g);
			lua_call(LUCE_GET_STATE(), 2, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void Component::mouseMove(const juce::MouseEvent& event) {
			if (!LUCE_GET_STATE()) {
				this->juce::Component::mouseMove(event);
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "mouseMove");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::Component::mouseMove(event);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			LUCE_PUSH_USERDATA(LUCE_GET_STATE(), MouseEvent, pEvent, const_cast<juce::MouseEvent&>(event));
			lua_call(LUCE_GET_STATE(), 2, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void Component::mouseEnter(const juce::MouseEvent& event) {
			if (!LUCE_GET_STATE()) {
				this->juce::Component::mouseEnter(event);
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "mouseEnter");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::Component::mouseEnter(event);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			LUCE_PUSH_USERDATA(LUCE_GET_STATE(), MouseEvent, pEvent, const_cast<juce::MouseEvent&>(event));
			lua_call(LUCE_GET_STATE(), 2, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void Component::mouseExit(const juce::MouseEvent& event) {
			if (!LUCE_GET_STATE()) {
				this->juce::Component::mouseExit(event);
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "mouseExit");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::Component::mouseExit(event);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			LUCE_PUSH_USERDATA(LUCE_GET_STATE(), MouseEvent, pEvent, const_cast<juce::MouseEvent&>(event));
			lua_call(LUCE_GET_STATE(), 2, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void Component::mouseDown(const juce::MouseEvent& event) {
			if (!LUCE_GET_STATE()) {
				this->juce::Component::mouseDown(event);
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "mouseDown");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::Component::mouseDown(event);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			LUCE_PUSH_USERDATA(LUCE_GET_STATE(), MouseEvent, pEvent, const_cast<juce::MouseEvent&>(event));
			lua_call(LUCE_GET_STATE(), 2, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void Component::mouseDrag(const juce::MouseEvent& event) {
			if (!LUCE_GET_STATE()) {
				this->juce::Component::mouseDrag(event);
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "mouseDrag");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::Component::mouseDrag(event);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			LUCE_PUSH_USERDATA(LUCE_GET_STATE(), MouseEvent, pEvent, const_cast<juce::MouseEvent&>(event));
			lua_call(LUCE_GET_STATE(), 2, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void Component::mouseUp(const juce::MouseEvent& event) {
			if (!LUCE_GET_STATE()) {
				this->juce::Component::mouseUp(event);
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "mouseUp");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::Component::mouseUp(event);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			LUCE_PUSH_USERDATA(LUCE_GET_STATE(), MouseEvent, pEvent, const_cast<juce::MouseEvent&>(event));
			lua_call(LUCE_GET_STATE(), 2, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void Component::mouseDoubleClick(const juce::MouseEvent& event) {
			if (!LUCE_GET_STATE()) {
				this->juce::Component::mouseDoubleClick(event);
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "mouseDoubleClick");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::Component::mouseDoubleClick(event);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			LUCE_PUSH_USERDATA(LUCE_GET_STATE(), MouseEvent, pEvent, const_cast<juce::MouseEvent&>(event));
			lua_call(LUCE_GET_STATE(), 2, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void Component::mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel) {
			if (!LUCE_GET_STATE()) {
				this->juce::Component::mouseWheelMove(event, wheel);
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "mouseWheelMove");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::Component::mouseWheelMove(event, wheel);
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			LUCE_PUSH_USERDATA(LUCE_GET_STATE(), MouseEvent, pEvent, const_cast<juce::MouseEvent&>(event));
			LUCE_PUSH_USERDATA(LUCE_GET_STATE(), MouseWheelDetails, pDetails, const_cast<juce::MouseWheelDetails&>(wheel));
			lua_call(LUCE_GET_STATE(), 3, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void Component::resized() {
			if (!LUCE_GET_STATE()) {
				this->juce::Component::resized();
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "resized");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::Component::resized();
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_call(LUCE_GET_STATE(), 1, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}

		void Component::moved() {
			if (!LUCE_GET_STATE()) {
				this->juce::Component::moved();
				return;
			}

			LUCE_PUSH_OBJ(LUCE_GET_STATE(), LUCE_GET_REF());

			lua_getfield(LUCE_GET_STATE(), -1, "moved");
			if (!lua_isfunction(LUCE_GET_STATE(), -1)) {
				lua_pop(LUCE_GET_STATE(), 2);
				this->juce::Component::moved();
				return;
			}

			lua_pushvalue(LUCE_GET_STATE(), -2);
			lua_call(LUCE_GET_STATE(), 1, 0);

			lua_pop(LUCE_GET_STATE(), 1);
		}
	}
}
