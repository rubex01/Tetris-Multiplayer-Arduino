#ifndef SRC_TETRIS_TETROMINOES_SBLOCK_H_
#define SRC_TETRIS_TETROMINOES_SBLOCK_H_

#include "../Block.h"

class SBlock : public Block {
 public:
    SBlock(int xPos, int yPos);
    void rotateBlock();
    void resetBlock();
    void drawSectionBlock(int section);
};

#endif  // SRC_TETRIS_TETROMINOES_SBLOCK_H_
