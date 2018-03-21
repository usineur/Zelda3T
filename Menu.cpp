/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <sstream>
#include <iostream>
#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Menu.h"
#include "Texte.h"
#include "Joueur.h"
#include "Monde.h"
#include "Projectile.h"
#include "Jeu.h"

Menu::Menu(Jeu* jeu) : gpJeu(jeu), sens(0), val(0), anim(0) {
    lastAnimTime = SDL_GetTicks();
    
    imageCadre = gpJeu->loadImg("data/images/menu/bord.png");
    imageCoeur = gpJeu->loadImg("data/images/menu/coeur.png");
    imageObjets = gpJeu->loadImg("data/images/statut/objets.png");
    imageInventaire = gpJeu->loadImg("data/images/statut/inventaire.png");
    imageGemme = gpJeu->loadImg("data/images/objet/objets.png");
    
    SDL_SetColorKey(imageCadre,SDL_SRCCOLORKEY,SDL_MapRGB(imageCadre->format,0,0,255));
    SDL_SetColorKey(imageCoeur,SDL_SRCCOLORKEY,SDL_MapRGB(imageCoeur->format,0,0,255));
    SDL_SetColorKey(imageGemme,SDL_SRCCOLORKEY,SDL_MapRGB(imageGemme->format,0,0,255));
}

Menu::~Menu() {
    SDL_FreeSurface(imageCadre);
    SDL_FreeSurface(imageCoeur);
    SDL_FreeSurface(imageObjets);
    SDL_FreeSurface(imageInventaire);
    SDL_FreeSurface(imageGemme);
}

void Menu::draw(SDL_Surface* gpScreen) {
    
    if (!gpJeu->getStop()) gpJeu->setStop(true);
    
    drawCadres(gpScreen);
    
    drawEquipe(gpScreen);
    drawGemme(gpScreen);
    drawCoeur(gpScreen);
    drawCristaux(gpScreen);
    drawStatut(gpScreen);
    drawInventaire(gpScreen);
    drawCurseur(gpScreen);
    
    if(SDL_GetTicks() > lastAnimTime + 240) {
        lastAnimTime = SDL_GetTicks();
        anim++;            
        if (anim > 1) anim = 0;
    }
    
    if(sens==1 && val<200)val+=25;
    if(sens==0 && val > 0) {
        val-=25;
        if (val<=0) gpJeu->setStop(false);
    }
}

