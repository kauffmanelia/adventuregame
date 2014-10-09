//
//  main.c
//  adventuregame
//
//  Created by Elia Kauffman on 2014-10-08.
//  Copyright (c) 2014 Elia Kauffman. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define null NULL

const int maze_x = 4;
const int maze_y = 4;
const char upstring[] = "go north\n";
const char downstring[] = "go south\n";
const char leftstring[] = "go east\n";
const char rightstring[] = "go west\n";
const char dennisstring[] = "go Dennis\n";
const char dennisstring2[] = "go dennis\n";
const char amuletstring[] = "get amulet\n";
const char yeamuletstring[] = "get ye amulet\n";
const char flaskstring[] = "get ye flask\n";
const char describegrue[] = "describe grue\n";
const char describeamulet[] = "describe amulet\n";
const char quitstring[] = "quit\n";

const int numofcommands = 12;
const char * commandsarray[] = {upstring, downstring, leftstring, rightstring, dennisstring, dennisstring2, amuletstring, yeamuletstring, flaskstring, describegrue, describeamulet, quitstring};

const char magicword[] = "xyzzy\n";
const char nomagic[] = "A HOLLOW VOICE SAYS 'PLUGH'.\n";

const char desc1[] = "YOU ARE IN A MAZE OF TWISTY LITTLE PASSAGES, ALL DIFFERENT.\n";
const char desc2[] = "YOU ARE IN A LITTLE MAZE OF TWISTING PASSAGES, ALL DIFFERENT.\n";
const char desc3[] = "YOU ARE IN A MAZE OF TWISTING LITTLE PASSAGES, ALL DIFFERENT.\n";
const char desc4[] = "YOU ARE IN A LITTLE MAZE OF TWISTY PASSAGES, ALL DIFFERENT.\n";
const char desc5[] = "YOU ARE IN A TWISTING MAZE OF LITTLE PASSAGES, ALL DIFFERENT.\n";
const char desc6[] = "YOU ARE IN A TWISTING LITTLE MAZE OF PASSAGES, ALL DIFFERENT.\n";
const char desc7[] = "YOU ARE IN A TWISTY LITTLE MAZE OF PASSAGES, ALL DIFFERENT.\n";
const char desc8[] = "YOU ARE IN A TWISTY MAZE OF LITTLE PASSAGES, ALL DIFFERENT.\n";
const char desc9[] = "YOU ARE IN A LITTLE TWISTY MAZE OF PASSAGES, ALL DIFFERENT.\n";
const char desc10[] = "YOU ARE IN A MAZE OF LITTLE TWISTING PASSAGES, ALL DIFFERENT.\n";
const char desc11[] = "YOU ARE IN A MAZE OF LITTLE TWISTY PASSAGES, ALL DIFFERENT.\n";
const char descalike[] = "YOU ARE IN A MAZE OF TWISTY LITTLE PASSAGES, ALL ALIKE.\n";
const char * descarray[] = {desc1, desc2, desc3, desc4, desc5, desc6, desc7, desc8, desc9, desc10, desc11, descalike};

const char pitchblack[] = "It is pitch black. You are likely to be eaten by a GRUE.\n";
const char gruedescript[] = "The grue is a sinister, lurking presence in the dark places of the earth. Its favorite diet is adventurers, but its insatiable appetite is tempered by its fear of light. No grue has ever been seen by the light of day, and few have survived its fearsome jaws to tell the tale.\n";

const char amuletdescript[] = "This mysterious talisman is the object of your quest. It is said to possess powers which mere mortals can scarcely comprehend, let alone utilize. The gods will grant the gift of immortality to the adventurer who can deliver it from the depths of Moloch's Sanctum and offer it on the appropriate high altar on the Astral Plane.\n";
const char writestring[] = "write";

const char magicwriting[] = "MAGIC WORD XYZZY\n";

const char startdesc[] = "YOU ARE STANDING AT THE END OF A ROAD BEFORE A SMALL BRICK BUILDING. AROUND YOU IS A FOREST. A SMALL STREAM FLOWS OUT OF THE BUILDING AND DOWN A GULLY.\n";

const char mirrorcanyon[] = "YOU ARE IN A NORTH/SOUTH CANYON ABOUT 25 FEET ACROSS. THE FLOOR IS COVERED BY WHITE MIST SEEPING IN FROM THE NORTH. THE WALLS EXTEND UPWARD FOR WELL OVER 100 FEET. SUSPENDED FROM SOME UNSEEN POINT FAR ABOVE YOU, AN ENORMOUS TWO-SIDED MIRROR IS HANGING PARALLEL TO AND MIDWAY BETWEEN THE CANYON WALLS. (THE MIRROR IS OBVIOUSLY PROVIDED FOR THE USE OF THE DWARVES, WHO AS YOU KNOW, ARE EXTREMELY VAIN.) A SMALL WINDOW CAN BE SEEN IN EITHER WALL, SOME FIFTY FEET UP.\n";

