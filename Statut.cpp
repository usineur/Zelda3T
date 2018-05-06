/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "Statut.h"
#include "Joueur.h"
#include "Monde.h"
#include "Menu.h"
#include "Texte.h"
#include "Projectile.h"
#include "Jeu.h"
#include "Lang.h"

#include <iostream>

Statut::Statut(Jeu* jeu) : gpJeu(jeu), jauge(false), valjauge(0), maxjauge(10), nivjauge(50), 
valjauge2(0), maxjauge2(10), nivjauge2(60), dec(0) {
    
    imageStatut = gpJeu->loadImg("data/images/statut/statut.png");
    imageChiffre = gpJeu->loadImg("data/images/statut/chiffres.png");
    imageInventaire = gpJeu->loadImg("data/images/statut/inventaire.png");
    imageTroc = gpJeu->loadImg("data/images/objet/troc.png");
    imageGemmes = gpJeu->loadImg("data/images/objet/gemmes.png");
    
    SDL_SetColorKey(imageStatut,SDL_SRCCOLORKEY,SDL_MapRGB(imageStatut->format,0,0,255));
    SDL_SetColorKey(imageChiffre,SDL_SRCCOLORKEY,SDL_MapRGB(imageChiffre->format,0,0,255));
    SDL_SetColorKey(imageTroc,SDL_SRCCOLORKEY,SDL_MapRGB(imageTroc->format,0,0,255));
    SDL_SetColorKey(imageGemmes,SDL_SRCCOLORKEY,SDL_MapRGB(imageGemmes->format,0,0,255));
}

Statut::~Statut() {
    SDL_FreeSurface(imageStatut);
    SDL_FreeSurface(imageChiffre);
    SDL_FreeSurface(imageInventaire);
    SDL_FreeSurface(imageTroc);
    SDL_FreeSurface(imageGemmes);
}

void Statut::draw(SDL_Surface* gpScreen) {
    drawBoss(gpScreen);
    drawItems(gpScreen);
    drawVie(gpScreen);
    drawMagie(gpScreen);
}

void Statut::drawBoss(SDL_Surface* gpScreen) {
    SDL_Rect src;
    SDL_Rect dst;

    //jauge vie boss
    if (valjauge<0) valjauge=0;
    if (valjauge2<0) valjauge2=0;
    
    int niv = 220;
    if (gpJeu->getZone()==58 && gpJeu->getText()) niv = 215;
    
    if (jauge==false) {valjauge=0; valjauge2=0;}
    
    if (jauge==true || nivjauge<50 || nivjauge2<60) {
        
        //armée de Ganon dans OLB
        /*if (gpJeu->getZone() == 9) {
            valjauge=gpJeu->nbEnnemis();
            maxjauge=20;
        }*/
        
        if (jauge==true && valjauge>0 && nivjauge>0 && (!gpJeu->getStop() || gpJeu->getText())) 
            nivjauge--;
        if ((jauge==false || (gpJeu->getZone()==25 && valjauge==0 && valjauge2>0)) 
            && nivjauge<50 && (!gpJeu->getStop() || gpJeu->getText())) nivjauge++;
        if (valjauge2>0 && nivjauge2>0 && (!gpJeu->getStop() || gpJeu->getText())) nivjauge2--;
        if (valjauge2==0 && nivjauge2<60 && (!gpJeu->getStop() || gpJeu->getText())) nivjauge2++;
        if (gpJeu->getZone()==25 && dec<60 && valjauge>0 && valjauge2>0 
            && (!gpJeu->getStop() || gpJeu->getText())) dec++;
        if (gpJeu->getZone()==25 && dec>0 && (valjauge==0 || valjauge2==0) 
            && (!gpJeu->getStop() || gpJeu->getText())) dec--;
        
        
        src.h = 10;src.w = 100;
        dst.x = 110-dec;dst.y = niv+nivjauge;
        src.x=100;src.y=45;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
        
        if (maxjauge==0) maxjauge=1;
        if(valjauge>maxjauge) valjauge = maxjauge;
        src.w = (valjauge*90)/maxjauge;src.h = 10;
        dst.x = 115-dec;dst.y = niv+nivjauge;
        src.x=5+90-src.w;src.y=45;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
        
        if (gpJeu->getZone()==25 && nivjauge2<50) {
            
        src.h = 10;src.w = 100;
        dst.x = 110+dec;dst.y = 220+nivjauge2;
        src.x=100;src.y=45;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
        
        if (maxjauge2==0) maxjauge2=1;
        if(valjauge2>maxjauge2) valjauge2 = maxjauge2;
        src.w = (valjauge2*90)/maxjauge2;src.h = 10;
        dst.x = 115+dec;dst.y = 220+nivjauge2;
        src.x=5+90-src.w;src.y=45;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
        
        }
        
    }
}

