/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "Menu.h"
#include "Joueur.h"
#include "Monde.h"
#include "Texte.h"
#include "Projectile.h"
#include "Ennemi.h"
#include "Pnj.h"
#include "Jeu.h"

Pnj::Pnj(Jeu* jeu, int type, int i, int j, int msg) : Personnage(), gpJeu(jeu), 
id(type), message(msg), typePnj(P_SIMPLE), immo(false), typeIA(IA_RANDOM), special1(0), 
special2(0) {
    if (id) {
        ostringstream im;
        im << id;
        image = gpJeu->loadImg(("data/images/personnage/personnage" + im.str() + ".png").c_str());
        SDL_SetColorKey(image,SDL_SRCCOLORKEY,SDL_MapRGB(image->format,0,0,255));
        x=i; y=j; saveEmpl(); animmax=1;
        init();
    }
}

Pnj::~Pnj() {
    if (suivant != NULL) {
        Pnj* pnj_ = (Pnj*)suivant;
        suivant = NULL;
        delete pnj_;
    }
}

bool Pnj::isActif() {
    Monde* gpMonde = gpJeu->getMonde();
    return (id && vie && x+w > gpMonde->regionValue(0) && x < gpMonde->regionValue(2)
    && y+h > gpMonde->regionValue(1) && y < gpMonde->regionValue(3));
}

void Pnj::draw(SDL_Surface* gpScreen) {
    if (isActif()) {
        
        if (id == 76 && gpJeu->getJoueur()->hasObjet(O_TROC2)>4) {
            id = 77;
            SDL_FreeSurface(image);
            image = gpJeu->loadImg("data/images/personnage/personnage77.png");
            SDL_SetColorKey(image,SDL_SRCCOLORKEY,SDL_MapRGB(image->format,0,0,255));
        }
        
        int phg[2];
        phg[0] = gpJeu->getPhg(0);
        phg[1] = gpJeu->getPhg(1);
    
        if (!gpJeu->getStop()) IA();
        
        SDL_Rect src;
        SDL_Rect dst;
        
        switch (typePnj) {
            case P_SIMPLE : src.x=direction*w; src.y=h*anim; break;
            case P_MONO_DIR : src.x=0; src.y=h*anim; break;
            case P_PROFIL : src.x=(direction%2)*w; src.y=h*anim; break;
        }
        dst.x=x-phg[0]; dst.y=y-phg[1]; src.w=w; src.h=h;
        
        if (id == 58 && animmax > 0) {src.y+=27;}
        
        if (id == 90 && direction == N) {src.x=w; if (vie < 3) vie++;}
        if (id == 90 && direction == O) {src.x=w*2;}
        
        //marchand troc
        if (gpJeu->getZone()>15 && gpJeu->isDehors() &&
        (id == 2 ||id == 7 || id == 20 || id == 12 || id == 24 || id == 45)) src.h=18;
        
        if (id == 46 && immo) src.y=h*2;
        if (id == 65 && 
        (gpJeu->getZone()!=34 || x==37*16 || x==41*16+10 || x==38*16+6 || x==40*16+4) &&
        (gpJeu->getZone()!=155 || x==68*16+5+4 || x==66*16+5+4 || x==70*16+5-4 || x==72*16+5-4
        || x==129*16+5 || x==127*16+5)) 
            src.y=h*2;
        
        if (id==82 && animmax>0) {src.y=h*(anim/4)+h;}
        
        if (id==15 && gpJeu->getZone()==57 && x==162*16+8 && y==19*16+9 
        && direction==E && !gpJeu->getJoueur()->getEnnemi(50)) {
            src.x=64; src.y=0;
        }
        if (id==15 && gpJeu->getZone()==60 && x==62*16 && y==81*16+9 
        && direction==E && gpJeu->getEnnemi()->getSuivant()->getSpecial(2) < 12) {
            src.x=64; src.y=0;
        }
        if (id==90 && gpJeu->getZone()==60 && x<80*16-20-8 && direction==O
        && gpJeu->getEnnemi()->getSuivant()->getSpecial(2) < 13) {
            if (x > 77*16) {src.x=60; src.w=31; dst.x-=3;}
            else if (x > 75*16) {src.x=91; src.w=31; dst.x-=15;}
            else if (x > 73*16) {src.x=122; src.w=36; dst.x-=20;}
            else {src.x=158; src.w=41; dst.x-=25;}
        }
        
        SDL_BlitSurface(image, &src, gpScreen, &dst);
        
        if(animmax){    
            if(SDL_GetTicks() > lastAnimTime + 240 && !gpJeu->getStop()) {
            lastAnimTime = SDL_GetTicks();
                anim++;
                if (anim > animmax) anim = 0;
            }
        }
    }
    if (suivant != NULL) ((Pnj*)suivant)->draw(gpScreen);
}

