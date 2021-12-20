#ifndef SRC_COMMUNICATION_RECEIVEDDATA_H_
#define SRC_COMMUNICATION_RECEIVEDDATA_H_

class ReceivedData {
 public:
    static void addNewResult(uint8_t result);
    static uint8_t * getResults();
    static bool newResultsAvailable();

 private:
    static uint8_t results[20];
    static int count;
};

#endif  // SRC_COMMUNICATION_RECEIVEDDATA_H_