const char view[] = "YOU ARE ON THE EDGE OF A BREATH-TAKING VIEW. FAR BELOW YOU IS AN ACTIVE VOLCANO, FROM WHICH GREAT GOUTS OF MOLTEN LAVA COME SURGING OUT, CASCADING BACK DOWN INTO THE DEPTHS. THE GLOWING ROCK FILLS THE FARTHEST REACHES OF THE CAVERN WITH A BLOOD-RED GLARE, GIVING EVERY- THING AN EERIE, MACABRE APPEARANCE. THE AIR IS FILLED WITH FLICKERING SPARKS OF ASH AND A HEAVY SMELL OF BRIMSTONE. THE WALLS ARE HOT TO THE TOUCH, AND THE THUNDERING OF THE VOLCANO DROWNS OUT ALL OTHER SOUNDS. EMBEDDED IN THE JAGGED ROOF FAR OVERHEAD ARE MYRIAD TWISTED FORMATIONS COMPOSED OF PURE WHITE ALABASTER, WHICH SCATTER THE MURKY LIGHT INTO SINISTER APPARITIONS UPON THE WALLS. TO ONE SIDE IS A DEEP GORGE, FILLED WITH A BIZARRE CHAOS OF TORTURED ROCK WHICH SEEMS TO HAVE BEEN CRAFTED BY THE DEVIL HIMSELF. AN IMMENSE RIVER OF FIRE CRASHES OUT FROM THE DEPTHS OF THE VOLCANO, BURNS ITS WAY THROUGH THE GORGE, AND PLUMMETS INTO A BOTTOMLESS PIT FAR OFF TO YOUR LEFT. TO THE RIGHT, AN IMMENSE GEYSER OF BLISTERING STEAM ERUPTS CONTINUOUSLY FROM A BARREN ISLAND IN THE CENTER OF A SULFUROUS LAKE, WHICH BUBBLES OMINOUSLY. THE FAR RIGHT WALL IS AFLAME WITH AN INCANDESCENCE OF ITS OWN, WHICH LENDS AN ADDITIONAL INFERNAL SPLENDOR TO THE ALREADY HELLISH SCENE.\n";

enum roomstate{
    cube,
    treasure,
    none
};

typedef struct room room;

typedef struct character character;

struct room{
    enum roomstate state;
    int x;
    int y;
    room * uproom;
    room * downroom;
    room * leftroom;
    room * rightroom;
    char writing[20];
    char desc[65];
    char * specialdesc;
    bool ismagic;
    bool isdark;
};

struct character{
    int health;
    room * currentroom;
    bool hasAmulet;
};

bool isRoomThere(room * aroom){
    if(aroom == null) return false;
    else return true;
}

bool canMove(room * aroom){
    bool moveup = isRoomThere(aroom->uproom);
    bool movedown = isRoomThere(aroom->downroom);
    bool moveleft = isRoomThere(aroom->leftroom);
    bool moveright = isRoomThere(aroom->rightroom);
    return (moveup || movedown || moveleft || moveright);
}

bool isWinnable(room maze[maze_x][maze_y]){
    room * amuletroom = null;
    for(int i=0;i<maze_x;i++){
        for(int j=0;j<maze_y;j++){
            if(maze[i][j].state == treasure){
                amuletroom = &maze[i][j];
                break;
            }
        }
        if(amuletroom != null) break;
    }
    
    return (canMove(amuletroom));
}

void playerstatus(character * player){
    printf("\nYou have %d health.\n", player->health);
    if(player->health == 1){
        printf("Blue valkyrie! You are about to die.\n");
    }
    printf("You are currently in room %dx%d.\n", player->currentroom->x, player->currentroom->y);
    printf("%s", player->currentroom->desc);
    if(player->currentroom->specialdesc != null) printf("%s", player->currentroom->specialdesc);
    if((!player->currentroom->writing[0] == '\0')){
        printf("Someone has scrawled a message in chalk on the wall: %s", player->currentroom->writing);
    }
    if(player->currentroom->state == treasure){
        printf("You see an AMULET.\n");
    }
    if(player->currentroom->state == cube){
        printf("You are attacked by a GELATINOUS CUBE. Aaaah!\nYou lose a point of health.\n");
    }
    printf("Obvious exits are: ");
    if(isRoomThere(player->currentroom->uproom)){
        printf("NORTH, ");
    }
    if(isRoomThere(player->currentroom->downroom)){
        printf("SOUTH, ");
    }
    if(isRoomThere(player->currentroom->leftroom)){
        printf("EAST, ");
    }
    if(isRoomThere(player->currentroom->rightroom)){
        printf("WEST, ");
    }
    printf("and DENNIS.\n");
}

