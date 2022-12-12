#include "Engine/include/2D/2D.h"
#include "include/images.h"


void initialize();
void initializeGameObjects();
void update();
void draw();
void GameOver();
void GameMenu();
int DifficulityMenu();
void game();
void LoadGame();
void PlayIntro();

Box Enemy,Enemy1;
Image HealthKit;
Image Enemy2;
Image Player,Bullet1,Bullet2;
Vector2i PlayerPos;
Vector2i EnemyPos;
Vector2i Enemy1Pos;
Vector2i Enemy2Pos;
Vector2i MedikitPos;
int col = 0;
int Speed = 5;
int life = 3;
int dtime = 0,ftime = 60,seconds = 0,ltime = 0;
int fire = 0;
int x1,y1;
int x2,y2;
int BulletSpeed = 8;
float EnemySpeed = 1.5;
int Score = 0;
int PlayerDamage = 2;
int EnemyHealth =  3;
int Enemy1Health = 3;
int Enemy2Health = 3;
int SpawnRate = 250;
int EnemyRandomPosition;
int EnemyRandomPosition1;
int isr = 0,isb = 1;
int EnemyRandomPosition2;
int MedikitDistance = 4000;
int dificullity = 0;
int LoadingDelay = 250;


unsigned long*  soundData[5];
int             TempData[5];

int main(){initialize();PlayIntro();}

void game(int dm)
{

    LoadGame();
    TempData[1] = 255;
    while(1)
    {
        FntPrint("Score:%d\n\n",Score);
        FntPrint("Life:%d\n\n",life);
        FntPrint("Time:%d\n\n",seconds);
        FntPrint("Save our world");

        clearDisplay();
        update();
        draw();
        display();
    }


}




void initialize()
{
    initializeMemory();
    initializeScreen();
    initializeFont();
    initializePad();
    initializeVideo();
    setScreenMode(PAL);
}



