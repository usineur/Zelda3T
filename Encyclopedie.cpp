/*
    Zelda Time to Triumph
    Copyright (C) 2007-2009  Vincent Jouillat
    Please send bugreports with examples or suggestions to www.zeldaroth.fr
*/

#include "Encyclopedie.h"

Encyclopedie::Encyclopedie(Jeu* jeu) : gpJeu(jeu), page(0), gpEnnemi(0), gpPnj(0) {
    image = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
    imageCadre = gpJeu->loadImg("data/images/logos/cadres.png");
    gpEnnemi = new Ennemi(gpJeu, 0, 0, 0, true);
    gpPnj = new Pnj(gpJeu, 8, gpJeu->getPhg(0)+128+8+((48-16)/2), 
        gpJeu->getPhg(1)+112-16+((48-23)/2), 0);
}

Encyclopedie::~Encyclopedie() {
    SDL_FreeSurface(image);
    SDL_FreeSurface(imageCadre);
    delete gpEnnemi;
    delete gpPnj;
}

void Encyclopedie::draw(SDL_Surface* gpScreen) {
    SDL_Rect dst; dst.x = 0; dst.y = 0;
    SDL_BlitSurface(image, NULL, gpScreen, &dst);
}

void Encyclopedie::init() {
    fond();
}

void Encyclopedie::fond() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
        
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 5; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 112; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 112; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 112; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    
    ostringstream os; os << (page+1);
    gpJeu->afficheTexteAvecId(image, 100, os.str(), 40, 17);
    
    placeCadres();
    
    gpJeu->setStop(true);
    gpEnnemi->draw(image);
    if (page == 11) {
        gpPnj->setX(gpJeu->getPhg(0)+128+8+((48-16)/2));
        gpPnj->setY(gpJeu->getPhg(1)+112-16+((48-23)/2));
        gpPnj->draw(image);
    }
    gpJeu->setStop(false);
    
    delete gpEnnemi;
    gpEnnemi = new Ennemi(gpJeu, 0, 0, 0, true);
}

void Encyclopedie::placeCadres() {
    switch (page) {
        case 0 :
            cadre(152,8,32,32,4);
            cadre(208,8,32,32,53);
            cadre(264,8,32,32,54);
            cadre(16,48,48,48,27);
            cadre(96,48,48,48,10);
            cadre(176,48,48,48,9);
            cadre(256,48,48,48,8);
            cadre(16,112,48,48,12);
            cadre(96,112,48,48,6);
            cadre(176,112,48,48,5);
            cadre(256,112,48,48,1);
            cadre(16,176,48,48,22);
            cadre(96,176,48,48,3);
            cadre(176,176,48,48,13);
            cadre(252,176,56,48,14);
            break; // -> 15
        case 1 :
            cadre(152,8,32,32,18);
            cadre(208,8,32,32,121);
            cadre(264,8,32,32,7);
            cadre(16,48,48,48,23);
            cadre(96,48,48,48,25);
            cadre(176,48,48,48,16);
            cadre(256,48,48,48,29);
            cadre(16,112,80,48,19);
            cadre(96+32-16,112,48,48,28);
            cadre(176,112,64,64,40);
            cadre(256,112,48,64,24);
            cadre(16,176,48,48,35);
            cadre(96,176,48,48,43);
            break; // -> 28
        case 2 :
            cadre(16,48,48,64,91);
            cadre(96-8,48,48,48,93);
            cadre(176,8,48,48,95);
            cadre(256,8,48,48,104);
            cadre(16,128,96,96,105);
            cadre(144+8,160,48,48,94);
            cadre(240,160-8,64,80,97);
            cadre(256-96,112-32-8,144,64,92);
            break; // -> 36
        case 3 :
            cadre(152,8,32,32,84);
            cadre(208,8,32,32,56);
            cadre(264,8,32,32,86);
            cadre(16,48,48,48,32);
            cadre(96,48,48,48,11);
            cadre(176,48,48,48,55);
            cadre(256,48,48,48,37);
            cadre(16,112,48,48,15);
            cadre(96,112,48,48,44);
            cadre(176,112,48,48,26);
            cadre(256,112,48,48,101);
            cadre(16,176,48,48,62);
            cadre(96,176,48,48,64);
            break; // -> 49
        case 4 :
            cadre(16,48,48,48,98);
            cadre(104,48,48,48,102);
            cadre(184,64,96,128,99);
            cadre(32,112,96,96,103);
            break; // -> 53
        case 5 :
            cadre(152,8,32,32,112);
            cadre(208,8,32,32,118);
            cadre(16,48,48,48,77);
            cadre(96,48,48,48,42);
            cadre(176,48,48,48,41);
            cadre(256,48,48,48,87);
            cadre(16,112,48,48,30);
            cadre(96,112,48,48,33);
            cadre(176,112,48,48,34);
            cadre(256,112,48,48,2);
            cadre(16,176,48,48,72);
            cadre(96,176,48,48,38);
            cadre(176,176,48,48,39);
            cadre(256,176,48,48,119);
            break; // -> 67
        case 6 :
            cadre(16,48,48,48,108);
            cadre(96-16,48,48,48,110);
            cadre(160-8,8,48+8,64,106);
            cadre(240-16,8,80,64,76);
            cadre(16,112,48,48,113);
            cadre(240-32,112-16-8,96,64,107);
            cadre(80,112,112,112,109);
            cadre(240-16,176-8,80,64,111);
            break; // -> 75
        case 7 :
            cadre(32,64,144,112,115);
            cadre(176+32,64,48,48,120);
            cadre(176+32,128,48,48,89);
            break; // -> 78
        case 8 :
            cadre(16,48,48,48,46);
            cadre(96,48,48,48,47);
            cadre(176,48,48,48,48);
            cadre(16,112,48,48,31);
            cadre(96,112,64,48,50);
            break; // -> 83
        case 9 :
            cadre(16,48,48,48,123);
            cadre(96,48,48,48,126);
            cadre(16,112,96,80,127);
            cadre(144,112,80,80,128);
            break; // -> 87
        case 10 :
            cadre(16,48,48,48,129);
            cadre(96,48,48,48,130);
            cadre(176,48,48,48,131);
            cadre(256,32,48,64,139);
            cadre(16,112,48,48,133);
            cadre(96,112,48,48,134);
            cadre(176,112,48,48,135);
            cadre(256,112,48,48,136);
            cadre(16,176,48,48,137);
            cadre(96,176,48,48,138);
            cadre(176,176,48,48,132);
            cadre(252,176,56,48,140);
            break; // -> 99
        case 11 :
            cadre(128+8,112-16,48,48,141);
            break; // -> 100
    }
}

