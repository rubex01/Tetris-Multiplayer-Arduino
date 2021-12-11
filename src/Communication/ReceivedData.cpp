#include <avr/io.h>
#include "ReceivedData.h"

uint8_t ReceivedData::results[20] = {0};
int ReceivedData::count = 0;

void ReceivedData::addNewResult(uint8_t result)
{
    results[count] = result;
    count++;
}

bool ReceivedData::newResultsAvailable()
{
    return (count != 0);
}

uint8_t * ReceivedData::getResults()
{
    uint8_t* returnResults = new uint8_t[20];
    for (int i = 0; i < 20; ++i)
        returnResults[i] = results[i];
    for (int i = 0; i < count; ++i)
        results[i] = 0;
    count = 0;
    return returnResults;
}