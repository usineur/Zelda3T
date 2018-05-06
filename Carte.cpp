/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "Carte.h"
#include "Keyboard.h"

Carte::Carte(Jeu* jeu) : gpJeu(jeu), levely(0) {
    image = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
}

Carte::~Carte() {
    SDL_FreeSurface(image);
}

void Carte::init() {
    SDL_Rect src;
    SDL_Rect dst;
    Joueur* gpJoueur = gpJeu->getJoueur();
    int zone = gpJeu->getZone();
    
    if (gpJeu->isDehors() || 
    (zone==46 && gpJeu->getMonde()->regionValue(0)==340*16 
    && gpJeu->getMonde()->regionValue(1)==0) || 
    (zone==53 && gpJeu->getMonde()->regionValue(0)==180*16 
    && gpJeu->getMonde()->regionValue(1)==75*16)) {
        SDL_Surface* tmp = NULL;
        switch (gpJeu->getEpoque()) {
            case T_PASSE :
                if (!gpJoueur->getCoffre(15, 2)) 
                    tmp = gpJeu->loadImg("data/images/carte/monde1-1.png");
                else tmp = gpJeu->loadImg("data/images/carte/monde1-2.png");
                break;
            case T_PRESENT :
                if (gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_UTILISE
                && gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_FERME) {
                    if (gpJoueur->getAvancement()<PONT_CONSTRUIT) 
                        tmp = gpJeu->loadImg("data/images/carte/monde4-1.png");
                    else tmp = gpJeu->loadImg("data/images/carte/monde4-2.png");
                } else if (gpJoueur->getTroc(M_ROUAGE)!=0) 
                    tmp = gpJeu->loadImg("data/images/carte/monde2-1.png");
                else if (gpJoueur->getCoffre(15,27)==15)
                    tmp = gpJeu->loadImg("data/images/carte/monde2-3.png");
                else tmp = gpJeu->loadImg("data/images/carte/monde2-2.png");
                break;
            case T_FUTUR : 
                if (!gpJoueur->hasObjet(O_FFEU) || !gpJoueur->hasObjet(O_FGLACE)
                || !gpJoueur->hasObjet(O_FLUM) || !gpJoueur->hasBouteille(3))
                    tmp = gpJeu->loadImg("data/images/carte/monde3-1.png"); 
                else tmp = gpJeu->loadImg("data/images/carte/monde3-2.png"); 
                break;
            default :
                break;
        }
        src.w = 320; src.h = 240; src.x = 0; src.y = 0; dst.y = 0; dst.x = 0;
        SDL_BlitSurface(tmp, &src, image, &dst);
        SDL_FreeSurface(tmp);
        
        //si en téléportation
        if (gpJeu->getKeyboard()->getMode() == 22) {
            gpJeu->getKeyboard()->setTelep(0); return;}
        
        tmp = gpJeu->loadImg("data/images/carte/link.png");
        SDL_SetColorKey(tmp,SDL_SRCCOLORKEY,SDL_MapRGB(tmp->format,0,0,255));
        src.w = 14; src.h = 12; src.x = 0; src.y = 0; 
        if (gpJoueur->isLapin()) {src.w = 16; src.h = 15; src.x = 14;}
        
        //dst.x = gpJoueur->getX()/18; dst.y = gpJoueur->getY()/18;
        //dst.y+=30;
                    
        switch (zone) {
            case 1 : case 16 : case 31 :
                dst.x = ((gpJoueur->getX()/16)*56)/(20*4); 
                dst.y = ((gpJoueur->getY()/16)*46)/(15*4);
                dst.x+=35; dst.y+=120; break;
            case 2 : case 17 : case 32 :
                dst.x = ((gpJoueur->getX()/16)*44)/(20*3); 
                dst.y = ((gpJoueur->getY()/16)*48)/(15*4);
                dst.x+=88; dst.y+=120; break;
            case 3 : case 18 : case 33 :
                dst.x = ((gpJoueur->getX()/16)*55)/(20*4); 
                dst.y = ((gpJoueur->getY()/16)*73)/(15*6);
                dst.x+=133; dst.y+=96; break;
            case 4 : case 19 : case 34 :
                dst.x = ((gpJoueur->getX()/16)*54)/(20*4); 
                dst.y = ((gpJoueur->getY()/16)*49)/(15*4);
                dst.x+=134; dst.y+=48; break;
            case 5 : case 20 : case 35 :
                dst.x = ((gpJoueur->getX()/16)*37)/(20*3); 
                dst.y = ((gpJoueur->getY()/16)*72)/(15*6);
                dst.x+=189; dst.y+=48; break;
            case 6 : case 21 : case 36 :
                dst.x = ((gpJoueur->getX()/16)*58)/(20*4); 
                dst.y = ((gpJoueur->getY()/16)*73)/(15*6);
                dst.x+=226; dst.y+=48; break;
            case 7 : case 22 : case 37 :
                dst.x = ((gpJoueur->getX()/16)*93)/(20*7); 
                dst.y = ((gpJoueur->getY()/16)*36)/(15*3);
                dst.x+=186; dst.y+=12; break;
            case 8 : case 23 : case 38 :
                dst.x = ((gpJoueur->getX()/16)*50)/(20*4); 
                dst.y = ((gpJoueur->getY()/16)*33)/(15*3);
                dst.x+=136; dst.y+=11; break;
            case 9 : case 24 : case 39 :
                dst.x = ((gpJoueur->getX()/16)*99)/(20*7); 
                dst.y = ((gpJoueur->getY()/16)*47)/(15*4);
                dst.x+=187; dst.y+=121; break;
            case 10: case 25 : case 40 :
                dst.x = ((gpJoueur->getX()/16)*60)/(20*4); 
                dst.y = ((gpJoueur->getY()/16)*60)/(15*5);
                dst.x+=232; dst.y+=168; break;
            case 11 : case 26 : case 41 :
                dst.x = ((gpJoueur->getX()/16)*92)/(20*7); 
                dst.y = ((gpJoueur->getY()/16)*60)/(15*5);
                dst.x+=132; dst.y+=168; break;
            case 12 : case 27 : case 42 :
                dst.x = ((gpJoueur->getX()/16)*101)/(20*7); 
                dst.y = ((gpJoueur->getY()/16)*60)/(15*5);
                dst.x+=30; dst.y+=168; break;
            case 13 : case 28 : case 43 :
                dst.x = ((gpJoueur->getX()/16)*51)/(20*4); 
                dst.y = ((gpJoueur->getY()/16)*58)/(15*5);
                dst.x+=40; dst.y+=61; break;
            case 14 : case 29 : case 44 :
                dst.x = ((gpJoueur->getX()/16)*40)/(20*3); 
                dst.y = ((gpJoueur->getY()/16)*59)/(15*5);
                dst.x+=93; dst.y+=61; break;
            case 15 : case 30 : case 45 :
                dst.x = ((gpJoueur->getX()/16)*90)/(20*7); 
                dst.y = ((gpJoueur->getY()/16)*49)/(15*4);
                dst.x+=45; dst.y+=12; break;
            case 46 : case 53 : dst.x=238; dst.y=8; break;
            /*case 28 : dst.x=133; dst.y=14; break;*/
        }
                    
        dst.x-=7; dst.y-=6;
        if (gpJoueur->isLapin()) {dst.x-=1; dst.y-=3;}
        
        SDL_BlitSurface(tmp, &src, image, &dst);
        SDL_FreeSurface(tmp);
    }
    else if (gpJeu->isDonjon()) {
        levely = gpJeu->getMonde()->etage();
        initDonjon();
    }
}