void Pnj::moveX(int i) {
    if (gpJeu->isLink(x + gpZoneBase->getZone()->x + i, y + gpZoneBase->getZone()->y, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h)) return;
    if (gpJeu->isEnnemi(x + gpZoneBase->getZone()->x + i, y + gpZoneBase->getZone()->y, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h)) return;
    if (gpJeu->isPnj(x + gpZoneBase->getZone()->x + i, y + gpZoneBase->getZone()->y, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h, getListId())) return;
    if (!gpJeu->isNotFull(x + gpZoneBase->getZone()->x + i, y + gpZoneBase->getZone()->y, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h, 0, 0, 0)) return;
    x+=i;
}

void Pnj::moveY(int i) {
    if (gpJeu->isLink(x + gpZoneBase->getZone()->x, y + gpZoneBase->getZone()->y + i, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h)) return;
    if (gpJeu->isEnnemi(x + gpZoneBase->getZone()->x, y + gpZoneBase->getZone()->y + i, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h)) return;
    if (gpJeu->isPnj(x + gpZoneBase->getZone()->x, y + gpZoneBase->getZone()->y + i, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h, getListId())) return;
    if (!gpJeu->isNotFull(x + gpZoneBase->getZone()->x, y + gpZoneBase->getZone()->y + i, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h, 0, 0, 0)) return;
    y+=i;
}

Pnj* Pnj::getSuivant() {return (Pnj*)suivant;}

int Pnj::getMessage() {return message;}

void Pnj::setMessage(int i) {message=i;}

void Pnj::setTypeIA(int i) {typeIA=i;}

void Pnj::setImmo(bool b) {immo=b;}

int Pnj::getId() {return id;}

void Pnj::revie() {
    special1=0; special2=0;
    if (gpJeu->getZone()==20 || gpJeu->getZone()==56 || gpJeu->getZone()==140) return;
    if (gpJeu->getZone()==154 && ((id==46 && gpJeu->getJoueur()->hasObjet(O_TROC1)>5) 
    || (id==90 && gpJeu->getJoueur()->getCoffre(15,28)))) vie=0;
    else { vie = 1; x = xdep; y = ydep;}
    if (suivant != NULL) getSuivant()->revie();
}