void randommazer(room maze[maze_x][maze_y]){
    int randommaze;
    for(int i=0;i<maze_x;i++){
        for(int j=0;j<maze_y;j++){
            randommaze = rand() % 8;
            if(maze[i][j].uproom != null){
                randommaze = rand() % 8;
                if(randommaze == 0){
                    maze[i][j].uproom = null;
                    maze[i][j-1].downroom = null;
                }
            }
            
            randommaze = rand() % 8;
            if(maze[i][j].downroom != null){
                randommaze = rand() % 8;
                if(randommaze == 0){
                    maze[i][j].downroom = null;
                    maze[i][j+1].uproom = null;
                }
            }
            
            randommaze = rand() % 8;
            if(maze[i][j].leftroom != null){
                randommaze = rand() % 8;
                if(randommaze == 0){
                    maze[i][j].leftroom = null;
                    maze[i-1][j].rightroom = null;
                }
            }
            
            randommaze = rand() % 8;
            if(maze[i][j].rightroom != null){
                randommaze = rand() % 8;
                if(randommaze == 0){
                    maze[i][j].rightroom = null;
                    maze[i+1][j].leftroom = null;
                }
            }
        }
    }
}

void mazedescs(room maze[maze_x][maze_y]){
    maze[0][0].specialdesc = malloc(sizeof(startdesc));
    strcpy(maze[0][0].specialdesc, startdesc);
    
    int mirrorcanyonx = rand() % maze_x;
    int mirrorcanyony = rand() % maze_y;
    while(maze[mirrorcanyonx][mirrorcanyony].specialdesc != null){
        mirrorcanyonx = rand() % maze_x;
        mirrorcanyony = rand() % maze_y;
    }
    
    maze[mirrorcanyonx][mirrorcanyony].specialdesc = malloc(sizeof(mirrorcanyon));
    strcpy(maze[mirrorcanyonx][mirrorcanyony].specialdesc, mirrorcanyon);
    
    int viewx = rand() % maze_x;
    int viewy = rand() % maze_y;
    while(maze[viewx][viewy].specialdesc != null){
        viewx = rand() % maze_x;
        viewy = rand() % maze_y;
    } // Don't want to overwrite mirrorcanyon with view, so keep randomizing until they're different.
    maze[viewx][viewy].specialdesc = malloc(sizeof(view));
    strcpy(maze[viewx][viewy].specialdesc, view);
    
    int darkx;
    int darky;
    for(int i=0;i<5;i++){
        darkx = rand() % maze_x;
        darky = rand() % maze_y;
        while(maze[darkx][darky].specialdesc != null){
            darkx = rand() % maze_x;
            darky = rand() % maze_y;
        }
        maze[darkx][darky].specialdesc = malloc(sizeof(pitchblack));
        strcpy(maze[darkx][darky].specialdesc, pitchblack);
        maze[darkx][darky].isdark = true;
    }
    
    // Special descriptions that come before this block aren't supposed to have regular descriptions.
    int randomdesc;
    for(int i=0;i<maze_x;i++){
        for(int j=0;j<maze_y;j++){
            randomdesc = rand() % 20;
            if(randomdesc > 11) randomdesc = 11; // Weighting the random generation towards descalike
            if(maze[i][j].specialdesc == null){
                strcpy(maze[i][j].desc, descarray[randomdesc]);
            }
        }
    }
    
    
    int magicplace1x = rand() % maze_x;
    int magicplace1y = rand() % maze_y;
    while(maze[magicplace1x][magicplace1y].specialdesc != null){
        magicplace1x = rand() % maze_x;
        magicplace1y = rand() % maze_y;
    }
    maze[magicplace1x][magicplace1y].ismagic = true;
    strcpy(maze[magicplace1x][magicplace1y].writing, magicwriting);
    
    int magicplace2x = rand() % maze_x;
    int magicplace2y = rand() % maze_y;
    while(maze[magicplace2x][magicplace2y].specialdesc != null){
        magicplace2x = rand() % maze_x;
        magicplace2y = rand() % maze_y;
    }
    maze[magicplace2x][magicplace2y].ismagic = true;
    strcpy(maze[magicplace2x][magicplace2y].writing, magicwriting);
    
}