void Statut::drawMagie(SDL_Surface* gpScreen) {
    SDL_Rect src;
    SDL_Rect dst;
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    //jauge magie
    if (gpJoueur->hasObjet(O_LANTERNE)) {
        src.h = 45; src.w = 16; src.x = 0; src.y = 0;
        dst.x = 10; dst.y = 10;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
        //demi magie
        if (gpJoueur->getMagieMax()>32) {
            src.h = 8; src.w = 16; src.x = 186; src.y = 37;
            SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
        }
        src.h = (gpJoueur->getMagie()/(gpJoueur->getMagieMax()/32));src.w = 8;
        dst.x = 14;
        dst.y = 50-(gpJoueur->getMagie()/(gpJoueur->getMagieMax()/32));
        src.x=124;src.y=8;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
    }
    
    //emplacement objet
    if (gpJoueur->hasObjet(O_ARC)) {
        src.h = 22;src.w = 22; src.x=17; src.y=5;
        dst.x = 27; dst.y = 15;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
    }
    
    src.h = 17; src.w = 16;
    dst.x = 30; dst.y = 18;
    //bool test=false;
    int obj = gpJoueur->getObjet();
    int old_obj = obj;
    switch (obj) {
        case 0 : 
            obj = O_ARC;
            src.x=0; src.y=0; if (gpJoueur->hasObjet(O_ARC)==2){src.x=16;src.y=102;} break;
        case 1 : src.x=16; src.y=0; break;
        case 2 : obj = O_SAC_BOMBES; src.x=32; src.y=0; break;
        case 3 :
            if (gpJoueur->hasObjet(O_FFEU)) {obj = O_FFEU; src.x=0; src.y=136; break;}
            if (gpJoueur->hasObjet(O_TROC1)) {
                obj = O_TROC1; src.y=0; src.h=16;
                if (gpJoueur->hasObjet(O_TROC1) > 1) {
                    src.x=(gpJoueur->hasObjet(O_TROC1)-2)*16; src.y+=64;
                    if ((gpJoueur->hasObjet(O_TROC1)!=3 || !gpJoueur->getCoffre(15,14)) 
                    && (gpJoueur->hasObjet(O_TROC1)!=6 || !gpJoueur->getCoffre(15,26)) )
                        SDL_BlitSurface(imageTroc, &src, gpScreen, &dst);
                }
                else {
                    src.x=128;
                    SDL_BlitSurface(imageGemmes, &src, gpScreen, &dst);
                }
            } else return;
            break;
        case 4 : obj = O_BFEU; src.x=0; src.y=17; break;
        case 5 : obj = O_BGLACE; src.x=16; src.y=17; break;
        case 6 : obj = O_LANTERNE; src.x=32; src.y=17; break;
        case 7 :
            if (gpJoueur->hasObjet(O_FGLACE)) {obj = O_FGLACE; src.x=16; src.y=136; break;}
            if (gpJoueur->hasObjet(O_TROC2)) {
                obj = O_TROC2; src.y=16; src.h=16;
                if (gpJoueur->hasObjet(O_TROC2) > 1) {
                    src.x=(gpJoueur->hasObjet(O_TROC2)-2)*16; src.y+=64;
                    SDL_BlitSurface(imageTroc, &src, gpScreen, &dst);
                }
                else {
                    src.x=128;
                    SDL_BlitSurface(imageGemmes, &src, gpScreen, &dst);
                }
            } else return;
            break;
        case 8 : obj = O_MARTEAU; src.x=0; src.y=34; break;
        case 9 : obj = O_OCARINA; src.x=0; src.y=85; break;
        case 10 : obj = O_CANNE; src.x=(gpJoueur->hasObjet(O_CANNE)-1)*16; src.y=119; break;
        case 11 :
            if (gpJoueur->hasObjet(O_FLUM)) {obj = O_FLUM; src.x=32; src.y=136; break;}
            if (gpJoueur->hasObjet(O_TROC3)) {
                obj = O_TROC3; src.y=32; src.h=16;
                if (gpJoueur->hasObjet(O_TROC3) > 1) {
                    src.x=(gpJoueur->hasObjet(O_TROC3)-2)*16; src.y+=64;
                    SDL_BlitSurface(imageTroc, &src, gpScreen, &dst);
                }
                else {
                    src.x=128;
                    SDL_BlitSurface(imageGemmes, &src, gpScreen, &dst);
                }
            } else return;
            break;
        case 15 :
            if (gpJoueur->hasObjet(O_TROC4) && !gpJoueur->hasBouteille(3)) {
                obj = O_TROC4; src.y=48; src.h=16;
                if (gpJoueur->hasObjet(O_TROC4) > 1) {
                    src.x=(gpJoueur->hasObjet(O_TROC4)-2)*16; src.y+=64;
                    SDL_BlitSurface(imageTroc, &src, gpScreen, &dst);
                }
                else {
                    src.x=128;
                    SDL_BlitSurface(imageGemmes, &src, gpScreen, &dst);
                }
                break;
            } else if (!gpJoueur->hasBouteille(3)) return;
        default :
            obj=O_BOUTEILLE;
            src.x=0;
            if(gpJoueur->hasBouteille(old_obj-12)==3)src.x=16;
            if(gpJoueur->hasBouteille(old_obj-12)==4)src.x=32;
            if(gpJoueur->hasBouteille(old_obj-12)>1)src.y=51;
            if(gpJoueur->hasBouteille(old_obj-12)==1)src.y=68;
            break;
    }    
    if(obj != O_BOUTEILLE) {
        if (gpJoueur->hasObjet(obj)) 
            if ((gpJoueur->getObjet() != 2 || gpJoueur->getBombe()) 
            && obj != O_TROC1 && obj != O_TROC2 && obj != O_TROC3 && obj != O_TROC4)
                SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
    }
    else {
        if(gpJoueur->hasBouteille(old_obj-12))
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
    }
    
}

