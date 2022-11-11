#ifndef SKILLBEHAVIOUR_H
#define SKILLBEHAVIOUR_H

#include <QObject>
#include "config.h"

class Someone;

/*********************************************\
|*                                           *|
|*  Skill                                    *|
|*                                           *|
\*********************************************/
class Skill
{
protected:
    int attackValue;
    int defenseValue;
    int skill;                // Wert, mit dem der Skill ausgeführt wird
    QString name     = "noSkill";

public:
    Skill( int skillValue, QString skillName )        { setSkillValue( skillValue ); setSkillName( skillName ); }
    int          getSkillValue() const                {return skill;}
    void         setSkillValue( int value )           {this->skill = value;}
    QString      getSkillName() const                 {return name;}
    void         setSkillName( const QString& value ) {this->name = value;}
};

/*********************************************\
|*                                           *|
|*  CardSkill                                *|
|*                                           *|
\*********************************************/
class CardSkill : public Skill
{
protected:
    int normalBehaviour( Someone *target );       // gibt den verursachten Schaden zurück

public:
    CardSkill( int attack, int defense, int skillValue, QString skillName );
    virtual ~CardSkill();
    int           getAttackValue() const            {return attackValue;}
    void          setAttackValue(int value)         {this->attackValue = value;}
    int           getDefenseValue() const           {return defenseValue;}
    void          setDefenseValue(int value)        {this->defenseValue = value;}
    virtual void  playAgainst( Someone *target );
};

/*********************************************\
|*                                           *|
|*  CardSkillLifeDrain                       *|
|*                                           *|
\*********************************************/
class CardSkillLifeDrain : public CardSkill
{
public:
    CardSkillLifeDrain( int attack, int defense, int skillValue, QString skillName );
    void playAgainst( Someone *target ) override;
};

/*********************************************\
|*                                           *|
|*  CardSkillStun                            *|
|*                                           *|
\*********************************************/
class CardSkillStun : public CardSkill
{
public:
    CardSkillStun( int attack, int defense, int skillValue, QString skillName );
    void playAgainst(Someone *target ) override;
};

/*********************************************\
|*                                           *|
|*  CardSkillWeaken                          *|
|*                                           *|
\*********************************************/
class CardSkillWeaken : public CardSkill
{
public:
    CardSkillWeaken( int attack, int defense, int skillValue, QString skillName );
    void playAgainst( Someone *target );
};

/*********************************************\
|*                                           *|
|*  MonsterSkill                             *|
|*                                           *|
\*********************************************/
class MonsterSkill : public Skill
{
protected:
    int chance;

public:
    MonsterSkill( int skillValue, QString skillName, int skillChance );
    virtual ~MonsterSkill();
    virtual void activateSkill(Someone *target) = 0;
    int          getChance() const        {return chance;}
    void         setChance( int value )   {this->chance = value;}
};

/*********************************************\
|*                                           *|
|*  MonsterSkillAttack                       *|
|*                                           *|
\*********************************************/
class MonsterSkillAttack : public MonsterSkill
{
public:
    MonsterSkillAttack( int skillValue, QString skillName, int skillChance, int attackValue );
    void activateSkill(Someone *target) override;
};

/*********************************************\
|*                                           *|
|*  MonsterSkillDefend                       *|
|*                                           *|
\*********************************************/
class MonsterSkillDefend : public MonsterSkill
{
public:
    MonsterSkillDefend(int skillValue, QString skillName, int skillChance , int defendValue);
    void activateSkill(Someone *target) override;
};

#endif // SKILLBEHAVIOUR_H
