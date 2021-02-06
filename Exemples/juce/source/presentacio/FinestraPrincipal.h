#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

namespace presentacio
{
	class FinestraPrincipal : public juce::DocumentWindow
	{
	public:
		FinestraPrincipal(const juce::String& name);
		void closeButtonPressed() override;

	private:
		class ComponentPrincipal : public juce::Component, public juce::Button::Listener
		{
		public:
			ComponentPrincipal();
			~ComponentPrincipal();
			void resized() override;

			void buttonClicked(juce::Button*) override;

		private:
			juce::TextButton m_afegeixPersonaButton;
			juce::Label m_nomPersonaLabel;
			juce::TextEditor m_nomPersonaText;
		};

	private:
		ComponentPrincipal m_componentPrincipal;
	};
}