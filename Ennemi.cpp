/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <cmath>

#include "Menu.h"
#include "Joueur.h"
#include "Monde.h"
#include "Texte.h"
#include "Projectile.h"
#include "Ennemi.h"
#include "Jeu.h"
#include "Keyboard.h"

Ennemi::Ennemi(Jeu* jeu, int type, int i, int j, bool p) : Personnage(), gpJeu(jeu), 
id(type), vanim(120), vinvin(3), vol(0), nage(0), spectre(0), porte(0), typeIA(IA_RIEN), 
vitesse(1), force(0), recul(16), glace(0), maxglace(60), typeEnn(E_SIMPLE), 
zonesAttaques(NULL), zonesVulnerables(NULL), chargeIm(false), arme(false),
special1(0), special2(0), persistent(p), type_att(ENNEMI), dist(16) {
    if (id) {
        Ennemi* gpEnnemi = gpJeu->existEnnemi(id);
        if (gpEnnemi != NULL) {
            image = gpEnnemi->image;
        }
        else {
            ostringstream im;
            im << id;
            image = gpJeu->loadImg(("data/images/ennemi/ennemi" + im.str() + ".png").c_str());
            if (id != 70) 
                SDL_SetColorKey(image,SDL_SRCCOLORKEY,SDL_MapRGB(image->format,0,0,255));
            chargeIm = true;
        }
        x=i; y=j; saveEmpl();
        special1=0; // A sortir pour l'ennemi 20
        init();
    }
}

Ennemi::~Ennemi() {
    delete zonesAttaques;
    delete zonesVulnerables;
    if (!chargeIm) image = NULL;
    if (suivant != NULL) {
        Ennemi* ennemi_ = (Ennemi*)suivant;
        suivant = NULL;
        delete ennemi_;
    }
}

void Ennemi::drawSpecial(SDL_Surface* gpScreen) {
    int phg[2];
    phg[0] = gpJeu->getPhg(0);
    phg[1] = gpJeu->getPhg(1);
    
    Monde* gpMonde = gpJeu->getMonde();
    
    if (id && vie>0 && x+w > gpMonde->regionValue(0) && x < gpMonde->regionValue(2)
    && y+h > gpMonde->regionValue(1) && y < gpMonde->regionValue(3)) {
        
        SDL_Rect src;
        SDL_Rect dst;
        
        if (id == 51) {
            if (anim > 10+10) {
                dst.x = x-phg[0]+2;
                dst.y = y-phg[1]+18;
                src.y=22; src.x=2; src.h=6; src.w=20;
                SDL_BlitSurface(image, &src, gpScreen, &dst);
            }
        }
        
        if (id == 81) {
            dst.x = x-phg[0]+2;
            dst.y = y-phg[1]+22;
            src.y=30; src.x=2; src.h=6; src.w=12;
            SDL_BlitSurface(image, &src, gpScreen, &dst);
        }
        
        if (id == 85) {
            dst.x = x-phg[0]+2;
            dst.y = y-phg[1]+22;
            src.y=28; src.x=2; src.h=6; src.w=12;
            SDL_BlitSurface(image, &src, gpScreen, &dst);
        }
        
    }
    
    if (suivant != NULL) ((Ennemi*)suivant)->drawSpecial(gpScreen);
}

void Ennemi::reactiveDes() {
    if (id != 125) return;
    special2=0;
    typeIA = IA_RANDOM;
    for (int k = 0; k < 25; k++) effets[k]=2;
}

bool Ennemi::isActif() {
    Monde* gpMonde = gpJeu->getMonde();
    return (id && vie>0 && x+w > gpMonde->regionValue(0) && x < gpMonde->regionValue(2)
    && y+h > gpMonde->regionValue(1) && y < gpMonde->regionValue(3));
}

