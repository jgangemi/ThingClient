#ifndef ThingSpeak_H
#define ThingSpeak_H

#include <Client.h>

#include "ThingCommon.h"
#include "ThingEvent.h"

class ThingSpeak
{
    private:
         Client *client;
        
    public:
        ThingSpeak(Client *client);

        int readResponse();
        int readResponse(String *response);        
        
        void updateChannel(ThingEvent *event);

    private:
        void updateThingSpeak(const char *uri, const char* apiKey, String body);

};

#endif
