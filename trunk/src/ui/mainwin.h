/*!
        Copyright (c) 2012, Matevž Jekovec, Happy farmer development team
        All Rights Reserved. See AUTHORS for a complete list of authors.

        Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef MAINWIN_H_
#define MAINWIN_H_

#include <QObject>
#include <QMainWindow>

#include "ui_mainwin.h"

class HFGame;
class HFResource;
class HFSettings;

class QGraphicsScene;
class QMouseEvent;

class HFMainWin : public QMainWindow, private Ui::MainWin
{
	Q_OBJECT

public:
	HFMainWin(QMainWindow *parent = 0);
	~HFMainWin();
	
	void newGame();

private:
	HFGame *_game;
	QGraphicsScene *_scene;
	HFResource *_resource;
	HFSettings *_settings;
};

#endif
