#include "RemoteProcessClient.h"

#include <algorithm>

using namespace model;
using namespace std;

const bool LITTLE_ENDIAN_BYTE_ORDER = true;
const int INTEGER_SIZE_BYTES = sizeof(int);
const int LONG_SIZE_BYTES = sizeof(long long);

RemoteProcessClient::RemoteProcessClient(string host, int port) {
    socket.Initialize();

    if (!socket.Open((uint8*) host.c_str(), port)) {
        exit(10001);
    }

    cells = NULL;
    cellVisibilities = NULL;
}

RemoteProcessClient::~RemoteProcessClient() {
    if (cells != NULL) {
        delete cells;
    }

    if (cellVisibilities != NULL) {
        delete cellVisibilities;
    }
}

void RemoteProcessClient::writeToken(string token) {
    writeEnum(AUTHENTICATION_TOKEN);
    writeString(token);
}

int RemoteProcessClient::readTeamSize() {
    ensureMessageType((MessageType) readEnum(), TEAM_SIZE);
    return readInt();
}

void RemoteProcessClient::writeProtocolVersion() {
    writeEnum(PROTOCOL_VERSION);
    writeInt(2);
}

Game RemoteProcessClient::readGameContext() {
    ensureMessageType((MessageType) readEnum(), GAME_CONTEXT);
    if (!readBoolean()) {
        exit(10017);
    }

    int moveCount = readInt();
    int lastPlayerEliminationScore = readInt();
    int playerEliminationScore = readInt();
    int trooperEliminationScore = readInt();
    double trooperDamageScoreFactor = readDouble();
    int stanceChangeCost = readInt();
    int standingMoveCost = readInt();
    int kneelingMoveCost = readInt();
    int proneMoveCost = readInt();
    int commanderAuraBonusActionPoints = readInt();
    double commanderAuraRange = readDouble();
    int commanderRequestEnemyDispositionCost = readInt();
    int commanderRequestEnemyDispositionMaxOffset = readInt();
    int fieldMedicHealCost = readInt();
    int fieldMedicHealBonusHitpoints = readInt();
    int fieldMedicHealSelfBonusHitpoints = readInt();
    double sniperStandingStealthBonus = readDouble();
    double sniperKneelingStealthBonus = readDouble();
    double sniperProneStealthBonus = readDouble();
    double sniperStandingShootingRangeBonus = readDouble();
    double sniperKneelingShootingRangeBonus = readDouble();
    double sniperProneShootingRangeBonus = readDouble();
    double scoutStealthBonusNegation = readDouble();
    int grenadeThrowCost = readInt();
    double grenadeThrowRange = readDouble();
    int grenadeDirectDamage = readInt();
    int grenadeCollateralDamage = readInt();
    int medikitUseCost = readInt();
    int medikitBonusHitpoints = readInt();
    int medikitHealSelfBonusHitpoints = readInt();
    int fieldRationEatCost = readInt();
    int fieldRationBonusActionPoints = readInt();

    return Game(moveCount,
        lastPlayerEliminationScore, playerEliminationScore,
        trooperEliminationScore, trooperDamageScoreFactor,
        stanceChangeCost, standingMoveCost, kneelingMoveCost, proneMoveCost,
        commanderAuraBonusActionPoints, commanderAuraRange,
        commanderRequestEnemyDispositionCost, commanderRequestEnemyDispositionMaxOffset,
        fieldMedicHealCost, fieldMedicHealBonusHitpoints, fieldMedicHealSelfBonusHitpoints,
        sniperStandingStealthBonus, sniperKneelingStealthBonus, sniperProneStealthBonus,
        sniperStandingShootingRangeBonus, sniperKneelingShootingRangeBonus,
        sniperProneShootingRangeBonus, scoutStealthBonusNegation,
        grenadeThrowCost, grenadeThrowRange, grenadeDirectDamage, grenadeCollateralDamage,
        medikitUseCost, medikitBonusHitpoints, medikitHealSelfBonusHitpoints,
        fieldRationEatCost, fieldRationBonusActionPoints);
}

PlayerContext* RemoteProcessClient::readPlayerContext() {
    MessageType messageType = (MessageType) readEnum();
    if (messageType == GAME_OVER) {
        return NULL;
    }

    ensureMessageType(messageType, PLAYER_CONTEXT);

    if (!readBoolean()) {
        return NULL;
    }

    Trooper trooper = readTrooper();
    World world = readWorld();

    return new PlayerContext(trooper, world);
}

void RemoteProcessClient::writeMove(Move move) {
    writeEnum(MOVE_MESSAGE);

    writeBoolean(true);

    writeEnum(move.getAction());
    writeEnum(move.getDirection());
    writeInt(move.getX());
    writeInt(move.getY());
}