void Ennemi::draw(SDL_Surface* gpScreen) {
    int phg[2];
    phg[0] = gpJeu->getPhg(0);
    phg[1] = gpJeu->getPhg(1);
    
    Monde* gpMonde = gpJeu->getMonde();
    
    if ((isBoss() || isMiniBoss()) 
    && id != 100
    && x+w > gpMonde->regionValue(0) && x < gpMonde->regionValue(2)
    && y+h > gpMonde->regionValue(1) && y < gpMonde->regionValue(3)) {
        if (id!=74) {
            gpJeu->getStatut()->setValJauge(vie); gpJeu->getStatut()->setMaxJauge(viemax);}
        else if (y>-152) {
            gpJeu->getStatut()->setValJauge2(vie); gpJeu->getStatut()->setMaxJauge2(viemax);}
    }
    
    if (isActif()) {
        
        if (!gpJeu->getStop() 
        && (!invincible || (isBoss() || isMiniBoss() || isBig())) && !glace) IA();
        
        if (gpJeu->getTransition()) return;
        
        SDL_Rect src;
        SDL_Rect dst;
        
        int anim2 = anim;
        
        if (id == 15 || id == 130) {
            if (anim < 18) anim2 = anim2%2;
            else anim2 = 2;
        }
        
        if (id == 16 || id == 30 || id == 131) anim2 = anim/5;
        
        if (id == 27) {
            if (anim < 6) anim2 = anim2%2;
            else if (anim < 8) anim2 = 2;
            else anim2 = 3;
        }
        
        if (id == 31 && anim > 3) anim2=3;
        
        if (id == 40) anim2=anim%3;
        
        if (id == 45) anim2 = anim/2;
        
        if (id == 51) {
            if (anim > 30 && special1 == 0) anim2=1;
            else anim2=0;
        }
        
        if (id == 57) {
            if (anim < 36) anim2 = 0;
            else if (anim < 38) anim2 = 1;
            else anim2 = 2;
        }
        
        if (typeIA==IA_STATUE) anim2=0;
        
        switch (typeEnn) {
            case E_SIMPLE : src.x=direction*w; src.y=h*anim2; break;
            case E_PROFIL : src.x=(direction%2)*w; src.y=h*anim2; break;
            case E_MONO_DIR : src.x=w*anim2; src.y=0; break;
        }
        dst.x=x-phg[0]; dst.y=y-phg[1]; src.w=w; src.h=h;
        
        if ((id == 20 || id == 88) && special1) src.x+=16;
        
        if(id == 45) {
            if (special1 < 3) {
                SDL_BlitSurface(image, &src, gpScreen, &dst);
                src.y=76; src.x=48*special1; src.w=48; src.h=38;
                dst.x = x+9-phg[0]; dst.y = y+29-phg[1];
            }
            if ((special2 > 10 && special1 > 2) || special2 > 40) {
                SDL_BlitSurface(image, &src, gpScreen, &dst);
                src.y=76; src.x=144; src.w=16; src.h=10;
                dst.x = x+25-phg[0]; dst.y = y+64-phg[1];
            }
        }
        
        if (id == 50) {
            //if (glace) {src.y=h*2; effets[FLECHE]=0;}
            //else if (gpJeu->getJoueur()->hasObjet(O_ARC)==5 && vie>100) effets[FLECHE]=2;
            if (special1>1 && special1<7) {dst.y-=6; src.h+=6; src.x=52;src.y=113;}
            if (special1>=7) {dst.y-=6; src.h+=6; src.x=0;src.y=113;}
        }
        
        if (id == 51) dst.y-=special1;
        if ((id == 52 || id == 78) && special1 >= 3) src.y+=34;
        
        if (id == 58 && special1 > 0) {
            src.x=29; src.y=30; src.w=12; src.h=6; dst.x++; dst.y+=9;
            SDL_BlitSurface(image, &src, gpScreen, &dst);
            src.x=28; src.y=15*anim2; src.w=14; src.h=15; dst.x--; dst.y-=(9+special1);
        }
        
        if (id == 61) {src.y=h*anim2; src.x=0;}
        
        if((id == 62 || id == 135) && special2) {
            int a = dst.x; int b = dst.y;
            src.x=14;src.y=74;src.w=24;src.h=17;dst.y+=20;
            SDL_BlitSurface(image, &src, gpScreen, &dst);
            dst.x=a; dst.y=b+20;
            src.x=0;src.y=74;src.w=14;src.h=16;dst.x+=5;dst.y-=5;
            if (special2<5) dst.y-=15-(special2-1)*5;
            if (special2>46) dst.y-=(special2-46)*5;
        }
        
        if (id == 63 && special2) {
            src.x=0;
            if (special2==1) src.y=68;
            else {
                src.y=128+56*anim2;
            }
        }
        
        if (id == 66 && special1 > 5 && special1 < 134) {
            SDL_BlitSurface(image, &src, gpScreen, &dst);
            src.y=124; src.h = 16; dst.y = y-phg[1]+h-10;
        }
        if(id == 67 && anim>=20) {src.y=0; src.x=w*(anim-20);}
        if(id == 68 || id == 69) {
            src.y=0;
            switch (special2) {
                case 0 : src.x=0; break;
                case 1 : src.x=26; break;
                case 2 : src.x=67; break;
                case 3 : src.x=95; break;
            }
            if (special1>5 && special1<50) {
                SDL_BlitSurface(image, &src, gpScreen, &dst);
                src.x=32*anim; src.w = 32; src.y = 63; src.h = 16;
                dst.y = y-phg[1]+h-15+5; dst.x = x-phg[0]-4;
            }
        }
        
        if (id==70) {
            
            int i = 0;
            while (special1-i > 0) {
                int dif = special1-i;
                if (dif > 16) dif = 16;
                i+=dif;
                src.x=16-dif; src.y=0; src.w=dif; src.h=25; 
                dst.x=x-phg[0]+special1-i; dst.y=y-phg[1];
                SDL_BlitSurface(image, &src, gpScreen, &dst);
                for (int j = 0; j < h-50; j+=16) {
                    src.x=16-dif; src.y=25; src.w=dif; src.h=16; 
                    dst.x=x-phg[0]+special1-i; dst.y=y-phg[1]+25+j;
                    SDL_BlitSurface(image, &src, gpScreen, &dst);
                }
                src.x=16-dif; src.y=41; src.w=dif; src.h=25; 
                dst.x=x-phg[0]+special1-i; dst.y=y-phg[1]+h-25;
                SDL_BlitSurface(image, &src, gpScreen, &dst);
            }
            src.x=16; src.y=0; src.w=25; src.h=25; dst.x=x-phg[0]+special1; dst.y=y-phg[1];
            SDL_BlitSurface(image, &src, gpScreen, &dst);
            for (int j = 0; j < h-50; j+=16) {
                src.x=16; src.y=25; src.w=25; src.h=16; 
                dst.x=x-phg[0]+special1; dst.y=y-phg[1]+25+j;
                SDL_BlitSurface(image, &src, gpScreen, &dst);
            }
            src.x=16; src.y=41; src.w=25; src.h=25; dst.x=x-phg[0]+special1; dst.y=y-phg[1]+h-25;
            SDL_BlitSurface(image, &src, gpScreen, &dst);
            
            for (i = x-phg[0]+320-special1; i < x-phg[0]+320; i+=16) {
                src.x=0; src.y=0; src.w=16; src.h=25; dst.x=i; dst.y=y-phg[1];
                SDL_BlitSurface(image, &src, gpScreen, &dst);
                for (int j = 0; j < h-50; j+=16) {
                    src.x=0; src.y=25; src.w=16; src.h=16; dst.x=i; dst.y=y-phg[1]+25+j;
                    SDL_BlitSurface(image, &src, gpScreen, &dst);
                }
                src.x=0; src.y=41; src.w=16; src.h=25; dst.x=i; dst.y=y-phg[1]+h-25;
                SDL_BlitSurface(image, &src, gpScreen, &dst);
            }
            src.x=41; src.y=0; src.w=25; src.h=25; 
            dst.x=x-phg[0]+320-25-special1; dst.y=y-phg[1];
            SDL_BlitSurface(image, &src, gpScreen, &dst);
            for (int j = 0; j < h-50; j+=16) {
                src.x=41; src.y=25; src.w=25; src.h=16; 
                dst.x=x-phg[0]+320-25-special1; dst.y=y-phg[1]+25+j;
                SDL_BlitSurface(image, &src, gpScreen, &dst);
            }
            src.x=41; src.y=41; src.w=25; src.h=25; 
            dst.x=x-phg[0]+320-25-special1; dst.y=y-phg[1]+h-25;
            SDL_BlitSurface(image, &src, gpScreen, &dst);
            
            
            //pousse Link
            Joueur* gpJoueur = gpJeu->getJoueur();
            int oldx=gpJoueur->getX();
            if (gpJoueur->getVie()>0 && gpJoueur->getTypeAnim()!=CHUTE
            && gpJoueur->getY()+24>y && gpJoueur->getY()+8<y+h) {
                if (special1<135-8) {
                    while (gpJoueur->getX()+2<=x+25+special1)
                        gpJoueur->setX(gpJoueur->getX()+2);
                    while (gpJoueur->getX()+17>=x+320-25-special1)
                        gpJoueur->setX(gpJoueur->getX()-2);
                    if (gpJoueur->getX()!=oldx) gpJeu->testFin();
                } else {
                    gpJoueur->setVie(0); gpJoueur->nonvisible();
                    gpJeu->getAudio()->playSound(43);
                    gpJeu->ajouteProjectile(20, direction, gpJoueur->getX()-8, 
                        gpJoueur->getY()-4, 0);
                }
	    }
        }
        
        if (id==75) {
            Joueur* gpJoueur = gpJeu->getJoueur();
            if (!gpJoueur->getVie()) {typeIA=IA_RIEN; special1=0;}
            //immobile - parle
            if (typeIA==IA_RIEN && special1==0 && special2==0) src.y=0;
            //marche
            if (typeIA!=IA_RIEN && special1==0 && special2==0) src.y+=24;
            //mort
            if (special2) {dst.y+=9; src.x=0; src.y=216; src.w=24; src.h=15;}
            //epee
            if (!special1 && !special2 && typeIA!=IA_RIEN)
            switch (direction) {
                case S : 
                    if (gpJoueur->getX()>x-4 && gpJoueur->getX()<x+32 
                    && gpJoueur->getY()>y && gpJoueur->getY()+10<y+43) special1=1; break;
                case N : 
                    if (gpJoueur->getX()>x-12 && gpJoueur->getX()<x+26 
                    && gpJoueur->getY()<y && gpJoueur->getY()+22>y-17) special1=1; break;
                case O : 
                    if (gpJoueur->getX()+14>x-18 && gpJoueur->getX()<x 
                    && gpJoueur->getY()+10<y+32 && gpJoueur->getY()+22>y-1) special1=1; break;
                case E : 
                    if (gpJoueur->getX()+5<x+36 && gpJoueur->getX()>x 
                    && gpJoueur->getY()+10<y+32 && gpJoueur->getY()+22>y-1) special1=1; break;
            }
            
            int aa1=0; int bb1=0; int aa2=w; int bb2=h;
            if (special1>0) {
                switch (direction) {
                    case S : 
                        dst.x-=6; src.x=76;src.y=43*((special1-2)/2); src.w=37; src.h=43;
                        switch (special1) {
                            case 1 : aa1=-6;bb1=15;aa2=5;bb2=23;break;
                            case 2 : aa1=-3;bb1=20;aa2=10;bb2=35;break;
                            case 3 : aa1=3;bb1=22;aa2=13;bb2=37;break;
                            case 4 : aa1=12;bb1=25;aa2=16;bb2=43;break;
                            case 5 : aa1=16;bb1=18;aa2=26;bb2=33;break;
                            case 6 : aa1=18;bb1=16;aa2=31;bb2=28;break;
                        }
                        break;
                case N : 
                    dst.x-=14; dst.y-=20; src.x=113;src.y=44*((special1-2)/2); src.w=40; src.h=44;
                    switch (special1) {
                        case 1 : aa1=15;bb1=7;aa2=26;bb2=13;break;
                        case 2 : aa1=5;bb1=-13;aa2=16;bb2=4;break;
                        case 3 : aa1=3;bb1=-20;aa2=7;bb2=2;break;
                        case 4 : aa1=-15;bb1=-6;aa2=2;bb2=10;break;
                        case 5 : aa1=-14;bb1=3;aa2=0;bb2=15;break;
                    }
                    break;
                case O : 
                    dst.x-=18; dst.y-=1; src.x=153;src.y=36*((special1-2)/2); src.w=39; src.h=36;
                    switch (special1) {
                        case 1 : aa1=-1;bb1=-1;aa2=5;bb2=12;break;
                        case 2 : aa1=-11;bb1=1;aa2=5;bb2=13;break;
                        case 3 : aa1=-19;bb1=12;aa2=1;bb2=18;break;
                        case 4 : aa1=-11;bb1=16;aa2=2;bb2=29;break;
                        case 5 : aa1=-3;bb1=21;aa2=10;bb2=34;break;
                    }
                    break;
                case E : 
                    dst.x-=1; dst.y-=1; src.x=192;src.y=36*((special1-2)/2); src.w=39; src.h=36;
                    switch (special1) {
                        case 1 : aa1=14;bb1=-1;aa2=19;bb2=12;break;
                        case 2 : aa1=14;bb1=1;aa2=29;bb2=13;break;
                        case 3 : aa1=18;bb1=12;aa2=37;bb2=18;break;
                        case 4 : aa1=16;bb1=16;aa2=29;bb2=29;break;
                        case 5 : aa1=8;bb1=21;aa2=21;bb2=34;break;
                    }
                    break;
                }
                zonesAttaques->getZone()->x=aa1; zonesAttaques->getZone()->y=bb1;
                zonesAttaques->getZone()->w=aa2; zonesAttaques->getZone()->h=bb2;
                if (!gpJeu->getStop()) special1++;
                if(special1==4) gpJeu->getAudio()->playSound(22);
                if (special1>=12 && direction!=S) special1=0;
                if (special1>=14) special1=0;
            }
        }
        
        if (id==89) {
            Joueur* gpJoueur = gpJeu->getJoueur();
            switch (direction) {
                case S : src.x=0; break;
                case N : src.x=20; break;
                case O : src.x=40; src.w=18; break;
                case E : src.x=58; src.w=18; break;
            }
            if (!gpJoueur->getVie()) typeIA=IA_RIEN;
            //immobile - parle
            if (typeIA==IA_RIEN && special1==0 && special2==0) src.y=0;
            //marche
            if (typeIA!=IA_RIEN && special1==0 && special2==0) src.y+=h;
            //mort ou animation
            if (special2) {
                if (special2 == 1) {
                    dst.x-=2; dst.y+=12; src.x=0; src.y=78; src.w=23; src.h=14;
                }
                if (special2 == 2) {
                    src.x=0; src.y=0; src.w=w; src.h=h;
                    if (gpJoueur->getImmo()) {
                        special2=3; animmax=1; direction=N;
                    }
                }
                if (special2 == 3) {
                    src.x=20; src.y=h*(anim+1); src.w=w; src.h=h; y--;
                    if (y<15*16) {
                        x=169*16+6; y=4*16; special2=0; saveEmpl(); 
                        gpJoueur->setImmo(false); return;
                    }
                }
            }
            //epee
            if (gpJeu->getZone()!=57) {
            if (!special1 && !special2 && typeIA!=IA_RIEN)
            switch (direction) {
                case S : 
                    if (gpJoueur->getX()>x-4 && gpJoueur->getX()<x+32 
                    && gpJoueur->getY()>y && gpJoueur->getY()+10<y+41) special1=1; break;
                case N : 
                    if (gpJoueur->getX()>x-12 && gpJoueur->getX()<x+26 
                    && gpJoueur->getY()<y && gpJoueur->getY()+22>y-8) special1=1; break;
                case O : 
                    if (gpJoueur->getX()+14>x-21 && gpJoueur->getX()<x 
                    && gpJoueur->getY()+10<y+32 && gpJoueur->getY()+22>y-1) special1=1; break;
                case E : 
                    if (gpJoueur->getX()+5<x+39 && gpJoueur->getX()>x 
                    && gpJoueur->getY()+10<y+32 && gpJoueur->getY()+22>y-1) special1=1; break;
            }
            
            int aa1=0; int bb1=0; int aa2=w; int bb2=h;
            if (special1>0) {
                if ((special1+1)/2 <= 3) {
                switch (direction) {
                    case S : 
                        src.x=220;
                        switch ((special1+1)/2) {
                            case 1 : 
                                aa1=16;bb1=-6;aa2=8;bb2=14;
                                dst.x+=1; dst.y-=6; 
                                src.y=0;src.w=23;src.h=32;break;
                            case 2 : 
                                aa1=13;bb1=0;aa2=14;bb2=31;
                                dst.x+=1; dst.y+=1; 
                                src.y=32;src.w=26;src.h=30;break;
                            case 3 : 
                                aa1=12;bb1=22;aa2=12;bb2=19;
                                dst.x+=1; dst.y+=3; 
                                src.y=62;src.w=19;src.h=38;break;
                        }
                        break;
                    case N : 
                        src.x=246;
                        switch ((special1+1)/2) {
                            case 1 : 
                                aa1=-5;bb1=-7;aa2=8;bb2=14;
                                dst.x-=5; dst.y-=7; 
                                src.y=0;src.w=25;src.h=33;break;
                            case 2 : 
                                aa1=-8;bb1=-3;aa2=12;bb2=16;
                                dst.x-=8; dst.y-=3; 
                                src.y=33;src.w=28;src.h=29;break;
                            case 3 : 
                                aa1=0;bb1=-8;aa2=8;bb2=18;
                                dst.y-=8; 
                                src.y=62;src.w=19;src.h=34;break;
                        }
                        break;
                    case O : 
                        src.x=274;
                        switch ((special1+1)/2) {
                            case 1 : 
                                aa1=16;bb1=-1;aa2=8;bb2=14;
                                dst.y-=1; 
                                src.y=0;src.w=24;src.h=27;break;
                            case 2 : 
                                aa1=-15;bb1=0;aa2=16;bb2=16;
                                dst.x-=15;
                                src.y=27;src.w=28;src.h=26;break;
                            case 3 : 
                                aa1=-21;bb1=10;aa2=21;bb2=8;
                                dst.x-=21; dst.y+=1; 
                                src.y=53;src.w=34;src.h=25;break;
                        }
                        break;
                    case E : 
                        src.x=308;
                        switch ((special1+1)/2) {
                            case 1 : 
                                aa1=-6;bb1=-1;aa2=8;bb2=14;
                                dst.x-=6;dst.y-=1; 
                                src.y=0;src.w=24;src.h=27;break;
                            case 2 : 
                                aa1=17;bb1=0;aa2=16;bb2=16;
                                dst.x+=5;
                                src.y=27;src.w=28;src.h=26;break;
                            case 3 : 
                                aa1=18;bb1=10;aa2=21;bb2=8;
                                dst.x+=5; dst.y+=1; 
                                src.y=53;src.w=34;src.h=25;break;
                        }
                        break;
                }
                zonesAttaques->getZone()->x=aa1; zonesAttaques->getZone()->y=bb1;
                zonesAttaques->getZone()->w=aa2; zonesAttaques->getZone()->h=bb2;
                }
                if (!gpJeu->getStop()) special1++;
                if(special1==4) gpJeu->getAudio()->playSound(22);
                if (special1>=14) special1=0;
            }
            }
            //trident
            if (gpJeu->getZone()==57) {
            if (!special1 && !special2 && typeIA!=IA_RIEN)
            switch (direction) {
                case S : 
                    if (gpJoueur->getX()>x-6 && gpJoueur->getX()<x+22 
                    && gpJoueur->getY()>y && gpJoueur->getY()+10<y+45) special1=1; break;
                case N : 
                    if (gpJoueur->getX()>x-5 && gpJoueur->getX()<x+10 
                    && gpJoueur->getY()<y && gpJoueur->getY()+22>y-17) special1=1; break;
                case O : 
                    if (gpJoueur->getX()+14>x-28 && gpJoueur->getX()<x 
                    && gpJoueur->getY()+10<y+32 && gpJoueur->getY()+22>y-1) special1=1; break;
                case E : 
                    if (gpJoueur->getX()+5<x+46 && gpJoueur->getX()>x 
                    && gpJoueur->getY()+10<y+32 && gpJoueur->getY()+22>y-1) special1=1; break;
            }
            
            int aa1=0; int bb1=0; int aa2=w; int bb2=h;
            if (special1>0) {
                if ((special1+1)/2 <= 4) {
                switch (direction) {
                    case S : 
                        src.x=76;
                        switch ((special1+1)/2) {
                            case 1 :
                                aa1=16;bb1=-8;aa2=15;bb2=15;
                                dst.x+=1; dst.y-=8;
                                src.y=0;src.w=30;src.h=34;break;
                            case 2 :
                                aa1=7;bb1=0;aa2=13;bb2=36;
                                dst.x+=1; dst.y+=1; 
                                src.y=34;src.w=26;src.h=30;break;
                            case 3 :
                                aa1=10;bb1=21;aa2=13;bb2=21;
                                dst.x+=1; dst.y+=3; 
                                src.y=69;src.w=22;src.h=39;break;
                            case 4 :
                                aa1=10;bb1=21;aa2=13;bb2=24;
                                dst.x+=1; dst.y+=3; 
                                src.y=108;src.w=22;src.h=42;break;
                        }
                        break;
                    case N : 
                        src.x=106;
                        switch ((special1+1)/2) {
                            case 1 :
                                aa1=-12;bb1=-7;aa2=15;bb2=15;
                                dst.x-=12; dst.y-=7; 
                                src.y=0;src.w=32;src.h=33;break;
                            case 2 :
                                aa1=-1;bb1=-10;aa2=13;bb2=17;
                                dst.x-=1; dst.y-=10; 
                                src.y=33;src.w=21;src.h=36;break;
                            case 3 :
                                aa1=-1;bb1=-14;aa2=13;bb2=22;
                                dst.x-=1; dst.y-=14; 
                                src.y=69;src.w=21;src.h=40;break;
                            case 4 :
                                aa1=-1;bb1=-17;aa2=13;bb2=25;
                                dst.x-=1; dst.y-=17; 
                                src.y=109;src.w=21;src.h=43;break;
                        }
                        break;
                    case O : 
                        src.x=138;
                        switch ((special1+1)/2) {
                            case 1 : 
                                aa1=16;bb1=-1;aa2=15;bb2=15;
                                dst.y-=1; 
                                src.y=0;src.w=31;src.h=27;break;
                            case 2 : 
                                aa1=-18;bb1=7;aa2=20;bb2=13;
                                dst.x-=18;
                                src.y=27;src.w=31;src.h=26;break;
                            case 3 : 
                                aa1=-23;bb1=8;aa2=23;bb2=13;
                                dst.x-=23; dst.y+=1; 
                                src.y=53;src.w=36;src.h=25;break;
                            case 4 : 
                                aa1=-28;bb1=8;aa2=28;bb2=13;
                                dst.x-=28; dst.y+=1; 
                                src.y=78;src.w=41;src.h=25;break;
                            
                        }
                        break;
                    case E : 
                        src.x=179;
                        switch ((special1+1)/2) {
                            case 1 : 
                                aa1=-13;bb1=-1;aa2=15;bb2=15;
                                dst.x-=13;dst.y-=1; 
                                src.y=0;src.w=31;src.h=27;break;
                            case 2 : 
                                aa1=16;bb1=7;aa2=20;bb2=13;
                                dst.x+=5;
                                src.y=27;src.w=31;src.h=26;break;
                            case 3 : 
                                aa1=18;bb1=8;aa2=23;bb2=13;
                                dst.x+=5; dst.y+=1; 
                                src.y=53;src.w=36;src.h=25;break;
                            case 4 : 
                                aa1=18;bb1=8;aa2=28;bb2=13;
                                dst.x+=5; dst.y+=1; 
                                src.y=78;src.w=41;src.h=25;break;
                        }
                        break;
                }
                zonesAttaques->getZone()->x=aa1; zonesAttaques->getZone()->y=bb1;
                zonesAttaques->getZone()->w=aa2; zonesAttaques->getZone()->h=bb2;
                }
                if (!gpJeu->getStop()) special1++;
                if(special1==4) gpJeu->getAudio()->playSound(22);
                if (special1>=16) special1=0;
            }
            }
        }
    
        if (id==90) {
            src.y=22*anim;
            switch (direction) {
                case S : src.x=15; src.w=15; src.h=22; dst.y-=7; break;
                case N : src.x=0; src.w=15; src.h=22; break;
                case O : src.x=30; src.y+=5; src.w=24; src.h=17; dst.x-=4; dst.y-=2;break;
                case E : src.x=54; src.y+=5; src.w=24; src.h=17; dst.x-=4; dst.y-=2;break;
            }
            
        }
        
        if (id == 91 || id == 139) {
            src.y=0; src.x=anim*22; if (gpJeu->getJoueur()->getX()+8>x+11) src.x+=44;
            if (special1) src.x=88+22*((special1-1)/4);
        }
        
        if (id == 93) {
            int a;
            int b;
            
            switch (special1) {
                case 0 : case 1 : case 2 : case 3 : src.w=0; src.h=0; break;
                case 4 : case 5 : case 6 : case 7 :
                    if (special2) {
                        a = (x==326*16) ? (332*16) : (326*16);
                        b = (y==49*16+8) ? (54*16+8) : (49*16+8);
                        dst.x=a-phg[0]; dst.y=b-phg[1];
                    }
                    src.x=32; src.y=(special1-4)*32; src.w=32; src.h=32;
                    break;
                case 8 : case 9 :
                    src.x=0;
                    if (special2) {
                        a = (x==326*16) ? (332*16) : (326*16);
                        b = (y==49*16+8) ? (54*16+8) : (49*16+8);
                        src.y=64; dst.x=a-phg[0]; dst.y=b-phg[1];
                        SDL_BlitSurface(image, &src, gpScreen, &dst);
                    }
                    src.y=0; dst.x=x-phg[0]; dst.y=y-phg[1];
                    break;
                case 10 : case 11 : case 12 : case 13 : case 14 : case 15 : case 16 :
                    src.x=0;
                    if (special2) {
                        a = (x==326*16) ? (332*16) : (326*16);
                        b = (y==49*16+8) ? (54*16+8) : (49*16+8);
                        src.y=64; dst.x=a-phg[0]; dst.y=b-phg[1];
                        SDL_BlitSurface(image, &src, gpScreen, &dst);
                    }
                    src.y=32; dst.x=x-phg[0]; dst.y=y-phg[1];
                    break;
                case 17 : case 18 : case 19 : case 20 :
                    src.x=32; src.y=(special1-17)*32;
                    break;
            }
    
            //de 0 à 3, ne fait rien
            //de 4 à 7, tourbillon
            //de 8 à 9, sorti de l'eau
            //de 10 à 16 bouche ouverte, tire en 11, 13, 15
            //de 17 à 20 tourbillon
        }
        
        if (id==94) {
            src.y=special1*32;
            if (special1==2) {
                SDL_BlitSurface(image, &src, gpScreen, &dst);
                src.y=96; src.w=16; src.h=16; dst.x+=8; dst.y-=8;
            }
        }
        
        if (id==95 && (special1 || invincible)) {
            if (special1 > 0 && special1 < 10) {
                src.x=40+19*((special1-1)%2); src.y=0; src.w=19; src.h=31; dst.x++; dst.y-=9;}
            if (special1 >= 10) {
                src.x=27*((special1-10)%2); src.y=44; src.w=27; src.h=24; dst.x-=3; dst.y-=2;}
            if (invincible) {
                src.x=59; src.y=0; src.w=19; src.h=31; dst.x++; dst.y-=9;}
        }
        
        if (id==97) {
            Joueur* gpJoueur = gpJeu->getJoueur();
            if (special2>=17 || gpJoueur->getVie()<=0) {
                if (special2>=17) {
                    gpJeu->getAudio()->playSound(6);
                    if (x < 280*16) {
                        x+=140*16;// xdep+=140*16;
                    } else {
                        vie=0;
                        gpJoueur->setEnnemi(getEnnId());
                        gpJeu->ajouteProjectile(15, direction, x+(w/2)-14, y+(h/2)-14, 0);
                        gpJeu->donneObjet(this);
                    }
                }
                special1=0; special2=0; vitesse=1;
            }
            if (special1>2) {
                special1=0; special2++;
                if (special2 == 10) effets[FEU]=0;
            }
            //regarde si peut frapper
            if (special1==0 && special2<10 && gpJoueur->getVie()>0
            && gpJeu->getKeyboard()->getMode()!=13) {
                //si Link au dessus ou en dessous
                if (gpJoueur->getX()+16>x && gpJoueur->getX()<x+w) {
                    //si au dessus
                    if (gpJoueur->getY()+24 < y && gpJoueur->getY()>y-64) {
                        direction=N; special1=1; lastAnimTime = SDL_GetTicks();
                    }
                    //si au dessous
                    if (gpJoueur->getY()+24 > y+h && gpJoueur->getY()+24<y+h+64) {
                        direction=S; special1=1; lastAnimTime = SDL_GetTicks();
                    }
                }
                //si Link à gauche ou à droite
                if (gpJoueur->getY()+24>y+24 && gpJoueur->getY()+8<y+h) {
                    //si à gauche
                    if (gpJoueur->getX()+16 < x && gpJoueur->getX()>x-64) {
                        direction=O; special1=1; lastAnimTime = SDL_GetTicks();
                    }
                    //si à droite
                    if (gpJoueur->getX() > x+w && gpJoueur->getX()+16<x+w+64) {
                        direction=E; special1=1; lastAnimTime = SDL_GetTicks();
                    }
                }
            }
            
            
            if (special1==0) {
                src.y=h*anim; src.x=0;
                if (special2==10 && !gpJeu->getStop()) {
                    if (x<100*16) {
                        if (x<8*16+6) moveX(1);
                        if (x>8*16+6) moveX(-1);
                        if (y<35*16) moveY(1);
                        if (y>35*16) moveY(-1);
                        if (x == 8*16+6 && y == 35*16) {
                            special2=11; lastAnimTime = SDL_GetTicks();
                        }
                    } else if (x<200*16) {
                        if (x<148*16+6) moveX(1);
                        if (x>148*16+6) moveX(-1);
                        if (y<35*16) moveY(1);
                        if (y>35*16) moveY(-1);
                        if (x == 148*16+6 && y == 35*16) {
                            special2=11; lastAnimTime = SDL_GetTicks();
                        }
                    } else {
                        if (x<288*16+6) moveX(1);
                        if (x>288*16+6) moveX(-1);
                        if (y<35*16) moveY(1);
                        if (y>35*16) moveY(-1);
                        if (x == 288*16+6 && y == 35*16) {
                            special2=11; lastAnimTime = SDL_GetTicks();
                        }
                    }
                }
                if (special2>10) {
                    src.x=162; 
                    if (special2==11 || special2==12) {
                        src.y=0; src.w=60; src.h=52; dst.x-=6; dst.y+=12;}
                    if (special2==13 || special2==14) {
                        src.y=52; src.w=48; src.h=69; dst.x+=6; dst.y-=5;}
                    if (special2==15 || special2==16) {
                        src.y=121; src.w=55; src.h=57; dst.x-=1; dst.y+=13;}
                }
            } else if (special2 < 10) {
                vitesse=3-2*(special1-1);
                switch(direction) {
                    case N : 
                        src.x=54; src.y=75*(special1-1);
                        src.w=43+6*(special1-1); src.h=75-20*(special1-1);
                        dst.x+=(11-6*(special1-1)); dst.y-=(11-20*(special1-1));
                        break;
                    case S : 
                        src.x=54; src.y=130+71*(special1-1);
                        src.w=40+5*(special1-1); src.h=71-15*(special1-1);
                        dst.x+=(14-5*(special1-1)); dst.y-=(7-15*(special1-1));
                        break;
                    case O : 
                        src.x=103; src.y=68*(special1-1);
                        src.w=47+12*(special1-1); src.h=68-19*(special1-1);
                        dst.x+=(7-12*(special1-1)); dst.y-=(4-19*(special1-1));
                        break;
                    case E : 
                        src.x=103; src.y=117+68*(special1-1);
                        src.w=47+12*(special1-1); src.h=68-19*(special1-1);
                        dst.x+=(7-12*(special1-1)); dst.y-=(4-19*(special1-1));
                        break;
                }
            }
        }
        
        if (id == 98) {
            int a;
            
            switch (special1) {
                case 0 : case 1 : case 2 : case 3 : src.w=0; src.h=0; break;
                case 4 : case 5 : case 6 : case 7 :
                    if (special2==1) {
                        if (x==89*16) a=95*16;
                        else if (x==95*16) a=83*16;
                        else a=89*16;
                        dst.x=a-phg[0];
                    }
                    if (special2==2) {
                        if (x==89*16) a=83*16;
                        else if (x==95*16) a=89*16;
                        else a=95*16;
                        dst.x=a-phg[0];
                    }
                    src.x=32; src.y=(special1-4)*32; src.w=32; src.h=32;
                    break;
                case 8 : case 9 :
                    src.x=0;
                    if (special2==1) {
                        if (x==89*16) a=95*16;
                        else if (x==95*16) a=83*16;
                        else a=89*16;
                        src.y=64; dst.x=a-phg[0];
                        SDL_BlitSurface(image, &src, gpScreen, &dst);
                    }
                    if (special2==2) {
                        if (x==89*16) a=83*16;
                        else if (x==95*16) a=89*16;
                        else a=95*16;
                        src.y=64; dst.x=a-phg[0];
                        SDL_BlitSurface(image, &src, gpScreen, &dst);
                        if (x==89*16) a=95*16;
                        else if (x==95*16) a=83*16;
                        else a=89*16;
                        src.y=96; dst.x=a-phg[0];
                        SDL_BlitSurface(image, &src, gpScreen, &dst);
                    }
                    src.y=0; dst.x=x-phg[0]; dst.y=y-phg[1];
                    break;
                case 10 : case 11 : case 12 : case 13 : case 14 : case 15 : case 16 :
                    src.x=0;
                    if (special2==1) {
                        if (x==89*16) a=95*16;
                        else if (x==95*16) a=83*16;
                        else a=89*16;
                        src.y=64; dst.x=a-phg[0];
                        SDL_BlitSurface(image, &src, gpScreen, &dst);
                    }
                    if (special2==2) {
                        if (x==89*16) a=83*16;
                        else if (x==95*16) a=89*16;
                        else a=95*16;
                        src.y=64; dst.x=a-phg[0];
                        SDL_BlitSurface(image, &src, gpScreen, &dst);
                        if (x==89*16) a=95*16;
                        else if (x==95*16) a=83*16;
                        else a=89*16;
                        src.y=96; dst.x=a-phg[0];
                        SDL_BlitSurface(image, &src, gpScreen, &dst);
                    }
                    src.y=32; dst.x=x-phg[0]; dst.y=y-phg[1];
                    break;
                case 17 : case 18 : case 19 : case 20 :
                    src.x=32; src.y=(special1-17)*32;
                    break;
            }
    
            //de 0 à 3, ne fait rien
            //de 4 à 7, tourbillon
            //de 8 à 9, sorti de l'eau
            //de 10 à 16 bouche ouverte, tire en 11, 13, 15
            //de 17 à 20 tourbillon
        }
        
        if (id == 99) {
            if (special1 > 200) {
                if (!gpJeu->getStop()) special1++;
                if (special1>=210) {
                    special1=0;
                    int randomValue = (int)((float)rand() / RAND_MAX * (6));
                    switch (randomValue) {
                        case 0 : x=184*16-2; y=26*16; break;
                        case 1 : x=190*16-2; y=17*16; break;
                        case 2 : x=198*16-2; y=32*16; break;
                        case 3 : x=201*16-2; y=23*16; break;
                        case 4 : x=211*16-2; y=35*16; break;
                        case 5 : x=212*16-2; y=19*16; break;
                        default : x=198*16-2; y=32*16; break;
                    }
                }
            }
            else if (special1 > 105) {
                if (!gpJeu->getStop()) special1+=2;
                if (special1>201) special1=201;
                src.y=0; src.h=95-(special1-107); dst.y+=(special1-107);
                SDL_BlitSurface(image, &src, gpScreen, &dst);
                src.x=72; src.y=190+16*((special1/8)%3);
                src.w=64; src.h=16;
                dst.x=x+2-phg[0]; dst.y=y+95-8-phg[1];
            }
            else if (special1 > 95) {
                src.x=w;
                if (special1==100) src.y+=h;
            }
            else if (special1 < 95) {
                if (!gpJeu->getStop()) special1+=2;
                if (vie == viemax && !gpJeu->getStop()) special1--;
                if (special1>95) special1=95;
                src.y=0; src.h=special1; dst.y+=(95-special1);
                SDL_BlitSurface(image, &src, gpScreen, &dst);
                src.x=72; src.y=190+16*((special1/8)%3);
                src.w=64; src.h=16;
                dst.x=x+2-phg[0]; dst.y=y+95-8-phg[1];
                if (special1>=95) {
                    force=4;
                    zonesAttaques->getZone()->w=w; zonesAttaques->getZone()->h=h;
                    zonesVulnerables->getZone()->w=w; zonesVulnerables->getZone()->h=60;
                }
            }
            else if (special2 >= 3) src.y+=h;
            if (special1>0 && special1 <= 200) SDL_BlitSurface(image, &src, gpScreen, &dst);
        }
        
        if (id == 101) {src.y+=h*special1;}
        
        if (id==102) {
            int nb_torches=0;
            
            if (gpJeu->getMonde()->motifValue(162*16,47*16)==1001) nb_torches++;
            if (gpJeu->getMonde()->motifValue(177*16,47*16)==1001) nb_torches++;
            if (gpJeu->getMonde()->motifValue(162*16,57*16)==1001) nb_torches++;
            if (gpJeu->getMonde()->motifValue(177*16,57*16)==1001) nb_torches++;
            
            if (gpJeu->getKeyboard()->getMode() == 13) nb_torches = 4;
            
            if (nb_torches==4 && special2==0) {
                special2=1; special1=0; for (int k = 0; k < 25; k++) effets[k]=1;
                if (gpJeu->getJoueur()->getEpee()>=2) {
                    effets[COUP_EPEE]=2; effets[EPEE_SPIN]=2;}
                if (gpJeu->getJoueur()->hasObjet(O_ARC)==5) 
                    effets[FLECHE]=2; 
            }
            
            int alpha = nb_torches*64;
            if (alpha == 256) alpha--;
            SDL_SetAlpha(image, SDL_SRCALPHA, alpha);
            
            SDL_BlitSurface(image, &src, gpScreen, &dst);
            src.x=0; src.y=42; src.w=24; src.h=6; dst.y+=21;
            SDL_SetAlpha(image, SDL_SRCALPHA, 255);
        }
        
        if (id == 103 && (special2>=0 || special1<0)) {
            
            //apparait
            if (special2>=0 && special2<=256 && special1>=0) {
                int alpha=special2;
                if (special2>255) {
                    alpha=255;
                    if (gpJeu->getJoueur()->getEpee()>=2) {
                        effets[COUP_EPEE]=2; effets[EPEE_SPIN]=2;}
                    if (gpJeu->getJoueur()->hasObjet(O_ARC)==5) effets[FLECHE]=2;
                    zonesVulnerables->getZone()->w=81;
                    zonesVulnerables->getZone()->h=40;
                    zonesVulnerables->getSuivant()->getZone()->w=27; 
                    zonesVulnerables->getSuivant()->getZone()->h=12;
                    force = 5;
                }
                SDL_SetAlpha(image, SDL_SRCALPHA, alpha);
                special2+=8;
            }
            
            //disparait 
            if (special2>=0 && special1==-1) {
                special2-=8;
                if (special2 > 255) special2=255;
                int alpha=special2;
                if (special2<=0) {
                    alpha=0; special1=0; special2=0;
                    int random = rand()%3;
                    x = (242+(5*random))*16+6;
                    y = 20*16; if (random==1) y-=3*16;
                }
                SDL_SetAlpha(image, SDL_SRCALPHA, alpha);
            }
            
            if (special1==-2) {
                src.x=255; src.y=0; src.w=71; dst.x+=5;
            } else if (special1<-2) {
                if (special1==-3) {
                    if (x==242*16+6) direction=E;
                    if (x==247*16+6) direction=S;
                    if (x==252*16+6) direction=O;
                }
                switch (direction) {
                    case S : y+=2; break;
                    case O : x-=4; break;
                    case E : x+=4; break;
                    default : break;
                }
                dst.x=x-phg[0]; dst.y=y-phg[1];
                int step = (-special1-3)/7;
                switch (step) {
                    case 0 : 
                        src.x=249; src.y=82; src.w=95; dst.x-=2;
                        zonesVulnerables->getSuivant()->getZone()->x=35; 
                        zonesVulnerables->getSuivant()->getZone()->y=30;
                        zonesVulnerables->getSuivant()->getZone()->w=49; 
                        zonesVulnerables->getSuivant()->getZone()->h=22;
                        zonesAttaques->getSuivant()->getZone()->x=35; 
                        zonesAttaques->getSuivant()->getZone()->y=30;
                        zonesAttaques->getSuivant()->getZone()->w=49; 
                        zonesAttaques->getSuivant()->getZone()->h=22;
                        break;
                    case 1 : 
                        src.x=253; src.y=165; src.w=87; src.h=74; dst.x+=2; dst.y+=9;
                        zonesVulnerables->getSuivant()->getZone()->x=32+2; 
                        zonesVulnerables->getSuivant()->getZone()->y=35+9;
                        zonesVulnerables->getSuivant()->getZone()->w=47; 
                        zonesVulnerables->getSuivant()->getZone()->h=34;
                        zonesAttaques->getSuivant()->getZone()->x=32+2; 
                        zonesAttaques->getSuivant()->getZone()->y=35+9;
                        zonesAttaques->getSuivant()->getZone()->w=47; 
                        zonesAttaques->getSuivant()->getZone()->h=34;
                        break;
                    case 2 : 
                        src.x=253; src.y=239; src.w=87; src.h=66; dst.x+=2; dst.y+=17;
                        zonesVulnerables->getSuivant()->getZone()->x=11+2; 
                        zonesVulnerables->getSuivant()->getZone()->y=28+17;
                        zonesVulnerables->getSuivant()->getZone()->w=55; 
                        zonesVulnerables->getSuivant()->getZone()->h=37;
                        zonesAttaques->getSuivant()->getZone()->x=11+2; 
                        zonesAttaques->getSuivant()->getZone()->y=28+17;
                        zonesAttaques->getSuivant()->getZone()->w=55; 
                        zonesAttaques->getSuivant()->getZone()->h=37;
                        break;
                    case 3 : 
                        src.x=253; src.y=305; src.w=87; src.h=56; dst.x+=2; dst.y+=27;
                        zonesVulnerables->getSuivant()->getZone()->x=11+2; 
                        zonesVulnerables->getSuivant()->getZone()->y=15+27;
                        zonesVulnerables->getSuivant()->getZone()->w=40; 
                        zonesVulnerables->getSuivant()->getZone()->h=35;
                        zonesAttaques->getSuivant()->getZone()->x=11+2; 
                        zonesAttaques->getSuivant()->getZone()->y=15+27;
                        zonesAttaques->getSuivant()->getZone()->w=40; 
                        zonesAttaques->getSuivant()->getZone()->h=35;
                        break;
                    case 4 : 
                        src.x=253; src.y=361; src.w=87; src.h=55; dst.x+=2; dst.y+=28;
                        zonesVulnerables->getSuivant()->getZone()->x=11+2; 
                        zonesVulnerables->getSuivant()->getZone()->y=30+28;
                        zonesVulnerables->getSuivant()->getZone()->w=40; 
                        zonesVulnerables->getSuivant()->getZone()->h=20;
                        zonesAttaques->getSuivant()->getZone()->x=11+2; 
                        zonesAttaques->getSuivant()->getZone()->y=30+28;
                        zonesAttaques->getSuivant()->getZone()->w=40; 
                        zonesAttaques->getSuivant()->getZone()->h=20;
                        break;
                    default : 
                        zonesAttaques->getSuivant()->getZone()->x=30; 
                        zonesAttaques->getSuivant()->getZone()->y=46;
                        zonesAttaques->getSuivant()->getZone()->w=27; 
                        zonesAttaques->getSuivant()->getZone()->h=12;
                        src.x=0; if (gpJeu->getJoueur()->getX()+16 < x) src.x=w;
                        else if (gpJeu->getJoueur()->getX() > x+w) src.x=w*2;
                        special1=0;
                        for (int k = 0; k < 25; k++) effets[k]=0;
                        zonesVulnerables->getZone()->w=0;
                        zonesVulnerables->getZone()->h=0;
                        zonesVulnerables->getSuivant()->getZone()->w=0; 
                        zonesVulnerables->getSuivant()->getZone()->h=0;
                        force=0; break;
                }
                special1--;
            } else {
                src.x=0; if (gpJeu->getJoueur()->getX()+16 < x) src.x=w;
                else if (gpJeu->getJoueur()->getX() > x+w) src.x=w*2;
            }
        }
        
        if (id==105) {
            Joueur* gpJoueur = gpJeu->getJoueur();
            if (special1>2) {special1=0; typeIA=IA_FONCE;}
            //regarde si peut frapper
            if (special1==0 && gpJoueur->getVie()>0) {
                //si Link au dessus ou en dessous
                if (gpJoueur->getX()+16>x+16 && gpJoueur->getX()<x+w-16) {
                    //si au dessus
                    if (gpJoueur->getY()+24 < y && gpJoueur->getY()>y+16-64) {
                        direction=N; special1=1; lastAnimTime = SDL_GetTicks();
                        ajuste();
                    }
                    //si au dessous
                    if (gpJoueur->getY()+24 > y+h && gpJoueur->getY()+24<y+h+64) {
                        direction=S; special1=1; lastAnimTime = SDL_GetTicks();
                        ajuste();
                    }
                }
                //si Link à gauche ou à droite
                if (gpJoueur->getY()>y && gpJoueur->getY()+8<y+h) {
                    //si à gauche
                    if (gpJoueur->getX()+16 < x && gpJoueur->getX()>x-64) {
                        direction=O; special1=1; lastAnimTime = SDL_GetTicks();
                        ajuste();
                    }
                    //si à droite
                    if (gpJoueur->getX() > x+w && gpJoueur->getX()+16<x+w+64) {
                        direction=E; special1=1; lastAnimTime = SDL_GetTicks();
                        ajuste();
                    }
                }
            }
            vitesse=1;
            if (special1 > 0) {
                vitesse=4*(special1-1);
                src.y=480+80*(special1-1);
                if (direction == S && special1 > 1) src.h=87;
                typeIA=IA_RANDOM;
            }
        }
        
        if (id==106) {
            src.x=special2*w;
            if (invincible) src.x=156;
            src.y=anim*h;
        }
        
        if (id == 107) {
            
            if (gpJeu->getKeyboard()->getMode()==13) {
                src.x=0; src.y=64; src.w=77; src.h=51;
            } else {
            
            vitesse = (((viemax-vie)/4) + 1);
            src.x=0; src.y=123-h;
            if (invincible) src.x=234;
            if (gpJeu->getJoueur()->getX()+16 < x) src.x=156;
            if (gpJeu->getJoueur()->getX() > x+w) src.x=78;
            if (special2==0 && h < 123) {
                if (!gpJeu->getStop()) h+=vitesse; if (h > 123) h = 123;
                if (h-59 < 0) zonesVulnerables->getZone()->y = 0;
                else zonesVulnerables->getZone()->y = h-59;
                if (h-(9+64) < 0) zonesVulnerables->getZone()->h = 0;
                else zonesVulnerables->getZone()->h = h-(9+64);
            }
            if ((special2==(((viemax-vie)/8) + 1) && h > 1) || (special2 > 0 && h < 123)) {
                if (!gpJeu->getStop()) h-=vitesse; if (h < 1) h = 1;
                if (h-59 < 0) zonesVulnerables->getZone()->y = 0;
                else zonesVulnerables->getZone()->y = h-59;
                if (h-(9+64) < 0) zonesVulnerables->getZone()->h = 0;
                else zonesVulnerables->getZone()->h = h-(9+64);
                if (h==1) {
                    special1=0; special2=0;
                    x = 242*16 + (5*16+8)*(rand()%3); 
                }
            }
            src.w=w; src.h=h;
            
            }    
        }
        
        if (id == 109 && !gpJeu->getStop()) {
            if (h < 96) {
                src.y=96*anim+(96-h);
                h++; 
            }
            if (special2==1) {
                if (direction == E) {
                    if (x < 200*16-w) x+=vitesse;
                    if (x > 200*16-w) x = 200*16-w;
                    if (x == 200*16-w) {direction=O; special2=0;}
                } 
                else if (direction == O) {
                    if (x > 180*16) x-=vitesse;
                    if (x < 180*16) x = 180*16;
                    if (x == 180*16) {direction=E; special2=0;}
                }
                dst.x = x - phg[0];
            }
        }
        
        if (id == 110) {
            //anim de 0 à 14 : au sol
            //anim à 15 : se relève
            //anim de 16 à 28 : debout
            //anim à 29 : se rabaisse
            //anim de 30 à 31 : au sol
            
            if (gpJeu->getKeyboard()->getMode()==13) anim=16;
            
            if (invincible || (anim > 15 && anim < 29)) src.y=32;
            else src.y=0;
            if (invincible || anim == 15 || anim == 29) src.x = 116;
            else src.x = w*(anim%4);
        }
        
        
        if (id == 111 && glace) {src.y=0; src.x=w*4; special1=0; typeIA=IA_FONCE;}
        if (id==111 && !glace) {
            Joueur* gpJoueur = gpJeu->getJoueur();
            if (special1>2) {special1=0; typeIA=IA_FONCE;}
            //regarde si peut frapper
            if (special1==0 && gpJoueur->getVie()>0) {
                //si Link au dessus ou en dessous
                if (gpJoueur->getX()+16>x+8 && gpJoueur->getX()<x+w-8) {
                    //si au dessus
                    if (gpJoueur->getY()+24 < y && gpJoueur->getY()>y+16-64) {
                        direction=N; special1=1; lastAnimTime = SDL_GetTicks();
                    }
                    //si au dessous
                    else if (gpJoueur->getY()+24 > y+h && gpJoueur->getY()+24<y+h+64) {
                        direction=S; special1=1; lastAnimTime = SDL_GetTicks();
                    }
                }
                //si Link à gauche ou à droite
                if (gpJoueur->getY()>y && gpJoueur->getY()+8<y+h && !special1) {
                    //si à gauche
                    if (gpJoueur->getX()+16 < x && gpJoueur->getX()>x-64) {
                        direction=O; special1=1; lastAnimTime = SDL_GetTicks();
                    }
                    //si à droite
                    else if (gpJoueur->getX() > x+w && gpJoueur->getX()+16<x+w+64) {
                        direction=E; special1=1; lastAnimTime = SDL_GetTicks();
                    }
                }
            }
            vitesse=1;
            if (special1 > 0) {
                vitesse=4*(special1-1);
                src.y=h*(special1+1);
                //if (direction == S && special1 > 1) src.h=87;
                typeIA=IA_RANDOM;
            }
        }
        
        if (id==113) {
            
            if (gpJeu->getKeyboard()->getMode()==13) anim=16;
            
            if (anim < 14) src.x=0;
            else if (anim < 16) src.x=(anim-13)*w;
            else if (anim < 30) src.x=w*3;
            else if (anim < 32) src.x=w*(3-(anim-29));
            //0 à 13 : oeil fermé
            //14 à 15 : oeil s'ouvre
            //16 à 29 : oeil ouvert
            //30 à 31 : oeil se ferme
        }
        
        if (id == 115 && special2>=0) {
            //if (gpJeu->getMonde()->regionValue(0)==60*16) {
            if (anim > animmax-4) src.x=w*(anim-(animmax-4)); else src.x=0;
            
            if (h < 91) {
                dst.x=x-phg[0]+16; src.x=16; src.w-=32;
                if (!gpJeu->getStop()) h++; 
                src.h=h;dst.y=y-phg[1]+((91-8)-h);
                if (dst.y<y-phg[1]) dst.y=y-phg[1];
                if (h==91) {
                    force=10; 
                    getSuivant()->special1=1; 
                    getSuivant()->getSuivant()->special1=1;
                    for (int k = 0; k < 25; k++) effets[k]=2; effets[FEU]=0;
                    zonesVulnerables->getZone()->y = 67;
                    zonesVulnerables->getZone()->h = 16;
                }
            }
            SDL_BlitSurface(image, &src, gpScreen, &dst);
        }
        
        if (id == 116 && special2>=0) {
            src.x=w*special2;
            if (h < 68) {
                if (!gpJeu->getStop()) h++; 
                src.h=h;dst.y=y-phg[1]+(50-h);
                if (dst.y<y-phg[1]) dst.y=y-phg[1];
            }
            if (special2==6 && gpJeu->getJoueur()->getX() < x+w-16 && special1>0) {
                special2=7;
            }
            if (special2 > 6) {
                src.x=w*7; dst.y+=8; dst.x-=16;
                if (special2==10) src.x=w*8;
            }
            SDL_BlitSurface(image, &src, gpScreen, &dst);
        }
        
        if (id == 117 && special2>=0) {
            src.x=w*special2;
            //if (gpJeu->getMonde()->regionValue(0)==60*16) {
                if (h < 68) {
                    if (!gpJeu->getStop()) h++; 
                    src.h=h;dst.y=y-phg[1]+(50-h);
                    if (dst.y<y-phg[1]) dst.y=y-phg[1];
                }
                if (special2==6 && gpJeu->getJoueur()->getX() > x+16 && special1>0) {
                    special2=7;
                }
                if (special2 > 6) {
                    src.x=w*7; dst.y+=8; dst.x+=16;
                    if (special2==10) src.x=w*8;
                }
                SDL_BlitSurface(image, &src, gpScreen, &dst);
            //}
        }
        
        if (id == 119 && typeIA==IA_RIEN) {
            src.x=0; src.y=h*2;
        }
        
        if (id == 120) {
            //décide quoi faire
            if (special2 == 0) special2 = 1 + (rand()%3);
            if (special1 > 1 && special1 <(3 + (vie / 15))) src.x=w*special2;
        }
        
        if (id == 124 || id == 125) {
            if (id == 125 && special2 == 0 && !gpJeu->getStop()) {
                int r = rand()%5;
                if (r >= special1) r++;
                special1 = r;
            }
            src.y=h*anim;
            src.x=w*special1;
        }
        
        if (id == 128 && distance()) {
            if (!gpJeu->getStop()) special1++;
            switch (special2) {
                case 0 : if (special1 >= 50) {special1=0; special2=1+(rand()%2);} break;
                case 1 :
                    if (special1 >= 50) {special1=0; special2=0; break;}
                    if (special1 == 25) tire();
                    src.x=w*(1+(special1/25));
                    break;
                case 2 :
                    if (special1 >= 50) {special1=0; special2=0; break;}
                    if (special1 == 30) {
                        snipe(); special2=3;
                        snipe(); special2=2;
                    }
                    src.x=w*(3+(special1/10));
                    break;
            }
        }
        
        if (id == 141) {
            invincible = 0;
            if (special2) src.y+=h;
            if (special2 == 12) {
                src.x=570; src.w=62; dst.x-=1;
            }
            if (special2 == 13) {
                src.x=632; src.w=64; dst.x-=2;
            }
        }
        
        
        
    
        
        if (direction==N && arme) drawArme(gpScreen);
        
        if ((id != 99) && ((id != 51 && id != 67) || anim>=20) && (id!=70) && id!=115
         && id!=116 && id!=117) 
            SDL_BlitSurface(image, &src, gpScreen, &dst);
        
        if (direction!=N && arme) drawArme(gpScreen);
        
        //if(animmax) {    
            if(SDL_GetTicks() > lastAnimTime + vanim && !gpJeu->getStop()) {
                lastAnimTime = SDL_GetTicks();
                if ((!invincible || id==115 || id==141) && !glace) {
                    anim++;
                    if (anim > animmax) anim = 0;
                    if ((id == 10 || id == 86) && anim == 1) snipe();
                    if ((id == 15 || id == 130) && anim == 20) tire();
                    if ((id == 16 || id == 131) && anim > 4 && anim%2==1) tire();
                    if (id == 27 && anim == 8) tire();
                    if (id == 30 && anim == 5) tire();
                    if (id == 31 && anim == 8) snipe();
                    if ((id == 36 || id == 49 || id == 65) && anim == 8) snipe();
                    if (id == 40 && anim == 8) snipe();
                    if (id == 45) {
                        if (special1 < 3 && special2 > 40) anim--;
                        special2++;
                        if (special1 < 3) {
                            if (special2 > 50) special2=0;
                            if (special2 == 45) snipe();
                        } else {
                            if (special2>20) special2=0;
                            if (special2==15) snipe();
                            if (special2==17) snipe();
                            if (special2==19) snipe();
                        }
                    }
                    if (id == 50 && special1>0) {
                        special1++;
                        if (!gpJeu->getJoueur()->getVie()) special1=9;
                        if (special1==8) {
                            snipe();
                            if (special2 >= 8 && special2 < 25 && gpJeu->getJoueur()->getVie()) 
                                special2++;
                            if (special2==25 && gpJeu->getJoueur()->hasObjet(O_ARC_OR)==2) {
                                gpJeu->getAudio()->playSound(20);
                                gpJeu->getMonde()->passage(160,21,1);
                                Pnj* zelda = gpJeu->getPnj()->getSuivant();
                                zelda->setX(160*16+8); zelda->setY(21*16+9); 
                                zelda->setDirection(E); zelda->setImmo(false);
                                special2=21;
                            }
                        }
                        else if (special1==10 && (special2==2 || special2==5 || special2>=8)) 
                            special1=(special2==2)?2:5;
                        else if (special1==10) special1=(rand()%2)*5;
                    }
                    if (id == 50 && special1==0 && (special2==0 || special2==3 || special2==6) 
                    && gpJeu->getJoueur()->getVie()) {
                        if (rand()%15==10) special1=1;
                    }
                    if (id == 50 && special1==0 && (special2==2 || special2==5 || special2>=8) 
                    && gpJeu->getJoueur()->getVie()) {
                        special1=1;
                    }
                    if (id == 51 && anim == 10+10) {
                        x=gpJeu->getJoueur()->getX()-4;y=gpJeu->getJoueur()->getY();}
                    if (id == 51 && anim == 20) {special1=240;gpJeu->getAudio()->playSound(6);}
                    if (id == 51 && anim == 30) if (special1>0) anim--;
                    if (id == 51 && anim == 40) if (special1<240) anim--;
                    if (id == 57 && anim > 30 && getSuivant()->vie 
                        && getSuivant()->getSuivant()->vie
                        && getSuivant()->getSuivant()->getSuivant()->vie) anim=0;
                    if (id == 57 && anim == 38) renfort();
                    if (id == 62 || id == 135) {
                        if (!special2) {
                            special1++;if (special1 >= 10) {special1=0; if (vie<viemax) vie++;}
                        }else {
                            special2++;
                            if (special2>=49) {
                                special1=0;special2=0;recul=4;
                                typeIA=IA_FONCE;force=2;vie=viemax;
                                for (int k = 0; k < 25; k++) effets[k]=2;
                                zonesVulnerables->getZone()->w=w; 
                                zonesVulnerables->getZone()->h=h;
                                zonesVulnerables->getZone()->x=0; 
                                zonesVulnerables->getZone()->y=0; 
                            }
                        }
                    }
                    if (id == 63 && special2>0 && special2==1) {
                        special2=2; w=82; h=56; y+=4; animmax=1;
                        zonesVulnerables->getZone()->h=56;
                        zonesVulnerables->getSuivant()->getZone()->w=82; 
                        zonesVulnerables->getSuivant()->getZone()->h=34;
                        zonesAttaques->getZone()->h=56;
                        zonesAttaques->getSuivant()->getZone()->w=82; 
                        zonesAttaques->getSuivant()->getZone()->h=34;
                    }
                    if (id == 66 && special1>0) {
                        if (special1 < 134) {
                            special1++;
                            if (special1 > 10) {
                                h++;
                                if (special1<134-8) {
                                    zonesAttaques->getZone()->h=h;
                                    zonesVulnerables->getZone()->h=h;
                                    y--;
                                }
                                else {
                                    h=124; special1=134; 
                                    for (int k = 0; k < 25; k++) effets[k]=2;
                                    Ennemi* enn = getSuivant();
                                    enn->vie=1;
                                    for (int z = 0; z < 4; z++) {
                                        enn = enn->getSuivant();
                                        enn->vie=1; enn->special1=1;
                                    }
                                }
                            }
                        }
                    }
                    if (id == 67) {
                        if (anim==0) {
                            force=0;
                            h=0; zonesAttaques->getZone()->h=h;
                            zonesVulnerables->getZone()->h=h;}
                        if (anim==10) {
                            x=gpJeu->getJoueur()->getX()+8;y=gpJeu->getJoueur()->getY()+24;
                            int k=x-x%16; if (x-k>4) x=k+12; else x=k-4;
                            int l=y-y%16; if (y-l>8) y=l+13+7; else y=l-3+7;
                        }
                        if (anim==20) {
                            force=8;
                            h=8; zonesAttaques->getZone()->h=h;
                            zonesVulnerables->getZone()->h=h; y-=7;}
                        if (anim==21) {
                            h=22; zonesAttaques->getZone()->h=h;
                            zonesVulnerables->getZone()->h=h; y-=14;}
                        if (anim==22) {
                            h=47; zonesAttaques->getZone()->h=h;
                            zonesVulnerables->getZone()->h=h; y-=25;}
                        if (anim==23) {
                            h=22; zonesAttaques->getZone()->h=h;
                            zonesVulnerables->getZone()->h=h; y+=25;}
                        if (anim==24) {
                            h=8; zonesAttaques->getZone()->h=h;
                            zonesVulnerables->getZone()->h=h; y+=14;}
                    }
                }
                if ((id == 68 || id == 69) && special1>0) {
                    if (special1 < 50) {
                        special1++;
                        if (special1 > 10) {
                            h++;
                            if (special1 < 42) {
                                zonesAttaques->getZone()->h=h;
                                zonesVulnerables->getZone()->h=h;
                                y--;
                            }
                            else {h=40; special1=50;}
                        }
                    }else {
                        if (id == 68) {
                            if (special2 > 0 
                            || (gpJeu->getJoueur()->getX() + 20 > x 
                            && gpJeu->getJoueur()->getX()< x + 80 
                            && gpJeu->getJoueur()->getY() + 24 > y 
                            && gpJeu->getJoueur()->getY() < y + 63)) {
                                special2++;
                                switch (special2) {
                                    case 1 : w=41; zonesAttaques->getZone()->w=w; break;
                                    case 2 : w=27; zonesAttaques->getZone()->w=w; break;
                                    case 3 : 
                                        w=80; zonesAttaques->getZone()->w=w;
                                        h=63; zonesAttaques->getZone()->h=h;
                                        zonesAttaques->getZone()->y=20; break;
                                    case 4 :
                                        w=26; zonesAttaques->getZone()->w=w;
                                        h=40; zonesAttaques->getZone()->h=h-10;
                                        zonesAttaques->getZone()->y=0; special2 = 0; break;
                                }
                            }
                        }else {
                            if (special2 > 0 
                            || (gpJeu->getJoueur()->getX() + 20 > (x+w)-80 
                            && gpJeu->getJoueur()->getX() < (x+w) 
                            && gpJeu->getJoueur()->getY() + 24 > y 
                            && gpJeu->getJoueur()->getY() < y + 63)) {
                                special2++;
                                switch (special2) {
                                    case 1 : x-=15; w=41; zonesAttaques->getZone()->w=w; break;
                                    case 2 : x+=14; w=27; zonesAttaques->getZone()->w=w; break;
                                    case 3 : x-=53;
                                        w=80; zonesAttaques->getZone()->w=w;
                                        h=63; zonesAttaques->getZone()->h=h;
                                        zonesAttaques->getZone()->y=20; break;
                                    case 4 : x+=54;
                                        w=26; zonesAttaques->getZone()->w=w;
                                        h=40; zonesAttaques->getZone()->h=h-10;
                                        zonesAttaques->getZone()->y=0; special2 = 0; break;
                                }
                            }
                        }
                    }
                }
                if (id == 70 && special1<135-8) special1++;
                if (id == 70 && special1==135-8) special1+=8;
                if (id == 73 && y<0) y++;
                if (id == 73 && y==0 && anim==0) {
                    special2++;
                    if (special2==3) snipe();
                    if (special2==4) special2=0;
                }
                if (id == 74 && y>-152 && y<0) y++;
                if (id == 74 && y==0 && anim==0) {
                    special2++;
                    if (special2==3) snipe();
                    if (special2==5) special2=0;
                }
                if (id == 75 && special2>0) {
                    vie+=2; if (vie>=viemax) {vie=viemax; special2=0; typeIA=IA_FONCE; force=10;}
                }
                if (id == 76 && anim==0 && special1==0) {snipe(); special1=1;}
                if (id == 76 && anim==1 && special1==1) special1=0;
                if (id == 91 || id == 139) {
                    if (special1==0) {
                        special2++;
                        if (special2==3) snipe();
                        if (special2>=16) special2=0;
                    }
                }
                if (id==92) {
                    special1++;
                    if (special1==3) snipe();
                    if (special1>=4+(vie/3)) special1=0;
                }
                if (id==93 || id==98) IAZoraG();
                if (id==94 && special1==1) {
                    gpJeu->getAudio()->playSound(34);
                    special1=2;
                }
                if (id==95 && special1) special1++;
                if (id==97 && special1) special1++;
                if (id==97 && special2>10) {
                    special2++;
                    if (special2==15) {
                        gpJeu->getAudio()->playSound(16);
                        if (x<100*16) {gpMonde->passage(3,33,5); xdep+=140*16;}
                        else if (x<200*16) {gpMonde->passage(144,34,6); xdep+=140*16;}
                        else gpMonde->passage(288,35,7);
                        gpJeu->testFin();
                    }
                }
                if (id==99) {
                    if (special1>95 && special1<=105) special1++;
                    if (special1==95) special2++;
                    if (special2==4) snipe();
                    if (special2==6) special2=0;
                    if (special2>=5 && vie < 30) special2=0;
                    if (special2==0 && vie < 30) special2=1;
                    if (special2==1 && vie < 20) special2=2;
                    if (special2==2 && vie < 10) special2=3;
                }
                if (id == 101 && special1) {
                    special2++;
                    if (special2==3) snipe();
                    if (special2==4) special2=0;
                }
                if (id == 102 && special2==0) {
                    special1++;
                    if (special1==7) snipe();
                    if (special1==8) special1=0;
                }
                if (id == 102 && special2>0) {
                    special2++;
                    if (special2==5) gpJeu->getMonde()->setValeur(162*16,47*16,1000,1);
                    if (special2==10) gpJeu->getMonde()->setValeur(177*16,47*16,1000,1);
                    if (special2==15) gpJeu->getMonde()->setValeur(162*16,57*16,1000,1);
                    if (special2==20) gpJeu->getMonde()->setValeur(177*16,57*16,1000,1);
                    if (special2==20) {
                        special2=0; for (int k = 0; k < 25; k++) effets[k]=1;
                    }
                }
                if (id == 103 && special2<0) {
                    special2+=2;
                    if (special2==-30) gpJeu->getMonde()->setValeur(242*16,17*16,1000,1);
                    if (special2==-20) gpJeu->getMonde()->setValeur(257*16,17*16,1000,1);
                    if (special2==-10) gpJeu->getMonde()->setValeur(242*16,27*16,1000,1);
                    if (special2==0) { 
                        gpJeu->getMonde()->setValeur(257*16,27*16,1000,1);
                        if (special1==-2) {
                            special1=-1;
                            y-=20;
                        }
                    }
                }
                if (id == 103 && special2>256 && special1>=0 && vie > viemax/2) {
                    special1++;
                    if (special1==7) snipe();
                    if (special1==8) special1=0;
                }
                if (id == 103 && special2>256 && special1>=0 && vie <= viemax/2) {
                    special1++;
                    if (special1==8) special1=-3;
                }
                if (id==105 && special1) {special1++; ajuste();}
                if (id==106) {
                    if (special2==0) {
                        special1++;
                        if (special1>=4) {
                            invincible=0;
                            special2=1+(rand()%3);
                            special1=0;
                            snipe();
                            if (special2==3) {special1=1; snipe(); special1=0;}
                        }
                    }
                    else {
                        special2++;
                        if (special2>=2) special2=0;
                    }
                }
                if (id==107) {
                    if (special2<(((viemax-vie)/8) + 1) && h==123) {
                        special1++;
                        if (special1>=2) {
                            invincible=0;
                            special2++;
                            special1=0;
                            snipe();
                        }
                    }
                }
                if (id == 108) {
                    special1++;
                    if (special1==10) snipe();
                    if (special1==11) special1=0;
                }
                if (id == 109 && special2==0 && invincible==0 && h==96) {
                    //special1++;
                    if (anim==2) {
                        special2=(rand()%3)-1;
                        for (int i = 5; i < 9; i++) {special1=i; snipe();}
                        special1=0; special2=0;
                        if (rand()%5==2) special2=1;
                    }
                }
                if (id == 110) {
                    if (anim == 16) {effets[FEU]=2; special1=0;}
                    if (anim == 22 && special1==0) {snipe(); special1=1;}
                    if (anim == 29) effets[FEU]=0;
                }
                if (id==111 && special1) {special1++; ajuste();}
                if (id == 113) {
                    if (anim == 14) {effets[FLECHE]=2; effets[COUP_GRAPPIN]=2;}
                    if (anim == 0) {effets[FLECHE]=0; effets[COUP_GRAPPIN]=0;}
                }
                if ((id == 115 || id == 116 || id == 117) 
                && special2<0 && gpJeu->getMonde()->regionValue(0)==60*16) {
                    special2++; if (id == 115 && special2==0) animmax=20;}
                if ((id == 116 || id == 117) && h==68 && special2>=0 && special2<6) {
                    special2++;
                    if (special2==6) force=10;
                }
                if (id == 115 && anim == animmax && special2>=0) {
                    special1=0; snipe();
                    special1=1; snipe();
                }
                if ((id == 116 || id == 117) && special2>=7 && special2<12) {
                    special2++;
                    if (special2==11) snipe();
                    if (special2==12) special2=6;
                }
                if (id == 120 && special2 > 0) {
                    if (gpJeu->getJoueur()->getVie() > 0) {
                        special1++;
                        if (special1 >= (4 + (vie / 15))) {snipe(); special1=0; special2=0;}
                    } else special1=0;
                }
                if (id == 124 && anim == 0 && special2 == 0) {
                    special1++;
                    if (special1 > 3) special1 = 0;
                }
                if (id == 126 && special1 == 0 && distance()) {
                    gpJeu->getJoueur()->setBoostGanon(-1);
                }
                if (id == 140 && special1 == 0 && distance() 
                && gpJeu->getJoueur()->getVie() > 0) {
                    gpJeu->getJoueur()->setVie(gpJeu->getJoueur()->getVie()-1);
                }
                if (id == 141) { 
                    if (special2 == 1) {
                        if (anim == 9) {
                            if (getSuivant()->getVie() && getSuivant()->getSuivant()->getVie()) {
                                snipe();
                            } else {
                                int result = (rand()%2);
                                if (result == 0) {
                                    if (getSuivant()->getVie()) {
                                        Ennemi* enn = getSuivant()->getSuivant();
                                        enn->init();
                                        gpJeu->ajouteProjectile(17, direction, enn->x+(enn->w/2)-14, 
                                            enn->y+(enn->h/2)-14, 0);
                                    } else if (getSuivant()->getSuivant()->getVie()) {
                                        Ennemi* enn = getSuivant();
                                        enn->init();
                                        gpJeu->ajouteProjectile(17, direction, enn->x+(enn->w/2)-14, 
                                            enn->y+(enn->h/2)-14, 0);
                                    } else {
                                        Ennemi* enn;
                                        if (rand()%2) enn = getSuivant();
                                        else enn = getSuivant()->getSuivant();
                                        enn->init();
                                        gpJeu->ajouteProjectile(17, direction, enn->x+(enn->w/2)-14, 
                                            enn->y+(enn->h/2)-14, 0);
                                    }
                                } else snipe();
                            }
                        }
                    }
                    if (special2 == 0 && anim == 0) {
                        special2=1; animmax=9; force=80; effets[MAGIE]=2; effets[MORTEL]=2;
                    }
                    if (special2 == 10 && gpJeu->nbEnnemis()==1) {
                        //gpJeu->getJoueur()->setImmo(true);
                        gpJeu->getAudio()->playSound(20);
                        gpJeu->getMonde()->passage(60,81,1);
                        Pnj* zelda = gpJeu->getPnj()->getSuivant()->getSuivant();
                        zelda->setX(60*16+8); zelda->setY(81*16+9); 
                        zelda->setDirection(E); zelda->setImmo(false);
                        special2=11;
                    }
                    if (special2 < 10 && vie == 1) special2++;
                }
                
                
                
                if (invincible > 0) invincible++;
                if (invincible > vinvin) invincible=0;
                if (glace > 0) glace++;
                if (glace >= (maxglace*40)/vanim) glace=0;
                
            }
            if (id == 58 && special1>0) {
                special1-=4;
                if (special1==0) {
                    force=1; for (int k = 0; k < 25; k++) effets[k]=2;
                    typeIA = IA_FONCE;
                }
            }
            if (id == 91 || id == 139) {
                if (special1) {
                    if (distance()) {if (special1<16) special1++;
                    } else {
                        special1--; 
                        if (special1==0) for (int k = 0; k < 25; k++) effets[k]=2;
                    }
                }
                else if (distance()) {special1=1; for (int k = 0; k < 25; k++) effets[k]=0;}
            }
        //}
    }
    if (suivant != NULL) ((Ennemi*)suivant)->draw(gpScreen);
}

