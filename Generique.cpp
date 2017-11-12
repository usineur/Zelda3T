/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "Generique.h"
#include "Jeu.h"
#include "Keyboard.h"

Generique::Generique(Jeu* jeu) : gpJeu(jeu), anim(0) {
    imageFin = NULL;
    imageArbre = NULL;
    image = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
    imageTitre = gpJeu->loadImg("data/images/logos/titre.png");
    SDL_SetColorKey(imageTitre,SDL_SRCCOLORKEY,SDL_MapRGB(imageTitre->format,0,0,255));
    imageCurseur = gpJeu->loadImg("data/images/logos/curseur.png");
    SDL_SetColorKey(imageCurseur,SDL_SRCCOLORKEY,SDL_MapRGB(imageCurseur->format,0,0,255));
    imageNiveau = gpJeu->loadImg("data/images/logos/niveau.png");
    SDL_SetColorKey(imageNiveau,SDL_SRCCOLORKEY,SDL_MapRGB(imageNiveau->format,0,0,255));
    imageFee = gpJeu->loadImg("data/images/logos/fee.png");
    imageCadre = gpJeu->loadImg("data/images/logos/cadres.png");
    imageFond1 = NULL;
    imageFond2 = NULL;
    for (int i = 0; i < 5; i++) imageIntro[i]=NULL;
}

Generique::~Generique() {
    SDL_FreeSurface(imageFin);
    SDL_FreeSurface(imageArbre);
    SDL_FreeSurface(image);
    SDL_FreeSurface(imageTitre);
    SDL_FreeSurface(imageCurseur);
    SDL_FreeSurface(imageNiveau);
    SDL_FreeSurface(imageFee);
    SDL_FreeSurface(imageCadre);
    SDL_FreeSurface(imageFond1);
    SDL_FreeSurface(imageFond2);
    for (int i = 0; i < 5; i++) SDL_FreeSurface(imageIntro[i]);
}

void Generique::drawFin(SDL_Surface* gpScreen) {
    if (!imageFin) imageFin = gpJeu->loadImg("data/images/logos/fin.png");
    SDL_Rect dst; dst.x = 0; dst.y = 0;
    SDL_BlitSurface(imageFin, NULL, gpScreen, &dst);
    gpJeu->getTexte()->draw(gpScreen);
}