void Pnj::IA() {
    /*if (id == 47 && gpJeu->getJoueur()->getAvancement()==1 && gpJeu->getZone()==1) {
        if (x<40*16+8) {direction=E; x++;}
        else {vie=0;gpJeu->getJoueur()->setImmo(false);}
    }
    
    if (id == 33 && gpJeu->getJoueur()->getAvancement()==9) {
        if (y<16*16+8 && x>69*16+8 && y>15*16+8) {direction=S; moveY(1);}
        else if (x>69*16+8) {direction=O; moveX(-1);}
        else if (y>15*16+8) {direction=N; moveY(-1);}
        else {direction=S; gpJeu->getJoueur()->setAvancement(10);}
    }*/
    
    if (id == 15 && gpJeu->getZone() == 64 && !gpJeu->getJoueur()->hasObjet(O_CARTE)) {
        if (y > 12*16-8) y--;
        else {
            if (gpJeu->getJoueur()->getAvancement()==STELE_LUE) gpJeu->ecrit(320);
            else {
                if (gpJeu->getJoueur()->getX()<8*16+8 
                || gpJeu->getJoueur()->getX()>10*16+8 || x < 7*16+8 || y == 8*16-8) {
                    if (y > 8*16-8) {y--; direction=N;}
                    else {
                        if (x < 9*16+8) {x++; direction=E;}
                        else {
                            direction=N;
                            gpJeu->getJoueur()->setImmo(false); 
                            gpJeu->getJoueur()->setDirection(N);
                            gpJeu->ecrit(321);
                        }
                    }
                }
                else {x--; direction=O;}
            }
        }
    }
    
    if (id == 15 && gpJeu->getZone() == 64 && gpJeu->getJoueur()->getEpee() == 2
    && (x < 12*16 || direction == E)) {
        if (x < 12*16) {x++; direction=E;}
        else {direction=S; gpJeu->getJoueur()->setImmo(false);}
    }
    
    if (id == 15 && gpJeu->getJoueur()->getAvancement()==ZELDA_SOUS_SOL 
    && gpJeu->getZone()==57 && y==171*16+9 && x>=100*16+8 && x<102*16+8) {
        direction=E; x++;
        if (x == 102*16+8) {
            saveEmpl(); gpJeu->getJoueur()->setImmo(false); gpJeu->ecrit(1024);
        }
    }
    
    if (id == 15 && gpJeu->getZone()==57 && !gpJeu->getJoueur()->getEnnemi(50) 
    && y<=21*16+9 && x>=160*16+8 && immo==false) {
        if (x<162*16+8) {x++; direction=E;}
        else if (y > 19*16+9) {y--; direction=N;}
        else {
            direction=E; immo=true;
            gpJeu->getAudio()->playSound(25);
            gpJeu->ajouteProjectile(33, direction, x+4, y+7, 8);
        }
    }
    
    if (id == 15 && gpJeu->getZone()==60 && immo==false) {
        gpZoneBase->getZone()->y=7; gpZoneBase->getZone()->h=16;
        if (x<62*16) {moveX(1); direction=E;}
        else {
            direction=E; immo=true;
            gpJeu->getAudio()->playSound(25);
            gpJeu->ajouteProjectile(33, direction, x+4, y+7, 8);
        }
    }
    
    if (id == 90 && gpJeu->getZone()==60 && immo==false) {
        gpZoneBase->getZone()->y=11; gpZoneBase->getZone()->h=16;
        gpZoneBase->getZone()->x=3; gpZoneBase->getZone()->w=16;
        if (x>72*16) {moveX(-4); direction=O;}
        else {
            direction=O; immo=true;
            gpJeu->testEpee(x-48, y, 16, 16, ENNEMI, 1, direction);
        }
    }
    
    
    
    if (id == 65 && gpJeu->getZone()==34 && gpJeu->getJoueur()->getCoffre(15,1)) {
        if (x<=38*16+6) {if (x>37*16) moveX(-1);}
        else {if (x<41*16+10) moveX(1);}
    }
    
    if (id == 65 && gpJeu->getZone()==155 
    && gpJeu->getJoueur()->getAvancement()==MOT_DE_PASSE_DONNE) {
        if (x<=68*16+5+4) {if (x>66*16+5+4) moveX(-1); if (x==66*16+5+4) saveEmpl();}
        else if (x<127*16+5) {if (x<72*16+5-4) moveX(1); if (x==72*16+5-4) saveEmpl();}
    }
    if (id == 65 && gpJeu->getZone()==155 
    && gpJeu->getJoueur()->getAvancement()==MULTIPASSE_UTILISE) {
        xdep = 127*16+5;
        if (x>127*16+5) moveX(-1);
        if (x==127*16+5) saveEmpl();
    }
    
    if (id == 71 /*&& direction==S*/) {
        int d = direction;
        if (abs(x+16-(gpJeu->getJoueur()->getX()+8))<=4*16
        && abs(y+16-(gpJeu->getJoueur()->getY()+16))<=4*16) direction=N;
        else direction=S;
        if (direction!=d) gpJeu->ajouteProjectile(8, direction, x+8, y+8, 0);
    }
    
    if (id == 52 && gpJeu->getZone() == 140 && gpJeu->getJoueur()->getCoffre(15,26)) {
        if (y<=10*16) moveY(1);
        else if (x<9*16+8) {moveX(1); direction=E;}
        else if (y<13*16+8) {moveY(1); direction=S;}
        else if (y<14*16+8) y++;
        else vie=0;
    }
    
    if (id == 46 && !immo) {
        gpZoneBase->getZone()->x=3; gpZoneBase->getZone()->w=16;   
        if (y<28*16) moveY(1);
        else if (y<29*16+8) y++;
        else vie=0;
    }
    
    if (id == 58 && gpJeu->getJoueur()->getAvancement()==PARLE_GARDE_RESERVE 
    && gpJeu->getZone()==57 && x==77*16+5-8 && y<=36*16+8 && y >34*16+8) {
        direction=N; animmax=1; moveY(-1);
        if (y == 34*16+8) {direction=O; anim=0; animmax=0; saveEmpl();}
    }
    
    if (id == 58 && gpJeu->getJoueur()->getAvancement()==RESERVE_VIDE 
    && gpJeu->getZone()==57 && y==31*16+8 && x<=69*16+5 && x>67*16+5) {
        direction=O; animmax=1; moveX(-1);
        if (x == 67*16+5) {direction=S; anim=0; animmax=0; saveEmpl();}
    }
    
    if (id == 58 && gpJeu->getJoueur()->getAvancement()==PARLE_GARDE_CH_FORTE 
    && gpJeu->getZone()==57 && x==77*16+5-8 && y<=51*16+8 && y >49*16+8) {
        direction=N; animmax=1; moveY(-1);
        if (y == 49*16+8) {direction=O; anim=0; animmax=0; saveEmpl();}
    }
    
    if (id == 58 && gpJeu->getJoueur()->getAvancement()==PARLE_GARDE_SOUS_SOL 
    && gpJeu->getZone()==57 && x==97*16+5-8 && y<=171*16+8*16+8 && y >169*16+8) {
        direction=N; animmax=1; moveY(-1);
        if (y == 169*16+8) {direction=O; anim=0; animmax=0; saveEmpl();}
    }
    
    if (id == 6 && gpJeu->getZone()==58 && gpJeu->getJoueur()->getCoffre(12,13)) {
        if (gpJeu->getMonde()->regionValue(0) == 0 
        && gpJeu->getMonde()->regionValue(1) == 75*16) {
            if (special2 < 3) {
                special1++;
                if (special1 >= 50) {
                    Ennemi* enn = gpJeu->getEnnemi()->getSuivant();
                    while (enn != NULL) {
                        if (enn->isActif() && enn->getEnnId()==125 
                        && enn->getX()<9*16 && enn->getSpecial(2)==0) {
                            enn->setVie(enn->getVieMax()-1);
                            break;
                        }
                        enn = enn->getSuivant();
                    }
                    special2++;
                    special1=0;
                    if (special2 == 3) {
                        int tot = 0;
                        Ennemi* enn = gpJeu->getEnnemi()->getSuivant();
                        while (enn != NULL) {
                            if (enn->isActif() && enn->getEnnId()==125 
                            && enn->getX()<9*16 && enn->getSpecial(2)) {
                                tot += (enn->getSpecial(1)+1);
                            }
                            enn = enn->getSuivant();
                        }
                        if (tot >= 12) {
                            special2 = 4; gpJeu->getJoueur()->setCoffre(12,13,3);
                        } else {
                            enn = gpJeu->getEnnemi()->getSuivant();
                            while (enn != NULL) {
                                if (enn->isActif() && enn->getEnnId() == 125) {
                                    if (enn->getX() > 9*16) enn->setTypeIA(IA_RANDOM);
                                }
                                enn = enn->getSuivant();
                            }
                        }
                    }
                }
            }
            else if (special2 < 4) {
                if (y<82*16) {moveY(1); direction=S;}
                else {if (x>12*16) moveX(-1);}
            }
        }
        if (gpJeu->getMonde()->regionValue(0) == 20*16 
        && gpJeu->getMonde()->regionValue(1) == 60*16) {
            if (y<67*16) {moveY(1); direction=S;}
            else {if (x>28*16) moveX(-1);}
        }
        if (gpJeu->getMonde()->regionValue(0) == 40*16 
        && gpJeu->getMonde()->regionValue(1) == 0) {
            if (y<7*16) {moveY(1); direction=S;}
            else {if (x>48*16) moveX(-1);}
        }
        if (gpJeu->getMonde()->regionValue(0) == 80*16 
        && gpJeu->getMonde()->regionValue(1) == 15*16) {
            if (special2 == 0) {
                special1++;
                if (special1 >= 50) {
                    Ennemi* enn = gpJeu->getEnnemi()->getSuivant();
                    while (enn != NULL) {
                        if (enn->isActif() && enn->getEnnId()==125 
                        && enn->getX()<85*16 && enn->getSpecial(2)==0) {
                            enn->setVie(enn->getVieMax()-1);
                            break;
                        }
                        enn = enn->getSuivant();
                    }
                    special2++;
                    special1=0;
                    
                    enn = gpJeu->getEnnemi()->getSuivant();
                    while (enn != NULL) {
                        if (enn->isActif() && enn->getEnnId() == 125) {
                            if (enn->getX() > 85*16) enn->setTypeIA(IA_RANDOM);
                        }
                        enn = enn->getSuivant();
                    }
                }
            }
            else {
                if (y<22*16) {moveY(1); direction=S;}
                else {if (x>90*16) moveX(-1);}
            }
        }
        if (gpJeu->getMonde()->regionValue(0) == 100*16 
        && gpJeu->getMonde()->regionValue(1) == 60*16) {
            if (special2 < 4) {
                special1++;
                if (special1 >= 50) {
                    Ennemi* enn = gpJeu->getEnnemi()->getSuivant();
                    while (enn != NULL) {
                        if (enn->isActif() && enn->getEnnId()==125 && enn->getSpecial(2)==0) {
                            enn->setVie(enn->getVieMax()-1);
                            break;
                        }
                        enn = enn->getSuivant();
                    }
                    special2++;
                    special1=0;
                    if (special2 == 4) {
                        bool gagne = false;
                        int min = 6;
                        int max = 0;
                        Ennemi* enn = gpJeu->getEnnemi()->getSuivant();
                        while (enn != NULL) {
                            if (enn->isActif() && enn->getEnnId()==125 && enn->getSpecial(2)) {
                                gagne = gagne || 
                                (enn->getSpecial(1)+1) == gpJeu->getJoueur()->getCoffre(12,13);
                                if (min > (enn->getSpecial(1)+1)) min = (enn->getSpecial(1)+1);
                                if (max < (enn->getSpecial(1)+1)) max = (enn->getSpecial(1)+1);
                            }
                            enn = enn->getSuivant();
                        }
                        if (gagne) {
                            gpJeu->getJoueur()->setCoffre(12,13,2);
                        } else {
                            if (gpJeu->getJoueur()->getCoffre(12,13) == 1) {
                                gpJeu->getJoueur()->setBoostGanon(-(10*(min-1)));
                            } else {
                                gpJeu->getJoueur()->setBoostGanon(-(10*(6-max)));
                            }
                            gpJeu->getJoueur()->setCoffre(12,13,3);
                        }
                        gpJeu->getJoueur()->setImmo(false);
                        gpJeu->ecrit(message);
                    }
                }
            }
        }
        if (gpJeu->getMonde()->regionValue(0) == 120*16 
        && gpJeu->getMonde()->regionValue(1) == 75*16) {
            if (y>82*16) {moveY(-1); direction=N;}
            else {if (x>125*16) moveX(-1);}
        }
    }
    
    
    
    
    
    /*if (id == 49 && !immo) {
        if (x<13*16) moveX(1);
        else if (y>4*16) moveY(-1);
        else immo=true;
    }
    if (id == 50 && !immo) {
        if (x>6*16) moveX(-1);
        else if (y>4*16) moveY(-1);
        else immo=true;
    }*/
    
    if (gpJeu->getZone() == 60 && (id == 90 || id == 15)) return;
    if (immo) return;
    if (parle()) return;
    if (typeIA==IA_SUIT) suit();
    if (typeIA==IA_RANDOM) bouge();
}

