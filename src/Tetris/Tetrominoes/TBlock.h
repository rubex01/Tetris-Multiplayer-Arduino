#ifndef SRC_TETRIS_TETROMINOES_TBLOCK_H_
#define SRC_TETRIS_TETROMINOES_TBLOCK_H_

#include "../Block.h"


class TBlock : public Block {
 public:
    TBlock(int xPos, int yPos);
    bool checkBlock();
    void rotateBlock();
    void resetBlock();
    void drawSectionBlock(int section);
};

#endif  // SRC_TETRIS_TETROMINOES_TBLOCK_H_
