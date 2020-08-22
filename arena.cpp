#include "arena.h"


CardPosition*               CardPosition::selectedCard = nullptr;
QList<CardPosition*>        CardPosition::allCards;
MonsterPosition*            MonsterPosition::selectedMonster = nullptr;
QList<MonsterPosition*>     MonsterPosition::allMonsters;
Arena                      *Arena::arena = nullptr;

/**********************************************************************\
|                                                                      |
|   CardPosition                                                       |
|   - Speicherung der Position und Infos zu Spielerkarten              |
|                                                                      |
\**********************************************************************/

CardPosition::CardPosition( QRectF value )
{
  originPosition = new QPointF(value.x(),value.y());
  rect = value;
  allCards << this;
}

CardPosition::~CardPosition()
{
  allCards.removeOne(this);
  if(this == selectedCard) selectedCard = nullptr;
}

void CardPosition::resetPosition()
{
  this->setRect(QRectF(originPosition->x(),
                       originPosition->y(),
                       this->getRect().width(),
                       this->getRect().height()));
}

/**********************************************************************\
|                                                                      |
|   MonsterPosition                                                    |
|   - Speicherung der Position und infos zu Monstern                   |
|                                                                      |
\**********************************************************************/

MonsterPosition::MonsterPosition( QRectF value )
{
  rect = value;
  allMonsters << this;
}

MonsterPosition::~MonsterPosition()
{
  allMonsters.removeOne(this);
  if (this == selectedMonster) selectedMonster == nullptr;
}

/**********************************************************************\
|                                                                      |
|   Arena                                                              |
|   - Spielfeld                                                        |
|                                                                      |
\**********************************************************************/
Arena::Arena( QWidget *parent ) : QWidget( parent )
{
  setWindowTitle( "Arena" );
  cardSize = new QSize(150,180);

  clickPosition = new QPoint(0,0);

  pbNextTurn = new QPushButton("Zug beenden",this);
  pbNextTurn->setGeometry(540,490,450,200);
  pbNextTurn->setStyleSheet("font-size:50pt;");
  update();

  connect( Game::get(), SIGNAL(dataChanged()), this, SLOT(update()) );
  connect( pbNextTurn, SIGNAL(clicked(bool)), this, SLOT(nextTurn()));
}

void Arena::paintHandCards(QPainter& p)
{
  syncHandCardRects();
  QPen pen(QPen(Qt::SolidPattern,2));
  pen.setColor(QColor(Qt::white));
  p.setPen( pen );
  for (int i = 0; i < Game::get()->getPlayer()->getHandCards().length(); i++)
  {
    CardPosition *cardPosition = handCardRects[i];
    Card *card = cardPosition->getCard();
    QPixmap icon;

    switch(card->getRange())
    {
      case 0: icon.load(":/pictogram/star.png"); break;
      case 1: icon.load(":/pictogram/melee.png"); break;
      default: icon.load(":/pictogram/ranged.png"); break;
    }

    if(CardPosition::getSelectedCard() != nullptr
       && CardPosition::getSelectedCard()->getRect() == cardPosition->getRect())
    {
      pen.setColor(QColor(51,167,206));
      cardPosition->setRect(QRectF(
                              clickPosition->x()-75,
                              clickPosition->y()-90,
                              cardPosition->getRect().width(),
                              cardPosition->getRect().height()));
    }
    p.setPen( pen );
    p.setBrush(QBrush(QColor(151,156,152)));
    p.drawRoundedRect(cardPosition->getRect(),5,5);
    pen.setColor(QColor(Qt::white));
    p.setPen( pen );

    QString cardText = card->getName();
    cardText.append("\r\n\r\nAtk: ");
    cardText.append(QString::number(Database::get()->getAttackValueOfCard(card->getId())));
    cardText.append("\t\tDef: ");
    cardText.append(QString::number(Database::get()->getDefenseValueOfCard(card->getId())));
    cardText.append("\r\n\r\n");


    int energyCost = card->getEnergyCost();
    if (energyCost < 0)
    {
      energyCost *= -1;
      cardText.append("+");
    }
    else if (energyCost > 0)
      cardText.append("-");

    cardText.append(QString::number(energyCost));
    cardText.append(" Energie");

    p.drawText(
          handCardRects[i]->getRect(),
          cardText,QTextOption(Qt::AlignCenter));
    p.drawPixmap(handCardRects[i]->getRect().x()+5, handCardRects[i]->getRect().y()+5,32,32,icon);
  }
}

