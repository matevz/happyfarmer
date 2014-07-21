/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <QApplication>
#include <QSplashScreen>
#include <QFont>
#include <QFile>

#include "ui/mainwin.h"

#include <iostream>

#ifdef Q_WS_X11
#include <signal.h>
void catch_sig(int)
{
	qApp->quit();
}
#endif

int main(int argc, char *argv[]) {
	QApplication mainApp(argc, argv);

#ifdef Q_WS_X11
	signal(SIGINT, catch_sig);
	signal(SIGQUIT, catch_sig);
#endif
	
	HFMainWin mainWin( nullptr );
	mainWin.show();
	
	return mainApp.exec();
}
