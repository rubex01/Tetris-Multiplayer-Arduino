#include <avr/io.h>
#include "ReceivedData.h"

uint8_t ReceivedData::results[20] = {0};
int ReceivedData::count = 0;

/**
 * Add a new result to the received values
 *
 * @param result
 */
void ReceivedData::addNewResult(uint8_t result) {
    results[count] = result;
    count++;
}

/**
 * Will check if there are any new results available that haven't been fetched yet
 *
 * @return bool
 */
bool ReceivedData::newResultsAvailable() {
    return (count != 0);
}

/**
 * Returns all the results that have been stored and will clear the result storage after
 *
 * @return uint8_t *
 */
uint8_t * ReceivedData::getResults() {
    uint8_t* returnResults = new uint8_t[20];
    for (int i = 0; i < 20; ++i)
        returnResults[i] = results[i];
    for (int i = 0; i < count; ++i)
        results[i] = 0;
    count = 0;
    return returnResults;
}