void Ennemi::drawArme(SDL_Surface* gpScreen) {
    int phg[2];
    phg[0] = gpJeu->getPhg(0);
    phg[1] = gpJeu->getPhg(1);
    
    SDL_Rect src;
    SDL_Rect dst;
    
    dst.x=x-phg[0]+zonesAttaques->getSuivant()->getZone()->x;
    dst.y=y-phg[1]+zonesAttaques->getSuivant()->getZone()->y;
    src.w = zonesAttaques->getSuivant()->getZone()->w;
    src.h = zonesAttaques->getSuivant()->getZone()->h;
    
    switch (id) {
        case 5 :
            switch (direction) {
                case N : src.x=64; src.y=10; break;
                case S : src.x=69; src.y=10; break;
                case O : src.x=64; src.y=0; break;
                case E : src.x=64; src.y=5; break;
            }
            SDL_BlitSurface(image, &src, gpScreen, &dst);
            break;
        case 44 :
        case 55 :
        case 123 :
        case 134 :
            switch (direction) {
                case N : src.x=88; src.y=14; break;
                case S : src.x=95; src.y=14; break;
                case O : src.x=88; src.y=0; break;
                case E : src.x=88; src.y=7; break;
            }
            SDL_BlitSurface(image, &src, gpScreen, &dst);
            break;
        case 46 :
        case 47 :
        case 48 :
        case 119 :
            switch (direction) {
                case N : src.x=88; src.y=10; break;
                case S : src.x=93; src.y=10; break;
                case O : src.x=88; src.y=0; break;
                case E : src.x=88; src.y=5; break;
            }
            SDL_BlitSurface(image, &src, gpScreen, &dst);
            break;
    }
}

