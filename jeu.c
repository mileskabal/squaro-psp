oslSetFont(pgfFont75);

if (osl_keys->released.triangle  && !osl_keys->held.L && afficheTrophee == 0){ 
	etat=9;
	timer_stop();
	if(soncheck){
	oslPlaySound(unchecksound, 4);
	}
}
if (osl_keys->pressed.right){ 
	if(casePos[0] < 5){
		casePos[0]++;
	}
	
}
if (osl_keys->pressed.left){ 
	if(casePos[0] > 0){
		casePos[0]--;
	}
}
if (osl_keys->pressed.down){ 
	if(casePos[1] < 5){
		casePos[1]++;
	}
	
}
if (osl_keys->pressed.up){ 
	if(casePos[1] > 0){
		casePos[1]--;
	}
}
if (osl_keys->pressed.cross  && !osl_keys->held.L  && afficheTrophee == 0){ 
	if(niveau == 3){
		if(gameGrille[casePos[0]][casePos[1]] == 0){
		gameGrille[casePos[0]][casePos[1]] = 1;
		if(soncheck){
		oslPlaySound(checksound, 3);
		}
		}
		else if(gameGrille[casePos[0]][casePos[1]] == 1){
		gameGrille[casePos[0]][casePos[1]] = 2;
		if(soncheck){
		oslPlaySound(checksound, 3);
		}
		}
		else if(gameGrille[casePos[0]][casePos[1]]){
		gameGrille[casePos[0]][casePos[1]] = 0;
		wrong++;
		if(soncheck){
		oslPlaySound(unchecksound, 4);
		}
		}
		
	}
	else{
		if(gameGrille[casePos[0]][casePos[1]] == 0){
		gameGrille[casePos[0]][casePos[1]] = 1;
		if(soncheck){
		oslPlaySound(checksound, 3);
		}
		}
		else if(gameGrille[casePos[0]][casePos[1]] == 1){
		gameGrille[casePos[0]][casePos[1]] = 0;
		wrong++;
		if(soncheck){
		oslPlaySound(unchecksound, 4);
		}
		}
	}
}
if (osl_keys->pressed.circle  && !osl_keys->held.L  && afficheTrophee == 0){ 
	if(gameGrille[casePos[0]][casePos[1]] == -1){
	gameGrille[casePos[0]][casePos[1]] = 0;
	reddot++;
	if(soncheck){
	oslPlaySound(unchecksound, 4);
	}
	}
	else{
		if(gameGrille[casePos[0]][casePos[1]] == 0){
		gameGrille[casePos[0]][casePos[1]] = -1;
		reddot++;
		if(soncheck){
		oslPlaySound(checksound, 3);
		}
		}
	}
	
}


oslDrawImageXY(bg,0,0);
oslDrawImageXY(gridBg,120,15);
oslDrawImageXY(squarologopetit,385,0);


for(i=0;i<6;i++){
	for(j=0;j<6;j++){
		
		if(niveau == 3){
			if(gameGrille[j][i] == -1){
				if(i == casePos[1] && j == casePos[0]){
					oslDrawImageXY(cercle_marque_active,cerclePosXY[j][0] ,cerclePosXY[i][1]);
				}
				else{
					oslDrawImageXY(cercle_marque,cerclePosXY[j][0] ,cerclePosXY[i][1]);
				}
			}
			else if(gameGrille[j][i] == 1){
				if(i == casePos[1] && j == casePos[0]){
					oslDrawImageXY(cercle_demi_active,cerclePosXY[j][0] ,cerclePosXY[i][1]);
				}
				else{
					oslDrawImageXY(cercle_demi,cerclePosXY[j][0] ,cerclePosXY[i][1]);
				}
			}
			else if(gameGrille[j][i] == 2){
				if(i == casePos[1] && j == casePos[0]){
					oslDrawImageXY(cercle_plein_active,cerclePosXY[j][0] ,cerclePosXY[i][1]);
				}
				else{
					oslDrawImageXY(cercle_plein,cerclePosXY[j][0] ,cerclePosXY[i][1]);
				}
			}
			else{
				if(i == casePos[1] && j == casePos[0]){
					oslDrawImageXY(cercle_vide_active,cerclePosXY[j][0] ,cerclePosXY[i][1]);
				}
				else{
					oslDrawImageXY(cercle_vide,cerclePosXY[j][0] ,cerclePosXY[i][1]);
				}
			}
		}
		else{
			if(gameGrille[j][i] == -1){
				if(i == casePos[1] && j == casePos[0]){
					oslDrawImageXY(cercle_marque_active,cerclePosXY[j][0] ,cerclePosXY[i][1]);
				}
				else{
					oslDrawImageXY(cercle_marque,cerclePosXY[j][0] ,cerclePosXY[i][1]);
				}
			}
			else if(gameGrille[j][i] == 1){
				if(i == casePos[1] && j == casePos[0]){
					oslDrawImageXY(cercle_plein_active,cerclePosXY[j][0] ,cerclePosXY[i][1]);
				}
				else{
					oslDrawImageXY(cercle_plein,cerclePosXY[j][0] ,cerclePosXY[i][1]);
				}
			}
			else{
				if(i == casePos[1] && j == casePos[0]){
					oslDrawImageXY(cercle_vide_active,cerclePosXY[j][0] ,cerclePosXY[i][1]);
				}
				else{
					oslDrawImageXY(cercle_vide,cerclePosXY[j][0] ,cerclePosXY[i][1]);
				}
			}
		}
	
	}
}


