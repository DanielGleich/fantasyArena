#include "game.h"

Game *Game::game = nullptr;

Player *Game::getPlayer() const {
    return player;
}

void Game::activateActiveMonsterTurn() {
    for ( int i = 0; i<activeMonsters->size(); i++ )
        if ( activeMonsters->at(i))
            activeMonsters->at(i)->activate();
}

void Game::generateNewActiveMonsters() {
    QList< Monster * > levelMonster = getMonsterOfLevelBetween( arenaLevel-5, arenaLevel+5 );

    for ( int i = 0; i<3; i++ )
        activeMonsters->append(new Monster( *levelMonster[ random( 0, levelMonster.size()-1 ) ] ));
}

void Game::nextArenaRound() {
    arenaLevel++;
    activeMonsters->clear();
    generateNewActiveMonsters();
}

void Game::nextTurn() {
    clearDeadMonster();
    if ( areAllActiveMonsterDown() )
        nextArenaRound();
    player->departHandCards();
    player->addEnergy();
    player->shuffleDepartedCardsIntoDeck();
    activateActiveMonsterTurn();
    player->drawToHandSize();
    emit dataChanged();
}

QList< Monster * > *Game::getActiveMonsters() const {
    return activeMonsters;
}

Game::Game( QObject *parent ) : QObject( parent ) {
    db = Database::get();
    activeMonsters = new QList<Monster*>();
    qsrand( uint( QTime::currentTime().msec() ) );
    initGame();
}

Game::~Game() {}

void Game::deleteCards() {
    while ( cards.size() ) delete cards.takeLast();
}

void Game::initCards() {
    QList< int > cardIds = db->getIdsOfCards();

    for ( int i = 0; i<cardIds.size(); i++ )
        cards << new Card( cardIds[ i ],
                           db->getNameOfCard( cardIds[ i ] ),
                           db->getAttackValueOfCard( cardIds[ i ] ),
                           db->getDefenseValueOfCard( cardIds[ i ] ),
                           db->getEnergyCostOfCard( cardIds[ i ] ),
                           db->getRangeOfCard( cardIds[ i ] ),
                           db->getSkillNameOfId( db->getSkillIdOfCard( cardIds[ i ] ) ),
                           db->getSkillValueOfCard( db->getSkillIdOfCard( cardIds[ i ] ) ) );
}

void Game::deleteMonsters() {
    for ( int i = monsters.size()-1; i>=0; i-- )
        delete monsters.takeLast();
}

MonsterSkill *Game::initMonsterSkillAttack( int monsterId ) {
    return new MonsterSkillAttack( db->getAttackOfMonster( monsterId ), "Attack", db->getAttackChanceOfMonster( monsterId ), db->getAttackOfMonster(monsterId)/2 );
}

MonsterSkill *Game::initMonsterSkillDefend( int monsterId ) {
    return new MonsterSkillDefend( db->getDefenseOfMonster( monsterId ), "Defend", db->getDefenseChanceOfMonster( monsterId ), db->getDefenseOfMonster(monsterId) );
}

QList< MonsterSkill * > Game::initMonsterSkills( int monsterId ) {
    QList< MonsterSkill * > skills;
    QList< int >            skillIds = db->getSkillIdsOfMonster( monsterId );

    skills<<initMonsterSkillAttack( monsterId );
    skills<<initMonsterSkillDefend( monsterId );
    // TODO: weitere Skills

    return skills;
}

void Game::initMonster( int monsterId ) {
    monsters<<new Monster( monsterId,
                          db->getNameOfMonster( monsterId ),
                          db->getLpOfMonster( monsterId ),
                          db->getLevelOfMonster( monsterId ),
                          initMonsterSkills( monsterId ) );
}

void Game::initMonsters() {
    QList< int > monsterIds = db->getIdsOfMonsters();

    for ( int i = 0; i<monsterIds.size(); i++ )
        initMonster( monsterIds[ i ] );

    for (int i = 0; i < ARENA_MONSTER_COUNT; i++) {
        activeMonsters->append(new Monster(monsters[(random(0,monsters.count()-1))]));
    }
}

Card *Game::getCard( int id ) {
    Card *card = nullptr;

    foreach( Card *c, cards )
        if ( c->getId() == id )
            card = c;

    return card;
}

void Game::resetMonsters() {
    deleteMonsters();
    initMonsters();
}

void Game::resetCards() {
    deleteCards();
    initCards();
}

void Game::initPlayer() {
    player = new Player();
    setPlayerAttributes();
    setPlayerCards();
    player->drawToHandSize();
}

void Game::setPlayerAttributes() {
    if ( !player )
        return;
    player->setMaxLp( db->getMaxLpOfPlayer( PLAYERID ) );
    player->setLp( db->getLpOfPlayer( PLAYERID ) );
    player->setMaxEnergy( db->getMaxEnergyOfPlayer( PLAYERID ) );
    player->setEnergy( db->getEnergyOfPlayer( PLAYERID ) );
    player->setGold( db->getGoldOfPlayer( PLAYERID ) );
}

void Game::setPlayerCards() {
    QList< int > cardIds = db->getCardIdsOfPlayer( PLAYERID );
    foreach( int i, cardIds ) {
        int cardCount = db->getCardCountOfPlayer(player->getId(),i);
        for( int j = 0; j < cardCount; j++) {
            player->addCard( new Card(*getCard( i )) );
        }
    }
}

void Game::clearDeadMonster() {
    QList<Monster*> deadMonster;
    for(int i = 0; i < activeMonsters->length(); i++)
        if (activeMonsters->at(i)->getLp() <= 0)
            deadMonster.append(activeMonsters->at(i));
    foreach(Monster* m, deadMonster) {
        activeMonsters->removeOne(m);
        delete m;
    }
}

QList< Monster * > Game::getMonsterOfLevelBetween( int minLevel, int maxLevel  ) const {
    QList< Monster * > levelMonster;

    foreach( Monster *m, monsters ) {
        if ( ( m->getLevel() >= minLevel ) && ( m->getLevel() <= maxLevel ) )
            levelMonster << m;
    }
    return levelMonster;
}

void Game::removeActiveMonster( Monster *monster ) {
    delete monster;
    bool test = activeMonsters->removeOne(monster);
}

bool Game::areAllActiveMonsterDown() {
    for ( int i = 0; i<activeMonsters->size(); i++ )
        if ( activeMonsters->at(i))
            return false;
    return true;
}

void Game::playCardAgainstSomeone( Card *card, Someone *someone ) {
    if ( player->getEnergy() < card->getEnergyCost() )
        return;
    player->playCardAgainst( card, someone );
    clearDeadMonster();
    emit( dataChanged() );
}

void Game::playCardOnPlayer(Card *card) {
    if ( player->getEnergy() < card->getEnergyCost() )
        return;
    player->playCardAgainst( card, player );
    clearDeadMonster();
    emit( dataChanged() );
}

void Game::resetPlayer() {
    delete player;
    initPlayer();
}

void Game::initGame() {
    arenaLevel = 1;
    initCards();
    initPlayer();
    initMonsters();
}

Game *Game::get() {
    if ( !game )
        game = new Game;
    return game;
}