void Ennemi::moveX(int i) {
    moveX(i, vol, nage, spectre);
}

void Ennemi::moveY(int i) {
    if (id==92) return;
    moveY(i, vol, nage, spectre);
}

void Ennemi::moveX(int i, int v, int n, int s) {
    if (id==97 && gpJeu->hasVide(x + gpZoneBase->getZone()->x + i, y + gpZoneBase->getZone()->y, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h)) return;
    if (id==21 && !gpJeu->isWater(x + gpZoneBase->getZone()->x + i, 
        y + gpZoneBase->getZone()->y, gpZoneBase->getZone()->w, 
        gpZoneBase->getZone()->h)) return;
    if (gpJeu->isEnnemi(x + gpZoneBase->getZone()->x + i, y + gpZoneBase->getZone()->y, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h, getListId())) return;
    if (gpJeu->isPnj(x + gpZoneBase->getZone()->x + i, y + gpZoneBase->getZone()->y, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h, getListId())) return;
    if (!gpJeu->isNotFull(x + gpZoneBase->getZone()->x + i, y + gpZoneBase->getZone()->y, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h, v, n, s)) return;
    x+=i;
}

void Ennemi::moveY(int i, int v, int n, int s) {
    if (id==97 && gpJeu->hasVide(x + gpZoneBase->getZone()->x, y + gpZoneBase->getZone()->y + i, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h)) return;
    if (id==21 && !gpJeu->isWater(x + gpZoneBase->getZone()->x, 
        y + gpZoneBase->getZone()->y + i, gpZoneBase->getZone()->w, 
        gpZoneBase->getZone()->h)) return;
    if (gpJeu->isEnnemi(x + gpZoneBase->getZone()->x, y + gpZoneBase->getZone()->y + i, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h, getListId())) return;
    if (gpJeu->isPnj(x + gpZoneBase->getZone()->x, y + gpZoneBase->getZone()->y + i, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h)) return;
    if (!gpJeu->isNotFull(x + gpZoneBase->getZone()->x, y + gpZoneBase->getZone()->y + i, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h, v, n, s)) return;
    y+=i;
}

void Ennemi::reveil() {
    special1 = 1;
}

void Ennemi::transforme() {
    if (id == 141) init();
}

void Ennemi::pousse(Direction dir) {
    switch (dir) {
        case N : for (int i = 0; i < recul; i++) moveY(-1, 1, 1, spectre); break;
        case S : for (int i = 0; i < recul; i++) moveY(1, 1, 1, spectre); break;
        case O : for (int i = 0; i < recul; i++) moveX(-1, 1, 1, spectre); break;
        case E : for (int i = 0; i < recul; i++) moveX(1, 1, 1, spectre); break;
    }
    //rajouter vérif eau/vide
    if (gpJeu->isVide(x+gpZoneBase->getZone()->x,y+gpZoneBase->getZone()->y,
    gpZoneBase->getZone()->w,gpZoneBase->getZone()->h) && !vol && !spectre) {
        vie = 0; gpJeu->getAudio()->playSound(6);
        gpJeu->getJoueur()->setEnnemi(getEnnId());
        gpJeu->ajouteProjectile(15, direction, x+(w/2)-14, y+(h/2)-14, 0);
        gpJeu->testAnim();
        //return;
    }
    if (gpJeu->isWater(x+gpZoneBase->getZone()->x,y+gpZoneBase->getZone()->y,
    gpZoneBase->getZone()->w,gpZoneBase->getZone()->h) && !vol && !nage && !spectre) {
        vie = 0; gpJeu->ajouteProjectile(8, direction, x, y, 0);
        gpJeu->getJoueur()->setEnnemi(getEnnId());
        gpJeu->testAnim();
    }
}

void Ennemi::revie() {
    int oldvie=vie;
    if ((((!isBoss() && !isMiniBoss() && !isBig() 
    && id!=49 && id!=65 && id!=96 && id!=114 && id!=122) || vie > 0) 
    && (id!=89 || !special2)) 
    && (id != 27 || xdep != 249*16+8 || ydep != 24*16)
    && (id != 136 || y!=77*16)) init();
    //else if ((gpJeu->getZone()==23 || gpJeu->getZone()==24) && vie > 0) {
    //    x=xdep; y=ydep; vie=viemax; direction=S;}
    if (id==97 && gpJeu->getZone()==48 && gpJeu->getMonde()->regionValue(1)==30*16) 
        vie = oldvie;
    if (suivant != NULL) getSuivant()->revie();
}

void Ennemi::permute(int val) {
    if (id == 20 || id == 88) {
        special1=val;
    }
    if (suivant != NULL) getSuivant()->permute(val);
}

int Ennemi::getEffet(int i) {return effets[i];}

int Ennemi::getObjets(int i) {return objets[i];}

ZoneRect* Ennemi::getZonesVulnerables() {return zonesVulnerables;}

Ennemi* Ennemi::getSuivant() {return (Ennemi*)suivant;}

void Ennemi::setInvincible(int i) {invincible=i;}

void Ennemi::gele() {glace=1;}

void Ennemi::degele() {glace=0;}

void Ennemi::mort() {
    vie=0;
    if (id == 50) {
        Ennemi* enn = getSuivant();
        while (enn != NULL) {
            if ((enn->getEnnId()==114 || enn->getEnnId()==122) && enn->getVie()) {
                enn->setVie(0);
                gpJeu->ajouteProjectile(15, direction, enn->getX()-6, enn->getY()+2, 0);
            }
            enn = enn->getSuivant();
        }
    }
}

void Ennemi::enerve() {
    if (id == 52 || id == 78) {
        for (int k = 0; k < 25; k++) effets[k]=0;
        typeIA = IA_FONCE;
        special1=3;
        vitesse=2;
        vanim = 120;
    }
    if (id == 101) {
        special1=1;
        effets[EXPLOSION]=2;
    }
    if (id == 103 && special1>-2) {
        int nb_torches=0;
        if (gpJeu->getMonde()->motifValue(242*16,17*16)==1001) nb_torches++;
        if (gpJeu->getMonde()->motifValue(257*16,17*16)==1001) nb_torches++;
        if (gpJeu->getMonde()->motifValue(242*16,27*16)==1001) nb_torches++;
        if (gpJeu->getMonde()->motifValue(257*16,27*16)==1001) nb_torches++;
        if (nb_torches < 4) {
            special1=-1;
            for (int k = 0; k < 25; k++) effets[k]=0;
            zonesVulnerables->getZone()->w=0;
            zonesVulnerables->getZone()->h=0;
            zonesVulnerables->getSuivant()->getZone()->w=0; 
            zonesVulnerables->getSuivant()->getZone()->h=0;
            force=0;
        } else {
            special1=-2;
            special2=-40;
            y+=20;
        }
    }
}

void Ennemi::setVie(int i) {
    if (id == 52 && special1 < 3) {
        special1++;
        if (special1 == 3) gpJeu->poule();
    }
    if (id == 78 && special1 < 3) {
        special1=3; gpJeu->poule();
    }
    if (id == 31) {
        special2++;
        special1 = 1 + special2;
    }
    if (id == 45 && special1 < 3) {
        special1++; 
        if (special1 == 3) {
            zonesVulnerables->getZone()->w=12; zonesVulnerables->getZone()->h=17;
            zonesVulnerables->getZone()->x=27; zonesVulnerables->getZone()->y=39; 
            for (int k = 0; k < 25; k++) effets[k]=2;
        }
        return;
    }
    if (id == 50) { 
        //if (effets[FLECHE]==2 && i < 100) effets[FLECHE]=0;
        if ((special2==2 || special2==5) && 
        (getSuivant()->getY()==24*16 || !getSuivant()->getVie()))  {
            Ennemi* enn = getSuivant();
            while (enn != NULL) {
                if (enn->getEnnId()==114 && enn->getVie()) {
                    enn->setVie(0);
                    gpJeu->ajouteProjectile(15, direction, enn->getX()-6, enn->getY()+2, 0);
                }
                enn = enn->getSuivant();
            }
            special1=0; special2++;
        }
        if ((i < 200 && special2==0) || (i < 100 && special2==3)) {
            special1=0; special2++;
            Ennemi* enn = getSuivant();
            while (enn != NULL) {
                if (enn->getEnnId()==114) enn->init();
                enn = enn->getSuivant();
            }
        }
        if (i<=1) {
            i=1; for (int k = 0; k < 25; k++) effets[k]=0; effets[MORTEL]=2;
            special1=0; special2=7;
            Ennemi* enn = getSuivant();
            while (enn != NULL) {
                if (enn->getEnnId()==122) enn->setVie(viemax);
                enn = enn->getSuivant();
            }
        }
    }
    if (id == 57) {
        Ennemi* enn = getSuivant();
        if (i <= 0) {
            for (int j=0; j <3; j++) {
                if (enn->vie) {
                    gpJeu->ajouteProjectile(15, direction, 
                        enn->x+(enn->w/2)-14, enn->y+(enn->h/2)-14, 0);
                    enn->init();
                }
                enn=enn->getSuivant();
            }
        }
        enn = getSuivant()->getSuivant()->getSuivant()->getSuivant();
        if (i <= 2 && enn->vie) {
            enn->vie=0;
            gpJeu->ajouteProjectile(15, direction, 
                enn->x+(enn->w/2)-14, enn->y+(enn->h/2)-14, 0);
            enn = enn->getSuivant();
            enn->vie=0;
            gpJeu->ajouteProjectile(15, direction, 
                enn->x+(enn->w/2)-14, enn->y+(enn->h/2)-14, 0);
            for (int i = 0; i < 4; i++) gpJeu->getMonde()->setMurs(89*2+i,24*2,0);
        }
    }
    if (id == 62 && special2==0) {
        if (i > 0 && i <= 5) {
            special1=0;special2=1;recul=0;typeIA=IA_RIEN;force=0;
            for (int k = 0; k < 25; k++) effets[k]=0; effets[EXPLOSION]=2;
            zonesVulnerables->getZone()->w=w; zonesVulnerables->getZone()->h=16;
            zonesVulnerables->getZone()->x=0; zonesVulnerables->getZone()->y=21; 
        }
    }
    if(id == 63 && special2==0 && vie < 11  && vie > 0) {
        special2=1; x-=12; w=71; h=60; y-=8; force=12;
        if (x < gpJeu->getMonde()->regionValue(0)) x = gpJeu->getMonde()->regionValue(0);
        zonesVulnerables->getZone()->x=25; zonesVulnerables->getZone()->h=60;
        zonesVulnerables->getSuivant()->getZone()->w=71; 
        zonesVulnerables->getSuivant()->getZone()->h=40;
        zonesVulnerables->getSuivant()->getZone()->x=0; 
        zonesVulnerables->getSuivant()->getZone()->y=1; 
        zonesAttaques->getZone()->x=25; zonesAttaques->getZone()->h=60;
        zonesAttaques->getSuivant()->getZone()->w=71; 
        zonesAttaques->getSuivant()->getZone()->h=40;
        zonesAttaques->getSuivant()->getZone()->x=0; 
        zonesAttaques->getSuivant()->getZone()->y=1; 
    }
    if (id == 66 && i <= 0) {
        Ennemi* enn = getSuivant();
        enn->vie=0;
        for (int z = 0; z < 4; z++) {
            enn = enn->getSuivant();
            enn->vie=0;
        }
    }
    if (id == 73 && getSuivant()->y==-152 && vie < 50) getSuivant()->y++;
    if (id == 75) {
        if (i<=0) {
            i=1;
            special2=1;
            special1=0;
            typeIA=IA_RIEN;
            force=0;
            effets[COUP_EPEE]=0; effets[EPEE_SPIN]=0;
        }
        //gpJeu->ecrit(183);
        if (i<=75) vitesse=2; else vitesse=1;
    }
    
    if (id == 89 && (gpJeu->getZone() != 57 || gpJeu->getMonde()->regionValue(1) != 0)) {
        if (i<=0) {
            i=1;
            special2=1;
            special1=0;
            typeIA=IA_RIEN;
            force=0;
            for (int k = 0; k < 25; k++) effets[k]=0;
            if (gpJeu->getZone() != 57) {
                gpJeu->testAnim();
                gpJeu->getAudio()->playSpecial(3);
                gpJeu->getStatut()->setJauge(false);
                gpJeu->ecrit(800);
            } else {
                if (gpJeu->getMonde()->regionValue(1) == 15*16) gpJeu->ecrit(1097);
            }
        }
    }
    
    if ((id == 93 || id == 98 || id == 99) && i > 0) {
        zonesVulnerables->getZone()->w=0; zonesVulnerables->getZone()->h=0;
        if (id == 99) {
            special1=96; special2=0; force=0;
        }
    }
    
    if (id == 94) {
        if (i < viemax/2) vitesse = 2;
        if (i < viemax/4) vitesse = 3;
    }
    
    if ((id == 95 || id ==105) && i<=0) {
        Ennemi* enn = getSuivant();
        while (enn != NULL) {
            if (enn->getEnnId()==96) {
                enn->setVie(0);
                gpJeu->ajouteProjectile(15, direction, enn->getX()-6, enn->getY()-6, 0);
                if (id == 105) gpJeu->getMonde()->setValeur(enn->getX(),enn->getY(),5137,0);
            }
            enn = enn->getSuivant();
        }
    }
    
    if (id == 99 && i <= 0) {
        Ennemi* enn = getSuivant();
        while (enn != NULL) {
            if (enn->getEnnId()==100) {
                enn->setVie(0);
                gpJeu->ajouteProjectile(15, direction, enn->getX()+18, enn->getY()+1, 0);
            }
            enn = enn->getSuivant();
        }
    }
    
    if (id == 104 && i <= 0) {
        Ennemi* enn = getSuivant();
        while (enn != NULL) {
            if (enn->getEnnId()==49) {
                enn->setVie(0);
                gpJeu->ajouteProjectile(15, direction, enn->getX()-6, enn->getY()-6, 0);
                gpJeu->getMonde()->setValeur(enn->getX(),enn->getY(),5000,0);
            }
            enn = enn->getSuivant();
        }
    }
    
    if (id == 109 && i > 0) {
        vitesse = 1 + (((viemax-vie)*4) / viemax);
    }
    
    if (id == 111 && i<=0) {
        Ennemi* enn = getSuivant();
        while (enn != NULL) {
            if (enn->getEnnId()==65) {
                enn->setVie(0);
                gpJeu->ajouteProjectile(15, direction, enn->getX()-6, enn->getY()-6, 0);
            }
            enn = enn->getSuivant();
        }
    }
    
    if (id == 113 && i<=0) {
        Ennemi* enn = getSuivant();
        while (enn != NULL) {
            if (enn->getEnnId()==114 && enn->getVie()) {
                enn->setVie(0);
                gpJeu->ajouteProjectile(15, direction, enn->getX()-6, enn->getY()+2, 0);
            }
            enn = enn->getSuivant();
        }
    }
    
    if (id == 115 && i>0) {
        if (i < viemax/4 && animmax > 6) {animmax=7; anim=0;}
        else if (i < viemax/2 && animmax > 10) {animmax=10; anim=0;}
    }
    if (id == 115 && i<=0) {
        Ennemi* enn = getSuivant();
        while (enn != NULL) {
            if ((enn->getEnnId()==116 || enn->getEnnId()==117) && enn->getVie()) {
                enn->setVie(0);
                gpJeu->ajouteProjectile(15, direction, enn->getX()+25, enn->getY()+20, 0);
            }
            enn = enn->getSuivant();
        }
    }
    
    if (id == 118 && i<=0) {
        gpJeu->ajouteProjectile(140, direction, x-9, y-8, 0);
    }
    
    if (id == 76 && i<=0) {
        Ennemi* enn = getSuivant();
        while (enn != NULL) {
            if (enn->getEnnId()==49 && enn->getVie()) {
                enn->setVie(0);
                gpJeu->ajouteProjectile(15, direction, enn->getX()-6, enn->getY()-6, 0);
            }
            enn = enn->getSuivant();
        }
    }
    if (id == 120 && i<=0) gpJeu->getPnj()->getSuivant()->setVie(1);
    if (id == 124) {
        for (int k = 0; k < 25; k++) effets[k]=0; i=vie;
        special2=1;
        typeIA = IA_RIEN;
        gpJeu->getAudio()->playSound(7);
        //vérifie que les 4 sont ok
        int ok[] = {0,0,0,0};
        int nb = 0;
        Ennemi* enn = gpJeu->getEnnemi()->getSuivant();
        while (enn != NULL) {
            if (enn->isActif() && enn->id == 124 && enn->special2 == 1) {
                if (ok[enn->special1] == 1) gpJeu->getJoueur()->setCoffre(12,13,3);
                ok[enn->special1] = 1;
                nb++;
            }
            enn = enn->getSuivant();
        }
        if (nb == 4 && gpJeu->getJoueur()->getCoffre(12,13) != 3) 
            gpJeu->getJoueur()->setCoffre(12,13,2);
    }
    if (id == 125) {
        for (int k = 0; k < 25; k++) effets[k]=0; i=vie;
        special2=1;
        typeIA = IA_RIEN;
        gpJeu->getAudio()->playSound(7);
        
        //421
        if (gpJeu->getMonde()->regionValue(0)==40*16) {
            int ok[] = {0,0,0};
            int nb = 0;
            int ind = 0;
            Ennemi* enn = gpJeu->getEnnemi()->getSuivant();
            while (enn != NULL) {
                if (enn->isActif() && enn->id == 125 && enn->special2 == 1) {
                    switch(enn->special1+1) {
                        case 4 : ind = 0; break;
                        case 2 : ind = 1; break;
                        case 1 : ind = 2; break;
                        default : ind = -1;
                    }
                    if (ind > -1) {
                        if (ok[ind] == 1) gpJeu->getJoueur()->setCoffre(12,13,3);
                        ok[ind] = 1;
                        nb++;
                    } else gpJeu->getJoueur()->setCoffre(12,13,3);
                }
                enn = enn->getSuivant();
            }
            if (nb == 3 && gpJeu->getJoueur()->getCoffre(12,13) != 3) 
                gpJeu->getJoueur()->setCoffre(12,13,2);
        }
        
        
        //3-2
        if (gpJeu->getMonde()->regionValue(0)==0) {
            int old = 0;
            int tot = 0;
            int nb = 0;
            Ennemi* enn = gpJeu->getEnnemi()->getSuivant();
            while (enn != NULL) {
                if (enn->isActif() && enn->id == 125 && enn->special2 == 1) { 
                    if (enn->x > 9*16 || enn->y > 81*16) {
                        tot += (enn->special1+1); nb++;}
                    else old += (enn->special1+1);
                }
                enn = enn->getSuivant();
            }
            if (old < tot) gpJeu->getJoueur()->setCoffre(12,13,2);
            else if (nb == 2) gpJeu->getJoueur()->setCoffre(12,13,3);
        }
        
        //caisses
        if (gpJeu->getMonde()->regionValue(0)==120*16) {
            Caisse* caisse = gpJeu->getCaisse()->getSuivant();
            while (caisse != NULL) {
                if (caisse->isActif() && caisse->getNombre() == 0) { 
                    caisse->setNombre(special1+1);
                    break;
                }
                caisse = caisse->getSuivant();
            }
        }
        
        //+/*
        if (gpJeu->getMonde()->regionValue(0)==80*16) {
            bool ok = true;
            int somme = 0;
            int mult = 0;
            Ennemi* enn = gpJeu->getEnnemi()->getSuivant();
            while (enn != NULL) {
                if (enn->isActif() && enn->id == 125) {
                    if (enn->special2 == 0) ok = false;
                    else {
                        if (enn->x < 85*16 && enn->y < 21*16) mult = enn->special1+1;
                        else somme += (enn->special1+1);
                    }
                }
                enn = enn->getSuivant();
            }
            if (ok) {
                gpJeu->getJoueur()->setCoffre(12,13,2 + somme*mult);
            }
        }
    }
    
    if (id == 127) {
        gpJeu->getAudio()->playSound(7);
        if (i <= 0) {
            gpJeu->ajouteProjectile(15, direction, x+26, y+18, 0);
            gpJeu->getJoueur()->setEnnemi(id);
        }
    }
    
    if (id == 135 && special2==0) {
        if (i > 0 && i <= 10) {
            special1=0;special2=1;recul=0;typeIA=IA_RIEN;force=0;
            for (int k = 0; k < 25; k++) effets[k]=0; effets[EXPLOSION]=2;
            zonesVulnerables->getZone()->w=w; zonesVulnerables->getZone()->h=16;
            zonesVulnerables->getZone()->x=0; zonesVulnerables->getZone()->y=21; 
        }
    }
    
    if (id == 141 && special2 > 0 && special2 < 13) {
        if (i<=1) {i=1; for (int k = 0; k < 25; k++) effets[k]=0; effets[ENNEMI]=2;}
        if (special2 == 12) {
            effets[COUP_EPEE]=2;
            effets[EPEE_SPIN]=2;
            special2=13;
            gpJeu->ecrit(1346);
            zonesVulnerables->getZone()->h=72; zonesVulnerables->getZone()->y=56;
            zonesAttaques->getZone()->h=72; zonesAttaques->getZone()->y=56;
        }
        if (special2 == 11) {
            gpJeu->getAudio()->playSound(20);
            gpJeu->getMonde()->passage(80,81,1);
            Pnj* ganondorf = gpJeu->getPnj()->getSuivant()->getSuivant()->getSuivant();
            ganondorf->setX(80*16-20-8+4); ganondorf->setY(81*16+5); 
            ganondorf->setDirection(O); ganondorf->setImmo(false);
            special2=12;
            zonesVulnerables->getZone()->h=96; zonesVulnerables->getZone()->y=32;
            zonesAttaques->getZone()->h=96; zonesAttaques->getZone()->y=32;
        }
    }
    
    vie=i;
    if (vie < 0) vie = 0;
    if (vie > viemax) vie = viemax;
}

