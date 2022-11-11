#ifndef CONFIG_H
#define CONFIG_H

#include <QColor>
#include <QtCore>

const bool DEBUG                            = true;

const QString file                          = "../../../fantasyArena.db";
const QString fileTest                      = "fantasyArena.db";

const int PLAYERID                          = 1;
const int HANDSIZE                          = 5;

const int ARENA_WIDTH                        = 1000;
const int ARENA_HEIGHT                       = 700;
const int ARENA_MONSTER_COUNT                 = 3;
const QColor GAME_BACKGROUND_COLOR          = QColor(  57,  41,  53 );

const int CARD_SPACE                        = 20;
const int CARD_SIZE_HEIGHT                  = 180;
const int CARD_SIZE_WIDTH                   = 150;
const int CARD_POS_Y                        = 300;
const int CARD_POS_X                        = 80;
const QColor CARD_NAME_COLOR                = QColor(  65,  43,  12 );
const int ICON_SIZE                         = 20;

const int MONSTER_SPACE                     = 14;
const int MONSTER_HEIGHT                    = 184;
const int MONSTER_WIDTH                     = 240;
const int MONSTER_SIDE_PADDING              = ( ARENA_WIDTH-3*MONSTER_WIDTH-2*MONSTER_SPACE )/2;// 126;
const int MONSTER_LP_HEIGHT                 = MONSTER_HEIGHT-50;

const QColor MONSTER_LP_BACKGROUND_COLOR    = QColor( 194,   6,   0 );
const QColor MONSTER_LP_BAR_COLOR           = QColor(   7, 110,  40 );
const QColor MONSTER_BACKGROUND_COLOR       = QColor( 241, 126,  82 );
const QColor MONSTER_BORDER_COLOR           = QColor( 255, 255, 255 );
const QColor MONSTER_SELECTED_BORDER_COLOR  = QColor( 143,  23,  37 );
const QColor MONSTER_TEXT_COLOR             = QColor( 255, 255, 255 );
const QRectF MONSTER_SKILLNAME              = QRectF( 0, 50, 240, 20 );

const QRectF END_TURN_BUTTON                = QRectF( 800, 600, 120, 50 );
const QRectF PLAYER                         = QRectF( 150, 500, 800, 160 );
const QRect  PLAYER_LP                      = QRect( 150, 500, 300, 60 );
const QRect  PLAYER_ENERGY                  = QRect( 150, 600, 300, 60 );
const QRect  PLAYER_DEFENSE                 = QRect( 650, 500, 300, 60 );
const int    PLAYER_LP_FONT                 = 45;
const int    PLAYER_ENERGY_FONT             = 45;
const int    PLAYER_DEFENSE_FONT            = 45;
const QColor PLAYER_CARD_BACKGROUND_COLOR   = QColor(109,115,176);
const QColor PLAYER_CARD_BORDER_COLOR       = QColor(117,137,184);
const QColor PLAYER_CARD_FONT_COLOR         = QColor(169,198,236);
const QColor PLAYER_INFO_SELECTED_COLOR     = QColor(113,66,76);
const QRect  PLAYER_INFO_POSITION           = QRect(10,490,450,200);

const int    END_TURN_BUTTON_FONT           = 16;


const int   ENERGY_BULLET_DIAMETER          = 10;
const int   ENERGY_BULLET_SPACING           = 5;

inline int  min( int a, int b )               { return a<b ? a : b; }
inline int  max( int a, int b )               { return a>b ? a : b; }
inline void sort( int &a, int &b )            { int temp = a; a = min( temp, b ); b = max( temp, b ); }
inline int  random( int min, int max )        { sort( min, max ); return qrand()%( max-min+1 )+min; }
inline int  lpLoss( int attack, int defense ) { return attack>defense ? attack-defense : 0; }

#endif // CONFIG_H
