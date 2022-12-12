#include "include/ALL.H"

int GameOver(){
	initializeScreen();
	initializeFont();
	while(1){
		FntPrint("\tGameOber");
		
		clearDisplay();
		display();
	}
	
}