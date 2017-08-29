#include <oslib/oslib.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspaudio.h>
#include <pspaudiolib.h>
#include <pspaudio_kernel.h>
#include <psprtc.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include <timeManager.h>

#include "grille.c"

#define printf pspDebugScreenPrintf

PSP_MODULE_INFO("SquarO PSP", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(12*1024);


// TWILIGHT ZONE! <do doo do doo>
/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
          sceKernelExitGame();
          return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
          int cbid;

          cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
          sceKernelRegisterExitCallback(cbid);

          sceKernelSleepThreadCB();

          return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
          int thid = 0;

          thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
          if(thid >= 0) {
                    sceKernelStartThread(thid, 0, 0);
          }

          return thid;
}
// END OF TWILIGHT ZONE! <do doo do do> 


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Init OSLib:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int initOSLib(){
    oslInit(0);
    oslInitGfx(OSL_PF_8888, 1);
    oslInitAudio();
	oslInitAudioME(OSL_FMT_MP3);
    oslSetQuitOnLoadFailure(1);
    oslSetKeyAutorepeatInit(40);
    oslSetKeyAutorepeatInterval(10);
    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    int skip = 0;
	
	scePowerSetClockFrequency(333, 333, 166);
    initOSLib();
	oslIntraFontInit(INTRAFONT_CACHE_ALL | INTRAFONT_STRING_CP1252);
	
	OSL_FONT *pgfFont60n = oslLoadFontFile("flash0:/font/ltn0.pgf");
    oslIntraFontSetStyle(pgfFont60n, 0.60, RGBA(57,86,99,255), RGBA(117,139,150,0), INTRAFONT_ALIGN_CENTER);
	OSL_FONT *pgfFont60b = oslLoadFontFile("flash0:/font/ltn4.pgf");
    oslIntraFontSetStyle(pgfFont60b, 0.60, RGBA(57,86,99,255), RGBA(117,139,150,0), INTRAFONT_ALIGN_LEFT);
	OSL_FONT *pgfFont60 = oslLoadFontFile("flash0:/font/ltn0.pgf");
    oslIntraFontSetStyle(pgfFont60, 0.60, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_LEFT);
	OSL_FONT *pgfFont60r = oslLoadFontFile("flash0:/font/ltn0.pgf");
    oslIntraFontSetStyle(pgfFont60r, 0.60, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_RIGHT);
	OSL_FONT *pgfFont60c = oslLoadFontFile("flash0:/font/ltn0.pgf");
    oslIntraFontSetStyle(pgfFont60c, 0.60, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_CENTER);
	OSL_FONT *pgfFont70 = oslLoadFontFile("flash0:/font/ltn0.pgf");
    oslIntraFontSetStyle(pgfFont70, 0.70, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_CENTER);
	OSL_FONT *pgfFont70b = oslLoadFontFile("flash0:/font/ltn4.pgf");
    oslIntraFontSetStyle(pgfFont70b, 0.70, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_CENTER);
	OSL_FONT *pgfFont75 = oslLoadFontFile("flash0:/font/ltn0.pgf");
    oslIntraFontSetStyle(pgfFont75, 0.75, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_LEFT);
	OSL_FONT *pgfFont75c = oslLoadFontFile("flash0:/font/ltn0.pgf");
    oslIntraFontSetStyle(pgfFont75c, 0.85, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_CENTER);
	OSL_FONT *pgfFont125 = oslLoadFontFile("flash0:/font/ltn0.pgf");
    oslIntraFontSetStyle(pgfFont125, 1.25, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_CENTER);
    
	
	OSL_IMAGE *bg, *gridBg, *squarologo, *squarologopetit, *fondmp3, *cercle_plein, *cercle_plein_active, *cercle_vide, *cercle_vide_active, *cercle_demi, *cercle_demi_active, *cercle_marque, *cercle_marque_active, *cercle_plein_grille, *cercle_plein_active_grille, *cercle_vide_grille, *cercle_vide_active_grille, *active0, *unactive0, *active1, *unactive1, *active2, *unactive2, *active3, *unactive3, *active4, *unactive4, *active5, *unactive5, *active6, *unactive6, *active7, *unactive7, *active8, *unactive8, *rules, *tropheedefaut, *troph1m, *troph2m, *troph3m, *troph4m, *troph5m, *troph6m, *troph7m, *troph8m, *troph9m, *troph10m, *troph11m, *troph12m, *troph13m, *troph14m, *troph15m, *troph16m, *troph17m, *troph18m, *curseurtrophee, *fondtrophee;
	
	bg = oslLoadImageFilePNG ("data/bg.png", OSL_IN_RAM,OSL_PF_8888);
	gridBg = oslLoadImageFilePNG ("data/grid-background.png", OSL_IN_RAM,OSL_PF_8888);
	squarologo = oslLoadImageFilePNG ("data/squarologo.png", OSL_IN_RAM,OSL_PF_8888);
	squarologopetit = oslLoadImageFilePNG ("data/squarologopetit.png", OSL_IN_RAM,OSL_PF_8888);
	fondmp3 = oslLoadImageFilePNG ("data/fondmp3.png", OSL_IN_RAM,OSL_PF_8888);
	cercle_plein = oslLoadImageFilePNG ("data/cercle_plein.png", OSL_IN_RAM,OSL_PF_8888);
	cercle_plein_active = oslLoadImageFilePNG ("data/cercle_plein_active.png", OSL_IN_RAM,OSL_PF_8888);
	cercle_vide = oslLoadImageFilePNG ("data/cercle_vide.png", OSL_IN_RAM,OSL_PF_8888);
	cercle_vide_active = oslLoadImageFilePNG ("data/cercle_vide_active.png", OSL_IN_RAM,OSL_PF_8888);
	cercle_demi = oslLoadImageFilePNG ("data/cercle_demi.png", OSL_IN_RAM,OSL_PF_8888);
	cercle_demi_active = oslLoadImageFilePNG ("data/cercle_demi_active.png", OSL_IN_RAM,OSL_PF_8888);
	cercle_marque = oslLoadImageFilePNG ("data/cercle_marque.png", OSL_IN_RAM,OSL_PF_8888);
	cercle_marque_active = oslLoadImageFilePNG ("data/cercle_marque_active.png", OSL_IN_RAM,OSL_PF_8888);
	cercle_plein_grille = oslLoadImageFilePNG ("data/cercle_plein_grille.png", OSL_IN_RAM,OSL_PF_8888);
	cercle_plein_active_grille = oslLoadImageFilePNG ("data/cercle_plein_active_grille.png", OSL_IN_RAM,OSL_PF_8888);
	cercle_vide_grille = oslLoadImageFilePNG ("data/cercle_vide_grille.png", OSL_IN_RAM,OSL_PF_8888);
	cercle_vide_active_grille = oslLoadImageFilePNG ("data/cercle_vide_active_grille.png", OSL_IN_RAM,OSL_PF_8888);
	active0 = oslLoadImageFilePNG ("data/active_0.png", OSL_IN_RAM,OSL_PF_8888);
	unactive0 = oslLoadImageFilePNG ("data/unactive_0.png", OSL_IN_RAM,OSL_PF_8888);
	active1 = oslLoadImageFilePNG ("data/active_1.png", OSL_IN_RAM,OSL_PF_8888);
	unactive1 = oslLoadImageFilePNG ("data/unactive_1.png", OSL_IN_RAM,OSL_PF_8888);
	active2 = oslLoadImageFilePNG ("data/active_2.png", OSL_IN_RAM,OSL_PF_8888);
	unactive2 = oslLoadImageFilePNG ("data/unactive_2.png", OSL_IN_RAM,OSL_PF_8888);
	active3 = oslLoadImageFilePNG ("data/active_3.png", OSL_IN_RAM,OSL_PF_8888);
	unactive3 = oslLoadImageFilePNG ("data/unactive_3.png", OSL_IN_RAM,OSL_PF_8888);
	active4 = oslLoadImageFilePNG ("data/active_4.png", OSL_IN_RAM,OSL_PF_8888);
	unactive4 = oslLoadImageFilePNG ("data/unactive_4.png", OSL_IN_RAM,OSL_PF_8888);
	active5 = oslLoadImageFilePNG ("data/active_5.png", OSL_IN_RAM,OSL_PF_8888);
	unactive5 = oslLoadImageFilePNG ("data/unactive_5.png", OSL_IN_RAM,OSL_PF_8888);
	active6 = oslLoadImageFilePNG ("data/active_6.png", OSL_IN_RAM,OSL_PF_8888);
	unactive6 = oslLoadImageFilePNG ("data/unactive_6.png", OSL_IN_RAM,OSL_PF_8888);
	active7 = oslLoadImageFilePNG ("data/active_7.png", OSL_IN_RAM,OSL_PF_8888);
	unactive7 = oslLoadImageFilePNG ("data/unactive_7.png", OSL_IN_RAM,OSL_PF_8888);
	active8 = oslLoadImageFilePNG ("data/active_8.png", OSL_IN_RAM,OSL_PF_8888);
	unactive8 = oslLoadImageFilePNG ("data/unactive_8.png", OSL_IN_RAM,OSL_PF_8888);
	rules = oslLoadImageFilePNG ("data/rules.png", OSL_IN_RAM,OSL_PF_8888);
	troph1m = oslLoadImageFilePNG ("data/trophee1m.png", OSL_IN_RAM,OSL_PF_8888);
	troph2m = oslLoadImageFilePNG ("data/trophee2m.png", OSL_IN_RAM,OSL_PF_8888);
	troph3m = oslLoadImageFilePNG ("data/trophee3m.png", OSL_IN_RAM,OSL_PF_8888);
	troph4m = oslLoadImageFilePNG ("data/trophee4m.png", OSL_IN_RAM,OSL_PF_8888);
	troph5m = oslLoadImageFilePNG ("data/trophee5m.png", OSL_IN_RAM,OSL_PF_8888);
	troph6m = oslLoadImageFilePNG ("data/trophee6m.png", OSL_IN_RAM,OSL_PF_8888);
	troph7m = oslLoadImageFilePNG ("data/trophee7m.png", OSL_IN_RAM,OSL_PF_8888);
	troph8m = oslLoadImageFilePNG ("data/trophee8m.png", OSL_IN_RAM,OSL_PF_8888);
	troph9m = oslLoadImageFilePNG ("data/trophee9m.png", OSL_IN_RAM,OSL_PF_8888);
	troph10m = oslLoadImageFilePNG ("data/trophee10m.png", OSL_IN_RAM,OSL_PF_8888);
	troph11m = oslLoadImageFilePNG ("data/trophee11m.png", OSL_IN_RAM,OSL_PF_8888);
	troph12m = oslLoadImageFilePNG ("data/trophee12m.png", OSL_IN_RAM,OSL_PF_8888);
	troph13m = oslLoadImageFilePNG ("data/trophee13m.png", OSL_IN_RAM,OSL_PF_8888);
	troph14m = oslLoadImageFilePNG ("data/trophee14m.png", OSL_IN_RAM,OSL_PF_8888);
	troph15m = oslLoadImageFilePNG ("data/trophee15m.png", OSL_IN_RAM,OSL_PF_8888);
	troph16m = oslLoadImageFilePNG ("data/trophee16m.png", OSL_IN_RAM,OSL_PF_8888);
	troph17m = oslLoadImageFilePNG ("data/trophee17m.png", OSL_IN_RAM,OSL_PF_8888);
	troph18m = oslLoadImageFilePNG ("data/trophee18m.png", OSL_IN_RAM,OSL_PF_8888);
	tropheedefaut = oslLoadImageFilePNG ("data/tropheedefaut.png", OSL_IN_RAM,OSL_PF_8888);
	curseurtrophee = oslLoadImageFilePNG ("data/curseurtrophee.png", OSL_IN_RAM,OSL_PF_8888);
	fondtrophee = oslLoadImageFilePNG ("data/fondtrophee.png", OSL_IN_RAM,OSL_PF_8888);
	
	int cerclePosXY[6][2];
	cerclePosXY[0][0] = 109;
	cerclePosXY[0][1] = 3;
	cerclePosXY[1][0] = 157;
	cerclePosXY[1][1] = 50;
	cerclePosXY[2][0] = 205;
	cerclePosXY[2][1] = 97;
	cerclePosXY[3][0] = 252;
	cerclePosXY[3][1] = 144;
	cerclePosXY[4][0] = 299;
	cerclePosXY[4][1] = 191;
	cerclePosXY[5][0] = 345;
	cerclePosXY[5][1] = 238;
	
	
	int chiffrePosXY[5][2];
	chiffrePosXY[0][0] = 129;
	chiffrePosXY[0][1] = 23;
	chiffrePosXY[1][0] = 177;
	chiffrePosXY[1][1] = 70;
	chiffrePosXY[2][0] = 225;
	chiffrePosXY[2][1] = 117;
	chiffrePosXY[3][0] = 272;
	chiffrePosXY[3][1] = 164;
	chiffrePosXY[4][0] = 319;
	chiffrePosXY[4][1] = 211;
	
	int i, j, k, x = 0;
	int etat = 0;
	//0: Menu - 1: Jeu - 2: Regles - 3:Credits 4: Quitter
	
	int niveau = 0;
	
	int premierLancement = 0;
	int langue = 0;
	int menuPos = 0;
	
	int casePos[2];
	casePos[0] = 0;
	casePos[1] = 0;
	
	
	int gameGrille[6][6];

	int grilleCourante = 0;
	int gameGrilleSoluce[6][6];
	
	int chiffreEnCours[25];	
	int chiffreDevine[25];
   
   
	OSL_SOUND *instru,*checksound,*unchecksound, *ping; 
  
	checksound = oslLoadSoundFileWAV("data/check.wav",OSL_FMT_NONE);
	unchecksound = oslLoadSoundFileWAV("data/uncheck.wav",OSL_FMT_NONE);
	ping = oslLoadSoundFileMP3("data/ping.mp3",OSL_FMT_STREAM);
   
	int posInstru = 0;
	int nbrMusic = 0;
	int activeMusic = 0;
	
	char playlist[200][1024];
	
	SceUID dir = sceIoDopen("ms0:/PSP/MUSIC/");
	struct SceIoDirent dirEnt;
	memset(&dirEnt, 0, sizeof(SceIoDirent));
	i=0;
	char tampon[255];
	while(sceIoDread(dir, &dirEnt) > 0){
		if (strstr(dirEnt.d_name,".mp3")!=NULL){
			sprintf(tampon,"ms0:/PSP/MUSIC/%s",dirEnt.d_name);
			//if(fopen(tampon,"r")){
				sprintf(playlist[i], "%s",dirEnt.d_name);
				if(i==0){
				instru = oslLoadSoundFileMP3(tampon,OSL_FMT_STREAM);
				}
				nbrMusic++;
				i++;
			//}
		}
	}
	sceIoDclose(dir);
	
	
	char ligne[500];
	
	int grilleComplete[400];
	FILE *fichierScore = fopen("data/grille","r");
	k = 0;
	if(fichierScore!=NULL){
		while(fgets(ligne,sizeof(ligne),fichierScore)){
			grilleComplete[k] = atoi(ligne); 
			k++;
		}
		fclose(fichierScore);
	}
	
	
	int posMenuOption = 0;
	int chiffresrouges = 1;
	int soncheck = 0;
	int effacerProgression = 0;
	int optionsPerso[2];
	FILE *fichierOption = fopen("data/option","r");
	k = 0;
	if(fichierOption!=NULL){
		while(fgets(ligne,sizeof(ligne),fichierOption)){
			optionsPerso[k] = atoi(ligne); 
			k++;
		}
		fclose(fichierOption);
		chiffresrouges = optionsPerso[0];
		soncheck = optionsPerso[1];
	}
	else{
	optionsPerso[0] = chiffresrouges;
	optionsPerso[1] = soncheck;
	}
	
	int recordenregistre = 0;
	int effacerRecord = 0;
	int recordsPerso[20];
	FILE *fichierRecord = fopen("data/record","r");
	k = 0;
	if(fichierRecord!=NULL){
		while(fgets(ligne,sizeof(ligne),fichierRecord)){
			recordsPerso[k] = atoi(ligne); 
			k++;
		}
		fclose(fichierRecord);
	}
	
	int afficheTrophee = 0;
	int effacerTrophee = 0;
	int tropheeTemps = 200;
	int nbrTropheeMontre = 0;
	int tropheeMontre[20];
	for(i=0;i<20;i++){
		tropheeMontre[i] = 0;
	}
	int posTrophee = 0;
	int tropheesPerso[20];
	FILE *fichierTrophee = fopen("data/trophee","r");
	k = 0;
	if(fichierTrophee!=NULL){
		while(fgets(ligne,sizeof(ligne),fichierTrophee)){
			tropheesPerso[k] = atoi(ligne); 
			k++;
		}
		fclose(fichierTrophee);
	}
	
	char titreTrophee[2][20][50] = {
		{"FAYOT",
		"ROUGE GORGE",
		"ASSISTÉ",
		"BONOBO",
		"RENARD FUTÉ",
		"SHÉRIF",
		"AVENTURIER",
		"PREMIER DE LA CLASSE",
		"TORTUE",
		"JOGGEUR",
		"F1",
		"SPEEDY GONZALES",
		"EXPLORATEUR",
		"HANNIBAL LECTOR",
		"GRAND MAITRE",
		"BARMAN",
		"EINSTEIN",
		"ALIEN"}
		,
		{"BEAN",
		"ROBIN REDBREAST",
		"SOS",
		"BONOBO",
		"FOX",
		"SHERIFF",
		"ADVENTURER",
		"FIRST OF THE CLASS",
		"TURTLE",
		"JOGGER",
		"F1",
		"SPEEDY GONZALES",
		"EXPLORER",
		"HANNIBAL LECTOR",
		"ZEN MASTER",
		"BARMAN",
		"EINSTEIN",
		"ALIEN"}
	};
	char labelTrophee[2][20][255] = {
		{"avoir lu les règles",
		"ne s'est pas aidé des ronds rouge",
		"s'est aidé des ronds rouges",
		"a réussi une grille facile",
		"a réussi une grille moyenne",
		"a réussi une grille difficile",
		"a réussi une grille evil",
		"a réussi une grille sans erreur",
		"a fini une grille en plus de 5min",
		"moins de 2 min dans chaque niveau",
		"moins de 1 min dans chaque niveau",
		"moins de 30 s dans chaque niveau",
		"a réussi 1 grille dans chaque niveau",
		"a réussi 10 grilles dans chaque niveau",
		"a réussi 50 grilles dans chaque niveau",
		"a réussi 100 grilles dans chaque niveau",
		"a réussi une grille difficile sans chiffres rouges et sans rond rouges",
		"a réussi une grille evil sans chiffres rouges et sans rond rouges"}
		,
		{"read the rules",
		"didn't use any red circles",
		"did use red circles",
		"finished an easy grid",
		"finished a medium grid",
		"finished a hard grid",
		"finished a evil grid",
		"finished a grid without mistake",
		"more than 5min to finish a grid",
		"finished each level in less than 2min",
		"finished each level in less than 1min",
		"finished each level in less than 30s",
		"finished 1 grid in each level",
		"finished 10 grid in each level",
		"finished 50 grid in each level",
		"finished 100 grid in each level",
		"finished a hard grid without red numbers neither mistake",
		"finished a evil grid without red numbers neither mistake"}
	};
	
	//var pour les trophées
	
	int reddot = 0;
	int wrong = 0;
	
	//TEST TIMER
	//pspTime time;
	//sceRtcGetCurrentClockLocalTime(&time);
	
	
    while(!osl_quit){
		
        if (!skip){
            
			oslStartDrawing();
			oslReadKeys(); 
			
			if (osl_keys->pressed.select){ 
				if(langue == 0){
					langue = 1;
				}
				else{
					langue = 0;
				}
			}
			//JEU
			if(etat == 1){
				#include "jeu.c"
			}
			//REGLES
			if(etat == 2){
				
				if (osl_keys->pressed.triangle && !osl_keys->held.L && afficheTrophee == 0){ 
					etat = 0;
					if(soncheck){
					oslPlaySound(unchecksound, 4);
					}
				}
				oslDrawImageXY(bg,0,0);
				oslDrawImageXY(squarologo,130,0);
				oslDrawImageXY(rules,240,125);
				oslSetFont(pgfFont125);
				if(langue==0){
				oslDrawString(240, 90, "Règles");
				}
				if(langue==1){
				oslDrawString(240, 90, "Rules");
				}
				
				
				oslSetFont(pgfFont60);
				if(langue==0){
				oslDrawString(10, 110, "Le but du SquarO est de deviner quels\ncercles doivent être remplis.");
				oslDrawString(10, 145, "Dans chaque case, il y a un chiffre\nentre 0 et 4 qui correspond au\nnombre de cercles entourant la case\nqui doivent être remplies en bleu.\nLes cercles rouges sont là pour\nmarquer au besoin des cercles vides.");
				oslDrawString(10, 220, "Chaque grille a une seule solution.");
				oslDrawString(10, 245, "En Mode Evil, il y a des chiffres entre \n0 et 8, et un demi cercle vaut 1.");
				}
				if(langue==1){
				oslDrawString(10, 110, "The goal of SquarO is to find out\nwhat circles must be filled in blue.");
				oslDrawString(10, 145, "In each square, there is a number\nbetween 0 and 4 which corresponds\nto the number of circles around that\nsquare that must be filled.\nRed circles is for help you to mark\nempty circle.");
				oslDrawString(10, 220, "Each grid has a unique solution.");
				oslDrawString(10, 245, "In Evil Mode, there's number between \n0 and 8,and half-circle is 1.");
				}
				
				oslSetFont(pgfFont60r);
				if(langue==0){oslDrawString(475, 258, "Triangle : Retour");} if(langue==1){oslDrawString(475, 258, "Triangle : Back");}
				
				//tropheetest
				if(tropheesPerso[0] == 0){
					tropheesPerso[0] = 1;
					tropheeTemps = 200;
					nbrTropheeMontre = 1;
					tropheeMontre[0] = 0;
					afficheTrophee = 1;
				}
			}
			// MODE D'EMPLOI
			if(etat == 3){
				if (osl_keys->pressed.triangle && !osl_keys->held.L){ 
					etat = 0;
					if(soncheck){
					oslPlaySound(unchecksound, 4);
					}
				}
				oslDrawImageXY(bg,0,0);
				oslDrawImageXY(squarologo,130,0);
				oslSetFont(pgfFont125);
				if(langue==0){
				oslDrawString(240, 90, "Mode d'emploi");
				}
				if(langue==1){
				oslDrawString(240, 90, "Guide");
				}
				
				
				if(langue==1){
				oslSetFont(pgfFont70b);
				oslDrawString(240, 110, "Main");
				oslSetFont(pgfFont60c);
				oslDrawString(240, 120, "Cross : Validate\nTriangle : Back\nSelect : Change language\nL + R : Show MP3 Player");
				oslSetFont(pgfFont70b);
				oslDrawString(240, 168, "Grid Selection");
				oslSetFont(pgfFont60c);
				oslDrawString(240, 178, "L or R : Switch Mode\nStart : Launch Grid");
				oslSetFont(pgfFont70b);
				oslDrawString(240, 205, "In Game");
				oslSetFont(pgfFont60c);
				oslDrawString(240, 215, "Cross : Fill/Empty circle\nCircle:Mark circle in red\nD-Pad : Move\nTriangle : Back to Grid Selection\nStart : next grid when grid completed");
				}
				if(langue==0){
				oslSetFont(pgfFont70b);
				oslDrawString(240, 110, "Général");
				oslSetFont(pgfFont60c);
				oslDrawString(240, 120, "Croix : Valider\nTriangle : Retour\nSelect : Changer la langue\nL+R : Afficher le Player MP3");
				oslSetFont(pgfFont70b);
				oslDrawString(240, 168, "Sélection des grilles");
				oslSetFont(pgfFont60c);
				oslDrawString(240, 178, "L ou R : Basculer entre les niveaux\nStart : Lancer la grille");
				oslSetFont(pgfFont70b);
				oslDrawString(240, 205, "En jeu");
				oslSetFont(pgfFont60c);
				oslDrawString(240, 215, "Croix : Remplir/Vider le cercle\nRond : Marquer le cercle en rouge\nTouches directionnelles : Se déplacer\nTriangle : Retour à la sélection\nStart : grille suivante une fois completée");
				
				}
				oslSetFont(pgfFont60r);
				if(langue==0){oslDrawString(475, 258, "Triangle : Retour");} if(langue==1){oslDrawString(475, 258, "Triangle : Back");}
			}
			// OPTIONS
			if(etat == 4){
				
				oslDrawImageXY(bg,0,0);
				oslDrawImageXY(squarologo,130,0);
				oslSetFont(pgfFont125);
				if(langue==0){
				oslDrawString(240, 90, "Options");
				}
				if(langue==1){
				oslDrawString(240, 90, "Options");
				}
				
				if(effacerProgression){
					if(langue == 0){
					oslDrawString(240, 140, "Attention suppression définitive");
					}
					if(langue == 1){
					oslDrawString(240, 140, "Warning, irreversible action");
					}
					if (osl_keys->pressed.triangle && !osl_keys->held.L){ 
						effacerProgression = 0;
					}
					if (osl_keys->pressed.start && !osl_keys->held.L){ 
						FILE *fichierScore = fopen("data/grille","w+");
						if(fichierScore!=NULL){
							for(i=0;i<400;i++){
								grilleComplete[i] = 0;
								fputs("0\n",fichierScore);
							}
							fclose(fichierScore);
							effacerProgression = 0;
						}
					}
					oslSetFont(pgfFont75c);
					if(langue == 0){
					oslDrawString(240, 160, "Start : Confirmer - Triangle : Annuler");
					}
					if(langue == 1){
					oslDrawString(240, 160, "Start : Confirm - Triangle : Cancel");
					}
				}
				else if(effacerRecord){
					if(langue == 0){
					oslDrawString(240, 140, "Attention suppression définitive");
					}
					if(langue == 1){
					oslDrawString(240, 140, "Warning, irreversible action");
					}
					if (osl_keys->pressed.triangle && !osl_keys->held.L){ 
						effacerRecord = 0;
					}
					if (osl_keys->pressed.start && !osl_keys->held.L){ 
						FILE *fichierScore = fopen("data/record","w+");
						if(fichierScore!=NULL){
							for(i=0;i<20;i++){
								recordsPerso[i] = 0;
								fputs("0\n",fichierScore);
							}
							fclose(fichierScore);
							effacerRecord = 0;
						}
					}
					oslSetFont(pgfFont75c);
					if(langue == 0){
					oslDrawString(240, 160, "Start : Confirmer - Triangle : Annuler");
					}
					if(langue == 1){
					oslDrawString(240, 160, "Start : Confirm - Triangle : Cancel");
					}
				}
				else if(effacerTrophee){
					if(langue == 0){
					oslDrawString(240, 140, "Attention suppression définitive");
					}
					if(langue == 1){
					oslDrawString(240, 140, "Warning, irreversible action");
					}
					if (osl_keys->pressed.triangle && !osl_keys->held.L){ 
						effacerTrophee = 0;
					}
					if (osl_keys->pressed.start && !osl_keys->held.L){ 
						FILE *fichierTrophee = fopen("data/trophee","w+");
						if(fichierTrophee!=NULL){
							for(i=0;i<18;i++){
								tropheesPerso[i] = 0;
								fputs("0\n",fichierTrophee);
							}
							fclose(fichierTrophee);
							effacerTrophee = 0;
						}
					}
					oslSetFont(pgfFont75c);
					if(langue == 0){
					oslDrawString(240, 160, "Start : Confirmer - Triangle : Annuler");
					}
					if(langue == 1){
					oslDrawString(240, 160, "Start : Confirm - Triangle : Cancel");
					}
				}
				else{
					if (osl_keys->pressed.triangle && !osl_keys->held.L){ 
						etat = 0;
						if(soncheck){
						oslPlaySound(unchecksound, 4);
						}
					}
					
					if (osl_keys->pressed.down){ 
						if(posMenuOption < 4){
							posMenuOption++;
						}
					}
					if (osl_keys->pressed.up){ 
						if(posMenuOption > 0){
							posMenuOption--;
						}
					}
					
					if (osl_keys->pressed.cross){ 
						if(posMenuOption == 0){
							if(chiffresrouges == 1){
							optionsPerso[0] = 0;
							chiffresrouges = 0;
							}
							else{
							optionsPerso[0] = 1;
							chiffresrouges = 1;
							}
							FILE *fichierOption = fopen("data/option","w+");
							if(fichierOption!=NULL){
								for(i=0;i<2;i++){
									fprintf(fichierOption, "%d\n", optionsPerso[i]);
								}
								fclose(fichierScore);
							}
							
						}
						if(posMenuOption == 1){
							if(soncheck == 1){
							optionsPerso[1] = 0;
							soncheck = 0;
							}
							else{
							optionsPerso[1] = 1;
							soncheck = 1;
							}
							FILE *fichierOption = fopen("data/option","w+");
							if(fichierOption!=NULL){
								for(i=0;i<2;i++){
									fprintf(fichierOption, "%d\n", optionsPerso[i]);
								}
								fclose(fichierScore);
							}
						}
						if(posMenuOption == 2){
							if(effacerProgression == 1){
							effacerProgression = 0;
							}
							else{
							effacerProgression = 1;
							}
						}
						if(posMenuOption == 3){
							if(effacerRecord == 1){
							effacerRecord = 0;
							}
							else{
							effacerRecord = 1;
							}
						}
						if(posMenuOption == 4){
							if(effacerTrophee == 1){
							effacerTrophee = 0;
							}
							else{
							effacerTrophee = 1;
							}
						}
					}
					
					
					oslSetFont(pgfFont75c);
					
					
					if(langue == 0){
						if(posMenuOption == 0){
							if(optionsPerso[0] == 1){
							oslDrawString(240, 140, ">> Chiffres rouge : oui <<");
							}
							else{
							oslDrawString(240, 140, ">> Chiffres rouge : non <<");
							}
						}
						else{
							if(optionsPerso[0] == 1){
							oslDrawString(240, 140, "Chiffres rouge : oui");
							}
							else{
							oslDrawString(240, 140, "Chiffres rouge : non");
							}
						}
						
						if(posMenuOption == 1){
							if(optionsPerso[1] == 1){
							oslDrawString(240, 160, ">> Sons : oui <<");
							}
							else{
							oslDrawString(240, 160, ">> Sons : non <<");
							}
						}
						else{
							if(optionsPerso[1] == 1){
							oslDrawString(240, 160, "Sons : oui");
							}
							else{
							oslDrawString(240, 160, "Sons : non");
							}
						}
						
						
						if(posMenuOption == 2){
						oslDrawString(240, 180, ">> Effacer la progression <<");
						}
						else{
						oslDrawString(240, 180, "Effacer la progression");
						}
						if(posMenuOption == 3){
						oslDrawString(240, 200, ">> Effacer les records <<");
						}
						else{
						oslDrawString(240, 200, "Effacer les records");
						}
						if(posMenuOption == 4){
						oslDrawString(240, 220, ">> Effacer les trophées <<");
						}
						else{
						oslDrawString(240, 220, "Effacer les trophées");
						}
					}
					
					
					if(langue == 1){
						
						if(posMenuOption == 0){
							if(optionsPerso[0] == 1){
							oslDrawString(240, 140, ">> Red Numbers : yes <<");
							}
							else{
							oslDrawString(240, 140, ">> Red Numbers : no <<");
							}
						}
						else{
							if(optionsPerso[0] == 1){
							oslDrawString(240, 140, "Red Numbers : yes");
							}
							else{
							oslDrawString(240, 140, "Red Numbers : no");
							}
						}
						
						if(posMenuOption == 1){
							if(optionsPerso[1] == 1){
							oslDrawString(240, 160, ">> Sounds : yes <<");
							}
							else{
							oslDrawString(240, 160, ">> Sounds : no <<");
							}
						}
						else{
							if(optionsPerso[1] == 1){
							oslDrawString(240, 160, "Sounds : yes");
							}
							else{
							oslDrawString(240, 160, "Sounds : no");
							}
						}
						
						
						if(posMenuOption == 2){
						oslDrawString(240, 180, ">> Delete your progression <<");
						}
						else{
						oslDrawString(240, 180, "Delete your progression");
						}
						if(posMenuOption == 3){
						oslDrawString(240, 200, ">> Delete your records <<");
						}
						else{
						oslDrawString(240, 200, "Delete your records");
						}
						if(posMenuOption == 4){
						oslDrawString(240, 220, ">> Delete your trophies <<");
						}
						else{
						oslDrawString(240, 220, "Delete your trophies");
						}
					}
				
				}
				

				
				oslSetFont(pgfFont60r);
				if(langue==0){oslDrawString(475, 258, "Triangle : Retour");} if(langue==1){oslDrawString(475, 258, "Triangle : Back");}
				
			}
			// RECORDS
			if(etat == 5){
				if (osl_keys->pressed.triangle && !osl_keys->held.L){ 
					etat = 0;
					if(soncheck){
					oslPlaySound(unchecksound, 4);
					}
				}
				oslDrawImageXY(bg,0,0);
				oslDrawImageXY(squarologo,130,0);
				oslSetFont(pgfFont125);
				if(langue==0){
				oslDrawString(240, 90, "Records");
				}
				if(langue==1){
				oslDrawString(240, 90, "Records");
				}
				
				
				oslSetFont(pgfFont70b);
				if(langue==0){
				oslDrawString(96, 130, "Facile");
				}
				if(langue==1){
				oslDrawString(96, 130, "Easy");
				}
				oslSetFont(pgfFont70);
				for(i=0;i<5;i++){
					if(recordsPerso[i] != 0){
					oslDrawStringf(96, 155+i*15, "%d:%d",recordsPerso[i]/60,recordsPerso[i]%60);
					}
					else{
					oslDrawString(96, 155+i*15, "--");
					}
				}

				oslSetFont(pgfFont70b);
				if(langue==0){
				oslDrawString(192, 130, "Moyen");
				}
				if(langue==1){
				oslDrawString(192, 130, "Medium");
				}
				oslSetFont(pgfFont70);
				for(i=0;i<5;i++){
					if(recordsPerso[i+5] != 0){
					oslDrawStringf(192, 155+i*15, "%d:%d",recordsPerso[i+5]/60,recordsPerso[i+5]%60);
					}
					else{
					oslDrawString(192, 155+i*15, "--");
					}
				}
				
				oslSetFont(pgfFont70b);
				if(langue==0){
				oslDrawString(288, 130, "Difficile");
				}
				if(langue==1){
				oslDrawString(288, 130, "Hard");
				}
				oslSetFont(pgfFont70);
				for(i=0;i<5;i++){
					if(recordsPerso[i+10] != 0){
					oslDrawStringf(288, 155+i*15, "%d:%d",recordsPerso[i+10]/60,recordsPerso[i+10]%60);
					}
					else{
					oslDrawString(288, 155+i*15, "--");
					}
				}
				
				oslSetFont(pgfFont70b);
				if(langue==0){
				oslDrawString(384, 130, "Evil");
				}
				if(langue==1){
				oslDrawString(384, 130, "Evil");
				}
				oslSetFont(pgfFont70);
				for(i=0;i<5;i++){
					if(recordsPerso[i+15] != 0){
					oslDrawStringf(384, 155+i*15, "%d:%d",recordsPerso[i+15]/60,recordsPerso[i+15]%60);
					}
					else{
					oslDrawString(384, 155+i*15, "--");
					}
				}
				
			
				
				oslSetFont(pgfFont60r);
				if(langue==0){oslDrawString(475, 258, "Triangle : Retour");} if(langue==1){oslDrawString(475, 258, "Triangle : Back");}
				
			}
			// TROPHÉES
			if(etat == 6){
				if (osl_keys->pressed.triangle && !osl_keys->held.L){ 
					etat = 0;
					if(soncheck){
					oslPlaySound(unchecksound, 4);
					}
				}
				oslDrawImageXY(bg,0,0);
				oslDrawImageXY(squarologo,130,0);
				oslSetFont(pgfFont125);
				if(langue==0){
				oslDrawString(240, 90, "Trophées");
				}
				if(langue==1){
				oslDrawString(240, 90, "Trophies");
				}
				
				int xtr, ytr, etr, ttr;
				xtr = 15;
				ytr = 110;
				etr = 50;
				ttr = 50;
				
				//oslDrawImageXY(tropheedefaut,xtr+etr,ytr);
				/*
				if(tropheesPerso[0] == 1){
				oslDrawImageXY(troph1m,xtr,ytr);
				}
				else{
				oslDrawImageXY(tropheedefaut,xtr,ytr);
				}
				
				if(tropheesPerso[1] == 1){
				oslDrawImageXY(troph2m,xtr+etr,ytr);
				}
				else{
				oslDrawImageXY(tropheedefaut,xtr+etr,ytr);
				}
				
				if(tropheesPerso[2] == 1){
				oslDrawImageXY(troph3m,xtr+etr*2,ytr);
				}
				else{
				oslDrawImageXY(tropheedefaut,xtr+etr*2,ytr);
				}
				
				if(tropheesPerso[3] == 1){
				oslDrawImageXY(troph4m,xtr+etr*3,ytr);
				}
				else{
				oslDrawImageXY(tropheedefaut,xtr+etr*3,ytr);
				}
				
				if(tropheesPerso[4] == 1){
				oslDrawImageXY(troph5m,xtr+etr*4,ytr);
				}
				else{
				oslDrawImageXY(tropheedefaut,xtr+etr*4,ytr);
				}
				
				if(tropheesPerso[5] == 1){
				oslDrawImageXY(troph6m,xtr+etr*5,ytr);
				}
				else{
				oslDrawImageXY(tropheedefaut,xtr+etr*5,ytr);
				}
				
				if(tropheesPerso[6] == 1){
				oslDrawImageXY(troph7m,xtr+etr*6,ytr);
				}
				else{
				oslDrawImageXY(tropheedefaut,xtr+etr*6,ytr);
				}
				
				if(tropheesPerso[7] == 1){
				oslDrawImageXY(troph8m,xtr+etr*7,ytr);
				}
				else{
				oslDrawImageXY(tropheedefaut,xtr+etr*7,ytr);
				}
				
				if(tropheesPerso[8] == 1){
				oslDrawImageXY(troph9m,xtr+etr*8,ytr);
				}
				else{
				oslDrawImageXY(tropheedefaut,xtr+etr*8,ytr);
				}
				
				
				
				oslDrawImageXY(troph10m,xtr,ytr+ttr);
				oslDrawImageXY(troph11m,xtr+etr,ytr+ttr);
				oslDrawImageXY(troph12m,xtr+etr*2,ytr+ttr);
				oslDrawImageXY(troph13m,xtr+etr*3,ytr+ttr);
				oslDrawImageXY(troph14m,xtr+etr*4,ytr+ttr);
				oslDrawImageXY(troph15m,xtr+etr*5,ytr+ttr);
				oslDrawImageXY(troph16m,xtr+etr*6,ytr+ttr);
				oslDrawImageXY(troph17m,xtr+etr*7,ytr+ttr);
				oslDrawImageXY(troph18m,xtr+etr*8,ytr+ttr);
				*/
				
				for(i=0;i<18;i++){
					OSL_IMAGE *temp;
					switch(i){
						case 0:
						temp = troph1m;
						break;
						
						case 1:
						temp = troph2m;
						break;
						
						case 2:
						temp = troph3m;
						break;
						
						case 3:
						temp = troph4m;
						break;
						
						case 4:
						temp = troph5m;
						break;
						
						case 5:
						temp = troph6m;
						break;
						
						case 6:
						temp = troph7m;
						break;
						
						case 7:
						temp = troph8m;
						break;
						
						case 8:
						temp = troph9m;
						break;
						
						case 9:
						temp = troph10m;
						break;
						
						case 10:
						temp = troph11m;
						break;
						
						case 11:
						temp = troph12m;
						break;
						
						case 12:
						temp = troph13m;
						break;
						
						case 13:
						temp = troph14m;
						break;
						
						case 14:
						temp = troph15m;
						break;
						
						case 15:
						temp = troph16m;
						break;
						
						case 16:
						temp = troph17m;
						break;
						
						case 17:
						temp = troph18m;
						break;
					}
					
					if(tropheesPerso[i] == 1){
						if(i<9){
						oslDrawImageXY(temp,xtr+etr*i,ytr);
						}
						else{
						oslDrawImageXY(temp,xtr+etr*(i-9),ytr+ttr);
						}
					}
					else{
						if(i<9){
						oslDrawImageXY(tropheedefaut,xtr+etr*i,ytr);
						}
						else{
						oslDrawImageXY(tropheedefaut,xtr+etr*(i-9),ytr+ttr);
						}
					}
					
					if(i == posTrophee){
						if(i<9){
						oslDrawImageXY(curseurtrophee,xtr+etr*i,ytr);
						}
						else{
						oslDrawImageXY(curseurtrophee,xtr+etr*(i-9),ytr+ttr);
						}
					}
				}
				
				if (osl_keys->pressed.right){ 
					if(posTrophee < 17){
						posTrophee++;
					}
				}
				if (osl_keys->pressed.left){ 
					if(posTrophee > 0){
						posTrophee--;
					}
				}
				if (osl_keys->pressed.down){ 
					if(posTrophee < 9){
						posTrophee = posTrophee + 9;
					}
				}
				if (osl_keys->pressed.up){ 
					if(posTrophee > 8){
						posTrophee = posTrophee - 9;
					}
				}
				
				oslSetFont(pgfFont70b);
				oslDrawString(240, 220,titreTrophee[langue][posTrophee]);
				oslSetFont(pgfFont70);
				oslDrawString(240, 235,labelTrophee[langue][posTrophee]);
				
				oslSetFont(pgfFont60r);
				if(langue==0){oslDrawString(475, 258, "Triangle : Retour");} if(langue==1){oslDrawString(475, 258, "Triangle : Back");}
				
			}
			// CREDITS
			if(etat == 7){
				if (osl_keys->pressed.triangle && !osl_keys->held.L){ 
					etat = 0;
					if(soncheck){
					oslPlaySound(unchecksound, 4);
					}
				}
				oslDrawImageXY(bg,0,0);
				oslDrawImageXY(squarologo,130,0);
				oslSetFont(pgfFont125);
				if(langue==0){
				oslDrawString(240, 90, "Crédits");
				}
				if(langue==1){
				oslDrawString(240, 90, "Credits");
				}
				
	
				if(langue==0){
				oslSetFont(pgfFont70b);
				oslDrawString(240, 120, "Créateur du Jeu");
				oslSetFont(pgfFont70);
				oslDrawString(240, 135, "Marc Lebel");
				oslDrawString(240, 150, "http://www.squaro.fr");
				oslSetFont(pgfFont70b);
				oslDrawString(240, 180, "Développeur PSP");
				oslSetFont(pgfFont70);
				oslDrawString(240, 195, "Miles");
				oslDrawString(240, 210, "http://mileskabal.free.fr/psp");
				}
				if(langue==1){
				oslSetFont(pgfFont70b);
				oslDrawString(240, 120, "Game Creator");
				oslSetFont(pgfFont70);
				oslDrawString(240, 135, "Marc Lebel");
				oslDrawString(240, 150, "http://www.squaro.fr");
				oslSetFont(pgfFont70b);
				oslDrawString(240, 180, "PSP Developer");
				oslSetFont(pgfFont70);
				oslDrawString(240, 195, "Miles");
				oslDrawString(240, 210, "http://mileskabal.free.fr/psp");
				}
				
				oslDrawString(240, 240, "Squaro PSP v1.3");
				oslSetFont(pgfFont60r);
				if(langue==0){oslDrawString(475, 258, "Triangle : Retour");} if(langue==1){oslDrawString(475, 258, "Triangle : Back");}
				
			}
			// QUITTER
			if(etat == 8){
				osl_quit = 1;
			}
			// SELECTION GRILLE
			if(etat == 9){
				if (osl_keys->pressed.triangle && !osl_keys->held.L){ 
					etat = 0;
					if(soncheck){
					oslPlaySound(unchecksound, 4);
					}
				}
				
				if (osl_keys->pressed.start){
					
					casePos[0] = 0;
					casePos[1] = 0;
					
					for(i=0;i<6;i++){
						for(j=0;j<6;j++){
							gameGrille[i][j] = 0;
						}
					}
					
					k = 0;
					for(i=0;i<6;i++){
						for(j=0;j<6;j++){
							gameGrilleSoluce[i][j] = grille[grilleCourante][k];
							k++;
						}
					}
					
					k = 0;
					for(i=0;i<6;i++){
						for(j=0;j<6;j++){
							if(i<5 && j<5){
							chiffreDevine[k] = gameGrilleSoluce[i][j] + gameGrilleSoluce[i+1][j] + gameGrilleSoluce[i][j+1] + gameGrilleSoluce[i+1][j+1];
							chiffreEnCours[k] = 0;
							k++;
							}
						}
					}
					if(soncheck){
					oslPlaySound(checksound, 3);
					}
					timer_start();
					recordenregistre = 0;
					etat = 1;
					reddot = 0;
					wrong = 0;
					nbrTropheeMontre = 0;
				}
				
				if (osl_keys->pressed.right){ 
					if(niveau == 0){
						if(grilleCourante<99){
						grilleCourante++;
						}
					}
					if(niveau == 1){
						if(grilleCourante<99+100){
						grilleCourante++;
						}
					}
					if(niveau == 2){
						if(grilleCourante<99+200){
						grilleCourante++;
						}
					}
					if(niveau == 3){
						if(grilleCourante<99+300){
						grilleCourante++;
						}
					}
				}
				if (osl_keys->pressed.left){ 
					if(niveau == 0){
						if(grilleCourante > 0){
						grilleCourante--;
						}
					}
					if(niveau == 1){
						if(grilleCourante > 0 + 100){
						grilleCourante--;
						}
					}
					if(niveau == 2){
						if(grilleCourante > 0 + 200){
						grilleCourante--;
						}
					}
					if(niveau == 3){
						if(grilleCourante > 0 + 300){
						grilleCourante--;
						}
					}
				}
				if (osl_keys->pressed.down){ 
					if(niveau == 0){
						if(grilleCourante<80){
						grilleCourante = grilleCourante + 20;
						}
					}
					if(niveau == 1){
						if(grilleCourante<80 + 100){
						grilleCourante = grilleCourante + 20;
						}
					}
					if(niveau == 2){
						if(grilleCourante<80 + 200){
						grilleCourante = grilleCourante + 20;
						}
					}
					if(niveau == 3){
						if(grilleCourante<80 + 300){
						grilleCourante = grilleCourante + 20;
						}
					}
				}
				if (osl_keys->pressed.up){ 
					if(niveau == 0){
						if(grilleCourante>=20){
						grilleCourante = grilleCourante - 20;
						}
					}
					if(niveau == 1){
						if(grilleCourante>=20+100){
						grilleCourante = grilleCourante - 20;
						}
					}
					if(niveau == 2){
						if(grilleCourante>=20+200){
						grilleCourante = grilleCourante - 20;
						}
					}
					if(niveau == 3){
						if(grilleCourante>=20+300){
						grilleCourante = grilleCourante - 20;
						}
					}
				}
				
				if (osl_keys->pressed.R){ 
					if(grilleCourante <= 299){
						grilleCourante = grilleCourante + 100;
						niveau++;
					}
				}
				if (osl_keys->pressed.L){ 
					if(grilleCourante >= 100){
						grilleCourante = grilleCourante - 100;
						niveau--;
					}
				}
				
				
				
				oslDrawImageXY(bg,0,0);
				oslDrawImageXY(squarologo,130,0);
				oslSetFont(pgfFont70b);
				
				
				if(langue==0){
					oslDrawString(240, 80, "Choix de la Grille");
					oslDrawStringf(240, 225, "Grille %d",grilleCourante+1);
					if(niveau == 0){
					oslDrawString(240, 240, "<< L - Niveau Facile - R >>");
					}
					if(niveau == 1){
					oslDrawString(240, 240, "<< L - Niveau Moyen - R >>");
					}
					if(niveau == 2){
					oslDrawString(240, 240, "<< L - Niveau Difficile - R >>");
					}
					if(niveau == 3){
					oslDrawString(240, 240, "<< L - Niveau Evil - R >>");
					}
					
					oslSetFont(pgfFont70);
					oslDrawString(240, 258, "Pressez Start pour jouer");
				}
				if(langue==1){
					oslDrawString(240, 80, "Grid Selection");
					oslDrawStringf(240, 225, "Grid %d",grilleCourante+1);
					if(niveau == 0){
					oslDrawString(240, 240, "<< L - Easy Mode - R >>");
					}
					if(niveau == 1){
					oslDrawString(240, 240, "<< L - Medium Mode - R >>");
					}
					if(niveau == 2){
					oslDrawString(240, 240, "<< L - Hard Mode - R >>");
					}
					if(niveau == 3){
					oslDrawString(240, 240, "<< L - Evil Mode - R >>");
					}
					
					oslSetFont(pgfFont70);
					oslDrawString(240, 258, "Press Start to play");
				}
				
				
				oslSetFont(pgfFont60r);
				if(langue==0){oslDrawString(475, 258, "Triangle : Retour");} if(langue==1){oslDrawString(475, 258, "Triangle : Back");}
				
				x = 0;
				k = 0;
				for(i=0;i<100;i++){
					j=110;
					if(i>19){
						j=132;
					}
					if(i>39){
						j=154;
					}
					if(i>59){
						j=176;
					}
					if(i>79){
						j=198;
					}
					
					
					k = i;
					if(niveau == 1){
						k = i + 100;
					}
					if(niveau == 2){
						k = i + 200;
					}
					if(niveau == 3){
						k = i + 300;
					}
					
					if(grilleComplete[k] == 1){
						if(k == grilleCourante){
						oslDrawImageXY(cercle_plein_active_grille,20+x*22,j-5);
						}
						else{
						oslDrawImageXY(cercle_plein_grille,20+x*22,j-5);
						}
						
					}
					else{
						if(k == grilleCourante){
						oslDrawImageXY(cercle_vide_active_grille,20+x*22,j-5);
						}
						else{
						oslDrawImageXY(cercle_vide_grille,20+x*22,j-5);
						}
					}
					
					
					if(x <19){
						x++;
					}
					else{
					x=0;
					}
				}
				
			}
			// MENU
			if(etat == 0){
				
				
				oslDrawImageXY(bg,0,0);
				oslDrawImageXY(squarologo,130,0);
				
				
				if(premierLancement == 0){
					
					//TEST TIMER
					//sceRtcGetCurrentClockLocalTime(&time);
					//oslDrawStringf(240, 200, "%d",time.seconds);
					
					oslSetFont(pgfFont125);
					
					oslDrawString(240, 90, "Langue / Language");
					if(langue == 0){
						if (osl_keys->pressed.down){ 
						langue = 1;
						timer_reset();
						}
						oslDrawString(240, 130, ">> Français <<");
						oslDrawString(240, 155, "English");
					}
					else{
						if (osl_keys->pressed.up){ 
						langue = 0;
						}
						oslDrawString(240, 130, "Français");
						oslDrawString(240, 155, ">> English <<");
					}
					
					oslSetFont(pgfFont75c);
					oslDrawString(240, 200, "Dev by Miles\nhttp://mileskabal.free.fr/psp");
					if (osl_keys->pressed.cross && !osl_keys->held.L){ 
						premierLancement = 1;
						if(soncheck){
						oslPlaySound(checksound, 3);
						}
					}
				}
				else{
					oslSetFont(pgfFont75c);
					if (osl_keys->pressed.cross  && !osl_keys->held.L){ 
						if(menuPos==0){
							etat = 9;
						}
						else{
						etat = menuPos + 1;
						}
						if(soncheck){
						oslPlaySound(checksound, 3);
						}
					}
					if (osl_keys->pressed.down){ 
						if(menuPos < 7){
							menuPos++;
						}
					}
					if (osl_keys->pressed.up){ 
						if(menuPos > 0){
							menuPos--;
						}
					}
					
					for(i=0;i<8;i++){
						if(i==menuPos){
							if(langue==0){
								if(i==0){
								oslDrawString(240, 90+i*20, ">> Jouer <<");
								}
								if(i==1){
								oslDrawString(240, 90+i*20, ">> Règles <<");
								}
								if(i==2){
								oslDrawString(240, 90+i*20, ">> Mode d'emploi <<");
								}
								if(i==3){
								oslDrawString(240, 90+i*20, ">> Options <<");
								}
								if(i==4){
								oslDrawString(240, 90+i*20, ">> Records <<");
								}
								if(i==5){
								oslDrawString(240, 90+i*20, ">> Trophées <<");
								}
								if(i==6){
								oslDrawString(240, 90+i*20, ">> Crédits <<");
								}
								if(i==7){
								oslDrawString(240, 90+i*20, ">> Quitter <<");
								}
							}
							if(langue==1){
								if(i==0){
								oslDrawString(240, 90+i*20, ">> Play <<");
								}
								if(i==1){
								oslDrawString(240, 90+i*20, ">> Rules <<");
								}
								if(i==2){
								oslDrawString(240, 90+i*20, ">> Guide <<");
								}
								if(i==3){
								oslDrawString(240, 90+i*20, ">> Options <<");
								}
								if(i==4){
								oslDrawString(240, 90+i*20, ">> Records <<");
								}
								if(i==5){
								oslDrawString(240, 90+i*20, ">> Trophies <<");
								}
								if(i==6){
								oslDrawString(240, 90+i*20, ">> Credits <<");
								}
								if(i==7){
								oslDrawString(240, 90+i*20, ">> Quit <<");
								}
							}
							
						}
						else{
							if(langue==0){
								if(i==0){
								oslDrawString(240, 90+i*20, "Jouer");
								}
								if(i==1){
								oslDrawString(240, 90+i*20, "Règles");
								}
								if(i==2){
								oslDrawString(240, 90+i*20, "Mode d'emploi");
								}
								if(i==3){
								oslDrawString(240, 90+i*20, "Options");
								}
								if(i==4){
								oslDrawString(240, 90+i*20, "Records");
								}
								if(i==5){
								oslDrawString(240, 90+i*20, "Trophées");
								}
								if(i==6){
								oslDrawString(240, 90+i*20, "Crédits");
								}
								if(i==7){
								oslDrawString(240, 90+i*20, "Quitter");
								}
							}
							if(langue==1){
								if(i==0){
								oslDrawString(240, 90+i*20, "Play");
								}
								if(i==1){
								oslDrawString(240, 90+i*20, "Rules");
								}
								if(i==2){
								oslDrawString(240, 90+i*20, "Guide");
								}
								if(i==3){
								oslDrawString(240, 90+i*20, "Options");
								}
								if(i==4){
								oslDrawString(240, 90+i*20, "Records");
								}
								if(i==5){
								oslDrawString(240, 90+i*20, "Trophies");
								}
								if(i==6){
								oslDrawString(240, 90+i*20, "Credits");
								}
								if(i==7){
								oslDrawString(240, 90+i*20, "Quit");
								}
							}
						}
					}
				}
			}
			// MP3
			if (osl_keys->held.L && osl_keys->held.R && afficheTrophee == 0){ 
			
				oslDrawImageXY(fondmp3,20,204);
				oslSetFont(pgfFont60n);
				
				
				if(nbrMusic > 0){
					oslDrawStringf(240,212,"SquarO Player - %d/%d",posInstru+1,nbrMusic);
					//oslDrawStringf(240,220,"%d",nbrMusic);
					oslDrawStringf(240,230,"%s",playlist[posInstru]);
					
					if (osl_keys->pressed.cross){ 
						if(activeMusic == 0){
							oslPlaySound(instru, 1);
							activeMusic = 1;
						}
						else{
							oslPauseSound(instru, -1);
						}
					}
					if (osl_keys->pressed.triangle){ 
						if(activeMusic == 1){
							oslStopSound(instru);
							activeMusic = 0;
						}
					}
					if (osl_keys->pressed.circle){ 
						if(posInstru < nbrMusic-1){
							//oslStopSound(instru);
							//oslDeleteSound(instru);
							posInstru++;
							//sprintf(tampon,"ms0:/PSP/MUSIC/%s",playlist[posInstru]);
							//instru = oslLoadSoundFileMP3(tampon, OSL_FMT_STREAM);
							//oslPlaySound(instru, 1);
							//activeMusic = 1;
						}
					}
					if (osl_keys->pressed.square){ 
						if(posInstru > 0){						
							oslStopSound(instru);
							oslDeleteSound(instru);
							posInstru--;
							sprintf(tampon,"ms0:/PSP/MUSIC/%s",playlist[posInstru]);
							instru = oslLoadSoundFileMP3(tampon, OSL_FMT_STREAM);
							oslPlaySound(instru, 1);
							activeMusic = 1;
						}
					}
				}
				else{
					oslDrawString(240,212,"SquarO Player");
					if(langue==0){
					oslDrawString(240,230,"Pas de son chargé");
					}
					if(langue==1){
					oslDrawString(240,230,"No Sound loaded");
					}
				}
				
			}
			//TROPHÉES AFFICHE
			if(afficheTrophee){
				
				if(nbrTropheeMontre > 0){
					
					if(tropheeTemps == 200){
					oslPlaySound(ping, 5);
					}
					
					OSL_IMAGE *temp;
					switch(tropheeMontre[nbrTropheeMontre-1]){
						case 0:
						temp = troph1m;
						break;
						
						case 1:
						temp = troph2m;
						break;
						
						case 2:
						temp = troph3m;
						break;
						
						case 3:
						temp = troph4m;
						break;
						
						case 4:
						temp = troph5m;
						break;
						
						case 5:
						temp = troph6m;
						break;
						
						case 6:
						temp = troph7m;
						break;
						
						case 7:
						temp = troph8m;
						break;
						
						case 8:
						temp = troph9m;
						break;
						
						case 9:
						temp = troph10m;
						break;
						
						case 10:
						temp = troph11m;
						break;
						
						case 11:
						temp = troph12m;
						break;
						
						case 12:
						temp = troph13m;
						break;
						
						case 13:
						temp = troph14m;
						break;
						
						case 14:
						temp = troph15m;
						break;
						
						case 15:
						temp = troph16m;
						break;
						
						case 16:
						temp = troph17m;
						break;
						
						case 17:
						temp = troph18m;
						break;
					}
						
					oslDrawImageXY(fondtrophee,130,204);
					oslDrawImageXY(temp,135,220);
					oslSetFont(pgfFont60n);
					if(langue == 0){
					oslDrawStringf(240,208,"Vous avez gagné le trophée :");
					}
					if(langue == 1){
					oslDrawStringf(240,208,"You have won the trophie :");
					}
					oslSetFont(pgfFont60b);
					oslDrawStringf(186,238,"%s",titreTrophee[langue][tropheeMontre[nbrTropheeMontre-1]]);
					
					tropheeTemps--;
					if(tropheeTemps == 0){
							nbrTropheeMontre--;
							if(nbrTropheeMontre == 0){
							afficheTrophee = 0;
							
							FILE *fichierTrophee = fopen("data/trophee","w+");
							if(fichierTrophee!=NULL){
								for(i=0;i<18;i++){
									fprintf(fichierTrophee, "%d\n", tropheesPerso[i]);
								}
								fclose(fichierTrophee);
							}
						}
						else{
						tropheeTemps = 200;
						}
					}
				}
				
			}
			
			/*
			if (osl_keys->pressed.R){
				afficheTrophee = 1;
				oslPlaySound(ping, 5);
				tropheeTemps = 200;
			}
			if (osl_keys->pressed.L){
				yo++;
			}
			*/
			
			oslEndDrawing();
			oslEndFrame();
	        skip = oslSyncFrame();
        }
		
    }
	
    //Quit OSL:
    oslEndGfx();

    sceKernelExitGame();
    return 0;

}
