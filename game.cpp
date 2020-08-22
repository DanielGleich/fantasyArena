#include "game.h"

Game *Game::game = nullptr;

Player *Game::getPlayer() const
{
  return player;
}

void Game::activateActiveMonster()
{
  for ( int i = 0; i<activeMonster.size(); i++ )
    if ( activeMonster[ i ] )
      activeMonster[ i ]->activate();
}

void Game::endPlayerMove()
{
  player->departHandCards();
  activateActiveMonster();
  player->drawToHandSize();
}

void Game::generateNewActiveMonsters()
{
  QList< Monster * > levelMonster = getMonsterOfLevelBetween( arenaLevel-5, arenaLevel+5 );

  for ( int i = 0; i<3; i++ )
    activeMonster<<new Monster( *levelMonster[ random( 0, levelMonster.size()-1 ) ] );
}

void Game::nextArenaRound()
{
  arenaLevel++;
  activeMonster.clear();
  player->departHandCards();
  player->shuffleDepartedCardsIntoDeck();
  player->drawToHandSize();
  generateNewActiveMonsters();
}

QList< Monster * > Game::getActiveMonster() const
{
  return activeMonster;
}

Game::Game( QObject *parent ) : QObject( parent )
{
  db = Database::get();
  qsrand( uint( QTime::currentTime().msec() ) );
  startNewGame();
}

Game::~Game()
{}

void Game::deleteCards()
{
  while ( cards.size() ) delete cards.takeLast();
}

void Game::initCards()
{
  QList< int > cardIds = db->getIdsOfCards();

  for ( int i = 0; i<cardIds.size(); i++ )
    cards<<new Card( cardIds[ i ],
                    db->getNameOfCard( cardIds[ i ] ),
                    db->getAttackValueOfCard( cardIds[ i ] ),
                    db->getDefenseValueOfCard( cardIds[ i ] ),
                    db->getEnergyCostOfCard( cardIds[ i ] ),
                    db->getRangeOfCard( cardIds[ i ] ),
                    db->getSkillNameOfId( db->getSkillIdOfCard( cardIds[ i ] ) ),
                    db->getSkillValueOfCard( db->getSkillIdOfCard( cardIds[ i ] ) ) );
}

void Game::deleteMonster()
{
  for ( int i = monster.size()-1; i>=0; i-- )
    delete monster.takeLast();
}

MonsterSkill *Game::initMonsterSkillAttack( int monsterId )
{
  return new MonsterSkillAttack( db->getAttackOfMonster( monsterId ), "Attack", db->getAttackChanceOfMonster( monsterId ) );
}

MonsterSkill *Game::initMonsterSkillDefend( int monsterId )
{
  return new MonsterSkillDefend( db->getDefenseOfMonster( monsterId ), "Defend", db->getDefenseChanceOfMonster( monsterId ) );
}

QList< MonsterSkill * > Game::initMonsterSkills( int monsterId )
{
  QList< MonsterSkill * > skills;
  QList< int >            skillIds = db->getSkillIdsOfMonster( monsterId );

  skills<<initMonsterSkillAttack( monsterId );
  skills<<initMonsterSkillDefend( monsterId );
  // TODO: weitere Skills

  return skills;
}

void Game::initMonster( int monsterId )
{
  monster<<new Monster( monsterId,
                       db->getNameOfMonster( monsterId ),
                       db->getLpOfMonster( monsterId ),
                       db->getLevelOfMonster( monsterId ),
                       initMonsterSkills( monsterId ) );
}

void Game::initMonsters()
{
  QList< int > monsterIds = db->getIdsOfMonsters();

  for ( int i = 0; i<monsterIds.size(); i++ )
    initMonster( monsterIds[ i ] );
}

Card *Game::getCard( int id )
{
  Card *card = nullptr;

  foreach( Card*c, cards )
  if ( c->getId()==id )
    card = c;

  return card;
}

void Game::resetMonster()
{
  deleteMonster();
  initMonsters();
}

void Game::resetCards()
{
  deleteCards();
  initCards();
}

void Game::setPlayerAttributes()
{
  if ( !player )
    return;
  player->setMaxLp( db->getMaxLpOfPlayer( PLAYERID ) );
  player->setLp( db->getLpOfPlayer( PLAYERID ) );
  player->setEnergy( db->getEnergyOfPlayer( PLAYERID ) );
  player->setMaxEnergy( db->getMaxEnergyOfPlayer( PLAYERID ) );
  player->setGold( db->getGoldOfPlayer( PLAYERID ) );
}

void Game::setPlayerCards()
{
  QList< int > cardIds = db->getCardIdsOfPlayer( PLAYERID );

  foreach( int i, cardIds ) player->addCard( getCard( i ) );
}

QList< Monster * > Game::getMonsterOfLevelBetween( int minLevel, int maxLevel  ) const
{
  QList< Monster * > levelMonster;

  foreach( Monster*m, monster )
  {
    if ( ( m->getLevel()>=minLevel ) && ( m->getLevel()<=maxLevel ) )
      levelMonster<<m;
  }

  return levelMonster;
}

void Game::removeMonster( Monster *monster )
{
  delete monster;
  activeMonster[ activeMonster.indexOf( monster ) ] = nullptr;
}

bool Game::areAllActiveMonsterDown()
{
  for ( int i = 0; i<activeMonster.size(); i++ )
    if ( activeMonster[ i ] )
      return false;

  return true;
}

void Game::removeSlainMonsters()
{
  for ( int i = 0; i<activeMonster.size(); i++ )
    if ( activeMonster[ i ] && ( activeMonster[ i ]->getLp()<=0 ) )
      removeMonster( activeMonster[ i ] );
}

void Game::playCardAgainstSomeone( Card *card, Someone *someone )
{
  player->playCardAgainst( card, someone );
  removeSlainMonsters();
  if ( areAllActiveMonsterDown() )
    nextArenaRound();
  emit( dataChanged() );
}

void Game::resetPlayer()
{
  delete player;
  player = new Player;
  setPlayerAttributes();
  setPlayerCards();
}

void Game::initGame()
{
  arenaLevel = 0;
  resetCards();
  resetPlayer();
  resetMonster();
}

Game *Game::get()
{
  if ( !game )
    game = new Game;

  return game;
}

void Game::startNewGame()
{
  initGame();
  nextArenaRound();
}
