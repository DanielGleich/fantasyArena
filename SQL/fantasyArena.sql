-- SQLite Code
CREATE TABLE "skill" (
	"skillId"				INTEGER NOT NULL,
	"skillName"				TEXT NOT NULL,
	PRIMARY KEY ( "skillId" )
);

CREATE TABLE "monster" (
	"monsterId"				INTEGER NOT NULL,		-- id
	"monsterName"			TEXT 	NOT NULL,		-- Name des Monsters
	"monsterLP"				INTEGER NOT NULL,		-- Lebenspunkte
	"monsterAttack"			INTEGER NOT NULL,		-- Angriffswert
	"monsterAttackChance"	INTEGER NOT NULL,		-- % Chance in einer Runde anzugreifen
	"monsterDefense"		INTEGER NOT NULL,		-- Verteidigungswert des Monsters
	"monsterDefenseChance"	INTEGER NOT NULL,		-- % Chance in einer Runde Schilde zu generieren
	"monsterLevel"			INTEGER NOT NULL,		-- Wie anspruchsvoll ist dieser Gegner
	PRIMARY KEY ( "monsterId" )
);

CREATE TABLE "zuoMonsterSkill" (
	"monsterId"				INTEGER NOT NULL,		-- id des Monsters
	"skillId"				INTEGER NOT NULL,		-- Fertigkeit des Monsters
	"skillValue"			INTEGER NOT NULL,		-- Fertigkeitswert
	"skillChance"			INTEGER NOT NULL,		-- % Chance, die Fertigkeit auszulösen
	FOREIGN KEY  ( "monsterId" ) 	REFERENCES "monster"( "monsterId" ),
	FOREIGN KEY  ( "skillId" ) 		REFERENCES "skill"( "skillId" ),
	PRIMARY KEY ( "monsterId", "skillId" ) 
);

CREATE TABLE "card" (
	"cardId"				INTEGER NOT NULL,		-- id
	"cardName"				INTEGER NOT NULL,		-- Name der Karte
	"attackValue"			INTEGER NOT NULL,		-- Angriffswert
	"defenseValue"			INTEGER NOT NULL,		-- Verteidigungswert
	"energyCost"			INTEGER NOT NULL,		-- Energiekosten
	"skillId"				INTEGER NOT NULL,		-- Fertigkeit
	"skillValue"			INTEGER NOT NULL,		-- Fertigkeitswert
	"range"					INTEGER NOT NULL,		-- Reichweite des Angriffs
	"upgradedTo"			INTEGER NOT NULL,		-- wird aufgewertet zu Karte mit dieser id
	FOREIGN KEY ( "skillId" )		REFERENCES "skill"( "skillId" ),
	PRIMARY KEY ( "cardId" ) 
);

CREATE TABLE "player" (
	"playerId"				INTEGER NOT NULL, 		-- id
	"lp"					INTEGER NOT NULL,		-- aktuelle LP
	"maxLp"					INTEGER NOT NULL,		-- maximale LP
	"energy"				INTEGER NOT NULL,		-- aktuelle Energie
	"maxEnergy"				INTEGER NOT NULL,		-- maxmal mögliche Energie
	"gold"					INTEGER	NOT NULL, 		-- Gold
	"defense"				INTEGER NOT NULL,		-- aktuelle Verteidigung
	PRIMARY KEY ( "playerId" )
);

CREATE TABLE "zuoPlayerCard" (
	"playerId"				INTEGER NOT NULL, 		-- Spieler-id
	"cardId"				INTEGER NOT NULL,		-- Karte des Spielers	
	"numberOfCards"			INTEGER NOT NULL, 		-- Wie oft hat der Spieler diese Karte im Besitz?
	FOREIGN KEY  ( "playerId" ) 	REFERENCES "player"( "playerId" ),
	FOREIGN KEY  ( "cardId" ) 		REFERENCES "card"( "cardId" ),
	PRIMARY KEY ( "playerId", "cardId" ) 
);

