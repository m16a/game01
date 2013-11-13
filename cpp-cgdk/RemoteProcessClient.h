#pragma once

#ifndef _REMOTE_PROCESS_CLIENT_H_
#define _REMOTE_PROCESS_CLIENT_H_

#include <string>
#include <vector>

#include "csimplesocket/ActiveSocket.h"
#include "model/Bonus.h"
#include "model/Game.h"
#include "model/Move.h"
#include "model/Player.h"
#include "model/PlayerContext.h"
#include "model/Trooper.h"
#include "model/World.h"

enum MessageType {
    UNKNOWN_MESSAGE,
    GAME_OVER,
    AUTHENTICATION_TOKEN,
    TEAM_SIZE,
    PROTOCOL_VERSION,
    GAME_CONTEXT,
    PLAYER_CONTEXT,
    MOVE_MESSAGE
};

class RemoteProcessClient {
private:
    CActiveSocket socket;
    std::vector<std::vector<model::CellType> >* cells;
    std::vector<bool>* cellVisibilities;

    model::World readWorld();
    std::vector<model::Player> readPlayers();
    std::vector<model::Trooper> readTroopers();
    model::Trooper readTrooper();
    std::vector<model::Bonus> readBonuses();
    std::vector<std::vector<model::CellType> >& readCells();
    std::vector<bool>& readCellVisibilities();

    static void ensureMessageType(MessageType actualType, MessageType expectedType);

    signed char readEnum();
    void writeEnum(signed char value);
    std::string readString();
    void writeString(std::string value);
    bool readBoolean();
    void writeBoolean(bool value);
    int readInt();
    void writeInt(int value);
    long long readLong();
    void writeLong(long long value);
    double readDouble();
    void writeDouble(double value);
    std::vector<signed char> readBytes(unsigned int byteCount);
    void writeBytes(std::vector<signed char> bytes);

    static bool isLittleEndianMachine();
public:
    RemoteProcessClient(std::string host, int port);
    ~RemoteProcessClient();

    void writeToken(std::string token);
    int readTeamSize();
    void writeProtocolVersion();
    model::Game readGameContext();
    model::PlayerContext* readPlayerContext();
    void writeMove(model::Move move);

    void close();
};

#endif