void Arena::paintMonsterCards(QPainter& p)
{
  syncMonsterRects();
  for (int i = 0; i < Game::get()->getActiveMonster().length(); i++)
  {
    MonsterPosition *monsterPosition = activeMonsterRects[i];
    Monster *monster = monsterPosition->getMonster();
    MonsterSkill *attack = monster->getNextSkill();

    p.setBrush(QColor(173,27,76));
    QPen pen(QPen(Qt::SolidPattern,2));

    pen.setColor(QColor( MonsterPosition::getSelectedMonster() == monsterPosition ? Qt::red : Qt::white ));

    p.setPen( pen );

    p.drawRect(monsterPosition->getRect());

    pen.setColor(QColor(Qt::white));
    p.setPen( pen );

    QString monsterText = "" + Game::get()->getActiveMonster()[i]->getName();
    monsterText.append("\r\n\r\n");
    monsterText.append(attack->getSkillName());
    monsterText.append("\r\nAtk: "+ QString::number(Database::get()->getAttackOfMonster(monster->getId())));
    monsterText.append("\t\tDef: "+ QString::number(monster->getDefense()));

    p.drawText(monsterPosition->getRect(),monsterText,QTextOption(Qt::AlignCenter));

    monsterPosition->getMonster()->setStunned(1);
    monsterPosition->getMonster()->setWeaken(1);

    if(monsterPosition->getMonster()->getStunned() >= 1)
    {
      p.drawText(monsterPosition->getRect().bottomLeft(),QString("Gestunnt"));
    }

    if(monsterPosition->getMonster()->getWeaken() >= 1)
    {
      //p.drawText();
    }


    //hp bar
    QRect hpBackground = QRect(monsterPosition->getRect().x()+15,monsterPosition->getRect().y()+10,120,25);
    QRect hpBar = hpBackground;

    p.setPen(QPen(Qt::black));
    p.setBrush(QBrush(Qt::red));
    p.drawRect(hpBackground);

    p.setPen(Qt::NoPen);
    p.setBrush(Qt::green);

    double width = hpBackground.width()* double(monster->getLp())/ double(monster->getMaxLp());
    hpBar.setWidth(int(width));
    p.drawRect(hpBar);

    p.setPen(Qt::white);
    p.drawText(hpBackground,QString::number(monster->getLp())+"/"+QString::number(monster->getMaxLp()),QTextOption(Qt::AlignCenter));
  }
}

void Arena::paintBackground(QPainter& p)
{
  //QPixmap background(":/pictogram/arena.jpg");
  //p.drawPixmap(0,0,this->width(),this->height(),background);
  p.setBrush(QBrush(Qt::gray));
  p.drawRect(0,0, this->width(),this->height());
}

void Arena::paintPlayerInfo(QPainter& p)
{
  Player* player = Game::get()->getPlayer();

  QRect playerDisplay = QRect(10,490,450,200);
  QRect hpBackground = QRect(10,50,430,40);

  QString playerString = "Spielerinfo";
  QString defenseString = "Verteidigung: " + QString::number(player->getDefense());
  QString energyString = QString::number(player->getEnergy()) + "/" + QString::number(player->getMaxEnergy())+ " Energie";
  QString text = "\r\n";
  text.append(defenseString);
  text.append("\r\n");
  text.append(energyString);

  //Rahmen
  p.setBrush(Qt::NoBrush);
  p.drawRect(playerDisplay);


  //Stats
  p.setFont(QFont("Comic Sans MS",12));
  p.drawText(playerDisplay,text,QTextOption(Qt::AlignCenter));

  p.translate(playerDisplay.topLeft());

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
}
Arena::~Arena()
{}

