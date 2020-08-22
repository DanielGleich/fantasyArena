#ifndef CARD_H
#define CARD_H

#include <QObject>
#include "skillbehaviour.h"

/*********************************************\
|*                                           *|
|*  Card                                     *|
|*                                           *|
\*********************************************/
class Card
{
private:
  int       id;                                                     /// Datenbank-ID dieser Karte
  QString   name;                                                   /// Name der Karte
  int       energyCost;                                             /// Energiekosten der Karte
  int       range;                                                  /// Reichweite der Karte
  CardSkill *skill = nullptr;                                       /// Skill

public:
  Card( int id, QString name, int attack, int defense, int energy, int range, QString skillName, int skillValue );
  int       getId() const                       {return id;}
  void      setId( int value )                  {this->id = value;}
  QString   getName() const                     {return name;}
  void      setName( const QString& value )     {this->name = value;}
  int       getEnergyCost() const               {return energyCost;}
  void      setEnergyCost( int value )          {energyCost = value;}
  int       getRange() const                    {return range;}
  void      setRange( int value )               {range = value;}
  CardSkill *getSkill() const                   {return skill;}
  void      setSkill( CardSkill *value )        {skill = value;}
  bool      isMelee() const                     {return range==0;}
  bool      isRange() const                     {return range==1;}
  bool      isSpecial() const                   {return range>1;}
  //void      debug( void );
};

#endif // CARD_H

/*! \class Card
 * \brief instanzen dieser klasse speichern alle Informationen zu einer Spielkarte.
 *
 * Zwecks Abwicklung eines Angriffs wird die Klasse SkillBehaviour verwendet. */
