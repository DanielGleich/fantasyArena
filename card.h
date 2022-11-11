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
    int       id;                                                     // Datenbank-ID dieser Karte
    QString   name;                                                   // Name der Karte
    int       energyCost;                                             // Energiekosten der Karte
    int       range;                                                  // Reichweite der Karte
    CardSkill *skill = nullptr;                                       // Skill
public:
    explicit  Card( int id, QString name, int attack, int defense, int energy, int range, QString skillName, int skillValue );
    int       getId() const                       {return id;}
    void      setId( int value )                  {id = value;}
    QString   getName() const                     {return name;}
    void      setName( const QString& value )     {name = value;}
    int       getEnergyCost() const               {return energyCost;}
    void      setEnergyCost( int value )          {energyCost = value;}
    int       getRange() const                    {return range;}
    void      setRange( int value )               {range = value;}
    CardSkill *getSkill() const                   {return skill;}
    void      setSkill( CardSkill *value )        {skill = value;}
    bool      isMelee() const                     {return range == 1;}
    bool      isRange() const                     {return range > 1;}
    bool      isSpecial() const                   {return range == 0;}
};

#endif // CARD_H
