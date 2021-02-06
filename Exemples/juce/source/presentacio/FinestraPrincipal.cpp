#include "FinestraPrincipal.h"
#include "domini/model/Persona.h"
#include "dades/BaseDeDades.h"
#include "domini/transaccions/TxAfegeixPersona.h"
#include "domini/Excepcions.h"
#include <set>

namespace presentacio
{
	//////////////////////////////////////////////////////////////////////////////////

	FinestraPrincipal::FinestraPrincipal(const juce::String& name) : juce::DocumentWindow(name,
		juce::Colours::lightgrey,
		juce::DocumentWindow::allButtons)
	{
		setUsingNativeTitleBar(true);
		setContentNonOwned(&m_componentPrincipal, true);
		centreWithSize(600, 110);
		setVisible(true);
	}

	void FinestraPrincipal::closeButtonPressed()
	{
		juce::JUCEApplication::getInstance()->systemRequestedQuit();
	}

	//////////////////////////////////////////////////////////////////////////////////

	FinestraPrincipal::ComponentPrincipal::ComponentPrincipal()
	{
		addAndMakeVisible(m_afegeixPersonaButton);
		m_afegeixPersonaButton.setButtonText("Afegeix Persona");
		m_afegeixPersonaButton.addListener(this);

		addAndMakeVisible(m_nomPersonaLabel);
		m_nomPersonaLabel.setText("Nom:", juce::dontSendNotification);
		m_nomPersonaLabel.setColour(juce::Label::textColourId, juce::Colours::black);
		m_nomPersonaLabel.setJustificationType(juce::Justification::right);

		addAndMakeVisible(m_nomPersonaText);
		m_nomPersonaText.setText("Nom Persona...");
		m_nomPersonaText.setJustification(juce::Justification::left);

		setSize(600, 110);
	}

	FinestraPrincipal::ComponentPrincipal::~ComponentPrincipal()
	{

	}

	void FinestraPrincipal::ComponentPrincipal::resized()
	{
		//int height = getHeight();
		int width = getWidth();
		int itemHeight = 30;
		int separatorSize = 5;

		m_nomPersonaLabel.setTopLeftPosition(0, 0);
		m_nomPersonaLabel.setSize(width / 2, itemHeight);

		m_nomPersonaText.setTopLeftPosition(width / 2, 0);
		m_nomPersonaText.setSize(width / 2, itemHeight);
		
		m_afegeixPersonaButton.setTopLeftPosition(0, itemHeight + separatorSize);
		m_afegeixPersonaButton.setSize(width, itemHeight);
	}

	void FinestraPrincipal::ComponentPrincipal::buttonClicked(juce::Button* i_buttonPressed)
	{
		//Aquí arriba l'esdeveniment
		if (i_buttonPressed == &m_afegeixPersonaButton)
		{
			std::string nom = m_nomPersonaText.getText().toStdString();
			try
			{
				domini::TxAfegirPersona afegirPersona(nom);
				afegirPersona.Executar();
				std::string message = "La persona amb nom [" + nom + "] inserida correctament";
				juce::NativeMessageBox::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon, "Ok", message.c_str(), nullptr);
			}
			catch (domini::PersonaJaExisteix pe)
			{
				std::string message = "La persona amb nom [" + nom +"] ja existeix";
				juce::NativeMessageBox::showMessageBox(juce::AlertWindow::AlertIconType::WarningIcon, "Error!", message.c_str(), nullptr);
			}
		}
	}

}



using namespace std;








class EmpleatUniversitari 
{
public:
	string nom;
	float souBase;

	virtual float pagarSou()
	{
		return souBase;
	}
};

class Professor: public EmpleatUniversitari
{
public:
	float plusLLoc;

	float pagarSou() override
	{
		return souBase + plusLLoc;
	}
};

class Administratiu : public EmpleatUniversitari
{
public:
	int horesExtra;
	float preuHoraExtra;

	float pagarSou() override
	{
		return souBase + horesExtra * preuHoraExtra;
	}
};

using namespace std;
struct Data {};


class Animal
{
private:
	string nom;
public:
	string GetNom() {
		return nom;
	}
};

class Persona
{
private:
	set<Animal*> mascotes;
public:
	set<string> LlistaNomAnimals(){
		set<string> nomAnimals;
		for (Animal* a : mascotes){
			nomAnimals.insert(a->GetNom());
		}
		return nomAnimals;
	}
};