void RemoteProcessClient::close() {
    socket.Close();
}

World RemoteProcessClient::readWorld() {
    if (!readBoolean()) {
        exit(10002);
    }

    int moveIndex = readInt();
    int width = readInt();
    int height = readInt();
    vector<Player> players = readPlayers();
    vector<Trooper> troopers = readTroopers();
    vector<Bonus> bonuses = readBonuses();
    vector<vector<CellType> >& cells = readCells();
    vector<bool>& cellVisibilities = readCellVisibilities();

    return World(moveIndex, width, height, players, troopers, bonuses, cells, cellVisibilities);
}

vector<Player> RemoteProcessClient::readPlayers() {
    int playerCount = readInt();
    if (playerCount < 0) {
        exit(10003);
    }

    vector<Player> players;
    players.reserve(playerCount);

    for (int playerIndex = 0; playerIndex < playerCount; ++playerIndex) {
        if (readBoolean()) {
            long long id = readLong();
            string name = readString();
            int score = readInt();
            bool strategyCrashed = readBoolean();
            int approximateX = readInt();
            int approximateY = readInt();

            players.push_back(Player(id, name, score, strategyCrashed, approximateX, approximateY));
        } else {
            exit(10004);
        }
    }

    return players;
}

vector<Trooper> RemoteProcessClient::readTroopers() {
    int trooperCount = readInt();
    if (trooperCount < 0) {
        exit(10005);
    }

    vector<Trooper> troopers;
    troopers.reserve(trooperCount);

    for (int trooperIndex = 0; trooperIndex < trooperCount; ++trooperIndex) {
        troopers.push_back(readTrooper());
    }

    return troopers;
}

Trooper RemoteProcessClient::readTrooper() {
    if (!readBoolean()) {
        exit(10006);
    }

    long long id = readLong();
    int x = readInt();
    int y = readInt();
    long long playerId = readLong();
    int teammateIndex = readInt();
    bool teammate = readBoolean();
    TrooperType type = (TrooperType) readEnum();
    TrooperStance stance = (TrooperStance) readEnum();
    int hitpoints = readInt();
    int maximalHitpoints = readInt();
    int actionPoints = readInt();
    int initialActionPoints = readInt();
    double visionRange = readDouble();
    double shootingRange = readDouble();
    int shootCost = readInt();
    int standingDamage = readInt();
    int kneelingDamage = readInt();
    int proneDamage = readInt();
    int damage = readInt();
    bool holdingGrenade = readBoolean();
    bool holdingMedikit = readBoolean();
    bool holdingFieldRation = readBoolean();

    return Trooper(id, x, y, playerId,
        teammateIndex, teammate, type, stance,
        hitpoints, maximalHitpoints, actionPoints, initialActionPoints,
        visionRange, shootingRange, shootCost,
        standingDamage, kneelingDamage, proneDamage, damage,
        holdingGrenade, holdingMedikit, holdingFieldRation);
}

vector<Bonus> RemoteProcessClient::readBonuses() {
    int bonusCount = readInt();
    if (bonusCount < 0) {
        exit(10009);
    }

    vector<Bonus> bonuses;
    bonuses.reserve(bonusCount);

    for (int bonusIndex = 0; bonusIndex < bonusCount; ++bonusIndex) {
        if (readBoolean()) {
            long long id = readLong();
            int x = readInt();
            int y = readInt();
            BonusType type = (BonusType) readEnum();

            bonuses.push_back(Bonus(id, x, y, type));
        } else {
            exit(10010);
        }
    }

    return bonuses;
}

vector<vector<CellType> >& RemoteProcessClient::readCells() {
    if (cells != NULL) {
        return *cells;
    }

    int width = readInt();
    if (width < 0) {
        exit(10007);
    }

    cells = new vector<vector<CellType> >();
    cells->reserve(width);

    for (int x = 0; x < width; ++x) {
        int height = readInt();
        if (height < 0) {
            exit(10008);
        }

        cells->push_back(vector<CellType>());
        cells->at(x).reserve(height);

        for (int y = 0; y < height; ++y) {
            cells->at(x).push_back((CellType) readEnum());
        }
    }

    return *cells;
}

vector<bool>& RemoteProcessClient::readCellVisibilities() {
    if (cellVisibilities != NULL) {
        return *cellVisibilities;
    }

    int worldWidth = readInt();
    if (worldWidth < 0) {
        exit(10018);
    }

    int worldHeight = readInt();
    if (worldHeight < 0) {
        exit(10019);
    }

    int stanceCount = readInt();
    if (stanceCount < 0) {
        exit(10020);
    }

    int rawVisibilityCount = worldWidth * worldHeight * worldWidth * worldHeight * stanceCount;
    vector<signed char> rawVisibilities = readBytes(rawVisibilityCount);
    cellVisibilities = new vector<bool>(rawVisibilityCount);

    for (int rawVisibilityIndex = 0; rawVisibilityIndex < rawVisibilityCount; ++rawVisibilityIndex) {
        (*cellVisibilities)[rawVisibilityIndex] = rawVisibilities[rawVisibilityIndex] != 0;
    }

    return *cellVisibilities;
}