void Generique::initLogo() {
    SDL_Rect dst;
    SDL_Surface* logo = gpJeu->loadImg("data/images/logos/logo.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(logo, NULL, image, &dst);
    SDL_FreeSurface(logo);
}

void Generique::initPresent() {
    SDL_Rect dst;
    SDL_Surface* present = gpJeu->loadImg("data/images/motifs/present.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(present, NULL, image, &dst);
    SDL_FreeSurface(present);
}

void Generique::drawToPresent(SDL_Surface* gpScreen) {
    draw(gpScreen);
    gpJeu->getTexte()->draw(gpScreen);
}

void Generique::initPasse() {
    SDL_Rect dst;
    SDL_Surface* passe = gpJeu->loadImg("data/images/motifs/passe.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(passe, NULL, image, &dst);
    SDL_FreeSurface(passe);
}

void Generique::initImageFin() {
    SDL_Rect dst;
    SDL_Surface* fin = gpJeu->loadImg("data/images/motifs/fin.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(fin, NULL, image, &dst);
    SDL_FreeSurface(fin);
}

void Generique::initTitre() {
    SDL_Rect dst;
    SDL_Surface* fond = gpJeu->loadImg("data/images/logos/fond.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(fond, NULL, image, &dst);
    SDL_FreeSurface(fond);
    SDL_Surface* logo = gpJeu->loadImg("data/images/logos/titre.png");
    SDL_SetColorKey(logo,SDL_SRCCOLORKEY,SDL_MapRGB(logo->format,0,0,255));
    logo = SDL_DisplayFormat(logo);
    dst.x = 76; dst.y = 53; SDL_BlitSurface(logo, NULL, image, &dst);
    SDL_FreeSurface(logo);
}

void Generique::initSelection() {
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
    
    for (int i = 0; i < 8; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 160; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 160; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 160; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,48,288,32);
    cadre(16,96,288,32);
    cadre(16,144,288,32);
    cadre(16,192,136,32);
    cadre(168,192,136,32);
    
    gpJeu->affiche(image, "ECRAN DE SELECTION", 40, 16);
    gpJeu->affiche(image, "1.", 44, 56);
    gpJeu->affiche(image, "2.", 44, 104);
    gpJeu->affiche(image, "3.", 44, 152);
    gpJeu->affiche(image, "OPTIONS", 63, 200);
    gpJeu->affiche(image, "RECORDS", 215, 200);
    
    //stats :
    SDL_Surface* imageStat = gpJeu->loadImg("data/images/statut/statut.png");
    SDL_SetColorKey(imageStat,SDL_SRCCOLORKEY,SDL_MapRGB(imageStat->format,0,0,255));
    SDL_Surface* inventaire = gpJeu->loadImg("data/images/statut/inventaire.png");
    SDL_Surface* objets = gpJeu->loadImg("data/images/statut/objets.png");
    
    for (int i = 0; i < 3; i++) {
        Joueur* gpJoueur = new Joueur(gpJeu,i+1);
        if (gpJoueur->getLoader()) {
            //vie
            if(gpJoueur->getVie()>gpJoueur->getVieMax()) gpJoueur->setVie(gpJoueur->getVieMax());
            for(int j=0;j<gpJoueur->getVieMax()/2;j++) {
                src.h = 7; src.w = 7; src.y=9;
                dst.x = 64-8+((j%10)*8)+8;dst.y = 57+8*((int)(j/10))+i*48;
                if (gpJoueur->getVie()-(j*2)>1)src.x=141;
                if (gpJoueur->getVie()-(j*2)==1)src.x=149;
                if (gpJoueur->getVie()-(j*2)<1)src.x=157;
                SDL_BlitSurface(imageStat, &src, image, &dst);
            }
            
            dst.x=176-4; dst.y=56+i*48;
            if (gpJoueur->nbCristaux()) {
                //cristaux
                src.x=16; src.y=17*4; src.w=16; src.h=17; dst.x-=(16-2);
                for (int j=0; j<7; j++) {
                    if (gpJoueur->hasCristal(j)) src.x=16; else src.x=32;
                    SDL_BlitSurface(inventaire, &src, image, &dst);
                    dst.x+=16;
                }
            } else if (gpJoueur->hasObjet(O_CARTE)) { //stèle lue
                //médaillons
                src.y=32; src.w=16; src.h=16;
                for (int i = 0; i < 3; i++) {
                    if (gpJoueur->hasMedaillon(i)) src.x=16*i;
                    else src.x=48;
                    SDL_BlitSurface(objets, &src, image, &dst);
                    dst.x+=16;
                }dst.x+=8;
                //clé du temps
                if (gpJoueur->hasObjet(O_CLE_TEMPS)) {
                    src.x=80;
                    SDL_BlitSurface(objets, &src, image, &dst);
                } dst.x+=16+8;
                //ocarina
                if (gpJoueur->hasObjet(O_OCARINA)) {
                    src.y=85; src.x=0;
                    SDL_BlitSurface(inventaire, &src, image, &dst);
                }
            }
            
            //cristaux
            /*dst.x=176+8-16-16-4; dst.y=56+i*48;
            src.x=16; src.y=17*4; src.w=16; src.h=17;
            for (int j=0; j<5; j++) {
                if (gpJoueur->hasCristal(j)) src.x=16; else src.x=32;
                SDL_BlitSurface(inventaire, &src, image, &dst);
                dst.x+=16+2;
            }
            
            //épée
            dst.x=280-48+8; dst.y=56+i*48;
            src.x=16*(gpJoueur->getEpee()-1); src.y=0; src.w=16; src.h=16;
            if (gpJoueur->getEpee()) SDL_BlitSurface(objets, &src, image, &dst);
            
            //masque
            dst.x=280-32+16-4; dst.y=56+i*48;
            src.x=16*(gpJoueur->hasObjet(O_MASQUE)-1); 
            src.y=102-17*(gpJoueur->hasObjet(O_MASQUE)-1); src.w=16; src.h=16;
            if (gpJoueur->hasObjet(O_MASQUE)) SDL_BlitSurface(inventaire, &src, image, &dst);*/
            
            //triforce
            dst.x=272+8; dst.y=56+i*48;
            src.x=128; src.y=0; src.w=17; src.h=16;
            if (gpJoueur->getEnnemi(50)) SDL_BlitSurface(objets, &src, image, &dst);
            
            gpJeu->getKeyboard()->setSave(i,1);
        }else gpJeu->getKeyboard()->setSave(i,0);
        delete gpJoueur;
    }
    
    SDL_FreeSurface(objets);
    SDL_FreeSurface(imageStat);
    SDL_FreeSurface(inventaire);
}

void Generique::initOption() {
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
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,64,288,32);
    cadre(16,128,288,32);
    cadre(16,192,136,32);
    
    gpJeu->affiche(image, "OPTIONS", 40, 16);
    gpJeu->affiche(image, "MUSIQUE", 60, 72);
    gpJeu->affiche(image, "SON", 60, 136);
    gpJeu->affiche(image, "RETOUR", 63, 200);
    
    src.x = 0; src.y = 96; dst.x = 128; dst.y = 72; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    for (int i = 144; i < 264; i+=16) {
        src.x = 16; src.y = 96; dst.x = i; dst.y = 72; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    src.x = 32; src.y = 96; dst.x = 264; dst.y = 72; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    src.x = 0; src.y = 96; dst.x = 128; dst.y = 136; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    for (int i = 144; i < 264; i+=16) {
        src.x = 16; src.y = 96; dst.x = i; dst.y = 136; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    src.x = 32; src.y = 96; dst.x = 264; dst.y = 136; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
}

void Generique::initRecord() {
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
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(128,8,176,32);
    cadre(16,48,144,32); cadre(176,48,32,32); cadre(224,48,32,32); cadre(272,48,32,32);
    cadre(16,96,144,32); cadre(176,96,32,32); cadre(224,96,32,32); cadre(272,96,32,32);
    cadre(16,144,144,32); cadre(176,144,32,32); cadre(224,144,32,32); cadre(272,144,32,32);
    cadre(16,192,136,32);
    cadre(168,192,136,32);
    
    ostringstream oss;
    int temps = gpJeu->getKeyboard()->getTemps();
    if (temps > 359999) temps = 359999;
    int h = temps/3600;
    int m = (temps - ((int)(temps/3600))*3600)/60;
    int s = temps%60;
    if (h < 10) oss<<"0"; oss << h << ":";
    if (m < 10) oss<<"0"; oss << m << ":";
    if (s < 10) oss<<"0"; oss << s;
    
    
    gpJeu->affiche(image, "RECORDS", 40, 16);
    gpJeu->affiche(image, "MEILLEUR TEMPS : " + oss.str(), 140, 16);
    gpJeu->affiche(image, "RANG DES 100%", 44, 56);
    gpJeu->affiche(image, "RANG ULTIME", 44, 104);
    gpJeu->affiche(image, "RANG DE RAPIDITE", 44, 152);
    gpJeu->affiche(image, "RETOUR", 63, 200);
    gpJeu->affiche(image, "EFFACER", 215, 200);
    
    SDL_Surface* objets = gpJeu->loadImg("data/images/statut/objets.png");
    
    //triforce
    src.y=0; src.w=17; src.h=16;
    
    for (int i = 0; i < 3; i++) {
        dst.x=231-48; dst.y=56+i*48;
        gpJeu->getKeyboard()->getRang(i) ? src.x=128 : src.x=145; 
        SDL_BlitSurface(objets, &src, image, &dst);}
    
    //graäl
    src.y=16; //src.w=17; src.h=16;
    
    for (int i = 0; i < 3; i++) {
        dst.x=280-48; dst.y=56+i*48;
        gpJeu->getKeyboard()->getRang(i+3) ? src.x=128 : src.x=145; 
        SDL_BlitSurface(objets, &src, image, &dst);}
    
    //ocarina
    src.x=162; src.w=16;
    
    for (int i = 0; i < 3; i++) {
        dst.x=280; dst.y=56+i*48;
        gpJeu->getKeyboard()->getRang(i+6) ? src.y=0 : src.y=16; 
        SDL_BlitSurface(objets, &src, image, &dst);}
    
    SDL_FreeSurface(objets);
}

void Generique::initEffacer() {
    cadre(104,84,112,72);
    gpJeu->affiche(image, "EFFACER ?", 133, 93);
    gpJeu->affiche(image, "OUI", 151, 113);
    gpJeu->affiche(image, "NON", 151, 133);
}

void Generique::initCharger() {
    cadre(104,84,112,72);
    gpJeu->affiche(image, "CHARGER", 139, 93);
    gpJeu->affiche(image, "EFFACER", 139, 113);
    gpJeu->affiche(image, "ANNULER", 139, 133);
}

void Generique::initIntro() {
    if (imageFond1==NULL) {
        imageFond1 = gpJeu->loadImg("data/images/logos/fond1.png");
        SDL_SetColorKey(imageFond1,SDL_SRCCOLORKEY,SDL_MapRGB(imageFond1->format,0,0,255));}
    if (imageFond2==NULL) imageFond2 = gpJeu->loadImg("data/images/logos/fond2.png");
    
    ostringstream oss;
    for (int i = 0; i < 5; i++) {
        if (imageIntro[i]==NULL) {
            oss.str(""); oss << (i+1);
            imageIntro[i] = gpJeu->loadImg(("data/images/logos/intro" + oss.str() + ".png").c_str());
        }
    }
    
    lastAnimTime = SDL_GetTicks(); anim=0;
    gpJeu->ecrit(1361, false, true, 32, 158, 256, 64);
}

void Generique::initNuit() {
    SDL_Rect dst;
    SDL_Surface* fond = gpJeu->loadImg("data/images/logos/nuit.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(fond, NULL, image, &dst);
    SDL_FreeSurface(fond);
    //SDL_FillRect(image, NULL, SDL_MapRGB(image->format, 0, 0, 0));
    gpJeu->ecrit(1366);
}

void Generique::initAide1() {
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
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,64-8,288,128);
    
    cadre(16,192+8,288,32);
    
#ifdef __PSP2__
    gpJeu->affiche(image, "Retour au jeu : Croix - Suite : Droite", 24, 208);
#else
    gpJeu->affiche(image, "Retour au jeu : Entrée - Suite : Droite", 24, 208);
#endif
    
    int ligne = 64;
    Joueur* gpJoueur = gpJeu->getJoueur();
    
#ifdef __PSP2__
    gpJeu->affiche(image, "Lire / Ouvrir / Parler : Rond", 24, ligne); ligne+=16;
    gpJeu->affiche(image, "Valider / Passer texte : Croix", 24, ligne); ligne+=16;
    gpJeu->affiche(image, "Déplacer Link : Stick Gauche", 24, ligne); ligne+=16;
#else
    gpJeu->affiche(image, "Lire / Ouvrir / Parler : Espace", 24, ligne); ligne+=16;
    gpJeu->affiche(image, "Valider / Passer texte : Entrée", 24, ligne); ligne+=16;
    gpJeu->affiche(image, "Déplacer Link : Flèches de direction", 24, ligne); ligne+=16;
#endif
    if (gpJoueur->hasObjet(O_BOTTES)) {
#ifdef __PSP2__
        gpJeu->affiche(image, "Courir : Maintenir R", 24, ligne); 
#else
        gpJeu->affiche(image, "Courir : Shift maintenu ou Capslock", 24, ligne); 
#endif
        ligne+=16;}
    if (gpJoueur->getEpee()) {
#ifdef __PSP2__
        gpJeu->affiche(image, "Coup d'épée : Croix", 24, ligne); ligne+=16;
        gpJeu->affiche(image, "Attaque Tornade : Croix maintenu puis lâché", 24, ligne); 
#else
        gpJeu->affiche(image, "Coup d'épée : W ou Z", 24, ligne); ligne+=16;
        gpJeu->affiche(image, "Attaque Tornade : W ou Z maintenu puis lâché", 24, ligne); 
#endif
        ligne+=16;}
#ifdef __PSP2__
    gpJeu->affiche(image, "Menu de sélection d'objet : D-Pad Droit", 24, ligne); ligne+=16;
#else
    gpJeu->affiche(image, "Menu de sélection d'objet : Entrée", 24, ligne); ligne+=16;
#endif
    if (ligne < 176)
#ifdef __PSP2__
    gpJeu->affiche(image, "Utiliser l'objet sélectionné : Triangle", 24, ligne); ligne+=16;
#else
    gpJeu->affiche(image, "Utiliser l'objet sélectionné : X", 24, ligne); ligne+=16;
#endif
    if (gpJoueur->hasObjet(O_GANTS)) {
#ifdef __PSP2__
        if (ligne < 176) gpJeu->affiche(image, "Porter : Croix", 24, ligne); 
#else
        if (ligne < 176) gpJeu->affiche(image, "Porter : C", 24, ligne); 
#endif
        ligne+=16;}
    if (gpJoueur->hasObjet(O_CARTE)) {
        if (ligne < 176) 
#ifdef __PSP2__
            gpJeu->affiche(image, "Afficher la carte : L (extérieur ou donjons)", 24, ligne);
#else
            gpJeu->affiche(image, "Afficher la carte : P (extérieur ou donjons)", 24, ligne);
#endif
    } else 
        if (ligne < 176) 
#ifdef __PSP2__
            gpJeu->affiche(image, "Afficher la carte : L (dans les donjons)", 24, ligne);
#else
            gpJeu->affiche(image, "Afficher la carte : P (dans les donjons)", 24, ligne);
#endif
    ligne+=16;
    if (gpJoueur->hasObjet(O_ENCYCL)) {
#ifdef __PSP2__
        if (ligne < 176) gpJeu->affiche(image, "Afficher les monstres vaincus : D-Pad Haut", 24, ligne); 
#else
        if (ligne < 176) gpJeu->affiche(image, "Afficher les monstres vaincus : M", 24, ligne); 
#endif
        ligne+=16;}
    if (gpJoueur->hasObjet(O_POISSONS)) {
#ifdef __PSP2__
        if (ligne < 176) gpJeu->affiche(image, "Afficher la liste des poissons péchés : D-Pad Bas", 24, ligne); 
#else
        if (ligne < 176) gpJeu->affiche(image, "Afficher la liste des poissons péchés : L", 24, ligne); 
#endif
        ligne+=16;}
    if (gpJoueur->hasObjet(O_SAC_TROC)) {
#ifdef __PSP2__
        if (ligne < 176) gpJeu->affiche(image, "Afficher les items de troc : D-Pad Gauche", 24, ligne); 
#else
        if (ligne < 176) gpJeu->affiche(image, "Afficher les items de troc : I", 24, ligne); 
#endif
        ligne+=16;}
    if (gpJoueur->hasObjet(O_MASQUE)) {
#ifdef __PSP2__
        if (ligne < 176) gpJeu->affiche(image, "Transformation Oni Link : L + R", 24, ligne); 
#else
        if (ligne < 176) gpJeu->affiche(image, "Transformation Oni Link : O", 24, ligne); 
#endif
        ligne+=16;}
    if (ligne < 176)
#ifdef __PSP2__
    gpJeu->affiche(image, "Regarder autour : Stick Droite", 24, ligne); ligne+=16;
#else
    gpJeu->affiche(image, "Regarder autour : Ctrl et direction", 24, ligne); ligne+=16;
    if (ligne < 176)
    gpJeu->affiche(image, "Agrandir / Rétrécir: Ctrl et Entrée", 24, ligne); ligne+=16;
#endif
    if (ligne < 176)
#ifdef __PSP2__
    gpJeu->affiche(image, "Sauvegarder / Quitter : Start", 24, ligne); ligne+=16;
#else
    gpJeu->affiche(image, "Sauvegarder / Quitter : Echap", 24, ligne); ligne+=16;
#endif
    
    if (ligne >= 288) gpJeu->affiche(image, "AIDE 1/3", 40, 16);
    else gpJeu->affiche(image, "AIDE 1/2", 40, 16);
}

void Generique::initAide2() {
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
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,64-8,288,128);
    
    cadre(16,192+8,288,32);
    
    int ligne = 64-112;
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    ligne+=64;
    if (gpJoueur->hasObjet(O_BOTTES)) ligne+=16;
    if (gpJoueur->getEpee()) ligne+=32;
    if (ligne >= 64) 
#ifdef __PSP2__
    gpJeu->affiche(image, "Utiliser l'objet sélectionné : Triangle", 24, ligne); ligne+=16;
#else
    gpJeu->affiche(image, "Utiliser l'objet sélectionné : X", 24, ligne); ligne+=16;
#endif
    if (gpJoueur->hasObjet(O_GANTS)) {
#ifdef __PSP2__
        if (ligne >= 64) gpJeu->affiche(image, "Porter : Croix", 24, ligne); 
#else
        if (ligne >= 64) gpJeu->affiche(image, "Porter : C", 24, ligne); 
#endif
        ligne+=16;}
    if (gpJoueur->hasObjet(O_CARTE)) {
        if (ligne >= 64) 
#ifdef __PSP2__
            gpJeu->affiche(image, "Afficher la carte : L (extérieur ou donjons)", 24, ligne);
#else
            gpJeu->affiche(image, "Afficher la carte : P (extérieur ou donjons)", 24, ligne);
#endif
    } else 
        if (ligne >= 64) 
#ifdef __PSP2__
            gpJeu->affiche(image, "Afficher la carte : L (dans les donjons)", 24, ligne);
#else
            gpJeu->affiche(image, "Afficher la carte : P (dans les donjons)", 24, ligne);
#endif
    ligne+=16;
    if (gpJoueur->hasObjet(O_ENCYCL)) {
#ifdef __PSP2__
        if (ligne >= 64) gpJeu->affiche(image, "Afficher les monstres vaincus : D-Pad Haut", 24, ligne); 
#else
        if (ligne >= 64) gpJeu->affiche(image, "Afficher les monstres vaincus : M", 24, ligne); 
#endif
        ligne+=16;}
    if (gpJoueur->hasObjet(O_POISSONS)) {
#ifdef __PSP2__
        if (ligne >= 64) gpJeu->affiche(image, "Afficher la liste des poissons péchés : D-Pad Bas", 24, ligne); 
#else
        if (ligne >= 64) gpJeu->affiche(image, "Afficher la liste des poissons péchés : L", 24, ligne); 
#endif
        ligne+=16;}
    if (gpJoueur->hasObjet(O_SAC_TROC)) {
#ifdef __PSP2__
        if (ligne >= 64) gpJeu->affiche(image, "Afficher les items de troc : D-Pad Gauche", 24, ligne); 
#else
        if (ligne >= 64) gpJeu->affiche(image, "Afficher les items de troc : I", 24, ligne); 
#endif
        ligne+=16;}
    if (gpJoueur->hasObjet(O_MASQUE)) {
#ifdef __PSP2__
        if (ligne >= 64) gpJeu->affiche(image, "Transformation Oni Link : L + R", 24, ligne); 
#else
        if (ligne >= 64) gpJeu->affiche(image, "Transformation Oni Link : O", 24, ligne); 
#endif
        ligne+=16;}
    if (ligne >= 176) {
        gpJeu->affiche(image, "HELP 2/3", 40, 16); 
#ifdef __PSP2__
        gpJeu->affiche(image, "Retour au jeu : Croix - Suite : Droite", 24, 208);
#else
        gpJeu->affiche(image, "Retour au jeu : Entrée - Suite : Droite", 24, 208);
#endif
        return;}
    if (ligne >= 64) 
#ifdef __PSP2__
    gpJeu->affiche(image, "Regarder autour : Stick Droite", 24, ligne); ligne+=16;
#else
    gpJeu->affiche(image, "Regarder autour : Ctrl et direction", 24, ligne); ligne+=16;
#endif
    if (ligne >= 176) {
        gpJeu->affiche(image, "AIDE 2/3", 40, 16); 
#ifdef __PSP2__
        gpJeu->affiche(image, "Retour au jeu : Croix - Suite : Droite", 24, 208);
#else
        gpJeu->affiche(image, "Retour au jeu : Entrée - Suite : Droite", 24, 208);
#endif
        return;}
#ifndef __PSP2__
    if (ligne >= 64) 
    gpJeu->affiche(image, "Agrandir / Rétrécir : Ctrl et Entrée", 24, ligne); ligne+=16;
#endif
    if (ligne >= 176) {
        gpJeu->affiche(image, "AIDE 2/3", 40, 16); 
#ifdef __PSP2__
        gpJeu->affiche(image, "Retour au jeu : Croix - Suite : Droite", 24, 208);
#else
        gpJeu->affiche(image, "Retour au jeu : Entrée - Suite : Droite", 24, 208);
#endif
        return;}
    if (ligne >= 64) 
#ifdef __PSP2__
    gpJeu->affiche(image, "Sauvegarder / Quitter : Start", 24, ligne); ligne+=16;
#else
    gpJeu->affiche(image, "Sauvegarder / Quitter : Echap", 24, ligne); ligne+=16;
#endif
    
    gpJeu->affiche(image, "AIDE 2/2", 40, 16);
#ifdef __PSP2__
    gpJeu->affiche(image, "Retour au jeu : Croix - Précédent : Gauche", 24, 208);
#else
    gpJeu->affiche(image, "Retour au jeu : Entrée - Précédent : Gauche", 24, 208);
#endif
}

bool Generique::initAide3() {
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
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,64-8,288,128);
    
    cadre(16,192+8,288,32);
    
    gpJeu->affiche(image, "AIDE 3/3", 40, 16);
    
#ifdef __PSP2__
    gpJeu->affiche(image, "Retour au jeu : Croix - Précédent : Gauche", 24, 208);
#else
    gpJeu->affiche(image, "Retour au jeu : Entrée - Précédent : Gauche", 24, 208);
#endif
    
    int ligne = 64-112*2;
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    ligne+=64;
    if (gpJoueur->hasObjet(O_BOTTES)) ligne+=16;
    if (gpJoueur->getEpee()) ligne+=32;
    ligne+=16;
    if (gpJoueur->hasObjet(O_GANTS)) ligne+=16;
    ligne+=16;
    if (gpJoueur->hasObjet(O_ENCYCL)) ligne+=16;
    if (gpJoueur->hasObjet(O_POISSONS)) ligne+=16;
    if (gpJoueur->hasObjet(O_SAC_TROC)) ligne+=16;
    if (gpJoueur->hasObjet(O_MASQUE)) ligne+=16;
    if (ligne >= 64) 
#ifdef __PSP2__
    gpJeu->affiche(image, "Regarder autour : Stick Droite", 24, ligne); ligne+=16;
#else
    gpJeu->affiche(image, "Regarder autour : Ctrl et direction", 24, ligne); ligne+=16;
    if (ligne >= 64) 
    gpJeu->affiche(image, "Agrandir / Rétrécir : Ctrl et Entrée", 24, ligne); ligne+=16;
#endif
    if (ligne >= 64) 
#ifdef __PSP2__
        gpJeu->affiche(image, "Sauvegarder / Quitter : Start", 24, ligne);
#else
        gpJeu->affiche(image, "Sauvegarder / Quitter : Echap", 24, ligne);
#endif
    else {
        initAide2();
        return false;
    }
    return true;
}


void Generique::initTroc() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    SDL_Surface* imageCadreTroc = gpJeu->loadImg("data/images/menu/cadrestroc.png");
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
        }
            
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
    
    for (int i = 0; i < 5; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 112; dst.y = 0; 
    SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 112; dst.y = 16; 
    SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 112; dst.y = 32; 
    SDL_BlitSurface(imageCadreTroc, &src, image, &dst);
    
    
    SDL_Surface* tmp = imageCadre;
    imageCadre = imageCadreTroc;
    
    cadre(16,48,288,176);
    
    imageCadre = tmp;
    
    SDL_FreeSurface(imageCadreTroc);
    
    gpJeu->affiche(image, "SAC DE TROC", 38-3, 16);
    
    int ligne = 58;
    int colonne = 44;
    ostringstream oss;
    Joueur* gpJoueur = gpJeu->getJoueur();
    src.w=16; src.h=16;
    
    for (int i = 0; i < 16; i++) {
        
        if (gpJoueur->getTroc(i)>-1) {
            
            src.x=i*16; src.y=153;
            dst.x=colonne-20; dst.y=ligne;
            
            SDL_BlitSurface(gpJeu->getImageObjets(), &src, image, &dst);
            
            oss.str(""); oss<<gpJoueur->getTroc(i);
        
            switch (i) {
                case 0 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" SACS DE RIZ", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" SAC DE RIZ", colonne, ligne); break;
                case 1 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" BOCAUX D'EPICES", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" BOCAL D'EPICES", colonne, ligne); break;
                case 2 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" SACS D'OLIVES", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" SAC D'OLIVES", colonne, ligne); break;
                case 3 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" PERLES", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" PERLE", colonne, ligne); break;
                case 4 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" PLUMES", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" PLUME", colonne, ligne); break;
                case 5 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" POULETS", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" POULET", colonne, ligne); break;
                case 6 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" TAPISSERIES", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" TAPISSERIE", colonne, ligne); break;
                case 7 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" AMULETTES", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" AMULETTE", colonne, ligne); break;
                case 8 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" PARFUMS", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" PARFUM", colonne, ligne); break;
                case 9 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" ROCS MAGMA", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" ROC MAGMA", colonne, ligne); break;
                case 10 : 
                    if (gpJoueur->getTroc(i)>1)
                        gpJeu->affiche(image, oss.str()+" ROCS GIVRE", colonne, ligne);
                    else
                        gpJeu->affiche(image, oss.str()+" ROC GIVRE", colonne, ligne); break;
                case 11 : gpJeu->affiche(image, oss.str()+" POIVRON", colonne, ligne); break;
                case 12 : gpJeu->affiche(image, oss.str()+" ROUAGE", colonne, ligne); break;
                case 13 : gpJeu->affiche(image, oss.str()+" JAUGE", colonne, ligne); break;
                case 14 : gpJeu->affiche(image, oss.str()+" ROUE", colonne, ligne); break;
                case 15 : gpJeu->affiche(image, oss.str()+" SOURCE D'ENERGIE", colonne, ligne); break;
        }
        
        }
        ligne+=20;
        if (ligne > 198) {ligne=58; colonne+=136;}
    }
}



