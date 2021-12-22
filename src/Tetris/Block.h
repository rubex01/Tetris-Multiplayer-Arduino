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
  void drawSectionBlock();
  int** blockArray;
  int blockColor;
  void rotate();
  virtual void rotateBlock();

 protected:
  void copyArray(int array[11][10]);
  void resetDirection(int direction);
  void setValue(int value);
  int xPos;
  int rotationLevel;
  int yPos;
};

#endif  // SRC_TETRIS_BLOCK_H_
