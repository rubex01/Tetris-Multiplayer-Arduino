#ifndef SRC_TETRIS_TETROMINOES_JBLOCK_H_
#define SRC_TETRIS_TETROMINOES_JBLOCK_H_

#include "../Block.h"


class JBlock : public Block {
 public:
    JBlock(int xPos, int yPos);
    bool checkBlock();
};

#endif  // SRC_TETRIS_TETROMINOES_JBLOCK_H_
