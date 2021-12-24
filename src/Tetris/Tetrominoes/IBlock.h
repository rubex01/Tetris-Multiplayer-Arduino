#ifndef SRC_TETRIS_TETROMINOES_IBLOCK_H_
#define SRC_TETRIS_TETROMINOES_IBLOCK_H_

#include "../Block.h"


class IBlock : public Block {
 public:
    IBlock(int xPos, int yPos);
    bool checkBlock();
    void rotateBlock();
    void resetBlock();
    void drawSectionBlock(int section);
};

#endif  // SRC_TETRIS_TETROMINOES_IBLOCK_H_
