#include <QtTest>

#include "database.h"
#include <algorithm>

class DatabaseTest : public QObject
{
  Q_OBJECT

private:
  Database *db;
  QList< int > getIdsOfCards();
  QList< int > getIdsOfMonster();

public:
  DatabaseTest();
  ~DatabaseTest();
private slots:
  void init();
  void cleanup();
  void nameOfSkill();
  void numberOfCardsAndMonsters();
  void idsOfCards();
  void nameOfCard();
  void attackValueOfCard();
  void defenseValueOfCard();
  void energyCostOfCard();
  void skillIdOfCard();
  void skillValueOfCard();
  void monsterIds();
  void monsterName();
  void monsterLp();
  void monsterAttack();
  void monsterAttackChance();
  void monsterDefense();
  void monsterDefenseChance();
  void monsterLevel();
  void monsterSkills();
};

QList< int > DatabaseTest::getIdsOfCards()
{
  QList< int > ids;

  ids<<1<<2<<3<<4<<5<<6<<7<<8<<9;

  return ids;
}

QList< int > DatabaseTest::getIdsOfMonster()
{
  QList< int > ids;

  ids<<1<<2<<3<<4<<5;

  return ids;
}

DatabaseTest::DatabaseTest()
{
  db = Database::get();
}

DatabaseTest::~DatabaseTest()
{
  delete db;
  db = nullptr;
}

void DatabaseTest::init()
{}

void DatabaseTest::cleanup()
{}

void DatabaseTest::nameOfSkill()
{
  QCOMPARE( db->getSkillNameOfId( 1 ),  "noSkill" );
  QCOMPARE( db->getSkillNameOfId( 2 ),  "lifedrain" );
  QCOMPARE( db->getSkillNameOfId( 3 ),  "stun" );
  QCOMPARE( db->getSkillNameOfId( 4 ),  "weaken" );
  QCOMPARE( db->getSkillNameOfId( 5 ),  "blind" );
  QCOMPARE( db->getSkillNameOfId( 6 ),  "decay" );
  QCOMPARE( db->getSkillNameOfId( 7 ),  "poison" );
  QCOMPARE( db->getSkillNameOfId( 8 ),  "thorns" );
  QCOMPARE( db->getSkillNameOfId( 9 ),  "selfheal" );
  QCOMPARE( db->getSkillNameOfId( 10 ), "healall" );
  QCOMPARE( db->getSkillNameOfId( 11 ), "revive" );
  QCOMPARE( db->getSkillNameOfId( 12 ), "defendall" );
}

void DatabaseTest::numberOfCardsAndMonsters()
{
  QVERIFY( db->getNumberOfCards()>=9 );
  QVERIFY( db->getNumberOfMonsters()>=5 );
}

void DatabaseTest::idsOfCards()
{
  QList< int > idsTest;
  QList< int > idsOrig;

  idsTest = getIdsOfCards();
  idsOrig = db->getIdsOfCards();
  std::sort( idsOrig.begin(), idsOrig.end() );
  for ( int i = 0; i<idsTest.size(); i++ )
    QCOMPARE( idsOrig.at( i ), idsTest.at( i ) );
}

void DatabaseTest::nameOfCard()
{
  QList< int >     ids;
  QList< QString > names;

  ids   = getIdsOfCards();
  names = names<<"Schuss I"<<"Giftpfeil I"<<"Präzisionsschuss I"<<"Doppelschuss I"<<"Sperrfeuer I"<<"Rauchbombe I"<<"Beinschuss I"<<"Schildmauer I"<<"Banane I";
  for ( int i = 0; i<ids.size() && i<names.size(); i++ )
    QCOMPARE( db->getNameOfCard( ids.at( i ) ), names.at( i ) );
}

void DatabaseTest::attackValueOfCard()
{
  QList< int > values;
  QList< int > ids;

  ids = getIdsOfCards();
  values<<6<<4<<8<<12<<20<<6<<5<<0<<0;
  for ( int i = 0; i<ids.size() && i<values.size(); i++ )
    QCOMPARE( db->getAttackValueOfCard( ids.at( i ) ), values.at( i ) );
}

void DatabaseTest::defenseValueOfCard()
{
  QList< int > values;
  QList< int > ids;

  ids = getIdsOfCards();
  values<<0<<0<<0<<0<<0<<0<<0<<18<<0;
  for ( int i = 0; i<ids.size() && i<values.size(); i++ )
    QCOMPARE( db->getDefenseValueOfCard( ids.at( i ) ), values.at( i ) );
}

void DatabaseTest::energyCostOfCard()
{
  QList< int > values;
  QList< int > ids;

  ids = getIdsOfCards();
  values<<1<<1<<1<<2<<3<<1<<1<<3<<1;
  for ( int i = 0; i<ids.size() && i<values.size(); i++ )
    QCOMPARE( db->getEnergyCostOfCard( ids.at( i ) ), values.at( i ) );
}

void DatabaseTest::skillIdOfCard()
{
  QList< int > values;
  QList< int > ids;

  ids = getIdsOfCards();
  values<<1<<7<<1<<1<<1<<5<<4<<1<<9;
  for ( int i = 0; i<ids.size() && i<values.size(); i++ )
    QCOMPARE( db->getSkillIdOfCard( ids.at( i ) ), values.at( i ) );
}