void Carte::initDonjon() {
    SDL_Rect src;
    SDL_Rect dst;
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    SDL_Surface* tmp = gpJeu->loadImg("data/images/carte/donjon.png");
    src.w = 320; src.h = 240; src.x = 0; src.y = 0; dst.y = 0; dst.x = 0;
    SDL_BlitSurface(tmp, &src, image, &dst);
    SDL_FreeSurface(tmp);
        
    initName();
    initItems();
    if (gpJoueur->getCle(gpJeu->getZone()-46,0)) initEtage();
}

void Carte::initEtage() {
    SDL_Rect src;
    SDL_Rect dst;
    int zone = gpJeu->getZone();
    
    src.h = 16; src.w = 32;src.x = 0;src.y=32;dst.x = 40; dst.y = 96;
    switch (zone-46) {
        case 0 : case 4 : case 5 : case 6 : case 13 : src.y=0; dst.y-=32; src.h=64; break;
        case 1 : case 2 : case 3 : case 8 : case 9 : src.y=32; src.h=48; break;
        case 7 : src.h=80; src.y=0; dst.y-=32; break;
        case 10 : src.h=32; src.y=16; dst.y-=16; break;
        case 11 : src.y=16; dst.y-=16; src.h=64; break;
        case 12 : src.y=32; src.h=16; break;
        case 14 : src.y=32; src.h=32; break;
    }
    
    SDL_Surface* tmp = gpJeu->loadImg("data/images/carte/level.png");
    SDL_BlitSurface(tmp, &src, image, &dst);
    SDL_FreeSurface(tmp);
    
    switch (zone-46) {
        case 0 : case 4 : case 5 : case 6 : case 13 :
            if (levely<-1) levely=2; if (levely>2) levely=-1; break;
        case 1 : case 2 : case 3 : case 8 : case 9 : 
            if (levely<-2) levely=0; if (levely>0) levely=-2; break;
        case 7 : if (levely<-2) levely=2; if (levely>2) levely=-2; break;
        case 10 : if (levely<0) levely=1; if (levely>1) levely=0; break;
        case 11 : if (levely<-2) levely=1; if (levely>1) levely=-2; break;
        case 12 : levely=0; break;
        case 14 : if (levely<-1) levely=0; if (levely>0) levely=-1; break;
    }
    src.h = 16; src.w = 32;src.x = 0;src.y=32-levely*16;dst.x = 40; dst.y = 96-levely*16;
    
    tmp = gpJeu->loadImg("data/images/carte/level2.png");
    SDL_BlitSurface(tmp, &src, image, &dst);
    SDL_FreeSurface(tmp);
    
    //étage de link
    tmp = gpJeu->loadImg("data/images/carte/link.png");
    SDL_SetColorKey(tmp,SDL_SRCCOLORKEY,SDL_MapRGB(tmp->format,0,0,255));
    src.h = 12; src.w = 14;src.x = 0;src.y=0;
    dst.x = 25; dst.y = 98-gpJeu->getMonde()->etage()*16;
    SDL_BlitSurface(tmp, &src, image, &dst);
    SDL_FreeSurface(tmp);
    
    initCarte();
}