void update()
{
    padUpdate();


    MedikitPos.y++;

    setScreenBackgroundColor(TempData[3],TempData[4],TempData[1]);
        if(isb){TempData[1] -= 2;}
        if(TempData[1] < 1)
        {
            isb = 0;
            isr = 1;
        }
        if(isr){TempData[1] += 2;}
        if(TempData[1] > 199){
            isb = 1;
            isr = 0;
        }

        if(TempData[3] > 1){TempData[3] -= 2;}


    EnemyPos.y  += EnemySpeed;
    Enemy1Pos.y += EnemySpeed;
    Enemy2Pos.y += EnemySpeed;

    x1 = PlayerPos.x + 22;
    x2 = PlayerPos.x + 48;

    Player = moveImage(Player,PlayerPos.x,PlayerPos.y);
    Bullet1 = moveImage(Bullet1,x1,y1);
    Bullet2 = moveImage(Bullet1,x2,y2);

    ltime++;

    HealthKit = moveImage(HealthKit,MedikitPos.x,MedikitPos.y);

    if(ltime > ftime)
    {
        ftime = ltime + 60;
        seconds++;
    }
    if(padCheck(Pad1Left)&& PlayerPos.x > -20)
    {
        PlayerPos.x -= Speed;
    }

    if(padCheck(Pad1Right) && PlayerPos.x < 257)
    {
        PlayerPos.x += Speed;
    }

    if(padCheck(Pad1Cross) || padCheck(Pad1L1) && !fire)
    {
        fire = 1;
        audioPlay(SPU_00CH);
    }

    if(fire == 0)
    {
        y1 = 200;
        y2 = 200;
    }

    if(y1 < -40)
    {
        fire = 0;
    }


    if(TempData[4] > 1){
        TempData[4] -= 2;
    }

    if(fire == 1)
    {
        y1 -= BulletSpeed;
        y2 -= BulletSpeed;
    }

    if(EnemyPos.y > 240)
    {
        audioPlay(SPU_03CH);
        life--;
       Enemy2Pos.x = GetRandomInteger(SpawnRate);
       Enemy2Pos.y = 0;
       Enemy1Pos.x = GetRandomInteger(SpawnRate);
       Enemy1Pos.y = 0;
       EnemyPos.x = GetRandomInteger(SpawnRate);
       EnemyPos.y = 0;
       TempData[3] = 255;
       TempData[1] = 0;
       TempData[4] = 0;
    }

    if(Enemy1Pos.y > 240)
    {
        audioPlay(SPU_03CH);
        life--;
       Enemy2Pos.x = GetRandomInteger(SpawnRate);
       Enemy2Pos.y = 0;
       Enemy1Pos.x = GetRandomInteger(SpawnRate);
       Enemy1Pos.y = 0;
       EnemyPos.x = GetRandomInteger(SpawnRate);
       EnemyPos.y = 0;
       TempData[3] = 255;
       TempData[1] = 0;
       TempData[4] = 0;
    }

    if(Enemy2Pos.y > 240)
    {
        audioPlay(SPU_03CH);
        life--;
       Enemy2Pos.x = GetRandomInteger(SpawnRate);
       Enemy2Pos.y = 0;
       Enemy1Pos.x = GetRandomInteger(SpawnRate);
       Enemy1Pos.y = 0;
       EnemyPos.x = GetRandomInteger(SpawnRate);
       EnemyPos.y = 0;
       TempData[3] = 255;
       TempData[1] = 0;
       TempData[4] = 0;
    }



    if(CheckBoxCollision(x1,y1,Bullet1.sprite.h,Bullet1.sprite.w,EnemyPos.x,EnemyPos.y,32,32) && fire)
    {
        EnemyHealth -= PlayerDamage;
    }

    if(CheckBoxCollision(x2,y2,Bullet2.sprite.h,Bullet2.sprite.w,EnemyPos.x,EnemyPos.y,32,32) && fire){
        EnemyHealth -= PlayerDamage;
    }



    if(CheckBoxCollision(x1,y1,Bullet1.sprite.h,Bullet1.sprite.w,Enemy1Pos.x,Enemy1Pos.y,32,32) && fire)
    {
        Enemy1Health -= PlayerDamage;
    }
    if(CheckBoxCollision(x2,y2,Bullet2.sprite.h,Bullet2.sprite.w,Enemy1Pos.x,Enemy1Pos.y,32,32) && fire)
    {
        Enemy1Health -= PlayerDamage;
    }

    if(CheckBoxCollision(x1,y1,Bullet2.sprite.h,Bullet2.sprite.w,Enemy2Pos.x,Enemy2Pos.y,Enemy2.sprite.h,Enemy2.sprite.w) && fire)
    {
        Enemy2Health -= PlayerDamage;
    }

    if(CheckBoxCollision(x2,y2,Bullet2.sprite.h,Bullet2.sprite.w,Enemy1Pos.x,Enemy1Pos.y,32,32) && fire)
    {
        Enemy2Health -= PlayerDamage;
    }



    if(CheckBoxCollision(PlayerPos.x,PlayerPos.y,Player.sprite.h,Player.sprite.w,MedikitPos.x,MedikitPos.y,HealthKit.sprite.h,HealthKit.sprite.w))
    {
        audioPlay(SPU_02CH);
        life = 3;
        MedikitPos.y = -2000;
        MedikitPos.x = GetRandomInteger(SpawnRate);
        TempData[4] = 255;
    }







    if(EnemyHealth < 1)
    {
        Score++;
        EnemyPos.x = GetRandomInteger(SpawnRate);
        EnemyPos.y = -80;
        EnemyHealth = 3;
    }

    if(Enemy1Health < 1)
    {
        Score++;
        Enemy1Pos.x = GetRandomInteger(SpawnRate);
        Enemy1Pos.y = -80;
        Enemy1Health = 3;
    }

    if(Enemy2Health < 1)
    {
        Score++;
        Enemy2Pos.x = GetRandomInteger(SpawnRate);
        Enemy2Pos.y = -80;
        Enemy2Health = 3;
    }

    Enemy = moveBox(Enemy,EnemyPos.x,EnemyPos.y);
    Enemy1 = moveBox(Enemy1,Enemy1Pos.x,Enemy1Pos.y);
    Enemy2 = moveImage(Enemy2,Enemy2Pos.x,Enemy2Pos.y);


    if(life < 1)
    {
     life = 3;
     GameOver();
    }


}




