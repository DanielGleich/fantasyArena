#include "arena.h"


CardPosition*               CardPosition::selectedCard = nullptr;
QList<CardPosition*>        CardPosition::allCards;
MonsterPosition*            MonsterPosition::selectedMonster = nullptr;
QList<MonsterPosition*>    MonsterPosition::allMonsters;
Arena                      *Arena::arena = nullptr;

/**********************************************************************\
|                                                                      |
|   CardPosition                                                       |
|   - Speicherung der Position und Infos zu Spielerkarten              |
|                                                                      |
\**********************************************************************/

CardPosition::CardPosition( QRectF value, Card *card) {
    originPosition = new QPointF(value.x(),value.y());
    rect = value;
    allCards << this;
    this->card = card;
}

CardPosition::~CardPosition() {
    allCards.removeOne(this);
    if(this == selectedCard) selectedCard = nullptr;
}

void CardPosition::resetPosition() {
    this->setRect(QRectF(originPosition->x(),
                         originPosition->y(),
                         this->getRect().width(),
                         this->getRect().height()));
}

void CardPosition::remove() {
    delete this;
}

/**********************************************************************\
|                                                                      |
|   MonsterPosition                                                    |
|   - Speicherung der Position und infos zu Monstern                   |
|                                                                      |
\**********************************************************************/

void MonsterPosition::remove() {
    delete this;
}

MonsterPosition::MonsterPosition( QRectF value, Monster* monster ) {
    rect = value;
    allMonsters << this;
    this->monster = monster;
}

MonsterPosition::~MonsterPosition() {
    allMonsters.removeOne(this);
    if (this == selectedMonster) selectedMonster = nullptr;
}

/**********************************************************************\
|                                                                      |
|   Arena                                                              |
|   - Spielfeld                                                        |
|                                                                      |
\**********************************************************************/
Arena::Arena( QWidget *parent ) : QWidget( parent ) {
    cardSize = new QSize(CARD_SIZE_WIDTH,CARD_SIZE_HEIGHT);
    clickPosition = new QPoint(0,0);
    pbNextTurn = new QPushButton("Zug beenden",this);


    activeMonsterRects = new QList<MonsterPosition*>();
    handCardRects = new QList<CardPosition*>();
    initPlayerCardsPositions();
    initMonsterPositions();

    setWindowTitle( "Arena" );

    pbNextTurn->setGeometry(590,610,400,80);
    pbNextTurn->setStyleSheet("font-size:32pt; font-family:Comic Sans MS; background-color:transparent; color:white; border:1px solid white;");
    update();
    connect( Game::get(), SIGNAL(dataChanged()), this, SLOT(update()) );
    connect( pbNextTurn, SIGNAL(clicked(bool)), this, SLOT(nextTurn()));
}

Arena::~Arena() {}

void Arena::paintBackground(QPainter& p) {
    p.setBrush(GAME_BACKGROUND_COLOR);
    p.drawRect(0,0,this->width(),this->height());
}