void Pnj::bouge() {
    int randomValue = (int)((float)rand() / RAND_MAX * (100));    
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
}

void Pnj::suit() {
    Joueur* gpJoueur = gpJeu->getJoueur();
    int pnjCX = x + gpZoneBase->getZone()->x + (gpZoneBase->getZone()->w/2);
    int pnjCY = y + gpZoneBase->getZone()->y + (gpZoneBase->getZone()->h);
    int linkCX = gpJoueur->getX() + 8;
    int linkCY = gpJoueur->getY() + 24;
    int difx = pnjCX - linkCX;
    int dify = pnjCY - linkCY;
    
    //test portée
    
    
    if ( max(abs(difx),abs(dify))>128) {
        if (gpJoueur->getAvancement()==6) gpJoueur->setAvancement(5);
        return;
    }
//    if (max(abs(difx),abs(dify))<16) return;
    if (gpJoueur->getAvancement()==5) gpJoueur->setAvancement(6);
    
    if (abs(difx) > abs(dify)) {
        if (difx>0) direction=O;
        else direction=E;
    }
    else {
        if (dify>0) direction=N;
        else direction=S;
    }
    
    if (gpJeu->getJoueur()->getX() < x) moveX(-1);
    if (gpJeu->getJoueur()->getX() > x) moveX(1);
    if (gpJeu->getJoueur()->getY() < y) moveY(-1);
    if (gpJeu->getJoueur()->getY() > y) moveY(1);
}

