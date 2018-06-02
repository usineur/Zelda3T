/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <iostream>

#include <SDL/SDL.h>
#include "Lang.h"

#include "Keyboard.h"

#define BTN_TRIANGLE 0
#define BTN_CIRCLE 1
#define BTN_CROSS 2
#define BTN_SQUARE 3
#define BTN_LTRIGGER 4
#define BTN_RTRIGGER 5
#define BTN_DOWN 6
#define BTN_LEFT 7
#define BTN_UP 8
#define BTN_RIGHT 9
#define BTN_SELECT 10
#define BTN_START 11

#define LSTICK 0
#define RSTICK 1
#define STICK_UP 0
#define STICK_DOWN 1
#define STICK_LEFT 2
#define STICK_RIGHT 3

Keyboard::Keyboard(Jeu* jeu, Carte* carte, Encyclopedie* encycl, Poissons* poissons,
SDL_Surface* screen, int m, bool e) : 
    gpJeu(jeu), gpCarte(carte), gpEncyclopedie(encycl), gpPoissons(poissons), mode(m), 
    gFullScreen(1), gpScreen(screen), tmp(0), tmpx(0), tmpc(0), tmpw(0), tmpt(0), tmpp(0), 
    tmpm(0), tmpo(0), tmptp(0), tmpl(0), tmpi(0), ligne(0), colonne(0), ligneOption(3), 
#ifdef __vita__
    volume(MIX_MAX_VOLUME), volson(32), ligneRecord(3), colonneRecord(0), temps(0), ligneVal(0), 
#else
    volume(32), volson(32), ligneRecord(3), colonneRecord(0), temps(0), ligneVal(0), 
#endif
    intro(0), telep(0), etire(e) {
    for (int i = 0; i < 3; i++) save[i]=0;
    for (int i = 0; i < 9; i++) rang[i]=0;
    loadP();
    loadOldP();
    gpJeu->getAudio()->setVolume(volume);
    gpJeu->getAudio()->setVolson(volson);
#ifdef __vita__
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    joystick = SDL_JoystickOpen(0);
#endif
}

void Keyboard::saveP() {
    int languageID = getLanguage();
#ifdef __vita__
    ofstream f("ux0:data/z3t/save/system.dat",ios::out | ios::binary);
#else
    ofstream f("data/save/system.dat",ios::out | ios::binary);
#endif
    f.write((char *)&volume,sizeof(int));
    f.write((char *)&volson,sizeof(int));
    f.write((char *)&temps,sizeof(int));
    for (int i = 0; i < 3; i++) f.write((char *)&rang[6+i],sizeof(int));
    f.write((char *)&languageID,sizeof(int));
    f.close();
}

void Keyboard::loadP() {
#ifdef __vita__
    ifstream f("ux0:data/z3t/save/system.dat",ios::out | ios::binary);
#else
    ifstream f("data/save/system.dat",ios::in | ios::binary);
#endif
    if(!f.is_open()) return;
    f.read((char *)&volume,sizeof(int));
    f.read((char *)&volson,sizeof(int));
    f.read((char *)&temps,sizeof(int));
    for (int i = 0; i < 3; i++) f.read((char *)&rang[6+i],sizeof(int));
    if(!f.eof()){ //for retro compatibility
		 int languageID = DEFAULT_LANG;
         f.read((char *)&languageID,sizeof(int));
		 setLanguage(gpJeu, languageID);  
 	}
    f.close();
}

void Keyboard::loadOldP() {
    ifstream f("../Zelda Return of the Hylian/data/save/system.dat",ios::in | ios::binary);
    if(f.is_open()) {
        int i;
        f.read((char *)&i,sizeof(int));
        f.read((char *)&i,sizeof(int));
        f.read((char *)&i,sizeof(int));
        for (i = 0; i < 3; i++) f.read((char *)&rang[i],sizeof(int));
        f.close();
    }
    
    ifstream f2("../Zelda Oni Link Begins/data/save/system.dat",ios::in | ios::binary);
    if(f2.is_open()) {
        int i;
        f2.read((char *)&i,sizeof(int));
        f2.read((char *)&i,sizeof(int));
        f2.read((char *)&i,sizeof(int));
        for (i = 0; i < 3; i++) f2.read((char *)&rang[3+i],sizeof(int));
        f2.close();
    }
}

int Keyboard::getLigne() {return ligne;}
int Keyboard::getColonne() {return colonne;}
int Keyboard::getSave(int i) {return save[i];}
void Keyboard::setSave(int i, int val) {save[i]=val;}
int Keyboard::getLigneOption() {return ligneOption;}
int Keyboard::getVolume() {return volume;}
int Keyboard::getVolson() {return volson;}
int Keyboard::getLigneRecord() {return ligneRecord;}
int Keyboard::getColonneRecord() {return colonneRecord;}
int Keyboard::getTemps() {return temps;}
void Keyboard::setTemps(int t) {temps=t;}
int Keyboard::getRang(int i) {return rang[i];}
void Keyboard::setRang(int i) {rang[i]=1;}
int Keyboard::getLigneVal() {return ligneVal;}
int Keyboard::getIntro() {return intro;}
int Keyboard::getMode() {return mode;}
void Keyboard::setMode(int i) {mode=i;}

int Keyboard::attendEntreeOuTemps(Uint32 t) {
    Uint8* k;
    Uint32 tc = SDL_GetTicks();
    while (SDL_GetTicks() - tc < t) {
    while (SDL_PollEvent(&event)) {}
    k = SDL_GetKeyState(NULL);
    if (k[SDLK_RETURN] || buttonPressed(BTN_CROSS)) return 1;
    SDL_Delay(20);
    }
    return 0;
}

int Keyboard::gererClavier() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
#ifdef __vita__
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
                if (joystick && pollKey(event) == -1) return -1;
                break;
#endif
            case SDL_QUIT : return -1;
            case SDL_KEYDOWN :
                if (pollKey(event) == -1) return -1;
                break;
        }
    }
    keys = SDL_GetKeyState(NULL);
    pollKeys(keys);
    
    return 0;
}

void Keyboard::toggleFullScreen() {
    gFullScreen = (gFullScreen ? 0 : SDL_FULLSCREEN);
    gFullScreen ? SDL_ShowCursor(SDL_DISABLE) : SDL_ShowCursor(SDL_ENABLE);
    if (etire || gFullScreen == 0) {
        gpScreen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE
                                    |SDL_DOUBLEBUF|gFullScreen);
    } else {
        gpScreen = SDL_SetVideoMode(320, 240, 32, SDL_HWSURFACE
                                    |SDL_DOUBLEBUF|gFullScreen);
    }
}

int Keyboard::isFullScreen() {
    return gFullScreen;
}

