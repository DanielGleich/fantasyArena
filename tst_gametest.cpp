#include "card.h"
#include "config.h"
#include "game.h"
#include <QtTest>

class GameTest : public QObject
{
  Q_OBJECT

private:
  Game *g;
public:
  GameTest();
  ~GameTest();

private slots:
  void init();
  void cleanup();
  void myRandom();
  void cards();
};

GameTest::GameTest()
{}

GameTest::~GameTest()
{}

void GameTest::init()
{
  g = Game::get();
}

void GameTest::cleanup()
{
  delete g;
  g = nullptr;
}

void GameTest::myRandom()
{
  for ( int i = 0; i<100; i++ )
    QVERIFY( random( 5, 9 )>=5 && random( 5, 9 )<=9 );
  for ( int i = 0; i<100; i++ )
    QVERIFY( random( 4, 2 )>=2 && random( 4, 2 )<=4 );
}

void GameTest::cards()
{
  QMap< int, Card * > allCards = g->getCards();

  QVERIFY( allCards.count()>=10 );
  QCOMPARE( allCards[ 1 ]->getId(),               1 );
  QCOMPARE( allCards[ 5 ]->getId(),               5 );
  QCOMPARE( allCards[ 2 ]->getName(), "Giftpfeil I" );
  QCOMPARE( allCards[ 9 ]->getName(),    "Banane I" );
  QCOMPARE( allCards[ 3 ]->getAttackValue(),      8 );
  QCOMPARE( allCards[ 8 ]->getAttackValue(),      0 );
  QCOMPARE( allCards[ 4 ]->getDefenseValue(),     0 );
  QCOMPARE( allCards[ 8 ]->getDefenseValue(),    18 );
  QCOMPARE( allCards[ 6 ]->getEnergyCost(),       1 );
  QCOMPARE( allCards[ 12 ]->getEnergyCost(),     -1 );
  QCOMPARE( allCards[ 6 ]->getSkill(),      "blind" );
  QCOMPARE( allCards[ 1 ]->getSkill(),    "noSkill" );
  QCOMPARE( allCards[ 2 ]->getSkillValue(),       2 );
  QCOMPARE( allCards[ 9 ]->getSkillValue(),       5 );
}

QTEST_APPLESS_MAIN( GameTest )

#include "tst_gametest.moc"