void Generique::initRang(int i) {
    
    switch (i) {
        case 0 :
            cadre(64+8,96,192-16,48);
            if (gpJeu->getKeyboard()->getRang(i) 
            && gpJeu->getKeyboard()->getRang(i+3) 
            && gpJeu->getKeyboard()->getRang(i+6)) 
                gpJeu->affiche(image, "RANG : Héros Légendaire", 72+8, 104);
            else if ((gpJeu->getKeyboard()->getRang(i) && gpJeu->getKeyboard()->getRang(i+3))
            || (gpJeu->getKeyboard()->getRang(i+3) && gpJeu->getKeyboard()->getRang(i+6))) 
                gpJeu->affiche(image, "RANG : Héros des deux Mondes", 72+8, 104);
            else if (gpJeu->getKeyboard()->getRang(i)) 
                gpJeu->affiche(image, "RANG : Héros d'Hyrule", 72+8, 104);
            else if (gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANG : Héros de Termina", 72+8, 104);
            else if (gpJeu->getKeyboard()->getRang(i+6)) 
                gpJeu->affiche(image, "RANG : Héros du Temps", 72+8, 104);
            else gpJeu->affiche(image, "RANG : INCONNU", 72+8, 104);
            gpJeu->affiche(image, "Finir le jeu à 100%.", 72+8, 120);
            break;
        case 1 :
            cadre(64,80,192+16,80);
            int l; l=88;
            if (gpJeu->getKeyboard()->getRang(i) 
            && gpJeu->getKeyboard()->getRang(i+3)
            && gpJeu->getKeyboard()->getRang(i+6)) 
                gpJeu->affiche(image, "RANG : Epéiste Légendaire", 72, l);
            else if ((gpJeu->getKeyboard()->getRang(i) && gpJeu->getKeyboard()->getRang(i+3)) 
            || (gpJeu->getKeyboard()->getRang(i) && gpJeu->getKeyboard()->getRang(i+6))
            || (gpJeu->getKeyboard()->getRang(i+3) && gpJeu->getKeyboard()->getRang(i+6)))
                gpJeu->affiche(image, "RANG : Maître Epéiste", 72, l);
            else if (gpJeu->getKeyboard()->getRang(i)) 
                gpJeu->affiche(image, "RANG : Frimeur", 72, l);
            else if (gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANG : Crâneur", 72, l);
            else if (gpJeu->getKeyboard()->getRang(i+6)) 
                gpJeu->affiche(image, "RANG : Orgueilleux", 72, l);
            else gpJeu->affiche(image, "RANG : INCONNU", 72, l);
            l+=16;
            gpJeu->affiche(image, "Finir le jeu sans mourir,", 72, l);l+=16;
            gpJeu->affiche(image, "avec 12 coeurs au maximum,", 72, l);l+=16;
            gpJeu->affiche(image, "et sans flacons.", 72, l);l+=16;
            break;
        case 2 :
            cadre(48,88,224,64);
            if (gpJeu->getKeyboard()->getRang(i) 
            && gpJeu->getKeyboard()->getRang(i+3)
            && gpJeu->getKeyboard()->getRang(i+6)) 
                gpJeu->affiche(image, "RANG : Marathonien Légendaire", 56, 96);
            else if ((gpJeu->getKeyboard()->getRang(i) && gpJeu->getKeyboard()->getRang(i+3))
            || (gpJeu->getKeyboard()->getRang(i+3) && gpJeu->getKeyboard()->getRang(i+6))) 
                gpJeu->affiche(image, "RANG : Marathonien des deux Mondes", 56, 96);
            else if (gpJeu->getKeyboard()->getRang(i)) 
                gpJeu->affiche(image, "RANG : Marathonien d'Hyrule", 56, 96);
            else if (gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANG : Marathonien de Termina", 56, 96);
            else if (gpJeu->getKeyboard()->getRang(i+6)) 
                gpJeu->affiche(image, "RANG : Marathonien du Temps", 56, 96);
            else gpJeu->affiche(image, "RANG : INCONNU", 56, 96);
            gpJeu->affiche(image, "Finir le jeu en moins de sept", 56, 112);
            gpJeu->affiche(image, "heures.", 56, 128);
            break;
    }
}

void Generique::cadre(int x, int y, int w, int h) {
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
}

void Generique::initScore() {
    SDL_FreeSurface(imageArbre);
    imageArbre = gpJeu->loadImg("data/images/logos/arbre.png");
    image = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
    
    SDL_Rect dst; 
    
    for (int i = 0; i < 320; i+=48) {
        dst.x = i;
        for (int j = 0; j < 240; j+=96) {
            dst.y = j;
            SDL_BlitSurface(imageArbre, NULL, image, &dst);
        }
    }
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    ostringstream oss;
    int pctg = 0;
    gpJeu->affiche(image, "SCORES :", 136, 10);
    
    int temps = gpJoueur->getTemps(0)+gpJoueur->getTemps(1)*60+gpJoueur->getTemps(2)*3600;
    if (temps < gpJeu->getKeyboard()->getTemps() || gpJeu->getKeyboard()->getTemps()==0) {
        gpJeu->getKeyboard()->setTemps(temps); gpJeu->getKeyboard()->saveP();}
        
    oss.str(""); 
    if (gpJoueur->getTemps(2)<10)oss<<"0";oss << gpJoueur->getTemps(2) << ":";
    if (gpJoueur->getTemps(1)<10)oss<<"0";oss << gpJoueur->getTemps(1) << ":";
    if (gpJoueur->getTemps(0)<10)oss<<"0";oss << gpJoueur->getTemps(0);
    gpJeu->affiche(image, ("Temps de jeu : " + oss.str()).c_str(), 10, 30);
    
    int tmp=gpJoueur->getMort();
    oss.str(""); oss << tmp;
    gpJeu->affiche(image, ("Mort " + oss.str() + " fois").c_str(), 160, 30);
    
    tmp=gpJoueur->nbQuarts();
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("1/4 Coeurs : " + oss.str() + " / 16").c_str(), 10, 50);

    tmp=gpJoueur->getNbGemmes();
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("Gemmes force : " + oss.str() + " / 200").c_str(), 160, 50);

    tmp=0;
    for (int i = 0; i < 16; i++) if (gpJoueur->hasObjet(i)) tmp++;
    for (int i = 21; i < 35; i++) if (gpJoueur->hasObjet(i)) tmp++;
    if (gpJoueur->hasObjet(O_ARC) == 5) tmp++;
    if (gpJoueur->hasObjet(O_GANTS) == 2) tmp++;
    if (gpJoueur->hasObjet(O_BONUS_FORCE) == 2) tmp++;
    if (gpJoueur->hasObjet(O_BONUS_DEFENSE) == 2) tmp++;
    tmp+=gpJoueur->getBouclier();
    for (int i = 0; i < 4; i++) if (gpJoueur->hasBouteille(i)) tmp++;
    tmp+=gpJoueur->getEpee();
    if (gpJoueur->getEpee() == 5) tmp--; // car que 4 épées
    tmp+=gpJoueur->getTunique();
    if (gpJoueur->getMagieMax() > 32) tmp++;
    tmp+=(gpJoueur->getFlecheMax()-30)/5;
    tmp+=(gpJoueur->getBombeMax()-10)/2;
    if (gpJoueur->getRubisMax()>0) tmp++;
    if (gpJoueur->getRubisMax()>99) tmp++;
    if (gpJoueur->getRubisMax()>200) tmp++;
    if (gpJoueur->getRubisMax()>500) tmp++;
    if (gpJoueur->getGanonMax()>0) tmp++;
    if (gpJoueur->getGanonMax()>99) tmp++;
    if (gpJoueur->getGanonMax()>200) tmp++;
    if (gpJoueur->getGanonMax()>500) tmp++;
    if (gpJoueur->getPieceMax()>0) tmp++;
    if (gpJoueur->getPieceMax()>99) tmp++;
    if (gpJoueur->getPieceMax()>200) tmp++;
    if (gpJoueur->getPieceMax()>500) tmp++;
    for (int i = 0; i < 3; i++) if (gpJoueur->hasMelodie(i)) tmp++;
    for (int i = 0; i < 3; i++) if (gpJoueur->hasMedaillon(i)) tmp++;
    for (int i = 0; i < 7; i++) if (gpJoueur->hasCristal(i)) tmp++;
    for (int j = 0; j < 15; j++) for (int i = 0; i < 3; i++) if (gpJoueur->getCle(j,i)) tmp++;
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("Objets: " + oss.str() + " / 139").c_str(), 10, 70);
    
    tmp=0;
    for (int i = 0; i < 16; i++) if (gpJoueur->getTroc(i) > -1) tmp++;
    if (gpJoueur->hasObjet(O_TROC1) < 10) tmp+=gpJoueur->hasObjet(O_TROC1);
    else tmp+=7;
    if (gpJoueur->hasObjet(O_TROC2) < 10) tmp+=gpJoueur->hasObjet(O_TROC2);
    else tmp+=7;
    if (gpJoueur->hasObjet(O_TROC3) < 10) tmp+=gpJoueur->hasObjet(O_TROC3);
    else tmp+=8;
    if (gpJoueur->hasObjet(O_TROC4) < 10) tmp+=gpJoueur->hasObjet(O_TROC4);
    else tmp+=7;
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("Objets de troc : " + oss.str() + " / 45").c_str(), 160, 70);
    
    tmp=gpJoueur->nbPoissons();
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("Poissons : " + oss.str() + " / 30").c_str(), 10, 90);
    
    
    tmp=gpJoueur->nbEnnemis();
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("Ennemis : " + oss.str() + " / 100").c_str(), 160, 90);
    
    pctg=(int)((pctg*100)/530);
    oss.str(""); oss << pctg;
    gpJeu->affiche(image, ("Tu as fini ce jeu à " + oss.str() + "%, félicitation !").c_str(), 
        10, 130);
    
    string result;
    int ligne = 170;
    gpJeu->affiche(image, "RANG : ", 10, ligne);
    
    if (gpJoueur->getMort()==0 && gpJoueur->hasBouteille(0)==0
        && gpJoueur->hasBouteille(1)==0 && gpJoueur->hasBouteille(2)==0
        && gpJoueur->hasBouteille(3)==0 && gpJoueur->getVieMax()==24) {
            if (gpJeu->getKeyboard()->getRang(1) && gpJeu->getKeyboard()->getRang(4)) 
                result="Epéiste Légendaire"; 
            else if (gpJeu->getKeyboard()->getRang(1))
                result="Maître Epéiste"; 
            else if (gpJeu->getKeyboard()->getRang(4))
                result="Maître Epéiste"; 
            else result="Orgueilleux"; 
            gpJeu->affiche(image, " - "+result, 52, ligne); ligne+=20;
            gpJeu->getKeyboard()->setRang(7); gpJeu->getKeyboard()->saveP();}
    else {
        if (pctg==100) {
            if (gpJeu->getKeyboard()->getRang(0) && gpJeu->getKeyboard()->getRang(3)) 
                result="Héros Légendaire"; 
            else if (gpJeu->getKeyboard()->getRang(0))
                result="Héros d'Hyrule"; 
            else if (gpJeu->getKeyboard()->getRang(3))
                result="Héros des deux Mondes"; 
            else result="Héros du Temps"; 
            gpJeu->getKeyboard()->setRang(6); gpJeu->getKeyboard()->saveP();}
        if (pctg<100) result="Perfectionniste";
        if (pctg<95) result="Fan de Zelda";
#ifdef __PSP2__
        if (pctg<90) result="Pro du clavier";
#else
		if (pctg<90) result="Pro du pad";
#endif
        if (pctg<85) result="Confirmé";
        if (pctg<80) result="Débutant";
        gpJeu->affiche(image, " - "+result, 52, ligne);
        ligne+=20;
    }
    
    if (gpJoueur->getMort()>=100) {
        result="Mort-vivant"; gpJeu->affiche(image, " - "+result, 52, ligne); ligne+=20;}
    else if (gpJoueur->getMort()>=50) {
        result="Kamikaze"; gpJeu->affiche(image, " - "+result, 52, ligne); ligne+=20;}
        
    if (temps<=25200) {
        if (gpJeu->getKeyboard()->getRang(2) && gpJeu->getKeyboard()->getRang(5)) 
            result="Marathonien Légendaire";
        else if (gpJeu->getKeyboard()->getRang(2)) 
            result="Marathonien d'Hyrule";
        else if (gpJeu->getKeyboard()->getRang(5)) 
            result="Marathonien des deux Mondes";
        else result="Marathonien du Temps"; 
        gpJeu->getKeyboard()->setRang(8); gpJeu->getKeyboard()->saveP();
        gpJeu->affiche(image, " - "+result, 52, ligne); ligne+=20;}
}

