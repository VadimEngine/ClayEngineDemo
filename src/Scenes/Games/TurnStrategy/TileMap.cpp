// third party
#include <clay/application/Logger.h>
// class
#include "Scenes/Games/TurnStrategy/TileMap.h"

namespace turn_strategy {
// TODO dont use a texture here since its only used to build the tile map. Unless there is plans to render this texture
TileMap::TileMap(clay::Texture* texture, clay::SpriteSheet* spriteSheet) {
    // Get the texture dimensions
    int width, height, channels;
    width = texture->getWidth();
    height = texture->getHeight();
    channels = texture->getChannels();

    // Allocate memory to hold the texture data
    size_t dataSize = width * height * channels;

    std::vector<unsigned char> textureData = texture->getPixelData(); 

    // Resize the tilemap
    mTiles_.resize(height);
    for (auto& row : mTiles_) {
        row.resize(width);
    }

    // iterate texture and do a y flip to handle opengl image flip
    for (int y = 0; y < height; ++y) { // y flip
        for (int x = 0; x < width; ++x) {
            // Calculate the index for accessing the pixel data in the textureData array
            int index = ((height - 1 - y) * width + x) * channels;

            unsigned char* pixel = &textureData[index];

            // Assuming the channels are ordered as RGB
            unsigned char red = pixel[0];
            unsigned char green = pixel[1];
            unsigned char blue = pixel[2];

            // Combine RGB values into a single integer representing the color
            unsigned int combinedColor = (red << 16) | (green << 8) | blue;

            if (combinedColor == 0x0000FF) {
                // Water
                mTiles_[y][x].type = Tile::Type::SEA;
                mTiles_[y][x].sprite = std::make_unique<clay::SpriteSheet::Sprite>(*spriteSheet, glm::ivec2(2, 1));
            } else if (combinedColor == 0x00FF00) {
                // grass
                mTiles_[y][x].type = Tile::Type::GRASS;
                mTiles_[y][x].sprite = std::make_unique<clay::SpriteSheet::Sprite>(*spriteSheet, glm::ivec2(0, 1));
            } else if (combinedColor == 0xFFFF00) {
                // sand
                mTiles_[y][x].type = Tile::Type::SAND;
                mTiles_[y][x].sprite = std::make_unique<clay::SpriteSheet::Sprite>(*spriteSheet, glm::ivec2(3, 1));
            }
        }
    }
}

TileMap::~TileMap() {}

void TileMap::render(const clay::Renderer& theRenderer) {
    for (int y = 0; y < mTiles_.size(); ++y) {
        for (int x = 0; x < mTiles_[0].size(); ++x) {
            glm::vec3 position = {x, y, 0};
            glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
            if (mTiles_[y][x].sprite != nullptr) {
                theRenderer.renderSprite(*(mTiles_[y][x].sprite), translationMatrix, {1,1,1,1});
            }
        }
    }
}

const TileMap::Tile* TileMap::tileAt(glm::ivec2 position) const {
    if (mTiles_.size() <= position.y || mTiles_[0].size() <= position.x) {
        return nullptr;
    } else {
        return &mTiles_[position.y][position.x];
    }
}

int TileMap::getWidth() const {
    if (mTiles_.empty()) {
        return 0;
    } else {
        return mTiles_[0].size();
    }
}

int TileMap::getHeight() const {
    return mTiles_.size();
}

} // namespace turn_strategy
