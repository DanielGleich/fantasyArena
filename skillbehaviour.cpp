#include "skillbehaviour.h"
#include "someone.h"
#include "game.h"

// CardSkill
CardSkill::CardSkill(int attack, int defense, int skillValue, QString skillName)
  : Skill(skillValue, skillName)
{
  setAttackValue(attack);
  setDefenseValue(defense);
}

CardSkill::~CardSkill()
{}

int CardSkill::normalBehaviour(Someone* target)
{
  target->addDefense(defenseValue);
  return target->beAttacked(attackValue);
}

void CardSkill::playAgainst(Someone* target)
{}


// CardSkillLifeDrain
CardSkillLifeDrain::CardSkillLifeDrain(int attack, int defense, int skillValue, QString skillName)
  : CardSkill::CardSkill(attack, defense, skillValue, skillName)
{}

void CardSkillLifeDrain::playAgainst(Someone* target)
{
  Game::get()->getPlayer()->healBy( normalBehaviour(target)>skill ? skill : normalBehaviour(target) );
}

// CardSkillWeaken
CardSkillWeaken::CardSkillWeaken(int attack, int defense, int skillValue, QString skillName)
  : CardSkill::CardSkill(attack, defense, skillValue, skillName )
{}

void CardSkillWeaken::playAgainst(Someone* target)
{
  normalBehaviour(target);
  target->setWeaken(1);
}

// CardSkillStun
CardSkillStun::CardSkillStun(int attack, int defense, int skillValue, QString skillName)
  : CardSkill( attack, defense, skillValue, skillName)
{}

void CardSkillStun::playAgainst(Someone* target)
{
  normalBehaviour(target);
  target->setStunned(1);
}

// MonsterSkill
MonsterSkill::MonsterSkill(int skillValue, QString skillName, int skillChance)
  : Skill(skillValue,skillName)
{
  setChance(skillChance);
}

MonsterSkill::~MonsterSkill()
{}

// MonsterSkillAttack
MonsterSkillAttack::MonsterSkillAttack(int skillValue, QString skillName, int skillChance)
  : MonsterSkill(skillValue, skillName, skillChance)
{}

void MonsterSkillAttack::activateSkill()
{
  //Game::getPlayer()->beAttacked(attackValue);
}

// MonsterSkillDefend
MonsterSkillDefend::MonsterSkillDefend(int skillValue, QString skillName, int skillChance)
  : MonsterSkill(skillValue, skillName, skillChance)
{}

void MonsterSkillDefend::activateSkill()
{
  //this->
}