void Encyclopedie::cadre(int x, int y, int w, int h, int id) {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    for (int j = y+16; j < y+h-16; j+=16)
        for (int i = x+16; i < x+w-16; i+=16) {
            src.x = 16; src.y = 64; dst.x = i; dst.y = j; 
            SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
    
    //haut et bas
    for (int i = x+16; i < x+w-16; i+=16) {
        src.x = 16; src.y = 48; dst.x = i; dst.y = y; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 80; dst.x = i; dst.y = y+h-16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    //gauche et droite
    for (int j = y+16; j < y+h-16; j+=16) {
        src.x = 0; src.y = 64; dst.x = x; dst.y = j; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 32; src.y = 64; dst.x = x+w-16; dst.y = j;
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    //haut gauche
    src.x = 0; src.y = 48; dst.x = x; dst.y = y; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    //haut droite
    src.x = 32; src.y = 48; dst.x = x+w-16; dst.y = y; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    //bas gauche
    src.x = 0; src.y = 80; dst.x = x; dst.y = y+h-16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    //bas droite
    src.x = 32; src.y = 80; dst.x = x+w-16; dst.y = y+h-16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    if (!gpJeu->getJoueur()->getEnnemi(id)) return;
    if (id != 141) {
    Ennemi* enn = new Ennemi(gpJeu, id, 0, 0, true);
    if (id == 66) enn->setH(124);
    if (id == 93 || id == 98) enn->setSpecial(1,8);
    if (id == 99) enn->setSpecial(1,95);
    if (id == 101) enn->setSpecial(1,1);
    if (id == 103) enn->setSpecial(2,256);
    enn->setX(gpJeu->getPhg(0)+x+((w-enn->getW())/2));
    enn->setY(gpJeu->getPhg(1)+y+((h-enn->getH())/2));
    gpEnnemi->ajout(enn);
    }
}

bool Encyclopedie::isVide() {
    Joueur* gpJoueur = gpJeu->getJoueur();
    switch (page) {
        case 0 :
            if (gpJoueur->getEnnemi(4) || gpJoueur->getEnnemi(53) || gpJoueur->getEnnemi(54)
            || gpJoueur->getEnnemi(27) || gpJoueur->getEnnemi(10) || gpJoueur->getEnnemi(9)
            || gpJoueur->getEnnemi(8) || gpJoueur->getEnnemi(12) || gpJoueur->getEnnemi(6)
            || gpJoueur->getEnnemi(5) || gpJoueur->getEnnemi(1) || gpJoueur->getEnnemi(22)
            || gpJoueur->getEnnemi(3) || gpJoueur->getEnnemi(13) || gpJoueur->getEnnemi(14))
                return false;
            return true;
            break;
        case 1 :
            if (gpJoueur->getEnnemi(18) || gpJoueur->getEnnemi(121) || gpJoueur->getEnnemi(7)
            || gpJoueur->getEnnemi(23) || gpJoueur->getEnnemi(25) || gpJoueur->getEnnemi(16)
            || gpJoueur->getEnnemi(29) || gpJoueur->getEnnemi(19) || gpJoueur->getEnnemi(28)
            || gpJoueur->getEnnemi(40) || gpJoueur->getEnnemi(24) || gpJoueur->getEnnemi(35)
            || gpJoueur->getEnnemi(43))
                return false;
            return true;
            break;
        case 2 :
            if (gpJoueur->getEnnemi(91) || gpJoueur->getEnnemi(93) || gpJoueur->getEnnemi(95)
            || gpJoueur->getEnnemi(104) || gpJoueur->getEnnemi(105) || gpJoueur->getEnnemi(94)
            || gpJoueur->getEnnemi(97) || gpJoueur->getEnnemi(92))
                return false;
            return true;
            break;
        case 3 :
            if (gpJoueur->getEnnemi(84) || gpJoueur->getEnnemi(56) || gpJoueur->getEnnemi(86)
            || gpJoueur->getEnnemi(32) || gpJoueur->getEnnemi(11) || gpJoueur->getEnnemi(55)
            || gpJoueur->getEnnemi(37) || gpJoueur->getEnnemi(15) || gpJoueur->getEnnemi(44)
            || gpJoueur->getEnnemi(26) || gpJoueur->getEnnemi(101) || gpJoueur->getEnnemi(62)
            || gpJoueur->getEnnemi(64))
                return false;
            return true;
            break;
        case 4 :
            if (gpJoueur->getEnnemi(98) || gpJoueur->getEnnemi(102) || gpJoueur->getEnnemi(99)
            || gpJoueur->getEnnemi(103))
                return false;
            return true;
            break;
        case 5 :
            if (gpJoueur->getEnnemi(112) || gpJoueur->getEnnemi(118) || gpJoueur->getEnnemi(77)
            || gpJoueur->getEnnemi(42) || gpJoueur->getEnnemi(41) || gpJoueur->getEnnemi(87)
            || gpJoueur->getEnnemi(30) || gpJoueur->getEnnemi(33) || gpJoueur->getEnnemi(34)
            || gpJoueur->getEnnemi(2) || gpJoueur->getEnnemi(72) || gpJoueur->getEnnemi(38)
            || gpJoueur->getEnnemi(39) || gpJoueur->getEnnemi(119)) 
                return false;
            return true;
            break;
        case 6 :
            if (gpJoueur->getEnnemi(108) || gpJoueur->getEnnemi(110) || gpJoueur->getEnnemi(106)
            || gpJoueur->getEnnemi(76) || gpJoueur->getEnnemi(113) || gpJoueur->getEnnemi(107)
            || gpJoueur->getEnnemi(109) || gpJoueur->getEnnemi(111)) 
                return false;
            return true;
            break;
        case 7 :
            if (gpJoueur->getEnnemi(115) || gpJoueur->getEnnemi(120) || gpJoueur->getEnnemi(89)) 
                return false;
            return true;
            break;
        case 8 :
            if (gpJoueur->getEnnemi(46) || gpJoueur->getEnnemi(47) || gpJoueur->getEnnemi(48)
            || gpJoueur->getEnnemi(31) || gpJoueur->getEnnemi(50)) 
                return false;
            return true;
            break;
        case 9 :
            if (gpJoueur->getEnnemi(123) || gpJoueur->getEnnemi(126) || gpJoueur->getEnnemi(127)
            || gpJoueur->getEnnemi(128)) 
                return false;
            return true;
            break;
        case 10 :
            if (gpJoueur->getEnnemi(129) || gpJoueur->getEnnemi(130) || gpJoueur->getEnnemi(131)
            || gpJoueur->getEnnemi(139) || gpJoueur->getEnnemi(133) || gpJoueur->getEnnemi(134)
            || gpJoueur->getEnnemi(135) || gpJoueur->getEnnemi(136) || gpJoueur->getEnnemi(137)
            || gpJoueur->getEnnemi(138) || gpJoueur->getEnnemi(132) || gpJoueur->getEnnemi(140)) 
                return false;
            return true;
            break;
        case 11 :
            if (gpJoueur->getEnnemi(141)) return false;
            return true;
            break;
    }
    return true;
}

void Encyclopedie::verif(int sens) {
    if (sens == 0) {while (isVide()) {page--; if (page < 0) page = 11;}}
    else {while (isVide()) {page++; if (page > 11) page = 0;}}
}

void Encyclopedie::moveL() {page--; verif(0); init();}

void Encyclopedie::moveR() {page++; verif(1); init();}

void Encyclopedie::setPage(int i) {
    page = i; if (page < 0) page = 0; if (page > 11) page = 11; verif(1);
}