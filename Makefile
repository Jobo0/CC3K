CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
OBJECTS = main.o observer.o display.o level.o tile.o object.o objectCreator.o player.o chamber.o charachter.o textCommands.o gameManager.o enemy.o ./Player/human.o ./Player/dwarf.o ./Player/elf.o ./Player/orc.o item.o gold.o ./Enemy/vampire.o ./Enemy/werewolf.o ./Enemy/troll.o ./Enemy/merchant.o ./Enemy/goblin.o ./Enemy/dragon.o ./Enemy/phoenix.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
