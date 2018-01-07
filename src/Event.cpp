// Event.cpp
// Implementation of the Event file.
// Created on January 2, 2018
// Last modified on January 2, 2018

#include "Event.h"

namespace Event
{

    void StartEvent(Ship* ship)
    {
        if(!visited[ship->si._location]) // If location hasn't been visited, run event.
        {
            switch(ship->si._location)
            {
            case 0:
                ship->si.DisplayPanel("You and your marauder crew are carrying vital information on the Janerian Empire's "
                                    "mothership. Your payment from the rebel camp will be wired once you return the intel "
                                    "to Earth-5. The Janerian's tagged your ship with a tracker and have a probe in pursuit!\n\n"
                                    "Your shields were damaged while escaping the Janerian space station and the enemies are "
                                    "hot on your trail.");
                break;
            
            case 1:
                ship->si.DisplayPanel("You are alone... This space sector appears to be empty, perhaps move on towards"
                                    "the next sector.");
                break;
            }
        }

        // Flag visited current location so when the ship returns, the same event won't run.
        visited[ship->si._location] = true;
    }

    void ResetLocations()
    {
        for(int i = 0; i < 15; i++)
        {
            visited[i] = false;
        }
    }
}