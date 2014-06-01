#ifndef ThingEvent_H
#define ThingEvent_H

#include <Arduino.h>
#include <WString.h>

class ThingEvent
{
    private:
        const char *apiKey;        
        String fields[8];
        
    public:        
        ThingEvent(const char *apiKey);

        const char* getAPIKey();
        
        String getField(int field); 
        void setField(int field, String value);
    
        String asNameValues();
    private:

};

#endif