int Keyboard::pollKey(SDL_Event event) {
#ifdef __vita__
    switch (event.jbutton.button) {
        case BTN_START :
#else
    switch (event.key.keysym.sym) {
        case SDLK_ESCAPE :
#endif
            if (mode==0) { if (!gpJeu->getStop() && !gpJeu->getJoueur()->getImmo() 
            && gpJeu->getJoueur()->getVie()>0) 
                gpJeu->ecrit(421);
#ifdef __vita__
            }
#else
            } else if (mode<8 || mode==9 || mode==15 || mode==16 
            || (mode >18 && mode!=22 && mode!=23 && mode!=24 && mode!=25 
            && mode!=26 && mode!=27 && mode!=28)) return -1;
#endif
            break;
#ifdef __vita__
        case BTN_SELECT :
#else
        case SDLK_F1 :
#endif
            if (mode == 0) {mode = 17; gpJeu->getGenerique()->initAide1(); 
                gpJeu->getAudio()->playSound(1);}
            break;
#ifndef __vita__
        case SDLK_F4 :
            if (event.key.keysym.mod & KMOD_ALT) return -1;
            break;
        case SDLK_RETURN :
            if (event.key.keysym.mod & KMOD_CTRL) toggleFullScreen();
            break;
#endif
        default : break;
    }
    return 0;
}

void Keyboard::pollKeys(Uint8* keys) {
    Joueur* gpJoueur;
    int vit;
    int avance;
    int nbdir;
    int leverJeter = 0;
    switch (mode) {
        case 0 :
            if (gpJeu->getMonde()->isChangeTemps()) return;
            
            gpJoueur = gpJeu->getJoueur();
            
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                if (gpJoueur->getTypeAnim() == MORT) gpJoueur->revie();
#ifndef __vita__
                else if (!gpJeu->getStop() && !gpJeu->getMenu()) gpJeu->setMenu(true);
#endif
                else if (gpJeu->getMenu()) gpJeu->setMenu(false);
                else if (gpJeu->getText() && !gpJeu->getTransition()) 
                    gpJeu->setText(gpJeu->getTexte()->suite());
                else
                    leverJeter = 1;
                tmp = 1;
            }
#ifdef __vita__
            if (buttonPressed(BTN_RIGHT) && !gpJeu->getStop() && !gpJeu->getMenu() && tmp == 0) {
                gpJeu->setMenu(true);
                tmp = 1;
            }
#endif
            if ((!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !gpJeu->getMenu()) || (gpJeu->getMenu() 
            && !(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) 
            && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)))) tmp=0;
            
            if (gpJeu->getText() && gpJeu->getTexte()->isFinished()) {
                if(tmpt==0){
                    tmpt=1;
                    switch (gpJeu->getTexte()->getId()) {
                        case 77 : case 80 : case 83 : case 86 : case 89 : case 92 : case 96 :
                        case 99 : case 102 : case 107 : case 126 : case 129 : case 132 : 
                        case 135 : case 138 : case 141 : case 144 : case 147 : case 150 :
                        case 159 : case 162 : case 165 : case 168 : case 171 : case 180 :
                        case 191 : case 204 : case 215 : case 218 : case 220 : case 222 :
                        case 228 : case 230 : case 232 : case 234 : case 240 : case 245 :
                        case 251 : case 265 : case 268 : case 271 : case 273 : case 278 : 
                        case 281 : case 290 : case 299 : case 309 : case 351 : case 356 : 
                        case 368 : case 370 : case 376 : case 378 : case 380 : case 383 : 
                        case 387 : case 390 : case 393 : case 395 : case 398 : case 400 : 
                        case 403 : case 413 : case 415 : case 426 : case 433 : case 447 :
                        case 451 : case 461 : case 464 : case 467 : case 470 : case 473 : 
                        case 506 : case 524 : case 530 : case 555 : case 561 : case 569 : 
                        case 576 : case 581 : case 586 : case 593 : case 600 : case 605 : 
                        case 614 : case 641 : case 643 : case 645 : case 647 : case 649 : 
                        case 678 : case 680 : case 688 : case 701 : case 706 : case 721 : 
                        case 728 : case 734 : case 740 : case 750 : case 752 : case 754 : 
                        case 756 : case 758 : case 767 : case 769 : case 780 : case 789 : 
                        case 823 : case 834 : case 859 : case 888 : case 896 : case 908 : 
                        case 916 : case 1048: case 1085: case 1114: case 1120: case 1126:
                        case 1132: case 1139: case 1141: case 1145: case 1154: case 1158:
                        case 1162: case 1166: case 1170: case 1174: case 1178: case 1182: 
                        case 1186: case 1190: case 1194: case 1198: case 1202: case 1206: 
                        case 1210: case 1214: case 1218: case 1222: case 1226: case 1230: 
                        case 1234: case 1238: case 1242: case 1246: case 1250: case 1254: 
                        case 1258: case 1262: case 1266: case 1270: case 1274: case 1278: 
                        case 1282: case 1286: case 1290: case 1294: case 1298: case 1302: 
                        case 1306: case 1310: case 1314: case 1327:
                            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) || (keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT))) {
                                gpJeu->getAudio()->playSound(3);
                                gpJeu->getTexte()->changeId(gpJeu->getTexte()->getId()+1);
                            }
                            break;
                        case 78 : case 81 : case 84 : case 87 : case 90 : case 93 : case 97 :
                        case 100 : case 103 : case 108 : case 127 : case 130 : case 133 :
                        case 136 : case 139 : case 142 : case 145 : case 148 : case 151 :
                        case 160 : case 163 : case 166 : case 169 : case 172 : case 181 :
                        case 192 : case 205 : case 216 : case 219 : case 221 : case 223 :
                        case 229 : case 231 : case 233 : case 235 : case 241 : case 246 :
                        case 252 : case 266 : case 269 : case 272 : case 274 : case 279 : 
                        case 282 : case 291 : case 300 : case 310 : case 352 : case 357 : 
                        case 369 : case 371 : case 377 : case 379 : case 381 : case 384 : 
                        case 388 : case 391 : case 394 : case 396 : case 399 : case 401 : 
                        case 404 : case 414 : case 416 : case 427 : case 434 : case 448 :
                        case 452 : case 462 : case 465 : case 468 : case 471 : case 474 : 
                        case 507 : case 525 : case 531 : case 556 : case 562 : case 570 : 
                        case 577 : case 582 : case 587 : case 594 : case 601 : case 606 : 
                        case 615 : case 642 : case 644 : case 646 : case 648 : case 650 : 
                        case 679 : case 681 : case 689 : case 702 : case 707 : case 722 : 
                        case 729 : case 735 : case 741 : case 751 : case 753 : case 755 : 
                        case 757 : case 759 : case 768 : case 770 : case 781 : case 790 : 
                        case 824 : case 835 : case 860 : case 889 : case 897 : case 909 : 
                        case 917 : case 1049: case 1086: case 1115: case 1121: case 1127:
                        case 1133: case 1140: case 1142: case 1146: case 1155: case 1159:
                        case 1163: case 1167: case 1171: case 1175: case 1179: case 1183: 
                        case 1187: case 1191: case 1195: case 1199: case 1203: case 1207: 
                        case 1211: case 1215: case 1219: case 1223: case 1227: case 1231: 
                        case 1235: case 1239: case 1243: case 1247: case 1251: case 1255: 
                        case 1259: case 1263: case 1267: case 1271: case 1275: case 1279: 
                        case 1283: case 1287: case 1291: case 1295: case 1299: case 1303: 
                        case 1307: case 1311: case 1315: case 1328:
                            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) || (keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT))) {
                                gpJeu->getAudio()->playSound(3);
                                gpJeu->getTexte()->changeId(gpJeu->getTexte()->getId()-1);
                            }
                            break;
                        case 48 : case 49 : case 50 : case 51 : case 52 : case 53 :
                        case 54 : case 55 : case 56 : case 57 : case 58 : case 59 :
                        case 60 : case 61 : case 62 : case 63 : case 64 : case 65 : 
                        case 66 : case 199 : case 200 : case 410 : case 411 : case 412 : 
                        case 421 : case 422 : case 423 : case 513 : case 514 : case 515 : 
                        case 516 : case 564 : case 565 : case 566 : case 608 : case 609 : 
                        case 610 : case 675 : case 676 : case 677 : case 709 : case 710 : 
                        case 711 : case 764 : case 765 : case 766 : 
                            if (gpJeu->getTexte()->getId()!=49 
                            && gpJeu->getTexte()->getId()!=52 && gpJeu->getTexte()->getId()!=56 
                            && gpJeu->getTexte()->getId()!=58 && gpJeu->getTexte()->getId()!=60
                            && gpJeu->getTexte()->getId()!=63 && gpJeu->getTexte()->getId()!=66 
                            && gpJeu->getTexte()->getId()!=200 
                            && gpJeu->getTexte()->getId()!=217
                            && gpJeu->getTexte()->getId()!=412
                            && gpJeu->getTexte()->getId()!=423
                            && gpJeu->getTexte()->getId()!=516
                            && gpJeu->getTexte()->getId()!=566
                            && gpJeu->getTexte()->getId()!=610
                            && gpJeu->getTexte()->getId()!=677
                            && gpJeu->getTexte()->getId()!=711
                            && gpJeu->getTexte()->getId()!=766) {
                                if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN))) {
                                    gpJeu->getAudio()->playSound(3);
                                    gpJeu->getTexte()->changeId(gpJeu->getTexte()->getId()+1);
                                }
                            }
                            if (gpJeu->getTexte()->getId()!=48 
                            && gpJeu->getTexte()->getId()!=50 && gpJeu->getTexte()->getId()!=53 
                            && gpJeu->getTexte()->getId()!=57 && gpJeu->getTexte()->getId()!=59
                            && gpJeu->getTexte()->getId()!=61 && gpJeu->getTexte()->getId()!=64 
                            && gpJeu->getTexte()->getId()!=199
                            && gpJeu->getTexte()->getId()!=215
                            && gpJeu->getTexte()->getId()!=410
                            && gpJeu->getTexte()->getId()!=421
                            && gpJeu->getTexte()->getId()!=513
                            && gpJeu->getTexte()->getId()!=564
                            && gpJeu->getTexte()->getId()!=608
                            && gpJeu->getTexte()->getId()!=675
                            && gpJeu->getTexte()->getId()!=709
                            && gpJeu->getTexte()->getId()!=764) {
                                if ((keys[SDLK_UP] || buttonPressed(BTN_UP))) {
                                    gpJeu->getAudio()->playSound(3);
                                    gpJeu->getTexte()->changeId(gpJeu->getTexte()->getId()-1);
                                }
                            }
                            break;
                    }
                }
                if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) 
                && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN))) tmpt=0;
            }
            
            nbdir=0;
            if (keys[SDLK_UP] || stickPosition(LSTICK, STICK_UP)) nbdir++;
            if (keys[SDLK_DOWN] || stickPosition(LSTICK, STICK_DOWN)) nbdir++;
            if (keys[SDLK_LEFT] || stickPosition(LSTICK, STICK_LEFT)) nbdir++;
            if (keys[SDLK_RIGHT] || stickPosition(LSTICK, STICK_RIGHT)) nbdir++;
            
            int vitesse;
            if ((keys[SDLK_CAPSLOCK] || keys[SDLK_LSHIFT] || buttonPressed(BTN_RTRIGGER)) && !gpJeu->getStop() 
            && gpJoueur->hasObjet(O_BOTTES) && gpJoueur->hasObjet(O_TROC1)!=2) vitesse=4; 
            else vitesse=2;
    
            avance=0;
            
            //marche