void Menu::drawCurseur(SDL_Surface* gpScreen) {
    int dec = 200-val;
    
    SDL_Rect src;
    SDL_Rect dst;
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    src.w=32; src.h=32; src.y=0;
    //curseur
    if (anim==1) {
        if ((gpJoueur->getTypeAnim()<4 || gpJoueur->getTypeAnim()==NAGE || gpJoueur->getTypeAnim()==FLOTTE ||
        (gpJoueur->getTypeAnim()>20 && gpJoueur->getTypeAnim()<25)) 
        && !gpJoueur->getOni()) 
            src.x=48; else src.x=80;
        dst.x=24+32*(gpJoueur->getObjet()%4)-dec; 
        dst.y=24+32*(gpJoueur->getObjet()/4);
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
}

void Menu::drawCadres(SDL_Surface* gpScreen) {
    int dec = 200-val;
    
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=16; src.h=16;
    
    //cadre inventaire
    src.x = 0; src.y = 0; dst.x = 16-dec; dst.y = 16;
    if (dst.x > -15) {
        if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
    }
    src.x = 16;
    for (int i = 0; i < 7; i++) {
        dst.x += 16;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    src.x = 32; dst.x+=16;
    if (dst.x > -15) {
        if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
    }
    src.y=16;
    for (int j = 0; j < 7; j++) {
        src.x=0; dst.x=16-dec; dst.y+=16;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
        src.x=16;
        for (int i = 0; i < 7; i++) {
            dst.x+=16;
            if (dst.x > -15) {
                if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
                SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
                if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
            }
        }
        src.x=32; dst.x+=16;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    src.y=32;
    src.x=0; dst.x=16-dec; dst.y+=16;
    if (dst.x > -15) {
        if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
    }
    src.x=16;
    for (int i = 0; i < 7; i++) {
        dst.x+=16;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    src.x=32; dst.x+=16;
    if (dst.x > -15) {
        if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
    }
    
    
    
    
    //cadre selection
    src.x = 0; src.y = 0; dst.x = 176; dst.y = 16 - dec;
    if (dst.y > -15) {
        if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
    }
    src.x = 16;
    for (int i = 0; i < 6; i++) {
        dst.x += 16;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
    src.x = 32; dst.x+=16;
    if (dst.y > -15) {
        if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
    }
    src.y=32; src.x=0; dst.x=176; dst.y+=16;
    if (dst.y > -15) {
        if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
    }
    src.x=16;
    for (int i = 0; i < 6; i++) {
        dst.x+=16;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
    src.x=32; dst.x+=16;
    if (dst.y > -15) {
        if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
    }
    
    //cadre statut
    src.x = 0; src.y = 0; dst.x = 176; dst.y = 64 - dec;
    if (dst.y > -15) {
        if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
    }
    src.x = 16;
    for (int i = 0; i < 6; i++) {
        dst.x += 16;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
    src.x = 32; dst.x+=16;
    if (dst.y > -15) {
        if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
    }
    src.y=16;
    for (int j = 0; j < 4; j++) {
        src.x=0; dst.x=176; dst.y+=16;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
        src.x=16;
        for (int i = 0; i < 6; i++) {
            dst.x+=16;
            if (dst.y > -15) {
                if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
                SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
                if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
            }
        }
        src.x=32; dst.x+=16;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
    src.y=32; src.x=0; dst.x=176; dst.y+=16;
    if (dst.y > -15) {
        if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
    }
    src.x=16;
    for (int i = 0; i < 6; i++) {
        dst.x+=16;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
    src.x=32; dst.x+=16;
    if (dst.y > -15) {
        if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
    }
    
    
    
    
    //cadre cristaux
    src.x = 0; src.y = 0; dst.x = 80; dst.y = 176+dec;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    src.x = 16;
    for (int i = 0; i < 8; i++) {
        dst.x += 16;
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    }
    src.x = 32; dst.x+=16;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    src.y=16; src.x=0; dst.x=80; dst.y+=16;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    src.x=16;
    for (int i = 0; i < 8; i++) {
        dst.x+=16;
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    }
    src.x=32; dst.x+=16;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    src.y=32; src.x=0; dst.x=80; dst.y+=16;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    src.x=16;
    for (int i = 0; i < 8; i++) {
        dst.x+=16;
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    }
    src.x=32; dst.x+=16;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    
    //cadre gemmes
    src.w=48; src.h=48;
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 176+dec;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    
    //cadre coeur
    src.w=48; src.h=48;
    src.x = 0; src.y = 0; dst.x = 256+dec; dst.y = 176;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    
}

void Menu::drawEquipe(SDL_Surface* gpScreen) {
    int dec = 200-val;
    Joueur* gpJoueur = gpJeu->getJoueur();
    int obj = gpJoueur->getObjet();
    switch(obj) {
        case 0 : 
            if (gpJoueur->hasObjet(O_ARC)==2)
                gpJeu->afficheTexteAvecId(gpScreen, 400, 184,24-dec);
            if (gpJoueur->hasObjet(O_ARC)==5)
                gpJeu->afficheTexteAvecId(gpScreen, 401, 184,24-dec);
            break;
        case 1 : 
            if (gpJoueur->hasObjet(O_GRAPPIN))
                gpJeu->afficheTexteAvecId(gpScreen, 402, 184,24-dec);
            break;
        case 2 : 
            if (gpJoueur->hasObjet(O_SAC_BOMBES) && gpJoueur->getBombe())
                gpJeu->afficheTexteAvecId(gpScreen, 403, 184,24-dec);
            break;
        case 3 :
            if (gpJoueur->hasObjet(O_FFEU)) {
                gpJeu->afficheTexteAvecId(gpScreen, 404, 184,24-dec);
                break;
            }
            switch (gpJoueur->hasObjet(O_TROC1)) {
                case 1 : gpJeu->afficheTexteAvecId(gpScreen, 405, 184,24-dec); break;
                case 2 : gpJeu->afficheTexteAvecId(gpScreen, 406, 184,24-dec); break;
                case 3 : if (!gpJoueur->getCoffre(15,14)) 
                    gpJeu->afficheTexteAvecId(gpScreen, 407, 184,24-dec); break;
                case 4 : gpJeu->afficheTexteAvecId(gpScreen, 408, 184,24-dec); break;
                case 5 : gpJeu->afficheTexteAvecId(gpScreen, 409, 184,24-dec); break;
                case 6 : if (!gpJoueur->getCoffre(15,26)) 
                    gpJeu->afficheTexteAvecId(gpScreen, 410, 184,24-dec); break;
                case 7 : gpJeu->afficheTexteAvecId(gpScreen, 411, 184,24-dec); break;
            }
            break;
        case 4 : 
            if (gpJoueur->hasObjet(O_BFEU))
                gpJeu->afficheTexteAvecId(gpScreen, 412, 184,24-dec);
            break;
        case 5 : 
            if (gpJoueur->hasObjet(O_BGLACE))
                gpJeu->afficheTexteAvecId(gpScreen, 413, 184,24-dec);
            break;
        case 6 : 
            if (gpJoueur->hasObjet(O_LANTERNE))
                gpJeu->afficheTexteAvecId(gpScreen, 414, 184,24-dec);
            break;
        case 7 :
            if (gpJoueur->hasObjet(O_FGLACE)) {
                gpJeu->afficheTexteAvecId(gpScreen, 415, 184,24-dec);
                break;
            }
            switch (gpJoueur->hasObjet(O_TROC2)) {
                case 1 : gpJeu->afficheTexteAvecId(gpScreen, 416, 184,24-dec); break;
                case 2 : gpJeu->afficheTexteAvecId(gpScreen, 417, 184,24-dec); break;
                case 3 : gpJeu->afficheTexteAvecId(gpScreen, 418, 184,24-dec); break;
                case 4 : gpJeu->afficheTexteAvecId(gpScreen, 419, 184,24-dec); break;
                case 5 : gpJeu->afficheTexteAvecId(gpScreen, 420, 184,24-dec); break;
                case 6 : gpJeu->afficheTexteAvecId(gpScreen, 421, 184,24-dec); break;
                case 7 : gpJeu->afficheTexteAvecId(gpScreen, 422, 184,24-dec); break;
            }
            break;
        case 8 : 
            if (gpJoueur->hasObjet(O_MARTEAU))
                gpJeu->afficheTexteAvecId(gpScreen, 423, 184,24-dec);
            break;
        case 9 : 
            if (gpJoueur->hasObjet(O_OCARINA))
                gpJeu->afficheTexteAvecId(gpScreen, 424, 184,24-dec);
            break;
        case 10 : 
            if (gpJoueur->hasObjet(O_CANNE)==1)
                gpJeu->afficheTexteAvecId(gpScreen, 425, 184,24-dec);
            if (gpJoueur->hasObjet(O_CANNE)==2)
                gpJeu->afficheTexteAvecId(gpScreen, 426, 184,24-dec);
            if (gpJoueur->hasObjet(O_CANNE)==3)
                gpJeu->afficheTexteAvecId(gpScreen, 427, 184,24-dec);
            break;
        case 11 :
            if (gpJoueur->hasObjet(O_FLUM)) {
                gpJeu->afficheTexteAvecId(gpScreen, 428, 184,24-dec);
                break;
            }
            switch (gpJoueur->hasObjet(O_TROC3)) {
                case 1 : gpJeu->afficheTexteAvecId(gpScreen, 429, 184,24-dec); break;
                case 2 : gpJeu->afficheTexteAvecId(gpScreen, 430, 184,24-dec); break;
                case 3 : gpJeu->afficheTexteAvecId(gpScreen, 431, 184,24-dec); break;
                case 4 : gpJeu->afficheTexteAvecId(gpScreen, 432, 184,24-dec); break;
                case 5 : gpJeu->afficheTexteAvecId(gpScreen, 433, 184,24-dec); break;
                case 6 : gpJeu->afficheTexteAvecId(gpScreen, 434, 184,24-dec); break;
                case 7 : gpJeu->afficheTexteAvecId(gpScreen, 435, 184,24-dec); break;
                case 8 : gpJeu->afficheTexteAvecId(gpScreen, 436, 184,24-dec); break;
            }
            break;
        case 12 :
        case 13 :
        case 14 :
        case 15 :
            switch (gpJoueur->hasBouteille(obj-12)) {
                case 0 : 
                    if (obj != 15) break;
                    switch (gpJoueur->hasObjet(O_TROC4)) {
                        case 1 : gpJeu->afficheTexteAvecId(gpScreen, 437, 184,24-dec); break;
                        case 2 : gpJeu->afficheTexteAvecId(gpScreen, 438, 184,24-dec); break;
                        case 3 : gpJeu->afficheTexteAvecId(gpScreen, 439, 184,24-dec); break;
                        case 4 : gpJeu->afficheTexteAvecId(gpScreen, 440, 184,24-dec); break;
                        case 5 : gpJeu->afficheTexteAvecId(gpScreen, 441, 184,24-dec); break;
                        case 6 : gpJeu->afficheTexteAvecId(gpScreen, 442, 184,24-dec); break;
                        case 7 : gpJeu->afficheTexteAvecId(gpScreen, 443, 184,24-dec); break;
                    }
                    break;
                case 1 : gpJeu->afficheTexteAvecId(gpScreen, 444, 184,24-dec); break;
                case 2 : gpJeu->afficheTexteAvecId(gpScreen, 445, 184,24-dec); break;
                case 3 : gpJeu->afficheTexteAvecId(gpScreen, 446, 184,24-dec); break;
                case 4 : gpJeu->afficheTexteAvecId(gpScreen, 447, 184,24-dec); break;
            }
            break;
    }
    
}

void Menu::drawInventaire(SDL_Surface* gpScreen) {
    int dec = 200-val;
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    gpJeu->affiche(gpScreen, "X", 20-dec,20);

    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=16; src.h=17;
    
    //arc
    if (gpJoueur->hasObjet(O_ARC)) {
        src.x=0; dst.x=32-dec; dst.y=32;
        if (gpJoueur->hasObjet(O_ARC)==5)src.y=0; else {src.x=16; src.y=102;}
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //grappin
    if (gpJoueur->hasObjet(O_GRAPPIN)) {
        src.x=16; src.y=0; dst.x=64-dec; dst.y=32;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //bombes
    if (gpJoueur->hasObjet(O_SAC_BOMBES) && gpJoueur->getBombe()>0) {
        src.x=32; src.y=0; dst.x=96-dec; dst.y=32;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //troc 1 ou flèche feu
    if (gpJoueur->hasObjet(O_FFEU)) {
        src.x=0; src.y=136; dst.x=128-dec; dst.y=32;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    else if (gpJoueur->hasObjet(O_TROC1)) {
        src.x=0; src.y=0; dst.x=128-dec; dst.y=32; src.h=16;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            if (gpJoueur->hasObjet(O_TROC1)==1) {
                src.x+=128;
                SDL_BlitSurface(gpJeu->getStatut()->getImageGemmes(), &src, gpScreen, &dst);
            } else {
                src.x+=(gpJoueur->hasObjet(O_TROC1)-2)*16; src.y+=64;
                if ((gpJoueur->hasObjet(O_TROC1)!=3 || !gpJoueur->getCoffre(15,14)) 
                && (gpJoueur->hasObjet(O_TROC1)!=6 || !gpJoueur->getCoffre(15,26)) )
                    SDL_BlitSurface(gpJeu->getStatut()->getImageTroc(), &src, gpScreen, &dst);
            }
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
        src.h=17;
    }
    
    //baguette de feu
    if (gpJoueur->hasObjet(O_BFEU)) {
        src.x=0; src.y=17; dst.x=32-dec; dst.y=64;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //baguette de glace
    if (gpJoueur->hasObjet(O_BGLACE)) {
        src.x=16; src.y=17; dst.x=64-dec; dst.y=64;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //lanterne
    if (gpJoueur->hasObjet(O_LANTERNE)) {
        src.x=32; src.y=17; dst.x=96-dec; dst.y=64;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //troc 2 ou flèche glace
    if (gpJoueur->hasObjet(O_FGLACE)) {
        src.x=16; src.y=136; dst.x=128-dec; dst.y=64;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    else if (gpJoueur->hasObjet(O_TROC2)) {
        src.x=0; src.y=16; dst.x=128-dec; dst.y=64; src.h=16;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            if (gpJoueur->hasObjet(O_TROC2)==1) {
                src.x+=128;
                SDL_BlitSurface(gpJeu->getStatut()->getImageGemmes(), &src, gpScreen, &dst);
            } else {
                src.x+=(gpJoueur->hasObjet(O_TROC2)-2)*16; src.y+=64;
                SDL_BlitSurface(gpJeu->getStatut()->getImageTroc(), &src, gpScreen, &dst);
            }
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
        src.h=17;
    }
    
    //marteau
    if (gpJoueur->hasObjet(O_MARTEAU)) {
        src.x=0; src.y=34; dst.x=32-dec; dst.y=96;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //flute
    if (gpJoueur->hasObjet(O_OCARINA)) {
        src.x=0; src.y=85; dst.x=64-dec; dst.y=96;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //canne à pêche
    if (gpJoueur->hasObjet(O_CANNE)) {
        src.y=119; dst.x=96-dec; dst.y=96;
        src.x=(gpJoueur->hasObjet(O_CANNE)-1)*16;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //troc 3 ou flèche lumière
    if (gpJoueur->hasObjet(O_FLUM)) {
        src.x=32; src.y=136; dst.x=128-dec; dst.y=96;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    else if (gpJoueur->hasObjet(O_TROC3)) {
        src.x=0; src.y=32; dst.x=128-dec; dst.y=96; src.h=16;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            if (gpJoueur->hasObjet(O_TROC3)==1) {
                src.x+=128;
                SDL_BlitSurface(gpJeu->getStatut()->getImageGemmes(), &src, gpScreen, &dst);
            } else {
                src.x+=(gpJoueur->hasObjet(O_TROC3)-2)*16; src.y+=64;
                SDL_BlitSurface(gpJeu->getStatut()->getImageTroc(), &src, gpScreen, &dst);
            }
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
        src.h=17;
    }

    
    
    //troc 4
    if (gpJoueur->hasObjet(O_TROC4)) {
        src.x=0; src.y=48; dst.x=128-dec; dst.y=128; src.h=16;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            if (gpJoueur->hasObjet(O_TROC4)==1) {
                src.x+=128;
                SDL_BlitSurface(gpJeu->getStatut()->getImageGemmes(), &src, gpScreen, &dst);
            } else {
                src.x+=(gpJoueur->hasObjet(O_TROC4)-2)*16; src.y+=64;
                SDL_BlitSurface(gpJeu->getStatut()->getImageTroc(), &src, gpScreen, &dst);
            }
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
        src.h=17;
    }
    
    //bouteilles
    for (int i = 0; i < 4; i++) {
        if (gpJoueur->hasBouteille(i)) {
            dst.x=32*(i+1)-dec; dst.y=128;
            switch (gpJoueur->hasBouteille(i)) {
                case 1 : src.x=0; src.y=68; break;
                case 2 : src.x=0; src.y=51; break;
                case 3 : src.x=16; src.y=51; break;
                case 4 : src.x=32; src.y=51; break;
            }    
            if (dst.x > -15) {
                if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
                SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
                if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
            }
        }
    }
    
}

void Menu::drawStatut(SDL_Surface* gpScreen) {
    int dec = 200-val;
    std::ostringstream oss;
    
    Joueur* gpJoueur = gpJeu->getJoueur();

    SDL_Rect src;
    SDL_Rect dst;
    
    //force
    int nb_chiffres=1;
    if (gpJoueur->getForce() > 9) nb_chiffres=2;
    src.w=12; src.h=12; src.x=124; src.y=32; dst.x=181; dst.y=72-3-dec;
    if (dst.y > -15) {
        SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
        gpJeu->getStatut()->drawNombre(gpScreen, 
            gpJoueur->getForce(), 10, 191, 72-3+3-dec, nb_chiffres);
    }
    
    //défense
    if (gpJoueur->getDefense() > 9) nb_chiffres=2; else nb_chiffres=1;
    src.w=12; src.h=12; src.x=136; src.y=32; dst.x=207; dst.y=72-3-dec;
    if (dst.y > -15) {
        SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
        gpJeu->getStatut()->drawNombre(gpScreen, 
            gpJoueur->getDefense(), 10, 218, 72-3+3-dec, nb_chiffres);
    }
    
    //temps
    src.w=12; src.h=12; src.x=112; src.y=32; dst.x=234; dst.y=72-3-dec;
    if (dst.y > -15) {
        SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
        gpJeu->getStatut()->drawNombre(gpScreen, 
            gpJoueur->getTemps(2), -1, 246, 72-3+3-dec, 2);
        gpJeu->getStatut()->drawSeparateur(gpScreen, 261, 72-3+3-dec);
        gpJeu->getStatut()->drawNombre(gpScreen, 
            gpJoueur->getTemps(1), -1, 264, 72-3+3-dec, 2);
        gpJeu->getStatut()->drawSeparateur(gpScreen, 279, 72-3+3-dec);
        gpJeu->getStatut()->drawNombre(gpScreen, 
            gpJoueur->getTemps(0), -1, 282, 72-3+3-dec, 2);
    }
    
    //bourse rubis
    src.w=16; src.h=16; src.y=48; dst.x=184-4; dst.y=88-4-dec;
    nb_chiffres=3;
    switch(gpJoueur->getRubisMax()) {
        case 99 :
            nb_chiffres=2;
            src.x=0; SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            break;
        case 200 :
            src.x=16; SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            break;
        case 500 :
            src.x=32; SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            break;
        case 999 :
            src.x=48; SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            break;
    }
    if (gpJoueur->getRubisMax())
    gpJeu->getStatut()->drawNombre(gpScreen, 
            gpJoueur->getRubis() + gpJoueur->getBoostRubis(), 
            gpJoueur->getRubisMax(), 200-4, 88-4+5-dec, nb_chiffres);
            
    //bourse ganon d'or
    int decx=0;
    if (gpJoueur->getPieceMax() == 0) decx=16;
    src.w=16; src.h=16; src.y=48; dst.x=184+32+4+decx; dst.y=88-4-dec;
    nb_chiffres=3;
    switch(gpJoueur->getGanonMax()) {
        case 99 :
            nb_chiffres=2;
            src.x=64; SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            break;
        case 200 :
            src.x=80; SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            break;
        case 500 :
            src.x=96; SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            break;
        case 999 :
            src.x=112; SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            break;
    }
    if (gpJoueur->getGanonMax())
        gpJeu->getStatut()->drawNombre(gpScreen, 
            gpJoueur->getGanon() + gpJoueur->getBoostGanon()
            , gpJoueur->getGanonMax(), 200+32+4+decx, 88-4+5-dec, nb_chiffres);
            
    //bourse pièces d'or
    src.w=16; src.h=16; src.y=48; dst.x=184+64+8+4; dst.y=88-4-dec;
    nb_chiffres=3;
    switch(gpJoueur->getPieceMax()) {
        case 99 :
            nb_chiffres=2;
            src.x=128; SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            break;
        case 200 :
            src.x=144; SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            break;
        case 500 :
            src.x=160; SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            break;
        case 999 :
            src.x=176; SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            break;
    }
    if (gpJoueur->getPieceMax())
        gpJeu->getStatut()->drawNombre(gpScreen, 
            gpJoueur->getPiece() + gpJoueur->getBoostPiece(), 
            gpJoueur->getPieceMax(), 200+64+8+4, 88-4+5-dec, nb_chiffres);
    
    
    // carquois
    if (gpJoueur->hasObjet(O_ARC)) {
        dst.x=184-4; dst.y=120-16-2-dec; src.x=176; src.y=32; src.w=16; src.h=16;
        if (dst.y > -15) SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
        gpJeu->getStatut()->drawNombre(gpScreen, 
            gpJoueur->getFlecheMax(), 70, 184-4+16, 120-16+5-dec, 2);
        if (gpJoueur->hasObjet(O_RECUP_FLECHE)) {
            dst.x=184-4+16; dst.y=120-16-2-dec; src.x=148; src.y=32; src.w=9; src.h=8;
            if (dst.y > -15) SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
        }
    }
    
    // sac bombes
    if (gpJoueur->hasObjet(O_SAC_BOMBES)) {
        dst.x=184+32+4; dst.y=120-16-2-dec; src.x=112; src.y=16; src.w=16; src.h=16;
        if (dst.y > -15) SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
        gpJeu->getStatut()->drawNombre(gpScreen, 
            gpJoueur->getBombeMax(), 30, 184+32+4+16, 120-16+5-dec, 2);
        if (gpJoueur->hasObjet(O_RECUP_BOMBE)) {
            dst.x=184+32+4+16; dst.y=120-16-2-dec; src.x=148; src.y=32; src.w=9; src.h=8;
            if (dst.y > -15) SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
        }
    }
    
    //notes
    dst.x=184+64+8; src.y=153; dst.y=120-16-2-dec; src.w=16; src.h=16;
    for (int i = 0; i < 3; i++) {
        src.x=16*i;
        if (gpJoueur->hasMelodie(i) && dst.y > -15) SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
        dst.x+=14;
    }
    
    
    src.y=32; dst.x=184-4;
    
    int haut=120-dec;
    if (gpJoueur->nbCristaux()==0) haut=136+2-dec;
    
    if (gpJoueur->getAvancement() >= STELE_LUE) { //stêle lue
    for (int i = 0; i < 3; i++) {
        dst.y=haut;
        if (gpJoueur->hasMedaillon(i)) src.x=16*i;
        else src.x=48;
        if (dst.y > -15) SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
        dst.x+=17;
    }}
    
    //clé du temps
    if (gpJoueur->hasObjet(O_CLE_TEMPS)) {
        dst.y=haut; src.x=80;
        if (dst.y > -15) SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
    }
    dst.x+=17;
    
    //arc d'or
    if (gpJoueur->hasObjet(O_ARC_OR)) {
        dst.y=haut; src.x=96;
        if (dst.y > -15) SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
    }
    dst.x+=17;
    
    //détecteur gemmes force
    if (gpJoueur->hasObjet(O_DETECTEUR)) {
        dst.y=haut; src.x=160; src.y=32;
        if (dst.y > -15) SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
    }
    dst.x+=17;
    
    //masque
    if (gpJoueur->hasObjet(O_MASQUE)) {
        dst.y=haut; src.x=16; src.y=85;
        if (dst.y > -15) SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
    }
    
    if (gpJoueur->nbCristaux()==0) return;
    
    src.y=68;
    dst.x=184-4;
    
    //cristaux
    for (int i = 0; i < 7; i++) {
        dst.y=136+2-dec;
        if (gpJoueur->hasCristal(i)) src.x=16;
        else src.x=32;
        if (dst.y > -15) SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
        dst.x+=17;
    }
}

void Menu::drawCristaux(SDL_Surface* gpScreen) {
    int dec = 200-val;
    
    gpJeu->afficheTexteAvecId(gpScreen, 448, 84,180+dec);
    
    SDL_Rect src;
    SDL_Rect dst;
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    src.y=0; src.w=16; src.h=16; dst.y=198+dec;
    
    //Epée
    if (gpJoueur->getEpee()) {
        src.x = 16 * (gpJoueur->getEpee()-1); dst.x=86;
        if (gpJoueur->getOni()) src.x=112;
        SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
    }
    //bouclier
    if (gpJoueur->getBouclier()) {
        src.x = 16 * (gpJoueur->getBouclier()-1); src.y=16; dst.x=105;
        if (gpJoueur->getBouclier()==4) src.x=178;
        if (gpJoueur->getOni()) {src.x=96; src.y=0;}
        SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
    }
    //tunique
    if (gpJoueur->getTunique()) {
        src.x = 48 + 16 * (gpJoueur->getTunique()-1); src.y=16; dst.x=124;
        if (gpJoueur->getTunique()==4 && !gpJoueur->getOni()) {src.x=178; src.y=0;}
        if (gpJoueur->getOni()) src.x=96;
        SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
    }
    //bottes
    if (gpJoueur->hasObjet(O_BOTTES)) {
        src.x = 80; src.y=0; dst.x=143;
        SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
    }
    //gants
    if (gpJoueur->hasObjet(O_GANTS)) {
        src.x=32; dst.x=162;
        if (gpJoueur->hasObjet(O_GANTS)==2)src.y=34; else src.y=85;
        SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
    }
    //palmes
    if (gpJoueur->hasObjet(O_PALMES)) {
        src.x=16; src.y=34; dst.x=181;
        SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
    }
    //perle lune
    if (gpJoueur->hasObjet(O_PERLE)) {
        src.x=64; src.y=32; dst.x=200;
        SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
    }
    //livre de mudora
    if (gpJoueur->hasObjet(O_LIVRE)) {
        src.x = 32; src.y = 102; dst.x=219;
        SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
    }
}

void Menu::drawGemme(SDL_Surface* gpScreen) {
    int dec = 200-val;
    
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=16; src.h=16; src.y=69; src.x=161;
    dst.x=32; dst.y=192-4+dec;
    
    SDL_BlitSurface(imageGemme, &src, gpScreen, &dst);
    
    int nb = 2;
    int val = gpJeu->getJoueur()->getGemme();
    if (val > 99) nb = 3;
    
    int max=-1;
    if (gpJeu->getJoueur()->hasObjet(O_DETECTEUR) && !gpJeu->getNbGemmes()) max = val;
    
    if (gpJeu->getZone()==10 && (!gpJeu->getJoueur()->getGemme(91) 
    || !gpJeu->getJoueur()->getGemme(92) || !gpJeu->getJoueur()->getGemme(93))) max =-1;
    
    if (gpJeu->getZone()==89 && (!gpJeu->getJoueur()->getGemme(160) 
    || !gpJeu->getJoueur()->getGemme(161) || !gpJeu->getJoueur()->getGemme(162))) max =-1;
    
    if (gpJeu->getZone()==119 && !gpJeu->getJoueur()->getGemme(173)) max =-1;
    
    if (gpJeu->getZone()==137 && !gpJeu->getJoueur()->getGemme(178)) max =-1;
    
    if (gpJeu->getZone()==145 && !gpJeu->getJoueur()->getGemme(182)) max =-1;
    
    gpJeu->getStatut()->drawNombre(gpScreen, val, max, 28+4*(3-nb), 208+dec-2, nb);
}

void Menu::drawCoeur(SDL_Surface* gpScreen) {
    int dec = 200-val;
    
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=16; src.h=16; src.y=0; src.x = 16*(gpJeu->getJoueur()->nbQuarts()%4);
    dst.x = 272+dec; dst.y = 192;
    SDL_BlitSurface(imageCoeur, &src, gpScreen, &dst);
}

void Menu::menuIn() {
    sens = 1; val = 0;
    gpJeu->getAudio()->playSound(1);
}

void Menu::menuOut() {
    sens = 0;
    gpJeu->getAudio()->playSound(2);
}

int Menu::getVal() { return val;}
