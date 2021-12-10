#ifndef KBS_RECEIVEDDATA_H
#define KBS_RECEIVEDDATA_H


class ReceivedData {
    public:
        static void addNewResult(uint8_t result);
        static uint8_t * getResults();
        static bool newResultsAvailable();

    private:
        static uint8_t results[20];
        static int count;

};


#endif //KBS_RECEIVEDDATA_H
