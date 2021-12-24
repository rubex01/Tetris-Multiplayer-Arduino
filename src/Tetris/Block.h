#ifndef SRC_TETRIS_BLOCK_H_
#define SRC_TETRIS_BLOCK_H_

#define HOLDSECTION 1
#define NEXTSECTION 2

#include <stdint.h>

class Block {
 public:
    uint8_t** blockArray;
    uint8_t blockColor;
    uint8_t tempArray[11][10] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};

    Block(int xPos, int yPos);
    ~Block();
    void initBlock();
    void moveDown();
    void moveSideways(int direction);
    void rotate();
    void setValue(int value);
    virtual void resetBlock() = 0;
    virtual void drawSectionBlock(int section) = 0;
    virtual void rotateBlock() = 0;
    static void triggerDrawSection(uint8_t section);

 protected:
    uint8_t xPos;
    uint8_t yPos;
    uint8_t rotationLevel;

    void copyArray(uint8_t array[11][10]);
    void resetDirection(int direction);
};

#endif  // SRC_TETRIS_BLOCK_H_
