#ifndef SRC_TETRIS_BLOCK_H_
#define SRC_TETRIS_BLOCK_H_

class Block {
 public:
  Block(int xPos, int yPos);
  ~Block();
  void initBlock();
  void updateBlock();
  void moveDown();
  void moveSideways(int direction);
  bool checkBlock();
  int** blockArray;
  int blockColor;

 protected:
  void copyArray(int array[11][10]);
  void resetDirection(int direction);
  void setValue(int value);
  int xPos;
  int yPos;
};

#endif  // SRC_TETRIS_BLOCK_H_