void Generique::draw(SDL_Surface* gpScreen) {
    SDL_Rect dst; dst.x = 0; dst.y = 0;
    SDL_BlitSurface(image, NULL, gpScreen, &dst);
}

void Generique::drawSelection(SDL_Surface* gpScreen, int ligne, int colonne) {
    draw(gpScreen);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 21; src.w = 16;src.x = 0;src.y=0;
    dst.x = 26+152*colonne; dst.y = 53+48*ligne;
    
    SDL_BlitSurface(imageCurseur, &src, gpScreen, &dst);
}

void Generique::drawOption(SDL_Surface* gpScreen, int ligne, int opt1, int opt2) {
    draw(gpScreen);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 21; src.w = 16;src.x = 0;src.y=0;
    dst.x = 26; dst.y = 69+64*ligne;
    
    SDL_BlitSurface(imageCurseur, &src, gpScreen, &dst);
    
    src.h = 16; src.w = 8;src.x = 0;src.y=0;
    dst.x = 136+16*opt1; dst.y = 56+16;
    SDL_BlitSurface(imageNiveau, &src, gpScreen, &dst);
                
    src.h = 16; src.w = 8;src.x = 0;src.y=0;
    dst.x = 136+16*opt2; dst.y = 56+16+64;
    SDL_BlitSurface(imageNiveau, &src, gpScreen, &dst);
}