CREATE TABLE "game" (
	"gameId"				INTEGER NOT NULL,		-- id
	"name"					TEXT NOT NULL,			-- Name des Spiels (Speichername)		
	"playerId"				INTEGER NOT NULL,		-- Spieler des Spiels	
	FOREIGN KEY  ( "playerId" ) 	REFERENCES "player"( "playerId" ),
	PRIMARY KEY ( "gameId" ) 
);

													-- ID		Hinweise
INSERT INTO skill VALUES ( 1, 'noSkill' );			--  0		kein Skill (nötig für QRelationalTableModel)							
INSERT INTO skill VALUES ( 2, 'lifedrain' );		--  1		gewinnt x LP beim Angriff zurück
INSERT INTO skill VALUES ( 3, 'stun' );				--  2		Ziel muss mit x% Wahrscheinlichkeit aussetzen
INSERT INTO skill VALUES ( 4, 'weaken' );			--  3		Ziel macht für x Runden -25% Schaden 
INSERT INTO skill VALUES ( 5, 'blind' );			--  4		Ziel trifft für x Runden nur mit 50% Wahrscheinlichkeit
INSERT INTO skill VALUES ( 6, 'decay' );			--  5		Ziel verliert bis zu x Rüstung
INSERT INTO skill VALUES ( 7, 'poison' );			--  6		Ziel erhält x Vergiftungen; jede Vergiftung raubt pro Runde 1 LP
INSERT INTO skill VALUES ( 8, 'thorns' );			--  7		Angriffe gegen diese Figur verursachen beim Angreifer x Schaden
INSERT INTO skill VALUES ( 9, 'selfheal' );			--  8		Selbstheilung
INSERT INTO skill VALUES ( 10, 'healall' );			--  9		Heilung aller Verbündeten
INSERT INTO skill VALUES ( 11, 'revive' );			-- 10		Wert gibt % Wahrscheinlichkeit an, mit der Figur automatisch wiederbelebt wird
INSERT INTO skill VALUES ( 12, 'defendall' );		-- 11		x Schilde für alle Verbündeten

-- 								  Name			LP, 	Att,	AttCh,  Def, 	DefCh,	Lvl
INSERT INTO monster VALUES ( 1, 'Goblin', 		20, 	8,  	40,		10,   	30, 	1 );
INSERT INTO monster VALUES ( 2, 'Ork',			40, 	12, 	60,   	15,   	20, 	5 );
INSERT INTO monster VALUES ( 3, 'Troll', 		80, 	20,  	60,  	0,   	0,   	10 );
INSERT INTO monster VALUES ( 4, 'Skelett',		30, 	10,  	70,   	12,   	30,  	3 );
INSERT INTO monster VALUES ( 5, 'Schamane',		30, 	10,  	30,   	12,   	20,  	3 );

--									 monsterID	 skillID	Value	Chance
INSERT INTO zuoMonsterSkill VALUES ( 	1, 			12,  	8,		30 );	-- Goblin: 	defendall
INSERT INTO zuoMonsterSkill VALUES ( 	2, 			4,  	2,		20 );	-- Ork: 	weaken 
INSERT INTO zuoMonsterSkill VALUES ( 	3, 			9,  	20,		30 );	-- Troll:	selfheal
INSERT INTO zuoMonsterSkill VALUES ( 	3, 			3,  	1,		10 );	-- Troll:	stun
INSERT INTO zuoMonsterSkill VALUES ( 	4, 			11,  	30,		25 );	-- Skelett:	revive
INSERT INTO zuoMonsterSkill VALUES ( 	5, 			9,  	20,		25 );	-- Schamane: selfheal
INSERT INTO zuoMonsterSkill VALUES ( 	5, 			10,  	10,		25 );	-- Schamane: healall