void Ennemi::releve() {
    if (id != 89) return;
    special2=2;
}

void Ennemi::capture() {
    Joueur* j = gpJeu->getJoueur();
    if (id==75 && j->hasObjet(O_MASQUE)==1 && special2) {
        gpJeu->trouve(C_MASQUE_ONI);
        vie=0;
        gpJeu->getAudio()->playSound(8);
        gpJeu->ajouteProjectile(15, direction, x+(w/2)-14, y+(h/2)-14, 0);
        gpJeu->donneObjet(this);
    }
}

void Ennemi::ajuste() {
    switch(id) {
        case 2 :
            if (direction==N || direction==S) {
                zonesAttaques->getZone()->x=0;
                zonesAttaques->getZone()->w=21;
            }
            else {
                zonesAttaques->getZone()->x=3;
                zonesAttaques->getZone()->w=16;
            }
            break;
        case 5 :
            switch(direction) {
                case N : 
                    zonesAttaques->getSuivant()->getZone()->w=5;
                    zonesAttaques->getSuivant()->getZone()->h=13;
                    zonesAttaques->getSuivant()->getZone()->x=12;
                    zonesAttaques->getSuivant()->getZone()->y=4-3*anim;
                    break;
                case S : 
                    zonesAttaques->getSuivant()->getZone()->w=5;
                    zonesAttaques->getSuivant()->getZone()->h=13;
                    zonesAttaques->getSuivant()->getZone()->x=0;
                    zonesAttaques->getSuivant()->getZone()->y=15+4*anim;
                    break;
                case O : 
                    zonesAttaques->getSuivant()->getZone()->w=13;
                    zonesAttaques->getSuivant()->getZone()->h=5;
                    zonesAttaques->getSuivant()->getZone()->x=-4-5*anim;
                    zonesAttaques->getSuivant()->getZone()->y=19;
                    break;
                case E : 
                    zonesAttaques->getSuivant()->getZone()->w=13;
                    zonesAttaques->getSuivant()->getZone()->h=5;
                    zonesAttaques->getSuivant()->getZone()->x=7+5*anim;
                    zonesAttaques->getSuivant()->getZone()->y=19;
                    break;
            }
            break;
        case 13 :
            switch (anim) {
                case 0 : zonesAttaques->getZone()->w=24; zonesAttaques->getZone()->x=4; break;
                case 1 : zonesAttaques->getZone()->w=32; zonesAttaques->getZone()->x=0; break;
                case 2 : zonesAttaques->getZone()->w=18; zonesAttaques->getZone()->x=7; break;
            }
            break;
        case 15 :
            if (direction!=N) {zonesAttaques->getZone()->y=5; zonesAttaques->getZone()->h=26;}
            else {zonesAttaques->getZone()->y=0; zonesAttaques->getZone()->h=31;}
            break;
        case 19 :
            switch (anim) {
                case 0 : gpZoneBase->getZone()->w=64; gpZoneBase->getZone()->x=0; break;
                case 1 : gpZoneBase->getZone()->w=44; gpZoneBase->getZone()->x=10; break;
                case 2 : gpZoneBase->getZone()->w=22; gpZoneBase->getZone()->x=21; break;
            }
            break;
        case 25 :
            if (direction==N || direction==S) {
                zonesAttaques->getZone()->x=0; zonesAttaques->getZone()->w=28;}
            else {zonesAttaques->getZone()->x=6; zonesAttaques->getZone()->w=16;}
            break;
        case 33 :
        case 38 :
            if (direction==N || direction==S) {
                zonesAttaques->getZone()->x=0; zonesAttaques->getZone()->w=22;}
            else {zonesAttaques->getZone()->x=2; zonesAttaques->getZone()->w=18;}
            break;
        case 34 :
        case 39 :
            if (direction==N || direction==S) {
                zonesAttaques->getZone()->x=0; zonesAttaques->getZone()->w=24;}
            else {zonesAttaques->getZone()->x=4; zonesAttaques->getZone()->w=16;}
            break;
        case 44 :
        case 55 :
        case 123 :
        case 134 :
            if (direction==N || direction==S) {
                zonesAttaques->getZone()->x=0; zonesAttaques->getZone()->w=22;}
            else {zonesAttaques->getZone()->x=3; zonesAttaques->getZone()->w=16;}
            switch(direction) {
                case N : 
                    zonesAttaques->getSuivant()->getZone()->w=7;
                    zonesAttaques->getSuivant()->getZone()->h=15;
                    zonesAttaques->getSuivant()->getZone()->x=15;
                    zonesAttaques->getSuivant()->getZone()->y=-6+7*anim;
                    break;
                case S : 
                    zonesAttaques->getSuivant()->getZone()->w=7;
                    zonesAttaques->getSuivant()->getZone()->h=15;
                    zonesAttaques->getSuivant()->getZone()->x=0;
                    zonesAttaques->getSuivant()->getZone()->y=17+3*anim;
                    break;
                case O : 
                    zonesAttaques->getSuivant()->getZone()->w=15;
                    zonesAttaques->getSuivant()->getZone()->h=7;
                    zonesAttaques->getSuivant()->getZone()->x=-12+5*anim;
                    zonesAttaques->getSuivant()->getZone()->y=14+2*anim;
                    break;
                case E : 
                    zonesAttaques->getSuivant()->getZone()->w=15;
                    zonesAttaques->getSuivant()->getZone()->h=7;
                    zonesAttaques->getSuivant()->getZone()->x=19-5*anim;
                    zonesAttaques->getSuivant()->getZone()->y=14+2*anim;
                    break;
            }
            break;
        case 45 :
            switch(anim%2) {
                case 0 : 
                    zonesAttaques->getSuivant()->getZone()->y=67;
                    zonesAttaques->getSuivant()->getSuivant()->getZone()->y=59;
                    break;
                case 1 : 
                    zonesAttaques->getSuivant()->getZone()->y=59;
                    zonesAttaques->getSuivant()->getSuivant()->getZone()->y=67;
                    break;
            }
            break;
        case 46 :
        case 47 :
        case 48 :
        case 119 :
            if (direction==N || direction==S) {
                zonesAttaques->getZone()->x=0; zonesAttaques->getZone()->w=22;}
            else {zonesAttaques->getZone()->x=2; zonesAttaques->getZone()->w=18;}
            switch(direction) {
                case N : 
                    zonesAttaques->getSuivant()->getZone()->w=5;
                    zonesAttaques->getSuivant()->getZone()->h=16+((int)(id/48));
                    if (id==119) zonesAttaques->getSuivant()->getZone()->h=17;
                    zonesAttaques->getSuivant()->getZone()->x=16;
                    zonesAttaques->getSuivant()->getZone()->y=-6+7*anim;
                    break;
                case S : 
                    zonesAttaques->getSuivant()->getZone()->w=5;
                    zonesAttaques->getSuivant()->getZone()->h=16+((int)(id/48));
                    if (id==119) zonesAttaques->getSuivant()->getZone()->h=17;
                    zonesAttaques->getSuivant()->getZone()->x=0;
                    zonesAttaques->getSuivant()->getZone()->y=21+anim-((int)(id/48));
                    if (id==119) zonesAttaques->getSuivant()->getZone()->y=20+anim;
                    break;
                case O : 
                    zonesAttaques->getSuivant()->getZone()->w=16+((int)(id/48));
                    if (id==119) zonesAttaques->getSuivant()->getZone()->w=17;
                    zonesAttaques->getSuivant()->getZone()->h=5;
                    zonesAttaques->getSuivant()->getZone()->x=-12+3*anim-((int)(id/48));
                    if (id==119) zonesAttaques->getSuivant()->getZone()->x=-13+3*anim;
                    zonesAttaques->getSuivant()->getZone()->y=16+2*anim;
                    break;
                case E : 
                    zonesAttaques->getSuivant()->getZone()->w=16+((int)(id/48));
                    if (id==119) zonesAttaques->getSuivant()->getZone()->w=17;
                    zonesAttaques->getSuivant()->getZone()->h=5;
                    zonesAttaques->getSuivant()->getZone()->x=18-3*anim;
                    zonesAttaques->getSuivant()->getZone()->y=16+2*anim;
                    break;
            }
            break;
        case 50 :
            switch(direction) {
                case N : zonesAttaques->getZone()->x=7; zonesAttaques->getZone()->w=38; break;
                case S : zonesAttaques->getZone()->x=4*anim; zonesAttaques->getZone()->w=48; 
                    break;
                default : break;
            }
            break;
        case 60 :
            switch(direction) {
                case N : 
                    zonesAttaques->getZone()->x=0; zonesAttaques->getZone()->y=11;
                    zonesAttaques->getZone()->w=36; zonesAttaques->getZone()->h=28;
                    zonesAttaques->getSuivant()->getZone()->x=9;
                    zonesAttaques->getSuivant()->getZone()->y=39;
                    zonesAttaques->getSuivant()->getZone()->w=32;
                    zonesAttaques->getSuivant()->getZone()->h=24;
                    zonesVulnerables->getZone()->x=9; zonesVulnerables->getZone()->y=39;
                    zonesVulnerables->getZone()->w=32; zonesVulnerables->getZone()->h=24;
                    break;
                case S : 
                    zonesAttaques->getZone()->x=0; zonesAttaques->getZone()->y=0;
                    zonesAttaques->getZone()->w=50; zonesAttaques->getZone()->h=36;
                    zonesAttaques->getSuivant()->getZone()->x=9;
                    zonesAttaques->getSuivant()->getZone()->y=36;
                    zonesAttaques->getSuivant()->getZone()->w=32;
                    zonesAttaques->getSuivant()->getZone()->h=26;
                    zonesVulnerables->getZone()->x=9; zonesVulnerables->getZone()->y=36;
                    zonesVulnerables->getZone()->w=32; zonesVulnerables->getZone()->h=26;
                    break;
                case O : 
                    zonesAttaques->getZone()->x=4; zonesAttaques->getZone()->y=0;
                    zonesAttaques->getZone()->w=26; zonesAttaques->getZone()->h=30;
                    zonesAttaques->getSuivant()->getZone()->x=6;
                    zonesAttaques->getSuivant()->getZone()->y=30;
                    zonesAttaques->getSuivant()->getZone()->w=39;
                    zonesAttaques->getSuivant()->getZone()->h=32;
                    zonesVulnerables->getZone()->x=6; zonesVulnerables->getZone()->y=30;
                    zonesVulnerables->getZone()->w=39; zonesVulnerables->getZone()->h=32;
                    break;
                case E : 
                    zonesAttaques->getZone()->x=20; zonesAttaques->getZone()->y=0;
                    zonesAttaques->getZone()->w=26; zonesAttaques->getZone()->h=30;
                    zonesAttaques->getSuivant()->getZone()->x=5;
                    zonesAttaques->getSuivant()->getZone()->y=30;
                    zonesAttaques->getSuivant()->getZone()->w=39;
                    zonesAttaques->getSuivant()->getZone()->h=32;
                    zonesVulnerables->getZone()->x=5; zonesVulnerables->getZone()->y=30;
                    zonesVulnerables->getZone()->w=39; zonesVulnerables->getZone()->h=32;
                    break;
            }
            break;
        case 77 :
        case 138 :
            if (direction==N || direction==S) {
                zonesAttaques->getZone()->x=0; zonesAttaques->getZone()->w=22;}
            else {zonesAttaques->getZone()->x=3; zonesAttaques->getZone()->w=16;}
            switch(direction) {
                case N : 
                    zonesAttaques->getZone()->x=12+2*anim;
                    zonesAttaques->getZone()->y=4*anim;
                    zonesAttaques->getZone()->w=19-4*anim;
                    zonesAttaques->getZone()->h=30-4*anim;
                    zonesVulnerables->getZone()->x=12+2*anim;
                    zonesVulnerables->getZone()->y=4*anim;
                    zonesVulnerables->getZone()->w=19-4*anim;
                    zonesVulnerables->getZone()->h=30-4*anim;
                    break;
                case S : 
                    zonesAttaques->getZone()->x=14-anim;
                    zonesAttaques->getZone()->y=4*anim;
                    zonesAttaques->getZone()->w=15+2*anim;
                    zonesAttaques->getZone()->h=30-4*anim;
                    zonesVulnerables->getZone()->x=14-anim;
                    zonesVulnerables->getZone()->y=4*anim;
                    zonesVulnerables->getZone()->w=15+2*anim;
                    zonesVulnerables->getZone()->h=30-4*anim;
                    break;
                case O : 
                    zonesAttaques->getZone()->x=0;
                    zonesAttaques->getZone()->y=4-anim;
                    zonesAttaques->getZone()->w=42-3*anim;
                    zonesAttaques->getZone()->h=26+anim;
                    zonesVulnerables->getZone()->x=0;
                    zonesVulnerables->getZone()->y=4-anim;
                    zonesVulnerables->getZone()->w=42-3*anim;
                    zonesVulnerables->getZone()->h=26+anim;
                    break;
                case E : 
                    zonesAttaques->getZone()->x=3*anim;
                    zonesAttaques->getZone()->y=4-anim;
                    zonesAttaques->getZone()->w=42-3*anim;
                    zonesAttaques->getZone()->h=26+anim;
                    zonesVulnerables->getZone()->x=3*anim;
                    zonesVulnerables->getZone()->y=4-anim;
                    zonesVulnerables->getZone()->w=42-3*anim;
                    zonesVulnerables->getZone()->h=26+anim;
                    break;
            }
            break;
        case 87 :
            zonesAttaques->getZone()->x=13-13*anim;
            zonesAttaques->getZone()->w=32+26*anim;
            break;
        case 89 :
            if (direction==N || direction==S) {
                zonesAttaques->getZone()->x=0; zonesAttaques->getZone()->w=20;
                zonesVulnerables->getZone()->x=0; zonesVulnerables->getZone()->w=20;}
            else {zonesAttaques->getZone()->x=0; zonesAttaques->getZone()->w=18;
                zonesVulnerables->getZone()->x=0; zonesVulnerables->getZone()->w=18;}
            break;
        case 105 :
            if (special1==2) {
                type_att=MARTEAU;
                switch (direction) {
                    case N :
                        zonesAttaques->getZone()->h=80; 
                        zonesAttaques->getZone()->y=0; break;
                    case S :
                        zonesAttaques->getZone()->y=16;
                        zonesAttaques->getZone()->h=72; break;
                    case O :
                        zonesAttaques->getZone()->w=72; 
                        zonesAttaques->getZone()->x=0; break;
                    case E :
                        zonesAttaques->getZone()->x=8;
                        zonesAttaques->getZone()->w=72; break;
                }
            } else {
                type_att=ENNEMI;
                zonesAttaques->getZone()->w=64; zonesAttaques->getZone()->h=64;
                zonesAttaques->getZone()->x=8; zonesAttaques->getZone()->y=16;
            }
            break;
        case 108 :
            switch (anim) {
                case 0 :
                    zonesAttaques->getZone()->w=30; zonesAttaques->getZone()->h=33;
                    zonesAttaques->getZone()->x=6; zonesAttaques->getZone()->y=0;
                    break;
                case 1 :
                    zonesAttaques->getZone()->w=33; zonesAttaques->getZone()->h=28;
                    zonesAttaques->getZone()->x=3; zonesAttaques->getZone()->y=7;
                    if (direction%2 == 1) zonesAttaques->getZone()->x=6;
                    break;
                case 2 :
                    zonesAttaques->getZone()->w=42; zonesAttaques->getZone()->h=21;
                    zonesAttaques->getZone()->x=0; zonesAttaques->getZone()->y=8;
                    break;
            }
            break;
    }
}

void Ennemi::regard() {
    //if (typeEnn == E_MONO_DIR) return;
    Joueur* gpJoueur = gpJeu->getJoueur();
    int ennCX = x + gpZoneBase->getZone()->x + (gpZoneBase->getZone()->w/2);
    int ennCY = y + gpZoneBase->getZone()->y + (gpZoneBase->getZone()->h);
    int linkCX = gpJoueur->getX() + 8;
    int linkCY = gpJoueur->getY() + 24;
    int difx = ennCX - linkCX;
    int dify = ennCY - linkCY;
    
    if (abs(difx) > abs(dify) || typeEnn == E_PROFIL) {
        if (difx>0) direction=O;
        else direction=E;
    }
    else {
        if (dify>0) direction=N;
        else direction=S;
    }
    
    if (id == 50) {
	if (dify>0) direction = N; else direction = S;
    }
    
    ajuste();
}

void Ennemi::hautbas() {
    int phg[2];
    phg[0] = gpJeu->getPhg(0);
    phg[1] = gpJeu->getPhg(1);
    
    int old = y;
    switch (direction) {
        case N :
            moveY(-1);
            if (old == y) {
                direction = S;
                if (x+w > phg[0] && x < phg[0] + 320 && y+h > phg[1] && y < phg[1] + 240)
                    gpJeu->getAudio()->playSound(21);
            }
            break;
        case S :
            moveY(1);
            if (old == y) {
                direction = N;
                if (x+w > phg[0] && x < phg[0] + 320 && y+h > phg[1] && y < phg[1] + 240)
                    gpJeu->getAudio()->playSound(21);
            }
            break;
        default : break;
    }
}

void Ennemi::special() {
    if (id==51) {
        if (special1>0) special1-=4;
        if (anim>31 && anim <36)
        gpJeu->testDegat(x + zonesAttaques->getZone()->x, 
            y + zonesAttaques->getZone()->y , 
            zonesAttaques->getZone()->w, 
            zonesAttaques->getZone()->h, 
            RETOUR, force, direction);
        if (anim>35) special1+=8;
    }
}

void Ennemi::IAZoraG() {
    int randomValue;
    int a;
    int b;
    
    special1++;
    if (special1>20) special1=0;
    
    switch (special1) {
        case 4 : 
            if (id == 93) {
                randomValue = (int)((float)rand() / RAND_MAX * (4));
                x = 16*(326+6*(randomValue%2));
                y = 16*(49+5*(randomValue/2))+8;
            }
            else if (id == 98) {
                randomValue = (int)((float)rand() / RAND_MAX * (3));
                x = 16*(83+6*(randomValue%3));
            }
            break;
        case 8 :
            gpJeu->ajouteProjectile(8, direction, x+8, y+8, 0);
            if (special2) {
                if (id == 93) {
                    a = (x==326*16) ? (332*16) : (326*16);
                    b = (y==49*16+8) ? (54*16+8) : (49*16+8);
                    gpJeu->ajouteProjectile(8, direction, a+8, b+8, 0);
                }
                else if (id == 98) {
                    if (x==89*16) a=95*16;
                    else if (x==95*16) a=83*16;
                    else a=89*16;
                    gpJeu->ajouteProjectile(8, direction, a+8, y+8, 0);
                    if (special2==2) {
                        if (x==89*16) a=83*16;
                        else if (x==95*16) a=89*16;
                        else a=95*16;
                        gpJeu->ajouteProjectile(8, direction, a+8, y+8, 0);
                    }
                }
            }
            zonesAttaques->getZone()->w=32; zonesAttaques->getZone()->h=32;
            zonesVulnerables->getZone()->w=32; zonesVulnerables->getZone()->h=32;
            break;
        case 11 : case 13 : case 15 : snipe(); break;
        case 17 :
            gpJeu->ajouteProjectile(8, direction, x+8, y+8, 0);
            if (special2) {
                if (id == 93) {
                    a = (x==326*16) ? (332*16) : (326*16);
                    b = (y==49*16+8) ? (54*16+8) : (49*16+8);
                    gpJeu->ajouteProjectile(8, direction, a+8, b+8, 0);
                }
                else if (id == 98) {
                    if (x==89*16) a=95*16;
                    else if (x==95*16) a=83*16;
                    else a=89*16;
                    gpJeu->ajouteProjectile(8, direction, a+8, y+8, 0);
                    if (special2==2) {
                        if (x==89*16) a=83*16;
                        else if (x==95*16) a=89*16;
                        else a=95*16;
                        gpJeu->ajouteProjectile(8, direction, a+8, y+8, 0);
                    }
                }
            }
            if (vie < 4 && id == 93) special2=1;
            if (vie <= 8 && id == 98) special2=1;
            if (vie <= 4 && id == 98) special2=2;
            zonesAttaques->getZone()->w=0; zonesAttaques->getZone()->h=0;
            zonesVulnerables->getZone()->w=0; zonesVulnerables->getZone()->h=0;
            break;
    }
    
    //de 0 à 3, ne fait rien
    //de 4 à 7, tourbillon
    //de 8 à 9, sorti de l'eau
    //de 10 à 16 bouche ouverte, tire en 11, 13, 15
    //de 17 à 20 tourbillon
}

void Ennemi::IACrabe() {
    //si special1=0, va chercher pierre
    //si bien placé, ramasse pierre avec special1=1
    //si special1=2, pierre rammassée, crâbe va vers Link
    //si au dessus de Link, lance pierre, special1=0
    if (special1==0) {
        if (x>354*16+4) x=354*16+4;
        if (x==354*16+4) {special1=1; lastAnimTime = SDL_GetTicks();}
        for (int i = 0; i < vitesse; i ++) if (x<354*16+4) x++;
    }
    else if (special1==2) {
        Joueur* gpJoueur = gpJeu->getJoueur();
        for (int i = 0; i < vitesse; i ++) {
            if (gpJoueur->getX()>x+8 && x<354*16+4) x++;
            if (gpJoueur->getX()<x+8 && x>344*16-8) x--;
        }
        if (gpJoueur->getVie()<=0) return;
        if (gpJoueur->getX()==x+8 
        || (x==354*16+4 && gpJoueur->getX()>x+8) 
        || (x==344*16-8 && gpJoueur->getX()<x+8)) {
            special1=0;
            gpJeu->getAudio()->playSound(35);
            gpJeu->ajouteProjectile(29,S,x+8,y+32,4);
        }
    }
}