void Statut::drawVie(SDL_Surface* gpScreen) {
    SDL_Rect src;
    SDL_Rect dst;
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    //life
    int langId = getLanguage();
    src.h = (langId == LANG_FR) ? 8 : 7;
    src.w = 44;
    dst.x = 250;
    dst.y = 10;
    src.x=158;
    src.y = (langId == LANG_FR) ? 17 : 0;
    SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
    
    for(int i=0; i < gpJoueur->getVieMax()/2; i++) {
        src.h = 7; src.w = 7;
        dst.x = 233+((i%10)*8);dst.y = 19+8*((int)(i/10));
        src.y=9;
        if (gpJoueur->getVie()-(i*2)>1)src.x=141;
        if (gpJoueur->getVie()-(i*2)==1)src.x=149;
        if (gpJoueur->getVie()-(i*2)<1)src.x=157;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
    }    
}

void Statut::drawItems(SDL_Surface* gpScreen) {
    SDL_Rect src;
    SDL_Rect dst;
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    //argent
    if (gpJeu->getZone() != 60) {
    src.h = 8;src.w = 8;
    dst.x =129;dst.y = 10;
    switch (gpJeu->getEpoque()) {
        case T_PASSE :
            //pièce d'or
            if (gpJoueur->getPieceMax()==0) break;
            src.x=52;src.y=18;
            SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
            if (gpJoueur->getPieceMax() > 99)
                drawNombre(gpScreen, gpJoueur->getPiece(), gpJoueur->getPieceMax(),121,20,3); 
            else
                drawNombre(gpScreen, gpJoueur->getPiece(), gpJoueur->getPieceMax(),125,20,2);
            break;
        case T_PRESENT :
            //rubis
            if (gpJoueur->getRubisMax()==0) break;
            src.x=52;src.y=0;
            SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
            if (gpJoueur->getRubisMax() > 99)
                drawNombre(gpScreen, gpJoueur->getRubis(), gpJoueur->getRubisMax(),121,20,3); 
            else
                drawNombre(gpScreen, gpJoueur->getRubis(), gpJoueur->getRubisMax(),125,20,2);
            break;
        case T_FUTUR :
            //ganon d'or
            if (gpJoueur->getGanonMax()==0) break;
            src.x=64;src.y=18;
            SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
            if (gpJoueur->getGanonMax() > 99)
                drawNombre(gpScreen, gpJoueur->getGanon(), gpJoueur->getGanonMax(),121,20,3); 
            else
                drawNombre(gpScreen, gpJoueur->getGanon(), gpJoueur->getGanonMax(),125,20,2);
            break;
    }
    }
    
    //bombes
    if (gpJoueur->hasObjet(O_SAC_BOMBES)) {
        src.h = 8;src.w = 8;
        dst.x =157;dst.y = 10;
        src.x=80;src.y=0;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
        drawNombre(gpScreen, gpJoueur->getBombe(), gpJoueur->getBombeMax(),153,20,2);
    }
    //fleches
    if (gpJoueur->hasObjet(O_ARC)) {
        src.h = 8;src.w = 14;
        dst.x =178;dst.y = 10;
        src.x=101;
        if (gpJoueur->hasObjet(O_ARC) == 5) src.y=21; else src.y=0;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
        drawNombre(gpScreen, gpJoueur->getFleche(), gpJoueur->getFlecheMax(),177,20,2);
    }
    
    //clées
    if (gpJeu->isDonjon() || (gpJeu->getZone() == 155 && gpJoueur->getCle())) {
        src.h = 8;src.w = 8;
        dst.x =89;dst.y = 10;
        src.x=50;src.y=28;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
        if (gpJoueur->getCle() > 9)
            drawNombre(gpScreen, gpJoueur->getCle(), 99,81,20,2);
        else
            drawNombre(gpScreen, gpJoueur->getCle(), 99,89,20,1);
    }
    
    //argent casino
    if (gpJoueur->isCompteurVisible() && gpJeu->getZone()==58) {
        int h = 16*14;
        if (gpJeu->getText() && gpJeu->getMonde()->regionValue(0)==60*16 
        && gpJeu->getMonde()->regionValue(1)==30*16) h -= 8;
        src.x=64;src.y=18;
        src.h = 8;src.w = 8;
        dst.x =16;dst.y = h;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
        drawNombre(gpScreen, gpJoueur->getCompteur(), gpJoueur->getGanonMax(),32,h,3); 
    }
    
    //course casino
    if (gpJoueur->isTempsVisible()) {
        src.x=78;src.y=28;
        src.h = 10;src.w = 12;
        dst.x =16*17+8;dst.y = 16*14;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
        Uint32 time = gpJoueur->getTimeC();
        if (time > 21*1000) {
            time = 21*1000;
            gpJoueur->setTempsVisible(false);
        }
        int t = 21-((int)(time / 1000));
        drawNombre(gpScreen, t, 30,320-32+8,16*14,2);
    }
    
    //dégâts destination finale
    if (gpJoueur->isCompteurVisible() && gpJeu->getZone()==60) {
        src.h = 7; src.w = 7; src.y=9; src.x=141;
        int h = 16*14; int d = gpJoueur->getCompteur();
        if (d == 0) {src.x=149; d=1;}
        dst.x =16;dst.y = h;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
        drawNombre(gpScreen, d, 20,32,h,2);
    }
    
    //ennemis destination finale
    if (gpJoueur->isEnnVisible() && gpJeu->getZone()==60) {
        if (gpJoueur->getCoffre(14,9) && gpJoueur->getCoffre(14,10)
        && gpJoueur->getCoffre(14,11) && gpJoueur->getCoffre(14,12)
        && gpJoueur->getCoffre(14,13) && gpJoueur->getCoffre(14,14)
        && gpJoueur->getCoffre(14,15)) return;
        
        //types d'ennemis
        src.h = 8; src.w = 8; src.y=33; src.x=96;
        int h = 16*14; int d = gpJoueur->getCompteurType();
        dst.x =16*15;dst.y = h;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
        drawNombre(gpScreen, d, 12,32+16*14,h,2); 
        
        //nb d'ennemis
        src.h = 6; src.w = 6; src.y=33; src.x=104;
        h = 16*14; d = gpJoueur->getCompteurEnn();
        dst.x =16*17+5;dst.y = h+1;
        SDL_BlitSurface(imageStatut, &src, gpScreen, &dst);
        drawNombre(gpScreen, d, 99,32+16*16,h,2); 
    }
}

