#ifndef SRC_TETRIS_TETROMINOES_ZBLOCK_H_
#define SRC_TETRIS_TETROMINOES_ZBLOCK_H_

#include "../Block.h"


class ZBlock : public Block {
 public:
    ZBlock(int xPos, int yPos);
    bool checkBlock();
    void rotateBlock();
    void drawSectionBlock();
};

#endif  // SRC_TETRIS_TETROMINOES_ZBLOCK_H_