void Arena::paintMonsterCards(QPainter& p) {
    for (int i = 0; i < Game::get()->getActiveMonsters()->length(); i++)     {
        MonsterPosition *monsterPosition = activeMonsterRects->at(i);
        Monster *monster = monsterPosition->getMonster();
        MonsterSkill *attack = monster->getNextSkill();
        QPen pen(QPen(Qt::SolidPattern,2));

        p.setBrush(MONSTER_BACKGROUND_COLOR);
        pen.setColor(QColor( MonsterPosition::getSelectedMonster() == monsterPosition ? MONSTER_SELECTED_BORDER_COLOR : MONSTER_BORDER_COLOR ));
        p.setPen( pen );

        p.drawRect(monsterPosition->getRect());

        pen.setColor(MONSTER_TEXT_COLOR);
        p.setPen( pen );

        QString monsterText = "" + Game::get()->getActiveMonsters()->at(i)->getName();
        monsterText.append("\r\n\r\n");
        monsterText.append("Skill: " + attack->getSkillName());
        monsterText.append("\r\nAtk: "+ QString::number(Database::get()->getAttackOfMonster(monster->getId())/2));
        monsterText.append("\t\tDef: "+ QString::number(monster->getDefense()));
        p.drawText(monsterPosition->getRect(),monsterText,QTextOption(Qt::AlignCenter));

        //hp bar
        QRect hpBackground = QRect(monsterPosition->getRect().x()+15,monsterPosition->getRect().y()+10,120,25);
        QRect hpBar = hpBackground;

        p.setPen(Qt::NoPen);
        p.setBrush(MONSTER_LP_BACKGROUND_COLOR);
        p.drawRect(hpBackground);

        p.setBrush(MONSTER_LP_BAR_COLOR);

        double width = hpBackground.width()* double(monster->getLp())/ double(monster->getMaxLp());
        hpBar.setWidth(int(width));
        p.drawRect(hpBar);

        p.setPen(MONSTER_TEXT_COLOR);
        p.drawText(hpBackground,QString::number(monster->getLp())+"/"+QString::number(monster->getMaxLp()),QTextOption(Qt::AlignCenter));
    }
}

void Arena::paintHandCards(QPainter& p) {
    p.resetTransform();
    QPen pen(QPen(Qt::SolidPattern,2));
    pen.setColor(PLAYER_CARD_FONT_COLOR);
    p.setPen( pen );
    QList<Card*> handCards = Game::get()->getPlayer()->getHandCards();
    for (int i = 0; i < handCards.length(); i++)     {
        CardPosition *cardPosition = handCardRects->at(i);
        Card *card = cardPosition->getCard();
        QPixmap icon;

        switch(card->getRange()) {
        case 0: icon.load(":/pictogram/star"); break;
        case 1: icon.load(":/pictogram/melee"); break;
        default: icon.load(":/pictogram/ranged"); break;
        }

        if(CardPosition::getSelectedCard() != nullptr && CardPosition::getSelectedCard()->getRect() == cardPosition->getRect()) {
            pen.setColor(PLAYER_CARD_BORDER_COLOR);
            cardPosition->setRect(QRectF(
                                      clickPosition->x()-75,
                                      clickPosition->y()-90,
                                      cardPosition->getRect().width(),
                                      cardPosition->getRect().height()));
        }
        p.setPen( pen );
        p.setBrush(QBrush(PLAYER_CARD_BACKGROUND_COLOR));
        p.drawRoundedRect(cardPosition->getRect(),5,5);
        pen.setColor(PLAYER_CARD_FONT_COLOR);
        p.setPen( pen );

        QString cardText = card->getName();
        cardText.append("\r\n\r\nAtk: ");
        cardText.append(QString::number(Database::get()->getAttackValueOfCard(card->getId())));
        cardText.append("\t\tDef: ");
        cardText.append(QString::number(Database::get()->getDefenseValueOfCard(card->getId())));
        cardText.append("\r\n\r\n");


        int energyCost = card->getEnergyCost();
        if (energyCost < 0) {
            energyCost *= -1;
            cardText.append("+");
        } else if (energyCost > 0)
            cardText.append("-");

        cardText.append(QString::number(energyCost));
        cardText.append(" Energie");

        p.drawText(
                    handCardRects->at(i)->getRect(),
                    cardText,QTextOption(Qt::AlignCenter));
        p.drawPixmap(handCardRects->at(i)->getRect().x()+5, handCardRects->at(i)->getRect().y()+5,32,32,icon);
    }
}