k = 0;
for(i=0;i<6;i++){
	for(j=0;j<6;j++){
		if(i<5 && j<5){
		chiffreEnCours[k] = gameGrille[i][j] + gameGrille[i+1][j] + gameGrille[i][j+1] + gameGrille[i+1][j+1];
		if(gameGrille[i][j] == -1){chiffreEnCours[k]++;}
		if(gameGrille[i+1][j] == -1){chiffreEnCours[k]++;}
		if(gameGrille[i][j+1] == -1){chiffreEnCours[k]++;}
		if(gameGrille[i+1][j+1] == -1){chiffreEnCours[k]++;}
		k++;
		}
	}
}

k = 0;
for(i=0;i<5;i++){
	for(j=0;j<5;j++){
		if(chiffreDevine[k] == 0){
			if(chiffreEnCours[k] == chiffreDevine[k] || chiffresrouges == 0){
			oslDrawImageXY(active0,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
			else{
			oslDrawImageXY(unactive0,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
		}
		if(chiffreDevine[k] == 1){
			if(chiffreEnCours[k] == chiffreDevine[k] || chiffresrouges == 0){
			oslDrawImageXY(active1,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
			else{
			oslDrawImageXY(unactive1,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
		}
		if(chiffreDevine[k] == 2){
			if(chiffreEnCours[k] == chiffreDevine[k] || chiffresrouges == 0){
			oslDrawImageXY(active2,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
			else{
			oslDrawImageXY(unactive2,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
		}
		if(chiffreDevine[k] == 3){
			if(chiffreEnCours[k] == chiffreDevine[k] || chiffresrouges == 0){
			oslDrawImageXY(active3,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
			else{
			oslDrawImageXY(unactive3,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
		}
		if(chiffreDevine[k] == 4){
			if(chiffreEnCours[k] == chiffreDevine[k] || chiffresrouges == 0){
			oslDrawImageXY(active4,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
			else{
			oslDrawImageXY(unactive4,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
		}
		if(chiffreDevine[k] == 5){
			if(chiffreEnCours[k] == chiffreDevine[k] || chiffresrouges == 0){
			oslDrawImageXY(active5,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
			else{
			oslDrawImageXY(unactive5,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
		}
		if(chiffreDevine[k] == 6){
			if(chiffreEnCours[k] == chiffreDevine[k] || chiffresrouges == 0){
			oslDrawImageXY(active6,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
			else{
			oslDrawImageXY(unactive6,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
		}
		if(chiffreDevine[k] == 7){
			if(chiffreEnCours[k] == chiffreDevine[k] || chiffresrouges == 0){
			oslDrawImageXY(active7,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
			else{
			oslDrawImageXY(unactive7,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
		}
		if(chiffreDevine[k] == 8){
			if(chiffreEnCours[k] == chiffreDevine[k] || chiffresrouges == 0){
			oslDrawImageXY(active8,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
			else{
			oslDrawImageXY(unactive8,chiffrePosXY[i][0] ,chiffrePosXY[j][1]);
			}
		}
		
		k++;
	}
}

k=0;
for(i=0;i<25;i++){
	if(chiffreDevine[i] == chiffreEnCours[i]){
		k++;
	}
}



if(k==25){

	if(grilleComplete[grilleCourante] != 1 && !osl_keys->pressed.start){
		grilleComplete[grilleCourante] = 1;
		FILE *fichierScore = fopen("data/grille","w+");
		if(fichierScore!=NULL){
			for(i=0;i<400;i++){
				if(grilleComplete[i] == 1){
				fprintf(fichierScore, "%d\n", grilleComplete[i]);
				}
				else{
				fputs("0\n",fichierScore);
				}
			}
			fclose(fichierScore);
		}
	}
	
	if(recordenregistre == 0){
	
		if(recordsPerso[4+5*niveau] > timer_getTimeSec() || recordsPerso[4+5*niveau] == 0){
			if(recordsPerso[3+5*niveau] > timer_getTimeSec() || recordsPerso[3+5*niveau] == 0){
				if(recordsPerso[2+5*niveau] > timer_getTimeSec() || recordsPerso[2+5*niveau] == 0){
					if(recordsPerso[1+5*niveau] > timer_getTimeSec() || recordsPerso[1+5*niveau] == 0){
						if(recordsPerso[0+5*niveau] > timer_getTimeSec() || recordsPerso[0+5*niveau] == 0){
							recordsPerso[4+5*niveau] = recordsPerso[3+5*niveau];
							recordsPerso[3+5*niveau] = recordsPerso[2+5*niveau];
							recordsPerso[2+5*niveau] = recordsPerso[1+5*niveau];
							recordsPerso[1+5*niveau] = recordsPerso[0+5*niveau];
							recordsPerso[0+5*niveau] = timer_getTimeSec();
						}
						else{
						recordsPerso[4+5*niveau] = recordsPerso[3+5*niveau];
						recordsPerso[3+5*niveau] = recordsPerso[2+5*niveau];
						recordsPerso[2+5*niveau] = recordsPerso[1+5*niveau];
						recordsPerso[1+5*niveau] = timer_getTimeSec();
						}
					}
					else{
					recordsPerso[4+5*niveau] = recordsPerso[3+5*niveau];
					recordsPerso[3+5*niveau] = recordsPerso[2+5*niveau];
					recordsPerso[2+5*niveau] = timer_getTimeSec();
					}
				}
				else{
					recordsPerso[4+5*niveau] = recordsPerso[3+5*niveau];
					recordsPerso[3+5*niveau] = timer_getTimeSec();
				}
			}
			else{
				recordsPerso[4+5*niveau] = timer_getTimeSec();
			}
		}
		
		
		FILE *fichierRecord = fopen("data/record","w+");
		if(fichierRecord!=NULL){
			for(i=0;i<20;i++){
				fprintf(fichierRecord, "%d\n", recordsPerso[i]);
			}
			fclose(fichierRecord);
			recordenregistre = 1;
		}
		
	}
	
	if(langue==0){
	oslDrawString(5, 10, "Grille finie\nen \nStart pour la\nsuivante");
	}
	if(langue==1){
	oslDrawString(5, 10, "Completed\nin \nStart for next");
	}
	
	timer_startPause();
	
	
	//AFFICHAGE TIMER
	int xti = 28;
	if(langue==1){
	xti = xti - 5;
	}
	int yti = 23;
	if(timer_getTimeSec() < 10){
		oslDrawStringf(xti, yti, "0%llu:0%llu",timer_getTimeMin(),timer_getTimeSec());	
	}
	else{
		if(timer_getTimeMin() < 1){
			oslDrawStringf(xti, yti, "0%llu:%llu",timer_getTimeMin(),timer_getTimeSec());	
		}
		else{
			if(timer_getTimeMin() < 10){
				if(timer_getTimeSec()-(timer_getTimeMin()*60) < 10){
					oslDrawStringf(xti, yti, "0%llu:0%llu",timer_getTimeMin(),timer_getTimeSec()-(timer_getTimeMin()*60));
				}
				else{
					oslDrawStringf(xti, yti, "0%llu:%llu",timer_getTimeMin(),timer_getTimeSec()-(timer_getTimeMin()*60));
				}
			}
			else{
				if(timer_getTimeSec()-(timer_getTimeMin()*60) < 10){
					oslDrawStringf(xti, yti, "%llu:0%llu",timer_getTimeMin(),timer_getTimeSec()-(timer_getTimeMin()*60));
				}
				else{
					oslDrawStringf(xti, yti, "%llu:%llu",timer_getTimeMin(),timer_getTimeSec()-(timer_getTimeMin()*60));
				}
			}
		}
	}
	//AFFICHAGE TIMER FIN
	
	//tropheetest
	// if(tropheesPerso[0] == 0){
		// tropheesPerso[0] = 1;
		// tropheesPerso[2] = 1;
		// tropheeTemps = 200;
		// nbrTropheeMontre = 2;
		// tropheeMontre[0] = 0;
		// tropheeMontre[1] = 2;
		// afficheTrophee = 1;
	// }
	
	//pas aidé des ronds rouges
	if(tropheesPerso[1] == 0){
		if(reddot == 0){
		tropheeMontre[nbrTropheeMontre] = 1;
		nbrTropheeMontre++;
		tropheeTemps = 200;
		tropheesPerso[1] = 1;
		afficheTrophee = 1;
		}
	}
	//aidé des ronds rouges
	if(tropheesPerso[2] == 0){
		if(reddot > 0){
		tropheeMontre[nbrTropheeMontre] = 2;
		nbrTropheeMontre++;
		tropheeTemps = 200;
		tropheesPerso[2] = 1;
		afficheTrophee = 1;
		}
	}
	//a reussi une grille facile
	if(tropheesPerso[3] == 0){
		int nbr = 0;
		for(i=0;i<100;i++){
			nbr = nbr + grilleComplete[i];
		}
		if(nbr == 1){
		tropheeMontre[nbrTropheeMontre] = 3;
		nbrTropheeMontre++;
		tropheeTemps = 200;
		tropheesPerso[3] = 1;
		afficheTrophee = 1;
		}
	}
	//a reussi une grille medium
	if(tropheesPerso[4] == 0){
		int nbr = 0;
		for(i=100;i<200;i++){
			nbr = nbr + grilleComplete[i];
		}
		if(nbr == 1){
		tropheeMontre[nbrTropheeMontre] = 4;
		nbrTropheeMontre++;
		tropheeTemps = 200;
		tropheesPerso[4] = 1;
		afficheTrophee = 1;
		}
	}
	//a reussi une grille difficile
	if(tropheesPerso[5] == 0){
		int nbr = 0;
		for(i=200;i<300;i++){
			nbr = nbr + grilleComplete[i];
		}
		if(nbr == 1){
		tropheeMontre[nbrTropheeMontre] = 5;
		nbrTropheeMontre++;
		tropheeTemps = 200;
		tropheesPerso[5] = 1;
		afficheTrophee = 1;
		}
	}
	//a reussi une grille evil
	if(tropheesPerso[6] == 0){
		int nbr = 0;
		for(i=300;i<400;i++){
			nbr = nbr + grilleComplete[i];
		}
		if(nbr == 1){
		tropheeMontre[nbrTropheeMontre] = 6;
		nbrTropheeMontre++;
		tropheeTemps = 200;
		tropheesPerso[6] = 1;
		afficheTrophee = 1;
		}
	}
	//a reussi une grille sans erreur
	if(tropheesPerso[7] == 0){
		if(wrong == 0){
		tropheeMontre[nbrTropheeMontre] = 7;
		nbrTropheeMontre++;
		tropheeTemps = 200;
		tropheesPerso[7] = 1;
		afficheTrophee = 1;
		}
	}
	//a reussi une grille + de 5 min
	if(tropheesPerso[8] == 0){
		if(timer_getTimeSec() > 299){
		tropheeMontre[nbrTropheeMontre] = 8;
		nbrTropheeMontre++;
		tropheeTemps = 200;
		tropheesPerso[8] = 1;
		afficheTrophee = 1;
		}
	}
	//moins de 2 min
	if(tropheesPerso[9] == 0){
		if(recordsPerso[0] != 0 && recordsPerso[5] != 0 && recordsPerso[10] != 0 && recordsPerso[15] != 0){
			if(recordsPerso[0] < 120 && recordsPerso[5] < 120 && recordsPerso[10] < 120 && recordsPerso[15] < 120){
				tropheeMontre[nbrTropheeMontre] = 9;
				nbrTropheeMontre++;
				tropheeTemps = 200;
				tropheesPerso[9] = 1;
				afficheTrophee = 1;
			}
		}
	}
	//moins de 1 min
	if(tropheesPerso[10] == 0){
		if(recordsPerso[0] != 0 && recordsPerso[5] != 0 && recordsPerso[10] != 0 && recordsPerso[15] != 0){
			if(recordsPerso[0] < 60 && recordsPerso[5] < 60 && recordsPerso[10] < 60 && recordsPerso[15] < 60){
				tropheeMontre[nbrTropheeMontre] = 10;
				nbrTropheeMontre++;
				tropheeTemps = 200;
				tropheesPerso[10] = 1;
				afficheTrophee = 1;
			}
		}
	}
	//moins de 30 s
	if(tropheesPerso[11] == 0){
		if(recordsPerso[0] != 0 && recordsPerso[5] != 0 && recordsPerso[10] != 0 && recordsPerso[15] != 0){
			if(recordsPerso[0] < 30 && recordsPerso[5] < 30 && recordsPerso[10] < 30 && recordsPerso[15] < 30){
				tropheeMontre[nbrTropheeMontre] = 11;
				nbrTropheeMontre++;
				tropheeTemps = 200;
				tropheesPerso[11] = 1;
				afficheTrophee = 1;
			}
		}
	}
	// a réussi 1 grille dans chaque niveau
	if(tropheesPerso[12] == 0){
		if(tropheesPerso[3] == 1 && tropheesPerso[4] == 1 && tropheesPerso[5] == 1 && tropheesPerso[6] == 1){
			tropheeMontre[nbrTropheeMontre] = 12;
			nbrTropheeMontre++;
			tropheeTemps = 200;
			tropheesPerso[12] = 1;
			afficheTrophee = 1;
		}
	}
	// a réussi 10 grille dans chaque niveau
	if(tropheesPerso[13] == 0){
		int nbrF = 0;
		for(i=0;i<100;i++){
			nbrF = nbrF + grilleComplete[i];
		}
		int nbrM = 0;
		for(i=100;i<200;i++){
			nbrM = nbrM + grilleComplete[i];
		}
		int nbrD = 0;
		for(i=200;i<300;i++){
			nbrD = nbrD + grilleComplete[i];
		}
		int nbrE = 0;
		for(i=300;i<400;i++){
			nbrE = nbrE + grilleComplete[i];
		}
		
		if(nbrF > 9 && nbrM > 9 && nbrD > 9 && nbrE > 9){
			tropheeMontre[nbrTropheeMontre] = 13;
			nbrTropheeMontre++;
			tropheeTemps = 200;
			tropheesPerso[13] = 1;
			afficheTrophee = 1;
		}
	}
	// a réussi 50 grille dans chaque niveau
	if(tropheesPerso[14] == 0){
		int nbrF = 0;
		for(i=0;i<100;i++){
			nbrF = nbrF + grilleComplete[i];
		}
		int nbrM = 0;
		for(i=100;i<200;i++){
			nbrM = nbrM + grilleComplete[i];
		}
		int nbrD = 0;
		for(i=200;i<300;i++){
			nbrD = nbrD + grilleComplete[i];
		}
		int nbrE = 0;
		for(i=300;i<400;i++){
			nbrE = nbrE + grilleComplete[i];
		}
		
		if(nbrF > 49 && nbrM > 49 && nbrD > 49 && nbrE > 49){
			tropheeMontre[nbrTropheeMontre] = 14;
			nbrTropheeMontre++;
			tropheeTemps = 200;
			tropheesPerso[14] = 1;
			afficheTrophee = 1;
		}
	}
	// a réussi 100 grille dans chaque niveau
	if(tropheesPerso[15] == 0){
		int nbrF = 0;
		for(i=0;i<100;i++){
			nbrF = nbrF + grilleComplete[i];
		}
		int nbrM = 0;
		for(i=100;i<200;i++){
			nbrM = nbrM + grilleComplete[i];
		}
		int nbrD = 0;
		for(i=200;i<300;i++){
			nbrD = nbrD + grilleComplete[i];
		}
		int nbrE = 0;
		for(i=300;i<400;i++){
			nbrE = nbrE + grilleComplete[i];
		}
		
		if(nbrF == 100 && nbrM == 100 && nbrD == 100 && nbrE == 100){
			tropheeMontre[nbrTropheeMontre] = 15;
			nbrTropheeMontre++;
			tropheeTemps = 200;
			tropheesPerso[15] = 1;
			afficheTrophee = 1;
		}
	}
	// difficile sans rouges
	if(tropheesPerso[16] == 0){
		if(niveau == 2 && wrong == 0 && chiffresrouges == 0){
			tropheeMontre[nbrTropheeMontre] = 16;
			nbrTropheeMontre++;
			tropheeTemps = 200;
			tropheesPerso[16] = 1;
			afficheTrophee = 1;
		}
	}
	// evil sans rouges
	if(tropheesPerso[17] == 0){
		if(niveau == 3 && wrong == 0 && chiffresrouges == 0){
			tropheeMontre[nbrTropheeMontre] = 17;
			nbrTropheeMontre++;
			tropheeTemps = 200;
			tropheesPerso[17] = 1;
			afficheTrophee = 1;
		}
	}
	
	if (osl_keys->pressed.start && afficheTrophee == 0){ 
		
		timer_stop();
		timer_start();
		
		grilleCourante++;
		
		if(grilleCourante==100){
		niveau = 1;
		}
		if(grilleCourante==200){
		niveau = 2;
		}
		if(grilleCourante==300){
		niveau = 3;
		}
		
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
		
		etat = 1;
		reddot = 0;
		wrong = 0;
		recordenregistre = 0;
		nbrTropheeMontre = 0;
	}
	
}
else{
	//AFFICHAGE TIMER
	if(timer_getTimeSec() < 10){
		oslDrawStringf(5, 10, "0%llu:0%llu",timer_getTimeMin(),timer_getTimeSec());	
	}
	else{
		if(timer_getTimeMin() < 1){
			oslDrawStringf(5, 10, "0%llu:%llu",timer_getTimeMin(),timer_getTimeSec());	
		}
		else{
			if(timer_getTimeMin() < 10){
				if(timer_getTimeSec()-(timer_getTimeMin()*60) < 10){
					oslDrawStringf(5, 10, "0%llu:0%llu",timer_getTimeMin(),timer_getTimeSec()-(timer_getTimeMin()*60));
				}
				else{
					oslDrawStringf(5, 10, "0%llu:%llu",timer_getTimeMin(),timer_getTimeSec()-(timer_getTimeMin()*60));
				}
			}
			else{
				if(timer_getTimeSec()-(timer_getTimeMin()*60) < 10){
					oslDrawStringf(5, 10, "%llu:0%llu",timer_getTimeMin(),timer_getTimeSec()-(timer_getTimeMin()*60));
				}
				else{
					oslDrawStringf(5, 10, "%llu:%llu",timer_getTimeMin(),timer_getTimeSec()-(timer_getTimeMin()*60));
				}
			}
		}
	}
	//AFFICHAGE TIMER FIN
}

if(langue==0){
oslDrawStringf(5, 240, "Grille %d", grilleCourante+1);
}
if(langue==1){
oslDrawStringf(5, 240, "Grid %d", grilleCourante+1);
}


if(langue==0){
	if(niveau == 0){
		oslDrawString(5, 255, "Facile");
	}
	if(niveau == 1){
		oslDrawString(5, 255, "Moyen");
	}
	if(niveau == 2){
		oslDrawString(5, 255, "Difficile");
	}
	if(niveau == 3){
		oslDrawString(5, 255, "Evil");
	}
}
if(langue==1){
	if(niveau == 0){
		oslDrawString(5, 255, "Easy Mode");
	}
	if(niveau == 1){
		oslDrawString(5, 255, "Medium Mode");
	}
	if(niveau == 2){
		oslDrawString(5, 255, "Hard Mode");
	}
	if(niveau == 3){
		oslDrawString(5, 255, "Evil Mode");
	}
}



oslSetFont(pgfFont60r);
if(langue==0){oslDrawString(475, 258, "Triangle : Retour");} if(langue==1){oslDrawString(475, 258, "Triangle : Back");}