void mazebuilder(room maze[maze_x][maze_y]){
    room * currentroom;
    for(int i=0;i<maze_x;i++){
        for(int j=0;j<maze_y;j++){
            currentroom = &maze[i][j];
            currentroom->state = none;
            currentroom->x = i;
            currentroom->y = j;
            currentroom->specialdesc = null;
            currentroom->ismagic = false;
            currentroom->desc[0] = '\0';
            currentroom->writing[0] = '\0';
            currentroom->isdark = false;
            if(i == 0){
                currentroom->leftroom = null;
            }
            else{
                currentroom->leftroom = &maze[i-1][j];
            }
            if(i == 3){
                currentroom->rightroom = null;
            }
            else{
                currentroom->rightroom = &maze[i+1][j];
            }
            if(j == 0){
                currentroom->uproom = null;
            }
            else{
                currentroom->uproom = &maze[i][j-1];
            }
            if(j == 3){
                currentroom->downroom = null;
            }
            else{
                currentroom->downroom = &maze[i][j+1];
            }
        }
    }
    randommazer(maze);
    mazedescs(maze);
    
    int treasurex = rand() % (maze_x);
    int treasurey = rand() % (maze_y);
    maze[treasurex][treasurey].state = treasure;
    
    int cubex = rand() % (maze_x);
    int cubey = rand() % (maze_y);
    maze[cubex][cubey].state = cube;
//    printf("Treasure at %d, %d\n", treasurex, treasurey);
//    printf("Cube at %d, %d\n", cubex, cubey);
}

bool movecharacter(character * player, room * targetroom){
    if(isRoomThere(targetroom)){
        player->currentroom = targetroom;
        return true;
    }
    else{
        return false;
    }
}

room * getmagicdestination(room maze[maze_x][maze_y], room * currentlocation){
    for(int i=0;i<maze_x;i++){
        for(int j=0;j<maze_y;j++){
            if((&maze[i][j] != currentlocation) && (maze[i][j].ismagic == true)){
                return &maze[i][j];
            }
        }
    }
    return null;
}

bool parser(room maze[maze_x][maze_y], char input[20], character * player){
    fgets(input, 20, stdin);
    printf("\n");
    if(strcmp(input, upstring) == 0){
        if(!(movecharacter(player, player->currentroom->uproom))){
            printf("You try to go north and walk into a wall. Ouch!\n");
        }
    }
    else if(strcmp(input, downstring) == 0){
        if(!(movecharacter(player, player->currentroom->downroom))){
            printf("You try to go south and walk into a wall. Ouch!\n");
        }
    }
    else if(strcmp(input, leftstring) == 0){
        if(!(movecharacter(player, player->currentroom->leftroom))){
            printf("You try to go east and walk into a wall. Ouch!\n");
        }
    }
    else if(strcmp(input, rightstring) == 0){
        if(!(movecharacter(player, player->currentroom->rightroom))){
            printf("You try to go west and walk into a wall. Ouch!\n");
        }
    }
    else if((strcmp(input, dennisstring) == 0) || (strcmp(input, dennisstring2) == 0)){
        printf("Who the heck is Dennis?\n");
    }
    else if(strcmp(input, amuletstring) == 0){
        if(player->currentroom->state == treasure){
            player->hasAmulet = true;
            printf("You got the Amulet!\n");
        }
        else{
            printf("There's no amulet there.\n");
        }
    }
    else if(strcmp(input, yeamuletstring) == 0){
        if(player->currentroom->state == treasure){
            player->hasAmulet = true;
            printf("You got ye amulet!\n");
        }
        else{
            printf("You can't get ye amulet!\n");
        }
    }
    else if(strcmp(input, flaskstring) == 0){
        printf("You can't get ye flask!\n");
    }
    else if(strncmp(input, writestring, 5) == 0){
        printf("You scrawl a message on the wall with some chalk.\n");
        strcpy(player->currentroom->writing, &(input[6]));
    }
    else if(strcmp(input, magicword) == 0){
        if(player->currentroom->ismagic != true){
            printf("%s", nomagic);
        }
        else{
            room * magicdestination = getmagicdestination(maze, player->currentroom);
            if(magicdestination != null){
                player->currentroom = magicdestination;
            }
            else{
                printf("Somehow there's no destination for the magic word.");
            }
        }
    }
    else if(strcmp(input, describegrue) == 0){
        printf("%s", gruedescript);
    }
    else if(strcmp(input, describeamulet) == 0){
        printf("%s", amuletdescript);
    }
    else if(strcmp(input, quitstring) == 0){
        return true;
    }
    else{
        printf("You wander aimlessly. In future, use lowercase, and try statements of the form 'go [direction]' or 'get [item]'.\nAdditionally, you can use 'write [text]' to scrawl something on the wall.\nYou can also use 'describe [subject]' on certain subjects or items.\n");
    }
    return false;
}