void Arena::paintPlayerInfo(QPainter& p) {
    Player* player = Game::get()->getPlayer();
    QRect hpBackground = QRect(10,50,430,40);

    QString playerString = "Spielerinfo";
    QString defenseString = "Verteidigung: " + QString::number(player->getDefense());
    QString energyString = QString::number(player->getEnergy()) + "/" + QString::number(player->getMaxEnergy())+ " Energie";
    QString text = "\r\n";
    text.append(defenseString+"\r\n");
    text.append(energyString);

    //Rahmen
    p.setBrush(playerSelected ? PLAYER_INFO_SELECTED_COLOR : Qt::NoBrush);
    p.drawRect(PLAYER_INFO_POSITION);


    //Stats
    p.setFont(QFont("Comic Sans MS",12));
    p.drawText(PLAYER_INFO_POSITION,text,QTextOption(Qt::AlignCenter));

    p.translate(PLAYER_INFO_POSITION.topLeft());

    //Überschrift
    p.setFont(QFont("Comic Sans MS",24));
    p.drawText(QRect(10,5,200,250),playerString);

    //hp bar
    p.setPen(QPen(Qt::black));
    p.setBrush(QBrush(Qt::red));
    p.drawRect(hpBackground);

    p.setPen(Qt::NoPen);
    p.setBrush(Qt::green);

    QRect hpBar = hpBackground;
    double width = hpBackground.width()* double(player->getLp())/ double(player->getMaxLp());
    hpBar.setWidth(int(width));
    p.drawRect(hpBar);

    p.setPen(Qt::white);
    p.drawText(hpBackground,QString::number(player->getLp())+"/"+QString::number(player->getMaxLp()),QTextOption(Qt::AlignCenter));
    p.setFont(QFont( "MS Shell Dlg 2,8.25,-1,5,50,0,0,0,0,0" ));
}

void Arena::initPlayerCardsPositions() {
    QList<Card*> handCards = Game::get()->getPlayer()->getHandCards();
    for(int i = 0; i < handCards.count(); i++) {
        handCardRects->append(new CardPosition(QRectF(CARD_POS_X+(cardSize->width()+CARD_SPACE)*i,
                                                      CARD_POS_Y,
                                                      cardSize->width(),
                                                      cardSize->height()),
                                               handCards[i]));
    }
}

void Arena::initMonsterPositions() {
    QList<Monster*> *monsters = Game::get()->getActiveMonsters();
    for( int i = 0; i < monsters->count(); i++)
        activeMonsterRects->append(new MonsterPosition(QRectF(220+(cardSize->width()+50)*i,100,cardSize->width(),cardSize->height()),monsters->at(i)));
}

Arena *Arena::get() {
    if ( !arena ) arena = new Arena;
    return arena;
}

void Arena::refresh() {
    syncHandCardRects();
    syncMonsterRects();
}

// Festlegung der Positionen der Handkarten in der Benutzeroberfläche
void Arena::syncHandCardRects() {
    QList<Card*> handCards = Game::get()->getPlayer()->getHandCards();

    QList<CardPosition*> removeHandCards;
    for (int i = 0; i < handCardRects->length(); i++) {
        if (!handCards.contains(handCardRects->at(i)->getCard())) {
            removeHandCards.append(handCardRects->at(i));
            handCardRects->at(i)->remove();
        }
    }

    foreach(CardPosition* cp, removeHandCards)
        handCardRects->removeOne(cp);

    if (handCards.count() > handCardRects->count()) {
        QList<Card*> missingCards;
        missingCards.append(handCards);

        for(int i = 0; i < handCardRects->count(); i++)
            if(handCards.contains(handCardRects->at(i)->getCard()))
                missingCards.removeOne(handCardRects->at(i)->getCard());
        foreach( Card* c, missingCards)
            handCardRects->append(new CardPosition(QRectF(0,0,0,0), c));
    }

    for (int i = 0; i < handCardRects->length(); i++) {
        handCardRects->at(i)->setRect(QRectF(CARD_POS_X+(cardSize->width()+CARD_SPACE)*i,
                                             CARD_POS_Y,
                                             cardSize->width(),
                                             cardSize->height()));
    }
}

