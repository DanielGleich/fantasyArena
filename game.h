#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "card.h"
#include "config.h"
#include "database.h"
#include "someone.h"

/*********************************************\
|*                                           *|
|*  Game                                     *|
|*                                           *|
\*********************************************/
class Game : public QObject
{
  Q_OBJECT

private:
  static Game        *game;
  int                arenaLevel = 0;
  QList< Card * >    cards;
  Player             *player    = nullptr;
  QList< Monster * > monster;                                   /// Alle in der Datenbank abgelegten Monster aller Level
  QList< Monster * > activeMonster;                             /// Die in der aktuellen Arenalevel-Runde (noch) aktiven (und nicht getöteten) Monster
  Database           *db        = nullptr;

  Game( QObject *parent = nullptr );
  ~Game();
  void                    resetCards();
  void                    resetPlayer();
  void                    initGame();
  void                    deleteCards();
  void                    initCards();
  void                    resetMonster();
  void                    deleteMonster();
  void                    initMonsters();
  Card                    *getCard( int id );
  void                    setPlayerAttributes();
  void                    setPlayerCards();
  QList< Monster * >      getMonsterOfLevelBetween( int minLevel, int maxLevel ) const;
  void                    removeMonster( Monster *monster );
  bool                    areAllActiveMonsterDown();
  void                    generateNewActiveMonsters();
  void                    activateActiveMonster();
  void                    initMonster( int monsterId );
  QList< MonsterSkill * > initMonsterSkills( int monsterId );
  MonsterSkill            *initMonsterSkillAttack( int monsterId );
  MonsterSkill            *initMonsterSkillDefend( int monsterId );

  void removeSlainMonsters();

public:
  static Game        *get();
  void               startNewGame();
  Player             *getPlayer() const;
  void               endPlayerMove();
  void               nextArenaRound();
  QList< Monster * > getActiveMonster() const;
  void               playCardAgainstSomeone( Card *card, Someone *someone );

signals:
  void dataChanged();
};

#endif // GAME_H

/*!
 * \class Game
 * \brief Steuerung der kompletten Spiellogik und Verwaltung aller notwendigen Daten
 *
 * Spielerkarten, Monster und Arenalevel werden hier verwaltet.*/

/*! \fn void Game::startNewGame()
 * \brief Initialisisiert ein neues Spiel; alle Daten werden zurückgesetzt.*/

/*! \fn Player* Game::getPlayer() const
 * \brief Gibt die Instanz des Spielers zurück
 *
 * \return Zeiger auf die Instanz des Spielers */

/*! \fn void Game::nextArenaRound()
 * \brief Eine neue Spielrunde wird gestartet.
 *
 * Folgende Schritte beinhaltet diese Methode:
 * - Das Arenalevel wird um 1 erhöht
 * - Alle evtl. noch aktiven Monster werden entfernt
 * - Alle Handkarten werden abgelegt
 * - Alle abgelegten Karten werden ins Deck zurückgemischt
 * - Der Spieler erhält 5 neue Handkarten
 * - Drei Monster im Levelbereich "Arenalevel plusminus 5" werden generiert und als aktive Monster gesetzt */

/*! \fn Game::playCardAgainstMonster( Card *card, Monster *monster )
 * \brief Eine Handkarte wird gegen ein Monster ausgespielt
 *
 * Abhängig von der gespielten Karte werden folgende Schritte durchgeführt:
 * - Sind die Energiekosten zu hoch, wird die Karte NICHT gespielt.
 * - Die Energiekosten des Spieler werden angepasst; bei positiven Kosten verringert sich die Energie des Spielers, bei negativen Kosten erhöht sich die Energie Des Spielers
 * - Die Verteidigung des Spielers wird angepasst
 * - Der Angriff gegen das Ziel wird durchgeführt
 * - Sollte es keine aktiven Monster mehr geben, wird die nächste Runde gestartet ( Game::nextArenaRound() )
 *
 * \param Card *card Die gespielte Karte
 * \param Monster *monster Das Ziel der ausgespielten Karte */

/*! \fn QList< Monster * > Game::getActiveMonster() const
 * \brief Gibt Game::activeMonster zurück */

/*! \fn void Game::initCards()
 * \brief Alle Karteninformationen aus der Datenbank auslesen und entsprechende Instanzen für die Liste Game::cards erzeugen.
 *
 * Für jede mögliche Karte aus der Datenbank wird genau EINE Instanz der Klasse Card erzeugt. Erhält der Spieler eie neue Karte, wird ein neuer Zeiger auf diese Karte erzeugt und in der Liste der Spielerkarten (siehe class Player) gespeichert. */

/*! \fn void Game::resetCards()
 * \brief Alle Karten des Spielers werden entfernt, alle vorhandenen Karten werden gelöscht. Dann werden die Karteninformationen aus der Datenbankausgelesen und entsprechend neue Karteninstanzen erstellt. */
