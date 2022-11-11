#include "database.h"

Database *Database::database = nullptr;

QSqlDatabase Database::getDb( void ) const
{
    return db;
}

QString Database::getSkillNameOfId( int skillId ) const
{
    QSqlQuery query;
    QString   skillname( "noSkill" );

    query.prepare( "SELECT skillName FROM skill WHERE skillId=:id" );
    query.bindValue( ":id", skillId );
    query.exec();
    if ( query.first() )
        skillname = query.value( 0 ).toString();

    return skillname;
}

int Database::getNumberOfCards() const
{
    QSqlQuery query;
    int       number = 0;

    query.prepare( "SELECT * FROM card" );
    query.exec();
    while ( query.next() ) number++;

    return number;
}

int Database::getNumberOfMonsters() const
{
    QSqlQuery query;
    int       number = 0;

    query.prepare( "SELECT * FROM monster" );
    query.exec();
    while ( query.next() ) number++;

    return number;
}

QList< int > Database::getIdsOfCards() const
{
    QList< int > ids;
    QSqlQuery    query;

    query.prepare( "SELECT * FROM card" );
    query.exec();
    while ( query.next() ) ids<<query.value( 0 ).toInt();

    return ids;
}

QString Database::getNameOfCard( int cardId ) const
{
    QString   name;
    QSqlQuery query;

    query.prepare( "SELECT cardName FROM card WHERE cardId=:id" );
    query.bindValue( ":id", cardId );
    query.exec();
    if ( query.first() )
        name = query.value( 0 ).toString();

    return name;
}