void Carte::initCarte() {
    SDL_Rect src;
    SDL_Rect dst;
    int zone = gpJeu->getZone();
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    int dx=0;
    int dy=0;
    
    ostringstream os;
    ostringstream os2;
    
    switch (zone-46) {
        case 0 : case 13 : dx=3; dy=3; break;
        case 1 : dx=2; dy=2; break;
        case 2 : case 9 : case 14 : dx=1; dy=2; break;
        case 3 : case 8 : dx=2; dy=2; if (levely==0) {dx=7; dy=4;} break;
        case 4 : case 5 : case 6 : dx=2+levely; dy=2+levely; break;
        case 7 : dx=3; dy=3; break;
        case 10 : dx=1+2*levely; dy=1; break;
        case 11 : dx=1; dy=1; if (levely==-1 || levely==1) dx=3; if (levely<0) dy=4; break;
        case 12 : dx=1; dy=1; break;
    }
    
    
    os << (zone-46+1);
    os2 << levely;
    
    SDL_Surface* tmp = gpJeu->loadImg(("data/images/carte/d"+os.str()+"e"+os2.str()+".png").c_str());
    src.x=0; src.y=0; src.w=tmp->w; src.h=tmp->h; dst.y = 48+dy*16; dst.x = 128+dx*16;
    SDL_BlitSurface(tmp, &src, image, &dst);
    SDL_FreeSurface(tmp);
    
    
    tmp = gpJeu->loadImg(("data/images/carte/nd"+os.str()+"e"+os2.str()+".png").c_str());
    
    int di=0;
    int dj=0;
    
    switch (zone-46) {
        case 0 : case 13 : di=4+levely*4; break;
        case 1 : di=(-levely)*6; break;
        case 2 : di=(-levely)*7; break;
        case 3 : case 8 : di=(-levely)*6-5; if (levely==0) {di=0; dj=2;} break;
        case 4 : case 5 : case 6 : di=(2-levely)*(2-levely); dj=1+levely; break;
        case 7 : di=4*levely;
            if (levely<0) {di+=8;dj=4;} break;
        case 9 : dj=10-(-levely)*5; break;
        case 10 : di=7*levely; break;
        case 11 :
            di=(levely==1)?7:0;
            if (levely==-1) {di=2;dj=9;}
            if (levely==-2) dj=15;
            break;
        case 12 : di=0; dj=0; break;
        case 14 : dj=(1+levely)*5; break;
    }
    
    for (int i = 0; i < tmp->w/16; i++) 
        for (int j = 0; j < tmp->h/16; j++) 
            if (!gpJoueur->getExplore(zone-46,i+di,j+dj)) {
                src.x=i*16; src.y=j*16; src.w=16; src.h=16; 
                dst.x = 128+(dx+i)*16; dst.y = 48+(dy+j)*16;
                SDL_BlitSurface(tmp, &src, image, &dst);
            }
        
    SDL_FreeSurface(tmp);
    
    if (gpJoueur->getCle(zone-46,1)) initBoussole();
    
    //Etage de link
    if (gpJeu->getMonde()->etage() == levely/* && ((zone-46)!=11 || levely==0)*/) {
        tmp = gpJeu->loadImg("data/images/carte/link.png");
        SDL_SetColorKey(tmp,SDL_SRCCOLORKEY,SDL_MapRGB(tmp->format,0,0,255));
        src.h = 12; src.w = 14;src.x = 0;src.y=0;
        dst.x = 128+(dx-di)*16+(gpJoueur->getX()/20)-6; 
        dst.y = 48+(dy-dj)*16+(gpJoueur->getY()/15)-7;
        SDL_BlitSurface(tmp, &src, image, &dst);
        SDL_FreeSurface(tmp);
    }
}