void cubemove(room maze[maze_x][maze_y]){
    room * cuberoom = null;
    for(int i=0;i<maze_x;i++){
        for(int j=0;j<maze_y;j++){
            if(maze[i][j].state == cube){
                cuberoom = &maze[i][j];
                break;
            }
        }
        if(cuberoom != null) break;
    }
    
    if(!canMove(cuberoom)){
        return;
    }
    
    bool moved = false;
    cuberoom->state = none;
    while(moved == false){
        int movedirection = rand() % 4;
        if(movedirection == 0){
            if(isRoomThere(cuberoom->uproom)){
                cuberoom->uproom->state = cube;
                cuberoom = cuberoom->uproom;
                moved = true;
            }
        }
        else if(movedirection == 1){
            if(isRoomThere(cuberoom->downroom)){
                cuberoom->downroom->state = cube;
                cuberoom = cuberoom->downroom;
                moved = true;
            }
        }
        else if(movedirection == 2){
            if(isRoomThere(cuberoom->rightroom)){
                cuberoom->rightroom->state = cube;
                cuberoom = cuberoom->rightroom;
                moved = true;
            }
        }
        else if(movedirection == 3){
            if(isRoomThere(cuberoom->leftroom)){
                cuberoom->leftroom->state = cube;
                cuberoom = cuberoom->leftroom;
                moved = true;
            }
        }
    }
//    printf("Cube is at %d, %d\n", cuberoom->x, cuberoom->y);
}

void playgame(room maze[maze_x][maze_y], character player){
    bool playagain;
    bool quitstring = false;
    bool canplayermove;
    bool amuletreachable;
    int darkcount = 0;
    do{
        mazebuilder(maze);
        amuletreachable = isWinnable(maze);
        player.health = 2;
        player.currentroom = &maze[0][0];
        canplayermove = canMove(player.currentroom);
        player.hasAmulet = false;
        char input[20];
        printf("Accepted commands:\n");
        for(int i=0;i<numofcommands;i++){
            printf("%s", commandsarray[i]);
        }
        printf("\nYe find yeself in yon dungeon in search of the legendary Amulet of Yendor. If you find this powerful artifact, you will be proclaimed as one of the most daring adventurers of all time.\n");
        playerstatus(&player);
        if(player.currentroom->state == cube){
            (player.health)--;
        }
        if(player.currentroom->isdark == true){
            if(darkcount < 2){
                darkcount++;
            }
        }
        while((player.health != 0) && (player.hasAmulet == false) && (darkcount < 2) && (canplayermove) && (amuletreachable)){
            printf("What wouldst thou deau?\n");
            quitstring = parser(maze, input, &player);
            if(quitstring){
                break;
            }
            if(!(player.currentroom->state == cube)){
                cubemove(maze);
            }
            playerstatus(&player);
            if(player.currentroom->state == cube){
                (player.health)--;
            }
            if(player.currentroom->isdark == true){
                if(darkcount < 2){
                    darkcount++;
                }
            }
            else if(player.currentroom->isdark == false){
                darkcount = 0;
            }
        }
        if(quitstring){
            printf("You abandon your quest for the AMULET OF YENDOR. The world burns without its power.\nPlay again? ");
        }
        if(player.health == 0){
            printf("You have been fangoriously devoured by a gelatinous monster. Your legs are being digested.\nPlay again? ");
        }
        else if(player.hasAmulet == true){
            printf("You have found the Amulet of Yendor, and you escape the maze with it in your grasp! Hooray!\nPlay again? ");
        }
        else if(darkcount == 2){
            printf("Oh no! You walked directly into the slavering fangs of a lurking grue! You have died.\nPlay again? ");
        }
        else if((canplayermove == false) || (amuletreachable == false)){
            printf("The vagaries of the labyrinth make the AMULET unreachable! Unfortunately, you have failed before you began.\nPlay again? ");
        }
        fgets(input, 20, stdin);
        if(strcmp(input, "yes\n") == 0) playagain = true;
        else playagain = false;
    }while(playagain);
}

int main(void){
    srand(time(null));
    room maze[maze_x][maze_y];
    character player;
    playgame(maze, player);
    return 0;
}









