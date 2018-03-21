/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL/SDL.h>

#include "Audio.h"

#ifdef __vita__
#include <sys/stat.h>
#endif

Audio::Audio() : musiqueId(0), specialId(0) {
    SOUND = true;
    music = NULL;
#ifdef __vita__
    f = NULL;
    mem = NULL;
#endif
    
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) == -1) SOUND = false;
    
    if (SOUND) {
#ifdef __vita__
        Mix_OpenAudio(22050, AUDIO_S16SYS, 1, 1024);
#else
        Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
#endif
        previous_volume = Mix_VolumeMusic(32);
        loadSounds();
        setVolson(32);
    }
}

Audio::~Audio() {
    if (SOUND) {
        freeSounds();
        Mix_PauseMusic();
        Mix_VolumeMusic(previous_volume);
        Mix_HaltMusic();
        freeMusic();
        Mix_CloseAudio();
    }
}

void Audio::setVolume(int volume) {
    if (SOUND) Mix_VolumeMusic(volume);
}

void Audio::setVolson(int volson) {
    if (SOUND) for (int i = 0; i < 44; i++) Mix_VolumeChunk(sons[i], volson);
}

void Audio::loadSounds() {
    sons = new Mix_Chunk*[44];

    sons[0] = getSound("text"); // lettres
    sons[1] = getSound("menu1"); // menu 1
    sons[2] = getSound("menu2"); // menu 2
    sons[3] = getSound("menu3"); // menu 3
    sons[4] = getSound("menu4"); // menu 4
    sons[5] = getSound("timewarp"); // time retour
    sons[6] = getSound("tombe"); // tombe (ennemi)
    sons[7] = getSound("hitenemy"); //shot 1
    sons[8] = getSound("killenemy"); // shot 2
    sons[9] = getSound("surprise"); // surprise
    sons[10] = getSound("monte"); // monte
    sons[11] = getSound("descend"); // descend
    sons[12] = getSound("chute"); // chute
    sons[13] = getSound("item"); // item
    sons[14] = getSound("rupee"); // rubis
    sons[15] = getSound("heart"); // coeur
    sons[16] = getSound("bomb"); // bombe
    sons[17] = getSound("textnext"); // suite texte
    sons[18] = getSound("textend"); // fin texte
    sons[19] = getSound("happy"); // trouve objet
    sons[20] = getSound("door"); // ouvre porte
    sons[21] = getSound("pics"); // pics contre mur
    sons[22] = getSound("sword"); // Epée
    sons[23] = getSound("SwordCharging"); // chargée
    sons[24] = getSound("Sword360"); // spin
    sons[25] = getSound("shoot"); // flèche
    sons[26] = getSound("hookshot"); // grappin
    sons[27] = getSound("stamp"); // pose bombe
    sons[28] = getSound("magic"); // magie
    sons[29] = getSound("burn"); // br˚le
    sons[30] = getSound("hammer"); // marteau
    sons[31] = getSound("plouf"); // plouf
    sons[32] = getSound("danger"); // danger
    sons[33] = getSound("hurt"); // link se blesse
    sons[34] = getSound("porte"); // porte objet
    sons[35] = getSound("lance"); // lance objet
    sons[36] = getSound("casse"); // casse objet
    sons[37] = getSound("charge"); // charge magie
    sons[38] = getSound("buisson"); // coupe buisson
    sons[39] = getSound("pousse"); // pousse caisse
	sons[40] = getSound("envol"); // chant envol
    sons[41] = getSound("inverse"); // hymne vide
    sons[42] = getSound("accelere"); // chant esprit
    sons[43] = getSound("splash"); // ...
}

void Audio::freeSounds() {
    if (SOUND) {
        for (int i = 0; i < 44; i++) Mix_FreeChunk(sons[i]);
        delete[] sons;
    }
}

void Audio::freeMusic() {
    Mix_FreeMusic(music);
#ifdef __vita__
    if (mem != NULL) {
        free(mem);
        mem = NULL;
    }
    if (f != NULL) {
        fclose(f);
        f = NULL;
    }
#endif
}