int Database::getAttackValueOfCard( int cardId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT attackValue FROM card WHERE cardId=:id" );
    query.bindValue( ":id", cardId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

int Database::getDefenseValueOfCard( int cardId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT defenseValue FROM card WHERE cardId=:id" );
    query.bindValue( ":id", cardId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

int Database::getEnergyCostOfCard( int cardId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT energyCost FROM card WHERE cardId=:id" );
    query.bindValue( ":id", cardId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

int Database::getSkillIdOfCard( int cardId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT skillId FROM card WHERE cardId=:id" );
    query.bindValue( ":id", cardId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

int Database::getSkillValueOfCard( int cardId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT skillValue FROM card WHERE cardId=:id" );
    query.bindValue( ":id", cardId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

int Database::getRangeOfCard( int cardId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT range FROM card WHERE cardId=:id" );
    query.bindValue( ":id", cardId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

QList< int > Database::getIdsOfMonsters() const
{
    QList< int > ids;
    QSqlQuery    query;

    query.prepare( "SELECT * FROM monster" );
    query.exec();
    while ( query.next() ) ids<<query.value( 0 ).toInt();

    return ids;
}

QString Database::getNameOfMonster( int monsterId ) const
{
    QString   name;
    QSqlQuery query;

    query.prepare( "SELECT monsterName FROM monster WHERE monsterId=:id" );
    query.bindValue( ":id", monsterId );
    query.exec();
    if ( query.first() )
        name = query.value( 0 ).toString();

    return name;
}

int Database::getLpOfMonster( int monsterId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT monsterLp FROM monster WHERE monsterId=:id" );
    query.bindValue( ":id", monsterId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

int Database::getAttackOfMonster( int monsterId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT monsterAttack FROM monster WHERE monsterId=:id" );
    query.bindValue( ":id", monsterId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

int Database::getAttackChanceOfMonster( int monsterId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT monsterAttackChance FROM monster WHERE monsterId=:id" );
    query.bindValue( ":id", monsterId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

int Database::getDefenseOfMonster( int monsterId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT monsterDefense FROM monster WHERE monsterId=:id" );
    query.bindValue( ":id", monsterId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

int Database::getDefenseChanceOfMonster( int monsterId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT monsterDefenseChance FROM monster WHERE monsterId=:id" );
    query.bindValue( ":id", monsterId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

int Database::getLevelOfMonster( int monsterId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT monsterLevel FROM monster WHERE monsterId=:id" );
    query.bindValue( ":id", monsterId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

QList< int > Database::getSkillIdsOfMonster( int monsterId ) const
{
    QList< int > ids;
    QSqlQuery    query;

    query.prepare( "SELECT skillId FROM zuoMonsterSkill WHERE monsterId=:id" );
    query.bindValue( ":id", monsterId );
    query.exec();
    while ( query.next() ) ids<<query.value( 0 ).toInt();

    return ids;
}

int Database::getSkillValueOfMonsterSkill( int monsterId, int skillId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT skillValue FROM zuoMonsterSkill WHERE monsterId=:idMonster AND skillId=:idSkill" );
    query.bindValue( ":idMonster", monsterId );
    query.bindValue( ":idSkill",   skillId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

int Database::getSkillChanceOfMonsterSkill( int monsterId, int skillId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT skillChance FROM zuoMonsterSkill WHERE monsterId=:idMonster AND skillId=:idSkill" );
    query.bindValue( ":idMonster", monsterId );
    query.bindValue( ":idSkill",   skillId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

QList< int > Database::getCardIdsOfPlayer( int playerId ) const
{
    QList< int > ids;
    QSqlQuery    query;

    query.prepare( "SELECT cardId FROM zuoPlayerCard WHERE playerId=:id" );
    query.bindValue( ":id", playerId );
    query.exec();
    while ( query.next() ) {
        ids<<query.value( 0 ).toInt();
    }

    return ids;
}

int Database::getCardCountOfPlayer( int playerId, int cardId ) const
{
    int       value = 0;
    QSqlQuery query;

    query.prepare( "SELECT numberOfCards FROM zuoPlayerCard WHERE cardId=:idCard AND playerId=:idPlayer" );
    query.bindValue( ":idCard",   cardId );
    query.bindValue( ":idPlayer", playerId );
    query.exec();
    if ( query.first() )
        value = query.value( 0 ).toInt();

    return value;
}

QList< int > Database::getIdsOfPlayers() const
{
    QList< int > ids;
    QSqlQuery    query;

    query.prepare( "SELECT playerId FROM player" );
    query.exec();
    while ( query.next() ) ids<<query.value( 0 ).toInt();

    return ids;
}

int Database::getLpOfPlayer( int playerId ) const
{
    int       lp = 0;
    QSqlQuery query;

    query.prepare( "SELECT lp FROM player WHERE playerId=:id" );
    query.bindValue( ":id", playerId );
    query.exec();
    if ( query.first() )
        lp = query.value( 0 ).toInt();

    return lp;
}

int Database::getMaxLpOfPlayer( int playerId ) const
{
    int       lp = 0;
    QSqlQuery query;

    query.prepare( "SELECT maxLp FROM player WHERE playerId=:id" );
    query.bindValue( ":id", playerId );
    query.exec();
    if ( query.first() )
        lp = query.value( 0 ).toInt();

    return lp;
}

int Database::getEnergyOfPlayer( int playerId ) const
{
    int       energy = 0;
    QSqlQuery query;

    query.prepare( "SELECT energy FROM player WHERE playerId=:id" );
    query.bindValue( ":id", playerId );
    query.exec();
    if ( query.first() )
        energy = query.value( 0 ).toInt();

    return energy;
}

int Database::getMaxEnergyOfPlayer( int playerId ) const
{
    int       energy = 0;
    QSqlQuery query;

    query.prepare( "SELECT maxEnergy FROM player WHERE playerId=:id" );
    query.bindValue( ":id", playerId );
    query.exec();
    if ( query.first() )
        energy = query.value( 0 ).toInt();

    return energy;
}

int Database::getGoldOfPlayer( int playerId ) const
{
    int       gold = 0;
    QSqlQuery query;

    query.prepare( "SELECT gold FROM player WHERE playerId=:id" );
    query.bindValue( ":id", playerId );
    query.exec();
    if ( query.first() )
        gold = query.value( 0 ).toInt();

    return gold;
}

Database::Database( QObject *parent ) : QObject( parent )
{
    db = QSqlDatabase::addDatabase( "QSQLITE" );
    if ( QFile::exists( file ) )
        db.setDatabaseName( file );
    if ( QFile::exists( fileTest ) )
        db.setDatabaseName( fileTest );
    if ( !db.isValid() )
        qDebug()<<"Datenbanktreiber ist ungültig";
    if ( QFile::exists( file ) ||  QFile::exists( fileTest ) )
        if ( !db.open() )
            qDebug()<<"Datenbank wurde nicht geöffnet";
}

Database::~Database()
{
    if ( db.isOpen() )
        db.close();
}

Database *Database::get()
{
    if ( !database )
        database = new Database;

    return database;
}

bool Database::loadDB( void )
{
    if ( db.isOpen() )
        return true;
    else if ( !QFile::exists( file ) || !db.open() )
        return false;
    else
        return true;
}

void Database::closeDB()
{
    if ( db.isOpen() )
        db.close();
}
