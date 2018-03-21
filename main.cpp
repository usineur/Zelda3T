/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Keyboard.h"
#include "Generique.h"

#ifdef __vita__
#include <psp2/power.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#endif

SDL_Surface* init(bool* etire) {             // initialise SDL
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        printf("Could not load SDL : %s\n", SDL_GetError());
        exit(-1);
    }
    atexit(SDL_Quit);
    //if(SDL_InitSubSystem(SDL_INIT_AUDIO) == -1) *SOUND = false;

#ifndef __vita__
    SDL_WM_SetCaption("Time to Triumph",NULL);
    SDL_Surface* icon = SDL_LoadBMP("data/images/logos/ocarina.ico");
    SDL_SetColorKey(icon,SDL_SRCCOLORKEY,SDL_MapRGB(icon->format,0,0,0));
    SDL_WM_SetIcon(icon,NULL);
#endif

    SDL_ShowCursor(SDL_DISABLE);


#ifdef __vita__
    return SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
#else
    SDL_Rect** modes;
    int gBpp = 0;
    
    modes = SDL_ListModes(NULL,SDL_FULLSCREEN|SDL_HWSURFACE);
    if (modes == (SDL_Rect**)-1) gBpp = 1;
    else {
        for (int i = 0; modes[i]; ++i) {
	    if (modes[i]->w == 320 && modes[i]->h == 240) {
                gBpp = 1; break;
            }
        }
    }
    
    if(!gBpp) {
        *etire = true;
        return SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    } else {
        return SDL_SetVideoMode(320, 240, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    }
#endif
}

int main(int argc, char** argv) {
#ifdef __vita__
    sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DISABLE_AUTO_SUSPEND);
    scePowerSetArmClockFrequency(444);

    sceIoMkdir("ux0:data/z3t", 0777);
    sceIoMkdir("ux0:data/z3t/save", 0777);
#endif
    if (argc && argv); //pour éviter un warning.....
    
    std::srand(std::time(NULL));
    
    SDL_Rect src;
    SDL_Rect dst;
    src.w=640; src.h=480; src.y=0;src.x=0;dst.x=0; dst.y=0;
    
    SDL_Surface* gpScreen = NULL;
    
    int mode = 2; //mode=1;
    
    bool etire = false;
    
    gpScreen = init(&etire);
#ifdef __vita__
    int sh = 544;
    int sw = (float)gpScreen->w*((float)sh/(float)gpScreen->h);
    int x = (960 - sw)/2;
    SDL_SetVideoModeScaling(x, 0, sw, sh);

    SDL_Surface* gpScreen2 = SDL_SetVideoMode(320, 240, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
#else
    SDL_Surface* gpScreen2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
#endif
    SDL_Surface* gpScreen3 = NULL;
    
    Audio* gpAudio = new Audio();
    Jeu* gpJeu = new Jeu(gpAudio);
    Carte* gpCarte = new Carte(gpJeu);
    Encyclopedie* gpEncyclopedie = new Encyclopedie(gpJeu);
    Poissons* gpPoissons = new Poissons(gpJeu);
    Keyboard* gpKeyboard = new Keyboard(gpJeu, gpCarte, gpEncyclopedie, gpPoissons, 
        gpScreen, mode, etire);
    gpJeu->setKeyboard(gpKeyboard);
    Generique* gpGenerique = new Generique(gpJeu);
    gpJeu->setGenerique(gpGenerique);
    gpGenerique->initLogo();
    
    //gpJeu->init(0); //à virer
    
    bool gLoop = true;
    
    Uint32 lastAnimTime = SDL_GetTicks();
    
    while (gLoop) {
        
        if (gpKeyboard->gererClavier() == -1) {gLoop = false;}
        
        switch (gpKeyboard->getMode()) {
            case 0 : //jeu normal
                gpJeu->draw(gpScreen2); break;
            case 1 : //disclamer
            case 2 : //logo
            case 3 : //titre
            case 14 : //générique score
            case 17 : //menu d'aide 1
            case 18 : //menu d'aide 2
            case 24 : //menu d'aide 3
            case 25 : //items de troc
            case 28 : //image de fin
                gpGenerique->draw(gpScreen2); break;
            case 4 : //selection
                gpGenerique->drawSelection(gpScreen2, gpKeyboard->getLigne(), 
                    gpKeyboard->getColonne()); break;
            case 6 : //options
                gpGenerique->drawOption(gpScreen2, gpKeyboard->getLigneOption(),
                gpKeyboard->getVolume()/8, gpKeyboard->getVolson()/8); break;
            case 7 : //charger partie
                gpGenerique->drawCharger(gpScreen2, gpKeyboard->getLigne(), 
                    gpKeyboard->getLigneVal()); break;
            case 8 : //générique intro
                gpGenerique->drawIntro(gpScreen2, gpKeyboard->getIntro()); break;
            case 9 : //effacer partie
                gpGenerique->drawEffacerSave(gpScreen2, gpKeyboard->getLigne(), 
                    gpKeyboard->getLigneVal()); break;
            case 10 : //générique début chez link
                gpGenerique->drawDebut(gpScreen2); break;
            case 11 : //générique fin
                gpGenerique->drawFin(gpScreen2); break;
            case 12 : //carte
            case 22 : //carte téléportation
                gpCarte->draw(gpScreen2); break;
            case 13 : //encyclopédie des monstres
                gpEncyclopedie->draw(gpScreen2); break;
            case 15 : //records
            case 19 : //rang 100%
            case 20 : //rang ultime
            case 21 : //rang de rapidité
                gpGenerique->drawRecord(gpScreen2, gpKeyboard->getLigneRecord(),
                    gpKeyboard->getColonneRecord()); break;
            case 16 : //effacer record
                gpGenerique->drawEffacer(gpScreen2, gpKeyboard->getLigneVal()); break;
            case 23 : //encyclopédie des poissons
                gpPoissons->draw(gpScreen2); break;
            case 26 : //générique vers présent
            case 27 : //générique vers passé
                gpGenerique->drawToPresent(gpScreen2); break;
            default : break;
        }
        
        if (etire || !gpKeyboard->isFullScreen()) {
            SDL_FreeSurface(gpScreen3);
            gpScreen3 = zoomSurface (gpScreen2, 2, 2, 0);
            SDL_BlitSurface(gpScreen3, &src, gpScreen, &dst);
        } else {
            SDL_BlitSurface(gpScreen2, &src, gpScreen, &dst);
        }
        
        SDL_Flip(gpScreen);
        
        if (SDL_GetTicks() < lastAnimTime + 20) SDL_Delay(lastAnimTime+20-SDL_GetTicks());
        lastAnimTime = SDL_GetTicks();
    
    }
    
    SDL_FreeSurface(gpScreen2);
    SDL_FreeSurface(gpScreen3);
    
    delete gpPoissons;
    delete gpEncyclopedie;
    delete gpGenerique;
    delete gpKeyboard;
    delete gpCarte;
    delete gpJeu;
    delete gpAudio;
    
    SDL_ShowCursor(SDL_ENABLE);
    SDL_Quit();
    exit(0);
    
    return 0;
}