--									Name				Att		Def 	Energy	skill 	value 	range	upgradeTo
INSERT INTO card VALUES ( 1, 	"Schuss I",				6,		0,		1,		1, 		0,		9,		13 );
INSERT INTO card VALUES ( 2, 	"Giftpfeil I",			4,		0,		1, 		7, 		2,		9,		14 );
INSERT INTO card VALUES ( 3, 	"Präzisionsschuss I",	8,		0,		1,		1, 		0,		9,		15 );
INSERT INTO card VALUES ( 4, 	"Doppelschuss I",		12,		0, 		2,		1, 		0,		9,		16 );
INSERT INTO card VALUES ( 5, 	"Sperrfeuer I",			20,		0,		3,		1, 		0,		9,		17 );
INSERT INTO card VALUES ( 6, 	"Rauchbombe I",			6,		0,		1,		5, 		1,		9,		18 );
INSERT INTO card VALUES ( 7, 	"Beinschuss I",			5,		0,		1,		4, 		2,		9,		19 );
INSERT INTO card VALUES ( 8, 	"Schildmauer I",		0,		18,		3,		1, 		0,		0,		20 );
INSERT INTO card VALUES ( 9, 	"Banane I",				0,		0,		1,		9, 		5,		9,		21 );
INSERT INTO card VALUES ( 10, 	"Schlag I",				6,		0,		0,		1, 		0,		1,		22 );
INSERT INTO card VALUES ( 11, 	"Schild I",				0,		6,		1,		1, 		0,		0,		23 );
INSERT INTO card VALUES ( 12, 	"Kugel I",				0,		0,		-1,		1, 		0,		0,		24 );
INSERT INTO card VALUES ( 13, 	"Schuss II",			9,		0,		1,		1, 		0,		9,		13 );
INSERT INTO card VALUES ( 14, 	"Giftpfeil II",			6,		0,		1, 		7, 		3,		9,		14 );
INSERT INTO card VALUES ( 15, 	"Präzisionsschuss II",	12,		0,		1,		1, 		0,		9,		15 );
INSERT INTO card VALUES ( 16, 	"Doppelschuss II",		24,		0, 		2,		1, 		0,		9,		16 );
INSERT INTO card VALUES ( 17, 	"Sperrfeuer II",		20,		0,		3,		4, 		2,		9,		17 );
INSERT INTO card VALUES ( 18, 	"Rauchbombe II",		9,		0,		1,		5, 		2,		9,		18 );
INSERT INTO card VALUES ( 19, 	"Beinschuss II",		8,		0,		1,		4, 		3,		9,		19 );
INSERT INTO card VALUES ( 20, 	"Schildmauer II",		0,		24,		3,		1, 		0,		0,		20 );
INSERT INTO card VALUES ( 21, 	"Banane II",			0,		0,		0,		9, 		5,		9,		21 );
INSERT INTO card VALUES ( 22, 	"Schlag II",			9,		0,		0,		1, 		0,		1,		22 );
INSERT INTO card VALUES ( 23, 	"Schild II",			0,		9,		1,		1, 		0,		0,		23 );
INSERT INTO card VALUES ( 24, 	"Kugel II",				0,		0,		-2,		1, 		0,		0,		24 );

-- Startwerte
INSERT INTO player VALUES ( 1, 50, 50, 2, 2, 0, 0 );		
INSERT INTO zuoPlayerCard VALUES ( 	1, 	1, 	3 );		-- 3 mal "Schuss"
INSERT INTO zuoPlayerCard VALUES ( 	1, 	3, 	1 );		-- 1 mal "Präzisionsschuss"
INSERT INTO zuoPlayerCard VALUES ( 	1, 	10,	2 );		-- 2 mal "Schlag"
INSERT INTO zuoPlayerCard VALUES ( 	1, 	11,	2 );		-- 2 mal "Schild"
INSERT INTO zuoPlayerCard VALUES ( 	1, 	12,	2 );		-- 2 mal "Kugel"
INSERT INTO game VALUES ( 1, "Spiel 1", 1 );