void Ennemi::IAImp() {
    if (invincible) {special1=0; special2=0; return;}
    
    //on compte les interrupteurs encore actifs
    int total = 0;
    int random;
    Monde* gpMonde = gpJeu->getMonde();
    if (gpMonde->motifValue(124*16,33*16)==1004) total++;
    if (gpMonde->motifValue(129*16,33*16)==1004) total++;
    if (gpMonde->motifValue(135*16,33*16)==1004) total++;
    
    //si aucun n'est actif, fait des vas et viens
    if ((total==0 || special1>=10) && (special1<1 || special1>=10)) {
        if (special1==0) {
            random = rand()%100;
            if (random==7) special1=10;
            else {
                int oldx = x;
                if (direction==O) {moveX(-1); if (x == oldx) direction=E;}
                else {moveX(1); if (x == oldx) direction=O;}
            }
        }
        else {
            if (special1>=16) special1=0;
        }
    }//sinon, va vers un interrupteur
    else {
        //quand il reste des interrupteur, special1 => début de saut
        if (special1 == 0) {
            // special2 indique l'interrupteur visé ( 1, 2 ou 3 )
            if (special2 == 0) {
                if (total == 1) {
                    if (gpMonde->motifValue(124*16,33*16)==1004) special2=1;
                    if (gpMonde->motifValue(129*16,33*16)==1004) special2=2;
                    if (gpMonde->motifValue(135*16,33*16)==1004) special2=3;
                }
                else if (total == 2) {
                    special2 = 1+(rand()%3);
                    switch (special2) {
                        case 1 :
                            if (gpMonde->motifValue(124*16,33*16)!=1004) special2=2;
                            if (gpMonde->motifValue(135*16,33*16)!=1004
                            && x > 129*16-2) special2=2;
                            break;
                        case 2 :
                            if (gpMonde->motifValue(129*16,33*16)!=1004) {
                                if (x < 129*16-2) special2=1; else special2=3;}
                            break;
                        case 3 :
                            if (gpMonde->motifValue(135*16,33*16)!=1004) special2=2;
                            if (gpMonde->motifValue(124*16,33*16)!=1004
                            && x < 129*16-2) special2=2;
                            break;
                    }
                }
                else if (total == 3) {
                    random = rand()%2;
                    if (x < 129*16-2) special2=random+1;
                    else special2=random+2;
                }
            }
            switch (special2) {
                case 1 :
                    if (x > 124*16-2) {x--; direction=O;}
                    else if (x < 124*16-2) {x++; direction=E;}
                    if (x == 124*16-2) special1=1;
                    break;
                case 2 :
                    if (x > 129*16-2) {x--; direction=O;}
                    else if (x < 129*16-2) {x++; direction=E;}
                    if (x == 129*16-2) special1=1;
                    break;
                case 3 :
                    if (x > 135*16-2) {x--; direction=O;}
                    else if (x < 135*16-2) {x++; direction=E;}
                    if (x == 135*16-2) special1=1;
                    break;
            }
            if (special1) lastAnimTime = SDL_GetTicks();
        }
        else {
            //si le saut arrive à son terme, on active l'interrupteur
            if (special1>=3) {
                special1=0; special2=0;
            }
            if (special1==2 && special2>-1) {
                special2=-1;
                if (x<126*16) gpMonde->setValeur(124*16,33*16,1005);
                else if (x>132*16) gpMonde->setValeur(135*16,33*16,1005);
                else gpMonde->setValeur(129*16,33*16,1005);
                
                if (gpMonde->motifValue(124*16,33*16)!=1004 
                && gpMonde->motifValue(129*16,33*16)!=1004 
                && gpMonde->motifValue(135*16,33*16)!=1004) {
                    gpMonde->setValeur(126*16,42*16,1004);
                    gpMonde->setValeur(133*16,42*16,1004);
                }
                //snipe
                Ennemi* enn = getSuivant();
                while (enn != NULL) {
                    if (enn->getEnnId()==96 && enn->y==35*16 
                    && ((enn->x==124*16 && x<126*16) 
                    || (enn->x==129*16 && x>126*16 && x<132*16) 
                    || (enn->x==135*16 && x>132*16))) {
                        enn->snipe();
                        return;
                    }
                    enn = enn->getSuivant();
                }
                
            }
        }
    }
    
}

void Ennemi::IAFire() {
    if (y < 24*16) y++;
    Joueur* gpJoueur = gpJeu->getJoueur();
    if (gpJoueur->getX() < x + w && gpJoueur->getX() + 16 > x 
    && gpJoueur->getY() + 24 > y && gpJoueur->getY() < y + 16) 
        gpJoueur->moveY(2);
}

void Ennemi::IA() {
    if (id == 50 && special1) return;
    if ((id!=75 && id!=89) || !special1)
    switch (typeIA) {
        case IA_FONCE : for (int i = 0; i < vitesse; i++) bouge(); break;
        case IA_ATTEND : attend(); break;
        case IA_RANDOM : for (int i = 0; i < vitesse; i++) deplace(); break;
        case IA_SNIPE : regard(); break;
        case IA_HAUT_BAS : for (int i = 0; i < vitesse; i++) hautbas(); break;
        case IA_SPECIAL : special(); break;
        case IA_RIEN : 
            if (id==94) IACrabe();
            if (id==95) IAImp();
            if (id==114 || id==122) IAFire();
        default : break;
    }
    
    if (((id == 52 || id == 78) && special1 < 3) || id == 20 || id == 51 
    || id == 88 || force==0) return;
    
    ZoneRect* zonesAttaques2 = zonesAttaques;
    while (zonesAttaques2 != NULL) {
        if (gpJeu->testDegat(x + zonesAttaques2->getZone()->x, 
            y + zonesAttaques2->getZone()->y , 
            zonesAttaques2->getZone()->w, 
            zonesAttaques2->getZone()->h, 
            type_att, force, direction, dist) && type_att == ASPIRE) {
            
            int degats=force;
            if (!gpJeu->getJoueur()->getDefense()) degats=degats*2;
            else degats=degats/gpJeu->getJoueur()->getDefense();
            if (force > 0 && degats < 1) degats = 1;
            setVie(vie + degats);
            
        }
        zonesAttaques2 = zonesAttaques2->getSuivant();
    }
}

void Ennemi::bouge() {
    if (!distance()) {
        if (id == 13 || id == 18) typeIA=IA_ATTEND;
        return;
    }
    if ((id == 15 || id == 130) && anim>=18) return;
    if (id == 27 && anim>=6) return;
    if (id == 45 && special1 < 3 && special2 > 40) return;
    if (id==50 && (special2 == 1 || special2 == 4 || special2 == 7)) {
        direction=N;
        if (x < 169*16-10) x++;
        if (x > 169*16-10) x--;
        if (y < 19*16) y++;
        if (y > 19*16) y--;
        if (x == 169*16-10 && y == 19*16) {special2++; special1=1;}
        return;
    }
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    int x1 = x + gpZoneBase->getZone()->x + (gpZoneBase->getZone()->w/2);
    int y1 = y + gpZoneBase->getZone()->y + gpZoneBase->getZone()->h;
    
    int x2 = gpJoueur->getX()+8;
    int y2 = gpJoueur->getY()+24-vol*7;
    
    
    if (x1 < x2) moveX(1);
    else if (x1 > x2) moveX(-1);
    
    if (y1 < y2) moveY(1);
    else if (y1 > y2) moveY(-1);
    
    regard();
}

void Ennemi::attend() {
    anim=animmax+1;
    if (!distance()) return;
    typeIA = IA_FONCE; 
    if (id != 13 && id !=18 && id != 54 && id != 84) porte+=130;
    for (int k = 0; k < 25; k++) if (effets[k]>=1) effets[k]=2; else effets[k]=1;
    effets[COUP_MARTEAU]=2;
    anim=0;
}

void Ennemi::deplace() {
    if ((id == 91 || id == 139) && special1) return;
    if (id == 97 && special2>=10) return;
    int randomValue = (int)((float)rand() / RAND_MAX * (100));
    if ((id==97 && special1) || id==105 || id==111) randomValue=10;
    switch (randomValue) {
        case 1 : moveX(-1);direction=O; break;
        case 2 : moveX(1); direction=E; break;
        case 3 : moveY(-1);direction=N; break;
        case 4 : moveY(1); direction=S; break;
        case 5 :
        case 6 :
        case 7 :
        case 8 : break;
        default :
            switch (direction) {
                case N : moveY(-1); break;
                case S : moveY(1); break;
                case O : moveX(-1); break;
                case E : moveX(1); break;
            }
            break;    
    }
    if (id==48) ajuste();
}

bool Ennemi::distance() {
    Joueur* gpJoueur = gpJeu->getJoueur();
    /*int x1 = x + gpZoneBase->getZone()->x + (gpZoneBase->getZone()->w/2);
    int y1 = y + gpZoneBase->getZone()->y + gpZoneBase->getZone()->h;
    if (typeIA==IA_ATTEND) y1 -= gpZoneBase->getZone()->h/2;
    int tmp1 = abs(x1-(gpJoueur->getX()+8));
    int tmp2 = abs(y1-(gpJoueur->getY()+24-vol*7));
    if (tmp1 > tmp2) return tmp1;
    else return tmp2;*/
    
    int gauche = x+gpZoneBase->getZone()->x;
    int droite = gauche + gpZoneBase->getZone()->w;
    int haut = y+gpZoneBase->getZone()->y;
    int bas = haut + gpZoneBase->getZone()->h;
    
    if (  ((gpJoueur->getX()<gauche-porte && gpJoueur->getX()+16>gauche-porte)
    || (gpJoueur->getX()>=gauche-porte && gpJoueur->getX()+16<=droite+porte)
    || (gpJoueur->getX()<droite+porte && gpJoueur->getX()+16>droite+porte))
    &&
    ((gpJoueur->getY()+8<haut-porte && gpJoueur->getY()+24>haut-porte)
    || (gpJoueur->getY()+8>=haut-porte && gpJoueur->getY()+24<=bas+porte)
    || (gpJoueur->getY()+8<bas+porte && gpJoueur->getY()+24>bas+porte))) {
        return true;
    }
    return false;
}

void Ennemi::snipe() {
    if(!distance() && id!=91 && id!=96 && id!=139) return;
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    int high= 16;
    /*if (gpJoueur->getTypeAnim()==FLOTTE || gpJoueur->getTypeAnim()==NAGE) high=10;
    else high = 16;*/
    
    double anglx = 0;
    double angly = 0;
    int origx = x + (w/2);
    int origy = y + (h/2);
    int destx = gpJoueur->getX() + 8;
    int desty = gpJoueur->getY() + high;
    
    if (id == 45) origy=y+69;
    if (id == 50) origy-=5;
    if (id == 73) {origx=x+75;origy=y+75;}
    if (id == 74) {origx=x+25;origy=y+75;}
    if (id == 76) {origx=x+23;origy=y+42;}
    if (id == 76 && (direction == N || direction == O)) origx=x+36;
    if (id == 91 || id == 139) origy=y+15;
    if (id == 92) origy=y+30;
    if (id == 101 && direction == S) origy=y+4;
    if (id == 101 && direction == O) origx=x+4;
    if (id == 103) origy=y+18;
    if (id == 106) {
        origx=x+4;
        if (special2==1 || (special2==3 && special1==0)) origy=y+10;
        if (special2==2 || (special2==3 && special1==1)) origy=y+27;
    }
    if (id == 107) origy=y+107;
    if (id == 109) {
        desty = (75+10)*16+8;
        destx = (185+3*(special1-5)) * 16 + 8 +special2*8;
    }
    if (id == 115 && special1==0) {origx=x+48; origy=y+54;}
    if (id == 115 && special1==1) {origx=x+80; origy=y+54;}
    if (id == 116) {origx=x+40-16; origy=y+51+8;}
    if (id == 117) {origx=x+38+16; origy=y+51+8;}
    if (id == 128) {
        if (special2==2) {origx=x+12; origy=y+9;}
        if (special2==3) {origx=x+58; origy=y+9;}
    }
    
    double coef1 = 0;
    double coef2 = 0;
    
    if ((destx-origx) == 0) {anglx=0; angly=12;}
    else if ((desty-origy) == 0) {anglx=12; angly=0;}
    else { 
        coef1=((double)(desty-origy))/((double)(destx-origx));
        coef2=((double)(destx-origx))/((double)(desty-origy));
        anglx=(sqrt(12/(1+(coef1*coef1))));
        angly=(sqrt(12/(1+(coef2*coef2))));
    }
    if (destx - origx < 0) anglx = -anglx;
    if (desty - origy < 0) angly = -angly;
    
    int type = 0;
    switch(id) {
        case 31 : 
            origy+=16;
            if (special1==0) {type = 5;gpJeu->getAudio()->playSound(35);}
            else if (special1 == 1 + special2) {
                type=7; special1--;gpJeu->getAudio()->playSound(28);}
            else {
                type=6+7*(rand()%2); special1--; gpJeu->getAudio()->playSound(28);
            }
            break;
        case 49 : case 86 : type = 8; gpJeu->getAudio()->playSound(35); break;
        case 50 : type = 14; gpJeu->getAudio()->playSound(29); break;
        //case 65 : type = 9; gpJeu->getAudio()->playSound(35); break;
        case 73 : case 103 : case 107 : type = 10; gpJeu->getAudio()->playSound(35); break;
        case 65 : case 74 : case 76 : case 110 : 
            type = 11; gpJeu->getAudio()->playSound(35); break;
        case 99 : case 108 : type = 5; gpJeu->getAudio()->playSound(35); break;
        case 106 : type = 20; gpJeu->getAudio()->playSound(35); break;
        case 109 : type = 10; if (special1==5) gpJeu->getAudio()->playSound(35); break;
        case 115 : type=6; if (special1==0) gpJeu->getAudio()->playSound(28); break;
        case 116 : case 117 : type=5; gpJeu->getAudio()->playSound(28); break;
        case 120 : 
            origy+=16;
            if (special2==1) {type = 5;gpJeu->getAudio()->playSound(35);}
            else if (special2==2) {type=7; special1--;gpJeu->getAudio()->playSound(28);}
            else {type=6; special1--; gpJeu->getAudio()->playSound(28);}
            break;
        case 128 : type = 11; gpJeu->getAudio()->playSound(35); break;
        case 139 : type = 18; gpJeu->getAudio()->playSound(35); break;
        case 141 : type = 19; gpJeu->getAudio()->playSound(35); break;
        default : type = 1; gpJeu->getAudio()->playSound(35); break;
    }
    
    if (id == 96 && gpJeu->getZone()==51) type=5;
    
    if (anglx>4) anglx=4;
    if (angly>4) angly=4;
    if (anglx<-4) anglx=-4;
    if (angly<-4) angly=-4;
    
    gpJeu->ajouteSnipe(type, origx, origy, anglx, angly);
}

//tire sur Imp
void Ennemi::snipeImp() {
    if(!distance() || id!=96) return;
    
    Ennemi* enn;
    enn = gpJeu->getEnnemi()->getSuivant();
    while (enn != NULL) {
        if (enn->getEnnId()==95) break;
        enn = enn->getSuivant();
    }
    if (enn == NULL) return;
    
    int high= 16;
    
    double anglx = 0;
    double angly = 0;
    int origx = x + (w/2);
    int origy = y + (h/2);
    int destx = enn->getX() + 10;
    int desty = enn->getY() + high;
    
    double coef1 = 0;
    double coef2 = 0;
    
    if ((destx-origx) == 0) {anglx=0; angly=12;}
    else if ((desty-origy) == 0) {anglx=12; angly=0;}
    else { 
        coef1=((double)(desty-origy))/((double)(destx-origx));
        coef2=((double)(destx-origx))/((double)(desty-origy));
        anglx=(sqrt(12/(1+(coef1*coef1))));
        angly=(sqrt(12/(1+(coef2*coef2))));
    }
    if (destx - origx < 0) anglx = -anglx;
    if (desty - origy < 0) angly = -angly;
    
    int type = 21; gpJeu->getAudio()->playSound(35);
    
    if (anglx>4) anglx=4;
    if (angly>4) angly=4;
    if (anglx<-4) anglx=-4;
    if (angly<-4) angly=-4;
    
    gpJeu->ajouteSnipe(type, origx, origy, anglx, angly);
}

void Ennemi::tire() {
    if(!distance()) return;
    
    double anglx = 0;
    double angly = 0;
    int origx = x + (w/2);
    int origy = y + (h/2);
    
    int type = 0;
    switch(id) {
        case 15 : type = 2; gpJeu->getAudio()->playSound(29); break;
        case 16 : case 30 : type = 3; gpJeu->getAudio()->playSound(28); origy+=4; break;
        case 27 : type = 4; gpJeu->getAudio()->playSound(35); break;
        case 128 : type = 15; gpJeu->getAudio()->playSound(28); break;
        case 130 : type = 16; gpJeu->getAudio()->playSound(29); break;
        case 131 : type = 17; gpJeu->getAudio()->playSound(28); origy+=4; break;
        default : type = 2; break;
    }
    
    if (direction==E) anglx=4;
    if (direction==S) angly=4;
    if (direction==O) anglx=-4;
    if (direction==N) angly=-4;
    
    gpJeu->ajouteSnipe(type, origx, origy, anglx, angly);
}

void Ennemi::renfort() {
    Ennemi* enn = getSuivant();
    
    for (int i=0; i<3; i++) {
        if (enn->vie<=0) {
            enn->init();
            enn->x = gpJeu->getJoueur()->getX()+2;
            enn->y = gpJeu->getJoueur()->getY()+9;
            enn->viemax=1;
            enn->vie=1;
            enn->special1=240;
            gpJeu->getAudio()->playSound(6);
            return;
        }
        enn=enn->getSuivant();
    }
}

void Ennemi::replace() {
    if (id != 119) return;
    if (xdep == 65*16+5 && ydep == 31*16+5-8) {xdep = 69*16+5; ydep = 38*16+5; return;}
    if (xdep == 73*16+5 && ydep == 31*16+5-8) {xdep = 69*16+5; ydep = 50*16+5; return;}
    if (xdep == 45*16+5 && ydep == 93*16+5-8) {xdep = 48*16+5; ydep = 96*16+5; return;}
    if (xdep == 85*16+5 && ydep == 46*16+5-8) {xdep = 86*16+5; ydep = 49*16+5; return;}
    if (xdep == 93*16+5 && ydep == 46*16+5-8) {xdep = 91*16+5; ydep = 54*16+5; return;}
    if (xdep == 49*16+5 && ydep == 46*16+5-8) {xdep = 49*16+5; ydep = 51*16+5; return;}
    if (xdep == 7*16+5 && ydep == 33*16+5-8) {xdep = 9*16+5; ydep = 38*16+5; return;}
    if (xdep == 23*16+5 && ydep == 35*16+5-8) {xdep = 27*16+5; ydep = 38*16+5; return;}
    if (xdep == 16*16+5 && ydep == 50*16+5-8) {xdep = 17*16+5; ydep = 53*16+5; return;}
    if (xdep == 25*16+5 && ydep == 50*16+5-8) {xdep = 33*16+5; ydep = 46*16+5; return;}
    if (xdep == 53*16+5 && ydep == 31*16+5-8) {xdep = 49*16+5; ydep = 37*16+5; return;}
    if (xdep == 7*16+5 && ydep == 61*16+5-8) {xdep = 9*16+5; ydep = 68*16+5; return;}
    if (xdep == 11*16+5 && ydep == 61*16+5-8) {xdep = 9*16+5; ydep = 78*16+5; return;}
    if (xdep == 16*16+5 && ydep == 93*16+5-8) {xdep = 7*16+5; ydep = 97*16+5; return;}
    if (xdep == 25*16+5 && ydep == 93*16+5-8) {xdep = 19*16+5; ydep = 95*16+5; return;}
    if (xdep == 34*16+5 && ydep == 93*16+5-8) {xdep = 29*16+5; ydep = 98*16+5; return;}
    if (xdep == 86*16+5 && ydep == 31*16+5-8) {xdep = 87*16+5; ydep = 35*16+5; return;}
    if (xdep == 92*16+5 && ydep == 31*16+5-8) {xdep = 91*16+5; ydep = 39*16+5; return;}
    if (xdep == 126*16+5 && ydep == 91*16+5-8) {xdep = 129*16+5; ydep = 97*16+5; return;}
    if (xdep == 113*16+5 && ydep == 31*16+5-8) {xdep = 109*16+5; ydep = 34*16+5; return;}
    if (xdep == 105*16+5 && ydep == 16*16+5-8) {xdep = 106*16+5; ydep = 19*16+5; return;}
    if (xdep == 113*16+5 && ydep == 16*16+5-8) {xdep = 112*16+5; ydep = 23*16+5; return;}
    if (xdep == 115*16+5 && ydep == 48*16+5-8) {xdep = 110*16+5; ydep = 53*16+5; return;}
    if (xdep == 123*16+5 && ydep == 48*16+5-8) {xdep = 127*16+5; ydep = 51*16+5; return;}
    if (xdep == 125*16+5-8 && ydep == 33*16+5-8) {xdep = 129*16+5; ydep = 36*16+5; return;}
    if (xdep == 125*16+5 && ydep == 61*16+5-8) {xdep = 129*16+5; ydep = 69*16+5; return;}
    if (xdep == 133*16+5 && ydep == 61*16+5-8) {xdep = 129*16+5; ydep = 78*16+5; return;}
    if (xdep == 129*16+5 && ydep == 3*16+5-8) {xdep = 129*16+5; ydep = 14*16+5; return;}
}


int Ennemi::getEnnId() {return id;}

void Ennemi::setTypeIA(int ia) {typeIA = ia;}

int Ennemi::getSpecial(int i) {if (i==1) return special1; return special2;}
void Ennemi::setSpecial(int i, int v) {
    if (i==1) special1=v;
    else special2=v;
}

void Ennemi::testTapis() {
    
    if (id!=17 && id!=61 && (typeIA == IA_FONCE || id==106) 
    && vol==0 && spectre==0 && vie>0) {
    
        int a=x+gpZoneBase->getZone()->x+(gpZoneBase->getZone()->w/2);
        int b=y+gpZoneBase->getZone()->y+(gpZoneBase->getZone()->h/2);
    
        Monde* gpMonde = gpJeu->getMonde();
    
        if (gpMonde->motifValue(a,b)>=5230 && gpMonde->motifValue(a,b)<=5245)
            switch (gpMonde->motifValue(a,b)) {
                case 5230 : moveY(-2); break;
                case 5234 : moveY(2); break;
                case 5238 : moveX(-2); break;
                case 5242 : moveX(2); break;
            }
    }    
    
    if (suivant != NULL) ((Ennemi*)suivant)->testTapis();
}    

bool Ennemi::isBig() {
    return (id == 19 || id == 24 || id == 28 || id == 35 || id == 40 || id == 43 || id == 101);
}

bool Ennemi::isMiniBoss() {
    return ((id == 91 && gpJeu->getZone()==46) || id == 93 || id == 95 || id == 98 
    || id == 102 || id == 104 || id == 106 || id == 108 || id == 110 || id == 113 
    || id == 76 || id == 31);
}

bool Ennemi::isBoss() {
    return (id == 89 || id == 92 || id == 94 || id == 97 || id == 99 || id == 100 || id == 103
    || id == 105 || id == 107 || id == 109 || id == 111 || id == 115 || id == 120 || id == 50
    || id == 127 || id == 128 || id == 141);
}

