#ifndef SOMEONE_H
#define SOMEONE_H

#include <QObject>
#include "card.h"
#include "config.h"

class CardSkill;
class Monster;

/*********************************************\
|*                                           *|
|*  Someone                                  *|
|*                                           *|
\*********************************************/
class Someone
{
protected:
  int lp;
  int maxLp;                      /// maximalen Lp
  int defense = 0;                /// Schilde (reduzieren einen Angriff)
  int stunned = 0;                /// Anzahl der Runden, die jmd. betäubt ist
  int weaken  = 0;                /// Anzahl der Runden, die jmd. geschwächt ist -> 25% weniger attack
public:
  Someone();
  int  getLp( void ) const;
  int  getDefense( void ) const;
  void setDefense( int value );
  void addDefense( int value );
  void reduceDefenseBy( int value );
  void setLp( int value );
  void reduceLpBy( int value );
  void healBy( int value );
  int  getMaxLp( void ) const;
  void setMaxLp( int value );
  int  getStunned( void ) const;
  void setStunned( int value );
  int  getWeaken( void ) const;
  void setWeaken( int value );
  int  beAttacked( int attackValue );
};

/*********************************************\
|*                                           *|
|*  Player                                   *|
|*                                           *|
\*********************************************/
class Player : public Someone
{
private:
  QList< Card * > deck;           /// Karten im (Nachzieh-)Spielerdeck
  QList< Card * > handCards;      /// Karten in der Hand
  QList< Card * > departedCards;  /// abgelegte Karten
  int             energy;
  int             maxEnergy;
  int             gold;
public:
  Player();
  ~Player();
  int             getEnergy( void ) const;
  void            setEnergy( int value );
  void            reduceEnergyBy( int value );
  QList< Card * > getDeck( void ) const;
  void            setDeck( const QList< Card * >& value );
  void            addCard( Card *card );
  void            drawCard( void );
  void            departHandCard( Card *card );
  void            departHandCards( void );
  void            shuffleDepartedCardsIntoDeck( void );
  void            shuffleDeck( void );
  QList< Card * > getHandCards( void ) const;
  void            drawToHandSize();
  int             getMaxEnergy() const;
  void            setMaxEnergy( int value );
  int             getGold() const;
  void            setGold( int value );
  void            playCardAgainst( Card *card, Someone *someone );
};

/*********************************************\
|*                                           *|
|*  Monster                                  *|
|*                                           *|
\*********************************************/
class Monster : public Someone
{
private:
  int                     id;               /// eindeutige id des Monsters (aus der Datenbank)
  QString                 name;             /// Monstername
  int                     level;            /// Level (Gefährlichkeit) des Monsters
  QList< MonsterSkill * > skill;            /// Alle Skills des Monsters
  MonsterSkill            *nextSkill = nullptr;   /// Skill, der vom Monster als nächstes ausgeführt wird

public:
  Monster( int id, QString name, int lp, int level, QList< MonsterSkill * > skills );
  int          getId() const;
  void         setId( int value );
  QString      getName() const;
  void         setName( const QString& value );
  int          getLevel() const;
  void         setLevel( int value );
  void         chooseSkill();
  void         setSkills( QList< MonsterSkill * > skills );
  void         debug();
  void         activate();
  MonsterSkill *getNextSkill();
};

#endif // SOMEONE_H

/*
 * doxygen doxygen.conf
*/

/*! \class Monster
    \brief Klasse einer einzelnen Monsterverwaltung
     Diese Klasse ist ein gegnerisches Monster.

    \var Monster::id
    die eindeutige Nummer eines Monsters

    \fn Monster::Monster()
    \brief Erstellmethode des Monsters
    Hier werden alle Startwerte eines Monsterobjekts gesetzt. Darunter zählen die Eigenschaften Monster::id, Monster::name, Monster::lp, Monster::level, Monster::skill

    \fn void Monster::setName()
    \brief Namessetzung des Monsters.
    \param value Der neue Name des Monsters

    Hier wird der Name des Monsters gesetzt.

    \fn QString Monster::getName()
    \brief Name des Monsters.

    Hier wird der Name des Monsters zurückgegeben.
    \return Der Name des Monsters



*/