bool Pnj::parle() {
    Joueur* gpJoueur = gpJeu->getJoueur();
    int difx = (gpJoueur->getX()+8)-(x+(w/2));
    int dify = (gpJoueur->getY()+16)-(y+(h/2));
    
    if (abs(difx) < 24 && abs(dify) < 24) {
        if (abs(difx) < abs(dify)) {
            if (dify < 0) direction = N;
            else direction = S;
        }
        else {
            if (difx < 0) direction = O;
            else direction = E;
        }
        return true;
    }
    return false;
    
    if (gpJeu->isLink(x + gpZoneBase->getZone()->x-8, 
    y + gpZoneBase->getZone()->y+gpZoneBase->getZone()->h-8, 1, 1)) {
        direction = O;
        return true;
    }
    if (gpJeu->isLink(x + gpZoneBase->getZone()->x+gpZoneBase->getZone()->w+7, 
    y + gpZoneBase->getZone()->y+gpZoneBase->getZone()->h-8, 1, 1)) {
        direction = E;
        return true;
    }
    if (gpJeu->isLink(x + gpZoneBase->getZone()->x, y + gpZoneBase->getZone()->y-8, 1, 1)) {
        direction = N;
        return true;
    }
    if (gpJeu->isLink(x + gpZoneBase->getZone()->x, 
    y + gpZoneBase->getZone()->y+gpZoneBase->getZone()->h+7, 1, 1)) {
        direction = S;
        return true;
    }
    return false;
}