Mix_Chunk* Audio::getSound(const char* son) {
    char fSon[512];
#ifdef __vita__
    snprintf(fSon, sizeof(fSon), "%s/%s.ogg", "app0:data/sound", son);
#else
    snprintf(fSon, sizeof(fSon), "%s/%s.ogg", "data/sound", son);
#endif
    return Mix_LoadWAV(fSon);
}

Mix_Music* Audio::getMusic(const char* zik) {
    char fZik[512];
#ifdef __vita__
    struct stat info;
    snprintf(fZik, sizeof(fZik), "%s/%s.it", "app0:data/music", zik);
    stat(fZik, &info);
    f = fopen(fZik, "rb");
    mem = (char*)malloc(info.st_size);
    fread(mem, 1, info.st_size, f);
    return Mix_LoadMUS_RW(SDL_RWFromMem(mem, info.st_size));
#else
    snprintf(fZik, sizeof(fZik), "%s/%s.it", "data/music", zik);
    return Mix_LoadMUS(fZik);
#endif
}

void Audio::playSound(int id, int chl) {
    if (SOUND) Mix_PlayChannel(chl,sons[id],0);
}

void Audio::stopSound() {
    if (SOUND) {if (SOUND) Mix_HaltChannel(-1); musiqueId=0;}
}

void Audio::playMusic(int id) {
    if (SOUND) {
	if (id == 2 || id == 5 || id == 7 || id == 8 || id == 9 || id == 14) id = 1;
        if (id == 20 || id == 22 || id == 24) id = 17;
        if (id == 29) id = 19;
        if (id == 32 || id == 34 || id == 35 || id == 39 || id == 44) id = 31;
        if (id >= 61 && id <= 78) id = 61;
        if (id == 82 || id == 84 || id == 94 || id == 98 || id == 99
        || id == 101 || id == 107 || id == 108 || id == 109 || id == 112 
        || id == 117 || id == 118 || id == 122 || id == 128 || id == 129
        || id == 142 || id == 143 || id == 148 || id == 149) id = 81; //magasins
        if (id == 91 || id == 120 || id == 132) id = 85; //potions
        if (id == 102 || id == 136) id = 80; //bar
        if (id == 105 || id == 106 || id == 131 || id == 139 || id == 147) id = 95; //maire
        if (id == 152 || id == 153) id = 151; //temple temps
        if (musiqueId != id) {
	    musiqueId = id;            
            if (specialId == 0) {
		Mix_HaltMusic();
        freeMusic();
		music = choixMusique(id);
		Mix_PlayMusic(music,-1);
		specialId = 0;
	    }
        }
    }
}

bool Audio::isSpecial() {return (specialId>0);}

void Audio::stopMusic() {
    if (SOUND) Mix_HaltMusic();
}

void Audio::replayMusic() {
    if (SOUND) Mix_PlayMusic(music,-1);
}