void Generique::drawRecord(SDL_Surface* gpScreen, int ligne, int colonne) {
    draw(gpScreen);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 21; src.w = 16;src.x = 0;src.y=0;
    dst.x = 26+152*colonne; dst.y = 53+48*ligne;
    
    SDL_BlitSurface(imageCurseur, &src, gpScreen, &dst);
}

void Generique::drawEffacer(SDL_Surface* gpScreen, int ligne) {
    drawRecord(gpScreen, 3, 1);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 16; src.w = 16;src.x = 0;src.y=0;
    dst.x = 112; dst.y = 113+20*ligne;
    
    SDL_BlitSurface(imageFee, &src, gpScreen, &dst);
}

void Generique::drawCharger(SDL_Surface* gpScreen, int ligne, int ligne2) {
    drawSelection(gpScreen, ligne, 0);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 16; src.w = 16;src.x = 0;src.y=0;
    dst.x = 112; dst.y = 93+20*ligne2;
    
    SDL_BlitSurface(imageFee, &src, gpScreen, &dst);
}

void Generique::drawEffacerSave(SDL_Surface* gpScreen, int ligne, int ligne2) {
    drawSelection(gpScreen, ligne, 0);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 16; src.w = 16;src.x = 0;src.y=0;
    dst.x = 112; dst.y = 113+20*ligne2;
    
    SDL_BlitSurface(imageFee, &src, gpScreen, &dst);
}

