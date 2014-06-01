#include "ThingSpeak.h"

const char *UPDATE PROGMEM = "/update";
const char* URL PROGMEM = "api.thingspeak.com";

ThingSpeak::ThingSpeak(Client *client)
{
    this->client = client;
}

int ThingSpeak::readResponse()
{
    return readResponse(NULL);
}

/*
 * this implementation comes from:
 *   https://github.com/csquared/arduino-restclient
 */
int ThingSpeak::readResponse(String *response)
{

    boolean httpBody = false;
    boolean inStatus = false;
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    
    int i = 0;
    int code = 0;
    char statusCode[4];
    
    while (client->connected())
    {
        if (client->available())
        {
            char c = client->read();

            if (c == ' ' && !inStatus)
            {
                inStatus = true;
            }

            if (inStatus && i < 3 && c != ' ')
            {
                statusCode[i] = c;
                i++;
            }
            
            if (i == 3)
            {
                statusCode[i] = '\0';
                code = atoi(statusCode);
            }
            
            if (httpBody && response != NULL)
            {
                response->concat(c);
            }
            
            if (c == '\n' && httpBody)
            {
                break;
            }
            
            if (c == '\n' && currentLineIsBlank)
            {
                httpBody = true;
            }
            
            if (c == '\n')
            {
                // you're starting a new line
                currentLineIsBlank = true;
            }
            else if (c != '\r')
            {
                // you've gotten a character on the current line
                currentLineIsBlank = false;
            }
        }
    }

    return code;
}
void ThingSpeak::updateChannel(ThingEvent *event)
{
    updateThingSpeak(UPDATE, event->getAPIKey(), event->asNameValues());
}

// private

void ThingSpeak::updateThingSpeak(const char *uri, const char *apiKey, String body)
{
    if (client->connect(URL, 80))
    {
        client->print(F("POST "));
        client->print(uri);
        client->print(F(" HTTP/1.1\n"));
        client->print(F("Host: api.thingspeak.com\n"));
        client->print(F("Connection: close\n"));
        client->print(F("X-THINGSPEAKAPIKEY: "));
        client->print(apiKey);
        client->print(F("\n"));
        client->print(F("Content-Type: application/x-www-form-urlencoded\n"));
        client->print(F("Content-Length: "));
        client->print(body.length());
        client->print(F("\n\n"));

        client->print(body);

        // small delay to send everything over
        delay(100);
    }
}