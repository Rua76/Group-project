# **Group 55: Werewolves of Miller's Hollow**

## **Team Member Identification**
_(Alphabetical Order)_

**Chen Zhaoheng**

UID: 3035535573

**Yu Haoshengzhe**

UID: 3035535080

## **Game Description with Basic Rules**
1. **Basic Information**
   - **Game Type**
   
     - A text-based game with the major feature of decision-orientated. 
     
     - The player will take his/her own character and corporate with computers to win this game. 
   
   - **Background**
   
     - Werewolves of Miller's Hollow stands on the background of a peaceful village and one day several werewolves infiltrated into this place, aiming at killing all people in this village.
     - However, feeling of something horrible will happen, people in this village do not choose to sit still waiting for death. With some special villagers as the leaders, all villagers unite together to fight for their survival.
     - Obvious things are not always easy. Werewolves have the ability of pretending themselves as people during the daytime and they are smart enough to choose to kill people only at midnight.
     - Considering the ability of werewolves, villagers choose to hold a survivors debate on every morning and vote to lynch a guy they think is a werewolf.
     - **As a player,** 
       - **if you are the werewolf,** try your best to pretend yourself smartly and apply all your wisdom to kill all the normal/special villagers at midnight with your werewolf friends.
       - **if you are the villager,** try your best to protect yourself and others, make use of every clues the system and players provided to figure out werewolves and lynch them through voting.

2. **Game Rules**
   - **Group Size:**
   
     - We design this game as a table for 12 people. Since this is an offline game, the individual player will join in the game with remaining computer players.
     - Character Distribution:
       
       12 Players: 4 Werewolves,  4 Special Villagers, 4 Normal Villagers
   - **Game Process:**
    
     - **At the beginning of a game:**
       
       The random process will provide each player with a character. The players look at their cards without revealing their roles.
     - **The game then takes place in alternating phases:**
       - **Night:** 
       
         The system calls the characters that have abilities one at a time, to perform his/her role's special action.
         
         The calling process will let the werewolves take actions first and then special villagers.
         
       - **Day:**
       
         The system reports the name(s) of the player(s) which have been killed during the night.
         
         Those killed are not allowed to speak to the living for the rest of the game.
         
         Then, all the survivors give their statements one by one and vote to lynch a player they think is a werewolf.
         
       - **The game will automatically end if:**
          
          **_Werewolves win:_** all the special villagers **_or_** all the normal villagers are killed.
          
          **_Villagers win:_** all the werewolves are killed.
       
         
        
       
   - **Group:**   
   
     - **Good people:** 
         
       As good people, your goal is to kill or execute every werewolf. 
       
         - **Villager**
             
            Villagers do not have any special abilities. They can only vote claim and vote during the daytime.
            
         - **Seer**
         
            As an seer, you can check the identity of a player once a night. The system will tell you if that player is "good" (belongs to good people group) or "bad" (is a werewolf). You can choose to speak out your character in the daytime, so every other player will follow you in the voting, but this also exposes you to the werewolves, be careful!
            
         - **Witch**
         
            You have two potions:
            one to save the werewolves's victim
            one to eliminate a player
            You can only use each potion once during the game. You can’t use both potions during the same night. You can’t save yourself if you has been attacked by the werewolves on the first night.
            
         - **Hunter**
            
            If you are killed by werewolves or eliminated by vote, you must kill a player of their choice.
            
         - **Guard**
         
            As a guard, you can choose to protect a player once a night. The one you take guard will not be killed at that night.
            
     - **Bad people:**
     
       As Bad people, your goal is to kill or execute good people.
            
         - **Werewolves**
            
            Werewolves always take action together. On the first night, you will know your teammates, and you three have to choose a good person to kill each night. During the daytime, you have to pretend you are a good character, and try not to be found and executed. 
            

## Features List

- [x] **Random game sets or status**
   
   During the game, the logic behind NPC's action involves a random process. For instance, if all three werewolves are NPCs, they will randomly choose other players to kill at each night. But once the seer claims her identity, and the guard is still alive, the werewolves have to consider whether their attack will be guarded. Therefore, the choices will be given different weights, but the decision will still be made based on random process. 

- [x] **Data structure for storing game status**

   We will use data structures to store the game status, such as arrays, variables, structure, etc. For example, two structures "Game" and "Player" were implemented in the program for storage of player status and game process. "Game" structure can store the parameters and variable needed for the game process. For example, all the players still alive will be stored in an array under "Game" structure. This array will be updated at the end of the night and at the end of the daytime, then the system will carry out checking function on this array to see if the game is set or not. "Player" structure can record single player status, like life, role, vote, etc. This is useful to determine each player's action.

- [x] **Dynamic Memory Management**
  - During the alternating days and nights, variables containing texts and commands from both players and computers will be cleared and reused instead of redeclaring new ones, so as to lessen memory wastage.
  - Also, since we apply randomness during the whole gaming process, lists insertions and deletions will be executed dynamically.

- [x] **File Input/Output**
  - One of the most attractive parts of our game is the inference through clues and texts provided by the system and other players (PCs). Therefore, we require systematic language/text packages for the program to read and write so as to process or record the game.
  
- [x] **Program Codes in Multiple Files**
  - As our game is quite a complex one, we need .h to systematically declare functions and some variables we need throughout the whole program.
  - We plan to separate our debating functions into several particular .cpp in order to make the main.cpp clear for running the main game process.
  - Considering situations a character under a player or a PC controls can be quite different, we need similar but different files to achieve this and do our best to let the PC players perform their logic.
       
      
         
     
    
     
       

   
   
