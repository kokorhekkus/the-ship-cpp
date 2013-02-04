all: theship

theship: main.o engine.o random.o player.o screens.o monster.o object.o map.o \
		 base.o log.o level.o message.o
		g++ -g -lncurses -o theship main.o engine.o random.o player.o screens.o \
		monster.o object.o map.o base.o log.o level.o message.o

main.o: main.cpp engine.h object.h map.h base.h player.h screens.h monster.h \
		log.h level.h message.h
		g++ -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c main.cpp

engine.o: engine.cpp engine.h enums.h log.h
		g++ -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c engine.cpp

random.o: random.cpp random.h log.h
		g++ -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c random.cpp

player.o: player.cpp player.h object.h log.h enums.h map.h base.h engine.h random.h
		g++ -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c player.cpp

screens.o: screens.cpp screens.h player.h engine.h enums.h
		g++ -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c screens.cpp

monster.o: monster.cpp monster.h log.h base.h enums.h
		g++ -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c monster.cpp

object.o: object.cpp object.h log.h base.h enums.h
		g++ -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c object.cpp

map.o: map.cpp map.h enums.h config.h engine.h base.h log.h
		g++ -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c map.cpp

base.o: base.cpp base.h enums.h map.h engine.h
		g++ -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c base.cpp

log.o:  log.cpp log.h config.h
		g++ -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c log.cpp

level.o: level.cpp level.h map.h object.h
		g++ -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c level.cpp

message.o: message.cpp message.h engine.h
		g++ -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c message.cpp

clean:
		rm -f theship main.o engine.o random.o player.o screens.o monster.o \
		object.o map.o base.o log.o level.o message.o core TheShip.log *~ *tdd
