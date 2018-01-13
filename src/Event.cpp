// Event.cpp
// Implementation of the Event file.
// Created on January 2, 2018
// Last modified on January 2, 2018

#include "Event.h"

namespace Event
{
    void UpdateEvent(Ship* ship, int panelNumber, int choice)
    {
        std::vector<std::string> answers; // Vector for passing possible answers.

        if(!visited[ship->si._location] || panelNumber > 1) // If location hasn't been visited or new panel, run event.
        {
            switch(ship->si._location)
            {
            case 0:
                if(panelNumber == 1)
                {
                    ship->si.DisplayPanel("You are the captain of an infamous raider mob. You and your marauder crew "
                                "were hired by the newly formed rebel alliance to thief vital information "
                                "on the Janerian Empire's mothership. The Janerian Empire led under their Lord, "
                                "Emperor Tommy Janna the Great, have been tyranizing the star citizens of this "
                                "galaxy for decades!\n\nYour crew successfully obtained the intel "
                                "and your payment from the rebel camp will be wired once you return it to the rebel "
                                "base on Earth-5. The empire tagged your ship with a tracker as you were escaping "
                                "and they have a probe in pursuit!\n\nYour shields were damaged while escaping the "
                                "Janerian's and the enemies are hot on your trail. You should open your space map "
                                "and head to the next space sector.");
                }
                break;
            case 1:
                if(panelNumber == 1)
                {
                    answers.push_back(">: Fly towards the origin of the distress beacon.");
                    answers.push_back(">: Ignore the signal, I have enough on my plate right now.");

                    ship->si.DisplayPanel("Your ship is picking up an incoming signal from a nearby planet in the sector.\n\n"
                                    "The radio is picking up a lot of static, but you're able to make out a few words:\n"
                                    "       ...help us...stuck...circumstances...\n"
                                    "       ...bZ..bloop...dyingggg...wzzzzZZ....", answers, 2);
                }

                else if(panelNumber == 2)
                {
                    if(choice == 0)
                    {
                        answers.push_back(">: Continue");

                        ship->si.DisplayPanel("You fly cautiously toward the planet where the signal originates.\n\n"
                                        "As the captain, you and another crew member, Cornelius, go down to the planet. "
                                        "On the planet you encounter a small village with humanoid dolphins living "
                                        "in huts built with metal debris.\n\nTheir leader informs you of the destruction "
                                        "of their city while Cornelius wanders off into "
                                        "the desolate planet.\n\nDuring your conversation with the leader, you hear "
                                        "a terrified yelp from outside the hut.", answers, 3);
                    }
                }

                else if(panelNumber == 3)
                {
                    answers.push_back(">: I'll leave, we'll return to save you Cornelius, I promise.");
                    answers.push_back(">: Grab your concealed weapon and fight the natives!!");

                    ship->si.DisplayPanel("You rush out of the hut to see the natives mercilessly beating Cornelius "
                                        "on the ground! You try to intervene, but the leader emerges from the tent pointing "
                                        "a gun at you.\n\n\"TAKE ANOTHER STEP AND YOU BOTH DIE!\"\n\n The leader escorts you "
                                        "back to your ship, and allows you and the rest of your crew to leave in peace, in "
                                        "exchange for Cornelius to work as a slave.", answers, 4);
                }

                else if(panelNumber == 4)
                {
                    if(choice == 0)
                    {
                        ship->si.DisplayPanel("You quickly leave the planet.\n\nYou lost a crew member. (-1 energy in combat)");
                    }

                    if(choice == 1)
                    {
                        ship->si.DisplayPanel("You pull out your gun from your leather jacket!\n\n"
                                "Unfortunately, the leader was intently prepared for such an event and shoots "
                                "you in the arm. You quickly hop aboard your ship and escape while all the natives"
                                "fire at your ship with their blasters.\n\n"
                                "You lost a crew member (-1 energy in combat) and your ship took 20 HP in damage.");
                        
                        ship->_health -= 20;
                    }

                    ship->_members--;
                }
                break;

            case 2:
                ship->si.DisplayPanel("You find a floating sack sitting in the distance. You fetch it with your "
                                    "ship's arm and open it.\n\nAww sweet, you found 50 trade credits!"
                                    "(Redeemable at any participating Galacic Trade Market)");
                
                ship->_credits += 50;
                break;
            
            case 3:
                if(panelNumber == 1)
                {
                    Enemy* enemy = new Enemy(2, Game::_renderer);
                    enemy->_texture->LoadTexture("../assets/graphics/enemyship.png");

                    answers.push_back(">: Loyalty tax my ass! Bite me.");
                    answers.push_back(">: Of course, we don't want to cause any trouble. Please take our " 
                                        + std::to_string(ship->_credits) + " credits.");

                    ship->si.DisplayPanel("An incoming ship slows to a halt, and a video transmission "
                                        "of a group of Klingons sitting around their ship's dashboard is "
                                        "patched through to your main systems monitor. The "
                                        "one in the front speaks first:\n\n"
                                        "\"We are on a diplomatic mission on behalf of the Empire "
                                        "and we ask that you forfeit all your trade credits as a loyalty tax "
                                        "to the Emporor.\"", answers, 2);
                }

                else if(panelNumber == 2)
                {
                    if(choice == 0)
                    {
                        answers.push_back("Battle!");

                        ship->si.DisplayPanel("\"Then you shall feel the full wrath of the EMPIRE!!!\"", answers, 3);
                    }

                    else if(choice == 1)
                    {
                        ship->si.DisplayPanel("\"Thanks for your compliance.\"\n\nYou lost "
                                + std::to_string(ship->_credits) + "credits.");

                        ship->_credits = 0;
                    }
                }

                else if(panelNumber == 3)
                {
                    ship->si.CombatPanel();
                }
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