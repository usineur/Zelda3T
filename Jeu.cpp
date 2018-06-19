/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "Joueur.h"
#include "Monde.h"
#include "Menu.h"
#include "Texte.h"
#include "Projectile.h"
#include "Jeu.h"
#include "Keyboard.h"

#include <cstdlib>
#include <iostream>

Jeu::Jeu(Audio* audio) : gpAudio(audio), gpGenerique(0), gpKeyboard(0),
zone(1), stop(false), transition(false),
menu(false), text(false), vueHorz(0), vueVert(0) {
    phg[0] = 0;
    phg[1] = 0;
    
    imageObjets = loadImg("data/images/objet/objets.png");
    SDL_SetColorKey(imageObjets,SDL_SRCCOLORKEY,SDL_MapRGB(imageObjets->format,0,0,255));
    
    gpProjectile = NULL; gpObjet = NULL; gpSnipe = NULL; gpCaisse = NULL; gpEnnemi = NULL;
    gpPiege = NULL; gpPnj = NULL; gpJoueur = NULL; gpMonde = NULL; gpMenu = NULL;
    gpStatut = NULL;
    gpTexte = new Texte(this);

    gpProjectileOld = NULL;
    gpObjetOld = NULL;
    gpSnipeOld = NULL;
    gpCaisseOld = NULL;
    gpEnnemiOld = NULL;
    gpPiegeOld = NULL;
    gpPnjOld = NULL;
}

Jeu::~Jeu() {
    delete gpMonde;
    delete gpJoueur;
    delete gpMenu;
    delete gpTexte;
    delete gpStatut;
    delete gpProjectile;
    delete gpObjet;
    delete gpSnipe;
    delete gpCaisse;
    delete gpEnnemi;
    delete gpPiege;
    delete gpPnj;

    if (gpProjectileOld != NULL) {
        delete gpProjectileOld;
    }
    if (gpObjetOld != NULL) {
        delete gpObjetOld;
    }
    if (gpSnipeOld != NULL) {
        delete gpSnipeOld;
    }
    if (gpCaisseOld != NULL) {
        delete gpCaisseOld;
    }
    if (gpEnnemiOld != NULL) {
        delete gpEnnemiOld;
    }
    if (gpPiegeOld != NULL) {
        delete gpPiegeOld;
    }
    if (gpPnjOld != NULL) {
        delete gpPnjOld;
    }

    SDL_FreeSurface(imageObjets);
}

void Jeu::init(int save) {
    zone=79; zoneOld=-1;
    if (gpProjectile != NULL) {
        delete gpProjectile;
    }
    gpProjectile = new Projectile(this, 0, N, 0, 0, 0);
    if (gpObjet != NULL) {
        delete gpObjet;
    }
    gpObjet = new Objet(this, 0, 0, 0, 0);
    if (gpSnipe != NULL) {
        delete gpSnipe;
    }
    gpSnipe = new Snipe(this, 0, 0, 0, 0, 0);
    if (gpCaisse != NULL) {
        delete gpCaisse;
    }
    gpCaisse = new Caisse(this, 0, 0, 0);
    if (gpEnnemi != NULL) {
        delete gpEnnemi;
    }
    gpEnnemi = new Ennemi(this, 0, 0, 0, true);
    if (gpPiege != NULL) {
        delete gpPiege;
    }
    gpPiege = new Ennemi(this, 0, 0, 0, true);
    if (gpPnj != NULL) {
        delete gpPnj;
    }
    gpPnj = new Pnj(this, 0, 0, 0, 0);
    if (gpJoueur != NULL) {
        delete gpJoueur;
    }
    gpJoueur = new Joueur(this, save);
    if (gpMonde != NULL) {
        delete gpMonde;
    }
    gpMonde = new Monde(this);
    if (gpMenu != NULL) {
        delete gpMenu;
    }
    gpMenu = new Menu(this);
    //gpTexte = new Texte(this);
    if (gpStatut != NULL) {
        delete gpStatut;
    }
    gpStatut = new Statut(this);
    //gpAudio->playMusic(zone);
    
    if (gpProjectileOld != NULL) {
        delete gpProjectileOld;
    }
    gpProjectileOld = NULL;
    if (gpObjetOld != NULL) {
        delete gpObjetOld;
    }
    gpObjetOld = NULL;
    if (gpSnipeOld != NULL) {
        delete gpSnipeOld;
    }
    gpSnipeOld = NULL;
    if (gpCaisseOld != NULL) {
        delete gpCaisseOld;
    }
    gpCaisseOld = NULL;
    if (gpEnnemiOld != NULL) {
        delete gpEnnemiOld;
    }
    gpEnnemiOld = NULL;
    if (gpPiegeOld != NULL) {
        delete gpPiegeOld;
    }
    gpPiegeOld = NULL;
    if (gpPnjOld != NULL) {
        delete gpPnjOld;
    }
    gpPnjOld = NULL;
    
    if ((zone == 18 || zone == 19) && 
    ((gpJoueur->getEpee()==0 && !gpJoueur->hasObjet(O_OCARINA)) 
    || (gpJoueur->getEpee()==5 && zone == 19 
    && !gpJoueur->getEnnemi(50)))) 
        gpAudio->playMusic(218);
    else if (zone == 137 && gpJoueur->nbCristaux()>=3 && gpJoueur->hasObjet(O_TROC4)>=6 
    && !gpJoueur->hasCristal(3)) gpAudio->playMusic(218);
    else if (zone == 4 && gpJoueur->getCoffre(15,2)) gpAudio->playMusic(219);
    else if (/*isDehors() && */gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_UTILISE
    && gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_FERME
    && getEpoque()==T_PRESENT) gpAudio->playMusic(199);
    else if (zone==10 && gpJoueur->nbCristaux()>=3 && gpJoueur->hasObjet(O_TROC4)>=6
        && !gpJoueur->hasCristal(3)) gpAudio->playMusic(218);
    else if ((zone == 111 || zone == 114 || zone == 124) 
        && gpJoueur->nbEnnemis() >= 87) gpAudio->playMusic(218);
    else gpAudio->playMusic(zone);
    
    if (isDonjon()) ecrit(927+zone-46);
    else if (zone==57) ecrit(1036);
}

void Jeu::setKeyboard(Keyboard* kb) {
    gpKeyboard = kb;
}

void Jeu::setGenerique(Generique* gen) {
    gpGenerique = gen;
}

void Jeu::videListes() {
    delete gpProjectile;
    gpProjectile = new Projectile(this, 0, N, 0, 0, 0);
    delete gpObjet;
    gpObjet = new Objet(this, 0, 0, 0, 0);
    delete gpSnipe;
    gpSnipe = new Snipe(this, 0, 0, 0, 0, 0);
    delete gpCaisse;
    gpCaisse = new Caisse(this, 0, 0, 0);
    delete gpEnnemi;
    gpEnnemi = new Ennemi(this, 0, 0, 0, true);
    delete gpPiege;
    gpPiege = new Ennemi(this, 0, 0, 0, true);
    delete gpPnj;
    gpPnj = new Pnj(this, 0, 0, 0, 0);
}

void Jeu::videListesOld() {
    delete gpProjectileOld;
    gpProjectileOld = new Projectile(this, 0, N, 0, 0, 0);
    delete gpObjetOld;
    gpObjetOld = new Objet(this, 0, 0, 0, 0);
    delete gpSnipeOld;
    gpSnipeOld = new Snipe(this, 0, 0, 0, 0, 0);
    delete gpCaisseOld;
    gpCaisseOld = new Caisse(this, 0, 0, 0);
    delete gpEnnemiOld;
    gpEnnemiOld = new Ennemi(this, 0, 0, 0, true);
    delete gpPiegeOld;
    gpPiegeOld = new Ennemi(this, 0, 0, 0, true);
    delete gpPnjOld;
    gpPnjOld = new Pnj(this, 0, 0, 0, 0);
}

void Jeu::saveOldMap() {
    zoneOld = zone;
    videListesOld();
    
    gpProjectileOld->setSuivant(gpProjectile->getSuivant());
    gpObjetOld->setSuivant(gpObjet->getSuivant());
    gpSnipeOld->setSuivant(gpSnipe->getSuivant());
    gpCaisseOld->setSuivant(gpCaisse->getSuivant());
    gpEnnemiOld->setSuivant(gpEnnemi->getSuivant());
    gpPiegeOld->setSuivant(gpPiege->getSuivant());
    gpPnjOld->setSuivant(gpPnj->getSuivant());
    
    gpProjectile->setSuivant(NULL);
    gpObjet->setSuivant(NULL);
    gpSnipe->setSuivant(NULL);
    gpCaisse->setSuivant(NULL);
    gpEnnemi->setSuivant(NULL);
    gpPiege->setSuivant(NULL);
    gpPnj->setSuivant(NULL);
}

void Jeu::restoreOldMap() {
    zone = zoneOld;
    videListes();
    
    gpProjectile->setSuivant(gpProjectileOld->getSuivant());
    gpObjet->setSuivant(gpObjetOld->getSuivant());
    gpSnipe->setSuivant(gpSnipeOld->getSuivant());
    gpCaisse->setSuivant(gpCaisseOld->getSuivant());
    gpEnnemi->setSuivant(gpEnnemiOld->getSuivant());
    gpPiege->setSuivant(gpPiegeOld->getSuivant());
    gpPnj->setSuivant(gpPnjOld->getSuivant());
    
    gpProjectileOld->setSuivant(NULL);
    gpObjetOld->setSuivant(NULL);
    gpSnipeOld->setSuivant(NULL);
    gpCaisseOld->setSuivant(NULL);
    gpEnnemiOld->setSuivant(NULL);
    gpPiegeOld->setSuivant(NULL);
    gpPnjOld->setSuivant(NULL);
    
    if ((zone == 18 || zone == 19) && 
    ((gpJoueur->getEpee()==0 && !gpJoueur->hasObjet(O_OCARINA)) 
    || (gpJoueur->getEpee()==5 && zone == 19 
    && !gpJoueur->getEnnemi(50)))) 
        gpAudio->playMusic(218);
    else if (zone == 137 && gpJoueur->nbCristaux()>=3 && gpJoueur->hasObjet(O_TROC4)>=6 
    && !gpJoueur->hasCristal(3)) gpAudio->playMusic(218);
    else if (zone == 4 && gpJoueur->getCoffre(15,2)) gpAudio->playMusic(219);
    else if (/*isDehors() && */gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_UTILISE
    && gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_FERME
    && getEpoque()==T_PRESENT) gpAudio->playMusic(199);
    else if (zone==10 && gpJoueur->nbCristaux()>=3 && gpJoueur->hasObjet(O_TROC4)>=6
        && !gpJoueur->hasCristal(3)) gpAudio->playMusic(218);
    else if ((zone == 111 || zone == 114 || zone == 124) 
        && gpJoueur->nbEnnemis() >= 87) gpAudio->playMusic(218);
    else gpAudio->playMusic(zone);
}

void Jeu::setTextLanguage(int id) {
    gpTexte->setTextLanguage(id);
}

void Jeu::scrolling() {
    phg[0] = gpJoueur->getX() - 320/2 + 8 + vueHorz;
    phg[1] = gpJoueur->getY() - 240/2 + 16 + vueVert;
    if (phg[0] < gpMonde->regionValue(0)) phg[0] = gpMonde->regionValue(0);
    if (phg[1] < gpMonde->regionValue(1)) phg[1] = gpMonde->regionValue(1);
    if (phg[0] > gpMonde->regionValue(2) - 320) phg[0] = gpMonde->regionValue(2) - 320;
    if (phg[1] > gpMonde->regionValue(3) - 240) phg[1] = gpMonde->regionValue(3) - 240;
}

void Jeu::replace() {
    gpEnnemi->revie();
    gpPiege->revie();
    gpPnj->revie();
    gpCaisse->revie();
    gpObjet->revie();
    delete gpSnipe;
    gpSnipe = new Snipe(this, 0, 0, 0, 0, 0);
    delete gpProjectile;
    gpProjectile = new Projectile(this, 0, N, 0, 0, 0);
    gpMonde->replace();
}

int Jeu::nbEnnemis() {
    int t=0;
    Ennemi* gpEnnemi2 = gpEnnemi->getSuivant();
    while (gpEnnemi2 != NULL) {
        if (gpEnnemi2->getVie()>0 
        && gpEnnemi2->getEnnId()!=17
        && (gpEnnemi2->getEnnId()!=89 || !gpEnnemi2->getSpecial(2))
        && gpEnnemi2->getX()+gpEnnemi2->getW()>gpMonde->regionValue(0) 
        && gpEnnemi2->getX()<gpMonde->regionValue(2) 
        && gpEnnemi2->getY()+gpEnnemi2->getH()>gpMonde->regionValue(1) 
        && gpEnnemi2->getY()<gpMonde->regionValue(3)) t++;
        gpEnnemi2 = gpEnnemi2->getSuivant();
    }
    return t;
}

void Jeu::draw(SDL_Surface* screen) {
    
    if (!transition) scrolling();
    
    gpMonde->drawSol(screen, phg);
    
    if (!transition/* || gpMonde->isChangeTemps()*/) {
        gpPiege->drawSpecial(screen);
        gpCaisse->draw(screen);
        gpObjet->draw(screen);
        gpPnj->draw(screen);
        gpEnnemi->draw(screen);
        gpSnipe->draw(screen);
        gpProjectile->draw(screen);
    }
    
    gpJoueur->draw(screen);
    gpMonde->drawAir(screen, phg);
    gpPiege->draw(screen);
    
    /*if (transition)*/ gpMonde->defilTransit(screen);
    
    gpStatut->draw(screen);
    
    if (menu || gpMenu->getVal()) gpMenu->draw(screen);
    if (text && !transition) gpTexte->draw(screen);
}

Joueur* Jeu::getJoueur() {
    return gpJoueur;
}

Monde* Jeu::getMonde() {
    return gpMonde;
}

Audio* Jeu::getAudio() {
    return gpAudio;
}

Texte* Jeu::getTexte() {
    return gpTexte;
}

Statut* Jeu::getStatut() {
    return gpStatut;
}

Generique* Jeu::getGenerique() {
    return gpGenerique;
}

Keyboard* Jeu::getKeyboard() {
    return gpKeyboard;
}

Pnj* Jeu::getPnj() {
    return gpPnj;
}

Ennemi* Jeu::getEnnemi() {
    return gpEnnemi;
}

Projectile* Jeu::getProjectile() {
    return gpProjectile;
}

Caisse* Jeu::getCaisse() {
    return gpCaisse;
}

void Jeu::ajouteProjectile(int type, Direction dir, int a, int b, int v) {
    Projectile* proj = new Projectile(this, type, dir, a, b, v);
    if (gpProjectile == NULL) gpProjectile = proj;
    else gpProjectile->ajout(proj);
}

void Jeu::ajouteObjet(int type, int i, int j, int num, int p) {
    Objet* obj = new Objet(this, i, j, type, num, p);
    if (gpObjet == NULL) gpObjet = obj;
    else gpObjet->ajout(obj);
}

void Jeu::ajouteSnipe(int type, double i, double j, double dirx, double diry) {
    Snipe* snp = new Snipe(this, type, i, j, dirx, diry);
    if (gpSnipe == NULL) gpSnipe = snp;
    else gpSnipe->ajout(snp);
}

void Jeu::ajouteCaisse(int type, int i, int j, int r, int revie) {
    Caisse* css = new Caisse(this, type, i, j, r, revie);
    if (gpCaisse == NULL) gpCaisse = css;
    else gpCaisse->ajout(css);
}

void Jeu::ajouteEnnemi(int type, int i, int j, bool p) {
    Ennemi* enn = new Ennemi(this, type, i, j, p);
    if (gpEnnemi == NULL) gpEnnemi = enn;
    else gpEnnemi->ajout(enn);
}

void Jeu::ajoutePiege(int type, int i, int j, bool p) {
    Ennemi* enn = new Ennemi(this, type, i, j, p);
    if (gpPiege == NULL) gpPiege = enn;
    else gpPiege->ajout(enn);
}

void Jeu::ajoutePnj(int type, int i, int j, int m, Direction dir) {
    Pnj* pnj = new Pnj(this, type, i, j, m);
    if (gpPnj == NULL) gpPnj = pnj;
    else gpPnj->ajout(pnj);
    pnj->setDirection(dir);
}

bool Jeu::isDonjon() {
    if (zone==57 && gpJoueur->getEpee()<5) return false;
    if (zone==58 && !gpJoueur->getEnnemi(50)) return false;
    return (zone >=46 && zone<=60);
}

bool Jeu::isDehors() {
    return (zone < 46);
}

bool Jeu::isGrotte() {
    return (zone > 60 && zone < 79);
}

void Jeu::poule() {
    Ennemi* gpEnnemi2 = gpEnnemi->getSuivant();
    while (gpEnnemi2 != NULL) {
        if (gpEnnemi2->getEnnId()==52 || gpEnnemi2->getEnnId()==78) gpEnnemi2->enerve();
        gpEnnemi2 = gpEnnemi2->getSuivant();
    }
}

void Jeu::lire() {
    int i=0;
    int j=0;
    switch(gpJoueur->getDirection()) {
        case N : i=gpJoueur->getX()+8; j=gpJoueur->getY()+7-2-2; break;
        case S : i=gpJoueur->getX()+8; j=gpJoueur->getY()+24+2; break;
        case O : i=gpJoueur->getX()-1-2; j=gpJoueur->getY()+16; break;
        case E : i=gpJoueur->getX()+16+2; j=gpJoueur->getY()+16; break;
    }
    int id = gpMonde->contenuValue(i, j);
    int val = gpMonde->motifValue(i, j);
    //lit pancarte ou achete
    if (gpMonde->murValue(i, j) && id && gpJoueur->getDirection()==N && 
    (val == 33 || val == 34 || val == 36 || val == 193 || val == 160 || val == 161 
    || val == 560 || val == 561 || val == 1341 || val == 4093 || val == 4095 || val == 4097
    || val == 4402 || val == 1333 || val == 1334 || val == 976 || val == 977 || val == 2528
    || val == 2384 || val == 2634 || val == 2635 || val == 6495 || val == 6496 
    || val == 6665 || val == 6666)) {
        ecrit(id);
        return;
    }
    //demande infos à Zelda
    if (zone == 57 && gpJoueur->getAvancement()>=ZELDA_SOUS_SOL 
    && gpJoueur->getAvancement() <= RIDEAUX_REPERES
    && i > 100*16 && i < 120*16 && j > 165*16 && j < 180*16) {
        if (val==1001) {ecrit(1026); return;}
        if (val==304) {ecrit(1027); return;}
        if (val==6329) {ecrit(1028); return;}
        if (val==6126) {ecrit(1029); return;}
    }
    //parle à un arbre
    if (val==4370 || val==4379) {
        ecrit(4);
        return;
    }
    //ouvre coffre
    if (gpMonde->murValue(i, j) && val==303 && gpJoueur->getDirection()==N) {
        switch (id) {
            case C_RIEN : 
            case C_QUART_COEUR :
            case C_GEMME :
                gpMonde->setValeur(6*16,6*16,304,-1,1,0); 
                gpMonde->setValeur(8*16,6*16,304,-1,1,0); 
                gpMonde->setValeur(10*16,6*16,304,-1,1,0);
                gpMonde->setValeur(6*16,8*16,304,-1,1,0); 
                gpMonde->setValeur(8*16,8*16,304,-1,1,0); 
                gpMonde->setValeur(10*16,8*16,304,-1,1,0);
                gpMonde->setValeur(6*16,10*16,304,-1,1,0); 
                gpMonde->setValeur(8*16,10*16,304,-1,1,0); 
                gpMonde->setValeur(10*16,10*16,304,-1,1,0);
                if (id == C_RIEN) ecrit(437);
                if (id == C_QUART_COEUR) {
                    gpJoueur->setCoeur(28); trouve(C_QUART_COEUR);
                }
                if (id == C_GEMME) {
                    if (!gpJoueur->getGemme(160)) gpJoueur->trouveGemme(160);
                    else if (!gpJoueur->getGemme(161)) gpJoueur->trouveGemme(161);
                    else if (!gpJoueur->getGemme(162)) gpJoueur->trouveGemme(162);
                    trouve(C_GEMME);
                }
                gpPnj->getSuivant()->setMessage(433);
                break;
            case C_PAIE : ecrit(id); break;
            default : gpMonde->setValeur(i, j, 304, -1, PLEIN, C_RIEN); trouve(id);
        }
        return;
    }
    //parle pnj
    Pnj* gpPnj2 = gpPnj->getSuivant();
    while (gpPnj2 != NULL) {
        int x1 = gpPnj2->getX();
        int y1 = gpPnj2->getY();
        int w1 = x1+gpPnj2->getZoneBase()->getZone()->x+gpPnj2->getZoneBase()->getZone()->w;
        int h1 = y1+gpPnj2->getZoneBase()->getZone()->y+gpPnj2->getZoneBase()->getZone()->h;
        if (i>=x1 && i<w1 && j>=y1 && j<h1 && gpPnj2->getVie()) {
            ecrit(gpPnj2->getMessage());
            return;
        }
        gpPnj2 = gpPnj2->getSuivant();
    }
}

void Jeu::trouve(int id) {
    ecrit(id);
    gpJoueur->setTrouve(id);
    gpAudio->playSound(19,2);
}

int Jeu::getNbGemmes() {
    Objet* obj = gpObjet->getSuivant();
    int total=0;
    while (obj != NULL) {
        if (obj->getType() == I_GEMME) total++;
        obj = obj->getSuivant();
    }
    return total;
}

bool Jeu::finTexte(int id) {
    Pnj* pnj;
    Ennemi* enn;
    Objet* obj;
    int ok[] = {0, 0, 0};
    int ind = 0;
    if (gpJoueur) gpJoueur->setTrouve(0);
    switch (id) {
        
        //textes 3t
        case 9 : case 10 : case 11 : case 12 : case 13 : case 14 : case 15 : case 16 :
        case 17 : case 18 : case 19 : case 20 : case 21 : case 22 : 
            gpJoueur->setPoisson(id-9);
            gpJoueur->setBoostVie(4);
            break;
        case 23 : gpJoueur->setPoisson(id-9); break;
        case 24 : case 25 : case 26 : case 27 : case 28 : case 29 : case 30 : case 31 : 
        case 32 : case 33 : 
            gpJoueur->setPoisson(id-9);
            gpJoueur->setBoostVie(8);
            break;
        case 34 : case 35 : case 36 : case 37 : case 38 :
            gpJoueur->setPoisson(id-9);
            gpJoueur->setBoostVie(16);
            break;
        case 44 : if (gpJoueur->getAvancement()<PARLE_GARDE_DEVANT_CHEZ_LINK) 
            gpJoueur->setAvancement(PARLE_GARDE_DEVANT_CHEZ_LINK); break;
        case 47 : case 49 : case 52 : case 56 : case 58 : case 60 : case 63 : case 66 :
            gpJoueur->setTypeAnim(AUCUNE); break;
        case 48 : case 50 : case 53 : case 61 : 
            gpJoueur->setMelodie(0,2); 
            return true;
        case 51 : case 54 : case 57 : case 64 :
            gpJoueur->setMelodie(1,2); return true;
        case 55 : case 59 : case 62 : case 65 :
            gpJoueur->setMelodie(2,2); return true;
        case 77 :
            if (gpJoueur->getTroc(M_ROUAGE)==-1) gpJoueur->setTroc(M_ROUAGE,0);
            gpJoueur->setTroc(M_ROUAGE,gpJoueur->getTroc(M_ROUAGE)+1);
            gpJoueur->setTroc(M_POULET,gpJoueur->getTroc(M_POULET)-1);
            gpJoueur->setBoostRubis(-100);
            trouve(C_ROUAGE); return true; break;
        case 80 :
            gpJoueur->setTroc(M_ROC_MAGMA,gpJoueur->getTroc(M_ROC_MAGMA)-1);
            gpJoueur->setTroc(M_ROC_GIVRE,gpJoueur->getTroc(M_ROC_GIVRE)-1);
            if (zone==18) gpJoueur->setCoeur(14); 
            if (zone==3) gpJoueur->setCoeur(15); 
            trouve(C_QUART_COEUR); return true; break;
        case 83 :
            gpJoueur->setRubisMax(200);
            gpJoueur->setTroc(M_PLUME,gpJoueur->getTroc(M_PLUME)-1);
            gpJoueur->setBoostRubis(-10);
            trouve(C_BOURSE_2); return true; break;
        case 86 :
            gpJoueur->setRubisMax(500);
            gpJoueur->setTroc(M_TAPISSERIE,gpJoueur->getTroc(M_TAPISSERIE)-1);
            gpJoueur->setBoostRubis(-100);
            trouve(C_BOURSE_3); return true; break;
        case 89 :
            gpJoueur->setRubisMax(999);
            gpJoueur->setTroc(M_AMULETTE,gpJoueur->getTroc(M_AMULETTE)-1);
            gpJoueur->setTroc(M_ROC_MAGMA,gpJoueur->getTroc(M_ROC_MAGMA)-1);
            gpJoueur->setBoostRubis(-250);
            trouve(C_BOURSE_4); return true; break;
        case 92 :
            if (gpJoueur->getTroc(M_POULET)==-1) gpJoueur->setTroc(M_POULET,0);
            gpJoueur->setTroc(M_POULET,gpJoueur->getTroc(M_POULET)+1);
            gpJoueur->setTroc(M_RIZ,gpJoueur->getTroc(M_RIZ)-2);
            gpJoueur->setTroc(M_OLIVES,gpJoueur->getTroc(M_OLIVES)-3);
            trouve(C_POULET); return true; break;
        case 96 :
            if (gpJoueur->getTroc(M_PLUME)==-1) gpJoueur->setTroc(M_PLUME,0);
            gpJoueur->setTroc(M_PLUME,gpJoueur->getTroc(M_PLUME)+1);
            gpJoueur->setTroc(M_EPICES,gpJoueur->getTroc(M_EPICES)-2);
            gpJoueur->setTroc(M_OLIVES,gpJoueur->getTroc(M_OLIVES)-2);
            trouve(C_PLUME); return true; break;
        case 99 :
            if (gpJoueur->getTroc(M_RIZ)==-1) gpJoueur->setTroc(M_RIZ,0);
            gpJoueur->setTroc(M_RIZ,gpJoueur->getTroc(M_RIZ)+1);
            gpJoueur->setBoostRubis(-15);
            trouve(C_RIZ); return true; break;
        case 101 :
            if (zone==90) {trouve(C_OLIVES); return true;}
            if (zone!=57 && zone!=87 && zone!=96 && zone!=140) break;
            if (gpJoueur->getTroc(M_RIZ)==-1) gpJoueur->setTroc(M_RIZ,0);
            gpJoueur->setTroc(M_RIZ,gpJoueur->getTroc(M_RIZ)+1);
            if (gpJoueur->getTroc(M_RIZ)>99) gpJoueur->setTroc(M_RIZ,99); 
            if (zone==57) gpJoueur->setCoffre(15,29);
            if (zone==87) gpJoueur->setCoffre(15,15);
            if (zone==96) gpJoueur->setCoffre(15,18);
            if (zone==140) gpJoueur->setCoffre(15,25);
            break;
        case 102 :
            if (gpJoueur->getTroc(M_OLIVES)==-1) gpJoueur->setTroc(M_OLIVES,0);
            gpJoueur->setTroc(M_OLIVES,gpJoueur->getTroc(M_OLIVES)+1);
            gpJoueur->setBoostRubis(-10);
            trouve(C_OLIVES); return true; break;
        case 104 :
            if (zone!=57 && zone!=87 && zone!=96) break;
            if (gpJoueur->getTroc(M_OLIVES)==-1) gpJoueur->setTroc(M_OLIVES,0);
            gpJoueur->setTroc(M_OLIVES,gpJoueur->getTroc(M_OLIVES)+1);
            if (gpJoueur->getTroc(M_OLIVES)>99) gpJoueur->setTroc(M_OLIVES,99); 
            if (zone==57) gpJoueur->setCoffre(15,30);
            if (zone==87) gpJoueur->setCoffre(15,16);
            if (zone==96) gpJoueur->setCoffre(15,19);
            break;
        case 109 :
            pnj = gpPnj->getSuivant();
            while (pnj != NULL) {
                if (pnj->getId() == 9) {pnj->setDirection(N); break;}
                pnj = pnj->getSuivant();
            }
            gpJoueur->trouveObjet(O_TROC4,3);
            trouve(C_BALAIS); return true; 
            break;
        case 126 :
            pnj = gpPnj->getSuivant();
            while (pnj != NULL) {
                if (pnj->getId() == 7) {
                    delete (Pnj*)gpPnj->enleve(pnj); ajoutePnj(53,32*16+8,30*16+5,126); break;}
                pnj = pnj->getSuivant();
            }
            gpJoueur->setTroc(M_ROUE,gpJoueur->getTroc(M_ROUE)-1);
            gpJoueur->setTroc(M_JAUGE,gpJoueur->getTroc(M_JAUGE)-1);
            gpJoueur->setTroc(M_SOURCE_ENERGIE,gpJoueur->getTroc(M_SOURCE_ENERGIE)-1);
            gpJoueur->setBoostGanon(-100);
            gpJoueur->setLapin(false);
            gpJoueur->trouveObjet(O_PERLE);
            trouve(C_PERLE_LUNE); return true; break;
        case 129 :
            gpJoueur->setGanonMax(200);
            gpJoueur->setTroc(M_PERLES,gpJoueur->getTroc(M_PERLES)-1);
            gpJoueur->setBoostGanon(-10);
            trouve(C_BOURSE_12); return true; break;
        case 132 :
            gpJoueur->setGanonMax(500);
            gpJoueur->setTroc(M_AMULETTE,gpJoueur->getTroc(M_AMULETTE)-1);
            gpJoueur->setBoostGanon(-100);
            trouve(C_BOURSE_13); return true; break;
        case 135 :
            gpJoueur->setGanonMax(999);
            gpJoueur->setTroc(M_PARFUM,gpJoueur->getTroc(M_PARFUM)-1);
            gpJoueur->setTroc(M_ROC_GIVRE,gpJoueur->getTroc(M_ROC_GIVRE)-1);
            gpJoueur->setBoostGanon(-250);
            trouve(C_BOURSE_14); return true; break;
        case 138 :
            if (gpJoueur->getTroc(M_ROUE)==-1) gpJoueur->setTroc(M_ROUE,0);
            gpJoueur->setTroc(M_ROUE,gpJoueur->getTroc(M_ROUE)+1);
            gpJoueur->setTroc(M_EPICES,gpJoueur->getTroc(M_EPICES)-3);
            trouve(C_ROUE); return true; break;
        case 141 :
            gpJoueur->trouveObjet(O_SAC_BOMBES);
            gpJoueur->setTroc(M_POIVRON,gpJoueur->getTroc(M_POIVRON)-1);
            gpJoueur->setTroc(M_EPICES,gpJoueur->getTroc(M_EPICES)-3);
            gpJoueur->setBombe(gpJoueur->getBombeMax());
            trouve(C_SAC_BOMBES); return true; break;
        case 144 :
            if (gpJoueur->getTroc(M_ROC_MAGMA)==-1) gpJoueur->setTroc(M_ROC_MAGMA,0);
            gpJoueur->setTroc(M_ROC_MAGMA,gpJoueur->getTroc(M_ROC_MAGMA)+1);
            gpJoueur->setTroc(M_TAPISSERIE,gpJoueur->getTroc(M_TAPISSERIE)-1);
            gpJoueur->setTroc(M_AMULETTE,gpJoueur->getTroc(M_AMULETTE)-1);
            gpJoueur->setTroc(M_PARFUM,gpJoueur->getTroc(M_PARFUM)-1);
            trouve(C_ROC_MAGMA); return true; break;
        case 147 :
            if (gpJoueur->getTroc(M_PERLES)==-1) gpJoueur->setTroc(M_PERLES,0);
            gpJoueur->setTroc(M_PERLES,gpJoueur->getTroc(M_PERLES)+1);
            gpJoueur->setTroc(M_EPICES,gpJoueur->getTroc(M_EPICES)-5);
            gpJoueur->setBoostGanon(-5);
            trouve(C_PERLES); return true; break;
        case 150 :
            if (gpJoueur->getTroc(M_EPICES)==-1) gpJoueur->setTroc(M_EPICES,0);
            gpJoueur->setTroc(M_EPICES,gpJoueur->getTroc(M_EPICES)+1);
            gpJoueur->setBoostGanon(-10);
            trouve(C_EPICES); return true; break;
        case 152 :
            if (zone!=83 && zone!=88 && zone!=96 && zone!=104 && zone!=140) break;
            if (gpJoueur->getTroc(M_EPICES)==-1) gpJoueur->setTroc(M_EPICES,0);
            gpJoueur->setTroc(M_EPICES,gpJoueur->getTroc(M_EPICES)+1);
            if (gpJoueur->getTroc(M_EPICES)>99) gpJoueur->setTroc(M_EPICES,99); 
            if (zone==83) gpJoueur->setCoffre(15,13);
            if (zone==88) gpJoueur->setCoffre(15,17);
            if (zone==96) gpJoueur->setCoffre(15,20);
            if (zone==104) gpJoueur->setCoffre(15,21);
            if (zone==140) gpJoueur->setCoffre(15,24);
            break;
        case 153 : gpJoueur->setBoostGanon(-5); break;
        case 159 :
            gpJoueur->setPieceMax(200);
            gpJoueur->setTroc(M_POULET,gpJoueur->getTroc(M_POULET)-1);
            gpJoueur->setBoostPiece(-10);
            trouve(C_BOURSE_22); return true; break;
        case 162 :
            gpJoueur->setPieceMax(500);
            gpJoueur->setTroc(M_PARFUM,gpJoueur->getTroc(M_PARFUM)-1);
            gpJoueur->setBoostPiece(-100);
            trouve(C_BOURSE_23); return true; break;
        case 165 :
            gpJoueur->setPieceMax(999);
            gpJoueur->setTroc(M_TAPISSERIE,gpJoueur->getTroc(M_TAPISSERIE)-1);
            gpJoueur->setTroc(M_ROC_MAGMA,gpJoueur->getTroc(M_ROC_MAGMA)-1);
            gpJoueur->setBoostPiece(-250);
            trouve(C_BOURSE_24); return true; break;
        case 168 :
            if (gpJoueur->getTroc(M_AMULETTE)==-1) gpJoueur->setTroc(M_AMULETTE,0);
            gpJoueur->setTroc(M_AMULETTE,gpJoueur->getTroc(M_AMULETTE)+1);
            gpJoueur->setTroc(M_POULET,gpJoueur->getTroc(M_POULET)-1);
            gpJoueur->setTroc(M_OLIVES,gpJoueur->getTroc(M_OLIVES)-2);
            trouve(C_AMULETTE); return true; break;
        case 171 :
            if (gpJoueur->getTroc(M_PLUME)==-1) gpJoueur->setTroc(M_PLUME,0);
            gpJoueur->setTroc(M_PLUME,gpJoueur->getTroc(M_PLUME)+1);
            gpJoueur->setTroc(M_EPICES,gpJoueur->getTroc(M_EPICES)-1);
            gpJoueur->setTroc(M_OLIVES,gpJoueur->getTroc(M_OLIVES)-1);
            trouve(C_PLUME); return true; break;
        case 182 :
            pnj = gpPnj->getSuivant();
            while (pnj != NULL) {
                if (pnj->getId() == 9) {pnj->setDirection(S); break;}
                pnj = pnj->getSuivant();
            }
            gpJoueur->trouveObjet(O_TROC4,4);
            trouve(C_CONFITURE); return true; 
            break;
        case 191 :
            pnj = gpPnj->getSuivant();
            pnj->setMessage(193);
            pnj = pnj->getSuivant();
            pnj->setMessage(193);
            gpJoueur->setBoostGanon(-5);
            gpJoueur->setCoffre(15,1);
            break;
        case 194 : 
            gpJoueur->setCoffre(15,2); zone=3;
            gpMonde->transitTemps(4,gpJoueur->getX(),gpJoueur->getY());
            break;
        case 198 :
            switch (zone) {
                case 6 : gpJoueur->setCristal(4); break;
                case 8 : gpJoueur->setCristal(0); break;
                case 9 : gpJoueur->setCristal(6); break;
                case 12 : gpJoueur->setCristal(1); break;
                case 15 : gpJoueur->setCristal(5); break;
                case 75 : gpJoueur->setCristal(2); break;
                case 137 : gpJoueur->setCristal(3); 
                    gpAudio->stopSpecial(); gpAudio->stopMusic();
                    zone=136; gpMonde->transitFull(137, 152, 200+240*4, N);
                    return true;
                    break;
            }
            break;
        case 199 : gpJoueur->save(); ecrit(201); return true; break;
        case 206 : gpJoueur->trouveObjet(O_TROC3,7); trouve(C_DETTE); return true; break;
        case 215 :
            if (gpJoueur->getTroc(M_TAPISSERIE)==-1) gpJoueur->setTroc(M_TAPISSERIE,0);
            gpJoueur->setTroc(M_TAPISSERIE,gpJoueur->getTroc(M_TAPISSERIE)+1);
            gpJoueur->setTroc(M_PERLES,gpJoueur->getTroc(M_PERLES)-2);
            gpJoueur->setTroc(M_EPICES,gpJoueur->getTroc(M_EPICES)-5);
            trouve(C_TAPISSERIE); return true; break;
        case 218 :
            if (gpJoueur->getTroc(M_AMULETTE)==-1) gpJoueur->setTroc(M_AMULETTE,0);
            gpJoueur->setTroc(M_AMULETTE,gpJoueur->getTroc(M_AMULETTE)+1);
            gpJoueur->setTroc(M_POULET,gpJoueur->getTroc(M_POULET)-5);
            gpJoueur->setTroc(M_OLIVES,gpJoueur->getTroc(M_OLIVES)-5);
            trouve(C_AMULETTE); return true; break;
        case 220 :
            if (gpJoueur->getTroc(M_PERLES)==-1) gpJoueur->setTroc(M_PERLES,0);
            gpJoueur->setTroc(M_PERLES,gpJoueur->getTroc(M_PERLES)+1);
            gpJoueur->setTroc(M_EPICES,gpJoueur->getTroc(M_EPICES)-2);
            gpJoueur->setTroc(M_RIZ,gpJoueur->getTroc(M_RIZ)-2);
            trouve(C_PERLES); return true; break;
        case 222 :
            if (gpJoueur->getTroc(M_RIZ)==-1) gpJoueur->setTroc(M_RIZ,0);
            gpJoueur->setTroc(M_RIZ,gpJoueur->getTroc(M_RIZ)+1);
            gpJoueur->setTroc(M_OLIVES,gpJoueur->getTroc(M_OLIVES)-1);
            gpJoueur->setBoostRubis(-2);
            trouve(C_RIZ); return true; break;
        case 228 :
            gpJoueur->trouveGemme(91);
            gpJoueur->setTroc(M_PERLES,gpJoueur->getTroc(M_PERLES)-2);
            trouve(C_GEMME); return true; break;
        case 230 :
            gpJoueur->trouveGemme(92);
            gpJoueur->setTroc(M_PLUME,gpJoueur->getTroc(M_PLUME)-2);
            trouve(C_GEMME); return true; break;
        case 232 :
            gpJoueur->trouveGemme(93);
            gpJoueur->setTroc(M_POULET,gpJoueur->getTroc(M_POULET)-2);
            trouve(C_GEMME); return true; break;
        case 234 :
            if (gpJoueur->getTroc(M_POULET)==-1) gpJoueur->setTroc(M_POULET,0);
            gpJoueur->setTroc(M_POULET,gpJoueur->getTroc(M_POULET)+1);
            gpJoueur->setTroc(M_OLIVES,gpJoueur->getTroc(M_OLIVES)-2);
            gpJoueur->setTroc(M_RIZ,gpJoueur->getTroc(M_RIZ)-1);
            trouve(C_POULET); return true; break;
        case 242 : 
            enn = gpEnnemi->getSuivant();
            for (int i = 0; i < 4; i++) {
                if (enn->getVie()) ajouteProjectile(8, N, enn->getX(), enn->getY(), 0);
                enn->setVie(0);
                enn=enn->getSuivant();
            }
            gpJoueur->trouveObjet(O_TROC2,3); trouve(C_MARTEAU2); return true; break;
        case 243 : 
            enn = gpEnnemi->getSuivant();
            for (int i = 0; i < 4; i++) {
                if (!enn->getVie()) ajouteProjectile(8, N, enn->getX(), enn->getY(), 0);
                enn->setVie(1);
                enn=enn->getSuivant();
            }
            break;
        case 247 : 
            enn = gpEnnemi->getSuivant();
            for (int i = 0; i < 4; i++) {
                if (enn->getVie()) ajouteProjectile(8, N, enn->getX(), enn->getY(), 0);
                enn->setVie(0);
                enn=enn->getSuivant();
            }
            break;
        case 253 :
            if (!gpJoueur->hasObjet(O_BARQUE)) {gpJoueur->setBoostRubis(-15); gpJoueur->trouveObjet(O_BARQUE);}
            break;
        case 265 :
            gpJoueur->trouveObjet(O_BOTTES);
            gpJoueur->setTroc(M_TAPISSERIE,gpJoueur->getTroc(M_TAPISSERIE)-1);
            gpJoueur->setTroc(M_PARFUM,gpJoueur->getTroc(M_PARFUM)-1);
            trouve(C_BOTTES); return true; break;
        case 268 :
            if (gpJoueur->getTroc(M_PARFUM)==-1) gpJoueur->setTroc(M_PARFUM,0);
            gpJoueur->setTroc(M_PARFUM,gpJoueur->getTroc(M_PARFUM)+1);
            gpJoueur->setTroc(M_PLUME,gpJoueur->getTroc(M_PLUME)-3);
            gpJoueur->setTroc(M_RIZ,gpJoueur->getTroc(M_RIZ)-4);
            trouve(C_PARFUM); return true; break;
        case 271 :
            if (gpJoueur->getTroc(M_OLIVES)==-1) gpJoueur->setTroc(M_OLIVES,0);
            gpJoueur->setTroc(M_OLIVES,gpJoueur->getTroc(M_OLIVES)+1);
            gpJoueur->setBoostRubis(-15);
            trouve(C_OLIVES); return true; break;
        case 273 :
            if (gpJoueur->getTroc(M_EPICES)==-1) gpJoueur->setTroc(M_EPICES,0);
            gpJoueur->setTroc(M_EPICES,gpJoueur->getTroc(M_EPICES)+1);
            gpJoueur->setBoostRubis(-20);
            trouve(C_EPICES); return true; break;
        case 278 :
            if (gpJoueur->getTroc(M_ROC_GIVRE)==-1) gpJoueur->setTroc(M_ROC_GIVRE,0);
            gpJoueur->setTroc(M_ROC_GIVRE,gpJoueur->getTroc(M_ROC_GIVRE)+1);
            gpJoueur->setTroc(M_TAPISSERIE,gpJoueur->getTroc(M_TAPISSERIE)-1);
            gpJoueur->setTroc(M_AMULETTE,gpJoueur->getTroc(M_AMULETTE)-1);
            gpJoueur->setTroc(M_PARFUM,gpJoueur->getTroc(M_PARFUM)-1);
            trouve(C_ROC_GIVRE); return true; break;
        case 280 : if (zone == 84) {ecrit(382); return true;} break;
        case 281 :
            if (gpJoueur->getTroc(M_PERLES)==-1) gpJoueur->setTroc(M_PERLES,0);
            gpJoueur->setTroc(M_PERLES,gpJoueur->getTroc(M_PERLES)+1);
            gpJoueur->setTroc(M_RIZ,gpJoueur->getTroc(M_RIZ)-1);
            gpJoueur->setTroc(M_EPICES,gpJoueur->getTroc(M_EPICES)-1);
            trouve(C_PERLES); return true; break;
        case 292 : gpJoueur->trouveObjet(O_TROC3,3); trouve(C_POUDRE_OR); return true; break;
        case 301 :
            gpPnj->getSuivant()->setAnimmax(1);
            gpJoueur->trouveObjet(O_TROC1,2); trouve(C_ENCLUME); return true; break;
        case 311 :
            gpPnj->getSuivant()->setAnimmax(1);
            gpJoueur->trouveObjet(O_TROC2,5); trouve(C_HACHE); return true; break;
        case 316 : gpJoueur->setEpee(1); break;
        case 319 : 
            if (gpJoueur->getAvancement()<STELE_LUE) gpJoueur->setAvancement(STELE_LUE); 
            if (gpJoueur->getEpee() == 2 && getEpoque()==T_PRESENT 
            && gpJoueur->getAvancement()<PORTAIL_F_OUVERT) {
                gpAudio->playSound(9);
                gpMonde->passage(9,6,0);
                gpMonde->passage(9,3,1);
                gpPnj->getSuivant()->setDirection(N);
                gpJoueur->setAvancement(PORTAIL_F_OUVERT); 
                ajouteProjectile(26, N, 9*16+8, 6*16+8, 0);
            }
            break;
        case 320 : if (gpJoueur->getAvancement()<PARLE_ZELDA_GROTTE) 
            gpJoueur->setAvancement(PARLE_ZELDA_GROTTE); break;
        case 322 : gpPnj->getSuivant()->setDirection(S); ecrit(323); return true; break;
        case 324 : gpJoueur->trouveObjet(O_CARTE); trouve(C_CARTE); return true; break;
        case 325 : ecrit(330); return true; break;
        case 327 : gpJoueur->setEpee(2); trouve(C_EXCALIBUR); return true; break;
        case 328 : ecrit(329); gpJoueur->setImmo(true); return true; break;
        case 331 : gpJoueur->setBouclier(2); trouve(C_BOUCLIER_R); return true; break;
        case 333 : gpJoueur->setBoostVie(gpJoueur->getVieMax()-gpJoueur->getVie()); break;
        case 334 :
            gpJoueur->setTroc(M_RIZ,gpJoueur->getTroc(M_RIZ)+10);
            if (gpJoueur->getTroc(M_RIZ)>99) gpJoueur->setTroc(M_RIZ,99); 
            if (zone==66) gpJoueur->setCoffre(15,7);
            break;
        case 335 :
            gpJoueur->setTroc(M_EPICES,gpJoueur->getTroc(M_EPICES)+10);
            if (gpJoueur->getTroc(M_EPICES)>99) gpJoueur->setTroc(M_EPICES,99);
            if (zone==66) gpJoueur->setCoffre(15,8);
            break;
        case 336 :
            gpJoueur->setTroc(M_OLIVES,gpJoueur->getTroc(M_OLIVES)+10);
            if (gpJoueur->getTroc(M_OLIVES)>99) gpJoueur->setTroc(M_OLIVES,99);
            if (zone==66) gpJoueur->setCoffre(15,9);
            break;
        case 338 : if (gpJoueur->getAvancement()<PANCARTE_MINE_LUE) 
            gpJoueur->setAvancement(PANCARTE_MINE_LUE); break;
        case 339 : if (gpJoueur->getAvancement()<PARLE_GARS_MINE_MINE) 
            gpJoueur->setAvancement(PARLE_GARS_MINE_MINE); break;
        case 340 : if (gpJoueur->getAvancement()<PLANCHES_TROUVEES) 
            gpJoueur->setAvancement(PLANCHES_TROUVEES); break;
        case 341 :
            if (gpJoueur->getAvancement()<PONT_CONSTRUIT) 
                gpJoueur->setAvancement(PONT_CONSTRUIT);
            zone=17;
            gpMonde->transitFull(18, gpJoueur->getX(), gpJoueur->getY(), N);
            break;
        case 343 : 
            if (gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_OUVERT) {
                gpJoueur->setAvancement(PORTAIL_PRE_PRESENT_OUVERT); 
                gpAudio->playSound(9);
                gpMonde->passage(9,3,1);
            }
            break;
        case 348 : if (gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_FERME) 
            gpJoueur->setAvancement(PORTAIL_PRE_PRESENT_FERME); 
            gpMonde->passage(9,3,10);
            break;
        case 349 :
            if (gpJoueur->getTroc(M_JAUGE)==-1) gpJoueur->setTroc(M_JAUGE,0);
            gpJoueur->setTroc(M_JAUGE,gpJoueur->getTroc(M_JAUGE)+1); break;
        case 351 :
            gpJoueur->setBoostGanon(-100);
            if (gpJoueur->getBombeMax()==30 || !gpJoueur->hasObjet(O_SAC_BOMBES)) ecrit(354);
            else if (gpJoueur->getFlecheMax()==70) ecrit(355);
            else ecrit(354+(rand()%2));
            return true; break;
        case 354 : 
            gpJoueur->setFlecheMax(gpJoueur->getFlecheMax()+5); 
            gpJoueur->setFleche(gpJoueur->getFlecheMax());
            break;
        case 355 : 
            gpJoueur->setBombeMax(gpJoueur->getBombeMax()+2); 
            gpJoueur->setBombe(gpJoueur->getBombeMax());
            break;
        case 356 :
            gpJoueur->setBoostGanon(-999);
            if (gpJoueur->hasObjet(O_RECUP_BOMBE)) ecrit(358);
            else if (gpJoueur->hasObjet(O_RECUP_FLECHE)) ecrit(359);
            else ecrit(358+(rand()%2));
            return true; break;
        case 358 : 
            gpJoueur->trouveObjet(O_RECUP_FLECHE); 
            gpJoueur->setFleche(gpJoueur->getFlecheMax());
            break;
        case 359 : 
            gpJoueur->trouveObjet(O_RECUP_BOMBE); 
            gpJoueur->setBombe(gpJoueur->getBombeMax());
            break;
        case 360 : gpJoueur->setMagieMax(64); trouve(C_MIMAGIE); return true; break;
        case 368 : 
            gpJoueur->setBoostRubis(-20);
            gpJoueur->setFleche(gpJoueur->getFleche()+10); 
            gpAudio->playSound(13);
            ecrit(375); return true; break;
        case 370 : 
            gpJoueur->setBoostRubis(-30);
            gpJoueur->setBombe(gpJoueur->getBombe()+5); 
            gpAudio->playSound(13);
            ecrit(375); return true; break;
        case 376 :
            gpJoueur->setBoostRubis(-5);
            gpJoueur->setBoostVie(gpJoueur->getBoostVie()+2);
            if (gpJoueur->getVie()==gpJoueur->getVieMax()) gpAudio->playSound(15);
            ecrit(375); return true; break;
        case 378 : 
            gpJoueur->setBoostRubis(-15);
            gpJoueur->setBoostMagie(gpJoueur->getBoostMagie()+gpJoueur->getMagieMax()/8);
            gpAudio->playSound(13);
            ecrit(375); return true; break;
        case 380 : 
            gpJoueur->setBoostRubis(-25);
            gpJoueur->setBoostMagie(gpJoueur->getBoostMagie()+gpJoueur->getMagieMax()/4);
            if (gpJoueur->getMagie()<gpJoueur->getMagieMax())
                gpAudio->playSound(37);
            else gpAudio->playSound(13);
            ecrit(375); return true; break;
        case 383 :
            if (gpJoueur->getTroc(M_ROC_GIVRE)==-1) gpJoueur->setTroc(M_ROC_GIVRE,0);
            gpJoueur->setTroc(M_ROC_GIVRE,gpJoueur->getTroc(M_ROC_GIVRE)+1);
            gpJoueur->setGemme(gpJoueur->getGemme()-30);
            trouve(C_ROC_GIVRE); return true; break;
        case 387 :
            obj = gpObjet->getSuivant();
            while (obj!=NULL) {
                if (obj->getType()==I_DETECTEUR) obj->setVie(0);
                obj=obj->getSuivant();
            }
            gpMonde->setContenu(14,6,0);
            gpJoueur->trouveObjet(O_DETECTEUR);
            gpJoueur->setGemme(gpJoueur->getGemme()-20);
            trouve(C_DETECTEUR); return true; break;
        case 390 :
        case 393 :
            if (!gpJoueur->hasBouteille(0)) {
                gpJoueur->setBouteille(0, 1);
                gpJoueur->setGemme(gpJoueur->getGemme()-10);
            } else {
                gpJoueur->setBouteille(1, 1);
                gpJoueur->setGemme(gpJoueur->getGemme()-20);
                obj = gpObjet->getSuivant();
                while (obj!=NULL) {
                    if (obj->getType()==I_BOUTEILLE) obj->setVie(0);
                    obj=obj->getSuivant();
                }
                gpMonde->setContenu(5,6,0);
            }
            trouve(C_BOUTEILLE); return true; break;
        case 395 :
        case 398 :
            gpJoueur->trouveObjet(O_BONUS_FORCE, gpJoueur->hasObjet(O_BONUS_FORCE)+1);
            gpJoueur->setGemme(gpJoueur->getGemme()-20*gpJoueur->hasObjet(O_BONUS_FORCE));
            if (gpJoueur->hasObjet(O_BONUS_FORCE)==2) {
                obj = gpObjet->getSuivant();
                while (obj!=NULL) {
                    if (obj->getType()==I_BONUS_FORCE) obj->setVie(0);
                    obj=obj->getSuivant();
                }
                gpMonde->setContenu(8,6,0);
            }    
            trouve(C_BONUS_FORCE); return true; break;
        case 400 :
        case 403 :
            gpJoueur->trouveObjet(O_BONUS_DEFENSE, gpJoueur->hasObjet(O_BONUS_DEFENSE)+1);
            gpJoueur->setGemme(gpJoueur->getGemme()-20*gpJoueur->hasObjet(O_BONUS_DEFENSE));
            if (gpJoueur->hasObjet(O_BONUS_DEFENSE)==2) {
                obj = gpObjet->getSuivant();
                while (obj!=NULL) {
                    if (obj->getType()==I_BONUS_DEFENSE) obj->setVie(0);
                    obj=obj->getSuivant();
                }
                gpMonde->setContenu(11,6,0);
            }
            gpJoueur->calculDef();
            trouve(C_BONUS_DEFENSE); return true; break;
        case 413 :
            int i; i=0; while(gpJoueur->hasBouteille(i)!=1) i++;
            gpJoueur->setBouteille(i,2);
            gpJoueur->setBoostRubis(-60);
            trouve(C_POTION_ROUGE);
            return true;
        case 415 :
            i=0; while(gpJoueur->hasBouteille(i)!=1) i++;
            gpJoueur->setBouteille(i,3);
            gpJoueur->setBoostRubis(-40);
            trouve(C_POTION_VERTE);
            return true;
        case 422 : gpJoueur->save();
        case 423 : 
            gpAudio->stopSpecial(); gpAudio->stopMusic(); videListes(); 
            gpKeyboard->setMode(2); gpGenerique->initLogo(); return false; break;
        case 428 : 
            gpJoueur->setCoffre(15,14);
            /*gpJoueur->trouveObjet(O_TROC1,3);*/ trouve(C_FAC_RIEN); return true; break;
        case 433 :
            int hasard;
            int nbprix;
            hasard=0;
            nbprix = 4-(gpJoueur->getCoeur(28) + gpJoueur->getGemme(160) 
            + gpJoueur->getGemme(161) + gpJoueur->getGemme(162));
            gpMonde->setValeur(6*16,6*16,303,-1,1,0); 
            gpMonde->setValeur(8*16,6*16,303,-1,1,0); 
            gpMonde->setValeur(10*16,6*16,303,-1,1,0);
            gpMonde->setValeur(6*16,8*16,303,-1,1,0); 
            gpMonde->setValeur(8*16,8*16,303,-1,1,0); 
            gpMonde->setValeur(10*16,8*16,303,-1,1,0);
            gpMonde->setValeur(6*16,10*16,303,-1,1,0); 
            gpMonde->setValeur(8*16,10*16,303,-1,1,0); 
            gpMonde->setValeur(10*16,10*16,303,-1,1,0);
            for (int i = 0; i < nbprix; i++) {
                hasard = rand()%(9-i);
                for (int j = 0; j <= hasard; j++) 
                    if (gpMonde->contenuValue((6+(j%3)*2)*16,(6+(j/3)*2)*16)!=0) hasard++;
                if (i==0 && !gpJoueur->getCoeur(28))
                    gpMonde->setContenu(6+(hasard%3)*2,6+(hasard/3)*2,C_QUART_COEUR);
                else
                    gpMonde->setContenu(6+(hasard%3)*2,6+(hasard/3)*2,C_GEMME);
            }
            gpJoueur->setBoostRubis(-(4-nbprix+1)*5); gpPnj->getSuivant()->setMessage(436);
            ecrit(375); return true; break;
        case 443 :
            gpJoueur->trouveObjet(O_SAC_TROC);
            gpJoueur->setTroc(M_RIZ,1); 
            gpJoueur->setTroc(M_OLIVES,1);
            trouve(C_RIZ); return true; break;
        case 445 :
            gpJoueur->setTroc(M_ROUAGE,0); 
            permuteBloc(1); gpAudio->playSound(39);
            break;
        case 447 :
            i=0; while(gpJoueur->hasBouteille(i)!=1) i++;
            gpJoueur->setBouteille(i,4);
            gpJoueur->setBoostRubis(-160);
            trouve(C_POTION_BLEUE);
            return true; break;
        case 453 : gpJoueur->trouveObjet(O_TROC4,2); trouve(C_CARTE_V); return true; break;
        case 454 : case 456 : gpJoueur->setBoostRubis(-10); break;
        case 463 : gpJoueur->setBoostRubis(-5);
        case 466 : gpJoueur->setBoostRubis(-3);
        case 469 : gpJoueur->setBoostRubis(-1);
        case 472 : gpJoueur->setBoostRubis(-1);
        case 475 : gpJoueur->trouveObjet(O_CANNE); trouve(C_CANNE_1); return true; break;
        case 485 : gpJoueur->trouveObjet(O_POISSONS); break;
        case 488 : gpJoueur->trouveObjet(O_CANNE,2); trouve(C_CANNE_2); return true; break;
        case 491 : gpJoueur->setBouteille(2, 1); trouve(C_BOUTEILLE); return true; break;
        case 493 : gpJoueur->trouveObjet(O_CANNE,3); trouve(C_CANNE_3); return true; break;
        case 496 : gpJoueur->setCoeur(27); trouve(C_QUART_COEUR); return true; break;
        case 498 : gpJoueur->trouveObjet(O_POISSONS,2); trouve(C_VIRE); return true; break;
        case 508 : gpJoueur->trouveObjet(O_TROC2,2); trouve(C_VIELLE_BOTTE); return true; break;
        case 527 : if (gpJoueur->getAvancement()<PARLE_BARMAN_SALOON) 
            gpJoueur->setAvancement(PARLE_BARMAN_SALOON); break;
        case 533 : 
            if (gpJoueur->getAvancement()<DETTE_PAYEE) {
                gpJoueur->setAvancement(DETTE_PAYEE);
                gpJoueur->setTroc(M_ROC_GIVRE,gpJoueur->getTroc(M_ROC_GIVRE)-1);
            } 
            break;
        case 537 : if (gpJoueur->getAvancement()<PARLE_GARS_MINE_SALOON) 
            gpJoueur->setAvancement(PARLE_GARS_MINE_SALOON); break;
        case 539 : if (gpJoueur->getAvancement()<APPREND_POUR_ROC_GIVRE) 
            gpJoueur->setAvancement(APPREND_POUR_ROC_GIVRE); break;
        case 543 : if (gpJoueur->getAvancement()<GARS_MINE_AIDE) 
            gpJoueur->setAvancement(GARS_MINE_AIDE); break;
        case 558 :
            int g;
            int gmax;
            g=gpJoueur->getGanon() + gpJoueur->getBoostGanon();
            gmax = ((gpJoueur->getRubisMax()-(gpJoueur->getRubis() + gpJoueur->getBoostRubis()))/2);
            if (g > gmax) g=gmax;
            gpJoueur->setBoostRubis(g*2);
            gpJoueur->setBoostGanon(-g);
            break;
        case 563 :
            g=gpJoueur->getPiece() + gpJoueur->getBoostPiece();
            gmax = ((gpJoueur->getRubisMax()-(gpJoueur->getRubis() + gpJoueur->getBoostRubis()))/4);
            if (g > gmax) g=gmax;
            gpJoueur->setBoostRubis(g*4);
            gpJoueur->setBoostPiece(-g);
            break;
        case 571 : 
            gpJoueur->trouveObjet(O_TROC1,10); 
            gpJoueur->trouveObjet(O_FFEU);
            trouve(C_FFEU); return true; break;
        case 578 : 
            gpJoueur->trouveObjet(O_TROC2,10); 
            gpJoueur->trouveObjet(O_FGLACE);
            trouve(C_FGLACE); return true; break;
        case 583 : 
            gpJoueur->trouveObjet(O_TROC3,10); 
            gpJoueur->trouveObjet(O_FLUM);
            trouve(C_FLUM); return true; break;
        case 588 : 
            gpJoueur->trouveObjet(O_TROC4,10); 
            gpJoueur->setBouteille(3, 1); 
            trouve(C_BOUTEILLE); return true; break;
        case 592 : gpJoueur->trouveObjet(O_ENCYCL); ecrit(593); return true; break;
        case 593 : gpJoueur->paye(); break;
        case 602 :
            g=gpJoueur->getRubis() + gpJoueur->getBoostRubis();
            if (g%2 != 0) g--;
            gmax = (gpJoueur->getGanonMax()-(gpJoueur->getGanon() + gpJoueur->getBoostGanon()))*2;
            if (g > gmax) g=gmax;
            gpJoueur->setBoostRubis(-g);
            gpJoueur->setBoostGanon(g/2);
            break;
        case 607 :
            g=gpJoueur->getPiece() + gpJoueur->getBoostPiece();
            gmax = ((gpJoueur->getGanonMax()-(gpJoueur->getGanon() + gpJoueur->getBoostGanon()))/2);
            if (g > gmax) g=gmax;
            gpJoueur->setBoostPiece(-g);
            gpJoueur->setBoostGanon(g*2);
            break;
        case 616 : gpJoueur->trouveObjet(O_TROC2,7); trouve(C_PLAN_PONT); return true; break;
        case 622 :
            if (gpJoueur->getTroc(M_POIVRON)==-1) gpJoueur->setTroc(M_POIVRON,0);
            gpJoueur->setTroc(M_POIVRON,gpJoueur->getTroc(M_POIVRON)+1);
            trouve(C_POIVRON); return true; break;
        case 633 : gpJoueur->trouveObjet(O_GRAPPIN); trouve(C_GRAPPIN); return true; break;
        case 638 : if (gpJoueur->getAvancement()<SAGES_GROTTE) 
            gpJoueur->setAvancement(SAGES_GROTTE); break;
        case 641 : 
            gpJoueur->setBoostGanon(-10);
            gpJoueur->setFleche(gpJoueur->getFleche()+10); 
            gpAudio->playSound(13);
            ecrit(375); return true; break;
        case 643 : 
            gpJoueur->setBoostGanon(-15);
            gpJoueur->setBombe(gpJoueur->getBombe()+5); 
            gpAudio->playSound(13);
            ecrit(375); return true; break;
        case 645 :
            gpJoueur->setBoostGanon(-4);
            gpJoueur->setBoostVie(gpJoueur->getBoostVie()+2);
            if (gpJoueur->getVie()==gpJoueur->getVieMax()) gpAudio->playSound(15);
            ecrit(375); return true; break;
        case 647 : 
            gpJoueur->setBoostGanon(-8);
            gpJoueur->setBoostMagie(gpJoueur->getBoostMagie()+gpJoueur->getMagieMax()/8);
            gpAudio->playSound(13);
            ecrit(375); return true; break;
        case 649 : 
            gpJoueur->setBoostGanon(-16);
            gpJoueur->setBoostMagie(gpJoueur->getBoostMagie()+gpJoueur->getMagieMax()/4);
            if (gpJoueur->getMagie()<gpJoueur->getMagieMax())
                gpAudio->playSound(37);
            else gpAudio->playSound(13);
            ecrit(375); return true; break;
        case 654 :
            if (gpJoueur->getCafe()==-1) {gpJoueur->boostCafe(); gpJoueur->payeCafe();}
            break;
        case 655 : case 656 : case 657 : case 658 : case 659 : case 660 : case 661 : 
        case 662 : case 663 : case 664 : case 665 : case 666 : case 667 : case 668 : 
        case 669 : case 670 : case 671 : 
            if (gpJoueur->getCafe() == gpJoueur->getCafePaye()) break;
            gpJoueur->setBoostGanon(25); gpJoueur->payeCafe(); break;
        case 672 : gpJoueur->trouveGemme(173); trouve(C_GEMME); return true; break;
        case 673 : gpJoueur->setBoostGanon(5); break;
        case 678 :
            i=0; while(gpJoueur->hasBouteille(i)!=1) i++;
            gpJoueur->setBouteille(i,2);
            gpJoueur->setBoostGanon(-40);
            trouve(C_POTION_ROUGE);
            return true;
        case 680 :
            i=0; while(gpJoueur->hasBouteille(i)!=1) i++;
            gpJoueur->setBouteille(i,3);
            gpJoueur->setBoostGanon(-25);
            trouve(C_POTION_VERTE);
            return true;
        case 683 : gpJoueur->trouveObjet(O_TROC1,4); trouve(C_BIJOUX); return true; break;
        case 690 : gpJoueur->trouveObjet(O_TROC4,5); trouve(C_CROISSANT); return true; break;
        case 694 : gpJoueur->setGanonMax(99); trouve(C_BOURSE_11); return true; break;
        case 703 :
            g=gpJoueur->getRubis() + gpJoueur->getBoostRubis();
            while (g%4 != 0) g--;
            gmax = (gpJoueur->getPieceMax()-(gpJoueur->getPiece() + gpJoueur->getBoostPiece()))*4;
            if (g > gmax) g=gmax;
            gpJoueur->setBoostRubis(-g);
            gpJoueur->setBoostPiece(g/4);
            break;
        case 708 :
            g=gpJoueur->getGanon() + gpJoueur->getBoostGanon();
            if (g%2 != 0) g--;
            gmax = (gpJoueur->getPieceMax()-(gpJoueur->getPiece() + gpJoueur->getBoostPiece()))*2;
            if (g > gmax) g=gmax;
            gpJoueur->setBoostGanon(-g);
            gpJoueur->setBoostPiece(g/2);
            break;
        case 718 : gpJoueur->setCoffre(15,22); break;
        case 723 : gpJoueur->trouveObjet(O_TROC1,3); trouve(C_FER_A_CHEVAL); return true; break;
        case 730 : gpJoueur->trouveObjet(O_TROC2,4); trouve(C_CLOCHETTE); return true; break;
        case 736 : gpJoueur->trouveObjet(O_TROC3,4); trouve(C_MIRROIR); return true; break;
        case 742 : gpJoueur->setEpee(0); ecrit(744); return true; break;
        case 746 : gpJoueur->setEpee(3); trouve(C_EPEE_R); return true; break;
        case 750 : 
            gpJoueur->setBoostPiece(-5);
            gpJoueur->setFleche(gpJoueur->getFleche()+10); 
            gpAudio->playSound(13);
            ecrit(375); return true; break;
        case 752 : 
            gpJoueur->setBoostPiece(-10);
            gpJoueur->setBombe(gpJoueur->getBombe()+5); 
            gpAudio->playSound(13);
            ecrit(375); return true; break;
        case 754 :
            gpJoueur->setBoostPiece(-1);
            gpJoueur->setBoostVie(gpJoueur->getBoostVie()+2);
            if (gpJoueur->getVie()==gpJoueur->getVieMax()) gpAudio->playSound(15);
            ecrit(375); return true; break;
        case 756 : 
            gpJoueur->setBoostPiece(-3);
            gpJoueur->setBoostMagie(gpJoueur->getBoostMagie()+gpJoueur->getMagieMax()/8);
            gpAudio->playSound(13);
            ecrit(375); return true; break;
        case 758 : 
            gpJoueur->setBoostPiece(-6);
            gpJoueur->setBoostMagie(gpJoueur->getBoostMagie()+gpJoueur->getMagieMax()/4);
            if (gpJoueur->getMagie()<gpJoueur->getMagieMax())
                gpAudio->playSound(37);
            else gpAudio->playSound(13);
            ecrit(375); return true; break;
        case 760 : gpJoueur->trouveObjet(O_LIVRE); break;
        case 762 : if (gpJoueur->getAvancement()<TEMPETE_NEIGE_FINIE) 
            gpJoueur->setAvancement(TEMPETE_NEIGE_FINIE); break;
        case 767 :
            i=0; while(gpJoueur->hasBouteille(i)!=1) i++;
            gpJoueur->setBouteille(i,2);
            gpJoueur->setBoostPiece(-15);
            trouve(C_POTION_ROUGE);
            return true; break;
        case 769 :
            i=0; while(gpJoueur->hasBouteille(i)!=1) i++;
            gpJoueur->setBouteille(i,3);
            gpJoueur->setBoostPiece(-10);
            trouve(C_POTION_VERTE);
            return true; break;
        case 771 : gpJoueur->setPieceMax(99); trouve(C_BOURSE_21); return true; break;
        case 782 : gpJoueur->trouveObjet(O_TROC4,6); trouve(C_BIERRE); return true; break;
        case 789 : gpJoueur->setBoostPiece(-1); ecrit(791); return true; break;
        case 791 : gpJoueur->setCoffre(15,23,1); break;
        case 792 : gpJoueur->setCoffre(15,23,2); break;
        case 793 : gpJoueur->setCoffre(15,23,3); 
            if (gpJoueur->getAvancement()<INFO_PASSE_OK) 
            gpJoueur->setAvancement(INFO_PASSE_OK); break;
        case 806 : if (gpJoueur->getAvancement()<GANON_CAPTURE) 
            gpJoueur->setAvancement(GANON_CAPTURE); break;
        case 815 : gpJoueur->trouveGemme(178); trouve(C_GEMME); return true; break;
        case 825 : gpJoueur->trouveObjet(O_TROC2,6); trouve(C_CORDE); return true; break;
        case 831 : gpJoueur->trouveObjet(O_TROC1,7); break;
        case 836 : gpJoueur->setCoffre(15,26); trouve(C_ALL_RIEN); return true; break;
        case 856 : gpJoueur->trouveGemme(182); trouve(C_GEMME); return true; break;
        case 861 : gpJoueur->trouveObjet(O_TROC1,5); trouve(C_LETTRE); return true; break;
        case 867 :
            if (gpJoueur->getCoffre(15,27)==0) {
                gpJoueur->setCoffre(15,27,1);
                gpAudio->playSound(20); 
                gpMonde->passage(20,36,1);
            }
            break;
        case 869 :
            if (gpJoueur->getCoffre(15,27)==1) {
                gpJoueur->setCoffre(15,27,2);
                gpAudio->playSound(20); 
                gpMonde->passage(100,21,1);
            }
            break;
        case 870 :
            if (gpJoueur->getCoffre(15,27)==2) {
                gpJoueur->setCoffre(15,27,3);
                gpAudio->playSound(20); 
                gpMonde->passage(80,36,1);
            }
            break;
        case 872 :
            if (gpJoueur->getCoffre(15,27)==3) {
                gpJoueur->setCoffre(15,27,4);
                gpAudio->playSound(20); 
                gpMonde->passage(40,21,1);
            }
            break;
        case 873 :
            if (gpJoueur->getCoffre(15,27)==4) {
                gpJoueur->setCoffre(15,27,5);
                gpAudio->playSound(20); 
                gpMonde->passage(100,36,1);
            }
            break;
        case 875 :
            if (gpJoueur->getCoffre(15,27)==5) {
                gpJoueur->setCoffre(15,27,6);
                gpAudio->playSound(20); 
                gpMonde->passage(20,21,1);
            }
            break;
        case 877 :
            if (gpJoueur->getCoffre(15,27)==6) {
                gpJoueur->setCoffre(15,27,7);
                gpAudio->playSound(20); 
                gpMonde->passage(80,21,1);
            }
            break;
        case 878 :
            if (gpJoueur->getCoffre(15,27)==7) {
                gpJoueur->setCoffre(15,27,8);
                gpAudio->playSound(20); 
                gpMonde->passage(40,36,1);
            }
            break;
        case 879 :
            if (gpJoueur->getCoffre(15,27)==8) {
                gpJoueur->setCoffre(15,27,9);
                gpPnj->getSuivant()->setXDep(209*16+8);
                gpPnj->getSuivant()->setYDep(4*16);
            }
            break;
        case 881 :
            if (gpJoueur->getCoffre(15,27)==9) {
                gpJoueur->setCoffre(15,27,10);
                gpAudio->playSound(20); 
                gpMonde->passage(160,21,11);
            }
            break;
        case 883 :
            if (gpJoueur->getCoffre(15,27)==10) {
                gpJoueur->setCoffre(15,27,11);
                gpAudio->playSound(20); 
                gpMonde->passage(149,30,10);
            }
            break;
        case 885 :
            if (gpJoueur->getCoffre(15,27)==11) {
                gpJoueur->setCoffre(15,27,12);
                gpAudio->playSound(20); 
                gpMonde->passage(209,15,10);
            }
            break;
        case 890 : gpJoueur->trouveObjet(O_TROC3,8); trouve(C_SCIE); return true; break;
        case 898 : gpJoueur->trouveObjet(O_TROC3,2); trouve(C_BOUTEILLE_VIN); return true; break;
        case 902 : 
            switch (zone) {
                case 151 :
                    gpAudio->stopMusic();
                    SDL_Delay(500);
                    gpAudio->playSound(40);
                    gpKeyboard->attendEntreeOuTemps(3500);
                    gpAudio->stopSound();
                    gpAudio->replayMusic();
                    if (!gpJoueur->hasMelodie(0)) {
                        gpJoueur->setMelodie(0); trouve(C_CHANT_ENVOL); return true;}
                    break;
                case 152 :
                    gpAudio->stopMusic();
                    SDL_Delay(500);
                    gpAudio->playSound(41);
                    gpKeyboard->attendEntreeOuTemps(8500);
                    gpAudio->stopSound();
                    gpAudio->replayMusic();
                    if (!gpJoueur->hasMelodie(1)) {
                        gpJoueur->setMelodie(1); trouve(C_TEMPS_INV); return true;}
                    break;
                case 153 :
                    gpAudio->stopMusic();
                    SDL_Delay(500);
                    gpAudio->playSound(42);
                    gpKeyboard->attendEntreeOuTemps(7500);
                    gpAudio->stopSound();
                    gpAudio->replayMusic();
                    if (!gpJoueur->hasMelodie(2)) {
                        gpJoueur->setMelodie(2); trouve(C_TEMPS_ACC); return true;}
                    break;
            }
            break;
        case 910 : gpJoueur->trouveObjet(O_TROC1,6); trouve(C_ALLIANCE); 
            gpPnj->getSuivant()->setImmo(false); return true; break;
        case 918 : gpJoueur->trouveObjet(O_TROC3,6); trouve(C_CRANE); return true; break;
        case 923 : 
            gpJoueur->setCoffre(15,28,1); 
            pnj = gpPnj->getSuivant();
            while (pnj != NULL) {
                if (pnj->getId() == 90) {pnj->setVie(0); break;}
                pnj = pnj->getSuivant();
            }
            gpMonde->passage(60,19,4);
            break;
        case 926 : 
            gpJoueur->setCoffre(15,28,2);
            gpAudio->playSound(5);
            SDL_Delay(1500);
            gpAudio->stopSpecial();
            pnj = gpPnj->getSuivant();
            while (pnj != NULL) {
                if (pnj->getId() == 90 || pnj->getId() == 101) pnj->setVie(0);
                pnj = pnj->getSuivant();
            }
            break;
        case 938 : if (gpAudio->isSpecial()) {ecrit(1352); return true;} break;
        case 942 : gpJoueur->setCle(zone-46,0); break;
        case 943 : gpJoueur->setCle(zone-46,1); break;
        case 944 : gpJoueur->setCle(zone-46,2); break;
        
        case 945 : 
            if (zone>=46 && zone<=60) gpJoueur->setCle(zone-46,3,gpJoueur->getCle(zone-46,3)+1);
            switch (zone) {
                case 46 :
                    if (gpMonde->regionValue(0) == 60*16) gpJoueur->setCoffre(0,17);
                    if (gpMonde->regionValue(0) == 180*16) gpJoueur->setCoffre(0,18);
                    if (gpMonde->regionValue(0) == 260*16) gpJoueur->setCoffre(0,19);
                    if (gpMonde->regionValue(0) == 300*16) gpJoueur->setCoffre(0,20);
                    if (gpMonde->regionValue(0) == 200*16) gpJoueur->setCoffre(0,21);
                    break;
                case 47 :
                    if (gpMonde->regionValue(0) == 160*16) gpJoueur->setCoffre(1,10);
                    if (gpMonde->regionValue(0) == 200*16) gpJoueur->setCoffre(1,11);
                    if (gpMonde->regionValue(0) == 240*16) gpJoueur->setCoffre(1,12);
                    if (gpMonde->regionValue(0) == 320*16) gpJoueur->setCoffre(1,13);
                    if (gpMonde->regionValue(0) == 340*16) gpJoueur->setCoffre(1,14);
                    if (gpMonde->regionValue(0) == 280*16) gpJoueur->setCoffre(1,16);
                    break;
                case 48 :
                    if (gpMonde->regionValue(0) == 200*16) gpJoueur->setCoffre(2,8);
                    if (gpMonde->regionValue(0) == 60*16 && gpMonde->regionValue(1) == 0) 
                        gpJoueur->setCoffre(2,9);
                    if (gpMonde->regionValue(0) == 180*16) gpJoueur->setCoffre(2,10);
                    if (gpMonde->regionValue(0) == 80*16) gpJoueur->setCoffre(2,11);
                    if (gpMonde->regionValue(0) == 60*16 && gpMonde->regionValue(1) == 60*16) 
                        gpJoueur->setCoffre(2,12);
                    if (gpMonde->regionValue(0) == 60*16 && gpMonde->regionValue(1) == 30*16) 
                        gpJoueur->setCoffre(2,13);
                    break;
                case 49 :
                    if (gpMonde->regionValue(0) == 100*16) gpJoueur->setCoffre(3,1);
                    if (gpMonde->regionValue(0) == 80*16) gpJoueur->setCoffre(3,2);
                    if (gpMonde->regionValue(0) == 60*16) gpJoueur->setCoffre(3,3);
                    if (gpMonde->regionValue(0) == 200*16) gpJoueur->setCoffre(3,4);
                    break;
                case 50 :
                    if (gpMonde->regionValue(0) == 80*16) gpJoueur->setCoffre(4,6);
                    if (gpMonde->regionValue(0) == 140*16) gpJoueur->setCoffre(4,7);
                    if (gpMonde->regionValue(0) == 280*16 && gpMonde->regionValue(1) == 30*16) 
                        gpJoueur->setCoffre(4,8);
                    if (gpMonde->regionValue(0) == 280*16 && gpMonde->regionValue(1) == 75*16) 
                        gpJoueur->setCoffre(4,9);
                    break;
                case 51 :
                    if (gpMonde->regionValue(0) == 100*16) gpJoueur->setCoffre(5,4);
                    if (gpMonde->regionValue(0) == 220*16) gpJoueur->setCoffre(5,5);
                    if (gpMonde->regionValue(0) == 260*16) gpJoueur->setCoffre(5,6);
                    break;
                case 52 :
                    if (gpMonde->regionValue(0) == 80*16) gpJoueur->setCoffre(6,5);
                    if (gpMonde->regionValue(0) == 160*16) gpJoueur->setCoffre(6,6);
                    if (gpMonde->regionValue(0) == 140*16) gpJoueur->setCoffre(6,7);
                    if (gpMonde->regionValue(0) == 200*16) gpJoueur->setCoffre(6,8);
                    break;
                case 53 :
                    if (gpMonde->regionValue(0) == 0) gpJoueur->setCoffre(7,5);
                    if (gpMonde->regionValue(0) == 60*16) gpJoueur->setCoffre(7,6);
                    if (gpMonde->regionValue(0) == 100*16) gpJoueur->setCoffre(7,7);
                    if (gpMonde->regionValue(0) == 140*16) gpJoueur->setCoffre(7,8);
                    break;
                case 54 :
                    if (gpMonde->regionValue(0) == 20*16 && gpMonde->regionValue(1) == 0) 
                        gpJoueur->setCoffre(8,10);
                    if (gpMonde->regionValue(0) == 20*16 && gpMonde->regionValue(1) == 15*16) 
                        gpJoueur->setCoffre(8,11);
                    if (gpMonde->regionValue(0) == 60*16) gpJoueur->setCoffre(8,12);
                    if (gpMonde->regionValue(0) == 100*16 && gpMonde->regionValue(1) == 15*16) 
                        gpJoueur->setCoffre(8,13);
                    if (gpMonde->regionValue(0) == 100*16 && gpMonde->regionValue(1) == 60*16) 
                        gpJoueur->setCoffre(8,14);
                    if (gpMonde->regionValue(0) == 120*16) gpJoueur->setCoffre(8,15);
                    if (gpMonde->regionValue(0) == 140*16) gpJoueur->setCoffre(8,16);
                    if (gpMonde->regionValue(0) == 220*16) gpJoueur->setCoffre(8,17);
                    if (gpMonde->regionValue(0) == 240*16) gpJoueur->setCoffre(8,18);
                    break;
                case 55 :
                    if (gpMonde->regionValue(0) == 40*16) gpJoueur->setCoffre(9,1);
                    if (gpMonde->regionValue(0) == 60*16) gpJoueur->setCoffre(9,2);
                    if (gpMonde->regionValue(0) == 80*16) gpJoueur->setCoffre(9,3);
                    if (gpMonde->regionValue(0) == 100*16) gpJoueur->setCoffre(9,4);
                    break;
                case 56 :
                    if (gpMonde->regionValue(0) == 0) gpJoueur->setCoffre(10,4);
                    if (gpMonde->regionValue(0) == 100*16) gpJoueur->setCoffre(10,5);
                    if (gpMonde->regionValue(0) == 180*16) gpJoueur->setCoffre(10,6);
                    break;
                case 57 :
                    if (gpMonde->regionValue(0) == 180*16) gpJoueur->setCoffre(11,1);
                    if (gpMonde->regionValue(0) == 40*16) gpJoueur->setCoffre(11,2);
                    if (gpMonde->regionValue(0) == 80*16) gpJoueur->setCoffre(11,3);
                    break;
                case 58 :
                    if (gpMonde->regionValue(0) == 20*16) gpJoueur->setCoffre(12,1);
                    if (gpMonde->regionValue(0) == 40*16) gpJoueur->setCoffre(12,2);
                    if (gpMonde->regionValue(0) == 80*16) gpJoueur->setCoffre(12,3);
                    if (gpMonde->regionValue(0) == 100*16) gpJoueur->setCoffre(12,4);
                    if (gpMonde->regionValue(0) == 120*16) gpJoueur->setCoffre(12,5);
                    break;
                case 59 :
                    if (gpMonde->regionValue(0) == 60*16) gpJoueur->setCoffre(13,1);
                    if (gpMonde->regionValue(0) == 140*16) gpJoueur->setCoffre(13,2);
                    break;
                case 60 : gpJoueur->setCoffre(14,1); break;
                case 155 :
                    if (gpJoueur->getAvancement()<CLE_PRISON_F_TROUVEE) 
                        gpJoueur->setAvancement(CLE_PRISON_F_TROUVEE);
                    break;
            }
            break;
        case 947 : 
            gpJoueur->trouveObjet(O_ARC,2); gpJoueur->setFleche(gpJoueur->getFlecheMax()); break;
        case 948 : case 949 : case 950 : case 962 : case 965 : 
        case 967 : case 969 : case 971 : ecrit(199); return true; break;
        case 951 : gpJoueur->trouveObjet(O_GANTS); break;
        case 955 : gpJoueur->trouveObjet(O_LANTERNE); gpJoueur->setMagie(gpJoueur->getMagieMax()); break;
        case 956 : gpJoueur->trouveObjet(O_PALMES); break;
        case 960 : 
            if (!gpJoueur->getCoffre(3,29)) {
                gpJoueur->setCoffre(3,29); ecrit(199); return true;} 
            break;
        case 961 : gpJoueur->setTunique(2); gpJoueur->calculDef(); break;
        case 963 : gpJoueur->trouveObjet(O_MARTEAU); ecrit(199); return true; break;
        case 964 : gpJoueur->trouveObjet(O_GANTS, 2); break;
        case 966 : gpJoueur->trouveObjet(O_ARC, 5); gpJoueur->setFleche(gpJoueur->getFlecheMax()); break;
        case 968 : gpJoueur->trouveObjet(O_BGLACE); gpJoueur->setMagie(gpJoueur->getMagieMax()); break;
        case 970 : gpJoueur->trouveObjet(O_BFEU); gpJoueur->setMagie(gpJoueur->getMagieMax()); break;
        case 972 : gpJoueur->setBouclier(3); gpJoueur->calculDef(); break;
        case 980 : if (gpJoueur->getAvancement()<SPEECH_AGAHNIM) 
            gpJoueur->setAvancement(SPEECH_AGAHNIM); break;
        case 982 : gpPnj->getSuivant()->setDirection(N); 
            gpJoueur->setImmo(true); setStop(true); break;
        case 998 : trouve(C_EPEE_J); gpJoueur->setEpee(5); return true; break;
        case 999 : trouve(C_ARC_OR); gpJoueur->trouveObjet(O_ARC_OR); return true; break;
        case 1000 : ecrit(1001); return true;
        case 1001 :
            gpAudio->playSound(5);
            gpMonde->transitFull(19, 16*39+8, 16*45+8);
            break;
        case 1003 : if (gpJoueur->getAvancement()<TELE_ZELDA) 
            gpJoueur->setAvancement(TELE_ZELDA); ecrit(199); return true; break;
        case 1006 : if (gpJoueur->getAvancement()<PARLE_GARDE_PALAIS) 
            gpJoueur->setAvancement(PARLE_GARDE_PALAIS); break;
        case 1008 : if (gpJoueur->getAvancement()<PARLE_GARDE_RESERVE) 
            gpJoueur->setAvancement(PARLE_GARDE_RESERVE); break;
        case 1011 : gpJoueur->setBouclier(1); break;
        case 1012 : gpJoueur->setRubisMax(99); break;
        case 1013 : if (gpJoueur->getAvancement()<RESERVE_VIDE) 
            gpJoueur->setAvancement(RESERVE_VIDE); break;
        case 1019 : if (gpJoueur->getAvancement()<PARLE_ZELDA_PALAIS) 
            gpJoueur->setAvancement(PARLE_ZELDA_PALAIS); break;
        case 1020 : if (gpJoueur->getAvancement()<PARLE_GARDE_CH_FORTE) 
            gpJoueur->setAvancement(PARLE_GARDE_CH_FORTE); break;
        case 1022 : 
            if (gpJoueur->getAvancement()<PARLE_GARDE_SOUS_SOL) {
                gpJoueur->setAvancement(PARLE_GARDE_SOUS_SOL); 
                gpAudio->playSound(20); gpMonde->passage(100,171,1);
            } break;
        case 1028 : if (gpJoueur->getAvancement()<RIDEAUX_REPERES) 
            gpJoueur->setAvancement(RIDEAUX_REPERES); break;
        case 1030 : if (gpJoueur->getAvancement()<PASSAGE_TROUVE) 
            gpJoueur->setAvancement(PASSAGE_TROUVE);
            gpAudio->playSound(9); gpMonde->passage(109,165,4); 
            ecrit(1031); return true; break;
        case 1048 : 
            gpJoueur->setIvre(); 
            gpJoueur->setBoostVie(gpJoueur->getBoostVie()+2); break;
        case 1058 :
            if (gpJoueur->getTroc(M_SOURCE_ENERGIE)==-1) gpJoueur->setTroc(M_SOURCE_ENERGIE,0);
            gpJoueur->setTroc(M_SOURCE_ENERGIE,gpJoueur->getTroc(M_SOURCE_ENERGIE)+1); break;
        case 1061 : if (gpJoueur->getAvancement()<MOT_DE_PASSE_DONNE) 
            gpJoueur->setAvancement(MOT_DE_PASSE_DONNE); break;
        case 1063 : if (gpJoueur->getAvancement()<MULTIPASSE_UTILISE) 
            gpJoueur->setAvancement(MULTIPASSE_UTILISE); break;
        case 1070 : if (gpJoueur->getAvancement()<MOT_DE_PASSE_CONNU) 
            gpJoueur->setAvancement(MOT_DE_PASSE_CONNU); break;
        case 1073 : if (gpJoueur->getAvancement()<MULTIPASS) 
            gpJoueur->setAvancement(MULTIPASS); break;
        case 1076 : gpJoueur->trouveObjet(O_TROC4,7); trouve(C_CLOUS); return true; break;
        case 1080 : gpJoueur->trouveObjet(O_OCARINA); break;
        case 1081 : 
            gpKeyboard->setMode(0);
            if (gpJoueur->getAvancement()<RETOUR_PRESENT) 
            gpJoueur->setAvancement(RETOUR_PRESENT); 
            newy=25*16+8; newx=69*16+8; newdir=N; newzone=57; finZone();
            ecrit(1082); return true; break;
        case 1084 : 
            gpKeyboard->setMode(0);
            if (gpJoueur->getAvancement()<ARRIVE_PASSE) 
            gpJoueur->setAvancement(ARRIVE_PASSE);
            newx=51*16+8; newy=42*16+8; newdir=N; newzone=9; finZone(); break;
        case 1087 : 
            gpJoueur->trouveObjet(O_TROC3,5); trouve(C_CUILLIERE);
            gpMonde->setMap(62,5,6290); gpMonde->setMap(63,5,6291);
            return true; break;
        case 1091 : gpJoueur->setTunique(3); gpJoueur->calculDef(); break;
        case 1093 :
            gpJoueur->trouveObjet(O_ARC_OR,2);
            ecrit(1094); return true; break;
        case 1098 : gpJoueur->setImmo(true); break;
        case 1099 : if (gpJoueur->getAvancement()<SPEECH_GANON) 
            gpJoueur->setAvancement(SPEECH_GANON); break;
        case 1109 : if (gpJoueur->getAvancement()<SPEECH_GANONDORF) 
            gpJoueur->setAvancement(SPEECH_GANONDORF); break;
        case 1110 : gpAudio->playSpecial(5); gpKeyboard->setMode(11);
            ecrit(1111, false, true, 0, 0, 322, 240); break;
        case 1111 :
            gpAudio->stopSpecial();
            gpAudio->stopMusic(); 
            gpGenerique->initScore();
            zone = 79;
            gpJoueur->setVie(gpJoueur->getVieMax());
            gpJoueur->setXDep(152);
            gpJoueur->setYDep(72);
            gpJoueur->setDirDep(S);
            gpJoueur->save();
            gpKeyboard->setMode(14); break;
        case 1117 :
            gpJoueur->setBoostGanon(-10); 
            gpAudio->playSound(20); 
            gpMonde->passage(69,90,0);
            gpJoueur->setCompteurVisible(true);
            gpJoueur->setCompteur(10);
            break;
        case 1124 : gpJoueur->setBoostGanon(-5); break;
        case 1126 : 
            gpJoueur->setBoostGanon(-10); 
            
            if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==0) {
                gpJoueur->setTempsVisible(true);
                gpJoueur->initTimeC();
                break;
            }
            
            gpJoueur->setCoffre(12,13,1);
            
            if (gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==75*16) break;
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==15*16) break;
            
            enn = gpEnnemi->getSuivant();
            while (enn != NULL) {
                if (enn->isActif() && (enn->getEnnId() == 124 || enn->getEnnId() == 125)) {
                    enn->setTypeIA(IA_RANDOM);
                }
                enn = enn->getSuivant();
            }
            break;
        case 1129 : 
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==15*16) {
                gpJoueur->setBoostGanon(-(gpJoueur->getCoffre(12,13)-2)); 
            }
            
            if (gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==75*16) {
                trouve(C_CARTE_D); return true; break;
            }
            if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==75*16) {
                trouve(C_BOUSSOLE); return true; break;
            }
            trouve(C_CLE);
            gpJoueur->setTempsVisible(false);
            return true; break;
        case 1130 :
            if (gpJoueur->getGanon() + gpJoueur->getBoostGanon() <= 0) {
                zone = 44; // 44 car futur
                int retX = gpJoueur->getXDep();
                int retY = gpJoueur->getYDep();
                gpAudio->playSound(5);
                gpMonde->transitFull(58, retX, retY, N);
            }
            break;
        case 1132 :
            gpJoueur->setBoostGanon(-5); 
            gpJoueur->setCoffre(12,13,1);
            enn = gpEnnemi->getSuivant();
            while (enn != NULL) {
                if (enn->isActif() && enn->getEnnId() == 125) {
                    switch (enn->getSpecial(1)+1) {
                        case 4 : ind = 0; break;
                        case 2 : ind = 1; break;
                        case 1 : ind = 2; break;
                        default : ind = -1;
                    }
                    if (ind > -1) {
                        if (ok[ind]==1) enn->reactiveDes();
                        ok[ind]=1;
                    } else enn->reactiveDes();
                }
                enn = enn->getSuivant();
            }
            break;
        case 1141 : gpJoueur->setCoffre(12,13,1); gpJoueur->setImmo(true); break;
        case 1142 : gpJoueur->setCoffre(12,13,6); gpJoueur->setImmo(true); break;
        //quizz - bonne réponse
        case 1156 : case 1160 : case 1164 : case 1168 : case 1172 :
        case 1176 : case 1180 : case 1184 : case 1188 : case 1192 :
        case 1196 : case 1200 : case 1204 : case 1208 : case 1212 :
        case 1216 : case 1220 : case 1224 : case 1228 : case 1232 :
        case 1236 : case 1240 : case 1244 : case 1248 : case 1252 :
        case 1256 : case 1260 : case 1264 : case 1268 : case 1272 :
        case 1276 : case 1280 : case 1284 : case 1288 : case 1292 :
        case 1296 : case 1300 : case 1304 : case 1308 : case 1312 :
            gpJoueur->setCoffre(12,14,gpJoueur->getCoffre(12,14)+1);
            enn = gpEnnemi->getSuivant();
            while (enn != NULL) {
                if (enn->isActif() && enn->getEnnId() == 127) {
                    if (enn->getVie()==1) {
                        ecrit(1314);
                        return true;
                    }
                    enn->setVie(enn->getVie()-1);
                    if (!enn->getVie()) {
                        donneObjet(enn);
                        break;
                    } else {
                        ecrit(1153);
                        return true;
                    }
                }
                enn = enn->getSuivant();
            }
            break;
        //quizz - mauvaise réponse
        case 1157 : case 1161 : case 1165 : case 1169 : case 1173 :
        case 1177 : case 1181 : case 1185 : case 1189 : case 1193 :
        case 1197 : case 1201 : case 1205 : case 1209 : case 1213 :
        case 1217 : case 1221 : case 1225 : case 1229 : case 1233 :
        case 1237 : case 1241 : case 1245 : case 1249 : case 1253 :
        case 1257 : case 1261 : case 1265 : case 1269 : case 1273 :
        case 1277 : case 1281 : case 1285 : case 1289 : case 1293 :
        case 1297 : case 1301 : case 1305 : case 1309 : case 1313 :
            gpJoueur->setCoffre(12,14,gpJoueur->getCoffre(12,14)+1);
            gpJoueur->setBoostGanon(-gpJoueur->getCompteur());
            gpJoueur->setCompteur(gpJoueur->getCompteur()+10);
            if (gpJoueur->getGanon() + gpJoueur->getBoostGanon() <= 0) {
                zone = 44; // 44 car futur
                int retX = gpJoueur->getXDep();
                int retY = gpJoueur->getYDep();
                gpAudio->playSound(5);
                gpMonde->transitFull(58, retX, retY, N);
                gpAudio->stopSpecial();
                gpStatut->setJauge(false);
            } else {
                ecrit(1153);
            } return true;
            break;
        case 1314 : case 1315 :
            enn = gpEnnemi->getSuivant();
            while (enn != NULL) {
                if (enn->isActif() && enn->getEnnId() == 127) {
                    enn->setVie(0);
                    donneObjet(enn);
                    break;
                }
                enn = enn->getSuivant();
            }
            break;
        case 1316 : gpJoueur->setBouclier(4); gpJoueur->calculDef(); break;
        case 1321 : gpJoueur->setTunique(4); gpJoueur->calculDef(); break;
        case 1332 :
            if (gpMonde->motifValue(69*16, 135*16) == 6729) {
                gpAudio->playSound(20);
                gpMonde->passage(69,135,0);
            }
            if (!gpJoueur->isCompteurVisible()) {
                gpJoueur->setCompteurVisible(true);
                gpJoueur->setCompteur(0);
                gpJoueur->setCompteurEnn(0);
                gpJoueur->razCompteurType();
            }
            break;
        case 1335 :
            gpAudio->playSound(20);
            switch (gpMonde->regionValue(0)) {
                case 0 :
                    gpMonde->passage(9,90,0);
                    gpJoueur->setCoffre(14,9);
                    break;
                case 20*16 :
                    gpMonde->passage(29,90,0);
                    gpJoueur->setCoffre(14,10);
                    break;
                case 40*16 :
                    gpMonde->passage(49,90,0);
                    gpJoueur->setCoffre(14,11);
                    break;
                case 60*16 :
                    if (gpMonde->regionValue(1) == 15*16) {
                        gpMonde->passage(69,15,0);
                        gpJoueur->setCoffre(14,12);
                    }
                    else {
                        gpMonde->passage(69,90,0);
                        gpJoueur->setCoffre(14,13);
                    }
                    break;
                case 80*16 :
                    gpMonde->passage(89,90,0);
                    gpJoueur->setCoffre(14,14);
                    break;
                case 120*16 :
                    gpMonde->passage(129,90,0);
                    gpJoueur->setCoffre(14,15);
                    break;
            }
            break;
        case 1342 : gpJoueur->trouveObjet(O_MASQUE); break;
        case 1345 : 
            gpAudio->playSpecial(29); gpStatut->setJauge(true);
            gpPnj->getSuivant()->setVie(0);
            gpEnnemi->getSuivant()->transforme();
            break;
        case 1348 : 
            gpMonde->transitFull(57,69*16+8,26*16-8); 
            gpAudio->playSpecial(5); return true;
            break;
        case 1358 : /*gpAudio->playSpecial(5);*/ gpKeyboard->setMode(11);
            ecrit(1359, false, true, 0, 0, 322, 240); break;
        case 1360 :
            gpGenerique->initImageFin();
            gpKeyboard->setMode(28); break;
        case 1365 : return false;
        case 1366 : return false;
    }
    testAnim();
    return false;
}

void Jeu::testRamasse(int x, int y, int w, int h) {
    Objet* gpObjet2 = gpObjet->getSuivant();
    while (gpObjet2 != NULL) {
        if (gpObjet2->getVie()) {
            if (x<gpObjet2->getX()+gpObjet2->getW()-2 && x+w>gpObjet2->getX()+2
            && y<gpObjet2->getY()+gpObjet2->getH()-2 && y+h-4>gpObjet2->getY()+2) {
                gpObjet2->ramasse();
            }
        }
        gpObjet2 = gpObjet2->getSuivant();
    }
}

bool Jeu::testEpee(int x, int y, int w, int h, int type, int force, Direction direction) {
    bool retour = false;
    
    //fait fondre caisse
    if (type==FEU && zone == 54) {
        Caisse* gpCaisse2 = gpCaisse->getSuivant();
        while (gpCaisse2 != NULL) {
            if (gpCaisse2->isActif()) {
                if (((x <= gpCaisse2->getX() && x+w > gpCaisse2->getX())
                || (x >= gpCaisse2->getX() && x < gpCaisse2->getX()+16))
                && ((y <= gpCaisse2->getY() && y+h > gpCaisse2->getY())
                || (y >= gpCaisse2->getY() && y < gpCaisse2->getY()+16))) {
                    gpCaisse2->fond();
                    for (int j = gpCaisse2->getY()-8; j < gpCaisse2->getY() + 24; j++)
                    for (int i = gpCaisse2->getX()-8; i < gpCaisse2->getX() + 24; i++) {
                        etteintTorche(i, j);
                    }
                }
            }
            gpCaisse2 = gpCaisse2->getSuivant();
        }
    }
    
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            if (i >= 0 && j >=0) {
                retour = (retour || coupeBuisson(i, j, type));
                if (type==COUP_MARTEAU) retour = (retour || applatitBloc(i, j));
                if (type==FEU) retour = (retour || allumeTorche(i, j));
                if (type==COUP_GLACE) retour = (retour || etteintTorche(i, j));
                if (type==EXPLOSION) retour = (retour || exploseMur(i, j));
                /*if (type==COUP_EPEE || type==EPEE_SPIN) {
                    //retour = (retour || casseBarriere(i, j, type));
                    retour = (retour || renvoieProj(i, j, direction));}*/
                if (type==COUP_EPEE || type==EPEE_SPIN) {
                    retour = (retour || renvoieProj(i, j, direction));
                    retour = (retour || coupeRideau(i, j));
                }
                retour = (retour || tueEnnemi(i, j, type, force, direction));
            }
        }
    }
    return retour;
}

bool Jeu::renvoieProj(int i, int j, Direction dir) {
    
    Snipe* gpSnipe2 = gpSnipe->getSuivant();
    while (gpSnipe2 != NULL) {
        if (i >= gpSnipe2->getX() && i < gpSnipe2->getX() + gpSnipe2->getW()
        && j >= gpSnipe2->getY() && j < gpSnipe2->getY() + gpSnipe2->getH()) {
            if (gpSnipe2->renvoit(dir)) {
                gpAudio->playSound(7);
                return true;
            }
        }
        gpSnipe2 = gpSnipe2->getSuivant();
    }
    
    return false;
}

bool Jeu::coupeRideau(int i, int j) {
    if (gpMonde->motifValue(i,j)==6109) {
        if (gpMonde->motifValue(i-16,j)!=6109) gpMonde->passage(i/16,(j/16)-1,0);
        else gpMonde->passage((i/16)-1,(j/16)-1,0);
        return true;
    }
    return false;
}

bool Jeu::coupeBuisson(int i, int j, int type) {
    int donne = 0;
    bool retour = false;
    if (type==COUP_EPEE || type==EPEE_SPIN || type==FEU 
    || type==COUP_GLACE || type==EXPLOSION) {
        if (gpMonde->motifValue(i,j)==26) {
            if (gpMonde->contenuValue(i,j)==-1) {
                gpMonde->setValeur(i,j,25,-1);
                if (zone==21) gpAudio->playSound(9);
            }
            else gpMonde->setValeur(i, j, 29, -1, 0, 0);
            donne=1;
            ajouteProjectile(9, N, i-(i%16)-5,j-(j%16)-13, 0);
        }    
        if (gpMonde->motifValue(i,j)==385) {
            gpMonde->setValeur(i, j, 386, -1, 0, 0);
            donne=2;
            ajouteProjectile(10, N, i-(i%16)-5,j-(j%16)-13, 0);
        }
        if (gpMonde->motifValue(i,j)==48) {
            gpMonde->setValeur(i, j, 49, -1, 0, 0);
            donne=3;
            ajouteProjectile(11, N, i-(i%16)-5,j-(j%16)-13, 0);
        }
        if (gpMonde->motifValue(i,j)==4399) {
            gpMonde->setValeur(i, j, 4400, -1, 0, 0);
            donne=3;
            ajouteProjectile(12, N, i-(i%16)-5,j-(j%16)-13, 0);
        }
        if (donne) {
            retour=true;
            //nombreMystere = (std::rand() % (MAX - MIN + 1)) + MIN;
            int ob=0;
            int randomV = (int)((float)std::rand() / RAND_MAX * (15*donne));
            //int randomV = (int) ((std::rand() % (15*donne)) + 1);
            switch (randomV) {                        
                case 1: 
                    if ((gpJoueur->getRubis()<gpJoueur->getRubisMax() && getEpoque()==T_PRESENT)
                    || (gpJoueur->getGanon()<gpJoueur->getGanonMax() && getEpoque()==T_FUTUR)
                    || (gpJoueur->getPiece()<gpJoueur->getPieceMax() && getEpoque()==T_PASSE)) 
                    ob=I_RUBIS_VERT; break;
                case 2: if (gpJoueur->getVie()<gpJoueur->getVieMax()) 
                    ob=I_PETIT_COEUR; break;
                case 3: if (gpJoueur->getFleche()<gpJoueur->getFlecheMax()
                    && gpJoueur->hasObjet(O_ARC)) 
                    ob=I_FLECHE; break;
                case 4: if (gpJoueur->getBombe()<gpJoueur->getBombeMax()
                    && gpJoueur->hasObjet(O_SAC_BOMBES)) 
                    ob=I_BOMBE; break;
                case 5: if (gpJoueur->getMagie()<gpJoueur->getMagieMax()
                    && gpJoueur->hasObjet(O_LANTERNE)) 
                    ob=I_MAGIE_PEU; break; 
            }
            if(ob>0) ajouteObjet(ob, i-(i%16), j-(j%16));
        }
    }
    return retour;
}

bool Jeu::applatitBloc(int i, int j) {
    int val = gpMonde->motifValue(i,j);
    if (val==126 || val==393 || val==987) {
        gpMonde->setValeur(i, j, val+1, -1, 0, 0);
        return true;
    }
    if (val>=1923 && val<=1925) { 
        gpMonde->passage(((int)(i/16))-(val-1923),((int)(j/16))-2,2); 
        gpAudio->playSound(9);
        gpJoueur->setCoffre(15,5);
        return true;
    }
    if (val==2077) {
        gpMonde->setValeur(i,j,2076, -1, 0, 0);
        return true;
    }
    if (val==4360) {
        gpMonde->setValeur(i,j,44, -1, 0, 0);
        ajouteProjectile(26, N, i-(i%16), j-(j%16), 0);
        return true;
    }
    if (val==4658) {
        gpMonde->setValeur(i,j,404, -1, 0, 0);
        ajouteProjectile(26, N, i-(i%16), j-(j%16), 0);
        return true;
    }
    if (val==4659) {
        gpMonde->setValeur(i,j,41, -1, 0, 0);
        ajouteProjectile(26, N, i-(i%16), j-(j%16), 0);
        return true;
    }
    if (val==4456) {
        gpMonde->setValeur(i,j,4457, -1, 0, 0);
        return true;
    }
    return false;
}

bool Jeu::allumeTorche(int i, int j) {
    int val = gpMonde->motifValue(i,j);
    if (val==1000 && gpMonde->contenuValue(i,j)==0) {
        gpMonde->setValeur(i, j, 1001, PLEIN);
        if (zone==48) {
            if (i/16==37 && j/16==50) gpJoueur->setCoffre(2,31);
            if (i/16==37 && j/16==54) gpJoueur->setCoffre(2,32);
            if (i/16==68 && j/16==27) gpJoueur->setCoffre(2,33);
            if (i/16==71 && j/16==27) gpJoueur->setCoffre(2,34);
            if (i/16==69 && j/16==41) gpJoueur->setCoffre(2,35);
            if (i/16==70 && j/16==41) gpJoueur->setCoffre(2,36);
            if (i/16==102 && j/16==35) gpJoueur->setCoffre(2,37);
            if (i/16==102 && j/16==39) gpJoueur->setCoffre(2,38);
            if (i/16==109 && j/16==7) gpJoueur->setCoffre(2,39);
            if (i/16==127 && j/16==17) gpJoueur->setCoffre(2,40);
            if (i/16==132 && j/16==17) gpJoueur->setCoffre(2,41);
            if (i/16==186 && j/16==26) gpJoueur->setCoffre(2,42);
            if (i/16==191 && j/16==49) gpJoueur->setCoffre(2,43);
            if (i/16==191 && j/16==34) gpJoueur->setCoffre(2,44);
            if (i/16==196 && j/16==34) gpJoueur->setCoffre(2,45);
            if (i/16==207 && j/16==24) gpJoueur->setCoffre(2,46);
            if (i/16==212 && j/16==24) gpJoueur->setCoffre(2,47);
            if (i/16==204 && j/16==35) gpJoueur->setCoffre(2,48);
            if (i/16==215 && j/16==35) gpJoueur->setCoffre(2,49);
            if (i/16==206 && j/16==51) gpJoueur->setCoffre(2,50);
            if (i/16==213 && j/16==51) gpJoueur->setCoffre(2,51);
            if (i/16==224 && j/16==20) gpJoueur->setCoffre(2,52);
            if (i/16==234 && j/16==26) gpJoueur->setCoffre(2,53);
            if (i/16==229 && j/16==37) gpJoueur->setCoffre(2,54);
            if (i/16==227 && j/16==56) gpJoueur->setCoffre(2,55);
            if (i/16==234 && j/16==53) gpJoueur->setCoffre(2,56);
            if (i/16==242 && j/16==49) gpJoueur->setCoffre(2,57);
            if (i/16==242 && j/16==55) gpJoueur->setCoffre(2,58);
            if (i/16==247 && j/16==57) gpJoueur->setCoffre(2,59);
            if (i/16==252 && j/16==57) gpJoueur->setCoffre(2,60);
        }
        if (zone==49) {
            if (i/16==117 && j/16==35) gpJoueur->setCoffre(3,11);
            if (i/16==117 && j/16==39) gpJoueur->setCoffre(3,12);
            if (i/16==228 && j/16==27) gpJoueur->setCoffre(3,19);
            if (i/16==231 && j/16==27) gpJoueur->setCoffre(3,20);
            if (i/16==237 && j/16==19) gpJoueur->setCoffre(3,21);
            if (i/16==222 && j/16==21) gpJoueur->setCoffre(3,22);
            if (i/16==222 && j/16==9) gpJoueur->setCoffre(3,23);
            if (i/16==230 && j/16==2) gpJoueur->setCoffre(3,24);
            if (i/16==237 && j/16==5) gpJoueur->setCoffre(3,25);
            if (i/16==237 && j/16==9) gpJoueur->setCoffre(3,26);
        }
        if (zone==54) {
            if (i/16==102 && j/16==71) gpJoueur->setCoffre(8,25);
            if (i/16==115 && j/16==62) gpJoueur->setCoffre(8,26);
            if (i/16==127 && j/16==62) gpJoueur->setCoffre(8,27);
            if (i/16==135 && j/16==62) gpJoueur->setCoffre(8,28);
            if (i/16==133 && j/16==76) gpJoueur->setCoffre(8,29);
            if (i/16==107 && j/16==80) gpJoueur->setCoffre(8,30);
            if (i/16==102 && j/16==86) gpJoueur->setCoffre(8,31);
            if (i/16==107 && j/16==86) gpJoueur->setCoffre(8,32);
            if (i/16==130 && j/16==86) gpJoueur->setCoffre(8,33);
            if (i/16==135 && j/16==83) gpJoueur->setCoffre(8,34);
        }
        if (zone==55) {
            if (i/16==47 && j/16==57) gpJoueur->setCoffre(9,23);
            if (i/16==52 && j/16==57) gpJoueur->setCoffre(9,24);
            if (i/16==106 && j/16==15) gpJoueur->setCoffre(9,25);
            if (i/16==115 && j/16==2) gpJoueur->setCoffre(9,26);
            if (i/16==119 && j/16==10) gpJoueur->setCoffre(9,27);
            if (i/16==119 && j/16==22) gpJoueur->setCoffre(9,28);
            if (i/16==136 && j/16==4) gpJoueur->setCoffre(9,29);
            if (i/16==134 && j/16==17) gpJoueur->setCoffre(9,30);
            if (i/16==24 && j/16==102) gpJoueur->setCoffre(9,31);
            if (i/16==35 && j/16==102) gpJoueur->setCoffre(9,32);
            if (i/16==55 && j/16==104) gpJoueur->setCoffre(9,33);
            if (i/16==66 && j/16==104) gpJoueur->setCoffre(9,34);
            if (i/16==73 && j/16==104) gpJoueur->setCoffre(9,35);
            if (i/16==84 && j/16==104) gpJoueur->setCoffre(9,36);
            if (i/16==55 && j/16==112) gpJoueur->setCoffre(9,37);
            if (i/16==84 && j/16==112) gpJoueur->setCoffre(9,38);
            if (i/16==55 && j/16==119) gpJoueur->setCoffre(9,39);
            if (i/16==66 && j/16==119) gpJoueur->setCoffre(9,40);
            if (i/16==73 && j/16==119) gpJoueur->setCoffre(9,41);
            if (i/16==84 && j/16==119) gpJoueur->setCoffre(9,42);
            if (i/16==108 && j/16==122) gpJoueur->setCoffre(9,43);
            if (i/16==111 && j/16==122) gpJoueur->setCoffre(9,44);
            if (i/16==108 && j/16==132) gpJoueur->setCoffre(9,45);
            if (i/16==111 && j/16==132) gpJoueur->setCoffre(9,46);
            if (i/16==97 && j/16==152) gpJoueur->setCoffre(9,47);
            if (i/16==97 && j/16==162) gpJoueur->setCoffre(9,48);
            if (i/16==6 && j/16==201) gpJoueur->setCoffre(9,49);
            if (i/16==27 && j/16==201) gpJoueur->setCoffre(9,50);
            if (i/16==30 && j/16==201) gpJoueur->setCoffre(9,51);
            if (i/16==14 && j/16==219) gpJoueur->setCoffre(9,52);
            if (i/16==23 && j/16==213) gpJoueur->setCoffre(9,53);
            if (i/16==27 && j/16==220) gpJoueur->setCoffre(9,54);
        }
        testAnim();
        return true;
    }
    //sol gelé
    if (val==5629) {
        if (zone == 54) gpJoueur->setCoffre(8,54);
        
        int x1, y1;
        x1=((int)(i/16)); y1=((int)(j/16));
        while(gpMonde->motifValue((x1-1)*16,y1*16)==val) x1--;
        while(gpMonde->motifValue(x1*16,(y1-1)*16)==val) y1--;
        gpMonde->passage(x1,y1,8);
        gpAudio->playSound(9);
        return true;
    }
    return false;
}

bool Jeu::etteintTorche(int i, int j) {
    int val = gpMonde->motifValue(i,j);
    if (val==1001) {
        gpMonde->setValeur(i, j, 1000, -1, PLEIN, 40);
        if (zone==55) {
            if (i/16==47 && j/16==57) gpJoueur->setCoffre(9,23,0);
            if (i/16==52 && j/16==57) gpJoueur->setCoffre(9,24,0);
            if (i/16==106 && j/16==15) gpJoueur->setCoffre(9,25,0);
            if (i/16==115 && j/16==2) gpJoueur->setCoffre(9,26,0);
            if (i/16==119 && j/16==10) gpJoueur->setCoffre(9,27,0);
            if (i/16==119 && j/16==22) gpJoueur->setCoffre(9,28,0);
            if (i/16==136 && j/16==4) gpJoueur->setCoffre(9,29,0);
            if (i/16==134 && j/16==17) gpJoueur->setCoffre(9,30,0);
            if (i/16==24 && j/16==102) gpJoueur->setCoffre(9,31,0);
            if (i/16==35 && j/16==102) gpJoueur->setCoffre(9,32,0);
            if (i/16==55 && j/16==104) gpJoueur->setCoffre(9,33,0);
            if (i/16==66 && j/16==104) gpJoueur->setCoffre(9,34,0);
            if (i/16==73 && j/16==104) gpJoueur->setCoffre(9,35,0);
            if (i/16==84 && j/16==104) gpJoueur->setCoffre(9,36,0);
            if (i/16==55 && j/16==112) gpJoueur->setCoffre(9,37,0);
            if (i/16==84 && j/16==112) gpJoueur->setCoffre(9,38,0);
            if (i/16==55 && j/16==119) gpJoueur->setCoffre(9,39,0);
            if (i/16==66 && j/16==119) gpJoueur->setCoffre(9,40,0);
            if (i/16==73 && j/16==119) gpJoueur->setCoffre(9,41,0);
            if (i/16==84 && j/16==119) gpJoueur->setCoffre(9,42,0);
            if (i/16==108 && j/16==122) gpJoueur->setCoffre(9,43,0);
            if (i/16==111 && j/16==122) gpJoueur->setCoffre(9,44,0);
            if (i/16==108 && j/16==132) gpJoueur->setCoffre(9,45,0);
            if (i/16==111 && j/16==132) gpJoueur->setCoffre(9,46,0);
            if (i/16==97 && j/16==152) gpJoueur->setCoffre(9,47,0);
            if (i/16==97 && j/16==162) gpJoueur->setCoffre(9,48,0);
            if (i/16==6 && j/16==201) gpJoueur->setCoffre(9,49,0);
            if (i/16==27 && j/16==201) gpJoueur->setCoffre(9,50,0);
            if (i/16==30 && j/16==201) gpJoueur->setCoffre(9,51,0);
            if (i/16==14 && j/16==219) gpJoueur->setCoffre(9,52,0);
            if (i/16==23 && j/16==213) gpJoueur->setCoffre(9,53,0);
            if (i/16==27 && j/16==220) gpJoueur->setCoffre(9,54,0);
        }
        testAnim();
        return true;
    }
    //gel eau
    if (val==28 || val==463 || val==466 || (val >= 2450-507 && val <= 2462-507)
    || val==1144 || val==1183 || val==1186 || (val >= 3529 && val <= 3541))
        if (i>gpMonde->regionValue(0)+31 && j>gpMonde->regionValue(1)+31 
        && i<gpMonde->regionValue(2)+-20 && j<gpMonde->regionValue(3)+-20)
            gpMonde->setValeur(i,j,27,-1,GLACE,C_RIEN);
    if (val==540 || val==1207) {
        gpMonde->setValeur(i,j,980,-1,GLACE,C_RIEN);
        gpMonde->setMurs(((int)(i/16))*2,((int)(j/16))*2,2);
    }
    if (val==543 || val==1210) {
        gpMonde->setValeur(i,j,981,-1,GLACE,C_RIEN);
        gpMonde->setMurs(((int)(i/16))*2+1,((int)(j/16))*2,2);
    }
    return false;
}

bool Jeu::exploseMur(int i, int j) {
    int val = gpMonde->motifValue(i,j);
    
    if (val==4360) {
        gpMonde->setValeur(i,j,44, -1, 0, 0);
        ajouteProjectile(26, N, i-(i%16), j-(j%16), 0);
        return true;
    }
    
    if (val==4658) {
        gpMonde->setValeur(i,j,404, -1, 0, 0);
        ajouteProjectile(26, N, i-(i%16), j-(j%16), 0);
        return true;
    }
    
    if (val==4659) {
        gpMonde->setValeur(i,j,41, -1, 0, 0);
        ajouteProjectile(26, N, i-(i%16), j-(j%16), 0);
        return true;
    }
    
    
    
    if (val==532 || val==533 || val ==790 || val==791 || val==4487 || val==1570) {
        switch (val) {
            case 532 : gpMonde->passage(((int)(i/16)),((int)(j/16))-1,0); break;
            case 533 : gpMonde->passage(((int)(i/16))-1,((int)(j/16))-1,0); break;
            case 790 : gpMonde->passage(((int)(i/16)),((int)(j/16))-1,1); break;
            case 791 : gpMonde->passage(((int)(i/16))-1,((int)(j/16))-1,1); break;
            case 1570 : 
                gpMonde->setValeur(((int)(i/16))*16,(((int)(j/16))-3)*16, 999, 1545, 0);
                gpMonde->setValeur(((int)(i/16))*16,(((int)(j/16))-2)*16, 999, 1576, 0);
                gpMonde->setValeur(((int)(i/16))*16,(((int)(j/16))-1)*16, 1571, 1573, 0);
                gpMonde->setValeur(((int)(i/16))*16,((int)(j/16))*16, 1572, 0);
                ajouteProjectile(26, N, ((int)(i/16))*16, ((int)(j/16))*16-8, 0);
                break;
            case 4487 : 
                if (gpMonde->motifValue(i-16,j)==4487) i-=16;
                gpMonde->passage(((int)(i/16)),((int)(j/16))-1,5); break;
        }
        if (zone==1) gpJoueur->setCoffre(15,0);
        if (zone==23) gpJoueur->setCoffre(15,4);
        if (zone==37) gpJoueur->setCoffre(15,3);
        gpAudio->playSound(9);
        return true;
    }
    //donjon
    //h et b
    if (val==2324 || val==2325 || val==2326 || val==2327
    || val==3325 || val==3326 || val==3333 || val==3334
    || val==3739 || val==3740 
    || val==5187 || val==5188
    || val==5836 || val==5837
    || val==6224 || val==6225
    || val==4735 || val==4736) {
        if (zone == 48) gpJoueur->setCoffre(2,7);
        if (zone == 50 && gpMonde->regionValue(0)<240*16) gpJoueur->setCoffre(4,11);
        if (zone == 50 && gpMonde->regionValue(0)>240*16) gpJoueur->setCoffre(4,12);
        if (zone == 51) gpJoueur->setCoffre(5,23);
        if (zone == 55) gpJoueur->setCoffre(9,60);
        if (zone == 57 && gpJoueur->getAvancement()<EXPLOSE_MUR) 
            gpJoueur->setAvancement(EXPLOSE_MUR);
        if (zone == 69) gpJoueur->setCoffre(15,12);
        if (zone == 155 && gpMonde->regionValue(1)==30*16) gpJoueur->setCoffre(15,31);
        if (zone == 155 && gpMonde->regionValue(1)==60*16) gpJoueur->setCoffre(15,32);
        
        int x1 = 0, y1 = 0;
        switch(val) {
            case 2324 : case 3325 :
                x1=((int)(i/16)); y1=((int)(j/16))-1; break;
            case 2325 : case 3326 :
                x1=((int)(i/16))-1; y1=((int)(j/16))-1; break;
            case 2326 : case 3333 : case 6224 : case 4735 :
                x1=((int)(i/16)); y1=((int)(j/16))+2; break;
            case 2327 : case 3334 : case 6225 : case 4736 :
                x1=((int)(i/16))-1; y1=((int)(j/16))+2; break;
            case 3739 : case 5187 : case 5836 :
                x1=((int)(i/16)); y1=((int)(j/16))-1;
                if (gpMonde->motifValue(i+16,j)!=val) x1--; break;
            case 3740 : case 5188 : case 5837 :
                x1=((int)(i/16)); y1=((int)(j/16))+2;
                if (gpMonde->motifValue(i+16,j)!=val) x1--; break;
        }
        gpMonde->passage(x1,y1,4);
        gpAudio->playSound(9);
        return true;
    }
    //g et d
    if (val==3716 || val==3717 || val==5135 || val==5136 || val==6480 || val==6481) {
        if (zone == 50 && gpMonde->regionValue(0)<180*16) gpJoueur->setCoffre(4,5);
        if (zone == 50 && gpMonde->regionValue(0)>180*16) gpJoueur->setCoffre(4,10);
        if (zone == 51) gpJoueur->setCoffre(5,26);
        if (zone == 58 && gpMonde->regionValue(0)==20*16) gpJoueur->setCoffre(12,14);
        if (zone == 58 && gpMonde->regionValue(0)==100*16) gpJoueur->setCoffre(12,15);
        
        int x1, y1;
        x1=((int)(i/16))-1; y1=((int)(j/16))-1;
        switch(val) {
            case 3717 : case 5136 : case 6481 :
                x1+=3; break;
        }
        gpMonde->passage(x1,y1,3);
        gpAudio->playSound(9);
        return true;
    }
    //sol fissuré
    if (val==3790 || val==3791 || val==3792 || val==5433) {
        if (zone == 50 && gpMonde->regionValue(0) == 0) gpJoueur->setCoffre(4,28);
        if (zone == 50 && gpMonde->regionValue(0) == 20*16 && i<26*16) gpJoueur->setCoffre(4,29);
        if (zone == 50 && gpMonde->regionValue(0) == 20*16 && i>=28*16 && i<30*16) gpJoueur->setCoffre(4,30);
        if (zone == 50 && gpMonde->regionValue(0) == 20*16 && i>=33*16 && i<35*16) gpJoueur->setCoffre(4,31);
        if (zone == 50 && gpMonde->regionValue(0) == 20*16 && i>=35*16) gpJoueur->setCoffre(4,32);
        if (zone == 50 && gpMonde->regionValue(0) == 60*16 && i<66*16) gpJoueur->setCoffre(4,33);
        if (zone == 50 && gpMonde->regionValue(0) == 60*16 && i>=69*16 && i<71*16) gpJoueur->setCoffre(4,34);
        if (zone == 50 && gpMonde->regionValue(0) == 60*16 && j<51*16) gpJoueur->setCoffre(4,35);
        if (zone == 50 && gpMonde->regionValue(0) == 60*16 && i>=74*16 && i<76*16 && j>=53*16) gpJoueur->setCoffre(4,36);
        if (zone == 50 && gpMonde->regionValue(0) == 260*16) gpJoueur->setCoffre(4,37);
        if (zone == 53) gpJoueur->setCoffre(7,22);
        
        int x1, y1;
        x1=((int)(i/16)); y1=((int)(j/16));
        while(gpMonde->motifValue((x1-1)*16,y1*16)==val) x1--;
        while(gpMonde->motifValue(x1*16,(y1-1)*16)==val) y1--;
        gpMonde->passage(x1,y1,8);
        gpAudio->playSound(9);
        return true;
    }
    
    return false;
}

bool Jeu::tueEnnemi(int i, int j, int type, int force, Direction direction) {
    Ennemi* gpEnnemi2 = gpEnnemi->getSuivant();
    ZoneRect* z;
    SDL_Rect* r;
    int degats;
    bool retour = false;
    while (gpEnnemi2 != NULL) {
        if (gpEnnemi2->getVie()) {
            
            if (gpEnnemi2->getEnnId() == 141 && gpJoueur->getOni() && type != ENNEMI) {
                gpEnnemi2 = gpEnnemi2->getSuivant();
                continue;
            }
            
            if (type == CAISSE) z = gpEnnemi2->getZoneBase();
            else z = gpEnnemi2->getZonesVulnerables();
            while (z != NULL && gpEnnemi2->getVie()) {
                r = z->getZone();
                if (i >= gpEnnemi2->getX() + r->x && i < gpEnnemi2->getX() + r->x + r->w
                && j >= gpEnnemi2->getY() + r->y && j < gpEnnemi2->getY() + r->y + r->h) {
                    
                    /*if (gpEnnemi2->getEnnId()==50 && (type==COUP_EPEE || type==EPEE_SPIN)) {
                        if (gpEnnemi2->getVie()>100 && gpJoueur->getOni()
                        || gpEnnemi2->getVie()<=100 && !gpJoueur->getOni()) return false;
                    }*/
                    if (gpEnnemi2->getEnnId()==101 && !gpEnnemi2->getSpecial(1)) {
                        gpEnnemi2->enerve();
                        gpEnnemi2->setInvincible(1);
                        return false;
                    }
                    if (gpEnnemi2->getEnnId()==103 && gpEnnemi2->getSpecial(2)>256) {
                        gpEnnemi2->enerve();
                        if (gpEnnemi2->getSpecial(1)==-1) return false;
                    }
                    if (gpEnnemi2->getEnnId()==114 && type==COUP_GLACE) {
                        gpEnnemi2->setVie(0);
                        return false;
                    }
                    
                    
                    if (gpEnnemi2->getEffet(type)) {
                        
                        if ((gpEnnemi2->getEffet(type)==2 && !gpEnnemi2->getInvincible()) 
                        || type == CAISSE) {
                            degats = force;
                            if (gpEnnemi2->getEnnId()!=20 && gpEnnemi2->getEnnId()!=88) {
                                if (type==DEMI) degats=(gpEnnemi2->getVie()+1)/2;
                                gpEnnemi2->setVie(gpEnnemi2->getVie()-degats);
                                if (type==MORTEL) gpEnnemi2->mort();
                            }
                            else {
                                gpMonde->permuteBlocs();
                                if (!verifZoneJoueur(gpJoueur->getX(), 
                                gpJoueur->getY()+8, 16, 16, 2)) 
                                    gpMonde->permuteBlocs();
                            }
                        }
                        if (gpEnnemi2->getVie()) {
                            if (gpEnnemi2->getEnnId()==50 && type == FLECHE 
                                && gpEnnemi2->getVie()>100) gpEnnemi2->gele();
                            if (type == COUP_GLACE && !gpEnnemi2->getInvincible()
                            && gpEnnemi2->getEffet(type)) 
                                gpEnnemi2->gele();
                            if (type == FEU && !gpEnnemi2->getInvincible()) 
                                gpEnnemi2->degele();
                            if (gpEnnemi2->getEffet(type)==2 && !gpEnnemi2->getInvincible()) {
                                gpAudio->playSound(7);
                            }
                            if (gpEnnemi2->getEffet(type)>=1) {
                                if ((!gpEnnemi2->isBoss() && !gpEnnemi2->isBig()) 
                                || !gpEnnemi2->getInvincible()) 
                                    gpEnnemi2->pousse(direction);
                                if (!gpEnnemi2->getInvincible()) gpEnnemi2->setInvincible(1);
                            }
                        }
                        else {
                            gpJoueur->setEnnemi(gpEnnemi2->getEnnId());
                            if (gpEnnemi2->getEnnId() != 93) {
                                gpAudio->playSound(8);
                                ajouteProjectile(15, direction, 
                                    gpEnnemi2->getX()+(gpEnnemi2->getW()/2)-14, 
                                    gpEnnemi2->getY()+(gpEnnemi2->getH()/2)-14, 0);
                            } else {
                                ajoutePnj(71,gpEnnemi2->getX(),gpEnnemi2->getY(),952);
                            }
                            donneObjet(gpEnnemi2);
                            testAnim();
                        }
                        
                    }
                    retour = true;
                }
                z = z->getSuivant();
            }
        }
        gpEnnemi2 = gpEnnemi2->getSuivant();
    }
    return retour;;
}

void Jeu::donneObjet(Ennemi* ennemi) {
    int obj = 0;
    
    if (ennemi->isBoss()) {
        gpStatut->setJauge(false);
        gpAudio->playSpecial(3);
        if (zone < 60) {
            obj = I_COEUR;
            if (zone == 57) {
                if (gpMonde->regionValue(1)==0) {
                    obj = I_TRIFORCE;
                } else {
                    ajouteEnnemi(89,169*16+6,19*16);
                    Ennemi* enn = ennemi->getSuivant();
                    while (enn != NULL) {
                        if (enn->getEnnId() == 89) enn->setVie(0);
                        enn = enn->getSuivant();
                    }
                    return;
                }
            }
            if (zone==46) {ajouteObjet(obj, 349*16+8, 9*16); return;}
            if (zone==48) {ajouteObjet(obj, 289*16+8, 33*16); return;}
            if (zone==52) {ajouteObjet(obj, 249*16+8, 33*16); return;}
            if (zone==53) {ajouteObjet(obj, 189*16+8, 84*16); return;}
            if (zone==55) {ajouteObjet(obj, 69*16+8, 39*16); return;}
        }
        /*else {
            if (zone==28 && ennemi->getEnnId()!=50) {
                gpAudio->stopSpecial();
                gpStatut->setJauge(false);
                gpJoueur->setCoffre(13,10); return;
            }
            if (zone==28) obj = I_TRIFORCE; else obj=0;
            gpAudio->playSpecial(3);
            gpStatut->setJauge(false);
        }*/
    }else if (ennemi->isMiniBoss()) {
        if (gpJoueur->getVie()) gpAudio->stopSpecial();
        gpStatut->setJauge(false);
        return;
    }else {
    
        int randomValue = (int)(((float)rand() / RAND_MAX) * 12);
        switch (randomValue){
            case 0: case 1: case 2: case 3: obj=ennemi->getObjets(0); break;
            case 4: case 5: case 6: obj=ennemi->getObjets(1); break;
            case 7: case 8: obj=ennemi->getObjets(2); break;                        
            default:obj=0;break;
        }
        if (
        ((obj == I_RUBIS_VERT || obj == I_RUBIS_BLEU || obj == I_RUBIS_ROUGE) 
            && 
            ((gpJoueur->getRubis()>=gpJoueur->getRubisMax() && getEpoque()==T_PRESENT)
            || (gpJoueur->getGanon()>=gpJoueur->getGanonMax() && getEpoque()==T_FUTUR)
            || (gpJoueur->getPiece()>=gpJoueur->getPieceMax() && getEpoque()==T_PASSE)) 
            )
        || (obj == I_PETIT_COEUR && gpJoueur->getVie() >= gpJoueur->getVieMax())
        || (obj == I_FLECHE && (!gpJoueur->hasObjet(O_ARC)
            || gpJoueur->getFleche() >= gpJoueur->getFlecheMax()))
        || (obj == I_BOMBE && (!gpJoueur->hasObjet(O_SAC_BOMBES) 
            || gpJoueur->getBombe() >= gpJoueur->getBombeMax()))
        || ((obj == I_MAGIE_PEU || obj == I_MAGIE_BCP) 
            && (gpJoueur->getMagie() >= gpJoueur->getMagieMax() 
            || !gpJoueur->hasObjet(O_LANTERNE)))
        ) obj = 0;
    }
    
    //spécial
    if ((zone==46 && gpMonde->regionValue(0)==200*16 && gpMonde->regionValue(1)==0 && gpJoueur->getCoffre(0,21)==0 && ennemi->getEnnId()==1) 
/*    || (zone==20 && gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==45*16 && gpJoueur->getCoffre(5,4)==0 && nbEnnemis()==0)
    || (zone==20 && gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==60*16 && gpJoueur->getCoffre(5,5)==0 && nbEnnemis()==0)
    || (zone==20 && gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==45*16 && gpJoueur->getCoffre(5,6)==0 && nbEnnemis()==0)
    || (zone==20 && gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==45*16 && gpJoueur->getCoffre(5,7)==0 && nbEnnemis()==0)
    || (zone==20 && gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==60*16 && gpJoueur->getCoffre(5,8)==0 && nbEnnemis()==0)
    || (zone==20 && gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==0 && gpJoueur->getCoffre(5,11)==0 && nbEnnemis()==4)
    || (zone==20 && gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==60*16 && gpJoueur->getCoffre(5,12)==0 && nbEnnemis()==4)
    || (zone==20 && gpMonde->regionValue(0)==220*16 && gpMonde->regionValue(1)==0 && gpJoueur->getCoffre(5,13)==0 && nbEnnemis()==4)
    || (zone==20 && gpMonde->regionValue(0)==220*16 && gpMonde->regionValue(1)==60*16 && gpJoueur->getCoffre(5,14)==0 && nbEnnemis()==4)
    || (zone==23 && gpMonde->regionValue(0)==140*16 && gpMonde->regionValue(1)==0 && gpJoueur->getCoffre(8,16)==0 && nbEnnemis()==0)
    || (zone==28 && gpMonde->regionValue(0)==140*16 && gpMonde->regionValue(1)==15*16 && gpJoueur->getCoffre(13,8)==0 && nbEnnemis()==0)*/
    ) obj=I_PETITE_CLE;
    
    /*if (zone==16 && gpMonde->regionValue(0)==140*16 
    && gpMonde->regionValue(1)==30*16 && gpJoueur->getCoffre(9,9)==0) obj=I_PETITE_CLE;*/
    
    if (obj) ajouteObjet(obj, ennemi->getX()+(ennemi->getW()/2)-8, 
        ennemi->getY()+(ennemi->getH()/2)-8);
}

bool Jeu::testDegat(int x, int y, int w, int h, int type, int force, Direction direction, int distance) {
    if ((gpJoueur->getInvincible() && type!=SAOUL) || !gpJoueur->getVie() 
    || (type==COUP_GLACE && gpJoueur->getGel())) return false;
    int degats=0;
    SDL_Rect* z = gpJoueur->getZoneBase()->getZone();
    
    int a = z->x+z->w+gpJoueur->getX();
    int b = z->x+gpJoueur->getX();
    int c = z->y+z->h+gpJoueur->getY();
    int d = z->y+gpJoueur->getY();
    
    for (int i = x; i < x + w; i++)
        for (int j = y; j < y + h; j++)
            if (i >= 0 && j >=0) {
                if (type==FEU) allumeTorche(i, j);
                if (type==MARTEAU) applatitBloc(i, j);
            }
    
    if (gpJoueur->getTypeAnim() == FLOTTE || gpJoueur->getTypeAnim() == NAGE) c-=4;
    
    if (x < a && x + w > b && y < c && y + h > d) {
        
        if (type!=LAPIN && type!=RETOUR && type!=SAOUL) gpAudio->playSound(33);
        
        if (type==ARGENT) {
            gpJoueur->setBoostGanon(-gpJoueur->getCompteur());
            gpJoueur->setCompteur(gpJoueur->getCompteur()+10);
            if (gpJoueur->getGanon() + gpJoueur->getBoostGanon() <= 0) {
                zone = 44; // 44 car futur
                int retX = gpJoueur->getXDep();
                int retY = gpJoueur->getYDep();
                gpAudio->playSound(5);
                gpMonde->transitFull(58, retX, retY, N);
            }
        } else {
            degats=force;
            if (!gpJoueur->getDefense()) degats=degats*2;
            else degats=degats/gpJoueur->getDefense();
            if (type==OMBRE) {
                degats = (gpJoueur->getCompteur()*2);
                if (degats > 40) degats = 40;
                if (degats == 0) {gpJoueur->setCompteur(1); degats=1;}
                else gpJoueur->setCompteur(degats);
                if (gpJoueur->getCompteur() > 20) gpJoueur->setCompteur(20);
            }
            if (type==DEMI) degats=(gpJoueur->getVie()+1)/2;
            if (type==VENIN) degats=gpJoueur->getVie()-1;
            if (force > 0 && degats < 1) degats = 1;
            gpJoueur->setVie(gpJoueur->getVie()-degats);
        }
        if (type==MORTEL) gpJoueur->mortel();
        if (type!=RETOUR && type!=SAOUL) gpJoueur->setTypeAnim(TOUCHE);
        if (type==LAPIN) gpJoueur->setLapin();
        if (type == RETOUR) {
            int retX = gpJoueur->getXDep();
            int retY = gpJoueur->getYDep();
            if (zone==50 && gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==45*16) {
                retX=129*16+8; retY=39*16+8;}
            //else if (zone==23 && gpMonde->regionValue(0)==300*16) {retX=209*16+6; retY=51*16;}
            gpAudio->playSound(5);
            gpMonde->transitFull(zone, retX, retY);
        }
        if (type==SAOUL) gpJoueur->setIvre();
        
        if (type==EXPLOSION) {
            int dfx = (x+(w/2)) - (gpJoueur->getX()+8);
            int dfy = (y+(h/2)) - (gpJoueur->getY()+16);
            if (std::abs(dfx) > std::abs(dfy)) { 
                if (dfx > 0) direction = O; else direction = E;}
            else { if (dfy > 0) direction = N; else direction = S;}
        }
        
        if (type==COUP_GLACE) gpJoueur->geler();
        else gpJoueur->degeler();
        
        if (type!=LAPIN && type!=RETOUR && type!=COUP_GLACE && type!=SAOUL) {
            for (int i = 0; i < distance; i+=2) {
                switch (direction) {
                    case N : gpJoueur->setDirection(S); gpJoueur->moveY(-2,2);break;
                    case S : gpJoueur->setDirection(N); gpJoueur->moveY(2,2);break;
                    case O : gpJoueur->setDirection(E); gpJoueur->moveX(-2,2);break;
                    case E : gpJoueur->setDirection(O); gpJoueur->moveX(2,2);break;
                }
            }
        }
        testFin();
        return true;
    }
    
    return false;
}

bool Jeu::pousse(int i, int j, Direction dir) {
    Caisse* gpCaisse2 = gpCaisse->getSuivant();
    while (gpCaisse2!=NULL) {
        if (i>=gpCaisse2->getX() && i<gpCaisse2->getX()+16 
        && j>=gpCaisse2->getY() && j<gpCaisse2->getY()+16
        && gpCaisse2->getVie()) {
            return gpCaisse2->pousse(dir);
        }
        gpCaisse2=gpCaisse2->getSuivant();
    }
    return false;
}

void Jeu::ouvrePorteDonjon(int x, int y) {
    if (!isDonjon()) return;
    
    //porte boss
    int val = gpMonde->motifValue(x+7,y+8);
    
    if ((val==2813 || val==2814 || val==3013 || val==3014 || val==3185 || val==3186
    || val==3448 || val==3449 || val==3664 || val==3665 || val==5083 || val==5084
    || val==3914 || val==3915 || val==5354 || val==5355 || val==5547 || val==5548
    || val==5736 || val==5737 || val==5982 || val==5983 || val==6098 || val==6099
    || val==6416 || val==6417 || val==6590 || val==6591 || val==6751 || val==6752)
    && gpJoueur->getCle(zone-46, 2)>0) {
        gpJoueur->setCoffre(zone-46, 0);
        gpAudio->playSound(20);
        int x1,y1;
        x1=(int)((x+7)/16); y1=(int)((y+8)/16)-1;
        switch(val) {
            case 2814 : case 3014 : case 3186 : case 3449 : case 3665 : case 5084 : 
            case 3915 : case 5355 : case 5548 : case 5737 : case 5983 : case 6099 :
            case 6417 : case 6591 : case 6752 :
                x1--; break;
        }
        gpMonde->passage(x1,y1,0);
    }
    //porte vérouillée h b
    if ((val==2793 || val==2794 || val==2795 || val==2796
    || val==2993 || val==2994 || val==2995 || val==2996
    || val==3165 || val==3166 || val==3167 || val==3168
    || val==3406 || val==3407 || val==3408 || val==3409
    || val==3644 || val==3645 || val==3646 || val==3647
    || val==5063 || val==5064 || val==5065 || val==5066
    || val==5314 || val==5315 || val==5316 || val==5317
    || val==5507 || val==5508 || val==5509 || val==5510
    || val==5696 || val==5697 || val==5698 || val==5699
    || val==5942 || val==5943 || val==5944 || val==5945
    || val==6182 || val==6183 || val==6184 || val==6185
    || val==6408 || val==6409 || val==6410 || val==6411
    || val==6562 || val==6563 || val==6564 || val==6565)
    && gpJoueur->getCle(zone-46, 3)>0) {
        if (zone==46 && gpMonde->regionValue(0)==80*16) gpJoueur->setCoffre(0,12);
        if (zone==46 && gpMonde->regionValue(0)==120*16) gpJoueur->setCoffre(0,14);
        if (zone==47 && gpMonde->regionValue(0)==140*16) gpJoueur->setCoffre(1,1);
        if (zone==47 && gpMonde->regionValue(0)==180*16) gpJoueur->setCoffre(1,2);
        if (zone==47 && gpMonde->regionValue(0)==200*16) gpJoueur->setCoffre(1,3);
        if (zone==47 && gpMonde->regionValue(0)==320*16) gpJoueur->setCoffre(1,5);
        if (zone==47 && gpMonde->regionValue(0)==120*16) gpJoueur->setCoffre(1,17);
        if (zone==48 && gpMonde->regionValue(0)==100*16) gpJoueur->setCoffre(2,3);
        if (zone==48 && gpMonde->regionValue(0)==160*16) gpJoueur->setCoffre(2,4);
        if (zone==48 && gpMonde->regionValue(0)==220*16) gpJoueur->setCoffre(2,5);
        if (zone==49 && gpMonde->regionValue(0)<=40*16) gpJoueur->setCoffre(3,5);
        if (zone==49 && gpMonde->regionValue(0)==60*16) gpJoueur->setCoffre(3,6);
        if (zone==49 && gpMonde->regionValue(0)==120*16) gpJoueur->setCoffre(3,8);
        if (zone==50 && gpMonde->regionValue(0)==40*16) gpJoueur->setCoffre(4,1);
        if (zone==50 && gpMonde->regionValue(0)==160*16) gpJoueur->setCoffre(4,4);
        if (zone==51 && gpMonde->regionValue(0)==80*16) gpJoueur->setCoffre(5,1);
        if (zone==51 && gpMonde->regionValue(0)==100*16) gpJoueur->setCoffre(5,2);
        if (zone==53) gpJoueur->setCoffre(7,4);
        if (zone==54 && gpMonde->regionValue(0)==140*16) gpJoueur->setCoffre(8,4);
        if (zone==54 && gpMonde->regionValue(0)==160*16) gpJoueur->setCoffre(8,5);
        if (zone==54 && gpMonde->regionValue(0)==180*16 && gpJoueur->getX()<200*16) 
            gpJoueur->setCoffre(8,7);
        if (zone==54 && gpMonde->regionValue(0)==180*16 && gpJoueur->getX()>200*16) 
            gpJoueur->setCoffre(8,8);
        if (zone==55) gpJoueur->setCoffre(9,5);
        if (zone==56 && gpMonde->regionValue(1)==15*16) gpJoueur->setCoffre(10,1);
        if (zone==56 && gpMonde->regionValue(1)==30*16) gpJoueur->setCoffre(10,2);
        if (zone==57) gpJoueur->setCoffre(11,4);
        if (zone==58) gpJoueur->setCoffre(12,7);
        if (zone==59 && gpMonde->regionValue(0)==100*16) gpJoueur->setCoffre(13,3);
        if (zone==59 && gpMonde->regionValue(0)==240*16) gpJoueur->setCoffre(13,4);
        
        gpAudio->playSound(20);
        
        int x1,y1;
        x1=(int)((x+7)/16); y1=(int)((y+8)/16)-1;
        switch(val) {
            case 2794 : case 2994 : case 3166 : case 3407 : case 3645 : case 5064 :
            case 5315 : case 5508 : case 5697 : case 5943 : case 6183 : case 6409 :
            case 6563 :
                x1--; break;
        }
        switch(val) {
            case 2795 : case 2995 : case 3167 : case 3408 : case 3646 : case 5065 :
            case 5316 : case 5509 : case 5698 : case 5944 : case 6184 : case 6410 :
            case 6564 :
                y1=(int)((y+10+8)/16)+2;; break;
            case 2796 : case 2996 : case 3168 : case 3409 : case 3647 : case 5066 :
            case 5317 : case 5510 : case 5699 : case 5945 : case 6185 : case 6411 :
            case 6565 :
                x1--; y1=(int)((y+10+8)/16)+2;; break;
        }
        gpMonde->passage(x1,y1,0);
        gpJoueur->setCle(zone-46, 3, gpJoueur->getCle(zone-46, 3)-1);
    }
    //porte vérouillée g d
    if ((val==2801 || val==2808 || val==3001 || val==3008 || val==3173 || val==3180
    || val==3415 || val==3424 || val==3653 || val==3658 || val==5072 || val==5077
    || val==3883 || val==3888 || val==5323 || val==5328 || val==5516 || val==5521
    || val==5705 || val==5710 || val==5951 || val==5956 || val==6471 || val==6476
    || val==6720 || val==6725)
    && gpJoueur->getCle(zone-46, 3)>0) {
        
        if (zone==46 && gpMonde->regionValue(0)==80*16) gpJoueur->setCoffre(0,13);
        if (zone==46 && gpMonde->regionValue(0)==200*16) gpJoueur->setCoffre(0,15);
        if (zone==46 && gpMonde->regionValue(0)==280*16) gpJoueur->setCoffre(0,16);
        if (zone==47 && gpMonde->regionValue(0)==260*16) gpJoueur->setCoffre(1,4);
        if (zone==48 && gpJoueur->getX()<70*16) gpJoueur->setCoffre(2,1);
        if (zone==48 && gpJoueur->getX()>=70*16 && gpMonde->regionValue(0)==60*16) 
            gpJoueur->setCoffre(2,2);
        if (zone==48 && gpMonde->regionValue(0)==240*16) gpJoueur->setCoffre(2,6);
        if (zone==49) gpJoueur->setCoffre(3,7);
        if (zone==50 && gpMonde->regionValue(1)==30*16) gpJoueur->setCoffre(4,2);
        if (zone==50 && gpMonde->regionValue(1)==75*16) gpJoueur->setCoffre(4,3);
        if (zone==51) gpJoueur->setCoffre(5,3);
        if (zone==52 && gpMonde->regionValue(1)==45*16) gpJoueur->setCoffre(6,1);
        if (zone==52 && gpMonde->regionValue(1)==60*16 && gpJoueur->getX()<130*16) 
            gpJoueur->setCoffre(6,2);
        if (zone==52 && gpMonde->regionValue(1)==60*16 && gpJoueur->getX()>=130*16) 
            gpJoueur->setCoffre(6,3);
        if (zone==52 && gpMonde->regionValue(1)==0) gpJoueur->setCoffre(6,4);
        if (zone==53 && gpMonde->regionValue(1)==45*16) gpJoueur->setCoffre(7,1);
        if (zone==53 && gpMonde->regionValue(0)==100*16) gpJoueur->setCoffre(7,2);
        if (zone==53 && gpMonde->regionValue(0)==140*16) gpJoueur->setCoffre(7,3);
        if (zone==54 && gpMonde->regionValue(0)==20*16) gpJoueur->setCoffre(8,1);
        if (zone==54 && gpMonde->regionValue(0)==40*16 
        && gpMonde->regionValue(1)==45*16) gpJoueur->setCoffre(8,2);
        if (zone==54 && gpMonde->regionValue(0)==40*16 
        && gpMonde->regionValue(1)==0) gpJoueur->setCoffre(8,3);
        if (zone==54 && gpMonde->regionValue(0)==180*16 && gpJoueur->getX()<200*16) 
            gpJoueur->setCoffre(8,6);
        if (zone==54 && gpMonde->regionValue(0)==180*16 && gpJoueur->getX()>200*16) 
            gpJoueur->setCoffre(8,9);
        if (zone==55 && gpMonde->regionValue(1)==105*16) gpJoueur->setCoffre(9,6);
        if (zone==55 && gpMonde->regionValue(1)==150*16) gpJoueur->setCoffre(9,7);
        if (zone==55 && gpMonde->regionValue(1)==75*16) gpJoueur->setCoffre(9,8);
        if (zone==56) gpJoueur->setCoffre(10,3);
        if (zone==58 && gpMonde->regionValue(0)==40*16) gpJoueur->setCoffre(12,6);
        if (zone==58 && gpMonde->regionValue(0)==80*16) gpJoueur->setCoffre(12,8);
        if (zone==58 && gpMonde->regionValue(0)==100*16) gpJoueur->setCoffre(12,9);
        if (zone==58 && gpMonde->regionValue(0)==120*16) gpJoueur->setCoffre(12,10);
        if (zone==60) gpJoueur->setCoffre(14,2);
        
        gpAudio->playSound(20);
        int x1,y1;
        x1=(int)((x+7)/16)-1; y1=(int)((y+8)/16)-1;
        switch(val) {
            case 2801 : case 3001 : case 3173 : case 3424 : case 3658 : case 5077 : 
            case 3888 : case 5328 : case 5521 : case 5710 : case 5956 : case 6476 :
            case 6725 :
                x1=(int)((x+7+10)/16)+2; break;
        }
        gpMonde->passage(x1,y1,1);
        gpJoueur->setCle(zone-46, 3, gpJoueur->getCle(zone-46, 3)-1);
    }
}

void Jeu::ouvrePorteMaison(int x, int y) {
    if (zone == 57 && !gpJoueur->getCle(11, 3)) return;
    if (zone == 155 && gpJoueur->getAvancement()<CLE_PRISON_F_TROUVEE) return;
    int val = gpMonde->motifValue(x,y);
    x=x/16; y=y/16;
    if (val==610 || val==611 || val==705 || val==706 || val==1054 || val==1055 
    || val==4220 || val==4221 || val==4328 || val==4329 || val==4585 || val==4586
    || val==1818 || val==1819 || val==4769 || val==6249) {
        gpAudio->playSound(20);
        switch (val) {
            case 610 :
                gpMonde->setMap(x,y,602);//setValeur(x, y, 602, -1, LIBRE, 0);
                gpMonde->setMap(x+1,y,603);//gpMonde->setValeur(x+16, y, 603, -1, LIBRE, 0);
                break;
            case 611 :
                gpMonde->setMap(x-1,y,602);//gpMonde->setValeur(x-16, y, 602, -1, LIBRE, 0);
                gpMonde->setMap(x,y,603);//gpMonde->setValeur(x, y, 603, -1, LIBRE, 0);
                break;
            case 705 :
                gpMonde->setMap(x,y,711);//gpMonde->setValeur(x, y, 711, -1, LIBRE, 0);
                gpMonde->setMap(x+1,y,712);//gpMonde->setValeur(x+16, y, 712, -1, LIBRE, 0);
                break;
            case 706 :
                gpMonde->setMap(x-1,y,711);//gpMonde->setValeur(x-16, y, 711, -1, LIBRE, 0);
                gpMonde->setMap(x,y,712);//gpMonde->setValeur(x, y, 712, -1, LIBRE, 0);
                break;
            case 1054 :
                gpMonde->setMap(x,y,1066); gpMonde->setMap(x+1,y,1066);
                break;
            case 1055 :
                gpMonde->setMap(x-1,y,1066); gpMonde->setMap(x,y,1066);
                break;
            case 1818 :
                gpMonde->setMap(x,y,1817); gpMonde->setMap(x+1,y,1817);
                break;
            case 1819 :
                gpMonde->setMap(x-1,y,1817); gpMonde->setMap(x,y,1817);
                break;
            case 4220 :
                gpMonde->setMap(x,y-1,4225);
                gpMonde->setMap(x+1,y-1,4226);
                gpMonde->setMap(x,y,4227);
                gpMonde->setMap(x+1,y,4228);
                break;
            case 4221 :
                gpMonde->setMap(x-1,y-1,4225);
                gpMonde->setMap(x,y-1,4226);
                gpMonde->setMap(x-1,y,4227);
                gpMonde->setMap(x,y,4228);
                break;
            case 4328 :
                gpMonde->setMap(x,y-1,4333);
                gpMonde->setMap(x+1,y-1,4334);
                gpMonde->setMap(x,y,4335);
                gpMonde->setMap(x+1,y,4336);
                break;
            case 4329 :
                gpMonde->setMap(x-1,y-1,4333);
                gpMonde->setMap(x,y-1,4334);
                gpMonde->setMap(x-1,y,4335);
                gpMonde->setMap(x,y,4336);
                break;
            case 4585 :
                gpMonde->setMap(x,y-1,4590);
                gpMonde->setMap(x+1,y-1,4591);
                gpMonde->setMap(x,y,4592);
                gpMonde->setMap(x+1,y,4593);
                break;
            case 4586 :
                gpMonde->setMap(x-1,y-1,4590);
                gpMonde->setMap(x,y-1,4591);
                gpMonde->setMap(x-1,y,4592);
                gpMonde->setMap(x,y,4593);
                break;
            case 4769 :
                gpMonde->setValeur(x*16,y*16,4680,0);
                if (gpJoueur->getAvancement()<BOWSER_AIDE)
                    gpJoueur->setAvancement(BOWSER_AIDE);
                break;
            case 6249 :
                if (zone != 57) break;
                if (gpMonde->regionValue(0)==0) gpJoueur->setCoffre(11,5);
                if (gpMonde->regionValue(0)==60*16) gpJoueur->setCoffre(11,6);
                gpJoueur->setCle(11, 3, gpJoueur->getCle(11, 3)-1);
                gpMonde->setValeur(x*16,y*16,6137,0);
                break;
        }
    }
}

void Jeu::monteBarque(int x, int y) {
    if (!gpJoueur->getVie() || !gpJoueur->hasObjet(O_BARQUE)
    || gpJoueur->getTypeAnim()==TOUCHE || gpJoueur->getTypeAnim()==MORT) return;
    if (gpMonde->motifValue(x,y+8)==1652) {
        int ind;
        switch (x/16) {
            case 118 : ind = 0; break;
            case 105 : ind = 1; break;
            case 76 : ind = 2; break;
            case 50 : ind = 3; break;
            case 32 : ind = 4; break;
            case 13 : ind = 5; break;
            default : ind = 0; break;
        }
        gpJoueur->setDirection(S);
        gpJoueur->setTypeAnim(BARQUE);
        gpMonde->barque(ind, false);
    }
}

void Jeu::descendBarque(int x, int y) {
    if (gpJoueur->getTypeAnim()!=BARQUE && gpJoueur->getTypeAnim()!=RAME) return;
    if (gpMonde->motifValue(x,y+8)==540) {
        int ind;
        switch (x/16) {
            case 118 : ind = 0; break;
            case 105 : ind = 1; break;
            case 76 : ind = 2; break;
            case 50 : ind = 3; break;
            case 32 : ind = 4; break;
            case 13 : ind = 5; break;
            default : ind = 0; break;
        }
        gpJoueur->setPosBarque(ind);
        //gpJoueur->setDirection(S);
        gpJoueur->setTypeAnim(AUCUNE);
        gpMonde->barque(ind, true);
    }
}

void Jeu::monteWagon(int x, int y) {
    if (!gpJoueur->getVie() || gpJoueur->getTypeAnim()==TOUCHE 
    || gpJoueur->getTypeAnim()==MORT) return;
    if (gpMonde->motifValue(x+8,y+8)==2348 || gpMonde->motifValue(x+8,y+16)==2348 
    || gpMonde->motifValue(x+8,y+24)==2348) {
        int ind;
        switch ((x+8)/16) {
            case 28 : 
                if (gpJoueur->getPosWagon()!=0) return;
                gpJoueur->setDirection(E);
                gpJoueur->setX(29*16+4);
                gpJoueur->setY(22*16+8);
                ind = 0;  break;
            case 51 : 
                if (gpJoueur->getPosWagon()!=1) return;
                gpJoueur->setDirection(E);
                gpJoueur->setX(50*16-4);
                gpJoueur->setY(21*16+8);
                ind = 1; break;
            case 29 : 
                if (gpJoueur->getPosWagon()!=2) return;
                gpJoueur->setDirection(E);
                gpJoueur->setX(30*16+4);
                gpJoueur->setY(4*16+8);
                ind = 2; break;
            default : ind = 0; break;
        }
        gpJoueur->setImmo(true);
        //gpJoueur->setDirection(S);
        gpJoueur->setTypeAnim(WAGON);
        gpMonde->wagon(ind, false);
    }
}

void Jeu::descendWagon() {
    if (gpJoueur->getTypeAnim()!=WAGON) return;
    int ind;
    switch (gpJoueur->getPosWagon()) {
        case 1 :
            gpJoueur->setDirection(E);
            gpJoueur->setX(52*16);
            gpJoueur->setY(21*16+8);
            break;
        case 0 : 
            gpJoueur->setDirection(O);
            gpJoueur->setX(27*16);
            gpJoueur->setY(22*16+8);
            break;
        case 2 : 
            gpJoueur->setDirection(O);
            gpJoueur->setX(28*16);
            gpJoueur->setY(4*16+8);
            break;
        default : ind = 0; break;
    }
    gpJoueur->setImmo(false);
    gpJoueur->setTypeAnim(AUCUNE);
    gpMonde->wagon(gpJoueur->getPosWagon(), true);
}

bool Jeu::isDangereux(int x, int y) {
    if (gpJoueur->getInvincible() || !gpJoueur->getVie()) return false;
    
    //barrière magique
    if ((gpMonde->motifAirValue(x+2,y+8-8)>=2001 && gpMonde->motifAirValue(x+2,y+8-8)<=2004) ||
    (gpMonde->motifAirValue(x+10,y+8-8)>=2001 && gpMonde->motifAirValue(x+10,y+8-8)<=2004) ||
    (gpMonde->motifAirValue(x+17,y+8-8)>=2001 && gpMonde->motifAirValue(x+17,y+8-8)<=2004) ||
    (gpMonde->motifAirValue(x+2,y+8)>=2001 && gpMonde->motifAirValue(x+2,y+8)<=2004) ||
    (gpMonde->motifAirValue(x+10,y+8)>=2001 && gpMonde->motifAirValue(x+10,y+8)<=2004) ||
    (gpMonde->motifAirValue(x+17,y+8)>=2001 && gpMonde->motifAirValue(x+17,y+8)<=2004)) {
        
        gpAudio->playSound(33);
        int degats=4;
        if (!gpJoueur->getDefense()) degats=degats*2;
        else degats=degats/gpJoueur->getDefense();
        if (degats < 1) degats = 1;
        gpJoueur->setVie(gpJoueur->getVie()-degats);
        gpJoueur->setTypeAnim(TOUCHE);
        gpJoueur->setInvincible(0);
        for (int i = 0; i < 16; i+=2) {
            gpJoueur->setDirection(N); gpJoueur->moveY(2,2);
        }
        testFin();
        return true;
    }
    
    //motif dangereux
    if (gpMonde->motifValue(x,y)==830 || gpMonde->motifValue(x+15,y)==830
    || gpMonde->motifValue(x,y+15)==830 || gpMonde->motifValue(x+15,y+15)==830
    || gpMonde->motifValue(x,y)==1761 || gpMonde->motifValue(x+15,y)==1761
    || gpMonde->motifValue(x,y+15)==1761 || gpMonde->motifValue(x+15,y+15)==1761
    || gpMonde->motifValue(x,y)==1519 || gpMonde->motifValue(x+15,y)==1519
    || gpMonde->motifValue(x,y+15)==1519 || gpMonde->motifValue(x+15,y+15)==1519
    || gpMonde->motifValue(x,y)==1006 || gpMonde->motifValue(x+15,y)==1006
    || gpMonde->motifValue(x,y+15)==1006 || gpMonde->motifValue(x+15,y+15)==1006) {
    
        gpAudio->playSound(33);
        int degats=2;
        if (!gpJoueur->getDefense()) degats=degats*2;
        else degats=degats/gpJoueur->getDefense();
        if (degats < 1) degats = 1;
        gpJoueur->setVie(gpJoueur->getVie()-degats);
        gpJoueur->setTypeAnim(TOUCHE);
        
        for (int i = 0; i < 16; i+=2) {
            switch (gpJoueur->getDirection()) {
                case S : gpJoueur->setDirection(S); gpJoueur->moveY(-2,2);break;
                case N : gpJoueur->setDirection(N); gpJoueur->moveY(2,2);break;
                case E : gpJoueur->setDirection(E); gpJoueur->moveX(-2,2);break;
                case O : gpJoueur->setDirection(O); gpJoueur->moveX(2,2);break;
            }
        }
        testFin();
        return true;
    }
    
    return false;
}

void Jeu::testInterrupteur(int x, int y) {
    if (gpMonde->motifValue(x,y)==1004) {
        gpMonde->setValeur(x, y, 1005, -1, LIBRE, 0);
        switch (zone) {
            case 46 :
                //mini boss
                if (gpMonde->regionValue(0)==0) {
                    int randomP = (int)((float)rand() / RAND_MAX * (3));
                    switch (randomP) {                        
                        case 0: gpMonde->setValeur(4*16,32*16,30,PLEIN); break;
                        case 1: gpMonde->setValeur(15*16,32*16,30,PLEIN); break;
                        default : gpMonde->setValeur(15*16,42*16,30,PLEIN); break;
                    }
                    gpAudio->playSound(35);
                    break;
                }
                //boss
                if (gpMonde->regionValue(0)==340*16) {
                    int randomP = (int)((float)rand() / RAND_MAX * (6));
                    gpMonde->setValeur((342+randomP*3)*16,7*16,30,PLEIN);
                    gpAudio->playSound(35);
                    break;
                }
                gpAudio->playSound(20);
                if (gpMonde->regionValue(0)==160*16) {gpMonde->passage(169,30,0); gpJoueur->setCoffre(0,1);}
                if (gpMonde->regionValue(0)==180*16) {gpMonde->passage(209,45,0); gpJoueur->setCoffre(0,2);}
                if (gpMonde->regionValue(0)==300*16 && gpMonde->regionValue(1)==30*16){ gpMonde->passage(300,36,1); gpJoueur->setCoffre(0,3);}
                if (gpMonde->regionValue(0)==300*16 && gpMonde->regionValue(1)==15*16){ gpMonde->passage(300,21,1); gpJoueur->setCoffre(0,4);}
                if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==30*16
                && gpJoueur->getY()<37*16){ gpMonde->passage(29,30,0); gpJoueur->setCoffre(0,5);}
                if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==30*16
                && gpJoueur->getY()>=37*16){ gpMonde->passage(29,45,0); gpJoueur->setCoffre(0,6);}
                if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==30*16){ gpMonde->passage(69,45,0); gpJoueur->setCoffre(0,7);}
                if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==0){ gpMonde->passage(69,15,0); gpJoueur->setCoffre(0,8);}
                if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==15*16
                && gpJoueur->getY()<30*16){ gpMonde->passage(100,21,1); gpJoueur->setCoffre(0,9);}
                if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==15*16
                && gpJoueur->getY()>=30*16){ gpMonde->passage(109,45,0); gpJoueur->setCoffre(0,10);}
                if (gpMonde->regionValue(0)==120*16) {gpMonde->passage(140,6,1); gpJoueur->setCoffre(0,11);}
                break;
            case 47 :
                gpAudio->playSound(20);
                if (gpMonde->regionValue(0)==240*16) {gpMonde->passage(260,51,1); gpJoueur->setCoffre(1,6); gpMonde->setContenu(257,49,51);}
                if (gpMonde->regionValue(0)==260*16) {gpMonde->passage(289,30,0); gpJoueur->setCoffre(1,7);}
                if (gpMonde->regionValue(0)==280*16) {gpMonde->passage(320,36,1); gpJoueur->setCoffre(1,8);}
                if (gpMonde->regionValue(0)==320*16) {gpMonde->passage(340,66,1); gpJoueur->setCoffre(1,9);}
                break;
            case 48 :
                if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==30*16) {
                    if (gpMonde->motifValue(126*16,42*16)==1005 
                    && gpMonde->motifValue(133*16,42*16)==1005) {
                        gpMonde->setValeur(124*16,33*16,1004);
                        gpMonde->setValeur(129*16,33*16,1004);
                        gpMonde->setValeur(135*16,33*16,1004);
                    }
                    Ennemi* enn;
                    enn = gpEnnemi->getSuivant();
                    while (enn != NULL) {
                        if (enn->getEnnId()==96 && enn->getY()==39*16
                        && ((enn->getX()==124*16 && x<129*16) 
                        || (enn->getX()==135*16 && x>=129*16))) {
                            enn->snipeImp();
                            break;
                        }
                        enn = enn->getSuivant();
                    }
                    break;
                }
                gpAudio->playSound(20);
                if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==0) {
                    gpMonde->passage(189,15,0); gpJoueur->setCoffre(2,20);}
                if (gpMonde->regionValue(0)==40*16) {gpMonde->passage(60,6,1); gpJoueur->setCoffre(2,21);}
                if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==0) {
                    gpMonde->passage(69,15,0); gpJoueur->setCoffre(2,22);
                    gpMonde->setValeur(68*16, 17*16, 1001, PLEIN);
                    gpMonde->setValeur(71*16, 17*16, 1001, PLEIN);
                }
                if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==45*16) {
                    gpMonde->passage(69,60,0); gpJoueur->setCoffre(2,23);}
                if (gpMonde->regionValue(0)==80*16) {gpMonde->passage(89,15,0); gpJoueur->setCoffre(2,24);}
                if (gpMonde->regionValue(0)==100*16) {gpMonde->passage(109,60,0); gpJoueur->setCoffre(2,25);}
                if (gpMonde->regionValue(0)==140*16) {gpMonde->passage(149,60,0); gpJoueur->setCoffre(2,26);}
                if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==15*16
                && gpJoueur->getY()<30*16) {gpMonde->passage(180,21,1); gpJoueur->setCoffre(2,27);}
                if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==15*16
                && gpJoueur->getX()<200*16 && gpJoueur->getY()>45*16) {
                    gpMonde->passage(180,51,1); gpJoueur->setCoffre(2,28);}
                if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==15*16
                && gpJoueur->getX()>200*16 && gpJoueur->getY()>45*16) {
                    gpMonde->passage(209,60,0); gpJoueur->setCoffre(2,29);}
                if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==15*16
                && gpJoueur->getX()>220*16) {gpMonde->passage(240,36,1); gpJoueur->setCoffre(2,30);}
                break;
            case 49 :
                gpAudio->playSound(20);
                if (gpMonde->regionValue(0)==20*16) {gpMonde->passage(29,30,0); gpJoueur->setCoffre(3,9);}
                if (gpMonde->regionValue(0)==60*16 && gpJoueur->getY()>=45*16) {gpMonde->passage(60,51,1); gpJoueur->setCoffre(3,10);}
                if (gpMonde->regionValue(0)==80*16) {gpMonde->passage(100,66,1); gpJoueur->setCoffre(3,13);}
                if (gpMonde->regionValue(0)==60*16 && gpJoueur->getY()<45*16) {gpMonde->passage(89,30,0); gpJoueur->setCoffre(3,14);}
                if (gpMonde->regionValue(0)==140*16 && gpMonde->regionValue(1)==45*16) {gpMonde->passage(149,75,0); gpJoueur->setCoffre(3,15);}
                if (gpMonde->regionValue(0)==140*16 && gpMonde->regionValue(1)==75*16) {gpMonde->passage(160,81,1); gpJoueur->setCoffre(3,16);}
                if (gpMonde->regionValue(0)==160*16) {gpMonde->passage(160,6,1); gpJoueur->setCoffre(3,17);}
                if (gpMonde->regionValue(0)==220*16) {gpMonde->passage(229,75,0); gpJoueur->setCoffre(3,18);}
                break;
            case 50 :
                if (gpMonde->regionValue(0)==80*16) {
                    gpAudio->playSound(9);
                    if(!gpJoueur->getCoffre(4,6)) 
                        gpMonde->setValeur(84*16,49*16,303,-1,PLEIN,C_CLE);
                    else gpMonde->setValeur(84*16,49*16,304,-1,PLEIN,C_RIEN);
                    gpJoueur->setCoffre(4,24);
                    break;
                }
                gpAudio->playSound(20);
                if (gpMonde->regionValue(0)==40*16) {gpMonde->passage(60,66,1); gpJoueur->setCoffre(4,13);}
                if (gpMonde->regionValue(0)==120*16) {gpMonde->passage(129,30,0); gpJoueur->setCoffre(4,14);}
                if (gpMonde->regionValue(0)==140*16) {gpMonde->passage(160,66,1); gpJoueur->setCoffre(4,15);}
                if (gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==75*16) {gpMonde->passage(160,81,1); gpJoueur->setCoffre(4,16);}
                if (gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==30*16) {gpMonde->passage(169,30,0); gpJoueur->setCoffre(4,17);}
                if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==60*16) {gpMonde->passage(189,75,0); gpJoueur->setCoffre(4,18);}
                if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==75*16) {gpMonde->passage(209,75,0); gpJoueur->setCoffre(4,19);}
                if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==75*16) {gpMonde->passage(249,75,0); gpJoueur->setCoffre(4,20);}
                if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==30*16) {gpMonde->passage(260,36,1); gpJoueur->setCoffre(4,21);}
                if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==90*16) {gpMonde->passage(249,90,0); gpJoueur->setCoffre(4,22);}
                if (gpMonde->regionValue(0)==280*16) {gpMonde->passage(289,60,0); gpJoueur->setCoffre(4,23);}
                break;
            case 51 :
                if (gpMonde->regionValue(0)==230*16 && gpMonde->regionValue(1)==15*16) {
                    if (gpMonde->motifValue(240*16,23*16)==1005 
                    && gpMonde->motifValue(240*16,40*16)==1005
                    && gpMonde->motifValue(259*16,23*16)==1005 
                    && gpMonde->motifValue(259*16,40*16)==1005) {
                        int inter = ((x/16)-240)/19 + 2*(((y/16)-23)/17);
                        int active = rand()%3;
                        if (active >= inter) active++;
                        gpMonde->setValeur((240+19*(active%2))*16,(23+17*(active/2))*16,1004);
                    }
                    int statue = rand()%4; int actuelle=0;
                    Ennemi* enn;
                    enn = gpEnnemi->getSuivant();
                    while (enn != NULL) {
                        if (enn->getEnnId()==96 && enn->getVie()>0) {
                            if (statue == actuelle) {
                                enn->snipe();
                                break;
                            }
                            actuelle++;
                        }
                        enn = enn->getSuivant();
                    }
                    break;
                }
                gpAudio->playSound(20);
                if (gpMonde->regionValue(0)==20*16) {gpMonde->passage(40,66,1); gpJoueur->setCoffre(5,8);}
                if (gpMonde->regionValue(0)==60*16) {gpMonde->passage(69,60,0); gpJoueur->setCoffre(5,9);}
                if (gpMonde->regionValue(0)==80*16) {gpMonde->passage(100,66,1); gpJoueur->setCoffre(5,10);}
                if (gpMonde->regionValue(0)==100*16) {gpMonde->passage(109,30,0); gpJoueur->setCoffre(5,11);}
                if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==45*16) {gpMonde->passage(129,60,0); gpJoueur->setCoffre(5,12);}
                if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==75*16) {gpMonde->passage(129,75,0); gpJoueur->setCoffre(5,13);}
                if (gpMonde->regionValue(0)==140*16) {gpMonde->passage(140,66,1); gpJoueur->setCoffre(5,14);}
                if (gpMonde->regionValue(0)==200*16 && gpMonde->regionValue(1)==45*16 && y < 54*16) {gpMonde->passage(200,51,1); gpJoueur->setCoffre(5,15);}
                if (gpMonde->regionValue(0)==200*16 && gpMonde->regionValue(1)==45*16 && y > 54*16) {
                    gpMonde->passage(209,60,0); gpJoueur->setCoffre(5,16); gpMonde->setContenu(217,57,51);}
                if (gpMonde->regionValue(0)==220*16) {gpMonde->passage(229,75,0); gpJoueur->setCoffre(5,17);}
                if (gpMonde->regionValue(0)==240*16) {gpMonde->passage(249,90,0); gpJoueur->setCoffre(5,18);}
                if (gpMonde->regionValue(0)==260*16) {gpMonde->passage(269,60,0); gpJoueur->setCoffre(5,19);}
                if (gpMonde->regionValue(0)==280*16 && gpMonde->regionValue(1)==0) {gpMonde->passage(289,30,0); gpJoueur->setCoffre(5,20);}
                if (gpMonde->regionValue(0)==280*16 && gpMonde->regionValue(1)==45*16) {
                    gpMonde->passage(289,60,0); gpJoueur->setCoffre(5,21); gpMonde->setContenu(285,57,51);}
                if (gpMonde->regionValue(0)==300*16) {gpMonde->passage(300,66,1); gpJoueur->setCoffre(5,22);}
                break;
            case 52 :
                gpAudio->playSound(20);
                if (gpMonde->regionValue(0)==20*16) {gpMonde->passage(40,66,1); gpJoueur->setCoffre(6,9);}
                if (gpMonde->regionValue(0)==40*16) {gpMonde->passage(49,60,0); gpJoueur->setCoffre(6,10);}
                if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==60*16) {gpMonde->passage(60,66,1); gpJoueur->setCoffre(6,11);}
                if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==30*16) {gpMonde->passage(69,45,0); gpJoueur->setCoffre(6,12);}
                if (gpMonde->regionValue(0)==100*16) {gpMonde->passage(120,21,1); gpJoueur->setCoffre(6,13);}
                if (gpMonde->regionValue(0)==140*16) {gpMonde->passage(140,21,1); gpJoueur->setCoffre(6,14);}
                if (gpMonde->regionValue(0)==120*16) {gpMonde->passage(129,30,0); gpJoueur->setCoffre(6,15);}
                if (gpMonde->regionValue(0)==160*16) {gpMonde->passage(169,45,0); gpJoueur->setCoffre(6,17);}
                if (gpMonde->regionValue(0)==200*16) {gpMonde->passage(200,36,1); gpJoueur->setCoffre(6,18);}
                break;
            case 53 :
                gpAudio->playSound(20);
                if (gpMonde->regionValue(0)==0) {gpMonde->passage(9,30,0); gpJoueur->setCoffre(7,9);}
                if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==0) {
                    gpMonde->passage(29,15,0); gpJoueur->setCoffre(7,10);}
                if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==15*16 && x < 40*16) {
                    gpMonde->passage(29,45,0); gpJoueur->setCoffre(7,11);}
                if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==15*16 && x >= 40*16) {
                    gpMonde->passage(60,36,1); gpJoueur->setCoffre(7,12);}
                if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==15*16) {
                    gpMonde->passage(69,30,0); gpJoueur->setCoffre(7,13);}
                if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==90*16) {
                    gpMonde->passage(69,105,0); gpJoueur->setCoffre(7,14);}
                if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==0) {
                    gpMonde->passage(100,6,1); gpJoueur->setCoffre(7,15);}
                if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==60*16) {
                    gpMonde->passage(89,75,0); gpJoueur->setCoffre(7,16);}
                if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==75*16 && x < 120*16) {
                    gpMonde->passage(109,75,0); gpJoueur->setCoffre(7,17);}
                if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==45*16) {
                    gpMonde->passage(129,45,0); gpJoueur->setCoffre(7,18);}
                if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==75*16 && x >= 120*16) {
                    gpMonde->passage(129,105,0); gpJoueur->setCoffre(7,19);}
                if (gpMonde->regionValue(0)==180*16) {gpMonde->passage(200,51,1); gpJoueur->setCoffre(7,20);}
                break;
            case 54 :
                gpAudio->playSound(20);
                if (gpMonde->regionValue(0)==20*16) {gpMonde->passage(29,15,0); gpJoueur->setCoffre(8,19);}
                if (gpMonde->regionValue(0)==60*16) {gpMonde->passage(69,75,0); gpJoueur->setCoffre(8,20);}
                if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==0) {
                    gpMonde->passage(120,6,1); gpJoueur->setCoffre(8,22);}
                if (gpMonde->regionValue(0)==120*16) {gpMonde->passage(120,51,1); gpJoueur->setCoffre(8,36);}
                if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==45*16) {
                    gpMonde->passage(109,45,0); gpJoueur->setCoffre(8,37);}
                if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==15*16) {
                    gpMonde->passage(109,30,0); gpJoueur->setCoffre(8,38);}
                if (gpMonde->regionValue(0)==140*16) {gpMonde->passage(160,51,1); gpJoueur->setCoffre(8,39);}
                if (gpMonde->regionValue(0)==160*16) {gpMonde->passage(169,30,0); gpJoueur->setCoffre(8,40);}
                if (gpMonde->regionValue(0)==180*16) {gpMonde->passage(180,81,1); gpJoueur->setCoffre(8,43);}
                if (gpMonde->regionValue(0)==220*16 && gpMonde->regionValue(1)==30*16) {
                    gpMonde->passage(220,36,1); gpJoueur->setCoffre(8,46);}
                if (gpMonde->regionValue(0)==220*16 && gpMonde->regionValue(1)==60*16) {
                    gpMonde->passage(229,75,0); gpJoueur->setCoffre(8,48);}
                if (gpMonde->regionValue(0)==220*16 && gpMonde->regionValue(1)==75*16) {
                    gpMonde->passage(240,81,1); gpJoueur->setCoffre(8,49);}
                if (gpMonde->regionValue(0)==240*16) {gpMonde->passage(249,60,0); gpJoueur->setCoffre(8,50);}
                break;
            case 55 :
                gpAudio->playSound(20);
                if (gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==135*16) {
                    gpMonde->passage(20,141,1); gpJoueur->setCoffre(9,9);}
                if (gpMonde->regionValue(1)==0) {gpMonde->passage(29,30,0); gpJoueur->setCoffre(9,10);}
                if (gpMonde->regionValue(0)==40*16) {gpMonde->passage(60,216,1); gpJoueur->setCoffre(9,14);}
                if (gpMonde->regionValue(0)==80*16) {gpMonde->passage(80,216,1); gpJoueur->setCoffre(9,17);}
                if (gpMonde->regionValue(1)==30*16) {gpMonde->passage(129,30,0); gpJoueur->setCoffre(9,21);}
                if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==135*16) {
                    gpMonde->passage(120,141,1); gpJoueur->setCoffre(9,22);}
                break;
            case 56 :
                if (gpMonde->regionValue(1)==90*16) {
                    gpAudio->playSound(28);
                    gpJoueur->setCoffre(10,12);
                    Ennemi* enn = gpEnnemi->getSuivant();
                    while (enn != NULL) {
                        if (enn->getEnnId() == 119) {
                            enn->revie();
                            enn->replace();
                            gpMonde->passage(enn->getX(),enn->getY(),9);
                        }
                        enn = enn->getSuivant();
                    }
                    break;
                }
                gpAudio->playSound(20);
                if (gpMonde->regionValue(1)==15*16) {gpMonde->passage(40,21,1); gpJoueur->setCoffre(10,7);}
                if (gpMonde->regionValue(1)==30*16) {gpMonde->passage(49,30,0); gpJoueur->setCoffre(10,9);}
                if (gpMonde->regionValue(1)==0) {gpMonde->passage(120,6,1); gpJoueur->setCoffre(10,10);}
                break;
            case 58 :
                gpAudio->playSound(20);
                if (gpMonde->regionValue(0)==0) {gpMonde->passage(20,36,1); gpJoueur->setCoffre(12,11);}
                if (gpMonde->regionValue(0)==120*16) {gpMonde->passage(129,45,0); gpJoueur->setCoffre(12,12);}
                break;
            case 59 :
                gpAudio->playSound(20);
                if (gpMonde->regionValue(0)==0) {gpMonde->passage(9,15,0); gpJoueur->setCoffre(13,5);}
                if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==0) {
                    gpMonde->passage(20,6,1); gpJoueur->setCoffre(13,6);}
                if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==15*16) {
                    gpMonde->passage(29,45,0); gpJoueur->setCoffre(13,7);}
                if (gpMonde->regionValue(0)==40*16 && gpMonde->regionValue(1)==45*16) {
                    gpMonde->passage(40,51,1); gpJoueur->setCoffre(13,9);}
                if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==0) {
                    gpMonde->passage(69,15,0); gpJoueur->setCoffre(13,10);}
                if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==15*16) {
                    gpMonde->passage(69,45,0); gpJoueur->setCoffre(13,11);}
                if (gpMonde->regionValue(0)==80*16) {gpMonde->passage(100,51,1); gpJoueur->setCoffre(13,12);}
                break;
            case 60 :
                gpAudio->playSound(20);
                if (gpMonde->regionValue(0)==0) {gpMonde->passage(9,60,0); gpJoueur->setCoffre(14,3);}
                if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==60*16) {
                    gpMonde->passage(29,60,0); gpJoueur->setCoffre(14,4);}
                if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==15*16) {
                    gpMonde->passage(60,36,1); gpJoueur->setCoffre(14,5);}
                if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==105*16) {
                    gpMonde->passage(49,135,0); gpJoueur->setCoffre(14,6);}
                if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==60*16) {
                    gpMonde->passage(129,60,0); gpJoueur->setCoffre(14,7);}
                if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==90*16) {
                    gpMonde->passage(129,105,0); gpJoueur->setCoffre(14,8);}
                if (gpMonde->regionValue(0)==40*16 && gpMonde->regionValue(1)==45*16) {
                    gpMonde->passage(49,45,0); gpJoueur->setCoffre(14,16);}
                break;
            case 63 :
                gpAudio->playSound(20);
                gpMonde->passage(80,6,1); gpJoueur->setCoffre(15,6); break;
            case 67 :
                gpAudio->playSound(20);
                gpMonde->passage(60,21,1); gpJoueur->setCoffre(15,10); break;
            case 68 :
                gpAudio->playSound(20);
                gpMonde->passage(9,15,0); gpJoueur->setCoffre(15,11); break;
            case 119 :
                gpAudio->playSound(31); gpMonde->animCafe(); break;
        }
    }
}

void Jeu::testInterrupteurEtoile(int x, int y) {
    if (gpMonde->motifValue(x,y)==5154) {
        //if (gpMonde->contenuValue(x,y)==70) gpMonde->setContenu(x/16,y/16,71);
        gpAudio->playSound(28);
        switch (zone) {
            case 51 : 
                gpMonde->setValeur(130*16,22*16,5153,LIBRE);
                gpJoueur->setCoffre(5,7,1);
                gpMonde->rempli(42,64,4,7); gpMonde->rempli(64,35,2,5); 
                gpMonde->rempli(62,62,15,11); gpMonde->rempli(84,37,12,4);
                gpMonde->rempli(164,37,12,4); gpMonde->rempli(149,63,2,2);
                gpMonde->rempli(214,48,4,9); gpMonde->rempli(282,62,4,11);
                gpMonde->vide(7,51,2,2); gpMonde->vide(28,66,4,3); gpMonde->vide(45,51,2,2);
                gpMonde->vide(89,35,2,2); gpMonde->vide(82,47,4,2); gpMonde->vide(88,47,10,2);
                gpMonde->vide(82,51,11,2); gpMonde->vide(95,51,3,2);
                gpMonde->vide(82,55,2,2); gpMonde->vide(86,55,12,2);
                gpMonde->vide(128,51,4,4); gpMonde->vide(169,35,2,2);
                gpMonde->vide(49,36,2,2);
                break;
            case 55 :
                gpMonde->setValeur(69*16,42*16,5153,LIBRE);
                gpMonde->setValeur(70*16,42*16,5153,LIBRE);
                gpMonde->passage(68,43,9);
                testAnim();
                break;
        }
    }
}

void Jeu::testTeleporteur(int x, int y) {
    if (gpMonde->motifValue(x,y)==3417) {
        gpAudio->playSound(5);
        switch (zone) {
            case 46 : 
                if (gpMonde->regionValue(0)==240*16) {
                    gpMonde->transitFull(46,gpJoueur->getX()+(100*16),gpJoueur->getY()-(12*16));
                }else{
                    gpMonde->transitFull(46,gpJoueur->getX()-(100*16),gpJoueur->getY()+(12*16));
                }
                break;
            case 48 : 
                gpMonde->transitFull(48,gpJoueur->getX()-(280*16),gpJoueur->getY()-(8*16));
                break;
            case 53 : 
                if (gpMonde->regionValue(1)==0) {
                    gpMonde->transitFull(53,gpJoueur->getX(),gpJoueur->getY()+(78*16));
                }else{
                    gpMonde->transitFull(53,gpJoueur->getX(),gpJoueur->getY()-(78*16));
                }
                break;
            case 55 : 
                gpMonde->transitFull(55,69*16+8,178*16-8);
                break;
            case 60 :
                gpMonde->transitFull(111,9*16+8,10*16-8);
                break;
            case 64 :
                SDL_Delay(1500);
                gpMonde->transitTemps(70,x,y+4,S);
                if (gpJoueur->getAvancement() < PORTAIL_F_UTILISE) {
                    gpJoueur->setLapin(true);
                    gpJoueur->setAvancement(PORTAIL_F_UTILISE);}
                break;
            case 69 :
                SDL_Delay(1500);
                gpMonde->transitTemps(70,x,y+4,S);
                if (gpJoueur->hasObjet(O_OCARINA)) ecrit(348);
                break;
            case 70 :
                SDL_Delay(1500);
                gpMonde->transitTemps(69,x,y+4,S);
                if (gpJoueur->getAvancement() < PORTAIL_PRE_PRESENT_UTILISE) 
                    gpJoueur->setAvancement(PORTAIL_PRE_PRESENT_UTILISE);
                break;
            case 111 :
            case 114 :
            case 124 :
                //todo : ajuster les coordonnées d'arrivée
                gpMonde->transitFull(60,69*16+8,145*16-8);
                break;
            /*case 25 : 
                if (gpMonde->regionValue(0)==40*16) {
                    gpMonde->transitFull(25,gpJoueur->getX()+(140*16),gpJoueur->getY()-(75*16));
                }else{
                    gpMonde->transitFull(25,gpJoueur->getX()-(140*16),gpJoueur->getY()+(75*16));
                }
                break;
            case 26 :
                int randomV;
                if (gpJoueur->getCle(11,0) && !gpJoueur->getCle(11,1)) randomV=4;
                else randomV = rand()%4;
                switch (randomV) {
                    case 0 : 
                        gpMonde->transitFull(26,gpJoueur->getX()-(60*16),gpJoueur->getY()-(72*16));
                        break;
                    case 1 : 
                        gpMonde->transitFull(26,gpJoueur->getX()+(60*16),gpJoueur->getY()-(72*16));
                        break;
                    case 2 : 
                        gpMonde->transitFull(26,gpJoueur->getX()-(60*16),gpJoueur->getY()+(18*16));
                        break;
                    case 3 : 
                        gpMonde->transitFull(26,gpJoueur->getX()+(60*16),gpJoueur->getY()+(18*16));
                        break;
                    case 4 : 
                        gpMonde->transitFull(26,gpJoueur->getX(),gpJoueur->getY()-(27*16));
                        break;
                }
                break;
            case 28 :
                gpMonde->transitFull(28,149*16+8,115*16-32+8-8);
                gpAudio->playSpecial(4); //gpStatut->setJauge(true); 
                ecrit(409); break;*/
        }
        testAnim();
    }
}

/*bool Jeu::testVillage(int i, int j) {
    if (isVillage(i,j))
    if (((zone == 3 || zone == 7 || zone == 13) && gpJoueur->getOni() ) 
    || (zone == 11 && !gpJoueur->getOni())) {
        if (!getText()) ecrit(129);
        return true;
    }
    return false;
}*/

bool Jeu::verifZoneJoueur(int x, int y, int w, int h, int nbdir) {
    
    monteBarque(x, y);
    
    descendBarque(x, y);
    
    monteWagon(x, y);
    
    //ouvre porte
    ouvrePorteMaison(x+8, y);
    
    //portes verrouillées
    ouvrePorteDonjon(x/*+8*/, y/*-2*/);
    
    testInterrupteur(x+8, y+4);
    
    testInterrupteurEtoile(x+8, y+8);
    
    testTeleporteur(x+8,y+8);
    
    if (isDangereux(x,y)) return false;
    
    if (!isNotFull(x,y,w,h)) {
        if ((x-(gpJoueur->getX()+gpJoueur->getZoneBase()->getZone()->x)==0 
        || y-(gpJoueur->getY()+gpJoueur->getZoneBase()->getZone()->y)==0) && nbdir==1) {
        //en fonction de la direction
            if (y-(gpJoueur->getY()+gpJoueur->getZoneBase()->getZone()->y)<0 
            && gpJoueur->getDirection()==N) { 
                if ( isMarchable(x-2,y, 1, 1, 0)
                && isMarchable(x-2,y+h-1, 1, 1, 0)
                && isMarchable(x,y, 1, 1, 0)
                && isMarchable(x+7,y, 1, 1, 0)) gpJoueur->moveX(-2);
                if ( isMarchable(x+8,y, 1, 1, 0)
                && isMarchable(x+w-1,y, 1, 1, 0)
                && isMarchable(x+w+1,y, 1, 1, 0)
                && isMarchable(x+w+1,y+h-1, 1, 1, 0)) gpJoueur->moveX(2);
            }
            if (y-(gpJoueur->getY()+gpJoueur->getZoneBase()->getZone()->y)>0 
            && gpJoueur->getDirection()==S) {
                if ( isMarchable(x-2,y, 1, 1, 0)
                && isMarchable(x-2,y+h-1, 1, 1, 0)
                && isMarchable(x,y+h-1, 1, 1, 0)
                && isMarchable(x+7,y+h-1, 1, 1, 0)) gpJoueur->moveX(-2);
                if ( isMarchable(x+8,y+h-1, 1, 1, 0)
                && isMarchable(x+w-1,y+h-1, 1, 1, 0)
                && isMarchable(x+w+1,y, 1, 1, 0)
                && isMarchable(x+w+1,y+h-1, 1, 1, 0)) gpJoueur->moveX(2);
            }
            if (x-(gpJoueur->getX()+gpJoueur->getZoneBase()->getZone()->x)<0 
            && gpJoueur->getDirection()==O) {
                if ( isMarchable(x,y-2, 1, 1, 0)
                && isMarchable(x+w-1,y-2, 1, 1, 0)
                && isMarchable(x,y, 1, 1, 0)
                && isMarchable(x,y+7, 1, 1, 0)) gpJoueur->moveY(-2);
                if ( isMarchable(x,y+8, 1, 1, 0)
                && isMarchable(x,y+h-1, 1, 1, 0)
                && isMarchable(x,y+h+1, 1, 1, 0)
                && isMarchable(x+w+1,y+h+1, 1, 1, 0)) gpJoueur->moveY(2);
            }
            if (x-(gpJoueur->getX()+gpJoueur->getZoneBase()->getZone()->x)>0 
            && gpJoueur->getDirection()==E) {
                if ( isMarchable(x,y-2, 1, 1, 0)
                && isMarchable(x+w-1,y-2, 1, 1, 0)
                && isMarchable(x+w-1,y, 1, 1, 0)
                && isMarchable(x+w-1,y+7, 1, 1, 0)) gpJoueur->moveY(-2);
                if ( isMarchable(x+w-1,y+8, 1, 1, 0)
                && isMarchable(x+w-1,y+h-1, 1, 1, 0)
                && isMarchable(x,y+h+1, 1, 1, 0)
                && isMarchable(x+w+1,y+h+1, 1, 1, 0)) gpJoueur->moveY(2);
            }
        }
        return false;
    }
    
    //test village
    //if (testVillage(x,y-8)) return false;
        
    return true;
}

// renvoit vrai si Link peut y aller
bool Jeu::isNotFull(int x, int y, int w, int h) {
    for (int i = x; i < x + w; i++)
        for (int j = y; j < y + h; j++) {
            if (!isMarchable(i, j, 1, 1, 0)) return false;
        }
    return true;
}

//cas général
bool Jeu::isNotFull(int x, int y, int w, int h, int vol, int nage, int spectre) {
    for (int i = x; i < x + w; i++)
        for (int j = y; j < y + h; j++) {
            if (!isMarchable(i, j, 1, 1, spectre)) return false;
        }
    if (isVide(x,y,w,h) && !vol && !spectre) return false;
    if (isWater(x,y,w,h) && !vol && !nage && !spectre) return false;
    return true;
}

//renvoit vrai si plein d'eau, lol
bool Jeu::isWater(int x, int y, int w, int h) {
    for (int i = x; i < x + w; i++)
        for (int j = y; j < y + h; j++) {
            if (i>0 && j>0 && i<gpMonde->getLargeur() && j<gpMonde->getHauteur()) 
                if (gpMonde->murValue(i,j)!=EAU) return false;
        }
    return true;
}

//renvoit vrai si plein de vide, super lol
bool Jeu::isVide(int x, int y, int w, int h) {
    for (int i = x; i < x + w; i++)
        for (int j = y; j < y + h; j++) {
            if (i>0 && j>0 && i<gpMonde->regionValue(2) && j<gpMonde->regionValue(3)) 
                if (gpMonde->murValue(i,j)!=VIDE) return false;
        }
    return true;
}

//renvoit vrai si contient du vide
bool Jeu::hasVide(int x, int y, int w, int h) {
    for (int i = x; i < x + w; i++)
        for (int j = y; j < y + h; j++) {
            if (i>0 && j>0 && i<gpMonde->regionValue(2) && j<gpMonde->regionValue(3)) 
                if (gpMonde->murValue(i,j)==VIDE) return true;
        }
    return false;
}

//renvoit vrai présence de glace
bool Jeu::isGlace(int x, int y, int w, int h) {
    for (int i = x; i < x + w; i++)
        for (int j = y; j < y + h; j++) {
            if (i>0 && j>0 && i<gpMonde->regionValue(2) && j<gpMonde->regionValue(3)) 
                if (gpMonde->murValue(i,j)==GLACE) return true;
        }
    return false;
}

//renvoit vrai si ramassable
bool Jeu::isRamassable(int x, int y, int g) {
    int val = gpMonde->motifValue(x,y);
    if ((val==38 || val==39 || val==192 || val==1213 || (val>=3970 && val<=3973) 
    || val==1687 || val==4403 || val==3997) && g==2) 
        return true;
    if ((val==32 || val==35 || val==191 || val==1686 || val==4401 
    || (val>=3088 && val<=3091)) && g>=1) return true;
    if (((val>=30 && val <=37 && val!=32 && val!=35) 
    || val==193 || val==1341 || val==4402) && g>=0) return true;
    return false;
}

bool Jeu::isMarchable(int i, int j, int vol, int nage, int spectre, int caisse) {
    if (i < gpMonde->regionValue(0) || i>= gpMonde->regionValue(2) 
    || j < gpMonde->regionValue(1) || j>= gpMonde->regionValue(3)) return false;
    if (spectre) return true;
    //vérif caisses
    Caisse* gpCaisse2 = gpCaisse->getSuivant();
    while (gpCaisse2!=NULL) {
        if (abs(i-gpCaisse2->getX()<16) || abs(j-gpCaisse2->getY()<16)) {
            if (i >= gpCaisse2->getX() && i < gpCaisse2->getX()+16
                && j >= gpCaisse2->getY() && j < gpCaisse2->getY()+16
                && gpCaisse2->getVie()) return false;
        }
        gpCaisse2 = gpCaisse2->getSuivant();
    }
    int val = gpMonde->murValue(i, j);
    if (val == LIBRE || val == GLACE || (val == BLOC && !caisse)) return true;
    if (val == VIDE && vol) return true;
    if (val == EAU && (vol || nage)) return true;
    return false;
}

bool Jeu::isEnnemi(int x, int y, int w, int h, int id, int type) {
    Ennemi* gpEnnemi2 = gpEnnemi->getSuivant();
    SDL_Rect* r;
    int x1;
    int y1;
    while (gpEnnemi2 != NULL) {
        if (gpEnnemi2->getListId() != id && gpEnnemi2->getVie()>0 
        && (gpEnnemi2->getEnnId()==type || type ==0)) {
            r = gpEnnemi2->getZoneBase()->getZone();
            x1 = gpEnnemi2->getX();
            y1 = gpEnnemi2->getY();
            if ((x1 + r->x + r->w > x && x1 + r->x < x+w)
            && (y1 + r->y + r->h > y && y1 + r->y < y+h)) 
                return true;
        }
        gpEnnemi2 = gpEnnemi2->getSuivant();
    }
    return false;
}

bool Jeu::isPnj(int x, int y, int w, int h, int id) {
    Pnj* gpPnj2 = gpPnj->getSuivant();
    SDL_Rect* r;
    int x1;
    int y1;
    while (gpPnj2 != NULL) {
        if (gpPnj2->getListId() != id && gpPnj2->getVie()>0) {
            r = gpPnj2->getZoneBase()->getZone();
            x1 = gpPnj2->getX();
            y1 = gpPnj2->getY();
            if ((x1 + r->x + r->w > x && x1 + r->x < x+w)
            && (y1 + r->y + r->h > y && y1 + r->y < y+h)) 
                return true;
        }
        gpPnj2 = gpPnj2->getSuivant();
    }
    return false;
}

bool Jeu::isLink(int x, int y, int w, int h) {
    SDL_Rect* r = gpJoueur->getZoneBase()->getZone();
    int x1 = gpJoueur->getX();
    int y1 = gpJoueur->getY();
    
    if (gpJoueur->getVie()>0) {
        if ((x1 + r->x + r->w > x && x1 + r->x < x+w)
        && (y1 + r->y + r->h > y && y1 + r->y < y+h)) 
            return true;
    }
    return false;
}

//ramasse objet rammassable (pancarte, pierre, etc.)
void Jeu::ramasse() {
    int i = 0;
    int j = 0;
    int g = gpJoueur->hasObjet(O_GANTS);
    switch(gpJoueur->getDirection()) {
        case N : i=gpJoueur->getX()+8; j=gpJoueur->getY()+7-2; break;
        case S : i=gpJoueur->getX()+8; j=gpJoueur->getY()+24+2; break;
        case O : i=gpJoueur->getX()-1-2; j=gpJoueur->getY()+16; break;
        case E : i=gpJoueur->getX()+16+2; j=gpJoueur->getY()+16; break;
    }
    if (isRamassable(i,j,g)) {gpJoueur->setTypeAnim(SOULEVE); return;}
    if (g < 2) if (isRamassable(i,j,2)) gpJoueur->setTypeAnim(LOURD);
}

int Jeu::enleve() {
    int i = 0;
    int j = 0;
    int g = gpJoueur->hasObjet(O_GANTS);
    switch(gpJoueur->getDirection()) {
        case N : i=gpJoueur->getX()+8; j=gpJoueur->getY()+7-2; break;
        case S : i=gpJoueur->getX()+8; j=gpJoueur->getY()+24+2; break;
        case O : i=gpJoueur->getX()-1-2; j=gpJoueur->getY()+16; break;
        case E : i=gpJoueur->getX()+16+2; j=gpJoueur->getY()+16; break;
    }
    if (!isRamassable(i,j,g)) return 0;
    
    int val = gpMonde->motifValue(i,j);
    int new_val = val+9;
    int obj=0;
    
    switch(val) {
        case 30 : obj = 1; new_val = 40; break;
        case 31 : obj = 2; new_val = 40; break;
        case 32 : obj = 3; new_val = 41; break;
        case 33 : obj = 4; new_val = 42; break;
        case 34 : obj = 4; new_val = 43; break;
        case 35 : obj = 3; new_val = 44; break;
        case 36 : obj = 4; new_val = 45; break;
        case 37 : obj = 5; new_val = 44; break;
        case 38 : obj = 6; new_val = 41; break;
        case 39 : obj = 6; new_val = 44; break;
        case 191 : obj = 3; new_val = 46; break;
        case 192 : obj = 6; new_val = 46; break;
        case 193 : obj = 4; new_val = 47; break;
        case 1213 : obj = 7; new_val = 44; break;
        case 1686 : obj = 5; new_val = 46; break;
        case 1687 : obj = 7; new_val = 46; break;
        case 1341 : obj = 4; new_val = 1342; break;
        case 3088 : case 3089 : case 3090 : case 3091 : obj = 8; new_val = val; break;
        case 3970 : case 3971 : case 3972 : case 3973 : obj = 9; new_val = val; break;
        case 3997 : obj = 9; new_val = 3804; break;
        case 4401 : obj = 3; new_val = 4404; break;
        case 4402 : obj = 4; new_val = 4405; break;
        case 4403 : obj = 6; new_val = 4404; break;
    }
    
    //pierres désert
    if (zone == 27) {
        int a=((int)(i/16));
        int b=((int)(j/16));
        switch (a) {
            case 42 : if (b == 25) gpMonde->setUtile(1); break;
            case 68 : if (b == 32 && gpMonde->getUtile() == 1) gpMonde->setUtile(2); break;
            case 48 : if (b == 25 && gpMonde->getUtile() == 2) gpMonde->setUtile(3); break;
            case 58 : if (b == 32 && gpMonde->getUtile() == 3) gpMonde->setUtile(4); break;
            case 41 : if (b == 41 && gpMonde->getUtile() == 4) gpMonde->setUtile(5); break;
            case 51 : if (b == 49 && gpMonde->getUtile() == 5) {
                gpAudio->playSound(9); gpMonde->setValeur(i,j,194,VIDE);
                for (int z = 0; z < 4; z++) {
                    gpMonde->setMurs(a*2-1,b*2-1+z,VIDE);
                    gpMonde->setMurs(a*2+2,b*2-1+z,VIDE);
                    gpMonde->setMurs(a*2-1+z,b*2-1,VIDE);
                    gpMonde->setMurs(a*2-1+z,b*2+2,VIDE);
                }
                gpAudio->playSound(34); return obj;} break;
        }
    }
    
    if (obj!=8 && (obj!=9 || val==3997)) gpMonde->setValeur(i,j,new_val,0);
    if (isDonjon()) {
        if(gpMonde->contenuValue(i, j)==51) gpMonde->setValeur(i,j,1005,-1,0,51);
        if(gpMonde->contenuValue(i, j)==50) gpMonde->setValeur(i,j,1004,-1,0,50);
        if(gpMonde->contenuValue(i, j)==71) gpMonde->setValeur(i,j,2950,-1,0,71);
        if(gpMonde->contenuValue(i, j)==70) gpMonde->setValeur(i,j,2951,-1,0,70);
    }
    
    if (gpMonde->contenuValue(i,j)==-1) {
        gpMonde->setValeur(i,j,25,VIDE);
        int a=((int)(i/16));
        int b=((int)(j/16));
        for (int z = 0; z < 4; z++) {
            gpMonde->setMurs(a*2-1,b*2-1+z,VIDE);
            gpMonde->setMurs(a*2+2,b*2-1+z,VIDE);
            gpMonde->setMurs(a*2-1+z,b*2-1,VIDE);
            gpMonde->setMurs(a*2-1+z,b*2+2,VIDE);
        }
        if (zone==26) gpAudio->playSound(9);
    }
    
    if (zone==46) {
        if (gpMonde->regionValue(0)==340*16 && gpMonde->motifValue(342*16,7*16)==40 
        && gpMonde->motifValue(345*16,7*16)==40 && gpMonde->motifValue(348*16,7*16)==40 
        && gpMonde->motifValue(351*16,7*16)==40 && gpMonde->motifValue(354*16,7*16)==40 
        && gpMonde->motifValue(357*16,7*16)==40) 
            gpMonde->setValeur(357*16,12*16,1004,LIBRE);
        if (gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==30*16 
        && gpMonde->motifValue(4*16,32*16)==40 && gpMonde->motifValue(15*16,32*16)==40 
        && gpMonde->motifValue(4*16,42*16)!=30 && gpMonde->motifValue(15*16,42*16)==40) 
            gpMonde->setValeur(4*16,42*16,1004,-1,LIBRE,51);
    }
    
    gpAudio->playSound(34);
    
    return obj;
}

void Jeu::setMenu(bool b) {
    menu = b;
    if (!menu) gpMenu->menuOut();
    else {stop = true; gpMenu->menuIn();}
}

void Jeu::ecrit(int id, bool anim, bool cadre, int x, int y, int w, int h) {
    setText(true);
    gpTexte->setTexte(id, x, y, w, h, anim, cadre);
}

void Jeu::affiche(SDL_Surface* gpScreen, std::string s, int x, int y) {
    gpTexte->affiche(gpScreen, s, x, y);
}

void Jeu::afficheTexteAvecId(SDL_Surface* gpScreen, int id, int x, int y) {
    afficheTexteAvecId(gpScreen, id, "", x, y);
}

void Jeu::afficheTexteAvecId(SDL_Surface* gpScreen, int id, std::string s, int x, int y) {
    gpTexte->afficheTexteAvecId(gpScreen, id, s, x, y);
}

Ennemi* Jeu::existEnnemi(int type) {
    Ennemi* gpEnnemi2 = gpEnnemi->getSuivant();
    while (gpEnnemi2 != NULL) {
        if (gpEnnemi2->getEnnId() == type) return gpEnnemi2;
        gpEnnemi2 = gpEnnemi2->getSuivant();
    }
    return NULL;
}

void Jeu::setStop(bool b) { stop = b;}

void Jeu::setTransition(bool b) { transition = b;}

void Jeu::setText(bool b) {
    text = b;
    stop = text;
    if (zone==56 && gpMonde->regionValue(0)==160*16 
    && ((gpMonde->regionValue(1)==0 && gpJoueur->getEpee()<5) 
    || gpMonde->regionValue(1)==60*16)) stop=true;
}

void Jeu::setPhg(int i, int j) {phg[0]=i;phg[1]=j;}

void Jeu::setZone(int i) {zone=i;}

bool Jeu::getStop() { return stop;}
bool Jeu::getTransition() { return transition;}
int Jeu::getZone() { return zone;}
int Jeu::getPhg(int i) { return phg[i];}
bool Jeu::getMenu() { return menu;}
bool Jeu::getText() { return text;}
SDL_Surface* Jeu::getImageObjets() { return imageObjets;}

int Jeu::getVueHorz() {return vueHorz;}
int Jeu::getVueVert() {return vueVert;}
void Jeu::setVueHorz(int i) {vueHorz = i;}
void Jeu::setVueVert(int i) {vueVert = i;}

void Jeu::setNewZone(int nz) { newzone = nz;}
void Jeu::setNewX(int nx) { newx = nx;}
void Jeu::setNewY(int ny) { newy = ny;}
void Jeu::setNewDir(int dir) { newdir = dir;}

int Jeu::getNewZone() { return newzone;}
int Jeu::getNewX() { return newx;}
int Jeu::getNewY() { return newy;}

void Jeu::permuteBloc(int val) {
    gpEnnemi->permute(val);
}

void Jeu::testAnim() {
    switch (zone) {
        case 46 :
            //mini boss
            if (gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==30*16 
            && !gpJoueur->getCoffre(0,22) && gpMonde->motifValue(9*16,30*16)==2765) {
                gpAudio->playSound(20);
                gpAudio->playSpecial(1); gpStatut->setJauge(true);
                gpJoueur->moveY(16);
                gpMonde->setValeur(9*16, 30*16, 2815, -1, LIBRE, 0);
                gpMonde->setValeur(10*16, 30*16, 2816, -1, LIBRE, 0);
                gpMonde->setValeur(9*16, 31*16, 2817, 0, LIBRE, 0);
                gpMonde->setValeur(10*16, 31*16, 2818, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(9*2+i,30*2,SEMI_PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(9*2+i,30*2+1,BAS);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(9*2+i,30*2+2,PLEIN);
            }
            if (gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==30*16 
            && nbEnnemis()==0 && gpMonde->motifValue(9*16,30*16)==2815) {
                gpAudio->playSound(20);
                gpMonde->passage(9,30,0); gpMonde->passage(20,36,1);
                gpJoueur->setCoffre(0,22);
            }
            //boss
            if (gpMonde->regionValue(0)==340*16 && gpMonde->regionValue(1)==0
            && !gpJoueur->getCoeur(0) && nbEnnemis() && !gpStatut->getJauge()) {
                gpAudio->playSpecial(10); gpStatut->setJauge(true);}
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoeur(0)) gpAudio->playSpecial(3);
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->hasMedaillon(0) && gpMonde->motifValue(249*16,28*16)==2819) {
                gpAudio->playSound(20); gpMonde->passage(249,30,0); break;}
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==15*16 
            && !gpJoueur->hasMedaillon(0) && gpMonde->motifValue(249*16,28*16)==2771) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                if (gpJoueur->getCoeur(0)) gpAudio->playSpecial(3);
                gpMonde->setValeur(249*16, 28*16, 2819, -1, LIBRE, 0);
                gpMonde->setValeur(250*16, 28*16, 2820, -1, LIBRE, 0);
                gpMonde->setValeur(249*16, 29*16, 2821, 0, LIBRE, 0);
                gpMonde->setValeur(250*16, 29*16, 2822, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(249*2+i,28*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(249*2+i,28*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(249*2+i,28*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoeur(0) && gpMonde->motifValue(249*16,15*16)==2815) {
                gpAudio->playSound(20); gpMonde->passage(249,15,0);}
            if (gpMonde->regionValue(0)==340*16 && gpMonde->regionValue(1)==0 
            && gpJoueur->getCoeur(0) && gpMonde->motifValue(352*16,10*16)==3416)
                gpMonde->setValeur(352*16, 10*16, 3417, LIBRE);
            //donjon
            if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==45*16 
            && nbEnnemis()==0 && gpMonde->motifValue(129*16,45*16)==2815) {
                gpAudio->playSound(20); gpMonde->passage(129,45,0);}
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==45*16 
            && nbEnnemis()==0 && gpMonde->motifValue(180*16,51*16)==2823) {
                gpAudio->playSound(20); gpMonde->passage(180,51,1);}
            if (gpMonde->regionValue(0)==300*16 && gpMonde->regionValue(1)==0 
            && nbEnnemis()==0 && gpMonde->motifValue(300*16,6*16)==2823) {
                gpAudio->playSound(20); gpMonde->passage(300,6,1);}
            if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==0 
            && nbEnnemis()==0 && gpMonde->motifValue(20*16,6*16)==2823) {
                gpAudio->playSound(20); gpMonde->passage(20,6,1);}
            break;
        case 47 :
            //mini boss
            if (gpMonde->regionValue(0)==320*16 && gpMonde->regionValue(1)==45*16 
            && !gpJoueur->getCoffre(1,15) && gpMonde->motifValue(329*16,45*16)==2965) {
                gpAudio->playSound(20);
                gpAudio->playSpecial(1); gpStatut->setJauge(true);
                gpJoueur->moveY(16);
                gpMonde->setValeur(329*16, 45*16, 3015, -1, LIBRE, 0);
                gpMonde->setValeur(330*16, 45*16, 3016, -1, LIBRE, 0);
                gpMonde->setValeur(329*16, 46*16, 3017, 0, LIBRE, 0);
                gpMonde->setValeur(330*16, 46*16, 3018, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(329*2+i,45*2,SEMI_PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(329*2+i,45*2+1,BAS);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(329*2+i,45*2+2,PLEIN);
            }
            if (gpMonde->regionValue(0)==320*16 && gpMonde->regionValue(1)==45*16 
            && nbEnnemis()==0 && gpMonde->motifValue(329*16,45*16)==3015) {
                gpAudio->playSound(20);
                gpMonde->passage(329,45,0); gpMonde->passage(329,60,0);
                gpJoueur->setCoffre(1,15);
            }
            //boss
            if (gpMonde->regionValue(0)==340*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getCoeur(1)) gpAudio->playSpecial(3);
            if (gpMonde->regionValue(0)==340*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->hasMedaillon(1) && gpMonde->motifValue(349*16,43*16)==3019) {
                gpAudio->playSound(20); gpMonde->passage(349,45,0); break;}
            if (gpMonde->regionValue(0)==340*16 && gpMonde->regionValue(1)==30*16 
            && !gpJoueur->hasMedaillon(1) && gpMonde->motifValue(349*16,43*16)==2971) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                if (!gpJoueur->getCoeur(1)) {gpAudio->playSpecial(11); gpStatut->setJauge(true);}
                gpMonde->setValeur(349*16, 43*16, 3019, -1, LIBRE, 0);
                gpMonde->setValeur(350*16, 43*16, 3020, -1, LIBRE, 0);
                gpMonde->setValeur(349*16, 44*16, 3021, 0, LIBRE, 0);
                gpMonde->setValeur(350*16, 44*16, 3022, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(349*2+i,43*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(349*2+i,43*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(349*2+i,43*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==340*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getCoeur(1) && gpMonde->motifValue(349*16,30*16)==3015) {
                gpAudio->playSound(20); gpMonde->passage(349,30,0);}
            if (gpMonde->regionValue(0)==340*16 && gpMonde->regionValue(1)==30*16 
            && nbEnnemis()==0 && gpMonde->motifValue(349*16,36*16)!=3084) {
                gpMonde->setValeur(349*16,36*16,3084,0);
                gpMonde->setValeur(350*16,36*16,3084,0);
                gpMonde->setValeur(349*16,37*16,3084,0);
                gpMonde->setValeur(350*16,37*16,3084,0);
                gpMonde->setValeur(349*16,38*16,3084,0);
                gpMonde->setValeur(350*16,38*16,3084,0);}
            //donjon
            //caisses à 0
            if (gpMonde->regionValue(0)==200*16 && gpMonde->regionValue(1)==30*16 
            && gpMonde->motifValue(204*16,34*16)==3084) {
                Caisse* caisse = gpCaisse->getSuivant();
                while (caisse != NULL) {
                    if (caisse->isActif() && caisse->getNombre()) return;
                    caisse = caisse->getSuivant();
                }
                gpAudio->playSound(9);
                gpMonde->setValeur(204*16,34*16,303,-1,PLEIN,C_CLE);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<205*16) gpJoueur->moveX(205*16-gpJoueur->getX());
            }
            //puzzles caisses à 0
            if (gpMonde->regionValue(0)==260*16 && gpMonde->regionValue(1)==75*16 
            && gpMonde->motifValue(260*16,81*16)==3023) {
                Caisse* caisse = gpCaisse->getSuivant();
                while (caisse != NULL) {
                    if (caisse->isActif() && 
                    (caisse->getNombre()
                    || ( (caisse->getX()/16!=268 && caisse->getY()/16!=80)
                    && (caisse->getX()/16!=272 || caisse->getY()/16!=80)
                    && (caisse->getX()/16!=270 || caisse->getY()/16!=82)
                    && (caisse->getX()/16!=268 || caisse->getY()/16!=83)
                    && (caisse->getX()/16!=272 || caisse->getY()/16!=83)
                    && (caisse->getX()/16!=269 || caisse->getY()/16!=84)
                    && (caisse->getX()/16!=270 || caisse->getY()/16!=84)
                    && (caisse->getX()/16!=271 || caisse->getY()/16!=84)))
                    ) return;
                    caisse = caisse->getSuivant();
                }
                gpAudio->playSound(20); gpMonde->passage(260,81,1);
            }
            if (gpMonde->regionValue(0)==320*16 && gpMonde->regionValue(1)==0 
            && gpMonde->motifValue(340*16,6*16)==3023) {
                Caisse* caisse = gpCaisse->getSuivant();
                while (caisse != NULL) {
                    if (caisse->isActif() && 
                    (caisse->getNombre()
                    || ( (caisse->getX()/16!=328 && caisse->getY()/16!=5)
                    && (caisse->getX()/16!=331 || caisse->getY()/16!=5)
                    && (caisse->getX()/16!=329 || caisse->getY()/16!=6)
                    && (caisse->getX()/16!=330 || caisse->getY()/16!=6)
                    && (caisse->getX()/16!=329 || caisse->getY()/16!=7)
                    && (caisse->getX()/16!=330 || caisse->getY()/16!=7)
                    && (caisse->getX()/16!=328 || caisse->getY()/16!=8)
                    && (caisse->getX()/16!=331 || caisse->getY()/16!=8)))
                    ) return;
                    caisse = caisse->getSuivant();
                }
                gpAudio->playSound(20); gpMonde->passage(340,6,1);
            }
            if (gpMonde->regionValue(0)==320*16 && gpMonde->regionValue(1)==30*16 
            && gpMonde->motifValue(334*16,33*16)==3084) {
                Caisse* caisse = gpCaisse->getSuivant();
                while (caisse != NULL) {
                    if (caisse->isActif() && 
                    (caisse->getNombre()
                    || ( (caisse->getX()/16!=330 && caisse->getY()/16!=35)
                    && (caisse->getX()/16!=331 || caisse->getY()/16!=35)
                    && (caisse->getX()/16!=332 || caisse->getY()/16!=35)
                    && (caisse->getX()/16!=332 || caisse->getY()/16!=36)
                    && (caisse->getX()/16!=330 || caisse->getY()/16!=37)
                    && (caisse->getX()/16!=332 || caisse->getY()/16!=37)
                    && (caisse->getX()/16!=329 || caisse->getY()/16!=38)))
                    ) return;
                    caisse = caisse->getSuivant();
                }
                gpAudio->playSound(9);
                gpMonde->setValeur(334*16,33*16,303,-1,PLEIN,C_CLE);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>333*16) gpJoueur->moveX(333*16-gpJoueur->getX());
            }
            //combinaison 12086
            if (gpMonde->regionValue(0)==320*16 && gpMonde->regionValue(1)==60*16 
            && gpMonde->motifValue(323*16,63*16)==3084) {
                Caisse* caisse = gpCaisse->getSuivant();
                while (caisse != NULL) {
                    if (caisse->isActif() && 
                    ( (caisse->getX()/16!=326 || caisse->getNombre()!=1)
                    && (caisse->getX()/16!=328 || caisse->getNombre()!=2)
                    && (caisse->getX()/16!=330 || caisse->getNombre()!=0)
                    && (caisse->getX()/16!=332 || caisse->getNombre()!=8)
                    && (caisse->getX()/16!=334 || caisse->getNombre()!=6))
                    ) return;
                    caisse = caisse->getSuivant();
                }
                gpAudio->playSound(9);
                gpMonde->setValeur(323*16,63*16,303,-1,PLEIN,C_GANTS);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<324*16) gpJoueur->moveX(324*16-gpJoueur->getX());
            }
            //caisse ouvre porte
            if (gpMonde->regionValue(0)==280*16 && gpMonde->regionValue(1)==60*16) {
                Caisse* caisse = gpCaisse->getSuivant();
                while (caisse != NULL) {
                    if (caisse->isActif() && caisse->getX()>=299*16 && caisse->getX()<=300*16
                    && caisse->getY()>=74*16 && caisse->getY()<=75*16) {
                        if (caisse->getX()==299*16 && caisse->getY()==74*16) {
                            if (gpMonde->motifValue(280*16,66*16)==3023) {
                                gpAudio->playSound(20); gpMonde->passage(280,66,1);}
                        } else {
                            for (int i=0; i<6; i++) {
                                gpMonde->setValeur((278+2+(i%2))*16,(66+((int)(i/2)))*16,3023+i,1);
                                gpMonde->setValeur((278+(i%2))*16,(66+((int)(i/2)))*16,3029+i,1);}
                            for (int i=0; i<6; i++) {
                                gpMonde->setMurs(281*2+1,66*2+i,0);
                                gpMonde->setMurs(278*2,66*2+i,0);}
                        }
                        if (caisse->getX()==300*16 && caisse->getY()==74*16) {
                            if (gpMonde->motifValue(309*16,60*16)==3015) {
                                gpAudio->playSound(20); gpMonde->passage(309,60,0);}
                        } else {
                            for (int i=0; i<4; i++) {
                                gpMonde->setValeur((309+(i%2))*16,(58+((int)(i/2)))*16,3019+i,1);
                                gpMonde->setValeur((309+(i%2))*16,(58+2+((int)(i/2)))*16,3015+i,1);}
                            for (int i=0; i<4; i++) {
                                gpMonde->setMurs(309*2+i,58*2,0);
                                gpMonde->setMurs(309*2+i,61*2+1,0);}
                        }
                        if (caisse->getX()==299*16 && caisse->getY()==75*16) {
                            if (gpMonde->motifValue(280*16,81*16)==3023) {
                                gpAudio->playSound(20); gpMonde->passage(280,81,1);}
                        } else {
                            for (int i=0; i<6; i++) {
                                gpMonde->setValeur((278+2+(i%2))*16,(81+((int)(i/2)))*16,3023+i,1);
                                gpMonde->setValeur((278+(i%2))*16,(81+((int)(i/2)))*16,3029+i,1);}
                            for (int i=0; i<6; i++) {
                                gpMonde->setMurs(281*2+1,81*2+i,0);
                                gpMonde->setMurs(278*2,81*2+i,0);}
                        }
                        if (caisse->getX()==300*16 && caisse->getY()==75*16) {
                            if (gpMonde->motifValue(320*16,81*16)==3023) {
                                gpAudio->playSound(20); gpMonde->passage(320,81,1);}
                        } else {
                            for (int i=0; i<6; i++) {
                                gpMonde->setValeur((318+2+(i%2))*16,(81+((int)(i/2)))*16,3023+i,1);
                                gpMonde->setValeur((318+(i%2))*16,(81+((int)(i/2)))*16,3029+i,1);}
                            for (int i=0; i<6; i++) {
                                gpMonde->setMurs(321*2+1,81*2+i,0);
                                gpMonde->setMurs(318*2,81*2+i,0);}
                        }
                        return;
                    }
                    caisse = caisse->getSuivant();
                }
            }
            //coffre
            if (gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==15*16
            && gpJoueur->getCoffre(1,10) && gpMonde->motifValue(180*16,21*16)==3023) {
                gpAudio->playSound(20); gpMonde->passage(180,21,1);}
            break;
        case 48 :
            //mini boss
            if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==30*16 
            && !gpJoueur->getCoffre(2,61) && gpMonde->motifValue(129*16,43*16)==3143) {
                gpAudio->playSound(20);
                gpAudio->playSpecial(12); gpStatut->setJauge(true);
                gpJoueur->moveY(-16);
                gpMonde->setValeur(129*16, 43*16, 3191, -1, LIBRE, 0);
                gpMonde->setValeur(130*16, 43*16, 3192, -1, LIBRE, 0);
                gpMonde->setValeur(129*16, 44*16, 3193, 0, LIBRE, 0);
                gpMonde->setValeur(130*16, 44*16, 3194, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(129*2+i,43*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(129*2+i,43*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(129*2+i,43*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==30*16 
            && nbEnnemis()==0 && gpMonde->motifValue(129*16,43*16)==3191) {
                gpAudio->playSound(20);
                gpMonde->passage(129,30,0); gpMonde->passage(129,45,0);
                gpMonde->setValeur(124*16,33*16,3084); gpMonde->setValeur(129*16,33*16,3084); 
                gpMonde->setValeur(135*16,33*16,3084); gpMonde->setValeur(126*16,42*16,3084); 
                gpMonde->setValeur(133*16,42*16,3084);
                gpMonde->setValeur(128*16,34*16,3263,2); gpMonde->setValeur(131*16,34*16,3261,2);
                gpMonde->setValeur(129*16,34*16,3252,0); gpMonde->setValeur(130*16,34*16,3252,0);
                gpMonde->setValeur(128*16,40*16,3263,2); gpMonde->setValeur(131*16,40*16,3261,2);
                gpMonde->setValeur(129*16,40*16,3252,0); gpMonde->setValeur(130*16,40*16,3252,0);
                gpJoueur->setCoffre(2,61);
            }
            //boss
            if (gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getCoeur(2)) gpAudio->playSpecial(3);
            if (gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->hasMedaillon(2) && gpMonde->motifValue(9*16,43*16)==3191) {
                gpAudio->playSound(20); gpMonde->passage(9,45,0); break;}
            if (gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==30*16 
            && !gpJoueur->hasMedaillon(2) && gpMonde->motifValue(9*16,43*16)==3143) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                if (!gpJoueur->getCoeur(2)) {gpAudio->playSpecial(13); gpStatut->setJauge(true);}
                gpMonde->setValeur(9*16, 43*16, 3191, -1, LIBRE, 0);
                gpMonde->setValeur(10*16, 43*16, 3192, -1, LIBRE, 0);
                gpMonde->setValeur(9*16, 44*16, 3193, 0, LIBRE, 0);
                gpMonde->setValeur(10*16, 44*16, 3194, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(9*2+i,43*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(9*2+i,43*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(9*2+i,43*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==280*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getCoeur(2) && gpMonde->motifValue(289*16,30*16)==3187) {
                gpAudio->playSound(20); gpMonde->passage(289,30,0);}
            if (gpMonde->regionValue(0)==280*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->hasMedaillon(2) && gpMonde->motifValue(289*16,40*16)!=3417) {
                gpAudio->playSound(9);
                gpMonde->setValeur(9*16,32*16,3416);
                gpMonde->setValeur(289*16,40*16,3417);}
            //donjon
            //ennemi vaincu => coffre carte
            if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==30*16 
             && nbEnnemis()==0 && gpMonde->motifValue(36*16,33*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(36*16,33*16,303,-1,PLEIN,C_CARTE_D);
                gpJoueur->setCoffre(2,16);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>35*16) gpJoueur->moveX(35*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre boussole
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==30*16 
             && nbEnnemis()==0 && gpMonde->motifValue(244*16,33*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(244*16,33*16,303,-1,PLEIN,C_BOUSSOLE);
                gpJoueur->setCoffre(2,19);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<245*16) gpJoueur->moveX(245*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==200*16 && gpMonde->regionValue(1)==60*16 
             && nbEnnemis()==0 && gpMonde->motifValue(216*16,62*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(216*16,62*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(2,17);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>215*16) gpJoueur->moveX(215*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==60*16 
             && nbEnnemis()==0 && gpMonde->motifValue(69*16,66*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(69*16,66*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(2,18);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<70*16) gpJoueur->moveX(70*16-gpJoueur->getX());
            }
            //ennemi vaincu => interrupteur
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==0 
             && nbEnnemis()==0 && gpMonde->motifValue(195*16,12*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(195*16,12*16,1004);
                gpJoueur->setCoffre(2,14);
            }
            //ennemi vaincu => interrupteur
            if (gpMonde->regionValue(0)==40*16 && gpMonde->regionValue(1)==0 
             && nbEnnemis()==0 && gpMonde->motifValue(57*16,3*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(57*16,3*16,1004);
                gpJoueur->setCoffre(2,15);
            }
            //torches ouvre porte
            if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==45*16 
            && gpJoueur->getCoffre(2,31) && gpJoueur->getCoffre(2,32) 
            && gpMonde->motifValue(40*16,51*16)==3195) {
                gpAudio->playSound(20); gpMonde->passage(40,51,1);}
            //torches ouvre porte
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoffre(2,33) && gpJoueur->getCoffre(2,34) 
            && gpMonde->motifValue(69*16,30*16)==3187) {
                gpAudio->playSound(20); gpMonde->passage(69,30,0);}
            //torches ouvre porte
            if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getCoffre(2,37) && gpJoueur->getCoffre(2,38) 
            && gpMonde->motifValue(100*16,36*16)==3195) {
                gpAudio->playSound(20); gpMonde->passage(100,36,1);}
            //torches ouvre porte
            if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==0 
            && gpJoueur->getCoffre(2,39) && gpMonde->motifValue(100*16,6*16)==3195) {
                gpAudio->playSound(20); gpMonde->passage(100,6,1);}
            //torches ouvre porte
            if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoffre(2,40) && gpJoueur->getCoffre(2,41) 
            && gpMonde->motifValue(129*16,15*16)==3187) {
                gpAudio->playSound(20); gpMonde->passage(129,15,0);}
            //torches ouvre porte
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoffre(2,42) && gpJoueur->getCoffre(2,43) 
            && gpJoueur->getCoffre(2,44) && gpJoueur->getCoffre(2,45) 
            && gpJoueur->getCoffre(2,46) && gpJoueur->getCoffre(2,47) 
            && gpJoueur->getCoffre(2,48) && gpJoueur->getCoffre(2,49) 
            && gpJoueur->getCoffre(2,50) && gpJoueur->getCoffre(2,51) 
            && gpJoueur->getCoffre(2,52) && gpJoueur->getCoffre(2,53) 
            && gpJoueur->getCoffre(2,54) && gpJoueur->getCoffre(2,55) 
            && gpJoueur->getCoffre(2,56) && gpMonde->motifValue(209*16,15*16)==3187) {
                gpAudio->playSound(20); gpMonde->passage(209,15,0);}
            //torches ouvre porte
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==45*16 
            && gpJoueur->getCoffre(2,57) && gpJoueur->getCoffre(2,58) 
            && gpMonde->motifValue(240*16,51*16)==3195) {
                gpAudio->playSound(20); gpMonde->passage(240,51,1);}
            //torches ouvre porte
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==45*16 
            && gpJoueur->getCoffre(2,59) && gpJoueur->getCoffre(2,60) 
            && gpMonde->motifValue(249*16,60*16)==3187) {
                gpAudio->playSound(20); gpMonde->passage(249,60,0);}
            //torches donne coffre
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getCoffre(2,35) && gpJoueur->getCoffre(2,36) 
            && gpMonde->motifValue(75*16,40*16)==3084) {
                gpAudio->playSound(9);
                if(!gpJoueur->getCoffre(2,13)) 
                    gpMonde->setValeur(75*16,40*16,303,-1,PLEIN,C_CLE);
                else gpMonde->setValeur(75*16,40*16,304,-1,PLEIN,C_RIEN);}
            //torches ouvrent porte
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==15*16 
            && !gpJoueur->getCoffre(2,22) 
            && gpMonde->motifValue(68*16,17*16) == 1001 
            && gpMonde->motifValue(71*16,17*16) == 1001 
            && gpMonde->motifValue(69*16,15*16)==3187) {
                gpAudio->playSound(20); gpMonde->passage(69,15,0);
                gpJoueur->setCoffre(2,22);
                gpMonde->setValeur(75*16,12*16,1005,0);
            }
            break;
        case 49 :
            //mini boss
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==15*16 
            && !gpJoueur->getCoffre(3,27) && gpMonde->motifValue(89*16,28*16)==3385) {
                gpAudio->playSound(20);
                gpAudio->playSpecial(14); gpStatut->setJauge(true);
                gpJoueur->moveY(-16);
                gpMonde->setValeur(89*16, 28*16, 3454, -1, LIBRE, 0);
                gpMonde->setValeur(90*16, 28*16, 3455, -1, LIBRE, 0);
                gpMonde->setValeur(89*16, 29*16, 3456, 0, LIBRE, 0);
                gpMonde->setValeur(90*16, 29*16, 3457, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(89*2+i,28*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(89*2+i,28*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(89*2+i,28*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==15*16 
            && nbEnnemis()==0 && gpMonde->motifValue(89*16,15*16)==3450) {
                gpAudio->playSound(20);
                gpMonde->passage(89,15,0); gpMonde->passage(89,30,0);
                gpJoueur->setCoffre(3,27);
            }
            //boss
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoeur(3)) gpAudio->playSpecial(3);
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoffre(3,29) && gpMonde->motifValue(199*16,43*16)==3454) {
                gpAudio->playSound(20); gpMonde->passage(199,45,0); break;}
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==15*16 
            && !gpJoueur->getCoffre(3,29) && gpMonde->motifValue(199*16,43*16)==3385) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                if (!gpJoueur->getCoeur(3)) {gpAudio->playSpecial(15); gpStatut->setJauge(true);}
                gpMonde->setValeur(199*16, 43*16, 3454, -1, LIBRE, 0);
                gpMonde->setValeur(200*16, 43*16, 3455, -1, LIBRE, 0);
                gpMonde->setValeur(199*16, 44*16, 3456, 0, LIBRE, 0);
                gpMonde->setValeur(200*16, 44*16, 3457, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(199*2+i,43*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(199*2+i,43*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(199*2+i,43*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoeur(3) && gpMonde->motifValue(199*16,15*16)==3450) {
                gpAudio->playSound(20); gpMonde->passage(199,15,0);}
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==140*16 && gpMonde->regionValue(1)==15*16 
            && nbEnnemis()==0 && gpMonde->motifValue(169*16,15*16)==3450) {
                gpAudio->playSound(20); gpMonde->passage(169,15,0);}
            //ennemi vaincu => coffre carte
            if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==60*16 
             && nbEnnemis()==0 && gpMonde->motifValue(103*16,83*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(103*16,83*16,303,-1,PLEIN,C_CARTE_D);
                gpJoueur->setCoffre(3,28);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getY()>82*16) gpJoueur->moveY(82*16-gpJoueur->getY());
            }
            //torches ouvre porte
            if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getCoffre(3,11) && gpJoueur->getCoffre(3,12) 
            && gpMonde->motifValue(120*16,36*16)==3458) {
                gpAudio->playSound(20); gpMonde->passage(120,36,1);}
            //torches ouvre porte
            if (gpMonde->regionValue(0)==220*16 && gpMonde->regionValue(1)==0 
            && gpJoueur->getCoffre(3,19) && gpJoueur->getCoffre(3,20) 
            && gpJoueur->getCoffre(3,21) && gpJoueur->getCoffre(3,22) 
            && gpJoueur->getCoffre(3,23) && gpJoueur->getCoffre(3,24) 
            && gpJoueur->getCoffre(3,25) && gpJoueur->getCoffre(3,26) 
            && gpMonde->motifValue(240*16,6*16)==3458) {
                gpAudio->playSound(20); gpMonde->passage(240,6,1);}
            break;
        case 50 :
            //mini boss
            if (gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==45*16 
            && !gpJoueur->getCoffre(4,38) && gpMonde->motifValue(169*16,58*16)==3622) {
                gpAudio->playSound(20);
                gpAudio->playSpecial(16); gpStatut->setJauge(true);
                gpJoueur->moveY(-16);
                gpMonde->setValeur(169*16, 58*16, 3670, -1, LIBRE, 0);
                gpMonde->setValeur(170*16, 58*16, 3671, -1, LIBRE, 0);
                gpMonde->setValeur(169*16, 59*16, 3672, 0, LIBRE, 0);
                gpMonde->setValeur(170*16, 59*16, 3673, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,58*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,58*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,58*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==45*16 
            && nbEnnemis()==0 && gpMonde->motifValue(169*16,45*16)==3666) {
                gpAudio->playSound(20);
                gpMonde->passage(169,45,0); gpMonde->passage(169,60,0);
                gpJoueur->setCoffre(4,38);
                gpMonde->setValeur(162*16, 47*16, 1001, 1);
                gpMonde->setValeur(177*16, 47*16, 1001, 1);
                gpMonde->setValeur(162*16, 57*16, 1001, 1);
                gpMonde->setValeur(177*16, 57*16, 1001, 1);
            }
            //boss
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoeur(4)) gpAudio->playSpecial(3);
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->hasObjet(O_CLE_TEMPS) && gpMonde->motifValue(249*16,28*16)==3670) {
                gpAudio->playSound(20); gpMonde->passage(249,30,0); break;}
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==15*16 
            && !gpJoueur->hasObjet(O_CLE_TEMPS) && gpMonde->motifValue(249*16,28*16)==3622) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                if (!gpJoueur->getCoeur(4)) {gpAudio->playSpecial(17); gpStatut->setJauge(true);}
                gpMonde->setValeur(249*16, 28*16, 3670, -1, LIBRE, 0);
                gpMonde->setValeur(250*16, 28*16, 3671, -1, LIBRE, 0);
                gpMonde->setValeur(249*16, 29*16, 3672, 0, LIBRE, 0);
                gpMonde->setValeur(250*16, 29*16, 3673, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(249*2+i,28*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(249*2+i,28*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(249*2+i,28*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoeur(4) && gpMonde->motifValue(249*16,15*16)==3666) {
                gpAudio->playSound(20); gpMonde->passage(249,15,0);
                gpMonde->setValeur(242*16, 17*16, 1001, 1);
                gpMonde->setValeur(257*16, 17*16, 1001, 1);
                gpMonde->setValeur(242*16, 27*16, 1001, 1);
                gpMonde->setValeur(257*16, 27*16, 1001, 1);
            }
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==15*16 
            && !gpJoueur->getCoeur(4) && gpMonde->motifValue(242*16,17*16)==1001
            && gpMonde->motifValue(257*16,17*16)==1001
            && gpMonde->motifValue(242*16,27*16)==1001
            && gpMonde->motifValue(257*16,27*16)==1001) {
                Ennemi* enn = gpEnnemi->getSuivant();
                while (enn != NULL) {
                    if (enn->getEnnId() == 103 && enn->getSpecial(2)>=0) enn->enerve();
                    enn = enn->getSuivant();
                }
            }
            //ennemi vaincu => coffre boussole
            if (gpMonde->regionValue(0)==40*16 && gpMonde->regionValue(1)==30*16 
             && nbEnnemis()==0 && gpMonde->motifValue(49*16,37*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(49*16,37*16,303,-1,PLEIN,C_BOUSSOLE);
                gpJoueur->setCoffre(4,27);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<50*16) gpJoueur->moveX(50*16-gpJoueur->getX());
            }
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==100*16 
            && (gpMonde->regionValue(1)==45*16 || gpMonde->regionValue(1)==60*16)
            && nbEnnemis()==0 && gpMonde->motifValue(109*16,60*16)==3666) {
                gpAudio->playSound(20); gpMonde->passage(109,60,0);}
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==220*16 && gpMonde->regionValue(1)==15*16 
            && nbEnnemis()==0 && gpMonde->motifValue(220*16,21*16)==3674) {
                gpAudio->playSound(20); gpMonde->passage(220,21,1);}
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==45*16 
            && nbEnnemis()==0 && gpMonde->motifValue(29*16,60*16)==3666) {
                gpAudio->playSound(20); gpMonde->passage(29,60,0);}
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==220*16 && gpMonde->regionValue(1)==30*16 
            && nbEnnemis()==0 && gpMonde->motifValue(240*16,36*16)==3674) {
                gpAudio->playSound(20); gpMonde->passage(240,36,1);}
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==220*16 && gpMonde->regionValue(1)==75*16 
            && nbEnnemis()==0 && gpMonde->motifValue(229*16,90*16)==3666) {
                gpAudio->playSound(20); gpMonde->passage(229,90,0);}
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==260*16 && gpMonde->regionValue(1)==75*16 
            && nbEnnemis()==0 && gpMonde->motifValue(269*16,90*16)==3666) {
                gpAudio->playSound(20); gpMonde->passage(269,90,0);}
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==180*16 
            && (gpMonde->regionValue(1)==30*16 || gpMonde->regionValue(1)==45*16)
            && nbEnnemis()==0 && gpMonde->motifValue(189*16,45*16)==3666) {
                gpAudio->playSound(20); gpMonde->passage(189,45,0);}
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==300*16 
            && (gpMonde->regionValue(1)==45*16 || gpMonde->regionValue(1)==60*16)
            && nbEnnemis()==0 && gpMonde->motifValue(309*16,60*16)==3666) {
                gpAudio->playSound(20); gpMonde->passage(309,60,0);}
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==280*16 && gpMonde->regionValue(1)==30*16 
             && nbEnnemis()==0 && gpMonde->motifValue(290*16,37*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(290*16,37*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(4,25);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>289*16) gpJoueur->moveX(289*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==280*16 && gpMonde->regionValue(1)==75*16 
             && nbEnnemis()==0 && gpMonde->motifValue(300*16,90*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(300*16,90*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(4,26);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>299*16) gpJoueur->moveX(299*16-gpJoueur->getX());
            }
            break;
        case 51 :
            //mini boss
            if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==30*16 
            && !gpJoueur->getCoffre(5,24) && gpMonde->motifValue(138*16,36*16)==5054) {
                gpAudio->playSound(20);
                gpAudio->playSpecial(10); gpStatut->setJauge(true);
                gpJoueur->moveX(-16);
                gpMonde->setValeur(138*16, 36*16, 5099, -1, LIBRE, 0);
                gpMonde->setValeur(139*16, 36*16, 5100, -1, LIBRE, 0);
                gpMonde->setValeur(138*16, 37*16, 5101, -1, LIBRE, 0);
                gpMonde->setValeur(139*16, 37*16, 5102, 0, LIBRE, 0);
                gpMonde->setValeur(138*16, 38*16, 5103, -1, LIBRE, 0);
                gpMonde->setValeur(139*16, 38*16, 5104, -1, LIBRE, 0);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(138*2+1,36*2+i,PLEIN);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(138*2+2,36*2+i,GAUCHE);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(138*2+3,36*2+i,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==30*16 
            && nbEnnemis()==0 && gpMonde->motifValue(138*16,36*16)==5099) {
                gpAudio->playSound(20);
                gpMonde->passage(140,36,1); gpMonde->passage(129,30,0);
                gpJoueur->setCoffre(5,24);
            }
            //boss
            if (gpMonde->regionValue(0)==230*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoeur(5)) gpAudio->playSpecial(3);
            if (gpMonde->regionValue(0)==230*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->hasObjet(O_MARTEAU) && gpMonde->motifValue(249*16,43*16)==5089) {
                gpAudio->playSound(20); gpMonde->passage(249,45,0); break;}
            if (gpMonde->regionValue(0)==230*16 && gpMonde->regionValue(1)==15*16 
            && !gpJoueur->hasObjet(O_MARTEAU) && gpMonde->motifValue(249*16,43*16)==5041) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                if (!gpJoueur->getCoeur(5)) {gpAudio->playSpecial(16); gpStatut->setJauge(true);}
                gpMonde->setValeur(249*16, 43*16, 5089, -1, LIBRE, 0);
                gpMonde->setValeur(250*16, 43*16, 5090, -1, LIBRE, 0);
                gpMonde->setValeur(249*16, 44*16, 5091, 0, LIBRE, 0);
                gpMonde->setValeur(250*16, 44*16, 5092, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(249*2+i,43*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(249*2+i,43*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(249*2+i,43*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==230*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoeur(5) && gpMonde->motifValue(249*16,15*16)==5085) {
                gpAudio->playSound(20); gpMonde->passage(249,15,0);}
            //porte se ferme salle piégée 1
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==30*16 
            && gpMonde->motifValue(89*16,58*16)==5041) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                gpMonde->setValeur(89*16, 58*16, 5089, -1, LIBRE, 0);
                gpMonde->setValeur(90*16, 58*16, 5090, -1, LIBRE, 0);
                gpMonde->setValeur(89*16, 59*16, 5091, 0, LIBRE, 0);
                gpMonde->setValeur(90*16, 59*16, 5092, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(89*2+i,58*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(89*2+i,58*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(89*2+i,58*2+3,SEMI_PLEIN);
            }
            //porte se ferme salle piégée 2
            if (gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==30*16 
            && gpMonde->motifValue(169*16,58*16)==5041) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                gpMonde->setValeur(169*16, 58*16, 5089, -1, LIBRE, 0);
                gpMonde->setValeur(170*16, 58*16, 5090, -1, LIBRE, 0);
                gpMonde->setValeur(169*16, 59*16, 5091, 0, LIBRE, 0);
                gpMonde->setValeur(170*16, 59*16, 5092, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,58*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,58*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,58*2+3,SEMI_PLEIN);
            }
            //ennemi vaincu => ouvre porte
            if ((gpMonde->regionValue(0)==40*16 || gpMonde->regionValue(0)==60*16) 
            && gpMonde->regionValue(1)==30*16 
            && nbEnnemis()==0 && gpMonde->motifValue(60*16,36*16)==5093) {
                gpAudio->playSound(20); gpMonde->passage(60,36,1);}
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==100*16 
            && (gpMonde->regionValue(1)==30*16 || gpMonde->regionValue(1)==45*16)
            && nbEnnemis()==0 && gpMonde->motifValue(109*16,45*16)==5085) {
                gpAudio->playSound(20); gpMonde->passage(109,45,0);}
            //ennemi vaincu => coffre boussole
            if (gpMonde->regionValue(0)==140*16 && gpMonde->regionValue(1)==15*16 
             && nbEnnemis()==0 && gpMonde->motifValue(150*16,21*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(150*16,21*16,303,-1,PLEIN,C_BOUSSOLE);
                gpJoueur->setCoffre(5,25);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>149*16) gpJoueur->moveX(149*16-gpJoueur->getX());
            }
            break;
        case 52 :
            //mini boss
            if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==45*16 
            && !gpJoueur->getCoffre(6,22) && !gpAudio->isSpecial()) {
                gpAudio->playSpecial(11); gpStatut->setJauge(true);
            }
            if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==45*16 
            && nbEnnemis()==0 && gpMonde->motifValue(129*16,45*16)==3892) {
                gpAudio->playSound(20);
                if (gpJoueur->getVie()) gpAudio->stopSpecial();
                gpStatut->setJauge(false);
                gpMonde->passage(129,45,0);
                gpMonde->setValeur(130*16,52*16,3980,11);
                gpJoueur->setCoffre(6,22);
            }
            //boss
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getCoeur(6)) gpAudio->playSpecial(3);
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->hasObjet(O_TROC3) && gpMonde->motifValue(249*16,43*16)==3896) {
                gpAudio->playSound(20); gpMonde->passage(249,45,0); break;}
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==30*16 
            && !gpJoueur->hasObjet(O_TROC3) && gpMonde->motifValue(249*16,43*16)==3852) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                if (!gpJoueur->getCoeur(6)) {gpAudio->playSpecial(18); gpStatut->setJauge(true);}
                gpMonde->setValeur(249*16, 43*16, 3896, -1, LIBRE, 0);
                gpMonde->setValeur(250*16, 43*16, 3897, -1, LIBRE, 0);
                gpMonde->setValeur(249*16, 44*16, 3898, 0, LIBRE, 0);
                gpMonde->setValeur(250*16, 44*16, 3899, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(249*2+i,43*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(249*2+i,43*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(249*2+i,43*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getCoeur(6) && gpMonde->motifValue(249*16,30*16)==3892) {
                gpAudio->playSound(20); gpMonde->passage(249,30,0);}
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==30*16 
            && nbEnnemis()==0 && gpMonde->motifValue(248*16,32*16)==3084) {
                gpMonde->setValeur(248*16,32*16,3979,11);
            }
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==15*16 
            && nbEnnemis()==0 && gpMonde->motifValue(100*16,21*16)==3900) {
                gpAudio->playSound(20); gpMonde->passage(100,21,1);}
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==160*16 
            && (gpMonde->regionValue(1)==60*16 || gpMonde->regionValue(1)==75*16)
            && nbEnnemis()==0 && gpMonde->motifValue(169*16,75*16)==3892) {
                gpAudio->playSound(20); gpMonde->passage(169,75,0);}
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==140*16 && gpMonde->regionValue(1)==60*16
            && nbEnnemis()==0 && gpMonde->motifValue(149*16,60*16)==3892) {
                gpAudio->playSound(20); gpMonde->passage(149,60,0);
                gpJoueur->setCoffre(6,16);}
            //ennemi vaincu => coffre carte
            if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==75*16 
             && nbEnnemis()==0 && gpMonde->motifValue(109*16,82*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(109*16,82*16,303,-1,PLEIN,C_CARTE_D);
                gpJoueur->setCoffre(6,19);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<110*16) gpJoueur->moveX(110*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre boussole
            if (gpMonde->regionValue(0)==140*16 && gpMonde->regionValue(1)==75*16 
             && nbEnnemis()==0 && gpMonde->motifValue(150*16,82*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(150*16,82*16,303,-1,PLEIN,C_BOUSSOLE);
                gpJoueur->setCoffre(6,20);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>149*16) gpJoueur->moveX(149*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==60*16 
             && nbEnnemis()==0 && gpMonde->motifValue(90*16,66*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(90*16,66*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(6,21);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>89*16) gpJoueur->moveX(89*16-gpJoueur->getX());
            }
            break;
        case 53 :
            //mini boss
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==15*16 
            && !gpJoueur->getCoffre(7,23) && gpMonde->motifValue(98*16,21*16)==5305) {
                gpAudio->playSound(20);
                gpAudio->playSpecial(19); gpStatut->setJauge(true);
                gpJoueur->moveX(-16);
                gpMonde->setValeur(98*16, 21*16, 5346, -1, LIBRE, 0);
                gpMonde->setValeur(99*16, 21*16, 5347, -1, LIBRE, 0);
                gpMonde->setValeur(98*16, 22*16, 5348, -1, LIBRE, 0);
                gpMonde->setValeur(99*16, 22*16, 5349, 0, LIBRE, 0);
                gpMonde->setValeur(98*16, 23*16, 5350, -1, LIBRE, 0);
                gpMonde->setValeur(99*16, 23*16, 5351, -1, LIBRE, 0);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(98*2+1,21*2+i,PLEIN);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(98*2+2,21*2+i,GAUCHE);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(98*2+3,21*2+i,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==15*16 
            && nbEnnemis()==0 && gpMonde->motifValue(98*16,21*16)==5346) {
                gpAudio->playSound(20);
                gpMonde->passage(100,21,1); gpMonde->passage(89,15,0);
                gpJoueur->setCoffre(7,23);
            }
            //boss
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==75*16
            && !gpJoueur->getCoeur(7) && nbEnnemis() && !gpStatut->getJauge()) {
                gpAudio->playSpecial(20); gpStatut->setJauge(true);}
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==0 
            && gpJoueur->getCoeur(7)) gpAudio->playSpecial(3);
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==0 
            && gpJoueur->hasObjet(O_TROC4) && gpMonde->motifValue(189*16,13*16)==5336) {
                gpAudio->playSound(20); gpMonde->passage(189,15,0); break;}
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==0 
            && !gpJoueur->hasObjet(O_TROC4) && gpMonde->motifValue(189*16,13*16)==5292) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                if (gpJoueur->getCoeur(7)) gpAudio->playSpecial(3);
                gpMonde->setValeur(189*16, 13*16, 5336, -1, LIBRE, 0);
                gpMonde->setValeur(190*16, 13*16, 5337, -1, LIBRE, 0);
                gpMonde->setValeur(189*16, 14*16, 5338, 0, LIBRE, 0);
                gpMonde->setValeur(190*16, 14*16, 5339, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(189*2+i,13*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(189*2+i,13*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(189*2+i,13*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==0 
            && gpJoueur->getCoeur(7) && gpMonde->motifValue(200*16,6*16)==5340) {
                gpAudio->playSound(20); gpMonde->passage(200,6,1);}
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==75*16 
            && gpJoueur->getCoeur(7) && gpMonde->motifValue(192*16,85*16)==3416)
                gpMonde->setValeur(192*16, 85*16, 3417, LIBRE);
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==60*16 
            && (gpMonde->regionValue(1)==30*16 || gpMonde->regionValue(1)==45*16)
            && nbEnnemis()==0 && gpMonde->motifValue(69*16,45*16)==5332) {
                gpAudio->playSound(20); gpMonde->passage(69,45,0);}
            //ennemi vaincu => ouvre porte
            if ((gpMonde->regionValue(0)==100*16 || gpMonde->regionValue(0)==120*16)
            && gpMonde->regionValue(1)==105*16
            && nbEnnemis()==0 && gpMonde->motifValue(120*16,111*16)==5340) {
                gpAudio->playSound(20); gpMonde->passage(120,111,1);}
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==220*16 && gpMonde->regionValue(1)==45*16
            && nbEnnemis()==0 && gpMonde->motifValue(229*16,45*16)==5332) {
                gpAudio->playSound(20); gpMonde->passage(229,45,0);
                gpJoueur->setCoffre(7,21);}
            //ennemi vaincu => coffre carte
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==60*16 
             && nbEnnemis()==0 && gpMonde->motifValue(89*16,67*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(89*16,67*16,303,-1,PLEIN,C_CARTE_D);
                gpJoueur->setCoffre(7,24);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<90*16) gpJoueur->moveX(90*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==30*16 
             && nbEnnemis()==0 && gpMonde->motifValue(9*16,37*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(9*16,37*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(7,25);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<10*16) gpJoueur->moveX(10*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==140*16 && gpMonde->regionValue(1)==30*16 
             && nbEnnemis()==0 && gpMonde->motifValue(149*16,37*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(149*16,37*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(7,26);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<150*16) gpJoueur->moveX(150*16-gpJoueur->getX());
            }
            break;
        case 54 :
            //mini boss
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==0 
            && !gpJoueur->getCoffre(8,23) && gpMonde->motifValue(60*16,6*16)==5491) {
                gpAudio->playSound(20);
                gpAudio->playSpecial(12); gpStatut->setJauge(true);
                gpJoueur->moveX(16);
                gpMonde->setValeur(60*16, 6*16, 5533, -1, LIBRE, 0);
                gpMonde->setValeur(61*16, 6*16, 5534, -1, LIBRE, 0);
                gpMonde->setValeur(60*16, 7*16, 5535, -1, LIBRE, 0);
                gpMonde->setValeur(61*16, 7*16, 5536, 0, LIBRE, 0);
                gpMonde->setValeur(60*16, 8*16, 5537, -1, LIBRE, 0);
                gpMonde->setValeur(61*16, 8*16, 5538, -1, LIBRE, 0);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(60*2,6*2+i,SEMI_PLEIN);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(60*2+1,6*2+i,DROITE);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(60*2+2,6*2+i,PLEIN);
            }
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==0 
            && nbEnnemis()==0 && gpMonde->motifValue(60*16,6*16)==5533) {
                gpAudio->playSound(20);
                gpMonde->passage(60,6,1); gpMonde->passage(80,6,1);
                gpJoueur->setCoffre(8,23);
            }
            //boss
            if (gpMonde->regionValue(0)==190*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoeur(8)) gpAudio->playSpecial(3);
            if (gpMonde->regionValue(0)==190*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->hasObjet(O_TROC2) && gpMonde->motifValue(199*16,28*16)==5529) {
                gpAudio->playSound(20); gpMonde->passage(199,30,0); break;}
            if (gpMonde->regionValue(0)==190*16 && gpMonde->regionValue(1)==15*16 
            && !gpJoueur->hasObjet(O_TROC2) && gpMonde->motifValue(199*16,28*16)==5485) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                if (!gpJoueur->getCoeur(8)) {gpAudio->playSpecial(21); gpStatut->setJauge(true);}
                gpMonde->setValeur(199*16, 28*16, 5529, -1, LIBRE, 0);
                gpMonde->setValeur(200*16, 28*16, 5530, -1, LIBRE, 0);
                gpMonde->setValeur(199*16, 29*16, 5531, 0, LIBRE, 0);
                gpMonde->setValeur(200*16, 29*16, 5532, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(199*2+i,28*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(199*2+i,28*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(199*2+i,28*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==190*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoeur(8) && gpMonde->motifValue(199*16,15*16)==5525) {
                gpAudio->playSound(20); gpMonde->passage(199,15,0);}
            //ennemi vaincu => coffre carte
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==30*16 
             && nbEnnemis()==0 && gpMonde->motifValue(71*16,45*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(71*16,45*16,303,-1,PLEIN,C_CARTE_D);
                gpJoueur->setCoffre(8,53);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<72*16) gpJoueur->moveX(72*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==0 
             && nbEnnemis()==0 && gpMonde->motifValue(29*16,7*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(29*16,7*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(8,42);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<30*16) gpJoueur->moveX(30*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==140*16 && gpMonde->regionValue(1)==0 
             && nbEnnemis()==0 && gpMonde->motifValue(150*16,6*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(150*16,6*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(8,44);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>149*16) gpJoueur->moveX(149*16-gpJoueur->getX());
            }
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==75*16
            && nbEnnemis()==0 && gpMonde->motifValue(249*16,75*16)==5525) {
                gpAudio->playSound(20); gpMonde->passage(249,75,0);}
            //puzzles caisses à 0
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==75*16 
            && gpMonde->motifValue(100*16,81*16)==5533) {
                Caisse* caisse = gpCaisse->getSuivant();
                int total = 0;
                while (caisse != NULL) {
                    if (caisse->isActif() && caisse->getNombre()==0) {
                        if ((caisse->getX()/16==88 && caisse->getY()/16==83)
                        || (caisse->getX()/16==89 && caisse->getY()/16==84)
                        || (caisse->getX()/16==91 && caisse->getY()/16==82)) total++;
                    }
                    caisse = caisse->getSuivant();
                }
                if (total == 3) {
                    gpAudio->playSound(20); 
                    gpMonde->passage(100,81,1); 
                    gpJoueur->setCoffre(8,21);
                }
            }
            //puzzles caisses à 0
            if (gpMonde->regionValue(0)==220*16 && gpMonde->regionValue(1)==45*16 
            && gpMonde->motifValue(229*16,60*16)==5525) {
                Caisse* caisse = gpCaisse->getSuivant();
                int total = 0;
                while (caisse != NULL) {
                    if (caisse->isActif() && caisse->getNombre()==0) {
                        if ((caisse->getX()/16==228 && caisse->getY()/16==51)
                        || (caisse->getX()/16==228 && caisse->getY()/16==53)
                        || (caisse->getX()/16==231 && caisse->getY()/16==51)) total++;
                    }
                    caisse = caisse->getSuivant();
                }
                if (total == 3) {
                    gpAudio->playSound(20); 
                    gpMonde->passage(229,60,0); 
                    gpJoueur->setCoffre(8,47);
                }
            }
            //éteint torches => coffre clé
            if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==15*16 
             && gpMonde->motifValue(47*16,20*16)==1000 && gpMonde->motifValue(53*16,20*16)==1000
             && gpMonde->motifValue(50*16,20*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(50*16,20*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(8,35);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>49*16) gpJoueur->moveX(49*16-gpJoueur->getX());
            }
            //éteint torches => coffre clé
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==0 
             && gpMonde->motifValue(247*16,17*16)==1000 && gpMonde->motifValue(251*16,17*16)==1000
             && gpMonde->motifValue(249*16,17*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(249*16,17*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(8,45);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<250*16) gpJoueur->moveX(250*16-gpJoueur->getX());
            }
            //éteint torches ouvre porte
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==30*16 
             && gpMonde->motifValue(182*16,50*16)==1000 && gpMonde->motifValue(182*16,54*16)==1000
             && gpMonde->motifValue(180*16,51*16)==5533) {
                gpAudio->playSound(20); gpMonde->passage(180,51,1);
                gpJoueur->setCoffre(8,41);
            }
            //éteint torches ouvre porte
            if (gpMonde->regionValue(0)==240*16 && gpMonde->regionValue(1)==30*16 
             && gpMonde->motifValue(248*16,37*16)==1000 && gpMonde->motifValue(251*16,37*16)==1000
             && gpMonde->motifValue(249*16,30*16)==5525) {
                gpAudio->playSound(20); gpMonde->passage(249,30,0);
                gpJoueur->setCoffre(8,51);
            }
            //éteint torches ouvre porte
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==30*16 
             && gpMonde->motifValue(80*16,45*16)==1000
             && gpMonde->motifValue(79*16,30*16)==5525) {
                gpAudio->playSound(20); gpMonde->passage(79,30,0);
                gpJoueur->setCoffre(8,24);
            }
            //éteint torches ouvre porte
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==0 
             && gpMonde->motifValue(97*16,2*16)==1000 && gpMonde->motifValue(97*16,12*16)==1000
             && gpMonde->motifValue(100*16,6*16)==5533) {
                gpAudio->playSound(20); gpMonde->passage(100,6,1);
                gpJoueur->setCoffre(8,52);
            }
            //torches ouvre porte
            if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==60*16 
            && gpMonde->motifValue(102*16,71*16)==1001 && gpMonde->motifValue(115*16,62*16)==1001 
            && gpMonde->motifValue(127*16,62*16)==1001 && gpMonde->motifValue(135*16,62*16)==1001 
            && gpMonde->motifValue(133*16,76*16)==1001 && gpMonde->motifValue(107*16,80*16)==1001 
            && gpMonde->motifValue(102*16,86*16)==1001 && gpMonde->motifValue(107*16,86*16)==1001 
            && gpMonde->motifValue(130*16,86*16)==1001 && gpMonde->motifValue(135*16,83*16)==1001 
            && gpMonde->motifValue(129*16,60*16)==5525) {
                gpAudio->playSound(20); gpMonde->passage(129,60,0);
                gpJoueur->setCoffre(8,55);
            }
            break;
        case 55 :
            //mini boss
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==150*16 
            && !gpJoueur->getCoffre(9,16) && gpMonde->motifValue(60*16,156*16)==5680) {
                gpAudio->playSound(20);
                gpAudio->playSpecial(22); gpStatut->setJauge(true);
                gpJoueur->moveX(16);
                gpMonde->setValeur(60*16, 156*16, 5722, -1, LIBRE, 0);
                gpMonde->setValeur(61*16, 156*16, 5723, -1, LIBRE, 0);
                gpMonde->setValeur(60*16, 157*16, 5724, -1, LIBRE, 0);
                gpMonde->setValeur(61*16, 157*16, 5725, 0, LIBRE, 0);
                gpMonde->setValeur(60*16, 158*16, 5726, -1, LIBRE, 0);
                gpMonde->setValeur(61*16, 158*16, 5727, -1, LIBRE, 0);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(60*2,156*2+i,SEMI_PLEIN);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(60*2+1,156*2+i,DROITE);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(60*2+2,156*2+i,PLEIN);
            }
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==150*16 
            && nbEnnemis()==0 && gpMonde->motifValue(60*16,156*16)==5722) {
                gpAudio->playSound(20);
                gpMonde->passage(60,156,1); gpMonde->passage(80,156,1);
                gpJoueur->setCoffre(9,16);
            }
            //boss
            if (gpMonde->regionValue(0)==40*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoeur(9) && gpJoueur->getX()>66*16 && gpJoueur->getX()<74*16
            && gpJoueur->getY()>30*16) gpAudio->playSpecial(3);
            if (gpMonde->regionValue(0)==40*16 && gpMonde->regionValue(1)==165*16 
            && gpJoueur->hasObjet(O_TROC1) && gpMonde->motifValue(70*16,197*16)==5869) {
                gpMonde->setValeur(70*16,197*16,5878,11); break;}
            if (gpMonde->regionValue(0)==40*16 && gpMonde->regionValue(1)==15*16 
            && !gpJoueur->hasObjet(O_TROC1) && gpJoueur->getX()>66*16 && gpJoueur->getX()<74*16
            && gpJoueur->getY()>30*16 && gpMonde->motifValue(69*16,58*16)==5674) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                gpMonde->setValeur(69*16, 58*16, 5718, -1, LIBRE, 0);
                gpMonde->setValeur(70*16, 58*16, 5719, -1, LIBRE, 0);
                gpMonde->setValeur(69*16, 59*16, 5720, 0, LIBRE, 0);
                gpMonde->setValeur(70*16, 59*16, 5721, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(69*2+i,58*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(69*2+i,58*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(69*2+i,58*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==40*16 && gpMonde->regionValue(1)==15*16 
            && !gpJoueur->hasObjet(O_TROC1) && gpJoueur->getX()>60*16 && gpJoueur->getX()<80*16
            && gpJoueur->getY()>30*16 && gpJoueur->getY()<45*16 && !gpJoueur->getCoeur(9)
            && !gpAudio->isSpecial()) {
                gpAudio->playSpecial(23); gpStatut->setJauge(true);
                gpJoueur->moveY(-16);
                gpJoueur->saveSemiEmpl();
                setStop(true);
            }
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getCoeur(9) && gpMonde->motifValue(65*16,38*16)==3416) {
                gpMonde->passage(69,60,0); gpMonde->setValeur(65*16, 38*16, 3417, 0, LIBRE, 0);}
            //ennemi vaincu => coffre carte
            if (gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==30*16 
             && nbEnnemis()==0 && gpMonde->motifValue(9*16,36*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(9*16,36*16,303,-1,PLEIN,C_CARTE_D);
                gpJoueur->setCoffre(9,55);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<10*16) gpJoueur->moveX(10*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==40*16 && gpMonde->regionValue(1)==0 
             && nbEnnemis()==0 && gpMonde->motifValue(50*16,6*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(50*16,6*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(9,56);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>49*16) gpJoueur->moveX(49*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==0 
             && nbEnnemis()==0 && gpMonde->motifValue(69*16,6*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(69*16,6*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(9,57);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<70*16) gpJoueur->moveX(70*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==0 
             && nbEnnemis()==0 && gpMonde->motifValue(89*16,6*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(89*16,6*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(9,58);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<90*16) gpJoueur->moveX(90*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre boussole
            if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==180*16 
             && nbEnnemis()==0 && gpMonde->motifValue(110*16,186*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(110*16,186*16,303,-1,PLEIN,C_BOUSSOLE);
                gpJoueur->setCoffre(9,59);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>109*16) gpJoueur->moveX(109*16-gpJoueur->getX());
            }
            //torches ouvre porte
            if (gpMonde->regionValue(0)==40*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoffre(9,23) && gpJoueur->getCoffre(9,24)
            && !gpJoueur->getCoffre(9,13)) {
                gpAudio->playSound(20); gpMonde->passage(49,60,0); gpJoueur->setCoffre(9,13);}
            //torches ouvre porte
            if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==0 
            && gpJoueur->getCoffre(9,25) && gpJoueur->getCoffre(9,26)
            && gpJoueur->getCoffre(9,27) && gpJoueur->getCoffre(9,28)
            && gpJoueur->getCoffre(9,29) && gpJoueur->getCoffre(9,30)
            && !gpJoueur->getCoffre(9,18)) {
                gpAudio->playSound(20); gpMonde->passage(100,6,1); gpJoueur->setCoffre(9,18);}
            //torches ouvre porte
            if (gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==90*16 
            && gpJoueur->getCoffre(9,31) && gpJoueur->getCoffre(9,32)
            && !gpJoueur->getCoffre(9,11)) {
                gpAudio->playSound(20); gpMonde->passage(29,105,0); gpJoueur->setCoffre(9,11);}
            //torches ouvre porte
            if (gpMonde->regionValue(0)==40*16 && gpMonde->regionValue(1)==90*16 
            && gpJoueur->getCoffre(9,33) && gpJoueur->getCoffre(9,34)
            && gpJoueur->getCoffre(9,35) && gpJoueur->getCoffre(9,36)
            && gpJoueur->getCoffre(9,37) && gpJoueur->getCoffre(9,38)
            && gpJoueur->getCoffre(9,39) && gpJoueur->getCoffre(9,40)
            && gpJoueur->getCoffre(9,41) && gpJoueur->getCoffre(9,42)
            && !gpJoueur->getCoffre(9,15)) {
                gpAudio->playSound(20); gpMonde->passage(69,90,0); gpJoueur->setCoffre(9,15);}
            //torches ouvre porte
            if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==120*16 
            && gpJoueur->getCoffre(9,43) && gpJoueur->getCoffre(9,44)
            && gpJoueur->getCoffre(9,45) && gpJoueur->getCoffre(9,46)
            && !gpJoueur->getCoffre(9,19)) {
                gpAudio->playSound(20); gpMonde->passage(100,126,1); gpJoueur->setCoffre(9,19);}
            //torches ouvre porte
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==150*16 
            && gpJoueur->getCoffre(9,47) && gpJoueur->getCoffre(9,48)
            && !gpJoueur->getCoffre(9,20)) {
                gpAudio->playSound(20); gpMonde->passage(100,156,1); gpJoueur->setCoffre(9,20);}
            //torches ouvre porte
            if (gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==195*16 
            && gpJoueur->getCoffre(9,49) && gpJoueur->getCoffre(9,50)
            && gpJoueur->getCoffre(9,51) && gpJoueur->getCoffre(9,52)
            && gpJoueur->getCoffre(9,53) && gpJoueur->getCoffre(9,54)
            && !gpJoueur->getCoffre(9,12)) {
                gpAudio->playSound(20); gpMonde->passage(40,201,1); gpJoueur->setCoffre(9,12);}
            break;
        case 56 :
            //mini boss
            if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==90*16 
            && !gpJoueur->getCoffre(10,11) && gpMonde->motifValue(118*16,96*16)==5933) {
                gpAudio->playSound(20);
                gpAudio->playSpecial(19); gpStatut->setJauge(true);
                gpJoueur->moveX(-16);
                gpMonde->setValeur(118*16, 96*16, 5974, -1, LIBRE, 0);
                gpMonde->setValeur(119*16, 96*16, 5975, -1, LIBRE, 0);
                gpMonde->setValeur(118*16, 97*16, 5976, -1, LIBRE, 0);
                gpMonde->setValeur(119*16, 97*16, 5977, 0, LIBRE, 0);
                gpMonde->setValeur(118*16, 98*16, 5978, -1, LIBRE, 0);
                gpMonde->setValeur(119*16, 98*16, 5979, -1, LIBRE, 0);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(118*2+1,96*2+i,PLEIN);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(118*2+2,96*2+i,GAUCHE);
                for (int i = 0; i < 6; i++) gpMonde->setMurs(118*2+3,96*2+i,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==90*16 
            && nbEnnemis()==0 && gpMonde->motifValue(118*16,96*16)==5974) {
                gpAudio->playSound(20);
                gpMonde->passage(100,96,1); gpMonde->passage(120,96,1);
                gpJoueur->setCoffre(10,11);
            }
            //boss
            if (gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoeur(10)) gpAudio->playSpecial(3);
            if (gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getEpee()>=5 && gpMonde->motifValue(169*16,28*16)==5964) {
                gpAudio->playSound(20); gpMonde->passage(169,30,0); break;}
            if (gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getEpee()<5 && gpMonde->motifValue(169*16,28*16)==5920) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                if (!gpJoueur->getCoeur(10)) {gpAudio->playSpecial(24); gpStatut->setJauge(true);}
                gpMonde->setValeur(169*16, 28*16, 5964, -1, LIBRE, 0);
                gpMonde->setValeur(170*16, 28*16, 5965, -1, LIBRE, 0);
                gpMonde->setValeur(169*16, 29*16, 5966, 0, LIBRE, 0);
                gpMonde->setValeur(170*16, 29*16, 5967, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,28*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,28*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,28*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getCoeur(10) && gpMonde->motifValue(169*16,15*16)==5960) {
                gpAudio->playSound(20); gpMonde->passage(169,15,0);}
            //ennemi vaincu => coffre carte
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==45*16 
             && nbEnnemis()==0 && gpMonde->motifValue(90*16,51*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(90*16,51*16,303,-1,PLEIN,C_CARTE_D);
                gpJoueur->setCoffre(10,14);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>89*16) gpJoueur->moveX(89*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre boussole
            if (gpMonde->regionValue(0)==140*16 && gpMonde->regionValue(1)==0 
             && nbEnnemis()==0 && gpMonde->motifValue(149*16,6*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(149*16,6*16,303,-1,PLEIN,C_BOUSSOLE);
                gpJoueur->setCoffre(10,16);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<150*16) gpJoueur->moveX(150*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==15*16 
             && nbEnnemis()==0 && gpMonde->motifValue(30*16,21*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(30*16,21*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(10,13);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>29*16) gpJoueur->moveX(29*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==15*16 
             && nbEnnemis()==0 && gpMonde->motifValue(109*16,21*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(109*16,21*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(10,15);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()<110*16) gpJoueur->moveX(110*16-gpJoueur->getX());
            }
            //ennemi vaincu => coffre clé
            if (gpMonde->regionValue(0)==180*16 && gpMonde->regionValue(1)==0 
             && nbEnnemis()==0 && gpMonde->motifValue(190*16,6*16)==3084) {
                gpAudio->playSound(9);
                gpMonde->setValeur(190*16,6*16,303,-1,PLEIN,C_CLE);
                gpJoueur->setCoffre(10,17);
                if (!verifZoneJoueur(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16, 2)
                && gpJoueur->getX()>189*16) gpJoueur->moveX(189*16-gpJoueur->getX());
            }
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==30*16
            && nbEnnemis()==0 && gpMonde->motifValue(40*16,36*16)==5968) {
                gpAudio->playSound(20); gpMonde->passage(40,36,1); 
                gpJoueur->setCoffre(10,8);}
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==30*16
            && nbEnnemis()==0 && gpMonde->motifValue(89*16,30*16)==5960) {
                gpAudio->playSound(20); gpMonde->passage(89,30,0); 
                gpJoueur->setCoffre(10,18);}
            break;
        case 57 :
            if (gpJoueur->getEpee() < 5) return;
            //mini boss
            if (gpMonde->regionValue(0)==40*16 && gpMonde->regionValue(1)==225*16 
            && !gpJoueur->getCoffre(11,7) && gpMonde->motifValue(49*16,238*16)==6160) {
                gpAudio->playSound(20);
                gpAudio->playSpecial(26); gpStatut->setJauge(true);
                gpJoueur->moveY(-16);
                gpMonde->setValeur(49*16, 238*16, 6196, -1, LIBRE, 0);
                gpMonde->setValeur(50*16, 238*16, 6197, -1, LIBRE, 0);
                gpMonde->setValeur(49*16, 239*16, 6198, 0, LIBRE, 0);
                gpMonde->setValeur(50*16, 239*16, 6199, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(49*2+i,238*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(49*2+i,238*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(49*2+i,238*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==40*16 && gpMonde->regionValue(1)==225*16 
            && nbEnnemis()==0 && gpMonde->motifValue(49*16,238*16)==6196) {
                gpAudio->playSound(20);
                gpMonde->passage(49,240,0); gpMonde->passage(40,231,1); gpMonde->passage(60,231,1);
                gpJoueur->setCoffre(11,7);
            }
            //boss
            if (gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==15*16 
            && !gpJoueur->getEnnemi(50) && gpMonde->motifValue(169*16,28*16)==6036) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                gpAudio->playSpecial(4); gpStatut->setJauge(true);
                gpMonde->setValeur(169*16, 28*16, 6080, -1, LIBRE, 0);
                gpMonde->setValeur(170*16, 28*16, 6081, -1, LIBRE, 0);
                gpMonde->setValeur(169*16, 29*16, 6082, 0, LIBRE, 0);
                gpMonde->setValeur(170*16, 29*16, 6083, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,28*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,28*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,28*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==15*16 
            && gpJoueur->getEnnemi(50) && gpMonde->motifValue(169*16,15*16)==6076) {
                gpAudio->playSound(20); gpMonde->passage(169,15,0);}
            //boss final
            if (gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(1)==0 
            && gpJoueur->getAvancement()>=SPEECH_GANONDORF 
            && gpMonde->motifValue(169*16,13*16)==6036) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                gpAudio->playSpecial(27); gpStatut->setJauge(true);
                gpMonde->setValeur(169*16, 13*16, 6080, -1, LIBRE, 0);
                gpMonde->setValeur(170*16, 13*16, 6081, -1, LIBRE, 0);
                gpMonde->setValeur(169*16, 14*16, 6082, 0, LIBRE, 0);
                gpMonde->setValeur(170*16, 14*16, 6083, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,13*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,13*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(169*2+i,13*2+3,SEMI_PLEIN);
            }
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==150*16
            && nbEnnemis()==0 && gpMonde->motifValue(80*16,156*16)==6200) {
                gpAudio->playSound(20); gpMonde->passage(80,156,1); 
                gpJoueur->setCoffre(11,8);}
            //ennemi vaincu => ouvre porte
            if (gpMonde->regionValue(0)==80*16 && gpMonde->regionValue(1)==165*16
            && nbEnnemis()==0 && gpMonde->motifValue(89*16,180*16)==6192) {
                gpAudio->playSound(20); gpMonde->passage(89,180,0); 
                gpJoueur->setCoffre(11,9);}
            break;
        case 58 :
            //boss
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getCoeur(11)) gpAudio->playSpecial(3);
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getBouclier()>=4 && gpMonde->motifValue(69*16,43*16)==6422) {
                gpAudio->playSound(20); gpMonde->passage(69,45,0); break;}
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getBouclier()<4 && gpMonde->motifValue(69*16,43*16)==6386) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                if (!gpJoueur->getCoeur(11)) {gpAudio->playSpecial(28); gpStatut->setJauge(true);}
                gpMonde->setValeur(69*16, 43*16, 6422, -1, LIBRE, 0);
                gpMonde->setValeur(70*16, 43*16, 6423, -1, LIBRE, 0);
                gpMonde->setValeur(69*16, 44*16, 6424, 0, LIBRE, 0);
                gpMonde->setValeur(70*16, 44*16, 6425, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(69*2+i,43*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(69*2+i,43*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(69*2+i,43*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getCoeur(11) && gpMonde->motifValue(69*16,30*16)==6418) {
                gpAudio->playSound(20); gpMonde->passage(69,30,0);}
            //puzzles caisses à 0
            if (gpMonde->regionValue(0)==120*16 && gpMonde->regionValue(1)==75*16
            && gpJoueur->getCoffre(12,13) == 1) {
                int nb = 0;
                Ennemi* enn = gpEnnemi->getSuivant();
                while (enn != NULL) {
                    if (enn->isActif() && enn->getEnnId()==125 && enn->getSpecial(2) == 0) 
                        return;
                    enn = enn->getSuivant();
                }
                
                nb=0;
                Caisse* caisse = gpCaisse->getSuivant();
                while (caisse != NULL) {
                    if (caisse->isActif()) {
                        if (caisse->getNombre() == 0) {
                            nb++;
                            if (caisse->getX()/16!=135) gpJoueur->setCoffre(12,13,3);
                            if (caisse->getY()/16<83 || caisse->getY()/16>85) 
                                gpJoueur->setCoffre(12,13,3);
                        } else return;
                    }
                    if (nb == 3 && gpJoueur->getCoffre(12,13) != 3) 
                        gpJoueur->setCoffre(12,13,2);
                    caisse = caisse->getSuivant();
                }
            }
            break;
        case 59 :
            //boss
            if (gpMonde->regionValue(0)==270*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getCoeur(12)) gpAudio->playSpecial(3);
            if (gpMonde->regionValue(0)==270*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getTunique()>=4 && gpMonde->motifValue(279*16,43*16)==6572) {
                gpAudio->playSound(20); gpMonde->passage(279,45,0); break;}
            if (gpMonde->regionValue(0)==270*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getTunique()<4 && gpMonde->motifValue(279*16,43*16)==6542) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                if (!gpJoueur->getCoeur(12)) {gpAudio->playSpecial(19); gpStatut->setJauge(true);}
                gpMonde->setValeur(279*16, 43*16, 6572, -1, LIBRE, 0);
                gpMonde->setValeur(280*16, 43*16, 6573, -1, LIBRE, 0);
                gpMonde->setValeur(279*16, 44*16, 6574, 0, LIBRE, 0);
                gpMonde->setValeur(280*16, 44*16, 6575, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(279*2+i,43*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(279*2+i,43*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(279*2+i,43*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(0)==270*16 && gpMonde->regionValue(1)==30*16 
            && gpJoueur->getCoeur(12) && gpMonde->motifValue(279*16,30*16)==6568) {
                gpAudio->playSound(20); gpMonde->passage(279,30,0);}
            break;
        case 60 :
            //boss final
            if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==75*16 
            && gpMonde->motifValue(69*16,88*16)==6689) {
                gpAudio->playSound(20); gpJoueur->moveY(-16);
                gpAudio->stopMusic();
                gpMonde->setValeur(69*16, 88*16, 6733, -1, LIBRE, 0);
                gpMonde->setValeur(70*16, 88*16, 6734, -1, LIBRE, 0);
                gpMonde->setValeur(69*16, 89*16, 6735, 0, LIBRE, 0);
                gpMonde->setValeur(70*16, 89*16, 6736, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(69*2+i,88*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(69*2+i,88*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(69*2+i,88*2+3,SEMI_PLEIN);
                ecrit(1343);
            }
            break;
        case 137 :
            if (gpMonde->regionValue(1)<30*16 && gpJoueur->hasCristal(3)) gpAudio->playSpecial(3);
            if (gpMonde->regionValue(1)==15*16 
            && gpJoueur->hasCristal(3) && gpMonde->motifValue(9*16,28*16)==2286) {
                gpAudio->playSound(20); gpMonde->passage(9,30,0); break;}
            if (gpMonde->regionValue(1)==15*16 
            && !gpJoueur->hasCristal(3) && gpMonde->motifValue(9*16,28*16)==2244) {
                gpAudio->playSound(20); 
                ecrit(799); gpAudio->playSpecial(4); gpStatut->setJauge(true);
                gpJoueur->moveY(-16);
                gpMonde->setValeur(9*16, 28*16, 2286, -1, LIBRE, 0);
                gpMonde->setValeur(10*16, 28*16, 2287, -1, LIBRE, 0);
                gpMonde->setValeur(9*16, 29*16, 2288, 0, LIBRE, 0);
                gpMonde->setValeur(10*16, 29*16, 2289, 0, LIBRE, 0);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(9*2+i,28*2+1,PLEIN);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(9*2+i,28*2+2,HAUT);
                for (int i = 0; i < 4; i++) gpMonde->setMurs(9*2+i,28*2+3,SEMI_PLEIN);
            }
            if (gpMonde->regionValue(1)==15*16 && nbEnnemis()==0 
            && gpMonde->motifValue(9*16,15*16)==2282) {
                gpAudio->playSound(20); gpMonde->passage(9,15,0);}
            break;
    }
}

void Jeu::testTapis() {
    gpJoueur->testTapis();
    gpEnnemi->testTapis();
}

void Jeu::teleporte(int tel) {
    switch (tel) {
        case 0 : newx=16*39+8; newy=16*14; newzone=8; break;
        case 1 : newx=16*84; newy=16*12; newzone=7; break;    
        case 2 : newx=16*62+8; newy=16*15; newzone=6; break;    
        case 3 : newx=16*42+8; newy=16*38; newzone=13; break;
        case 4 : newx=16*39+8; newy=16*42; newzone=1; break;
        case 5 : newx=16*39+8; newy=16*53; newzone=3; break;
        case 6 : newx=16*45; newy=16*40; newzone=12; break;
        case 7 : newx=16*72+8; newy=16*60; newzone=11; break;
        case 8 : newx=16*50; newy=16*31; newzone=10; break;
        default : return;
    }
    newzone+=15*getEpoque();
    newdir=S;
    //gpJoueur->setDirection(S);
    finZone();
}

int Jeu::getEpoque() {
    if (isDehors()) return (zone-1)/15;
    if (zone == 58) return T_FUTUR;
    if (isGrotte()) {
        if (zone < 70) return T_PRESENT;
        if (zone < 74) return T_FUTUR;
        return T_PASSE;
    }
    if (isDonjon()) {
        if (zone > 48 && zone < 51) return T_FUTUR;
        if (zone > 51 && zone < 57) return T_PASSE;
        if (zone > 57 && zone < 60) return T_FUTUR;
        return T_PRESENT;
    }
    if ((zone > 78 && zone < 112) || (zone > 149 && zone < 152)) return T_PRESENT;
    if ((zone > 111 && zone < 124) || zone == 152 || zone == 155) return T_FUTUR;
    if ((zone > 123 && zone < 150) || (zone > 152 && zone < 155)) return T_PASSE;
    return T_PRESENT;
}

void Jeu::finZone() {
    gpJoueur->setX(newx);
    gpJoueur->setY(newy);
    if (newdir!=-1) gpJoueur->setDirection((Direction)newdir);
    gpJoueur->saveSemiEmpl();
    if (zone != newzone) {
        if (gpJoueur->isCompteurVisible() && !isDonjon()) {
            gpJoueur->setCompteurVisible(false);
            gpJoueur->setCompteur(0);
        }
        gpJoueur->saveEmpl();
        videListes();
        zone = newzone;
        if (isDonjon() && !gpJoueur->getCharge() && !(zone==51 && newx>300*16) 
        && !(zone>=56 && zone<=58 && (newy<15*16 || newy>195*16))) 
            gpJoueur->setDirection(N);
        /*if (zone==2 && newx==16*14+8 && newy==16*25) gpJoueur->setDirection(S);
        if (zone==5 && newx==16*42+8 && newy==16*73) gpJoueur->setDirection(S);
        if (zone==5 && newx==16*53+8 && newy==16*72) gpJoueur->setDirection(S);
        if (zone==6 && newx==16*89+8 && newy==16*26) gpJoueur->setDirection(S);
        if (zone==8 && newx==16*26+8 && newy==16*17) gpJoueur->setDirection(S);
        if (zone==14 && newx==16*13+8 && newy==16*51) gpJoueur->setDirection(S);
        if (zone==33 && newy==120) gpJoueur->setDirection(S);
        if (zone==37 && newy==136) gpJoueur->setDirection(S);
        if (zone==38 && newy==136) gpJoueur->setDirection(S);
        if (zone==40) gpJoueur->setDirection(S);
        if (zone==43 && newy==88) gpJoueur->setDirection(S);*/
        
        /*if (isDehors() && gpJoueur->getAvancement()<67 && gpJoueur->hasObjet(O_MASQUE)==2) 
            ecrit(192);*/
        if (zone==16 && gpJoueur->getAvancement()==DEPART) ecrit(46);
        
        if (zone > 0) gpMonde->changeZone(zone);
        if (isDonjon()) ecrit(927+zone-46);
        else if (zone==57) ecrit(1036);
        if (gpJoueur->getAvancement() == INFO_PASSE_OK && isDehors()) ecrit(762);
        if ((zone == 18 || zone == 19) && 
        ((gpJoueur->getEpee()==0 && !gpJoueur->hasObjet(O_OCARINA)) 
        || (gpJoueur->getEpee()==5 && zone == 19 
        && !gpJoueur->getEnnemi(50)))) 
            gpAudio->playMusic(218);
        else if (zone == 137 && gpJoueur->nbCristaux()>=3 && gpJoueur->hasObjet(O_TROC4)>=6 
        && !gpJoueur->hasCristal(3)) gpAudio->playMusic(218);
        else if (zone == 4 && gpJoueur->getCoffre(15,2)) gpAudio->playMusic(219);
        else if (/*isDehors() && */gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_UTILISE
        && gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_FERME
        && getEpoque()==T_PRESENT) gpAudio->playMusic(199);
        else if (zone==10 && gpJoueur->nbCristaux()>=3 && gpJoueur->hasObjet(O_TROC4)>=6
        && !gpJoueur->hasCristal(3)) gpAudio->playMusic(218);
        else if ((zone == 111 || zone == 114 || zone == 124) 
        && gpJoueur->nbEnnemis() >= 87) gpAudio->playMusic(218);
        else if (zone > 0) gpAudio->playMusic(zone);
        if (zone == 19 && gpJoueur->getEpee()==5 && gpAudio->isSpecial()) {
            gpAudio->stopSpecial();
        }
    } else gpMonde->detRegion(zone);
    
    //if (zone==28 && newx==16*149+8 && newy==16*113) gpJoueur->setDirection(N);
    
    if (gpJoueur->getTypeAnim()==EMMENE) gpJoueur->setTypeAnim(MARCHE);
    gpJoueur->visible();
    scrolling();
}

void Jeu::testFin() {
    if (transition) return;
    //si peut ramasser un objet
    testRamasse(gpJoueur->getX(), gpJoueur->getY()+8, 16, 16);
    //si dans l'eau
    if (isWater(gpJoueur->getX(), gpJoueur->getY()+8, 16,16)) {
        gpJoueur->bigPlouf();
    }else {
        gpJoueur->antiPlouf();
        if (gpJoueur->getTypeAnim()==FLOTTE || gpJoueur->getTypeAnim()==NAGE) 
            gpJoueur->setTypeAnim(AUCUNE);
    }
    //si tombe dans le vide
    if (isVide(gpJoueur->getX(), gpJoueur->getY()+8, 16,16)) {
        gpAudio->playSound(12);
        gpJoueur->setTypeAnim(CHUTE);
    }
    switch(zone) {
        case 1 :
            if (gpJoueur->getX()>320*3+16*18+8) 
                gpMonde->transitZone(2, 4, 0, E);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(13, 0, -5, N);
            if (((int)(gpJoueur->getX()/16))==59 && ((int)((gpJoueur->getY()-8)/16))==9)
                gpMonde->transitFull(75, 152, 200);
            if (((int)(gpJoueur->getX()/16))==39 && ((int)((gpJoueur->getY()-8)/16))==39)
                gpMonde->transitFull(126, 152, 200);
            break;
        case 2 :
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(1, -4, 0, O);
            if (gpJoueur->getX()>320*2+16*18+8) 
                gpMonde->transitZone(3, 3, -2, E);
            if (gpJoueur->getY()>240*3+16*13+8-4) 
                gpMonde->transitZone(12, -4, 4, S);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(14, 0, -5, N);
            break;
        case 3 :
            if (((int)(gpJoueur->getX()/16))==63 && ((int)((gpJoueur->getY()-8)/16))==31)
                gpMonde->transitFull(128, 152, 200);
            if (((int)(gpJoueur->getX()/16))==63 && ((int)((gpJoueur->getY()-8)/16))==42)
                gpMonde->transitFull(129, 152, 200);
            if (((int)(gpJoueur->getX()/16))==15 && ((int)((gpJoueur->getY()-8)/16))==58)
                gpMonde->transitFull(130, 152, 200);
            if (((int)(gpJoueur->getX()/16))==49 && ((int)((gpJoueur->getY()-8)/16))==58)
                gpMonde->transitFull(131, 152, 200);
            if (((int)(gpJoueur->getX()/16))==63 && ((int)((gpJoueur->getY()-8)/16))==58)
                gpMonde->transitFull(132, 152, 200);
            if (((int)(gpJoueur->getX()/16))==29 && ((int)((gpJoueur->getY()-8)/16))==74)
                gpMonde->transitFull(133, 152, 200);
            if (((int)(gpJoueur->getX()/16))==49 && ((int)((gpJoueur->getY()-8)/16))==74)
                gpMonde->transitFull(134, 152, 200);
            if (((int)(gpJoueur->getX()/16))==63 && ((int)((gpJoueur->getY()-8)/16))==74)
                gpMonde->transitFull(135, 152, 200);
            if (((int)(gpJoueur->getX()/16))==17 && ((int)((gpJoueur->getY()-8)/16))==36)
                gpMonde->transitFull(136, 152, 440);
            if (gpJoueur->getAvancement()<INFO_PASSE_OK) {
                if (gpJoueur->getX()<6) {
                    ecrit(749); gpJoueur->setX(gpJoueur->getX()+4); gpJoueur->setDirection(E);}
                if (gpJoueur->getY()<6) {
                    ecrit(749); gpJoueur->setY(gpJoueur->getY()+4); gpJoueur->setDirection(S);}
                if (gpJoueur->getX()>320*3+16*18+8) {
                    ecrit(749); gpJoueur->setX(gpJoueur->getX()-4); gpJoueur->setDirection(O);}
                if (gpJoueur->getY()>240*5+16*13+8-4) {
                    ecrit(749); gpJoueur->setY(gpJoueur->getY()-4); gpJoueur->setDirection(N);}
                return;
            }
            if (gpJoueur->getX()<6 && gpJoueur->getY()>=240*2) 
                gpMonde->transitZone(2, -3, 2, O);
            if (gpJoueur->getX()<6 && gpJoueur->getY()<240*2) 
                gpMonde->transitZone(14, -3, -3, O);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(4, 0, -4, N);
            if (gpJoueur->getX()>320*3+16*18+8 && gpJoueur->getY()<240*2) 
                gpMonde->transitZone(5, 4, -4, E);
            if (gpJoueur->getX()>320*3+16*18+8 && gpJoueur->getY()>=240*2) 
                gpMonde->transitZone(9, 4, 2, E);
            if (gpJoueur->getY()>240*5+16*13+8-4) 
                gpMonde->transitZone(11, 0, 6, S);
            break;
        case 4 :
            if ((gpJoueur->getX()/16==39 || gpJoueur->getX()/16==40) 
            && (gpJoueur->getY())/16==36 
            && gpJoueur->nbCristaux()==7 && !gpJoueur->getCoffre(15,2)) {
                gpAudio->stopMusic(); SDL_Delay(1500);
                ecrit(194);
            }
            if (gpJoueur->getY()>240*3+16*13+8-4) 
                gpMonde->transitZone(3, 0, 4, S);
            if (gpJoueur->getX()>320*3+16*18+8) 
                gpMonde->transitZone(5, 4, 0, E);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(8, 0, -3, N);
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(14, -3, 1, O);
            if (gpJoueur->getCoffre(15,2)) {
            if ((((int)(gpJoueur->getX()/16))==39 || ((int)(gpJoueur->getX()/16))==40) 
            && ((int)((gpJoueur->getY()-8)/16))==33)
                gpMonde->transitFull(56, 152+320*3, 200+240*3);
            if ((((int)(gpJoueur->getX()/16))==39 || ((int)(gpJoueur->getX()/16))==40) 
            && ((int)((gpJoueur->getY()-8)/16))==28)
                gpMonde->transitFull(56, 152+320*8, 200+240*2);
            if (((int)(gpJoueur->getX()/16))==53 && ((int)(gpJoueur->getY()/16))==26) {
                gpAudio->playSound(11); gpMonde->transitFull(56, 152+320*5, 120,S);}
            }
            break;
        case 5 :
            if (gpJoueur->getX()<6 && gpJoueur->getY()>=240*4) 
                gpMonde->transitZone(3, -4, 4, O);
            if (gpJoueur->getX()<6 && gpJoueur->getY()<240*4) 
                gpMonde->transitZone(4, -4, 0, O);
            if (gpJoueur->getX()>320*2+16*18+8) 
                gpMonde->transitZone(6, 3, 0, E);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(7, 0, -3, N);
            if (gpJoueur->getY()>240*5+16*13+8-4) 
                gpMonde->transitZone(9, 0, 6, S);
            break;
        case 6 :
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(5, -3, 0, O);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(7, -3, -3, N);
            if (gpJoueur->getY()>240*5+16*13+8-4) 
                gpMonde->transitZone(9, -3, 6, S);
            if (((int)(gpJoueur->getX()/16))==65 && ((int)((gpJoueur->getY()-8)/16))==79)
                gpMonde->transitFull(77, 152, 200);
            if (((int)(gpJoueur->getX()/16))==15 && ((int)((gpJoueur->getY()-8)/16))==9)
                gpMonde->transitFull(78, 152+320*3, 200);
            if (((int)(gpJoueur->getX()/16))==27 && ((int)((gpJoueur->getY()-8)/16))==9)
                gpMonde->transitFull(78, 152+320*5, 200);
            break;
        case 7 :
            if (gpJoueur->getY()>240*2+16*13+8-4 && gpJoueur->getX()<320*3) 
                gpMonde->transitZone(5, 0, 3, S);
            if (gpJoueur->getY()>240*2+16*13+8-4 && gpJoueur->getX()>=320*3) 
                gpMonde->transitZone(6, 3, 3, S);
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(8, -4, 0, O);
            if (((int)(gpJoueur->getX()/16))==10 && ((int)((gpJoueur->getY()-8)/16))==3)
                gpMonde->transitFull(74, 152, 200);
            if (((int)(gpJoueur->getX()/16))==84 && ((int)((gpJoueur->getY()-8)/16))==6)
                gpMonde->transitFull(53, 152+320, 200+240*3);
            break;
        case 8 :
            if (gpJoueur->getY()>240*2+16*13+8-4) 
                gpMonde->transitZone(4, 0, 3, S);
            if (gpJoueur->getX()>320*3+16*18+8) 
                gpMonde->transitZone(7, 4, 0, E);
            if (((int)(gpJoueur->getX()/16))==39 && ((int)((gpJoueur->getY()-8)/16))==10)
                gpMonde->transitFull(124, 152, 200);
            break;
        case 9 :
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(3, -4, -2, O);
            if (gpJoueur->getY()<6 && gpJoueur->getX()<3*320) 
                gpMonde->transitZone(5, 0, -6, N);
            if (gpJoueur->getY()<6 && gpJoueur->getX()>=3*320) 
                gpMonde->transitZone(6, 3, -6, N);
            if (gpJoueur->getY()>240*3+16*13+8-4 && gpJoueur->getX()>=3*320) 
                gpMonde->transitZone(10, 3, 4, S);
            if (gpJoueur->getY()>240*3+16*13+8-4 && gpJoueur->getX()<3*320) 
                gpMonde->transitZone(11, -4, 4, S);
            if (((int)(gpJoueur->getX()/16))==113 && ((int)((gpJoueur->getY()-8)/16))==34)
                gpMonde->transitFull(154, 152, 200+240);
            if (((int)(gpJoueur->getX()/16))==129 && ((int)((gpJoueur->getY()-8)/16))==37) {
                gpAudio->playSound(11); gpMonde->transitFull(154, 152+320*3, 120+240,S);}
            break;
        case 10 :
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(9, -3, -4, N);
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(11, -7, 0, O);
            if (((int)(gpJoueur->getX()/16))==37 && ((int)((gpJoueur->getY()-8)/16))==7)
                gpMonde->transitFull(137, 152, 200+240*4);
            if (((int)(gpJoueur->getX()/16))==31 && ((int)((gpJoueur->getY()-8)/16))==22)
                gpMonde->transitFull(138, 152, 200);
            if (((int)(gpJoueur->getX()/16))==43 && ((int)((gpJoueur->getY()-8)/16))==24)
                gpMonde->transitFull(139, 152, 200);
            if (((int)(gpJoueur->getX()/16))==30 && ((int)((gpJoueur->getY()-8)/16))==37)
                gpMonde->transitFull(140, 152, 200);
            if (((int)(gpJoueur->getX()/16))==47 && ((int)((gpJoueur->getY()-8)/16))==40)
                gpMonde->transitFull(141, 152, 200);
            if (((int)(gpJoueur->getX()/16))==62 && ((int)((gpJoueur->getY()-8)/16))==32)
                gpMonde->transitFull(142, 152, 200);
            if (((int)(gpJoueur->getX()/16))==65 && ((int)((gpJoueur->getY()-8)/16))==47)
                gpMonde->transitFull(143, 152, 200);
            break;
        case 11 :
            if (gpJoueur->getY()<6 && gpJoueur->getX()<4*320) 
                gpMonde->transitZone(3, 0, -6, N);
            if (gpJoueur->getY()<6 && gpJoueur->getX()>=4*320) 
                gpMonde->transitZone(9, 4, -4, N);
            if (gpJoueur->getX()>320*6+16*18+8) 
                gpMonde->transitZone(10, 7, 0, E);
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(12, -7, 0, O);
            if (((int)(gpJoueur->getX()/16))==72 && ((int)((gpJoueur->getY()-8)/16))==41)
                gpMonde->transitFull(127, 152, 200);
            if (((int)(gpJoueur->getX()/16))==72 && ((int)((gpJoueur->getY()-8)/16))==50)
                gpMonde->transitFull(54, 152, 200+240*2);
            break;
        case 12 :
            if (gpJoueur->getY()<6 && gpJoueur->getX()>=4*320) 
                gpMonde->transitZone(2, 4, -4, N);
            if (gpJoueur->getX()>320*6+16*18+8) 
                gpMonde->transitZone(11, 7, 0, E);
            if (((int)(gpJoueur->getX()/16))==84 && ((int)((gpJoueur->getY()-8)/16))==55)
                gpMonde->transitFull(76, 152, 200);
            if ((((int)(gpJoueur->getX()/16))==15 || ((int)(gpJoueur->getX()/16))==16) 
            && ((int)(gpJoueur->getY()/16))==20)
                gpMonde->transitFull(52, 152+320*6, 200+240*5);
            break;
        case 13 :
            if (gpJoueur->getY()>240*4+16*13+8-4) 
                gpMonde->transitZone(1, 0, 5, S);
            if (gpJoueur->getX()>320*3+16*18+8) 
                gpMonde->transitZone(14, 4, 0, E);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(15, 0, -4, N);
            if (((int)(gpJoueur->getX()/16))==15 && ((int)((gpJoueur->getY()-8)/16))==14)
                gpMonde->transitFull(144, 152, 200);
            if (((int)(gpJoueur->getX()/16))==21 && ((int)((gpJoueur->getY()-8)/16))==14)
                gpMonde->transitFull(144, 472, 200);
            if (((int)(gpJoueur->getX()/16))==18 && ((int)((gpJoueur->getY()-8)/16))==34)
                gpMonde->transitFull(145, 152, 200);
            if (((int)(gpJoueur->getX()/16))==13 && ((int)((gpJoueur->getY()-8)/16))==46)
                gpMonde->transitFull(146, 152, 200);
            if (((int)(gpJoueur->getX()/16))==42 && ((int)((gpJoueur->getY()-8)/16))==20)
                gpMonde->transitFull(147, 152, 200);
            if (((int)(gpJoueur->getX()/16))==61 && ((int)((gpJoueur->getY()-8)/16))==33)
                gpMonde->transitFull(148, 152, 200);
            if (((int)(gpJoueur->getX()/16))==61 && ((int)((gpJoueur->getY()-8)/16))==43)
                gpMonde->transitFull(149, 152, 200);
            break;
        case 14 :
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(13, -4, 0, O);
            if (gpJoueur->getX()>320*2+16*18+8 && gpJoueur->getY()<3*240) 
                gpMonde->transitZone(4, 3, -1, E);
            if (gpJoueur->getX()>320*2+16*18+8 && gpJoueur->getY()>=3*240) 
                gpMonde->transitZone(3, 3, 3, E);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(15, -4, -4, N);
            if (gpJoueur->getY()>240*4+16*13+8-4) 
                gpMonde->transitZone(2, 0, 5, S);
            if (((int)(gpJoueur->getX()/16))==18 && ((int)((gpJoueur->getY()-8)/16))==40)
                gpMonde->transitFull(125, 152, 200);
            if ((((int)(gpJoueur->getX()/16))==34 || ((int)(gpJoueur->getX()/16))==35) 
            && ((int)((gpJoueur->getY()-8)/16))==51)
                gpMonde->transitFull(153, 152+320, 200+240*2);
            break;
        case 15 :
            if (gpJoueur->getY()>240*3+16*13+8-4 && gpJoueur->getX()<4*240) 
                gpMonde->transitZone(13, 0, 4, S);
            if (((int)(gpJoueur->getX()/16))==122 && ((int)(gpJoueur->getY()/16))==33)
                gpMonde->transitFull(55, 152+320*3, 200+240*14);
            break;
        case 16 :
            if (gpJoueur->getY()>45*16-4 && !gpJoueur->getAvancement()) {
                ecrit(45); gpJoueur->setY(gpJoueur->getY()-4); gpJoueur->setDirection(N);
            }
            if (gpJoueur->getX()>320*3+16*18+8) 
                gpMonde->transitZone(17, 4, 0, E);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(28, 0, -5, N);
            if (((int)(gpJoueur->getX()/16))==59 && ((int)((gpJoueur->getY()-8)/16))==9)
                gpMonde->transitFull(61, 152, 200);
            if (((int)(gpJoueur->getX()/16))==39 && ((int)((gpJoueur->getY()-8)/16))==39)
                gpMonde->transitFull(79, 152, 200);
            break;
        case 17 :
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(16, -4, 0, O);
            if (gpJoueur->getX()>320*2+16*18+8) 
                gpMonde->transitZone(18, 3, -2, E);
            if (gpJoueur->getY()>240*3+16*13+8-4) 
                gpMonde->transitZone(27, -4, 4, S);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(29, 0, -5, N);
            break;
        case 18 :
            if (gpJoueur->getX()<6 && gpJoueur->getY()>240*2) 
                gpMonde->transitZone(17, -3, 2, O);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(19, 0, -4, N);
            if (gpJoueur->getX()>320*3+16*18+8 && gpJoueur->getY()<240*2) 
                gpMonde->transitZone(20, 4, -4, E);
            if (gpJoueur->getX()>320*3+16*18+8 && gpJoueur->getY()>=240*2) 
                gpMonde->transitZone(24, 4, 2, E);
            if (gpJoueur->getY()>240*5+16*13+8-4) 
                gpMonde->transitZone(26, 0, 6, S);
            if (((int)(gpJoueur->getX()/16))==17 && ((int)((gpJoueur->getY()-8)/16))==36)
                gpMonde->transitFull(80, 152, 440);
            if (((int)(gpJoueur->getX()/16))==17 && ((int)((gpJoueur->getY()-8)/16))==31)
                gpMonde->transitFull(80, 152, 8);
            if (((int)(gpJoueur->getX()/16))==63 && ((int)((gpJoueur->getY()-8)/16))==32)
                gpMonde->transitFull(81, 152, 200);
            if (((int)(gpJoueur->getX()/16))==63 && ((int)((gpJoueur->getY()-8)/16))==43)
                gpMonde->transitFull(82, 152, 200);
            if (((int)(gpJoueur->getX()/16))==15 && ((int)((gpJoueur->getY()-8)/16))==58)
                gpMonde->transitFull(83, 152, 200);
            if (((int)(gpJoueur->getX()/16))==49 && ((int)((gpJoueur->getY()-8)/16))==59)
                gpMonde->transitFull(84, 152, 200);
            if (((int)(gpJoueur->getX()/16))==63 && ((int)((gpJoueur->getY()-8)/16))==59)
                gpMonde->transitFull(85, 152, 200);
            if (((int)(gpJoueur->getX()/16))==15 && ((int)((gpJoueur->getY()-8)/16))==75)
                gpMonde->transitFull(86, 152, 200);
            if (((int)(gpJoueur->getX()/16))==29 && ((int)((gpJoueur->getY()-8)/16))==75)
                gpMonde->transitFull(87, 152, 200);
            if (((int)(gpJoueur->getX()/16))==49 && ((int)((gpJoueur->getY()-8)/16))==75)
                gpMonde->transitFull(88, 152, 200);
            if (((int)(gpJoueur->getX()/16))==63 && ((int)((gpJoueur->getY()-8)/16))==75)
                gpMonde->transitFull(89, 152, 200);
            /*if (((int)(gpJoueur->getX()/16))==17 && ((int)((gpJoueur->getY()-8)/16))==31
            && gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_UTILISE
            && gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_FERME) {
                gpJoueur->setDirection(N); gpJoueur->setY(gpJoueur->getY()-4); ecrit(366);
            }*/
            if (gpJoueur->getAvancement()==PLANCHES_TROUVEES && gpJoueur->getY()-8<16*5) 
                ecrit(341);
            break;
        case 19 :
            if (gpJoueur->getY()>240*3+16*13+8-4) 
                gpMonde->transitZone(18, 0, 4, S);
            if (gpJoueur->getX()>320*3+16*18+8) 
                gpMonde->transitZone(20, 4, 0, E);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(23, 0, -3, N);
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(29, -3, 1, O);
            if ((((int)(gpJoueur->getX()/16))==39 || ((int)(gpJoueur->getX()/16))==40) 
            && ((int)((gpJoueur->getY()-8)/16))==33)
                gpMonde->transitFull(57, 152+320*3, 200+240*3);
            if ((((int)(gpJoueur->getX()/16))==39 || ((int)(gpJoueur->getX()/16))==40) 
            && ((int)((gpJoueur->getY()-8)/16))==28)
                gpMonde->transitFull(57, 152+320*8, 200+240*2);
            if (((int)(gpJoueur->getX()/16))==53 && ((int)(gpJoueur->getY()/16))==26) {
                gpAudio->playSound(11); gpMonde->transitFull(57, 152+320*5, 120,S);}
            if (((int)(gpJoueur->getX()/16))==68 && ((int)((gpJoueur->getY()-8)/16))==47) {
                gpAudio->playSound(11); gpMonde->transitFull(57, 152+320*7, 120+240*13,S);}
            break;
        case 20 :
            if (gpJoueur->getX()<6 && gpJoueur->getY()>=240*4) 
                gpMonde->transitZone(18, -4, 4, O);
            if (gpJoueur->getX()<6 && gpJoueur->getY()<240*4) 
                gpMonde->transitZone(19, -4, 0, O);
            if (gpJoueur->getX()>320*2+16*18+8) 
                gpMonde->transitZone(21, 3, 0, E);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(22, 0, -3, N);
            if (gpJoueur->getY()>240*5+16*13+8-4) 
                gpMonde->transitZone(24, 0, 6, S);
            break;
        case 21 :
            if (gpJoueur->getCoffre(15,27)<15 && gpJoueur->hasObjet(O_TROC3)==8) {
                gpJoueur->setCoffre(15,27,15);
                zone=20; gpMonde->transitTemps(21,gpJoueur->getX(),gpJoueur->getY());}
            if (gpJoueur->getX()<6) {
                if (!gpJoueur->hasObjet(O_CARTE)) {
                    ecrit(1033); gpJoueur->setX(gpJoueur->getX()+4); gpJoueur->setDirection(E);
                } else gpMonde->transitZone(20, -3, 0, O);
            }
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(22, -3, -3, N);
            if (gpJoueur->getY()>240*5+16*13+8-4) 
                gpMonde->transitZone(24, -3, 6, S);
            if (((int)(gpJoueur->getX()/16))==65 && ((int)((gpJoueur->getY()-8)/16))==79)
                gpMonde->transitFull(62, 152, 200);
            if (((int)(gpJoueur->getX()/16))==15 && ((int)((gpJoueur->getY()-8)/16))==9)
                gpMonde->transitFull(63, 152+320*3, 200);
            if (((int)(gpJoueur->getX()/16))==27 && ((int)((gpJoueur->getY()-8)/16))==9)
                gpMonde->transitFull(63, 152+320*4, 200);
            if (((int)(gpJoueur->getX()/16))==62 && ((int)((gpJoueur->getY()-8)/16))==12
            && (gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_UTILISE
            || gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_FERME))
                gpMonde->transitFull(64, 152, 200);
            if (((int)(gpJoueur->getX()/16))==62 && ((int)((gpJoueur->getY()-8)/16))==12
            && gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_UTILISE
            && gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_FERME)
                gpMonde->transitFull(69, 152, 200);
            if ((((int)(gpJoueur->getX()/16))==16 || ((int)(gpJoueur->getX()/16))==17) 
            && ((int)((gpJoueur->getY()-8)/16))==67 && gpJoueur->getCoffre(15,27)<15)
                gpMonde->transitFull(150, 152+320*4, 200+240*2);
            break;
        case 22 :
            if (gpJoueur->getY()>240*2+16*13+8-4 && gpJoueur->getX()<320*3) 
                gpMonde->transitZone(20, 0, 3, S);
            if (gpJoueur->getY()>240*2+16*13+8-4 && gpJoueur->getX()>=320*3) 
                gpMonde->transitZone(21, 3, 3, S);
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(23, -4, 0, O);
            if (((int)(gpJoueur->getX()/16))==10 && ((int)((gpJoueur->getY()-8)/16))==3)
                gpMonde->transitFull(65, 152, 200);
            if (((int)(gpJoueur->getX()/16))==18 && ((int)((gpJoueur->getY()-8)/16))==28
            && (gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_UTILISE
            || gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_FERME))
                gpMonde->transitFull(90, 152, 200);
            if (((int)(gpJoueur->getX()/16))==18 && ((int)((gpJoueur->getY()-8)/16))==28
            && gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_UTILISE
            && gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_FERME) {
                gpJoueur->setDirection(S); gpJoueur->setY(gpJoueur->getY()+4); ecrit(366);}
            if (((int)(gpJoueur->getX()/16))==50 && ((int)(gpJoueur->getY()/16))==33
            && (gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_UTILISE
            || gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_FERME))
                gpMonde->transitFull(91, 152, 200);
            if (((int)(gpJoueur->getX()/16))==50 && ((int)(gpJoueur->getY()/16))==33
            && gpJoueur->getAvancement()>=PORTAIL_PRE_PRESENT_UTILISE
            && gpJoueur->getAvancement()<PORTAIL_PRE_PRESENT_FERME) {
                gpJoueur->setDirection(S); gpJoueur->setY(gpJoueur->getY()+4); ecrit(366);}
            if (((int)(gpJoueur->getX()/16))==112 && ((int)((gpJoueur->getY()-8)/16))==16)
                gpMonde->transitFull(92, 152, 200);
            if (((int)(gpJoueur->getX()/16))==84 && ((int)((gpJoueur->getY()-8)/16))==6)
                gpMonde->transitFull(46, 152+320*5, 200+240*3);
            break;
        case 23 :
            if (gpJoueur->getY()>240*2+16*13+8-4) 
                gpMonde->transitZone(19, 0, 3, S);
            if (gpJoueur->getX()>320*3+16*18+8) 
                gpMonde->transitZone(22, 4, 0, E);
            if (((int)(gpJoueur->getX()/16))==58 && ((int)((gpJoueur->getY()-8)/16))==17)
                gpMonde->transitFull(66, 152, 200);
            if (((int)(gpJoueur->getX()/16))==39 && ((int)((gpJoueur->getY()-8)/16))==10)
                gpMonde->transitFull(111, 152, 200);
            break;
        case 24 :
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(18, -4, -2, O);
            if (gpJoueur->getY()<6 && gpJoueur->getX()<3*320) 
                gpMonde->transitZone(20, 0, -6, N);
            if (gpJoueur->getY()<6 && gpJoueur->getX()>=3*320) 
                gpMonde->transitZone(21, 3, -6, N);
            if (gpJoueur->getY()>240*3+16*13+8-4 && gpJoueur->getX()>=3*320) 
                gpMonde->transitZone(25, 3, 4, S);
            if (gpJoueur->getY()>240*3+16*13+8-4 && gpJoueur->getX()<3*320) 
                gpMonde->transitZone(26, -4, 4, S);
            break;
        case 25 :
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(24, -3, -4, N);
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(26, -7, 0, O);
            if (((int)(gpJoueur->getX()/16))==37 && ((int)((gpJoueur->getY()-8)/16))==8)
                gpMonde->transitFull(93, 152, 200);
            if (((int)(gpJoueur->getX()/16))==31 && ((int)((gpJoueur->getY()-8)/16))==23)
                gpMonde->transitFull(94, 152, 200);
            if (((int)(gpJoueur->getX()/16))==43 && ((int)((gpJoueur->getY()-8)/16))==25)
                gpMonde->transitFull(95, 152, 200);
            if (((int)(gpJoueur->getX()/16))==30 && ((int)((gpJoueur->getY()-8)/16))==38)
                gpMonde->transitFull(96, 152, 200);
            if (((int)(gpJoueur->getX()/16))==47 && ((int)((gpJoueur->getY()-8)/16))==41)
                gpMonde->transitFull(97, 152, 200);
            if (((int)(gpJoueur->getX()/16))==65 && ((int)((gpJoueur->getY()-8)/16))==21)
                gpMonde->transitFull(98, 152, 200);
            if (((int)(gpJoueur->getX()/16))==62 && ((int)((gpJoueur->getY()-8)/16))==33)
                gpMonde->transitFull(99, 152, 200);
            if (((int)(gpJoueur->getX()/16))==65 && ((int)((gpJoueur->getY()-8)/16))==48)
                gpMonde->transitFull(100, 152, 200);
            break;
        case 26 :
            if (gpJoueur->getY()<6 && gpJoueur->getX()<4*320) 
                gpMonde->transitZone(18, 0, -6, N);
            if (gpJoueur->getY()<6 && gpJoueur->getX()>=4*320) 
                gpMonde->transitZone(24, 4, -4, N);
            if (gpJoueur->getX()>320*6+16*18+8) 
                gpMonde->transitZone(25, 7, 0, E);
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(27, -7, 0, O);
            if (((int)(gpJoueur->getX()/16))==120 && ((int)((gpJoueur->getY()-8)/16))==35)
                gpMonde->transitFull(101, 152, 200);
            if (((int)(gpJoueur->getX()/16))==72 && ((int)((gpJoueur->getY()-8)/16))==40)
                gpMonde->transitFull(47, 152+320*5, 200+240*2);
            if (((int)(gpJoueur->getX()/16))==50 && ((int)((gpJoueur->getY()-8)/16))==25)
                gpMonde->transitFull(47, 152+320*3, 200);
            if (((int)(gpJoueur->getX()/16))==32 && ((int)((gpJoueur->getY()-8)/16))==46)
                gpMonde->transitFull(47, 152+320, 200+240*4);
            break;
        case 27 :
            if (gpJoueur->getY()<6 && gpJoueur->getX()>=4*320) 
                gpMonde->transitZone(17, 4, -4, N);
            if (gpJoueur->getX()>320*6+16*18+8) 
                gpMonde->transitZone(26, 7, 0, E);
            if (((int)(gpJoueur->getX()/16))==84 && ((int)((gpJoueur->getY()-8)/16))==55)
                gpMonde->transitFull(67, 152+320*3, 200+240);
            if ((((int)(gpJoueur->getX()/16))==15 || ((int)(gpJoueur->getX()/16))==16) 
            && ((int)(gpJoueur->getY()/16))==20)
                gpMonde->transitFull(51, 152+320*6, 200+240*5);
            break;
        case 28 :
            if (gpJoueur->getY()>240*4+16*13+8-4) 
                gpMonde->transitZone(16, 0, 5, S);
            if (gpJoueur->getX()>320*3+16*18+8) 
                gpMonde->transitZone(29, 4, 0, E);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(30, 0, -4, N);
            if (((int)(gpJoueur->getX()/16))==15 && ((int)((gpJoueur->getY()-8)/16))==15)
                gpMonde->transitFull(102, 152, 200);
            if (((int)(gpJoueur->getX()/16))==21 && ((int)((gpJoueur->getY()-8)/16))==15)
                gpMonde->transitFull(102, 472, 200);
            if (((int)(gpJoueur->getX()/16))==24 && ((int)((gpJoueur->getY()-8)/16))==24)
                gpMonde->transitFull(103, 152, 200);
            if (((int)(gpJoueur->getX()/16))==18 && ((int)((gpJoueur->getY()-8)/16))==34)
                gpMonde->transitFull(104, 152, 200);
            if (((int)(gpJoueur->getX()/16))==13 && ((int)((gpJoueur->getY()-8)/16))==46)
                gpMonde->transitFull(105, 152, 200);
            if (((int)(gpJoueur->getX()/16))==42 && ((int)((gpJoueur->getY()-8)/16))==20)
                gpMonde->transitFull(106, 152, 200);
            if (((int)(gpJoueur->getX()/16))==61 && ((int)((gpJoueur->getY()-8)/16))==33)
                gpMonde->transitFull(107, 152, 200);
            if (((int)(gpJoueur->getX()/16))==61 && ((int)((gpJoueur->getY()-8)/16))==43)
                gpMonde->transitFull(108, 152, 200);
            break;
        case 29 :
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(28, -4, 0, O);
            if (gpJoueur->getX()>320*2+16*18+8 && gpJoueur->getY()<3*240) 
                gpMonde->transitZone(19, 3, -1, E);
            if (gpJoueur->getY()>240*4+16*13+8-4) 
                gpMonde->transitZone(17, 0, 5, S);
            if (((int)(gpJoueur->getX()/16))==18 && ((int)((gpJoueur->getY()-8)/16))==41)
                gpMonde->transitFull(109, 152, 200);
            if (((int)(gpJoueur->getX()/16))==45 && ((int)((gpJoueur->getY()-8)/16))==42)
                gpMonde->transitFull(110, 152, 200);
            if ((((int)(gpJoueur->getX()/16))==34 || ((int)(gpJoueur->getX()/16))==35) 
            && ((int)((gpJoueur->getY()-8)/16))==51)
                gpMonde->transitFull(151, 152+320, 200+240*2);
            break;
        case 30 :
            if (gpJoueur->getY()>240*3+16*13+8-4 && gpJoueur->getX()<4*240) 
                gpMonde->transitZone(28, 0, 4, S);
            if (((int)(gpJoueur->getX()/16))==25 && ((int)((gpJoueur->getY()-8-8)/16))==39) {
                if (!gpJoueur->getCoffre(15,11) && gpJoueur->getPosWagon() == 2) {
                    gpJoueur->setPosWagon(0);
                }
                gpMonde->transitFull(68, 152, 200+240*2);
            }
            if (((int)(gpJoueur->getX()/16))==45 && ((int)((gpJoueur->getY()-8-8)/16))==31)
                gpMonde->transitFull(68, 152+320+160, 200+240*2);
            if (((int)(gpJoueur->getX()/16))==23 && ((int)((gpJoueur->getY()-8-8)/16))==32)
                gpMonde->transitFull(68, 152+320*4, 200+240*2);
            if (((int)(gpJoueur->getX()/16))==53 && ((int)((gpJoueur->getY()-8)/16))==30) {
                gpAudio->playSound(11);
                gpMonde->transitFull(68, 152+320*3, 120+240, S);}
            if (((int)(gpJoueur->getX()/16))==122 && ((int)((gpJoueur->getY()-8)/16))==34)
                gpMonde->transitFull(48, 152+320*3, 200+240*4);
            break;
        case 31 :
            if (gpJoueur->getX()>320*3+16*18+8) 
                gpMonde->transitZone(32, 4, 0, E);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(43, 0, -5, N);
            if (((int)(gpJoueur->getX()/16))==59 && ((int)((gpJoueur->getY()-8)/16))==9)
                gpMonde->transitFull(71, 152, 200);
            if (((int)(gpJoueur->getX()/16))==39 && ((int)((gpJoueur->getY()-8)/16))==39)
                gpMonde->transitFull(116, 152, 200);
            break;
        case 32 :
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(31, -4, 0, O);
            if (gpJoueur->getX()>320*2+16*18+8) 
                gpMonde->transitZone(33, 3, -2, E);
            if (gpJoueur->getY()>240*3+16*13+8-4) 
                gpMonde->transitZone(42, -4, 4, S);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(44, 0, -5, N);
            break;
        case 33 :
            if (gpJoueur->getX()<6 && gpJoueur->getY()>240*2) 
                gpMonde->transitZone(32, -3, 2, O);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(34, 0, -4, N);
            if (gpJoueur->getX()>320*3+16*18+8 && gpJoueur->getY()<240*2) 
                gpMonde->transitZone(35, 4, -4, E);
            if (gpJoueur->getX()>320*3+16*18+8 && gpJoueur->getY()>=240*2) 
                gpMonde->transitZone(39, 4, 2, E);
            if (gpJoueur->getY()>240*5+16*13+8-4) 
                gpMonde->transitZone(41, 0, 6, S);
            if (((int)(gpJoueur->getX()/16))==63 && ((int)((gpJoueur->getY()-8)/16))==31)
                gpMonde->transitFull(117, 152, 200);
            if (((int)(gpJoueur->getX()/16))==63 && ((int)((gpJoueur->getY()-8)/16))==42)
                gpMonde->transitFull(118, 152, 200);
            if (((int)(gpJoueur->getX()/16))==49 && ((int)((gpJoueur->getY()-8)/16))==58)
                gpMonde->transitFull(119, 152, 200);
            if (((int)(gpJoueur->getX()/16))==63 && ((int)((gpJoueur->getY()-8)/16))==58)
                gpMonde->transitFull(120, 152, 200);
            if (((int)(gpJoueur->getX()/16))==15 && ((int)((gpJoueur->getY()-8)/16))==74)
                gpMonde->transitFull(121, 152, 200);
            if (((int)(gpJoueur->getX()/16))==29 && ((int)((gpJoueur->getY()-8)/16))==74)
                gpMonde->transitFull(122, 152, 200);
            if (((int)(gpJoueur->getX()/16))==63 && ((int)((gpJoueur->getY()-8)/16))==74)
                gpMonde->transitFull(123, 152, 200);
            break;
        case 34 :
            if (gpJoueur->getY()>240*3+16*13+8-4) 
                gpMonde->transitZone(33, 0, 4, S);
            if (gpJoueur->getX()>320*3+16*18+8) 
                gpMonde->transitZone(35, 4, 0, E);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(38, 0, -3, N);
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(44, -3, 1, O);
            if ((((int)(gpJoueur->getX()/16))==39 || ((int)(gpJoueur->getX()/16))==40) 
            && ((int)((gpJoueur->getY()-8)/16))==33)
                gpMonde->transitFull(155, 152+320*3, 200+240*3);
            if ((((int)(gpJoueur->getX()/16))==39 || ((int)(gpJoueur->getX()/16))==40) 
            && ((int)((gpJoueur->getY()-8)/16))==28)
                gpMonde->transitFull(155, 152+320*7, 200+240*2);
            if (((int)(gpJoueur->getX()/16))==53 && ((int)(gpJoueur->getY()/16))==26) {
                gpAudio->playSound(11); gpMonde->transitFull(155, 152+320*5, 120,S);}
            break;
        case 35 :
            if (gpJoueur->getX()<6 && gpJoueur->getY()>=240*4) 
                gpMonde->transitZone(33, -4, 4, O);
            if (gpJoueur->getX()<6 && gpJoueur->getY()<240*4) 
                gpMonde->transitZone(34, -4, 0, O);
            if (gpJoueur->getX()>320*2+16*18+8) 
                gpMonde->transitZone(36, 3, 0, E);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(37, 0, -3, N);
            if (gpJoueur->getY()>240*5+16*13+8-4) 
                gpMonde->transitZone(39, 0, 6, S);
            break;
        case 36 :
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(35, -3, 0, O);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(37, -3, -3, N);
            if (((int)(gpJoueur->getX()/16))==62 && ((int)((gpJoueur->getY()-8)/16))==12)
                gpMonde->transitFull(70, 152, 200);
            break;
        case 37 :
            if (gpJoueur->getY()>240*2+16*13+8-4 && gpJoueur->getX()<320*3) 
                gpMonde->transitZone(35, 0, 3, S);
            if (gpJoueur->getY()>240*2+16*13+8-4 && gpJoueur->getX()>=320*3) 
                gpMonde->transitZone(36, 3, 3, S);
            if (((int)(gpJoueur->getX()/16))==10 && ((int)((gpJoueur->getY()-8)/16))==3)
                gpMonde->transitFull(73, 152, 200);
            if (((int)(gpJoueur->getX()/16))==112 && ((int)((gpJoueur->getY()-8)/16))==15)
                gpMonde->transitFull(115, 152, 200);
            break;
        case 38 :
            if (gpJoueur->getY()>240*2+16*13+8-4) 
                gpMonde->transitZone(34, 0, 3, S);
            if (((int)(gpJoueur->getX()/16))==58 && ((int)((gpJoueur->getY()-8)/16))==17)
                gpMonde->transitFull(72, 152, 200);
            if (((int)(gpJoueur->getX()/16))==39 && ((int)((gpJoueur->getY()-8)/16))==10)
                gpMonde->transitFull(114, 152, 200);
            break;
        case 39 :
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(33, -4, -2, O);
            if (gpJoueur->getY()<6 && gpJoueur->getX()<3*320) 
                gpMonde->transitZone(35, 0, -6, N);
            if (gpJoueur->getY()>240*3+16*13+8-4 && gpJoueur->getX()>=3*320) 
                gpMonde->transitZone(40, 3, 4, S);
            if (gpJoueur->getY()>240*3+16*13+8-4 && gpJoueur->getX()<3*320) 
                gpMonde->transitZone(41, -4, 4, S);
            break;
        case 40 :
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(39, -3, -4, N);
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(41, -7, 0, O);
            break;
        case 41 :
            if (gpJoueur->getY()<6 && gpJoueur->getX()<4*320) 
                gpMonde->transitZone(33, 0, -6, N);
            if (gpJoueur->getY()<6 && gpJoueur->getX()>=4*320) 
                gpMonde->transitZone(39, 4, -4, N);
            if (gpJoueur->getX()>320*6+16*18+8) 
                gpMonde->transitZone(40, 7, 0, E);
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(42, -7, 0, O);
            if (((int)(gpJoueur->getX()/16))==72 && ((int)((gpJoueur->getY()-8)/16))==41)
                gpMonde->transitFull(49, 152, 200+240*2);
            break;
        case 42 :
            if (gpJoueur->getY()<6 && gpJoueur->getX()>=4*320) 
                gpMonde->transitZone(32, 4, -4, N);
            if (gpJoueur->getX()>320*6+16*18+8) 
                gpMonde->transitZone(41, 7, 0, E);
            if ((((int)(gpJoueur->getX()/16))==15 || ((int)(gpJoueur->getX()/16))==16) 
            && ((int)(gpJoueur->getY()/16))==20)
                gpMonde->transitFull(50, 152+320*6, 200+240*5);
            break;
        case 43 :
            if (gpJoueur->getY()>240*4+16*13+8-4) 
                gpMonde->transitZone(31, 0, 5, S);
            if (gpJoueur->getX()>320*3+16*18+8) 
                gpMonde->transitZone(44, 4, 0, E);
            if (gpJoueur->getY()<6) 
                gpMonde->transitZone(45, 0, -4, N);
            break;
        case 44 :
            if (gpJoueur->getX()<6) 
                gpMonde->transitZone(43, -4, 0, O);
            if (gpJoueur->getX()>320*2+16*18+8 && gpJoueur->getY()<3*240) 
                gpMonde->transitZone(34, 3, -1, E);
            if (gpJoueur->getY()>240*4+16*13+8-4) 
                gpMonde->transitZone(32, 0, 5, S);
            if (((int)(gpJoueur->getX()/16))==18 && ((int)((gpJoueur->getY()-8)/16))==40)
                gpMonde->transitFull(112, 152, 200);
            if (((int)(gpJoueur->getX()/16))==45 && ((int)((gpJoueur->getY()-8)/16))==41)
                gpMonde->transitFull(113, 152, 200);
            if ((((int)(gpJoueur->getX()/16))==34 || ((int)(gpJoueur->getX()/16))==35) 
            && ((int)((gpJoueur->getY()-8)/16))==51)
                gpMonde->transitFull(152, 152+320, 200+240*2);
            if (((int)(gpJoueur->getX()/16))==34 && ((int)((gpJoueur->getY()-8)/16))==23)
                gpMonde->transitFull(58, 152+320*3, 200+240*6);
            break;
        case 45 :
            if (gpJoueur->getY()>240*3+16*13+8-4 && gpJoueur->getX()<4*240) 
                gpMonde->transitZone(43, 0, 4, S);
            if (((int)(gpJoueur->getX()/16))==108 && ((int)((gpJoueur->getY()-8)/16))==2
            && gpJoueur->getNbGemmes()==200)
                gpMonde->transitFull(59, 152+320*5, 200+240*3);
            break;
        case 46 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(3)==60*16)
                gpMonde->transitFull(22, 16*84, 16*8+8);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==2835) {
                gpAudio->playSound(10);
                gpMonde->transitFull(46, gpJoueur->getX()+(16*80), gpJoueur->getY()-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==2841) {
                gpAudio->playSound(11);
                gpMonde->transitFull(46, gpJoueur->getX()-(16*80), gpJoueur->getY()+16);
                break;
            }
            break;
        case 47 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 
            && gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==30*16)
                gpMonde->transitFull(26, 16*72+8, 16*42);
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 
            && gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(26, 16*50+8, 16*27);
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 
            && gpMonde->regionValue(0)==20*16 && gpMonde->regionValue(1)==60*16)
                gpMonde->transitFull(26, 16*32+8, 16*48);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==3035) {
                gpAudio->playSound(10);
                gpMonde->transitFull(47, gpJoueur->getX()-(16*120), gpJoueur->getY()-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==3041) {
                gpAudio->playSound(11);
                gpMonde->transitFull(47, gpJoueur->getX()+(16*120), gpJoueur->getY()+16);
                break;
            }
            break;
        case 48 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(3)==75*16)
                gpMonde->transitFull(30, 16*122, 16*36+8);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==3207) {
                gpAudio->playSound(10);
                gpMonde->transitFull(48, gpJoueur->getX()-(16*140), gpJoueur->getY()-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==3213) {
                gpAudio->playSound(11);
                gpMonde->transitFull(48, gpJoueur->getX()+(16*140), gpJoueur->getY()+16);
                break;
            }
            break;
        case 49 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(0)==0)
                gpMonde->transitFull(41, 16*72+8, 16*43+8);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==3480) {
                gpAudio->playSound(10);
                gpMonde->transitFull(49, gpJoueur->getX()-(16*120), gpJoueur->getY()-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==3486) {
                gpAudio->playSound(11);
                gpMonde->transitFull(49, gpJoueur->getX()+(16*120), gpJoueur->getY()+16);
                break;
            }
            break;
        case 50 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(0)==120*16
             && gpMonde->regionValue(1)==60*16)
                gpMonde->transitFull(42, 16*15+8, 16*22);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==3686) {
                gpAudio->playSound(10);
                int dec = 6*320;
                if (gpMonde->regionValue(0)<80*16) dec = 2*320;
                else if (gpMonde->regionValue(0)<180*16) dec = 4*320;
                gpMonde->transitFull(50, gpJoueur->getX()-dec, gpJoueur->getY()-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==3692) {
                gpAudio->playSound(11);
                int dec = 6*320;
                if (gpMonde->regionValue(0)<20*16) dec = 2*320;
                else if (gpMonde->regionValue(0)<80*16) dec = 4*320;
                gpMonde->transitFull(50, gpJoueur->getX()+dec, gpJoueur->getY()+16);
                break;
            }
            break;
        case 51 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(0)==120*16
             && gpMonde->regionValue(1)==75*16)
                gpMonde->transitFull(27, 16*15+8, 16*22);
            if (gpJoueur->getX()>gpMonde->regionValue(2)-24 && gpMonde->regionValue(0)==280*16
             && gpMonde->regionValue(1)==75*16)
                gpMonde->transitFull(67, 16*1, gpJoueur->getY()-16*90);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==5105) {
                gpAudio->playSound(10);
                int dec = 6*320;
                if (gpMonde->regionValue(0)<80*16) dec = 2*320;
                else if (gpMonde->regionValue(0)<180*16) dec = 4*320;
                gpMonde->transitFull(51, gpJoueur->getX()-dec, gpJoueur->getY()-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==5111) {
                gpAudio->playSound(11);
                int dec = 6*320;
                if (gpMonde->regionValue(0)<20*16) dec = 2*320;
                else if (gpMonde->regionValue(0)<80*16) dec = 4*320;
                gpMonde->transitFull(51, gpJoueur->getX()+dec, gpJoueur->getY()+16);
                break;
            }
            break;
        case 52 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(0)==120*16
             && gpMonde->regionValue(1)==60*16)
                gpMonde->transitFull(12, 16*15+8, 16*22);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==3925) {
                gpAudio->playSound(10);
                int dec = 6*320;
                if (gpMonde->regionValue(0)<80*16) dec = 2*320;
                else if (gpMonde->regionValue(0)<180*16) dec = 4*320;
                gpMonde->transitFull(52, gpJoueur->getX()-dec, gpJoueur->getY()-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==3931) {
                gpAudio->playSound(11);
                int dec = 6*320;
                if (gpMonde->regionValue(0)<20*16) dec = 2*320;
                else if (gpMonde->regionValue(0)<80*16) dec = 4*320;
                gpMonde->transitFull(52, gpJoueur->getX()+dec, gpJoueur->getY()+16);
                break;
            }
            break;
        case 53 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(0)==20*16
             && gpMonde->regionValue(1)==45*16)
                gpMonde->transitFull(7, 16*84, 16*8+8);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==5365) {
                gpAudio->playSound(10);
                int decX = 4*320;
                int decY = 0;
                if (gpMonde->regionValue(0)>=80*16 && gpMonde->regionValue(1)>=60*16) {
                    decX=-decX; decY=4*240;}
                gpMonde->transitFull(53, gpJoueur->getX()+decX, gpJoueur->getY()-decY-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==5371) {
                gpAudio->playSound(11);
                int decX = 4*320;
                int decY = 0;
                if (gpMonde->regionValue(0)<80*16) {decX=-decX; decY=4*240;}
                gpMonde->transitFull(53, gpJoueur->getX()-decX, gpJoueur->getY()+decY+16);
                break;
            }
            break;
        case 54 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(0)==0)
                gpMonde->transitFull(11, 16*72+8, 16*52+8);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==5558) {
                gpAudio->playSound(10);
                gpMonde->transitFull(54, gpJoueur->getX()-(16*120), gpJoueur->getY()-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==5564) {
                gpAudio->playSound(11);
                gpMonde->transitFull(54, gpJoueur->getX()+(16*120), gpJoueur->getY()+16);
                break;
            }
            break;
        case 55 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(3)==225*16)
                gpMonde->transitFull(15, 16*122, 16*35+8);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==5747) {
                gpAudio->playSound(10);
                gpMonde->transitFull(55, gpJoueur->getX(), gpJoueur->getY()-16+(16*75));
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==5753) {
                gpAudio->playSound(11);
                gpMonde->transitFull(55, gpJoueur->getX(), gpJoueur->getY()+16-(16*75));
                break;
            }
            break;
        case 56 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 
            && gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(3)==60*16)
                gpMonde->transitFull(4, 16*39+8, 16*35+8);
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 
            && gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(3)==45*16)
                gpMonde->transitFull(4, 16*39+8, 16*30+8);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==5894) {
                gpAudio->playSound(10);
                gpMonde->transitFull(4, 16*53+8, 16*25);
                break;
            }
            break;
        case 57 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 
            && gpJoueur->getAvancement()<PARLE_ZELDA_PALAIS
            && gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(3)==30*16) {
                ecrit(1015); gpJoueur->setY(gpJoueur->getY()-4); gpJoueur->setDirection(N);
            }
            if (gpJoueur->getX()>gpMonde->regionValue(0)+16*4 
            && gpJoueur->getAvancement()<ZELDA_SOUS_SOL
            && gpMonde->regionValue(0)==100*16 && gpMonde->regionValue(1)==165*16) {
                gpJoueur->setAvancement(ZELDA_SOUS_SOL);
                gpJoueur->setImmo(true); gpJoueur->setDirection(O);
                Pnj* pnj = gpPnj->getSuivant();
                while (pnj != NULL) {
                    if (pnj->getId() == 15) {
                        pnj->setX(100*16+8); pnj->setY(171*16+9); pnj->setDirection(E);
                        break;
                    }
                    pnj = pnj->getSuivant();
                }
            }
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 
            && gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(3)==60*16)
                gpMonde->transitFull(19, 16*39+8, 16*35+8);
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 
            && gpMonde->regionValue(0)==160*16 && gpMonde->regionValue(3)==45*16)
                gpMonde->transitFull(19, 16*39+8, 16*30+8);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==6100) {
                gpAudio->playSound(10);
                gpMonde->transitFull(19, 16*53+8, 16*25);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==6106 ||
            gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==6218) {
                gpAudio->playSound(11);
                gpMonde->transitFull(57, gpJoueur->getX(), gpJoueur->getY()+16+(16*90));
                break;
            }
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==6212) {
                gpAudio->playSound(10);
                if (gpMonde->regionValue(0)==140*16 && gpMonde->regionValue(1)==195*16)
                    gpMonde->transitFull(19, 16*68+8, 16*49, S);
                else gpMonde->transitFull(57, gpJoueur->getX(), gpJoueur->getY()-16-(16*90));
                break;
            }
            break;
        case 58 :
            if (gpJoueur->isTempsVisible() && gpMonde->regionValue(0)==120*16 
            && gpMonde->regionValue(1)==90*16 && ((int)((gpJoueur->getX()+8)/16))==126) {
                ecrit(1129);
            }
            if (nbEnnemis() && gpMonde->regionValue(0)==60*16 
            && gpMonde->regionValue(1)==30*16 && ((int)(gpJoueur->getY()/16))==37) {
                ecrit(1150);
            }
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==90*16) {
                gpJoueur->setTempsVisible(false);
                gpMonde->transitFull(44, 16*34+8, 16*25+8);
            }
            break;
        case 59 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(3)==60*16)
                gpMonde->transitFull(45, 16*108+8, 16*4+8);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==6592) {
                gpAudio->playSound(10);
                gpMonde->transitFull(59, gpJoueur->getX()+(16*80), gpJoueur->getY()-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==6598) {
                gpAudio->playSound(11);
                gpMonde->transitFull(59, gpJoueur->getX()-(16*80), gpJoueur->getY()+16);
                break;
            }
            break;
        case 60 :
            if (gpJoueur->getX()>gpMonde->regionValue(2)-24 
            && gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==75*16) {
                ecrit(1351); gpJoueur->setX(gpJoueur->getX()-4); gpJoueur->setDirection(O);
            }
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==6762) {
                gpAudio->playSound(10);
                gpMonde->transitFull(60, gpJoueur->getX(), gpJoueur->getY()-16+(16*75));
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==6768) {
                gpAudio->playSound(11);
                gpMonde->transitFull(60, gpJoueur->getX(), gpJoueur->getY()+16-(16*75));
                break;
            }
            break;
        case 61 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(16, 16*59+8, 16*11);
            break;
        case 62 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(21, 16*65+8, 16*81);
            break;
        case 63 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(0)==60*16)
                gpMonde->transitFull(21, 16*15+8, 16*11);
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(0)==80*16)
                gpMonde->transitFull(21, 16*27+8, 16*11);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==2306) {
                gpAudio->playSound(10);
                gpMonde->transitFull(63, gpJoueur->getX()+(16*20*2), gpJoueur->getY()-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==2312) {
                gpAudio->playSound(11);
                gpMonde->transitFull(63, gpJoueur->getX()-(16*20*2), gpJoueur->getY()+16);
                break;
            }
            break;
        case 64 :
            if (gpJoueur->getAvancement()==STELE_LUE && !gpJoueur->hasObjet(O_CARTE) 
            && gpJoueur->getY()>=gpMonde->regionValue(3)-28-16*3-8
            && gpJoueur->getY()<=gpMonde->regionValue(3)-28-16*3-4) {
                gpJoueur->setImmo(true);
                gpJoueur->setDirection(S);
                ajoutePnj(15,9*16+8,15*16-8,326);
                gpPnj->getSuivant()->setDirection(N);
            }
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(21, 16*62+8, 16*14);
            break;
        case 65 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(22, 16*10+8, 16*5);
            break;
        case 66 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(23, 16*58+8, 16*19);
            break;
        case 67 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==15*16)
                gpMonde->transitFull(27, 16*84+8, 16*57);
            if (gpJoueur->getX()<gpMonde->regionValue(0)+6 && gpMonde->regionValue(0)==0
             && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(51, 16*318, gpJoueur->getY()+16*90);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==2306) {
                gpAudio->playSound(10);
                gpMonde->transitFull(67, gpJoueur->getX()+(16*20), gpJoueur->getY()-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==2312) {
                gpAudio->playSound(11);
                gpMonde->transitFull(67, gpJoueur->getX()-(16*20), gpJoueur->getY()+16);
                break;
            }
            break;
        case 68 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28
             && gpMonde->regionValue(0)==0 && gpMonde->regionValue(1)==15*16)
                gpMonde->transitFull(30, 16*25+8, 16*41);
             if (gpJoueur->getY()>gpMonde->regionValue(3)-28
             && gpMonde->regionValue(0)==30*16 && gpMonde->regionValue(1)==30*16)
                gpMonde->transitFull(30, 16*45+8, 16*33);
             if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(0)==80*16)
                gpMonde->transitFull(30, 16*23+8, 16*34);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==2306) {
                gpAudio->playSound(10);
                if (gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(1)==15*16)
                    gpMonde->transitFull(30, 16*53+8, 16*32, S);
                else if (gpMonde->regionValue(0)==0) 
                    gpMonde->transitFull(68, gpJoueur->getX()+(16*80), gpJoueur->getY()-16+(16*15));
                else gpMonde->transitFull(68, gpJoueur->getX(), gpJoueur->getY()-16+(16*15));
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==2312) {
                gpAudio->playSound(11);
                if (gpMonde->regionValue(0)==80*16) 
                    gpMonde->transitFull(68, gpJoueur->getX()-(16*80), gpJoueur->getY()+16-(16*15));
                else gpMonde->transitFull(68, gpJoueur->getX(), gpJoueur->getY()+16-(16*15));
                break;
            }
            break;
        case 69 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(21, 16*62+8, 16*14);
            break;
        case 70 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(36, 16*62+8, 16*14);
            break;
        case 71 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(31, 16*59+8, 16*11);
            break;
        case 72 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(38, 16*58+8, 16*19);
            break;
        case 73 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(37, 16*10+8, 16*5);
            break;
        case 74 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(7, 16*10+8, 16*5);
            break;
        case 75 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(1, 16*59+8, 16*11);
            break;
        case 76 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(12, 16*84+8, 16*57);
            break;
        case 77 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==0)
                gpMonde->transitFull(6, 16*65+8, 16*81);
            break;
        case 78 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpJoueur->getX()<80*16)
                gpMonde->transitFull(6, 16*15+8, 16*11);
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpJoueur->getX()>=80*16)
                gpMonde->transitFull(6, 16*27+8, 16*11);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==2306) {
                gpAudio->playSound(10);
                gpMonde->transitFull(78, gpJoueur->getX()+(16*20*3), gpJoueur->getY()-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==2312) {
                gpAudio->playSound(11);
                gpMonde->transitFull(78, gpJoueur->getX()-(16*20*3), gpJoueur->getY()+16);
                break;
            }
            break;
        case 79 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(16, 16*39+8, 16*41);
            break;
        case 80 :
            if (gpJoueur->getY()<6)
                gpMonde->transitFull(18, 16*17+8, 16*29+8);
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(18, 16*17+8, 16*38+8);
            break;
        case 81 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(18, 16*63+8, 16*34+8);
            break;
        case 82 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(18, 16*63+8, 16*45+8);
            break;
        case 83 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(18, 16*15+8, 16*60+8);
            break;
        case 84 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(18, 16*49+8, 16*61+8);
            break;
        case 85 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(18, 16*63+8, 16*61+8);
            break;
        case 86 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(18, 16*15+8, 16*77+8);
            break;
        case 87 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(18, 16*29+8, 16*77+8);
            break;
        case 88 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(18, 16*49+8, 16*77+8);
            break;
        case 89 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(18, 16*63+8, 16*77+8);
            break;
        case 90 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(22, 16*18+8, 16*30+8);
            break;
        case 91 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(22, 16*50+8, 16*34+8);
            break;
        case 92 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(22, 16*112+8, 16*18+8);
            break;
        case 93 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(25, 16*37+8, 16*10+8);
            break;
        case 94 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(25, 16*31+8, 16*25+8);
            break;
        case 95 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(25, 16*43+8, 16*27+8);
            break;
        case 96 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(25, 16*30+8, 16*40+8);
            break;
        case 97 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(25, 16*47+8, 16*43+8);
            break;
        case 98 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(25, 16*65+8, 16*23+8);
            break;
        case 99 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(25, 16*62+8, 16*35+8);
            break;
        case 100 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(25, 16*65+8, 16*50+8);
            break;
        case 101 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(26, 16*120+8, 16*37+8);
            break;
        case 102 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpJoueur->getX()<20*16)
                gpMonde->transitFull(28, 16*15+8, 16*17+8);
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpJoueur->getX()>=20*16)
                gpMonde->transitFull(28, 16*21+8, 16*17+8);
            break;
        case 103 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(28, 16*24+8, 16*26+8);
            break;
        case 104 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(28, 16*18+8, 16*36+8);
            break;
        case 105 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(28, 16*13+8, 16*48+8);
            break;
        case 106 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(28, 16*42+8, 16*22+8);
            break;
        case 107 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(28, 16*61+8, 16*35+8);
            break;
        case 108 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(28, 16*61+8, 16*45+8);
            break;
        case 109 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(29, 16*18+8, 16*43+8);
            break;
        case 110 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(29, 16*45+8, 16*44+8);
            break;
        case 111 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(23, 16*39+8, 16*12+8);
            break;
        case 112 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(44, 16*18+8, 16*42+8);
            break;
        case 113 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(44, 16*45+8, 16*43+8);
            break;
        case 114 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(38, 16*39+8, 16*12+8);
            break;
        case 115 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(37, 16*112+8, 16*17+8);
            break;
        case 116 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(31, 16*39+8, 16*41);
            break;
        case 117 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(33, 16*63+8, 16*33+8);
            break;
        case 118 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(33, 16*63+8, 16*44+8);
            break;
        case 119 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(33, 16*49+8, 16*60+8);
            break;
        case 120 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(33, 16*63+8, 16*60+8);
            break;
        case 121 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(33, 16*15+8, 16*76+8);
            break;
        case 122 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(33, 16*29+8, 16*76+8);
            break;
        case 123 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(33, 16*63+8, 16*76+8);
            break;
        case 124 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(8, 16*39+8, 16*12+8);
            break;
        case 125 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(14, 16*18+8, 16*42+8);
            break;
        case 126 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(1, 16*39+8, 16*41);
            break;
        case 127 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(11, 16*72+8, 16*43+8);
            break;
        case 128 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(3, 16*63+8, 16*33+8);
            break;
        case 129 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(3, 16*63+8, 16*44+8);
            break;
        case 130 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(3, 16*15+8, 16*60+8);
            break;
        case 131 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(3, 16*49+8, 16*60+8);
            break;
        case 132 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(3, 16*63+8, 16*60+8);
            break;
        case 133 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(3, 16*29+8, 16*76+8);
            break;
        case 134 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(3, 16*49+8, 16*76+8);
            break;
        case 135 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(3, 16*63+8, 16*76+8);
            break;
        case 136 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(3, 16*17+8, 16*38+8);
            break;
        case 137 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(1)==60*16)
                gpMonde->transitFull(10, 16*37+8, 16*9+8);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==2306) {
                gpAudio->playSound(10);
                gpMonde->transitFull(137, gpJoueur->getX(), gpJoueur->getY()-16+(16*15));
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==2312) {
                gpAudio->playSound(11);
                gpMonde->transitFull(137, gpJoueur->getX(), gpJoueur->getY()+16-(16*15));
                break;
            }
            break;
        case 138 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(10, 16*31+8, 16*24+8);
            break;
        case 139 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(10, 16*43+8, 16*26+8);
            break;
        case 140 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(10, 16*30+8, 16*39+8);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==2306) {
                gpAudio->playSound(10);
                gpMonde->transitFull(140, gpJoueur->getX()-(16*20), gpJoueur->getY()-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==2312) {
                if (!gpJoueur->getCoffre(15,26)) {
                    ecrit(840); gpJoueur->setY(gpJoueur->getY()-4); gpJoueur->setDirection(N);
                    break;
                }
                if (gpPnj->getSuivant()) gpPnj->getSuivant()->setVie(0);
                gpAudio->playSound(11);
                gpMonde->transitFull(140, gpJoueur->getX()+(16*20), gpJoueur->getY()+16);
                break;
            }
            break;
        case 141 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(10, 16*47+8, 16*42+8);
            break;
        case 142 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(10, 16*62+8, 16*34+8);
            break;
        case 143 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(10, 16*65+8, 16*49+8);
            break;
        case 144 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpJoueur->getX()<20*16)
                gpMonde->transitFull(13, 16*15+8, 16*16+8);
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpJoueur->getX()>=20*16)
                gpMonde->transitFull(13, 16*21+8, 16*16+8);
            break;
        case 145 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(13, 16*18+8, 16*36+8);
            break;
        case 146 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(13, 16*13+8, 16*48+8);
            break;
        case 147 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(13, 16*42+8, 16*22+8);
            break;
        case 148 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(13, 16*61+8, 16*35+8);
            break;
        case 149 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28)
                gpMonde->transitFull(13, 16*61+8, 16*45+8);
            break;
        case 150 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(3)==45*16)
                gpMonde->transitFull(21, 16*16+8, 16*69+8);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==2508
            || gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==2306) {
                gpAudio->playSound(10);
                gpMonde->transitFull(150, gpJoueur->getX()-(16*60), gpJoueur->getY()-16);
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==2514
            || gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==2312) {
                gpAudio->playSound(11);
                gpMonde->transitFull(150, gpJoueur->getX()+(16*60), gpJoueur->getY()+16);
                break;
            }
            break;
        case 151 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(3)==45*16)
                gpMonde->transitFull(29, 16*34+8, 16*53+8);
            break;
        case 152 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(3)==45*16)
                gpMonde->transitFull(44, 16*34+8, 16*53+8);
            break;
        case 153 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(3)==45*16)
                gpMonde->transitFull(14, 16*34+8, 16*53+8);
            break;
        case 154 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && gpMonde->regionValue(3)==30*16)
                gpMonde->transitFull(9, 16*113+8, 16*36+8);
            if (gpJoueur->getCoffre(15,28)==0 && gpJoueur->nbCristaux()>=6
            && gpJoueur->getY()>15*16 && gpJoueur->getX()>35*16) {
                gpAudio->stopMusic();
                SDL_Delay(500);
                gpAudio->playSound(16);
                SDL_Delay(1500);
                gpAudio->stopSound();
                gpAudio->replayMusic();
                gpAudio->playSpecial(9);
                ecrit(923);
            }
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==2682
            || gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==2306) {
                if (gpJoueur->getCoffre(15,28)==1 && gpJoueur->getX()<60*16) {
                    ecrit(923); gpJoueur->setY(gpJoueur->getY()+4); gpJoueur->setDirection(S);
                    break;
                }
                gpAudio->playSound(10);
                if (gpJoueur->getX()>60*16) 
                    gpMonde->transitFull(9, 129*16+8, 39*16, S);
                else if (gpJoueur->getY()<15*16) 
                    gpMonde->transitFull(154, gpJoueur->getX()-(16*20), gpJoueur->getY()-16);
                else
                    gpMonde->transitFull(154, gpJoueur->getX(), gpJoueur->getY()-16-(16*15));
                break;
            }
            //escalier vers b
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==2688
            || gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+16)==2312) {
                gpAudio->playSound(11);
                if (gpJoueur->getX()<20*16) 
                    gpMonde->transitFull(154, gpJoueur->getX()+(16*20), gpJoueur->getY()+16);
                else 
                    gpMonde->transitFull(154, gpJoueur->getX(), gpJoueur->getY()+16+(16*15));
                break;
            }
            break;
        case 155 :
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 
            && gpMonde->regionValue(0)==60*16 && gpMonde->regionValue(3)==60*16)
                gpMonde->transitFull(34, 16*39+8, 16*35+8);
            if (gpJoueur->getY()>gpMonde->regionValue(3)-28 
            && gpMonde->regionValue(0)==140*16 && gpMonde->regionValue(3)==45*16)
                gpMonde->transitFull(34, 16*39+8, 16*30+8);
            //escaliers vers h
            if (gpMonde->motifValue(gpJoueur->getX(),gpJoueur->getY()+15)==4723) {
                gpAudio->playSound(10);
                gpMonde->transitFull(34, 16*53+8, 16*25);
                break;
            }
            break;
    }
    
    if (!isDehors() && !transition) {
        
        int dir=-1;
        
        if (gpJoueur->getY()<gpMonde->regionValue(1)+6 && !transition) {
            gpMonde->transitSalle(N);dir=N;}
        if (gpJoueur->getY()>gpMonde->regionValue(3)-28 && !transition) {
            gpMonde->transitSalle(S);dir=S;}
        if (gpJoueur->getX()<gpMonde->regionValue(0)+6 && !transition) {
            gpMonde->transitSalle(O);dir=O;}
        if (gpJoueur->getX()>gpMonde->regionValue(2)-24 && !transition) {
            gpMonde->transitSalle(E);dir=E;}
        
    }
}

SDL_Surface* Jeu::loadImg(const char* image) {
    char fImage[512];
#ifdef __vita__
    snprintf(fImage, sizeof(fImage), "%s%s", "app0:", image);
#else
    snprintf(fImage, sizeof(fImage), "%s", image);
#endif
    return IMG_Load(fImage);
}
