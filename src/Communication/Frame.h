#ifndef KBS_FRAME_H
#define KBS_FRAME_H


class Frame {
 public:
    static uint8_t ROW_TYPE;
    static uint8_t SEED_TYPE;
    static uint8_t LOST_TYPE;
    static uint8_t CONFIRM_TYPE;

    Frame(uint8_t data, uint8_t type);
    Frame(uint8_t receivedFrameData);
    uint8_t getData();
    uint8_t getType();
    uint8_t getFrame();

 private:
    void createFrame();
    void decodeFrame();
    uint8_t frame;
    uint8_t data;
    uint8_t type;
};


#endif //KBS_FRAME_H