void Statut::drawSeparateur(SDL_Surface* gpScreen, int x, int y, int max) {
    SDL_Rect src;
    SDL_Rect dst;
    src.h = 8;src.w = 8;
    dst.x = x;dst.y = y;
    src.x = 40;
    if (max) src.y = 16; else src.y = 0;
    SDL_BlitSurface(imageChiffre, &src, gpScreen, &dst);
}

void Statut::drawNombre(SDL_Surface* gpScreen, int val, int max, int x, int y, int nb) {
    int val2;
    
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 8;src.w = 8;
    
    dst.x = x;dst.y = y;
    
    //si on commence par les centaines
    if (nb >= 3) {
        val2 = val/100;
        src.x = (val2%5)*8;
        src.y = ((int)(val2/5))*8;
        if (val == max) src.y += 16;
        SDL_BlitSurface(imageChiffre, &src, gpScreen, &dst);
        dst.x += 8;
    }
    
    //les dizaines
    if (nb >= 2) {
        dst.y = y;
        val2 = (val%100)/10;
        src.x = (val2%5)*8;
        src.y = ((int)(val2/5))*8;
        if (val == max) src.y += 16;
        SDL_BlitSurface(imageChiffre, &src, gpScreen, &dst);
        dst.x += 8;
    }
    
    //unitées
    dst.y = y;
    val2 = val%10;
    src.x = (val2%5)*8;
    src.y = ((int)(val2/5))*8;
    if (val == max) src.y += 16;
    SDL_BlitSurface(imageChiffre, &src, gpScreen, &dst);
    
}

bool Statut::getJauge() {return jauge;}
void Statut::setJauge(bool b) {jauge=b;}
void Statut::setValJauge(int i) {valjauge=i;}
void Statut::setMaxJauge(int i) {maxjauge=i;}
void Statut::setValJauge2(int i) {valjauge2=i;}
void Statut::setMaxJauge2(int i) {maxjauge2=i;}
SDL_Surface* Statut::getImageTroc() {return imageTroc;}
SDL_Surface* Statut::getImageGemmes() {return imageGemmes;}