void Pnj::setAnimmax(int m) {animmax=m;}

void Pnj::setVie(int i) {vie=i;}

void Pnj::init() {
    switch(id){
        case 1: case 13: case 14: case 23: case 33: case 56 : case 69 : w=16; h=25; break;
        case 2: case 18: case 43: case 45: case 63 : 
            w=16; h=24; typePnj = P_MONO_DIR; immo = true; break;
        case 3: w=16; h=23; typePnj = P_PROFIL; break;
        case 4: w=16; h=17; animmax=3; typePnj = P_MONO_DIR; break;
        case 5: case 83: w=13; h=16; break;
        case 6: w=15; h=16; typePnj = P_PROFIL; break;
        case 7: case 12: case 19: case 25: case 34: case 62 : case 84 :
            w=16; h=25; typePnj = P_MONO_DIR; immo = true; break;
        case 8: case 40: case 41: case 42: w=16; h=23; typePnj = P_MONO_DIR; immo = true; break;
        case 9: w=16; h=27; /*typePnj = P_MONO_DIR;*/ immo = true; break;
        case 10: case 20: w=16; h=26; animmax=3; typePnj = P_MONO_DIR; immo = true; break;
        case 11: case 36: case 47: case 52: w=16; h=24; break;
        case 15: w=16; h=23; immo = true; typeIA=IA_RIEN; break;
        case 16: case 48: w=32; h=48; typePnj = P_MONO_DIR; immo = true; break;
        case 17: w=18; h=25; typePnj = P_MONO_DIR; immo = true; break;
        case 21: case 55: case 98 : case 99 : 
            w=17; h=25; typePnj = P_MONO_DIR; immo = true; break;
        case 22: case 73 : w=16; h=29; animmax=3; typePnj = P_MONO_DIR; immo = true; break;
        case 24: w=16; h=21; typePnj = P_MONO_DIR; immo = true; break;
        case 26: w=39; h=30; animmax=3; typePnj = P_MONO_DIR; immo = true; break;
        case 27: case 30: case 31: case 64 : w=16; h=17; typePnj = P_MONO_DIR; immo = true; break;
        case 28: w=25; h=35; animmax=4; typePnj = P_MONO_DIR; immo = true; break;
        case 29: w=21; h=27; animmax=4; typePnj = P_MONO_DIR; immo = true; break;
        case 32: case 54: w=16; h=23; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 35: w=16; h=22; animmax=3; typePnj = P_MONO_DIR; immo = true; break;
        case 37: w=19; h=22; break;
        case 38: w=16; h=16; break;
        case 39: w=24; h=16; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 44: w=28; h=28; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 46: case 65 : w=22; h=27; animmax=1; typePnj = P_MONO_DIR; immo = true; 
            typeIA=IA_RIEN; break;
        case 49: case 50: w=16; h=16; animmax=1; typePnj = P_MONO_DIR; immo = true; 
            typeIA=IA_RIEN; break;
        case 51: w=16; h=27; typePnj = P_PROFIL; break;
        case 53: w=16; h=17; typePnj = P_MONO_DIR; immo = true; break;
        case 57 : case 58 : w=22; h=27; animmax=0; immo = true; break;
        case 59: w=15; h=17; typePnj = P_MONO_DIR; immo = true; break;
        case 60: w=16; h=22; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 61: w=17; h=19; break;
        case 66: w=16; h=29; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 67: w=16; h=32; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 68 : w=22; h=27; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 70 : w=23; h=25; animmax=2; typePnj = P_MONO_DIR; immo = true; break;
        case 71 : w=32; h=32; animmax=3; /*typePnj = P_MONO_DIR;*/ immo = true; break;
        case 72 : w=20; h=38; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 74 : w=16; h=25; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 75 : case 76 : case 77 : w=26; h=32; animmax=1; typePnj = P_PROFIL; break;
        case 78 : case 80 : w=16; h=25; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 79 : w=24; h=27; animmax=2; typePnj = P_MONO_DIR; immo = true; break;
        case 81 : w=24; h=27; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 82 : w=16; h=25; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 85 : w=16; h=25; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 86 : w=16; h=25; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 87 : w=17; h=24; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 88 : w=16; h=24; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 89 : w=20; h=27; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 90 : w=20; h=27; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 91 : w=23; h=13; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 92 : w=23; h=13; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 93 : w=23; h=14; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 94 : w=23; h=13; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 95 : w=23; h=14; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 96 : w=16; h=29; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 97 : w=16; h=25; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 100 : w=28; h=28; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 101 : w=30; h=32; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 102 : w=16; h=25; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 103 : case 104 : w=16; h=24; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 105 : w=22; h=27; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 106 : w=18; h=32; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 107 : w=20; h=32; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 108 : w=16; h=32; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 109 : w=35; h=30; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 110 : w=44; h=40; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 111 : w=12; h=26; animmax=3; typePnj = P_MONO_DIR; immo = true; break;
        case 112 : w=16; h=28; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 113 : w=12; h=22; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 114 : w=16; h=28; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
    }
    gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
    gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
    
    //if (id == 15) {gpZoneBase->getZone()->y=7; gpZoneBase->getZone()->h=16;}
    if (id == 16 || id == 48 || id == 79) {gpZoneBase->getZone()->h+=4;}
    //if (id == 33) {gpZoneBase->getZone()->y=9; gpZoneBase->getZone()->h=16; immo = true;}
    if (id == 46 && gpJeu->getZone()!=154) {
        gpZoneBase->getZone()->y=11; gpZoneBase->getZone()->h=16;}
    if (id == 47) {immo = true;if(gpJeu->getZone()==1)direction=N;}
    if (id == 65 && gpJeu->getZone()==34) {
        gpZoneBase->getZone()->y+=10; gpZoneBase->getZone()->h-=10;}
    if (id == 70) gpZoneBase->getZone()->w=16;
    if (id == 72) {gpZoneBase->getZone()->w=16; gpZoneBase->getZone()->h=29;}
    if (id == 100) {gpZoneBase->getZone()->w=16;}
}
