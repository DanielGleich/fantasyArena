#include "card.h"

/**********************************************************************\
|                                                                      |
|   Card                                                               |
|   - Modell zu den Spielkarten                                        |
|                                                                      |
\**********************************************************************/


/*
void Card::debug()
{
  if ( !DEBUG )
    return;
  qDebug()<<"Karten-Information";
  qDebug()<<"---------------------------------";
  qDebug()<<"Name:          "<<name;
  qDebug()<<"Range:         "<<range;
  qDebug()<<"Energiekosten: "<<energyCost;
  qDebug()<<"AttackValue:   "<<skill->getAttackValue();
  qDebug()<<"DefenseValue:  "<<skill->getDefenseValue();
  if ( !skill )
  {
    qDebug()<<"SkillName:     "<<skill->getSkillName();
    qDebug()<<"SkillName:     "<<skill->getSkillValue();
    qDebug()<<"SkillValue:    "<<skill->getSkillValue();
  }
  qDebug()<<"\n";
}
*/

Card::Card( int id, QString name, int attack, int defense, int energy, int range, QString skillName, int skillValue )
{
  setId( id );
  setName( name );
  setRange( range );
  setEnergyCost( energy );
  if ( skillName=="lifedrain" )
    skill = new CardSkillLifeDrain( attack, defense, skillValue, skillName );
  else if ( skillName=="stun" )
    skill = new CardSkillStun( attack, defense, skillValue, skillName );
  else if ( skillName=="weaken" )
    skill = new CardSkillWeaken( attack, defense, skillValue, skillName );
  else
    skill = new CardSkill( attack, defense, skillValue, "normal" );
}