void Carte::initBoussole() {
    SDL_Rect src;
    SDL_Rect dst;
    int zone = gpJeu->getZone();
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    SDL_Surface* tmp = gpJeu->loadImg("data/images/carte/boussole.png");
    SDL_SetColorKey(tmp,SDL_SRCCOLORKEY,SDL_MapRGB(tmp->format,0,0,255));
    
    switch (zone-46) {
        case 0 :
            if (levely==-1) {
                if (!gpJoueur->getCoffre(0,22)) {
                    src.h = 6; src.w = 6;src.x = 10;src.y=0;
                    dst.x = 127+16*3+6; dst.y = 48+16*5+5;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->hasObjet(O_ARC)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*5+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(0,17)) {
                    dst.x = 127+16*6+8; dst.y = 48+16*5+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==1) {
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(!gpJoueur->getCoffre(0,18)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(0,21)) {
                    dst.x = 127+16*5+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==2) {
                if (!gpJoueur->getCoeur(0)) {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*3+5; dst.y = 48+16*4+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->hasMedaillon(0)) {
                    dst.x = 127+16*3+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCle(0,2)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(0,19)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*4+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(0,20)) {
                    dst.x = 127+16*6+8; dst.y = 48+16*4+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (!gpJoueur->getCoeur(0)) {
                src.h = 8; src.w = 8;src.x = 2;src.y=0;
                dst.x = 24+48+4; dst.y = 96+4-16*2;
                SDL_BlitSurface(tmp, &src, image, &dst);
            }
            break;
        case 1 :
            if (levely==-1) {
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(!gpJoueur->getCoffre(1,10)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==-2) {
                if (!gpJoueur->getCoffre(1,15)) {
                    src.h = 6; src.w = 6;src.x = 10;src.y=0;
                    dst.x = 127+16*6+6; dst.y = 48+16*5+5;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if (!gpJoueur->getCoeur(1)) {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*7+5; dst.y = 48+16*4+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->hasMedaillon(1)) {
                    dst.x = 127+16*7+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if (!gpJoueur->hasObjet(O_GANTS)) {
                    dst.x = 127+16*6+4; dst.y = 48+16*6+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCle(1,2)) {
                    dst.x = 127+16*4+8+7; dst.y = 48+16*4+7+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(1,12)) {
                    dst.x = 127+16*2+8; dst.y = 48+16*7+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(1,13)) {
                    dst.x = 127+16*6+8+4; dst.y = 48+16*4+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(1,14)) {
                    dst.x = 127+16*7+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(1,16)) {
                    dst.x = 127+16*4+8-2; dst.y = 48+16*4+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (!gpJoueur->getCoeur(1)) {
                src.h = 8; src.w = 8;src.x = 2;src.y=0;
                dst.x = 24+48+4; dst.y = 96+4+16*2;
                SDL_BlitSurface(tmp, &src, image, &dst);
            }
            break;
        case 2 :
            if (levely==0) {
                if (!gpJoueur->getCoeur(2)) {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*1+5; dst.y = 48+16*4+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if (!gpJoueur->getCoffre(2,61)) {
                    src.h = 6; src.w = 6;src.x = 10;src.y=0;
                    dst.x = 127+16*7+6; dst.y = 48+16*4+5;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->hasObjet(O_LANTERNE)) {
                    dst.x = 127+16*7+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(2,9)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(2,11)) {
                    dst.x = 127+16*5+8; dst.y = 48+16*4+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(2,13)) {
                    dst.x = 127+16*4+8+4; dst.y = 48+16*4+7+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==-1) {
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(!gpJoueur->getCle(2,2)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(2,8)) {
                    dst.x = 127+16*4+8+4; dst.y = 48+16*6+7-4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(2,10)) {
                    dst.x = 127+16*5+8+4; dst.y = 48+16*5+7-4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==-2) {
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->hasMedaillon(2)) {
                    dst.x = 127+16*1+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (!gpJoueur->getCoeur(2)) {
                src.h = 8; src.w = 8;src.x = 2;src.y=0;
                dst.x = 24+48+4; dst.y = 96+4;
                SDL_BlitSurface(tmp, &src, image, &dst);
            }
            break;
        case 3 :
            if (levely==-1) {
                if (!gpJoueur->getCoffre(3,27)) {
                    src.h = 6; src.w = 6;src.x = 10;src.y=0;
                    dst.x = 127+16*5+6; dst.y = 48+16*3+5;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->hasObjet(O_PALMES)) {
                    dst.x = 127+16*5+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCle(3,2)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(3,2)) {
                    dst.x = 127+16*5+8-4; dst.y = 48+16*6+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(3,3)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==-2) {
                if (!gpJoueur->getCoeur(3)) {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*4+5+8; dst.y = 48+16*3+4+8;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->getCoffre(3,29)) {
                    dst.x = 127+16*4+8+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(3,4)) {
                    dst.x = 127+16*5+8; dst.y = 48+16*6+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (!gpJoueur->getCoeur(3)) {
                src.h = 8; src.w = 8;src.x = 2;src.y=0;
                dst.x = 24+48+4; dst.y = 96+4+16*2;
                SDL_BlitSurface(tmp, &src, image, &dst);
            }
            break;
        case 4 :
            if (levely==0) {
                if (!gpJoueur->getCoffre(4,38)) {
                    src.h = 6; src.w = 6;src.x = 10;src.y=0;
                    dst.x = 127+16*6+6; dst.y = 48+16*4+5;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (gpJoueur->getTunique()<2) {
                    dst.x = 127+16*6+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCle(4,2)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(4,7)) {
                    dst.x = 127+16*5+8; dst.y = 48+16*4+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==-1) {
                if (!gpJoueur->getCoeur(4)) {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*4+5; dst.y = 48+16*2+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->hasObjet(O_CLE_TEMPS)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*1+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(4,8)) {
                    dst.x = 127+16*6+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(4,9)) {
                    dst.x = 127+16*6+8+8; dst.y = 48+16*7+7+8;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (!gpJoueur->getCoeur(4)) {
                src.h = 8; src.w = 8;src.x = 2;src.y=0;
                dst.x = 24+48+4; dst.y = 96+4+16*1;
                SDL_BlitSurface(tmp, &src, image, &dst);
            }
            break;
        case 5 :
            if (levely==0) {
                if (!gpJoueur->getCoffre(5,24)) {
                    src.h = 6; src.w = 6;src.x = 10;src.y=0;
                    dst.x = 127+16*4+6; dst.y = 48+16*3+5;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(!gpJoueur->getCle(5,2)) {
                    dst.x = 127+16*2+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(5,4)) {
                    dst.x = 127+16*3+8; dst.y = 48+16*5+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==-1) {
                if (!gpJoueur->getCoeur(5)) {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*4+5; dst.y = 48+16*2+4+8;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->hasObjet(O_MARTEAU)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*1+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(5,5)) {
                    dst.x = 127+16*3+8; dst.y = 48+16*1+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (!gpJoueur->getCoeur(5)) {
                src.h = 8; src.w = 8;src.x = 2;src.y=0;
                dst.x = 24+48+4; dst.y = 96+4+16*1;
                SDL_BlitSurface(tmp, &src, image, &dst);
            }
            break;
        case 6 :
            if (levely==0) {
                if (!gpJoueur->getCoffre(6,22)) {
                    src.h = 6; src.w = 6;src.x = 10;src.y=0;
                    dst.x = 127+16*4+6; dst.y = 48+16*4+5;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(gpJoueur->hasObjet(O_GANTS) < 2) {
                    dst.x = 127+16*4+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(6,5)) {
                    dst.x = 127+16*2+8; dst.y = 48+16*5+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(6,6)) {
                    dst.x = 127+16*6+8; dst.y = 48+16*3+7+2;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(6,7)) {
                    dst.x = 127+16*5+8-2; dst.y = 48+16*5+7-2;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==-1) {
                if (!gpJoueur->getCoeur(6)) {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*4+5; dst.y = 48+16*3+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->hasObjet(O_TROC3)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCle(6,2)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*1+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(6,8)) {
                    dst.x = 127+16*2+8; dst.y = 48+16*1+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (!gpJoueur->getCoeur(6)) {
                src.h = 8; src.w = 8;src.x = 2;src.y=0;
                dst.x = 24+48+4; dst.y = 96+4+16*1;
                SDL_BlitSurface(tmp, &src, image, &dst);
            }
            break;
        case 7 :
            if (levely==2) {
                if (!gpJoueur->getCoeur(7)) {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*4+5; dst.y = 48+16*3+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->hasObjet(O_TROC4)) {
                    dst.x = 127+16*5+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCle(7,2)) {
                    dst.x = 127+16*3+8; dst.y = 48+16*4+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==1) {
                if (!gpJoueur->getCoffre(7,23)) {
                    src.h = 6; src.w = 6;src.x = 10;src.y=0;
                    dst.x = 127+16*3+6; dst.y = 48+16*4+5;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(gpJoueur->hasObjet(O_ARC) < 5) {
                    dst.x = 127+16*3+8-4; dst.y = 48+16*3+7-4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(7,7)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*4+7+8;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(7,8)) {
                    dst.x = 127+16*6+8; dst.y = 48+16*5+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==-2) {
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(!gpJoueur->getCoffre(7,6)) {
                    dst.x = 127+16*6+8; dst.y = 48+16*5+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (!gpJoueur->getCoeur(7)) {
                src.h = 8; src.w = 8;src.x = 2;src.y=0;
                dst.x = 24+48+4; dst.y = 96+4-16*2;
                SDL_BlitSurface(tmp, &src, image, &dst);
            }
            break;
        case 8 :
            if (levely==-1) {
                if (!gpJoueur->getCoffre(8,23)) {
                    src.h = 6; src.w = 6;src.x = 10;src.y=0;
                    dst.x = 127+16*4+6; dst.y = 48+16*2+5;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->hasObjet(O_BGLACE)) {
                    dst.x = 127+16*5+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCle(8,2)) {
                    dst.x = 127+16*4+8+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(8,10)) {
                    dst.x = 127+16*2+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(8,11)) {
                    dst.x = 127+16*3+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(8,12)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*7+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(8,13)) {
                    dst.x = 127+16*6+8-4; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(8,14)) {
                    dst.x = 127+16*6+8-2; dst.y = 48+16*7+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(8,15)) {
                    dst.x = 127+16*7+8; dst.y = 48+16*5+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==-2) {
                if (!gpJoueur->getCoeur(8)) {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*4+5+8; dst.y = 48+16*3+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->hasObjet(O_TROC2)) {
                    dst.x = 127+16*4+8+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(8,16)) {
                    dst.x = 127+16*2+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(8,17)) {
                    dst.x = 127+16*6+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(8,18)) {
                    dst.x = 127+16*7+8; dst.y = 48+16*3+7-4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (!gpJoueur->getCoeur(8)) {
                src.h = 8; src.w = 8;src.x = 2;src.y=0;
                dst.x = 24+48+4; dst.y = 96+4+16*2;
                SDL_BlitSurface(tmp, &src, image, &dst);
            }
            break;
        case 9 :
            if (levely==0) {
                if (!gpJoueur->getCoffre(9,16)) {
                    src.h = 6; src.w = 6;src.x = 10;src.y=0;
                    dst.x = 127+16*4+6; dst.y = 48+16*2+5;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->hasObjet(O_BFEU)) {
                    dst.x = 127+16*5+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if (!gpJoueur->hasObjet(O_TROC1)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*4+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==-1) {
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(!gpJoueur->getCle(9,2)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==-2) {
                if (!gpJoueur->getCoeur(9)) {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*4+5; dst.y = 48+16*4+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(!gpJoueur->getCoffre(9,1)) {
                    dst.x = 127+16*3+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(9,3)) {
                    dst.x = 127+16*5+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (!gpJoueur->getCoeur(9)) {
                src.h = 8; src.w = 8;src.x = 2;src.y=0;
                dst.x = 24+48+4; dst.y = 96+4+16*2;
                SDL_BlitSurface(tmp, &src, image, &dst);
            }
            break;
        case 10 :
            if (levely==0) {
                if (!gpJoueur->getCoffre(10,11)) {
                    src.h = 6; src.w = 6;src.x = 10;src.y=0;
                    dst.x = 127+16*6+6; dst.y = 48+16*7+5;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (gpJoueur->getBouclier() < 3) {
                    dst.x = 127+16*5+8; dst.y = 48+16*7+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCle(10,2)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*1+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(10,4)) {
                    dst.x = 127+16*2+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(10,5)) {
                    dst.x = 127+16*6+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==1) {
                if (!gpJoueur->getCoeur(10)) {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*4+5; dst.y = 48+16*2+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (gpJoueur->getEpee() < 5) {
                    dst.x = 127+16*4+8; dst.y = 48+16*1+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(10,6)) {
                    dst.x = 127+16*5+8; dst.y = 48+16*1+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (!gpJoueur->getCoeur(10)) {
                src.h = 8; src.w = 8;src.x = 2;src.y=0;
                dst.x = 24+48+4; dst.y = 96+4-16;
                SDL_BlitSurface(tmp, &src, image, &dst);
            }
            break;
        case 11 :
            if (levely==0) {
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(!gpJoueur->getCoffre(11,2)) {
                    dst.x = 127+16*3+8; dst.y = 48+16*7+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(11,3)) {
                    dst.x = 127+16*5+8; dst.y = 48+16*7+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==1) {
                if (!gpJoueur->getEnnemi(50)) {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*4+5; dst.y = 48+16*2+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                } else {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*4+5; dst.y = 48+16*1+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(!gpJoueur->getCoffre(11,1)) {
                    dst.x = 127+16*5+8; dst.y = 48+16*1+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==-1) {
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (gpJoueur->getTunique() < 3) {
                    dst.x = 127+16*5+8; dst.y = 48+16*7+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==-2) {
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(!gpJoueur->getCle(11,2)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*4+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            src.h = 8; src.w = 8;src.x = 2;src.y=0;
            dst.x = 24+48+4; dst.y = 96+4-16;
            SDL_BlitSurface(tmp, &src, image, &dst);
            break;
        case 12 :
            if (levely==0) {
                if (!gpJoueur->getCoeur(11)) {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*4+5; dst.y = 48+16*3+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(gpJoueur->getBouclier() < 4) {
                    dst.x = 127+16*4+8-4; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCle(12,2)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*1+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(12,1)) {
                    dst.x = 127+16*2+8; dst.y = 48+16*5+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(12,2)) {
                    dst.x = 127+16*3+8; dst.y = 48+16*1+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(12,3)) {
                    dst.x = 127+16*5+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(12,4)) {
                    dst.x = 127+16*6+8; dst.y = 48+16*5+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(12,5)) {
                    dst.x = 127+16*7+8; dst.y = 48+16*7+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (!gpJoueur->getCoeur(11)) {
                src.h = 8; src.w = 8;src.x = 2;src.y=0;
                dst.x = 24+48+4; dst.y = 96+4;
                SDL_BlitSurface(tmp, &src, image, &dst);
            }
            break;
        case 13 :
            if (levely==-1) {
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(!gpJoueur->getCoffre(13,1)) {
                    dst.x = 127+16*6+8; dst.y = 48+16*3+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==0) {
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(!gpJoueur->getCoffre(13,2)) {
                    dst.x = 127+16*6+8; dst.y = 48+16*5+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==2) {
                if (!gpJoueur->getCoeur(12)) {
                    src.h = 8; src.w = 8;src.x = 2;src.y=0;
                    dst.x = 127+16*4+5+8; dst.y = 48+16*5+4;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (gpJoueur->getTunique()<4) {
                    dst.x = 127+16*4+8+8-4; dst.y = 48+16*4+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCle(13,2)) {
                    dst.x = 127+16*3+8; dst.y = 48+16*4+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (!gpJoueur->getCoeur(12)) {
                src.h = 8; src.w = 8;src.x = 2;src.y=0;
                dst.x = 24+48+4; dst.y = 96+4-16*2;
                SDL_BlitSurface(tmp, &src, image, &dst);
            }
            break;
        case 14 :
            if (levely==-1) {
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if (!gpJoueur->hasObjet(O_MASQUE)) {
                    dst.x = 127+16*4+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            if (levely==0) {
                src.h = 8; src.w = 8;src.x = 2;src.y=0;
                dst.x = 127+16*4+5; dst.y = 48+16*2+4;
                SDL_BlitSurface(tmp, &src, image, &dst);
                src.h = 2; src.w = 2;src.x = 0;src.y=0;
                if(!gpJoueur->getCle(14,2)) {
                    dst.x = 127+16*2+8; dst.y = 48+16*2+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
                if(!gpJoueur->getCoffre(14,1)) {
                    dst.x = 127+16*5+8; dst.y = 48+16*6+7;
                    SDL_BlitSurface(tmp, &src, image, &dst);
                }
            }
            src.h = 8; src.w = 8;src.x = 2;src.y=0;
            dst.x = 24+48+4; dst.y = 96+4;
            SDL_BlitSurface(tmp, &src, image, &dst);
            break;
        
        
        
        
    }
    SDL_FreeSurface(tmp);
}

void Carte::initItems() {
    SDL_Rect src;
    SDL_Rect dst;
    Joueur* gpJoueur = gpJeu->getJoueur();
    if (gpJoueur->getCle(gpJeu->getZone()-46,0)) { //carte
        src.h = 16; src.w = 16;src.x = 48;src.y=0;dst.x = 28; dst.y = 192;
        SDL_BlitSurface(gpJeu->getImageObjets(), &src, image, &dst);
    }
    if (gpJoueur->getCle(gpJeu->getZone()-46,1)) { //boussole
        src.h = 16; src.w = 16;src.x = 96;src.y=0;dst.x = 48; dst.y = 192;
        SDL_BlitSurface(gpJeu->getImageObjets(), &src, image, &dst);
    }
    if (gpJoueur->getCle(gpJeu->getZone()-46,2)) { //cle boss
        src.h = 16; src.w = 16;src.x = 16;src.y=0;dst.x = 68; dst.y = 192;
        SDL_BlitSurface(gpJeu->getImageObjets(), &src, image, &dst);
    }
}

void Carte::initName() {
    int zone = gpJeu->getZone();
    //message
    switch (zone-46) {
        case 0 : gpJeu->afficheTexteAvecId(image, 0,128,25); break;
        case 1 : gpJeu->afficheTexteAvecId(image, 1,128,25); break;
        case 2 : gpJeu->afficheTexteAvecId(image, 2,128,25); break;
        case 3 : gpJeu->afficheTexteAvecId(image, 3,128,25); break;
        case 4 : gpJeu->afficheTexteAvecId(image, 4,128,25); break;
        case 5 : gpJeu->afficheTexteAvecId(image, 5,128,25); break;
        case 6 : gpJeu->afficheTexteAvecId(image, 6,128,25); break;
        case 7 : gpJeu->afficheTexteAvecId(image, 7,128,25); break;
        case 8 : gpJeu->afficheTexteAvecId(image, 8,128,25); break;
        case 9 : gpJeu->afficheTexteAvecId(image, 9,128,25); break;
        case 10 : gpJeu->afficheTexteAvecId(image, 10,128,25); break;
        case 11 : gpJeu->afficheTexteAvecId(image, 11,128,25); break;
        case 12 : gpJeu->afficheTexteAvecId(image, 12,128,25); break;
        case 13 : gpJeu->afficheTexteAvecId(image, 13,128,25); break;
        case 14 : gpJeu->afficheTexteAvecId(image, 14,128,25); break;
    }
}

void Carte::moveLevel(Direction dir) {
    if (!gpJeu->isDonjon()) return;
    if (!gpJeu->getJoueur()->getCle(gpJeu->getZone()-46,0)) return;
    if (gpJeu->getZone()==27) return;
    int old = levely;
    if (dir == N) levely++;
    if (dir == S) levely--;
    initDonjon();
    if (old != levely) gpJeu->getAudio()->playSound(3);
}

void Carte::draw(SDL_Surface* gpScreen) {
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w = 320; src.h = 240; src.x = 0; src.y = 0; dst.y = 0; dst.x = 0;
    
    SDL_BlitSurface(image, &src, gpScreen, &dst);
    
    if (gpJeu->getKeyboard()->getMode() == 22) { //si en téléportation
        
        
        
        SDL_Surface* tmp = gpJeu->loadImg("data/images/carte/link.png");
        SDL_SetColorKey(tmp,SDL_SRCCOLORKEY,SDL_MapRGB(tmp->format,0,0,255));
        src.w = 14; src.h = 12; src.x = 0; src.y = 0; 
        
        int tel = gpJeu->getKeyboard()->getTelep();
        
        if (tel != 0) gpJeu->getTexte()->affiche(gpScreen, "1", 156, 15);
        else {dst.x=156-4; dst.y=15+1;}
        if (tel != 1) gpJeu->getTexte()->affiche(gpScreen, "2", 234, 16);
        else {dst.x=234-4; dst.y=16+1;}
        if (tel != 2) gpJeu->getTexte()->affiche(gpScreen, "3", 264, 54);
        else {dst.x=264-4; dst.y=54+1;}
        if (tel != 3) gpJeu->getTexte()->affiche(gpScreen, "4", 65, 86);
        else {dst.x=65-4; dst.y=86+1;}
        if (tel != 4) gpJeu->getTexte()->affiche(gpScreen, "5", 59, 145);
        else {dst.x=59-4; dst.y=145+1;}
        if (tel != 5) gpJeu->getTexte()->affiche(gpScreen, "6", 156, 133);
        else {dst.x=156-4; dst.y=133+1;}
        if (tel != 6) gpJeu->getTexte()->affiche(gpScreen, "7", 59, 194);
        else {dst.x=59-4; dst.y=194+1;}
        if (tel != 7) gpJeu->getTexte()->affiche(gpScreen, "8", 180, 210);
        else {dst.x=180-4; dst.y=210+1;}
        if (tel != 8) gpJeu->getTexte()->affiche(gpScreen, "9", 264, 185);
        else {dst.x=264-4; dst.y=185+1;}
        
        SDL_BlitSurface(tmp, &src, gpScreen, &dst);
        SDL_FreeSurface(tmp);
    
    }
}