#ifdef __vita__
           if (!stickPosition(RSTICK, STICK_LEFT) && !stickPosition(RSTICK, STICK_RIGHT) && !stickPosition(RSTICK, STICK_UP) && !stickPosition(RSTICK, STICK_DOWN) && (
#else
            if (!keys[SDLK_LCTRL] && (
#endif
            gpJoueur->getTypeAnim()==AUCUNE || gpJoueur->getTypeAnim()==MARCHE 
            || gpJoueur->getTypeAnim()==PORTE || gpJoueur->getTypeAnim()==EMMENE
            || gpJoueur->getTypeAnim()==NAGE || gpJoueur->getTypeAnim()==FLOTTE
            || gpJoueur->getTypeAnim()==RAME || gpJoueur->getTypeAnim()==BARQUE) 
            && !gpJeu->getStop() && !gpJeu->getTransition() && !gpJoueur->getImmo()) {
                gpJoueur->savePrec();
                if (((keys[SDLK_LEFT] || stickPosition(LSTICK, STICK_LEFT)) && !gpJoueur->isIvre()) 
                || ((keys[SDLK_RIGHT] || stickPosition(LSTICK, STICK_RIGHT)) && gpJoueur->isIvre())) {
                    if(!gpJoueur->getCharge() 
                    && (!(keys[SDLK_UP] || stickPosition(LSTICK, STICK_UP)) || gpJoueur->getDirection()!=N) 
                    && (!(keys[SDLK_DOWN] || stickPosition(LSTICK, STICK_DOWN)) || gpJoueur->getDirection()!=S))
                        gpJoueur->setDirection(O);
                    if (gpJoueur->getX()%4==2) vit=2; else vit = vitesse;
                    //gpJeu->moveJoueurX(-vit, nbdir);
                    gpJoueur->moveX(-vit, nbdir);
                    avance = 1;
                }
                if (((keys[SDLK_RIGHT] || stickPosition(LSTICK, STICK_RIGHT)) && !gpJoueur->isIvre()) 
                || ((keys[SDLK_LEFT] || stickPosition(LSTICK, STICK_LEFT)) && gpJoueur->isIvre())) {
                    if(!gpJoueur->getCharge() 
                    && (!(keys[SDLK_UP] || stickPosition(LSTICK, STICK_UP)) || gpJoueur->getDirection()!=N) 
                    && (!(keys[SDLK_DOWN] || stickPosition(LSTICK, STICK_DOWN)) || gpJoueur->getDirection()!=S))
                        gpJoueur->setDirection(E);
                    if (gpJoueur->getX()%4==2) vit=2; else vit = vitesse;
                    //gpJeu->moveJoueurX(vit, nbdir);
                    gpJoueur->moveX(vit, nbdir);
                    avance=1;
                }
                if (((keys[SDLK_UP] || stickPosition(LSTICK, STICK_UP)) && !gpJoueur->isIvre())
                || ((keys[SDLK_DOWN] || stickPosition(LSTICK, STICK_DOWN)) && gpJoueur->isIvre())) {
                    if(!gpJoueur->getCharge()
                    && (!(keys[SDLK_LEFT] || stickPosition(LSTICK, STICK_LEFT)) || gpJoueur->getDirection()!=O) 
                    && (!(keys[SDLK_RIGHT] || stickPosition(LSTICK, STICK_RIGHT)) || gpJoueur->getDirection()!=E))
                        gpJoueur->setDirection(N);
                    if (gpJoueur->getY()%4!=0) vit=2; else vit = vitesse;
                    //gpJeu->moveJoueurY(-vit, nbdir);
                    gpJoueur->moveY(-vit, nbdir);
                    avance=1;
                }
                if (((keys[SDLK_DOWN] || stickPosition(LSTICK, STICK_DOWN)) && !gpJoueur->isIvre())
                || ((keys[SDLK_UP] || stickPosition(LSTICK, STICK_UP)) && gpJoueur->isIvre())) {
                    if(!gpJoueur->getCharge()
                    && (!(keys[SDLK_LEFT] || stickPosition(LSTICK, STICK_LEFT)) || gpJoueur->getDirection()!=O) 
                    && (!(keys[SDLK_RIGHT] || stickPosition(LSTICK, STICK_RIGHT)) || gpJoueur->getDirection()!=E))
                        gpJoueur->setDirection(S);
                    if (gpJoueur->getY()%4!=0) vit=2; else vit = vitesse;
                    //gpJeu->moveJoueurY(vit, nbdir);
                    gpJoueur->moveY(vit, nbdir);
                    avance=1;
                }
                if (gpJeu->getVueHorz()>0) {
                    if (gpJeu->getVueHorz()>=4) gpJeu->setVueHorz(gpJeu->getVueHorz()-4);
                    else gpJeu->setVueHorz(0);
                }
                if (gpJeu->getVueHorz()<0) {
                    if (gpJeu->getVueHorz()<=-4) gpJeu->setVueHorz(gpJeu->getVueHorz()+4);
                    else gpJeu->setVueHorz(0);
                }
                if (gpJeu->getVueVert()>0) {
                    if (gpJeu->getVueVert()>=4) gpJeu->setVueVert(gpJeu->getVueVert()-4);
                    else gpJeu->setVueVert(0);
                }
                if (gpJeu->getVueVert()<0) {
                    if (gpJeu->getVueVert()<=-4) gpJeu->setVueVert(gpJeu->getVueVert()+4);
                    else gpJeu->setVueVert(0);
                }
            }
#ifdef __vita__
            if (!gpJoueur->getImmo()) {
                if (stickPosition(RSTICK, STICK_LEFT) && gpJeu->getVueHorz()>-64)
                    gpJeu->setVueHorz(gpJeu->getVueHorz()-2);
                if (stickPosition(RSTICK, STICK_RIGHT) && gpJeu->getVueHorz()<64)
                    gpJeu->setVueHorz(gpJeu->getVueHorz()+2);
                if (stickPosition(RSTICK, STICK_UP) && gpJeu->getVueVert()>-64)
                   gpJeu->setVueVert(gpJeu->getVueVert()-2);
                if (stickPosition(RSTICK, STICK_DOWN) && gpJeu->getVueVert()<64)
                   gpJeu->setVueVert(gpJeu->getVueVert()+2);
            }
#else
            if (keys[SDLK_LCTRL] && !gpJoueur->getImmo()) {
                if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && gpJeu->getVueHorz()>-64)
                    gpJeu->setVueHorz(gpJeu->getVueHorz()-2);
                if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && gpJeu->getVueHorz()<64)
                    gpJeu->setVueHorz(gpJeu->getVueHorz()+2);
                if ((keys[SDLK_UP] || buttonPressed(BTN_UP)) && gpJeu->getVueVert()>-64)
                    gpJeu->setVueVert(gpJeu->getVueVert()-2);
                if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && gpJeu->getVueVert()<64)
                    gpJeu->setVueVert(gpJeu->getVueVert()+2);
            }
