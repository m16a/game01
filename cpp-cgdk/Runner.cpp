#include "Runner.h"

#include <vector>

#include "MyStrategy.h"
#include "Strategy.h"

using namespace model;
using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 4) {
        Runner runner(argv[1], argv[2], argv[3]);
        runner.run();
    } else {
        Runner runner("localhost", "31001", "0000000000000000");
        runner.run();
    }
    
    return 0;
}

Runner::Runner(const char* host, const char* port, const char* token)
: remoteProcessClient(host, atoi(port)), token(token) {
}

void Runner::run() {
    remoteProcessClient.writeToken(token);
    int teamSize = remoteProcessClient.readTeamSize();
    remoteProcessClient.writeProtocolVersion();
    Game game = remoteProcessClient.readGameContext();

    vector<Strategy*> strategies;

    for (int strategyIndex = 0; strategyIndex < teamSize; ++strategyIndex) {
        Strategy* strategy = new MyStrategy;
        strategies.push_back(strategy);
    }

    PlayerContext* playerContext;

    while ((playerContext = remoteProcessClient.readPlayerContext()) != NULL) {
        Trooper playerTrooper = playerContext->getTrooper();

        Move move;
        strategies[playerTrooper.getTeammateIndex()]->move(playerTrooper, playerContext->getWorld(), game, move);
        remoteProcessClient.writeMove(move);

        delete playerContext;
    }

    for (int strategyIndex = 0; strategyIndex < teamSize; ++strategyIndex) {
        delete strategies[strategyIndex];
    }
}