Mix_Music* Audio::choixMusique(int id) {
    switch (id) {
	case 1 : case 2 : case 7 : return getMusic("PlaineP");
        case 3 : return getMusic("VilleCP");
        case 4 : return getMusic("TerresS");
        case 6 : return getMusic("BoisPerdus");
        case 8 : return getMusic("CimetiereP");
        case 10 : return getMusic("VillageMP");
        case 11 : return getMusic("LacP");
        case 12 : return getMusic("DesertP");
        case 13 : return getMusic("Cocorico");
        case 15 : return getMusic("MontP");
        case 16 : return getMusic("Foret");
        case 17 : return getMusic("Plaine");
        case 18 : return getMusic("Cite");
        case 19 : return getMusic("Chateau");
        case 21 : return getMusic("Lanelle");
        case 23 : return getMusic("Cimetiere");
        case 25 : return getMusic("VillageM");
        case 26 : return getMusic("Lac");
        case 27 : return getMusic("Desert");
        case 28 : return getMusic("VillageO");
        case 30 : return getMusic("Mont");
        case 31 : case 32 : case 34 : case 35 :
            return getMusic("Ombre");
        case 33 : return getMusic("VilleF");
        case 36 : return getMusic("BoisPerdusF");
        case 37 : return getMusic("Cascades");
        case 38 : return getMusic("CimetiereF");
        case 40 : return getMusic("VillageMF");
        case 41 : return getMusic("LacF");
        case 42 : return getMusic("DesertF");
        case 43 : return getMusic("VillageOF");
        case 45 : return getMusic("MontF");
        case 46 : return getMusic("Courage");
        case 47 : return getMusic("Sagesse");
        case 48 : return getMusic("Force");
        case 49 : return getMusic("Abysses");
        case 50 : return getMusic("PyramideF");
        case 51 : return getMusic("PyramideP");
        case 52 : return getMusic("Ordinn");
        case 53 : return getMusic("Air");
        case 54 : return getMusic("Glace");
        case 55 : return getMusic("Feu");
        case 56 : return getMusic("Titre");
        case 57 : return getMusic("DFinal");
        case 58 : return getMusic("Casino");
        case 59 : return getMusic("Gemme");
        case 60 : return getMusic("DestinationF");
        case 61 : return getMusic("Cave");
        case 79 : return getMusic("Home");
        case 80 : return getMusic("Bar");
        case 81 : return getMusic("Magasin");
        case 83 : return getMusic("Maison");
        case 85 : return getMusic("Potion");
        case 89 : return getMusic("Jeu");
        case 95 : return getMusic("Maire");
        case 119 : return getMusic("Cafe");
        case 144 : return getMusic("Sages");
        case 150 : return getMusic("Opera");
        case 151 : return getMusic("Epee");
        case 154 : return getMusic("Prison");
        case 155 : return getMusic("ChateauF");
        case 218 : return getMusic("probleme");
        case 219 : return getMusic("Epee");
        case 180 : return getMusic("Titre");
        case 190 : return getMusic("Selection");
        case 199 : return getMusic("Nuit");
        case 200 : return getMusic("Debut");
        default : return getMusic("Maison");
    }
}

void Audio::playSpecial(int id) {
    if (SOUND) {
        if (specialId != id) {
            Mix_HaltMusic();
            freeMusic();
            music = choixSpecial(id);
            Mix_PlayMusic(music,-1);
            specialId=id;
        }    
    }
}

void Audio::stopSpecial() {
    if (!specialId) return;
    int tmp = musiqueId;
    musiqueId = 0;
    specialId = 0;
    playMusic(tmp);
}

Mix_Music* Audio::choixSpecial(int id) {
    switch (id) {
	case 1 : return getMusic("Boss");
        case 2 : return getMusic("Mort");
        case 3 : return getMusic("Epee");
        case 4 : return getMusic("BossF");
        case 5 : return getMusic("Fin");
        case 6 : return getMusic("BossM");
        case 7 : return getMusic("Area81");
        case 8 : return getMusic("OniLink");
        case 9 : return getMusic("probleme");
        case 10 : return getMusic("Harpie");
        case 11 : return getMusic("Crabe");
        case 12 : return getMusic("Imp");
        case 13 : return getMusic("Masamune");
        case 14 : return getMusic("ZoraS");
        case 15 : return getMusic("Marlag");
        case 16 : return getMusic("Fantomas");
        case 17 : return getMusic("Vampire");
        case 18 : return getMusic("Araignee");
        case 19 : return getMusic("Plumes");
        case 20 : return getMusic("Garuda");
        case 21 : return getMusic("Heckran");
        case 22 : return getMusic("Sun");
        case 23 : return getMusic("Orcus");
        case 24 : return getMusic("Agahnim");
        case 25 : return getMusic("Zelda");
        case 26 : return getMusic("AgahnimFinal");
        case 27 : return getMusic("GanondorfFinal");
        case 28 : return getMusic("Quizz");
        case 29 : return getMusic("FinalBattle");
        default : return getMusic("Boss");
    }
}