#endif
            
            if (avance == 1) {
                if (gpJoueur->getTypeAnim()==AUCUNE) gpJoueur->setTypeAnim(MARCHE);
                if (gpJoueur->getTypeAnim()==FLOTTE) gpJoueur->setTypeAnim(NAGE);
                if (gpJoueur->getTypeAnim()==PORTE) gpJoueur->setTypeAnim(EMMENE);
                if (gpJoueur->getTypeAnim()==BARQUE) gpJoueur->setTypeAnim(RAME);
                gpJeu->testFin();
            }
            else {
                if (gpJoueur->getTypeAnim()==MARCHE && !gpJeu->getStop()) 
                    gpJoueur->setTypeAnim(AUCUNE);
                if (gpJoueur->getTypeAnim()==NAGE && !gpJeu->getStop()) 
                    gpJoueur->setTypeAnim(FLOTTE);
                if (gpJoueur->getTypeAnim()==EMMENE && !gpJeu->getStop()) 
                    gpJoueur->setTypeAnim(PORTE);
                if (gpJoueur->getTypeAnim()==RAME && !gpJeu->getStop()) 
                    gpJoueur->setTypeAnim(BARQUE);
            }
            
            
            //épée
            if ((gpJoueur->getTypeAnim()==AUCUNE || gpJoueur->getTypeAnim()==MARCHE) 
            && !gpJoueur->getCharge() && gpJoueur->getEpee() && !gpJeu->getStop()
            && !gpJoueur->isLapin() && !gpJoueur->getImmo()) {
                if (((keys[SDLK_z] || buttonPressed(BTN_SQUARE)) || keys[SDLK_w]) && !tmpw) {
                    gpJoueur->setTypeAnim(EPEE);
                    gpJoueur->chargeSpin();
                    tmpw=1;
                }
                if (!(keys[SDLK_z] || buttonPressed(BTN_SQUARE)) && !keys[SDLK_w] && tmpw) tmpw=0;
            }
            if (!(keys[SDLK_z] || buttonPressed(BTN_SQUARE)) && !keys[SDLK_w] && gpJoueur->getCharge() && !gpJeu->getStop() 
            && !gpJoueur->isLapin()) {
                if (gpJoueur->getCharge() >= 20) gpJoueur->setTypeAnim(SPIN);
                gpJoueur->dechargeSpin();
            }
            
            
            //curseur menu
            if (gpJeu->getMenu() && !gpJoueur->getOni() &&
            (gpJoueur->getTypeAnim()<4 || gpJoueur->getTypeAnim()==NAGE || gpJoueur->getTypeAnim()==FLOTTE ||
            (gpJoueur->getTypeAnim()>20 && gpJoueur->getTypeAnim()<25)) && tmp==0) {
                if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT))) {
                    int obj = gpJoueur->getObjet();
                    if (obj%4 == 0) gpJoueur->setObjet(obj+3);
                    else gpJoueur->setObjet(obj-1);
                    gpJeu->getAudio()->playSound(3);
                    tmp=1;
                }
                if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT))) {
                    int obj = gpJoueur->getObjet();
                    if (obj%4 == 3) gpJoueur->setObjet(obj-3);
                    else gpJoueur->setObjet(obj+1);
                    gpJeu->getAudio()->playSound(3);
                    tmp=1;
                }
                if ((keys[SDLK_UP] || buttonPressed(BTN_UP))) {
                    int obj = gpJoueur->getObjet();
                    if (obj/4 == 0) gpJoueur->setObjet(obj+12);
                    else gpJoueur->setObjet(obj-4);
                    gpJeu->getAudio()->playSound(3);
                    tmp=1;
                }
                if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN))) {
                    int obj = gpJoueur->getObjet();
                    if (obj/4 == 3) gpJoueur->setObjet(obj-12);
                    else gpJoueur->setObjet(obj+4);
                    gpJeu->getAudio()->playSound(3);
                    tmp=1;
                }
            }
            
            
            
            if ((keys[SDLK_x] || buttonPressed(BTN_TRIANGLE)) && (
            gpJoueur->getTypeAnim()==AUCUNE || gpJoueur->getTypeAnim()==MARCHE || 
            gpJoueur->getTypeAnim()==PECHE) 
            && !gpJeu->getStop() && !gpJoueur->getImmo()
            && gpJoueur->getVie()>0 && !gpJoueur->getCharge() && !gpJoueur->isLapin() 
            && !gpJoueur->getOni() && !tmpx) {
                tmpx=1;
                switch(gpJoueur->getObjet()) {
                    case 0 : //arc
                        if (gpJoueur->hasObjet(O_ARC)) gpJoueur->setTypeAnim(ARC);
                        break;
                    case 1 : //grappin
                        if (gpJoueur->hasObjet(O_GRAPPIN)) gpJoueur->setTypeAnim(GRAPPIN);
                        break;
                    case 2 : //bombe
                        if (gpJoueur->hasObjet(O_SAC_BOMBES) && gpJoueur->getBombe()) 
                            gpJoueur->setTypeAnim(BOMBE);
                        break;
                    case 3 : //flèche feu ou troc 1
                        if (gpJoueur->hasObjet(O_FFEU)) {
                            if (gpJoueur->hasObjet(O_ARC)) gpJoueur->setTypeAnim(ARC);
                        }
                        else if (gpJoueur->hasObjet(O_TROC1))
                            gpJeu->ecrit(1);
                        break;
                    case 4 : //baguette de feu
                        if (gpJoueur->hasObjet(O_BFEU)) gpJoueur->setTypeAnim(BFEU);
                        break;
                    case 5 : //baguette de glace
                        if (gpJoueur->hasObjet(O_BGLACE)) gpJoueur->setTypeAnim(BGLACE);
                        break;
                    case 6 : //lanterne
                        if (gpJoueur->hasObjet(O_LANTERNE) && gpJoueur->getMagie() >= 2) 
                            gpJoueur->setTypeAnim(LANTERNE);
                        break;
                    case 7 : //troc 2
                        if (gpJoueur->hasObjet(O_FGLACE)) {
                            if (gpJoueur->hasObjet(O_ARC)) gpJoueur->setTypeAnim(ARC);
                        }
                        else if (gpJoueur->hasObjet(O_TROC2))
                            gpJeu->ecrit(1);
                        break;
                    case 8 : //marteau
                        if (gpJoueur->hasObjet(O_MARTEAU)) gpJoueur->setTypeAnim(MARTEAU);
                        break;
                    case 9 : //ocarina
                        if (gpJoueur->hasObjet(O_OCARINA)) {
                            gpJoueur->setTypeAnim(JOUE);
                            gpJeu->ecrit(47);}
                        break;
                    case 10 : //canne à pêche
                        if (gpJoueur->getTypeAnim()==PECHE) gpJoueur->finPeche();
                        else gpJoueur->peche();
                        break;
                    case 11 : //troc 3
                        if (gpJoueur->hasObjet(O_FLUM)) {
                            if (gpJoueur->hasObjet(O_ARC)) gpJoueur->setTypeAnim(ARC);
                        }
                        else if (gpJoueur->hasObjet(O_TROC3))
                            gpJeu->ecrit(1);
                        break;
                    case 12 : // flacon
                    case 13 :
                    case 14 :
                    case 15 :
                        if (gpJoueur->hasBouteille(gpJoueur->getObjet()-12)) 
                            gpJoueur->setTypeAnim(BOIRE);
                        else if (gpJoueur->getObjet()==15 && gpJoueur->hasObjet(O_TROC4))
                            gpJeu->ecrit(1);
                        break;
                }
            }
            
            if (!(keys[SDLK_x] || buttonPressed(BTN_TRIANGLE)) && tmpx) tmpx=0;
            
            if ((keys[SDLK_c] || leverJeter) && !tmpc && !gpJoueur->getCharge() && gpJoueur->getVie()>0
            && !gpJoueur->isLapin() && !gpJeu->getStop() && !gpJoueur->getImmo()) {
                if (gpJoueur->getTypeAnim()==AUCUNE || gpJoueur->getTypeAnim()==MARCHE)
                    gpJeu->ramasse();
                else if (gpJoueur->getTypeAnim()==PORTE || gpJoueur->getTypeAnim()==EMMENE)
                    gpJoueur->setTypeAnim(LANCE);
            }
            
            if (!(keys[SDLK_c] || buttonPressed(BTN_CROSS)) && tmpc) tmpc=0;
            
            if ((keys[SDLK_SPACE] || buttonPressed(BTN_CIRCLE)) && !gpJeu->getStop() && gpJoueur->getVie() && 
            (gpJoueur->getTypeAnim()==AUCUNE || gpJoueur->getTypeAnim()==MARCHE
            || gpJoueur->getTypeAnim()==PORTE || gpJoueur->getTypeAnim()==EMMENE
            || gpJoueur->getTypeAnim()==FLOTTE || gpJoueur->getTypeAnim()==NAGE
            || gpJoueur->getTypeAnim()==BARQUE || gpJoueur->getTypeAnim()==RAME) 
             && !gpJoueur->getImmo()) {
                gpJeu->lire();
            }
            
            if ((keys[SDLK_p] || (buttonPressed(BTN_LTRIGGER) && !buttonPressed(BTN_RTRIGGER))) && (gpJoueur->hasObjet(O_CARTE) || gpJeu->isDonjon()) && 
            (gpJeu->isDehors() || gpJeu->isDonjon())
            && !gpJeu->getStop() && gpJoueur->getVie()>0 && !tmpp) {
                mode = 12;
                gpJeu->getAudio()->playSound(1);
                gpCarte->init();
                tmpp=1;
            }
            
            if (!(keys[SDLK_p] || buttonPressed(BTN_LTRIGGER)) && tmpp) tmpp=0;
            
            if ((keys[SDLK_m] || keys[SDLK_SEMICOLON] || buttonPressed(BTN_UP)) && gpJoueur->hasObjet(O_ENCYCL)
            && !gpJeu->getStop() && gpJoueur->getVie()>0 && gpJoueur->nbEnnemis() && !tmpm) {
                mode = 13;
                gpJeu->getAudio()->playSound(1);
                gpEncyclopedie->setPage(0);
                gpEncyclopedie->init();
                tmpm=1;
            }
            
            if (!(keys[SDLK_m] || keys[SDLK_SEMICOLON] || buttonPressed(BTN_UP)) && tmpm) tmpm=0;
            
            if ((keys[SDLK_o] || (buttonPressed(BTN_LTRIGGER) && buttonPressed(BTN_RTRIGGER))) && gpJoueur->hasObjet(O_MASQUE) && !gpJoueur->isLapin() && !tmpo
            && !gpJeu->getStop() && !gpJoueur->getImmo() && gpJoueur->getVie()>0) {
                if (gpJoueur->getOni()) {
                    gpJeu->getAudio()->playSound(2);gpJoueur->setOni(false);}
                else {gpJeu->getAudio()->playSound(1); gpJoueur->setOni(true);}
                tmpo=1;
            }
            
            if (!(keys[SDLK_o] || (buttonPressed(BTN_LTRIGGER) && buttonPressed(BTN_RTRIGGER))) && tmpo) tmpo=0;
            
            
            if (keys[SDLK_t] && gpJoueur->getOni() && !gpJoueur->isLapin()
            && gpJeu->isDonjon() && !tmptp
            && !gpJeu->getStop() && !gpJoueur->getImmo() && gpJoueur->getVie()>0) {
                gpJeu->getAudio()->playSound(5);
                SDL_Delay(1000);
                gpJeu->getAudio()->stopSpecial();
                gpJoueur->restoreEmpl();
                tmptp=1;
            }
            
            if (!(keys[SDLK_t]) && tmptp) tmptp=0;
            
            
            // liste poissons
            if ((keys[SDLK_l] || buttonPressed(BTN_DOWN)) && gpJoueur->hasObjet(O_POISSONS) && gpJoueur->nbPoissons() && !tmpl
            && !gpJeu->getStop() && !gpJoueur->getImmo() && gpJoueur->getVie()>0) {
                mode = 23;
                gpJeu->getAudio()->playSound(1);
                gpPoissons->setPage(0);
                gpPoissons->init();
                tmpl=1;
            }
            
            if (!(keys[SDLK_l] || buttonPressed(BTN_DOWN)) && tmpl) tmpl=0;
            
            // liste items troc
            if ((keys[SDLK_i] || buttonPressed(BTN_LEFT)) && gpJoueur->hasObjet(O_SAC_TROC) && !tmpi
            && !gpJeu->getStop() && !gpJoueur->getImmo() && gpJoueur->getVie()>0) {
                mode = 25;
                gpJeu->getAudio()->playSound(1);
                gpJeu->getGenerique()->initTroc();
                tmpi=1;
            }
            
            if (!(keys[SDLK_i] || buttonPressed(BTN_LEFT)) && tmpi) tmpi=0;
            
            break;
        case 1 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                mode = 2;
                gpJeu->getGenerique()->initLogo();
                gpJeu->getAudio()->playSound(1);
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS))) tmp=0;
            break;
        case 2 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                mode = 3;
                gpJeu->getGenerique()->initTitre();
                gpJeu->getAudio()->playSound(1);
                gpJeu->getAudio()->playMusic(180);
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS))) tmp=0;
            break;
        case 3 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                mode = 4; colonne=0;
                gpJeu->getGenerique()->initSelection();
                gpJeu->getAudio()->playSound(1);
                gpJeu->getAudio()->playMusic(190);
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS))) tmp=0;
            break;
        case 4 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                if (ligne < 3) {
                    if (save[ligne]) {
                        mode = 7; ligneVal=0;
                        gpJeu->getGenerique()->initCharger();
                    }
                    else {
                        mode = 8; intro = 0; gpJeu->getGenerique()->initIntro();
                        gpJeu->getAudio()->playMusic(200);
                    }
                }
                if (ligne == 3 && colonne == 0) {
                    mode = 6; ligneOption=3;
                    gpJeu->getGenerique()->initOption();
                }
                if (ligne == 3 && colonne == 1) {
                    mode = 15; ligneRecord=3; colonneRecord=0;
                    gpJeu->getGenerique()->initRecord();
                }
                tmp=1; gpJeu->getAudio()->playSound(1);
            }
            
            if ((keys[SDLK_UP] || buttonPressed(BTN_UP)) && !tmp) {
                ligne--; if (ligne<0) ligne=3; tmp=1; 
                if (ligne!=3) colonne=0;
                gpJeu->getAudio()->playSound(3);}
            if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && !tmp) {
                ligne++; if (ligne>3) ligne=0; tmp=1;
                if (ligne!=3) colonne=0;
                gpJeu->getAudio()->playSound(3);}
            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !tmp && ligne==3) {
                colonne--; if (colonne<0) colonne=1; tmp=1;
                gpJeu->getAudio()->playSound(3);}
            if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && !tmp && ligne==3) {
                colonne++; if (colonne>1) colonne=0; tmp=1;
                gpJeu->getAudio()->playSound(3);}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) 
                && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && tmp) tmp=0;
            break;
        case 6 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0 && ligneOption == 3) {
                mode = 4;
                gpJeu->getGenerique()->initSelection();
                gpJeu->getAudio()->playSound(2);
                tmp = 1;
                saveP();
            }
            
            if ((keys[SDLK_UP] || buttonPressed(BTN_UP)) && !tmp) {
                ligneOption--; if (ligneOption<0) ligneOption=3; tmp=1; 
                gpJeu->getAudio()->playSound(3);}
            if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && !tmp) {
                ligneOption++; if (ligneOption>3) ligneOption=0; tmp=1;
                gpJeu->getAudio()->playSound(3);}
            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !tmp) {
                if (ligneOption == 0) {
                    volume-=8; if (volume < 0) volume = 0; tmp=1;
                    gpJeu->getAudio()->setVolume(volume); gpJeu->getAudio()->playSound(3);}
                if (ligneOption == 1) {
                    volson-=8; if (volson < 0) volson = 0; tmp=1;
                    gpJeu->getAudio()->setVolson(volson); gpJeu->getAudio()->playSound(3);}
                if (ligneOption == 2) {
                    if (getLanguage()==MIN_LANG) setLanguage(gpJeu, MAX_LANG); 
					else setLanguage(gpJeu, getLanguage()-1);
					tmp=1;
                    gpJeu->getAudio()->playSound(3);}}
            if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && !tmp) {
                if (ligneOption == 0) {
                    volume+=8; if (volume > 64) volume = 64; tmp=1;
                    gpJeu->getAudio()->setVolume(volume);gpJeu->getAudio()->playSound(3);}
                if (ligneOption == 1) {
                    volson+=8; if (volson > 64) volson = 64; tmp=1;
                    gpJeu->getAudio()->setVolson(volson);gpJeu->getAudio()->playSound(3);}
                if (ligneOption == 2) {
					if (getLanguage()==MAX_LANG) setLanguage(gpJeu, MIN_LANG); 
					else setLanguage(gpJeu, getLanguage()+1);
					tmp=1;
                    gpJeu->getAudio()->playSound(3);}}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) 
                && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && tmp) tmp=0;
            break;
        case 7 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                if (ligneVal==0) {
                    mode = 0;
                    gpJeu->init(ligne+1);
                }
                if (ligneVal==1) {
                    mode = 9; ligneVal=1;
                    gpJeu->getGenerique()->initEffacer();
                    gpJeu->getAudio()->playSound(1);
                }
                if (ligneVal==2) {
                    mode = 4; gpJeu->getGenerique()->initSelection();
                    gpJeu->getAudio()->playSound(2);
                }    
                tmp = 1;
            }
            
            if ((keys[SDLK_UP] || buttonPressed(BTN_UP)) && !tmp) {
                if (--ligneVal<0) ligneVal=2; tmp=1; 
                gpJeu->getAudio()->playSound(3);}
            if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && !tmp) {
                if (++ligneVal>2) ligneVal=0; tmp=1;
                gpJeu->getAudio()->playSound(3);}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && tmp) tmp=0;
            break;
        case 8 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                int old;
                old = gpJeu->getTexte()->getId();
                if (!gpJeu->getTexte()->suite()) {
                    mode = 10; gpJeu->getGenerique()->initNuit();
                    gpJeu->getAudio()->stopMusic();
                }
                else if (old != gpJeu->getTexte()->getId()) intro++;
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp) tmp=0;
            break;
        case 9 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                if (ligneVal==0) {
                    ostringstream oss; oss << (ligne+1);
#ifdef __vita__
                    remove(("ux0:data/z3t/save/3t" + oss.str() + ".dat").c_str());
#else
                    remove(("data/save/3t" + oss.str() + ".dat").c_str());
#endif
                    mode = 4; gpJeu->getGenerique()->initSelection();
                    gpJeu->getAudio()->playSound(2);
                }
                else {
                    mode = 7; gpJeu->getGenerique()->initCharger();
                    gpJeu->getAudio()->playSound(1);
                }
                tmp = 1;
            }
            
            if (((keys[SDLK_UP] || buttonPressed(BTN_UP)) || (keys[SDLK_DOWN] || buttonPressed(BTN_DOWN))) && !tmp) {
                ligneVal ? ligneVal=0 : ligneVal = 1; tmp=1;
                gpJeu->getAudio()->playSound(3);}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && tmp) tmp=0;
            break;
        case 10 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                if (gpJeu->getText()) gpJeu->setText(gpJeu->getTexte()->suite());
                if (!gpJeu->getText()) {
                    //gpJeu->getAudio()->playSound(5);
                    //SDL_Delay(2500);
                    mode = 0; gpJeu->init(ligne+1);
                    gpJeu->ecrit(1367);
                }
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp) tmp=0;
            break;
        case 11 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                gpJeu->setText(gpJeu->getTexte()->suite());
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS))) tmp=0;
            break;
        case 12 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 0;
                gpJeu->getAudio()->playSound(2);
                tmp=1;
            }
            
            if ((keys[SDLK_UP] || buttonPressed(BTN_UP)) && !tmp) {
                gpCarte->moveLevel(N);
                tmp=1;
            }
            if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && !tmp) {
                gpCarte->moveLevel(S);
                tmp=1;
            }
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && tmp) tmp=0;
            break;
        case 13 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 0;
                gpJeu->getAudio()->playSound(2);
                tmp=1;
            }
            
            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !tmp) {
                gpJeu->getAudio()->playSound(3);
                gpEncyclopedie->moveL();
                tmp=1;
            }
            if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && !tmp) {
                gpJeu->getAudio()->playSound(3);
                gpEncyclopedie->moveR();
                tmp=1;
            }
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && tmp) tmp=0;
            break;
        case 14 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                mode = 2; gpJeu->getAudio()->playSound(1);
                gpJeu->getGenerique()->initLogo();
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp) tmp=0;
            break;
        case 15 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                if (ligneRecord==3) {
                    if (colonneRecord == 0) {
                        mode = 4;
                        gpJeu->getGenerique()->initSelection();
                        gpJeu->getAudio()->playSound(2);
                    }
                    else {
                        mode = 16; ligneVal=1;
                        gpJeu->getGenerique()->initEffacer();
                        gpJeu->getAudio()->playSound(1);
                    }
                }
                else {
                    mode = 19 + ligneRecord;
                    gpJeu->getGenerique()->initRang(ligneRecord);
                    gpJeu->getAudio()->playSound(1);
                }
                tmp = 1;
            }
            
            if ((keys[SDLK_UP] || buttonPressed(BTN_UP)) && !tmp) {
                ligneRecord--; if (ligneRecord<0) ligneRecord=3; tmp=1; 
                colonneRecord=0; gpJeu->getAudio()->playSound(3);}
            if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && !tmp) {
                ligneRecord++; if (ligneRecord>3) ligneRecord=0; tmp=1;
                colonneRecord=0; gpJeu->getAudio()->playSound(3);}
            
            if (((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) || (keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT))) && ligneRecord==3 && !tmp) {
                if (colonneRecord == 0) colonneRecord=1;
                else colonneRecord=0; tmp=1;
                gpJeu->getAudio()->playSound(3);}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) 
                && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && tmp) tmp=0;
            break;
        case 16 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                mode = 15;
                if (ligneVal==0) {
                    gpJeu->getAudio()->playSound(2);
                    temps=0; for (int i = 0; i < 3; i++) rang[6+i]=0; saveP();
                }
                else gpJeu->getAudio()->playSound(1);
                gpJeu->getGenerique()->initRecord();
                tmp = 1;
            }
            
            if (((keys[SDLK_UP] || buttonPressed(BTN_UP)) || (keys[SDLK_DOWN] || buttonPressed(BTN_DOWN))) && !tmp) {
                ligneVal ? ligneVal=0 : ligneVal = 1; tmp=1;
                gpJeu->getAudio()->playSound(3);}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && tmp) tmp=0;
            break;
        case 17 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 0;
                gpJeu->getAudio()->playSound(2);
                tmp=1;
            }
            if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && !tmp) {
                mode = 18; gpJeu->getGenerique()->initAide2();
                gpJeu->getAudio()->playSound(3); tmp=1;}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && tmp) tmp=0;
            break;
        case 18 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 0;
                gpJeu->getAudio()->playSound(2);
                tmp=1;
            }
            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !tmp) {
                mode = 17; gpJeu->getGenerique()->initAide1();
                gpJeu->getAudio()->playSound(3); tmp=1;}
            if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && !tmp) {
                if (gpJeu->getGenerique()->initAide3()) {
                    mode = 24;
                    gpJeu->getAudio()->playSound(3); tmp=1;}}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && tmp) tmp=0;
            break;
        case 24 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 0;
                gpJeu->getAudio()->playSound(2);
                tmp=1;
            }
            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !tmp) {
                mode = 18; gpJeu->getGenerique()->initAide2();
                gpJeu->getAudio()->playSound(3); tmp=1;}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && tmp) tmp=0;
            break;
        case 19 :
        case 20 :
        case 21 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 15; gpJeu->getGenerique()->initRecord();
                gpJeu->getAudio()->playSound(2);
                tmp=1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp) tmp=0;
            break;
        case 22 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 0;
                gpJeu->getAudio()->playSound(5);
                SDL_Delay(2500);
                gpJeu->teleporte(telep);
                tmp=1;
            }
            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !tmp) {
                telep--; if (telep<0) telep=8;
                gpJeu->getAudio()->playSound(3); tmp=1;}
            if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && !tmp) {
                telep++; if (telep>8) telep=0;
                gpJeu->getAudio()->playSound(3); tmp=1;}
            if ((keys[SDLK_1] || keys[SDLK_KP1]
            || keys[SDLK_2] || keys[SDLK_KP2]
            || keys[SDLK_3] || keys[SDLK_KP3]
            || keys[SDLK_4] || keys[SDLK_KP4]
            || keys[SDLK_5] || keys[SDLK_KP5]
            || keys[SDLK_6] || keys[SDLK_KP6]
            || keys[SDLK_7] || keys[SDLK_KP7]
            || keys[SDLK_8] || keys[SDLK_KP8]
            || keys[SDLK_9] || keys[SDLK_KP9]
            ) && !tmp) {
                if (keys[SDLK_1] || keys[SDLK_KP1])telep=0;
                if (keys[SDLK_2] || keys[SDLK_KP2])telep=1;
                if (keys[SDLK_3] || keys[SDLK_KP3])telep=2;
                if (keys[SDLK_4] || keys[SDLK_KP4])telep=3;
                if (keys[SDLK_5] || keys[SDLK_KP5])telep=4;
                if (keys[SDLK_6] || keys[SDLK_KP6])telep=5;
                if (keys[SDLK_7] || keys[SDLK_KP7])telep=6;
                if (keys[SDLK_8] || keys[SDLK_KP8])telep=7;
                if (keys[SDLK_9] || keys[SDLK_KP9])telep=8;
                gpJeu->getAudio()->playSound(3); tmp=1;
            }
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) 
            && !keys[SDLK_1] && !keys[SDLK_2] && !keys[SDLK_3]
            && !keys[SDLK_4] && !keys[SDLK_5] && !keys[SDLK_6]
            && !keys[SDLK_7] && !keys[SDLK_8] && !keys[SDLK_9]
            && !keys[SDLK_KP1] && !keys[SDLK_KP2] && !keys[SDLK_KP3]
            && !keys[SDLK_KP4] && !keys[SDLK_KP5] && !keys[SDLK_KP6]
            && !keys[SDLK_KP7] && !keys[SDLK_KP8] && !keys[SDLK_KP9]
            && tmp) tmp=0;
            break;
        case 23 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 0;
                gpJeu->getAudio()->playSound(2);
                tmp=1;
            }
            
            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !tmp) {
                gpJeu->getAudio()->playSound(3);
                gpPoissons->moveL();
                tmp=1;
            }
            if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && !tmp) {
                gpJeu->getAudio()->playSound(3);
                gpPoissons->moveR();
                tmp=1;
            }
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && tmp) tmp=0;
            break;
        case 25 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 0;
                gpJeu->getAudio()->playSound(2);
                tmp=1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp) tmp=0;
            break;
        case 26 :
        case 27 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                gpJeu->setText(gpJeu->getTexte()->suite());
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS))) tmp=0;
            break;
        case 28 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 14;
                gpJeu->getAudio()->stopSpecial();
                gpJeu->getAudio()->stopMusic(); 
                gpJeu->getGenerique()->initScore();
                gpJeu->setZone(79);
                gpJeu->getJoueur()->setVie(gpJeu->getJoueur()->getVieMax());
                gpJeu->getJoueur()->setXDep(152);
                gpJeu->getJoueur()->setYDep(72);
                gpJeu->getJoueur()->setDirDep(S);
                gpJeu->getJoueur()->save();
                gpJeu->getAudio()->playSound(2);
                tmp=1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp) tmp=0;
            break;
    }
}

