#include "someone.h"

QList< Card * > Player::getDeck( void ) const
{
    return deck;
}

void Player::setDeck( const QList< Card * >& value )
{
    deck = value;
}

void Player::addCard(  Card *card )
{
    deck<<card;
}

void Player::drawCard()
{
    if ( !deck.size() )
        shuffleDepartedCardsIntoDeck();
    handCards << deck.takeLast();
}

void Player::departHandCard( Card *card )
{
    int index = handCards.indexOf( card );
    if ( index==-1 )
        return;
    departedCards <<  handCards.takeAt( index );
}

void Player::departHandCards( void )
{
    while ( handCards.size() != 0 )
        departedCards << handCards.takeLast();
}

void Player::shuffleDepartedCardsIntoDeck( void )
{
    while ( departedCards.size() )
        deck << departedCards.takeLast();
    shuffleDeck();
}

void Player::shuffleDeck( void )
{
    QList< Card * > cards;

    while ( deck.size() != 0 )
        cards << deck.takeAt( random( 0, deck.size()-1 ) );
    deck = cards;
}

QList< Card * > Player::getHandCards( void ) const
{
    return handCards;
}

void Player::drawToHandSize()
{
    for ( int i = 0; i<HANDSIZE; i++ )
        drawCard();
}

void Player::setEnergy( int value )
{
    energy = value;
    if ( energy<0 )
        energy = 0;
    if ( energy>maxEnergy )
        energy = maxEnergy;
}

void Player::addEnergy()
{
    this->energy = energy + 1 > this->maxEnergy ? maxEnergy : energy + 1;
}

void Player::reduceEnergyBy( int value )
{
    setEnergy( energy-value );
}

int Player::getMaxEnergy() const
{
    return maxEnergy;
}

void Player::setMaxEnergy( int value )
{
    maxEnergy = value;
}

int Player::getGold() const
{
    return gold;
}

void Player::setGold( int value )
{
    gold = value;
}

void Player::playCardAgainst( Card *card, Someone *someone )
{
    reduceEnergyBy( card->getEnergyCost() );
    card->getSkill()->playAgainst( someone );
    departHandCard( card );
}

int Player::getId() const
{
    return id;
}

void Player::setId(int value)
{
    id = value;
}

Player::Player()
{
    id = PLAYERID;
}

Player::~Player()
{}

int Player::getEnergy( void ) const
{
    return energy;
}

int Someone::getMaxLp( void ) const
{
    return maxLp;
}

int Someone::getStunned( void ) const
{
    return stunned;
}

void Someone::setStunned( int value )
{
    stunned = value;
}

int Someone::getWeaken( void ) const
{
    return weaken;
}

void Someone::setWeaken( int value )
{
    weaken = value;
}

int Someone::beAttacked( int attackValue )
{
    int damageDone = lpLoss( attackValue, defense );

    reduceLpBy( damageDone );
    reduceDefenseBy( attackValue );

    return damageDone;
}

void Someone::setMaxLp( int value )
{
    maxLp = value;
}

Someone::Someone()
{}

int Someone::getLp( void ) const
{
    return lp;
}

int Someone::getDefense( void ) const
{
    return defense;
}

void Someone::setDefense( int value )
{
    if ( value<0 )
        value = 0;
    defense = value;
}

void Someone::addDefense( int value )
{
    defense += value;
}

void Someone::reduceDefenseBy( int value )
{
    setDefense( defense-value );
}

void Someone::setLp( int value )
{
    lp = value;
    if ( lp<0 )
        lp = 0;
    if ( lp>maxLp )
        lp = maxLp;
}

void Someone::reduceLpBy( int value )
{
    setLp( value >= lp ? 0 : lp-value );
}

void Someone::healBy( int value )
{
    setLp( value + lp >= maxLp ? maxLp : lp+value );
}

int Monster::getId() const
{
    return id;
}

void Monster::setId( int value )
{
    id = value;
}

QString Monster::getName() const
{
    return name;
}

void Monster::setName( const QString& value )
{
    name = value;
}

int Monster::getLevel() const
{
    return level;
}

void Monster::setLevel( int value )
{
    level = value;
}

void Monster::chooseSkill()
{
    int          sumOfChance = 0;
    QList< int > chances;
    int          r;

    for ( int i = 0; i<skills.size(); i++ )
    {
        chances<<skills[ i ]->getChance();
        sumOfChance += chances.last();
    }
    r = random( 1, sumOfChance );
    for ( int i = 0; i<skills.size() && i<chances.size(); i++ )
    {
        if ( r<chances[ i ] )
        {
            nextSkill = skills[ i ];
            break;
        }
        r -= chances[ i ];
    }
}

void Monster::setSkills( QList< MonsterSkill * > skills )
{
    this->skills = skills;
}

QList<MonsterSkill *> Monster::getSkills()
{
    return skills;
}

void Monster::debug()
{
    if ( !DEBUG )
        return;
    qDebug()<<"Monster-Information";

    qDebug()<<"----------------------------------";
    qDebug()<<"Monster:       "<<name;
    qDebug()<<"Level:         "<<level;
    qDebug()<<"LP:            "<<lp<<"/"<<maxLp;
    qDebug()<<"Defense:       "<<defense;
    qDebug()<<"\n";
}

void Monster::activate()
{
    nextSkill->activateSkill(this);
    chooseSkill();
}

MonsterSkill *Monster::getNextSkill()
{
    if ( !nextSkill )
        chooseSkill();

    return nextSkill;
}

Monster::Monster( int myId, QString name, int myLp, int level, QList< MonsterSkill * > skills  )
{
    setId( myId );
    setMaxLp( myLp );
    setLp( myLp );
    setName( name );
    setLevel( level );
    setSkills( skills );
    //debug();
}

Monster::Monster(Monster *m)
{
    setId( m->getId());
    setMaxLp( m->getMaxLp());
    setLp( m->getLp());
    setName( m->getName());
    setLevel( m->getLevel());
    setSkills( m->getSkills() );
}
