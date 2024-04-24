#include "GameState.h"
#include <array> // Add this include directive

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    playStatus = PlayStatus::PLAYING;
    dimensions = _dimensions;
    numMines = _numberOfMines;

    tiles.resize(dimensions.y); // Resize outer vector

    for (int y = 0; y < dimensions.y; y++) {
        tiles[y].resize(dimensions.x); // Resize inner vectors
        for (int x = 0; x < dimensions.x; x++) {
            tiles[y][x] = std::make_unique<Tile>(sf::Vector2f(x * 32.0f, y * 32.0f)); // Use make_unique to create unique pointers
        }
    }

    srand(static_cast<unsigned int>(time(nullptr))); // random number generator
    int placedMines = 0;
    while (placedMines < numMines) { // randomly places mines throughout the board
        int x = rand() % dimensions.x;
        int y = rand() % dimensions.y;
        if (!tiles[y][x]) {
            tiles[y][x] = std::make_unique<mine>(sf::Vector2f(x * 32.0f, y * 32.0f));
            placedMines++;
        }
    }

    setNeighborsAndMines(); // Set neighbors and number of mines near each tile
}

GameState::GameState(const char *filepath) {
    std::ifstream file(filepath);
    std::vector<std::vector<char>> tempVec;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.find_first_not_of(" \t") != std::string::npos) { // skips blank lines
                std::vector<char> row(line.begin(), line.end());
                tempVec.push_back(row);
            }
        }
    } else {
        std::cerr << "Error opening file" << std::endl;
    }
    file.close();

    dimensions = sf::Vector2i(tempVec[0].size(), tempVec.size()); // checks for the number of mines in the vector

    tiles.resize(dimensions.y); // Resize outer vector
    for (auto& row : tiles) {
        row.resize(dimensions.x); // Resize inner vectors
    }


    for (int y = 0; y < dimensions.y; y++) { // fills in tile vector using temporary vector values ('0', '1')
        for (int x = 0; x < dimensions.x; x++) {
            if (tempVec[y][x] == '1') {
                tiles[y][x] = std::make_unique<mine>(sf::Vector2f(x * 32.0f, y * 32.0f));
            } else {
                tiles[y][x] = std::make_unique<Tile>(sf::Vector2f(x * 32.0f, y * 32.0f));
            }
        }
    }

    setNeighborsAndMines(); // Set neighbors and number of mines near each tile
}

void GameState::setNeighborsAndMines() {
    for (int y = 0; y < dimensions.y; y++) {
        for (int x = 0; x < dimensions.x; x++) {
            std::array<Tile*, 8> neighbors{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
            if (x != 0 && y != 0) {
                neighbors[0] = tiles[y - 1][x - 1].get();
            }
            if (y != 0) {
                neighbors[1] = tiles[y - 1][x].get();
            }
            if (x != dimensions.x - 1 && y != 0) {
                neighbors[2] = tiles[y - 1][x + 1].get();
            }
            if (x != 0) {
                neighbors[3] = tiles[y][x - 1].get();
            }
            if (x != dimensions.x - 1) {
                neighbors[4] = tiles[y][x + 1].get();
            }
            if (x != 0 && y != dimensions.y - 1) {
                neighbors[5] = tiles[y + 1][x - 1].get();
            }
            if (y != dimensions.y - 1) {
                neighbors[6] = tiles[y + 1][x].get();
            }
            if (x != dimensions.x - 1 && y != dimensions.y - 1) {
                neighbors[7] = tiles[y + 1][x + 1].get();
            }
            for (Tile* neighbor : neighbors) {
                if (neighbor != nullptr) {
                    tiles[y][x]->addNeighbor(neighbor);
                }
            }
        }
    }
    for (int y = 0; y < dimensions.y; y++) {
        for (int x = 0; x < dimensions.x; x++) {
            if (tiles[y][x]->isMine()) {
                continue;
            }
            int count = 0;
            for (Tile* a : tiles[y][x]->getNeighbors()) {
                if (a != nullptr && a->isMine()) {
                    count++;
                }
            }
            tiles[y][x]->setNumMines(count);
        }
    }
}

int GameState::getFlagCount() {
    int flags = 0;
    for (int y = 0; y < dimensions.y; y++) { // loops through the tile vector for the number of tiles with the flagged state
        for (int x = 0; x < dimensions.x; x++) {
            if (tiles[y][x]->getState() == Tile::State::FLAGGED) {
                flags++;
            }
        }
    }
    return flags;
}

int GameState::getMineCount() {
    return numMines;
}

Tile* GameState::getTile(int x, int y) {
    return tiles[y][x].get();
}

GameState::PlayStatus GameState::getPlayStatus() {
    return playStatus;
}

void GameState::setPlayStatus(GameState::PlayStatus _status) {
    playStatus = _status;
}

sf::Vector2i GameState::getDimensions() {
    return dimensions;
}

std::vector<std::vector<std::unique_ptr<Tile>>>& GameState::getTiles() {
    return tiles;
}

// Destructor definition
GameState::~GameState() {
    // Optionally, add cleanup code here if necessary
}