void DatabaseTest::skillValueOfCard()
{
  QList< int > values;
  QList< int > ids;

  ids = getIdsOfCards();
  values<<0<<2<<0<<0<<0<<1<<2<<0<<5;
  for ( int i = 0; i<ids.size() && i<values.size(); i++ )
    QCOMPARE( db->getSkillValueOfCard( ids.at( i ) ), values.at( i ) );
}

void DatabaseTest::monsterIds()
{
  QList< int > idsTest;
  QList< int > idsOrig;

  idsTest = getIdsOfMonster();
  idsOrig = db->getIdsOfMonsters();
  std::sort( idsOrig.begin(), idsOrig.end() );
  QCOMPARE( idsOrig, idsTest );
}

void DatabaseTest::monsterName()
{
  QList< int >     ids;
  QList< QString > names;

  ids   = getIdsOfMonster();
  names = names<<"Goblin"<<"Ork"<<"Troll"<<"Skelett"<<"Schamane";
  for ( int i = 0; i<ids.size() && i<names.size(); i++ )
    QCOMPARE( db->getNameOfMonster( ids.at( i ) ), names.at( i ) );
}

void DatabaseTest::monsterLp()
{
  QList< int > values;
  QList< int > ids;

  ids = getIdsOfMonster();
  values<<20<<40<<80<<30<<30;
  for ( int i = 0; i<ids.size() && i<values.size(); i++ )
    QCOMPARE( db->getLpOfMonster( ids.at( i ) ), values.at( i ) );
}

void DatabaseTest::monsterAttack()
{
  QList< int > values;
  QList< int > ids;

  ids = getIdsOfMonster();
  values<<8<<12<<20<<10<<10;
  for ( int i = 0; i<ids.size() && i<values.size(); i++ )
    QCOMPARE( db->getAttackOfMonster( ids.at( i ) ), values.at( i ) );
}

void DatabaseTest::monsterAttackChance()
{
  QList< int > values;
  QList< int > ids;

  ids = getIdsOfMonster();
  values<<40<<60<<60<<70<<30;
  for ( int i = 0; i<ids.size() && i<values.size(); i++ )
    QCOMPARE( db->getAttackChanceOfMonster( ids.at( i ) ), values.at( i ) );
}

void DatabaseTest::monsterDefense()
{
  QList< int > values;
  QList< int > ids;

  ids = getIdsOfMonster();
  values<<10<<15<<0<<12<<12;
  for ( int i = 0; i<ids.size() && i<values.size(); i++ )
    QCOMPARE( db->getDefenseOfMonster( ids.at( i ) ), values.at( i ) );
}

void DatabaseTest::monsterDefenseChance()
{
  QList< int > values;
  QList< int > ids;

  ids = getIdsOfMonster();
  values<<30<<20<<0<<30<<20;
  for ( int i = 0; i<ids.size() && i<values.size(); i++ )
    QCOMPARE( db->getDefenseChanceOfMonster( ids.at( i ) ), values.at( i ) );
}

void DatabaseTest::monsterLevel()
{
  QList< int > values;
  QList< int > ids;

  ids = getIdsOfMonster();
  values<<1<<5<<10<<3<<3;
  for ( int i = 0; i<ids.size() && i<values.size(); i++ )
    QCOMPARE( db->getLevelOfMonster( ids.at( i ) ), values.at( i ) );
}

void DatabaseTest::monsterSkills()
{
  QList< QList< int > > skillIds;
  QList< int >          skillIds1, skillIds2, skillIds3, skillIds4, skillIds5;
  QList< int >          ids;

  ids = getIdsOfMonster();
  skillIds1<<12;
  skillIds2<<4;
  skillIds3<<3<<9;
  skillIds4<<11;
  skillIds5<<9<<10;
  skillIds<<skillIds1<<skillIds2<<skillIds3<<skillIds4<<skillIds5;

  for ( int i = 0; i<ids.size() && i<skillIds.size(); i++ )
  {
    QList< int > list = db->getSkillIdsOfMonster( ids.at( i ) );
    std::sort( list.begin(), list.end() );
    QCOMPARE( list, skillIds.at( i ) );
  }

  QCOMPARE( db->getSkillValueOfMonsterSkill( 1, 12 ),  8 );
  QCOMPARE( db->getSkillValueOfMonsterSkill( 3, 9 ),   20 );
  QCOMPARE( db->getSkillValueOfMonsterSkill( 3, 3 ),   1 );
  QCOMPARE( db->getSkillValueOfMonsterSkill( 5, 9 ),   20 );
  QCOMPARE( db->getSkillValueOfMonsterSkill( 5, 10 ),  10 );
  QCOMPARE( db->getSkillChanceOfMonsterSkill( 4, 11 ), 25 );
  QCOMPARE( db->getSkillChanceOfMonsterSkill( 2, 4 ),  20 );
  QCOMPARE( db->getSkillChanceOfMonsterSkill( 3, 3 ),  10 );
  QCOMPARE( db->getSkillChanceOfMonsterSkill( 3, 9 ),  30 );
  QCOMPARE( db->getSkillChanceOfMonsterSkill( 5, 10 ), 25 );
}

QTEST_APPLESS_MAIN( DatabaseTest )

#include "tst_databasetest.moc"
