#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "card.h"
#include "config.h"
#include "database.h"
#include "someone.h"

/*********************************************\
|*                                           *|
|*  Game                                     *|
|*                                           *|
\*********************************************/
class Game : public QObject
{
    Q_OBJECT

private:
    QList< Monster * > *activeMonsters;                             // Die in der aktuellen Arenalevel-Runde (noch) aktiven (und nicht getöteten) Monster
    int                arenaLevel = 0;
    QList< Card * >    cards;
    Database           *db        = nullptr;
    static Game        *game;
    QList< Monster * > monsters;                                   // Alle in der Datenbank abgelegten Monster aller Level
    Player             *player    = nullptr;

    Game( QObject *parent = nullptr );
    ~Game();
    void                    activateActiveMonsterTurn();
    bool                    areAllActiveMonsterDown();
    void                    deleteCards();
    void                    deleteMonsters();
    void                    generateNewActiveMonsters();
    Card                    *getCard( int id );
    QList< Monster * >      getMonsterOfLevelBetween( int minLevel, int maxLevel ) const;
    void                    initCards();
    void                    initGame();
    void                    initMonster( int monsterId );
    QList< MonsterSkill * > initMonsterSkills( int monsterId );
    MonsterSkill            *initMonsterSkillAttack( int monsterId );
    MonsterSkill            *initMonsterSkillDefend( int monsterId );
    void                    initMonsters();
    void                    initPlayer();
    void                    resetCards();
    void                    resetMonsters();
    void                    resetPlayer();
    void                    setPlayerAttributes();
    void                    setPlayerCards();
    void                    clearDeadMonster();


public:
    static Game        *get();
    QList< Monster * > *getActiveMonsters() const;
    Player             *getPlayer() const;
    void               nextArenaRound();
    void               nextTurn();
    void               playCardAgainstSomeone( Card *card, Someone *someone );
    void               playCardOnPlayer(Card *card);
    void               removeActiveMonster( Monster *monster );

signals:
    void               dataChanged();
};

#endif // GAME_H
