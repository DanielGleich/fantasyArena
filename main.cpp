#include <QApplication>
#include "controller.h"

int main( int argc, char *argv[] )
{
  QApplication a( argc, argv );

  Controller::get();

  return a.exec();
}

/*!
 * \mainpage Fantasy Fight
 *
 * \section wasistdas Was ist das?
 *
 * Bei der App FantasyFight handelt es sich um ein Kartenspiel für einen Spieler.
 *
 * \section spielregel Spielregeln
 *
 * Der Spieler erhölt zu Spielbeginn eine gewisse Anzahl an Standardkarten. Weitere Karten können im Verlaufe des Spieles hinzugewonnen werden. Karten können aber auch wieder entfernt werden. So ist es das Ziel des Spielers, sein Kartendeck im Verlaufe des Spiels zu optimieren, um immer gefährlichere Gegner bekämpfen zu können.
 *
 * Die Gegenpartei, repräsentiert von verschiedenen Monstern, wird von der KI übernommen. In jeder Runde spielt der Spieler beliebige seiner fünf Handkarten gegen die Gegner aus. Anschließend sind die genger am Zug. Die Gegner reagieren immer unterschiedlich. Jeder Gegner hat ein Repertoir an Fertigkeiten, wie zum Beispiel
 * - Vergiftung
 * - Verteidigung
 * - Angriff
 * - Heilung
 * - ...
 *
 * Zufallsbasiert wählt die KI eine der Fertigkeiten jedes aktiven Monsters aus. Diese wird auch schon im SPielerzug angezeigt und im Gegnerzug ausgeführt. So kann der Spieler rechtzeitig auf gefährliche Angriffe der Gegner reagieren.
 *
 */