void RemoteProcessClient::ensureMessageType(MessageType actualType, MessageType expectedType) {
    if (actualType != expectedType) {
        exit(10011);
    }
}

signed char RemoteProcessClient::readEnum() {
    return this->readBytes(1)[0];
}

void RemoteProcessClient::writeEnum(signed char value) {
    vector<signed char> bytes;
    bytes.push_back(value);
    this->writeBytes(bytes);
}

string RemoteProcessClient::readString() {
    int length = this->readInt();
    if (length == -1) {
        exit(10014);
    }

    vector<signed char> bytes = this->readBytes(length);
    return string((char*) (&bytes[0]), length);
}

void RemoteProcessClient::writeString(string value) {
    vector<signed char> bytes(value.size());
    
    memcpy(&bytes[0], value.c_str(), value.size());

    this->writeInt(static_cast<int>(bytes.size()));
    this->writeBytes(bytes);
}

bool RemoteProcessClient::readBoolean() {
    return this->readBytes(1)[0] != 0;
}

void RemoteProcessClient::writeBoolean(bool value) {
    vector<signed char> bytes;
    bytes.push_back((signed char) (value ? 1 : 0));
    this->writeBytes(bytes);
}

int RemoteProcessClient::readInt() {
    vector<signed char> bytes = this->readBytes(INTEGER_SIZE_BYTES);

    if (this->isLittleEndianMachine() != LITTLE_ENDIAN_BYTE_ORDER) {
        reverse(&bytes[0], &bytes[INTEGER_SIZE_BYTES - 1]);
    }

    int value;

    memcpy(&value, &bytes[0], INTEGER_SIZE_BYTES);

    return value;
}

void RemoteProcessClient::writeInt(int value) {
    vector<signed char> bytes(INTEGER_SIZE_BYTES);

    memcpy(&bytes[0], &value, INTEGER_SIZE_BYTES);

    if (this->isLittleEndianMachine() != LITTLE_ENDIAN_BYTE_ORDER) {
        reverse(&bytes[0], &bytes[INTEGER_SIZE_BYTES - 1]);
    }

    this->writeBytes(bytes);
}

long long RemoteProcessClient::readLong() {
    vector<signed char> bytes = this->readBytes(LONG_SIZE_BYTES);

    if (this->isLittleEndianMachine() != LITTLE_ENDIAN_BYTE_ORDER) {
        reverse(&bytes[0], &bytes[LONG_SIZE_BYTES - 1]);
    }

    long long value;

    memcpy(&value, &bytes[0], LONG_SIZE_BYTES);

    return value;
}

void RemoteProcessClient::writeLong(long long value) {
    vector<signed char> bytes(LONG_SIZE_BYTES);

    memcpy(&bytes[0], &value, LONG_SIZE_BYTES);

    if (this->isLittleEndianMachine() != LITTLE_ENDIAN_BYTE_ORDER) {
        reverse(&bytes[0], &bytes[LONG_SIZE_BYTES - 1]);
    }

    this->writeBytes(bytes);
}

double RemoteProcessClient::readDouble() {
    long long value = this->readLong();
    return *((double*) &value);
}

void RemoteProcessClient::writeDouble(double value) {
    this->writeLong(*((long long*) &value));
}

vector<signed char> RemoteProcessClient::readBytes(unsigned int byteCount) {
    vector<signed char> bytes(byteCount);
    unsigned int offset = 0;
    int receivedByteCount;

    while (offset < byteCount && (receivedByteCount = socket.Receive(byteCount - offset)) > 0) {
        memcpy(&bytes[offset], socket.GetData(), receivedByteCount);
        offset += receivedByteCount;
    }

    if (offset != byteCount) {
        exit(10012);
    }

    return bytes;
}

void RemoteProcessClient::writeBytes(vector<signed char> bytes) {
    vector<signed char>::size_type byteCount = bytes.size();
    unsigned int offset = 0;
    int sentByteCount;

    while (offset < byteCount && (sentByteCount = socket.Send((uint8*) &bytes[offset], byteCount - offset)) > 0) {
        offset += sentByteCount;
    }

    if (offset != byteCount) {
        exit(10013);
    }
}

bool RemoteProcessClient::isLittleEndianMachine() {
    union {
        uint16 value;
        unsigned char bytes[2];
    } test = {0x0201};

    return test.bytes[0] == 1; 
}
