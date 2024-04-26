#include "GameState.h"
#include "string"
using namespace std;
int GameState::getFlagCount() {
    int flags = 0;
    for (int x = 0; x < dimensions.x; x++) {  // loops through tile vector for number of tiles with flagged state
        for (int y = 0; y < dimensions.y; y++) {
            if (tiles[x][y]->getState() == Tile::State::FLAGGED) {
                flags++;
            }
        }
    }
    return flags;
}

int GameState::getMineCount() {
    return mineNum;
}

Tile* GameState::getTile(int x, int y) {
    return tiles[x][y];
}

GameState::PlayStatus GameState::getPlayStatus() {
    return currstatus;
}

void GameState::setPlayStatus(GameState::PlayStatus _status) {
    currstatus = _status;
}

sf::Vector2i GameState::getDimensions() {
    return dimensions;
}

vector<vector<Tile*>> GameState::getTiles() {
    return this->tiles;
}
GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    currstatus = PlayStatus::PLAYING;
    dimensions = _dimensions;
    mineNum = _numberOfMines;
    tiles.resize(dimensions.x, vector<Tile*>(dimensions.y, nullptr));
    srand(static_cast<unsigned int>(time(nullptr)));
    int placedMines = 0;
    while (placedMines < mineNum) {  // puts mine around the board
        int x = rand() % dimensions.x;
        int y = rand() % dimensions.y;
        if (tiles[x][y] == nullptr) {
            tiles[x][y] = new mine(sf::Vector2f(x * 32.0f, y * 32.0f));
            placedMines++;
        }
    }
    for (int x = 0; x < dimensions.x; x++) {  // makes the tiles after the mines to the blank ones
        for (int y = 0; y < dimensions.y; y++) {
            if (tiles[x][y] == nullptr) {
                tiles[x][y] = new Tile(sf::Vector2f(x * 32.0f, y * 32.0f));
            }
        }
    }
    for (int x = 0; x < dimensions.x; x++) {  // sets  array
        for (int y = 0; y < dimensions.y; y++) {
            array<Tile*, 8> arr{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
            if (x != 0 && y != 0) {
                arr[0] = tiles[x-1][y-1];
            }
            if (y != 0) {
                arr[1] = tiles[x][y-1];
            }
            if (x != dimensions.x - 1 && y != 0) {
                arr[2] = tiles[x+1][y-1];
            }
            if (x != 0) {
                arr[3] = tiles[x-1][y];
            }
            if (x != dimensions.x - 1) {
                arr[4] = tiles[x+1][y];
            }
            if (x != 0 && y != dimensions.y - 1) {
                arr[5] = tiles[x-1][y+1];
            }
            if (y != dimensions.y - 1) {
                arr[6] = tiles[x][y+1];
            }
            if (x != dimensions.x - 1 && y != dimensions.y - 1) {
                arr[7] = tiles[x+1][y+1];
            }
            tiles[x][y]->setNeighbors(arr);
        }
    }
    for (int x = 0; x < dimensions.x; x++) {  // checks how many mines are next to a tile
        for (int y = 0; y < dimensions.y; y++) {
            if (tiles[x][y]->isMine()) {
                continue;
            }
            int count = 0;
            for (Tile* a : tiles[x][y]->getNeighbors()) {
                if (a != nullptr && a->isMine()) {
                    count++;
                }
            }
            tiles[x][y]->setNumMines(count);
        }
    }
}

GameState::GameState(const char *filepath) {
    ifstream file(filepath);
    vector<vector<char>> tempVec;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find_first_not_of(" \t") != string::npos) {
                vector<char> row(line.begin(), line.end());
                tempVec.push_back(row);
            }
        }
    }
    else {
        cerr << "Error" << endl;
    }
    file.close();
    dimensions = sf::Vector2i(tempVec[0].size(), tempVec.size());
    for (int x = 0; x < dimensions.y; x++) {//sees how many bombs are in a certain vector
        for (int y = 0; y < dimensions.x; y++) {
            if (tempVec[x][y] == '1') {
                mineNum++;
            }
        }
    }
    tiles.resize(dimensions.x, vector<Tile*>(dimensions.y, nullptr));
    for (int x = 0; x < dimensions.x; x++) {
        for (int y = 0; y < dimensions.y; y++) {
            if (tempVec[y][x] == '1') {
                tiles[x][y] = new mine(sf::Vector2f(x * 32.0f, y * 32.0f));
            }
            else {
                tiles[x][y] = new Tile(sf::Vector2f(x * 32.0f, y * 32.0f));
            }
        }
    }
    for (int x = 0; x < dimensions.x; x++) {
        for (int y = 0; y < dimensions.y; y++) {
            array<Tile*, 8> arr{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
            if (x != 0 && y != 0) {
                arr[0] = tiles[x-1][y-1];
            }
            if (y != 0) {
                arr[1] = tiles[x][y-1];
            }
            if (x != dimensions.x - 1 && y != 0) {
                arr[2] = tiles[x+1][y-1];
            }
            if (x != 0) {
                arr[3] = tiles[x-1][y];
            }
            if (x != dimensions.x - 1) {
                arr[4] = tiles[x+1][y];
            }
            if (x != 0 && y != dimensions.y - 1) {
                arr[5] = tiles[x-1][y+1];
            }
            if (y != dimensions.y - 1) {
                arr[6] = tiles[x][y+1];
            }
            if (x != dimensions.x - 1 && y != dimensions.y - 1) {
                arr[7] = tiles[x+1][y+1];
            }
            tiles[x][y]->setNeighbors(arr);
        }
    }
    for (int x = 0; x < dimensions.x; x++) {
        for (int y = 0; y < dimensions.y; y++) {
            if (tiles[x][y]->isMine()) {
                continue;
            }
            int count = 0;
            for (Tile* a : tiles[x][y]->getNeighbors()) {
                if (a != nullptr && a->isMine()) {
                    count++;
                }
            }
            tiles[x][y]->setNumMines(count);
        }
    }
}
