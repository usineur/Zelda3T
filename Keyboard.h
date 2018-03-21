/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "Carte.h"
#include "Encyclopedie.h"
#include "Poissons.h"

class Keyboard {
    public :
        Keyboard(Jeu* jeu, Carte* carte, Encyclopedie* encycl, Poissons* poissons,
            SDL_Surface* screen, int m, bool e);
        int gererClavier();
        int getMode();
        void setMode(int i);
        int getLigne();
        int getColonne();
        int getSave(int i);
        void setSave(int i, int val);
        int getLigneOption();
        int getVolume();
        int getVolson();
        int getLigneRecord();
        int getColonneRecord();
        int getTemps();
        void setTemps(int t);
        int getRang(int i);
        void setRang(int i);
        int getLigneVal();
        int getIntro();
        int getTelep();
        void setTelep(int i);
        void saveP();
        Carte* getCarte();
        int attendEntreeOuTemps(Uint32 t);
        int isFullScreen();
    private :
        void loadP();
        void loadOldP();
        int pollKey(SDL_Event event);
        void pollKeys(Uint8* keys);
        void toggleFullScreen();
        int buttonPressed(int i);
        int stickPosition(int stick, int direction);
        
        Jeu* gpJeu;
        Carte* gpCarte;
        Encyclopedie* gpEncyclopedie;
        Poissons* gpPoissons;
        int mode;
        int gFullScreen;
        SDL_Surface* gpScreen;
        int tmp;
        int tmpx;
        int tmpc;
        int tmpw;
        int tmpt;
        int tmpp;
        int tmpm;
        int tmpo;
        int tmptp;
        int tmpl;
        int tmpi;
        int ligne;
        int colonne;
        int save[3];
        int ligneOption;
        int volume;
        int volson;
        int ligneRecord;
        int colonneRecord;
        int temps;
        int rang[9];
        int ligneVal;
        int intro;
        int telep;
        bool etire;
        SDL_Event event;
        Uint8* keys;
        
#ifdef __vita__
        SDL_Joystick* joystick;
#endif
};

#endif  // Keyboard.h
