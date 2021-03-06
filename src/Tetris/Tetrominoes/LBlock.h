#ifndef SRC_TETRIS_TETROMINOES_LBLOCK_H_
#define SRC_TETRIS_TETROMINOES_LBLOCK_H_

#include "../Block.h"

class LBlock : public Block {
 public:
    LBlock(int xPos, int yPos);
    void rotateBlock();
    void resetBlock();
    void drawSectionBlock(int section);
};

#endif  // SRC_TETRIS_TETROMINOES_LBLOCK_H_