void initializeGameObjects()
{


    EnemyRandomPosition = GetRandomInteger(SpawnRate);
    EnemyRandomPosition1 = GetRandomInteger(SpawnRate);
    EnemyRandomPosition2 = GetRandomInteger(SpawnRate);

    if(dificullity == 1){EnemySpeed = 1;}
    if(dificullity == 2){EnemySpeed = 1.5;}
    if(dificullity == 3){EnemySpeed = 2;}

    PlayerPos = createVector2i(SCREEN_WIDTH / 2 - 40,185);
    Player = createImage(img_plain);
    Bullet1 = createImage(img_bullet);
    Bullet2 = createImage(img_bullet);
    Enemy = createBox(createPolygonColor(255,0,0),32,32,64,64);
    Enemy1 = createBox(createPolygonColor(255,0,0),32,32,64,64);
    Enemy2 = createImage(img_crash);
    HealthKit = createImage(img_healthkit);

    TempData[3] = 0;
    TempData[4] = 0;
    Enemy1Pos = createVector2i(EnemyRandomPosition,-100);
    Enemy2Pos = createVector2i(EnemyRandomPosition2,-100);
    EnemyPos  = createVector2i(EnemyRandomPosition1,-100);
    MedikitPos= createVector2i(GetRandomInteger(SpawnRate),-2000);

    y2 = 200;
    y1 = 200;


    cd_open();
    cd_read_file("FIRE.VAG",&soundData[0]);
    cd_read_file("LOSE.VAG",&soundData[1]);
    cd_read_file("HPUP.VAG",&soundData[2]);
    cd_read_file("DMG.VAG" ,&soundData[3]);
    cd_close();

    audioInit();
    audioTransferVagToSPU(soundData[0],SECTOR * 13, SPU_00CH);
    audioTransferVagToSPU(soundData[1],SECTOR * 71, SPU_01CH);
    audioTransferVagToSPU(soundData[2],SECTOR * 23, SPU_02CH);
    audioTransferVagToSPU(soundData[3],SECTOR *  8, SPU_03CH);
}






void draw()
{

    drawImage(Player);

    drawBox(Enemy);
    drawBox(Enemy1);
    drawImage(Enemy2);
    drawImage(HealthKit);

    if(fire)
    {
        drawImage(Bullet1);
        drawImage(Bullet2);
    }
}





void GameOver(){

    audioPlay(SPU_01CH);
    TempData[0] = 0;
    setScreenBackgroundColor(0,0,0);
while(1){
        if(TempData[0] < 255){ TempData[0]++;}
    setScreenBackgroundColor(TempData[0],0,0);

    FntPrint("\t\t\t Game Over");
    FntPrint("\n\n\n\t  Oh no the world is destroyed !!");
    FntPrint("\n\n\n\t\t\tYour Score:%d",Score);
    FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n   \tPress start to try again");
    Score = 0;
    life = 3;
    padUpdate();
    if(padCheck(Pad1Start)){dificullity = 0;GameMenu();}

    clearDisplay();
    display();
}
}


void GameMenu(){
    int R = 0,G = 0,B = 0;int TEMP = 0;

while(1){
        padUpdate();
        if(R < 255 && !TEMP){R += 2;}
        else{TEMP = 1;}
        if(TEMP){R -= 2;}
        if(R < 1){TEMP = 0;}

        setScreenBackgroundColor(R,G,B);
        FntPrint("\t\t\tSave the Earth");
        FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t  Press Start");

        if(padCheck(Pad1Start) && dificullity == 0){
            clearDisplay();
            dificullity = DifficulityMenu();
        }
        if(dificullity == 1){game(1);}
        if(dificullity == 2){game(2);}
        if(dificullity == 3){game(3);}



    clearDisplay();
    display();
}
}





int DifficulityMenu(){
int huhu = 0;


while(1){
        if(huhu < 120){huhu += 2;}
    setScreenBackgroundColor(0,huhu,0);
    FntPrint("\t\t    Select Difficulity\n----------------------------------------\n\n");
    FntPrint("\n\n\n\n\n\n\t\t\tCross - Easy");
    FntPrint("\n\n\n\n\n\n\t\t\tTriangle - Medium");
    FntPrint("\n\n\n\n\n\n\t\t\tCircle - Hard");
    padUpdate();
    if(padCheck(Pad1Cross)){return 1;}
    if(padCheck(Pad1Triangle)){return 2;}
    if(padCheck(Pad1Circle)){return 3;}


    clearDisplay();
    display();
}

}


void LoadGame(){
    int tyutyu = 0;
    int hug = 1;
    int g = 0;
    int loadte = 0;
    setScreenBackgroundColor(0,0,0);
while(1){
    if(hug > 50 && !g){initializeGameObjects();g = 1;}
    if(hug < 51){hug++;}

    loadte += 3;
    tyutyu++;
    if(tyutyu > LoadingDelay){return;}


        if(loadte < 70){
        FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tLoading.");
        }
        if(loadte > 69 && loadte < 130){
          FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tLoading..");
        }
        if(loadte > 130){
            FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tLoading...");
        }
clearDisplay();
display();
}
}


void PlayIntro(){
    STRFILE Intro[] = {"\\INTRO.STR;1", 320, 240,73};
    PlayStr(320, 240, 0, 0, &Intro[0]) == 0;
    clearDisplay();
    clearVRAM();
    initialize();
    GameMenu();
}