void Generique::drawIntro(SDL_Surface* gpScreen, int etape) {
    SDL_Rect src;
    SDL_Rect dst;
    
    if(SDL_GetTicks() > lastAnimTime + 40) {
        lastAnimTime = SDL_GetTicks();
        anim++;
        if (anim > 31) anim = 0;
    }
                
    src.h = 16; src.w = 16;
    for (int j=0; j<240; j+=16) 
        for (int i=0; i<320; i+=16) {
            src.x = 16-anim%16;src.y=anim%16; dst.x = i; dst.y = j;
            if (i>16 && i<288 && j>144 && j<224) src.x+=32;
            SDL_BlitSurface(imageFond2, &src, gpScreen, &dst);
        }
                
    src.h = 32; src.w = 32;
    for (int j=0; j<240; j+=32) 
        for (int i=0; i<320; i+=32) {
            src.x = anim;src.y=anim; dst.x = i; dst.y = j;
            if (i>16 && i<288 && j>144 && j<224) src.x+=64;
            SDL_BlitSurface(imageFond1, &src, gpScreen, &dst);
        }
                
    src.h = 111; src.w = 320;
    src.x = 0; src.y=0; dst.x = 0; dst.y = 17;
    SDL_BlitSurface(imageIntro[etape], &src, gpScreen, &dst);
                
    gpJeu->getTexte()->draw(gpScreen);
}

void Generique::drawDebut(SDL_Surface* gpScreen) {
    SDL_Rect dst; dst.x = 0; dst.y = 0;
    SDL_BlitSurface(image, NULL, gpScreen, &dst);
    gpJeu->getTexte()->draw(gpScreen);
}
