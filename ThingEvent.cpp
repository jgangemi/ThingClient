#include "ThingCommon.h"
#include "ThingEvent.h"

ThingEvent::ThingEvent(const char *apiKey)
{
    this->apiKey = apiKey;
}

const char* ThingEvent::getAPIKey()
{
    return this->apiKey;
}

void ThingEvent::setField(int field, String value)
{
    if (field >= 1 && field <= 8)
    {
        this->fields[field - 1] = value;        
    }
}

String ThingEvent::getField(int field)
{
    if (field >= 1 && field <= 8)
    {
        return this->fields[field - 1];        
    }
    
    return EMPTY;
}

String ThingEvent::asNameValues()
{
    String nvp;
    
    for (int i = 0; i < 8; i++)
    {
        String value = this->fields[i - 1];
        if (value != EMPTY)
        {
            nvp += String(i) + EQS + this->fields[i - 1] + AMP;
        }
    }
    
    if (nvp.endsWith(AMP))
    {
        nvp = nvp.substring(0, nvp.length() - 1);
    }
    
    return nvp;
}
