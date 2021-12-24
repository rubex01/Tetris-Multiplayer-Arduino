#ifndef SRC_COMMUNICATION_RECEIVEDDATA_H_
#define SRC_COMMUNICATION_RECEIVEDDATA_H_

class ReceivedData {
 public:
    static void addNewResult(uint8_t result);
    static bool newResultsAvailable();
    static uint8_t * getResults();

 private:
    static uint8_t results[20];
    static uint8_t count;
};

#endif  // SRC_COMMUNICATION_RECEIVEDDATA_H_
