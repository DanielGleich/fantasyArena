#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "arena.h"
#include "game.h"
#include "widget.h"

/*********************************************\
|*                                           *|
|*  Controller                               *|
|*                                           *|
\*********************************************/
class Controller : public QObject
{
  Q_OBJECT

private:
  static Controller *controller;                                          /// Zeiger auf die Singleton-Instanz dieser Klasse
  Widget            *widget;                                              /// Zeiger auf das Widget
  Game              *game;                                                /// Zeiger auf das Game
  Arena             *arena;                                               /// zeiger auf die Arena
  QSettings         *settings;                                            /// zeiger zum Speichern der Fensterposition
  Controller( QObject *parent = nullptr );
  ~Controller();
  void saveWindowGeometry();
  void loadWindowGeometry();

private slots:
  void exit();
  void loadGame();
  void closeArena();
  void endTurn();

public:
  static Controller *get();
};

#endif // CONTROLLER_H

/*! \class Controller
 * \brief Diese Klasse steuert das gesamte Programm als übereordnete Instanz */