void Ennemi::init() {
    x=xdep; y=ydep; direction=S; anim=0; if (id!=20 && id!=88) special1=0; special2=0;
    vanim=240; vol=0; nage=0; spectre=0; porte=0; typeIA=IA_RIEN; 
    vitesse=1; force=0; recul=16; glace=0; maxglace=60; typeEnn=E_SIMPLE;
    for (int k = 0; k < 25; k++) effets[k]=2;
    for (int k = 0; k < 3; k++) objets[k]=0;

    if (zonesAttaques != NULL) {
        delete zonesAttaques;
    }
    if (zonesVulnerables != NULL) {
        delete zonesVulnerables;
    }

    switch (id) {
        case 1 :
            viemax=3; w=16; h=26; animmax=1; typeIA=IA_FONCE; porte=160; force = 2;
            objets[0]=I_FLECHE;objets[1]=I_BOMBE;objets[2]=I_RUBIS_BLEU;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=10; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            break;
        case 2 :
            viemax=12; w=21; h=26; animmax=1; typeIA=IA_FONCE; porte=300; force = 8;
            objets[0]=I_BOMBE;objets[1]=I_MAGIE_PEU;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=2; gpZoneBase->getZone()->y=10; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            recul = 8; maxglace=30;
            break;
        case 3 :
            viemax=2; w=28; h=17; animmax=2; typeIA=IA_FONCE; porte=200; force = 1;
            objets[0]=I_PETIT_COEUR;objets[1]=I_RUBIS_VERT;objets[2]=I_RUBIS_BLEU;
            gpZoneBase->getZone()->w=28; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=1; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_MONO_DIR;
            break;
        case 4 :
            viemax=1; w=16; h=17; animmax=2; typeIA=IA_FONCE; porte=100; force = 1;
            objets[0]=I_PETIT_COEUR;objets[1]=I_RUBIS_VERT;objets[2]=I_RUBIS_BLEU;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=1; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_MONO_DIR;
            break;
        case 5 :
            viemax=3; w=16; h=26; animmax=1; typeIA=IA_FONCE; porte=200; force = 2;
            objets[0]=I_FLECHE;objets[1]=I_MAGIE_PEU;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=10; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesAttaques->ajout(new ZoneRect(0,15,5,13));
            zonesVulnerables = new ZoneRect(0,0,w,h); arme = true;
            break;
        case 6 :
            viemax=5; w=16; h=37; animmax=9; typeIA=IA_ATTEND; porte=30; force = 2;
            objets[0]=I_FLECHE;objets[1]=I_RUBIS_BLEU;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=21; 
            zonesAttaques = new ZoneRect(0,5,w,32);
            zonesVulnerables = new ZoneRect(0,5,w,32); recul = 8; vanim = 30; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=1;
            break;
        case 7 :
            viemax=1; w=16; h=16; animmax=1; typeIA=IA_FONCE; porte=100; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RUBIS_VERT;objets[2]=I_RUBIS_BLEU;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=1; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            type_att = VENIN;
            break;
        case 8 :
            viemax=4; w=16; h=24; animmax=1; typeIA=IA_FONCE; porte=160; force = 2;
            objets[0]=I_RUBIS_BLEU;objets[1]=I_RUBIS_BLEU;objets[2]=I_RUBIS_ROUGE;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=8; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=100;
            break;
        case 9 :
            viemax=3; w=16; h=24; animmax=1; typeIA=IA_FONCE; porte=160; force = 2;
            objets[0]=I_FLECHE;objets[1]=I_PETIT_COEUR;objets[2]=I_RUBIS_ROUGE;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=8; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=100;
            break;
        case 10 :
            viemax=1; w=16; h=16; animmax=1; typeIA=IA_SNIPE; porte=200; force = 2;
            objets[0]=I_FLECHE;objets[1]=I_PETIT_COEUR;objets[2]=I_RUBIS_ROUGE;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=100; recul=0; vanim=1240; direction=N; typeEnn=E_MONO_DIR;
            break;
        case 11 :
            viemax=1; w=16; h=21; animmax=2; typeIA=IA_ATTEND; porte=30; force = 8;
            objets[0]=I_BOMBE;objets[1]=I_RUBIS_BLEU;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,16);
            zonesVulnerables = new ZoneRect(0,0,w,16); recul = 8; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 12 :
            viemax=3; w=17; h=17; animmax=2; typeIA=IA_FONCE; porte=150; force = 2;
            objets[0]=I_RUBIS_BLEU;objets[1]=I_MAGIE_PEU;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=17; gpZoneBase->getZone()->h=17;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=30; typeEnn=E_PROFIL; spectre=1; direction=E;
            for (int k = 0; k < 25; k++) effets[k]=1;
            if (gpJeu->getJoueur()->getEpee()>=2) {effets[COUP_EPEE]=2; effets[EPEE_SPIN]=2;}
            if (gpJeu->getJoueur()->hasObjet(O_ARC)==5) effets[FLECHE]=2; 
            break;
        case 13 :
            viemax=5; w=32; h=15; animmax=1; typeIA=IA_ATTEND; porte=100; force = 6;
            objets[0]=I_RUBIS_VERT;objets[1]=I_RUBIS_BLEU;objets[2]=I_FLECHE;
            gpZoneBase->getZone()->w=18; gpZoneBase->getZone()->h=15;
            gpZoneBase->getZone()->x=7; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(7,0,18,15);
            zonesVulnerables = new ZoneRect(7,0,18,15);
            maxglace=100; direction=N; typeEnn=E_MONO_DIR; spectre=1; vol=1; vanim=150;
            break;
        case 14 :
            viemax=5; w=41; h=16; animmax=1; typeIA=IA_FONCE; porte=160; force = 18;
            objets[0]=I_BOMBE;objets[1]=I_FLECHE;objets[2]=I_RUBIS_ROUGE;
            gpZoneBase->getZone()->w=41; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=100; direction=N; typeEnn=E_MONO_DIR;
            break;
        case 15 :
            viemax=10; w=24; h=31; animmax=20; typeIA=IA_FONCE; porte=200; force = 12;
            objets[0]=I_RUBIS_BLEU;objets[1]=I_RUBIS_ROUGE;objets[2]=I_BOMBE;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=4; gpZoneBase->getZone()->y=15; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h); vanim=120;
            break;
        case 16 :
            viemax=10; w=16; h=24; animmax=9; typeIA=IA_SNIPE; porte=200; force = 10;
            objets[0]=I_BOMBE;objets[1]=I_FLECHE;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=8; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=40; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=1;
            effets[ENNEMI]=2;
            break;
        case 17 :
            viemax=1; w=16; h=16; animmax=0; typeIA=IA_HAUT_BAS; porte=0; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(2,2,12,12);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; recul=0; vol=1; vitesse=2; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 18 :
            viemax=1; w=16; h=14; animmax=1; typeIA=IA_ATTEND; porte=70; force = 1;
            objets[0]=I_PETIT_COEUR;objets[1]=I_RUBIS_VERT;objets[2]=I_RUBIS_BLEU;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=14;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=60; direction=N; typeEnn=E_MONO_DIR; spectre=1; vol=1;
            break;
        case 19 :
            viemax=8; w=64; h=32; animmax=2; typeIA=IA_FONCE; porte=300; force = 2;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_MONO_DIR; recul=4; spectre=1;
            break;
        case 20 :
            viemax=1; w=16; h=16; animmax=0; typeIA=IA_RIEN; porte=200; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_MONO_DIR; recul=0; maxglace=0;
            break;
        case 21 :
            viemax=2; w=16; h=15; animmax=1; typeIA=IA_FONCE; porte=200; force = 2;
            objets[0]=I_FLECHE;objets[1]=I_RUBIS_BLEU;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=15;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=30; typeEnn=E_PROFIL; direction=E; nage=1;
            break;
        case 22 :
            viemax=2; w=16; h=23; animmax=1; typeIA=IA_FONCE; porte=200; force = 2;
            objets[0]=I_FLECHE;objets[1]=I_RUBIS_BLEU;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=23;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=30; direction=N; typeEnn=E_MONO_DIR; spectre=1;
            break;
        case 23 :
            viemax=2; w=26; h=17; animmax=1; typeIA=IA_FONCE; porte=200; force = 2;
            objets[0]=I_FLECHE;objets[1]=I_RUBIS_BLEU;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=26; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=1; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=30; direction=N; typeEnn=E_MONO_DIR;
            break;
        case 24 :
            viemax=10; w=32; h=53; animmax=1; typeIA=IA_FONCE; porte=300; force = 2;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_MONO_DIR; recul=4; spectre=1;
            break;
        case 25 :
            viemax=7; w=28; h=30; animmax=1; typeIA=IA_FONCE; porte=160; force = 3;
            objets[0]=I_BOMBE;objets[1]=I_RUBIS_ROUGE;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=6; gpZoneBase->getZone()->y=14; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            recul=8; maxglace=100;
            break;
        case 26 :
            viemax=2; w=14; h=16; animmax=1; typeIA=IA_ATTEND; porte=100; force = 3;
            objets[0]=I_RUBIS_ROUGE;objets[1]=I_MAGIE_PEU;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=60; direction=N; typeEnn=E_MONO_DIR; spectre=1; vol=1;
            break;
        case 27 :
            viemax=3; w=16; h=17; animmax=10; typeIA=IA_FONCE; porte=300; force = 2;
            objets[0]=I_FLECHE;objets[1]=I_MAGIE_PEU;objets[2]=I_BOMBE;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=1; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            break;
        case 28 :
            viemax=10; w=32; h=38; animmax=1; typeIA=IA_FONCE; porte=300; force = 3;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=8; gpZoneBase->getZone()->y=22; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_MONO_DIR; recul=4;
            break;
        case 29 :
            viemax=1; w=16; h=26; animmax=1; typeIA=IA_FONCE; porte=300; force = 6;
            objets[0]=I_RUBIS_BLEU;objets[1]=I_MAGIE_PEU;objets[2]=I_MAGIE_BCP;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=10; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            for (int k = 0; k < 25; k++) effets[k]=1; effets[FEU]=2;
            maxglace=100;
            break;
        case 30 :
            viemax=3; w=16; h=24; animmax=9; typeIA=IA_SNIPE; porte=200; force = 6;
            objets[0]=I_RUBIS_BLEU;objets[1]=I_PETIT_COEUR;objets[2]=I_MAGIE_PEU;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=8; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=40; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=1;
            effets[ENNEMI]=2;
            break;
        case 31 :
            viemax=60; w=32; h=32; animmax=9; typeIA=IA_SNIPE; porte=300; force = 20;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=40; recul=0; typeEnn=E_MONO_DIR; vanim=120;
            for (int k = 0; k < 25; k++) effets[k]=1; effets[ENNEMI]=2; 
            break;
        case 32 :
            viemax=5; w=16; h=23; animmax=2; typeIA=IA_FONCE; porte=200; force = 3;
            objets[0]=I_MAGIE_PEU;objets[1]=I_RUBIS_BLEU;objets[2]=I_RUBIS_ROUGE;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=7; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_MONO_DIR; maxglace=100;
            break;
        case 33 :
            viemax=10; w=22; h=25; animmax=1; typeIA=IA_FONCE; porte=300; force = 6;
            objets[0]=I_RUBIS_BLEU;objets[1]=I_MAGIE_PEU;objets[2]=I_FLECHE;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=3; gpZoneBase->getZone()->y=9; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=100;
            break;
        case 34 :
            viemax=5; w=24; h=25; animmax=1; typeIA=IA_FONCE; porte=300; force = 9;
            objets[0]=I_FLECHE;objets[1]=I_RUBIS_ROUGE;objets[2]=I_RUBIS_ROUGE;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=4; gpZoneBase->getZone()->y=9; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            recul=8; maxglace=100;
            for (int k = 0; k < 25; k++) effets[k]=1; effets[FLECHE]=2;
            break;
        case 35 :
            viemax=12; w=32; h=32; animmax=2; typeIA=IA_FONCE; porte=300; force = 3;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_MONO_DIR; recul=4; spectre=1; maxglace=40;
            break;
        case 36 :
            viemax=1; w=16; h=16; animmax=9; typeIA=IA_STATUE; porte=300; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; recul=0; vanim=120; direction=N; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 37 :
            viemax=6; w=16; h=26; animmax=1; typeIA=IA_FONCE; porte=160; force = 4;
            objets[0]=I_BOMBE;objets[1]=I_FLECHE;objets[2]=I_RUBIS_ROUGE;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=10; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            break;
        case 38 :
            viemax=15; w=22; h=25; animmax=1; typeIA=IA_FONCE; porte=300; force = 8;
            objets[0]=I_RUBIS_ROUGE;objets[1]=I_MAGIE_PEU;objets[2]=I_MAGIE_BCP;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=3; gpZoneBase->getZone()->y=9; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=100;
            break;
        case 39 :
            viemax=10; w=24; h=25; animmax=1; typeIA=IA_FONCE; porte=300; force = 10;
            objets[0]=I_RUBIS_ROUGE;objets[1]=I_RUBIS_ROUGE;objets[2]=I_RUBIS_ROUGE;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=4; gpZoneBase->getZone()->y=9; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            for (int k = 0; k < 25; k++) effets[k]=1; effets[FLECHE]=2; recul=8; maxglace=100;
            break;
        case 40 :
            viemax=12; w=54; h=42; animmax=8; typeIA=IA_FONCE; porte=300; force = 3;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_MONO_DIR; recul=4; spectre=1; maxglace=100; vanim=120;
            break;
        case 41 :
            viemax=9; w=16; h=24; animmax=1; typeIA=IA_FONCE; porte=300; force = 6;
            objets[0]=I_RUBIS_BLEU;objets[1]=I_FLECHE;objets[2]=I_MAGIE_PEU;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=8; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=30;
            break;
        case 42 :
            viemax=3; w=26; h=19; animmax=1; typeIA=IA_FONCE; porte=300; force = 10;
            objets[0]=I_MAGIE_PEU;objets[1]=I_MAGIE_PEU;objets[2]=I_MAGIE_BCP;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=5; gpZoneBase->getZone()->y=3; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=10; direction=N; typeEnn=E_MONO_DIR; type_att=COUP_GLACE;
            for (int k = 0; k < 25; k++) effets[k]=1; effets[FEU]=2;
            break;
        case 43 :
            viemax=16; w=32; h=32; animmax=2; typeIA=IA_FONCE; porte=300; force = 4;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            recul=4; spectre=1; maxglace=30;
            break;
        case 44 :
            viemax=9; w=22; h=26; animmax=1; typeIA=IA_FONCE; porte=300; force = 8;
            objets[0]=I_RUBIS_BLEU;objets[1]=I_FLECHE;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=3; gpZoneBase->getZone()->y=10; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesAttaques->ajout(new ZoneRect(0,20,7,15));
            zonesVulnerables = new ZoneRect(0,0,w,h); arme = true;
            break;
        case 45 :
            viemax=20; w=66; h=76; animmax=6; typeIA=IA_FONCE; porte=300; force = 6;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,66,64);
            zonesAttaques->ajout(new ZoneRect(0,67,16,9));
            zonesAttaques->ajout(new ZoneRect(50,59,16,9));
            zonesVulnerables = new ZoneRect(9,29,48,38);
            for (int k = 0; k < 25; k++) effets[k]=0; effets[COUP_MARTEAU]=2;
            typeEnn=E_MONO_DIR; recul=4; spectre=1; maxglace=40; vanim = 120;
            break;
        case 46 :
            viemax=6; w=22; h=27; animmax=1; typeIA=IA_FONCE; porte=300; force = 10;
            objets[0]=I_RUBIS_VERT;objets[1]=I_MAGIE_PEU;objets[2]=I_MAGIE_BCP;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=3; gpZoneBase->getZone()->y=11; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesAttaques->ajout(new ZoneRect(0,21,5,16));
            zonesVulnerables = new ZoneRect(0,0,w,h); arme = true;
            break;
        case 47 :
            viemax=12; w=22; h=27; animmax=1; typeIA=IA_FONCE; porte=300; force = 20;
            objets[0]=I_RUBIS_BLEU;objets[1]=I_FLECHE;objets[2]=I_BOMBE;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=3; gpZoneBase->getZone()->y=11; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesAttaques->ajout(new ZoneRect(0,21,5,16));
            zonesVulnerables = new ZoneRect(0,0,w,h); arme = true;
            break;
        case 48 :
            viemax=18; w=22; h=27; animmax=1; typeIA=IA_FONCE; porte=300; force = 30;
            objets[0]=I_RUBIS_ROUGE;objets[1]=I_PETIT_COEUR;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=3; gpZoneBase->getZone()->y=11; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesAttaques->ajout(new ZoneRect(0,21,5,17));
            zonesVulnerables = new ZoneRect(0,0,w,h); arme = true;
            if (gpJeu->getZone()==57 && x >= 0 && x <=30*16 && y >= 30*16 && y <=60*16) 
                typeIA=IA_RANDOM;
            break;
        case 49 :
            viemax=1; w=16; h=16; animmax=9; typeIA=IA_STATUE; porte=300; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; recul=0; vanim=120; direction=N; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 50 :
            viemax=300; w=52; h=36; animmax=1; typeIA=IA_FONCE; porte=300; force = 50;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_SIMPLE; recul=4; maxglace=60; vanim=120; vinvin=5;
            for (int k = 0; k < 25; k++) effets[k]=0;
            if (gpJeu->getJoueur()->getEpee()==5) {effets[COUP_EPEE]=2; effets[EPEE_SPIN]=2;}
            //if (gpJeu->getJoueur()->hasObjet(O_ARC)==5) effets[FLECHE]=2; 
            break;
        case 51 :
            viemax=1; w=24; h=22; animmax=40; typeIA=IA_SPECIAL; porte=300; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_MONO_DIR; recul=0; spectre=1; maxglace=0; vanim=120;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 52 :
            viemax=100; w=16; h=17; animmax=1; typeIA=IA_RANDOM; porte=1000; force = 2;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=1; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; typeEnn=E_PROFIL;
            break;
        case 53 :
            viemax=1; w=14; h=15; animmax=1; typeIA=IA_FONCE; porte=100; force = 1;
            objets[0]=I_RUBIS_VERT;objets[1]=I_RUBIS_VERT;objets[2]=I_MAGIE_PEU;
            gpZoneBase->getZone()->w=14; gpZoneBase->getZone()->h=15;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=60; typeEnn=E_PROFIL; direction=E;
            break;
        case 54 :
            viemax=2; w=16; h=17; animmax=1; typeIA=IA_ATTEND; porte=100; force = 2;
            objets[0]=I_PETIT_COEUR;objets[1]=I_PETIT_COEUR;objets[2]=I_RUBIS_BLEU;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=17;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=60; typeEnn=E_PROFIL; spectre=1; vol=1; direction=E;
            break;
        case 55 :
            viemax=3; w=22; h=26; animmax=1; typeIA=IA_FONCE; porte=200; force = 4;
            objets[0]=I_PETIT_COEUR;objets[1]=I_RUBIS_BLEU;objets[2]=I_FLECHE;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=3; gpZoneBase->getZone()->y=10; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesAttaques->ajout(new ZoneRect(0,20,7,15));
            zonesVulnerables = new ZoneRect(0,0,w,h); arme = true;
            break;
        case 56 :
            viemax=6; w=17; h=17; animmax=2; typeIA=IA_FONCE; porte=150; force = 3;
            objets[0]=I_RUBIS_BLEU;objets[1]=I_MAGIE_PEU;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=17; gpZoneBase->getZone()->h=17;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=30; typeEnn=E_PROFIL; spectre=1; direction=E;
            for (int k = 0; k < 25; k++) effets[k]=1;
            if (gpJeu->getJoueur()->getEpee()>=2) {effets[COUP_EPEE]=2; effets[EPEE_SPIN]=2;}
            if (gpJeu->getJoueur()->hasObjet(O_ARC)==5) effets[FLECHE]=2; 
            break;
        case 57 :
            viemax=8; w=48; h=65; animmax=40; typeIA=IA_SNIPE; porte=300; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(12,0,24,h);
            zonesAttaques->ajout(new ZoneRect(0,41,w,24));
            zonesVulnerables = new ZoneRect(0,0,w,h); recul=0; typeEnn=E_PROFIL;
            break;
        case 58 :
            viemax=0; w=14; h=15; animmax=1; typeIA=IA_RIEN; porte=100; force = 0;
            objets[0]=I_RUBIS_VERT;objets[1]=I_RUBIS_VERT;objets[2]=I_MAGIE_PEU;
            gpZoneBase->getZone()->w=14; gpZoneBase->getZone()->h=15;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=60; typeEnn=E_PROFIL; direction=E;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 59 :
            viemax=999; w=16; h=16; animmax=0; typeIA=IA_RIEN; porte=300; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h); recul=0; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 60 :
            viemax=12; w=50; h=66; animmax=3; typeIA=IA_FONCE; porte=300; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=32; gpZoneBase->getZone()->h=24;
            gpZoneBase->getZone()->x=9; gpZoneBase->getZone()->y=42; 
            zonesAttaques = new ZoneRect(0,0,50,36);
            zonesAttaques->ajout(new ZoneRect(9,36,32,26));
            zonesVulnerables = new ZoneRect(9,36,32,26); recul=4;
            break;
        case 61 :
            viemax=1; w=128; h=16; animmax=3; typeIA=IA_HAUT_BAS; porte=200; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; recul=0; vol=1; vitesse=2; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 62 :
            viemax=10; w=24; h=37; animmax=1; typeIA=IA_FONCE; porte=300; force = 4;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=21; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h); recul=4; vanim=120;
            break;
        case 63 :
            viemax=30; w=58; h=68; animmax=0; typeIA=IA_FONCE; porte=300; force = 6;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=24;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=42; 
            zonesAttaques = new ZoneRect(13,0,32,68); vanim=120;
            zonesAttaques->ajout(new ZoneRect(5,28,48,20)); type_att = ASPIRE;
            zonesVulnerables = new ZoneRect(13,0,32,68); direction=S; typeEnn=E_MONO_DIR;
            zonesVulnerables->ajout(new ZoneRect(5,28,48,20)); recul=4; spectre=1;
            for (int k = 0; k < 25; k++) effets[k]=1;
            if (gpJeu->getJoueur()->getEpee()>=2) {effets[COUP_EPEE]=2; effets[EPEE_SPIN]=2;}
            if (gpJeu->getJoueur()->hasObjet(O_ARC)==5) effets[FLECHE]=2; 
            break;
        case 64 :
            viemax=10; w=40; h=36; animmax=3; typeIA=IA_FONCE; porte=200; force = 4;
            objets[0]=I_BOMBE;objets[1]=I_RUBIS_BLEU;objets[2]=I_RUBIS_ROUGE;
            gpZoneBase->getZone()->w=20; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=9; gpZoneBase->getZone()->y=19; 
            zonesAttaques = new ZoneRect(9,0,20,h);
            zonesVulnerables = new ZoneRect(9,0,20,h); recul=4; vanim=120; maxglace=100;
            break;
        case 65 :
            viemax=1; w=16; h=16; animmax=9; typeIA=IA_STATUE; porte=300; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; recul=0; vanim=120; direction=N; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 66 :
            viemax=50; w=96; h=0; animmax=3; typeIA=IA_RIEN; porte=300; force = 8;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=0;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,0);
            zonesVulnerables = new ZoneRect(0,0,w,0);
            maxglace=60; recul=0; vanim=120; direction=S; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0; vol=1;
            break;
        case 67 :
            viemax=0; w=8; h=0; animmax=24; typeIA=IA_SPECIAL; porte=300; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=60; recul=0; vanim=120; direction=N; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0; vol=1;
            break;
        case 68 :
            viemax=0; w=26; h=0; animmax=3; typeIA=IA_SPECIAL; porte=300; force = 8;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=60; recul=0; vanim=120; direction=E; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0; vol=1;
            break;
        case 69 :
            viemax=0; w=26; h=0; animmax=3; typeIA=IA_SPECIAL; porte=300; force = 8;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=60; recul=0; vanim=120; direction=O; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0; vol=1;
            break;
        case 70 :
            viemax=1; w=1; h=272; animmax=0; typeIA=IA_RIEN; porte=300; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; recul=0; vanim=120; direction=O; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0; spectre=1;
            break;
        case 71 :
            viemax=30; w=52; h=55; animmax=3; typeIA=IA_FONCE; porte=300; force = 12;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=32; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=10; gpZoneBase->getZone()->y=34; 
            zonesAttaques = new ZoneRect(10,0,32,h);
            zonesVulnerables = new ZoneRect(10,0,32,h);
            maxglace=0; recul=0; vanim=120; vol=1; dist=32;
            break;
        case 72 :
            viemax=1; w=16; h=26; animmax=1; typeIA=IA_FONCE; porte=200; force = 10;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=10; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h); maxglace=15;
            for (int k = 0; k < 25; k++) effets[k]=1;
            break;
        case 73 :
            viemax=60; w=104; h=153; animmax=3; typeIA=IA_RIEN; porte=300; force = 24;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN; vanim=120;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(30,0,14,h); direction=E; typeEnn=E_MONO_DIR;
            zonesAttaques->ajout(new ZoneRect(30,30,40,74));
            zonesVulnerables = new ZoneRect(30,30,40,74); maxglace=0; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=0; effets[COUP_GLACE]=2; spectre=1;
            break;
        case 74 :
            viemax=90; w=104; h=153; animmax=3; typeIA=IA_RIEN; porte=300; force = 24;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN; vanim=120;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(60,0,14,h); direction=O; typeEnn=E_MONO_DIR;
            zonesAttaques->ajout(new ZoneRect(24,30,40,74));
            zonesVulnerables = new ZoneRect(24,30,40,74); maxglace=0; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=0; effets[FEU]=2; spectre=1;
            break;
        case 75 :
            viemax=100; w=19; h=24; animmax=7; typeIA=IA_FONCE; porte=300; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN; vanim=120; vinvin=5;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=8; 
            zonesAttaques = new ZoneRect(0,0,w,h); type_att=DEMI;
            zonesAttaques->ajout(new ZoneRect(0,0,w,h));
            zonesVulnerables = new ZoneRect(0,0,w,h); maxglace=0;
            for (int k = 0; k < 25; k++) effets[k]=0; effets[COUP_EPEE]=2; effets[EPEE_SPIN]=2;
            break;
        case 76 :
            viemax=70; w=60; h=51; animmax=5; typeIA=IA_FONCE; porte=300; force = 20;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN; vanim=120; vinvin=5;
            gpZoneBase->getZone()->w=32; gpZoneBase->getZone()->h=24;
            gpZoneBase->getZone()->x=11; gpZoneBase->getZone()->y=18; 
            zonesAttaques = new ZoneRect(0,0,w,43);
            zonesVulnerables = new ZoneRect(0,0,w,43); recul=4; typeEnn=E_PROFIL;
            break;
        case 77 :
            viemax=10; w=42; h=30; animmax=1; typeIA=IA_FONCE; porte=200; force = 12;
            objets[0]=I_BOMBE;objets[1]=I_RUBIS_BLEU;objets[2]=I_RUBIS_BLEU;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=14; gpZoneBase->getZone()->y=14; 
            zonesAttaques = new ZoneRect(12,0,19,30);
            zonesVulnerables = new ZoneRect(12,0,19,30); maxglace=30; vitesse=2;
            break;
        case 78 :
            viemax=100; w=15; h=17; animmax=1; typeIA=IA_RANDOM; porte=1000; force = 4;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=15; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=1; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; typeEnn=E_PROFIL;
            break;
        case 79 :
            viemax=1; w=16; h=21; animmax=2; typeIA=IA_RANDOM; porte=200; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=5; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; typeEnn=E_PROFIL;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 80 :
            viemax=1; w=24; h=32; animmax=3; typeIA=IA_RANDOM; porte=200; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=24; gpZoneBase->getZone()->h=32;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; typeEnn=E_PROFIL;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 81 :
            viemax=1; w=15; h=15; animmax=1; typeIA=IA_RANDOM; porte=200; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=15; gpZoneBase->getZone()->h=15;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; typeEnn=E_PROFIL;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 82 :
            viemax=1; w=16; h=21; animmax=1; typeIA=IA_RANDOM; porte=200; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=5; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; typeEnn=E_PROFIL;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 83 :
            viemax=1; w=7; h=7; animmax=1; typeIA=IA_RANDOM; porte=200; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=7; gpZoneBase->getZone()->h=7;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; typeEnn=E_PROFIL;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 84 :
            viemax=5; w=16; h=17; animmax=1; typeIA=IA_ATTEND; porte=150; force = 6;
            objets[0]=I_FLECHE;objets[1]=I_BOMBE;objets[2]=I_PETIT_COEUR;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=17;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=60; typeEnn=E_PROFIL; spectre=1; vol=1; direction=E;
            break;
        case 85 :
            viemax=1; w=18; h=14; animmax=1; typeIA=IA_RANDOM; porte=200; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=18; gpZoneBase->getZone()->h=14;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; typeEnn=E_PROFIL;
            for (int k = 0; k < 25; k++) effets[k]=0; spectre=1; vol=1;
            break;
        case 86 :
            viemax=1; w=16; h=16; animmax=1; typeIA=IA_SNIPE; porte=200; force = 5;
            objets[0]=I_FLECHE;objets[1]=I_BOMBE;objets[2]=I_RUBIS_ROUGE;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h); nage=1;
            maxglace=40; recul=0; vanim=1240; direction=N; typeEnn=E_MONO_DIR;
            break;
        case 87 :
            viemax=7; w=58; h=24; animmax=1; typeIA=IA_FONCE; porte=200; force = 10;
            objets[0]=I_MAGIE_PEU;objets[1]=I_MAGIE_PEU;objets[2]=I_MAGIE_BCP;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=21; gpZoneBase->getZone()->y=6; 
            zonesAttaques = new ZoneRect(13,0,32,24);
            zonesVulnerables = new ZoneRect(21,6,16,16);
            maxglace=10; direction=N; typeEnn=E_MONO_DIR; type_att=COUP_GLACE;
            break;
        case 88 :
            viemax=1; w=16; h=16; animmax=0; typeIA=IA_RIEN; porte=200; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_MONO_DIR; recul=0; maxglace=0;
            special1=gpJeu->getJoueur()->getPosRails();
            break;
        case 89 :
            viemax=50; w=20; h=26; animmax=1; typeIA=IA_FONCE; porte=300; force = 10;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN; vanim=120; vinvin=5;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=2; gpZoneBase->getZone()->y=10; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesAttaques->ajout(new ZoneRect(0,0,w,h));
            zonesVulnerables = new ZoneRect(0,0,w,h); maxglace=20; vitesse=2;
            if (gpJeu->getZone()==57) force = 40;
            //for (int k = 0; k < 25; k++) effets[k]=0; effets[COUP_EPEE]=2; effets[EPEE_SPIN]=2;
            break;
        case 90 :
            viemax=1; w=15; h=22; animmax=1; typeIA=IA_RANDOM; porte=200; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=15; gpZoneBase->getZone()->h=15;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=7; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 91 :
            viemax=5; w=22; h=47; animmax=1; typeIA=IA_RANDOM; porte=48; force = 0;
            objets[0]=I_FLECHE;objets[1]=I_BOMBE;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=35;
            gpZoneBase->getZone()->x=3; gpZoneBase->getZone()->y=12; 
            zonesAttaques = new ZoneRect(0,0,22,26);
            zonesVulnerables = new ZoneRect(0,0,22,26);
            break;
        case 92 :
            viemax=30; w=121; h=52; animmax=1; typeIA=IA_RANDOM; porte=300; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=121; gpZoneBase->getZone()->h=52;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,0,0);
            zonesVulnerables = new ZoneRect(18,0,85,52); 
            direction=N; typeEnn=E_MONO_DIR; vol=1; recul=0;
            break;
        case 93 :
            viemax=10; w=32; h=32; animmax=0; typeIA=IA_RIEN; porte=300; force = 4;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=32; gpZoneBase->getZone()->h=32;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,0,0);
            zonesVulnerables = new ZoneRect(0,0,0,0);
            direction=N; typeEnn=E_MONO_DIR; nage=1; recul=0;
            break;
        case 94 :
            viemax=20; w=32; h=32; animmax=0; typeIA=IA_RIEN; porte=300; force = 4;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=32; gpZoneBase->getZone()->h=32;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            direction=N; typeEnn=E_MONO_DIR; nage=1; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=0;
            effets[POT]=2; vanim=240;
            break;
        case 95 :
            viemax=10; w=20; h=22; animmax=1; typeIA=IA_RIEN; porte=300; force = 4;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=20; gpZoneBase->getZone()->h=22;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,20,22);
            zonesVulnerables = new ZoneRect(0,0,20,22);
            direction=N; typeEnn=E_PROFIL; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=0; effets[FEU]=2;
            break;
        case 96 :
            viemax=1; w=16; h=16; animmax=0; typeIA=IA_RIEN; porte=300; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=0; recul=0; direction=N; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 97 :
            viemax=200; w=54; h=64; animmax=3; typeIA=IA_RANDOM; porte=300; force = 4;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=24; gpZoneBase->getZone()->h=40;
            gpZoneBase->getZone()->x=15; gpZoneBase->getZone()->y=24; 
            zonesAttaques = new ZoneRect(9,6,35,58);
            zonesVulnerables = new ZoneRect(9,6,35,58);
            direction=N; typeEnn=E_MONO_DIR; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=0; effets[FEU]=2;
            break;
        case 98 :
            viemax=14; w=32; h=32; animmax=0; typeIA=IA_RIEN; porte=300; force = 4;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=32; gpZoneBase->getZone()->h=32;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,0,0);
            zonesVulnerables = new ZoneRect(0,0,0,0);
            direction=N; typeEnn=E_MONO_DIR; nage=1; recul=0;
            break;
        case 99 :
            viemax=70; w=68; h=95; animmax=0; typeIA=IA_RIEN; porte=700; force = 4;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,0,0);
            zonesVulnerables = new ZoneRect(0,0,0,0);
            direction=N; typeEnn=E_MONO_DIR; vol=1; spectre=1; nage=1; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=0; effets[ENNEMI]=2;
            break;
        case 100 :
            viemax=1; w=63; h=31; animmax=0; typeIA=IA_RIEN; porte=0; force = 4;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=0; gpZoneBase->getZone()->h=0;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,0,0);
            direction=N; typeEnn=E_MONO_DIR; vol=1; spectre=1; nage=1; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 101 :
            viemax=5; w=32; h=32; animmax=0; typeIA=IA_RIEN; porte=320; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=0; gpZoneBase->getZone()->h=0;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,0,0);
            zonesVulnerables = new ZoneRect(0,0,32,24);
            direction=N; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=0;
            if (x%320>9*16) direction=O;
            else if (y%240<6*16) direction=N;
            else if (y%240>9*16) direction=S;
            break;
        case 102 :
            viemax=20; w=24; h=21; animmax=1; typeIA=IA_RANDOM; porte=300; force = 3;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h+6;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=30; typeEnn=E_PROFIL; direction=E;
            for (int k = 0; k < 25; k++) effets[k]=1;
            break;
        case 103 :
            viemax=40; w=83; h=83; animmax=5; typeIA=IA_RIEN; porte=300; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(1,6,81,40);
            zonesAttaques->ajout(new ZoneRect(30,46,27,12));
            zonesVulnerables = new ZoneRect(1,6,81,40);
            zonesVulnerables->ajout(new ZoneRect(30,46,27,12));
            maxglace=30; typeEnn=E_PROFIL; direction=E; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=0;
            SDL_SetAlpha(image, SDL_SRCALPHA, 0);
            /*if (gpJeu->getJoueur()->getEpee()>=2) {effets[COUP_EPEE]=1; effets[EPEE_SPIN]=1;}
            if (gpJeu->getJoueur()->hasObjet(O_ARC)==5) effets[FLECHE]=1; */
            special2=-40;
            break;
        case 104 :
            viemax=400; w=32; h=31; animmax=7; typeIA=IA_RANDOM; porte=300; force = 8;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=30; typeEnn=E_MONO_DIR; recul=0;
            break;
        case 105 :
            viemax=21; w=80; h=80; animmax=5; typeIA=IA_FONCE; porte=300; force = 12;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=48; gpZoneBase->getZone()->h=32;
            gpZoneBase->getZone()->x=16; gpZoneBase->getZone()->y=48; 
            zonesAttaques = new ZoneRect(8,16,64,64);
            zonesVulnerables = new ZoneRect(8,16,64,64);
            maxglace=30; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=0; effets[ENNEMI]=2;
            break;
        case 106 :
            viemax=1; w=39; h=48; animmax=1; typeIA=IA_RIEN; porte=300; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=17; gpZoneBase->getZone()->y=24; 
            zonesAttaques = new ZoneRect(0,0,0,0);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=60; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0; effets[ENNEMI]=1;
            break;
        case 107 :
            viemax=120; w=78; h=1/*123*/; animmax=0; typeIA=IA_RIEN; porte=300; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=0; gpZoneBase->getZone()->h=0;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,0,0);
            zonesVulnerables = new ZoneRect(18,0,42,0/*50*/);
            maxglace=60; spectre=1; typeEnn=E_MONO_DIR; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=0; effets[POT]=2;
            if (gpJeu->getKeyboard()->getMode()==13) {w=77; h=51;}
            break;
        case 108 :
            viemax=40; w=42; h=35; animmax=2; typeIA=IA_RANDOM; porte=300; force = 8;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=20; gpZoneBase->getZone()->h=20;
            gpZoneBase->getZone()->x=7; gpZoneBase->getZone()->y=12; 
            zonesAttaques = new ZoneRect(6,0,30,33);
            zonesVulnerables = new ZoneRect(6,8,20,20);
            maxglace=60; typeEnn=E_PROFIL; recul=32; vol=1;
            break;
        case 109 :
            viemax=60; w=123; h=1/*96*/; animmax=3; typeIA=IA_RIEN; porte=300; force = 8;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=0; gpZoneBase->getZone()->h=0;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,0,0);
            zonesVulnerables = new ZoneRect(33,33,57,45);
            maxglace=30; typeEnn=E_PROFIL; recul=0; vol=1; spectre=1; effets[FEU]=1;
            direction=E;
            if (gpJeu->getKeyboard()->getMode()==13) h=96;
            break;
        case 110 :
            viemax=15; w=29; h=32; animmax=31; typeIA=IA_RANDOM; porte=300; force = 8;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=7; gpZoneBase->getZone()->y=16;
            zonesAttaques = new ZoneRect(4,16,21,16);
            zonesVulnerables = new ZoneRect(0,0,29,32);
            maxglace=10; direction=N; typeEnn=E_MONO_DIR; type_att=COUP_GLACE;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 111 :
            viemax=40; w=63; h=48; animmax=1; typeIA=IA_FONCE; porte=300; force = 12;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=32; gpZoneBase->getZone()->h=32;
            gpZoneBase->getZone()->x=16; gpZoneBase->getZone()->y=16; 
            zonesAttaques = new ZoneRect(16,0,32,48);
            zonesVulnerables = new ZoneRect(16,0,32,48);
            maxglace=60; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=0;
            effets[COUP_EPEE]=2; effets[EPEE_SPIN]=2; effets[COUP_GLACE]=1;
            break;
        case 112 :
            viemax=3; w=14; h=15; animmax=1; typeIA=IA_FONCE; porte=100; force = 3;
            objets[0]=I_RUBIS_BLEU;objets[1]=I_RUBIS_BLEU;objets[2]=I_BOMBE;
            gpZoneBase->getZone()->w=14; gpZoneBase->getZone()->h=15;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=30; typeEnn=E_PROFIL; direction=E; type_att=COUP_GLACE;
            break;
        case 113 :
            viemax=30; w=28; h=29; animmax=31; typeIA=IA_RANDOM; porte=300; force = 8;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0;
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(6,10,16,16);
            maxglace=60; direction=N; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0; effets[COUP_GLACE]=1;
            break;
        case 114 :
            viemax=1; w=16; h=32; animmax=2; typeIA=IA_RANDOM; porte=300; force = 8;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=16;
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            direction=S; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0;
            if (gpJeu->getZone()==57) typeIA = IA_RIEN;
            break;
        case 115 :
            viemax=100; w=128; h=1/*91*/; animmax=0; typeIA=IA_RIEN; porte=300; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=0; gpZoneBase->getZone()->h=0;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0;
            zonesAttaques = new ZoneRect(32,67,64,16);
            zonesVulnerables = new ZoneRect(32,0,64,0);
            maxglace=70; direction=S; typeEnn=E_MONO_DIR; recul=0;
            for (int k = 0; k < 25; k++) effets[k]=0; spectre=1; vol=1;
            special2=-30;
            if (gpJeu->getKeyboard()->getMode()==13) {h=91; special2=1;}
            break;
        case 116 :
            viemax=9; w=78; h=1/*68*/; animmax=0; typeIA=IA_RIEN; porte=300; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=0; gpZoneBase->getZone()->h=0;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0;
            zonesAttaques = new ZoneRect(8,32,42,28);
            zonesVulnerables = new ZoneRect(8,32,42,28);
            direction=S; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0; spectre=1; vol=1;
            special2=-5;
            break;
        case 117 :
            viemax=9; w=78; h=1/*68*/; animmax=0; typeIA=IA_RIEN; porte=300; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=0; gpZoneBase->getZone()->h=0;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0;
            zonesAttaques = new ZoneRect(28,32,48,28);
            zonesVulnerables = new ZoneRect(28,32,48,28);
            direction=S; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0; spectre=1; vol=1;
            special2=-15;
            break;
        case 118 :
            viemax=1; w=14; h=15; animmax=1; typeIA=IA_FONCE; porte=100; force = 3;
            objets[0]=I_FLECHE;objets[1]=I_RUBIS_ROUGE;objets[2]=I_RUBIS_ROUGE;
            gpZoneBase->getZone()->w=14; gpZoneBase->getZone()->h=15;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=90; typeEnn=E_PROFIL; direction=E;
            break;
        case 119 :
            viemax=18; w=22; h=27; animmax=1; typeIA=IA_FONCE; porte=300; force = 30;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=3; gpZoneBase->getZone()->y=11; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesAttaques->ajout(new ZoneRect(0,21,5,17));
            zonesVulnerables = new ZoneRect(0,0,w,h); arme = true;
            if (!gpJeu->getJoueur()->getCoffre(10,12)) {
                typeIA=IA_RIEN; porte=300; force = 0; arme=false;
                for (int k = 0; k < 25; k++) effets[k]=0;
            }
            break;
        case 120 :
            viemax=60; w=32; h=32; animmax=0; typeIA=IA_SNIPE; porte=300; force = 20;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=40; recul=0; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=1; effets[ENNEMI]=2; 
            break;
        case 121 :
            viemax=1; w=16; h=16; animmax=1; typeIA=IA_RANDOM; porte=60; force = 1;
            objets[0]=I_PETIT_COEUR;objets[1]=I_RUBIS_VERT;objets[2]=I_RUBIS_VERT;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            break;
        case 122 :
            viemax=1; w=16; h=32; animmax=2; typeIA=IA_RIEN; porte=300; force = 8;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=16;
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            direction=S; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=0; type_att=MORTEL;
            break;
        case 123 :
            viemax=9; w=22; h=26; animmax=1; typeIA=IA_FONCE; porte=300; force = 8;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RUBIS_VERT;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=3; gpZoneBase->getZone()->y=10; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesAttaques->ajout(new ZoneRect(0,20,7,15));
            zonesVulnerables = new ZoneRect(0,0,w,h); arme = true;type_att=ARGENT;
            break;
        case 124 :
            viemax=999; w=16; h=16; animmax=1; typeIA=IA_RIEN; porte=300; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h); type_att=ARGENT;
            break;
        case 125 :
            viemax=999; w=16; h=16; animmax=1; typeIA=IA_RIEN; porte=300; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h); type_att=ARGENT;
            break;
        case 126 :
            viemax=1; w=14; h=15; animmax=1; typeIA=IA_FONCE; porte=100; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RUBIS_VERT;
            gpZoneBase->getZone()->w=14; gpZoneBase->getZone()->h=15;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_PROFIL; direction=E; type_att=ARGENT;
            break;
        case 127 :
            viemax=10; w=79; h=63; animmax=3; typeIA=IA_RIEN; porte=100; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=14; gpZoneBase->getZone()->h=15;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,0,0);
            zonesVulnerables = new ZoneRect(0,0,0,0);
            typeEnn=E_MONO_DIR; type_att=ARGENT;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
        case 128 :
            viemax=200; w=69; h=70; animmax=0; typeIA=IA_RIEN; porte=144; force = 30;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=0; gpZoneBase->getZone()->h=0;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(4,15,61,55);
            zonesVulnerables = new ZoneRect(4,15,61,55); recul=0; spectre=1;
            typeEnn=E_MONO_DIR; type_att=COUP_GLACE; effets[COUP_GLACE]=0;
            break;
        case 129 :
            viemax=30; w=16; h=37; animmax=9; typeIA=IA_ATTEND; porte=30; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=21; 
            zonesAttaques = new ZoneRect(0,5,w,32);
            zonesVulnerables = new ZoneRect(0,5,w,32); recul = 8; vanim = 30; typeEnn=E_MONO_DIR;
            for (int k = 0; k < 25; k++) effets[k]=1; type_att=OMBRE;
            break;
        case 130 :
            viemax=20; w=24; h=31; animmax=20; typeIA=IA_FONCE; porte=200; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=4; gpZoneBase->getZone()->y=15; 
            zonesAttaques = new ZoneRect(0,0,w,h); type_att=OMBRE;
            zonesVulnerables = new ZoneRect(0,0,w,h); vanim=120;
            break;
        case 131 :
            viemax=10; w=16; h=24; animmax=9; typeIA=IA_SNIPE; porte=200; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=8; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            maxglace=40; recul=0; type_att=OMBRE;
            for (int k = 0; k < 25; k++) effets[k]=1; effets[OMBRE]=2;
            break;
        case 132 :
            viemax=5; w=16; h=26; animmax=1; typeIA=IA_FONCE; porte=300; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=10; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h); type_att=OMBRE;
            for (int k = 0; k < 25; k++) effets[k]=1; effets[FEU]=2;
            maxglace=100;
            break;
        case 133 :
            viemax=20; w=24; h=25; animmax=1; typeIA=IA_FONCE; porte=300; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=4; gpZoneBase->getZone()->y=9; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h); type_att=OMBRE;
            for (int k = 0; k < 25; k++) effets[k]=1; effets[FLECHE]=2; recul=8; maxglace=100;
            break;
        case 134 :
            viemax=20; w=22; h=26; animmax=1; typeIA=IA_FONCE; porte=300; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=3; gpZoneBase->getZone()->y=10; 
            zonesAttaques = new ZoneRect(0,0,w,h); type_att=OMBRE;
            zonesAttaques->ajout(new ZoneRect(0,20,7,15));
            zonesVulnerables = new ZoneRect(0,0,w,h); arme = true;
            break;
        case 135 :
            viemax=20; w=24; h=37; animmax=1; typeIA=IA_FONCE; porte=300; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=21; 
            zonesAttaques = new ZoneRect(0,0,w,h); type_att=OMBRE;
            zonesVulnerables = new ZoneRect(0,0,w,h); recul=4; vanim=120;
            break;
        case 136 :
            viemax=30; w=40; h=36; animmax=3; typeIA=IA_FONCE; porte=200; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=20; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=9; gpZoneBase->getZone()->y=19; 
            zonesAttaques = new ZoneRect(9,0,20,h); type_att=OMBRE;
            zonesVulnerables = new ZoneRect(9,0,20,h); recul=4; vanim=120; maxglace=100;
            break;
        case 137 :
            viemax=1; w=16; h=26; animmax=1; typeIA=IA_FONCE; porte=200; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=10; 
            zonesAttaques = new ZoneRect(0,0,w,h); type_att=OMBRE;
            zonesVulnerables = new ZoneRect(0,0,w,h); maxglace=15;
            for (int k = 0; k < 25; k++) effets[k]=1;
            break;
        case 138 :
            viemax=20; w=42; h=30; animmax=1; typeIA=IA_FONCE; porte=200; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=16;
            gpZoneBase->getZone()->x=14; gpZoneBase->getZone()->y=14; 
            zonesAttaques = new ZoneRect(12,0,19,30); type_att=OMBRE;
            zonesVulnerables = new ZoneRect(12,0,19,30); maxglace=30; vitesse=2;
            break;
        case 139 :
            viemax=20; w=22; h=47; animmax=1; typeIA=IA_RANDOM; porte=48; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=35;
            gpZoneBase->getZone()->x=3; gpZoneBase->getZone()->y=12; 
            zonesAttaques = new ZoneRect(0,0,22,26); type_att=OMBRE;
            zonesVulnerables = new ZoneRect(0,0,22,26);
            break;
        case 140 :
            viemax=1; w=14; h=15; animmax=1; typeIA=IA_FONCE; porte=100; force = 1;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=14; gpZoneBase->getZone()->h=15;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_PROFIL; direction=E; type_att=OMBRE;
            break;
        case 141 :
            viemax=500; w=57; h=128; animmax=11; typeIA=IA_RIEN; porte=300; force = 0;
            objets[0]=I_RIEN;objets[1]=I_RIEN;objets[2]=I_RIEN;
            gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
            gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
            zonesAttaques = new ZoneRect(0,0,w,h);
            zonesVulnerables = new ZoneRect(0,0,w,h);
            typeEnn=E_MONO_DIR; direction=E;
            for (int k = 0; k < 25; k++) effets[k]=0;
            break;
    }
    vie=viemax;
    lastAnimTime = SDL_GetTicks();
}
