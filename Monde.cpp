/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <string>
#include <sstream>
#include <fstream>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "Menu.h"
#include "Texte.h"
#include "Joueur.h"
#include "Monde.h"
#include "Projectile.h"
#include "Jeu.h"
#include "Common.h"
#include "Keyboard.h"

Monde::Monde(Jeu* jeu) : largeur(0), hauteur(0), plafondmax(0), anim(0), animold(0), utile(0),
musique(0), gpJeu(jeu), animtransX(0), animtransY(0), animtransC(0), animtransT(0),
niveau(0), charge(1), avion(0), ovni(0), ecl1(0), ecl2(0), xecl1(0), xecl2(0), xfiltre(0), yfiltre(0),
afiltre(0) {
    
    for (int i = 0; i < 7; i++) {
        std::ostringstream im;
        im << (i+1);
        image[i] = gpJeu->loadImg(("data/images/motifs/image" + im.str() + ".png").c_str());
        SDL_SetColorKey(image[i],SDL_SRCCOLORKEY,SDL_MapRGB(image[i]->format,0,0,255));
    }
    
    imagetransit = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
    
    imagelevel = gpJeu->loadImg("data/images/menu/level.png");
    SDL_SetColorKey(imagelevel,SDL_SRCCOLORKEY,SDL_MapRGB(imagelevel->format,0,0,255));
    
    imageSpe[0] = gpJeu->loadImg("data/images/motifs/fond.png");
    imageSpe[1] = gpJeu->loadImg("data/images/motifs/fond2.png");
    imageSpe[2] = gpJeu->loadImg("data/images/motifs/fond3.png");
    imageSpe[3] = gpJeu->loadImg("data/images/motifs/eclair.png");
    imageSpe[4] = gpJeu->loadImg("data/images/motifs/pluie1.png");
    imageSpe[5] = gpJeu->loadImg("data/images/motifs/pluie2.png");
    imageSpe[6] = gpJeu->loadImg("data/images/motifs/pluie3.png");
    imageSpe[7] = gpJeu->loadImg("data/images/motifs/ciel.png");
    imageSpe[9] = gpJeu->loadImg("data/images/motifs/foret.png");
    imageSpe[10] = gpJeu->loadImg("data/images/motifs/foret2.png");
    imageSpe[11] = gpJeu->loadImg("data/images/motifs/foret3.png");
    imageSpe[12] = gpJeu->loadImg("data/images/motifs/neige1.png");
    imageSpe[13] = gpJeu->loadImg("data/images/motifs/neige2.png");
    imageSpe[14] = gpJeu->loadImg("data/images/motifs/neige3.png");
    imageSpe[15] = gpJeu->loadImg("data/images/motifs/jurassic.png");
    imageSpe[16] = gpJeu->loadImg("data/images/motifs/apocalypse.png");
    imageSpe[17] = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
    SDL_FillRect(imageSpe[17], NULL, SDL_MapRGB(imageSpe[17]->format, 0, 0, 255));
    imageSpe[18] = gpJeu->loadImg("data/images/motifs/deesses.png");
    
    SDL_SetAlpha(imageSpe[9], SDL_SRCALPHA, 128);
    SDL_SetAlpha(imageSpe[10], SDL_SRCALPHA, 128);
    SDL_SetAlpha(imageSpe[11], SDL_SRCALPHA, 128);
    SDL_SetAlpha(imageSpe[17], SDL_SRCALPHA, 128);
    
    for (int i = 3; i < 8; i++)
        SDL_SetColorKey(imageSpe[i],SDL_SRCCOLORKEY,SDL_MapRGB(imageSpe[i]->format,0,0,255));
    for (int i = 12; i < 15; i++)
        SDL_SetColorKey(imageSpe[i],SDL_SRCCOLORKEY,SDL_MapRGB(imageSpe[i]->format,0,0,255));
    
    changeZone(gpJeu->getZone());
    
    charge=0;
}

Monde::~Monde() {
    for (int i = 0; i < 7; i++) SDL_FreeSurface(image[i]);
    SDL_FreeSurface(imagetransit);
    SDL_FreeSurface(imagelevel);
    for (int i = 0; i < 19; i++) {
        if (i != 8) {
            SDL_FreeSurface(imageSpe[i]);
        }
    }
}

void Monde::changeZone(int newZone) {
    
    //à virer
    //if (gpJeu->getZone()==60) {mapper(gpJeu->getZone()); corrigeMap(gpJeu->getZone());}

    //else 
    chargeMap(newZone);
    
    initMatrice(newZone);
    
    detRegion(newZone);
    
    lastAnimTime = SDL_GetTicks();
}

void Monde::corrigeMap(int zone) {
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    switch(zone) {
        case 1 :
            if (gpJoueur->getCoffre(15, 0)) passage(59,10,5); break;
        case 4 :  
            if (!gpJoueur->getCoffre(15, 2)) {
                for (int j = 0; j < 11; j++) for (int i = 0; i < 42; i++)
                    setValeur((19+i)*16,(22+j)*16,4386,0,0);
                for (int j = 0; j < 7; j++) for (int i = 0; i < 42; i++)
                    setValeur((19+i)*16,(38+j)*16,4386,0,0);
                for (int j = 0; j < 5; j++) for (int i = 0; i < 40; i++)
                    setValeur((20+i)*16,(33+j)*16,4386,0,0);
                for (int j = 0; j < 3; j++) for (int i = 0; i < 16; i++)
                    setValeur((32+i)*16,(45+j)*16,4386,0,0);
                map[22][28]=4385; map[25][24]=4385; map[25][34]=4385;
                map[26][41]=4385; map[28][37]=4385; map[30][31]=4385;
                map[33][25]=4385; map[34][36]=4385; map[36][43]=4385;
                map[38][38]=4385; map[39][32]=4385; map[41][45]=4385;
                map[42][25]=4385; map[44][36]=4385; map[47][41]=4385;
                map[48][30]=4385; map[51][26]=4385; map[52][33]=4385;
                map[53][37]=4385; map[55][24]=4385; map[56][28]=4385;
                map[56][42]=4385; map[57][34]=4385;
                
                map[39][36]=1408; map[40][36]=1409;
                map[38][37]=1410; map[39][37]=1411; map[40][37]=1412; map[41][37]=1413;
                map[38][38]=1414; map[39][38]=1415; map[40][38]=1414; map[41][38]=1415;
            }
            break;
        case 6 :
            //cristal 5
            if(!gpJoueur->hasCristal(4)) setValeur(48*16,42*16,303,-1,PLEIN,C_CRISTAL);
            else setValeur(48*16,42*16,304,-1,PLEIN,C_RIEN);
            break;
        case 8 :
            //cristal 1
            if(!gpJoueur->hasCristal(0)) setValeur(75*16,20*16,303,-1,PLEIN,C_CRISTAL);
            else setValeur(75*16,20*16,304,-1,PLEIN,C_RIEN);
            break;
        case 9 :
            //cristal 7
            if(!gpJoueur->hasCristal(6)) setValeur(136*16,22*16,303,-1,PLEIN,C_CRISTAL);
            else setValeur(136*16,22*16,304,-1,PLEIN,C_RIEN);
            break;
        case 12 :
            //cristal 2
            if(!gpJoueur->hasCristal(1)) setValeur(101*16,3*16,303,-1,PLEIN,C_CRISTAL);
            else setValeur(101*16,3*16,304,-1,PLEIN,C_RIEN);
            break;
        case 15 :
            //cristal 6
            if(!gpJoueur->hasCristal(5)) setValeur(59*16,48*16,303,-1,PLEIN,C_CRISTAL);
            else setValeur(59*16,48*16,304,-1,PLEIN,C_RIEN);
            if (gpJoueur->getCoffre(15, 5)) passage(121,34,2);
            break;
        case 18 :
            if (gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_UTILISE
            && gpJoueur->getAvancement()<PONT_CONSTRUIT) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 6; j++) {
                        map[66+i][j]=map[79][j+5];
                        mur[(66+i)*2][j*2]=mur[79*2][(j+5)*2];
                        mur[(66+i)*2+1][j*2]=mur[79*2+1][(j+5)*2];
                        mur[(66+i)*2][j*2+1]=mur[79*2][(j+5)*2+1];
                        mur[(66+i)*2+1][j*2+1]=mur[79*2+1][(j+5)*2+1];
                    }
                }
            }
            break;
        case 21 :
            if (gpJoueur->getCoffre(15,27)==15) {
                for (int i = 0; i < 8; i++) 
                    for (int j = 0; j < 9; j++) {
                        setValeur((13+i)*16,(62+j)*16,0,0,0);
                    }
            }
            break;
        case 22 :
            if (gpJoueur->getTroc(M_ROUAGE)==0 
            && (gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_UTILISE
            || gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_FERME)) {
                for (int j = 0; j < 8; j++) for (int i = 0; i < 6; i++)
                    setValeur((25+i)*16,(15+j)*16,4639,0);
                for (int j = 0; j < 8; j++) {
                    setValeur(24*16,(15+j)*16,4638,0);
                    mur[24*2][(15+j)*2]=1; mur[24*2][(15+j)*2+1]=1;
                    setValeur(31*16,(15+j)*16,4640,0);
                    mur[31*2+1][(15+j)*2]=1; mur[31*2+1][(15+j)*2+1]=1;
                }
            }
            break;
        case 23 :
            if (gpJoueur->getCoffre(15, 4)) passage(58,18,1); break;
        case 26 :
            if (!gpJoueur->hasObjet(O_PALMES)) barque(gpJoueur->getPosBarqueOld(), true);
            break;
        case 37 :
            if (gpJoueur->getCoffre(15, 3)) {
                setValeur(88*16,8*16, 999, 1545, 0);
                setValeur(88*16,9*16, 999, 1576, 0);
                setValeur(88*16,10*16, 1571, 1573, 0);
                setValeur(88*16,11*16, 1572, 0);
            }
            break;
        case 44 :
            if (!gpJoueur->hasObjet(O_FFEU) || !gpJoueur->hasObjet(O_FGLACE)
            || !gpJoueur->hasObjet(O_FLUM) || !gpJoueur->hasBouteille(3)) break;
            setValeur(31*16,29*16, 1848, 0);
            for (int i = 0; i < 6; i++) setValeur((32+i)*16,29*16, 1849, 0);
            setValeur(38*16,29*16, 1850, 0);
            for (int j = 0; j < 8; j++) {
            setValeur(31*16,(30+j)*16, 1851, 0);
            for (int i = 0; i < 6; i++) setValeur((32+i)*16,(30+j)*16, 1852, 0);
            setValeur(38*16,(30+j)*16, 1853, 0);}
            setValeur(31*16,38*16, 1854, 0);
            for (int i = 0; i < 6; i++) setValeur((32+i)*16,38*16, 1855, 0);
            setValeur(38*16,38*16, 1856, 0);
            for (int i = 0; i < 20; i++) {mur[31*2][29*2+i]=2; mur[38*2+1][29*2+i]=2;}
            for (int i = 0; i < 16; i++) {mur[31*2][29*2+i+2]=GAUCHE; mur[38*2+1][29*2+i+2]=DROITE;}
            break;
        case 45 :
            if (gpJoueur->getNbGemmes() < 200) {
            map[99+9][4]=map[99+11][4];
            map[99+10][4]=map[99+8][4];
            map[99+8][5]=map[99+6][5];
            map[99+9][5]=map[99+13][5];
            map[99+10][5]=map[99+6][5];
            map[99+11][5]=map[99+13][5];
            for (int i = 0; i < 4; i++) {setValeur((99+8+i)*16,6*16,999,map[99+6][6],1);}
            for (int i = 0; i < 16; i++) {mur[(99+9)*2+1][i]=1; mur[(99+9)*2+2][i]=1;}}
            break;
        case 46 :
            //carte
            if(!gpJoueur->getCle(0,0)) setValeur(70*16,51*16,303,-1,PLEIN,C_CARTE_D);
            else setValeur(70*16,51*16,304,-1,PLEIN,C_RIEN);
            //boussole
            if(!gpJoueur->getCle(0,1)) setValeur(229*16,34*16,303,-1,PLEIN,C_BOUSSOLE);
            else setValeur(229*16,34*16,304,-1,PLEIN,C_RIEN);
            //cle boss
            if(!gpJoueur->getCle(0,2)) setValeur(270*16,6*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(270*16,6*16,304,-1,PLEIN,C_RIEN);
            //cles
            if(!gpJoueur->getCoffre(0,17)) setValeur(70*16,36*16,303,-1,PLEIN,C_CLE);
            else setValeur(70*16,36*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(0,18)) setValeur(190*16,6*16,303,-1,PLEIN,C_CLE);
            else setValeur(190*16,6*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(0,19)) setValeur(268*16,20*16,303,-1,PLEIN,C_CLE);
            else setValeur(268*16,20*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(0,20)) setValeur(310*16,21*16,303,-1,PLEIN,C_CLE);
            else setValeur(310*16,21*16,304,-1,PLEIN,C_RIEN);
            //arc
            if (!gpJoueur->hasObjet(O_ARC)) setValeur(29*16,36*16,303,-1,PLEIN,C_ARC);
            else setValeur(29*16,36*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(0,0)) passage(249,30,0);
            //portes
            if (gpJoueur->getCoffre(0,1)) {passage(169,30,0); map[166][34]=1005;}
            if (gpJoueur->getCoffre(0,2)) {passage(209,45,0); map[212][41]=1005;}
            if (gpJoueur->getCoffre(0,3)) {passage(300,36,1); map[310][40]=1005;}
            if (gpJoueur->getCoffre(0,4)) {passage(300,21,1); map[304][17]=1005;}
            if (gpJoueur->getCoffre(0,5)) {passage(29,30,0); map[33][34]=1005;}
            if (gpJoueur->getCoffre(0,6)) {passage(29,45,0); map[33][40]=1005;}
            if (gpJoueur->getCoffre(0,7)) {passage(69,45,0); map[64][37]=1005;}
            if (gpJoueur->getCoffre(0,8)) {passage(69,15,0); map[73][11]=1005;}
            if (gpJoueur->getCoffre(0,9)) {passage(100,21,1); map[104][26]=1005;}
            if (gpJoueur->getCoffre(0,10)) {passage(109,45,0); map[113][41]=1005;}
            if (gpJoueur->getCoffre(0,11)) {passage(140,6,1); map[123][7]=1005;}
            if (gpJoueur->getCoffre(0,12)) passage(89,45,0);
            if (gpJoueur->getCoffre(0,13)) passage(100,6,1);
            if (gpJoueur->getCoffre(0,14)) passage(129,15,0);
            if (gpJoueur->getCoffre(0,15)) passage(220,6,1);
            if (gpJoueur->getCoffre(0,16)) passage(280,6,1);
            if (gpJoueur->getCoffre(0,22)) passage(20,36,1);
            break;
        case 47 :
            //carte
            if(!gpJoueur->getCle(1,0)) setValeur(307*16,81*16,303,-1,PLEIN,C_CARTE_D);
            else setValeur(307*16,81*16,304,-1,PLEIN,C_RIEN);
            //boussole
            if(!gpJoueur->getCle(1,1)) setValeur(270*16,51*16,303,-1,PLEIN,C_BOUSSOLE);
            else setValeur(270*16,51*16,304,-1,PLEIN,C_RIEN);
            //cle boss
            if(!gpJoueur->getCle(1,2)) setValeur(299*16,44*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(299*16,44*16,304,-1,PLEIN,C_RIEN);
            //cles
            if(!gpJoueur->getCoffre(1,10)) setValeur(169*16,22*16,303,-1,PLEIN,C_CLE);
            else setValeur(169*16,22*16,304,-1,PLEIN,C_RIEN);
            if(gpJoueur->getCoffre(1,11)) setValeur(204*16,34*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(1,12)) setValeur(250*16,81*16,303,-1,PLEIN,C_CLE);
            else setValeur(250*16,81*16,304,-1,PLEIN,C_RIEN);
            if(gpJoueur->getCoffre(1,13)) setValeur(334*16,33*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(1,14)) setValeur(350*16,6*16,303,-1,PLEIN,C_CLE);
            else setValeur(350*16,6*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(1,16)) setValeur(287*16,39*16,303,-1,PLEIN,C_CLE);
            else setValeur(287*16,39*16,304,-1,PLEIN,C_RIEN);
            //gants
            if (gpJoueur->hasObjet(O_GANTS)) setValeur(323*16,63*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(1,0)) passage(349,45,0);
            //portes
            if (gpJoueur->getCoffre(1,1)) passage(149,75,0);
            if (gpJoueur->getCoffre(1,2)) passage(189,15,0);
            if (gpJoueur->getCoffre(1,3)) passage(209,45,0);
            if (gpJoueur->getCoffre(1,4)) passage(260,6,1);
            if (gpJoueur->getCoffre(1,5)) passage(329,30,0);
            if (gpJoueur->getCoffre(1,6)) {passage(260,51,1); contenu[257][49]=51;}
            if (gpJoueur->getCoffre(1,7)) {passage(289,30,0); map[283][24]=1005;}
            if (gpJoueur->getCoffre(1,8)) {passage(320,36,1); map[314][33]=1005;}
            if (gpJoueur->getCoffre(1,9)) {passage(340,66,1); map[336][69]=1005;}
            if (gpJoueur->getCoffre(1,10)) passage(180,21,1);
            if (gpJoueur->getCoffre(1,15)) passage(329,60,0);
            if (gpJoueur->getCoffre(1,17)) passage(129,75,0);
            if(gpJoueur->getCoeur(1)==1) {
                setValeur(349*16,36*16,3084,0); setValeur(350*16,36*16,3084,0);
                setValeur(349*16,37*16,3084,0); setValeur(350*16,37*16,3084,0);
                setValeur(349*16,38*16,3084,0); setValeur(350*16,38*16,3084,0);
            }
            break;
        case 48 :
            //carte
            if (gpJoueur->getCoffre(2,16)) {
                if(!gpJoueur->getCle(2,0)) setValeur(36*16,33*16,303,-1,PLEIN,C_CARTE_D);
                else setValeur(36*16,33*16,304,-1,PLEIN,C_RIEN);
            }
            //boussole
            if (gpJoueur->getCoffre(2,19)) {
                if(!gpJoueur->getCle(2,1)) setValeur(244*16,33*16,303,-1,PLEIN,C_BOUSSOLE);
                else setValeur(244*16,33*16,304,-1,PLEIN,C_RIEN);
            }
            //cle boss
            if(!gpJoueur->getCle(2,2)) setValeur(210*16,5*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(210*16,5*16,304,-1,PLEIN,C_RIEN);
            //cles
            if (gpJoueur->getCoffre(2,17)) {
                if(!gpJoueur->getCoffre(2,8)) setValeur(216*16,62*16,303,-1,PLEIN,C_CLE);
                else setValeur(216*16,62*16,304,-1,PLEIN,C_RIEN);
            }
            if (gpJoueur->getCoffre(2,18)) {
                if(!gpJoueur->getCoffre(2,12)) setValeur(69*16,66*16,303,-1,PLEIN,C_CLE);
                else setValeur(69*16,66*16,304,-1,PLEIN,C_RIEN);
            }
            if(!gpJoueur->getCoffre(2,9)) setValeur(70*16,5*16,303,-1,PLEIN,C_CLE);
            else setValeur(70*16,5*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(2,10)) setValeur(235*16,48*16,303,-1,PLEIN,C_CLE);
            else setValeur(235*16,48*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(2,11)) setValeur(88*16,37*16,303,-1,PLEIN,C_CLE);
            else setValeur(88*16,37*16,304,-1,PLEIN,C_RIEN);
            if (gpJoueur->getCoffre(2,35) && gpJoueur->getCoffre(2,36)) {
                if(!gpJoueur->getCoffre(2,13)) setValeur(75*16,40*16,303,-1,PLEIN,C_CLE);
                else setValeur(75*16,40*16,304,-1,PLEIN,C_RIEN);
            }
            //lanterne
            if (!gpJoueur->hasObjet(O_LANTERNE)) setValeur(130*16,21*16,303,-1,PLEIN,C_LANTERNE);
            else setValeur(130*16,21*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(2,0)) passage(9,45,0);
            //portes
            if (gpJoueur->getCoffre(2,1)) passage(60,66,1);
            if (gpJoueur->getCoffre(2,2)) passage(80,66,1);
            if (gpJoueur->getCoffre(2,3)) passage(129,45,0);
            if (gpJoueur->getCoffre(2,4)) passage(169,45,0);
            if (gpJoueur->getCoffre(2,5)) passage(229,60,0);
            if (gpJoueur->getCoffre(2,6)) passage(240,66,1);
            if (gpJoueur->getCoffre(2,7)) passage(289,15,4);
            if (gpJoueur->getCoffre(2,14)) {
                if (gpJoueur->getCoffre(2,20)) {passage(189,15,0); map[195][12]=1005;}
                else map[195][12]=1004;
            }
            if (gpJoueur->getCoffre(2,15)) {
                if (gpJoueur->getCoffre(2,21)) {passage(60,6,1); map[57][3]=1005;}
                else map[57][3]=1004;
            }
            if (gpJoueur->getCoffre(2,22)) {passage(69,15,0); map[75][12]=1005; 
                        map[68][17]=1001; map[71][17]=1001;}
            if (gpJoueur->getCoffre(2,23)) {passage(69,60,0); map[67][57]=1005;}
            if (gpJoueur->getCoffre(2,24)) {passage(89,15,0); map[84][10]=1005;}
            if (gpJoueur->getCoffre(2,25)) {passage(109,60,0); map[103][52]=1005;}
            if (gpJoueur->getCoffre(2,26)) {passage(149,60,0); map[147][57]=1005;}
            if (gpJoueur->getCoffre(2,27)) {passage(180,21,1); map[189][20]=1005;}
            if (gpJoueur->getCoffre(2,28)) {passage(180,51,1); map[184][55]=1005;}
            if (gpJoueur->getCoffre(2,29)) {passage(209,60,0); map[207][56]=1005;}
            if (gpJoueur->getCoffre(2,30)) {passage(240,36,1); map[236][37]=1005;}
            if (gpJoueur->getCoffre(2,31) && gpJoueur->getCoffre(2,32)) passage(40,51,1);
            if (gpJoueur->getCoffre(2,33) && gpJoueur->getCoffre(2,34)) passage(69,30,0);
            if (gpJoueur->getCoffre(2,37) && gpJoueur->getCoffre(2,38)) passage(100,36,1);
            if (gpJoueur->getCoffre(2,39)) passage(100,6,1);
            if (gpJoueur->getCoffre(2,40) && gpJoueur->getCoffre(2,41)) passage(129,15,0);
            if (gpJoueur->getCoffre(2,42) && gpJoueur->getCoffre(2,43) 
            && gpJoueur->getCoffre(2,44) && gpJoueur->getCoffre(2,45) 
            && gpJoueur->getCoffre(2,46) && gpJoueur->getCoffre(2,47) 
            && gpJoueur->getCoffre(2,48) && gpJoueur->getCoffre(2,49) 
            && gpJoueur->getCoffre(2,50) && gpJoueur->getCoffre(2,51) 
            && gpJoueur->getCoffre(2,52) && gpJoueur->getCoffre(2,53) 
            && gpJoueur->getCoffre(2,54) && gpJoueur->getCoffre(2,55) 
            && gpJoueur->getCoffre(2,56)) passage(209,15,0);
            if (gpJoueur->getCoffre(2,57) && gpJoueur->getCoffre(2,58)) passage(240,51,1);
            if (gpJoueur->getCoffre(2,59) && gpJoueur->getCoffre(2,60)) passage(249,60,0);
            //torches allumées
            if (gpJoueur->getCoffre(2,31)) map[37][50]=1001;
            if (gpJoueur->getCoffre(2,32)) map[37][54]=1001;
            if (gpJoueur->getCoffre(2,33)) map[68][27]=1001;
            if (gpJoueur->getCoffre(2,34)) map[71][27]=1001;
            if (gpJoueur->getCoffre(2,35)) map[69][41]=1001;
            if (gpJoueur->getCoffre(2,36)) map[70][41]=1001;
            if (gpJoueur->getCoffre(2,37)) map[102][35]=1001;
            if (gpJoueur->getCoffre(2,38)) map[102][39]=1001;
            if (gpJoueur->getCoffre(2,39)) map[109][7]=1001;
            if (gpJoueur->getCoffre(2,40)) map[127][17]=1001;
            if (gpJoueur->getCoffre(2,41)) map[132][17]=1001;
            if (gpJoueur->getCoffre(2,42)) map[186][26]=1001;
            if (gpJoueur->getCoffre(2,43)) map[191][49]=1001;
            if (gpJoueur->getCoffre(2,44)) map[191][34]=1001;
            if (gpJoueur->getCoffre(2,45)) map[196][34]=1001;
            if (gpJoueur->getCoffre(2,46)) map[207][24]=1001;
            if (gpJoueur->getCoffre(2,47)) map[212][24]=1001;
            if (gpJoueur->getCoffre(2,48)) map[204][35]=1001;
            if (gpJoueur->getCoffre(2,49)) map[215][35]=1001;
            if (gpJoueur->getCoffre(2,50)) map[206][51]=1001;
            if (gpJoueur->getCoffre(2,51)) map[213][51]=1001;
            if (gpJoueur->getCoffre(2,52)) map[224][20]=1001;
            if (gpJoueur->getCoffre(2,53)) map[234][26]=1001;
            if (gpJoueur->getCoffre(2,54)) map[229][37]=1001;
            if (gpJoueur->getCoffre(2,55)) map[227][56]=1001;
            if (gpJoueur->getCoffre(2,56)) map[234][53]=1001;
            if (gpJoueur->getCoffre(2,57)) map[242][49]=1001;
            if (gpJoueur->getCoffre(2,58)) map[242][55]=1001;
            if (gpJoueur->getCoffre(2,59)) map[247][57]=1001;
            if (gpJoueur->getCoffre(2,60)) map[252][57]=1001;
            //salle mini boss
            if (!gpJoueur->getCoffre(2,61)) {
                for (int i = 0; i < 4; i++) {
                    setValeur((128+i)*16,34*16,3262,2);
                    setValeur((128+i)*16,40*16,3262,2);
                    map[124][33]=1004; map[129][33]=1004; map[135][33]=1004;
                    map[126][42]=1005; map[133][42]=1005;
                }
            } else passage(129,30,0);
            //salle boss
            if (gpJoueur->getCoeur(2)) {
                passage(3,33,5); passage(144,34,6); passage(288,35,7);
                map[9][32]=3416; map[289][40]=3417;
            }
            break;
        case 49 :
            //carte
            if (gpJoueur->getCoffre(3,28)) {
                if(!gpJoueur->getCle(3,0)) setValeur(103*16,83*16,303,-1,PLEIN,C_CARTE_D);
                else setValeur(103*16,83*16,304,-1,PLEIN,C_RIEN);
            }
            //boussole
            if(!gpJoueur->getCle(3,1)) setValeur(29*16,25*16,303,-1,PLEIN,C_BOUSSOLE);
            else setValeur(29*16,25*16,304,-1,PLEIN,C_RIEN);
            //cle boss
            if(!gpJoueur->getCle(3,2)) setValeur(70*16,21*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(70*16,21*16,304,-1,PLEIN,C_RIEN);
            //cles
            if(!gpJoueur->getCoffre(3,1)) setValeur(119*16,5*16,303,-1,PLEIN,C_CLE);
            else setValeur(119*16,5*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(3,2)) setValeur(84*16,68*16,303,-1,PLEIN,C_CLE);
            else setValeur(84*16,68*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(3,3)) setValeur(70*16,7*16,303,-1,PLEIN,C_CLE);
            else setValeur(70*16,7*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(3,4)) setValeur(210*16,67*16,303,-1,PLEIN,C_CLE);
            else setValeur(210*16,67*16,304,-1,PLEIN,C_RIEN);
            //palmes
            if (!gpJoueur->hasObjet(O_PALMES)) setValeur(90*16,6*16,303,-1,PLEIN,C_PALMES);
            else setValeur(90*16,6*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(3,0)) passage(199,45,0);
            //portes
            if (gpJoueur->getCoffre(3,5)) passage(49,60,0);
            if (gpJoueur->getCoffre(3,6)) passage(69,30,0);
            if (gpJoueur->getCoffre(3,7)) passage(120,51,1);
            if (gpJoueur->getCoffre(3,8)) passage(129,45,0);
            if (gpJoueur->getCoffre(3,9)) {passage(29,30,0); map[30][21]=1005;}
            if (gpJoueur->getCoffre(3,10)) {passage(60,51,1); map[62][55]=1005;}
            if (gpJoueur->getCoffre(3,11) && gpJoueur->getCoffre(3,12)) passage(120,36,1);
            if (gpJoueur->getCoffre(3,13)) {passage(100,66,1); map[88][71]=1005;}
            if (gpJoueur->getCoffre(3,14)) {passage(89,30,0); map[82][32]=1005;}
            if (gpJoueur->getCoffre(3,15)) {passage(149,75,0); map[155][69]=1005;}
            if (gpJoueur->getCoffre(3,16)) {passage(160,81,1); map[157][85]=1005;}
            if (gpJoueur->getCoffre(3,17)) {passage(160,6,1); map[162][5]=1005;}
            if (gpJoueur->getCoffre(3,18)) {passage(229,75,0); map[228][62]=1005;}
            if (gpJoueur->getCoffre(3,19) && gpJoueur->getCoffre(3,20)
            && gpJoueur->getCoffre(3,21) && gpJoueur->getCoffre(3,22)
            && gpJoueur->getCoffre(3,23) && gpJoueur->getCoffre(3,24)
            && gpJoueur->getCoffre(3,25) && gpJoueur->getCoffre(3,26)) passage(240,6,1);
            if (gpJoueur->getCoffre(3,27)) passage(89,15,0);
            //torches allumées
            if (gpJoueur->getCoffre(3,11)) map[117][35]=1001;
            if (gpJoueur->getCoffre(3,12)) map[117][39]=1001;
            if (gpJoueur->getCoffre(3,19)) map[228][27]=1001;
            if (gpJoueur->getCoffre(3,20)) map[231][27]=1001;
            if (gpJoueur->getCoffre(3,21)) map[237][19]=1001;
            if (gpJoueur->getCoffre(3,22)) map[222][21]=1001;
            if (gpJoueur->getCoffre(3,23)) map[222][9]=1001;
            if (gpJoueur->getCoffre(3,24)) map[230][2]=1001;
            if (gpJoueur->getCoffre(3,25)) map[237][5]=1001;
            if (gpJoueur->getCoffre(3,26)) map[237][9]=1001;
            break;
        case 50 :
            //carte
            if(!gpJoueur->getCle(4,0)) setValeur(250*16,82*16,303,-1,PLEIN,C_CARTE_D);
            else setValeur(250*16,82*16,304,-1,PLEIN,C_RIEN);
            //boussole
            if (gpJoueur->getCoffre(4,27)) {
                if(!gpJoueur->getCle(4,1)) setValeur(49*16,37*16,303,-1,PLEIN,C_BOUSSOLE);
                else setValeur(49*16,37*16,304,-1,PLEIN,C_RIEN);
            }
            //cle boss
            if(!gpJoueur->getCle(4,2)) setValeur(130*16,37*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(130*16,37*16,304,-1,PLEIN,C_RIEN);
            //cles
            if (gpJoueur->getCoffre(4,24)) {
                if(!gpJoueur->getCoffre(4,6)) setValeur(84*16,49*16,303,-1,PLEIN,C_CLE);
                else setValeur(84*16,49*16,304,-1,PLEIN,C_RIEN);
                map[89][56]=1005;
            }
            if(!gpJoueur->getCoffre(4,7)) setValeur(150*16,51*16,303,-1,PLEIN,C_CLE);
            else setValeur(150*16,51*16,304,-1,PLEIN,C_RIEN);
            if (gpJoueur->getCoffre(4,25)) {
                if(!gpJoueur->getCoffre(4,8)) setValeur(290*16,37*16,303,-1,PLEIN,C_CLE);
                else setValeur(290*16,37*16,304,-1,PLEIN,C_RIEN);
            }
            if (gpJoueur->getCoffre(4,26)) {
                if(!gpJoueur->getCoffre(4,9)) setValeur(300*16,90*16,303,-1,PLEIN,C_CLE);
                else setValeur(300*16,90*16,304,-1,PLEIN,C_RIEN);
            }
            //tunique bleue
            if (gpJoueur->getTunique()<2) setValeur(170*16,37*16,303,-1,PLEIN,C_TUNIQUE_BLEUE);
            else setValeur(170*16,37*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(4,0)) passage(249,30,0);
            //portes
            if (gpJoueur->getCoffre(4,1)) passage(49,60,0);
            if (gpJoueur->getCoffre(4,2)) passage(100,36,1);
            if (gpJoueur->getCoffre(4,3)) passage(100,81,1);
            if (gpJoueur->getCoffre(4,4)) passage(169,60,0);
            if (gpJoueur->getCoffre(4,5)) passage(100,66,3);
            if (gpJoueur->getCoffre(4,10)) passage(280,21,3);
            if (gpJoueur->getCoffre(4,11)) passage(209,30,4);
            if (gpJoueur->getCoffre(4,12)) passage(289,75,4);
            if (gpJoueur->getCoffre(4,13)) {passage(60,66,1); map[43][67]=1005;}
            if (gpJoueur->getCoffre(4,14)) {passage(129,30,0); map[134][34]=1005;}
            if (gpJoueur->getCoffre(4,15)) {passage(160,66,1); map[150][63]=1005;}
            if (gpJoueur->getCoffre(4,16)) {passage(160,81,1); map[162][79]=1005;}
            if (gpJoueur->getCoffre(4,17)) {passage(169,30,0); map[167][32]=1005;}
            if (gpJoueur->getCoffre(4,18)) {passage(189,75,0); map[196][67]=1005;}
            if (gpJoueur->getCoffre(4,19)) {passage(209,75,0); map[204][81]=1005;}
            if (gpJoueur->getCoffre(4,20)) {passage(249,75,0); map[247][79]=1005;}
            if (gpJoueur->getCoffre(4,21)) {passage(260,36,1); map[243][37]=1005;}
            if (gpJoueur->getCoffre(4,22)) {passage(249,90,0); map[256][97]=1005;}
            if (gpJoueur->getCoffre(4,23)) {passage(289,60,0); map[283][52]=1005;}
            if (gpJoueur->getCoffre(4,28)) passage(6,51,8);
            if (gpJoueur->getCoffre(4,29)) passage(24,54,8);
            if (gpJoueur->getCoffre(4,30)) passage(28,51,8);
            if (gpJoueur->getCoffre(4,31)) passage(33,49,8);
            if (gpJoueur->getCoffre(4,32)) passage(35,53,8);
            if (gpJoueur->getCoffre(4,33)) passage(64,53,8);
            if (gpJoueur->getCoffre(4,34)) passage(69,52,8);
            if (gpJoueur->getCoffre(4,35)) passage(73,49,8);
            if (gpJoueur->getCoffre(4,36)) passage(74,53,8);
            if (gpJoueur->getCoffre(4,37)) passage(269,6,8);
            //torches
            if (gpJoueur->getCoffre(4,38)) {
                map[162][47]=1001; map[177][47]=1001;
                map[162][57]=1001; map[177][57]=1001;
                passage(169,45,0);
            }
            break;
        case 51 :
            //carte
            if(!gpJoueur->getCle(5,0)) setValeur(170*16,21*16,303,-1,PLEIN,C_CARTE_D);
            else setValeur(170*16,21*16,304,-1,PLEIN,C_RIEN);
            //boussole
            if (gpJoueur->getCoffre(5,25)) {
                if(!gpJoueur->getCle(5,1)) setValeur(150*16,21*16,303,-1,PLEIN,C_BOUSSOLE);
                else setValeur(150*16,21*16,304,-1,PLEIN,C_RIEN);
            }
            //cle boss
            if(!gpJoueur->getCle(5,2)) setValeur(90*16,21*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(90*16,21*16,304,-1,PLEIN,C_RIEN);
            //cles
            if(!gpJoueur->getCoffre(5,4)) setValeur(110*16,65*16,303,-1,PLEIN,C_CLE);
            else setValeur(110*16,65*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(5,5)) setValeur(230*16,6*16,303,-1,PLEIN,C_CLE);
            else setValeur(230*16,6*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(5,6)) setValeur(270*16,6*16,303,-1,PLEIN,C_CLE);
            else setValeur(270*16,6*16,304,-1,PLEIN,C_RIEN);
            //marteau
            if (!gpJoueur->hasObjet(O_MARTEAU)) setValeur(250*16,5*16,303,-1,PLEIN,C_MARTEAU);
            else setValeur(250*16,5*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(5,0)) passage(249,45,0);
            //boss vaincu
            if(gpJoueur->getCoeur(5)) {
                setValeur(249*16,22*16,2076,0); setValeur(250*16,22*16,2076,0);
                setValeur(249*16,25*16,2076,0); setValeur(250*16,25*16,2076,0);
            }
            //portes
            if (gpJoueur->getCoffre(5,1)) passage(89,30,0);
            if (gpJoueur->getCoffre(5,2)) passage(109,75,0);
            if (gpJoueur->getCoffre(5,3)) passage(140,36,1);
            if (gpJoueur->getCoffre(5,8)) {passage(40,66,1); map[37][70]=1005;}
            if (gpJoueur->getCoffre(5,9)) {passage(69,60,0); map[67][57]=1005;}
            if (gpJoueur->getCoffre(5,10)) {passage(100,66,1); map[97][64]=1005;}
            if (gpJoueur->getCoffre(5,11)) {passage(109,30,0); map[108][21]=1005;}
            if (gpJoueur->getCoffre(5,12)) {passage(129,60,0); map[127][57]=1005;}
            if (gpJoueur->getCoffre(5,13)) {passage(129,75,0); map[136][82]=1005;}
            if (gpJoueur->getCoffre(5,14)) {passage(140,66,1); map[149][72]=1005;}
            if (gpJoueur->getCoffre(5,15)) {passage(200,51,1); map[216][52]=1005;}
            if (gpJoueur->getCoffre(5,16)) {passage(209,60,0); contenu[217][57]=51;}
            if (gpJoueur->getCoffre(5,17)) {passage(229,75,0); map[229][85]=1005;}
            if (gpJoueur->getCoffre(5,18)) {passage(249,90,0); map[246][92]=1005;}
            if (gpJoueur->getCoffre(5,19)) {passage(269,60,0); map[263][67]=1005;}
            if (gpJoueur->getCoffre(5,20)) {passage(289,30,0); map[295][25]=1005;}
            if (gpJoueur->getCoffre(5,21)) {passage(289,60,0); contenu[285][57]=51;}
            if (gpJoueur->getCoffre(5,22)) {passage(300,66,1); map[302][64]=1005;}
            if (gpJoueur->getCoffre(5,23)) passage(309,75,4);
            if (gpJoueur->getCoffre(5,24)) passage(129,30,0);
            if (gpJoueur->getCoffre(5,26)) passage(120,81,3);
            //sol
            if (gpJoueur->getCoffre(5,7)) {
                rempli(42,64,4,7); rempli(64,35,2,5); 
                rempli(62,62,15,11); rempli(84,37,12,4);
                rempli(164,37,12,4); rempli(149,63,2,2);
                rempli(214,48,4,9); rempli(282,62,4,11);
                vide(7,51,2,2); vide(28,66,4,3); vide(45,51,2,2);
                vide(89,35,2,2); vide(82,47,4,2); vide(88,47,10,2);
                vide(82,51,11,2); vide(95,51,3,2);
                vide(82,55,2,2); vide(86,55,12,2);
                vide(128,51,4,4); vide(169,35,2,2);
                vide(49,36,2,2);
            }
            break;
        case 52 :
            //carte
            if (gpJoueur->getCoffre(6,19)) {
                if(!gpJoueur->getCle(6,0)) setValeur(109*16,82*16,303,-1,PLEIN,C_CARTE_D);
                else setValeur(109*16,82*16,304,-1,PLEIN,C_RIEN);
            }
            //boussole
            if (gpJoueur->getCoffre(6,20)) {
                if(!gpJoueur->getCle(6,1)) setValeur(150*16,82*16,303,-1,PLEIN,C_BOUSSOLE);
                else setValeur(150*16,82*16,304,-1,PLEIN,C_RIEN);
            }
            //cle boss
            if(!gpJoueur->getCle(6,2)) setValeur(250*16,7*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(250*16,7*16,304,-1,PLEIN,C_RIEN);
            //cles
            if (gpJoueur->getCoffre(6,21)) {
                if(!gpJoueur->getCoffre(6,5)) setValeur(90*16,66*16,303,-1,PLEIN,C_CLE);
                else setValeur(90*16,66*16,304,-1,PLEIN,C_RIEN);
            }
            if(!gpJoueur->getCoffre(6,6)) setValeur(170*16,39*16,303,-1,PLEIN,C_CLE);
            else setValeur(170*16,39*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(6,7)) setValeur(146*16,64*16,303,-1,PLEIN,C_CLE);
            else setValeur(146*16,64*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(6,8)) setValeur(210*16,6*16,303,-1,PLEIN,C_CLE);
            else setValeur(210*16,6*16,304,-1,PLEIN,C_RIEN);
            //gants 2
            if (gpJoueur->hasObjet(O_GANTS)<2) setValeur(130*16,37*16,303,-1,PLEIN,C_GANTS_R);
            else setValeur(130*16,37*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(6,0)) passage(249,45,0);
            //portes
            if (gpJoueur->getCoffre(6,1)) passage(60,51,1);
            if (gpJoueur->getCoffre(6,2)) passage(120,81,1);
            if (gpJoueur->getCoffre(6,3)) passage(140,81,1);
            if (gpJoueur->getCoffre(6,4)) passage(260,6,1);
            if (gpJoueur->getCoffre(6,9)) {passage(40,66,1); map[28][68]=1005;}
            if (gpJoueur->getCoffre(6,10)) {passage(49,60,0); map[48][57]=1005;}
            if (gpJoueur->getCoffre(6,11)) {passage(60,66,1); map[71][68]=1005;}
            if (gpJoueur->getCoffre(6,12)) {passage(69,45,0); map[63][37]=1005;}
            if (gpJoueur->getCoffre(6,13)) {passage(120,21,1); map[103][22]=1005;}
            if (gpJoueur->getCoffre(6,14)) {passage(140,21,1); map[156][22]=1005;}
            if (gpJoueur->getCoffre(6,15)) {passage(129,30,0); map[127][32]=1005;}
            if (gpJoueur->getCoffre(6,16)) passage(149,60,0);
            if (gpJoueur->getCoffre(6,17)) {passage(169,45,0); map[167][33]=1005;}
            if (gpJoueur->getCoffre(6,18)) {passage(200,36,1); map[216][37]=1005;}
            if (gpJoueur->getCoffre(6,22)) {passage(129,45,0); setValeur(130*16,52*16,3980,11);}
            if(gpJoueur->getCoeur(6)) setValeur(248*16,32*16,3979,11);
            break;
        case 53 :
            //carte
            if (gpJoueur->getCoffre(7,24)) {
                if(!gpJoueur->getCle(7,0)) setValeur(89*16,67*16,303,-1,PLEIN,C_CARTE_D);
                else setValeur(89*16,67*16,304,-1,PLEIN,C_RIEN);
            }
            //boussole
            if(!gpJoueur->getCle(7,1)) setValeur(40*16,20*16,303,-1,PLEIN,C_BOUSSOLE);
            else setValeur(40*16,20*16,304,-1,PLEIN,C_RIEN);
            //cle boss
            if(!gpJoueur->getCle(7,2)) setValeur(169*16,21*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(169*16,21*16,304,-1,PLEIN,C_RIEN);
            //cles
            if (gpJoueur->getCoffre(7,25)) {
                if(!gpJoueur->getCoffre(7,5)) setValeur(9*16,37*16,303,-1,PLEIN,C_CLE);
                else setValeur(9*16,37*16,304,-1,PLEIN,C_RIEN);
            }
            if(!gpJoueur->getCoffre(7,6)) setValeur(70*16,96*16,303,-1,PLEIN,C_CLE);
            else setValeur(70*16,96*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(7,7)) setValeur(109*16,29*16,303,-1,PLEIN,C_CLE);
            else setValeur(109*16,29*16,304,-1,PLEIN,C_RIEN);
            if (gpJoueur->getCoffre(7,26)) {
                if(!gpJoueur->getCoffre(7,8)) setValeur(149*16,37*16,303,-1,PLEIN,C_CLE);
                else setValeur(149*16,37*16,304,-1,PLEIN,C_RIEN);
            }
            //arc 2
            if (gpJoueur->hasObjet(O_ARC)<5) setValeur(86*16,5*16,303,-1,PLEIN,C_ARC_FEE);
            else setValeur(86*16,5*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(7,0)) passage(189,15,0);
            //portes
            if (gpJoueur->getCoffre(7,1)) passage(20,51,1);
            if (gpJoueur->getCoffre(7,2)) passage(100,21,1);
            if (gpJoueur->getCoffre(7,3)) passage(140,21,1);
            if (gpJoueur->getCoffre(7,4)) passage(169,15,0);
            if (gpJoueur->getCoffre(7,9)) {passage(9,30,0); map[12][27]=1005;}
            if (gpJoueur->getCoffre(7,10)) {passage(29,15,0); map[23][7]=1005;}
            if (gpJoueur->getCoffre(7,11)) {passage(29,45,0); map[32][42]=1005;}
            if (gpJoueur->getCoffre(7,12)) {passage(60,36,1); map[50][41]=1005;}
            if (gpJoueur->getCoffre(7,13)) {passage(69,30,0); map[72][27]=1005;}
            if (gpJoueur->getCoffre(7,14)) {passage(69,105,0); map[68][92]=1005;}
            if (gpJoueur->getCoffre(7,15)) {passage(100,6,1); map[97][5]=1005;}
            if (gpJoueur->getCoffre(7,16)) {passage(89,75,0); map[87][72]=1005;}
            if (gpJoueur->getCoffre(7,17)) {passage(109,75,0); map[107][77]=1005;}
            if (gpJoueur->getCoffre(7,18)) {passage(129,45,0); map[132][47]=1005;}
            if (gpJoueur->getCoffre(7,19)) {passage(129,105,0); map[134][102]=1005;}
            if (gpJoueur->getCoffre(7,20)) {passage(200,51,1); map[197][55]=1005;}
            if (gpJoueur->getCoffre(7,21)) passage(229,45,0);
            if (gpJoueur->getCoffre(7,22)) passage(229,6,8);
            if (gpJoueur->getCoffre(7,23)) passage(89,15,0);
            break;
        case 54 :
            //carte
            if (gpJoueur->getCoffre(8,53)) {
                if(!gpJoueur->getCle(8,0)) setValeur(71*16,45*16,303,-1,PLEIN,C_CARTE_D);
                else setValeur(71*16,45*16,304,-1,PLEIN,C_RIEN);
            }
            //boussole
            if(!gpJoueur->getCle(8,1)) setValeur(26*16,65*16,303,-1,PLEIN,C_BOUSSOLE);
            else setValeur(26*16,65*16,304,-1,PLEIN,C_RIEN);
            //cle boss
            if(!gpJoueur->getCle(8,2)) setValeur(79*16,22*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(79*16,22*16,304,-1,PLEIN,C_RIEN);
            //cles
            if (gpJoueur->getCoffre(8,42)) {
                if(!gpJoueur->getCoffre(8,10)) setValeur(29*16,7*16,303,-1,PLEIN,C_CLE);
                else setValeur(29*16,7*16,304,-1,PLEIN,C_RIEN);
            }
            if (gpJoueur->getCoffre(8,35)) {
                if(!gpJoueur->getCoffre(8,11)) setValeur(50*16,20*16,303,-1,PLEIN,C_CLE);
                else setValeur(50*16,20*16,304,-1,PLEIN,C_RIEN);
            }
            if(!gpJoueur->getCoffre(8,12)) setValeur(69*16,82*16,303,-1,PLEIN,C_CLE);
            else setValeur(69*16,82*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(8,13)) setValeur(106*16,21*16,303,-1,PLEIN,C_CLE);
            else setValeur(106*16,21*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(8,14)) setValeur(106*16,82*16,303,-1,PLEIN,C_CLE);
            else setValeur(106*16,82*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(8,15)) setValeur(130*16,51*16,303,-1,PLEIN,C_CLE);
            else setValeur(130*16,51*16,304,-1,PLEIN,C_RIEN);
            if (gpJoueur->getCoffre(8,44)) {
                if(!gpJoueur->getCoffre(8,16)) setValeur(150*16,6*16,303,-1,PLEIN,C_CLE);
                else setValeur(150*16,6*16,304,-1,PLEIN,C_RIEN);
            }
            if(!gpJoueur->getCoffre(8,17)) setValeur(229*16,20*16,303,-1,PLEIN,C_CLE);
            else setValeur(229*16,20*16,304,-1,PLEIN,C_RIEN);
            if (gpJoueur->getCoffre(8,45)) {
                if(!gpJoueur->getCoffre(8,18)) setValeur(249*16,17*16,303,-1,PLEIN,C_CLE);
                else setValeur(249*16,17*16,304,-1,PLEIN,C_RIEN);
            }
            //baguette de glace
            if (!gpJoueur->hasObjet(O_BGLACE)) setValeur(89*16,7*16,303,-1,PLEIN,C_BGLACE);
            else setValeur(89*16,7*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(8,0)) passage(199,30,0);
            //portes
            if (gpJoueur->getCoffre(8,1)) passage(40,51,1);
            if (gpJoueur->getCoffre(8,2)) passage(60,51,1);
            if (gpJoueur->getCoffre(8,3)) passage(60,6,1);
            if (gpJoueur->getCoffre(8,4)) passage(149,60,0);
            if (gpJoueur->getCoffre(8,5)) passage(169,15,0);
            if (gpJoueur->getCoffre(8,6)) passage(180,36,1);
            if (gpJoueur->getCoffre(8,7)) passage(189,60,0);
            if (gpJoueur->getCoffre(8,8)) passage(209,60,0);
            if (gpJoueur->getCoffre(8,9)) passage(220,51,1);
            if (gpJoueur->getCoffre(8,19)) {passage(29,15,0); map[36][21]=1005;}
            if (gpJoueur->getCoffre(8,20)) {passage(69,75,0); map[72][77]=1005;}
            if (gpJoueur->getCoffre(8,21)) passage(100,81,1);
            if (gpJoueur->getCoffre(8,22)) {passage(120,6,1); map[117][10]=1005;}
            if (gpJoueur->getCoffre(8,23)) passage(80,6,1);
            if (gpJoueur->getCoffre(8,24)) {passage(79,30,0); map[80][45]=1000;}
            if (gpJoueur->getCoffre(8,55)) passage(129,60,0);
            if (gpJoueur->getCoffre(8,36)) {passage(120,51,1); map[122][55]=1005;}
            if (gpJoueur->getCoffre(8,37)) {passage(109,45,0); map[112][47]=1005;}
            if (gpJoueur->getCoffre(8,38)) {passage(109,30,0); map[108][17]=1005;}
            if (gpJoueur->getCoffre(8,39)) {passage(160,51,1); map[148][55]=1005;}
            if (gpJoueur->getCoffre(8,40)) {passage(169,30,0); map[171][40]=1005;}
            if (gpJoueur->getCoffre(8,41)) {
                passage(180,51,1); map[182][50]=1000; map[182][54]=1000;}
            if (gpJoueur->getCoffre(8,43)) {passage(180,81,1); map[196][82]=1005;}
            if (gpJoueur->getCoffre(8,46)) {passage(220,36,1); map[236][37]=1005;}
            if (gpJoueur->getCoffre(8,47)) passage(229,60,0);
            if (gpJoueur->getCoffre(8,48)) {passage(229,75,0); map[233][67]=1005;}
            if (gpJoueur->getCoffre(8,49)) {passage(240,81,1); map[235][85]=1005;}
            if (gpJoueur->getCoffre(8,50)) {passage(249,60,0); map[248][70]=1005;}
            if (gpJoueur->getCoffre(8,51)) passage(249,30,0);
            if (gpJoueur->getCoffre(8,52)) passage(100,6,1);
            if (gpJoueur->getCoffre(8,54)) passage(109,21,8);
            //torches
            if (gpJoueur->getCoffre(8,25)) map[102][71]=1001;
            if (gpJoueur->getCoffre(8,26)) map[115][62]=1001;
            if (gpJoueur->getCoffre(8,27)) map[127][62]=1001;
            if (gpJoueur->getCoffre(8,28)) map[135][62]=1001;
            if (gpJoueur->getCoffre(8,29)) map[133][76]=1001;
            if (gpJoueur->getCoffre(8,30)) map[107][80]=1001;
            if (gpJoueur->getCoffre(8,31)) map[102][86]=1001;
            if (gpJoueur->getCoffre(8,32)) map[107][86]=1001;
            if (gpJoueur->getCoffre(8,33)) map[130][86]=1001;
            if (gpJoueur->getCoffre(8,34)) map[135][83]=1001;
            break;
        case 55 :
            //carte
            if (gpJoueur->getCoffre(9,55)) {
                if(!gpJoueur->getCle(9,0)) setValeur(9*16,36*16,303,-1,PLEIN,C_CARTE_D);
                else setValeur(9*16,36*16,304,-1,PLEIN,C_RIEN);
            }
            //boussole
            if (gpJoueur->getCoffre(9,59)) {
                if(!gpJoueur->getCle(9,1)) setValeur(110*16,186*16,303,-1,PLEIN,C_BOUSSOLE);
                else setValeur(110*16,186*16,304,-1,PLEIN,C_RIEN);
            }
            //cle boss
            if(!gpJoueur->getCle(9,2)) setValeur(70*16,82*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(70*16,82*16,304,-1,PLEIN,C_RIEN);
            //cles
            if (gpJoueur->getCoffre(9,56)) {
                if(!gpJoueur->getCoffre(9,1)) setValeur(50*16,6*16,303,-1,PLEIN,C_CLE);
                else setValeur(50*16,6*16,304,-1,PLEIN,C_RIEN);
            }
            if (gpJoueur->getCoffre(9,57)) {
                if(!gpJoueur->getCoffre(9,2)) setValeur(69*16,6*16,303,-1,PLEIN,C_CLE);
                else setValeur(69*16,6*16,304,-1,PLEIN,C_RIEN);
            }
            if (gpJoueur->getCoffre(9,58)) {
                if(!gpJoueur->getCoffre(9,3)) setValeur(89*16,6*16,303,-1,PLEIN,C_CLE);
                else setValeur(89*16,6*16,304,-1,PLEIN,C_RIEN);
            }
            if(!gpJoueur->getCoffre(9,4)) setValeur(132*16,61*16,303,-1,PLEIN,C_CLE);
            else setValeur(132*16,61*16,304,-1,PLEIN,C_RIEN);
            //baguette de feu
            if (!gpJoueur->hasObjet(O_BFEU)) setValeur(90*16,157*16,303,-1,PLEIN,C_BFEU);
            else setValeur(90*16,157*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(9,0)) passage(69,60,0);
            if (gpJoueur->getCoeur(9)) map[65][38]=3417;
            if (gpJoueur->hasObjet(O_TROC1)) setValeur(70*16,197*16,5878,11);
            //portes
            if (gpJoueur->getCoffre(9,5)) passage(29,45,0);
            if (gpJoueur->getCoffre(9,6)) passage(40,111,1);
            if (gpJoueur->getCoffre(9,7)) passage(60,156,1);
            if (gpJoueur->getCoffre(9,8)) passage(120,81,1);
            if (gpJoueur->getCoffre(9,9)) {passage(20,141,1); map[17][145]=1005;}
            if (gpJoueur->getCoffre(9,10)) {passage(29,30,0); map[27][27]=1005;}
            if (gpJoueur->getCoffre(9,11)) passage(29,105,0);
            if (gpJoueur->getCoffre(9,12)) passage(40,201,1);
            if (gpJoueur->getCoffre(9,13)) passage(49,60,0);
            if (gpJoueur->getCoffre(9,14)) {passage(60,216,1); map[57][220]=1005;}
            if (gpJoueur->getCoffre(9,15)) passage(69,90,0);
            if (gpJoueur->getCoffre(9,16)) passage(80,156,1);
            if (gpJoueur->getCoffre(9,17)) {passage(80,216,1); map[82][220]=1005;}
            if (gpJoueur->getCoffre(9,18)) passage(100,6,1);
            if (gpJoueur->getCoffre(9,19)) passage(100,126,1);
            if (gpJoueur->getCoffre(9,20)) passage(100,156,1);
            if (gpJoueur->getCoffre(9,21)) {passage(129,30,0); map[123][37]=1005;}
            if (gpJoueur->getCoffre(9,22)) {passage(120,141,1); map[122][145]=1005;}
            if (gpJoueur->getCoffre(9,60)) passage(69,15,4);
            //torches
            if (gpJoueur->getCoffre(9,23)) map[47][57]=1001;
            if (gpJoueur->getCoffre(9,24)) map[52][57]=1001;
            if (gpJoueur->getCoffre(9,25)) map[106][15]=1001;
            if (gpJoueur->getCoffre(9,26)) map[115][2]=1001;
            if (gpJoueur->getCoffre(9,27)) map[119][10]=1001;
            if (gpJoueur->getCoffre(9,28)) map[119][22]=1001;
            if (gpJoueur->getCoffre(9,29)) map[136][4]=1001;
            if (gpJoueur->getCoffre(9,30)) map[134][17]=1001;
            if (gpJoueur->getCoffre(9,31)) map[24][102]=1001;
            if (gpJoueur->getCoffre(9,32)) map[35][102]=1001;
            if (gpJoueur->getCoffre(9,33)) map[55][104]=1001;
            if (gpJoueur->getCoffre(9,34)) map[66][104]=1001;
            if (gpJoueur->getCoffre(9,35)) map[73][104]=1001;
            if (gpJoueur->getCoffre(9,36)) map[84][104]=1001;
            if (gpJoueur->getCoffre(9,37)) map[55][112]=1001;
            if (gpJoueur->getCoffre(9,38)) map[84][112]=1001;
            if (gpJoueur->getCoffre(9,39)) map[55][119]=1001;
            if (gpJoueur->getCoffre(9,40)) map[66][119]=1001;
            if (gpJoueur->getCoffre(9,41)) map[73][119]=1001;
            if (gpJoueur->getCoffre(9,42)) map[84][119]=1001;
            if (gpJoueur->getCoffre(9,43)) map[108][122]=1001;
            if (gpJoueur->getCoffre(9,44)) map[111][122]=1001;
            if (gpJoueur->getCoffre(9,45)) map[108][132]=1001;
            if (gpJoueur->getCoffre(9,46)) map[111][132]=1001;
            if (gpJoueur->getCoffre(9,47)) map[97][152]=1001;
            if (gpJoueur->getCoffre(9,48)) map[97][162]=1001;
            if (gpJoueur->getCoffre(9,49)) map[6][201]=1001;
            if (gpJoueur->getCoffre(9,50)) map[27][201]=1001;
            if (gpJoueur->getCoffre(9,51)) map[30][201]=1001;
            if (gpJoueur->getCoffre(9,52)) map[14][219]=1001;
            if (gpJoueur->getCoffre(9,53)) map[23][213]=1001;
            if (gpJoueur->getCoffre(9,54)) map[27][220]=1001;
            break;
        case 56 :
            //carte
            if (gpJoueur->getCoffre(10,14)) {
                if(!gpJoueur->getCle(10,0)) setValeur(90*16,51*16,303,-1,PLEIN,C_CARTE_D);
                else setValeur(90*16,51*16,304,-1,PLEIN,C_RIEN);
            }
            //boussole
            if (gpJoueur->getCoffre(10,16)) {
                if(!gpJoueur->getCle(10,1)) setValeur(149*16,6*16,303,-1,PLEIN,C_BOUSSOLE);
                else setValeur(149*16,6*16,304,-1,PLEIN,C_RIEN);
            }
            //cle boss
            if(!gpJoueur->getCle(10,2)) setValeur(69*16,6*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(69*16,6*16,304,-1,PLEIN,C_RIEN);
            //cles
            if (gpJoueur->getCoffre(10,13)) {
                if(!gpJoueur->getCoffre(10,4)) setValeur(30*16,21*16,303,-1,PLEIN,C_CLE);
                else setValeur(30*16,21*16,304,-1,PLEIN,C_RIEN);
            }
            if (gpJoueur->getCoffre(10,15)) {
                if(!gpJoueur->getCoffre(10,5)) setValeur(109*16,21*16,303,-1,PLEIN,C_CLE);
                else setValeur(109*16,21*16,304,-1,PLEIN,C_RIEN);
            }
            if (gpJoueur->getCoffre(10,17)) {
                if(!gpJoueur->getCoffre(10,6)) setValeur(190*16,6*16,303,-1,PLEIN,C_CLE);
                else setValeur(190*16,6*16,304,-1,PLEIN,C_RIEN);
            }
            //bouclier 3
            if (gpJoueur->getBouclier() < 3) setValeur(89*16,96*16,303,-1,PLEIN,C_BOUCLIER_J);
            else setValeur(89*16,96*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(10,0)) passage(169,30,0);
            //portes
            if (gpJoueur->getCoffre(10,1)) passage(69,15,0);
            if (gpJoueur->getCoffre(10,2)) passage(69,30,0);
            if (gpJoueur->getCoffre(10,3)) passage(120,96,1);
            if (gpJoueur->getCoffre(10,7)) {passage(40,21,1); map[37][25]=1005;}
            if (gpJoueur->getCoffre(10,8)) passage(40,36,1);
            if (gpJoueur->getCoffre(10,9)) {passage(49,30,0); map[43][37]=1005;}
            if (gpJoueur->getCoffre(10,10)) {passage(120,6,1); map[103][7]=1005;}
            if (gpJoueur->getCoffre(10,11)) passage(100,96,1);
            if (gpJoueur->getCoffre(10,12)) map[54][97]=1005;
            if (gpJoueur->getCoffre(10,18)) passage(89,30,0);
            break;
        case 57 :
            //ocarina
            if (gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_UTILISE
            || gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_FERME
            || gpJoueur->hasObjet(O_OCARINA))
                setValeur(110*16,171*16,304,-1,PLEIN,C_RIEN);
            else setValeur(110*16,171*16,303,-1,PLEIN,C_OCARINA);
            //bouclier
            if(!gpJoueur->getBouclier()) setValeur(87*16,6*16,303,-1,PLEIN,C_BOUCLIER);
            else setValeur(87*16,6*16,304,-1,PLEIN,C_RIEN);
            //petite bourse
            if(!gpJoueur->getBouclier()) setValeur(92*16,6*16,303,-1,PLEIN,C_BOURSE_1);
            else setValeur(92*16,6*16,304,-1,PLEIN,C_RIEN);
            //porte chambre forte
            if (gpJoueur->getAvancement()>=PARLE_GARDE_SOUS_SOL
            && (gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_UTILISE
            || gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_FERME)) passage(100,171,1);
            //passage secret
            if (gpJeu->getJoueur()->getAvancement()>=PASSAGE_TROUVE
            && (gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_UTILISE
            || gpJoueur->getAvancement()>=EXPLOSE_MUR)) passage(109,165,4);
            //riz et olives
            if (!gpJoueur->getCoffre(15,29)) setValeur(4*16,4*16,303,-1,PLEIN,C_RIZ);
            else setValeur(4*16,4*16,304,-1,PLEIN,C_RIEN);
            if (!gpJoueur->getCoffre(15,30)) setValeur(6*16,4*16,303,-1,PLEIN,C_OLIVES);
            else setValeur(6*16,4*16,304,-1,PLEIN,C_RIEN);
            //mirroir au mur
            if (gpJoueur->hasObjet(O_TROC3)>=5) {map[62][5]=6290; map[63][5]=6291;}
            //carte
            if(!gpJoueur->getCle(11,0)) setValeur(69*16,156*16,303,-1,PLEIN,C_CARTE_D);
            else setValeur(69*16,156*16,304,-1,PLEIN,C_RIEN);
            //boussole
            if(!gpJoueur->getCle(11,1)) setValeur(105*16,18*16,303,-1,PLEIN,C_BOUSSOLE);
            else setValeur(105*16,18*16,304,-1,PLEIN,C_RIEN);
            //cle boss
            if(!gpJoueur->getCle(11,2)) setValeur(72*16,229*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(72*16,229*16,304,-1,PLEIN,C_RIEN);
            //cles
            if(!gpJoueur->getCoffre(11,1)) setValeur(190*16,6*16,303,-1,PLEIN,C_CLE);
            else setValeur(190*16,6*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(11,2)) setValeur(51*16,97*16,303,-1,PLEIN,C_CLE);
            else setValeur(51*16,97*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(11,3)) setValeur(87*16,94*16,303,-1,PLEIN,C_CLE);
            else setValeur(87*16,94*16,304,-1,PLEIN,C_RIEN);
            //tunique 3
            if (gpJoueur->getTunique() < 3) setValeur(89*16,186*16,303,-1,PLEIN,C_TUNIQUE_ROUGE);
            else setValeur(89*16,186*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(11,0)) passage(169,30,0);
            if (gpJoueur->getEnnemi(50)) {
                passage(169,15,0); passage(160,21,1); passage(180,21,1);}
            //portes
            if (gpJoueur->getCoffre(11,4)) passage(49,240,0);
            if (gpJoueur->getCoffre(11,5)) setValeur(5*16,233*16,6137,0);
            if (gpJoueur->getCoffre(11,6)) setValeur(72*16,233*16,6137,0);
            if (gpJoueur->getCoffre(11,7)) {passage(40,231,1); passage(60,231,1);}
            if (gpJoueur->getCoffre(11,8)) passage(80,156,1);
            if (gpJoueur->getCoffre(11,9)) passage(89,180,0);
            
            int total;
            total = 0;
            for (int i = 0; i < 9; i++) if (gpJeu->getKeyboard()->getRang(i)) total++;
            if (total == 9 && gpJoueur->getEnnemi(141)) passage(149,15,0);
            break;
        case 58 :
            //cle boss
            if(!gpJoueur->getCle(12,2)) setValeur(69*16,6*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(69*16,6*16,304,-1,PLEIN,C_RIEN);
            //bouclier 4
            if (gpJoueur->getBouclier() < 4) setValeur(66*16,21*16,303,-1,PLEIN,C_BOUCLIER_OR);
            else setValeur(66*16,21*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(12,0)) passage(69,45,0);
            //portes
            if (gpJoueur->getCoffre(12,6)) passage(40,96,1);
            if (gpJoueur->getCoffre(12,7)) passage(69,60,0);
            if (gpJoueur->getCoffre(12,8)) passage(80,6,1);
            if (gpJoueur->getCoffre(12,9)) passage(100,6,1);
            if (gpJoueur->getCoffre(12,10)) passage(120,6,1);
            if (gpJoueur->getCoffre(12,11)) {passage(20,36,1); map[11][41]=1005;}
            if (gpJoueur->getCoffre(12,12)) {passage(129,45,0); map[123][37]=1005;}
            if (gpJoueur->getCoffre(12,14)) passage(20,66,3);
            if (gpJoueur->getCoffre(12,15)) passage(120,66,3);
            break;
        case 59 :
            //carte
            if(!gpJoueur->getCle(13,0)) setValeur(113*16,28*16,303,-1,PLEIN,C_CARTE_D);
            else setValeur(113*16,28*16,304,-1,PLEIN,C_RIEN);
            //boussole
            if(!gpJoueur->getCle(13,1)) setValeur(186*16,33*16,303,-1,PLEIN,C_BOUSSOLE);
            else setValeur(186*16,33*16,304,-1,PLEIN,C_RIEN);
            //cle boss
            if(!gpJoueur->getCle(13,2)) setValeur(249*16,21*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(249*16,21*16,304,-1,PLEIN,C_RIEN);
            //cles
            if(!gpJoueur->getCoffre(13,1)) setValeur(69*16,6*16,303,-1,PLEIN,C_CLE);
            else setValeur(69*16,6*16,304,-1,PLEIN,C_RIEN);
            if(!gpJoueur->getCoffre(13,2)) setValeur(149*16,36*16,303,-1,PLEIN,C_CLE);
            else setValeur(149*16,36*16,304,-1,PLEIN,C_RIEN);
            //tunique 4
            if (gpJoueur->getTunique() < 4) setValeur(276*16,22*16,303,-1,PLEIN,C_TUNIQUE_OR);
            else setValeur(276*16,22*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(13,0)) passage(279,45,0);
            //portes
            if (gpJoueur->getCoffre(13,3)) passage(109,45,0);
            if (gpJoueur->getCoffre(13,4)) passage(249,45,0);
            if (gpJoueur->getCoffre(13,5)) {passage(9,15,0); map[7][12]=1005;}
            if (gpJoueur->getCoffre(13,6)) {passage(20,6,1); map[22][10]=1005;}
            if (gpJoueur->getCoffre(13,7)) {passage(29,45,0); map[27][42]=1005;}
            if (gpJoueur->getCoffre(13,9)) {passage(40,51,1); map[42][55]=1005;}
            if (gpJoueur->getCoffre(13,10)) {passage(69,15,0); map[67][12]=1005;}
            if (gpJoueur->getCoffre(13,11)) {passage(69,45,0); map[67][42]=1005;}
            if (gpJoueur->getCoffre(13,12)) {passage(100,51,1); map[95][52]=1005;}
            break;
        case 60 :
            //carte
            if(!gpJoueur->getCle(14,0)) setValeur(49*16,82*16,303,-1,PLEIN,C_CARTE_D);
            else setValeur(49*16,82*16,304,-1,PLEIN,C_RIEN);
            //boussole
            if(!gpJoueur->getCle(14,1)) setValeur(109*16,82*16,303,-1,PLEIN,C_BOUSSOLE);
            else setValeur(109*16,82*16,304,-1,PLEIN,C_RIEN);
            //cle boss
            if(!gpJoueur->getCle(14,2)) setValeur(29*16,82*16,303,-1,PLEIN,C_CLE_BOSS);
            else setValeur(29*16,82*16,304,-1,PLEIN,C_RIEN);
            //cles
            if(!gpJoueur->getCoffre(14,1)) setValeur(89*16,142*16,303,-1,PLEIN,C_CLE);
            else setValeur(89*16,142*16,304,-1,PLEIN,C_RIEN);
            //masque oni link
            if (!gpJoueur->hasObjet(O_MASQUE)) setValeur(69*16,6*16,303,-1,PLEIN,C_MASQUE_ONI);
            else setValeur(69*16,6*16,304,-1,PLEIN,C_RIEN);
            //porte boss
            if (gpJoueur->getCoffre(14,0)) passage(69,120,0);
            //portes
            if (gpJoueur->getCoffre(14,2)) passage(20,66,1);
            if (gpJoueur->getCoffre(14,3)) {passage(9,60,0); map[7][57]=1005;}
            if (gpJoueur->getCoffre(14,4)) {passage(29,60,0); map[32][62]=1005;}
            if (gpJoueur->getCoffre(14,5)) {passage(60,36,1); map[52][38]=1005;}
            if (gpJoueur->getCoffre(14,6)) {passage(49,135,0); map[44][128]=1005;}
            if (gpJoueur->getCoffre(14,7)) {passage(129,60,0); map[127][62]=1005;}
            if (gpJoueur->getCoffre(14,8)) {passage(129,105,0); map[122][100]=1005;}
            if (gpJoueur->getCoffre(14,9)) passage(9,90,0);
            if (gpJoueur->getCoffre(14,10)) passage(29,90,0);
            if (gpJoueur->getCoffre(14,11)) passage(49,90,0);
            if (gpJoueur->getCoffre(14,12)) passage(69,15,0);
            if (gpJoueur->getCoffre(14,13)) passage(69,90,0);
            if (gpJoueur->getCoffre(14,14)) passage(89,90,0);
            if (gpJoueur->getCoffre(14,15)) passage(129,90,0);
            if (gpJoueur->getCoffre(14,16)) {passage(49,45,0); map[47][47]=1005;}
            break;
        case 61 : setValeur(10*16,7*16,304,-1,PLEIN,C_RIEN); break;
        case 63 : 
            if (gpJoueur->getCoffre(15,6)) {passage(80,6,1); map[84][5]=1005;} break;
        case 64 :
            // si le portail est apparu
            if (gpJoueur->getAvancement() >= PORTAIL_F_OUVERT) {
                passage(9,6,0); 
                if (gpJoueur->getAvancement() < RETOUR_PRESENT) passage(9,3,1);
            }
            break;
        case 66 :
            if (!gpJoueur->getCoffre(15,7)) setValeur(7*16,6*16,303,-1,PLEIN,C_RIZ_10);
            else setValeur(7*16,6*16,304,-1,PLEIN,C_RIEN);
            if (!gpJoueur->getCoffre(15,8)) setValeur(10*16,6*16,303,-1,PLEIN,C_EPICES_10);
            else setValeur(10*16,6*16,304,-1,PLEIN,C_RIEN);
            if (!gpJoueur->getCoffre(15,9)) setValeur(13*16,6*16,303,-1,PLEIN,C_OLIVES_10);
            else setValeur(13*16,6*16,304,-1,PLEIN,C_RIEN);
            break;
        case 67 : if (gpJoueur->getCoffre(15,10)) {passage(60,21,1); map[53][19]=1005;} break;
        case 68 : 
            if (gpJoueur->getCoffre(15,11)) {passage(9,15,0); map[7][11]=1005;} 
            if (gpJoueur->getPosRails()) {
                setValeur(41*16,9*16,2367,2);
                setValeur(34*16,13*16,2368,2);
                setValeur(45*16,13*16,2369,2);
            }
            if (gpJoueur->getAvancement() >=GARS_MINE_AIDE && gpJoueur->getPosWagon() == 1) 
                gpJoueur->setPosWagon(0);
            break;
        case 69 :
            if (gpJoueur->getCoffre(15,12)) passage(9,15,4);
            break;
        case 70 : 
            // si le portail est apparu
            if (gpJoueur->getAvancement() >= PORTAIL_PRE_PRESENT_OUVERT
            && gpJoueur->getAvancement() < PORTAIL_PRE_PRESENT_FERME) 
                passage(9,3,1);
            break;
        case 71 : setValeur(10*16,7*16,304,-1,PLEIN,C_RIEN); break;
        case 72 :
            if (gpJoueur->getTroc(M_JAUGE)==-1) setValeur(10*16,6*16,303,-1,PLEIN,C_JAUGE);
            else setValeur(10*16,6*16,304,-1,PLEIN,C_RIEN);
            break;
        case 75 :
            //cristal 3
            if(!gpJoueur->hasCristal(2)) setValeur(10*16,7*16,303,-1,PLEIN,C_CRISTAL);
            else setValeur(10*16,7*16,304,-1,PLEIN,C_RIEN);
            break;
        case 83 :
            if (!gpJoueur->getCoffre(15,13)) setValeur(6*16,5*16,303,-1,PLEIN,C_EPICES);
            else setValeur(6*16,5*16,304,-1,PLEIN,C_RIEN);
            break; //(15, 14) pris pour troc1
        case 87 :
            if (!gpJoueur->getCoffre(15,15)) setValeur(9*16,5*16,303,-1,PLEIN,C_RIZ);
            else setValeur(9*16,5*16,304,-1,PLEIN,C_RIEN);
            if (!gpJoueur->getCoffre(15,16)) setValeur(11*16,5*16,303,-1,PLEIN,C_OLIVES);
            else setValeur(11*16,5*16,304,-1,PLEIN,C_RIEN);
            break;
        case 88 :
            if (!gpJoueur->getCoffre(15,17)) setValeur(4*16,11*16,303,-1,PLEIN,C_EPICES);
            else setValeur(4*16,11*16,304,-1,PLEIN,C_RIEN);
            break;
        case 89 :
            if(!gpJoueur->getCoeur(28) && !gpJoueur->getGemme(160) 
            && !gpJoueur->getGemme(161) && !gpJoueur->getGemme(162)) {
                setValeur(6*16,6*16,303,1);
                setValeur(8*16,6*16,303,1);
                setValeur(10*16,6*16,303,1);
                setValeur(6*16,8*16,303,1);
                setValeur(8*16,8*16,303,1);
                setValeur(10*16,8*16,303,1);
                setValeur(6*16,10*16,303,1);
                setValeur(8*16,10*16,303,1);
                setValeur(10*16,10*16,303,1);
                contenu[6][6]=C_PAIE; contenu[8][6]=C_PAIE; contenu[10][6]=C_PAIE;
                contenu[6][8]=C_PAIE; contenu[8][8]=C_PAIE; contenu[10][8]=C_PAIE;
                contenu[6][10]=C_PAIE; contenu[8][10]=C_PAIE; contenu[10][10]=C_PAIE;
            }else {
                setValeur(6*16,6*16,304,1);
                setValeur(8*16,6*16,304,1);
                setValeur(10*16,6*16,304,1);
                setValeur(6*16,8*16,304,1);
                setValeur(8*16,8*16,304,1);
                setValeur(10*16,8*16,304,1);
                setValeur(6*16,10*16,304,1);
                setValeur(8*16,10*16,304,1);
                setValeur(10*16,10*16,304,1);
            }
            break;
        case 96 :
            if (!gpJoueur->getCoffre(15,18)) setValeur(8*16,5*16,303,-1,PLEIN,C_RIZ);
            else setValeur(8*16,5*16,304,-1,PLEIN,C_RIEN);
            if (!gpJoueur->getCoffre(15,19)) setValeur(12*16,5*16,303,-1,PLEIN,C_OLIVES);
            else setValeur(12*16,5*16,304,-1,PLEIN,C_RIEN);
            if (!gpJoueur->getCoffre(15,20)) setValeur(10*16,5*16,303,-1,PLEIN,C_EPICES);
            else setValeur(10*16,5*16,304,-1,PLEIN,C_RIEN);
            break;
        case 104 :
            if (!gpJoueur->getCoffre(15,21)) setValeur(13*16,9*16,303,-1,PLEIN,C_EPICES);
            else setValeur(13*16,9*16,304,-1,PLEIN,C_RIEN);
            break; //15,22 = parler au sage chez link passé
        case 111 :
        case 114 :
        case 124 :
            if (gpJoueur->nbEnnemis() >= 87) {map[9][5]=3417; map[10][5]=3417;}
            break;
        case 127 :
            if (gpJoueur->hasObjet(O_TROC1)>2 && gpJoueur->hasObjet(O_TROC2)>3
            && gpJoueur->hasObjet(O_TROC3)>3) {
                setValeur(8*16,7*16,4676,-1,PLEIN);
                setValeur(9*16,7*16,4677,-1,PLEIN);
                setValeur(8*16,8*16,4678,-1,PLEIN);
                setValeur(9*16,8*16,4679,-1,PLEIN);
                for (int i = 0; i < 4; i++) mur[8*2+i][7*2]=0;
            }
            break;
        case 134 :
            if(!gpJoueur->hasObjet(O_LIVRE)) setValeur(11*16,5*16,303,-1,PLEIN,C_LIVRE);
            else setValeur(11*16,5*16,304,-1,PLEIN,C_RIEN);
            break; //15,23 = infos achettées au bar
        case 137 :
            //cristal 4
            if(!gpJoueur->hasCristal(3)) setValeur(10*16,7*16,303,-1,PLEIN,C_CRISTAL);
            else setValeur(10*16,7*16,304,-1,PLEIN,C_RIEN);
            if (gpJeu->getJoueur()->nbCristaux()<3 || gpJeu->getJoueur()->hasObjet(O_TROC4)<6
            || gpJeu->getJoueur()->hasCristal(3)) {
                for (int j = 0; j < 2; j++) 
                    for (int i = 0; i < 3; i++) {
                        map[9+i][67+j]=map[12+i][67+j];
                        mur[(9+i)*2][(67+j)*2]=mur[(12+i)*2][(67+j)*2];
                        mur[(9+i)*2+1][(67+j)*2]=mur[(12+i)*2+1][(67+j)*2];
                        mur[(9+i)*2][(67+j)*2+1]=mur[(12+i)*2][(67+j)*2+1];
                        mur[(9+i)*2+1][(67+j)*2+1]=mur[(12+i)*2+1][(67+j)*2+1];
                        setValeur((12+i)*16,(67+j)*16,4004,0);
                    }
            }
            break;
        case 140 :
            if (!gpJoueur->hasObjet(O_TROC1)<7 && !gpJoueur->hasObjet(O_FFEU)) 
                setValeur(26*16,5*16,303,-1,PLEIN,C_MARTEAU3);
            else setValeur(26*16,5*16,304,-1,PLEIN,C_RIEN);
            if (!gpJoueur->getCoffre(15,24)) setValeur(26*16,8*16,303,-1,PLEIN,C_EPICES);
            else setValeur(26*16,8*16,304,-1,PLEIN,C_RIEN);
            if (!gpJoueur->getCoffre(15,25)) setValeur(26*16,11*16,303,-1,PLEIN,C_RIZ);
            else setValeur(26*16,11*16,304,-1,PLEIN,C_RIEN);
            break; //15,26 si troc avancé  -  15,27 pour opéra
        case 150 :
            if (gpJoueur->getCoffre(15,27)>=1) passage(20,36,1);
            if (gpJoueur->getCoffre(15,27)>=2) passage(100,21,1);
            if (gpJoueur->getCoffre(15,27)>=3) passage(80,36,1);
            if (gpJoueur->getCoffre(15,27)>=4) passage(40,21,1);
            if (gpJoueur->getCoffre(15,27)>=5) passage(100,36,1);
            if (gpJoueur->getCoffre(15,27)>=6) passage(20,21,1);
            if (gpJoueur->getCoffre(15,27)>=7) passage(80,21,1);
            if (gpJoueur->getCoffre(15,27)>=8) passage(40,36,1);
            if (gpJoueur->getCoffre(15,27)>=10) passage(160,21,11);
            if (gpJoueur->getCoffre(15,27)>=11) passage(149,30,10);
            if (gpJoueur->getCoffre(15,27)>=12) passage(209,15,10);
            break;
        case 154 :
            if (gpJoueur->getCoffre(15,28)) passage(60,19,4);
            if (gpJoueur->getX()>320*3) {
                for (int j = 0; j < 2; j++) {
                    setValeur(54*16,(8+15*j)*16,2638,0);
                    for (int i=0; i<6; i++) {
                        mur[40*2][(6+15*j)*2+i]=1;
                        mur[40*2+1][(6+15*j)*2+i]=1;
                        mur[40*2+2][(6+15*j)*2+i]=1;
                        map[40+(i%2)][(6+15*j)+((int)(i/2))]=2720+i;
                    }
                }
            }
            break;
        case 155 :
            //clé
            if(gpJeu->getJoueur()->getAvancement() < CLE_PRISON_F_TROUVEE) 
                setValeur(11*16,2*16,303,-1,PLEIN,C_CLE);
            else setValeur(11*16,2*16,304,-1,PLEIN,C_RIEN);
            //porte prison
            if(gpJeu->getJoueur()->getAvancement() >= BOWSER_AIDE) 
                setValeur(89*16,94*16,4680,0);
            //source d'énergie
            if (gpJoueur->getTroc(M_SOURCE_ENERGIE)==-1)
                setValeur(109*16,21*16,303,-1,PLEIN,C_SOURCE_ENERGIE);
            else setValeur(109*16,21*16,304,-1,PLEIN,C_RIEN);
            //murs détruits
            if (gpJoueur->getCoffre(15,31)) passage(9,60,4);
            if (gpJoueur->getCoffre(15,32)) passage(9,90,4);
            break;
    }
}

void Monde::initMatrice(int zone) {
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    //int monstre1=0, monstre2=0, monstre3=0;
    /*if (!gpJoueur->getOnilink()) {
        if (zone==12 || zone==5 || zone==6 || zone==4 || zone==10 || zone==2 || zone==9) {
            if (!gpJoueur->getEnnemi(19)) monstre1=1+(rand()%14);
            if (!gpJoueur->getEnnemi(24)) monstre2=1+(rand()%14); 
            if (monstre2==monstre1) monstre2=0;
            if (!gpJoueur->getEnnemi(35)) monstre3=1+(rand()%14); 
            if (monstre3==monstre1 || monstre3==monstre2) monstre3=0;
        }
    }*/
    
    Ennemi* enn;
    switch(zone) {
        case 1 :
            gpJeu->ajouteEnnemi(77,6*16,52*16); gpJeu->ajouteEnnemi(77,7*16,33*16);
            gpJeu->ajouteEnnemi(77,12*16,17*16); gpJeu->ajouteEnnemi(77,12*16,42*16);
            gpJeu->ajouteEnnemi(77,25*16,28*16); gpJeu->ajouteEnnemi(77,30*16,50*16);
            gpJeu->ajouteEnnemi(77,34*16,14*16); gpJeu->ajouteEnnemi(77,50*16,14*16);
            gpJeu->ajouteEnnemi(77,52*16,28*16); gpJeu->ajouteEnnemi(77,61*16,48*16);
            gpJeu->ajouteEnnemi(77,69*16,37*16);
            if (!gpJoueur->getGemme(6)) gpJeu->ajouteObjet(I_GEMME,16*7,16*54,6);
            if (!gpJoueur->getGemme(7)) gpJeu->ajouteObjet(I_GEMME,16*18,16*15,7);
            if (!gpJoueur->getGemme(8)) gpJeu->ajouteObjet(I_GEMME,16*66,16*5,8);
            break;
        case 2 :
            gpJeu->ajouteEnnemi(77,12*16,33*16); gpJeu->ajouteEnnemi(77,14*16,47*16);
            gpJeu->ajouteEnnemi(77,22*16,44*16); gpJeu->ajouteEnnemi(77,28*16,11*16);
            gpJeu->ajouteEnnemi(77,40*16,32*16); gpJeu->ajouteEnnemi(77,46*16,39*16);
            gpJeu->ajouteEnnemi(77,53*16,13*16);
            if (!gpJoueur->getGemme(15)) gpJeu->ajouteObjet(I_GEMME,16*37,16*36,15);
            if (!gpJoueur->getGemme(16)) gpJeu->ajouteObjet(I_GEMME,16*53,16*41,16);
            if (!gpJoueur->getGemme(17)) gpJeu->ajouteObjet(I_GEMME,16*7,16*53,17);
            break;
        case 3 :
            if (!gpJoueur->getCoeur(18)) gpJeu->ajouteObjet(I_QUART_COEUR,19*16,5*16,18);
            if (gpJeu->getJoueur()->getAvancement()>=INFO_PASSE_OK) {
                gpJeu->ajoutePnj(9,33*16+8,75*16,178);
                if (gpJoueur->hasObjet(O_TROC4)<4) gpJeu->getPnj()->getSuivant()->setDirection(N);
                gpJeu->ajoutePnj(20,46*16+8,30*16+5,159); 
                contenu[46][32]=159; contenu[47][32]=159;
                gpJeu->ajoutePnj(12,46*16+8,37*16+5,168); 
                contenu[46][39]=168; contenu[47][39]=168;
                gpJeu->ajoutePnj(42,32*16+8,44*16+5,80); 
                contenu[32][46]=80; contenu[33][46]=80;
                gpJeu->ajoutePnj(39,46*16+4,45*16-4,171); 
                contenu[46][46]=171; contenu[47][46]=171;
                gpJeu->ajoutePnj(14,57*16,51*16,173);
                gpJeu->ajoutePnj(35,46*16,65*16,174);
                gpJeu->ajoutePnj(10,27*16+8,57*16+8,175);
                gpJeu->ajouteEnnemi(52,25*16,58*16);
                gpJeu->ajouteEnnemi(52,30*16,57*16);
                gpJeu->ajouteEnnemi(52,26*16,61*16);
                gpJeu->ajouteEnnemi(52,33*16,62*16);
                gpJeu->ajouteEnnemi(52,29*16,59*16);
                gpJeu->ajoutePnj(23,17*16,66*16,176);
                gpJeu->ajoutePnj(51,57*16,81*16,177);
            }
            if (!gpJoueur->getGemme(21)) gpJeu->ajouteObjet(I_GEMME,16*65,16*7,21);
            if (!gpJoueur->getGemme(22)) gpJeu->ajouteObjet(I_GEMME,16*76,16*82,22);
            if (!gpJoueur->getGemme(23)) gpJeu->ajouteObjet(I_GEMME,16*24,16*30,23);
            break;
        case 4 :
            if (!gpJoueur->getCoffre(15,2)) {
                gpJeu->ajouteEnnemi(79,32*16,29*16);
                gpJeu->ajouteEnnemi(79,53*16,24*16);
                gpJeu->ajouteEnnemi(80,39*16,23*16);
                gpJeu->ajoutePiege(81,25*16,38*16);
                gpJeu->ajoutePiege(81,55*16,39*16);
                gpJeu->ajouteEnnemi(82,45*16,47*16);
                gpJeu->ajouteEnnemi(82,21*16,23*16);
                gpJeu->ajouteEnnemi(83,49*16,31*16);
                gpJeu->ajouteEnnemi(83,32*16,44*16);
                gpJeu->ajouteEnnemi(83,43*16,28*16);
            }
            if (!gpJoueur->getGemme(32)) gpJeu->ajouteObjet(I_GEMME,16*3,16*44,32);
            if (!gpJoueur->getGemme(33)) gpJeu->ajouteObjet(I_GEMME,16*62,16*5,33);
            break;
        case 5 :
            if (!gpJoueur->getCoeur(19)) gpJeu->ajouteObjet(I_QUART_COEUR,9*16-8,75*16,19);
            gpJeu->ajouteEnnemi(77,43*16,59*16); gpJeu->ajouteEnnemi(77,32*16,68*16);
            gpJeu->ajouteEnnemi(77,52*16,21*16); gpJeu->ajouteEnnemi(77,23*16,9*16);
            gpJeu->ajouteEnnemi(77,13*16,27*16); gpJeu->ajouteEnnemi(77,14*16,55*16);
            gpJeu->ajouteEnnemi(77,48*16,72*16); gpJeu->ajouteEnnemi(77,53*16,41*16);
            if (!gpJoueur->getGemme(40)) gpJeu->ajouteObjet(I_GEMME,16*35,16*42,40);
            if (!gpJoueur->getGemme(41)) gpJeu->ajouteObjet(I_GEMME,16*56,16*50,41);
            break;
        case 6 :
            gpJeu->ajoutePnj(66,16*16+8,66*16,202);
            gpJeu->ajouteEnnemi(42,31*16,27*16); gpJeu->ajouteEnnemi(42,41*16,12*16);
            gpJeu->ajouteEnnemi(42,64*16,28*16); gpJeu->ajouteEnnemi(42,7*16,18*16);
            gpJeu->ajouteEnnemi(42,54*16,82*16); gpJeu->ajouteEnnemi(42,41*16,44*16);
            gpJeu->ajouteEnnemi(42,25*16,39*16);
            if (!gpJoueur->getGemme(53)) gpJeu->ajouteObjet(I_GEMME,16*65+8,16*36,53);
            if (!gpJoueur->getGemme(54)) gpJeu->ajouteObjet(I_GEMME,16*55,16*55,54);
            break;
        case 7 :
            gpJeu->ajouteEnnemi(77,19*16,28*16);
            gpJeu->ajouteEnnemi(41,27*16,6*16); gpJeu->ajouteEnnemi(41,65*16,14*16);
            gpJeu->ajouteEnnemi(41,94*16,7*16); gpJeu->ajouteEnnemi(41,112*16,17*16);
            gpJeu->ajouteEnnemi(41,52*16,34*16); gpJeu->ajouteEnnemi(41,89*16,37*16);
            if (!gpJoueur->getGemme(62)) gpJeu->ajouteObjet(I_GEMME,16*120,16*39,62);
            if (!gpJoueur->getGemme(63)) gpJeu->ajouteObjet(I_GEMME,16*10,16*21,63);
            if (!gpJoueur->getGemme(64)) gpJeu->ajouteObjet(I_GEMME,16*134,16*17,64);
            break;
        case 8 :
            gpJeu->ajouteEnnemi(64,39*16-4,20*16); gpJeu->ajouteEnnemi(64,18*16-4,33*16);
            gpJeu->ajouteEnnemi(64,55*16-4,22*16); gpJeu->ajouteEnnemi(64,20*16-4,22*16);
            if (!gpJoueur->getGemme(71)) gpJeu->ajouteObjet(I_GEMME,16*48,16*7,71);
            if (!gpJoueur->getGemme(72)) gpJeu->ajouteObjet(I_GEMME,16*26,16*16,72);
            if (!gpJoueur->getGemme(73)) gpJeu->ajouteObjet(I_GEMME,16*20,16*36,73);
            break;
        case 9 :
            if (gpJoueur->getCoffre(15,28)==1) {
                gpJeu->ajoutePnj(90,135*16,35*16,0);
                gpJeu->ajoutePnj(101,134*16,38*16,0);
            }
            gpJeu->ajouteEnnemi(77,33*16,38*16); gpJeu->ajouteEnnemi(77,38*16,50*16);
            gpJeu->ajouteEnnemi(77,49*16,30*16); gpJeu->ajouteEnnemi(77,59*16,55*16);
            gpJeu->ajouteEnnemi(77,65*16,42*16); gpJeu->ajouteEnnemi(77,86*16,13*16);
            gpJeu->ajouteEnnemi(77,99*16,42*16); gpJeu->ajouteEnnemi(77,110*16,23*16);
            if (!gpJoueur->getGemme(82)) gpJeu->ajouteObjet(I_GEMME,16*62,16*3,82);
            if (!gpJoueur->getGemme(83)) gpJeu->ajouteObjet(I_GEMME,16*43,16*52,83);
            if (!gpJoueur->getGemme(84)) gpJeu->ajouteObjet(I_GEMME,16*97,16*21,84);
            break;
        case 10 :
            if (gpJeu->getJoueur()->nbCristaux()>=3 && gpJeu->getJoueur()->hasObjet(O_TROC4)>=6
            && !gpJeu->getJoueur()->hasCristal(3)) {
                gpJeu->ajoutePnj(37,43*16,12*16,1369);
                gpJeu->ajoutePnj(36,45*16,8*16,1370);
                Pnj* pnj = gpJeu->getPnj()->getSuivant();
                while (pnj != NULL) {
                    pnj->setImmo(true);
                    pnj = pnj->getSuivant();
                }
            } else {
                gpJeu->ajoutePnj(37,39*16,31*16,236);
                gpJeu->ajoutePnj(36,55*16,36*16,237);
            }
            gpJeu->ajoutePnj(12,62*16+8,40*16+5,228); 
            contenu[62][42]=228; contenu[63][42]=228;
            gpJeu->ajoutePnj(19,49*16+8,48*16+5,234); 
            contenu[49][50]=234; contenu[50][50]=234;
            if (!gpJoueur->getGemme(89)) gpJeu->ajouteObjet(I_GEMME,16*49,16*55,89);
            if (!gpJoueur->getGemme(90)) gpJeu->ajouteObjet(I_GEMME,16*66,16*28,90);
            // gemmes 91 à 93 via le troc
            break;
        case 11 :
            gpJeu->ajouteEnnemi(41,59*16,63*16); gpJeu->ajouteEnnemi(41,78*16,60*16);
            gpJeu->ajouteEnnemi(41,120*16,68*16); gpJeu->ajouteEnnemi(41,121*16,38*16);
            gpJeu->ajouteEnnemi(41,13*16,38*16);
            gpJeu->ajouteEnnemi(77,119*16,9*16); gpJeu->ajouteEnnemi(77,23*16,8*16);
            gpJeu->ajouteEnnemi(77,65*16,10*16);
            if (!gpJoueur->getGemme(102)) gpJeu->ajouteObjet(I_GEMME,16*46,16*25,102);
            if (!gpJoueur->getGemme(103)) gpJeu->ajouteObjet(I_GEMME,16*115,16*31,103);
            if (!gpJoueur->getGemme(104)) gpJeu->ajouteObjet(I_GEMME,16*86,16*5,104);
            break;
        case 12 :
            gpJeu->ajouteEnnemi(41,108*16,24*16); gpJeu->ajouteEnnemi(41,109*16,62*16);
            gpJeu->ajouteEnnemi(87,48*16,27*16); gpJeu->ajouteEnnemi(87,16*16,43*16);
            gpJeu->ajouteEnnemi(87,33*16,57*16); gpJeu->ajouteEnnemi(87,55*16,51*16);
            gpJeu->ajouteEnnemi(87,71*16,59*16); gpJeu->ajouteEnnemi(87,72*16,35*16);
            if (!gpJoueur->getGemme(111)) gpJeu->ajouteObjet(I_GEMME,16*135,16*56,111);
            if (!gpJoueur->getGemme(112)) gpJeu->ajouteObjet(I_GEMME,16*110,16*72,112);
            if (!gpJoueur->getGemme(113)) gpJeu->ajouteObjet(I_GEMME,16*27,16*66,113);
            break;
        case 13 :
            gpJeu->ajoutePnj(41,34*16+8,34*16+5,278);
            contenu[34][36]=278; contenu[35][36]=278;
            gpJeu->ajoutePnj(43,50*16+8,44*16+5,281);
            contenu[50][46]=281; contenu[51][46]=281;
            gpJeu->ajoutePnj(33,17*16,28*16,283);
            gpJeu->ajoutePnj(14,42*16+8,30*16,284);
            if (!gpJoueur->getGemme(119)) gpJeu->ajouteObjet(I_GEMME,16*9,16*18,119);
            if (!gpJoueur->getGemme(120)) gpJeu->ajouteObjet(I_GEMME,16*28,16*10,120);
            if (!gpJoueur->getGemme(121)) gpJeu->ajouteObjet(I_GEMME,16*58,16*53,121);
            break;
        case 14 :
            gpJeu->ajouteEnnemi(77,16*16,64*16); gpJeu->ajouteEnnemi(77,33*16,38*16);
            if (!gpJoueur->getGemme(128)) gpJeu->ajouteObjet(I_GEMME,16*26,16*39,128);
            if (!gpJoueur->getGemme(129)) gpJeu->ajouteObjet(I_GEMME,16*34,16*17,129);
            if (!gpJoueur->getGemme(130)) gpJeu->ajouteObjet(I_GEMME,16*40,16*28,130);
            break;
        case 15 :
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>4) gpJeu->ajoutePnj(77,114*16,12*16,306);
            else gpJeu->ajoutePnj(76,114*16,12*16,306);
            gpJeu->ajoutePnj(74,117*16+8,6*16+8,307);
            gpJeu->ajoutePnj(75,102*16,4*16,306);
            gpJeu->ajouteEnnemi(42,105*16,45*16); gpJeu->ajouteEnnemi(42,86*16,25*16);
            gpJeu->ajouteEnnemi(42,50*16,36*16); gpJeu->ajouteEnnemi(42,28*16,45*16);
            gpJeu->ajouteEnnemi(42,25*16,21*16); gpJeu->ajouteEnnemi(42,52*16,18*16);
            gpJeu->ajouteEnnemi(42,58*16,43*16);
            if (!gpJoueur->getGemme(141)) gpJeu->ajouteObjet(I_GEMME,16*6,16*9,141);
            if (!gpJoueur->getGemme(142)) gpJeu->ajouteObjet(I_GEMME,16*8,16*39,142);
            if (!gpJoueur->getGemme(143)) gpJeu->ajouteObjet(I_GEMME,16*20,16*47,143);
            if (!gpJoueur->getGemme(144)) gpJeu->ajouteObjet(I_GEMME,16*22,16*18,144);
            if (!gpJoueur->getGemme(145)) gpJeu->ajouteObjet(I_GEMME,16*110,16*33,145);
            break;
        case 16 :
            if (!gpJoueur->getCoeur(13)) gpJeu->ajouteObjet(I_QUART_COEUR,57*16+8,6*16+8,13);
            if (gpJoueur->getAvancement() < PARLE_ZELDA_PALAIS) 
                gpJeu->ajoutePnj(46,41*16+8,42*16,40);
            if (gpJoueur->getEpee() || gpJoueur->hasObjet(O_OCARINA)) {
                gpJeu->ajouteEnnemi(4,71*16,45*16); gpJeu->ajouteEnnemi(4,53*16,29*16);
                gpJeu->ajouteEnnemi(4,32*16,14*16); gpJeu->ajouteEnnemi(4,9*16,17*16);
                gpJeu->ajouteEnnemi(4,9*16,42*16); gpJeu->ajouteEnnemi(4,28*16,48*16);
                gpJeu->ajouteEnnemi(3,53*16,46*16); gpJeu->ajouteEnnemi(3,23*16,27*16);
                gpJeu->ajouteEnnemi(3,48*16,15*16); gpJeu->ajouteEnnemi(4,38*16,51*16);
            }
            if (!gpJoueur->getGemme(0)) gpJeu->ajouteObjet(I_GEMME,16*75,16*30,0);
            if (!gpJoueur->getGemme(1)) gpJeu->ajouteObjet(I_GEMME,16*27,16*34,1);
            if (!gpJoueur->getGemme(2)) gpJeu->ajouteObjet(I_GEMME,16*24,16*44,2);
            if (!gpJoueur->getGemme(3)) gpJeu->ajouteObjet(I_GEMME,16*25,16*4,3);
            break;
        case 17 :
            if (gpJoueur->getEpee() || gpJoueur->hasObjet(O_OCARINA)) {
                gpJeu->ajouteEnnemi(53,16*16,30*16); gpJeu->ajouteEnnemi(53,18*16,45*16);
                gpJeu->ajouteEnnemi(53,23*16,12*16); gpJeu->ajouteEnnemi(53,36*16,10*16);
                gpJeu->ajouteEnnemi(53,42*16,36*16); gpJeu->ajouteEnnemi(53,46*16,26*16);
                gpJeu->ajouteEnnemi(53,52*16,13*16); gpJeu->ajouteEnnemi(53,51*16,39*16);
                gpJeu->ajouteEnnemi(54,8*16,31*16); gpJeu->ajouteEnnemi(54,37*16,25*16);
                gpJeu->ajouteEnnemi(54,24*16,48*16);
            }
            if (!gpJoueur->getGemme(9)) gpJeu->ajouteObjet(I_GEMME,16*57,16*4,9);
            if (!gpJoueur->getGemme(10)) gpJeu->ajouteObjet(I_GEMME,16*4,16*52,10);
            if (!gpJoueur->getGemme(11)) gpJeu->ajouteObjet(I_GEMME,16*15,16*6,11);
            break;
        case 18 :
            if (!gpJoueur->getEpee() && !gpJoueur->hasObjet(O_OCARINA)) {
                gpJeu->ajoutePnj(46,15*16+5,60*16+8,72);
                gpJeu->ajoutePnj(46,15*16+5,77*16+8,72);
                gpJeu->ajoutePnj(46,29*16+5,77*16+8,72);
                gpJeu->ajoutePnj(46,49*16+5,77*16+8,72);
                gpJeu->ajoutePnj(46,63*16+5,77*16+8,72);
                gpJeu->ajoutePnj(46,49*16+5,61*16+8,72);
                gpJeu->ajoutePnj(46,63*16+5,61*16+8,72);
                gpJeu->ajoutePnj(46,17*16+5,41*16+8,72);
                gpJeu->ajoutePnj(46,63*16+5,34*16+8,72);
                gpJeu->ajoutePnj(46,63*16+5,45*16+8,72);
                gpJeu->ajoutePnj(58,39*16+5,7*16+8,73);
                gpJeu->ajoutePnj(57,3*16+5,59*16+8,74);
                gpJeu->ajoutePnj(57,3*16+5,65*16,74,N);
                gpJeu->ajoutePnj(57,38*16+5,87*16+8,74,N);
                gpJeu->ajoutePnj(57,40*16+5,87*16+8,74,N);
                gpJeu->ajoutePnj(57,77*16+5,61*16+8,74,O);
                gpJeu->ajoutePnj(57,77*16+5,63*16+8,74,O);
            } else {
                if (gpJoueur->hasObjet(O_SAC_TROC) &&
                (gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_UTILISE
                || gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_FERME)) {
                    gpJeu->ajoutePnj(7,32*16+8,30*16+5,77); 
                    contenu[32][32]=77; contenu[33][32]=77;
                    gpJeu->ajoutePnj(2,46*16+8,30*16+5,83); 
                    contenu[46][32]=83; contenu[47][32]=83;
                    gpJeu->ajoutePnj(20,32*16+8,37*16+5,92); 
                    contenu[32][39]=92; contenu[33][39]=92;
                    gpJeu->ajoutePnj(45,46*16+8,37*16+5,96); 
                    contenu[46][39]=96; contenu[47][39]=96;
                    gpJeu->ajoutePnj(24,32*16+8,44*16+5,99); 
                    contenu[32][46]=99; contenu[33][46]=99;
                    gpJeu->ajoutePnj(12,46*16+8,44*16+5,102); 
                    contenu[46][46]=102; contenu[47][46]=102;
                    if (gpJoueur->hasObjet(O_TROC4)<3) gpJeu->ajoutePnj(9,33*16+8,75*16,105);
                    gpJeu->ajoutePnj(10,27*16+8,57*16+8,113);
                    gpJeu->ajouteEnnemi(52,25*16,58*16);
                    gpJeu->ajouteEnnemi(52,30*16,57*16);
                    gpJeu->ajouteEnnemi(52,26*16,61*16);
                    gpJeu->ajouteEnnemi(52,33*16,62*16);
                    gpJeu->ajouteEnnemi(52,29*16,59*16);
                    gpJeu->ajoutePnj(11,56*16+8,67*16+8,114);
                    gpJeu->ajoutePnj(1,21*16+8,83*16+8,115);
                    gpJeu->ajoutePnj(36,39*16+8,33*16+8,116);
                    gpJeu->ajoutePnj(35,43*16+8,51*16,117);
                    gpJeu->ajoutePnj(34,53*16+8,72*16+8,120);
                    gpJeu->ajoutePnj(57,3*16+5,59*16+8,119,E);
                    gpJeu->ajoutePnj(57,3*16+5,65*16,118,E);
                    gpJeu->ajoutePnj(57,75*16+5,59*16+8,121,O);
                    gpJeu->ajoutePnj(57,75*16+5,65*16,122,O);
                    gpJeu->ajoutePnj(57,36*16+5,85*16+8,123,N);
                    gpJeu->ajoutePnj(57,42*16+5,85*16+8,124,N); gpJeu->ajouteProjectile(40, N, 43*16+5,85*16, 0);
                }
            }
            if (!gpJoueur->getGemme(18)) gpJeu->ajouteObjet(I_GEMME,16*66,16*14,18);
            if (!gpJoueur->getGemme(24)) gpJeu->ajouteObjet(I_GEMME,16*11,16*36,24);
            break;
        case 19 :
            if (gpJoueur->getEpee()<5) {
            gpJeu->ajoutePnj(58,37*16,43*16+8,188);
            gpJeu->ajoutePnj(58,41*16+10,43*16+8,189);}
            if (gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_UTILISE
            && gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_FERME) {
                gpJeu->ajoutePnj(68,61*16+5,30*16,124); gpJeu->ajouteProjectile(40, N, 62*16+5,30*16-8, 0);
                gpJeu->ajoutePnj(68,52*16+5+8,48*16,124); gpJeu->ajouteProjectile(40, N, 53*16+5+8,48*16-8, 0);
            }
            if (!gpJoueur->getGemme(26)) gpJeu->ajouteObjet(I_GEMME,16*9,16*27,26);
            if (!gpJoueur->getGemme(27)) gpJeu->ajouteObjet(I_GEMME,16*71,16*18,27);
            if (!gpJoueur->getGemme(28)) gpJeu->ajouteObjet(I_GEMME,16*26,16*33,28);
            break;
        case 20 :
            if (gpJoueur->getEpee() &&
            (gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_UTILISE
            || gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_FERME)) {
                gpJeu->ajouteEnnemi(53,16*16,52*16);
                gpJeu->ajouteEnnemi(53,10*16,77*16);
                gpJeu->ajouteEnnemi(53,39*16,75*16);
                gpJeu->ajouteEnnemi(53,34*16,60*16);
                gpJeu->ajouteEnnemi(53,53*16,43*16);
                gpJeu->ajouteEnnemi(53,53*16,20*16);
                gpJeu->ajouteEnnemi(53,35*16,31*16);
                gpJeu->ajouteEnnemi(53,23*16,8*16);
                gpJeu->ajouteEnnemi(53,14*16,34*16);
                gpJeu->ajouteEnnemi(54,17*16,22*16);
                gpJeu->ajouteEnnemi(54,45*16,9*16);
                gpJeu->ajouteEnnemi(54,40*16,40*16);
                gpJeu->ajouteEnnemi(54,24*16,47*16);
                gpJeu->ajouteEnnemi(54,50*16,66*16);
                gpJeu->ajouteEnnemi(54,26*16,80*16);
            }
            if (gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_UTILISE
            && gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_FERME) {
                gpJeu->ajoutePnj(68,25*16+5,13*16+8,124); gpJeu->ajouteProjectile(40, N, 26*16+5,13*16, 0);
                gpJeu->ajoutePnj(68,17*16+5,59*16+8,124); gpJeu->ajouteProjectile(40, N, 18*16+5,59*16, 0);
                gpJeu->ajoutePnj(68,27*16+5,79*16+8,124); gpJeu->ajouteProjectile(40, N, 28*16+5,79*16, 0);
                gpJeu->ajoutePnj(68,41*16+5,36*16,124); gpJeu->ajouteProjectile(40, N, 42*16+5,36*16-8, 0);
                gpJeu->ajoutePnj(68,19*16+5,28*16,124); gpJeu->ajouteProjectile(40, N, 20*16+5,28*16-8, 0);
                gpJeu->ajoutePnj(68,9*16+5,85*16,124); gpJeu->ajouteProjectile(40, N, 10*16+5,85*16-8, 0);
                gpJeu->ajoutePnj(68,7*16+5,84*16,124); gpJeu->ajouteProjectile(40, N, 8*16+5,84*16-8, 0);
            }
            if (!gpJoueur->getGemme(34)) gpJeu->ajouteObjet(I_GEMME,16*2,16*77,34);
            if (!gpJoueur->getGemme(35)) gpJeu->ajouteObjet(I_GEMME,16*44,16*4,35);
            if (!gpJoueur->getGemme(36)) gpJeu->ajouteObjet(I_GEMME,16*10,16*16,36);
            break;
        case 21 :
            if (!gpJoueur->getCoeur(20)) gpJeu->ajouteObjet(I_QUART_COEUR,77*16,76*16,20);
            // stèle lue ou pré-présent
            if (gpJoueur->getAvancement() >= STELE_LUE &&
            (gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_UTILISE
            || gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_FERME)) {
                gpJeu->ajouteEnnemi(4,9*16,51*16);
                gpJeu->ajouteEnnemi(4,4*16,60*16);
                gpJeu->ajouteEnnemi(4,22*16,46*16);
                gpJeu->ajouteEnnemi(4,25*16,52*16);
                gpJeu->ajouteEnnemi(4,14*16,35*16);
                gpJeu->ajouteEnnemi(4,7*16,16*16);
                gpJeu->ajouteEnnemi(4,20*16,25*16);
                gpJeu->ajouteEnnemi(4,41*16,12*16);
                gpJeu->ajouteEnnemi(4,61*16,45*16);
                gpJeu->ajouteEnnemi(4,54*16,54*16);
                gpJeu->ajouteEnnemi(4,61*16,62*16);
                gpJeu->ajouteEnnemi(4,53*16,83*16);
                gpJeu->ajouteEnnemi(4,38*16,73*16);
                gpJeu->ajouteEnnemi(4,32*16,67*16);
                gpJeu->ajouteEnnemi(4,41*16,46*16);
                gpJeu->ajouteEnnemi(4,50*16,32*16);
                gpJeu->ajouteEnnemi(4,74*16,30*16);
                gpJeu->ajouteEnnemi(4,34*16,34*16);
                gpJeu->ajouteEnnemi(4,42*16,21*16);
                gpJeu->ajouteEnnemi(4,47*16,59*16);
                gpJeu->ajouteEnnemi(54,69*16,16*16);
                gpJeu->ajouteEnnemi(54,37*16,25*16);
                gpJeu->ajouteEnnemi(54,69*16,60*16);
                gpJeu->ajouteEnnemi(54,49*16,72*16);
                gpJeu->ajouteEnnemi(54,12*16,62*16);
                gpJeu->ajouteEnnemi(54,45*16,83*16);
                gpJeu->ajouteEnnemi(54,75*16,72*16);
                gpJeu->ajouteEnnemi(54,13*16,82*16);
                gpJeu->ajouteEnnemi(54,6*16,73*16);
                gpJeu->ajouteEnnemi(54,21*16,78*16);
                gpJeu->ajouteEnnemi(54,4*16,85*16);
                gpJeu->ajouteEnnemi(54,11*16,40*16);
                gpJeu->ajouteEnnemi(54,45*16,65*16);
                gpJeu->ajouteEnnemi(54,68*16,49*16);
                gpJeu->ajouteEnnemi(54,50*16,14*16);
                gpJeu->ajouteEnnemi(54,59*16,23*16);
                
            }
            if (gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_UTILISE
            && gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_FERME) {
                gpJeu->ajoutePnj(68,44*16+5,2*16+8,124); gpJeu->ajouteProjectile(40, N, 45*16+5,2*16, 0);
                gpJeu->ajoutePnj(68,27*16+5,11*16,124); gpJeu->ajouteProjectile(40, N, 28*16+5,10*16+8, 0);
                gpJeu->ajoutePnj(68,33*16+5-8,31*16+8,124); gpJeu->ajouteProjectile(40, N, 34*16+5-8,31*16, 0);
                gpJeu->ajoutePnj(68,15*16+5,11*16,124); gpJeu->ajouteProjectile(40, N, 16*16+5,10*16+8, 0);
                gpJeu->ajoutePnj(68,9*16+5,8*16+8,124); gpJeu->ajouteProjectile(40, N, 10*16+5,8*16, 0);
                gpJeu->ajoutePnj(68,8*16+5-8,31*16+8,124); gpJeu->ajouteProjectile(40, N, 9*16+5-8,31*16, 0);
            }
            if (!gpJoueur->getGemme(42)) gpJeu->ajouteObjet(I_GEMME,16*25,16*58,42);
            if (!gpJoueur->getGemme(43)) gpJeu->ajouteObjet(I_GEMME,16*50,16*55,43);
            if (!gpJoueur->getGemme(44)) gpJeu->ajouteObjet(I_GEMME,16*54,16*23,44);
            if (!gpJoueur->getGemme(45)) gpJeu->ajouteObjet(I_GEMME,16*23,16*43,45);
            if (!gpJoueur->getGemme(46)) gpJeu->ajouteObjet(I_GEMME,16*9,16*66,46);
            break;
        case 22 :
            if (!gpJoueur->getCoeur(21)) gpJeu->ajouteObjet(I_QUART_COEUR,132*16,20*16,21);
            if (gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_UTILISE
            || gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_FERME) {
                gpJeu->ajoutePnj(71,124*16,8*16,238,S);
                gpJeu->ajouteEnnemi(10,119*16,7*16); gpJeu->ajouteEnnemi(10,119*16,9*16);
                gpJeu->ajouteEnnemi(10,123*16,12*16); gpJeu->ajouteEnnemi(10,126*16,12*16);
                enn = gpJeu->getEnnemi()->getSuivant();
                for (int i = 0; i < 4; i++) {
                    enn->setVie(0);
                    enn=enn->getSuivant();
                }
                gpJeu->ajouteEnnemi(27,29*16,3*16); gpJeu->ajouteEnnemi(27,53*16,12*16);
                gpJeu->ajouteEnnemi(27,76*16,16*16);
                gpJeu->ajouteEnnemi(53,27*16,27*16); gpJeu->ajouteEnnemi(53,94*16,38*16);
                gpJeu->ajouteEnnemi(53,59*16,39*16); gpJeu->ajouteEnnemi(53,54*16,31*16);
                gpJeu->ajouteEnnemi(54,108*16,39*16); gpJeu->ajouteEnnemi(54,124*16,32*16);
                gpJeu->ajouteEnnemi(54,79*16,37*16); gpJeu->ajouteEnnemi(54,94*16,15*16);
            }
            if (gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_UTILISE
            && gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_FERME) {
                gpJeu->ajoutePnj(68,9*16+5,36*16+8-2,124); gpJeu->ajouteProjectile(40, N, 10*16+5,36*16-2, 0);
                gpJeu->ajoutePnj(68,21*16+5,12*16+8,124); gpJeu->ajouteProjectile(40, N, 22*16+5,12*16, 0);
                gpJeu->ajoutePnj(68,36*16+5+8,4*16-2,124); gpJeu->ajouteProjectile(40, N, 37*16+5+8,4*16-8-2, 0);
                gpJeu->ajoutePnj(68,49*16+5,9*16,124); gpJeu->ajouteProjectile(40, N, 50*16+5,9*16-8, 0);
                gpJeu->ajoutePnj(68,56*16+5,29*16,124); gpJeu->ajouteProjectile(40, N, 57*16+5,29*16-8, 0);
                if (gpJoueur->getAvancement()<PLANCHES_TROUVEES) 
                    gpJeu->ajouteObjet(I_PLANCHES,16*23,16*28);
            }
            if (!gpJoueur->getGemme(55)) gpJeu->ajouteObjet(I_GEMME,16*10,16*29,55);
            if (!gpJoueur->getGemme(56)) gpJeu->ajouteObjet(I_GEMME,16*53,16*3,56);
            if (!gpJoueur->getGemme(57)) gpJeu->ajouteObjet(I_GEMME,16*118,16*22,57);
            break;
        case 23 :
            gpJeu->ajouteEnnemi(12,17*16,8*16); gpJeu->ajouteEnnemi(12,62*16,8*16);
            gpJeu->ajouteEnnemi(12,16*16,24*16);
            if (!gpJoueur->getGemme(65)) gpJeu->ajouteObjet(I_GEMME,16*69,16*30,65);
            if (!gpJoueur->getGemme(66)) gpJeu->ajouteObjet(I_GEMME,16*15,16*16,66);
            if (!gpJoueur->getGemme(67)) gpJeu->ajouteObjet(I_GEMME,16*51,16*26,67);
            break;
        case 24 :
            gpJeu->ajouteEnnemi(20,6*16,17*16); setValeur(6*16,17*16,0,2);
            if (gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_UTILISE
            || gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_FERME) {
                gpJeu->ajoutePnj(68,8*16+5,15*16+8,124); gpJeu->ajouteProjectile(40, N, 9*16+5,15*16, 0);
                gpJeu->ajouteEnnemi(8,48*16,32*16); gpJeu->ajouteEnnemi(8,34*16,50*16);
                gpJeu->ajouteEnnemi(8,64*16,44*16); gpJeu->ajouteEnnemi(8,97*16,28*16);
                gpJeu->ajouteEnnemi(53,27*16,35*16); gpJeu->ajouteEnnemi(53,21*16,9*16);
                gpJeu->ajouteEnnemi(53,45*16,10*16); gpJeu->ajouteEnnemi(53,98*16,7*16);
                gpJeu->ajouteEnnemi(53,113*16,22*16); gpJeu->ajouteEnnemi(53,83*16,25*16);
                gpJeu->ajouteEnnemi(53,49*16,46*16); gpJeu->ajouteEnnemi(53,90*16,39*16);
                gpJeu->ajouteEnnemi(53,116*16,51*16);
                gpJeu->ajouteEnnemi(54,65*16,31*16); gpJeu->ajouteEnnemi(54,92*16,22*16);
                gpJeu->ajouteEnnemi(54,80*16,10*16); gpJeu->ajouteEnnemi(54,34*16,11*16);
                gpJeu->ajouteEnnemi(54,54*16,6*16); gpJeu->ajouteEnnemi(54,104*16,17*16);
                gpJeu->ajouteEnnemi(54,104*16,43*16); gpJeu->ajouteEnnemi(54,74*16,54*16);
                gpJeu->ajouteEnnemi(54,115*16,8*16); gpJeu->ajouteEnnemi(54,95*16,53*16);
                gpJeu->ajouteEnnemi(54,41*16,55*16);
            }
            if (!gpJoueur->getGemme(74)) gpJeu->ajouteObjet(I_GEMME,16*13,16*56,74);
            if (!gpJoueur->getGemme(75)) gpJeu->ajouteObjet(I_GEMME,16*59,16*3,75);
            if (!gpJoueur->getGemme(76)) gpJeu->ajouteObjet(I_GEMME,16*58,16*40,76);
            if (!gpJoueur->getGemme(77)) gpJeu->ajouteObjet(I_GEMME,16*109,16*38,77);
            break;
        case 25 :
            gpJeu->ajoutePnj(20,56*16+8,19*16+5,215); 
            contenu[56][21]=215; contenu[57][21]=215;
            gpJeu->ajoutePnj(7,56*16+8,26*16+5,218); 
            contenu[56][28]=218; contenu[57][28]=218;
            gpJeu->ajoutePnj(45,62*16+8,40*16+5,220); 
            contenu[62][42]=220; contenu[63][42]=220;
            gpJeu->ajoutePnj(24,49*16+8,48*16+5,222); 
            contenu[49][50]=222; contenu[50][50]=222;
            gpJeu->ajoutePnj(52,41*16,31*16,224);
            gpJeu->ajoutePnj(69,56*16,40*16,225);
            gpJeu->ajoutePiege(85,11*16,55*16); gpJeu->ajoutePiege(85,32*16,52*16);
            gpJeu->ajoutePiege(85,37*16,18*16); gpJeu->ajoutePiege(85,65*16,28*16);
            gpJeu->ajoutePiege(85,42*16,41*16); gpJeu->ajoutePiege(85,64*16,57*16);
            gpJeu->ajoutePiege(85,61*16,23*16); gpJeu->ajoutePiege(85,49*16,34*16);
            gpJeu->ajoutePiege(85,8*16,31*16); gpJeu->ajoutePiege(85,51*16,61*16);
            if (!gpJoueur->getGemme(85)) gpJeu->ajouteObjet(I_GEMME,16*72,16*36,85);
            if (!gpJoueur->getGemme(86)) gpJeu->ajouteObjet(I_GEMME,16*29,16*72,86);
            break;
        case 26 :
            if (gpJoueur->hasObjet(O_POISSONS)) {
                gpJeu->ajoutePnj(73,121*16,40*16,251);
            }
            else gpJeu->ajoutePnj(72,118*16+8,45*16+8,250);
            gpJeu->ajouteEnnemi(8,113*16,10*16);
            gpJeu->ajouteEnnemi(9,13*16,35*16); gpJeu->ajouteEnnemi(9,23*16,70*16);
            gpJeu->ajouteEnnemi(9,116*16,69*16); gpJeu->ajouteEnnemi(9,62*16,61*16);
            gpJeu->ajouteEnnemi(9,69*16,42*16);
            gpJeu->ajouteEnnemi(10,97*16,42*16); gpJeu->ajouteEnnemi(10,52*16,46*16);
            gpJeu->ajouteEnnemi(10,31*16,30*16); gpJeu->ajouteEnnemi(10,71*16,27*16);
            gpJeu->ajouteEnnemi(53,22*16,10*16); gpJeu->ajouteEnnemi(53,45*16,12*16);
            gpJeu->ajouteEnnemi(53,74*16,8*16); gpJeu->ajouteEnnemi(53,86*16,17*16);
            gpJeu->ajouteEnnemi(53,129*16,13*16);
            gpJeu->ajouteEnnemi(54,124*16,4*16); gpJeu->ajouteEnnemi(54,118*16,17*16);
            gpJeu->ajouteEnnemi(54,56*16,71*16); gpJeu->ajouteEnnemi(54,80*16,69*16);
            if (!gpJoueur->getGemme(94)) gpJeu->ajouteObjet(I_GEMME,16*4,16*32,94);
            if (!gpJoueur->getGemme(95)) gpJeu->ajouteObjet(I_GEMME,16*50,16*68,95);
            if (!gpJoueur->getGemme(96)) gpJeu->ajouteObjet(I_GEMME,16*90,16*7,96);
            break;
        case 27 :
            gpJeu->ajouteEnnemi(7,17*16,37*16); gpJeu->ajouteEnnemi(7,31*16,58*16);
            gpJeu->ajouteEnnemi(7,56*16,20*16); gpJeu->ajouteEnnemi(7,75*16,53*16);
            gpJeu->ajouteEnnemi(7,31*16,19*16);
            gpJeu->ajouteEnnemi(9,123*16,69*16); gpJeu->ajouteEnnemi(9,102*16,32*16);
            gpJeu->ajouteEnnemi(13,12*16-9,47*16-4); gpJeu->ajouteEnnemi(13,43*16-9,15*16-4);
            gpJeu->ajouteEnnemi(13,69*16-9,45*16-4); gpJeu->ajouteEnnemi(13,43*16-9,61*16-4);
            gpJeu->ajouteEnnemi(14,26*16-12,44*16); gpJeu->ajouteEnnemi(14,67*16-12,59*16);
            gpJeu->ajouteEnnemi(14,72*16-12,16*16); gpJeu->ajouteEnnemi(14,51*16-12,31*16);
            if (!gpJoueur->getGemme(105)) gpJeu->ajouteObjet(I_GEMME,16*124,16*30,105);
            if (!gpJoueur->getGemme(106)) gpJeu->ajouteObjet(I_GEMME,16*103,16*65,106);
            if (!gpJoueur->getGemme(107)) gpJeu->ajouteObjet(I_GEMME,16*70,16*55,107);
            break;
        case 28 :
            gpJeu->ajoutePnj(12,34*16+8,34*16+5,265); 
            contenu[34][36]=265; contenu[35][36]=265;
            gpJeu->ajoutePnj(20,50*16+8,34*16+5,268); 
            contenu[50][36]=268; contenu[51][36]=268;
            gpJeu->ajoutePnj(2,34*16+8,44*16+5,271); 
            contenu[34][46]=271; contenu[35][46]=271;
            gpJeu->ajoutePnj(7,50*16+8,44*16+5,273); 
            contenu[50][46]=273; contenu[51][46]=273;
            gpJeu->ajoutePnj(13,13*16,24*16,275);
            gpJeu->ajoutePnj(23,68*16,32*16,276);
            gpJeu->ajoutePnj(1,42*16,33*16,277);
            if (!gpJoueur->getGemme(114)) gpJeu->ajouteObjet(I_GEMME,16*6,16*65,114);
            if (!gpJoueur->getGemme(115)) gpJeu->ajouteObjet(I_GEMME,16*69,16*10,115);
            if (!gpJoueur->getGemme(116)) gpJeu->ajouteObjet(I_GEMME,16*10,16*5,116);
            break;
        case 29 :
            if (!gpJoueur->getCoeur(26)) gpJeu->ajouteObjet(I_QUART_COEUR,39*16+8,70*16+8,26);
            gpJeu->ajouteEnnemi(8,19*16,61*16);
            gpJeu->ajouteEnnemi(53,39*16,41*16);
            gpJeu->ajouteEnnemi(54,11*16,47*16); gpJeu->ajouteEnnemi(54,17*16,24*16);
            gpJeu->ajouteEnnemi(54,34*16,9*16);
            if (!gpJoueur->getGemme(122)) gpJeu->ajouteObjet(I_GEMME,16*39,16*28,122);
            if (!gpJoueur->getGemme(123)) gpJeu->ajouteObjet(I_GEMME,16*46,16*12,123);
            if (!gpJoueur->getGemme(124)) gpJeu->ajouteObjet(I_GEMME,16*40,16*65,124);
            break;
        case 30 :
            gpJeu->ajoutePnj(21,9*16+8,8*16,288);
            gpJeu->ajouteEnnemi(5,87*16,22*16); gpJeu->ajouteEnnemi(5,61*16,22*16);
            gpJeu->ajouteEnnemi(5,31*16,49*16); gpJeu->ajouteEnnemi(5,62*16,43*16);
            gpJeu->ajouteEnnemi(5,96*16,41*16); gpJeu->ajouteEnnemi(5,32*16,28*16);
            gpJeu->ajouteEnnemi(6,50*16,35*16); gpJeu->ajouteEnnemi(6,23*16,21*16);
            gpJeu->ajouteEnnemi(6,76*16,30*16); gpJeu->ajouteEnnemi(6,28*16,36*16);
            gpJeu->ajouteEnnemi(6,49*16,46*16);
            if (!gpJoueur->getGemme(131)) gpJeu->ajouteObjet(I_GEMME,16*71,16*45,131);
            if (!gpJoueur->getGemme(132)) gpJeu->ajouteObjet(I_GEMME,16*97,16*29,132);
            if (!gpJoueur->getGemme(133)) gpJeu->ajouteObjet(I_GEMME,16*101,16*41,133);
            if (!gpJoueur->getGemme(134)) gpJeu->ajouteObjet(I_GEMME,16*40,16*46,134);
            if (!gpJoueur->getGemme(135)) gpJeu->ajouteObjet(I_GEMME,16*19,16*28,135);
            break;
        case 31 :
            if (!gpJoueur->getCoeur(16)) gpJeu->ajouteObjet(I_QUART_COEUR,11*16,5*16,16);
            gpJeu->ajouteEnnemi(32,9*16,41*16); gpJeu->ajouteEnnemi(32,11*16,17*16);
            gpJeu->ajouteEnnemi(32,27*16,28*16); gpJeu->ajouteEnnemi(32,29*16,50*16);
            gpJeu->ajouteEnnemi(32,47*16,50*16); gpJeu->ajouteEnnemi(32,48*16,12*16);
            gpJeu->ajouteEnnemi(32,55*16,28*16); gpJeu->ajouteEnnemi(32,68*16,10*16);
            gpJeu->ajouteEnnemi(32,70*16,46*16); gpJeu->ajouteEnnemi(32,36*16,16*16);
            gpJeu->ajouteEnnemi(32,8*16,53*16); gpJeu->ajouteEnnemi(11,9*16,2*16);
            if (!gpJoueur->getGemme(4)) gpJeu->ajouteObjet(I_GEMME,16*22,16*17,4);
            if (!gpJoueur->getGemme(5)) gpJeu->ajouteObjet(I_GEMME,16*65,16*36,5);
            break;
        case 32 :
            gpJeu->ajouteEnnemi(32,15*16,7*16); gpJeu->ajouteEnnemi(32,19*16,28*16);
            gpJeu->ajouteEnnemi(32,40*16,27*16); gpJeu->ajouteEnnemi(32,52*16,8*16);
            gpJeu->ajouteEnnemi(55,27*16,12*16); gpJeu->ajouteEnnemi(55,9*16,28*16);
            gpJeu->ajouteEnnemi(55,21*16,45*16); gpJeu->ajouteEnnemi(55,43*16,37*16);
            gpJeu->ajouteEnnemi(55,56*16,18*16); gpJeu->ajouteEnnemi(11,33*16,10*16);
            if (!gpJoueur->getGemme(12)) gpJeu->ajouteObjet(I_GEMME,16*18,16*5,12);
            if (!gpJoueur->getGemme(13)) gpJeu->ajouteObjet(I_GEMME,16*57,16*3,13);
            if (!gpJoueur->getGemme(14)) gpJeu->ajouteObjet(I_GEMME,16*7,16*21,14);
            break;
        case 33 :
            if (!gpJoueur->getCoeur(17)) gpJeu->ajouteObjet(I_QUART_COEUR,28*16,60*16,17);
            if (!gpJoueur->hasObjet(O_PERLE)) gpJeu->ajoutePnj(7,32*16+8,30*16+5,126);
            else gpJeu->ajoutePnj(53,32*16+8,30*16+5,126); 
            contenu[32][32]=126; contenu[33][32]=126;
            gpJeu->ajoutePnj(30,46*16+8,30*16+5,129); 
            contenu[46][32]=129; contenu[47][32]=129;
            gpJeu->ajoutePnj(49,32*16+8,37*16+5,138); 
            contenu[32][39]=138; contenu[33][39]=138;
            gpJeu->ajoutePnj(27,46*16+8,37*16+5,144); 
            contenu[46][39]=144; contenu[47][39]=144;
            gpJeu->ajoutePnj(59,32*16+8,44*16+5,147); 
            contenu[32][46]=147; contenu[33][46]=147;
            gpJeu->ajoutePnj(31,46*16+8,44*16+5,150); 
            contenu[46][46]=150; contenu[47][46]=150;
            gpJeu->ajoutePnj(61,54*16,68*16,153);
            gpJeu->ajoutePnj(3,23*16,51*16,154);
            gpJeu->ajoutePnj(4,64*16,83*16,155);
            gpJeu->ajoutePnj(5,40*16,36*16,156);
            gpJeu->ajoutePnj(6,22*16,67*16,157);
            gpJeu->ajouteEnnemi(78,25*16,58*16);
            gpJeu->ajouteEnnemi(78,30*16,57*16);
            gpJeu->ajouteEnnemi(78,26*16,61*16);
            gpJeu->ajouteEnnemi(78,33*16,62*16);
            gpJeu->ajouteEnnemi(78,29*16,59*16);
            if (!gpJoueur->getGemme(19)) gpJeu->ajouteObjet(I_GEMME,16*53,16*43,19);
            if (!gpJoueur->getGemme(20)) gpJeu->ajouteObjet(I_GEMME,16*24,16*59,20);
            if (!gpJoueur->getGemme(25)) gpJeu->ajouteObjet(I_GEMME,16*39,16*50,25);
            break;
        case 34 :
            if (gpJoueur->getCoffre(15,1)) {
                gpJeu->ajoutePnj(65,37*16,43*16+8,193);
                gpJeu->ajoutePnj(65,41*16+10,43*16+8,193);}
            else {
                gpJeu->ajoutePnj(65,38*16+6,43*16+8,191);
                gpJeu->ajoutePnj(65,40*16+4,43*16+8,191);}
            if (!gpJoueur->getGemme(29)) gpJeu->ajouteObjet(I_GEMME,16*70,16*54,29);
            if (!gpJoueur->getGemme(30)) gpJeu->ajouteObjet(I_GEMME,16*76,16*39,30);
            if (!gpJoueur->getGemme(31)) gpJeu->ajouteObjet(I_GEMME,16*9,16*21,31);
            break;
        case 35 :
            if (!gpJoueur->isLapin()) {
                gpJeu->ajouteEnnemi(32,12*16,36*16); gpJeu->ajouteEnnemi(32,30*16,6*16);
                gpJeu->ajouteEnnemi(32,35*16,34*16); gpJeu->ajouteEnnemi(32,49*16,11*16);
                gpJeu->ajouteEnnemi(32,8*16,79*16); gpJeu->ajouteEnnemi(32,51*16,71*16);
                gpJeu->ajouteEnnemi(32,27*16,79*16);
                gpJeu->ajouteEnnemi(55,17*16,15*16); gpJeu->ajouteEnnemi(55,53*16,49*16);
                gpJeu->ajouteEnnemi(55,38*16,65*16); gpJeu->ajouteEnnemi(55,25*16,51*16);
                gpJeu->ajouteEnnemi(11,8*16,86*16);
            }
            if (!gpJoueur->getGemme(37)) gpJeu->ajouteObjet(I_GEMME,16*4,16*78,37);
            if (!gpJoueur->getGemme(38)) gpJeu->ajouteObjet(I_GEMME,16*26,16*46,38);
            if (!gpJoueur->getGemme(39)) gpJeu->ajouteObjet(I_GEMME,16*29,16*61,39);
            break;
        case 36 :
            if (!gpJoueur->isLapin()) {
                gpJeu->ajouteEnnemi(32,8*16,22*16); gpJeu->ajouteEnnemi(32,54*16,65*16);
                gpJeu->ajouteEnnemi(32,40*16,65*16); gpJeu->ajouteEnnemi(32,13*16,78*16);
                gpJeu->ajouteEnnemi(32,10*16,51*16); gpJeu->ajouteEnnemi(32,38*16,43*16);
                gpJeu->ajouteEnnemi(32,54*16,16*16);
                gpJeu->ajouteEnnemi(37,30*16,13*16); gpJeu->ajouteEnnemi(37,61*16,46*16);
                gpJeu->ajouteEnnemi(37,56*16,82*16); gpJeu->ajouteEnnemi(37,21*16,84*16);
                gpJeu->ajouteEnnemi(37,22*16,45*16); gpJeu->ajouteEnnemi(37,40*16,20*16);
                gpJeu->ajouteEnnemi(11,23*16,65*16);
            }
            
            if (!gpJoueur->getGemme(47)) gpJeu->ajouteObjet(I_GEMME,16*17,16*65,47);
            if (!gpJoueur->getGemme(48)) gpJeu->ajouteObjet(I_GEMME,16*30,16*54,48);
            if (!gpJoueur->getGemme(49)) gpJeu->ajouteObjet(I_GEMME,16*28,16*79,49);
            if (!gpJoueur->getGemme(50)) gpJeu->ajouteObjet(I_GEMME,16*77,16*76,50);
            if (!gpJoueur->getGemme(51)) gpJeu->ajouteObjet(I_GEMME,16*37,16*45,51);
            if (!gpJoueur->getGemme(52)) gpJeu->ajouteObjet(I_GEMME,16*26,16*15,52);
            break;
        case 37 :
            if (!gpJoueur->getCoeur(22)) gpJeu->ajouteObjet(I_QUART_COEUR,84*16,3*16+8,22);
            gpJeu->ajouteEnnemi(32,26*16,5*16); gpJeu->ajouteEnnemi(32,90*16,15*16);
            gpJeu->ajouteEnnemi(32,61*16,15*16); gpJeu->ajouteEnnemi(32,51*16,34*16);
            gpJeu->ajouteEnnemi(32,123*16,36*16);
            gpJeu->ajouteEnnemi(84,50*16,4*16); gpJeu->ajouteEnnemi(84,79*16,37*16);
            gpJeu->ajouteEnnemi(84,33*16,29*16); gpJeu->ajouteEnnemi(84,78*16,14*16);
            gpJeu->ajouteEnnemi(84,107*16,20*16);
            gpJeu->ajouteEnnemi(11,17*16,35*16);
            if (!gpJoueur->getGemme(58)) gpJeu->ajouteObjet(I_GEMME,16*79,16*7,58);
            if (!gpJoueur->getGemme(59)) gpJeu->ajouteObjet(I_GEMME,16*10,16*29,59);
            if (!gpJoueur->getGemme(60)) gpJeu->ajouteObjet(I_GEMME,16*119,16*13,60);
            if (!gpJoueur->getGemme(61)) gpJeu->ajouteObjet(I_GEMME,16*51,16*40,61);
            break;
        case 38 :
            if (!gpJoueur->isLapin()) {
                gpJeu->ajouteEnnemi(56,17*16,8*16); gpJeu->ajouteEnnemi(56,62*16,8*16);
                gpJeu->ajouteEnnemi(56,16*16,24*16); gpJeu->ajouteEnnemi(56,46*16,19*16);
                gpJeu->ajouteEnnemi(56,61*16,23*16);
                gpJeu->ajouteEnnemi(11,48*16,4*16);
            }
            if (!gpJoueur->getGemme(68)) gpJeu->ajouteObjet(I_GEMME,16*67,16*38,68);
            if (!gpJoueur->getGemme(69)) gpJeu->ajouteObjet(I_GEMME,16*66,16*17,69);
            if (!gpJoueur->getGemme(70)) gpJeu->ajouteObjet(I_GEMME,16*36,16*19,70);
            break;
        case 39 : 
            gpJeu->ajouteEnnemi(11,69*16,51*16);
            gpJeu->ajouteEnnemi(32,113*16,51*16); gpJeu->ajouteEnnemi(32,99*16,30*16);
            gpJeu->ajouteEnnemi(32,99*16,6*16); gpJeu->ajouteEnnemi(32,53*16,30*16);
            gpJeu->ajouteEnnemi(32,21*16,10*16); gpJeu->ajouteEnnemi(32,40*16,11*16);
            gpJeu->ajouteEnnemi(32,30*16,49*16); gpJeu->ajouteEnnemi(32,29*16,28*16);
            gpJeu->ajouteEnnemi(55,38*16,38*16); gpJeu->ajouteEnnemi(55,59*16,46*16);
            gpJeu->ajouteEnnemi(55,96*16,44*16); gpJeu->ajouteEnnemi(55,87*16,23*16);
            gpJeu->ajouteEnnemi(55,113*16,22*16);
            if (!gpJoueur->getGemme(78)) gpJeu->ajouteObjet(I_GEMME,16*5,16*11,78);
            if (!gpJoueur->getGemme(79)) gpJeu->ajouteObjet(I_GEMME,16*62,16*3,79);
            if (!gpJoueur->getGemme(80)) gpJeu->ajouteObjet(I_GEMME,16*65,16*36,80);
            if (!gpJoueur->getGemme(81)) gpJeu->ajouteObjet(I_GEMME,16*114,16*5,81);
            break;
        case 40 :
            gpJeu->ajouteEnnemi(11,40*16,41*16); gpJeu->ajouteEnnemi(11,62*16,26*16);
            gpJeu->ajouteEnnemi(11,69*16,44*16);
            gpJeu->ajouteEnnemi(56,35*16,31*16); gpJeu->ajouteEnnemi(56,60*16,47*16);
            gpJeu->ajouteEnnemi(56,55*16,23*16);
            if (!gpJoueur->getGemme(87)) gpJeu->ajouteObjet(I_GEMME,16*11,16*14,87);
            if (!gpJoueur->getGemme(88)) gpJeu->ajouteObjet(I_GEMME,16*38,16*28,88);
            break;
        case 41 :
            if (!gpJoueur->getCoeur(23)) gpJeu->ajouteObjet(I_QUART_COEUR,105*16,23*16,23);
            if (!gpJoueur->isLapin()) {
                gpJeu->ajouteEnnemi(11,115*16,14*16);
                gpJeu->ajouteEnnemi(32,82*16,61*16); gpJeu->ajouteEnnemi(32,60*16,66*16);
                gpJeu->ajouteEnnemi(32,13*16,37*16);
                gpJeu->ajouteEnnemi(55,63*16,10*16); gpJeu->ajouteEnnemi(55,27*16,7*16);
                gpJeu->ajouteEnnemi(55,120*16,68*16); gpJeu->ajouteEnnemi(55,12*16,69*16);
                gpJeu->ajouteEnnemi(55,123*16,10*16);
                gpJeu->ajouteEnnemi(86,97*16,44*16); gpJeu->ajouteEnnemi(86,51*16,46*16);
                gpJeu->ajouteEnnemi(86,28*16,29*16); gpJeu->ajouteEnnemi(86,130*16,55*16);
            }
            if (!gpJoueur->getGemme(97)) gpJeu->ajouteObjet(I_GEMME,16*85,16*19,97);
            if (!gpJoueur->getGemme(98)) gpJeu->ajouteObjet(I_GEMME,16*10,16*42,98);
            if (!gpJoueur->getGemme(99)) gpJeu->ajouteObjet(I_GEMME,16*14,16*72,99);
            if (!gpJoueur->getGemme(100)) gpJeu->ajouteObjet(I_GEMME,16*33,16*46,100);
            if (!gpJoueur->getGemme(101)) gpJeu->ajouteObjet(I_GEMME,16*55,16*25,101);
            break;
        case 42 :
            if (!gpJoueur->getCoeur(24)) gpJeu->ajouteObjet(I_QUART_COEUR,10*16,71*16,24);
            if (!gpJoueur->getCoeur(25)) gpJeu->ajouteObjet(I_QUART_COEUR,132*16,49*16,25);
            gpJeu->ajouteEnnemi(11,99*16,29*16);
            gpJeu->ajouteEnnemi(15,17*16,41*16); gpJeu->ajouteEnnemi(15,31*16,57*16);
            gpJeu->ajouteEnnemi(15,39*16,21*16); gpJeu->ajouteEnnemi(15,70*16,57*16);
            gpJeu->ajouteEnnemi(15,62*16,12*16); gpJeu->ajouteEnnemi(15,57*16,37*16);
            gpJeu->ajouteEnnemi(55,120*16,67*16); gpJeu->ajouteEnnemi(55,107*16,24*16);
            if (!gpJoueur->getGemme(108)) gpJeu->ajouteObjet(I_GEMME,16*106,16*65,108);
            if (!gpJoueur->getGemme(109)) gpJeu->ajouteObjet(I_GEMME,16*22,16*51,109);
            if (!gpJoueur->getGemme(110)) gpJeu->ajouteObjet(I_GEMME,16*85,16*68,110);
            break;
        case 43 :
            gpJeu->ajouteEnnemi(11,69*16,47*16);
            gpJeu->ajouteEnnemi(56,16*16,20*16); gpJeu->ajouteEnnemi(56,27*16,40*16);
            gpJeu->ajouteEnnemi(56,45*16,31*16); gpJeu->ajouteEnnemi(56,65*16,55*16);
            if (!gpJoueur->getGemme(117)) gpJeu->ajouteObjet(I_GEMME,16*70,16*61,117);
            if (!gpJoueur->getGemme(118)) gpJeu->ajouteObjet(I_GEMME,16*9,16*20,118);
            break;
        case 44 :
            gpJeu->ajouteEnnemi(11,46*16,17*16);
            gpJeu->ajouteEnnemi(32,51*16,20*16); gpJeu->ajouteEnnemi(32,36*16,40*16);
            gpJeu->ajouteEnnemi(55,19*16,61*16);
            if (!gpJoueur->getGemme(125)) gpJeu->ajouteObjet(I_GEMME,16*57,16*69,125);
            if (!gpJoueur->getGemme(126)) gpJeu->ajouteObjet(I_GEMME,16*7,16*61,126);
            if (!gpJoueur->getGemme(127)) gpJeu->ajouteObjet(I_GEMME,16*15,16*69,127);
            break;
        case 45 :
            gpJeu->ajoutePnj(63,9*16+8,8*16+8,297);
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)<2) 
                gpJeu->getPnj()->getSuivant()->setAnimmax(0);
            gpJeu->ajouteEnnemi(11,121*16,54*16);
            gpJeu->ajouteEnnemi(15,53*16,35*16); gpJeu->ajouteEnnemi(15,26*16,20*16);
            gpJeu->ajouteEnnemi(15,88*16,21*16); gpJeu->ajouteEnnemi(15,92*16,40*16);
            gpJeu->ajouteEnnemi(15,111*16,45*16); gpJeu->ajouteEnnemi(15,59*16,21*16);
            gpJeu->ajouteEnnemi(44,32*16,28*16); gpJeu->ajouteEnnemi(44,73*16,31*16);
            gpJeu->ajouteEnnemi(44,121*16,48*16); gpJeu->ajouteEnnemi(44,22*16,36*16);
            if (!gpJoueur->getGemme(136)) gpJeu->ajouteObjet(I_GEMME,16*130,16*47,136);
            if (!gpJoueur->getGemme(137)) gpJeu->ajouteObjet(I_GEMME,16*104,16*41,137);
            if (!gpJoueur->getGemme(138)) gpJeu->ajouteObjet(I_GEMME,16*82,16*24,138);
            if (!gpJoueur->getGemme(139)) gpJeu->ajouteObjet(I_GEMME,16*13,16*28,139);
            if (!gpJoueur->getGemme(140)) gpJeu->ajouteObjet(I_GEMME,16*26,16*27,140);
            break;
        case 46 :
            //caisses
            gpJeu->ajouteCaisse(2,70*16,52*16);
            //ennemis
            gpJeu->ajouteEnnemi(1,169*16+8,21*16); gpJeu->ajouteEnnemi(1,209*16,5*16);
            gpJeu->ajouteEnnemi(1,26*16,4*16); gpJeu->ajouteEnnemi(1,33*16,4*16);
            gpJeu->ajouteEnnemi(1,73*16,21*16); gpJeu->ajouteEnnemi(1,131*16,5*16);
            gpJeu->ajouteEnnemi(1,200*16,36*16); gpJeu->ajouteEnnemi(1,277*16,23*16);
            gpJeu->ajouteEnnemi(1,287*16,34*16); gpJeu->ajouteEnnemi(1,249*16,35*16);
            gpJeu->ajouteEnnemi(1,270*16,8*16);
            gpJeu->ajouteEnnemi(4,129*16+8,56*16); gpJeu->ajouteEnnemi(4,29*16,52*16);
            gpJeu->ajouteEnnemi(4,106*16,51*16); gpJeu->ajouteEnnemi(4,113*16,51*16);
            gpJeu->ajouteEnnemi(4,184*16+8,47*16-1); gpJeu->ajouteEnnemi(4,315*16,7*16);
            gpJeu->ajouteEnnemi(4,227*16,22*16);
            gpJeu->ajouteEnnemi(18,287*16,3*16); gpJeu->ajouteEnnemi(18,287*16,11*16);
            gpJeu->ajouteEnnemi(18,128*16,27*16); gpJeu->ajouteEnnemi(18,70*16,35*16+8);
            gpJeu->ajouteEnnemi(18,125*16,48*16); gpJeu->ajouteEnnemi(18,134*16,48*16);
            gpJeu->ajouteEnnemi(18,190*16,5*16+8); gpJeu->ajouteEnnemi(18,265*16,48*16);
            gpJeu->ajouteEnnemi(18,294*16,48*16); gpJeu->ajouteEnnemi(18,310*16,20*16+8);
            gpJeu->ajouteEnnemi(18,278*16,43*16); gpJeu->ajouteEnnemi(18,268*16,19*16+8);
            gpJeu->ajouteEnnemi(53,67*16,51*16); gpJeu->ajouteEnnemi(53,70*16,54*16);
            gpJeu->ajouteEnnemi(53,72*16,50*16); gpJeu->ajouteEnnemi(53,90*16,36*16);
            gpJeu->ajouteEnnemi(53,124*16,19*16); gpJeu->ajouteEnnemi(53,117*16,36*16);
            gpJeu->ajouteEnnemi(53,106*16,30*16); gpJeu->ajouteEnnemi(53,226*16,51*16);
            gpJeu->ajouteEnnemi(53,45*16,13*16); gpJeu->ajouteEnnemi(53,90*16,22*16);
            gpJeu->ajouteEnnemi(53,136*16,32*16); gpJeu->ajouteEnnemi(53,163*16,4*16);
            gpJeu->ajouteEnnemi(53,176*16,4*16); gpJeu->ajouteEnnemi(53,185*16,33*16);
            gpJeu->ajouteEnnemi(53,205*16,20*16); gpJeu->ajouteEnnemi(53,197*16,24*16);
            gpJeu->ajouteEnnemi(53,306*16,23*16); gpJeu->ajouteEnnemi(53,313*16,23*16);
            gpJeu->ajouteEnnemi(53,293*16,26*16);
            //pièges
            gpJeu->ajouteEnnemi(17,34*16,49*16); gpJeu->ajouteEnnemi(17,38*16,49*16);
            gpJeu->ajouteEnnemi(17,42*16,49*16); gpJeu->ajouteEnnemi(17,46*16,49*16);
            gpJeu->ajouteEnnemi(17,189*16,54*16); gpJeu->ajouteEnnemi(17,190*16,53*16);
            gpJeu->ajouteEnnemi(17,191*16,52*16); gpJeu->ajouteEnnemi(17,200*16,54*16);
            gpJeu->ajouteEnnemi(17,201*16,53*16); gpJeu->ajouteEnnemi(17,202*16,52*16);
            gpJeu->ajouteEnnemi(17,195*16,51*16); gpJeu->ajouteEnnemi(17,196*16,51*16);
            gpJeu->ajouteEnnemi(17,197*16,51*16); gpJeu->ajouteEnnemi(17,305*16,32*16);
            gpJeu->ajouteEnnemi(17,308*16,32*16); gpJeu->ajouteEnnemi(17,305*16,51*16);
            gpJeu->ajouteEnnemi(17,50*16,7*16); gpJeu->ajouteEnnemi(17,51*16,7*16);
            gpJeu->ajouteEnnemi(17,52*16,7*16); gpJeu->ajouteEnnemi(17,53*16,7*16);
            gpJeu->ajouteEnnemi(61,6*16,25*16); gpJeu->ajouteEnnemi(61,166*16,40*16);
            gpJeu->ajouteEnnemi(61,106*16,2*16); gpJeu->ajouteEnnemi(61,48*16,18*16);
            //mini boss
            if (!gpJoueur->getCoffre(0,22)) gpJeu->ajouteEnnemi(91,9*16+5,38*16);
            //boss
            if(gpJoueur->getCoeur(0)==0) gpJeu->ajouteEnnemi(92,349*16-52,2*16-8);
            //médaillon
            if(!gpJoueur->hasMedaillon(0))gpJeu->ajouteObjet(I_PENDENTIF_V,16*249+8,16*5,0,1);
            //objets
            gpJeu->ajouteObjet(4,16*4,16*32-4,0,1); gpJeu->ajouteObjet(4,16*15,16*32-4,0,1);
            gpJeu->ajouteObjet(4,16*4,16*42-4,0,1); gpJeu->ajouteObjet(4,16*15,16*42-4,0,1);
            gpJeu->ajouteObjet(4,16*24,16*34-4,0,1); gpJeu->ajouteObjet(4,16*24,16*40-4,0,1);
            gpJeu->ajouteObjet(4,16*44,16*2-4,0,1); gpJeu->ajouteObjet(4,16*46,16*2-4,0,1);
            gpJeu->ajouteObjet(4,16*120,16*17-4,0,1); gpJeu->ajouteObjet(4,16*121,16*17-4,0,1);
            gpJeu->ajouteObjet(4,16*125,16*34-4,0,1); gpJeu->ajouteObjet(4,16*125,16*35-4,0,1);
            gpJeu->ajouteObjet(4,16*165,16*55-4,0,1); gpJeu->ajouteObjet(4,16*166,16*55-4,0,1);
            gpJeu->ajouteObjet(4,16*201,16*19-4,0,1); gpJeu->ajouteObjet(4,16*202,16*19-4,0,1);
            gpJeu->ajouteObjet(4,16*206,16*47-4,0,1); gpJeu->ajouteObjet(4,16*244,16*40-4,0,1);
            gpJeu->ajouteObjet(4,16*253,16*19-4,0,1);
            gpJeu->ajouteObjet(4,16*295,16*29-4,0,1); gpJeu->ajouteObjet(4,16*315,16*32-4,0,1);
            gpJeu->ajouteObjet(4,16*348,16*7-4,0,1); gpJeu->ajouteObjet(4,16*351,16*7-4,0,1);
            gpJeu->ajouteObjet(1,16*47,16*2,0,1);
            gpJeu->ajouteObjet(1,16*122,16*17,0,1); gpJeu->ajouteObjet(1,16*167,16*55,0,1);
            gpJeu->ajouteObjet(1,16*315,16*34,0,1); gpJeu->ajouteObjet(1,16*295,16*31,0,1);
            gpJeu->ajouteObjet(1,16*246,16*40,0,1);
            gpJeu->ajouteObjet(5,16*246,16*19,0,1);
            //gemme
            if (!gpJoueur->getGemme(185)) gpJeu->ajouteObjet(I_GEMME,16*280,16*19,185,1);
            break;
        case 47 :
            //caisses
            gpJeu->ajouteCaisse(3,208*16,36*16,3); gpJeu->ajouteCaisse(3,212*16,38*16,2);
            gpJeu->ajouteCaisse(3,209*16,39*16,1); gpJeu->ajouteCaisse(3,300*16,75*16,1,0);
            gpJeu->ajouteCaisse(3,306*16,82*16,1); gpJeu->ajouteCaisse(3,315*16,75*16,1);
            gpJeu->ajouteCaisse(3,271*16,80*16,3); gpJeu->ajouteCaisse(3,268*16,81*16,4);
            gpJeu->ajouteCaisse(3,270*16,81*16,3); gpJeu->ajouteCaisse(3,272*16,82*16,2);
            gpJeu->ajouteCaisse(3,270*16,83*16,2); gpJeu->ajouteCaisse(3,271*16,83*16,2);
            gpJeu->ajouteCaisse(3,268*16,84*16,1); gpJeu->ajouteCaisse(3,272*16,84*16,1);
            gpJeu->ajouteCaisse(3,172*16,6*16,1); gpJeu->ajouteCaisse(3,172*16,7*16,1);
            gpJeu->ajouteCaisse(3,172*16,8*16,1); gpJeu->ajouteCaisse(3,260*16,37*16,1);
            gpJeu->ajouteCaisse(3,261*16,38*16,1); gpJeu->ajouteCaisse(3,260*16,39*16,1);
            gpJeu->ajouteCaisse(3,329*16,5*16,1); gpJeu->ajouteCaisse(3,330*16,5*16,1);
            gpJeu->ajouteCaisse(3,328*16,6*16,1); gpJeu->ajouteCaisse(3,331*16,6*16,1);
            gpJeu->ajouteCaisse(3,328*16,7*16,1); gpJeu->ajouteCaisse(3,331*16,7*16,1);
            gpJeu->ajouteCaisse(3,329*16,8*16,1); gpJeu->ajouteCaisse(3,330*16,8*16,1);
            gpJeu->ajouteCaisse(3,329*16,35*16,2); gpJeu->ajouteCaisse(3,329*16,36*16,2);
            gpJeu->ajouteCaisse(3,330*16,36*16,3); gpJeu->ajouteCaisse(3,331*16,36*16,2);
            gpJeu->ajouteCaisse(3,329*16,37*16,1); gpJeu->ajouteCaisse(3,330*16,38*16,1);
            gpJeu->ajouteCaisse(3,332*16,38*16,2); gpJeu->ajouteCaisse(3,326*16,63*16,9);
            gpJeu->ajouteCaisse(3,328*16,63*16,9); gpJeu->ajouteCaisse(3,330*16,63*16,9);
            gpJeu->ajouteCaisse(3,332*16,63*16,9); gpJeu->ajouteCaisse(3,334*16,63*16,9);
            //switchs
            gpJeu->ajouteEnnemi(20,269*16,67*16); setValeur(269*16,67*16,3087,2);
            gpJeu->ajouteEnnemi(20,337*16,64*16); setValeur(337*16,64*16,3087,2);
            gpJeu->ajouteEnnemi(20,260*16,34*16); setValeur(260*16,34*16,3087,2);
            gpJeu->ajouteEnnemi(20,329*16,20*16); setValeur(329*16,20*16,3087,2);
            gpJeu->ajouteEnnemi(20,168*16,4*16); setValeur(168*16,4*16,3086,2);
            gpJeu->ajouteEnnemi(20,166*16,19*16); setValeur(166*16,19*16,3086,2);
            //ennemis
            gpJeu->ajouteEnnemi(9,250*16,84*16); gpJeu->ajouteEnnemi(9,311*16,66*16);
            gpJeu->ajouteEnnemi(10,279*16,14*16); gpJeu->ajouteEnnemi(10,255*16,41*16);
            gpJeu->ajouteEnnemi(10,264*16,41*16); gpJeu->ajouteEnnemi(10,354*16,74*16);
            gpJeu->ajouteEnnemi(10,139*16+8,78*16);
            gpJeu->ajouteEnnemi(22,185*16,18*16); gpJeu->ajouteEnnemi(22,245*16,7*16);
            gpJeu->ajouteEnnemi(22,252*16,16*16); gpJeu->ajouteEnnemi(22,245*16,23*16);
            gpJeu->ajouteEnnemi(22,348*16,6*16); gpJeu->ajouteEnnemi(22,270*16,52*16);
            gpJeu->ajouteEnnemi(22,266*16,69*16); gpJeu->ajouteEnnemi(22,272*16,64*16);
            gpJeu->ajouteEnnemi(22,274*16,70*16); gpJeu->ajouteEnnemi(22,349*16+8,67*16);
            gpJeu->ajouteEnnemi(22,349*16+8,78*16);
            gpJeu->ajouteEnnemi(23,209*16+3,52*16); gpJeu->ajouteEnnemi(23,267*16+3,5*16);
            gpJeu->ajouteEnnemi(23,291*16+3,5*16); gpJeu->ajouteEnnemi(23,313*16+3,37*16);
            gpJeu->ajouteEnnemi(23,291*16+3,44*16); gpJeu->ajouteEnnemi(23,286*16+3,65*16);
            gpJeu->ajouteEnnemi(23,291*16+3,84*16); gpJeu->ajouteEnnemi(23,129*16+3,82*16);
            gpJeu->ajouteEnnemi(23,149*16+3,82*16); gpJeu->ajouteEnnemi(23,109*16+3,38*16);
            gpJeu->ajouteEnnemi(27,309*16+8,4*16); gpJeu->ajouteEnnemi(27,247*16,51*16);
            gpJeu->ajouteEnnemi(27,254*16,51*16); gpJeu->ajouteEnnemi(27,329*16+8,82*16);
            //mini boss
            if (!gpJoueur->getCoffre(1,15)) gpJeu->ajouteEnnemi(93,326*16,54*16+8);
            //pnj
            if (gpJoueur->getCoffre(1,15)) gpJeu->ajoutePnj(71,326*16,54*16+8,952);
            //boss
            if(gpJoueur->getCoeur(1)==0) gpJeu->ajouteEnnemi(94,349*16,34*16);
            //médaillon
            if(!gpJoueur->hasMedaillon(1))gpJeu->ajouteObjet(I_PENDENTIF_B,16*349+8,16*20,0,1);
            //objets
            gpJeu->ajouteObjet(1,16*288,16*4,0,1); gpJeu->ajouteObjet(1,16*301,16*55,0,1);
            gpJeu->ajouteObjet(4,16*204,16*55-4,0,1); gpJeu->ajouteObjet(4,16*244,16*78-4,0,1);
            gpJeu->ajouteObjet(4,16*264,16*71-4,0,1); gpJeu->ajouteObjet(4,16*286,16*4-4,0,1);
            gpJeu->ajouteObjet(4,16*288,16*53-4,0,1); gpJeu->ajouteObjet(4,16*309,16*40-4,0,1);
            gpJeu->ajouteObjet(4,16*336,16*47-4,0,1); gpJeu->ajouteObjet(4,16*337,16*62-4,0,1);
            gpJeu->ajouteObjet(4,16*324,16*78-4,0,1); gpJeu->ajouteObjet(4,16*345,16*55-4,0,1);
            gpJeu->ajouteObjet(5,16*204,16*49,0,1); gpJeu->ajouteObjet(5,16*323,16*47,0,1);
            gpJeu->ajouteObjet(5,16*354,16*55,0,1);
            //gemme
            if (!gpJoueur->getGemme(186)) gpJeu->ajouteObjet(I_GEMME,16*296,16*55,186,1);
            break;
        case 48 :
            //pièges
            gpJeu->ajouteEnnemi(36,275*16,49*16); setValeur(275*16,49*16,3254,2);
            gpJeu->ajouteEnnemi(36,275*16,55*16); setValeur(275*16,55*16,3254,2);
            gpJeu->ajouteEnnemi(36,164*16,70*16); setValeur(164*16,70*16,3254,2);
            gpJeu->ajouteEnnemi(36,90*16,67*16); setValeur(90*16,67*16,3252,2);
            gpJeu->ajouteEnnemi(36,117*16,4*16); setValeur(117*16,4*16,3252,2);
            gpJeu->ajouteEnnemi(36,64*16,32*16); setValeur(64*16,32*16,3252,2);
            gpJeu->ajouteEnnemi(36,75*16,32*16); setValeur(75*16,32*16,3252,2);
            gpJeu->ajouteEnnemi(36,18*16,21*16); setValeur(18*16,21*16,1006,2);
            //big 6
            if (!gpJoueur->getCoffre(2,18)) gpJeu->ajouteEnnemi(19,68*16,64*16);
            if (!gpJoueur->getCoffre(2,16)) gpJeu->ajouteEnnemi(24,29*16,34*16);
            if (!gpJoueur->getCoffre(2,17)) gpJeu->ajouteEnnemi(28,209*16,66*16-6);
            if (!gpJoueur->getCoffre(2,14)) gpJeu->ajouteEnnemi(35,189*16,3*16);
            if (!gpJoueur->getCoffre(2,19)) gpJeu->ajouteEnnemi(40,249*16-11,33*16);
            if (!gpJoueur->getCoffre(2,15)) gpJeu->ajouteEnnemi(43,49*16,3*16);
            //ennemis
            gpJeu->ajouteEnnemi(5,49*16,66*16); gpJeu->ajouteEnnemi(5,29*16+8,51*16);
            gpJeu->ajouteEnnemi(5,249*16+8,51*16); gpJeu->ajouteEnnemi(5,263*16,17*16);
            gpJeu->ajouteEnnemi(5,255*16+8,26*16); gpJeu->ajouteEnnemi(5,269*16+8,36*16);
            gpJeu->ajouteEnnemi(5,89*16+8,52*16-5); gpJeu->ajouteEnnemi(5,189*16,65*16-5);
            gpJeu->ajouteEnnemi(5,189*16,69*16-5); gpJeu->ajouteEnnemi(5,229*16+8,6*16);
            gpJeu->ajouteEnnemi(5,89*16+8,6*16); gpJeu->ajouteEnnemi(5,69*16+8,6*16);
            gpJeu->ajouteEnnemi(5,169*16+8,6*16); gpJeu->ajouteEnnemi(5,149*16+8,21*16);
            gpJeu->ajouteEnnemi(5,129*16+8,51*16);
            gpJeu->ajouteEnnemi(18,42*16,63*16); gpJeu->ajouteEnnemi(18,44*16,71*16);
            gpJeu->ajouteEnnemi(18,124*16,63*16); gpJeu->ajouteEnnemi(18,259*16,48*16);
            gpJeu->ajouteEnnemi(18,270*16,21*16); gpJeu->ajouteEnnemi(18,250*16,23*16);
            gpJeu->ajouteEnnemi(18,233*16,63*16); gpJeu->ajouteEnnemi(18,269*16,72*16);
            gpJeu->ajouteEnnemi(18,144*16,64*16); gpJeu->ajouteEnnemi(18,155*16,64*16);
            gpJeu->ajouteEnnemi(18,144*16,69*16); gpJeu->ajouteEnnemi(18,155*16,69*16);
            gpJeu->ajouteEnnemi(18,53*16,48*16); gpJeu->ajouteEnnemi(18,264*16,11*16);
            gpJeu->ajouteEnnemi(18,108*16,23*16); gpJeu->ajouteEnnemi(18,111*16,23*16);
            gpJeu->ajouteEnnemi(18,146*16,12*16); gpJeu->ajouteEnnemi(18,14*16,12*16);
            gpJeu->ajouteEnnemi(25,109*16+2,66*16); gpJeu->ajouteEnnemi(25,29*16+2,66*16);
            gpJeu->ajouteEnnemi(25,248*16+2,66*16); gpJeu->ajouteEnnemi(25,69*16+2,49*16);
            gpJeu->ajouteEnnemi(25,249*16+2,5*16); gpJeu->ajouteEnnemi(25,91*16+2,21*16);
            gpJeu->ajouteEnnemi(25,149*16+2,51*16); gpJeu->ajouteEnnemi(25,49*16+2,36*16);
            gpJeu->ajouteEnnemi(25,69*16+2,21*16); gpJeu->ajouteEnnemi(25,106*16+2,36*16);
            gpJeu->ajouteEnnemi(25,169*16+2,21*16);
            gpJeu->ajouteEnnemi(53,13*16,69*16); gpJeu->ajouteEnnemi(53,5*16,63*16);
            gpJeu->ajouteEnnemi(53,125*16,5*16); gpJeu->ajouteEnnemi(53,133*16,10*16);
            gpJeu->ajouteEnnemi(53,49*16+8,22*16); gpJeu->ajouteEnnemi(53,32*16,7*16);
            gpJeu->ajouteEnnemi(53,197*16,26*16); gpJeu->ajouteEnnemi(53,198*16,47*16);
            gpJeu->ajouteEnnemi(53,219*16,27*16); gpJeu->ajouteEnnemi(53,221*16,47*16);
            //mini boss
            if (!gpJoueur->getCoffre(2,61)) {
                gpJeu->ajouteEnnemi(95,132*16+6,32*16+8-2);
                gpJeu->ajouteEnnemi(96,124*16,35*16);
                gpJeu->ajouteEnnemi(96,129*16,35*16);
                gpJeu->ajouteEnnemi(96,135*16,35*16);
                gpJeu->ajouteEnnemi(96,124*16,39*16);
                gpJeu->ajouteEnnemi(96,135*16,39*16);
            }
            //boss
            if(gpJoueur->getCoeur(2)==0) gpJeu->ajouteEnnemi(97,8*16+6,32*16);
            //médaillon
            if(!gpJoueur->hasMedaillon(2))gpJeu->ajouteObjet(I_PENDENTIF_R,16*289+8,16*21,0,1);
            //objets
            gpJeu->ajouteObjet(1,16*15,16*72,0,1); gpJeu->ajouteObjet(1,16*124,16*27,0,1);
            gpJeu->ajouteObjet(1,16*135,16*49,0,1); gpJeu->ajouteObjet(1,16*233,16*17,0,1);
            gpJeu->ajouteObjet(3,16*289,16*6,0,1);
            gpJeu->ajouteObjet(4,16*27,16*70-4,0,1); gpJeu->ajouteObjet(4,16*15,16*62-4,0,1);
            gpJeu->ajouteObjet(4,16*6,16*55-4,0,1); gpJeu->ajouteObjet(4,16*13,16*55-4,0,1);
            gpJeu->ajouteObjet(4,16*26,16*6-4,0,1); gpJeu->ajouteObjet(4,16*75,16*57-4,0,1);
            gpJeu->ajouteObjet(4,16*122,16*25-4,0,1); gpJeu->ajouteObjet(4,16*137,16*25-4,0,1);
            gpJeu->ajouteObjet(4,16*124,16*49-4,0,1); gpJeu->ajouteObjet(4,16*155,16*49-4,0,1);
            gpJeu->ajouteObjet(4,16*264,16*25-4,0,1); gpJeu->ajouteObjet(4,16*264,16*49-4,0,1);
            gpJeu->ajouteObjet(5,16*29,16*70,0,1); gpJeu->ajouteObjet(5,16*26,16*8,0,1);
            gpJeu->ajouteObjet(5,16*175,16*10,0,1); gpJeu->ajouteObjet(5,16*264,16*55,0,1);
            gpJeu->ajouteObjet(7,16*191,16*55-4,0,1); gpJeu->ajouteObjet(7,16*216,16*19-4,0,1);
            gpJeu->ajouteObjet(7,16*215,16*57-4,0,1); gpJeu->ajouteObjet(7,16*233,16*57-4,0,1);
            gpJeu->ajouteObjet(7,16*254,16*70-4,0,1);
            //gemme
            if (!gpJoueur->getGemme(187)) gpJeu->ajouteObjet(I_GEMME,16*290,16*6,187,1);
            break;
        case 49 :
            //ennemis
            gpJeu->ajouteEnnemi(26,101*16,21*16); gpJeu->ajouteEnnemi(26,95*16,31*16);
            gpJeu->ajouteEnnemi(26,58*16,61*16); gpJeu->ajouteEnnemi(26,23*16,64*16);
            gpJeu->ajouteEnnemi(26,47*16,8*16); gpJeu->ajouteEnnemi(26,24*16,0);
            gpJeu->ajouteEnnemi(26,58*16,15*16); gpJeu->ajouteEnnemi(26,225*16,80*16);
            gpJeu->ajouteEnnemi(26,231*16,84*16); gpJeu->ajouteEnnemi(26,155*16,72*16);
            gpJeu->ajouteEnnemi(26,155*16,76*16);
            gpJeu->ajouteEnnemi(32,134*16,22*16); gpJeu->ajouteEnnemi(32,65*16,50*16);
            gpJeu->ajouteEnnemi(32,110*16,52*16); gpJeu->ajouteEnnemi(32,90*16,67*16);
            gpJeu->ajouteEnnemi(32,89*16,82*16); gpJeu->ajouteEnnemi(32,49*16,52*16);
            gpJeu->ajouteEnnemi(32,29*16+8,52*16); gpJeu->ajouteEnnemi(32,49*16,36*16);
            gpJeu->ajouteEnnemi(32,67*16,7*16); gpJeu->ajouteEnnemi(32,70*16,4*16);
            gpJeu->ajouteEnnemi(32,72*16,10*16); gpJeu->ajouteEnnemi(32,126*16,38*16);
            gpJeu->ajouteEnnemi(32,229*16,67*16); gpJeu->ajouteEnnemi(32,166*16,84*16);
            gpJeu->ajouteEnnemi(32,173*16,82*16); gpJeu->ajouteEnnemi(32,223*16,10*16);
            gpJeu->ajouteEnnemi(86,109*16,15*16); gpJeu->ajouteEnnemi(86,116*16,8*16);
            gpJeu->ajouteEnnemi(86,120*16,22*16); gpJeu->ajouteEnnemi(86,105*16,34*16);
            gpJeu->ajouteEnnemi(86,114*16,40*16); gpJeu->ajouteEnnemi(86,71*16,43*16);
            gpJeu->ajouteEnnemi(86,108*16,76*16); gpJeu->ajouteEnnemi(86,116*16,85*16);
            gpJeu->ajouteEnnemi(86,120*16,64*16); gpJeu->ajouteEnnemi(86,132*16,75*16);
            gpJeu->ajouteEnnemi(86,134*16,55*16); gpJeu->ajouteEnnemi(86,69*16,82*16);
            gpJeu->ajouteEnnemi(86,35*16,71*16); gpJeu->ajouteEnnemi(86,25*16,34*16);
            gpJeu->ajouteEnnemi(86,25*16,21*16); gpJeu->ajouteEnnemi(86,35*16,11*16);
            gpJeu->ajouteEnnemi(86,42*16,23*16); gpJeu->ajouteEnnemi(86,226*16,37*16);
            gpJeu->ajouteEnnemi(86,238*16,36*16); gpJeu->ajouteEnnemi(86,252*16,40*16);
            gpJeu->ajouteEnnemi(86,223*16,17*16); gpJeu->ajouteEnnemi(86,229*16,7*16);
            gpJeu->ajouteEnnemi(86,233*16,20*16); gpJeu->ajouteEnnemi(86,246*16,63*16);
            gpJeu->ajouteEnnemi(86,231*16,51*16); gpJeu->ajouteEnnemi(86,205*16,78*16);
            gpJeu->ajouteEnnemi(86,150*16,57*16); gpJeu->ajouteEnnemi(86,160*16,65*16);
            gpJeu->ajouteEnnemi(86,171*16,57*16); gpJeu->ajouteEnnemi(86,143*16,22*16);
            gpJeu->ajouteEnnemi(86,144*16,39*16); gpJeu->ajouteEnnemi(86,155*16,31*16);
            gpJeu->ajouteEnnemi(86,163*16,18*16); gpJeu->ajouteEnnemi(86,167*16,40*16);
            gpJeu->ajouteEnnemi(86,175*16,22*16);
            //mini boss
            if (!gpJoueur->getCoffre(3,27)) gpJeu->ajouteEnnemi(98,89*16,21*16+8);
            //boss
            if(gpJoueur->getCoeur(3)==0) {
                gpJeu->ajouteEnnemi(99,198*16-2,32*16);
                gpJeu->ajouteEnnemi(100,183*16-2,20*16);
                gpJeu->ajouteEnnemi(100,185*16-2,40*16);
                gpJeu->ajouteEnnemi(100,192*16-2,30*16);
                gpJeu->ajouteEnnemi(100,205*16-2,34*16);
                gpJeu->ajouteEnnemi(100,207*16-2,24*16);
            }
            //sage
            if(!gpJoueur->getCoffre(3,29)) gpJeu->ajoutePnj(62,199*16+8,3*16,957);
            //objets
            gpJeu->ajouteObjet(1,16*222,16*14,0,1);
            gpJeu->ajouteObjet(3,16*32,16*73,0,1); gpJeu->ajouteObjet(3,16*77,16*40,0,1);
            gpJeu->ajouteObjet(4,16*32,16*25-4,0,1); gpJeu->ajouteObjet(4,16*29,16*72-4,0,1);
            gpJeu->ajouteObjet(4,16*33,16*66-4,0,1); gpJeu->ajouteObjet(4,16*62,16*49-4,0,1);
            gpJeu->ajouteObjet(4,16*76,16*62-4,0,1); gpJeu->ajouteObjet(4,16*87,16*50-4,0,1);
            gpJeu->ajouteObjet(4,16*104,16*12-4,0,1);
            gpJeu->ajouteObjet(4,16*112,16*24-4,0,1); gpJeu->ajouteObjet(4,16*121,16*79-4,0,1);
            gpJeu->ajouteObjet(4,16*146,16*4-4,0,1); gpJeu->ajouteObjet(4,16*153,16*38-4,0,1);
            gpJeu->ajouteObjet(4,16*175,16*39-4,0,1); gpJeu->ajouteObjet(4,16*145,16*85-4,0,1);
            gpJeu->ajouteObjet(4,16*172,16*77-4,0,1); gpJeu->ajouteObjet(4,16*187,16*53-4,0,1);
            gpJeu->ajouteObjet(4,16*212,16*53-4,0,1); gpJeu->ajouteObjet(4,16*224,16*2-4,0,1);
            gpJeu->ajouteObjet(4,16*237,16*27-4,0,1); gpJeu->ajouteObjet(4,16*224,16*41-4,0,1);
            gpJeu->ajouteObjet(4,16*227,16*55-4,0,1);
            gpJeu->ajouteObjet(5,16*75,16*62,0,1); gpJeu->ajouteObjet(5,16*124,16*70,0,1);
            gpJeu->ajouteObjet(5,16*145,16*25,0,1); gpJeu->ajouteObjet(5,16*162,16*85,0,1);
            gpJeu->ajouteObjet(5,16*172,16*53,0,1); gpJeu->ajouteObjet(5,16*192,16*69,0,1);
            gpJeu->ajouteObjet(5,16*92,16*32,0,1); gpJeu->ajouteObjet(5,16*104,16*13,0,1);
            gpJeu->ajouteObjet(7,16*33,16*72-4,0,1); gpJeu->ajouteObjet(7,16*95,16*41-4,0,1);
            gpJeu->ajouteObjet(7,16*125,16*21-4,0,1); gpJeu->ajouteObjet(7,16*222,16*13-4,0,1);
            //gemme
            if (!gpJoueur->getGemme(188)) gpJeu->ajouteObjet(I_GEMME,16*106,16*74,188,1);
            break;
        case 50 :
            //pièges
            gpJeu->ajoutePiege(51,242*16,47*16); gpJeu->ajoutePiege(51,182*16,77*16);
            gpJeu->ajoutePiege(51,182*16,2*16); gpJeu->ajoutePiege(51,282*16,77*16);
            gpJeu->ajoutePiege(51,282*16,2*16); gpJeu->ajoutePiege(51,62*16,62*16);
            //ennemis
            gpJeu->ajouteEnnemi(37,112*16,48*16); gpJeu->ajouteEnnemi(37,249*16,96*16);
            gpJeu->ajouteEnnemi(37,125*16,20*16); gpJeu->ajouteEnnemi(37,285*16,66*16);
            gpJeu->ajouteEnnemi(37,294*16,68*16);
            gpJeu->ajouteEnnemi(1,106*16,50*16); gpJeu->ajouteEnnemi(1,114*16,55*16);
            gpJeu->ajouteEnnemi(1,107*16,84*16); gpJeu->ajouteEnnemi(1,112*16,79*16);
            gpJeu->ajouteEnnemi(1,226*16,96*16); gpJeu->ajouteEnnemi(1,233*16,97*16);
            gpJeu->ajouteEnnemi(1,208*16,66*16); gpJeu->ajouteEnnemi(1,109*16,20*16);
            gpJeu->ajouteEnnemi(1,152*16,23*16); gpJeu->ajouteEnnemi(1,144*16,21*16);
            gpJeu->ajouteEnnemi(1,25*16,50*16); gpJeu->ajouteEnnemi(1,33*16,53*16);
            gpJeu->ajouteEnnemi(1,267*16,36*16); gpJeu->ajouteEnnemi(1,273*16,38*16);
            gpJeu->ajouteEnnemi(1,305*16,49*16); gpJeu->ajouteEnnemi(1,310*16,53*16);
            gpJeu->ajouteEnnemi(1,314*16,50*16);
            gpJeu->ajouteEnnemi(26,146*16,66*16); gpJeu->ajouteEnnemi(26,153*16,66*16);
            gpJeu->ajouteEnnemi(26,86*16,65*16); gpJeu->ajouteEnnemi(26,90*16,71*16);
            gpJeu->ajouteEnnemi(26,93*16,64*16); gpJeu->ajouteEnnemi(26,85*16,53*16);
            gpJeu->ajouteEnnemi(26,266*16,63*16); gpJeu->ajouteEnnemi(26,273*16,69*16);
            gpJeu->ajouteEnnemi(26,282*16,48*16); gpJeu->ajouteEnnemi(26,283*16,56*16);
            gpJeu->ajouteEnnemi(26,265*16,101*16); gpJeu->ajouteEnnemi(26,266*16,93*16);
            gpJeu->ajouteEnnemi(26,273*16,97*16); gpJeu->ajouteEnnemi(26,243*16,93*16);
            gpJeu->ajouteEnnemi(26,253*16,101*16); gpJeu->ajouteEnnemi(26,206*16,71*16);
            gpJeu->ajouteEnnemi(26,194*16,63*16); gpJeu->ajouteEnnemi(26,196*16,71*16);
            gpJeu->ajouteEnnemi(26,185*16,39*16); gpJeu->ajouteEnnemi(26,194*16,34*16);
            gpJeu->ajouteEnnemi(26,224*16,11*16); gpJeu->ajouteEnnemi(26,95*16,16*16);
            gpJeu->ajouteEnnemi(26,145*16,42*16); gpJeu->ajouteEnnemi(26,156*16,35*16);
            gpJeu->ajouteEnnemi(26,141*16,49*16); gpJeu->ajouteEnnemi(26,153*16,58*16);
            gpJeu->ajouteEnnemi(26,26*16,42*16); gpJeu->ajouteEnnemi(26,31*16,31*16);
            gpJeu->ajouteEnnemi(26,35*16,39*16); gpJeu->ajouteEnnemi(26,45*16,63*16);
            gpJeu->ajouteEnnemi(26,46*16,71*16); gpJeu->ajouteEnnemi(26,53*16,63*16);
            gpJeu->ajouteEnnemi(26,64*16,33*16); gpJeu->ajouteEnnemi(26,71*16,31*16);
            gpJeu->ajouteEnnemi(26,75*16,38*16); gpJeu->ajouteEnnemi(26,273*16,26*16);
            gpJeu->ajouteEnnemi(26,305*16,69*16); gpJeu->ajouteEnnemi(26,314*16,65*16);
            gpJeu->ajouteEnnemi(56,126*16,80*16); gpJeu->ajouteEnnemi(56,133*16,80*16);
            gpJeu->ajouteEnnemi(56,129*16+8,71*16); gpJeu->ajouteEnnemi(56,91*16,49*16);
            gpJeu->ajouteEnnemi(56,166*16,82*16); gpJeu->ajouteEnnemi(56,246*16,67*16);
            gpJeu->ajouteEnnemi(56,253*16,67*16); gpJeu->ajouteEnnemi(56,273*16,53*16);
            gpJeu->ajouteEnnemi(56,289*16,52*16); gpJeu->ajouteEnnemi(56,189*16,85*16);
            gpJeu->ajouteEnnemi(56,195*16,95*16); gpJeu->ajouteEnnemi(56,202*16,87*16);
            gpJeu->ajouteEnnemi(56,212*16,89*16); gpJeu->ajouteEnnemi(56,190*16,10*16);
            gpJeu->ajouteEnnemi(56,195*16,20*16); gpJeu->ajouteEnnemi(56,203*16,9*16);
            gpJeu->ajouteEnnemi(56,206*16,18*16); gpJeu->ajouteEnnemi(56,229*16,36*16);
            gpJeu->ajouteEnnemi(56,106*16,40*16); gpJeu->ajouteEnnemi(56,113*16,33*16);
            gpJeu->ajouteEnnemi(56,249*16+8,37*16); gpJeu->ajouteEnnemi(56,169*16,66*16);
            gpJeu->ajouteEnnemi(56,33*16,66*16); gpJeu->ajouteEnnemi(56,66*16,50*16);
            gpJeu->ajouteEnnemi(56,73*16,54*16); gpJeu->ajouteEnnemi(56,50*16,48*16);
            gpJeu->ajouteEnnemi(56,273*16,7*16); gpJeu->ajouteEnnemi(56,287*16,14*16);
            gpJeu->ajouteEnnemi(56,296*16,7*16); gpJeu->ajouteEnnemi(56,297*16,24*16);
            gpJeu->ajouteEnnemi(56,307*16,14*16); gpJeu->ajouteEnnemi(56,287*16,36*16);
            gpJeu->ajouteEnnemi(62,269*16,81*16); gpJeu->ajouteEnnemi(62,189*16,51*16);
            gpJeu->ajouteEnnemi(62,298*16,90*16);
            gpJeu->ajouteEnnemi(64,106*16,65*16); gpJeu->ajouteEnnemi(64,112*16,69*16);
            gpJeu->ajouteEnnemi(64,93*16,82*16); gpJeu->ajouteEnnemi(64,148*16,84*16);
            gpJeu->ajouteEnnemi(64,152*16,78*16); gpJeu->ajouteEnnemi(64,229*16,66*16);
            gpJeu->ajouteEnnemi(64,189*16,66*16); gpJeu->ajouteEnnemi(64,228*16,6*16);
            gpJeu->ajouteEnnemi(64,209*16,36*16); gpJeu->ajouteEnnemi(64,209*16,53*16);
            gpJeu->ajouteEnnemi(64,218*16,50*16); gpJeu->ajouteEnnemi(64,227*16,52*16);
            gpJeu->ajouteEnnemi(64,89*16,37*16); gpJeu->ajouteEnnemi(64,166*16,21*16);
            gpJeu->ajouteEnnemi(64,69*16,66*16); gpJeu->ajouteEnnemi(64,271*16,21*16);
            gpJeu->ajouteEnnemi(64,292*16,12*16); gpJeu->ajouteEnnemi(64,309*16,36*16);
            gpJeu->ajouteEnnemi(91,229*16+8,82*16); gpJeu->ajouteEnnemi(91,226*16,20*16);
            gpJeu->ajouteEnnemi(91,232*16,23*16); gpJeu->ajouteEnnemi(91,119*16,23*16);
            gpJeu->ajouteEnnemi(91,135*16,23*16); gpJeu->ajouteEnnemi(91,46*16,34*16);
            gpJeu->ajouteEnnemi(91,48*16,39*16); gpJeu->ajouteEnnemi(91,53*16,36*16);
            gpJeu->ajouteEnnemi(91,288*16,89*16); gpJeu->ajouteEnnemi(91,296*16,96*16);
            gpJeu->ajouteEnnemi(91,298*16,83*16); gpJeu->ajouteEnnemi(91,307*16,91*16);
            gpJeu->ajouteEnnemi(101,29*16,58*16); gpJeu->ajouteEnnemi(101,238*16,36*16+8);
            gpJeu->ajouteEnnemi(101,298*16,36*16+8);
            //mini boss
            if (!gpJoueur->getCoffre(4,38)) gpJeu->ajouteEnnemi(102,169*16+4,51*16);
            //boss
            if(gpJoueur->getCoeur(4)==0) {
                gpJeu->ajouteEnnemi(103,247*16+6,17*16);
            }
            //clé du temps
            if(!gpJoueur->hasObjet(O_CLE_TEMPS)) gpJeu->ajouteObjet(I_CLE_TEMPS,16*249+8,16*5,0,1);
            //objets
            gpJeu->ajouteObjet(3,16*195,16*81,0,1);
            gpJeu->ajouteObjet(4,16*43,16*55-4,0,1); gpJeu->ajouteObjet(4,16*96,16*55-4,0,1);
            gpJeu->ajouteObjet(4,16*166,16*64-4,0,1); gpJeu->ajouteObjet(4,16*184,16*85-4,0,1);
            gpJeu->ajouteObjet(4,16*188,16*9-4,0,1);
            gpJeu->ajouteObjet(4,16*248,16*40-4,0,1); gpJeu->ajouteObjet(4,16*282,16*25-4,0,1);
            gpJeu->ajouteObjet(4,16*284,16*79-4,0,1); gpJeu->ajouteObjet(4,16*285,16*100-4,0,1);
            gpJeu->ajouteObjet(5,16*56,16*55,0,1); gpJeu->ajouteObjet(5,16*162,16*25,0,1);
            gpJeu->ajouteObjet(5,16*173,16*64,0,1); gpJeu->ajouteObjet(5,16*211,16*27,0,1);
            gpJeu->ajouteObjet(5,16*244,16*70,0,1); gpJeu->ajouteObjet(5,16*251,16*40,0,1);
            gpJeu->ajouteObjet(5,16*272,16*6,0,1); gpJeu->ajouteObjet(5,16*284,16*77,0,1);
            gpJeu->ajouteObjet(5,16*310,16*100,0,1);
            gpJeu->ajouteObjet(6,16*95,16*87,0,1); gpJeu->ajouteObjet(6,16*185,16*85,0,1);
            gpJeu->ajouteObjet(6,16*255,16*70,0,1); gpJeu->ajouteObjet(6,16*272,16*7,0,1);
            gpJeu->ajouteObjet(6,16*284,16*100,0,1); gpJeu->ajouteObjet(6,16*315,16*100,0,1);
            //gemme
            if (!gpJoueur->getGemme(189)) gpJeu->ajouteObjet(I_GEMME,16*194,16*81,189,1);
            break;
        case 51 :
            //pièges
            gpJeu->ajouteEnnemi(70,80*16,41*16); gpJeu->ajouteEnnemi(70,160*16,41*16);
            //ennemis
            gpJeu->ajouteEnnemi(7,146*16,70*16); gpJeu->ajouteEnnemi(7,154*16,63*16);
            gpJeu->ajouteEnnemi(7,143*16,21*16); gpJeu->ajouteEnnemi(7,147*16,26*16);
            gpJeu->ajouteEnnemi(7,148*16,18*16); gpJeu->ajouteEnnemi(7,151*16,22*16);
            gpJeu->ajouteEnnemi(7,153*16,25*16); gpJeu->ajouteEnnemi(7,156*16,20*16);
            gpJeu->ajouteEnnemi(7,129*16+8,81*16); gpJeu->ajouteEnnemi(7,45*16,55*16);
            gpJeu->ajouteEnnemi(7,49*16,54*16); gpJeu->ajouteEnnemi(7,55*16,51*16);
            gpJeu->ajouteEnnemi(7,105*16,71*16); gpJeu->ajouteEnnemi(7,106*16,63*16);
            gpJeu->ajouteEnnemi(7,115*16,66*16); gpJeu->ajouteEnnemi(7,288*16,88*16);
            gpJeu->ajouteEnnemi(7,297*16,97*16); gpJeu->ajouteEnnemi(7,302*16,81*16);
            gpJeu->ajouteEnnemi(7,312*16,87*16); gpJeu->ajouteEnnemi(7,294*16,20*16);
            gpJeu->ajouteEnnemi(7,296*16,11*16); gpJeu->ajouteEnnemi(7,304*16,22*16);
            gpJeu->ajouteEnnemi(7,306*16,12*16); gpJeu->ajouteEnnemi(7,307*16,37*16);
            gpJeu->ajouteEnnemi(7,275*16,81*16); gpJeu->ajouteEnnemi(7,226*16,96*16);
            gpJeu->ajouteEnnemi(7,233*16,98*16); gpJeu->ajouteEnnemi(7,199*16,85*16);
            gpJeu->ajouteEnnemi(7,207*16,98*16); gpJeu->ajouteEnnemi(7,209*16,88*16);
            gpJeu->ajouteEnnemi(7,189*16,18*16); gpJeu->ajouteEnnemi(7,196*16,8*16);
            gpJeu->ajouteEnnemi(7,201*16,21*16); gpJeu->ajouteEnnemi(7,214*16,15*16);
            gpJeu->ajouteEnnemi(7,226*16,51*16); gpJeu->ajouteEnnemi(7,230*16,54*16);
            gpJeu->ajouteEnnemi(17,164*16,64*16-8); gpJeu->ajouteEnnemi(17,34*16,36*16-8);
            gpJeu->ajouteEnnemi(17,84*16,71*16); gpJeu->ajouteEnnemi(17,85*16,62*16);
            gpJeu->ajouteEnnemi(17,94*16,72*16); gpJeu->ajouteEnnemi(17,95*16,63*16);
            gpJeu->ajouteEnnemi(17,113*16,21*16); gpJeu->ajouteEnnemi(17,114*16,22*16);
            gpJeu->ajouteEnnemi(17,115*16,23*16); gpJeu->ajouteEnnemi(17,286*16,51*16);
            gpJeu->ajouteEnnemi(17,293*16,51*16); gpJeu->ajouteEnnemi(17,192*16,51*16);
            gpJeu->ajouteEnnemi(17,194*16,51*16); gpJeu->ajouteEnnemi(17,196*16,51*16);
            gpJeu->ajouteEnnemi(17,269*16,100*16); gpJeu->ajouteEnnemi(17,271*16,93*16);
            gpJeu->ajouteEnnemi(29,125*16,64*16); gpJeu->ajouteEnnemi(29,134*16,68*16);
            gpJeu->ajouteEnnemi(29,166*16,66*16); gpJeu->ajouteEnnemi(29,47*16,34*16);
            gpJeu->ajouteEnnemi(29,65*16,52*16); gpJeu->ajouteEnnemi(29,73*16,54*16);
            gpJeu->ajouteEnnemi(29,54*16,66*16); gpJeu->ajouteEnnemi(29,27*16,65*16);
            gpJeu->ajouteEnnemi(29,34*16,68*16); gpJeu->ajouteEnnemi(29,105*16,54*16);
            gpJeu->ajouteEnnemi(29,114*16,56*16); gpJeu->ajouteEnnemi(29,147*16,50*16);
            gpJeu->ajouteEnnemi(29,153*16,52*16); gpJeu->ajouteEnnemi(29,292*16,71*16);
            gpJeu->ajouteEnnemi(29,294*16,63*16); gpJeu->ajouteEnnemi(29,266*16,8*16);
            gpJeu->ajouteEnnemi(29,272*16,3*16); gpJeu->ajouteEnnemi(29,307*16,51*16);
            gpJeu->ajouteEnnemi(29,286*16,37*16); gpJeu->ajouteEnnemi(29,270*16,51*16);
            gpJeu->ajouteEnnemi(29,273*16,66*16); gpJeu->ajouteEnnemi(29,249*16+8,96*16);
            gpJeu->ajouteEnnemi(29,228*16,6*16); gpJeu->ajouteEnnemi(29,205*16,35*16);
            gpJeu->ajouteEnnemi(29,214*16,37*16); gpJeu->ajouteEnnemi(29,193*16,66*16);
            gpJeu->ajouteEnnemi(29,233*16,78*16);
            gpJeu->ajouteEnnemi(16,149*16+8,37*16-8); gpJeu->ajouteEnnemi(16,51*16+8,37*16-8);
            gpJeu->ajouteEnnemi(16,69*16+8,37*16-8); gpJeu->ajouteEnnemi(16,69*16+8,67*16-8);
            gpJeu->ajouteEnnemi(16,109*16+8,51*16-8); gpJeu->ajouteEnnemi(16,149*16+8,82*16-8);
            gpJeu->ajouteEnnemi(16,289*16+8,52*16-8); gpJeu->ajouteEnnemi(16,268*16,85*16);
            gpJeu->ajouteEnnemi(16,229*16+8,67*16-8); gpJeu->ajouteEnnemi(16,189*16+8,37*16-8);
            gpJeu->ajouteEnnemi(16,209*16+8,67*16-8); gpJeu->ajouteEnnemi(16,270*16,97*16-8);
            gpJeu->ajouteEnnemi(16,249*16+8,82*16-8);
            gpJeu->ajouteEnnemi(61,109*16,81*16-8); gpJeu->ajouteEnnemi(61,26*16,55*16+8);
            gpJeu->ajouteEnnemi(61,86*16,64*16);
            gpJeu->ajouteEnnemi(62,309*16,67*16); gpJeu->ajouteEnnemi(62,207*16,51*16);
            gpJeu->ajouteEnnemi(62,249*16,66*16);
            //mini boss
            if (!gpJoueur->getCoffre(5,24)) {
                gpJeu->ajouteEnnemi(104,129*16,34*16);
                gpJeu->ajouteEnnemi(49,123*16,32*16); setValeur(123*16,32*16,5000,2);
                gpJeu->ajouteEnnemi(49,137*16,32*16); setValeur(137*16,32*16,5000,2);
            }
            //boss
            if(gpJoueur->getCoeur(5)==0) {
                gpJeu->ajouteEnnemi(105,247*16+8,25*16);
                gpJeu->ajouteEnnemi(96,236*16,19*16); setValeur(236*16,19*16,5137,2);
                gpJeu->ajouteEnnemi(96,263*16,19*16); setValeur(263*16,19*16,5137,2);
                gpJeu->ajouteEnnemi(96,236*16,40*16); setValeur(236*16,40*16,5137,2);
                gpJeu->ajouteEnnemi(96,263*16,40*16); setValeur(263*16,40*16,5137,2);
            }
            //objets
            gpJeu->ajouteObjet(1,16*206,16*16,0,1);
            gpJeu->ajouteObjet(3,16*284,16*11,0,1);
            gpJeu->ajouteObjet(4,16*64,16*49-4,0,1); gpJeu->ajouteObjet(4,16*134,16*19-4,0,1);
            gpJeu->ajouteObjet(4,16*142,16*35-4,0,1); gpJeu->ajouteObjet(4,16*213,16*87-4,0,1);
            gpJeu->ajouteObjet(4,16*244,16*54-4,0,1); gpJeu->ajouteObjet(4,16*315,16*11-4,0,1);
            gpJeu->ajouteObjet(4,16*315,16*77-4,0,1);
            gpJeu->ajouteObjet(5,16*75,16*49,0,1); gpJeu->ajouteObjet(5,16*104,16*49,0,1);
            gpJeu->ajouteObjet(6,16*84,16*62,0,1); gpJeu->ajouteObjet(6,16*115,16*49,0,1);
            gpJeu->ajouteObjet(6,16*142,16*39,0,1); gpJeu->ajouteObjet(6,16*255,16*54,0,1);
            //gemme
            if (!gpJoueur->getGemme(190)) gpJeu->ajouteObjet(I_GEMME,16*284,16*20,190,1);
            break;
        case 52 :
            //caisses
            gpJeu->ajouteCaisse(1,310*16,81*16,1); gpJeu->ajouteCaisse(1,309*16,82*16,1);
            gpJeu->ajouteCaisse(1,310*16,83*16,1);
            //ennemis
            gpJeu->ajouteEnnemi(7,147*16,66*16); gpJeu->ajouteEnnemi(7,153*16,68*16);
            gpJeu->ajouteEnnemi(7,146*16,85*16); gpJeu->ajouteEnnemi(7,148*16,79*16);
            gpJeu->ajouteEnnemi(7,152*16,86*16); gpJeu->ajouteEnnemi(7,105*16,50*16);
            gpJeu->ajouteEnnemi(7,114*16,54*16); gpJeu->ajouteEnnemi(7,167*16,41*16);
            gpJeu->ajouteEnnemi(7,173*16,40*16); gpJeu->ajouteEnnemi(7,114*16,22*16);
            gpJeu->ajouteEnnemi(7,165*16,20*16); gpJeu->ajouteEnnemi(7,174*16,23*16);
            gpJeu->ajouteEnnemi(7,189*16+8,22*16); gpJeu->ajouteEnnemi(7,263*16,63*16);
            gpJeu->ajouteEnnemi(7,276*16,71*16); gpJeu->ajouteEnnemi(7,287*16,82*16);
            gpJeu->ajouteEnnemi(7,309*16+8,7*16); gpJeu->ajouteEnnemi(7,203*16,63*16);
            gpJeu->ajouteEnnemi(7,216*16,71*16);
            gpJeu->ajouteEnnemi(30,124*16+8,67*16-8); gpJeu->ajouteEnnemi(30,134*16+8,67*16-8);
            gpJeu->ajouteEnnemi(30,109*16+8,67*16-8); gpJeu->ajouteEnnemi(30,83*16+8,34*16-8);
            gpJeu->ajouteEnnemi(30,95*16+8,41*16-8); gpJeu->ajouteEnnemi(30,89*16+8,18*16-8);
            gpJeu->ajouteEnnemi(30,129*16+8,22*16-8); gpJeu->ajouteEnnemi(30,49*16+8,37*16-8);
            gpJeu->ajouteEnnemi(30,29*16+8,67*16-8); gpJeu->ajouteEnnemi(30,69*16+8,67*16-8);
            gpJeu->ajouteEnnemi(30,229*16+8,67*16-8); gpJeu->ajouteEnnemi(30,229*16+8,7*16-8);
            gpJeu->ajouteEnnemi(30,229*16+8,37*16-8); gpJeu->ajouteEnnemi(30,189*16+8,37*16-8);
            gpJeu->ajouteEnnemi(30,289*16+8,97*16-8); gpJeu->ajouteEnnemi(30,309*16+8,22*16-8);
            gpJeu->ajouteEnnemi(30,289*16+8,7*16-8);
            gpJeu->ajouteEnnemi(42,125*16-5,81*16-3); gpJeu->ajouteEnnemi(42,134*16-5,81*16-3);
            gpJeu->ajouteEnnemi(42,85*16-5,68*16-3); gpJeu->ajouteEnnemi(42,89*16-5,64*16-3);
            gpJeu->ajouteEnnemi(42,92*16-5,69*16-3); gpJeu->ajouteEnnemi(42,169*16-5+8,69*16-3);
            gpJeu->ajouteEnnemi(42,85*16-5,79*16-3); gpJeu->ajouteEnnemi(42,93*16-5,84*16-3);
            gpJeu->ajouteEnnemi(42,106*16-5,37*16-3); gpJeu->ajouteEnnemi(42,114*16-5,39*16-3);
            gpJeu->ajouteEnnemi(42,93*16-5,22*16-3); gpJeu->ajouteEnnemi(42,149*16-5+8,22*16-3);
            gpJeu->ajouteEnnemi(42,69*16-5+8,52*16-3); gpJeu->ajouteEnnemi(42,249*16-5+8,97*16-3);
            gpJeu->ajouteEnnemi(42,189*16-5+8,7*16-3); gpJeu->ajouteEnnemi(42,209*16-5+8,37*16-3);
            gpJeu->ajouteEnnemi(42,189*16-5+8,67*16-3); gpJeu->ajouteEnnemi(42,309*16-5+8,67*16-3);
            gpJeu->ajouteEnnemi(42,269*16-5+8,22*16-3);
            gpJeu->ajouteEnnemi(62,166*16,80*16); gpJeu->ajouteEnnemi(62,171*16,83*16);
            gpJeu->ajouteEnnemi(62,106*16,80*16); gpJeu->ajouteEnnemi(62,111*16,84*16);
            gpJeu->ajouteEnnemi(62,85*16,22*16);
            //mini boss
            if (!gpJoueur->getCoffre(6,22)) gpJeu->ajouteEnnemi(106,132*16,51*16);
            //boss
            if(gpJoueur->getCoeur(6)==0) {
                gpJeu->ajouteEnnemi(107,247*16+9,30*16);
            }
            //gemme jaune
            if(!gpJoueur->hasObjet(O_TROC3)) gpJeu->ajouteObjet(I_GEMME_JAUNE,16*249+8,16*21,0,1);
            //objets
            gpJeu->ajouteObjet(3,16*175,16*72,0,1);
            gpJeu->ajouteObjet(4,16*24,16*40-4,0,1); gpJeu->ajouteObjet(4,16*104,16*55-4,0,1);
            gpJeu->ajouteObjet(4,16*203,16*6-4,0,1); gpJeu->ajouteObjet(4,16*255,16*51-4,0,1);
            gpJeu->ajouteObjet(5,16*115,16*33,0,1); gpJeu->ajouteObjet(5,16*196,16*96,0,1);
            gpJeu->ajouteObjet(5,16*255,16*53,0,1);
            gpJeu->ajouteObjet(6,16*172,16*33,0,1); gpJeu->ajouteObjet(6,16*243,16*8,0,1);
            gpJeu->ajouteObjet(6,16*308,16*18,0,1);
            gpJeu->ajouteObjet(7,16*35,16*40-4,0,1);
            //gemme
            if (!gpJoueur->getGemme(191)) gpJeu->ajouteObjet(I_GEMME,16*263,16*51,191,1);
            break;
        case 53 :
            //ennemis
            gpJeu->ajouteEnnemi(12,234*16,48*16); gpJeu->ajouteEnnemi(12,234*16,54*16);
            gpJeu->ajouteEnnemi(12,225*16,38*16); gpJeu->ajouteEnnemi(12,230*16,35*16);
            gpJeu->ajouteEnnemi(12,234*16,37*16); gpJeu->ajouteEnnemi(12,184*16,30*16);
            gpJeu->ajouteEnnemi(12,193*16,37*16); gpJeu->ajouteEnnemi(12,204*16,22*16);
            gpJeu->ajouteEnnemi(12,215*16,28*16); gpJeu->ajouteEnnemi(12,229*16+8,8*16);
            gpJeu->ajouteEnnemi(12,229*16+8,22*16); gpJeu->ajouteEnnemi(12,209*16+8,51*16);
            gpJeu->ajouteEnnemi(12,187*16,50*16); gpJeu->ajouteEnnemi(12,192*16,53*16);
            gpJeu->ajouteEnnemi(12,169*16,52*16);
            gpJeu->ajouteEnnemi(13,44*16-8,46*16); gpJeu->ajouteEnnemi(13,55*16-8,46*16);
            gpJeu->ajouteEnnemi(13,58*16-8,31*16); gpJeu->ajouteEnnemi(13,40*16-8,39*16);
            gpJeu->ajouteEnnemi(13,21*16-8,31*16); gpJeu->ajouteEnnemi(13,18*16-8,43*16);
            gpJeu->ajouteEnnemi(13,44*16-8,16*16); gpJeu->ajouteEnnemi(13,18*16-8,13*16);
            gpJeu->ajouteEnnemi(13,61*16-8,13*16); gpJeu->ajouteEnnemi(13,142*16-8,36*16);
            gpJeu->ajouteEnnemi(13,144*16-8,43*16); gpJeu->ajouteEnnemi(13,149*16,31*16);
            gpJeu->ajouteEnnemi(13,155*16-8,43*16); gpJeu->ajouteEnnemi(13,157*16-8,36*16);
            gpJeu->ajouteEnnemi(13,124*16-8,46*16); gpJeu->ajouteEnnemi(13,135*16-8,46*16);
            gpJeu->ajouteEnnemi(13,109*16-8,37*16); gpJeu->ajouteEnnemi(13,104*16-8,24*16);
            gpJeu->ajouteEnnemi(13,134*16-8,24*16); gpJeu->ajouteEnnemi(13,147*16-8,7*16);
            gpJeu->ajouteEnnemi(13,146*16-8,16*16); gpJeu->ajouteEnnemi(13,152*16-8,28*16);
            gpJeu->ajouteEnnemi(13,105*16-8,1*16); gpJeu->ajouteEnnemi(13,114*16-8,1*16);
            gpJeu->ajouteEnnemi(13,84*16-8,46*16); gpJeu->ajouteEnnemi(13,90*16-8,58*16);
            gpJeu->ajouteEnnemi(13,96*16-8,46*16);
            gpJeu->ajouteEnnemi(17,124*16,37*16);
            gpJeu->ajouteEnnemi(33,26*16+3,50*16); gpJeu->ajouteEnnemi(33,32*16+3,50*16);
            gpJeu->ajouteEnnemi(33,49*16+3,52*16); gpJeu->ajouteEnnemi(33,67*16+3,51*16);
            gpJeu->ajouteEnnemi(33,71*16+3,55*16); gpJeu->ajouteEnnemi(33,73*16+3,49*16);
            gpJeu->ajouteEnnemi(33,69*16+3,36*16); gpJeu->ajouteEnnemi(33,13*16+3,51*16);
            gpJeu->ajouteEnnemi(33,6*16+3,35*16); gpJeu->ajouteEnnemi(33,11*16+3,39*16);
            gpJeu->ajouteEnnemi(33,65*16+3,22*16); gpJeu->ajouteEnnemi(33,26*16+3,20*16);
            gpJeu->ajouteEnnemi(33,6*16+3,7*16); gpJeu->ajouteEnnemi(33,12*16+3,4*16);
            gpJeu->ajouteEnnemi(33,13*16+3,21*16); gpJeu->ajouteEnnemi(33,51*16+3,5*16);
            gpJeu->ajouteEnnemi(33,69*16+3,6*16); gpJeu->ajouteEnnemi(33,91*16+3,107*16);
            gpJeu->ajouteEnnemi(33,93*16+3,115*16); gpJeu->ajouteEnnemi(33,129*16+3,111*16);
            gpJeu->ajouteEnnemi(33,85*16+3,84*16); gpJeu->ajouteEnnemi(33,109*16+3,87*16);
            gpJeu->ajouteEnnemi(33,120*16+3,95*16); gpJeu->ajouteEnnemi(33,128*16+3,84*16);
            gpJeu->ajouteEnnemi(33,109*16+3,66*16); gpJeu->ajouteEnnemi(33,147*16+3,66*16);
            gpJeu->ajouteEnnemi(33,146*16+3,95*16); gpJeu->ajouteEnnemi(33,152*16+3,98*16);
            gpJeu->ajouteEnnemi(33,148*16+3,111*16);
            gpJeu->ajouteEnnemi(34,109*16-4+8,111*16); gpJeu->ajouteEnnemi(34,91*16-4,65*16);
            gpJeu->ajouteEnnemi(34,89*16-4+8,96*16); gpJeu->ajouteEnnemi(34,129*16-4+8,66*16);
            gpJeu->ajouteEnnemi(34,9*16-4,66*16); gpJeu->ajouteEnnemi(34,10*16-4,81*16);
            gpJeu->ajouteEnnemi(34,10*16-4,112*16); gpJeu->ajouteEnnemi(34,11*16-4,97*16);
            gpJeu->ajouteEnnemi(34,28*16-4,111*16); gpJeu->ajouteEnnemi(34,29*16-4,67*16);
            gpJeu->ajouteEnnemi(34,30*16-4,88*16); gpJeu->ajouteEnnemi(34,38*16-4,81*16);
            gpJeu->ajouteEnnemi(34,41*16-4,93*16); gpJeu->ajouteEnnemi(34,49*16-4,112*16);
            gpJeu->ajouteEnnemi(34,50*16-4,65*16); gpJeu->ajouteEnnemi(34,51*16-4,85*16);
            gpJeu->ajouteEnnemi(34,69*16-4,111*16); gpJeu->ajouteEnnemi(34,70*16-4,67*16);
            gpJeu->ajouteEnnemi(34,65*16-4,96*16); gpJeu->ajouteEnnemi(34,74*16-4,96*16);
            gpJeu->ajouteEnnemi(61,106*16+3,49*16); gpJeu->ajouteEnnemi(61,126*16+3,4*16);
            //mini boss
            if (!gpJoueur->getCoffre(7,23)) gpJeu->ajouteEnnemi(108,89*16-5,21*16+8-2);
            //boss
            if(gpJoueur->getCoeur(7)==0) gpJeu->ajouteEnnemi(109,180*16,75*16);
            //gemme verte
            if(!gpJoueur->hasObjet(O_TROC4)) gpJeu->ajouteObjet(I_GEMME_VERTE,16*209+8,16*5,0,1);
            //objets
            gpJeu->ajouteObjet(3,16*49,16*83,0,1); gpJeu->ajouteObjet(3,16*151,16*6,0,1);
            gpJeu->ajouteObjet(4,16*26,16*36-4,0,1); gpJeu->ajouteObjet(4,16*27,16*86-4,0,1);
            gpJeu->ajouteObjet(4,16*135,16*84-4,0,1); gpJeu->ajouteObjet(4,16*226,16*5-4,0,1);
            gpJeu->ajouteObjet(4,16*186,16*4-4,0,1);
            gpJeu->ajouteObjet(5,16*34,16*102,0,1); gpJeu->ajouteObjet(5,16*53,16*37,0,1);
            gpJeu->ajouteObjet(5,16*108,16*97,0,1); gpJeu->ajouteObjet(5,16*193,16*4,0,1);
            gpJeu->ajouteObjet(5,16*233,16*5,0,1);
            gpJeu->ajouteObjet(6,16*43,16*19,0,1); gpJeu->ajouteObjet(6,16*131,16*81,0,1);
            gpJeu->ajouteObjet(6,16*232,16*5,0,1);
            gpJeu->ajouteObjet(7,16*104,16*84-4,0,1); gpJeu->ajouteObjet(7,16*227,16*5-4,0,1);
            //gemme
            if (!gpJoueur->getGemme(192)) gpJeu->ajouteObjet(I_GEMME,16*148,16*6,192,1);
            break;
        case 54 :
            //caisses
            gpJeu->ajouteCaisse(6,88*16,81*16,5); gpJeu->ajouteCaisse(6,90*16,81*16,3);
            gpJeu->ajouteCaisse(6,91*16,84*16,3); gpJeu->ajouteCaisse(6,247*16,39*16);
            gpJeu->ajouteCaisse(6,249*16,35*16); gpJeu->ajouteCaisse(6,250*16,39*16);
            gpJeu->ajouteCaisse(6,130*16,76*16); gpJeu->ajouteCaisse(6,130*16,77*16);
            gpJeu->ajouteCaisse(6,224*16,79*16); gpJeu->ajouteCaisse(6,230*16,52*16,3);
            gpJeu->ajouteCaisse(6,224*16,85*16); gpJeu->ajouteCaisse(6,235*16,79*16);
            gpJeu->ajouteCaisse(6,235*16,85*16); gpJeu->ajouteCaisse(6,229*16,51*16,1);
            gpJeu->ajouteCaisse(6,230*16,51*16,4); gpJeu->ajouteCaisse(6,229*16,52*16,2);
            //ennemis
            gpJeu->ajouteEnnemi(2,109*16+5,36*16-6); gpJeu->ajouteEnnemi(2,67*16+5,65*16-6);
            gpJeu->ajouteEnnemi(2,71*16+5,68*16-6); gpJeu->ajouteEnnemi(2,50*16+5,51*16-6);
            gpJeu->ajouteEnnemi(2,147*16+5,26*16-6); gpJeu->ajouteEnnemi(2,149*16+5,34*16-6);
            gpJeu->ajouteEnnemi(2,152*16+5,30*16-6); gpJeu->ajouteEnnemi(2,209*16+5,65*16-6);
            gpJeu->ajouteEnnemi(2,209*16+5,81*16-6); gpJeu->ajouteEnnemi(2,228*16+5,36*16-6);
            gpJeu->ajouteEnnemi(41,69*16,42*16); gpJeu->ajouteEnnemi(41,76*16,50*16);
            gpJeu->ajouteEnnemi(41,91*16,48*16); gpJeu->ajouteEnnemi(41,127*16,52*16);
            gpJeu->ajouteEnnemi(41,130*16,10*16);
            gpJeu->ajouteEnnemi(42,111*16-5,77*16-3); gpJeu->ajouteEnnemi(42,117*16-5,67*16-3);
            gpJeu->ajouteEnnemi(42,121*16-5,75*16-3); gpJeu->ajouteEnnemi(42,109*16-5+8,52*16-3);
            gpJeu->ajouteEnnemi(42,30*16-5,82*16-3); gpJeu->ajouteEnnemi(42,42*16-5,73*16-3);
            gpJeu->ajouteEnnemi(42,31*16-5,33*16-3); gpJeu->ajouteEnnemi(42,39*16-5,37*16-3);
            gpJeu->ajouteEnnemi(42,46*16-5,26*16-3); gpJeu->ajouteEnnemi(42,169*16-5+8,22*16-3);
            gpJeu->ajouteEnnemi(42,191*16-5,40*16-3); gpJeu->ajouteEnnemi(42,203*16-5,45*16-3);
            gpJeu->ajouteEnnemi(42,249*16-5+8,51*16-3); gpJeu->ajouteEnnemi(42,89*16-5+8,67*16-3);
            gpJeu->ajouteEnnemi(62,249*16,81*16); gpJeu->ajouteEnnemi(62,189*16,66*16);
            gpJeu->ajouteEnnemi(112,26*16,6*16); gpJeu->ajouteEnnemi(112,31*16,4*16);
            gpJeu->ajouteEnnemi(112,32*16,9*16); gpJeu->ajouteEnnemi(112,126*16,35*16);
            gpJeu->ajouteEnnemi(112,71*16,36*16); gpJeu->ajouteEnnemi(112,85*16,33*16);
            gpJeu->ajouteEnnemi(112,134*16,69*16); gpJeu->ajouteEnnemi(112,53*16,66*16);
            gpJeu->ajouteEnnemi(112,50*16,79*16); gpJeu->ajouteEnnemi(112,54*16,7*16);
            gpJeu->ajouteEnnemi(112,106*16,7*16); gpJeu->ajouteEnnemi(112,114*16,8*16);
            gpJeu->ajouteEnnemi(112,147*16,6*16); gpJeu->ajouteEnnemi(112,149*16,9*16);
            gpJeu->ajouteEnnemi(112,152*16,7*16); gpJeu->ajouteEnnemi(112,166*16,38*16);
            gpJeu->ajouteEnnemi(112,173*16,37*16); gpJeu->ajouteEnnemi(112,186*16,52*16);
            gpJeu->ajouteEnnemi(112,213*16,36*16); gpJeu->ajouteEnnemi(112,215*16,49*16);
            gpJeu->ajouteEnnemi(112,185*16,82*16); gpJeu->ajouteEnnemi(112,191*16,80*16);
            gpJeu->ajouteEnnemi(112,147*16,75*16); gpJeu->ajouteEnnemi(112,158*16,69*16);
            gpJeu->ajouteEnnemi(112,160*16,81*16); gpJeu->ajouteEnnemi(112,171*16,68*16);
            gpJeu->ajouteEnnemi(112,227*16,80*16); gpJeu->ajouteEnnemi(112,233*16,82*16);
            gpJeu->ajouteEnnemi(112,249*16,24*16); gpJeu->ajouteEnnemi(112,102*16,66*16);
            gpJeu->ajouteEnnemi(112,225*16,67*16);
            //mini boss
            if (!gpJoueur->getCoffre(8,23)) gpJeu->ajouteEnnemi(110,70*16+1,6*16);
            //boss
            if(gpJoueur->getCoeur(8)==0) {
                gpJeu->ajouteEnnemi(111,198*16,19*16);
                gpJeu->ajouteEnnemi(65,193*16,17*16);
                gpJeu->ajouteEnnemi(65,206*16,17*16);
            }
            //gemme bleue
            if(!gpJoueur->hasObjet(O_TROC2)) gpJeu->ajouteObjet(I_GEMME_BLEUE,16*199+8,16*5,0,1);
            //objets
            gpJeu->ajouteObjet(3,16*137,16*15,0,1);
            gpJeu->ajouteObjet(4,16*46,16*4-4,0,1); gpJeu->ajouteObjet(4,16*52,16*83-4,0,1);
            gpJeu->ajouteObjet(4,16*113,16*21-4,0,1); gpJeu->ajouteObjet(4,16*122,16*2-4,0,1);
            gpJeu->ajouteObjet(4,16*136,16*15-4,0,1); gpJeu->ajouteObjet(4,16*144,16*41-4,0,1);
            gpJeu->ajouteObjet(4,16*174,16*78-4,0,1); gpJeu->ajouteObjet(4,16*202,16*32-4,0,1);
            gpJeu->ajouteObjet(5,16*52,16*84,0,1); gpJeu->ajouteObjet(5,16*64,16*45,0,1);
            gpJeu->ajouteObjet(6,16*217,16*48,0,1);
            gpJeu->ajouteObjet(7,16*46,16*10-4,0,1); gpJeu->ajouteObjet(7,16*62,16*45-4,0,1);
            gpJeu->ajouteObjet(7,16*84,16*37-4,0,1); gpJeu->ajouteObjet(7,16*137,16*2-4,0,1);
            gpJeu->ajouteObjet(7,16*197,16*32-4,0,1); gpJeu->ajouteObjet(7,16*215,16*48-4,0,1);
            gpJeu->ajouteObjet(7,16*244,16*25-4,0,1);
            //gemme
            if (!gpJoueur->getGemme(193)) gpJeu->ajouteObjet(I_GEMME,16*159,16*87,193,1);
            break;
        case 55 :
            //caisses
            gpJeu->ajouteCaisse(5,118*16,154*16); gpJeu->ajouteCaisse(5,118*16,155*16);
            gpJeu->ajouteCaisse(5,118*16,156*16);
            //ennemis
            gpJeu->ajouteEnnemi(38,67*16+3,66*16); gpJeu->ajouteEnnemi(38,29*16+3,37*16);
            gpJeu->ajouteEnnemi(38,45*16+3,3*16); gpJeu->ajouteEnnemi(38,47*16+3,9*16);
            gpJeu->ajouteEnnemi(38,53*16+3,5*16); gpJeu->ajouteEnnemi(38,107*16+3,21*16);
            gpJeu->ajouteEnnemi(38,89*16+3,66*16); gpJeu->ajouteEnnemi(38,45*16+3,54*16);
            gpJeu->ajouteEnnemi(38,125*16+3,111*16); gpJeu->ajouteEnnemi(38,69*16+3,125*16);
            gpJeu->ajouteEnnemi(38,92*16+3,114*16); gpJeu->ajouteEnnemi(38,89*16+3,141*16);
            gpJeu->ajouteEnnemi(38,29*16+3,111*16); gpJeu->ajouteEnnemi(38,27*16+3,140*16);
            gpJeu->ajouteEnnemi(38,107*16+3,94*16); gpJeu->ajouteEnnemi(38,112*16+3,99*16);
            gpJeu->ajouteEnnemi(38,107*16+3,84*16); gpJeu->ajouteEnnemi(38,112*16+3,81*16);
            gpJeu->ajouteEnnemi(38,49*16+3,216*16); gpJeu->ajouteEnnemi(38,89*16+3,216*16);
            gpJeu->ajouteEnnemi(38,27*16+3,185*16); gpJeu->ajouteEnnemi(38,32*16+3,187*16);
            gpJeu->ajouteEnnemi(38,49*16+3,155*16); gpJeu->ajouteEnnemi(38,107*16+3,172*16);
            gpJeu->ajouteEnnemi(38,105*16+3,217*16); gpJeu->ajouteEnnemi(38,109*16+3,198*16);
            gpJeu->ajouteEnnemi(38,86*16+3,4*16); gpJeu->ajouteEnnemi(38,89*16+3,9*16);
            gpJeu->ajouteEnnemi(39,5*16+4,34*16); gpJeu->ajouteEnnemi(39,13*16+4,34*16);
            gpJeu->ajouteEnnemi(39,129*16+4,36*16); gpJeu->ajouteEnnemi(39,129*16+4,125*16);
            gpJeu->ajouteEnnemi(39,47*16+4,110*16); gpJeu->ajouteEnnemi(39,70*16+4,97*16);
            gpJeu->ajouteEnnemi(39,89*16+4,126*16); gpJeu->ajouteEnnemi(39,29*16+4,96*16);
            gpJeu->ajouteEnnemi(39,9*16+4,126*16); gpJeu->ajouteEnnemi(39,109*16+4,110*16);
            gpJeu->ajouteEnnemi(39,89*16+4,81*16); gpJeu->ajouteEnnemi(39,49*16+4,81*16);
            gpJeu->ajouteEnnemi(39,9*16+4,186*16); gpJeu->ajouteEnnemi(39,113*16+4,187*16);
            gpJeu->ajouteEnnemi(39,129*16+4,186*16); gpJeu->ajouteEnnemi(39,91*16+4,5*16);
            gpJeu->ajouteEnnemi(72,66*16,5*16-6); gpJeu->ajouteEnnemi(72,69*16,8*16-6);
            gpJeu->ajouteEnnemi(72,73*16,4*16-6); gpJeu->ajouteEnnemi(72,17*16,12*16-6);
            gpJeu->ajouteEnnemi(72,12*16,56*16-6); gpJeu->ajouteEnnemi(72,25*16,66*16-6);
            gpJeu->ajouteEnnemi(72,25*16,53*16-6); gpJeu->ajouteEnnemi(72,31*16,55*16-6);
            gpJeu->ajouteEnnemi(72,110*16,55*16-6); gpJeu->ajouteEnnemi(72,121*16,63*16-6);
            gpJeu->ajouteEnnemi(72,122*16,53*16-6); gpJeu->ajouteEnnemi(72,132*16,65*16-6);
            gpJeu->ajouteEnnemi(118,73*16+1,215*16+1); gpJeu->ajouteEnnemi(118,5*16+1,157*16+1);
            gpJeu->ajouteEnnemi(118,9*16+1,173*16+1); gpJeu->ajouteEnnemi(118,11*16+1,162*16+1);
            gpJeu->ajouteEnnemi(118,13*16+1,156*16+1); gpJeu->ajouteEnnemi(118,17*16+1,170*16+1);
            gpJeu->ajouteEnnemi(118,22*16+1,159*16+1); gpJeu->ajouteEnnemi(118,23*16+1,166*16+1);
            gpJeu->ajouteEnnemi(118,29*16+1,172*16+1); gpJeu->ajouteEnnemi(118,31*16+1,156*16+1);
            gpJeu->ajouteEnnemi(118,43*16+1,44*16+1); gpJeu->ajouteEnnemi(118,44*16+1,18*16+1);
            gpJeu->ajouteEnnemi(118,58*16+1,56*16+1); gpJeu->ajouteEnnemi(118,83*16+1,55*16+1);
            gpJeu->ajouteEnnemi(118,93*16+1,18*16+1); gpJeu->ajouteEnnemi(118,94*16+1,39*16+1);
            gpJeu->ajouteEnnemi(118,95*16+1,56*16+1); gpJeu->ajouteEnnemi(118,9*16+1,15*16+1);
            gpJeu->ajouteEnnemi(118,16*16+1,20*16+1); gpJeu->ajouteEnnemi(118,23*16+1,9*16+1);
            gpJeu->ajouteEnnemi(118,25*16+1,14*16+1); gpJeu->ajouteEnnemi(118,27*16+1,20*16+1);
            gpJeu->ajouteEnnemi(118,31*16+1,15*16+1); gpJeu->ajouteEnnemi(118,9*16+1,38*16+1);
            gpJeu->ajouteEnnemi(118,106*16+1,37*16+1); gpJeu->ajouteEnnemi(118,107*16+1,65*16+1);
            gpJeu->ajouteEnnemi(118,115*16+1,67*16+1); gpJeu->ajouteEnnemi(118,127*16+1,51*16+1);
            gpJeu->ajouteEnnemi(118,46*16+1,66*16+1); gpJeu->ajouteEnnemi(118,52*16+1,68*16+1);
            gpJeu->ajouteEnnemi(118,6*16+1,106*16+1); gpJeu->ajouteEnnemi(118,8*16+1,112*16+1);
            gpJeu->ajouteEnnemi(118,10*16+1,96*16+1); gpJeu->ajouteEnnemi(118,11*16+1,104*16+1);
            gpJeu->ajouteEnnemi(118,13*16+1,100*16+1); gpJeu->ajouteEnnemi(118,131*16+1,105*16+1);
            gpJeu->ajouteEnnemi(118,132*16+1,97*16+1); gpJeu->ajouteEnnemi(118,132*16+1,110*16+1);
            gpJeu->ajouteEnnemi(118,105*16+1,126*16+1); gpJeu->ajouteEnnemi(118,114*16+1,127*16+1);
            gpJeu->ajouteEnnemi(118,50*16+1,96*16+1); gpJeu->ajouteEnnemi(118,50*16+1,125*16+1);
            gpJeu->ajouteEnnemi(118,79*16+1,93*16+1); gpJeu->ajouteEnnemi(118,90*16+1,101*16+1);
            gpJeu->ajouteEnnemi(118,92*16+1,95*16+1); gpJeu->ajouteEnnemi(118,28*16+1,125*16+1);
            gpJeu->ajouteEnnemi(118,33*16+1,128*16+1); gpJeu->ajouteEnnemi(118,31*16+1,143*16+1);
            gpJeu->ajouteEnnemi(118,46*16+1,141*16+1); gpJeu->ajouteEnnemi(118,51*16+1,143*16+1);
            gpJeu->ajouteEnnemi(118,54*16+1,139*16+1); gpJeu->ajouteEnnemi(118,107*16+1,141*16+1);
            gpJeu->ajouteEnnemi(118,113*16+1,144*16+1); gpJeu->ajouteEnnemi(118,26*16+1,81*16+1);
            gpJeu->ajouteEnnemi(118,33*16+1,84*16+1); gpJeu->ajouteEnnemi(118,6*16+1,205*16+1);
            gpJeu->ajouteEnnemi(118,11*16+1,212*16+1); gpJeu->ajouteEnnemi(118,17*16+1,201*16+1);
            gpJeu->ajouteEnnemi(118,20*16+1,209*16+1); gpJeu->ajouteEnnemi(118,32*16+1,210*16+1);
            gpJeu->ajouteEnnemi(118,44*16+1,194*16+1); gpJeu->ajouteEnnemi(118,45*16+1,170*16+1);
            gpJeu->ajouteEnnemi(118,56*16+1,204*16+1); gpJeu->ajouteEnnemi(118,62*16+1,169*16+1);
            gpJeu->ajouteEnnemi(118,85*16+1,170*16+1); gpJeu->ajouteEnnemi(118,87*16+1,205*16+1);
            gpJeu->ajouteEnnemi(118,93*16+1,194*16+1); gpJeu->ajouteEnnemi(118,95*16+1,180*16+1);
            gpJeu->ajouteEnnemi(118,123*16+1,155*16+1); gpJeu->ajouteEnnemi(118,130*16+1,172*16+1);
            gpJeu->ajouteEnnemi(118,106*16+1,184*16+1); gpJeu->ajouteEnnemi(118,108*16+1,190*16+1);
            gpJeu->ajouteEnnemi(118,113*16+1,205*16+1); gpJeu->ajouteEnnemi(118,117*16+1,213*16+1);
            gpJeu->ajouteEnnemi(118,125*16+1,203*16+1);
            //mini boss
            if (!gpJoueur->getCoffre(9,16)) {
                gpJeu->ajouteEnnemi(113,69*16+2,154*16);
                gpJeu->ajouteEnnemi(114,64*16,154*16);
                gpJeu->ajouteEnnemi(114,75*16,155*16);
                gpJeu->ajouteEnnemi(114,72*16,159*16);
                gpJeu->ajouteEnnemi(114,66*16,158*16);
                gpJeu->ajouteEnnemi(114,77*16,159*16);
            }
            //boss
            if(gpJoueur->getCoeur(9)==0) {
                gpJeu->ajouteEnnemi(115,66*16,31*16);
                gpJeu->ajouteEnnemi(116,64*16+1,34*16-4);
                gpJeu->ajouteEnnemi(117,71*16+1,34*16-4);
            }
            //gemme rougee
            if(!gpJoueur->hasObjet(O_TROC1)) gpJeu->ajouteObjet(I_GEMME_ROUGE,16*69+8,16*185,0,1);
            //objets
            gpJeu->ajouteObjet(3,16*127,16*94,0,1); gpJeu->ajouteObjet(3,16*33,16*169,0,1);
            gpJeu->ajouteObjet(4,16*24,16*87-4,0,1); gpJeu->ajouteObjet(4,16*104,16*87-4,0,1);
            gpJeu->ajouteObjet(4,16*56,16*128-4,0,1); gpJeu->ajouteObjet(4,16*23,16*154-4,0,1);
            gpJeu->ajouteObjet(4,16*42,16*160-4,0,1); gpJeu->ajouteObjet(4,16*116,16*154-4,0,1);
            gpJeu->ajouteObjet(4,16*76,16*205-4,0,1);
            gpJeu->ajouteObjet(5,16*65,16*65,0,1); gpJeu->ajouteObjet(5,16*115,16*87,0,1);
            gpJeu->ajouteObjet(5,16*66,16*92,0,1); gpJeu->ajouteObjet(5,16*4,16*117,0,1);
            gpJeu->ajouteObjet(5,16*95,16*116,0,1); gpJeu->ajouteObjet(5,16*37,16*154,0,1);
            gpJeu->ajouteObjet(5,16*42,16*154,0,1); gpJeu->ajouteObjet(5,16*55,16*152,0,1);
            gpJeu->ajouteObjet(5,16*116,16*156,0,1); gpJeu->ajouteObjet(5,16*133,16*203,0,1);
            gpJeu->ajouteObjet(6,16*75,16*132,0,1); gpJeu->ajouteObjet(6,16*21,16*197,0,1);
            gpJeu->ajouteObjet(7,16*24,16*94-4,0,1); gpJeu->ajouteObjet(7,16*56,16*95-4,0,1);
            gpJeu->ajouteObjet(7,16*45,16*115-4,0,1); gpJeu->ajouteObjet(7,16*76,16*204-4,0,1);
            //gemme
            if (!gpJoueur->getGemme(194)) gpJeu->ajouteObjet(I_GEMME,16*81,16*186,194,1);
            break;
        case 56 :
            //caisses
            for (int j = 0; j < 2; j++) for (int i = 0; i < 5; i++) 
                gpJeu->ajouteCaisse(5,(164+i)*16,(17+j)*16);
            for (int j = 0; j < 2; j++) for (int i = 0; i < 5; i++) 
                gpJeu->ajouteCaisse(5,(171+i)*16,(17+j)*16);
            //ennemis
            if (gpJoueur->getCoffre(10,12)) {
                gpJeu->ajouteEnnemi(119,69*16+5,38*16+5);
                gpJeu->ajouteEnnemi(119,69*16+5,50*16+5);
                gpJeu->ajouteEnnemi(119,48*16+5,96*16+5);
                gpJeu->ajouteEnnemi(119,86*16+5,49*16+5);
                gpJeu->ajouteEnnemi(119,91*16+5,54*16+5);
                gpJeu->ajouteEnnemi(119,49*16+5,51*16+5);
                gpJeu->ajouteEnnemi(119,9*16+5,38*16+5);
                gpJeu->ajouteEnnemi(119,27*16+5,38*16+5);
                gpJeu->ajouteEnnemi(119,17*16+5,53*16+5);
                gpJeu->ajouteEnnemi(119,33*16+5,46*16+5);
                gpJeu->ajouteEnnemi(119,49*16+5,37*16+5);
                gpJeu->ajouteEnnemi(119,9*16+5,68*16+5);
                gpJeu->ajouteEnnemi(119,9*16+5,78*16+5);
                gpJeu->ajouteEnnemi(119,7*16+5,97*16+5);
                gpJeu->ajouteEnnemi(119,19*16+5,95*16+5);
                gpJeu->ajouteEnnemi(119,29*16+5,98*16+5);
                gpJeu->ajouteEnnemi(119,87*16+5,35*16+5);
                gpJeu->ajouteEnnemi(119,91*16+5,39*16+5);
                gpJeu->ajouteEnnemi(119,129*16+5,97*16+5);
                gpJeu->ajouteEnnemi(119,109*16+5,34*16+5);
                gpJeu->ajouteEnnemi(119,106*16+5,19*16+5);
                gpJeu->ajouteEnnemi(119,112*16+5,23*16+5);
                gpJeu->ajouteEnnemi(119,110*16+5,53*16+5);
                gpJeu->ajouteEnnemi(119,127*16+5,51*16+5);
                gpJeu->ajouteEnnemi(119,129*16+5,36*16+5);
                gpJeu->ajouteEnnemi(119,129*16+5,69*16+5);
                gpJeu->ajouteEnnemi(119,129*16+5,78*16+5);
                gpJeu->ajouteEnnemi(119,129*16+5,14*16+5);
            } else {
                gpJeu->ajouteEnnemi(119,65*16+5,31*16+5-8); 
                mur[65*2+1][32*2-1]=1; mur[65*2+2][32*2-1]=1;
                mur[65*2+1][32*2]=1; mur[65*2+2][32*2]=1;
                gpJeu->ajouteEnnemi(119,73*16+5,31*16+5-8);
                mur[73*2+1][32*2-1]=1; mur[73*2+2][32*2-1]=1;
                mur[73*2+1][32*2]=1; mur[73*2+2][32*2]=1;
                gpJeu->ajouteEnnemi(119,45*16+5,93*16+5-8); 
                mur[45*2+1][94*2-1]=1; mur[45*2+2][94*2-1]=1;
                mur[45*2+1][94*2]=1; mur[45*2+2][94*2]=1;
                gpJeu->ajouteEnnemi(119,85*16+5,46*16+5-8); 
                mur[85*2+1][47*2-1]=1; mur[85*2+2][47*2-1]=1;
                mur[85*2+1][47*2]=1; mur[85*2+2][47*2]=1;
                gpJeu->ajouteEnnemi(119,93*16+5,46*16+5-8); 
                mur[93*2+1][47*2-1]=1; mur[93*2+2][47*2-1]=1;
                mur[93*2+1][47*2]=1; mur[93*2+2][47*2]=1;
                gpJeu->ajouteEnnemi(119,49*16+5,46*16+5-8); 
                mur[49*2+1][47*2-1]=1; mur[49*2+2][47*2-1]=1;
                mur[49*2+1][47*2]=1; mur[49*2+2][47*2]=1;
                gpJeu->ajouteEnnemi(119,7*16+5,33*16+5-8); 
                mur[7*2+1][34*2-1]=1; mur[7*2+2][34*2-1]=1;
                mur[7*2+1][34*2]=1; mur[7*2+2][34*2]=1;
                gpJeu->ajouteEnnemi(119,23*16+5,35*16+5-8); 
                mur[23*2+1][36*2-1]=1; mur[23*2+2][36*2-1]=1;
                mur[23*2+1][36*2]=1; mur[23*2+2][36*2]=1;
                gpJeu->ajouteEnnemi(119,16*16+5,50*16+5-8); 
                mur[16*2+1][51*2-1]=1; mur[16*2+2][51*2-1]=1;
                mur[16*2+1][51*2]=1; mur[16*2+2][51*2]=1;
                gpJeu->ajouteEnnemi(119,25*16+5,50*16+5-8); 
                mur[25*2+1][51*2-1]=1; mur[25*2+2][51*2-1]=1;
                mur[25*2+1][51*2]=1; mur[25*2+2][51*2]=1;
                gpJeu->ajouteEnnemi(119,53*16+5,31*16+5-8); 
                mur[53*2+1][32*2-1]=1; mur[53*2+2][32*2-1]=1;
                mur[53*2+1][32*2]=1; mur[53*2+2][32*2]=1;
                gpJeu->ajouteEnnemi(119,7*16+5,61*16+5-8); 
                mur[7*2+1][62*2-1]=1; mur[7*2+2][62*2-1]=1;
                mur[7*2+1][62*2]=1; mur[7*2+2][62*2]=1;
                gpJeu->ajouteEnnemi(119,11*16+5,61*16+5-8); 
                mur[11*2+1][62*2-1]=1; mur[11*2+2][62*2-1]=1;
                mur[11*2+1][62*2]=1; mur[11*2+2][62*2]=1;
                gpJeu->ajouteEnnemi(119,16*16+5,93*16+5-8); 
                mur[16*2+1][94*2-1]=1; mur[16*2+2][94*2-1]=1;
                mur[16*2+1][94*2]=1; mur[16*2+2][94*2]=1;
                gpJeu->ajouteEnnemi(119,25*16+5,93*16+5-8); 
                mur[25*2+1][94*2-1]=1; mur[25*2+2][94*2-1]=1;
                mur[25*2+1][94*2]=1; mur[25*2+2][94*2]=1;
                gpJeu->ajouteEnnemi(119,34*16+5,93*16+5-8); 
                mur[34*2+1][94*2-1]=1; mur[34*2+2][94*2-1]=1;
                mur[34*2+1][94*2]=1; mur[34*2+2][94*2]=1;
                gpJeu->ajouteEnnemi(119,86*16+5,31*16+5-8);
                mur[86*2+1][32*2-1]=1; mur[86*2+2][32*2-1]=1;
                mur[86*2+1][32*2]=1; mur[86*2+2][32*2]=1;
                gpJeu->ajouteEnnemi(119,92*16+5,31*16+5-8);
                mur[92*2+1][32*2-1]=1; mur[92*2+2][32*2-1]=1;
                mur[92*2+1][32*2]=1; mur[92*2+2][32*2]=1;
                gpJeu->ajouteEnnemi(119,126*16+5,91*16+5-8);
                mur[126*2+1][92*2-1]=1; mur[126*2+2][92*2-1]=1;
                mur[126*2+1][92*2]=1; mur[126*2+2][92*2]=1;
                gpJeu->ajouteEnnemi(119,113*16+5,31*16+5-8);
                mur[113*2+1][32*2-1]=1; mur[113*2+2][32*2-1]=1;
                mur[113*2+1][32*2]=1; mur[113*2+2][32*2]=1;
                gpJeu->ajouteEnnemi(119,105*16+5,16*16+5-8);
                mur[105*2+1][17*2-1]=1; mur[105*2+2][17*2-1]=1;
                mur[105*2+1][17*2]=1; mur[105*2+2][17*2]=1;
                gpJeu->ajouteEnnemi(119,113*16+5,16*16+5-8);
                mur[113*2+1][17*2-1]=1; mur[113*2+2][17*2-1]=1;
                mur[113*2+1][17*2]=1; mur[113*2+2][17*2]=1;
                gpJeu->ajouteEnnemi(119,115*16+5,48*16+5-8);
                mur[115*2+1][49*2-1]=1; mur[115*2+2][49*2-1]=1;
                mur[115*2+1][49*2]=1; mur[115*2+2][49*2]=1;
                gpJeu->ajouteEnnemi(119,123*16+5,48*16+5-8);
                mur[123*2+1][49*2-1]=1; mur[123*2+2][49*2-1]=1;
                mur[123*2+1][49*2]=1; mur[123*2+2][49*2]=1;
                gpJeu->ajouteEnnemi(119,125*16+5-8,33*16+5-8);
                mur[125*2][34*2-1]=1; mur[125*2+1][34*2-1]=1;
                mur[125*2][34*2]=1; mur[125*2+1][34*2]=1;
                gpJeu->ajouteEnnemi(119,125*16+5,61*16+5-8); 
                mur[125*2+1][62*2-1]=1; mur[125*2+2][62*2-1]=1;
                mur[125*2+1][62*2]=1; mur[125*2+2][62*2]=1;
                gpJeu->ajouteEnnemi(119,133*16+5,61*16+5-8); 
                mur[133*2+1][62*2-1]=1; mur[133*2+2][62*2-1]=1;
                mur[133*2+1][62*2]=1; mur[133*2+2][62*2]=1;
                gpJeu->ajouteEnnemi(119,129*16+5,3*16+5-8); 
                mur[129*2+1][4*2-1]=1; mur[129*2+2][4*2-1]=1;
                mur[129*2+1][4*2]=1; mur[129*2+2][4*2]=1;
            }
            gpJeu->ajouteEnnemi(119,49*16+5,21*16+5);
            gpJeu->ajouteEnnemi(119,48*16+5,6*16+5);
            gpJeu->ajouteEnnemi(119,7*16+5,23*16+5);
            gpJeu->ajouteEnnemi(119,19*16+5,20*16+5);
            gpJeu->ajouteEnnemi(119,31*16+5,23*16+5);
            gpJeu->ajouteEnnemi(119,10*16+5,6*16+5);
            gpJeu->ajouteEnnemi(119,27*16+5,6*16+5);
            gpJeu->ajouteEnnemi(119,89*16+5,21*16+5);
            gpJeu->ajouteEnnemi(119,149*16+5,22*16+5);
            gpJeu->ajouteEnnemi(119,149*16+5,32*16+5);
            gpJeu->ajouteEnnemi(119,189*16+5,22*16+5);
            gpJeu->ajouteEnnemi(119,189*16+5,32*16+5);
            gpJeu->ajouteEnnemi(119,146*16+5,5*16+5);
            gpJeu->ajouteEnnemi(119,152*16+5,5*16+5);
            gpJeu->ajouteEnnemi(119,187*16+5,5*16+5);
            gpJeu->ajouteEnnemi(119,193*16+5,5*16+5);
            gpJeu->ajouteEnnemi(119,169*16+5,36*16+5);
            gpJeu->ajouteEnnemi(119,90*16+5,6*16+5);
            gpJeu->ajouteEnnemi(119,69*16+5,21*16+5);
            //mini boss
            if (!gpJoueur->getCoffre(10,11)) {
                gpJeu->ajouteEnnemi(76,106*16+2,95*16);
                gpJeu->ajouteEnnemi(49,104*16+2,92*16);
                gpJeu->ajouteEnnemi(49,104*16+2,102*16);
            }
            //triforce
            if(gpJoueur->getEpee() < 5) {
                gpJeu->ajouteObjet(I_TRIFORCE,16*169+3,16*5,0,1);
                gpJeu->ajoutePnj(90,169*16-2+8,6*16+5,775);
            }
            //boss
            if(gpJoueur->getCoeur(10)==0) {
                gpJeu->ajouteEnnemi(120,169*16,17*16);
                if(gpJoueur->getEpee() < 5) gpJeu->getPnj()->getSuivant()->setVie(0);
            }
            //objets
            gpJeu->ajouteObjet(4,16*44,16*32-4,0,1); gpJeu->ajouteObjet(4,16*86,16*92-4,0,1);
            gpJeu->ajouteObjet(4,16*164,16*32-4,0,1);
            gpJeu->ajouteObjet(5,16*4,16*34,0,1); gpJeu->ajouteObjet(5,16*55,16*94,0,1);
            gpJeu->ajouteObjet(5,16*104,16*12,0,1); gpJeu->ajouteObjet(5,16*175,16*32,0,1);
            gpJeu->ajouteObjet(7,16*4,16*4-4,0,1); gpJeu->ajouteObjet(7,16*55,16*100-4,0,1);
            gpJeu->ajouteObjet(7,16*86,16*102-4,0,1); gpJeu->ajouteObjet(7,16*135,16*102-4,0,1);
            //gemme
            if (!gpJoueur->getGemme(195)) gpJeu->ajouteObjet(I_GEMME,16*5,16*83,195,1);
            break;
        case 57 :
            //générique fin
            if (gpJeu->getAudio()->isSpecial()) {
                gpJeu->ajoutePnj(15,69*16+8,21*16+8,1352);
                gpJeu->ajoutePnj(90,75*16+8,22*16+8,1352);
            }
            //quand lieu commun
            if (gpJoueur->getEpee() < 5) {
                //commun
                gpJeu->ajoutePnj(58,82*16+5-8,156*16+8,1021,E);
                gpJeu->ajoutePnj(58,89*16+5,176*16+8,1021,N);
                gpJeu->ajoutePnj(58,169*16+5,31*16+8,1090);
                gpJeu->ajoutePnj(58,162*16+5-8,36*16+8,1090,E);
                gpJeu->ajoutePnj(58,177*16+5-8,36*16+8,1090,O);
                
                // propre au début de jeu
                if (!gpJoueur->getEpee() && !gpJoueur->hasObjet(O_OCARINA)) {
                    if (gpJoueur->getAvancement() < ZELDA_SOUS_SOL) 
                        gpJeu->ajoutePnj(15,69*16+8,23*16-7,1016);
                    else gpJeu->ajoutePnj(15,102*16+8,171*16+9,1016, E);
                    
                    gpJeu->ajoutePnj(58,62*16+5-8,36*16+8,1004,E);
                    gpJeu->ajoutePnj(58,62*16+5-8,51*16+8,1004,E);
                    if (gpJoueur->getAvancement() < PARLE_GARDE_RESERVE) 
                        gpJeu->ajoutePnj(58,77*16+5-8,36*16+8,1008,O);
                    else gpJeu->ajoutePnj(58,77*16+5-8,34*16+8,1008,O);
                    if (gpJoueur->getAvancement() < PARLE_GARDE_CH_FORTE) 
                        gpJeu->ajoutePnj(58,77*16+5-8,51*16+8,1020,O);
                    else gpJeu->ajoutePnj(58,77*16+5-8,49*16+8,1020,O);
                    if (gpJoueur->getAvancement() < RESERVE_VIDE) 
                        gpJeu->ajoutePnj(58,69*16+5,31*16+8,1005);
                    else gpJeu->ajoutePnj(58,67*16+5,31*16+8,1005);
                    gpJeu->ajoutePnj(58,97*16+5-8,36*16+8,1010,O);
                    
                    
                    if (gpJoueur->getAvancement() < PARLE_GARDE_SOUS_SOL) 
                        gpJeu->ajoutePnj(58,97*16+5-8,171*16+8,1022,O);
                    else gpJeu->ajoutePnj(58,97*16+5-8,169*16+8,1022,O);
                }
                //propre au reste du jeu
                else {
                    if (gpJoueur->getAvancement() >= RETOUR_PRESENT)
                        gpJeu->ajoutePnj(15,69*16+8,23*16-7,1083);
                    gpJeu->ajoutePnj(58,97*16+5-8,169*16+8,1032,O);
                    gpJeu->ajoutePnj(58,49*16+5,49*16+8,1037,N);
                    gpJeu->ajoutePnj(58,122*16+5-8,6*16+8,1038,E);
                    gpJeu->ajoutePnj(58,117*16+5-8,6*16+8,1039,O);
                    gpJeu->ajoutePnj(58,85*16+5,48*16+8,1040);
                    gpJeu->ajoutePnj(58,66*16+5,31*16+8,1041);
                    gpJeu->ajoutePnj(58,72*16+5,31*16+8,1042);
                    gpJeu->ajoutePnj(58,45*16+5,31*16+8,1043);
                    gpJeu->ajoutePnj(58,9*16+5,57*16,1054,N);
                    gpJeu->ajoutePnj(58,129*16+5,57*16,1055,N);
                    gpJeu->ajoutePnj(58,86*16+5,31*16+8,1056);
                    gpJeu->ajoutePnj(58,107*16+5-8-4,18*16-2,1057);
                    
                    gpJeu->ajoutePnj(102,7*16+2,35*16+6,1044);
                    gpJeu->ajoutePnj(103,6*16,37*16+6,1045);
                    gpJeu->ajoutePnj(104,10*16,35*16,1046);
                    gpJeu->ajoutePnj(106,12*16,5*16,1050);
                    gpJeu->ajoutePnj(107,6*16,8*16,1051);
                    gpJeu->ajoutePnj(108,21*16,5*16,1052);
                    gpJeu->ajoutePnj(36,11*16,22*16,1053);
                }
            } 
            //quand donjon
            else {
                //caisses
                for (int j = 0; j < 2; j++) for (int i = 0; i < 5; i++) 
                    gpJeu->ajouteCaisse(5,(44+i)*16,(227+j)*16);
                for (int j = 0; j < 2; j++) for (int i = 0; i < 5; i++) 
                    gpJeu->ajouteCaisse(5,(51+i)*16,(227+j)*16);
                //boss
                if (!gpJoueur->getEnnemi(50)) {
                    gpJeu->ajoutePnj(15,5*16,229*16-7,1083);
                    gpJeu->ajouteEnnemi(50,169*16-10,17*16);
                    Ennemi* enn = gpJeu->getEnnemi()->getSuivant();
                    for (int i = 0; i < 10; i++) {
                        gpJeu->ajouteEnnemi(114,(165+i)*16,16*16);
                        gpJeu->ajouteEnnemi(122,(165+i)*16,16*16);
                        for (int j = 0; j < 2; j++) {
                            enn = enn->getSuivant();
                            enn->setVie(0);
                        }
                    }
                
                //ennemis
                gpJeu->ajouteEnnemi(46,67*16+5,35*16+5); gpJeu->ajouteEnnemi(46,68*16+5,48*16+5);
                gpJeu->ajouteEnnemi(46,72*16+5,42*16+5); gpJeu->ajouteEnnemi(46,8*16+5,7*16+5);
                gpJeu->ajouteEnnemi(46,20*16+5,4*16+5); gpJeu->ajouteEnnemi(46,30*16+5,8*16+5);
                gpJeu->ajouteEnnemi(46,8*16+5,21*16+5); gpJeu->ajouteEnnemi(46,14*16+5,25*16+5);
                gpJeu->ajouteEnnemi(46,26*16+5,26*16+5); gpJeu->ajouteEnnemi(46,33*16+5,19*16+5);
                gpJeu->ajouteEnnemi(46,4*16+5,96*16+5); gpJeu->ajouteEnnemi(46,9*16+5,99*16+5);
                gpJeu->ajouteEnnemi(46,17*16+5,94*16+5); gpJeu->ajouteEnnemi(46,22*16+5,99*16+5);
                gpJeu->ajouteEnnemi(46,28*16+5,95*16+5); gpJeu->ajouteEnnemi(46,89*16+5,21*16+5);
                gpJeu->ajouteEnnemi(46,105*16+5,5*16+5); gpJeu->ajouteEnnemi(46,113*16+5,4*16+5);
                gpJeu->ajouteEnnemi(46,109*16+5,52*16+5); gpJeu->ajouteEnnemi(46,117*16+5,53*16+5);
                gpJeu->ajouteEnnemi(46,126*16+5,50*16+5); gpJeu->ajouteEnnemi(46,127*16+5,81*16+5);
                gpJeu->ajouteEnnemi(46,128*16+5,71*16+5); gpJeu->ajouteEnnemi(46,133*16+5,76*16+5);
                gpJeu->ajouteEnnemi(47,85*16+5,48*16+5); gpJeu->ajouteEnnemi(47,87*16+5,55*16+5);
                gpJeu->ajouteEnnemi(47,47*16+5,47*16+5); gpJeu->ajouteEnnemi(47,51*16+5,55*16+5);
                gpJeu->ajouteEnnemi(47,54*16+5,49*16+5); gpJeu->ajouteEnnemi(47,47*16+5,6*16+5);
                gpJeu->ajouteEnnemi(47,47*16+5,22*16+5); gpJeu->ajouteEnnemi(47,46*16+5,34*16+5);
                gpJeu->ajouteEnnemi(47,53*16+5,39*16+5); gpJeu->ajouteEnnemi(47,32*16+5,97*16+5);
                gpJeu->ajouteEnnemi(47,86*16+5,34*16+5); gpJeu->ajouteEnnemi(47,92*16+5,40*16+5);
                gpJeu->ajouteEnnemi(47,106*16+5,26*16+5); gpJeu->ajouteEnnemi(47,110*16+5,18*16+5);
                gpJeu->ajouteEnnemi(47,113*16+5,25*16+5); gpJeu->ajouteEnnemi(47,125*16+5,35*16+5);
                gpJeu->ajouteEnnemi(47,133*16+5,38*16+5); gpJeu->ajouteEnnemi(47,107*16+5,96*16+5);
                gpJeu->ajouteEnnemi(47,110*16+5,99*16+5); gpJeu->ajouteEnnemi(47,115*16+5,94*16+5);
                gpJeu->ajouteEnnemi(47,126*16+5,99*16+5); gpJeu->ajouteEnnemi(47,133*16+5,94*16+5);
                gpJeu->ajouteEnnemi(48,86*16+5,171*16+5); gpJeu->ajouteEnnemi(48,93*16+5,173*16+5);
                gpJeu->ajouteEnnemi(48,86*16+5,156*16+5); gpJeu->ajouteEnnemi(48,11*16+5,236*16+5);
                gpJeu->ajouteEnnemi(48,21*16+5,235*16+5); gpJeu->ajouteEnnemi(48,30*16+5,236*16+5);
                gpJeu->ajouteEnnemi(48,71*16+5,235*16+5); gpJeu->ajouteEnnemi(48,17*16+5,40*16+5);
                gpJeu->ajouteEnnemi(48,21*16+5,48*16+5); gpJeu->ajouteEnnemi(48,27*16+5,43*16+5);
                gpJeu->ajouteEnnemi(48,7*16+5,69*16+5); gpJeu->ajouteEnnemi(48,9*16+5,81*16+5);
                gpJeu->ajouteEnnemi(48,11*16+5,75*16+5); gpJeu->ajouteEnnemi(48,47*16+5,95*16+5);
                gpJeu->ajouteEnnemi(48,69*16+5,22*16+5); gpJeu->ajouteEnnemi(48,127*16+5,21*16+5);
                gpJeu->ajouteEnnemi(48,129*16+5,7*16+5); gpJeu->ajouteEnnemi(48,132*16+5,16*16+5);
                gpJeu->ajouteEnnemi(48,109*16+5,35*16+5); gpJeu->ajouteEnnemi(48,91*16+5,98*16+5);
                gpJeu->ajouteEnnemi(48,147*16+5,26*16+5); gpJeu->ajouteEnnemi(48,149*16+5,34*16+5);
                gpJeu->ajouteEnnemi(48,152*16+5,21*16+5); gpJeu->ajouteEnnemi(48,167*16+5,36*16+5);
                gpJeu->ajouteEnnemi(48,171*16+5,36*16+5); gpJeu->ajouteEnnemi(48,187*16+5,21*16+5);
                gpJeu->ajouteEnnemi(48,189*16+5,7*16+5); gpJeu->ajouteEnnemi(48,189*16+5,34*16+5);
                gpJeu->ajouteEnnemi(48,192*16+5,27*16+5); gpJeu->ajouteEnnemi(48,45*16+5,245*16+5);
                gpJeu->ajouteEnnemi(48,53*16+5,245*16+5);
                
                } else {
                    gpJeu->ajoutePnj(15,169*16+8,19*16,1083);
                    gpJeu->ajouteEnnemi(89,169*16+6,4*16);
                    gpJeu->ajoutePnj(58,147*16+5-8,16*16+8,1371);
                }
                //mini boss
                if (!gpJoueur->getCoffre(11,7))
                    gpJeu->ajouteEnnemi(31,49*16,227*16);
            }
            //toujours
            gpJeu->ajoutePnj(105,6*16,48*16,1048); contenu[6][50]=1048;
            gpJeu->ajouteEnnemi(121,113*16,157*16); gpJeu->ajouteEnnemi(121,126*16,158*16);
            gpJeu->ajouteEnnemi(121,129*16,172*16); gpJeu->ajouteEnnemi(121,144*16,171*16);
            gpJeu->ajouteEnnemi(121,146*16,185*16); gpJeu->ajouteEnnemi(121,151*16,189*16);
            gpJeu->ajouteEnnemi(121,154*16,186*16); gpJeu->ajouteEnnemi(121,119*16,156*16);
            gpJeu->ajouteEnnemi(121,138*16,173*16); gpJeu->ajouteEnnemi(121,145*16,200*16);
            gpJeu->ajouteEnnemi(121,153*16,205*16);
            gpJeu->ajouteObjet(4,16*164,16*32-4,0,1); gpJeu->ajouteObjet(7,16*175,16*32-4,0,1);
            if (!gpJoueur->getGemme(197)) gpJeu->ajouteObjet(I_GEMME,16*4,16*27,197,1);
            if (!gpJoueur->getGemme(198)) gpJeu->ajouteObjet(I_GEMME,16*115,16*32,198,1);
            if (map[149][16]==6032) {
                gpJeu->ajoutePnj(112,149*16+8,4*16,1373);
                gpJeu->ajoutePnj(113,154*16+2,8*16+6,1375);
                gpJeu->ajoutePnj(114,145*16,8*16,1376);
            }
            break;
        case 58 :
            if (gpJeu->getJoueur()->getEnnemi(50)) {
                //caisses
                for (int j = 0; j < 3; j++) 
                    gpJeu->ajouteCaisse(5,134*16,(83+j)*16, 0);
                //immmobiles
                gpJeu->ajoutePnj(6,64*16,92*16+8,1114); contenu[64][94]=1114;
                gpJeu->ajoutePnj(6,29*16+8,66*16,1125);
                gpJeu->ajoutePnj(6,49*16+8,6*16,1131);
                gpJeu->ajoutePnj(6,30*16+8,5*16,1134);
                gpJeu->ajoutePnj(6,130*16+8,95*16,1136);
                gpJeu->ajoutePnj(6,13*16+8,81*16,1137);
                gpJeu->ajoutePnj(6,109*16+8,66*16,1138);
                gpJeu->ajoutePnj(6,126*16+8,83*16,1143);
                gpJeu->ajoutePnj(6,91*16+8,21*16,1144);
                Pnj* pnj = gpJeu->getPnj()->getSuivant();
                while (pnj != NULL) {
                    pnj->setImmo(true);
                    pnj = pnj->getSuivant();
                }
                //mobiles
                gpJeu->ajoutePnj(6,73*16,94*16+8,1120);
                gpJeu->ajoutePnj(6,129*16+8,6*16,1147);
                gpJeu->ajouteEnnemi(123,69*16+5,69*16); gpJeu->ajouteEnnemi(123,69*16+5,78*16);
                gpJeu->ajouteEnnemi(123,49*16+5,66*16); gpJeu->ajouteEnnemi(123,49*16+5,81*16);
                gpJeu->ajouteEnnemi(123,89*16+5,66*16); gpJeu->ajouteEnnemi(123,89*16+5,81*16);
                gpJeu->ajouteEnnemi(123,129*16+5,21*16); gpJeu->ajouteEnnemi(123,69*16+5,51*16);
                gpJeu->ajouteEnnemi(123,49*16+5,36*16); gpJeu->ajouteEnnemi(123,89*16+5,36*16);
                gpJeu->ajouteEnnemi(123,109*16+5,36*16); gpJeu->ajouteEnnemi(123,89*16+5,96*16);
                gpJeu->ajouteEnnemi(123,99*16+5,100*16); gpJeu->ajouteEnnemi(123,109*16+5,94*16);
                gpJeu->ajouteEnnemi(123,29*16+5,36*16); gpJeu->ajouteEnnemi(123,45*16+5,21*16);
                gpJeu->ajouteEnnemi(123,53*16+5,21*16); gpJeu->ajouteEnnemi(123,49*16+5,96*16);
                gpJeu->ajouteEnnemi(123,9*16+5,6*16); gpJeu->ajouteEnnemi(123,9*16+5,18*16);
                gpJeu->ajouteEnnemi(123,9*16+5,51*16); gpJeu->ajouteEnnemi(123,6*16+5,67*16);
                gpJeu->ajouteEnnemi(123,129*16+5,51*16); gpJeu->ajouteEnnemi(123,133*16+5,66*16);
                gpJeu->ajouteEnnemi(123,6*16+5,97*16); gpJeu->ajouteEnnemi(123,18*16+5,100*16);
                gpJeu->ajouteEnnemi(123,27*16+5,94*16);
                gpJeu->ajouteEnnemi(124,25*16,63*16); gpJeu->ajouteEnnemi(124,28*16,63*16);
                gpJeu->ajouteEnnemi(124,31*16,63*16); gpJeu->ajouteEnnemi(124,34*16,63*16);
                gpJeu->ajouteEnnemi(125,46*16,3*16); gpJeu->ajouteEnnemi(125,49*16,3*16);
                gpJeu->ajouteEnnemi(125,52*16,3*16);
                gpJeu->ajouteEnnemi(125,3*16,78*16); gpJeu->ajouteEnnemi(125,5*16,78*16);
                gpJeu->ajouteEnnemi(125,7*16,78*16); gpJeu->ajouteEnnemi(125,12*16,78*16);
                gpJeu->ajouteEnnemi(125,15*16,78*16);
                gpJeu->ajouteEnnemi(125,103*16,63*16); gpJeu->ajouteEnnemi(125,116*16,63*16);
                gpJeu->ajouteEnnemi(125,103*16,71*16); gpJeu->ajouteEnnemi(125,116*16,71*16);
                gpJeu->ajouteEnnemi(125,123*16,86*16); gpJeu->ajouteEnnemi(125,126*16,86*16);
                gpJeu->ajouteEnnemi(125,129*16,86*16);
                gpJeu->ajouteEnnemi(125,83*16,18*16); gpJeu->ajouteEnnemi(125,87*16,18*16);
                gpJeu->ajouteEnnemi(125,90*16,18*16); gpJeu->ajouteEnnemi(125,93*16,18*16);
                gpJeu->ajouteEnnemi(125,96*16,18*16);
                gpJeu->ajouteEnnemi(126,49*16+8,52*16); gpJeu->ajouteEnnemi(126,89*16+8,52*16);
                gpJeu->ajouteEnnemi(126,86*16,3*16); gpJeu->ajouteEnnemi(126,93*16,3*16);
                gpJeu->ajouteEnnemi(126,106*16,3*16); gpJeu->ajouteEnnemi(126,113*16,3*16);
                gpJeu->ajouteEnnemi(126,86*16,11*16); gpJeu->ajouteEnnemi(126,93*16,11*16);
                gpJeu->ajouteEnnemi(126,106*16,11*16); gpJeu->ajouteEnnemi(126,113*16,11*16);
                gpJeu->ajouteEnnemi(126,127*16,36*16); gpJeu->ajouteEnnemi(126,133*16,37*16);
                gpJeu->ajouteEnnemi(126,9*16,37*16);
                //boss
                if(gpJoueur->getCoeur(11)==0) {
                    gpJeu->ajouteEnnemi(127,67*16+9,32*16+1);
                }
            } else {
                gpJeu->ajoutePnj(6,73*16,94*16+8,1119);
            }
            gpJeu->ajouteObjet(3,16*62,16*27,0,1);
            if (!gpJoueur->getGemme(199)) gpJeu->ajouteObjet(I_GEMME,16*77,16*27,199,1);
            break;
        case 59 :
            //ennemis
            gpJeu->ajouteEnnemi(17,174*16,48*16); gpJeu->ajouteEnnemi(17,185*16,48*16);
            gpJeu->ajouteEnnemi(17,189*16,48*16); gpJeu->ajouteEnnemi(17,193*16,48*16);
            gpJeu->ajouteEnnemi(26,129*16+1,56*16); gpJeu->ajouteEnnemi(26,135*16+1,48*16);
            gpJeu->ajouteEnnemi(26,142*16+1,53*16); gpJeu->ajouteEnnemi(26,103*16+1,29*16);
            gpJeu->ajouteEnnemi(26,112*16+1,35*16); gpJeu->ajouteEnnemi(26,116*16+1,21*16);
            gpJeu->ajouteEnnemi(26,119*16+1,41*16); gpJeu->ajouteEnnemi(26,124*16+1,29*16);
            gpJeu->ajouteEnnemi(26,130*16+1,23*16); gpJeu->ajouteEnnemi(26,135*16+1,33*16);
            gpJeu->ajouteEnnemi(26,144*16+1,39*16); 
            gpJeu->ajouteEnnemi(26,145*16+1,18*16); gpJeu->ajouteEnnemi(26,145*16+1,30*16);
            gpJeu->ajouteEnnemi(26,153*16+1,27*16); gpJeu->ajouteEnnemi(26,155*16+1,37*16);
            gpJeu->ajouteEnnemi(26,152*16+1,4*16); gpJeu->ajouteEnnemi(26,124*16+1,5*16);
            gpJeu->ajouteEnnemi(26,114*16+1,9*16); gpJeu->ajouteEnnemi(26,86*16+1,4*16);
            gpJeu->ajouteEnnemi(26,85*16+1,40*16); gpJeu->ajouteEnnemi(26,88*16+1,25*16);
            gpJeu->ajouteEnnemi(26,95*16+1,30*16); gpJeu->ajouteEnnemi(26,245*16+1,25*16);
            gpJeu->ajouteEnnemi(26,245*16+1,38*16); gpJeu->ajouteEnnemi(26,252*16+1,29*16);
            gpJeu->ajouteEnnemi(26,256*16+1,21*16); gpJeu->ajouteEnnemi(26,245*16+1,55*16);
            gpJeu->ajouteEnnemi(26,313*16+1,55*16); gpJeu->ajouteEnnemi(26,313*16+1,4*16);
            gpJeu->ajouteEnnemi(26,190*16+1,33*16); gpJeu->ajouteEnnemi(26,194*16+1,20*16);
            gpJeu->ajouteEnnemi(26,209*16+1,26*16); gpJeu->ajouteEnnemi(26,185*16+1,3*16);
            gpJeu->ajouteEnnemi(26,198*16+1,4*16); gpJeu->ajouteEnnemi(26,205*16+1,11*16);
            gpJeu->ajouteEnnemi(26,213*16+1,3*16); gpJeu->ajouteEnnemi(26,234*16+1,4*16);
            gpJeu->ajouteEnnemi(26,224*16+1,32*16); gpJeu->ajouteEnnemi(26,230*16+1,25*16);
            gpJeu->ajouteEnnemi(26,234*16+1,39*16); gpJeu->ajouteEnnemi(26,232*16+1,55*16);
            gpJeu->ajouteEnnemi(26,166*16+1,53*16); gpJeu->ajouteEnnemi(26,165*16+1,30*16);
            gpJeu->ajouteEnnemi(26,170*16+1,23*16); gpJeu->ajouteEnnemi(26,176*16+1,34*16);
            gpJeu->ajouteEnnemi(42,6*16,34*16); gpJeu->ajouteEnnemi(42,8*16,6*16);
            gpJeu->ajouteEnnemi(42,14*16,24*16); gpJeu->ajouteEnnemi(42,27*16,35*16);
            gpJeu->ajouteEnnemi(42,29*16,52*16); gpJeu->ajouteEnnemi(42,32*16,4*16);
            gpJeu->ajouteEnnemi(42,33*16,21*16); gpJeu->ajouteEnnemi(42,44*16,31*16);
            gpJeu->ajouteEnnemi(42,48*16,8*16); gpJeu->ajouteEnnemi(42,54*16,22*16);
            gpJeu->ajouteEnnemi(42,54*16,49*16); gpJeu->ajouteEnnemi(42,55*16,39*16);
            gpJeu->ajouteEnnemi(42,66*16,21*16); gpJeu->ajouteEnnemi(42,69*16,55*16);
            gpJeu->ajouteEnnemi(42,73*16,33*16);
            gpJeu->ajouteEnnemi(61,207*16,48*16); gpJeu->ajouteEnnemi(61,217*16,48*16);
            gpJeu->ajouteEnnemi(61,204*16,34*16); gpJeu->ajouteEnnemi(61,266*16,48*16);
            gpJeu->ajouteEnnemi(61,286*16,48*16); gpJeu->ajouteEnnemi(61,266*16,3*16);
            gpJeu->ajouteEnnemi(61,276*16,11*16); gpJeu->ajouteEnnemi(61,286*16,3*16);
            gpJeu->ajouteEnnemi(61,306*16,29*16+8);
            //boss
            if(gpJoueur->getCoeur(12)==0) {
                gpJeu->ajouteEnnemi(128,278*16-3,31*16);
            }
            break;
        case 60 :
            //boss
            gpJeu->ajoutePnj(8,69*16+8,79*16,1343);
            gpJeu->ajouteEnnemi(141,68*16+4,76*16);
            gpJeu->ajouteEnnemi(136,62*16,77*16);
            gpJeu->ajouteEnnemi(136,76*16-8,77*16);
            gpJeu->getEnnemi()->getSuivant()->setVie(0);
            gpJeu->getEnnemi()->getSuivant()->getSuivant()->setVie(0);
            gpJeu->getEnnemi()->getSuivant()->getSuivant()->getSuivant()->setVie(0);
            gpJeu->ajoutePnj(15,145*16,0,1346);
            gpJeu->ajoutePnj(90,145*16,5*16,1347);
            //pnj
            gpJeu->ajoutePnj(111,67*16+2,137*16-10,1327);
            gpJeu->ajoutePnj(111,7*16+2,92*16-10,1333);
            gpJeu->ajoutePnj(111,27*16+2,92*16-10,1336);
            gpJeu->ajoutePnj(111,47*16+2,92*16-10,1337);
            gpJeu->ajoutePnj(111,67*16+2,17*16-10,1338);
            gpJeu->ajoutePnj(111,67*16+2,92*16-10,1339);
            gpJeu->ajoutePnj(111,87*16+2,92*16-10,1340);
            gpJeu->ajoutePnj(111,127*16+2,92*16-10,1341);
            //ennemis
            gpJeu->ajouteEnnemi(129,36*16,138*16-5); gpJeu->ajouteEnnemi(129,43*16,138*16-5);
            gpJeu->ajouteEnnemi(129,29*16+8,141*16-5);
            gpJeu->ajouteEnnemi(130,66*16,49*16); gpJeu->ajouteEnnemi(130,71*16,51*16);
            gpJeu->ajouteEnnemi(130,106*16,140*16); gpJeu->ajouteEnnemi(130,111*16,143*16);
            gpJeu->ajouteEnnemi(130,126*16,24*16); gpJeu->ajouteEnnemi(130,132*16,22*16);
            gpJeu->ajouteEnnemi(130,87*16,65*16); gpJeu->ajouteEnnemi(130,91*16,68*16);
            gpJeu->ajouteEnnemi(131,29*16+8,7*16-8); gpJeu->ajouteEnnemi(131,49*16+8,7*16-8);
            gpJeu->ajouteEnnemi(131,9*16+8,22*16-8); gpJeu->ajouteEnnemi(131,9*16+8,37*16-8);
            gpJeu->ajouteEnnemi(131,9*16+8,52*16-8); gpJeu->ajouteEnnemi(131,29*16+8,52*16-8);
            gpJeu->ajouteEnnemi(132,32*16,120*16+6); gpJeu->ajouteEnnemi(132,40*16,125*16+6);
            gpJeu->ajouteEnnemi(132,44*16,116*16+6);
            gpJeu->ajouteEnnemi(133,89*16+4,5*16+7); gpJeu->ajouteEnnemi(133,99*16+4,8*16+7);
            gpJeu->ajouteEnnemi(133,109*16+4,5*16+7);
            gpJeu->ajouteEnnemi(134,66*16+5,125*16+6); gpJeu->ajouteEnnemi(134,72*16+5,125*16+6);
            gpJeu->ajouteEnnemi(134,26*16+5,127*16+6); gpJeu->ajouteEnnemi(134,39*16+5,110*16+6);
            gpJeu->ajouteEnnemi(134,50*16+5,126*16+6); gpJeu->ajouteEnnemi(134,39*16+5,141*16+6);
            gpJeu->ajouteEnnemi(134,9*16+5,126*16+6); gpJeu->ajouteEnnemi(134,9*16+5,111*16+6);
            gpJeu->ajouteEnnemi(135,128*16,38*16); gpJeu->ajouteEnnemi(135,128*16,51*16);
            gpJeu->ajouteEnnemi(135,133*16,44*16);
            gpJeu->ajouteEnnemi(136,88*16,126*16); gpJeu->ajouteEnnemi(136,96*16,128*16);
            gpJeu->ajouteEnnemi(136,104*16,125*16); gpJeu->ajouteEnnemi(136,112*16,127*16);
            gpJeu->ajouteEnnemi(136,129*16,126*16); gpJeu->ajouteEnnemi(136,126*16,110*16);
            gpJeu->ajouteEnnemi(136,132*16,112*16);
            gpJeu->ajouteEnnemi(137,34*16,30*16+6); gpJeu->ajouteEnnemi(137,42*16,22*16+6);
            gpJeu->ajouteEnnemi(137,49*16,36*16+6);
            gpJeu->ajouteEnnemi(138,67*16,40*16); gpJeu->ajouteEnnemi(138,71*16,37*16);
            gpJeu->ajouteEnnemi(138,86*16,22*16); gpJeu->ajouteEnnemi(138,92*16,24*16);
            gpJeu->ajouteEnnemi(138,109*16,22*16); gpJeu->ajouteEnnemi(138,66*16,67*16);
            gpJeu->ajouteEnnemi(138,106*16,68*16);
            gpJeu->ajouteEnnemi(139,45*16,51*16); gpJeu->ajouteEnnemi(139,54*16,54*16);
            gpJeu->ajouteEnnemi(139,30*16,67*16); gpJeu->ajouteEnnemi(139,40*16,65*16);
            gpJeu->ajouteEnnemi(139,50*16,68*16);
            gpJeu->ajouteEnnemi(140,97*16,101*16); gpJeu->ajouteEnnemi(140,99*16,111*16);
            gpJeu->ajouteEnnemi(140,108*16,107*16); gpJeu->ajouteEnnemi(140,85*16,83*16);
            gpJeu->ajouteEnnemi(140,88*16,80*16); gpJeu->ajouteEnnemi(140,92*16,82*16);
            gpJeu->ajouteEnnemi(140,91*16,42*16); gpJeu->ajouteEnnemi(140,92*16,52*16);
            gpJeu->ajouteEnnemi(140,100*16,48*16); gpJeu->ajouteEnnemi(140,101*16,38*16);
            break;
        case 61 : break;
        case 62 :
            if (!gpJoueur->getEpee() && !gpJoueur->hasObjet(O_OCARINA)) 
                gpJeu->ajouteObjet(I_EPEE, 10*16, 3*16-8, 0, 1);
            gpJeu->ajouteEnnemi(20,14*16,7*16); setValeur(14*16,7*16,135,2);
            break;
        case 63 :
            if (!gpJoueur->getGemme(146)) gpJeu->ajouteObjet(I_GEMME,16*35,16*12,146,1);
            break;
        case 64 :
            //si pas encore été dans futur
            if (gpJoueur->getAvancement() < PORTAIL_F_UTILISE) {
                if (gpJoueur->getEpee()==2) gpJeu->ajoutePnj(15,12*16,8*16-8,329);
                else if (gpJoueur->hasObjet(O_CARTE)) gpJeu->ajoutePnj(15,9*16+8,8*16-8,326);
            }
            break;
        case 65 : gpJeu->ajoutePnj(16,9*16,4*16,331); break;
        case 66 : 
            if (!gpJoueur->getGemme(148)) gpJeu->ajouteObjet(I_GEMME,16*5,16*8,148,1);
            break;
        case 67 : 
            gpJeu->ajouteObjet(4,16*13,16*25-4,0,1);
            if (!gpJoueur->getGemme(149)) gpJeu->ajouteObjet(I_GEMME,16*15,16*25,149,1);
            break;
        case 68 :
            if (gpJoueur->getAvancement() >= GARS_MINE_AIDE) 
                gpJeu->ajoutePnj(78,37*16,22*16+6,339);
            gpJeu->ajouteEnnemi(88,36*16,23*16); setValeur(36*16,23*16,135,2);
            gpJeu->ajouteObjet(4,16*5,16*19-4,0,1); gpJeu->ajouteObjet(4,16*35,16*22-4,0,1);
            gpJeu->ajouteObjet(5,16*5,16*21,0,1);
            if (!gpJoueur->getGemme(150)) gpJeu->ajouteObjet(I_GEMME,16*43,16*16,150,1);
            if (!gpJoueur->getGemme(151)) gpJeu->ajouteObjet(I_GEMME,16*15,16*4,151,1);
            if (!gpJoueur->getGemme(152)) gpJeu->ajouteObjet(I_GEMME,16*4,16*35,152,1);
            break;
        case 69 : break;
        case 70 :
            if (gpJoueur->getAvancement() < PORTAIL_PRE_PRESENT_FERME) {
                if (gpJoueur->getTroc(M_POIVRON)>-1)
                    gpJeu->ajoutePnj(60,15*16,4*16,344);
                if (gpJoueur->getCoffre(3,29))
                    gpJeu->ajoutePnj(62,4*16,4*16,345);
                if (gpJoueur->getAvancement() >= SAGES_GROTTE) 
                    gpJeu->ajoutePnj(29,9*16+3,8*16,346);
            }
            break;
        case 71 : break;
        case 72 : break;
        case 73 : gpJeu->ajoutePnj(48,9*16,4*16,350); break;
        case 74 : gpJeu->ajoutePnj(79,9*16+4,5*16+4,360); break;
        case 75 : break;
        case 76 :
            gpJeu->ajouteObjet(4,16*3,16*6-4,0,1); gpJeu->ajouteObjet(4,16*3,16*7-4,0,1);
            gpJeu->ajouteObjet(7,16*3,16*8,0,1);
            gpJeu->ajouteObjet(5,16*9,16*4,0,1);
            gpJeu->ajouteObjet(6,16*11,16*4,0,1);
            if (!gpJoueur->getGemme(153)) gpJeu->ajouteObjet(I_GEMME,16*10,16*4,153,1);
            break;
        case 77 :
            gpJeu->ajouteObjet(4,16*9,16*2-4,0,1);
            gpJeu->ajouteObjet(7,16*11,16*2,0,1);
            if (!gpJoueur->getGemme(154)) gpJeu->ajouteObjet(I_GEMME,16*8,16*2,154,1);
            break;
        case 78 :
            gpJeu->ajouteObjet(4,16*86,16*6-4,0,1); gpJeu->ajouteObjet(4,16*93,16*6-4,0,1);
            gpJeu->ajouteObjet(7,16*86,16*8,0,1); gpJeu->ajouteObjet(7,16*93,16*8,0,1);
            if (!gpJoueur->getGemme(155)) gpJeu->ajouteObjet(I_GEMME,16*27,16*7,155,1);
            if (!gpJoueur->getGemme(156)) gpJeu->ajouteObjet(I_GEMME,16*32,16*7,156,1);
            break;
        case 79 :
            gpJeu->ajouteObjet(4,16*4,16*4-4,0,1); gpJeu->ajouteObjet(4,16*4,16*5-4,0,1);
            gpJeu->ajouteObjet(4,16*4,16*6-4,0,1);
            break;
        case 80 :
            gpJeu->ajoutePnj(18,9*16+8,3*16,362);
            gpJeu->ajoutePnj(41,14*16,6*16+8,363);
            gpJeu->ajoutePnj(57,5*16+5+8,18*16-2-8,364);
            gpJeu->ajoutePnj(52,12*16,12*16,365);
            gpJeu->ajouteObjet(4,16*4,16*27-4,0,1);
            gpJeu->ajouteObjet(2,16*5,16*27,0,1);
            gpJeu->ajouteObjet(1,16*4,16*4,0,1);
            if (!gpJoueur->getGemme(157)) gpJeu->ajouteObjet(I_GEMME,16*4,16*2,157,1);
            break;
        case 81 :
            gpJeu->ajouteObjet(5,16*7,16*5,0,1); contenu[7][6]=368;
            gpJeu->ajouteObjet(6,16*10,16*5,0,1); contenu[10][6]=370;
            gpJeu->ajoutePnj(10,13*16,9*16,367);
            break;
        case 82 :
            gpJeu->ajouteObjet(4,16*5,16*5,0,1); contenu[5][6]=376;
            gpJeu->ajouteObjet(7,16*8,16*5,0,1); contenu[8][6]=378;
            gpJeu->ajouteObjet(8,16*11,16*5,0,1); contenu[11][6]=380;
            gpJeu->ajoutePnj(12,13*16,9*16,367);
            break;
        case 83 :
            gpJeu->ajouteEnnemi(52,10*16,5*16);
            break;
        case 84 :
            if (gpJoueur->getAvancement()<PARLE_GARS_MINE_SALOON 
            || gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)==-1) {
                gpJeu->ajoutePnj(7,13*16,9*16,382);
            } else {
                gpJeu->ajoutePnj(7,13*16,9*16,367);
                if (!gpJoueur->hasBouteille(0) || !gpJoueur->hasBouteille(1)) {
                    gpJeu->ajouteObjet(I_BOUTEILLE,16*5,16*5,0,1); contenu[5][6]=390;
                }
                if (gpJoueur->hasObjet(O_BONUS_FORCE)<2) {
                    gpJeu->ajouteObjet(I_BONUS_FORCE,16*8,16*5,0,1); contenu[8][6]=395;
                }
                if (gpJoueur->hasObjet(O_BONUS_DEFENSE)<2) {
                    gpJeu->ajouteObjet(I_BONUS_DEFENSE,16*11,16*5,0,1); contenu[11][6]=400;
                }
                if (!gpJoueur->hasObjet(O_DETECTEUR)) {
                    gpJeu->ajouteObjet(I_DETECTEUR,16*14,16*5,0,1); contenu[14][6]=386;
                }
            }
            break;
        case 85 :
            gpJeu->ajoutePnj(17,9*16+8,6*16,409);
            gpJeu->ajouteObjet(4,16*5,16*12-4,0,1);
            gpJeu->ajouteObjet(1,16*6,16*12,0,1);
            if (!gpJoueur->getGemme(158)) gpJeu->ajouteObjet(I_GEMME,16*4,16*12,158,1);
            break;
        case 86 :
            gpJeu->ajoutePnj(43,9*16+8,4*16,424);
            break;
        case 87 :
            gpJeu->ajouteObjet(2,16*14,16*12,0,1); gpJeu->ajouteObjet(2,16*15,16*12,0,1);
            break;
        case 88 :
            if (!gpJoueur->getGemme(159)) gpJeu->ajouteObjet(I_GEMME,16*4,16*8,159,1);
            gpJeu->ajouteObjet(1,16*12,16*12,0,1);
            break;
        case 89 :
            gpJeu->ajoutePnj(20,14*16,11*16,433);
            break;
        case 90 :
            gpJeu->ajoutePnj(46,12*16,8*16,438);
            gpJeu->ajouteEnnemi(88,14*16,9*16); setValeur(14*16,9*16,4004,2);
            gpJeu->ajouteObjet(2,16*5,16*12,0,1); gpJeu->ajouteObjet(4,16*6,16*12-4,0,1);
            if (!gpJoueur->getGemme(163)) gpJeu->ajouteObjet(I_GEMME,16*4,16*12,163,1);
            break;
        case 91 :
            gpJeu->ajoutePnj(28,9*16,8*16,447);
            gpJeu->ajouteObjet(7,16*7,16*6-4,0,1); gpJeu->ajouteObjet(7,16*8,16*6-4,0,1);
            if (!gpJoueur->getGemme(164)) gpJeu->ajouteObjet(I_GEMME,16*6,16*6,164,1);
            break;
        case 92 :
            gpJeu->ajoutePnj(56,9*16,7*16,449);
            gpJeu->ajouteObjet(7,16*4,16*5-4,0,1); gpJeu->ajouteObjet(1,16*4,16*6,0,1);
            if (!gpJoueur->getGemme(165)) gpJeu->ajouteObjet(I_GEMME,16*4,16*4,165,1);
            break;
        case 93 :
            gpJeu->ajoutePnj(57,9*16+5,6*16,457,S);
            gpJeu->ajouteObjet(1,16*4,16*12,0,1);
            break;
        case 94 :
            gpJeu->ajoutePnj(80,9*16+8,5*16-9,458);
            break;
        case 95 :
            gpJeu->ajoutePnj(21,6*16+8,6*16,501);
            gpJeu->ajouteObjet(2,16*14,16*12,0,1);
            if (!gpJoueur->getGemme(166)) gpJeu->ajouteObjet(I_GEMME,16*15,16*12,166,1);
            break;
        case 96 :
            gpJeu->ajoutePnj(10,13*16,7*16,504);
            gpJeu->ajouteObjet(2,16*5,16*12,0,1); gpJeu->ajouteObjet(2,16*6,16*12,0,1);
            break;
        case 97 :
            gpJeu->ajoutePnj(70,7*16,8*16,512);
            gpJeu->ajouteObjet(1,16*13,16*12,0,1); gpJeu->ajouteObjet(4,16*15,16*12-4,0,1);
            break;
        case 98 :
            gpJeu->ajouteObjet(5,16*7,16*5,0,1); contenu[7][6]=368;
            gpJeu->ajouteObjet(6,16*10,16*5,0,1); contenu[10][6]=370;
            gpJeu->ajoutePnj(12,13*16,9*16,367);
            break;
        case 99 :
            gpJeu->ajouteObjet(4,16*5,16*5,0,1); contenu[5][6]=376;
            gpJeu->ajouteObjet(7,16*8,16*5,0,1); contenu[8][6]=378;
            gpJeu->ajouteObjet(8,16*11,16*5,0,1); contenu[11][6]=380;
            gpJeu->ajoutePnj(2,13*16,9*16,367);
            break;
        case 100 :
            gpJeu->ajoutePnj(41,11*16+8,8*16,521);
            break;
        case 101 :
            gpJeu->ajouteObjet(1,16*14,16*4,0,1);
            if (!gpJoueur->getGemme(167)) gpJeu->ajouteObjet(I_GEMME,16*15,16*4,167,1);
            break;
        case 102 :
            gpJeu->ajoutePnj(25,8*16,4*16+4,522); contenu[8][6]=522;
            if (gpJoueur->getAvancement()<GARS_MINE_AIDE)
                gpJeu->ajoutePnj(19,28*16,6*16+8,534);
            gpJeu->ajoutePnj(14,33*16,8*16+8,544);
            gpJeu->ajoutePnj(40,21*16,3*16+8,545);
            gpJeu->ajouteObjet(1,16*4,16*10,0,1);
            if (!gpJoueur->getGemme(168)) gpJeu->ajouteObjet(I_GEMME,16*4,16*12,168,1);
            break;
        case 103 :
            gpJeu->ajoutePnj(14,6*16,7*16,546);
            gpJeu->ajouteObjet(1,16*5,16*12,0,1);
            if (!gpJoueur->getGemme(169)) gpJeu->ajouteObjet(I_GEMME,16*4,16*12,169,1);
            break;
        case 104 :
            gpJeu->ajoutePnj(24,10*16,5*16,547);
            gpJeu->ajouteObjet(2,16*15,16*12,0,1);
            break;
        case 105 :
            gpJeu->ajoutePnj(51,5*16,6*16,548);
            break;
        case 106 :
            gpJeu->ajoutePnj(55,9*16,5*16,549);
            gpJeu->ajouteObjet(4,16*4,16*12-4,0,1);
            break;
        case 107 :
            gpJeu->ajouteObjet(5,16*7,16*5,0,1); contenu[7][6]=368;
            gpJeu->ajouteObjet(6,16*10,16*5,0,1); contenu[10][6]=370;
            gpJeu->ajoutePnj(41,13*16,9*16,367);
            break;
        case 108 :
            gpJeu->ajouteObjet(4,16*5,16*5,0,1); contenu[5][6]=376;
            gpJeu->ajouteObjet(7,16*8,16*5,0,1); contenu[8][6]=378;
            gpJeu->ajouteObjet(8,16*11,16*5,0,1); contenu[11][6]=380;
            gpJeu->ajoutePnj(45,13*16,9*16,367);
            break;
        case 109 :
            gpJeu->ajoutePnj(20,9*16+8,4*16+4,551); contenu[9][6]=551; contenu[10][6]=551;
            gpJeu->ajoutePnj(46,4*16+5,7*16,550);
            gpJeu->ajoutePnj(46,14*16+5,7*16,550);
            break;
        case 110 :
            gpJeu->ajoutePnj(22,7*16+8,6*16,567);
            gpJeu->ajouteObjet(5,16*14,16*12,0,1);
            gpJeu->ajouteObjet(4,16*15,16*12-4,0,1);
            break;
        case 111 :
            if (gpJoueur->nbEnnemis() < 87) gpJeu->ajoutePnj(8,9*16+8,4*16+8,589);
            break;
        case 112 :
            gpJeu->ajoutePnj(59,9*16+8,4*16+4,596); contenu[9][6]=596; contenu[10][6]=596;
            gpJeu->ajoutePnj(65,4*16+5,7*16,550);
            gpJeu->ajoutePnj(65,14*16+5,7*16,550);
            break;
        case 113 :
            if (gpJoueur->hasObjet(O_TROC2)>6) gpJeu->ajoutePnj(81,7*16,6*16,611);
            else gpJeu->ajoutePnj(64,7*16+8,6*16+10,612);
            gpJeu->ajouteObjet(2,16*5,16*12,0,1);
            if (!gpJoueur->getGemme(170)) gpJeu->ajouteObjet(I_GEMME,16*4,16*12,170,1);
            break;
        case 114 :
            if (gpJoueur->nbEnnemis() < 87) gpJeu->ajoutePnj(8,9*16+8,4*16+8,589);
            break;
        case 115 :
            if (gpJoueur->getTroc(M_POIVRON)<0) gpJeu->ajoutePnj(60,14*16,4*16,620);
            gpJeu->ajouteObjet(7,16*4,16*12-4,0,1); gpJeu->ajouteObjet(2,16*5,16*12,0,1);
            break;
        case 116 :
            if (gpJoueur->getAvancement() < SAGES_GROTTE
            || gpJoueur->getAvancement() >= PORTAIL_PRE_PRESENT_FERME)  
                gpJeu->ajoutePnj(29,9*16+3,5*16,625);
            gpJeu->ajouteObjet(4,16*14,16*12-4,0,1);
            if (!gpJoueur->getGemme(172)) gpJeu->ajouteObjet(I_GEMME,16*15,16*12,172,1);
            break;
        case 117 :
            gpJeu->ajouteObjet(5,16*7,16*5,0,1); contenu[7][6]=641;
            gpJeu->ajouteObjet(6,16*10,16*5,0,1); contenu[10][6]=643;
            gpJeu->ajoutePnj(30,13*16,9*16,367);
            break;
        case 118 :
            gpJeu->ajouteObjet(4,16*5,16*5,0,1); contenu[5][6]=645;
            gpJeu->ajouteObjet(7,16*8,16*5,0,1); contenu[8][6]=647;
            gpJeu->ajouteObjet(8,16*11,16*5,0,1); contenu[11][6]=649;
            gpJeu->ajoutePnj(50,13*16,9*16,367);
            break;
        case 119 :
            gpJeu->ajoutePnj(82,12*16-8,5*16,651);
            gpJeu->ajouteObjet(2,16*14,16*4,0,1); gpJeu->ajouteObjet(2,16*15,16*4,0,1);
            if (gpJoueur->getChargeCafe()==-1) gpJoueur->boostChargeCafe();
            gpJoueur->egaliseCafePaye();
            break;
        case 120 :
            gpJeu->ajoutePnj(31,9*16+8,6*16,674);
            gpJeu->ajouteObjet(1,16*15,16*4,0,1);
            if (!gpJoueur->getGemme(174)) gpJeu->ajouteObjet(I_GEMME,16*4,16*4,174,1);
            break;
        case 121 :
            gpJeu->ajoutePnj(53,9*16,5*16,682);
            break;
        case 122 :
            gpJeu->ajoutePnj(83,9*16,6*16,686);
            break;
        case 123 :
            gpJeu->ajoutePnj(27,9*16,6*16,694);
            gpJeu->ajouteObjet(1,16*15,16*12,0,1);
            break;
        case 124 :
            if (gpJoueur->nbEnnemis() < 87) gpJeu->ajoutePnj(8,9*16+8,4*16+8,589);
            break;
        case 125 :
            gpJeu->ajoutePnj(10,9*16+8,4*16+4,697); contenu[9][6]=697; contenu[10][6]=697;
            gpJeu->ajoutePnj(41,4*16+8,7*16,550);
            gpJeu->ajoutePnj(42,14*16+8,7*16,550);
            break;
        case 126 :
            gpJeu->ajouteObjet(4,16*15,16*4-4,0,1);
            gpJeu->ajoutePnj(21,7*16,6*16,712);
            break;
        case 127 :
            if (gpJoueur->hasObjet(O_TROC1)>2 && gpJoueur->hasObjet(O_TROC2)>3
            && gpJoueur->hasObjet(O_TROC3)>3) {
                if (gpJoueur->getEpee()) gpJeu->ajoutePnj(26,6*16+4,7*16-8,739);
                else gpJeu->ajoutePnj(26,6*16+4,7*16-8,746);
            }
            else gpJeu->ajoutePnj(38,6*16,6*16,719);
            gpJeu->ajouteObjet(4,16*5,16*12-4,0,1);
            if (!gpJoueur->getGemme(175)) gpJeu->ajouteObjet(I_GEMME,16*4,16*12,175,1);
            break;
        case 128 :
            gpJeu->ajouteObjet(5,16*7,16*5,0,1); contenu[7][6]=750;
            gpJeu->ajouteObjet(6,16*10,16*5,0,1); contenu[10][6]=752;
            gpJeu->ajoutePnj(20,13*16,9*16,367);
            break;
        case 129 :
            gpJeu->ajouteObjet(4,16*5,16*5,0,1); contenu[5][6]=754;
            gpJeu->ajouteObjet(7,16*8,16*5,0,1); contenu[8][6]=756;
            gpJeu->ajouteObjet(8,16*11,16*5,0,1); contenu[11][6]=758;
            gpJeu->ajoutePnj(2,13*16,9*16,367);
            break;
        case 130 :
            if (gpJeu->getJoueur()->getAvancement()<INFO_PASSE_OK) {
                gpJeu->ajoutePnj(10,12*16+8,5*16+8,175);
                gpJeu->ajouteEnnemi(52,4*16,9*16);
                gpJeu->ajouteEnnemi(52,14*16,10*16);
                gpJeu->ajouteEnnemi(52,6*16,11*16);
                gpJeu->ajouteEnnemi(52,9*16,6*16);
                gpJeu->ajouteEnnemi(52,15*16,6*16);
            }
            if (gpJoueur->getPieceMax()) gpJeu->ajouteObjet(2,16*14,16*12,0,1);
            if (!gpJoueur->getGemme(176)) gpJeu->ajouteObjet(I_GEMME,16*15,16*12,176,1);
            break;
        case 131 :
            gpJeu->ajoutePnj(84,12*16+8,5*16+8,761);
            gpJeu->ajouteObjet(4,16*15,16*12-4,0,1);
            break;
        case 132 :
            gpJeu->ajoutePnj(25,9*16+8,6*16,763);
            break;
        case 133 :
            if (gpJeu->getJoueur()->getAvancement()<INFO_PASSE_OK) {
                gpJeu->ajoutePnj(9,6*16+8,9*16,178);
                gpJeu->getPnj()->getSuivant()->setDirection(N);
            }
            break;
        case 134 :
            if (gpJeu->getJoueur()->getAvancement()<INFO_PASSE_OK) {
                gpJeu->ajoutePnj(51,14*16,9*16,177);
                gpJeu->ajoutePnj(55,9*16,5*16,773);
            }
            break;
        case 135 :
            if (gpJeu->getJoueur()->getAvancement()<INFO_PASSE_OK) 
                gpJeu->ajoutePnj(14,7*16,5*16,173);
            gpJeu->ajouteObjet(7,16*15,16*5-4,0,1);
            if (!gpJoueur->getGemme(177)) gpJeu->ajouteObjet(I_GEMME,16*15,16*4,177,1);
            break;
        case 136 :
            if (gpJeu->getJoueur()->getAvancement()<INFO_PASSE_OK) {
                gpJeu->ajoutePnj(90,5*16-2,6*16+5,775);
                gpJeu->ajoutePnj(35,6*16,18*16+10,174);
                gpJeu->ajoutePnj(23,12*16,17*16,176);
            }
            if (gpJeu->getJoueur()->nbCristaux()<3 || gpJeu->getJoueur()->hasObjet(O_TROC4)<6) {
                gpJeu->ajoutePnj(89,8*16-2,6*16+5,776);
                gpJeu->ajoutePnj(88,11*16,9*16+8,777);
                gpJeu->ajoutePnj(87,11*16,12*16+8,778);
                gpJeu->ajoutePnj(86,13*16,11*16+7,787);
                gpJeu->ajoutePnj(85,9*16,10*16+7,786);
            }
            gpJeu->ajoutePnj(18,10*16,3*16,894); contenu[10][6]=894;
            break;
        case 137 :
            if (gpJeu->getJoueur()->nbCristaux()>=3 && gpJeu->getJoueur()->hasObjet(O_TROC4)>=6
            && !gpJeu->getJoueur()->hasCristal(3)) {
                gpJeu->ajoutePnj(91,5*16+4,68*16,794);
                gpJeu->ajoutePnj(92,11*16+4,66*16,795);
                gpJeu->ajoutePnj(93,9*16+4,70*16,796);
                gpJeu->ajoutePnj(94,7*16+4,64*16,797);
                gpJeu->ajoutePnj(95,9*16+4,37*16,798);
                gpJeu->ajouteEnnemi(89,9*16+6,17*16);
                gpJeu->ajouteObjet(4,16*5,16*34-4,0,1);
                gpJeu->ajouteObjet(4,16*13,16*40-4,0,1);
                gpJeu->ajouteObjet(4,16*15,16*35-4,0,1);
                gpJeu->ajouteObjet(5,16*5,16*40,0,1);
                gpJeu->ajouteObjet(5,16*14,16*34,0,1);
            }
            if (gpJeu->getJoueur()->hasCristal(3)) {
                gpJeu->ajoutePnj(89,5*16-2,64*16+5,807);
                gpJeu->ajoutePnj(88,10*16,65*16+8,817);
                gpJeu->ajoutePnj(87,10*16,68*16+8,818);
                gpJeu->ajoutePnj(86,12*16,67*16+7,819);
                gpJeu->ajoutePnj(85,8*16,66*16+7,820);
            }
            break; //gemme 178 avec loups
        case 138 :
            gpJeu->ajoutePnj(96,10*16,5*16,821);
            break;
        case 139 :
            gpJeu->ajoutePnj(97,8*16+8,4*16+7,829);
            gpJeu->ajouteObjet(2,16*15,16*11,0,1);
            if (!gpJoueur->getGemme(179)) gpJeu->ajouteObjet(I_GEMME,16*15,16*12,179,1);
            break;
        case 140 :
            if (!gpJoueur->getCoffre(15,26)) {
                gpJeu->ajoutePnj(52,8*16,4*16+7,832);
                gpJeu->getPnj()->getSuivant()->setImmo(true);
            }
            gpJeu->ajouteObjet(4,16*34,16*4-4,0,1);
            gpJeu->ajouteObjet(5,16*34,16*6,0,1);
            gpJeu->ajouteObjet(7,16*34,16*7-4,0,1);
            if (!gpJoueur->getGemme(180)) gpJeu->ajouteObjet(I_GEMME,16*34,16*5,180,1);
            break;
        case 141 :
            gpJeu->ajoutePnj(17,8*16,4*16+7,841);
            gpJeu->ajouteObjet(1,16*5,16*4,0,1);
            if (!gpJoueur->getGemme(181)) gpJeu->ajouteObjet(I_GEMME,16*4,16*4,181,1);
            break;
        case 142 :
            gpJeu->ajouteObjet(4,16*5,16*5,0,1); contenu[5][6]=754;
            gpJeu->ajouteObjet(7,16*8,16*5,0,1); contenu[8][6]=756;
            gpJeu->ajouteObjet(8,16*11,16*5,0,1); contenu[11][6]=758;
            gpJeu->ajoutePnj(7,13*16,9*16,367);
            break;
        case 143 :
            gpJeu->ajouteObjet(5,16*7,16*5,0,1); contenu[7][6]=750;
            gpJeu->ajouteObjet(6,16*10,16*5,0,1); contenu[10][6]=752;
            gpJeu->ajoutePnj(20,13*16,9*16,367);
            break;
        case 144 :
            gpJeu->ajoutePnj(21,5*16,8*16,842);
            gpJeu->ajoutePnj(55,12*16,5*16,843);
            gpJeu->ajoutePnj(98,15*16,7*16,844);
            gpJeu->ajoutePnj(99,23*16,8*16,847);
            gpJeu->ajoutePnj(55,26*16,4*16,850);
            gpJeu->ajoutePnj(98,33*16,6*16,852);
            break;
        case 145 :
            gpJeu->ajoutePnj(24,11*16,5*16,853);
            gpJeu->ajouteObjet(1,16*14,16*12,0,1); gpJeu->ajouteObjet(4,16*15,16*12-4,0,1);
            break; //gemme 182 si donjon montagne passé fini
        case 146 :
            if (!gpJoueur->getCoffre(15,26)) gpJeu->ajoutePnj(45,11*16,4*16,857);
            break;
        case 147 : 
            gpJeu->ajoutePnj(54,11*16,5*16,865);
            gpJeu->ajouteObjet(7,16*5,16*12-4,0,1); gpJeu->ajouteObjet(4,16*6,16*12-4,0,1);
            if (!gpJoueur->getGemme(183)) gpJeu->ajouteObjet(I_GEMME,16*4,16*12,183,1);
            break;
        case 148 :
            gpJeu->ajouteObjet(5,16*7,16*5,0,1); contenu[7][6]=750;
            gpJeu->ajouteObjet(6,16*10,16*5,0,1); contenu[10][6]=752;
            gpJeu->ajoutePnj(10,13*16,9*16,367);
            break;
        case 149 :
            gpJeu->ajouteObjet(4,16*5,16*5,0,1); contenu[5][6]=754;
            gpJeu->ajouteObjet(7,16*8,16*5,0,1); contenu[8][6]=756;
            gpJeu->ajouteObjet(8,16*11,16*5,0,1); contenu[11][6]=758;
            gpJeu->ajoutePnj(35,13*16,9*16,367);
            break;
        case 150 :
            if (gpJoueur->getCoffre(15,27)<9) gpJeu->ajoutePnj(67,89*16+8,17*16,866);
            else gpJeu->ajoutePnj(67,209*16+8,4*16,866);
            gpJeu->ajouteEnnemi(90,66*16,21*16);
            break;
        case 151 : break;
        case 152 : break;
        case 153 : break;
        case 154 :
            if (gpJoueur->hasObjet(O_TROC1)<6) gpJeu->ajoutePnj(46,9*16+5,18*16,906);
            gpJeu->ajoutePnj(100,54*16,2*16,914);
            if (gpJeu->getJoueur()->hasCristal(3) && gpJoueur->getCoffre(15,28)==0) {
                gpJeu->ajoutePnj(90,54*16-2,17*16,922);
            }
            gpJeu->ajouteEnnemi(88,44*16+8,3*16);
            gpJeu->ajouteEnnemi(88,44*16+8,18*16);
            gpJeu->ajouteObjet(5,16*5,16*19,0,1);
            if (!gpJoueur->getGemme(184)) gpJeu->ajouteObjet(I_GEMME,16*4,16*19,184,1);
            break;
        case 155 :
            gpJeu->ajoutePnj(110,68*16+2+8,21*16,1074);
            if (gpJoueur->getAvancement()<MOT_DE_PASSE_CONNU) {
                gpJeu->ajoutePnj(109,89*16,91*16,1064);
            }
            if (gpJoueur->getAvancement()<MOT_DE_PASSE_DONNE) {
                gpJeu->ajoutePnj(65,68*16+5+4,31*16+8,1059);
                gpJeu->ajoutePnj(65,70*16+5-4,31*16+8,1059);
            } else {
                gpJeu->ajoutePnj(65,66*16+5+4,31*16+8,1059);
                gpJeu->ajoutePnj(65,72*16+5-4,31*16+8,1059);
            }
            if (gpJoueur->getAvancement()<MULTIPASSE_UTILISE) {
                gpJeu->ajoutePnj(65,129*16+5,31*16+8,1060);
            } else {
                gpJeu->ajoutePnj(65,127*16+5,31*16+8,1060);
            }
            if (!gpJoueur->getGemme(196)) gpJeu->ajouteObjet(I_GEMME,16*47,16*92,196,1);
            if (!gpJoueur->getGemme(147)) gpJeu->ajouteObjet(I_GEMME,16*144,16*34,147,1);
            if (!gpJoueur->getGemme(171)) gpJeu->ajouteObjet(I_GEMME,16*146,16*34,171,1);
            break;
        
            
        /*case 2 :
            if (!gpJoueur->getCoeur(15)) gpJeu->ajouteObjet(I_QUART_COEUR,115*16+8,32*16,15);
            if (!gpJoueur->getCoeur(16)) gpJeu->ajouteObjet(I_QUART_COEUR,14*16+8,22*16+8,16);
            gpJeu->ajouteEnnemi(53,108*16,45*16); gpJeu->ajouteEnnemi(53,70*16,50*16);
            gpJeu->ajouteEnnemi(53,70*16,22*16); gpJeu->ajouteEnnemi(53,20*16,38*16);
            gpJeu->ajouteEnnemi(53,11*16,9*16); gpJeu->ajouteEnnemi(53,70*16,6*16);
            gpJeu->ajouteEnnemi(53,35*16,15*16); gpJeu->ajouteEnnemi(53,105*16,6*16);
            gpJeu->ajouteEnnemi(54,114*16,12*16); gpJeu->ajouteEnnemi(54,114*16,25*16);
            gpJeu->ajouteEnnemi(54,112*16,36*16);
            gpJeu->ajouteEnnemi(8,21*16,9*16);
            if (monstre1==zone) gpJeu->ajouteEnnemi(19,50*16,49*16);
            if (monstre2==zone) gpJeu->ajouteEnnemi(24,50*16,49*16);
            if (monstre3==zone) gpJeu->ajouteEnnemi(35,50*16,49*16);
            break;
        case 9 :
            if (!gpJoueur->getCoeur(22)) gpJeu->ajouteObjet(I_QUART_COEUR,65*16+8,30*16,22);
            if (!gpJoueur->getCoeur(23)) gpJeu->ajouteObjet(I_QUART_COEUR,44*16,80*16,23);
            if (!gpJoueur->getCoeur(24)) gpJeu->ajouteObjet(I_QUART_COEUR,18*16,115*16,24);
            //armée de ganon
            if (gpJoueur->getAvancement()==67) {
                gpJeu->getAudio()->playSpecial(1);
                gpJeu->getStatut()->setJauge(true);
                gpJeu->ajouteEnnemi(46,65*16-18,30*16-19);gpJeu->ajouteEnnemi(46,60*16-18,41*16-19);
                gpJeu->ajouteEnnemi(46,27*16-18,72*16-19);gpJeu->ajouteEnnemi(46,23*16-18,82*16-19);
                gpJeu->ajouteEnnemi(46,28*16-18,95*16-19);gpJeu->ajouteEnnemi(46,42*16-18,101*16-19);
                gpJeu->ajouteEnnemi(46,55*16-18,98*16-19);gpJeu->ajouteEnnemi(46,66*16-18,87*16-19);
                gpJeu->ajouteEnnemi(46,53*16-18,81*16-19);gpJeu->ajouteEnnemi(46,41*16-18,74*16-19);
                gpJeu->ajouteEnnemi(46,67*16-18,72*16-19);gpJeu->ajouteEnnemi(46,59*16-18,60*16-19);
                gpJeu->ajouteEnnemi(47,21*16-18,53*16-19);gpJeu->ajouteEnnemi(47,32*16-18,53*16-19);
                gpJeu->ajouteEnnemi(47,18*16-18,42*16-19);gpJeu->ajouteEnnemi(47,9*16-18,36*16-19);
                gpJeu->ajouteEnnemi(47,15*16-18,16*16-19);gpJeu->ajouteEnnemi(47,34*16-18,11*16-19);
                gpJeu->ajouteEnnemi(47,14*16-18,25*16-19);
                gpJeu->ajouteEnnemi(48,52*16-7,9*16-3);
            }else{
                gpJeu->ajouteEnnemi(55,46*16,9*16);gpJeu->ajouteEnnemi(55,14*16,10*16);
                gpJeu->ajouteEnnemi(55,69*16,26*16);gpJeu->ajouteEnnemi(55,12*16,34*16);
                gpJeu->ajouteEnnemi(55,21*16,53*16);gpJeu->ajouteEnnemi(55,32*16,53*16);
                gpJeu->ajouteEnnemi(55,61*16,53*16);gpJeu->ajouteEnnemi(55,40*16,71*16);
                gpJeu->ajouteEnnemi(55,59*16,81*16);gpJeu->ajouteEnnemi(55,26*16,91*16);
                gpJeu->ajouteEnnemi(55,43*16,98*16);
                gpJeu->ajouteEnnemi(54,12*16,3*16);gpJeu->ajouteEnnemi(54,30*16,3*16);
                gpJeu->ajouteEnnemi(54,48*16,3*16);gpJeu->ajouteEnnemi(54,76*16,24*16);
                gpJeu->ajouteEnnemi(54,67*16,40*16);gpJeu->ajouteEnnemi(54,67*16,60*16);
                gpJeu->ajouteEnnemi(54,73*16,77*16);gpJeu->ajouteEnnemi(54,73*16,98*16);
                gpJeu->ajouteEnnemi(54,7*16,53*16);gpJeu->ajouteEnnemi(54,34*16,79*16);
                gpJeu->ajouteEnnemi(54,45*16,84*16);
                if (monstre1==zone) gpJeu->ajouteEnnemi(19,50*16,92*16);
                if (monstre2==zone) gpJeu->ajouteEnnemi(24,50*16,92*16);
                if (monstre3==zone) gpJeu->ajouteEnnemi(35,50*16,92*16);
            }
            break;
        case 12 :
            gpJeu->ajouteEnnemi(11,10*16,18*16);gpJeu->ajouteEnnemi(11,15*16,50*16);
            gpJeu->ajouteEnnemi(11,58*16,38*16);gpJeu->ajouteEnnemi(11,60*16,12*16);
            gpJeu->ajouteEnnemi(56,7*16,10*16);gpJeu->ajouteEnnemi(56,7*16,16*16);
            gpJeu->ajouteEnnemi(56,7*16,47*16);gpJeu->ajouteEnnemi(56,20*16,10*16);
            gpJeu->ajouteEnnemi(56,28*16,39*16);gpJeu->ajouteEnnemi(56,33*16,10*16);
            gpJeu->ajouteEnnemi(56,33*16,24*16);gpJeu->ajouteEnnemi(56,46*16,24*16);
            gpJeu->ajouteEnnemi(56,58*16,16*16);gpJeu->ajouteEnnemi(56,49*16,42*16);
            gpJeu->ajouteEnnemi(56,62*16,31*16);gpJeu->ajouteEnnemi(56,69*16,16*16);
            if (monstre1==zone) gpJeu->ajouteEnnemi(19,55*16,43*16);
            if (monstre2==zone) gpJeu->ajouteEnnemi(24,55*16,43*16);
            if (monstre3==zone) gpJeu->ajouteEnnemi(35,55*16,43*16);
            break;
        case 27 :
            //boss
            if(!gpJoueur->getCoeur(12)) gpJeu->ajouteEnnemi(76,28*16+2,47*16);
            //pièges
            gpJeu->ajouteEnnemi(49,22*16,47*16); setValeur(22*16,47*16,3728,2);
            gpJeu->ajouteEnnemi(49,37*16,47*16); setValeur(37*16,47*16,3728,2);
            //ennemi
            gpJeu->ajouteEnnemi(44,25*16,124*16-8);gpJeu->ajouteEnnemi(44,34*16,124*16-8);
            gpJeu->ajouteEnnemi(44,13*16,123*16-8);gpJeu->ajouteEnnemi(44,13*16,131*16-8);
            gpJeu->ajouteEnnemi(44,13*16,63*16-8);gpJeu->ajouteEnnemi(44,13*16,71*16-8);
            gpJeu->ajouteEnnemi(44,52*16,130*16-8);gpJeu->ajouteEnnemi(44,47*16,112*16-8);
            gpJeu->ajouteEnnemi(44,70*16,116*16-8);gpJeu->ajouteEnnemi(44,94*16,112*16-8);
            gpJeu->ajouteEnnemi(44,24*16,97*16-8);gpJeu->ajouteEnnemi(44,29*16,101*16-8);
            gpJeu->ajouteEnnemi(44,35*16,97*16-8);gpJeu->ajouteEnnemi(44,36*16-16,5*16-8);
            gpJeu->ajouteEnnemi(44,45*16-16,5*16-8);gpJeu->ajouteEnnemi(44,26*16-16,14*16-8);
            gpJeu->ajouteEnnemi(44,36*16-16,14*16-8);gpJeu->ajouteEnnemi(44,45*16-16,14*16-8);
            gpJeu->ajouteEnnemi(44,55*16-16,14*16-8);gpJeu->ajouteEnnemi(44,36*16-16,24*16-8);
            gpJeu->ajouteEnnemi(44,45*16-16,24*16-8);gpJeu->ajouteEnnemi(44,50*16-16,67*16-8);
            gpJeu->ajouteEnnemi(44,79*16-16,64*16-8);gpJeu->ajouteEnnemi(44,85*16-16,67*16-8);
            gpJeu->ajouteEnnemi(44,79*16-16,70*16-8);gpJeu->ajouteEnnemi(44,101*16-16,97*16-8);
            gpJeu->ajouteEnnemi(44,110*16-8,67*16-8);gpJeu->ajouteEnnemi(44,106*16-16,50*16-8);
            gpJeu->ajouteEnnemi(44,115*16-16,50*16-8);gpJeu->ajouteEnnemi(44,165*16-16,63*16-8);
            gpJeu->ajouteEnnemi(44,165*16-16,71*16-8);gpJeu->ajouteEnnemi(44,135*16-16,67*16-8);
            gpJeu->ajouteEnnemi(44,150*16-16,67*16-8);gpJeu->ajouteEnnemi(44,78*16-16,22*16-8);
            gpJeu->ajouteEnnemi(44,99*16-16,37*16-8);
            break;
        case 44 :
            gpJeu->ajouteObjet(4,16*4,16*12-4,0,1);gpJeu->ajouteObjet(4,16*5,16*12-4,0,1);
            if (gpJoueur->getAvancement()==1) gpJeu->ajoutePnj(47,9*16+8,6*16,245);
            if (gpJoueur->getAvancement()==2 && !gpJoueur->hasCristal(0)) gpJeu->ajoutePnj(47,9*16+8,6*16,250);
            if (gpJoueur->getAvancement()==2 && gpJoueur->hasCristal(0)) gpJeu->ajoutePnj(47,9*16+8,6*16,251);
            if (gpJoueur->getAvancement()>=3 && gpJoueur->getAvancement()<64) 
                gpJeu->ajoutePnj(47,9*16+8,6*16,250);
            if (gpJoueur->getAvancement()>=64 && gpJoueur->getAvancement()<=66) {
                gpJeu->ajoutePnj(47,7*16+8,5*16,272);
                gpJeu->ajoutePnj(15,11*16+8,5*16,259);
            }
            if (gpJoueur->getAvancement()==67) {
                gpJeu->ajoutePnj(47,7*16+8,5*16,274);
                gpJeu->ajoutePnj(15,11*16+8,5*16,273);
            }
            if (gpJoueur->getAvancement()==68) {
                gpJeu->ajoutePnj(47,7*16+8,5*16,274);
                gpJeu->ajoutePnj(15,11*16+8,5*16,276);
            }
            if (gpJoueur->getAvancement()==69) {
                gpJeu->ajoutePnj(47,7*16+8,5*16,274);
                gpJeu->ajoutePnj(15,11*16+8,5*16,282);
            }
            break;
        case 45 :
            gpJeu->ajoutePnj(32,9*16,5*16,283);
            break;
        case 46 :
            if (gpJoueur->hasObjet(O_SAC_BOMBES)) gpJeu->ajoutePnj(43,12*16,8*16,298);
            break;
        case 47 :
            if(gpJoueur->getCoeur(28)==0) {
                setValeur(6*16,6*16,303,1);
                setValeur(8*16,6*16,303,1);
                setValeur(10*16,6*16,303,1);
                setValeur(6*16,8*16,303,1);
                setValeur(8*16,8*16,303,1);
                setValeur(10*16,8*16,303,1);
                setValeur(6*16,10*16,303,1);
                setValeur(8*16,10*16,303,1);
                setValeur(10*16,10*16,303,1);
                contenu[6][6]=C_PAIE; contenu[8][6]=C_PAIE; contenu[10][6]=C_PAIE;
                contenu[6][8]=C_PAIE; contenu[8][8]=C_PAIE; contenu[10][8]=C_PAIE;
                contenu[6][10]=C_PAIE; contenu[8][10]=C_PAIE; contenu[10][10]=C_PAIE;
                gpJeu->ajoutePnj(20,14*16,11*16,300);
            }else {
                setValeur(6*16,6*16,304,1);
                setValeur(8*16,6*16,304,1);
                setValeur(10*16,6*16,304,1);
                setValeur(6*16,8*16,304,1);
                setValeur(8*16,8*16,304,1);
                setValeur(10*16,8*16,304,1);
                setValeur(6*16,10*16,304,1);
                setValeur(8*16,10*16,304,1);
                setValeur(10*16,10*16,304,1);
                gpJeu->ajoutePnj(20,14*16,11*16,299);
            }
            break;
        case 54 : gpJeu->ajoutePnj(52,9*16,5*16,343); break;
        case 55 :
            if (gpJeu->getJoueur()->getAvancement()==10 
            || gpJeu->getJoueur()->getAvancement()==11 
            || gpJeu->getJoueur()->getAvancement()>=15
            && gpJeu->getJoueur()->getAvancement()<=64) 
                gpJeu->ajoutePnj(25,29*16,6*16,50);
            else if (gpJeu->getJoueur()->getAvancement()==12) 
                gpJeu->ajoutePnj(25,29*16,6*16,349);
            else if (gpJeu->getJoueur()->getAvancement()==13) 
                gpJeu->ajoutePnj(25,29*16,6*16,354);
            else if (gpJeu->getJoueur()->getAvancement()==65 && !gpJoueur->hasMelodie(1)) 
                gpJeu->ajoutePnj(25,29*16,6*16,355);
            else gpJeu->ajoutePnj(25,29*16,6*16,358);
            if (gpJeu->getJoueur()->getAvancement()==65) gpJeu->ajoutePnj(45,9*16,6*16,359);
            gpJeu->ajouteObjet(1,16*17,16*12,0,1);gpJeu->ajouteObjet(1,16*22,16*12,0,1);
            break;
        case 56 : gpJeu->ajoutePnj(17,9*16+7,7*16,327); break;
        case 57 :
            gpJeu->ajouteObjet(1,16*14,16*12,0,1); gpJeu->ajouteObjet(4,16*15,16*12-4,0,1);
            //if (!gpJeu->getJoueur()->getOnilink() && gpJeu->getJoueur()->getAvancement()==64)
            gpJeu->ajoutePnj(9,12*16+8,8*16,80);
            break;
        case 58 :
            //if (!gpJeu->getJoueur()->getOnilink() && gpJeu->getJoueur()->getAvancement()==64)
            if (gpJoueur->hasObjet(O_OCARINA)) gpJeu->ajoutePnj(34,11*16,8*16-8-4,83);
            else gpJeu->ajoutePnj(34,11*16,8*16-8-4,82);
            break;*/
    }
}

void Monde::detRegion(int newZone) {
    region[0]=0; region[1]=0;
    region[2]=largeur;region[3]=hauteur;
    Joueur* gpJoueur = gpJeu->getJoueur();
    if (!gpJeu->isDehors()) {
        region[0]=((int)gpJoueur->getX()/320)*320; region[1]=((int)gpJoueur->getY()/240)*240;
        region[2]=region[0]+320;region[3]=region[1]+240;
        switch (newZone) {
            case 46 :
                if ((region[0]==0 || region[0]==40*16) 
                && (region[1]==0 || region[1]==15*16)) {
                    region[1]=0; region[3]=30*16;}
                if ((region[0]==20*16 || region[0]==40*16) && region[1]==45*16) {
                    region[0]=20*16; region[2]=60*16;}
                if ((region[0]==100*16 || region[0]==120*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=100*16; region[2]=140*16;
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==180*16 || region[0]==200*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=180*16; region[2]=220*16;
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==180*16 || region[0]==200*16) && region[1]==45*16) {
                    region[0]=180*16; region[2]=220*16;}
                if ((region[0]==260*16 || region[0]==280*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=260*16; region[2]=300*16;
                    region[1]=15*16; region[3]=45*16;}
                if (region[0]==240*16 && region[1]==30*16) gpJeu->getAudio()->stopSpecial();
                break;
            case 47 :
                if ((region[0]==120*16 || region[0]==140*16) && region[1]==75*16) {
                    region[0]=120*16; region[2]=160*16;}
                if (region[0]==240*16 && (region[1]==0 || region[1]==15*16)) {
                    region[1]=0*16; region[3]=30*16;}
                if ((region[0]==240*16 || region[0]==260*16) && region[1]==30*16) {
                    region[0]=240*16; region[2]=280*16;}
                if ((region[0]==260*16 || region[0]==280*16) 
                && (region[1]==0 || region[1]==15*16)) {
                    region[0]=260*16; region[2]=300*16;
                    region[1]=0; region[3]=30*16;}
                if ((region[0]==280*16 || region[0]==300*16) 
                && (region[1]==30*16 || region[1]==45*16)) {
                    region[0]=280*16; region[2]=320*16;
                    region[1]=30*16; region[3]=60*16;}
                if ((region[0]==280*16 || region[0]==300*16) 
                && (region[1]==60*16 || region[1]==75*16)) {
                    region[0]=280*16; region[2]=320*16;
                    region[1]=60*16; region[3]=90*16;}
                if (region[0]==340*16 && (region[1]==60*16 || region[1]==75*16)) {
                    region[1]=60*16; region[3]=90*16;}
                if (region[0]==340*16 && region[1]==45*16) gpJeu->getAudio()->stopSpecial();
                break;
            case 48 :
                if ((region[0]==0 || region[0]==20*16) && region[1]==15*16) {
                    region[0]=0; region[2]=40*16;}
                if ((region[0]==20*16 || region[0]==40*16) && region[1]==60*16) {
                    region[0]=20*16; region[2]=60*16;}
                if ((region[0]==100*16 || region[0]==120*16) && region[1]==45*16) {
                    region[0]=100*16; region[2]=140*16;}
                if ((region[0]==160*16 || region[0]==180*16) && region[1]==60*16) {
                    region[0]=160*16; region[2]=200*16;}
                if ((region[0]==240*16 || region[0]==260*16) 
                && (region[1]==15*16 || region[1]==45*16)) {
                    region[0]=240*16; region[2]=280*16;}
                if (region[0]==160*16 && (region[1]==15*16 || region[1]==30*16)) {
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==180*16 || region[0]==200*16 || region[0]==220*16) 
                && (region[1]==15*16 || region[1]==30*16 || region[1]==45*16)) {
                    region[0]=180*16; region[2]=240*16;
                    region[1]=15*16; region[3]=60*16;}
                if (region[0]==0 && region[1]==45*16) gpJeu->getAudio()->stopSpecial();
                break;
            case 49 :
                if ((region[0]==180*16 || region[0]==200*16) && region[1]==0) {
                    region[0]=190*16; region[2]=210*16;}
                if ((region[0]==60*16 || region[0]==80*16) 
                && (region[1]==30*16 || region[1]==45*16)) {
                    region[0]=60*16; region[2]=100*16;
                    region[1]=30*16; region[3]=60*16;}
                if ((region[0]==20*16 || region[0]==40*16) 
                && (region[1]==0 || region[1]==15*16 
                || region[1]==60*16 || region[1]==75*16)) {
                    region[0]=20*16; region[2]=60*16;}
                if ((region[0]==100*16 || region[0]==120*16) 
                && (region[1]==0 || region[1]==15*16 
                || region[1]==60*16 || region[1]==75*16)) {
                    region[0]=100*16; region[2]=140*16;}
                if ((region[0]==20*16 || region[0]==40*16
                || region[0]==100*16 || region[0]==120*16) 
                && (region[1]==0 || region[1]==15*16)) {
                    region[1]=0; region[3]=30*16;}
                if ((region[0]==20*16 || region[0]==40*16
                || region[0]==100*16 || region[0]==120*16) 
                && (region[1]==60*16 || region[1]==75*16)) {
                    region[1]=60*16; region[3]=90*16;}
                if (region[0]==220*16 && (region[1]==0 || region[1]==15*16)) {
                    region[1]=0; region[3]=30*16;}
                if ((region[0]==220*16 || region[0]==240*16) 
                && (region[1]==30*16 || region[1]==45*16)) {
                    region[0]=220*16; region[2]=260*16;}
                if ((region[0]==140*16 || region[0]==160*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=140*16; region[2]=180*16;
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==140*16 || region[0]==160*16) 
                && (region[1]==45*16 || region[1]==60*16)) {
                    region[0]=140*16; region[2]=180*16;
                    region[1]=45*16; region[3]=75*16;}
                if ((region[0]==180*16 || region[0]==200*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=180*16; region[2]=220*16;
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==180*16 || region[0]==200*16) 
                && (region[1]==45*16 || region[1]==75*16)) {
                    region[0]=180*16; region[2]=220*16;}
                if (region[0]==180*16 && region[1]==45*16) gpJeu->getAudio()->stopSpecial();
                break;
            case 50 :
                if ((region[0]==100*16 || region[0]==120*16 || region[0]==140*16) && region[1]==15*16) {
                    region[0]=100*16; region[2]=160*16;}
                if (region[0]==120*16 && (region[1]==60*16 || region[1]==75*16)) {
                    region[1]=60*16; region[3]=90*16;}
                if ((region[0]==180*16 || region[0]==200*16) 
                && (region[1]==0 || region[1]==15*16)) {
                    region[0]=180*16; region[2]=220*16;
                    region[1]=0; region[3]=30*16;}
                if ((region[0]==180*16 || region[0]==200*16) 
                && (region[1]==75*16 || region[1]==90*16)) {
                    region[0]=180*16; region[2]=220*16;
                    region[1]=75*16; region[3]=105*16;}
                if ((region[0]==280*16 || region[0]==300*16) 
                && (region[1]==0 || region[1]==15*16)) {
                    region[0]=280*16; region[2]=320*16;
                    region[1]=0; region[3]=30*16;}
                if ((region[0]==280*16 || region[0]==300*16) 
                && (region[1]==75*16 || region[1]==90*16)) {
                    region[0]=280*16; region[2]=320*16;
                    region[1]=75*16; region[3]=105*16;}
                if ((region[0]==200*16 || region[0]==220*16) && region[1]==45*16) {
                    region[0]=200*16; region[2]=240*16;}
                if (region[0]==240*16 && region[1]==30*16) gpJeu->getAudio()->stopSpecial();
                break;
            case 51 :
                if ((region[0]==80*16 || region[0]==160*16) 
                && (region[1]==30*16 || region[1]==45*16)) {
                    region[1]=30*16; region[3]=60*16;}
                if ((region[0]==180*16 || region[0]==200*16) 
                && (region[1]==0 || region[1]==15*16)) {
                    region[0]=180*16; region[2]=220*16;
                    region[1]=0; region[3]=30*16;}
                if ((region[0]==180*16 || region[0]==200*16) 
                && (region[1]==75*16 || region[1]==90*16)) {
                    region[0]=180*16; region[2]=220*16;
                    region[1]=75*16; region[3]=105*16;}
                if ((region[0]==280*16 || region[0]==300*16) 
                && (region[1]==0 || region[1]==15*16)) {
                    region[0]=280*16; region[2]=320*16;
                    region[1]=0; region[3]=30*16;}
                if ((region[0]==280*16 || region[0]==300*16) 
                && (region[1]==75*16 || region[1]==90*16)) {
                    region[0]=280*16; region[2]=320*16;
                    region[1]=75*16; region[3]=105*16;}
                if ((region[0]==220*16 || region[0]==240*16 || region[0]==260*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=230*16; region[2]=270*16;
                    region[1]=15*16; region[3]=45*16;}
                if (region[0]==80*16 && region[1]==60*16) passage(89,60,0);
                if (region[0]==160*16 && region[1]==60*16) passage(169,60,0);
                if (region[0]==240*16 && region[1]==45*16) gpJeu->getAudio()->stopSpecial();
                break;
            case 52 :
                if (region[0]==120*16 && (region[1]==60*16 || region[1]==75*16)) {
                    region[1]=60*16; region[3]=90*16;}
                if (region[0]==240*16 && region[1]==45*16) gpJeu->getAudio()->stopSpecial();
                break;
            case 53 :
                if ((region[0]==20*16 || region[0]==40*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=20*16; region[2]=60*16;
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==100*16 || region[0]==120*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=100*16; region[2]=140*16;
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==180*16 || region[0]==200*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=180*16; region[2]=220*16;
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==20*16 || region[0]==40*16) 
                && (region[1]==75*16 || region[1]==90*16)) {
                    region[0]=20*16; region[2]=60*16;
                    region[1]=75*16; region[3]=105*16;}
                if ((region[0]==100*16 || region[0]==120*16) 
                && (region[1]==75*16 || region[1]==90*16)) {
                    region[0]=100*16; region[2]=140*16;
                    region[1]=75*16; region[3]=105*16;}
                if (region[0]==180*16 && region[1]==15*16) gpJeu->getAudio()->stopSpecial();
                break;
            case 54 :
                if ((region[0]==20*16 || region[0]==40*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=20*16; region[2]=60*16;
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==20*16 || region[0]==40*16) 
                && (region[1]==60*16 || region[1]==75*16)) {
                    region[0]=20*16; region[2]=60*16;
                    region[1]=60*16; region[3]=90*16;}
                if ((region[0]==60*16 || region[0]==80*16) 
                && (region[1]==30*16 || region[1]==45*16)) {
                    region[0]=60*16; region[2]=100*16;
                    region[1]=30*16; region[3]=60*16;}
                if ((region[0]==100*16 || region[0]==120*16) 
                && (region[1]==60*16 || region[1]==75*16)) {
                    region[0]=100*16; region[2]=140*16;
                    region[1]=60*16; region[3]=90*16;}
                if ((region[0]==140*16 || region[0]==160*16) 
                && (region[1]==60*16 || region[1]==75*16)) {
                    region[0]=140*16; region[2]=180*16;
                    region[1]=60*16; region[3]=90*16;}
                if ((region[0]==180*16 || region[0]==200*16) 
                && (region[1]==30*16 || region[1]==45*16)) {
                    region[0]=180*16; region[2]=220*16;
                    region[1]=30*16; region[3]=60*16;}
                if ((region[0]==120*16 || region[0]==240*16) 
                && (region[1]==0 || region[1]==15*16)) {
                    region[1]=0; region[3]=30*16;}
                if (region[0]==140*16 && (region[1]==15*16 || region[1]==30*16)) {
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==60*16 || region[0]==80*16) && region[1]==15*16) {
                    region[0]=70*16; region[2]=90*16;}
                if ((region[0]==180*16 || region[0]==200*16) 
                && (region[1]==0 || region[1]==15*16)) {
                    region[0]=190*16; region[2]=210*16;}
                if (region[0]==180*16 && region[1]==30*16) gpJeu->getAudio()->stopSpecial();
                break;
            case 55 :
                if ((region[0]==40*16 || region[0]==60*16 || region[0]==80*16) 
                && (region[1]==15*16 || region[1]==30*16  || region[1]==45*16)) {
                    region[0]=40*16; region[2]=100*16;
                    region[1]=15*16; region[3]=60*16;}
                if ((region[0]==40*16 || region[0]==60*16 || region[0]==80*16) 
                && (region[1]==90*16 || region[1]==105*16 || region[1]==120*16)) {
                    region[0]=40*16; region[2]=100*16;
                    region[1]=90*16; region[3]=135*16;}
                if ((region[0]==40*16 || region[0]==60*16 || region[0]==80*16) 
                && (region[1]==165*16 || region[1]==180*16 || region[1]==195*16)) {
                    region[0]=40*16; region[2]=100*16;
                    region[1]=165*16; region[3]=210*16;}
                if ((region[0]==0 || region[0]==20*16) 
                && (region[1]==0 || region[1]==15*16)) {
                    region[0]=0; region[2]=40*16;
                    region[1]=0; region[3]=30*16;}
                if ((region[0]==0 || region[0]==20*16) 
                && (region[1]==45*16 || region[1]==60*16)) {
                    region[0]=0; region[2]=40*16;
                    region[1]=45*16; region[3]=75*16;}
                if ((region[0]==100*16 || region[0]==120*16) 
                && (region[1]==0 || region[1]==15*16)) {
                    region[0]=100*16; region[2]=140*16;
                    region[1]=0; region[3]=30*16;}
                if ((region[0]==100*16 || region[0]==120*16) 
                && (region[1]==45*16 || region[1]==60*16)) {
                    region[0]=100*16; region[2]=140*16;
                    region[1]=45*16; region[3]=75*16;}
                if ((region[0]==0 || region[0]==20*16) 
                && (region[1]==150*16 || region[1]==165*16)) {
                    region[0]=0; region[2]=40*16;
                    region[1]=150*16; region[3]=180*16;}
                if ((region[0]==0 || region[0]==20*16) 
                && (region[1]==195*16 || region[1]==210*16)) {
                    region[0]=0; region[2]=40*16;
                    region[1]=195*16; region[3]=225*16;}
                if ((region[0]==100*16 || region[0]==120*16) 
                && (region[1]==150*16 || region[1]==165*16)) {
                    region[0]=100*16; region[2]=140*16;
                    region[1]=150*16; region[3]=180*16;}
                if ((region[0]==100*16 || region[0]==120*16) 
                && (region[1]==195*16 || region[1]==210*16)) {
                    region[0]=100*16; region[2]=140*16;
                    region[1]=195*16; region[3]=225*16;}
                if ((region[0]==0 || region[0]==120*16) 
                && (region[1]==90*16 || region[1]==105*16)) {
                    region[1]=90*16; region[3]=120*16;}
                if (region[0]==60*16 && (region[1]==60*16 || region[1]==210*16)) 
                    gpJeu->getAudio()->stopSpecial();
                break;
            case 57 :
                if ((region[0]==0 || region[0]==20*16) && region[1]==225*16) {
                    region[0]=0; region[2]=40*16;}
                if ((region[0]==100*16 || region[0]==120*16) && region[1]==150*16) {
                    region[0]=100*16; region[2]=140*16;}
                if ((region[0]==120*16 || region[0]==140*16) && region[1]==165*16) {
                    region[0]=120*16; region[2]=160*16;}
                if (region[0]==60*16 && region[1]==30*16) 
                    gpJeu->getAudio()->stopSpecial();
            case 56 :
                if ((region[0]==140*16 || region[0]==180*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[1]=15*16; region[3]=45*16;}
                if (region[0]==160*16 && region[1]==30*16) 
                    gpJeu->getAudio()->stopSpecial();
            case 155 :
                if ((region[0]==0 || region[0]==20*16) 
                && (region[1]==30*16 || region[1]==45*16)) {
                    region[0]=0; region[2]=40*16;
                    region[1]=30*16; region[3]=60*16;}
                if ((region[0]==0 || region[0]==20*16) 
                && (region[1]==0 || region[1]==15*16 || region[1]==90*16)) {
                    region[0]=0; region[2]=40*16;}
                if ((region[0]==100*16 || region[0]==120*16) && region[1]==45*16) {
                    region[0]=100*16; region[2]=140*16;}
                if ((region[0]==0 || region[0]==120*16) 
                && (region[1]==60*16 || region[1]==75*16)) {
                    region[1]=60*16; region[3]=90*16;}
                if (region[0]==120*16 && (region[1]==0 || region[1]==15*16)) {
                    region[1]=0; region[3]=30*16;}
                if (region[0]==60*16 && (region[1]==30*16 || region[1]==45*16)) {
                    region[1]=30*16; region[3]=60*16;}
                break;
            case 58 :
                if (region[0]==0 && (region[1]==0 || region[1]==15*16)) {
                    region[1]=0; region[3]=30*16;}
                if (region[0]==60*16 && (region[1]==60*16 || region[1]==75*16)) {
                    region[1]=60*16; region[3]=90*16;}
                if ((region[0]==0 || region[0]==20*16) && region[1]==90*16) {
                    region[0]=0; region[2]=40*16;}
                if ((region[0]==80*16 || region[0]==100*16) && region[1]==90*16) {
                    region[0]=80*16; region[2]=120*16;}
                if (region[0]==60*16 && region[1]==45*16) gpJeu->getAudio()->stopSpecial();
                gpJeu->getJoueur()->setCoffre(12,13,0);
                break;
            case 59 :
                if ((region[0]==20*16 || region[0]==40*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=20*16; region[2]=60*16;
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==100*16 || region[0]==120*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=100*16; region[2]=140*16;
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==180*16 || region[0]==200*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=180*16; region[2]=220*16;
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==0 || region[0]==60*16 || region[0]==80*16 || region[0]==140*16 
                || region[0]==160*16 || region[0]==220*16 || region[0]==240*16 || region[0]==300*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==20*16 || region[0]==40*16) && region[1]==0) {
                    region[0]=20*16; region[2]=60*16;}
                if ((region[0]==40*16 || region[0]==60*16) && region[1]==45*16) {
                    region[0]=40*16; region[2]=80*16;}
                if ((region[0]==100*16 || region[0]==120*16) && region[1]==0) {
                    region[0]=100*16; region[2]=140*16;}
                if ((region[0]==120*16 || region[0]==140*16) && region[1]==45*16) {
                    region[0]=120*16; region[2]=160*16;}
                if ((region[0]==160*16 || region[0]==180*16) && region[1]==45*16) {
                    region[0]=160*16; region[2]=200*16;}
                if ((region[0]==180*16 || region[0]==200*16) && region[1]==0) {
                    region[0]=180*16; region[2]=220*16;}
                if ((region[0]==200*16 || region[0]==220*16) && region[1]==45*16) {
                    region[0]=200*16; region[2]=240*16;}
                if ((region[0]==260*16 || region[0]==280*16) 
                && (region[1]==0 || region[1]==45*16)) {
                    region[0]=260*16; region[2]=300*16;}
                if ((region[0]==260*16 || region[0]==280*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=270*16; region[2]=290*16;}
                if (region[0]==260*16 && region[1]==45*16) gpJeu->getAudio()->stopSpecial();
                break;
            case 60 :
                if ((region[0]==20*16 || region[0]==40*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[0]=20*16; region[2]=60*16;
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==20*16 || region[0]==40*16) 
                && (region[1]==105*16 || region[1]==120*16)) {
                    region[0]=20*16; region[2]=60*16;
                    region[1]=105*16; region[3]=135*16;}
                if ((region[0]==80*16 || region[0]==100*16) 
                && (region[1]==30*16 || region[1]==45*16)) {
                    region[0]=80*16; region[2]=120*16;
                    region[1]=30*16; region[3]=60*16;}
                if ((region[0]==80*16 || region[0]==100*16) 
                && (region[1]==90*16 || region[1]==105*16)) {
                    region[0]=80*16; region[2]=120*16;
                    region[1]=90*16; region[3]=120*16;}
                if ((region[0]==20*16 || region[0]==40*16) 
                && (region[1]==60*16 || region[1]==135*16)) {
                    region[0]=20*16; region[2]=60*16;}
                if ((region[0]==80*16 || region[0]==100*16) 
                && (region[1]==0 || region[1]==120*16)) {
                    region[0]=80*16; region[2]=120*16;}
                if (region[0]==60*16 && (region[1]==90*16 || region[1]==105*16)) {
                    region[1]=90*16; region[3]=120*16;}
                if (region[0]==120*16 && (region[1]==30*16 || region[1]==45*16)) {
                    region[1]=30*16; region[3]=60*16;}
                if (region[0]==60*16 && region[1]==90*16) gpJeu->getAudio()->stopSpecial();
                break;
            case 63 :
                if (region[0]==0 || region[0]==20*16 || region[0]==40*16) {
                    region[0]=0; region[2]=60*16;}
                break;
            case 68 :
                if ((region[0]==20*16 || region[0]==40*16) 
                && (region[1]==0 || region[1]==15*16)) {
                    region[0]=20*16; region[2]=60*16;
                    region[1]=0; region[3]=30*16;}
                if ((region[0]==0 || region[0]==80*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[1]=15*16; region[3]=45*16;}
                if ((region[0]==20*16 || region[0]==40*16) && region[1]==30*16) {
                    region[0]=30*16; region[2]=50*16;}
                break;
            case 78 :
                if (region[0]==0 || region[0]==20*16 || region[0]==40*16) {
                    region[0]=0; region[2]=60*16;}
                if (region[0]==60*16 || region[0]==80*16 || region[0]==100*16) {
                    region[0]=60*16; region[2]=120*16;}
                break;
            case 80 :
                region[1]=0; region[3]=30*16;
                break;
            case 102 :
                region[0]=0; region[2]=40*16;
                break;
            case 136 :
                region[1]=0; region[3]=30*16;
                break;
            case 137 :
                if (region[1]==30*16) gpJeu->getAudio()->stopSpecial();
                break;
            case 144 :
                region[0]=0; region[2]=40*16;
                break;
            case 150 :
                if ((region[0]==20*16 || region[0]==80*16) 
                && (region[1]==15*16 || region[1]==30*16)) {
                    region[1]=15*16; region[3]=45*16; }
                break;
            case 151 :
            case 152 :
            case 153 :
                if (region[0]==20*16 && (region[1]==15*16 || region[1]==30*16)) {
                    region[1]=15*16; region[3]=45*16; }
                break;
        }
        if (newZone<61 && gpJeu->isDonjon()) {
            for (int i = region[0]; i < region[2]; i+=320/2)
                for (int j = region[1]; j < region[3]; j+=240) {
                    gpJoueur->setExplore(newZone-46,i/320, j/240);
                }
            gpJoueur->setExplore(newZone-46,(region[2]-1)/320, (region[3]-1)/240);
        }
        
        if (charge) return;
        gpJeu->replace();
        gpJeu->testAnim();
        if (newZone==56 && region[0]==160*16 && region[1]==15*16) {
            if (gpJoueur->getAvancement() < SPEECH_AGAHNIM) gpJeu->ecrit(973);
        }
        if (newZone==56 && region[0]==160*16 && region[1]==0 && gpJoueur->getCoeur(10)) {
            if (gpJoueur->getEpee() < 5) {
                gpJeu->getAudio()->playSpecial(4);
                gpJeu->ecrit(981);
            }
        }
        if (newZone==57 && region[0]==160*16 && region[1]==15*16) {
            if (gpJoueur->getAvancement() < SPEECH_GANON) gpJeu->ecrit(1099);
        }
        if (newZone==57 && region[0]==160*16 && region[1]==0) {
            if (gpJoueur->getAvancement() < SPEECH_GANONDORF) gpJeu->ecrit(1100);
            else gpJeu->ecrit(1113);
        }
        if (newZone==68 && region[0]==20*16 && region[1]==0) {
            wagon(gpJoueur->getPosWagon(), true);
            if (gpJoueur->getAvancement() == GARS_MINE_AIDE) gpJeu->ecrit(339);
        }
    }
    
    //if (newZone == 1 && gpJoueur->getAvancement() == 0) gpJeu->ecrit(172);
    //if (newZone == 29 && gpJoueur->getTutoriel() == 0 && region[1]==240) gpJeu->ecrit(197);
    if (newZone == 9 && gpJoueur->getCoffre(15,28) == 1) {
        gpJeu->ecrit(924); gpJoueur->setDirection(E);}
    if (newZone == 57 && region[0]==320*3 && region[1]==240 
    && gpJoueur->getAvancement() < PARLE_ZELDA_PALAIS) {
        gpJeu->getAudio()->playSpecial(25); gpJeu->ecrit(1014);}
    if (newZone == 57 && region[0]==320*4 && region[1]==240 
    && !gpJoueur->getRubisMax()) gpJeu->ecrit(1034);
    if (newZone == 57 && region[0]==320*4 && region[1]==0 
    && !gpJoueur->getRubisMax()) gpJeu->ecrit(1035);
    if (newZone == 70 && gpJoueur->getAvancement() == SAGES_GROTTE) gpJeu->ecrit(343);
    if (newZone == 137 && gpJoueur->hasCristal(3) 
    && gpJoueur->getAvancement() < GANON_CAPTURE) gpJeu->ecrit(801);
    if (newZone == 155 && region[0]==320*3 && region[1]==240 
    && gpJoueur->getAvancement() < MULTIPASS) {
        gpJeu->getAudio()->playSpecial(4); gpJeu->ecrit(1071);}
    if (newZone == 19 && gpJoueur->getEpee() == 5 
    && gpJoueur->getAvancement() < TELE_ZELDA) gpJeu->ecrit(1002);
}

//replace crânes
void Monde::replace() {
    switch (gpJeu->getZone()) {
        case 46 :
            setValeur(4*16,32*16,30,1); setValeur(4*16,42*16,30,1); setValeur(15*16,32*16,30,1);
            setValeur(15*16,42*16,30,1); setValeur(24*16,34*16,30,1); setValeur(24*16,40*16,30,1);
            setValeur(44*16,2*16,30,1); setValeur(45*16,2*16,30,1); setValeur(46*16,2*16,30,1);
            setValeur(47*16,2*16,30,1); setValeur(120*16,17*16,30,1); setValeur(121*16,17*16,30,1);
            setValeur(122*16,17*16,30,1); setValeur(125*16,34*16,30,1); setValeur(125*16,35*16,30,1);
            setValeur(165*16,55*16,30,1); setValeur(166*16,55*16,30,1); setValeur(167*16,55*16,30,1);
            setValeur(201*16,19*16,30,1); setValeur(202*16,19*16,30,1); setValeur(203*16,19*16,30,1);
            setValeur(206*16,47*16,30,1); setValeur(207*16,47*16,30,1); setValeur(213*16,47*16,30,1);
            setValeur(244*16,40*16,30,1); setValeur(245*16,40*16,30,1); setValeur(246*16,40*16,30,1);
            setValeur(279*16,19*16,30,1); setValeur(280*16,19*16,30,1); setValeur(295*16,28*16,30,1);
            setValeur(295*16,29*16,30,1); setValeur(295*16,30*16,30,1); setValeur(295*16,31*16,30,1);
            setValeur(315*16,32*16,30,1); setValeur(315*16,33*16,30,1); setValeur(315*16,34*16,30,1);
            setValeur(305*16,53*16,30,1); setValeur(342*16,7*16,30,1); setValeur(345*16,7*16,30,1);
            setValeur(348*16,7*16,30,1); setValeur(351*16,7*16,30,1); setValeur(354*16,7*16,30,1);
            setValeur(357*16,7*16,30,1); setValeur(246*16,19*16,30,1); setValeur(253*16,19*16,30,1);
            break;
        case 47 :
            setValeur(204*16,49*16,30,1); setValeur(204*16,55*16,30,1); setValeur(244*16,49*16,30,1);
            setValeur(244*16,49*16,30,1); setValeur(244*16,78*16,30,1); setValeur(244*16,86*16,30,1);
            setValeur(257*16,49*16,30,1); setValeur(264*16,63*16,30,1); setValeur(264*16,71*16,30,1);
            setValeur(286*16,4*16,30,1); setValeur(287*16,4*16,30,1); setValeur(288*16,4*16,30,1);
            setValeur(288*16,53*16,30,1); setValeur(289*16,53*16,30,1); setValeur(296*16,55*16,30,1);
            setValeur(297*16,55*16,30,1); setValeur(301*16,55*16,30,1); setValeur(308*16,40*16,30,1);
            setValeur(309*16,40*16,30,1); setValeur(323*16,47*16,30,1); setValeur(336*16,47*16,30,1);
            setValeur(324*16,78*16,30,1); setValeur(335*16,78*16,30,1); setValeur(337*16,62*16,30,1);
            setValeur(345*16,55*16,30,1); setValeur(354*16,55*16,30,1);
            break;
        case 48 :
            setValeur(6*16,55*16,30,1); setValeur(13*16,55*16,30,1); setValeur(15*16,62*16,30,1);
            setValeur(15*16,72*16,30,1); setValeur(27*16,70*16,30,1); setValeur(28*16,70*16,30,1);
            setValeur(29*16,70*16,30,1); setValeur(26*16,6*16,30,1); setValeur(26*16,7*16,30,1);
            setValeur(26*16,8*16,30,1); setValeur(46*16,19*16,30,1); setValeur(75*16,57*16,30,1);
            setValeur(122*16,25*16,30,1); setValeur(124*16,27*16,30,1); setValeur(135*16,27*16,30,1);
            setValeur(137*16,25*16,30,1); setValeur(124*16,49*16,30,1); setValeur(135*16,49*16,30,1);
            setValeur(155*16,49*16,30,1); setValeur(174*16,10*16,30,1); setValeur(175*16,10*16,30,1);
            setValeur(190*16,55*16,30,1); setValeur(191*16,55*16,30,1); setValeur(216*16,19*16,30,1);
            setValeur(216*16,20*16,30,1); setValeur(215*16,57*16,30,1); setValeur(233*16,17*16,30,1);
            setValeur(233*16,57*16,30,1); setValeur(254*16,70*16,30,1); setValeur(255*16,19*16,30,1);
            setValeur(264*16,25*16,30,1); setValeur(264*16,49*16,30,1); setValeur(264*16,55*16,30,1);
            setValeur(289*16,6*16,30,1); setValeur(290*16,6*16,30,1);
            break;
        case 49 :
            setValeur(32*16,25*16,31,1); setValeur(29*16,72*16,31,1); setValeur(32*16,73*16,31,1);
            setValeur(33*16,72*16,31,1); setValeur(33*16,66*16,31,1); setValeur(62*16,49*16,31,1);
            setValeur(75*16,62*16,31,1); setValeur(76*16,62*16,31,1); setValeur(77*16,40*16,31,1);
            setValeur(80*16,40*16,31,1); setValeur(87*16,50*16,31,1); setValeur(92*16,32*16,31,1);
            setValeur(95*16,41*16,31,1); setValeur(104*16,12*16,31,1); setValeur(104*16,13*16,31,1);
            setValeur(106*16,74*16,31,1); setValeur(112*16,24*16,31,1); setValeur(121*16,79*16,31,1);
            setValeur(124*16,70*16,31,1); setValeur(125*16,21*16,31,1); setValeur(146*16,4*16,31,1);
            setValeur(145*16,25*16,31,1); setValeur(153*16,38*16,31,1); setValeur(175*16,39*16,31,1);
            setValeur(145*16,85*16,31,1); setValeur(162*16,85*16,31,1); setValeur(172*16,77*16,31,1);
            setValeur(172*16,53*16,31,1); setValeur(187*16,53*16,31,1); setValeur(212*16,53*16,31,1);
            setValeur(192*16,69*16,31,1); setValeur(222*16,13*16,31,1); setValeur(222*16,14*16,31,1);
            setValeur(224*16,2*16,31,1); setValeur(237*16,27*16,31,1); setValeur(224*16,41*16,31,1);
            setValeur(227*16,55*16,31,1);
            break;
        case 50 :
            setValeur(43*16,55*16,31,1); setValeur(56*16,55*16,31,1); setValeur(96*16,55*16,31,1);
            setValeur(97*16,55*16,31,1); setValeur(95*16,87*16,31,1); setValeur(162*16,25*16,31,1);
            setValeur(166*16,64*16,31,1); setValeur(173*16,64*16,31,1); setValeur(184*16,85*16,31,1);
            setValeur(185*16,85*16,31,1); setValeur(188*16,9*16,31,1); setValeur(188*16,10*16,31,1);
            setValeur(194*16,81*16,31,1); setValeur(195*16,81*16,31,1);
            setValeur(211*16,27*16,31,1); setValeur(244*16,70*16,31,1);
            setValeur(248*16,40*16,31,1); setValeur(251*16,40*16,31,1); setValeur(255*16,70*16,31,1);
            setValeur(272*16,6*16,31,1); setValeur(272*16,7*16,31,1); setValeur(272*16,8*16,31,1);
            setValeur(282*16,25*16,31,1); setValeur(283*16,25*16,31,1); setValeur(284*16,77*16,31,1);
            setValeur(284*16,78*16,31,1); setValeur(284*16,79*16,31,1); setValeur(284*16,100*16,31,1);
            setValeur(285*16,100*16,31,1); setValeur(310*16,100*16,31,1); setValeur(315*16,100*16,31,1);
            break;
        case 51 :
            setValeur(64*16,49*16,30,1); setValeur(75*16,49*16,30,1); setValeur(84*16,62*16,30,1);
            setValeur(104*16,49*16,30,1); setValeur(115*16,49*16,30,1); setValeur(134*16,19*16,30,1);
            setValeur(142*16,35*16,30,1); setValeur(142*16,39*16,30,1); setValeur(206*16,16*16,30,1);
            setValeur(207*16,16*16,30,1); setValeur(213*16,87*16,30,1); setValeur(213*16,88*16,30,1);
            setValeur(244*16,54*16,30,1); setValeur(255*16,54*16,30,1); setValeur(284*16,11*16,30,1);
            setValeur(284*16,20*16,30,1); setValeur(315*16,11*16,30,1); setValeur(315*16,20*16,30,1);
            setValeur(285*16,57*16,30,1); setValeur(294*16,57*16,30,1); setValeur(314*16,77*16,30,1);
            setValeur(315*16,77*16,30,1);
            break;
        case 52 :
            setValeur(265*16,6*16,3997,1); setValeur(265*16,7*16,3997,1); setValeur(265*16,8*16,3997,1);
            setValeur(24*16,40*16,30,1); setValeur(35*16,40*16,30,1); setValeur(104*16,55*16,30,1);
            setValeur(115*16,33*16,30,1); setValeur(172*16,33*16,30,1); setValeur(175*16,72*16,30,1);
            setValeur(196*16,96*16,30,1); setValeur(203*16,6*16,30,1); setValeur(243*16,8*16,30,1);
            setValeur(255*16,51*16,30,1); setValeur(255*16,52*16,30,1); setValeur(255*16,53*16,30,1);
            setValeur(263*16,51*16,30,1); setValeur(308*16,18*16,30,1);
            break;
        case 53 :
            setValeur(26*16,36*16,30,1); setValeur(27*16,86*16,30,1); setValeur(34*16,102*16,30,1);
            setValeur(43*16,19*16,30,1); setValeur(49*16,83*16,30,1); setValeur(53*16,37*16,30,1);
            setValeur(104*16,84*16,30,1); setValeur(108*16,97*16,30,1); setValeur(131*16,81*16,30,1);
            setValeur(135*16,84*16,30,1); setValeur(148*16,6*16,30,1); setValeur(233*16,5*16,30,1);
            setValeur(151*16,6*16,30,1); setValeur(186*16,4*16,30,1); setValeur(193*16,4*16,30,1);
            setValeur(226*16,5*16,30,1); setValeur(227*16,5*16,30,1); setValeur(232*16,5*16,30,1);
            break;
        case 54 :
            setValeur(46*16,4*16,30,1); setValeur(46*16,10*16,30,1); setValeur(52*16,83*16,30,1);
            setValeur(52*16,84*16,30,1); setValeur(62*16,45*16,30,1); setValeur(64*16,45*16,30,1);
            setValeur(84*16,37*16,30,1); setValeur(113*16,21*16,30,1); setValeur(122*16,2*16,30,1);
            setValeur(137*16,2*16,30,1); setValeur(136*16,15*16,30,1); setValeur(137*16,15*16,30,1);
            setValeur(149*16,18*16,30,1); setValeur(150*16,18*16,30,1); setValeur(149*16,63*16,30,1);
            setValeur(150*16,63*16,30,1); setValeur(159*16,87*16,30,1); setValeur(174*16,78*16,30,1);
            setValeur(197*16,32*16,30,1); setValeur(202*16,32*16,30,1); setValeur(215*16,48*16,30,1);
            setValeur(216*16,48*16,30,1); setValeur(217*16,48*16,30,1); setValeur(244*16,25*16,30,1);
            setValeur(249*16,7*16,30,1); setValeur(144*16,41*16,30,1); setValeur(171*16,75*16,30,1);
            break;
        case 55 :
            setValeur(65*16,65*16,30,1); setValeur(24*16,87*16,30,1); setValeur(104*16,87*16,30,1);
            setValeur(115*16,87*16,30,1); setValeur(24*16,94*16,30,1); setValeur(56*16,95*16,30,1);
            setValeur(66*16,92*16,30,1); setValeur(127*16,94*16,30,1); setValeur(4*16,117*16,30,1);
            setValeur(45*16,115*16,30,1); setValeur(95*16,116*16,30,1); setValeur(56*16,128*16,30,1);
            setValeur(75*16,132*16,30,1); setValeur(23*16,154*16,30,1); setValeur(33*16,169*16,30,1);
            setValeur(37*16,154*16,30,1); setValeur(42*16,154*16,30,1); setValeur(42*16,160*16,30,1);
            setValeur(44*16,152*16,30,1); setValeur(55*16,152*16,30,1); setValeur(116*16,154*16,30,1);
            setValeur(116*16,155*16,30,1); setValeur(116*16,156*16,30,1); setValeur(81*16,186*16,30,1);
            setValeur(21*16,197*16,30,1); setValeur(76*16,204*16,30,1); setValeur(76*16,205*16,30,1);
            setValeur(133*16,203*16,30,1); setValeur(133*16,204*16,30,1);
            break;
        case 56 :
            setValeur(4*16,4*16,30,1); setValeur(4*16,34*16,30,1); setValeur(44*16,32*16,30,1);
            setValeur(55*16,94*16,30,1); setValeur(55*16,100*16,30,1); setValeur(86*16,92*16,30,1);
            setValeur(86*16,102*16,30,1); setValeur(104*16,12*16,30,1); setValeur(135*16,102*16,30,1);
            setValeur(164*16,32*16,30,1); setValeur(175*16,32*16,30,1);
            break;
        case 57 :
            setValeur(88*16,17*16,30,1); setValeur(88*16,18*16,30,1); setValeur(89*16,18*16,30,1);
            setValeur(90*16,18*16,30,1); setValeur(91*16,18*16,30,1); setValeur(91*16,17*16,30,1);
            setValeur(164*16,32*16,30,1); setValeur(175*16,32*16,30,1); setValeur(4*16,27*16,30,1);
            setValeur(115*16,32*16,30,1);
            break;
        case 58 :
            setValeur(62*16,27*16,30,1); setValeur(77*16,27*16,30,1);
            break;
            
        case 137 :
            setValeur(4*16,35*16,30,1); setValeur(5*16,34*16,30,1); setValeur(6*16,34*16,30,1);
            setValeur(5*16,40*16,30,1); setValeur(13*16,40*16,30,1); setValeur(14*16,40*16,30,1);
            setValeur(14*16,34*16,30,1); setValeur(15*16,35*16,30,1); setValeur(15*16,36*16,30,1);
            break;
        case 140 :
            setValeur(34*16,4*16,30,1); setValeur(34*16,5*16,30,1); setValeur(34*16,6*16,30,1);
            setValeur(34*16,7*16,30,1);
            break;
        case 154 :
            setValeur(4*16,19*16,30,1); setValeur(5*16,19*16,30,1);
            break;
        case 155 : 
            setValeur(47*16,92*16,31,1); setValeur(144*16,34*16,31,1); setValeur(145*16,34*16,31,1);
            setValeur(146*16,34*16,31,1);
            break;
        /*case 15 :
            setValeur(10*16,21*16,31,1); setValeur(42*16,2*16,31,1); setValeur(42*16,12*16,31,1);
            setValeur(64*16,35*16,31,1); setValeur(64*16,38*16,31,1); setValeur(126*16,19*16,31,1);
            setValeur(127*16,19*16,31,1); setValeur(132*16,19*16,31,1); setValeur(133*16,19*16,31,1);
            setValeur(144*16,14*16,31,1); setValeur(149*16,6*16,31,1); setValeur(155*16,14*16,31,1);
            setValeur(154*16,32*16,31,1); setValeur(155*16,32*16,31,1); setValeur(156*16,32*16,31,1);
            setValeur(157*16,32*16,31,1); setValeur(82*16,17*16,40,0); setValeur(82*16,27*16,40,0);
            setValeur(97*16,17*16,40,0); setValeur(97*16,27*16,1004,0);
            setValeur(2*16,2*16,31,1);setValeur(17*16,2*16,31,1);setValeur(42*16,2*16,31,1);
            setValeur(42*16,12*16,31,1); setValeur(22*16,17*16,31,1); setValeur(23*16,17*16,31,1);
            setValeur(24*16,17*16,31,1); setValeur(26*16,42*16,31,1); setValeur(29*16,39*16,31,1);
            setValeur(36*16,20*16,31,1); setValeur(43*16,20*16,31,1); setValeur(45*16,33*16,31,1);
            setValeur(46*16,33*16,31,1); setValeur(47*16,33*16,31,1); setValeur(54*16,29*16,31,1);
            setValeur(55*16,29*16,31,1); setValeur(56*16,29*16,31,1); setValeur(74*16,20*16,31,1);
            setValeur(82*16,32*16,31,1); setValeur(82*16,42*16,31,1); setValeur(97*16,32*16,31,1);
            setValeur(97*16,42*16,31,1); setValeur(102*16,47*16,31,1); setValeur(102*16,57*16,31,1);
            setValeur(117*16,47*16,31,1); setValeur(117*16,57*16,31,1); setValeur(162*16,2*16,31,1);
            setValeur(162*16,12*16,31,1); setValeur(177*16,2*16,31,1); setValeur(177*16,12*16,31,1);
            setValeur(182*16,47*16,31,1); setValeur(197*16,47*16,31,1);
            break;
        case 16 :
            setValeur(42*16,47*16,30,1);setValeur(57*16,47*16,30,1);setValeur(42*16,57*16,30,1);
            setValeur(57*16,57*16,30,1);setValeur(24*16,2*16,30,1);setValeur(25*16,2*16,30,1);
            for (int j=0; j<5; j++) for (int i=0; i<6; i++) setValeur((87+i)*16,(20+j)*16,30,1);
            setValeur(30*16,2*16,30,1);setValeur(31*16,2*16,30,1);setValeur(36*16,2*16,30,1);
            setValeur(37*16,2*16,30,1);setValeur(24*16,12*16,30,1);setValeur(25*16,12*16,30,1);
            setValeur(30*16,12*16,30,1);setValeur(31*16,12*16,30,1);setValeur(36*16,12*16,30,1);
            setValeur(37*16,12*16,30,1);setValeur(148*16,54*16,30,1);setValeur(149*16,54*16,30,1);
            setValeur(150*16,54*16,30,1);setValeur(148*16,55*16,30,1);setValeur(149*16,55*16,30,1);
            setValeur(150*16,55*16,30,1);setValeur(142*16,17*16,30,1);setValeur(157*16,17*16,30,1);
            setValeur(142*16,27*16,30,1);setValeur(157*16,27*16,30,1);setValeur(162*16,62*16,30,1);
            setValeur(177*16,62*16,30,1);setValeur(162*16,72*16,30,1);setValeur(177*16,72*16,30,1);
            setValeur(182*16,32*16,30,1);setValeur(197*16,32*16,30,1);setValeur(182*16,42*16,30,1);
            setValeur(197*16,42*16,30,1);setValeur(242*16,47*16,30,1);setValeur(257*16,47*16,30,1);
            setValeur(242*16,57*16,30,1);setValeur(257*16,57*16,30,1);setValeur(237*16,40*16,30,1);
            setValeur(237*16,41*16,30,1);setValeur(237*16,42*16,30,1);setValeur(238*16,40*16,30,1);
            setValeur(238*16,41*16,30,1);setValeur(238*16,42*16,30,1);setValeur(222*16,92*16,30,1);
            setValeur(277*16,92*16,30,1);setValeur(222*16,102*16,30,1);setValeur(277*16,102*16,30,1);
            setValeur(242*16,77*16,30,1);setValeur(257*16,77*16,30,1);setValeur(242*16,87*16,30,1);
            setValeur(257*16,87*16,30,1);setValeur(202*16,62*16,30,1);setValeur(217*16,62*16,30,1);
            setValeur(202*16,72*16,30,1);setValeur(217*16,72*16,30,1);
            break;
        case 17 :
            setValeur(2*16,32*16,31,1);setValeur(17*16,32*16,31,1);setValeur(2*16,42*16,31,1);
            setValeur(17*16,42*16,31,1);setValeur(2*16,47*16,31,1);setValeur(17*16,47*16,31,1);
            setValeur(52*16,39*16,31,1);setValeur(64*16,24*16,31,1);setValeur(75*16,24*16,31,1);
            setValeur(87*16,39*16,31,1);setValeur(64*16,89*16,31,1);setValeur(71*16,89*16,31,1);
            setValeur(64*16,94*16,31,1);setValeur(71*16,94*16,31,1);setValeur(142*16,72*16,31,1);
            setValeur(147*16,72*16,31,1);setValeur(182*16,107*16,31,1);setValeur(197*16,107*16,31,1);
            setValeur(182*16,117*16,31,1);setValeur(197*16,117*16,31,1);setValeur(204*16,64*16,31,1);
            setValeur(215*16,64*16,31,1);setValeur(125*16,50*16,31,1);setValeur(125*16,51*16,31,1);
            setValeur(134*16,45*16,31,1);setValeur(134*16,46*16,31,1);setValeur(134*16,55*16,31,1);
            setValeur(134*16,56*16,31,1);setValeur(42*16,117*16,31,1);setValeur(57*16,117*16,31,1);
            setValeur(82*16,117*16,31,1);setValeur(97*16,117*16,31,1);
            break;
        case 18 :
            setValeur(20*16,28*16,30,1);setValeur(21*16,28*16,30,1);setValeur(162*16,2*16,30,1);
            setValeur(177*16,2*16,30,1);setValeur(162*16,12*16,30,1);setValeur(177*16,12*16,30,1);
            setValeur(182*16,32*16,30,1);setValeur(197*16,32*16,30,1);setValeur(182*16,42*16,30,1);
            setValeur(197*16,42*16,30,1);setValeur(182*16,47*16,30,1);setValeur(197*16,47*16,30,1);
            setValeur(182*16,57*16,30,1);setValeur(197*16,57*16,30,1);setValeur(242*16,32*16,30,1);
            setValeur(257*16,32*16,30,1);setValeur(242*16,42*16,30,1);setValeur(257*16,42*16,30,1);
            setValeur(162*16,47*16,30,1);setValeur(177*16,47*16,30,1);setValeur(317*16,47*16,30,1);
            setValeur(317*16,57*16,30,1);setValeur(203*16,11*16,30,1);setValeur(204*16,11*16,30,1);
            setValeur(205*16,11*16,30,1);setValeur(203*16,12*16,30,1);setValeur(204*16,12*16,30,1);
            setValeur(205*16,12*16,30,1);
            break;
        case 19 :
            setValeur(146*16,38*16,2311,1);setValeur(146*16,39*16,2311,1);setValeur(152*16,49*16,2311,1);
            setValeur(152*16,50*16,2311,1);setValeur(169*16,42*16,2311,1);setValeur(170*16,42*16,2311,1);
            setValeur(173*16,17*16,2311,1);setValeur(173*16,18*16,2311,1);setValeur(173*16,19*16,2311,1);
            setValeur(185*16,51*16,2311,1);setValeur(185*16,52*16,2311,1);setValeur(185*16,53*16,2311,1);
            setValeur(5*16,2*16,31,1);setValeur(5*16,8*16,31,1);
            for (int i=0; i<5; i++) {setValeur((64+i)*16,2*16,31,1);setValeur((64+i)*16,12*16,31,1);}
            for (int i=0; i<16; i++) setValeur((62+i)*16,47*16,31,1);
            for (int i=0; i<4; i++) setValeur(162*16,(21+i)*16,31,1);
            for (int i=0; i<3; i++) setValeur((35+i)*16,65*16,31,1);
            for (int i=0; i<2; i++) {setValeur((82+i)*16,47*16,31,1);setValeur((96+i)*16,47*16,31,1);}
            break;
        case 20 :
            setValeur(6*16,47*16,30,1);setValeur(7*16,47*16,30,1);setValeur(12*16,47*16,30,1);
            setValeur(13*16,47*16,30,1);setValeur(42*16,77*16,30,1);setValeur(57*16,77*16,30,1);
            setValeur(42*16,87*16,30,1);setValeur(57*16,87*16,30,1);setValeur(122*16,77*16,30,1);
            setValeur(137*16,77*16,30,1);setValeur(122*16,87*16,30,1);setValeur(137*16,87*16,30,1);
            setValeur(127*16,39*16,30,1);setValeur(132*16,39*16,30,1);
            for (int i=0; i<3; i++) {setValeur((25+i)*16,12*16,30,1);setValeur((32+i)*16,12*16,30,1);}
            for (int j=0; j<2; j++) for (int i=0; i<12; i++) setValeur((24+i)*16,(49+j)*16,30,1);
            for (int i=0; i<3; i++) {setValeur((142+i)*16,47*16,30,1);setValeur((155+i)*16,47*16,30,1);}
            setValeur(91*16,77*16,2324,11);setValeur(82*16,69*16,2324,11);setValeur(97*16,69*16,2324,11);
            setValeur(82*16,54*16,2324,11);setValeur(97*16,54*16,2324,11);setValeur(86*16,48*16,2324,11);
            setValeur(91*16,53*16,2324,11);
            break;
        case 21 :
            for (int i=0; i<5; i++) setValeur(255*16,(35+i)*16,31,1);
            setValeur(97*16,32*16,31,1);setValeur(97*16,42*16,31,1);setValeur(144*16,4*16,31,1);
            setValeur(144*16,10*16,31,1);setValeur(165*16,4*16,31,1);setValeur(165*16,10*16,31,1);
            setValeur(194*16,19*16,31,1);setValeur(194*16,25*16,31,1);setValeur(182*16,49*16,31,1);
            setValeur(184*16,47*16,31,1);setValeur(195*16,47*16,31,1);setValeur(197*16,49*16,31,1);
            setValeur(182*16,55*16,31,1);setValeur(184*16,57*16,31,1);setValeur(195*16,57*16,31,1);
            setValeur(197*16,55*16,31,1);setValeur(205*16,34*16,31,1);setValeur(205*16,40*16,31,1);
            break;
        case 22 :
            setValeur(206*16,21*16,2311,1);setValeur(206*16,22*16,2311,1);setValeur(229*16,55*16,2311,1);
            setValeur(230*16,55*16,2311,1);
            setValeur(5*16,34*16,30,1);setValeur(5*16,55*16,30,1);setValeur(10*16,23*16,30,1);
            for (int j=0; j<3; j++) for (int i=0; i<2; i++) setValeur((69+i)*16,(23+j)*16,30,1);
            setValeur(169*16,55*16,30,1);setValeur(170*16,55*16,30,1);setValeur(175*16,34*16,30,1);
            setValeur(176*16,34*16,30,1);setValeur(177*16,34*16,30,1);setValeur(182*16,32*16,30,1);
            setValeur(183*16,32*16,30,1);setValeur(182*16,42*16,30,1);setValeur(183*16,42*16,30,1);
            setValeur(216*16,32*16,30,1);setValeur(217*16,32*16,30,1);setValeur(216*16,42*16,30,1);
            setValeur(217*16,42*16,30,1);setValeur(222*16,34*16,30,1);setValeur(235*16,34*16,30,1);
            setValeur(222*16,40*16,30,1);setValeur(235*16,40*16,30,1);setValeur(84*16,34*16,30,1);
            setValeur(95*16,34*16,30,1);
            for (int i=0; i<5; i++) setValeur(237*16,(50+i)*16,30,1);
            break;
        case 23 :
            for (int i=0; i<6; i++) setValeur((207+i)*16,59*16,2311,1);
            setValeur(49*16,39*16,31,1);setValeur(50*16,39*16,31,1);setValeur(84*16,32*16,31,1);
            setValeur(95*16,32*16,31,1);setValeur(84*16,62*16,31,1);setValeur(84*16,72*16,31,1);
            setValeur(102*16,62*16,31,1);setValeur(117*16,62*16,31,1);setValeur(135*16,62*16,31,1);
            setValeur(135*16,72*16,31,1);setValeur(164*16,17*16,31,1);setValeur(175*16,17*16,31,1);
            setValeur(164*16,64*16,31,1);setValeur(164*16,70*16,31,1);setValeur(184*16,47*16,31,1);
            setValeur(195*16,47*16,31,1);setValeur(204*16,49*16,31,1);setValeur(215*16,49*16,31,1);
            setValeur(255*16,64*16,31,1);setValeur(255*16,70*16,31,1);setValeur(344*16,2*16,31,1);
            setValeur(355*16,2*16,31,1);setValeur(344*16,10*16,31,1);setValeur(355*16,10*16,31,1);
            break;
        case 24 :
            for (int i=0; i<2; i++) setValeur((109+i)*16,34*16,2311,1);
            for (int i=0; i<2; i++) setValeur((189+i)*16,34*16,2311,1);
            for (int i=0; i<4; i++) setValeur((148+i)*16,49*16,2311,1);
            for (int j=0; j<4; j++) for (int i=0; i<2; i++) setValeur((30+i)*16,(60+j)*16,31,1);
            setValeur(105*16,70*16,31,1);setValeur(114*16,70*16,31,1);setValeur(124*16,47*16,31,1);
            setValeur(124*16,57*16,31,1);setValeur(144*16,57*16,31,1);setValeur(155*16,57*16,31,1);
            setValeur(204*16,34*16,31,1);setValeur(204*16,40*16,31,1);setValeur(235*16,34*16,31,1);
            setValeur(235*16,40*16,31,1);
            for (int j=0; j<3; j++) setValeur(220*16,(61+j)*16,31,1);
            for (int j=0; j<2; j++) setValeur(225*16,(51+j)*16,31,1);
            for (int j=0; j<2; j++) for (int i=0; i<2; i++) setValeur((221+i)*16,(56+j)*16,31,1);
            for (int j=0; j<2; j++) setValeur(285*16,(21+j)*16,31,1);
            for (int j=0; j<2; j++) setValeur(294*16,(13+j)*16,31,1);
            break;
        case 25 :
            for (int i=0; i<2; i++) setValeur(145*16,(84+i)*16,2311,1);
            for (int i=0; i<2; i++) setValeur(154*16,(89+i)*16,2311,1);
            for (int i=0; i<2; i++) setValeur(145*16,(94+i)*16,2311,1);
            setValeur(7*16,100*16,31,1);setValeur(12*16,100*16,31,1);setValeur(31*16,99*16,31,1);
            setValeur(48*16,99*16,31,1);setValeur(48*16,110*16,31,1);setValeur(46*16,79*16,31,1);
            setValeur(53*16,79*16,31,1);setValeur(46*16,85*16,31,1);setValeur(53*16,85*16,31,1);
            setValeur(62*16,34*16,31,1);setValeur(64*16,32*16,31,1);setValeur(75*16,32*16,31,1);
            setValeur(77*16,34*16,31,1);setValeur(62*16,40*16,31,1);setValeur(64*16,42*16,31,1);
            setValeur(75*16,42*16,31,1);setValeur(77*16,40*16,31,1);setValeur(130*16,21*16,31,1);
            setValeur(62*16,79*16,31,1);setValeur(64*16,77*16,31,1);setValeur(75*16,77*16,31,1);
            setValeur(77*16,79*16,31,1);setValeur(62*16,85*16,31,1);setValeur(64*16,87*16,31,1);
            setValeur(75*16,87*16,31,1);setValeur(77*16,85*16,31,1);
            for (int j=0; j<4; j++) setValeur((122+j)*16,39*16,31,1);
            for (int j=0; j<3; j++) setValeur(125*16,(40+j)*16,31,1);
            break;
        case 26 :
            setValeur(22*16,34*16,31,1);setValeur(25*16,34*16,31,1);setValeur(34*16,34*16,31,1);
            setValeur(37*16,34*16,31,1);setValeur(56*16,71*16,31,1);setValeur(57*16,71*16,31,1);
            for (int i=0; i<4; i++) setValeur((134+i)*16,80*16,31,1);
            break;
        case 29 :
            setValeur(9*16,21*16,2324,11);
            setValeur(8*16,27*16,30,1);setValeur(11*16,27*16,30,1);
            for (int i=0; i<4; i++) setValeur((8+i)*16,26*16,30,1);
            break;*/
    }
}

void Monde::permuteBlocs() {
    int temoin=0;
    switch (gpJeu->getZone()) {
        case 24 :
            if (map[17][32]==1348) {
                //bloc bleu bas
                for (int j=0; j<5; j++) setValeur(17*16,(31+j)*16,1346,0);
                temoin=1;
            }
            else {
                //bloc bleu haut
                for (int j=0; j<5; j++) setValeur(17*16,(31+j)*16,1348,2);
                temoin=0;
            }
            break;
        case 47 :
            if (map[187][12]==1348) {
                //bloc bleu bas
                for (int i=0; i<6; i++) setValeur((187+i)*16,11*16,1346,0);
                setValeur(187*16,12*16,1346,0);
                setValeur(192*16,12*16,1346,0);
                for (int i=0; i<4; i++) setValeur((288+i)*16,26*16,1346,0);
                for (int i=0; i<4; i++) setValeur(307*16,(43+i)*16,1346,0);
                setValeur(307*16,82*16,1346,0);
                for (int i=0; i<4; i++) setValeur((312+i)*16,35*16,1346,0);
                for (int i=0; i<4; i++) setValeur((328+i)*16,41*16,1346,0);
                setValeur(269*16,82*16,1346,0);
                setValeur(271*16,82*16,1346,0);
                for (int i=0; i<3; i++) setValeur(175*16,(21+i)*16,1346,0);
                //bloc orange haut
                for (int i=0; i<2; i++) setValeur((149+i)*16,67*16,1347,2);
                for (int i=0; i<2; i++) setValeur((189+i)*16,7*16,1347,2);
                for (int i=0; i<2; i++) setValeur((229+i)*16,37*16,1347,2);
                for (int i=0; i<2; i++) setValeur(279*16,(22+i)*16,1347,2);
                setValeur(299*16,45*16,1347,2);
                for (int i=0; i<2; i++) setValeur((310+i)*16,46*16,1347,2);
                setValeur(315*16,76*16,1347,2);
                for (int i=0; i<3; i++) setValeur(323*16,(36+i)*16,1347,2);
                for (int i=0; i<4; i++) setValeur((328+i)*16,24*16,1347,2);
                for (int i=0; i<3; i++) setValeur(345*16,(66+i)*16,1347,2);
                temoin=1;
            }
            else {
                //bloc bleu haut
                for (int i=0; i<6; i++) setValeur((187+i)*16,11*16,1348,2);
                setValeur(187*16,12*16,1348,2);
                setValeur(192*16,12*16,1348,2);
                for (int i=0; i<4; i++) setValeur((288+i)*16,26*16,1348,2);
                for (int i=0; i<4; i++) setValeur(307*16,(43+i)*16,1348,2);
                setValeur(307*16,82*16,1348,2);
                for (int i=0; i<4; i++) setValeur((312+i)*16,35*16,1348,2);
                for (int i=0; i<4; i++) setValeur((328+i)*16,41*16,1348,2);
                setValeur(269*16,82*16,1348,2);
                setValeur(271*16,82*16,1348,2);
                for (int i=0; i<3; i++) setValeur(175*16,(21+i)*16,1348,2);
                //bloc orange bas
                for (int i=0; i<2; i++) setValeur((149+i)*16,67*16,1345,0);
                for (int i=0; i<2; i++) setValeur((189+i)*16,7*16,1345,0);
                for (int i=0; i<2; i++) setValeur((229+i)*16,37*16,1345,0);
                for (int i=0; i<2; i++) setValeur(279*16,(22+i)*16,1345,0);
                setValeur(299*16,45*16,1345,0);
                for (int i=0; i<2; i++) setValeur((310+i)*16,46*16,1345,0);
                setValeur(315*16,76*16,1345,0);
                for (int i=0; i<3; i++) setValeur(323*16,(36+i)*16,1345,0);
                for (int i=0; i<4; i++) setValeur((328+i)*16,24*16,1345,0);
                for (int i=0; i<3; i++) setValeur(345*16,(66+i)*16,1345,0);
                temoin=0;
            }
            break;
        case 62 :
            if (map[8][5]==1348) {
                //bloc bleu bas
                for (int i=0; i<5; i++) setValeur((8+i)*16,5*16,1346,0);
                //bloc orange haut
                for (int i=0; i<6; i++) setValeur((7+i)*16,11*16,1347,2);
                setValeur(7*16,12*16,1347,2); setValeur(12*16,12*16,1347,2);
                temoin=1;
            }
            else {
                //bloc bleu haut
                for (int i=0; i<5; i++) setValeur((8+i)*16,5*16,1348,2);
                //bloc orange bas
                for (int i=0; i<6; i++) setValeur((7+i)*16,11*16,1345,0);
                setValeur(7*16,12*16,1345,0); setValeur(12*16,12*16,1345,0);
                temoin=0;
            }
            break;
        case 68 :
            if (map[41][9]==2368) {
                map[41][9]=2367;
                map[34][13]=2368;
                map[45][13]=2369;
                gpJeu->getJoueur()->setPosRails(1);
                temoin=1;
            }
            else {
                map[41][9]=2368;
                map[34][13]=2367;
                map[45][13]=2367;
                gpJeu->getJoueur()->setPosRails(0);
                temoin=0;
            }
            break;
        case 90 : return; break;
        case 154 :
            gpJeu->getAudio()->playSound(20);
            if (map[54][8]==2714) {
                for (int j=0; j<2; j++) {
                    setValeur(54*16,(8+15*j)*16,2638,0);
                    for (int i=0; i<6; i++) {
                        mur[40*2][(6+15*j)*2+i]=1;
                        mur[40*2+1][(6+15*j)*2+i]=1;
                        mur[40*2+2][(6+15*j)*2+i]=1;
                        map[40+(i%2)][(6+15*j)+((int)(i/2))]=2720+i;
                    }
                }
                temoin=1;
            }
            else {
                for (int j=0; j<2; j++) {
                    setValeur(54*16,(8+15*j)*16,2714,1);
                    passage(40,6+15*j,1);
                }
                temoin=0;
            }
            break;
    }
    gpJeu->permuteBloc(temoin);
}

int Monde::etage() {
    int level = 0;
    switch (gpJeu->getZone()) {
        case 46 : level=(region[0]/(80*16))-1; break;
        case 47 : level=-(region[0]/(120*16)); break;
        case 48 : level=-(region[0]/(140*16)); break;
        case 49 : case 54 : level=-((region[0]+(100*16))/(120*16)); break;
        case 50 : case 51 : case 52 :
            level=-1;
            if (region[0]==0) level=2;
            else if (region[0]<80*16) level=1;
            else if (region[0]<180*16) level=0;
            break;
        case 53 :
            level = (region[0]/(80*16));
            if (region[1] >= 60*16) level-=2;
            break;
        case 55 : level=(region[1]/(75*16))-2; break;
        case 56 : level=(region[0]/(140*16)); break;
        case 57 : 
            if (region[1] < 105*16) level=(region[0]/(140*16)); 
            else level=0-(region[1]/(105*16)); 
            break;
        case 58 : level=0; break;
        case 59 : level=(region[0]/(80*16))-1; break;
        case 60 : level=(region[1]/(75*16))-1; break;
        case 63 : level=(region[0]/(60*16))-1; break;
        case 67 : level=(region[0]/(40*16))-1; break;
        case 68 : 
            if (region[0]==0 || (region[1]<30*16 && region[0]<80*16)) level=0;
            else level=1; break;
        case 78 : level=(region[0]/(60*16))-1; break;
        case 137 : 
            if (region[1]<60*16) level=-1;
            else level=0; break;
        case 150 : level=1-(region[0]/(60*16)); break;
        case 154 :
            if (region[0]==0) level=1;
            else if (region[1]==0) level=0;
            else level=-1;
            break;
    }
    return level;
}

int Monde::getLargeur() {return largeur;}
int Monde::getHauteur() {return hauteur;}

int Monde::motifValue(int x, int y) {
    return map[(int)(x/CASE)][(int)(y/CASE)];
}

int Monde::motifAirValue(int x, int y) {
    return air[(int)(x/CASE)][(int)(y/CASE)];
}

int Monde::murValue(int x, int y) {
    return mur[(int)(x/(CASE/2))][(int)(y/(CASE/2))];
}

int Monde::contenuValue(int x, int y) {
    return contenu[(int)(x/CASE)][(int)(y/CASE)];
}

int Monde::regionValue(int i) {
    return region[i];
}

void Monde::setValeur(int x, int y, int vsol, int vair, int vmur, int vcontenu) {
    setValeur(x, y, vsol, vmur);
    if (vair>-1) air[(int)(x/CASE)][(int)(y/CASE)] = vair;
    if (vcontenu>-1) contenu[(int)(x/CASE)][(int)(y/CASE)] = vcontenu;
}

void Monde::setValeur(int x, int y, int vsol, int vmur) {
    map[(int)(x/CASE)][(int)(y/CASE)] = vsol;
    if (vmur==999) return;
    mur[((int)(x/CASE))*2][((int)(y/CASE))*2] = vmur;
    mur[((int)(x/CASE))*2+1][((int)(y/CASE))*2] = vmur;
    mur[((int)(x/CASE))*2][((int)(y/CASE))*2+1] = vmur;
    mur[((int)(x/CASE))*2+1][((int)(y/CASE))*2+1] = vmur;
}

void Monde::setMap(int x, int y, int val) {map[x][y]=val;}

void Monde::setAir(int x, int y, int val) {air[x][y]=val;}

void Monde::setMurs(int x, int y, int val) {mur[x][y]=val;}

void Monde::setContenu(int x, int y, int val) {contenu[x][y]=val;}

void Monde::drawSol(SDL_Surface* screen, int phg[2]) {
    int x=0,y=0,val;
    SDL_Rect src;    
    SDL_Rect dst;
    
    dst.x = 0;
    dst.y = 0;
    
    plafondmax=0;
    
    if (gpJeu->getZone()<1) {
        src.x=0; src.y=0; src.w=320; src.h=240;
        if (gpJeu->getZone()==-1) SDL_BlitSurface(imageSpe[15], &src, screen, &dst);
        else SDL_BlitSurface(imageSpe[16], &src, screen, &dst);
        return;
    }
    
    if (gpJeu->getZone()==15 || gpJeu->getZone()==30 || gpJeu->getZone()==46 
    || gpJeu->getZone()==53) {
        src.x=0; src.y=0; src.w=320; src.h=240;
        SDL_BlitSurface(imageSpe[1], &src, screen, &dst);
    }
    
    if (gpJeu->getZone()==45) {
        src.x=0; src.y=0; src.w=320; src.h=240;
        SDL_BlitSurface(imageSpe[0], &src, screen, &dst);
    }
    
    if (gpJeu->getZone()==56 && region[0]==160*16 && region[1]==60*16) {
        src.x=0; src.y=0; src.w=320; src.h=240;
        SDL_BlitSurface(imageSpe[18], &src, screen, &dst);
        return;
    }
    
    while(x<=320){
        while(y<=240){
            
            if(air[((phg[0]+x)-((phg[0]+x)%CASE))/CASE][((phg[1]+y)-((phg[1]+y)%CASE))/CASE ]>0) {
                plafond[plafondmax][0]=x;
                plafond[plafondmax][1]=y;
                plafondmax++;
            }    
            
            val=map[((phg[0]+x)-((phg[0]+x)%CASE))/CASE][((phg[1]+y)-((phg[1]+y)%CASE))/CASE ];
            
            if (val != 999) { // image vide
            
                if (val==1) {
                    switch (anim%4) {
                        case 0 : val=128; break;
                        case 2 : val=129; break;                    
                    }    
                }
                if ((val >= 425 && val <= 452) || (val >= 457 && val <= 466)
                    || val == 540 || val == 543 || (val >= 425+1442 && val <= 452+1442) 
                    || (val >= 457+1442 && val <= 463+1442)
                    || val == 1207 || val == 1210 
                    || (val >= 1419 && val <= 1434) || (val >= 1495 && val <= 1510)
                    || (val >= 4618 && val <=4627)) {
                    switch (anim%3) {
                        case 0 : val++; break;
                        case 1 : val+=2; break;
                    }    
                }
                if ((val >= 1145 && val <= 1172) || (val >= 1177 && val <= 1186)
                    || val == 1160 || val == 1163) {
                    switch (anim%3) {
                        case 0 : val++; break;
                        case 1 : val+=2; break;
                    }    
                }
                if (val==1000 && !gpJeu->getStop()
                && contenu[((phg[0]+x)-((phg[0]+x)%CASE))/CASE][((phg[1]+y)-((phg[1]+y)%CASE))/CASE]>0) {
                    contenu[((phg[0]+x)-((phg[0]+x)%CASE))/CASE][((phg[1]+y)-((phg[1]+y)%CASE))/CASE]--;
                }
                if (val==1001 || (val >= 2349 && val <= 2364) || val==2077) {
                    switch (anim%4) {
                        case 1 : case 3 : val++; break;
                        case 2 : val+=2; break;
                    }
                }
                if ((val >= 2080 && val <= 2092) || (val >= 3278 && val <= 3290)
                || (val >= 5797 && val <= 5809)
                || (val >= 4775 && val <= 4787)) {
                    switch (anim%4) {
                        case 1 : case 3 : val+=13; break;
                        case 2 : val+=26; break;
                    }
                }
                if ((val >= 2450-507 && val <= 2462-507) 
                || (val >= 3529 && val <= 3541)) {
                    switch (anim%8) {
                        case 0 :
                        case 1 : val+=13; break;
                        case 2 :
                        case 3 : val+=26; break;
                        case 4 :
                        case 5 : val+=13; break;
                    }
                }
                if (val == 3417) val+=(anim%3);
                if (val==885 || val==893 || val==895) {
                    switch (anim%3) {
                        case 1 : val=val-885+4116; break;
                        case 2 : val=val-885+4117; break;                   
                    }    
                }
                if (val==888 || val==890 || val==892) {
                    switch (anim%3) {
                        case 1 : val=val-888+4118; break;
                        case 2 : val=val-888+4119; break;                   
                    }
                }
                if (val==896 || val==898) {
                    switch (anim%3) {
                        case 1 : val=val-896+4128; break;
                        case 2 : val=val-896+4129; break;                   
                    }
                }
                if (val==899) {
                    switch (anim%3) {
                        case 1 : val=4132; break;
                        case 2 : val=4133; break;                   
                    }
                }
                if (val==908) {
                    switch (anim%3) {
                        case 1 : val=4134; break;
                        case 2 : val=4135; break;                   
                    }
                }
                if (val==909) {
                    switch (anim%3) {
                        case 1 : val=4136; break;
                        case 2 : val=4137; break;                   
                    }
                }
                if (val == 1652 || val == 1653) val+=2*(anim%2);
                if (val == 4673) val+=(gpJeu->getJoueur()->getChargeCafe()/8)%3;
                if (val >= 5230 && val <= 5245) val+=(anim%3);
                
            }

            SDL_Surface* img = image[(int)(val/1000)];
            val = val%1000;

            src.x=(val%40)*16; src.y=((int)(val/40))*16;
            if(x==0)src.x+=phg[0]%CASE;
            src.w=CASE-(src.x%CASE);
            if(y==0)src.y+=phg[1]%CASE;
            src.h=CASE-(src.y%CASE);
            dst.x = x; dst.y = y;
            
            SDL_BlitSurface(img, &src, screen, &dst);
            
            y+=src.h;
        }    
        y=0;
        x+=src.w;
    }
    
    bool stop = gpJeu->getStop();
    bool transition = gpJeu->getTransition();
    
    animold=anim;
    
    if(SDL_GetTicks() > lastAnimTime + ANIM_REFRESH && (!stop || transition)) {
        lastAnimTime = SDL_GetTicks();
        anim++;            
        if (anim > 59) anim = 0;
        if (gpJeu->getZone()==52) gpJeu->testTapis();
    }
}


void Monde::drawAir(SDL_Surface* screen, int phg[2]) {
    int x=0,y=0,val=0,cpt=0;
    SDL_Rect src;    
    SDL_Rect dst;
    dst.x = 0; dst.y = 0;
    
    while(cpt<plafondmax) {
        x=plafond[cpt][0];
        y=plafond[cpt][1];
        val=air[((phg[0]+x)-((phg[0]+x)%CASE))/CASE][((phg[1]+y)-((phg[1]+y)%CASE))/CASE];
        
        if (val > 0) {
        
            if (val==760) {
                switch (animold%3) {
                    case 0 : val+=3; break;
                    case 1 : val+=5; break;
                }
            }
            if (val==762) {
                switch (animold%3) {
                    case 0 : val+=2; break;
                    case 1 : val+=4; break;
                }
            }
            if (val>=2000 && val<=2005 && animold%2==1) val+=10;
            if ((val==2007 || val==2008) && animold%2==1) val+=9;
            if (val >= 1495 && val <= 1518) {
                    switch (animold%3) {
                        case 0 : val++; break;
                        case 1 : val+=2; break;
                    }    
                }
            if (val == 4671 && anim==23) {
                air[13][5]=4672;
                gpJeu->getPnj()->getSuivant()->setAnimmax(7);
                gpJeu->getJoueur()->setImmo(false);
            }
            if (val == 4671 && anim>=11) val=4669;
        
            SDL_Surface* img = image[(int)(val/1000)];
            val = val%1000;

            src.x=(val%40)*16; src.y=((int)(val/40))*16;
            if(x==0)src.x+=phg[0]%CASE;
            src.w=CASE-(src.x%CASE);
            if(y==0)src.y+=phg[1]%CASE;
            src.h=CASE-(src.y%CASE);
            dst.x = x; dst.y = y;
            
            SDL_BlitSurface(img, &src, screen, &dst);
            
        }

        cpt++;
    }
    
    //neige
    if ((gpJeu->getZone()==9 || gpJeu->getZone()==3) 
    && gpJeu->getJoueur()->getAvancement()<INFO_PASSE_OK) {
        dst.x=0; dst.y=0; src.x=0; src.y=0; src.w=320; src.h=240;
        SDL_BlitSurface(imageSpe[12+(anim%3)], &src, screen, &dst); 
    }
    
    if (gpJeu->getZone()==40) {
        dst.x=0; dst.y=0; src.x=0; src.y=0; src.w=320; src.h=240;
        SDL_BlitSurface(imageSpe[4+(anim%3)], &src, screen, &dst); 
    }
    
    if (gpJeu->getZone()==6) {
        dst.x=0; dst.y=0; src.x=phg[0]/2; src.y=phg[1]/2; src.w=320; src.h=240;
        if (gpJeu->getTransition() && (animtransX || animtransY)) {
            int at = 0; if (animtransX) at = animtransX; else at = animtransY;
            SDL_SetAlpha(imageSpe[11], SDL_SRCALPHA, 255+((128*abs(at))/328));
            src.x=(int)xfiltre; src.y=(int)yfiltre;
        }
        else {
            while (src.x >= 256) src.x-=256;
            while (src.y >= 256) src.y-=256;
            xfiltre=src.x; yfiltre=src.y;
        }
        SDL_BlitSurface(imageSpe[11], &src, screen, &dst);
    }
    
    if (gpJeu->getTransition() && (animtransX || animtransY) && gpJeu->getNewZone()==6) {
        int at = 0; if (animtransX) at = animtransX; else at = animtransY;
        SDL_SetAlpha(imageSpe[11], SDL_SRCALPHA, 128-((128*abs(at))/328));
        
        int phg0 = 0;
        int phg1 = 0;
        
        phg0 = gpJeu->getNewX() - 320/2 + 8 + gpJeu->getVueHorz();
        phg1 = gpJeu->getNewY() - 240/2 + 16 + gpJeu->getVueVert();
        if (phg0 < 0) phg0 = 0; if (phg1 < 0) phg1 = 0;
        
        dst.x=0; dst.y=0; src.x=phg0/2; src.y=phg1/2; src.w=320; src.h=240;
        while (src.x >= 256) src.x-=256;
        while (src.y >= 256) src.y-=256;
        SDL_BlitSurface(imageSpe[11], &src, screen, &dst);
    }
    
    if (gpJeu->getZone()==21) {
        dst.x=0; dst.y=0; src.x=phg[0]/2; src.y=phg[1]/2; src.w=320; src.h=240;
        if (gpJeu->getTransition() && (animtransX || animtransY)) {
            int at = 0; if (animtransX) at = animtransX; else at = animtransY;
            SDL_SetAlpha(imageSpe[9], SDL_SRCALPHA, 255+((128*abs(at))/328));
            src.x=(int)xfiltre; src.y=(int)yfiltre;
        }
        else {
            while (src.x >= 256) src.x-=256;
            while (src.y >= 256) src.y-=256;
            xfiltre=src.x; yfiltre=src.y;
        }
        SDL_BlitSurface(imageSpe[9], &src, screen, &dst);
    }
    
    if (gpJeu->getTransition() && (animtransX || animtransY) && gpJeu->getNewZone()==21) {
        int at = 0; if (animtransX) at = animtransX; else at = animtransY;
        SDL_SetAlpha(imageSpe[9], SDL_SRCALPHA, 128-((128*abs(at))/328));
        
        int phg0 = 0;
        int phg1 = 0;
        
        phg0 = gpJeu->getNewX() - 320/2 + 8 + gpJeu->getVueHorz();
        phg1 = gpJeu->getNewY() - 240/2 + 16 + gpJeu->getVueVert();
        if (phg0 < 0) phg0 = 0; if (phg1 < 0) phg1 = 0;
        
        dst.x=0; dst.y=0; src.x=phg0/2; src.y=phg1/2; src.w=320; src.h=240;
        while (src.x >= 256) src.x-=256;
        while (src.y >= 256) src.y-=256;
        SDL_BlitSurface(imageSpe[9], &src, screen, &dst);
    }
    
    
    
    
    if (gpJeu->getZone()==36) {
        dst.x=0; dst.y=0; 
        
        src.x=(phg[0]+(int)afiltre)%256; src.y=(phg[1]+(int)afiltre)%256; src.w=320; src.h=240;
        afiltre+=0.5; if (afiltre >= 256) afiltre-=256;
        
        if (gpJeu->getTransition() && (animtransX || animtransY)) {
            int at = 0; if (animtransX) at = animtransX; else at = animtransY;
            SDL_SetAlpha(imageSpe[10], SDL_SRCALPHA, 255+((128*abs(at))/328));
            src.x=(int)xfiltre; src.y=(int)yfiltre;
        }
        else {
            xfiltre=src.x; yfiltre=src.y;
        }
        SDL_BlitSurface(imageSpe[10], &src, screen, &dst);
    }
    
    if (gpJeu->getTransition() && (animtransX || animtransY) && gpJeu->getNewZone()==36) {
        int at = 0; if (animtransX) at = animtransX; else at = animtransY;
        SDL_SetAlpha(imageSpe[10], SDL_SRCALPHA, 128-((128*abs(at))/328));
        
        int phg0 = 0;
        int phg1 = 0;
        
        phg0 = gpJeu->getNewX() - 320/2 + 8 + gpJeu->getVueHorz();
        phg1 = gpJeu->getNewY() - 240/2 + 16 + gpJeu->getVueVert();
        if (phg0 < 0) phg0 = 0; if (phg1 < 0) phg1 = 0;
        
        afiltre+=0.5; if (afiltre >= 256) afiltre-=256;
        xfiltre=src.x; yfiltre=src.y;
        
        dst.x=0; dst.y=0; src.x=(phg0+(int)afiltre)%256; src.y=(phg1+(int)afiltre)%256; src.w=320; src.h=240;
        SDL_BlitSurface(imageSpe[10], &src, screen, &dst);
    }
    
    if (gpJeu->isDehors()
    && gpJeu->getJoueur()->getAvancement()>=PORTAIL_PRE_PRESENT_UTILISE
    && gpJeu->getJoueur()->getAvancement()<PORTAIL_PRE_PRESENT_FERME
    && gpJeu->getEpoque()==T_PRESENT) {
        dst.x=0; dst.y=0; src.x=0; src.y=0; src.w=320; src.h=240;
        SDL_BlitSurface(imageSpe[17], &src, screen, &dst); 
    }
    
    
    if (niveau > 0) {
        if(gpJeu->isDehors()) niveau=0;
        else {
            if (!gpJeu->getTransition() && !gpJeu->getStop()) niveau--;
            if ((gpJeu->getZone()==46 && region[0]==340*16)
            || (gpJeu->getZone()==53 && region[0]==180*16 && region[1]==75*16)) {
                niveau=0;
            }
            else {
                src.h = 16; src.w = 32;src.x = 0;src.y=32-(etage()*16);
                dst.x = 288; dst.y = 0;
                SDL_BlitSurface(imagelevel, &src, screen, &dst);
            }
        }
    }
    
    if (gpJeu->getTransition() && animtransC>10) {
        dst.x = 0; dst.y = 0;
        SDL_BlitSurface(imagetransit, NULL, screen, &dst);
    }
    
    if (/*gpJeu->getTransition() &&*/ animtransT>0 && imageSpe[8]!=NULL) {
        dst.x = 0; dst.y = 0;
        SDL_BlitSurface(imageSpe[8], NULL, screen, &dst);
    }
    
    if (gpJeu->getZone()==55 && gpJeu->getStop() && !gpJeu->getMenu() 
    && region[0]==40*16 && region[1]==15*16 
    && gpJeu->getJoueur()->getX()>60*16 && gpJeu->getJoueur()->getX()<80*16
    && gpJeu->getJoueur()->getY()>30*16 && gpJeu->getJoueur()->getY()<45*16
    && !gpJeu->getJoueur()->getCoeur(9)) {
        if (gpJeu->getPhg(0)<60*16) gpJeu->setVueHorz(gpJeu->getVueHorz()+2);
        if (gpJeu->getPhg(0)>60*16) gpJeu->setVueHorz(gpJeu->getVueHorz()-2);
        if (gpJeu->getPhg(1)>30*16) gpJeu->setVueVert(gpJeu->getVueVert()-2);
        if (gpJeu->getPhg(1)==30*16) {
            region[0]=60*16; region[2]=80*16;
            region[1]=30*16; region[3]=45*16;
            gpJeu->setStop(false);
        }
    }
}



void Monde::chargeMap(int zone) {
    int cpt1=0,cpt2=0,a,b;
    
    utile = 0;
    
    for (int i = 0; i < 4; i++) region[i]=0;
    for (int i = 0; i < 400; i++) 
        for (int j = 0; j < 400; j++) 
            setValeur(i*CASE, j*CASE, 0, 0, 0, 0);
            
    std::ostringstream oss;
    oss << zone;
#ifdef __vita__
    std::string result = "app0:data/map/carte" + oss.str() + ".map";
#else
    std::string result = "data/map/carte" + oss.str() + ".map";
#endif
    std::ifstream file(result.c_str());
    
    file >> largeur;
    file >> hauteur;

    for (int i=0; i<largeur/16; i++){    
    for (int j=0; j<hauteur/16; j++){
        file >> map[i][j];
        file >> mur[i*2][j*2];
        file >> mur[i*2+1][j*2];
        file >> mur[i*2][j*2+1];
        file >> mur[i*2+1][j*2+1];
    }
    }
    
    file >> cpt1;
    for (int i=0; i<cpt1; i++) {
        file >> a;
        file >> b;
        file >> air[a][b];
    }
    
    file >> cpt2;
    for (int i=0; i<cpt2; i++) {
        file >> a;
        file >> b;
        file >> contenu[a][b];
    }
    corrigeMap(zone);
}

void Monde::transitFull(int nzone, int nx, int ny, int dir) {
    gpJeu->setStop(true);
    gpJeu->setTransition(true);
    if (gpJeu->getZone() != nzone) gpJeu->videListes();
    else niveau = 100;
    gpJeu->setNewZone(nzone);
    gpJeu->setNewX(nx);
    gpJeu->setNewY(ny);
    gpJeu->setNewDir(dir);
    
    animtransC=10;
}

void Monde::transitTemps(int nzone, int nx, int ny, int dir) {
    gpJeu->setStop(true);
    //gpJeu->setTransition(true);
    
    SDL_Rect dst;
    
    dst.y = 0; dst.x = 0;
    
    SDL_FreeSurface(imageSpe[8]);
    imageSpe[8]=NULL;
    
    saveOldMap();
    
    gpJeu->setNewZone(nzone);
    gpJeu->setNewX(nx);
    gpJeu->setNewY(ny);
    gpJeu->setNewDir(dir);
    
    animtransT=10;
}

void Monde::transitTempsRetour() {
    gpJeu->setStop(true);
    restoreOldMap();
    animtransT=10;
}

void Monde::saveOldMap() {
    int i, j;
    //zoneOld = gpJeu->getZone();
    for(i=0;i<400;i++){
        for(j=0;j<400;j++){
            mapOld[i][j]=map[i][j];
            airOld[i][j]=air[i][j];
            contenuOld[i][j]=contenu[i][j];
            murOld[i*2][j*2]=mur[i*2][j*2];
            murOld[i*2+1][j*2]=mur[i*2+1][j*2];
            murOld[i*2][j*2+1]=mur[i*2][j*2+1];
            murOld[i*2+1][j*2+1]=mur[i*2+1][j*2+1];
        }
    }
    gpJeu->saveOldMap();
    /*videlistesOld();
    gpEnnemiOld->suivant = gpEnnemi->suivant;
    gpPersoOld->suivant = gpPerso->suivant;
    gpObjetOld->suivant = gpObjet->suivant;
    gpCaisseOld->suivant = gpCaisse->suivant;
    gpEnnemi->suivant = 0;
    gpPerso->suivant = 0;
    gpObjet->suivant = 0;
    gpCaisse->suivant = 0;*/
}

void Monde::restoreOldMap() {
    int i, j;
    for(i=0;i<400;i++){
        for(j=0;j<400;j++){
            map[i][j]=mapOld[i][j];
            air[i][j]=airOld[i][j];
            contenu[i][j]=contenuOld[i][j];
            mur[i*2][j*2]=murOld[i*2][j*2];
            mur[i*2+1][j*2]=murOld[i*2+1][j*2];
            mur[i*2][j*2+1]=murOld[i*2][j*2+1];
            mur[i*2+1][j*2+1]=murOld[i*2+1][j*2+1];
        }
    }
    gpJeu->restoreOldMap();
    gpJeu->getJoueur()->restoreOldEmpl();
}

void Monde::transitSalle(Direction dir) {
    Joueur* gpJoueur = gpJeu->getJoueur();
    if (gpJoueur->getTypeAnim()==EMMENE) gpJoueur->setTypeAnim(MARCHE);
    
    //labyrinthe de l'ombre
    /*if (gpJeu->getZone()==26 && region[0]>=140*16 && region[0]<280*16) {
        int loupe=0;
        switch(dir) {
            case N :
                if (region[1]==0 || region[1]==15*16 && region[0]==260*16 
                || region[1]==30*16 && (region[0]==220*16 || region[0]==240*16) 
                || region[1]==45*16 && region[0]<200*16 || region[1]==60*16 && region[0]>200*16 
                || region[1]==75*16 && (region[0]==160*16 || region[0]==180*16 || region[0]==240*16) 
                || region[1]==90*16 && (region[0]==140*16 || region[0]==160*16 || region[0]==220*16) 
                ) loupe=1; break;
            case S :
                if (region[1]==90*16 || region[1]==0 && region[0]==260*16 
                || region[1]==15*16 && (region[0]==220*16 || region[0]==240*16) 
                || region[1]==30*16 && region[0]<200*16 || region[1]==45*16 && region[0]>200*16 
                || region[1]==60*16 && (region[0]==160*16 || region[0]==180*16 || region[0]==240*16) 
                || region[1]==75*16 && (region[0]==140*16 || region[0]==160*16 || region[0]==220*16) 
                ) loupe=1; break;
            case O :
                if (region[0]==140*16 
                || region[0]==160*16 && (region[1]==0 || region[1]==30*16 || region[1]==60*16)
                || region[0]==180*16 && (region[1]==15*16 || region[1]==45*16)
                || region[0]==200*16 && region[1]!=0 && region[1]!=45*16
                || region[0]==220*16 && region[1]!=45*16 && region[1]!=90*16
                || region[0]==240*16 && (region[1]==15*16 || region[1]==45*16)
                || region[0]==260*16 && (region[1]==30*16 || region[1]>60*16)
                ) loupe=1; break;
            case E :
                if (region[0]==260*16 
                || region[0]==140*16 && (region[1]==0 || region[1]==30*16 || region[1]==60*16)
                || region[0]==160*16 && (region[1]==15*16 || region[1]==45*16)
                || region[0]==180*16 && region[1]!=0 && region[1]!=45*16
                || region[0]==200*16 && region[1]!=45*16 && region[1]!=90*16
                || region[0]==220*16 && (region[1]==15*16 || region[1]==45*16)
                || region[0]==240*16 && (region[1]==30*16 || region[1]>60*16)
                ) loupe=1; break;
        }
        if (loupe) {
            gpJeu->getAudio()->playSound(5);
            transitFull(26, gpJoueur->getXDep(), gpJoueur->getYDep());
            return;
        }
    }*/
    
    gpJeu->setStop(true);
    gpJeu->setTransition(true);
    
    switch(dir){
        case N : animtransY=-248; gpJoueur->setY(gpJoueur->getY()-4); break;
        case S : animtransY=248; gpJoueur->setY(gpJoueur->getY()+20); break;
        case O : animtransX=-328; gpJoueur->setX(gpJoueur->getX()-4); break;
        case E : animtransX=328; gpJoueur->setX(gpJoueur->getX()+20); break;
    }
    
    //changement de sous zone par défaut
    switch (dir) {
        case N : region[0]=((int)(gpJoueur->getX()/320))*320; region[1]-=15*16; break;
        case S : region[0]=((int)(gpJoueur->getX()/320))*320; region[1]=region[3]; break;
        case O : region[0]-=20*16; region[1]=((int)(gpJoueur->getY()/240))*240; break;
        case E : region[0]=region[2]; region[1]=((int)(gpJoueur->getY()/240))*240; break;
    }
    region[3]=region[1]+15*16;
    region[2]=region[0]+20*16;
}

void Monde::transitZone(int nzone, int decx, int decy, Direction dir) {
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    if (gpJoueur->getTypeAnim()==BARQUE || gpJoueur->getTypeAnim()==RAME) {
        switch (dir) {
            case N : gpJoueur->moveY(4); gpJoueur->setDirection(S); break;
            case S : gpJoueur->moveY(-4); gpJoueur->setDirection(N); break;
            case O : gpJoueur->moveX(4); gpJoueur->setDirection(E); break;
            case E : gpJoueur->moveX(-4); gpJoueur->setDirection(O); break;
        }
        gpJeu->ecrit(254);
        return;
    }
    
    if (gpJoueur->getTypeAnim()==EMMENE) gpJoueur->setTypeAnim(MARCHE);
    int phg[2];
    phg[0] = gpJeu->getPhg(0);
    phg[1] = gpJeu->getPhg(1);
    
    gpJeu->setStop(true);
    gpJeu->setTransition(true);
    gpJeu->videListes();
    gpJeu->setNewZone(nzone);
    
    animtransX=0;
    animtransY=0;
    
    int nx = gpJoueur->getX()-320*decx;
    int ny = gpJoueur->getY()-240*decy;
    
    int savx=gpJoueur->getX()-phg[0];
    int savy=gpJoueur->getY()-phg[1];
    
    for (int i=0; i<42; i++)
        for (int j=0; j<32; j++){
            transMap[i][j]=0;
            transAir[i][j]=0;
        }
    
    //copie de la partie de la carte dans transMap et transAir
    int cor1=0,cor2=0;
    
    int ind1=21, ind2=16;
    if(phg[0]%16==0)ind1=20;
    if(phg[1]%16==0)ind2=15;
    switch(dir){
        case N:cor2=ind2;break;
        case O:cor1=ind1;break;
        default : break;
    }
    
    for (int i=0; i<ind1; i++){
        for (int j=0; j<ind2; j++){
            transMap[i+cor1][j+cor2]=map[((int)((phg[0])/16))+i][((int)((phg[1])/16))+j];
            transAir[i+cor1][j+cor2]=air[((int)((phg[0])/16))+i][((int)((phg[1])/16))+j];
        }
    }
    
    //changement de zone
    chargeMap(nzone);
    
    phg[0]-=decx*320;
    phg[1]-=decy*240;
    if (dir==N) phg[1]-=240;
    if (dir==S) phg[1]+=240;
    if (dir==O) phg[0]-=320;
    if (dir==E) phg[0]+=320;
    
    //copie de la partie de la nouvelle carte dans transMap et transAir
    cor1=0,cor2=0;
    switch(dir){
        case S:cor2=ind2;break;
        case E:cor1=ind1;break;
        default : break;
    }
    for (int i=0; i<ind1; i++){
        for (int j=0; j<ind2; j++){
            transMap[i+cor1][j+cor2]=map[((int)((phg[0])/16))+i][((int)((phg[1])/16))+j];
            transAir[i+cor1][j+cor2]=air[((int)((phg[0])/16))+i][((int)((phg[1])/16))+j];
        }
    }
    
    //copie de transMap vers map
    for (int i=0; i<42; i++){
        for (int j=0; j<32; j++){
            map[i][j]=transMap[i][j];
            air[i][j]=transAir[i][j];
        }
    }
    
    phg[0]=((phg[0])%16);
    phg[1]=((phg[1])%16);
    
    gpJoueur->setX(savx+phg[0]);
    gpJoueur->setY(savy+phg[1]);
    
    switch(dir){
        case N :
            ny-=(28+8);
            phg[1]+=16*ind2;
            gpJoueur->setX(gpJoueur->getX()%320);
            gpJoueur->setY(gpJoueur->getY()%240+240);
            animtransY=-248;
            break;
        case S :
            ny+=(28+4);
            gpJoueur->setX(gpJoueur->getX()%320);
            gpJoueur->setY(gpJoueur->getY()%240+16);
            animtransY=248;
            break;
        case O :
            nx-=28;
            phg[0]+=16*ind1;
            gpJoueur->setX(gpJoueur->getX()%320+320-4);
            gpJoueur->setY(gpJoueur->getY()%240);
            animtransX=-328;
            break;
        case E :
            nx+=28;
            gpJoueur->setX(gpJoueur->getX()%320+16+4);
            gpJoueur->setY(gpJoueur->getY()%240);
            animtransX=328;
            break;
    }
    
    gpJeu->setNewX(nx);
    gpJeu->setNewY(ny);
    gpJeu->setNewDir(-1);
    
    gpJeu->setPhg(phg[0],phg[1]);
}

bool Monde::isChangeTemps() {return (animtransT>0);}

void Monde::defilTransit(SDL_Surface* gpScreen) {
    int phg[2];
    phg[0] = gpJeu->getPhg(0);
    phg[1] = gpJeu->getPhg(1);
    Joueur* gpJoueur = gpJeu->getJoueur();
    int x = gpJoueur->getX();
    int y = gpJoueur->getY();
        
    if(animtransX>0) {
        phg[0]+=8;
        if(animtransX>=328-4) gpJoueur->setX(x+8);
        animtransX-=8;
        if(animtransX<=0){
            if (!gpJeu->isDehors()) detRegion(gpJeu->getZone());
            gpJoueur->saveSemiEmpl();
            if (gpJeu->isDehors()) gpJeu->finZone();
            if (!gpJeu->getText()) gpJeu->setStop(false);
            gpJeu->setTransition(false);
            return;
        }
    }
    if(animtransX<0) {
        phg[0]-=8;
        if(animtransX<=-328+20) gpJoueur->setX(x-8);
        animtransX+=8;
        if(animtransX>=0){
            if (!gpJeu->isDehors()) detRegion(gpJeu->getZone());
            gpJoueur->saveSemiEmpl();
            if (gpJeu->isDehors()) gpJeu->finZone();
            if (!gpJeu->getText()) gpJeu->setStop(false);
            gpJeu->setTransition(false);
            return;
        }
    }
    if(animtransY>0) {
        phg[1]+=8;
        if(animtransY>=248-8) gpJoueur->setY(y+8);
        animtransY-=8;
        if(animtransY<=0){
            if (!gpJeu->isDehors()) detRegion(gpJeu->getZone());
            gpJoueur->saveSemiEmpl();
            if (gpJeu->isDehors()) gpJeu->finZone();
            if (!gpJeu->getText()) gpJeu->setStop(false);
            gpJeu->setTransition(false);
            return;
        }
    }
    if(animtransY<0) {
        phg[1]-=8;
        if(animtransY<=-248+32-8+8) gpJoueur->setY(y-8);
        animtransY+=8;
        if(animtransY>=0){
            if (!gpJeu->isDehors()) detRegion(gpJeu->getZone());
            gpJoueur->saveSemiEmpl();
            if (gpJeu->isDehors()) gpJeu->finZone();
            if (!gpJeu->getText()) gpJeu->setStop(false);
            gpJeu->setTransition(false);
            return;
        }
    }
    if(animtransC>0) {
        animtransC+=10;
        SDL_FillRect(imagetransit, NULL, SDL_MapRGB(imagetransit->format, 0, 0, 0));
        int rayon;
        if (animtransC <=320) rayon = 320-animtransC;
        else rayon=animtransC-330;
        if (animtransC < 310 || animtransC >= 350) filledEllipseRGBA(imagetransit,
                        gpJeu->getJoueur()->getX()-phg[0]+8, 
                        gpJeu->getJoueur()->getY()-phg[1]+16,
                        rayon, rayon*2/3,
                        0, 0, 255, 255);
        SDL_SetColorKey(imagetransit,SDL_SRCCOLORKEY, SDL_MapRGB(imagetransit->format,0,0,255));
        if (animtransC==330) { 
            gpJeu->finZone();
            if (gpJoueur->getTypeAnim()!=TOUCHE && gpJoueur->getTypeAnim()!=MORT)
                gpJoueur->setTypeAnim(AUCUNE);
            return;
        }
        if (animtransC>=650) { 
            gpJeu->testAnim();
            if (!gpJeu->getText()) gpJeu->setStop(false);
            gpJeu->setTransition(false);
            animtransC=0;
            gpJeu->testFin();
            return;
        }
    }
    
    if(animtransT>0) {
        if (imageSpe[8]==NULL) {
            imageSpe[8] = SDL_CreateRGBSurface(SDL_HWSURFACE, 640, 480, 32, 0, 0, 0, 0);
            SDL_Rect dst; dst.x=0; dst.y=0;
            SDL_BlitSurface(gpScreen, NULL, imageSpe[8], &dst);
            gpJeu->finZone();
        }
        animtransT+=5;
        SDL_SetAlpha(imageSpe[8], SDL_SRCALPHA, 255-animtransT);
        
        if (animtransT>255) {
            gpJeu->testAnim();
            if (!gpJeu->getText()) gpJeu->setStop(false);
            //gpJeu->setTransition(false);
            animtransT=0;
            gpJeu->testFin();
            
            //si arrivée non libre
            if (gpJeu->getZone()<1) {
                transitTempsRetour();
                SDL_FreeSurface(imageSpe[8]);
                imageSpe[8] = SDL_CreateRGBSurface(SDL_HWSURFACE, 640, 480, 32, 0, 0, 0, 0);
                SDL_Rect dst; dst.x=0; dst.y=0;
                SDL_BlitSurface(gpScreen, NULL, imageSpe[8], &dst);
                return;
            }
            SDL_Rect* z = gpJoueur->getZoneBase()->getZone();
            int x = gpJoueur->getX();
            int y = gpJoueur->getY();
            if (
            gpJeu->isWater(x + z->x, y + z->y, z->w, z->h) ||
            gpJeu->isPnj(x + z->x, y + z->y, z->w, z->h) || 
            !gpJeu->verifZoneJoueur(x+z->x, y+z->y, z->w, z->h, 2)) {
                transitTempsRetour();
                SDL_FreeSurface(imageSpe[8]);
                imageSpe[8] = SDL_CreateRGBSurface(SDL_HWSURFACE, 640, 480, 32, 0, 0, 0, 0);
                SDL_Rect dst; dst.x=0; dst.y=0;
                SDL_BlitSurface(gpScreen, NULL, imageSpe[8], &dst);
            }
            
            return;
        }
    }
    
    gpJeu->setPhg(phg[0],phg[1]);
}

int Monde::getUtile() {return utile;}
void Monde::setUtile(int i) {utile = i;}

void Monde::rempli(int x, int y, int la, int lo) {
    for (int j=0; j<lo; j++)
        for (int i=0; i<la; i++)
            if (mur[(x+i)*2][(y+j)*2]==-1) setValeur((x+i)*16,(y+j)*16,5152,0);
}

void Monde::vide(int x, int y, int la, int lo) {
    for (int j=y; j<y+lo; j++)
        for (int i=x; i<x+la; i++)
            if (map[i][j]==5152) setValeur(i*16,j*16,5152,-1);
    for (int i=y; i<y+lo; i++)
        for (int j=x; j<x+la; j++) {
            
            if (mur[j*2][i*2]==-1) {
            
            if (mur[(j-1)*2][(i-1)*2]==-1 && mur[j*2][(i-1)*2]==-1 && mur[(j+1)*2][(i-1)*2]==-1
            && mur[(j-1)*2][i*2]==-1 && mur[(j+1)*2][i*2]==-1
            && mur[(j-1)*2][(i+1)*2]==-1 && mur[j*2][(i+1)*2]==-1 && mur[(j+1)*2][(i+1)*2]==-1) {
                setValeur(j*16,i*16,5117,-1);
            }
                
            if (mur[j*2][(i-1)*2]!=-1 && mur[(j-1)*2][i*2]==-1 && mur[(j+1)*2][i*2]==-1 && mur[j*2][(i+1)*2]==-1) setValeur(j*16,i*16,5114,-1);
            if (mur[j*2][(i-1)*2]==-1 && mur[(j-1)*2][i*2]==-1 && mur[(j+1)*2][i*2]==-1 && mur[j*2][(i+1)*2]!=-1) setValeur(j*16,i*16,5120,-1);
            if (mur[j*2][(i-1)*2]==-1 && mur[(j-1)*2][i*2]!=-1 && mur[(j+1)*2][i*2]==-1 && mur[j*2][(i+1)*2]==-1) setValeur(j*16,i*16,5116,-1);
            if (mur[j*2][(i-1)*2]==-1 && mur[(j-1)*2][i*2]==-1 && mur[(j+1)*2][i*2]!=-1 && mur[j*2][(i+1)*2]==-1) setValeur(j*16,i*16,5118,-1);
                
            if (mur[j*2][(i-1)*2]!=-1 && mur[(j-1)*2][i*2]!=-1 && mur[(j+1)*2][i*2]==-1 && mur[j*2][(i+1)*2]==-1) setValeur(j*16,i*16,5113,-1);
            if (mur[j*2][(i-1)*2]!=-1 && mur[(j-1)*2][i*2]==-1 && mur[(j+1)*2][i*2]!=-1 && mur[j*2][(i+1)*2]==-1) setValeur(j*16,i*16,5115,-1);
            if (mur[j*2][(i-1)*2]==-1 && mur[(j-1)*2][i*2]!=-1 && mur[(j+1)*2][i*2]==-1 && mur[j*2][(i+1)*2]!=-1) setValeur(j*16,i*16,5119,-1);
            if (mur[j*2][(i-1)*2]==-1 && mur[(j-1)*2][i*2]==-1 && mur[(j+1)*2][i*2]!=-1 && mur[j*2][(i+1)*2]!=-1) setValeur(j*16,i*16,5121,-1);
                
            if (mur[j*2][(i-1)*2]==-1 && mur[(j-1)*2][i*2]==-1 && mur[(j+1)*2][i*2]==-1 && mur[j*2][(i+1)*2]==-1) {
                if (mur[(j-1)*2][(i-1)*2]!=-1) setValeur(j*16,i*16,5125,-1);
                if (mur[(j+1)*2][(i-1)*2]!=-1) setValeur(j*16,i*16,5124,-1);
                if (mur[(j-1)*2][(i+1)*2]!=-1) setValeur(j*16,i*16,5123,-1);
                if (mur[(j+1)*2][(i+1)*2]!=-1) setValeur(j*16,i*16,5122,-1);
            }
            
            //if (gpJeu->getZone()==25) map[j][i]+=438;
            
            }
        }    
}

void Monde::barque(int pos, bool visible) {
    int a;
    int b;
    switch (pos) {
        case 0 : a=118; b=48; break;
        case 1 : a=105; b=29; break;
        case 2 : a=76; b=54; break;
        case 3 : a=50; b=36; break;
        case 4 : a=32; b=57; break;
        case 5 : a=13; b=18; break;
        default : a=118; b=48; break;
    }
    if (visible) {
        setValeur(a*16, b*16, 1650, 0); setValeur((a+1)*16, b*16, 1651, 0);
        setValeur(a*16, (b+1)*16, 1652, 1656, 0); setValeur((a+1)*16, (b+1)*16, 1653, 1657, 0);
        map[a][b+1]=1652; map[a+1][b+1]=1653;
        for (int i = 0; i < 4; i++) {
            mur[a*2][b*2+i]=2;
            mur[a*2+3][b*2+i]=2;
            mur[a*2+i][b*2+3]=2;
        }
    } else {
        setValeur(a*16, b*16, 28, 0, 12); setValeur((a+1)*16, b*16, 28, 0, 12);
        setValeur(a*16, (b+1)*16, 28, 0, 12); setValeur((a+1)*16, (b+1)*16, 28, 0, 12);
    }
}

void Monde::wagon(int pos, bool visible) {
    int a;
    int b;
    switch (pos) {
        case 0 : a=29*16; b=23*16-10; break;
        case 1 : a=50*16-8; b=22*16-10; break;
        case 2 : a=30*16; b=5*16-10; break;
        default : a=29*16; b=23*16-10; break;
    }
    if (visible) {
        gpJeu->ajouteProjectile(42, N, a, b, 0);
    } else {
        Projectile* proj = gpJeu->getProjectile()->getSuivant();
        while (proj != NULL) {
            if (proj->getId() == 42) proj->setVie(0);
            proj = proj->getSuivant();
        }
    }
}

void Monde::passage(int x, int y, int id) {
    if (gpJeu->isDehors()) {
        if (id < 2 || id == 5) {
            map[x][y]=534; mur[x*2+1][y*2+1]=0;
            map[x+1][y]=535; mur[(x+1)*2][y*2+1]=0;
            map[x][y+1]=536; mur[x*2+1][(y+1)*2]=0; mur[x*2+1][(y+1)*2+1]=0;
            map[x+1][y+1]=537; mur[(x+1)*2][(y+1)*2]=0; mur[(x+1)*2][(y+1)*2+1]=0;
            if (id==1) {
                map[x][y+1]=792;
                map[x+1][y+1]=793;
            }
            if (id==5) {
                map[x][y+1]=4488;
                map[x+1][y+1]=4489;
            }
        }
        if (id==2) {
            map[x][y]=971+963;
            setValeur((x+1)*16, y*16, 972+963, 0, LIBRE, 0);
            map[x+2][y]=973+963;
            map[x][y+1]=974+963;
            setValeur((x+1)*16, (y+1)*16, 975+963, 0, LIBRE, 0);
            map[x+2][y+1]=976+963;
            map[x][y+2]=977+963;
            setValeur((x+1)*16, (y+2)*16, 978+963, 0, LIBRE, 0);
            map[x+2][y+2]=979+963;
            mur[x*2][(y+2)*2]=1;
            mur[x*2+5][(y+2)*2]=1;
        }
        if (id==3) {
            for (int a = 2; a<10; a++) mur[x*2+a][y*2]=0;
            for (int a = 0; a<6; a++) air[x+a][y]=0;
            for (int a = 2; a<4; a++) air[x+a][y+1]=0;
            air[x][y]=2018;
            air[x+5][y]=2019;
        }
        if (id==4) {
            air[x][y-1]=0; air[x+1][y-1]=0;
            setValeur(x*16,y*16,158,0); setValeur((x+1)*16,y*16,159,0);
            contenu[x][y]=0; contenu[x+1][y]=0;
        }
        return;
    }
    switch (gpJeu->getZone()) {
        case 46 :
            if (id == 0) {
                map[x][y]=2765; map[x+1][y]=2766;
                map[x][y+1]=2767; map[x+1][y+1]=2768;
                air[x][y]=2769; air[x+1][y]=2770;
                map[x][y-2]=2771; map[x+1][y-2]=2772;
                map[x][y-1]=2773; map[x+1][y-1]=2774;
                air[x][y-1]=2775; air[x+1][y-1]=2776;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=2777; map[x+1][y]=2778;
                map[x][y+1]=2779; map[x+1][y+1]=2780;
                map[x][y+2]=2781; map[x+1][y+2]=2782;
                air[x][y+1]=2783;
                map[x-2][y]=2784; map[x-1][y]=2785;
                map[x-2][y+1]=2786; map[x-1][y+1]=2787;
                map[x-2][y+2]=2788; map[x-1][y+2]=2789;
                air[x-1][y+1]=2790;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            break;
        case 47 :
            if (id == 0) {
                map[x][y]=2965; map[x+1][y]=2966;
                map[x][y+1]=2967; map[x+1][y+1]=2968;
                air[x][y]=2969; air[x+1][y]=2970;
                map[x][y-2]=2971; map[x+1][y-2]=2972;
                map[x][y-1]=2973; map[x+1][y-1]=2974;
                air[x][y-1]=2975; air[x+1][y-1]=2976;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=2977; map[x+1][y]=2978;
                map[x][y+1]=2979; map[x+1][y+1]=2980;
                map[x][y+2]=2981; map[x+1][y+2]=2982;
                air[x][y+1]=2983;
                map[x-2][y]=2984; map[x-1][y]=2985;
                map[x-2][y+1]=2986; map[x-1][y+1]=2987;
                map[x-2][y+2]=2988; map[x-1][y+2]=2989;
                air[x-1][y+1]=2990;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            break;
        case 48 :
            if (id == 0) {
                map[x][y]=3137; map[x+1][y]=3138;
                map[x][y+1]=3139; map[x+1][y+1]=3140;
                air[x][y]=3141; air[x+1][y]=3142;
                map[x][y-2]=3143; map[x+1][y-2]=3144;
                map[x][y-1]=3145; map[x+1][y-1]=3146;
                air[x][y-1]=3147; air[x+1][y-1]=3148;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=3149; map[x+1][y]=3150;
                map[x][y+1]=3151; map[x+1][y+1]=3152;
                map[x][y+2]=3153; map[x+1][y+2]=3154;
                air[x][y+1]=3155;
                map[x-2][y]=3156; map[x-1][y]=3157;
                map[x-2][y+1]=3158; map[x-1][y+1]=3159;
                map[x-2][y+2]=3160; map[x-1][y+2]=3161;
                air[x-1][y+1]=3162;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            if (id ==4) {
                map[x][y]=3327; map[x+1][y]=3328;
                map[x][y+1]=3329; map[x+1][y+1]=3330;
                air[x][y]=3331; air[x+1][y]=3332;
                map[x][y-2]=3337; map[x+1][y-2]=3338;
                map[x][y-1]=3339; map[x+1][y-1]=3340;
                air[x][y-1]=3341; air[x+1][y-1]=3342;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            
            if (id == 5) {
                setValeur(x*16,y*16,3265,VIDE);
                for (int i = 0; i < 12; i++) setValeur((x+1+i)*16,y*16,3266,VIDE);
                setValeur((x+13)*16,y*16,3267,VIDE);
                for (int j=0; j<7; j++) {
                setValeur(x*16,(y+1+j)*16,3268,VIDE);
                for (int i = 0; i < 12; i++) setValeur((x+1+i)*16,(y+1+j)*16,3277,VIDE);
                setValeur((x+13)*16,(y+1+j)*16,3269,VIDE);
                }
                setValeur(x*16,(y+8)*16,3270,VIDE);
                for (int i = 0; i < 12; i++) setValeur((x+1+i)*16,(y+8)*16,3271,VIDE);
                setValeur((x+13)*16,(y+8)*16,3272,VIDE);
            }
            if (id == 6) {
                setValeur(x*16,y*16,3265,VIDE);
                for (int i = 0; i < 10; i++) setValeur((x+1+i)*16,y*16,3266,VIDE);
                setValeur((x+11)*16,y*16,3267,VIDE);
                for (int j=0; j<5; j++) {
                setValeur(x*16,(y+1+j)*16,3268,VIDE);
                for (int i = 0; i < 10; i++) setValeur((x+1+i)*16,(y+1+j)*16,3277,VIDE);
                setValeur((x+11)*16,(y+1+j)*16,3269,VIDE);
                }
                setValeur(x*16,(y+6)*16,3270,VIDE);
                for (int i = 0; i < 10; i++) setValeur((x+1+i)*16,(y+6)*16,3271,VIDE);
                setValeur((x+11)*16,(y+6)*16,3272,VIDE);
            }
            if (id == 7) {
                setValeur(x*16,y*16,3278,VIDE);
                for (int i = 0; i < 2; i++) setValeur((x+1+i)*16,y*16,3279,VIDE);
                setValeur((x+3)*16,y*16,3280,VIDE);
                for (int j=0; j<2; j++) {
                setValeur(x*16,(y+1+j)*16,3281,VIDE);
                for (int i = 0; i < 2; i++) setValeur((x+1+i)*16,(y+1+j)*16,3290,VIDE);
                setValeur((x+3)*16,(y+1+j)*16,3282,VIDE);
                }
                setValeur(x*16,(y+3)*16,3283,VIDE);
                for (int i = 0; i < 2; i++) setValeur((x+1+i)*16,(y+3)*16,3284,VIDE);
                setValeur((x+3)*16,(y+3)*16,3285,VIDE);
            }
            break;
        case 49 :
            if (id == 0) {
                map[x][y]=3428; map[x+1][y]=3429;
                map[x][y+1]=3382; map[x+1][y+1]=3383;
                air[x][y]=3430; air[x+1][y]=3431;
                map[x][y-2]=3385; map[x+1][y-2]=3386;
                map[x][y-1]=3432; map[x+1][y-1]=3433;
                air[x][y-1]=3434; air[x+1][y-1]=3435;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=3436; map[x+1][y]=3391;
                map[x][y+1]=3437; map[x+1][y+1]=3393;
                map[x][y+2]=3438; map[x+1][y+2]=3395;
                air[x][y+1]=3439; air[x][y]=3440;
                map[x-2][y]=3397; map[x-1][y]=3441;
                map[x-2][y+1]=3399; map[x-1][y+1]=3442;
                map[x-2][y+2]=3401; map[x-1][y+2]=3443;
                air[x-1][y+1]=3444; air[x-1][y]=3445;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            break;
        case 50 :
            if (id == 0) {
                map[x][y]=3616; map[x+1][y]=3617;
                map[x][y+1]=3618; map[x+1][y+1]=3619;
                air[x][y]=3620; air[x+1][y]=3621;
                map[x][y-2]=3622; map[x+1][y-2]=3623;
                map[x][y-1]=3624; map[x+1][y-1]=3625;
                air[x][y-1]=3626; air[x+1][y-1]=3627;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=3628; map[x+1][y]=3629;
                map[x][y+1]=3630; map[x+1][y+1]=3631;
                map[x][y+2]=3632; map[x+1][y+2]=3633;
                air[x][y+1]=3634;
                map[x-2][y]=3635; map[x-1][y]=3636;
                map[x-2][y+1]=3637; map[x-1][y+1]=3638;
                map[x-2][y+2]=3639; map[x-1][y+2]=3640;
                air[x-1][y+1]=3641;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            
            if (id == 3) {
                map[x][y]=3719; map[x+1][y]=3720;
                map[x][y+1]=3721; map[x+1][y+1]=3722;
                map[x][y+2]=3723; map[x+1][y+2]=3724;
                air[x][y+1]=3725;
                map[x-2][y]=3726; map[x-1][y]=3727;
                map[x-2][y+1]=3728; map[x-1][y+1]=3729;
                map[x-2][y+2]=3730; map[x-1][y+2]=3731;
                air[x-1][y+1]=3732;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            if (id == 4) {
                map[x][y]=3741; map[x+1][y]=3742;
                map[x][y+1]=3743; map[x+1][y+1]=3744;
                air[x][y]=3745; air[x+1][y]=3746;
                map[x][y-2]=3747; map[x+1][y-2]=3748;
                map[x][y-1]=3749; map[x+1][y-1]=3750;
                air[x][y-1]=3751; air[x+1][y-1]=3752;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            
            if (id == 8) {
                setValeur(x*16,y*16,3694,-1);
                setValeur((x+1)*16,y*16,3696,-1);
                setValeur(x*16,(y+1)*16,3700,-1);
                setValeur((x+1)*16,(y+1)*16,3702,-1);
            }
            break;
        case 51 :
            if (id == 0) {
                map[x][y]=5035; map[x+1][y]=5036;
                map[x][y+1]=5037; map[x+1][y+1]=5038;
                air[x][y]=5039; air[x+1][y]=5040;
                map[x][y-2]=5041; map[x+1][y-2]=5042;
                map[x][y-1]=5043; map[x+1][y-1]=5044;
                air[x][y-1]=5045; air[x+1][y-1]=5046;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=5047; map[x+1][y]=5048;
                map[x][y+1]=5049; map[x+1][y+1]=5050;
                map[x][y+2]=5051; map[x+1][y+2]=5052;
                air[x][y+1]=5053;
                map[x-2][y]=5054; map[x-1][y]=5055;
                map[x-2][y+1]=5056; map[x-1][y+1]=5057;
                map[x-2][y+2]=5058; map[x-1][y+2]=5059;
                air[x-1][y+1]=5060;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            
            if (id == 3) {
                map[x][y]=5138; map[x+1][y]=5139;
                map[x][y+1]=5140; map[x+1][y+1]=5141;
                map[x][y+2]=5142; map[x+1][y+2]=5143;
                air[x][y+1]=5144;
                map[x-2][y]=5145; map[x-1][y]=5146;
                map[x-2][y+1]=5147; map[x-1][y+1]=5148;
                map[x-2][y+2]=5149; map[x-1][y+2]=5150;
                air[x-1][y+1]=5151;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            if (id == 4) {
                map[x][y]=5189; map[x+1][y]=5190;
                map[x][y+1]=5191; map[x+1][y+1]=5192;
                air[x][y]=5193; air[x+1][y]=5194;
                map[x][y-2]=5195; map[x+1][y-2]=5196;
                map[x][y-1]=5197; map[x+1][y-1]=5198;
                air[x][y-1]=5199; air[x+1][y-1]=5200;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            break;
        case 52 :
            if (id == 0) {
                map[x][y]=3846; map[x+1][y]=3847;
                map[x][y+1]=3848; map[x+1][y+1]=3849;
                air[x][y]=3850; air[x+1][y]=3851;
                map[x][y-2]=3852; map[x+1][y-2]=3853;
                map[x][y-1]=3854; map[x+1][y-1]=3855;
                air[x][y-1]=3856; air[x+1][y-1]=3857;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=3858; map[x+1][y]=3859;
                map[x][y+1]=3860; map[x+1][y+1]=3861;
                map[x][y+2]=3862; map[x+1][y+2]=3863;
                air[x][y+1]=3864;
                map[x-2][y]=3865; map[x-1][y]=3866;
                map[x-2][y+1]=3867; map[x-1][y+1]=3868;
                map[x-2][y+2]=3869; map[x-1][y+2]=3870;
                air[x-1][y+1]=3871;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            break;
        case 53 :
            if (id == 0) {
                map[x][y]=5286; map[x+1][y]=5287;
                map[x][y+1]=5288; map[x+1][y+1]=5289;
                air[x][y]=5290; air[x+1][y]=5291;
                map[x][y-2]=5292; map[x+1][y-2]=5293;
                map[x][y-1]=5294; map[x+1][y-1]=5295;
                air[x][y-1]=5296; air[x+1][y-1]=5297;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=5298; map[x+1][y]=5299;
                map[x][y+1]=5300; map[x+1][y+1]=5301;
                map[x][y+2]=5302; map[x+1][y+2]=5303;
                air[x][y+1]=5304;
                map[x-2][y]=5305; map[x-1][y]=5306;
                map[x-2][y+1]=5307; map[x-1][y+1]=5308;
                map[x-2][y+2]=5309; map[x-1][y+2]=5310;
                air[x-1][y+1]=5311;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            
            if (id == 8) {
                setValeur(x*16,y*16,5373,-1);
                setValeur((x+1)*16,y*16,5375,-1);
                setValeur(x*16,(y+1)*16,5379,-1);
                setValeur((x+1)*16,(y+1)*16,5381,-1);
            }
            break;
        case 54 :
            if (id == 0) {
                map[x][y]=5479; map[x+1][y]=5480;
                map[x][y+1]=5481; map[x+1][y+1]=5482;
                air[x][y]=5483; air[x+1][y]=5484;
                map[x][y-2]=5485; map[x+1][y-2]=5486;
                map[x][y-1]=5487; map[x+1][y-1]=5488;
                air[x][y-1]=5489; air[x+1][y-1]=5490;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=5491; map[x+1][y]=5492;
                map[x][y+1]=5493; map[x+1][y+1]=5494;
                map[x][y+2]=5495; map[x+1][y+2]=5496;
                air[x][y+1]=5497;
                map[x-2][y]=5498; map[x-1][y]=5499;
                map[x-2][y+1]=5500; map[x-1][y+1]=5501;
                map[x-2][y+2]=5502; map[x-1][y+2]=5503;
                air[x-1][y+1]=5504;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            
            if (id == 8) {
                setValeur(x*16,y*16,5566,-1);
                setValeur((x+1)*16,y*16,5568,-1);
                setValeur(x*16,(y+1)*16,5572,-1);
                setValeur((x+1)*16,(y+1)*16,5574,-1);
            }
            break;
        case 55 :
            if (id == 0) {
                map[x][y]=5668; map[x+1][y]=5669;
                map[x][y+1]=5670; map[x+1][y+1]=5671;
                air[x][y]=5672; air[x+1][y]=5673;
                map[x][y-2]=5674; map[x+1][y-2]=5675;
                map[x][y-1]=5676; map[x+1][y-1]=5677;
                air[x][y-1]=5678; air[x+1][y-1]=5679;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=5680; map[x+1][y]=5681;
                map[x][y+1]=5682; map[x+1][y+1]=5683;
                map[x][y+2]=5684; map[x+1][y+2]=5685;
                air[x][y+1]=5686;
                map[x-2][y]=5687; map[x-1][y]=5688;
                map[x-2][y+1]=5689; map[x-1][y+1]=5690;
                map[x-2][y+2]=5691; map[x-1][y+2]=5692;
                air[x-1][y+1]=5693;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            
            if (id == 4) {
                map[x][y]=5838; map[x+1][y]=5839;
                map[x][y+1]=5840; map[x+1][y+1]=5841;
                air[x][y]=5842; air[x+1][y]=5843;
                map[x][y-2]=5844; map[x+1][y-2]=5845;
                map[x][y-1]=5846; map[x+1][y-1]=5847;
                air[x][y-1]=5848; air[x+1][y-1]=5849;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            
            if (id == 9) {
                setValeur(x*16,y*16,5798,-1);
                setValeur((x+1)*16,y*16,5798,-1);
                setValeur((x+2)*16,y*16,5798,-1);
                setValeur((x+3)*16,y*16,5798,-1);
                setValeur(x*16,(y+1)*16,5809,-1);
                setValeur((x+1)*16,(y+1)*16,5809,-1);
                setValeur((x+2)*16,(y+1)*16,5809,-1);
                setValeur((x+3)*16,(y+1)*16,5809,-1);
                setValeur(x*16,(y+2)*16,5805,-1);
                setValeur((x+1)*16,(y+2)*16,5803,-1);
                setValeur((x+2)*16,(y+2)*16,5803,-1);
                setValeur((x+3)*16,(y+2)*16,5806,-1);
                for (int i = x*2-18; i < x*2+18; i++) mur[i][y*2+3]=2;
            }
            break;
        case 56 :
            if (id == 0) {
                map[x][y]=5914; map[x+1][y]=5915;
                map[x][y+1]=5916; map[x+1][y+1]=5917;
                air[x][y]=5918; air[x+1][y]=5919;
                map[x][y-2]=5920; map[x+1][y-2]=5921;
                map[x][y-1]=5922; map[x+1][y-1]=5923;
                air[x][y-1]=5924; air[x+1][y-1]=5925;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=5926; map[x+1][y]=5927;
                map[x][y+1]=5928; map[x+1][y+1]=5929;
                map[x][y+2]=5930; map[x+1][y+2]=5931;
                air[x][y+1]=5932;
                map[x-2][y]=5933; map[x-1][y]=5934;
                map[x-2][y+1]=5935; map[x-1][y+1]=5936;
                map[x-2][y+2]=5937; map[x-1][y+2]=5938;
                air[x-1][y+1]=5939;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            
            if (id == 9) {
                mur[(x+3)/8][(y+11)/8]=0;
                mur[(x+3)/8+1][(y+11)/8]=0;
                mur[(x+3)/8][(y+11)/8+1]=0;
                mur[(x+3)/8+1][(y+11)/8+1]=0;
            }
            break;
        case 57 :
            if (y < 105) {
            if (id == 0) {
                map[x][y]=6030; map[x+1][y]=6031;
                map[x][y+1]=6032; map[x+1][y+1]=6033;
                air[x][y]=6034; air[x+1][y]=6035;
                map[x][y-2]=6036; map[x+1][y-2]=6037;
                map[x][y-1]=6038; map[x+1][y-1]=6039;
                air[x][y-1]=6040; air[x+1][y-1]=6041;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=6042; map[x+1][y]=6043;
                map[x][y+1]=6044; map[x+1][y+1]=6045;
                map[x][y+2]=6046; map[x+1][y+2]=6047;
                air[x][y+1]=6048;
                map[x-2][y]=6049; map[x-1][y]=6050;
                map[x-2][y+1]=6051; map[x-1][y+1]=6052;
                map[x-2][y+2]=6053; map[x-1][y+2]=6054;
                air[x-1][y+1]=6055;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            } else {
            if (id == 0) {
                map[x][y]=6154; map[x+1][y]=6155;
                map[x][y+1]=6156; map[x+1][y+1]=6157;
                air[x][y]=6158; air[x+1][y]=6159;
                map[x][y-2]=6160; map[x+1][y-2]=6161;
                map[x][y-1]=6162; map[x+1][y-1]=6163;
                air[x][y-1]=6164; air[x+1][y-1]=6165;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=6166; map[x+1][y]=6167;
                map[x][y+1]=6168; map[x+1][y+1]=6169;
                map[x][y+2]=6170; map[x+1][y+2]=6171;
                air[x][y+1]=6172;
                map[x-2][y]=6173; map[x-1][y]=6174;
                map[x-2][y+1]=6175; map[x-1][y+1]=6176;
                map[x-2][y+2]=6177; map[x-1][y+2]=6178;
                air[x-1][y+1]=6179;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            }
            if (id == 4) {
                map[x][y]=6228; map[x+1][y]=6229;
                map[x][y+1]=6230; map[x+1][y+1]=6231;
                air[x][y]=6232; air[x+1][y]=6233;
                map[x][y-2]=6234; map[x+1][y-2]=6235;
                map[x][y-1]=6236; map[x+1][y-1]=6237;
                air[x][y-1]=6238; air[x+1][y-1]=6239;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            break;
        case 58 :
            if (id == 0) {
                map[x][y]=6380; map[x+1][y]=6381;
                map[x][y+1]=6382; map[x+1][y+1]=6383;
                air[x][y]=6384; air[x+1][y]=6385;
                map[x][y-2]=6386; map[x+1][y-2]=6387;
                map[x][y-1]=6388; map[x+1][y-1]=6389;
                air[x][y-1]=6390; air[x+1][y-1]=6391;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=6392; map[x+1][y]=6393;
                map[x][y+1]=6394; map[x+1][y+1]=6395;
                map[x][y+2]=6396; map[x+1][y+2]=6397;
                air[x][y+1]=6398;
                map[x-2][y]=6399; map[x-1][y]=6400;
                map[x-2][y+1]=6401; map[x-1][y+1]=6402;
                map[x-2][y+2]=6403; map[x-1][y+2]=6404;
                air[x-1][y+1]=6405;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            
            if (id == 3) {
                map[x][y]=6426; map[x+1][y]=6427;
                map[x][y+1]=6428; map[x+1][y+1]=6429;
                map[x][y+2]=6430; map[x+1][y+2]=6431;
                air[x][y+1]=6432;
                map[x-2][y]=6433; map[x-1][y]=6434;
                map[x-2][y+1]=6435; map[x-1][y+1]=6436;
                map[x-2][y+2]=6437; map[x-1][y+2]=6438;
                air[x-1][y+1]=6439;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            break;
        case 59 :
            if (id == 0) {
                map[x][y]=6536; map[x+1][y]=6537;
                map[x][y+1]=6538; map[x+1][y+1]=6539;
                air[x][y]=6540; air[x+1][y]=6541;
                map[x][y-2]=6542; map[x+1][y-2]=6543;
                map[x][y-1]=6544; map[x+1][y-1]=6545;
                air[x][y-1]=6534; air[x+1][y-1]=6535;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=6546; map[x+1][y]=6547;
                map[x][y+1]=6548; map[x+1][y+1]=6549;
                map[x][y+2]=6550; map[x+1][y+2]=6551;
                air[x][y+1]=6552;
                map[x-2][y]=6553; map[x-1][y]=6554;
                map[x-2][y+1]=6555; map[x-1][y+1]=6556;
                map[x-2][y+2]=6557; map[x-1][y+2]=6558;
                air[x-1][y+1]=6559;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            break;
        case 60 :
            if (id == 0) {
                map[x][y]=6683; map[x+1][y]=6684;
                map[x][y+1]=6685; map[x+1][y+1]=6686;
                air[x][y]=6687; air[x+1][y]=6688;
                map[x][y-2]=6689; map[x+1][y-2]=6690;
                map[x][y-1]=6691; map[x+1][y-1]=6692;
                air[x][y-1]=6693; air[x+1][y-1]=6694;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=6695; map[x+1][y]=6696;
                map[x][y+1]=6697; map[x+1][y+1]=6698;
                map[x][y+2]=6699; map[x+1][y+2]=6700;
                air[x][y+1]=6701;
                map[x-2][y]=6702; map[x-1][y]=6703;
                map[x-2][y+1]=6704; map[x-1][y+1]=6705;
                map[x-2][y+2]=6706; map[x-1][y+2]=6707;
                air[x-1][y+1]=6708;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            break;
        case 63 :
        case 67 :
        case 68 :
        case 69 :
        case 137 :
            if (id == 0 || id ==4) {
                map[x][y]=2238; map[x+1][y]=2239;
                map[x][y+1]=2240; map[x+1][y+1]=2241;
                air[x][y]=2242; air[x+1][y]=2243;
                map[x][y-2]=2244; map[x+1][y-2]=2245;
                map[x][y-1]=2246; map[x+1][y-1]=2247;
                air[x][y-1]=2236; air[x+1][y-1]=2237;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1 || id ==3) {
                map[x][y]=2248; map[x+1][y]=2249;
                map[x][y+1]=2250; map[x+1][y+1]=2251;
                map[x][y+2]=2252; map[x+1][y+2]=2253;
                air[x][y+1]=2254;
                map[x-2][y]=2255; map[x-1][y]=2256;
                map[x-2][y+1]=2257; map[x-1][y+1]=2258;
                map[x-2][y+2]=2259; map[x-1][y+2]=2260;
                air[x-1][y+1]=2261;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            break;
        case 64 :
        case 70 :
            if (id == 0) {
                air[x][y]=0; air[x+1][y]=0;
                setValeur(x*16,(y+1)*16,158,0);
                setValeur((x+1)*16,(y+1)*16,159,0);
            }
            if (id == 1) {
                map[x][y]=3417; map[x+1][y]=3417;
            }
            if (id == 10) {
                map[x][y]=3416; map[x+1][y]=3416;
            }
            break;
        case 150 :
            if (id == 0) {
                map[x][y]=2418; map[x+1][y]=2419;
                map[x][y+1]=2420; map[x+1][y+1]=2421;
                air[x][y]=2422; air[x+1][y]=2423;
                map[x][y-2]=2424; map[x+1][y-2]=2425;
                map[x][y-1]=2426; map[x+1][y-1]=2427;
                air[x][y-1]=2428; air[x+1][y-1]=2429;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 1) {
                map[x][y]=2430; map[x+1][y]=2431;
                map[x][y+1]=2432; map[x+1][y+1]=2433;
                map[x][y+2]=2434; map[x+1][y+2]=2435;
                air[x][y+1]=2436;
                map[x-2][y]=2437; map[x-1][y]=2438;
                map[x-2][y+1]=2439; map[x-1][y+1]=2440;
                map[x-2][y+2]=2441; map[x-1][y+2]=2442;
                air[x-1][y+1]=2443;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            if (id == 10) {
                map[x][y]=2238; map[x+1][y]=2239;
                map[x][y+1]=2240; map[x+1][y+1]=2241;
                air[x][y]=2242; air[x+1][y]=2243;
                map[x][y-2]=2244; map[x+1][y-2]=2245;
                map[x][y-1]=2246; map[x+1][y-1]=2247;
                air[x][y-1]=2236; air[x+1][y-1]=2237;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            if (id == 11) {
                map[x][y]=2248; map[x+1][y]=2249;
                map[x][y+1]=2250; map[x+1][y+1]=2251;
                map[x][y+2]=2252; map[x+1][y+2]=2253;
                air[x][y+1]=2254;
                map[x-2][y]=2255; map[x-1][y]=2256;
                map[x-2][y+1]=2257; map[x-1][y+1]=2258;
                map[x-2][y+2]=2259; map[x-1][y+2]=2260;
                air[x-1][y+1]=2261;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            break;
        case 154 :
            if (id == 1) {
                map[x][y]=2668; map[x+1][y]=2669;
                map[x][y+1]=2670; map[x+1][y+1]=2671;
                map[x][y+2]=2672; map[x+1][y+2]=2673;
                air[x][y+1]=2674;
                map[x-2][y]=2675; map[x-1][y]=2676;
                map[x-2][y+1]=2677; map[x-1][y+1]=2678;
                map[x-2][y+2]=2679; map[x-1][y+2]=2680;
                air[x-1][y+1]=2681;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            if (id == 4) {
                map[x][y]=2248; map[x+1][y]=2249;
                map[x][y+1]=2250; map[x+1][y+1]=2251;
                map[x][y+2]=2252; map[x+1][y+2]=2253;
                air[x][y+1]=2254;
                map[x-2][y]=2698; map[x-1][y]=2699;
                map[x-2][y+1]=2700; map[x-1][y+1]=2701;
                map[x-2][y+2]=2702; map[x-1][y+2]=2703;
                air[x-1][y+1]=2704;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+2]=0;
                for (int j = x*2-3; j < x*2+4; j++) mur[j][y*2+3]=0;
            }
            break;
        case 155 :
            if (id ==4) {
                map[x][y]=4739; map[x+1][y]=4740;
                map[x][y+1]=4741; map[x+1][y+1]=4742;
                air[x][y]=4743; air[x+1][y]=4744;
                map[x][y-2]=4745; map[x+1][y-2]=4746;
                map[x][y-1]=4747; map[x+1][y-1]=4748;
                air[x][y-1]=4749; air[x+1][y-1]=4750;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+1][j]=0;
                for (int j = y*2-3; j < y*2+4; j++) mur[x*2+2][j]=0;
            }
            break;
    }
}

void Monde::animCafe() {
    gpJeu->getJoueur()->boostCafe();
    gpJeu->getJoueur()->setImmo(true);
    air[13][5]=4671;
    lastAnimTime = SDL_GetTicks();
    anim=0;
}