Carte* Keyboard::getCarte() {return gpCarte;}
int Keyboard::getTelep() {return telep;}
void Keyboard::setTelep(int i) {telep=i;}

int Keyboard::buttonPressed(int i) {
#ifdef __vita__
    return SDL_JoystickGetButton(joystick, i);
#else
    return 0;
#endif
}

int Keyboard::stickPosition(int stick, int direction) {
#ifdef __vita__
    int axis;
    int axisValue;
    if (stick == LSTICK && (direction == STICK_LEFT || direction == STICK_RIGHT)) axis = 0; // Left stick, horizontal axis
    if (stick == LSTICK && (direction == STICK_UP || direction == STICK_DOWN)) axis = 1; // Left stick, vertical axis
    if (stick == RSTICK && (direction == STICK_LEFT || direction == STICK_RIGHT)) axis = 2; // Right stick, horizontal axis
    if (stick == RSTICK && (direction == STICK_UP || direction == STICK_DOWN)) axis = 3; // Right stick, vertical axis

    axisValue = SDL_JoystickGetAxis(joystick, axis); // range is -32768 to 32767
    if ((axisValue < -31000 && direction == STICK_LEFT)
      || (axisValue > 31000 && direction == STICK_RIGHT)
      || (axisValue < -31000 && direction == STICK_UP)
      || (axisValue > 31000 && direction == STICK_DOWN)) return 1;
    else return 0;
#else
    return 0;
#endif
}
