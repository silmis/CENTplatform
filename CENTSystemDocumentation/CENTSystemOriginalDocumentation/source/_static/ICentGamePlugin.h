#ifndef CENT_GAME_PLUGIN_H
#define CENT_GAME_PLUGIN_H

// Includes special CENT data types. Data from device.
#include "CentDataTypes.h"

/*
	This virtual class is an interface for new games in CENT application.
*/
class ICentGamePlugin : public QObject
{
	Q_OBJECT
public:
	virtual ~ICentGamePlugin() {};

public:
	// Returns name of the game. You will see this name on page
	// in CENT where you can choose a game.
	virtual QString gameName() = 0;

	/* This one is called to initialize, create and return game widget ready to start the game
	*  It is mandatory to be called before gameWidget()
	*  @return Game Widget if it is ok to start the game, otherwise NULL.
	*/
	virtual QWidget* gameWidget() = 0;

	// Release Widget, is called prior to unloading the game plugin (this dll)
	virtual void releaseWidget() = 0;

	// Returns true if settings/configs can be written; returns false otherwise.
	virtual bool isConfigurable() const = 0;

public slots:
	// Called each time when the data comes from device.
	virtual void onUserInput(CentData::DigitalData data) = 0;

	// Called one time. Sets the expected input.
	virtual void onExpectedInput(const CentData::DigitalData& data) = 0;

	// Called each time when the EEG data come from the device.
	// You can use it to display EEG plot during the game.
	virtual void onEEG(CentData::AnalogData data) = 0;

	// This method starts the game. There you have to restore to the initial
	// state all variables and also emit gameStarted() signal.
	virtual void onStartGame() = 0;

	// Called when the game is ended from CENT ("End game" button or game time passed).
	virtual void onEndGame() = 0;

	// Called each time when the power data come from device. 
	// You can use it to display power plot during the game.
	virtual void onPowerSignal(CentData::AnalogData data) = 0;

	// This method shows the game settings.
	virtual void onShowSettings() = 0;

signals:
	// Copied from onExpectedSignal if not generated by game
	void expectedInput(CentData::DigitalData data);

	// Needed by the observer to start classification
	void gameStarted();

	// Decided by the game or called from onEndGame
	void gameEnded();
};

Q_DECLARE_INTERFACE(ICentGamePlugin, "cent.game.plugin");

#endif // CENT_GAME_PLUGIN_H