// Festlegung der Positionen der Monsterkarten in der Benutzeroberfläche
void Arena::syncMonsterRects() {
    QList<Monster*> *activeMonsters = Game::get()->getActiveMonsters();
    QList<MonsterPosition*> removeMonster;
    for(int i = 0; i < activeMonsterRects->length(); i++) {
        if(!activeMonsters->contains(activeMonsterRects->at(i)->getMonster())) {
            activeMonsterRects->at(i)->remove();
            removeMonster.append(activeMonsterRects->at(i));
        }
    }
    foreach(MonsterPosition *mp, removeMonster)
        activeMonsterRects->removeOne(mp);

    for(int i = 0; i < activeMonsterRects->length(); i++) {
        activeMonsterRects->at(i)->setRect(QRectF(220+(cardSize->width()+50)*i,100,cardSize->width(),cardSize->height()));
    }
    if (activeMonsters->count() > activeMonsterRects->count()) {
        QList<Monster*> missingRects;
        for(int i = 0; i < activeMonsterRects->count(); i++)
            missingRects.append(activeMonsterRects->at(i)->getMonster());

        for(int i = 0; i < activeMonsterRects->count(); i++)
            if(missingRects.contains(activeMonsterRects->at(i)->getMonster()))
                missingRects.removeOne(activeMonsterRects->at(i)->getMonster());
        foreach( Monster* m, missingRects)
            activeMonsterRects->append(new MonsterPosition(QRectF(0,0,0,0), m));
    }
}

void Arena::paintEvent( QPaintEvent * /*event*/ ) {
    QPainter painter( this );
    paintBackground(painter);
    paintMonsterCards(painter);
    paintPlayerInfo(painter);
    paintHandCards(painter);
}

void Arena::mousePressEvent( QMouseEvent *event ) {
    QPointF p( event->x(), event->y() );

    for(int i = 0; i<handCardRects->length(); i++)
        if ( handCardRects->at(i)->getRect().contains(p))
            CardPosition::setSelected(handCardRects->at(i));
    dragActive = true;
    clickPosition->setX(event->x());
    clickPosition->setY(event->y());
    update();
}

void Arena::mouseReleaseEvent( QMouseEvent * ) {
    dragActive = false;
    if (CardPosition::getSelectedCard() != nullptr && MonsterPosition::getSelectedMonster() != nullptr && !CardPosition::getSelectedCard()->getCard()->isSpecial()) {
        Game::get()->playCardAgainstSomeone(CardPosition::getSelectedCard()->getCard(),MonsterPosition::getSelectedMonster()->getMonster());
    }

    if(CardPosition::getSelectedCard() != nullptr && playerSelected && CardPosition::getSelectedCard()->getCard()->isSpecial()) {
        Game::get()->playCardOnPlayer(CardPosition::getSelectedCard()->getCard());
        playerSelected = false;
    }

    if(CardPosition::getSelectedCard() != nullptr)
        CardPosition::getSelectedCard()->resetPosition();
    if(MonsterPosition::getSelectedMonster() != nullptr)
        MonsterPosition::setSelected(nullptr);
    CardPosition::setSelected(nullptr);

    refresh();
    update();
}

void Arena::mouseMoveEvent( QMouseEvent *event ) {
    CardPosition *cardPos = CardPosition::getSelectedCard();
    if (!dragActive || cardPos == nullptr)
        return;
    clickPosition->setX(event->x());
    clickPosition->setY(event->y());


    bool isMonsterSelected = false;
    for(int i = 0; i<activeMonsterRects->length(); i++) {
        if(cardPos->getRect().intersects(activeMonsterRects->at(i)->getRect()) && !cardPos->getCard()->isSpecial()) {
            activeMonsterRects->at(i)->setSelected();
            isMonsterSelected = true;
        }
    }
    if (!isMonsterSelected )
        MonsterPosition::setSelected(nullptr);

    playerSelected = PLAYER_INFO_POSITION.contains(event->pos()) && cardPos->getCard()->isSpecial();
    update();
}

void Arena::closeEvent( QCloseEvent * /*event*/ ) {
    emit tryToClose();
}

void Arena::nextTurn() {
    Game::get()->nextTurn();
    refresh();
    update();
}
