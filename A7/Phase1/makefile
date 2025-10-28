
futballFantasy.out: main.o ReadWeeksData.o ReadLeagueTeamsData.o Process.o Player.o Match.o LeagueTeams.o LeagueRank.o FantasyTeam.o
	g++ -std=c++11 main.o ReadWeeksData.o ReadLeagueTeamsData.o Process.o Player.o Match.o LeagueTeams.o LeagueRank.o FantasyTeam.o -o futballFantasy.out

ReadWeeksData.o: ReadWeeksData.cpp ReadWeeksData.hpp
	g++ -std=c++11 -c ReadWeeksData.cpp
	
ReadLeagueTeamsData.o: ReadLeagueTeamsData.cpp ReadLeagueTeamsData.hpp
	g++ -std=c++11 -c ReadLeagueTeamsData.cpp

Process.o: Process.cpp Process.hpp
	g++ -std=c++11 -c Process.cpp

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Player.o: Player.cpp Player.hpp
	g++ -std=c++11 -c Player.cpp
	
Match.o: Match.cpp Match.hpp
	g++ -std=c++11 -c Match.cpp

LeagueTeams.o: LeagueTeams.cpp LeagueTeams.hpp
	g++ -std=c++11 -c LeagueTeams.cpp

LeagueRank.o: LeagueRank.cpp LeagueRank.hpp
	g++ -std=c++11 -c LeagueRank.cpp

FantasyTeam.o: FantasyTeam.cpp FantasyTeam.hpp
	g++ -std=c++11 -c FantasyTeam.cpp

clean:
	rm *.o
