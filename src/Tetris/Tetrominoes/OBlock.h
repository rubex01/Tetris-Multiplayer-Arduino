#ifndef SRC_TETRIS_TETROMINOES_OBLOCK_H_
#define SRC_TETRIS_TETROMINOES_OBLOCK_H_

#include "../Block.h"


class OBlock : public Block {
 public:
    OBlock(int xPos, int yPos);
    bool checkBlock();
    void rotateBlock();
};

#endif  // SRC_TETRIS_TETROMINOES_OBLOCK_H_
