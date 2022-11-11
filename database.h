#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>
#include "config.h"

class Database : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase    db;                                                     // Datenbank
    static Database *database;                                              // Zeiger auf die Singleton-Instanz dieser Klasse
    Database( QObject *parent = nullptr );
public:
    ~Database( void );
    static Database *get();
    bool            loadDB( void );
    void            closeDB( void );
    QSqlDatabase    getDb( void ) const;
    QString         getSkillNameOfId( int skillId ) const;
    int             getNumberOfCards( void ) const;
    int             getNumberOfMonsters( void ) const;
    QList< int >    getIdsOfCards( void ) const;
    QString         getNameOfCard( int cardId ) const;
    int             getAttackValueOfCard( int cardId ) const;
    int             getDefenseValueOfCard( int cardId ) const;
    int             getEnergyCostOfCard( int cardId ) const;
    int             getSkillIdOfCard( int cardId ) const;
    int             getSkillValueOfCard( int cardId ) const;
    int             getRangeOfCard( int cardId ) const;
    QList< int >    getIdsOfMonsters( void ) const;
    QString         getNameOfMonster( int monsterId ) const;
    int             getLpOfMonster( int monsterId ) const;
    int             getAttackOfMonster( int monsterId ) const;
    int             getAttackChanceOfMonster( int monsterId ) const;
    int             getDefenseOfMonster( int monsterId ) const;
    int             getDefenseChanceOfMonster( int monsterId ) const;
    int             getLevelOfMonster( int monsterId ) const;
    QList< int >    getSkillIdsOfMonster( int monsterId ) const;
    int             getSkillValueOfMonsterSkill( int monsterId, int skillId ) const;
    int             getSkillChanceOfMonsterSkill( int monsterId, int skillId ) const;
    QList< int >    getCardIdsOfPlayer( int playerId ) const;
    int             getCardCountOfPlayer( int playerId, int cardId ) const;
    QList< int >    getIdsOfPlayers() const;
    int             getLpOfPlayer( int playerId ) const;
    int             getMaxLpOfPlayer( int playerId ) const;
    int             getEnergyOfPlayer( int playerId ) const;
    int             getMaxEnergyOfPlayer( int playerId ) const;
    int             getGoldOfPlayer( int playerId ) const;
};

#endif // DATABASE_H
