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

#include <control/drawablectl.h>
#include <control/constructctl.h>

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
	
	
	HFGame *game() { return _game; }
	void newGame();
	
public slots:
	void on_cursorBtn_toggled(bool);
	void on_magnifierBtn_toggled(bool);
	void on_roadBtn_toggled(bool);
	void on_dirtRoadBtn_toggled(bool);
	void on_animalBtn_toggled(bool);
	
	void on_gameView_mousePress( QMouseEvent* );
	void on_gameView_mouseRelease( QMouseEvent* );
	void on_gameView_mouseMove( QMouseEvent* );
	
private:
	HFGame *_game;
	QGraphicsScene *_scene;
	HFResource *_resource;
	HFSettings *_settings;
	
	HFDrawableCtl _drawableCtl;
	HFConstructCtl _constructCtl;
};

#endif
