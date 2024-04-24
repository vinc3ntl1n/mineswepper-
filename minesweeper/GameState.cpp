#include "GameState.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines)
        : dimensions(_dimensions), numMines(_numberOfMines), playStatus(PLAYING) {
    tiles.resize(dimensions.x, std::vector<std::shared_ptr<Tile>>(dimensions.y));
    srand(static_cast<unsigned int>(time(nullptr)));
    int placedMines = 0;
    while (placedMines < numMines) {
        int x = rand() % dimensions.x;
        int y = rand() % dimensions.y;
        if (!tiles[x][y]) {
            tiles[x][y] = std::make_shared<mine>(sf::Vector2f(x * 32.0f, y * 32.0f));
            placedMines++;
        }
    }
    for (int x = 0; x < dimensions.x; x++) {
        for (int y = 0; y < dimensions.y; y++) {
            if (!tiles[x][y]) {
                tiles[x][y] = std::make_shared<Tile>(sf::Vector2f(x * 32.0f, y * 32.0f));
            }
        }
    }
    setNeighbors();
    calculateMineCounts();
}

void GameState::setNeighbors() {
    for (int x = 0; x < dimensions.x; x++) {
        for (int y = 0; y < dimensions.y; y++) {
            std::array<std::shared_ptr<Tile>, 8> neighbors = {nullptr};
            // Set neighbors as before but with shared pointers
            // Neighbors assignment logic here...
        }
    }
}

void GameState::calculateMineCounts() {
    for (int x = 0; x < dimensions.x; x++) {
        for (int y = 0; y < dimensions.y; y++) {
            if (!tiles[x][y]->isMine()) {
                int count = 0;
                // Count mines logic here...
                tiles[x][y]->setNumMines(count);
            }
        }
    }
}

GameState::GameState(const char* filepath) {
    std::ifstream file(filepath);
    std::vector<std::vector<char>> tempVec;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.find_first_not_of(" \t") != std::string::npos) {
                std::vector<char> row(line.begin(), line.end());
                tempVec.push_back(row);
            }
        }
    }
    file.close();
    dimensions = sf::Vector2i(tempVec[0].size(), tempVec.size());
    numMines = 0;
    tiles.resize(dimensions.x, std::vector<std::shared_ptr<Tile>>(dimensions.y));
    for (int y = 0; y < dimensions.y; y++) {
        for (int x = 0; x < dimensions.x; x++) {
            if (tempVec[y][x] == '1') {
                tiles[x][y] = std::make_shared<mine>(sf::Vector2f(x * 32.0f, y * 32.0f));
                numMines++;
            } else {
                tiles[x][y] = std::make_shared<Tile>(sf::Vector2f(x * 32.0f, y * 32.0f));
            }
        }
    }
    setNeighbors();
    calculateMineCounts();
}

int GameState::getFlagCount() const {
    int flags = 0;
    for (auto& row : tiles) {
        for (auto& tile : row) {
            if (tile->getState() == Tile::State::FLAGGED) {
                flags++;
            }
        }
    }
    return flags;
}

int GameState::getMineCount() const {
    return numMines;
}

std::shared_ptr<Tile> GameState::getTile(int x, int y) const {
    if (x >= 0 && x < dimensions.x && y >= 0 && y < dimensions.y) {
        return tiles[x][y];
    }
    return nullptr;
}

GameState::PlayStatus GameState::getPlayStatus() const {
    return playStatus;
}

void GameState::setPlayStatus(PlayStatus _status) {
    playStatus = _status;
}