Arena *Arena::get()
{
  if ( !arena )
    arena = new Arena;

  return arena;
}

void Arena::refresh()
{
  syncHandCardRects();
  syncMonsterRects();
}

void Arena::syncHandCardRects()
{
  if(handCardRects.isEmpty())
  {
    for (int i = 0; i < Game::get()->getPlayer()->getHandCards().length(); i++)
    {
      CardPosition* cardPosition = new CardPosition(QRectF(20+(cardSize->width()+50)*i,300,cardSize->width(),cardSize->height()));
      cardPosition->setCard(Game::get()->getPlayer()->getHandCards()[i]);
      handCardRects << cardPosition;
    }
  }

}

void Arena::syncMonsterRects()
{
  if(activeMonsterRects.isEmpty())
  {
    for(int i = 0; i < Game::get()->getActiveMonster().length(); i++)
    {
      MonsterPosition *temp = new MonsterPosition(QRectF(220+(cardSize->width()+50)*i,100,cardSize->width(),cardSize->height()));
      temp->setMonster(Game::get()->getActiveMonster()[i]);
      activeMonsterRects << temp;
    }
  }
  else {
    for(int i = 0; i < activeMonsterRects.length(); i++)
    {
      if(activeMonsterRects[i]->getMonster()->getLp() == 0)
        activeMonsterRects[i]->setMonster(nullptr);
    }
  }
}

void Arena::paintEvent( QPaintEvent * /*event*/ )
{
  QPainter painter( this );
  painter.setBrush(Qt::darkGray);
  paintBackground(painter);
  paintMonsterCards(painter);
  paintHandCards(painter);
  paintPlayerInfo(painter);
}

void Arena::mousePressEvent( QMouseEvent *event )
{
  QPointF p( event->x(), event->y() );

  for(int i = 0; i<handCardRects.length(); i++)
    if ( handCardRects[i]->getRect().contains(p))
      handCardRects[i]->setSelected();
  dragActive = true;
  clickPosition->setX(event->x());
  clickPosition->setY(event->y());
  update();
}

void Arena::mouseReleaseEvent( QMouseEvent *event )
{
  dragActive = false;
  if (CardPosition::getSelectedCard() != nullptr && MonsterPosition::getSelectedMonster() != nullptr)
  {
    Game::get()->playCardAgainstSomeone(CardPosition::getSelectedCard()->getCard(),MonsterPosition::getSelectedMonster()->getMonster());
    qDebug() << CardPosition::getSelectedCard()->getCard()->getName() << MonsterPosition::getSelectedMonster()->getMonster()->getName();
  }

  if(CardPosition::getSelectedCard() != nullptr)
    CardPosition::getSelectedCard()->resetPosition();
  if(MonsterPosition::getSelectedMonster() != nullptr)
    MonsterPosition::setSelected(nullptr);



  CardPosition::setSelected(nullptr);
  update();
}

void Arena::mouseMoveEvent( QMouseEvent *event )
{
  if (dragActive)
  {
    clickPosition->setX(event->x());
    clickPosition->setY(event->y());
    for(int i = 0; i<activeMonsterRects.length(); i++)
      if(CardPosition::getSelectedCard() != nullptr && activeMonsterRects[i]->getRect().contains(CardPosition::getSelectedCard()->getRect().center()))
        activeMonsterRects[i]->setSelected();
    update();
  }

}

void Arena::resizeEvent( QResizeEvent * )// event )
{

}

void Arena::closeEvent( QCloseEvent * /*event*/ )
{
  emit tryToClose();
}

void Arena::nextTurn()
{
  Game::get()->nextArenaRound();
  update();
}

