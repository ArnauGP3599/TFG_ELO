#include <juce_gui_basics/juce_gui_basics.h>
#include "presentacio/FinestraPrincipal.h"

//==============================================================================
class Applicacio : public juce::JUCEApplication
{
public:
	void initialise(const juce::String& commandLine) override
	{
		m_mainWindow = new presentacio::FinestraPrincipal(getApplicationName());
	}

	void shutdown() override
	{
		delete(m_mainWindow);
		m_mainWindow = nullptr;
	}
	

	virtual const juce::String getApplicationName() override
	{
		return "IES";
	}


	virtual const juce::String getApplicationVersion() override
	{
		return "0.0.1";
	}

private:
	presentacio::FinestraPrincipal* m_mainWindow;
};


START_JUCE_APPLICATION(Applicacio);
