#ifndef SRC_TETRIS_TETROMINOES_SBLOCK_H_
#define SRC_TETRIS_TETROMINOES_SBLOCK_H_

#include "../Block.h"


class SBlock : public Block {
 public:
    SBlock(int xPos, int yPos);
    bool checkBlock();
};

#endif  // SRC_TETRIS_TETROMINOES_SBLOCK_H_
