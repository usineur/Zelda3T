/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Texte.h"
#include "Menu.h"
#include "Joueur.h"
#include "Monde.h"
#include "Projectile.h"
#include "Jeu.h"
#include "Keyboard.h"

Texte::Texte(Jeu* jeu) : gpJeu(jeu), vitesse(40), av(0), x(0), y(0), w(0), h(0),
id(0), idsuiv(0), def(false), cadre(false), texte(""), buffer("") {
    lastAnimTime = SDL_GetTicks();
    imageFont = gpJeu->loadImg("data/images/texte/font.png");
    SDL_SetColorKey(imageFont,SDL_SRCCOLORKEY,SDL_MapRGB(imageFont->format,0,0,255));
    imageCoeur = gpJeu->loadImg("data/images/menu/coeur.png");
    SDL_SetColorKey(imageCoeur,SDL_SRCCOLORKEY,SDL_MapRGB(imageCoeur->format,0,0,255));
}

Texte::~Texte() {
    SDL_FreeSurface(imageFont);
    SDL_FreeSurface(imageCoeur);
}

void Texte::chercheText() {
    ostringstream os;
    ostringstream os2;
    int tmp;
    switch (id) {
        case 1 : texte = "Objet de troc*Parle à la bonne personne pour échanger."; break;
        case 2 : texte = "Tu ne peux pas pêcher ici, cherche un ponton."; break;
        case 3 : 
            tmp = 4-(gpJeu->getJoueur()->nbQuarts()%4);
            os << tmp;
            texte = "Tu as trouvé un quart de coeur !!!";
            if (tmp<4) buffer = "Encore "+os.str()+" et tu gagneras un coeur supplémentaire !!!";
            else buffer = "Ton nombre de coeurs vient d'augmenter !!!";
            break;
        case 4 : texte = "Ca te prend souvent de parler aux arbres ???"; break;
        case 5 : texte = "Maison de Link**Ne pas approcher."; break;
        case 6 : texte = "N : Vers le village Cocorico"; break;
        case 7 : texte = "E : Vers la cité d'Hyrule"; break;
        case 8 : texte = "Tu n'as rien attrapé."; break;
        case 9 : texte = "Tu as pêché une écrevisse!"; break;
        case 10 : texte = "Tu as pêché un éperlan!"; break;
        case 11 : texte = "Tu as pêché un poisson zèbre!"; break;
        case 12 : texte = "Tu as pêché un gobie!"; break;
        case 13 : texte = "Tu as pêché un crabe!"; break;
        case 14 : texte = "Tu as pêché une pibale!"; break;
        case 15 : texte = "Tu as pêché un vairon!"; break;
        case 16 : texte = "Tu as pêché un carassin doré!"; break;
        case 17 : texte = "Tu as pêché une ablette!"; break;
        case 18 : texte = "Tu as pêché un goujon!"; break;
        case 19 : texte = "Tu as pêché une loche!"; break;
        case 20 : texte = "Tu as pêché une épinoche!"; break;
        case 21 : texte = "Tu as pêché une grémille!"; break;
        case 22 : texte = "Tu as pêché une blennie!"; break;
        case 23 : texte = "Tu as pêché un magicarpe!"; buffer="Mais rien ne se passe..."; break;
        case 24 : texte = "Tu as pêché une truite!*C'est un gros poisson!"; break;
        case 25 : texte = "Tu as pêché un ayu!*C'est un gros poisson!"; break;
        case 26 : texte = "Tu as pêché une perche noire!*C'est un gros poisson!"; break;
        case 27 : texte = "Tu as pêché une anguille!*C'est un gros poisson!"; break;
        case 28 : texte = "Tu as pêché un poisson-chat!*C'est un gros poisson!"; break;
        case 29 : texte = "Tu as pêché un black-bass!*C'est un gros poisson!"; break;
        case 30 : texte = "Tu as pêché un huchon!*C'est un gros poisson!"; break;
        case 31 : texte = "Tu as pêché un barbeau!*C'est un gros poisson!"; break;
        case 32 : texte = "Tu as pêché une lamproie!*C'est un gros poisson!"; break;
        case 33 : texte = "Tu as pêché un hotu!*C'est un gros poisson!"; break;
        case 34 : texte = "Tu as pêché un saumon!*C'est un poisson énorme!"; break;
        case 35 : texte = "Tu as pêché un esturgeon!*C'est un poisson énorme!"; break;
        case 36 : texte = "Tu as pêché un omble chevalier!*C'est un poisson énorme!"; break;
        case 37 : texte = "Tu as pêché une carpe!*C'est un poisson énorme!"; break;
        case 38 : texte = "Tu as pêché un silure!*C'est un poisson énorme!"; break;
        case 39 : texte = "Tu as trouvé une gemme de force !**Troque-les en ville contre des prix."; break;
        case 40 : 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_DEVANT_CHEZ_LINK) {id=44; chercheText();break;}
            texte = "Bonjour Link!*Tu fais une drôle de tête, tu dormais ?"; idsuiv=41; break;
        case 41 : texte = "La princesse veux te voir de toute urgence au château!"; idsuiv=42; break;
        case 42 : texte = "..."; idsuiv=43; break;
        case 43 : texte = "..."; idsuiv=44; break;
        case 44 : texte = "Le château. A l'est d'ici, tu n'as tout de même pas oublié ?"; break;
        case 45 : texte = "Hum Hum..."; idsuiv=46; break;
#ifdef __PSP2__
        case 46 : texte = "TUTORIEL : Appuyez sur Rond près de quelqu'un pour lui parler, ou près d'une pancarte pour la lire."; break;
#else
        case 46 : texte = "TUTORIEL : Appuyez sur Espace près de quelqu'un pour lui parler, ou près d'une pancarte pour la lire."; break;
#endif
        case 47 : texte = "Tu n'as appris aucun thème.";
            if (gpJeu->getJoueur()->hasMelodie(0)) {id=48; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=57; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=59; chercheText();break;}
            break;
        case 48 : texte = "- CHANT DE L'ENVOL*- Ne rien jouer";
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=50; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=61; chercheText();break;}
            break;
        case 49 : texte = "- Chant de l'envol*- NE RIEN JOUER"; break;
        case 50 : texte = "- CHANT DE L'ENVOL*- Chant du temps inversé*- Ne rien jouer";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=53; chercheText();break;}
            break;
        case 51 : texte = "- Chant de l'envol*- CHANT DU TEMPS INVERSE*- Ne rien jouer"; break;
        case 52 : texte = "- Chant de l'envol*- Chant du temps inversé*- NE RIEN JOUER"; break;
        case 53 : texte = "- CHANT DE L'ENVOL*- Chant du temps inversé*- Chant du temps accéléré*- Ne rien jouer"; break;
        case 54 : texte = "- Chant de l'envol*- CHANT DU TEMPS INVERSE*- Chant du temps accéléré*- Ne rien jouer"; break;
        case 55 : texte = "- Chant de l'envol*- Chant du temps inversé*- CHANT DU TEMPS ACCELERE*- Ne rien jouer"; break;
        case 56 : texte = "- Chant de l'envol*- Chant du temps inversé*- Chant du temps accéléré*- NE RIEN JOUER"; break;
        case 57 : texte = "- CHANT DU TEMPS INVERSE*- Ne rien jouer";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=64; chercheText();break;}
            break;
        case 58 : texte = "- Chant du temps inversé*- NE RIEN JOUER"; break;
        case 59 : texte = "- CHANT DU TEMPS ACCELERE*- Ne rien jouer"; break;
        case 60 : texte = "- Chant du temps accéléré*- NE RIEN JOUER"; break;
        case 61 : texte = "- CHANT DE L'ENVOL*- Chant du temps accéléré*- Ne rien jouer"; break;
        case 62 : texte = "- Chant de l'envol*- CHANT DU TEMPS ACCELERE*- Ne rien jouer"; break;
        case 63 : texte = "- Chant de l'envol*- Chant du temps accéléré*- NE RIEN JOUER"; break;
        case 64 : texte = "- CHANT DU TEMPS INVERSE*- Chant du temps accéléré*- Ne rien jouer"; break;
        case 65 : texte = "- Chant du temps inversé*- CHANT DU TEMPS ACCELERE*- Ne rien jouer"; break;
        case 66 : texte = "- Chant du temps inversé*- Chant du temps accéléré*- NE RIEN JOUER"; break;
        case 67 : texte = "Sans effet..."; break;
        case 68 : texte = "Domaine de Link*Propriété privée"; break;
        case 69 : texte = "Cité d'Hyrule"; break;
        case 70 : texte = "Il n'y a pas l'air d'avoir de poissons ici..."; break;
        case 71 : texte = "N : Vers le Château d'Hyrule"; break;
        case 72 : texte = "Le château est plus au nord, dépêche-toi!"; break;
        case 73 : texte = "Le château est de l'autre côté du pont, hâte-toi!"; break;
        case 74 : texte = "La princesse t'attend au château, au nord d'ici."; break;
        case 75 : texte = "Tu n'as pas assez."; break;
        case 76 : texte = "Reviens si tu changes d'avis."; break;
        case 77 : 
            if (gpJeu->getJoueur()->getTroc(M_ROUAGE)>-1) {id=80; chercheText();break;}
            texte = "Un rouage contre un poulet et 100 rubis ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100
            || gpJeu->getJoueur()->getTroc(M_POULET)<1) idsuiv=75;
            break;
        case 78 : texte = "Un rouage contre un poulet et 100 rubis ?**              oui              NON ?"; idsuiv=76; break;
        case 79 : texte = "Tu as obtenu un rouage!*Va vite le donner à l'homme près des cascades!"; break;
        case 80 : 
            if ((gpJeu->getJoueur()->getCoeur(14) && gpJeu->getZone()==18)
            || (gpJeu->getJoueur()->getCoeur(15) && gpJeu->getZone()==3)) {
                id=82; chercheText();break;}
            texte = "Un quart de coeur contre un roc magma et un roc givre ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)<1) idsuiv=75;
            break;
        case 81 : texte = "Un quart de coeur contre un roc magma et un roc givre ?*              oui              NON ?"; idsuiv=76; break;
        case 82 : texte = "Désolé, je n'ai plus rien en stock."; break;
        case 83 : 
            if (gpJeu->getJoueur()->getRubisMax()>=200) {id=86; chercheText();break;}
            texte = "Une bourse pouvant contenir 200 rubis contre une plume et 10 rubis ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10
            || gpJeu->getJoueur()->getTroc(M_PLUME)<1) idsuiv=75;
            break;
        case 84 : texte = "Une bourse pouvant contenir 200 rubis contre une plume et 10 rubis ?*              oui              NON ?"; idsuiv=76; break;
        case 85 : texte = "Tu as obtenu une bourse moyenne!*Tu vas pouvoir transporter jusqu'à 200 rubis!"; break;
        case 86 : 
            if (gpJeu->getJoueur()->getRubisMax()>=500) {id=89; chercheText();break;}
            texte = "Une bourse pouvant contenir 500 rubis contre une tapisserie et 100 rubis ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100
            || gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1) idsuiv=75;
            break;
        case 87 : texte = "Une bourse pouvant contenir 500 rubis contre une tapisserie et 100 rubis ?*              oui              NON ?"; idsuiv=76; break;
        case 88 : texte = "Tu as obtenu une grande bourse!*Tu vas pouvoir transporter jusqu'à 500 rubis!!!"; break;
        case 89 : 
            if (gpJeu->getJoueur()->getRubisMax()==999) {id=82; chercheText();break;}
            texte = "Une bourse pouvant contenir 999 rubis contre une amulette, un roc magma et 250 rubis ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<250
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)<1) idsuiv=75;
            break;
        case 90 : texte = "Une bourse pouvant contenir 999 rubis contre une amulette, un roc magma et 250 rubis ?*              oui              NON ?"; idsuiv=76; break;
        case 91 : texte = "Tu as obtenu une énorme bourse!!!*Tu vas pouvoir transporter jusqu'à 999 rubis!!!"; break;
        case 92 : 
            texte = "Un poulet contre 2 sacs de riz et 3 sacs d'olives ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_RIZ)<2
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<3) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_POULET)>=99) idsuiv=95;
            break;
        case 93 : texte = "Un poulet contre 2 sacs de riz et 3 sacs d'olives ?**              oui              NON ?"; idsuiv=76; break;
        case 94 : texte = "Tu as obtenu un poulet!"; break;
        case 95 : texte = "Tu ne peux pas en porter plus..."; break;
        case 96 : 
            texte = "Une plume contre 2 bocaux d'épices et 2 sacs d'olives ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<2
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<2) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PLUME)>=99) idsuiv=95;
            break;
        case 97 : texte = "Une plume contre 2 bocaux d'épices et 2 sacs d'olives ?*              oui              NON ?"; idsuiv=76; break;
        case 98 : texte = "Tu as obtenu une plume!"; break;
        case 99 : 
            texte = "Un sac de riz contre 15 rubis ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_RIZ)>=99) idsuiv=95;
            break;
        case 100 : texte = "Un sac de riz contre 15 rubis ?**              oui              NON ?"; idsuiv=76; break;
        case 101 : texte = "Tu as obtenu un sac de riz!"; break;
        case 102 : 
            texte = "Un sac d'olives contre 10 rubis ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_OLIVES)>=99) idsuiv=95;
            break;
        case 103 : texte = "Un sac d'olives contre 10 rubis ?**              oui              NON ?"; idsuiv=76; break;
        case 104 : texte = "Tu as obtenu un sac d'olives!"; break;
        case 105 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>2) {id=112; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==2 
            && gpJeu->getJoueur()->getObjet()==15) {id=106; chercheText();break;}
            texte = "J'ai l'impression d'avoir passé ma vie à balayer...*Un de ces jours je partirai bien en voyage pour changer..."; break;
        case 106 : texte = "C'est une carte de voyage que tu as là ? *Tu veux bien me la donner ? Je rêve de faire du tourisme!"; idsuiv=107; break;
        case 107 : texte = "Je t'offre mon balai en échange, tu es d'accord ?*              OUI ?            non  "; idsuiv=109; break;
        case 108 : texte = "Je t'offre mon balai en échange, tu es d'accord ?*              oui              NON ?"; idsuiv=110; break;
        case 109 : texte = "Merci! Voici mon balai en récompense. C'est un très bon balai, il est dans ma famille depuis des siècles, tu fais une affaire!"; break;
        case 110 : texte = "J'imagine que je n'ai plus qu'à balayer dans ce cas..."; break;
        case 111 : texte = "Tu as troqué la carte de voyage contre un balai!"; break;
        case 112 : texte = "Bien, où vais-je partir ?"; break;
        case 113 : texte = "Parfois dans mes rêves je les mange à la broche..."; break;
        case 114 : texte = "Cette ville regorge de boutiques en tout genre, dommage qu'aucune d'entre elles ne m'intéresse..."; break;
        case 115 : texte = "Depuis que la paix est revenue, la princesse Zelda a fait énormément pour Hyrule. Il n'y aurait pas de villes aussi prospères que celle-ci sans elle."; break;
        case 116 : texte = "Le troc est le seul moyen de se procurer certains objets rares, ou de quoi faire sa cuisine."; break;
        case 117 : texte = "Ma maman me dit toujours de ne pas jouer avec les poules... Pourquoi ?"; break;
        case 118 : texte = "La princesse tient à ce que nous assurions la sécurité de la ville... Tout le monde sait pourtant que Ganon est mort..."; break;
        case 119 : texte = "Je préférerais dormir au château que monter la garde ici..."; break;
        case 120 : texte = "La vie est belle en Hyrule depuis que Ganon n'est plus une menace, merci encore Link!"; break;
        case 121 : texte = "Depuis le vol au château, la princesse a doublé la garde... et me revoilà de corvée..."; break;
        case 122 : texte = "Engagez-vous... Rengagez-vous qu'ils disaient..."; break;
        case 123 : texte = "J'ai entendu dire qu'un objet de valeur a été volé au palais, et depuis la princesse serait devenue complètement parano...";
            buffer="Ca devait être un objet auquel elle tenait beaucoup... Un miroir de sa collection sans doute..."; break;
        case 124 : texte = "Zzzzz... Zzzzz..."; break;
        case 125 : texte = "N : Vers le château de Ganon"; break;
        case 126 : 
            if (gpJeu->getJoueur()->hasObjet(O_PERLE)) {id=82; chercheText();break;}
            texte = "La perle de Lune contre une roue, une jauge, une source d'énergie et 100 Ganon d'or ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<100
            || gpJeu->getJoueur()->getTroc(M_ROUE)<1
            || gpJeu->getJoueur()->getTroc(M_JAUGE)<1
            || gpJeu->getJoueur()->getTroc(M_SOURCE_ENERGIE)<1) idsuiv=75;
            break;
        case 127 : texte = "La perle de Lune contre une roue, une jauge, une source d'énergie et 100 Ganon d'or ?*              oui              NON ?"; idsuiv=76; break;
        case 128 : texte = "Tu as obtenu la perle de Lune!*Tu retrouves ton apparence normale et l'usage de ton équipement!"; break;
        case 129 : 
            if (gpJeu->getJoueur()->getGanonMax()>=200) {id=132; chercheText();break;}
            texte = "Une bourse pouvant contenir 200 Ganon d'or contre une perle et 10 Ganon d'or ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10
            || gpJeu->getJoueur()->getTroc(M_PERLES)<1) idsuiv=75;
            break;
        case 130 : texte = "Une bourse pouvant contenir 200 Ganon d'or contre une perle et 10 Ganon d'or ?*              oui              NON ?"; idsuiv=76; break;
        case 131 : texte = "Tu as obtenu une bourse moyenne!*Tu vas pouvoir transporter jusqu'à 200 Ganon d'or!"; break;
        case 132 : 
            if (gpJeu->getJoueur()->getGanonMax()>=500) {id=135; chercheText();break;}
            texte = "Une bourse pouvant contenir 500 Ganon d'or contre une amulette et 100 Ganon d'or ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<100
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1) idsuiv=75;
            break;
        case 133 : texte = "Une bourse pouvant contenir 500 Ganon d'or contre une amulette et 100 Ganon d'or ?*              oui              NON ?"; idsuiv=76; break;
        case 134 : texte = "Tu as obtenu une grande bourse!*Tu vas pouvoir transporter jusqu'à 500 Ganon d'or!!!"; break;
        case 135 : 
            if (gpJeu->getJoueur()->getGanonMax()==999) {id=82; chercheText();break;}
            texte = "Une bourse pouvant contenir 999 Ganon d'or contre un parfum, un roc givre et 250 Ganon d'or ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<250
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)<1) idsuiv=75;
            break;
        case 136 : texte = "Une bourse pouvant contenir 999 Ganon d'or contre un parfum, un roc givre et 250 Ganon d'or ?*              oui              NON ?"; idsuiv=76; break;
        case 137 : texte = "Tu as obtenu une énorme bourse!!!*Tu vas pouvoir transporter jusqu'à 999 Ganon d'or!!!"; break;
        case 138 : 
            if (gpJeu->getJoueur()->getTroc(M_ROUE)>-1) {id=141; chercheText();break;}
            texte = "Une roue contre 3 bocaux d'épices ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<3) idsuiv=75;
            break;
        case 139 : texte = "Une roue contre 3 bocaux d'épices ?**              oui              NON ?"; idsuiv=76; break;
        case 140 : texte = "Tu as obtenu une roue!*...*Super..."; break;
        case 141 : 
            if (gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=82; chercheText();break;}
            texte = "Un sac de bombes contre 1 poivron et 3 bocaux d'épices ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_POIVRON)<1
            || gpJeu->getJoueur()->getTroc(M_EPICES)<3) idsuiv=75;
            break;
        case 142 : texte = "Un sac de bombes contre 1 poivron et 3 bocaux d'épices ?**              oui              NON ?"; idsuiv=76; break;
        case 143 : texte = "Tu as obtenu un sac de bombes!*Tu vas pouvoir déblayer des nouveaux chemins!"; break;
        case 144 : 
            texte = "Un roc magma contre une tapisserie, une amulette et un parfum ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)>=99) idsuiv=95;
            break;
        case 145 : texte = "Un roc magma contre une tapisserie, une amulette et un parfum ?*              oui              NON ?"; idsuiv=76; break;
        case 146 : texte = "Tu as obtenu un roc magma!"; break;
        case 147 : 
            texte = "Des perles contre 5 bocaux d'épices et 5 Ganon d'or ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<5
            || gpJeu->getJoueur()->getTroc(M_EPICES)<5) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PERLES)>=99) idsuiv=95;
            break;
        case 148 : texte = "Des perles contre 5 bocaux d'épices et 5 Ganon d'or ?**              oui              NON ?"; idsuiv=76; break;
        case 149 : texte = "Tu as obtenu des perles!"; break;
        case 150 : 
            texte = "Un bocal d'épices contre 10 Ganon d'or ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_EPICES)>=99) idsuiv=95;
            break;
        case 151 : texte = "Un bocal d'épices contre 10 Ganon d'or ?**              oui              NON ?"; idsuiv=76; break;
        case 152 : texte = "Tu as obtenu un bocal d'épices!"; break;
        case 153 : texte = "Hi! Hi! Hiiiiiiii!"; break;
        case 154 : texte = "L'autre soir le barman n'avait plus de bière...*Ganon est devenu rouge de colère et a tout détruit...*Au final plus personne n'a rien à boire..."; break;
        case 155 : texte = "Les maisons détruites étaient celles d'opposants à Ganon..."; 
            buffer="Le bar est détruit lui aussi, mais... ...pour d'autres raisons..."; break;
        case 156 : texte = "La place du marché est la principale activité de la ville maintenant que le bar a été détruit..."; break;
        case 157 : 
            if (gpJeu->getJoueur()->hasObjet(O_PERLE)) texte = "Tu as obtenu la perle de Lune ?*Enfin vu le résultat c'était peut-être pas une affaire...";
            else texte = "La perle de Lune permet de retrouver une apparence humaine, mais le marchand qui en a une la vend beaucoup trop chère..."; break;
        case 158 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "N : Terres Sacrées - Camping interdit"; break;
        case 159 : 
            if (gpJeu->getJoueur()->getPieceMax()>=200) {id=162; chercheText();break;}
            texte = "Une bourse pouvant contenir 200 pièces d'or contre un poulet et 10 pièces d'or ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<10
            || gpJeu->getJoueur()->getTroc(M_POULET)<1) idsuiv=75;
            break;
        case 160 : texte = "Une bourse pouvant contenir 200 pièces d'or contre un poulet et 10 pièces d'or ?*              oui              NON ?"; idsuiv=76; break;
        case 161 : texte = "Tu as obtenu une bourse moyenne!*Tu vas pouvoir transporter jusqu'à 200 pièces d'or!"; break;
        case 162 : 
            if (gpJeu->getJoueur()->getPieceMax()>=500) {id=165; chercheText();break;}
            texte = "Une bourse pouvant contenir 500 pièces d'or contre un parfum et 100 pièces d'or ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<100
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            break;
        case 163 : texte = "Une bourse pouvant contenir 500 pièces d'or contre un parfum et 100 pièces d'or ?*              oui              NON ?"; idsuiv=76; break;
        case 164 : texte = "Tu as obtenu une grande bourse!*Tu vas pouvoir transporter jusqu'à 500 pièces d'or!!!"; break;
        case 165 : 
            if (gpJeu->getJoueur()->getPieceMax()==999) {id=82; chercheText();break;}
            texte = "Une bourse pouvant contenir 999 pièces d'or contre une tapisserie, un roc magma et 250 pièces d'or ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<250
            || gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)<1) idsuiv=75;
            break;
        case 166 : texte = "Une bourse pouvant contenir 999 pièces d'or contre une tapisserie, un roc magma et 250 pièces d'or ?*              oui              NON ?"; idsuiv=76; break;
        case 167 : texte = "Tu as obtenu une énorme bourse!!!*Tu vas pouvoir transporter jusqu'à 999 pièces d'or!!!"; break;
        case 168 : 
            texte = "Une amulette contre 1 poulet et 2 sacs d'olives ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_POULET)<1
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<2) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_AMULETTE)>=99) idsuiv=95;
            break;
        case 169 : texte = "Une amulette contre 1 poulet et 2 sacs d'olives ?*              oui              NON ?"; idsuiv=76; break;
        case 170 : texte = "Tu as obtenu une amulette!"; break;
        case 171 : 
            texte = "Une plume contre un bocal d'épices et un sac d'olives ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<1
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PLUME)>=99) idsuiv=95;
            break;
        case 172 : texte = "Une plume contre un bocal d'épices et un sac d'olives ?*              oui              NON ?"; idsuiv=76; break;
        case 173 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Avec tous ces loups, quitter le village est devenu très dangereux..."; break;
        case 174 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Tes armes ressemblent à celles des chevaliers...*Tu as déjà affronté des loups avec ?"; break;
        case 175 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Je déteste les poules, mais si les loups pénètrent dans le village, ils n'oseront peut-être pas approcher..."; break;
        case 176 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Les torches aux entrées du village tiennent les loups à l'écart, mais ils approchent de plus en plus chaque jour..."; break;
        case 177 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Le chef du village a fait construire un bar dernièrement... D'après les rumeurs il aurait agit ainsi pour attirer les chevaliers hyliens et nous faire bénéficier de leur protection..."; break;
        case 178 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (!gpJeu->getJoueur()->getPieceMax()) {id=771; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>3) {id=185; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==3 
            && gpJeu->getJoueur()->getObjet()==15) {id=179; chercheText();break;}
            texte = "Quand les choses vont mal, je fais des confitures pour m'occuper... Mais en cette saison il va falloir que je trouve une autre activité..."; break;
        case 179 : texte = "Tu as un balai à me proposer ?*Je sens une vocation naître en moi... Tu me le cèdes contre mon dernier pot de confiture ?"; idsuiv=180; break;
        case 180 : texte = "Ce balai contre un pot de confiture, ok ?**              OUI ?            non  "; idsuiv=182; break;
        case 181 : texte = "Ce balai contre un pot de confiture, ok ?**              oui              NON ?"; idsuiv=183; break;
        case 182 : texte = "Cool! Je vais pouvoir me changer les idées, et peut-être même faire fuir les loups avec ce balai!"; break;
        case 183 : texte = "Je suis sûre que tu me le donneras tôt ou tard..."; break;
        case 184 : texte = "Tu as troqué le balai contre un pot de confiture!"; break;
        case 185 : texte = "Donner c'est donner!"; break;
        case 186 : texte = "Château d'Hyrule"; break;
        case 187 : texte = "N : Vers le cimetière"; break;
        case 188 : texte = "Bienvenue au château, Messire Link!"; break;
        case 189 : texte = "Nous avons ordre de vous laisser passer."; break;
        case 190 : texte = "Château de Ganon"; break;
        case 191 : 
            texte = "5 Ganon d'or et nous te laissons aller et venir au château ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<5) idsuiv=75;
            break;
        case 192 : texte = "5 Ganon d'or et nous te laissons aller et venir au château ?*              oui              NON ?"; idsuiv=76; break;
        case 193 : texte = "Tu peux entrer."; break;
        case 194 : texte = "QUE LE CHEMIN DE LA TRIFORCE TE SOIT OUVERT...*VOIS APPARAITRE LE TEMPLE DE LA TRIFORCE!"; break;
        case 195 : texte = "O : Vers le Château d'Hyrule"; break;
        case 196 : texte = "N : Vers les cascades"; break;
        case 197 : texte = "E : Entrée des bois perdus"; break;
        case 198 : 
            tmp = 6-(gpJeu->getJoueur()->nbCristaux());
            os << tmp;
            texte = "Tu as trouvé un cristal magique !!!";
            if (tmp>0) buffer = "Encore "+os.str()+" à trouver !";
            else buffer = "Tu les as enfin tous !!!";
            break;
        case 199 : texte = "Souhaites-tu sauvegarder ta partie ?**                    ? OUI ?*                      non  "; break;
        case 200 : texte = "Souhaites-tu sauvegarder ta partie ?**                      oui  *                    ? NON ?"; break;
        case 201 : texte = "Partie sauvegardée."; break;
        
        case 202 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>6) {id=209; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==6 
            && gpJeu->getJoueur()->getObjet()==11) {id=203; chercheText();break;}
            texte = "Je construis un opéra ici, je n'ai pas le temps de bavarder durant la pause!"; 
            buffer="En plus j'ai perdu mon accessoire vedette..."; break;
        case 203 : texte = "Tu as trouvé mon crâne fétiche ???*Je l'avais oublié en prison...*Rend-le-moi! Je te serais éternellement redevable!"; idsuiv=204; break;
        case 204 : texte = "Ce crâne contre ma gratitude, ok ?**              OUI ?            non  "; idsuiv=206; break;
        case 205 : texte = "Ce crâne contre ma gratitude, ok ?**              oui              NON ?"; idsuiv=207; break;
        case 206 : texte = "Merci! Je retrouve toute ma motivation! Je vais achever cet opéra!"; buffer="Après une pause..."; break;
        case 207 : texte = "Voleur..."; break;
        case 208 : texte = "Tu as troqué le crâne contre une reconnaissance de dette!"; break;
        case 209 : texte = "Etre ou ne pas être ? Telle est la question..."; buffer="Le ton est bon ?"; break;
        case 210 : texte = "Temple du Courage**Courage, fuyez!"; break;
        case 211 : texte = "Bienvenue chez Tingle!"; break;
        case 212 : texte = "Temple de l'Air**Risque de rhume!"; break;
        case 213 : texte = "S : Vers le village des Mouettes"; break;
        case 214 : texte = "Village des Mouettes"; break;
        case 215 : 
            texte = "Une tapisserie contre 2 perles et 5 bocaux d'épices ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_PERLES)<2
            || gpJeu->getJoueur()->getTroc(M_EPICES)<5) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)>=99) idsuiv=95;
            break;
        case 216 : texte = "Une tapisserie contre 2 perles et 5 bocaux d'épices ?*              oui              NON ?"; idsuiv=76; break;
        case 217 : texte = "Tu as obtenu une tapisserie!"; break;
        case 218 : 
            texte = "Une amulette contre 5 poulets et 5 sacs d'olives ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_POULET)<5
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<5) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_AMULETTE)>=99) idsuiv=95;
            break;
        case 219 : texte = "Une amulette contre 5 poulets et 5 sacs d'olives ?*              oui              NON ?"; idsuiv=76; break;
        case 220 : 
            texte = "Des perles contre 2 bocaux d'épices et 2 sacs de riz ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<2
            || gpJeu->getJoueur()->getTroc(M_RIZ)<2) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PERLES)>=99) idsuiv=95;
            break;
        case 221 : texte = "Des perles contre 2 bocaux d'épices et 2 sacs de riz ?*              oui              NON ?"; idsuiv=76; break;
        case 222 : 
            texte = "Un sac de riz contre 1 sac d'olives et 2 rubis? *              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<2
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_RIZ)>=99) idsuiv=95;
            break;
        case 223 : texte = "Un sac de riz contre 1 sac d'olives et 2 rubis? *              oui              NON ?"; idsuiv=76; break;
        case 224 : 
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)==0) 
                texte = "Les hommes du village sont tous obnubilés par le concours de pêche...*Je me demande qui gagnera..."; 
            else if (gpJeu->getJoueur()->hasObjet(O_POISSONS)==0)
                {texte = "Tu participes au concours de pêche ?*...*..."; buffer="Finalement tu es comme tous les autres...";} 
            else {texte = "Tu as gagné le concours de pêche ?*...*..."; buffer="Je suis ta plus grande fan!!!";}
            break;
        case 225 : 
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)==0) 
                texte = "Un stand de pêche vient d'ouvrir à l'ouest du village...*Le proprio organise un grand concours de pêche pour inaugurer sa boutique."; 
            else if (gpJeu->getJoueur()->hasObjet(O_POISSONS)==0)
                {texte = "Tu participes aussi au concours de pêche ? *C'est désespérant, je n'arrive pas à trouver plus de 3 sortes de poissons...";} 
            else {texte = "Depuis que le concours de pêche est fini, chacun est retourné à ses activités.";}
            break;
        case 226 : texte = "Vi l ge     Mo  t  s"; break;
        case 227 : 
            texte = "Repaire des Preux Chevaliers";
            if (gpJeu->getJoueur()->getAvancement()<GANON_CAPTURE)
            texte += "**NB : Si nous ne sommes pas là, passez voir à la taverne."; break;
        case 228 :
            if (gpJeu->getJoueur()->getGemme(91)) {id=230; chercheText();break;}
            texte = "Une gemme de force contre 2 perles ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_PERLES)<2) idsuiv=75;
            break;
        case 229 : texte = "Une gemme de force contre 2 perles ?**              oui              NON ?"; idsuiv=76; break;
        case 230 : 
            if (gpJeu->getJoueur()->getGemme(92)) {id=232; chercheText();break;}
            texte = "Une gemme de force contre 2 plumes ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_PLUME)<2) idsuiv=75;
            break;
        case 231 : texte = "Une gemme de force contre 2 plumes ?**              oui              NON ?"; idsuiv=76; break;
        case 232 : 
            if (gpJeu->getJoueur()->getGemme(93)) {id=82; chercheText();break;}
            texte = "Une gemme de force contre 2 poulets ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_POULET)<2) idsuiv=75;
            break;
        case 233 : texte = "Une gemme de force contre 2 poulets ?**              oui              NON ?"; idsuiv=76; break;
        case 234 : 
            texte = "Un poulet contre 1 sac de riz et 2 sacs d'olives ? *              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_OLIVES)<2
            || gpJeu->getJoueur()->getTroc(M_RIZ)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_POULET)>=99) idsuiv=95;
            break;
        case 235 : texte = "Un poulet contre 1 sac de riz et 2 sacs d'olives ? *              oui              NON ?"; idsuiv=76; break;
        case 236 : texte = "Au-delà de la frontière Sud d'Hyrule, on dit que se dresse un vaste océan..."; buffer="A la belle saison des mouettes franchissent les falaises qui nous séparent de la plage et viennent jusqu'à ce village."; break;
        case 237 : texte = "Ce village est sous la protection des chevaliers Hyliens, tu es donc en sécurité ici."; 
            if (gpJeu->getJoueur()->getAvancement()<GANON_CAPTURE) 
            buffer="Toutefois, depuis qu'une taverne a ouvert dans un village voisin, on ne voit plus beaucoup nos protecteurs dans le coin..."; break;
        case 238 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>2) {id=245; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==2 
            && gpJeu->getJoueur()->getObjet()==7) {id=239; chercheText();break;}
            texte = "Pas ici non plus ? Qu'est-ce que j'ai bien pu en faire ?"; break;
        case 239 : texte = "Tu as retrouvé le vase de ma belle-mère ??? *Ca fait des semaines qu'elle me force à le chercher partout! *Dépêche-toi de me le rendre!"; idsuiv=240; break;
        case 240 : texte = "Ce vase contre un truc que je viens de trouver, ok ?*              OUI ?            non  "; idsuiv=242; break;
        case 241 : texte = "Ce vase contre un truc que je viens de trouver, ok ?*              oui              NON ?"; idsuiv=243; break;
        case 242 : texte = "Sage décision petit."; break;
        case 243 : texte = "Tuez-le..."; break;
        case 244 : texte = "Tu as troqué la botte contre un marteau!"; break;
        case 245 : texte = "Ca te dirait d'entrer dans mon gang ?**              OUI ?            non  "; idsuiv=247; break;
        case 246 : texte = "Ca te dirait d'entrer dans mon gang ?**              oui              NON ?"; idsuiv=243; break;
        case 247 : texte = "Ha! Ha! Ha! *Je rigolais, tu es brave, mais sot! *Insecte ridicule! *Sais-tu bien qui nous sommes ?"; break;
        case 248 : texte = "Temple de la Sagesse**Seuls les sages sauront s'en tenir à l'écart."; break;
        case 249 : texte = "Stand de location de barques"; break;
        case 250 : texte = "Le stand de barques est fermé pour l'instant, je suis bien parti pour remporter le concours de pêche, j'en ai déjà 3 différents!"; break;
        case 251 : 
            if (gpJeu->getJoueur()->hasObjet(O_PALMES)) {id=1378; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_BARQUE)) {id=253; chercheText();break;}
            texte = "Veux-tu louer une barque pour 15 rubis ?**              OUI ?            non  "; idsuiv=253;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75;
            break;
        case 252 : texte = "Veux-tu louer une barque pour 15 rubis ?**              oui              NON ?"; idsuiv=76; break;
        case 253 : texte = "Tu peux utiliser la barque au ponton, amuse-toi bien, mais ne t'éloigne pas trop."; break;
        case 254 : texte = "(voix lointaine :) *J'ai dit... NE T'ELOIGNE PAS TROP!!!!"; break;
        case 255 : texte = "Grotte des Abysses**Merci de ne pas venir chercher le descendant des sages qui n'est pas caché là."; break;
        case 256 : texte = "Forgeron"; break;
        case 257 : texte = "Grande Pyramide"; break;
        case 258 : texte = "INDICE 1 : La pierre la plus à droite est la seconde. *INDICE 2 : Les pierres doivent être ôtées dans l'ordre de leurs poids."; break;
        case 259 : texte = "INDICE 3 : Les pierres de la queue doivent être ôtées avant celle de la nageoire. *INDICE 4 : La pierre de l'oeil doit être ôtée en 5ème."; break;
        case 260 : texte = "INDICE 5 : Les pierres aquatiques doivent être ôtées avant la dernière de la queue. *INDICE 6 : La pierre de l'oeil doit être ôtée après celle de la nageoire."; break;
        case 261 : texte = "INDICE 7 : La dernière pierre n'est pas l'oeil. *INDICE 8 : Les 2 pierres de la queue ne doivent pas être ôtées consécutivement."; break;
        case 262 : texte = "INDICE 9 : L'un des 9 indices est faux."; break;
        case 263 : texte = "N : Montagnes Rocheuses"; break;
        case 264 : texte = "Village Cocorico"; break;
        case 265 : 
            if (gpJeu->getJoueur()->hasObjet(O_BOTTES)) {id=82; chercheText();break;}
            texte = "Les bottes de Pégase contre une tapisserie et un parfum ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            break;
        case 266 : texte = "Les bottes de Pégase contre une tapisserie et un parfum ?*              oui              NON ?"; idsuiv=76; break;
        case 267 : texte = "Tu as obtenu les bottes de Pégase ! *Maintiens Shift ou appuie sur Capslock pour courir !"; break;
        case 268 : 
            texte = "Un parfum contre 3 plumes et 4 sacs de riz ? **              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_PLUME)<3
            || gpJeu->getJoueur()->getTroc(M_RIZ)<4) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PARFUM)>=99) idsuiv=95;
            break;
        case 269 : texte = "Un parfum contre 3 plumes et 4 sacs de riz ? **              oui              NON ?"; idsuiv=76; break;
        case 270 : texte = "Tu as obtenu un parfum !"; break;
        case 271 : 
            texte = "Un sac d'olives contre 15 rubis ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_OLIVES)>=99) idsuiv=95;
            break;
        case 272 : texte = "Un sac d'olives contre 15 rubis ?**              oui              NON ?"; idsuiv=76; break;
        case 273 : 
            texte = "Un bocal d'épices contre 20 rubis ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_EPICES)>=99) idsuiv=95;
            break;
        case 274 : texte = "Un bocal d'épices contre 20 rubis ?**              oui              NON ?"; idsuiv=76; break;
        case 275 : texte = "Le village Cocorico est un passage obligé pour les aventuriers qui souhaitent gravir la montagne. Les moins courageux se contentent d'atteindre le saloon..."; break;
        case 276 : texte = "Soit le bienvenu au village, Link! *Amuse-toi, mais évite tout de même de trop t'approcher des cactus..."; break;
        case 277 : texte = "Les bottes de Pégase permettent de se déplacer beaucoup plus rapidement. Cela donne un réel avantage au combat."; 
            if (gpJeu->getJoueur()->hasObjet(O_BOTTES)) buffer="Tu as ces bottes ? *Tu dois être plutôt fort désormais..."; break;
        case 278 : 
            texte = "Un roc givre contre une tapisserie, une amulette et un parfum ? *              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)>=99) idsuiv=95;
            break;
        case 279 : texte = "Un roc givre contre une tapisserie, une amulette et un parfum ? *              oui              NON ?"; idsuiv=76; break;
        case 280 : texte = "Tu as obtenu un roc givre !"; break;
        case 281 : 
            texte = "Des perles contre un bocal d'épices et un sac de riz ? *              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<1
            || gpJeu->getJoueur()->getTroc(M_RIZ)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PERLES)>=99) idsuiv=95;
            break;
        case 282 : texte = "Des perles contre un bocal d'épices et un sac de riz ? *              oui              NON ?"; idsuiv=76; break;
        case 283 : texte = "Ce village est sous la protection des 7 sages. Grâce à leur magie, il faut pas mal s'éloigner avant d'apercevoir les premiers loups..."; break;
        case 284 : texte = "Tu es ici au village le plus sûr que tu pourras trouver. Rien à voir avec le hameau du centre voué à disparaître, ni avec le village de l'Est défendu par des alcooliques..."; break;
        case 285 : texte = "Temple du Temps"; break;
        case 286 : texte = "Entrée de la mine"; break;
        case 287 : texte = "Temple de la Force**Réservé aux costauds."; break;
        case 288 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>2) {id=295; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==2 
            && gpJeu->getJoueur()->getObjet()==11) {id=289; chercheText();break;}
            texte = "Je me suis isolé du monde pour méditer sur le sens de la vie..."; buffer="...mais je dois bien admettre que certaines choses me manquent..."; break;
        case 289 : texte = "C'est une bouteille de vin que tu as là ??? *Donne-la-moi! Je te donnerai de l'or en échange !!!"; idsuiv=290; break;
        case 290 : texte = "Cette bouteille contre de l'or, ok ?**              OUI ?            non  "; idsuiv=292; break;
        case 291 : texte = "Cette bouteille contre de l'or, ok ?**              oui              NON ?"; idsuiv=293; break;
        case 292 : texte = "Je sens que j'approche de la vérité !"; break;
        case 293 : texte = "...*Je vais devoir méditer sur le sens de ton refus..."; break;
        case 294 : texte = "Tu as troqué la bouteille contre de la poudre d'or!"; break;
        case 295 : texte = "J'ai enfin trouvé le sens de la vie... Hic!"; break;
        case 296 : texte = "Tour de Glace**Le chemin s'ouvrira lorsque toutes les gemmes de force auront été trouvées."; break;
        case 297 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>1) {id=304; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==1 
            && gpJeu->getJoueur()->getObjet()==3) {id=298; chercheText();break;}
            texte = "D'ici je peux admirer le lac de lave... *D'ailleurs j'adore tout ce qui est rouge et qui brille."; break;
        case 298 : texte = "Mmm... c'est une magnifique gemme que tu as là... *Tu me la donnerais contre... une surprise ?"; idsuiv=299; break;
        case 299 : texte = "Cette gemme rouge contre une surprise, ok ?**              OUI ?            non  "; idsuiv=301; break;
        case 300 : texte = "Cette gemme rouge contre une surprise, ok ?**              oui              NON ?"; idsuiv=302; break;
        case 301 : texte = "Merci! Voilà ta surprise! Depuis le temps que je cherchais à m'en débarrasser..."; break;
        case 302 : texte = "Tans pis pour toi, pas de gemme pas de surprise."; break;
        case 303 : texte = "Tu as troqué la gemme rouge contre une enclume! Tu ne peux plus courir ni nager jusqu'à ce que tu t'en débarrasses!"; break;
        case 304 : texte = "Je me sens plus léger et plus riche, que du bonheur!"; break;
        case 305 : texte = "Temple du Feu"; break;
        case 306 : texte = "Nous sommes des rennes qui parlent."; break;
        case 307 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>4) {id=314; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==4 
            && gpJeu->getJoueur()->getObjet()==7) {id=308; chercheText();break;}
            texte = "Nous avons échoué ici après avoir percuté une mouette... *Tout ça ne serait jamais arrivé si j'avais eu un klaxon..."; 
            buffer = "Ah oui j'oubliais : *Ho! Ho! Ho!"; break;
        case 308 : texte = "C'est une clochette que tu as là ? *Ca me donne une idée... *Tu me la cèderais ? Je n'ai plus de poney, mais je devrais bien trouver de quoi te remercier..."; idsuiv=309; break;
        case 309 : texte = "Cette clochette contre une récompense, ok ?**              OUI ?            non  "; idsuiv=311; break;
        case 310 : texte = "Cette clochette contre une récompense, ok ?**              oui              NON ?"; idsuiv=312; break;
        case 311 : texte = "Merci! Voilà ta récompense : la hache que je devais livrer en cadeau au bourreau du coin. Heureux ?"; break;
        case 312 : texte = "... *Quel est ton nom ?*Je te raye de ma liste."; break;
        case 313 : texte = "Tu as troqué la clochette contre une hache!"; break;
        case 314 : texte = "Ho! Ho! Ho!"; buffer="C'est bien gentil, mais comment je rentre moi ?"; break;
        case 315 : texte = "TUTORIEL :*Un choc sur une de ces sphères de couleur permute les obstacles levés."; break;
        case 316 : texte = "Tu as trouvé une épée !!!*Sert-en avec la touche W (ou Z), ou maintiens W (ou Z) enfoncé pour charger une attaque tornade!"; break;
        case 317 : texte = "TUTORIEL :*Tomber dans un trou permet de descendre au niveau inférieur, cependant, s'il n'y a pas de niveau inférieur tel que c'est le cas ici, une chute fait perdre de la vie et renvoie à l'entrée de la zone. Prudence donc!"; break;
        case 318 : texte = "TUTORIEL :*Au cours du jeu, vous pourriez être amené à rencontrer des zones apparemment inaccessibles comme la plate-forme en bas. Vous aurez alors"; buffer="besoin de revenir plus tard dans le jeu avec un équipement plus fournit pour y accéder."; break;
        case 319 : texte = "@+@+@+@+@+@+@@@+*@=++=@=+@=+@=+=@*+@+@+@+=+="; break;
        case 320 : texte = "Les gardes t'ont aperçu te diriger vers la forêt, j'ai pensé que tu avais une piste et j'ai accouru..."; break;
        case 321 : texte = "Mmm... Cette stèle est en hylien ancien... Je vais te la traduire :"; idsuiv=322; break;
        case 322 : texte = "A l'aube du cataclysme, le héros trouvera cette stèle. Les pendentifs du courage, de la sagesse et de la force en sa possession, l'unique chance de sauver le monde se présentera à lui."; break;
        case 323 : texte = "..."; buffer="J'ai peur que nous devions laisser tomber cette affaire d'ocarina pour le moment...*Si cette stèle dit vrai, tu dois trouver les 3 pendentifs dans les plus brefs délais..."; idsuiv=324; break;
        case 324 : texte = "Ils sont cachés dans 3 temples, le plus proche est une tour près des cascades au Nord d'ici... Prends cette carte, elle t'aidera à t'orienter!"; break;
        case 325 : texte = "Tu as obtenu la carte d'Hyrule!**Appuie sur P à l'extérieur pour la consulter."; break;
        case 326 : 
            if (!gpJeu->getJoueur()->hasMedaillon(0)) {texte = "Le premier médaillon se trouve dans la tour au Nord de cette forêt, sors de la forêt par l'Ouest puis va au Nord pour arriver dans la zone des cascades."; break;}
            if (!gpJeu->getJoueur()->hasMedaillon(1)) {texte = "Le second médaillon se trouve dans le temple au milieu du lac. Tu devras louer une barque près du village des Mouettes..."; break;}
            if (!gpJeu->getJoueur()->hasMedaillon(2)) {texte = "Le dernier médaillon est dans un temple dans les montagnes, au Nord du village Cocorico."; break;}
            if (gpJeu->getJoueur()->getEpee()<2 && !gpJeu->getJoueur()->hasObjet(O_OCARINA)) {id=327; chercheText();break;}
            id=329; chercheText();break;
        case 327 : texte = "Tu as trouvé tous les pendentifs ?*Bien, nous ignorons tout de ce qui va se passer, alors prends cette épée avec toi."; break;
        case 328 : texte = "Tu as obtenu Excalibur !!!*Sa puissance devrait t'être utile!"; break;
        case 329 : 
            if (gpJeu->getJoueur()->getAvancement() == PORTAIL_F_OUVERT) {texte = "On dirait un portail de téléportation, mais... ...nous n'avons aucune information quant à sa destination..."; break;}
            texte = "Essaie de toucher la stèle, il va sûrement se passer quelque chose maintenant que tu as les pendentifs..."; break;
        case 330 : texte = "Une dernière chose :*Des monstres commencent à apparaître partout en Hyrule... C'est très mauvais signe... Soit prudent."; break;
        case 331 : 
            texte = "Bonjour Link, les visiteurs se font rares ces temps-ci...";
            if (gpJeu->getJoueur()->getBouclier()!=1) {idsuiv=333; break;}
            buffer="Laisse-moi améliorer ton bouclier..."; break;
        case 332 : texte = "Tu as obtenu un meilleur bouclier !!!*Ta défense augmente d'un point!"; break;
        case 333 : texte = "Viens me voir si tu es blessé, je te soignerai."; break;
        case 334 : texte = "Tu as obtenu 10 sacs de riz!"; break;
        case 335 : texte = "Tu as obtenu 10 bocaux d'épices!"; break;
        case 336 : texte = "Tu as obtenu 10 sacs d'olives!"; break;
        case 337 : texte = "Pour ouvrir l'accès à la Pyramide, trouve et note les 9 indices cachés sur des pancartes du désert, puis soulève les pierres de la baleine dans le bon ordre, et le chemin s'ouvrira..."; break;
        case 338 :
            if (gpJeu->getJoueur()->getAvancement() < GARS_MINE_AIDE) {
                texte = "Chariot express : Je suis absent pour le moment, en cas d'urgence, je suis au saloon.** - L'employé de la mine -"; break;}
            texte = "Chariot express : le service a repris!"; break;
        case 339 : texte = "Monte dans le wagonnet et laisse-moi m'occuper du levier. *Ne t'inquiète pas c'est mon métier!"; break;
        case 340 : texte = "Tu as trouvé des planches de bois!*Tu pourrais t'en servir pour construire un pont..."; break;
        case 341 : texte = "Ca semble être un bon endroit pour construire un pont."; break;
        case 342 : texte = "                      Link*                 Héros d'Hyrule*               - Tué par Ganon -"; break;
        case 343 : texte = "Nous sommes au complet, nous allons t'ouvrir le portail..."; break;
        case 344 : 
            if (gpJeu->getJoueur()->getAvancement() < SAGES_GROTTE) {id=347; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() < PORTAIL_PRE_PRESENT_FERME) {texte = "Prépare-toi bien, le voleur de l'ocarina doit être une créature très puissante..."; break;}
            texte = "Tu as réussi à reprendre l'ocarina ? Félicitation !"; break;
        case 345 : 
            if (gpJeu->getJoueur()->getAvancement() < SAGES_GROTTE) {id=347; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() < PORTAIL_PRE_PRESENT_FERME) {texte = "Ce portail est très particulier, il pointe vers un endroit précis du passé... Mais nous ne pourrons pas le maintenir ouvert éternellement, dépêche-toi!"; break;}
            texte = "Tu as l'ocarina ? Nous avons donc accompli la mission confiée par nos ancêtres..."; break;
        case 346 : 
            if (gpJeu->getJoueur()->getAvancement() < SAGES_GROTTE) {id=347; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() < PORTAIL_PRE_PRESENT_FERME) {texte = "Le portail est enfin ouvert... Va Link, tu dois reprendre l'ocarina!"; break;}
            texte = "L'Ocarina du Temps..."; buffer="Cours au Temple du Temps, accomplit ta destinée!"; break;
        case 347 : texte = "Lorsque nous serons au complet et munis de la clé du temps, nous t'ouvrirons le portail..."; break;
        case 348 : texte = "Tu as réussi... Nous refermons le portail..."; break;
        case 349 : texte = "Tu as obtenu une jauge!*...*Cool..."; break;
        case 350 :
            if ((gpJeu->getJoueur()->getBombeMax()<30 && gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) 
            || gpJeu->getJoueur()->getFlecheMax()<70)
                {id=351; chercheText();break;}
            if (!gpJeu->getJoueur()->hasObjet(O_RECUP_FLECHE) 
            || !gpJeu->getJoueur()->hasObjet(O_RECUP_BOMBE))
                {id=356; chercheText();break;}
            texte = "Ca va j'ai assez d'or, va-t'en."; break;
            break;
        case 351 : 
            texte = "Donne-moi vite 100 Ganon d'or si tu veux une récompense, ok ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<100) idsuiv=75;
            break;
        case 352 : texte = "Donne-moi vite 100 Ganon d'or si tu veux une récompense, ok ?*              oui              NON ?"; idsuiv=353; break;
        case 353 : texte = "Tu me fais perdre mon temps, oust!"; break;
        case 354 : texte = "Je vais augmenter le nombre de flèches que tu peux transporter.*Merci qui ?"; break;
        case 355 : texte = "Je vais augmenter le nombre de bombes que tu peux transporter.*Je suis trop bonne..."; break;
        case 356 : 
            texte = "Donne-moi 999 Ganon d'or si tu veux une super récompense, ok ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<999) idsuiv=75;
            break;
        case 357 : texte = "Donne-moi 999 Ganon d'or si tu veux une super récompense, ok ?*              oui              NON ?"; idsuiv=353; break;
        case 358 : texte = "Ton nombre de flèches va désormais augmenter en permanence, n'hésite plus à les utiliser."; break;
        case 359 : texte = "Ton stock de bombe se restitue désormais en permanence, tu peux exploser sans compter!"; break;
        case 360 : 
            if (gpJeu->getJoueur()->getMagieMax()>32) {id=333; chercheText();break;}
            texte = "Bienvenue à toi héros, je vais augmenter ta réserve de magie, ça devrait t'être utile."; break;
        case 361 : texte = "Ta réserve de magie a doublé!"; break;
        case 362 : 
            if (gpJeu->getEpoque()==T_PASSE && !gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Je te sers quelque chose ?"; break;
        case 363 : texte = "D'après les rumeurs, une fée se cacherait derrière une cascade...*Quelle sornette..."; break;
        case 364 : texte = "Je euh... monte la garde dans le bar, oui voilà.*Mais je préfèrerai que ça reste entre nous, ok?"; break;
        case 365 : texte = "Héros d'Hyrule ou pas, ne pense pas boire à l'oeil."; break;
        case 366 : texte = "C'est trop risqué de rentrer ici, on risque de te voir."; break;
        case 367 : 
            if (gpJeu->getEpoque()==T_PASSE && !gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getZone()==84 && gpJeu->getJoueur()->getNbGemmes() == 200 
            && gpJeu->getJoueur()->getGemme() == 0) {id=405; chercheText(); break;}
            texte = "Choisis ce que tu veux.*"; break;
        case 368 : texte = "10 flèches pour 20 rubis ?**              OUI ?            non  ";
            if (!gpJeu->getJoueur()->hasObjet(O_ARC)) {id=373; chercheText(); break;}
            else if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=75; break;
        case 369 : texte = "10 flèches pour 20 rubis ?**              oui              NON ?"; break;
        case 370 : texte = "5 bombes pour 30 rubis ?**              OUI ?            non  ";
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=372; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=75; break;
        case 371 : texte = "5 bombes pour 30 rubis ?**              oui              NON ?"; break;
        case 372 : texte = "Il te faut un sac de bombes pour acheter ceci."; break;
        case 373 : texte = "Il te faut un arc pour acheter ceci."; break;
        case 374 : texte = "Tu n'as pas besoin de ça."; break;
        case 375 : texte = "Merci."; break;
        case 376 : texte = "Un petit coeur pour 5 rubis ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getVie() + gpJeu->getJoueur()->getBoostVie() >= gpJeu->getJoueur()->getVieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<5) idsuiv=75; break;
        case 377 : texte = "Un petit coeur pour 5 rubis ?**              oui              NON ?"; break;
        case 378 : texte = "Une petite fiole de magie pour 15 rubis ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75; break;
        case 379 : texte = "Une petite fiole de magie pour 15 rubis ?**              oui              NON ?"; break;
        case 380 : texte = "Une grande fiole de magie pour 25 rubis ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<25) idsuiv=75; break;
        case 381 : texte = "Une grande fiole de magie pour 25 rubis ?**              oui              NON ?"; break;
        case 382 :
            if (gpJeu->getJoueur()->getAvancement()<APPREND_POUR_ROC_GIVRE) {texte = "Je viens d'arriver dans cette ville, je ne suis pas encore ouvert, reviens plus tard."; break;}
            if (gpJeu->getJoueur()->getAvancement()==APPREND_POUR_ROC_GIVRE 
            && gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)==-1) {
                texte = "Est-ce que j'ai un roc givre ?*Oui, tout juste."; idsuiv=383; break;
            }
            texte = "Je pensais que personne n'avait de gemmes de force, j'hésitais à ouvrir ma boutique, mais tu m'as décidé.";
            buffer = "Dès ta prochaine visite je serai ouvert, tu pourras acheter des articles rarissimes contre des gemmes.";
            break;
        case 383 : texte = "Je te le cède pour 30 gemmes de force, ok ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<30) idsuiv=385; break;
        case 384 : texte = "Je te le cède pour 30 gemmes de force, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 385 : texte = "Tu n'as pas assez de gemmes.*Cherche mieux, on en trouve partout."; break;
        case 386 : texte = "Ce détecteur permet de voir si tu as trouvé toutes les gemmes de force de ta zone actuelle. Un outil indispensable pour trouver toutes les gemmes, il est à toi contre 20 gemmes de force!"; idsuiv=387; break;
        case 387 : texte = "Le détecteur pour 20 gemmes de force, ok ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 388 : texte = "Le détecteur pour 20 gemmes de force, ok ?**              oui              NON ?"; break;
#ifdef __PSP2__
        case 389 : texte = "Tu as obtenu le détecteur !*Lorsque tu appuies sur Croix, le nombre de gemmes en ta possession sera écrit en vert si tu les as toutes dans la zone."; break;
#else
        case 389 : texte = "Tu as obtenu le détecteur !*Lorsque tu appuies sur Entrée, le nombre de gemmes en ta possession sera écrit en vert si tu les as toutes dans la zone."; break;
#endif
        case 390 : 
            if (gpJeu->getJoueur()->hasBouteille(0)) {id=393; chercheText(); break;}
            texte = "Une bouteille vide pour 10 gemmes de force ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<10) idsuiv=385; break;
        case 391 : texte = "Une bouteille vide pour 10 gemmes de force ?**              oui              NON ?"; break;
        case 392 : texte = "Tu as obtenu une bouteille !*Tu vas pouvoir stocker des potions dedans !"; break;
        case 393 : texte = "Une bouteille vide pour 20 gemmes de force ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 394 : texte = "Une bouteille vide pour 20 gemmes de force ?**              oui              NON ?"; break;
        case 395 : 
            if (gpJeu->getJoueur()->hasObjet(O_BONUS_FORCE)==1) {id=398; chercheText(); break;}
            texte = "Une augmentation de ta force pour 20 gemmes ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 396 : texte = "Une augmentation de ta force pour 20 gemmes ?**              oui              NON ?"; break;
        case 397 : texte = "Ta force augmente d'un point!"; break; 
        case 398 : 
            texte = "Une augmentation de ta force pour 40 gemmes ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<40) idsuiv=385; break;
        case 399 : texte = "Une augmentation de ta force pour 40 gemmes ?**              oui              NON ?"; break;
        case 400 : 
            if (gpJeu->getJoueur()->hasObjet(O_BONUS_DEFENSE)==1) {id=403; chercheText(); break;}
            texte = "Une augmentation de ta défense pour 20 gemmes ? *              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 401 : texte = "Une augmentation de ta défense pour 20 gemmes ? *              oui              NON ?"; break;
        case 402 : texte = "Ta défense augmente d'un point!"; break; 
        case 403 : 
            texte = "Une augmentation de ta défense pour 40 gemmes ? *              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGemme()<40) idsuiv=385; break;
        case 404 : texte = "Une augmentation de ta défense pour 40 gemmes ? *              oui              NON ?"; break;
        case 405 : texte = "Mmm... mon stock est vide..."; idsuiv=406; break;
        case 406 : texte = "Tu as dû trouver toutes les gemmes de force, c'est incroyable..."; idsuiv=407; break;
        case 407 : texte = "D'après une vielle légende, quand toutes les gemmes auront été trouvées, un temple gardant un trésor fabuleux s'ouvrira...*Plus qu'à attendre..."; break;
        case 408 : texte = "Reviens me voir lorsque tu auras un flacon vide et je te vendrais des potions."; break;
        case 409 :
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = "Les potions rouges redonnent de l'énergie alors que les potions vertes redonnent de la magie."; 
            idsuiv=410; break;
        case 410 : texte = "Que désires-tu ?*                ? POTION ROUGE ?*                  potion verte  *                      rien      "; idsuiv=413; break;
        case 411 : texte = "Que désires-tu ?*                  potion rouge  *                ? POTION VERTE ?*                      rien      "; 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=374;
            else idsuiv=415; break;
        case 412 : texte = "Que désires-tu ?*                  potion rouge  *                  potion verte  *                ?     RIEN     ?"; break;
        case 413 : texte = "Une potion rouge pour 60 rubis ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<60) idsuiv=75; break;
        case 414 : texte = "Une potion rouge pour 60 rubis ?**              oui              NON ?"; break;
        case 415 : texte = "Une potion verte pour 40 rubis ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<40) idsuiv=75; break;
        case 416 : texte = "Une potion verte pour 40 rubis ?**              oui              NON ?"; break;
        case 417 : texte = "Tu as trouvé une potion rouge !!!**Bois-la pour restaurer toute ton énergie!!!"; break;
        case 418 : texte = "Tu as trouvé une potion verte !!!**Bois-la pour restaurer toute ta magie!!!"; break;
        case 419 : texte = "Tu as trouvé une potion bleue !!!**Bois-la pour restaurer ton énergie et ta magie!!!"; break;
        case 420 : texte = "Tu n'as pas besoin de boire cette potion maintenant."; break;
        case 421 : texte = "                Déjà fatigué ?                  ?                CONTINUER                  ?             Sauvegarder et quitter                        Quitter sans sauvegarder           "; break;
        case 422 : texte = "                Déjà fatigué ?                                   Continuer                     ?          SAUVEGARDER ET QUITTER           ?            Quitter sans sauvegarder           "; break;
        case 423 : texte = "                Déjà fatigué ?                                   Continuer                                Sauvegarder et quitter              ?         QUITTER SANS SAUVEGARDER          ?"; break;
        case 424 : 
            if (gpJeu->getJoueur()->getCoffre(15,14)) {id=431; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==3 
            && gpJeu->getJoueur()->getObjet()==3) {id=425; chercheText();break;}
            texte = "Je suis l'homme le plus malchanceux du pays, il ne m'arrive jamais rien de bon..."; break;
        case 425 : texte = "C'est un porte-bonheur que tu as là ? *Donne-le-moi! *Personne n'en a autant besoin que moi!"; idsuiv=426; break;
        case 426 : texte = "Ce fer à cheval contre... rien, ok ?**              OUI ?            non  "; idsuiv=428; break;
        case 427 : texte = "Ce fer à cheval contre... rien, ok ?**              oui              NON ?"; idsuiv=429; break;
        case 428 : texte = "Merci mille fois! Je vais peut-être avoir de la chance maintenant!"; 
            buffer = "Par contre désolé l'ami, mais je n'ai rien à t'offrir en échange, on dirait que la chance a tourné."; break;
        case 429 : texte = "... *Quelle immonde déveine!"; break;
        case 430 : texte = "Tu as troqué le fer à cheval contre... sa reconnaissance ?"; break;
        case 431 : texte = "Finalement je suis un sacré veinard."; break;
        case 432 : texte = "Je n'ai plus de prix à mettre en jeu, désolé."; break;
        case 433 : 
            tmp = 4-(gpJeu->getJoueur()->getCoeur(28) + gpJeu->getJoueur()->getGemme(160) 
            + gpJeu->getJoueur()->getGemme(161) + gpJeu->getJoueur()->getGemme(162));
            if (tmp==0) {id=432; chercheText();break;}
            os << tmp; os2 << ((4-tmp+1)*5);
            texte = "Il y a "+os.str()+" prix dans ces 9 coffres, tu veux tenter ta chance pour "+os2.str()+" rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?              OUI ?            non  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<(4-tmp+1)*5) idsuiv=75; break;
        case 434 : 
            tmp = 4-(gpJeu->getJoueur()->getCoeur(28) + gpJeu->getJoueur()->getGemme(160) 
            + gpJeu->getJoueur()->getGemme(161) + gpJeu->getJoueur()->getGemme(162));
            os << tmp; os2 << ((4-tmp+1)*5);
            texte = "Il y a "+os.str()+" prix dans ces 9 coffres, tu veux tenter ta chance pour "+os2.str()+" rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?              oui              NON ?"; break;
        case 435 : texte = "Choisis un coffre."; break;
        case 436 : texte = "Hey! Il faut payer pour ouvrir un de mes coffres!!!"; break;
        case 437 : texte = "Perdu! Ce coffre est vide."; break;
        case 438 :
            if (gpJeu->getJoueur()->hasObjet(O_SAC_TROC)) {id=444; chercheText();break;}
            texte = "Bonjour Link, tu veux traverser le pont pour accéder au temple ?"; idsuiv=439;
            break;
        case 439 : texte = "Habituellement je n'aurais qu'à activer ce levier, mais j'ai joué avec toute la soirée d'hier, et euh... je l'ai cassé."; 
            buffer="J'ai même pensé à mettre des planches en bois pour permettre de passer, mais on m'a volé mes planches la nuit dernière..."; idsuiv=440; break;
        case 440 : texte = "Je pourrais toujours réparer le levier, mais j'ai besoin d'une pièce de rechange, et je ne peux pas quitter mon poste..."; idsuiv=441; break;
        case 441 : texte = "J'ai besoin d'un rouage, on en trouve sur la place du marché de la cité d'Hyrule."; idsuiv=442; break;
        case 442 : texte = "Tu connais le principe, non ? Chaque marchand te propose des marchandises contre d'autres, tu dois réunir ce qu'ils veulent pour obtenir ce que tu veux."; idsuiv=443; break;
#ifdef __PSP2__
        case 443 : texte = "Je vais te donner les marchandises que j'ai.*Si tu veux consulter ce que tu as déjà, appuie sur D-Pad Gauche."; break;
#else
        case 443 : texte = "Je vais te donner les marchandises que j'ai.*Si tu veux consulter ce que tu as déjà, appuie sur I."; break;
#endif
        case 444 : 
            if (gpJeu->getJoueur()->getTroc(M_ROUAGE)==0) {id=446; chercheText();break;}
            if (gpJeu->getJoueur()->getTroc(M_ROUAGE)>0) {id=445; chercheText();break;}
            texte = "Il me faut un rouage pour réparer le levier.*Va en chercher sur la place du marché de la cité d'Hyrule si tu veux franchir le pont."; break;
        case 445 : texte = "Tu as un rouage ?*Bien, ça devrait marcher maintenant."; break;
        case 446 : texte = "Le levier est à nouveau cassé...*Au moins le pont est sorti cette fois...*Ca m'apprendra à construire des ponts excentriques..."; break;
        case 447 : 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = "Une potion bleue pour 160 rubis ?*Tu ne seras pas déçu...*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<160) idsuiv=75; break;
        case 448 : texte = "Une potion bleue pour 160 rubis ?*Tu ne seras pas déçu...*              oui              NON ?"; break;
        case 449 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>1) {id=456; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==1 
            && gpJeu->getJoueur()->getObjet()==15) {id=450; chercheText();break;}
            texte = "J'adore tout ce qui est vert et qui brille!"; 
            buffer = "Ne t'en fais pas, je ne vais pas te voler de rubis... *J'essaie d'arrêter."; break;
        case 450 : texte = "C'est drôlement beau ce que tu as là... *J'adore!*Je te l'échange contre une carte de voyage d'une valeur... euh... INESTIMABLE!"; idsuiv=451; break;
        case 451 : texte = "Cette gemme verte contre une carte, ok ?**              OUI ?            non  "; idsuiv=453; break;
        case 452 : texte = "Cette gemme verte contre une carte, ok ?**              oui              NON ?"; idsuiv=454; break;
        case 453 : texte = "Merciiii!!! Voilà ta carte de voyage, maintenant du vent!"; break;
        case 454 : texte = "Très bien... *Surveille tes Rubis dans ce cas!"; break;
        case 455 : texte = "Tu as troqué la gemme verte contre une carte!"; break;
        case 456 : texte = "Tu es venu me donner des Rubis ?*Comme c'est gentil!"; break;
        case 457 : texte = "La princesse veut que je la prévienne s'il se passe quelque chose de curieux en ville..."; 
            buffer = "Ce matin j'ai vu une mouette qui volait curieusement... j'hésite à lui en parler..."; break;
        case 458 :
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)) {id=478; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() == PARLE_PECHE) {id=460; chercheText();break;}
            gpJeu->getJoueur()->setAvancement(PARLE_PECHE);
            texte = "Bonjour Link, soit le bienvenu au stand de pêche!"; idsuiv = 459; break;
        case 459 : texte = "Pour inaugurer l'ouverture du stand, j'organise un grand concours de pêche!*Tu as dû en entendre parler, toute la ville participe!"; idsuiv=460; break;
        case 460 : texte = "Pour remporter le concours et gagner un prix spécial, il faut être le premier à pêcher 5 espèces de poissons différentes."; idsuiv=461; break;
        case 461 : texte = "Veux-tu participer ? Les droits d'inscriptions sont de 10 Rubis, ok ?*              OUI ?            non  "; idsuiv=463;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=75; break;
        case 462 : texte = "Veux-tu participer ? Les droits d'inscriptions sont de 10 Rubis, ok ?*              oui              NON ?"; idsuiv=464; break;
        case 463 : texte = "Très bien, voici une canne à pêche, reviens lorsque tu auras pêché 5 poissons différents."; break;
        case 464 : 
            texte = "Mmm... Veux-tu participer pour 5 Rubis ?**              OUI ?            non  "; idsuiv=466; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<5) idsuiv=75; break;
        case 465 : texte = "Mmm... Veux-tu participer pour 5 Rubis ?**              oui              NON ?"; idsuiv=467; break;
        case 466 : texte = "Bien, voici une canne à pêche, reviens lorsque tu auras pêché 5 poissons différents."; break;
        case 467 : texte = "Et pour 2 Rubis ?**              OUI ?            non  "; idsuiv=469;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<2) idsuiv=75; break;
        case 468 : texte = "Et pour 2 Rubis ?**              oui              NON ?"; idsuiv=470; break;
        case 469 : texte = "Bon, voici une canne à pêche, reviens lorsque tu auras pêché 5 poissons différents."; break;
        case 470 : texte = "Pour 1 Rubis ?**              OUI ?            non  "; idsuiv=472;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<1) idsuiv=75; break;
        case 471 : texte = "Pour 1 Rubis ?**              oui              NON ?"; idsuiv=473; break;
        case 472 : texte = "Ok, voici une canne à pêche, reviens lorsque tu auras pêché 5 poissons différents."; break;
        case 473 : texte = "Tu ne veux tout de même pas participer gratuitement ???*               SI ?            non  "; idsuiv=475; break;
        case 474 : texte = "Tu ne veux tout de même pas participer gratuitement ???*               si              NON ?"; idsuiv=476; break;
        case 475 : texte = "...*Voici une canne à pêche, reviens lorsque tu auras pêché 5 poissons différents."; break;
        case 476 : texte = "Va-t-en, ennemi de la pêche!"; break;
#ifdef __PSP2__
        case 477 : texte = "Tu as obtenu une canne à pêche!*Utilise-la à un ponton, puis remonte la ligne en appuyant à nouveau sur Triangle lorsque la ligne bouge."; break;
#else
        case 477 : texte = "Tu as obtenu une canne à pêche!*Utilise-la à un ponton, puis remonte la ligne en appuyant à nouveau sur X lorsque la ligne bouge."; break;
#endif
        case 478 : 
            if (gpJeu->getJoueur()->hasObjet(O_POISSONS)) {id=487; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=5) {id=479; chercheText();break;}
            tmp = 5-gpJeu->getJoueur()->nbPoissons();
            os << tmp;
            if (tmp > 1) texte = "Encore "+os.str()+" poissons différents à trouver, bonne chance!";
            else texte = "Plus qu'un poisson à trouver!"; break;
        case 479 : texte = "Tu as trouvé suffisamment de poissons ???*Tu dois être un super pêcheur!"; idsuiv=480; break;
        case 480 : texte = "Ca signifie que le concours de pêche est terminé, tu en es le vainqueur!"; idsuiv=481; break;
        case 481 : texte = "J'imagine que tu vas vouloir ton prix...*Pour te récompenser d'avoir remporter le concours de pêche : *... ... ..."; idsuiv=482; break;
        case 482 : texte = "Je t'engage!"; idsuiv=483; break;
        case 483 : texte = "Il y a beaucoup d'autres espèces de poissons à Hyrule, je veux tous les répertorier par région."; idsuiv=484; break;
#ifdef __PSP2__
        case 484 : texte = "Je te récompenserai tous les 5 nouveaux poissons pêchés.*Tu peux désormais consulter la liste des poissons pêchés en appuyant sur D-Pad Bas"; idsuiv=485; break;
#else
        case 484 : texte = "Je te récompenserai tous les 5 nouveaux poissons pêchés.*Tu peux désormais consulter la liste des poissons pêchés en appuyant sur L"; idsuiv=485; break;
#endif
        case 485 : texte = "Avec ta canne à pêche actuelle, tu ne pourras hélas pêcher que des petits poissons..."; break;
        case 486 : texte = "N'hésite pas à pêcher partout!*Chaque poisson pêché te redonne de la vie, l'avais-tu remarqué ?"; break;
        case 487 :
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)>1) {id=490; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=10) {id=488; chercheText();break;}
            tmp = 10-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Encore "+os.str()+" poissons différents à trouver avant la prochaine récompense!";
            break;
        case 488 : texte = "Voici ta récompense pour avoir trouvé 10 poissons différents :"; break;
        case 489 : texte = "Tu as obtenu une meilleure canne à pêche!!!*Tu vas pouvoir attraper des poissons de taille moyenne."; break;
        case 490 : 
            if (gpJeu->getJoueur()->hasBouteille(2)) {id=492; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=15) {id=491; chercheText();break;}
            tmp = 15-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Encore "+os.str()+" poissons différents à trouver avant la prochaine récompense!";
            break;
        case 491 : texte = "Voici ta récompense pour avoir trouvé 15 poissons différents :"; break;
        case 492 : 
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)>2) {id=495; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=20) {id=493; chercheText();break;}
            tmp = 20-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Encore "+os.str()+" poissons différents à trouver avant la prochaine récompense!";
            break;
        case 493 : texte = "Voici ta récompense pour avoir trouvé 20 poissons différents :"; break;
        case 494 : texte = "Tu as obtenu la meilleure canne à pêche!!!*Tu vas pouvoir attraper des poissons de taille gigantesque!"; break;
        case 495 : 
            if (gpJeu->getJoueur()->getCoeur(27)) {id=497; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=25) {id=496; chercheText();break;}
            tmp = 25-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Encore "+os.str()+" poissons différents à trouver avant la prochaine récompense!";
            break;
        case 496 : texte = "Voici ta récompense pour avoir trouvé 25 poissons différents :"; break;
        case 497 : 
            if (gpJeu->getJoueur()->hasObjet(O_POISSONS)>1) {id=500; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=30) {id=498; chercheText();break;}
            tmp = 30-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = "Encore "+os.str()+" poissons différents à trouver avant la prochaine récompense!";
            break;
        case 498 : texte = "Voici ta récompense pour avoir trouvé tous les poissons différents :"; break;
        case 499 : texte = "T'ES VIRE !!!!"; break;
        case 500 : texte = "Tous les poissons d'Hyrule sont enfin recensés, mon guide du pêcheur est enfin fini..."; break;
        case 501 : texte = "Bonjour Link.*En temps que maire, je te souhaite la bienvenue au village des Mouettes."; 
            if (gpJeu->getJoueur()->hasObjet(O_POISSONS)) idsuiv=503; else idsuiv=502; break;
        case 502 : texte = "En ce moment un concours de pêche est organisé en ville, tout le monde ne parle que de ça... *Est-ce la raison de ta venue ?"; break;
        case 503 : texte = "Le concours de pêche étant fini, le village des Mouettes est redevenu un lieu calme."; break;
        case 504 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>1) {id=511; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==1 
            && gpJeu->getJoueur()->getObjet()==7) {id=505; chercheText();break;}
            texte = "Je suis un pêcheur légendaire!*J'aime le côté bleu et brillant de la mer..."; 
            buffer = "Pourquoi je n'ai pas remporté le concours de pêche ?*Et bien euh... Ce genre de choses ne m'intéressent pas.... Voilà."; break;
        case 505 : texte = "Une gemme bleue et brillante ?*Il me la faut!*Je te l'échange contre ma dernière pêche!"; idsuiv=506; break;
        case 506 : texte = "Cette gemme bleue contre sa pêche, ok ?**              OUI ?            non  "; idsuiv=508; break;
        case 507 : texte = "Cette gemme bleue contre sa pêche, ok ?**              oui              NON ?"; idsuiv=509; break;
        case 508 : texte = "Hé! Hé! Tu fais une affaire petit."; buffer="Cette botte était remplie d'algues quand je l'ai pêchée, ce n'est pas courant hein ?"; break;
        case 509 : texte = "Tu es trop gentil, mais ne t'en fais pas pour moi, n'ai pas peur de m'arnaquer."; break;
        case 510 : texte = "Tu as troqué la gemme bleue contre une vieille botte!*Bien joué..."; break;
        case 511 : texte = "Si tu trouves d'autres gemmes bleues, ce sera un plaisir de faire à nouveau des affaires avec toi!"; break;
        case 512 : 
            if (!gpJeu->getJoueur()->hasObjet(O_CANNE)) texte = "De nos jours les jeunes n'écoutent plus les conseils des plus âgés...*Je sens que ce concours de pêche va durer...";
            else {texte = "Autrefois j'étais un pêcheur réputé, veux-tu que je te donne quelques astuces ?"; idsuiv=513;} break;
        case 513 : texte = "A PROPOS DES ESPECES DE POISSONS ?*A propos des régions de pêche     *A propos des bonus                *Rien du tout                      "; idsuiv=517; break;
        case 514 : texte = "A propos des espèces de poissons  *A PROPOS DES REGIONS DE PECHE    ?*A propos des bonus                *Rien du tout                      "; idsuiv=518; break;
        case 515 : texte = "A propos des espèces de poissons  *A propos des régions de pêche     *A PROPOS DES BONUS               ?*Rien du tout                      "; idsuiv=519; break;
        case 516 : texte = "A propos des espèces de poissons  *A propos des régions de pêche     *A propos des bonus                *RIEN DU TOUT                     ?"; idsuiv=520; break;
        case 517 : texte = "On dit que les eaux d'Hyrule abritent pas moins de 30 espèces de poissons, mais ils ont chacun leur propre région, tu ne les trouveras pas tous au même endroit."; break;
        case 518 : texte = "Il y a en Hyrule beaucoup d'endroits où pêcher, mais seulement 6 régions distinctes. Pour trouver de nouveaux poissons tu devras aller pêcher à d'autres endroits."; 
            buffer="Si tu trouves un poisson déjà connu ailleurs, c'est que tu es toujours dans la même région de pêche."; break;
        case 519 : texte = "La pêche ne sert pas uniquement à se divertir, un poisson pêché te redonne de la vie. La quantité de vie gagnée dépend du poisson pêché."; break;
        case 520 : texte = "Tsss... la jeunesse de nos jours..."; break;
        case 521 : 
            if (!gpJeu->getJoueur()->hasObjet(O_POISSONS)) texte = "J'ai passé des heures à pêcher au bord du lac, et je n'ai pu trouver que 3 poissons différents..."; 
            else texte = "Il fallait aller pêcher à différents endroits pour trouver plus de 3 poissons ?*Si j'avais su..."; break;
        case 522 :
            if (gpJeu->getJoueur()->getAvancement()==PARLE_GARS_MINE_SALOON) {id=523; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_BARMAN_SALOON
            && gpJeu->getJoueur()->getAvancement()<DETTE_PAYEE) {id=528; chercheText();break;}
            texte = "Je te sers quelque chose ?"; break;
        case 523 : texte = "Tu as besoin de l'aide du gars qui picole là-bas ?*Je ne peux toutefois pas le laisser partir sans payer."; idsuiv=524; break;
        case 524 : texte = "Tu veux régler sa dette ? C'est 10 000 Rubis, ok ?*              OUI ?            non  "; idsuiv=75; break;
        case 525 : texte = "Tu veux régler sa dette ? C'est 10 000 Rubis, ok ?*              oui              NON ?"; idsuiv=526; break;
        case 526 : texte = "Evidemment..."; buffer="Je te propose autre chose : j'utilise habituellement un roc givre pour préparer des boissons fraîches, mais je viens d'user le dernier laissé par mes ancêtres..."; idsuiv=527; break;
        case 527 : texte = "Si tu m'apportes un nouveau roc givre, je veux bien effacer cette dette."; break;
        case 528 : 
            if (gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)>0) {id=529; chercheText();break;}
            texte = "Alors, tu ne trouves pas de roc givre ?"; break;
        case 529 : texte = "Tu as un roc givre ? Incroyable..."; idsuiv=530; break;
        case 530 : texte = "Tu me donnes ce roc givre et j'oublie la dette, ok ?*              OUI ?            non  "; idsuiv=533; break;
        case 531 : texte = "Tu me donnes ce roc givre et j'oublie la dette, ok ?*              oui              NON ?"; idsuiv=532; break;
        case 532 : texte = "Je comprends, ce ne sont pas tes affaires après tout."; break;
        case 533 : texte = "Merci!*Comme promis, le vieil homme peut partir, il ne me doit plus rien."; break;
        case 534 : 
            if (gpJeu->getJoueur()->getAvancement()==PANCARTE_MINE_LUE) {id=535; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==PARLE_GARS_MINE_SALOON) {id=537; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==PARLE_BARMAN_SALOON) {id=538; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>PARLE_BARMAN_SALOON
            && gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)<0) {id=540; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()<DETTE_PAYEE
            && gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)>0) {id=541; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==DETTE_PAYEE) {id=542; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==GARS_MINE_AIDE) {id=543; chercheText();break;}
            texte = "Laisse-moi boire en paix! Hic!"; break;
        case 535 : texte = "Tu viens de la mine ?*J'y travaille habituellement...*Avec l'apparition de monstres la mine a provisoirement fermé..."; idsuiv=536; break;
        case 536 : texte = "Je pourrais t'aider à traverser la mine, mais le barman ne veut pas me laisser partir sans payer. Or je n'ai plus d'argent, je suis donc coincé ici, et je bois pour passer le temps."; idsuiv=537; break;
        case 537 : texte = "Il faudrait vraiment que quelqu'un paie ma dette à ma place...*...*Hic!"; break;
        case 538 : texte = "Tu veux savoir où trouver un roc givre ?*Mmm... j'ai entendu dire qu'un gars est arrivé à la cité d'Hyrule dernièrement, et qu'il va ouvrir une boutique d'un nouveau genre..."; idsuiv=539; break;
        case 539 : texte = "Et bien il me semble que ce gars possède un roc givre."; break;
        case 540 : texte = "Va voir le gars qui tient une boutique bizarre dans la cité d'Hyrule, il doit avoir un roc givre."; break;
        case 541 : texte = "Tu as un roc givre ???*Donne-le vite au barman, je promets de t'aider pour la mine!"; break;
        case 542 : texte = "Je suis libre désormais... Moi qui pensais faire la vaiselle jusqu'à la fin de la semaine!*Merci Link!"; idsuiv=543; break;
        case 543 : texte = "Tu peux aller à la mine, on se retrouve là-bas.**Hic!"; break;
        case 544 : texte = "Bienvenue au saloon, fais comme chez toi Link!"; break;
        case 545 : texte = "Tant que la mine au Nord reste fermée, je n'ai rien d'autre à faire que de passer mon temps ici..."; break;
        case 546 : texte = "Pratiquement tous les hommes du village travaillent à la mine au Nord du village."; buffer="Ce matin des monstres sont apparus aux alentours et la mine a dû fermer."; break;
        case 547 : texte = "Le riz, les épices et les olives sont les marchandises de base du troc à Hyrule, tu devrais toujours en avoir sur toi."; break;
        case 548 : texte = "Je suis le chef de la mine, et l'homme le plus puissant du village, alors inutile d'essayer de me prendre de haut, fiston."; break;
        case 549 : texte = "Je suis le chef du village... Mais en réalité le chef de la mine a beaucoup plus d'influence que moi, il a embauché pratiquement tous les hommes du village."; break;
        case 550 : texte = "La banque est sous notre surveillance. RAS."; break;
        case 551 : 
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())==0) idsuiv=552;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>0) idsuiv=553;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())==0) idsuiv=559;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>0) idsuiv=564;
            texte = "Bienvenue dans la banque d'Hyrule. Je suis spécialisé en devises."; break;
        case 552 : texte = "Tu n'as rien qui m'intéresse, reviens si tu trouves de l'or, je t'en donnerai un bon prix."; break;
        case 553 : texte = "Tu possèdes des pièces d'or ? Avec une tête de monstre dessus... Des Ganon d'or tu dis ?"; idsuiv=554; break;
        case 554 : texte = "C'est très laid, mais l'or est récupérable, alors voyons..."; idsuiv=555; break;
        case 555 : 
            int g;
            int gmax;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()>gpJeu->getJoueur()->getRubisMax()-2) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+" Ganon d'or contre "+os2.str()+" Rubis, ok ?**              OUI ?            non  "; idsuiv=558; break;
        case 556 : 
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+" Ganon d'or contre "+os2.str()+" Rubis, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 557 : texte = "Ta bourse est pleine, reviens plus tard, je te rachèterai tout ça."; break;
        case 558 : texte = "Affaire conclue!"; break;
        case 559 : texte = "Tu possèdes des pièces d'or ? Je pensais que cette monnaie avait disparue depuis longtemps..."; idsuiv=560; break;
        case 560 : texte = "Je vais t'en donner un bon prix, alors voyons..."; idsuiv=561; break;
        case 561 : 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()>gpJeu->getJoueur()->getRubisMax()-4) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/4);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*4);
            texte = os.str()+" Pièce d'or contre "+os2.str()+" Rubis, ok ?**              OUI ?            non  "; idsuiv=563; break;
        case 562 : 
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/4);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*4);
            texte = os.str()+" Pièce d'or contre "+os2.str()+" Rubis, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 563 : texte = "Affaire conclue!"; break;
        case 564 : texte = "Que veux-tu me vendre ?*   - PIECE D'OR ?*   - Ganon d'or  *   - Rien  "; idsuiv=560; break;
        case 565 : texte = "Que veux-tu me vendre ?*   - Pièce d'or  *   - GANON D'OR ?*   - Rien  "; idsuiv=554; break;
        case 566 : texte = "Que veux-tu me vendre ?*   - Pièce d'or  *   - Ganon d'or  *   - RIEN ?"; idsuiv=76; break;
        case 567 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==10
            && gpJeu->getJoueur()->hasObjet(O_TROC2)==10
            && gpJeu->getJoueur()->hasObjet(O_TROC3)==10
            && gpJeu->getJoueur()->hasObjet(O_TROC4)==10) {id=574; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==7 
            && gpJeu->getJoueur()->getObjet()==3) {id=568; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==7 
            && gpJeu->getJoueur()->getObjet()==7) {id=575; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==8 
            && gpJeu->getJoueur()->getObjet()==11) {id=580; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==7 
            && gpJeu->getJoueur()->getObjet()==15) {id=585; chercheText();break;}
            texte = "Je suis ici pour construire un pont pour se rendre au Nord. Je suis sûr que ça servira un jour."; 
            buffer = "L'ennui c'est qu'il me manque des outils...*Comment vais-je faire ?"; break;
        case 568 : texte = "Ce marteau me plait...*Il me serait fort utile, veux-tu me le céder contre un trésor légendaire que j'ai trouvé lorsque j'étais explorateur ?"; idsuiv=569; break;
        case 569 : texte = "Ce marteau contre un trésor légendaire, ok ?**              OUI ?            non  "; idsuiv=571; break;
        case 570 : texte = "Ce marteau contre un trésor légendaire, ok ?**              oui              NON ?"; idsuiv=572; break;
        case 571 : texte = "Merci, prends ceci en échange :"; break;
        case 572 : texte = "Je sens que ce pont ne sera jamais terminé..."; break;
        case 573 : texte = "Tu as obtenu la flèche de feu!*Cette flèche enflammée utilise de la magie et délivre une puissance incroyable!"; break;
        case 574 : texte = "Il semblerait que j'ai enfin tout ce dont j'avais besoin...*Je me motive, puis j'y vais!"; break;
        case 575 : texte = "C'est le plan d'un pont ?*J'en aurais vraiment besoin, veux-tu me le céder contre un trésor légendaire que j'ai trouvé lorsque j'étais explorateur ?"; idsuiv=576; break;
        case 576 : texte = "Ce plan contre un trésor légendaire, ok ?**              OUI ?            non  "; idsuiv=578; break;
        case 577 : texte = "Ce plan contre un trésor légendaire, ok ?**              oui              NON ?"; idsuiv=572; break;
        case 578 : texte = "Merci, prends ce cadeau en échange :"; break;
        case 579 : texte = "Tu as obtenu la flèche de glace!*Cette flèche givrante utilise de la magie et délivre une puissance incroyable!"; break;
        case 580 : texte = "Tu as une scie ?*Je ne pourrais pas faire de pont sans, veux-tu me la céder contre un trésor légendaire que j'ai trouvé lorsque j'étais explorateur ?"; idsuiv=581; break;
        case 581 : texte = "Cette scie contre un trésor légendaire, ok ?**              OUI ?            non  "; idsuiv=583; break;
        case 582 : texte = "Cette scie contre un trésor légendaire, ok ?**              oui              NON ?"; idsuiv=572; break;
        case 583 : texte = "Merci, prends ce présent en échange :"; break;
        case 584 : texte = "Tu as obtenu la flèche de lumière!*Cette flèche utilise beaucoup de magie et délivre une puissance ultime!"; break;
        case 585 : texte = "Tu as un clou ?*Ca peut toujours servir, veux-tu me le céder contre une babiole ?"; idsuiv=586; break;
        case 586 : texte = "Ce clou contre une babiole, ok ?**              OUI ?            non  "; idsuiv=588; break;
        case 587 : texte = "Ce clou contre une babiole, ok ?**              oui              NON ?"; idsuiv=572; break;
        case 588 : texte = "Merci, prends donc ça en échange :"; break;
        case 589 : 
            if (gpJeu->getJoueur()->hasObjet(O_ENCYCL)) {id=593; chercheText();break;}
            texte = "Bonjour Link, tu te souviens de moi ?"; idsuiv=590; break;
        case 590 : texte = "Des monstres sont apparus sur Hyrule aujourd'hui, alors une fois de plus je vais tâcher de tous les répertorier, et une fois de plus je compte sur ton aide."; idsuiv=591; break;
#ifdef __PSP2__
        case 591 : texte = "En appuyant sur D-Pad Haut, tu peux voir les monstres déjà répertorier. Tu n'as qu'à vaincre un monstre pour qu'il soit ajouté."; idsuiv=592; break;
#else
        case 591 : texte = "En appuyant sur M, tu peux voir les monstres déjà répertorier. Tu n'as qu'à vaincre un monstre pour qu'il soit ajouté."; idsuiv=592; break;
#endif
        case 592 : 
            switch (gpJeu->getEpoque()) {
                case T_PASSE : os<<"10 pièces d'or"; break;
                case T_PRESENT : os<<"40 Rubis"; break;
                case T_FUTUR : os<<"20 Ganon d'or"; break;
            }
            texte = "Je te devrai "+os.str()+" à chaque monstre ajouté. Passe me voir régulièrement pour chercher ce que je te dois."; break;
        case 593 :
            g = gpJeu->getJoueur()->getSolde();
            if (g == 0) {id=595; chercheText();break;}
            switch (gpJeu->getEpoque()) {
                case T_PASSE : os<<(g/4)<<" Pièces d'or"; break;
                case T_PRESENT : os<<g<<" Rubis"; break;
                case T_FUTUR : os<<(g/2)<<" Ganon d'or"; break;
            }
            if (gpJeu->getEpoque() == T_FUTUR 
            && gpJeu->getJoueur()->getGanonMax() == 0) {id=1368; chercheText();break;}
            texte = "Je te dois "+os.str()+", veux-tu être payé maintenant ?*              OUI ?            non  "; break;
        case 594 : 
            g = gpJeu->getJoueur()->getSolde();
            switch (gpJeu->getEpoque()) {
                case T_PASSE : os<<(g/4)<<" Pièces d'or"; break;
                case T_PRESENT : os<<g<<" Rubis"; break;
                case T_FUTUR : os<<(g/2)<<" Ganon d'or"; break;
            }
            texte = "Je te dois "+os.str()+", veux-tu être payé maintenant ?*              oui              NON ?"; break;
        case 595 : texte="Ton compte est à 0, je t'ai tout donné."; break;
        case 596 : 
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<2) idsuiv=597;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>1) idsuiv=598;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<2) idsuiv=603;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>1) idsuiv=608;
            texte = "Bienvenue dans la banque d'Hyrule. Je suis spécialisé en devises."; break;
        case 597 : texte = "Tu n'as rien qui m'intéresse, reviens si tu trouves de l'or ou des Rubis, je t'en donnerai un bon prix."; break;
        case 598 : texte = "Tu possèdes des Rubis ? Ca fait longtemps qu'ils ne sont plus utilisés, mais leur valeur reste indéniable..."; idsuiv=599; break;
        case 599 : texte = "Alors voyons..."; idsuiv=600; break;
        case 600 : 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()==gpJeu->getJoueur()->getGanonMax()) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+" Rubis contre "+os2.str()+" Ganon d'or, ok ?**              OUI ?            non  "; idsuiv=602; break;
        case 601 : 
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+" Rubis contre "+os2.str()+" Ganon d'or, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 602 : texte = "Affaire conclue!"; break;
        case 603 : texte = "Tu possèdes des pièces d'or ? C'est incroyable que tu aies pu trouver une monnaie aussi ancienne!"; idsuiv=604; break;
        case 604 : texte = "Elles contiennent beaucoup d'or... *Alors voyons..."; idsuiv=605; break;
        case 605 : 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()>gpJeu->getJoueur()->getGanonMax()-2) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+" Pièce d'or contre "+os2.str()+" Ganon d'or, ok ?**              OUI ?            non  "; idsuiv=607; break;
        case 606 : 
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+" Pièce d'or contre "+os2.str()+" Ganon d'or, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 607 : texte = "Affaire conclue!"; break;
        case 608 : texte = "Que veux-tu me vendre ?*   - PIECE D'OR ?*   - Rubis  *   - Rien  "; idsuiv=604; break;
        case 609 : texte = "Que veux-tu me vendre ?*   - Pièce d'or  *   - RUBIS ?*   - Rien  "; idsuiv=599; break;
        case 610 : texte = "Que veux-tu me vendre ?*   - Pièce d'or  *   - Rubis  *   - RIEN ?"; idsuiv=76; break;
        case 611 : texte = "Ca faisait longtemps que je ne m'étais pas autant amusé!"; break;
        case 612 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>6) {id=619; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==6 
            && gpJeu->getJoueur()->getObjet()==7) {id=613; chercheText();break;}
            texte = "L'un de mes ancêtres voulait construire un pont, mais il n'a réussit qu'à en faire le plan..."; 
            buffer = "Je viens d'une lignée d'incapables, pas étonnant que je sois si nul en tout... En plus je suis malade, et personne ne m'aime..."; break;
        case 613 : texte = "Tu as une corde ?*Donne-la-moi s'il te plaît, je te donnerai l'héritage de ma famille, de toute façon je n'ai pas de descendants..."; idsuiv=614; break;
        case 614 : texte = "Cette corde contre son héritage, ok ?**              OUI ?            non  "; idsuiv=616; break;
        case 615 : texte = "Cette corde contre son héritage, ok ?**              oui              NON ?"; idsuiv=617; break;
        case 616 : texte = "Bon bah...*...Merci hein...*..."; break;
        case 617 : texte = "J'en étais sûr, de toute façon on ne m'a jamais rien donné..."; break;
        case 618 : texte = "Tu as troqué la corde contre le plan d'un pont."; break;
        case 619 : texte = "...*J'aimerais être seul un moment..."; break;
        case 620 : 
            if (gpJeu->getJoueur()->getTroc(M_POIVRON)>-1) {id=624; chercheText();break;}
            texte = "Bonjour, tu dois être Link, j'attendais ta venue."; idsuiv=621; break;
        case 621 : texte = "Je suis un descendant des 7 sages. Traqué par les sbires de Ganon, j'ai dû fuir jusqu'ici."; idsuiv=622; break;
        case 622 : texte = "Te voir ici me redonne espoir, je vais aller prendre place dans la grotte du portail.*Prends ceci, ça devrait t'être utile."; break;
        case 623 : texte = "Tu as obtenu un poivron !"; break;
        case 624 : texte = "Bonne chance Link!"; break;
        case 625 : 
            if (gpJeu->getJoueur()->hasObjet(O_GRAPPIN)) {id=635; chercheText();break;}
            texte = "Bienvenue Link, je t'attendais..."; idsuiv=626; break;
        case 626 : texte = "Tu dois avoir beaucoup de questions, laisse-moi y répondre."; idsuiv=627; break;
        case 627 : texte = "Nous sommes à Hyrule, mais dans ce qui n'est pour toi qu'un triste futur...*Le portail que tu as pris t'a permis de venir ici, pour être témoin de ces sombres jours..."; idsuiv=628; break;
        case 628 : texte = "Tu veux savoir ce qui s'est passé ? Ganon a attaqué le château, plus fort que jamais, et tu as été vaincu."; idsuiv=629; break;
        case 629 : texte = "Avant son exécution, la princesse Zelda a réussi à faire parvenir son plan aux sages. Le vol de l'Ocarina du Temps fut selon elle le tournant de cette guerre, elle a donc demandé aux descendants des 7 sages de te remettre l'ocarina lorsque tu arriverais via le portail."; idsuiv=630; break;
        case 630 : texte = "Le jour est enfin venu puisque tu te tiens désormais face à moi.*Cependant... l'ocarina n'a jamais été retrouvé."; idsuiv=631; break;
        case 631 : texte = "Nous avons donc mis au point un autre plan. Nous allons t'envoyer dans le passé, la nuit où l'ocarina fut volé, pour que tu surprennes le voleur."; idsuiv=632; break;
        case 632 : texte = "Nous ne sommes désormais plus que 3 descendants des sages, cherche et trouve les 2 autres ainsi que la clé du temps, et nous t'ouvrirons le portail."; idsuiv=633; break;
        case 633 : texte = "Prends ceci, ça devrait t'aider dans tes recherches :"; break;
        case 634 : texte = "Tu as obtenu le grappin !*Sers-t'en pour franchir les précipices!"; break;
        case 635 : 
            if (gpJeu->getJoueur()->getCoffre(3,29)) {id=636; chercheText();break;}
            texte = "L'un d'entre eux se cache au fond d'un donjon, au milieu du lac."; break;
        case 636 : 
            if (gpJeu->getJoueur()->getTroc(M_POIVRON)>-1) {id=637; chercheText();break;}
            texte = "Le dernier sage se cache vers les cascades."; break;
        case 637 : 
            if (gpJeu->getJoueur()->hasObjet(O_CLE_TEMPS)) {id=638; chercheText();break;}
            texte = "La clé du temps se trouve au fond de la Grande Pyramide."; break;
        case 638 : 
            if (gpJeu->getJoueur()->getAvancement()>SAGES_GROTTE) {id=639; chercheText();break;}
            texte = "Les sages sont dans la grotte, la clé du temps est en ta possession...*Très bien, retrouvons-nous à la grotte du portail, le temps est venu."; break;
        case 639 :
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=640; chercheText();break;}
            texte = "Dans le temple du Temps se trouve un air qui, joué par l'ocarina, te ramènera à ton époque."; break;
        case 640 : texte = "Bonne chance Link, nous comptons tous sur toi."; break;
        case 641 : texte = "10 flèches pour 10 Ganon d'or ?**              OUI ?            non  ";
            if (!gpJeu->getJoueur()->hasObjet(O_ARC)) {id=373; chercheText(); break;}
            else if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10) idsuiv=75; break;
        case 642 : texte = "10 flèches pour 10 Ganon d'or ?**              oui              NON ?"; break;
        case 643 : texte = "5 bombes pour 15 Ganon d'or ?**              OUI ?            non  ";
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=372; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<15) idsuiv=75; break;
        case 644 : texte = "5 bombes pour 15 Ganon d'or ?**              oui              NON ?"; break;
        case 645 : texte = "Un petit coeur pour 4 Ganon d'or ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getVie() + gpJeu->getJoueur()->getBoostVie() >= gpJeu->getJoueur()->getVieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<4) idsuiv=75; break;
        case 646 : texte = "Un petit coeur pour 4 Ganon d'or ?**              oui              NON ?"; break;
        case 647 : texte = "Une petite fiole de magie pour 8 Ganon d'or ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<8) idsuiv=75; break;
        case 648 : texte = "Une petite fiole de magie pour 8 Ganon d'or ?**              oui              NON ?"; break;
        case 649 : texte = "Une grande fiole de magie pour 16 Ganon d'or ? *              OUI ?            non  ";
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<16) idsuiv=75; break;
        case 650 : texte = "Une grande fiole de magie pour 16 Ganon d'or ? *              oui              NON ?"; break;
        case 651 : 
            if (gpJeu->getJoueur()->getGanonMax()>0) {id=652; chercheText(); break;}
            texte = "Chaque seconde est une goutte de plus dans la cafetière, tu me fais perdre mon temps."; break;
        case 652 :
            if (gpJeu->getJoueur()->getCafe()>-1) {id=653; chercheText(); break;}
            texte = "Tu veux bosser pour moi ? La valeur d'un homme se mesure à sa charge de travail, c'est ce que je dis toujours !"; idsuiv=653; break;
        case 653 : 
            if (gpJeu->getJoueur()->getChargeCafe()==-1 
            && gpJeu->getMonde()->motifValue(6*16,8*16)==1005) {id=655; chercheText(); break;}
            if (gpJeu->getJoueur()->getCafe()>=17) {id=672; chercheText(); break;}
            texte = "Cours sur le tapis roulant pour charger la dynamo, puis marche sur l'interrupteur. Cela mettra en marche la cafetière. Après ça viens me voir, et tu auras de l'argent."; idsuiv=654; break;
        case 654 : texte = "Je ne te demande pas si tu es prêt, la préparation est l'ultime refuge des faibles."; break;
        case 655 : 
            if (gpJeu->getJoueur()->getCafe()>1) {
                id=654+gpJeu->getJoueur()->getCafe(); chercheText(); break;}
            texte = "Je ne bois jamais plus de 17 tasses de café par jour.*Mais la première est toujours la meilleure."; break;
        case 656 : texte = "Plus noir qu'une nuit sans lune, plus brûlant et amer que l'enfer... *Ca, c'est du café."; break;
        case 657 : texte = "Visiblement, on va en prendre une autre pour la route."; break;
        case 658 : texte = "Au fait, ne mets pas de sel dans ton café. J'ai essayé, c'est dégoûtant."; break;
        case 659 : texte = "Ce café... C'est un mélange spécial que j'ai appelé Godot N107. J'hésite entre réduire son acidité et diminuer son amertume... C'est tout ce que j'ai en tête pour l'instant..."; break;
        case 660 : texte = "Ah... !*Ma 6ème tasse de café me regarde d'un air froid."; break;
        case 661 : texte = "Mélange Godot N102...*... Mon préféré."; break;
        case 662 : texte = "Ah... ! Ce mélange...*Du mélange Godot N107...*Il est peut-être un peu trop amer en fin de compte !"; break;
        case 663 : texte = "...*Aaah, amer !"; break;
        case 664 : texte = "Les faibles se font emporter par le flot du destin, les forts arrivent à l'ingurgiter. *Ah... !*Le destin a, aujourd'hui encore, un goût d'amertume."; break;
        case 665 : texte = "Ma 11ème tasse...*Je me suis promis de ne pas dépasser 17 tasses par jour, j'ai donc encore de la marge..."; break;
        case 666 : texte = "Une petite goutte de lait suffit à détruire la noire magie du café !"; break;
        case 667 : texte = "... Quelle amertume.*Tu apprendras à apprécier l'amertume quand tu seras plus grand."; break;
        case 668 : texte = "Tu connais ma règle d'or ?*Jeter la tasse de café qui est imbuvable et en prendre une autre."; break;
        case 669 : texte = "Ah !*En ce cas, le moment est bien choisi... pour une autre tasse de magie noire !"; break;
        case 670 : texte = "Deux minutes ne suffisent pas pour extraire tout l'arôme d'un bon arabica..."; break;
        case 671 : texte = "La 17ème et dernière tasse.*L'heure est venue de classer cette affaire."; break;
        case 672 : 
            if (gpJeu->getJoueur()->getGemme(173)) {id=673; chercheText(); break;}
            texte = "J'ai bu mes 17 tasses, voilà une récompense :"; break;
        case 673 : texte = "Tu as encore besoin d'argent ? En voilà..."; break;
        case 674 :
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = "Les potions rouges redonnent de l'énergie alors que les potions vertes redonnent de la magie."; 
            idsuiv=675; break;
        case 675 : texte = "Que désires-tu ?*                ? POTION ROUGE ?*                  potion verte  *                      rien      "; idsuiv=678; break;
        case 676 : texte = "Que désires-tu ?*                  potion rouge  *                ? POTION VERTE ?*                      rien      "; 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=374;
            else idsuiv=680; break;
        case 677 : texte = "Que désires-tu ?*                  potion rouge  *                  potion verte  *                ?     RIEN     ?"; break;
        case 678 : texte = "Une potion rouge pour 40 Ganon d'or ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<40) idsuiv=75; break;
        case 679 : texte = "Une potion rouge pour 40 Ganon d'or ?**              oui              NON ?"; break;
        case 680 : texte = "Une potion verte pour 25 Ganon d'or ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<25) idsuiv=75; break;
        case 681 : texte = "Une potion verte pour 25 Ganon d'or ?**              oui              NON ?"; break;
        case 682 : 
            if (gpJeu->getJoueur()->getCoffre(15,14)) {id=683; chercheText();break;}
            texte = "Ma famille n'a connu que malchance sur malchance depuis des siècles...*Même que je le voudrais, je n'aurai rien à t'offrir."; break;
        case 683 :
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>=4) {id=685; chercheText();break;}
            texte = "Je suis l'homme le plus chanceux du pays."; buffer = "Tu ne me crois pas ?*Prends ce trésor que j'ai trouvé ce matin en me promenant, j'en trouverai sans doute un nouveau demain!"; break;
        case 684 : texte = "Tu obtiens un bijou précieux !"; break;
        case 685 : texte = "C'est curieux, en te donnant ce bijou j'ai l'étrange impression de régler une vieille dette familiale..."; break;
        case 686 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>4) {id=693; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==4 
            && gpJeu->getJoueur()->getObjet()==15) {id=687; chercheText();break;}
            texte = "Je suis le pâtissier le plus réputé du pays."; buffer = "Malheureusement je n'ai plus rien en stock, on ne trouve plus grand chose de sucré depuis longtemps..."; break;
        case 687 : texte = "Tu as de la confiture ???*Je croyais que les dernières étaient périmées depuis des lustres! Donne-la-moi, contre ma réserve spéciale petit déj'!"; idsuiv=688; break;
        case 688 : texte = "Cette confiture contre sa réserve, ok ?**              OUI ?            non  "; idsuiv=690; break;
        case 689 : texte = "Cette confiture contre sa réserve, ok ?**              oui              NON ?"; idsuiv=691; break;
        case 690 : texte = "Je sens que je vais me régaler demain moi! *Voilà ce que je gardais de côté :"; break;
        case 691 : texte = "Dans ce cas pourquoi me l'as-tu présenté ? *Frimeur..."; break;
        case 692 : texte = "Tu as troqué la confiture contre un croissant."; break;
        case 693 : texte = "Tôt ou tard, il va bien falloir que je change de métier tout de même..."; break;
        case 694 :
            if (gpJeu->getJoueur()->getGanonMax() > 0) {id=696; chercheText();break;}
            texte = "Tu as l'air encore plus fauché que moi...*Tu devrais voir le gars de la maison du café, il cherche un employé."; buffer = "Prends également ça, tu en auras besoin :"; break;
        case 695 : texte = "Tu as obtenu une bourse pouvant contenir 99 Ganon d'or !"; break;
        case 696 : texte = "Alors, comment se portent tes finances ?"; break;
        case 697 : 
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())<2 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<4) idsuiv=698;
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())<2 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>3) idsuiv=699;
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>1 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<4) idsuiv=704;
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>1 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>3) idsuiv=709;
            texte = "Bienvenue dans la banque d'Hyrule. Je suis spécialisé en devises."; break;
        case 698 : texte = "Tu n'as rien qui m'intéresse, reviens si tu trouves des devises précieuses, je t'en donnerai un bon prix."; break;
        case 699 : texte = "Ce sont des Rubis dis-tu ? C'est assez curieux."; idsuiv=700; break;
        case 700 : texte = "Ca a l'air précieux, alors voyons..."; idsuiv=701; break;
        case 701 : 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()==gpJeu->getJoueur()->getPieceMax()) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            while (g%4 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*4;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/4);
            texte = os.str()+" Rubis contre "+os2.str()+" Pièce d'or, ok ?**              OUI ?            non  "; idsuiv=703; break;
        case 702 : 
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            while (g%4 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*4;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/4);
            texte = os.str()+" Rubis contre "+os2.str()+" Pièce d'or, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 703 : texte = "Affaire conclue!"; break;
        case 704 : texte = "Tu possèdes de l'or ? Avec une tête de monstre dessus... Des Ganon d'or tu dis ?"; idsuiv=705; break;
        case 705 : texte = "C'est très laid, mais l'or est récupérable, alors voyons..."; idsuiv=706; break;
        case 706 : 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()==gpJeu->getJoueur()->getPieceMax()) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+" Ganon d'or contre "+os2.str()+" Pièce d'or, ok ?**              OUI ?            non  "; idsuiv=708; break;
        case 707 : 
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+" Ganon d'or contre "+os2.str()+" Pièce d'or, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 708 : texte = "Affaire conclue!"; break;
        case 709 : texte = "Que veux-tu me vendre ?*   - RUBIS ?*   - Ganon d'or  *   - Rien  "; idsuiv=700; break;
        case 710 : texte = "Que veux-tu me vendre ?*   - Rubis  *   - GANON D'OR ?*   - Rien  "; idsuiv=705; break;
        case 711 : texte = "Que veux-tu me vendre ?*   - Rubis  *   - Ganon d'or  *   - RIEN ?"; idsuiv=76; break;
        case 712 :
            if (gpJeu->getJoueur()->getCoffre(15,22)) {id=717; chercheText();break;}
            texte = "Bonjour Link, je t'attendais."; idsuiv=713; break;
        case 713 : texte = "Je suis le chef des 7 sages, mais aussi le plus puissant d'entre eux. Je t'ai vu dans mes songes, ainsi qu'un bien triste avenir..."; idsuiv=714; break;
        case 714 : texte = "Ta présence ici semble indiquer que j'ai réussi... Au moins partiellement..."; idsuiv=715; break;
        case 715 : texte = "Je suis celui qui a créé le portail vers le futur, dans le but que tu sois témoin de l'objet de mes visions."; idsuiv=716; break;
        case 716 : texte = "J'ai également construit le temple du Temps avec les autres sages, pour te permettre de voyager à ta guise entre les époques."; idsuiv=717; break;
        case 717 : texte = "Désormais c'est à toi de jouer. Trouve les 7 cristaux magiques qui t'ouvriront l'accès au légendaire temple des Déesses, et soit le premier à t'emparer de la Triforce!"; idsuiv=718; break;
        case 718 : texte = "Puisse son chemin mener le héros à la Triforce."; break;
        case 719 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>2
            && gpJeu->getJoueur()->hasObjet(O_TROC2)>3
            && gpJeu->getJoueur()->hasObjet(O_TROC3)>3) {id=726; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==2 
            && gpJeu->getJoueur()->getObjet()==3) {id=720; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==3 
            && gpJeu->getJoueur()->getObjet()==7) {id=727; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==3 
            && gpJeu->getJoueur()->getObjet()==11) {id=733; chercheText();break;}
            texte = "Ne te fie pas à ma taille, je suis un forgeron de premier ordre."; 
            buffer = "Cependant je dois avouer que je viens d'emménager, et je n'étais pas de taille à déménager ma forge jusqu'ici... Donc je n'ai plus rien."; break;
        case 720 : texte = "Tu as transporté une enclume avec toi ???*T'es bête ou quoi ?"; buffer = "Je peux t'en délester si tu veux, je pourrais en avoir besoin. *Je te donnerai même une petite récompense pour l'effort."; idsuiv=721; break;
        case 721 : texte = "Cette enclume contre une récompense, ok ?**              OUI ?            non  "; idsuiv=723; break;
        case 722 : texte = "Cette enclume contre une récompense, ok ?**              oui              NON ?"; idsuiv=724; break;
        case 723 : texte = "Merci, voici un fer à cheval que j'avais réalisé il y a quelques temps :"; break;
        case 724 : texte = "Je disais ça pour t'aider..."; break;
        case 725 : texte = "Tu as obtenu un fer à cheval!"; break;
        case 726 : texte = "Avec tout ce que tu m'as apporté, je vais pouvoir réouvrir ma forge!"; break;
        case 727 : texte = "C'est un beau marteau que tu as là...*Il pourrait faire l'affaire pour ma forge... Tu me le cèderais ? Je te récompenserai par une de mes créations."; idsuiv=728; break;
        case 728 : texte = "Ce marteau contre une récompense, ok ?**              OUI ?            non  "; idsuiv=730; break;
        case 729 : texte = "Ce marteau contre une récompense, ok ?**              oui              NON ?"; idsuiv=731; break;
        case 730 : texte = "Merci, voici une de mes plus belles créations :"; break;
        case 731 : texte = "Comme si ce marteau pouvait t'être utile..."; break;
        case 732 : texte = "Tu as obtenu une clochette!"; break;
        case 733 : texte = "Tu as de la poudre d'or ?*J'en aurai besoin pour forger à nouveau des objets exceptionnels, tu me la donnes contre une récompense exceptionnelle ?"; idsuiv=734; break;
        case 734 : texte = "La poudre d'or contre une récompense, ok ?**              OUI ?            non  "; idsuiv=736; break;
        case 735 : texte = "La poudre d'or contre une récompense, ok ?**              oui              NON ?"; idsuiv=737; break;
        case 736 : texte = "Merci, prends ce miroir magique en échange! *Il a été envoûté par les sages et possède un pouvoir mystérieux..."; break;
        case 737 : texte = "Je t'aurais largement dédommagé pourtant..."; break;
        case 738 : texte = "Tu as obtenu le miroir magique!"; break;
        case 739 : 
            if (gpJeu->getJoueur()->getEpee()>2) {id=748; chercheText();break;}
            if (gpJeu->getJoueur()->getEpee()==0) {id=745; chercheText();break;}
            texte = "Ton épée est impressionnante... Je devrais toutefois pouvoir l'améliorer..."; idsuiv=740; break;
        case 740 : texte = "Veux-tu que je reforge ton épée ?**              OUI ?            non  "; idsuiv=742; break;
        case 741 : texte = "Veux-tu que je reforge ton épée ?**              oui              NON ?"; idsuiv=743; break;
        case 742 : texte = "Laisse-moi ton épée dans ce cas, ce ne sera pas long."; break;
        case 743 : texte = "Dommage, ton épée est vraiment fascinante..."; break;
        case 744 : texte = "Tu as confié Excalibur."; break;
        case 745 : texte = "Ce ne sera pas long, ne t'inquiète pas."; break;
        case 746 :
            if (gpJeu->getJoueur()->getEpee()) {id=748; chercheText();break;}
            texte = "C'est prêt, voici ton épée :"; break;
        case 747 : texte = "Excalibur a été reforgée! Sa puissance a bien augmenté!"; break;
        case 748 : texte = "Un jour, je forgerai une épée aussi belle que la tienne, foi de forgeron!"; break;
        case 749 : texte = "Tu ne devrais pas t'éloigner du village par ce temps..."; break;
        case 750 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "10 flèches pour 5 Pièces d'or ?**              OUI ?            non  ";
            if (!gpJeu->getJoueur()->hasObjet(O_ARC)) {id=373; chercheText(); break;}
            else if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<5) idsuiv=75; break;
        case 751 : texte = "10 flèches pour 5 Pièces d'or ?**              oui              NON ?"; break;
        case 752 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "5 bombes pour 10 Pièces d'or ?**              OUI ?            non  ";
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=372; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<10) idsuiv=75; break;
        case 753 : texte = "5 bombes pour 10 Pièces d'or ?**              oui              NON ?"; break;
        case 754 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Un petit coeur pour 1 Pièce d'or ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getVie() + gpJeu->getJoueur()->getBoostVie() >= gpJeu->getJoueur()->getVieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<1) idsuiv=75; break;
        case 755 : texte = "Un petit coeur pour 1 Pièce d'or ?**              oui              NON ?"; break;
        case 756 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Une petite fiole de magie pour 3 Pièces d'or ? *              OUI ?            non  ";
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<3) idsuiv=75; break;
        case 757 : texte = "Une petite fiole de magie pour 3 Pièces d'or ? *              oui              NON ?"; break;
        case 758 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Une grande fiole de magie pour 6 Pièces d'or ? *              OUI ?            non  ";
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<6) idsuiv=75; break;
        case 759 : texte = "Une grande fiole de magie pour 6 Pièces d'or ? *              oui              NON ?"; break;
        case 760 : texte = "Tu as trouvé le livre de Mudora!*Tu comprends désormais le Hylien ancien !"; break;
        case 761 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Bonjour, je suis le chef de ce village. *N'écoute pas les rumeurs comme quoi ce village serait menacé, et passe du bon temps parmi nous."; break;
        case 762 : texte = "La neige semble s'être arrêtée..."; break;
        case 763 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = "Les potions rouges redonnent de l'énergie alors que les potions vertes redonnent de la magie."; 
            idsuiv=764; break;
        case 764 : texte = "Que désires-tu ?*                ? POTION ROUGE ?*                  potion verte  *                      rien      "; idsuiv=767; break;
        case 765 : texte = "Que désires-tu ?*                  potion rouge  *                ? POTION VERTE ?*                      rien      "; 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=374;
            else idsuiv=769; break;
        case 766 : texte = "Que désires-tu ?*                  potion rouge  *                  potion verte  *                ?     RIEN     ?"; break;
        case 767 : texte = "Une potion rouge pour 15 Pièces d'or ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<15) idsuiv=75; break;
        case 768 : texte = "Une potion rouge pour 15 Pièces d'or ?**              oui              NON ?"; break;
        case 769 : texte = "Une potion verte pour 10 Pièces d'or ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<10) idsuiv=75; break;
        case 770 : texte = "Une potion verte pour 10 Pièces d'or ?**              oui              NON ?"; break;
        case 771 : texte = "Tu as l'air bien pauvre, tu n'as même pas de bourse sur toi ?*Prends donc celle-là :"; break;
        case 772 : texte = "Tu as obtenu une bourse pouvant contenir 99 pièces d'or !"; break;
        case 773 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Bonjour, je suis un des 7 sages, de passage dans le coin."; idsuiv=774; break; 
        case 774 :
            texte ="Le livre de Mudora a été envoûté pour permettre à quiconque le possède de parler couramment notre langue.";
            buffer = "Tu dois venir de loin pour ne pas parler hylien... Garde ce livre, tu en auras besoin."; break;
        case 775 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Salut mon gars, moi c'est Ganondorf, si tu découvres quoi que ce soit sur les cristaux magiques, tu viens m'en parler, ça marche ?"; break;
        case 776 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Je suis le chef des chevaliers hyliens. *Si tu ne veux pas de soucis tiens-toi à carreau, prends exemple sur Ganondorf, c'est un bon gars."; break;
        case 777 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Ce Ganondorf n'arrête pas de nous payer à boire... *C'est vraiment un type bien..."; break;
        case 778 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>5) {id=785; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==5 
            && gpJeu->getJoueur()->getObjet()==15) {id=779; chercheText();break;}
            texte = "C'est bien beau de boire... mais quand est-ce qu'on mange ?"; break;
        case 779 : texte = "Ne me dis rien... A l'odeur... C'est un croissant !*Donne-le-moi, en échange de mon amitié éternelle!"; idsuiv=780; break;
        case 780 : texte = "Ce croissant contre son amitié, ok ?**              OUI ?            non  "; idsuiv=782; break;
        case 781 : texte = "Ce croissant contre son amitié, ok ?**              oui              NON ?"; idsuiv=783; break;
        case 782 : texte = "Merci!!!*Prends ce cadeau en échange, ce sera le symbole de notre amitié!"; break;
        case 783 : texte = "... Tu déclares la guerre aux chevaliers hyliens ???*T'es fou ou quoi ???"; break;
        case 784 : texte = "Tu as troqué le croissant contre une bière."; break;
        case 785 : texte = "Salut mon pote!*Tu viens boire un coup avec nous ?"; break;
        case 786 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = "Si tu veux qu'un chevalier hylien te dévoile une info top secrète, il faut lui payer à boire. C'est notre règle."; break;
        case 787 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->getCoffre(15,23)<3) {id=788; chercheText(); break;}
            texte = "Tu connais déjà toutes mes infos...*Hic!"; break;
        case 788 : 
            texte = "J'ai plein d'infos secrètes connues de nous seuls (et de Ganondorf). Un verre de bière coûte 1 pièce d'or, affaire conclue ?"; idsuiv=789; break;
        case 789 : 
            texte = "Une info pour 1 pièce d'or, ok ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<1) idsuiv=75; break;
        case 790 : texte = "Une info pour 1 pièce d'or, ok ?**              oui              NON ?"; idsuiv=76; break;
        case 791 : 
            if (gpJeu->getJoueur()->getCoffre(15,23)>0) {id=792; chercheText(); break;}
            texte = "Les chevaliers hyliens auraient été fondés pour protéger le légendaire temple des Déesses... Temple qui cacherait une relique toute puissante appelée Triforce..."; break;
        case 792 : 
            if (gpJeu->getJoueur()->getCoffre(15,23)>1) {id=793; chercheText(); break;}
            texte = "Pour ouvrir l'accès au temple des Déesses, il faut se rendre sur la terre sacrée, au nord d'ici, et se tenir sur le symbole de la Triforce avec les 7 cristaux magiques en poche."; break;
        case 793 : texte = "Les 7 cristaux magiques sont cachés un peu partout dans Hyrule... Et, garde ça pour toi, l'un d'entre eux est en possession des légendaires chevaliers hyliens!"; break;
        case 794 : texte = "Notre chef l'a poursuivi en bas..."; break;
        case 795 : texte = "Quelle force... nous avons été balayés si vite..."; break;
        case 796 : texte = "Il est... au sous-sol...*Soit prudent... ... mon ami."; break;
        case 797 : texte = "Il est trop fort... Le chef ne tiendra pas longtemps...*Va l'aider, je t'en prie..."; break;
        case 798 : texte = "Il... faut l'arrêter..."; break;
        case 799 : texte = "Tu comptes également te mettre sur mon chemin ? Alors en garde!"; break;
        case 800 : texte = "J'ai échoué...*Pardonnez-moi maître..."; break;
        case 801 : texte = "Merci de ton aide Link, sans toi Ganondorf se serait emparé du cristal..."; idsuiv=802; break;
        case 802 : texte = "L'ordre des chevaliers a été fondé pour garder l'accès au temple des Déesses, nous avions donc pour mission de cacher ce cristal. Sans celui-ci, les 6 autres ne servent à rien."; idsuiv=803; break;
        case 803 : texte = "Hélas, avec le temps, l'ordre s'est affaibli. Et aujourd'hui, nous avons échoué."; idsuiv=804; break;
        case 804 : texte = "Garde le cristal, tu es plus à même de le défendre que nous..."; idsuiv=805; break;
        case 805 : texte = "Quant à Ganondorf... Jamais nous n'aurions pu deviner qu'il allait nous trahir... Il était pratiquement l'un des nôtres..."; idsuiv=806; break;
        case 806 : texte = "Il a été conduit à la prison de haute sécurité, un peu au Nord d'ici... *Il ne devrait plus causer de soucis désormais..."; break;
        case 807 : 
            if (gpJeu->getJoueur()->getGemme(178)) {id=816; chercheText(); break;}
            texte = "J'ai échoué contre Ganondorf, mais ne me sous-estime pas pour autant. Je suis l'homme qui a vaincu 100 loups."; idsuiv=808; break;
        case 808 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=1) {id=809; chercheText(); break;}
            texte = "Tu n'as battu aucun loup ???*Mais t'es un lâche!"; break;
        case 809 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=2) {id=810; chercheText(); break;}
            texte = "Tu n'as battu qu'un seul loup ???*Mais t'es un faible!"; break;
        case 810 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=50) {id=811; chercheText(); break;}
            os << g;
            texte = "Tu as battu seulement "+os.str()+" loups ?*C'est pas terrible..."; break;
        case 811 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=80) {id=812; chercheText(); break;}
            os << g;
            texte = "Tu as battu "+os.str()+" loups ?*C'est pas mal..."; break;
        case 812 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=100) {id=813; chercheText(); break;}
            os << g;
            texte = "Tu as battu "+os.str()+" loups ?*C'est plutôt impressionnant..."; break;
        case 813 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>100) {id=814; chercheText(); break;}
            texte = "Tu as battu 100 loups ?*Autant que moi... c'est dur à croire..."; break;
        case 814 : 
            texte = "Tu as battu plus de 100 loups ???*Incroyable..."; idsuiv=815; break;
        case 815 : texte = "Tu as bien mérité cette récompense :"; break;
        case 816 : texte = "Il est temps pour moi de reprendre l'entraînement..."; break;
        case 817 : texte = "Je vais changer de coiffure."; break;
        case 818 : texte = "Je vais commencer un régime."; break;
        case 819 : texte = "Je ne vendrai plus d'infos top secrètes."; break;
        case 820 : texte = "Je ne passerai plus mes journées à la taverne."; break;
        case 821 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>5) {id=828; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==5 
            && gpJeu->getJoueur()->getObjet()==7) {id=822; chercheText();break;}
            texte = "J'ai cassé ma dernière hache... Alors je joue au pendu pour tuer le temps, mais c'est pas pareil..."; break;
        case 822 : texte = "Tu as une hache pour moi ???*Donne-la-moi! Je te l'échange contre une corde tout aussi efficace!"; idsuiv=823; break;
        case 823 : texte = "Cette hache contre une corde, ok ?**              OUI ?            non  "; idsuiv=825; break;
        case 824 : texte = "Cette hache contre une corde, ok ?**              oui              NON ?"; idsuiv=826; break;
        case 825 : texte = "Je suis tellement ému...*Voilà pour toi :"; break;
        case 826 : texte = "...*Ca devrait être passible de la peine de mort..."; break;
        case 827 : texte = "Tu as troqué la hache contre une corde."; break;
        case 828 : texte = "Je suis impatient d'essayer cette hache!"; break;
        case 829 : texte = "Bonjour, je suis le chef de ce village."; idsuiv=830; break;
        case 830 : texte = "Le village des Mouettes est le paradis pour les touristes, mais aussi l'enfer pour les brigands."; buffer = "Savais-tu qu'un célèbre pirate avait été capturé lors de son passage dans cette ville ?"; break;
        case 831 : texte = "Tu as trouvé un marteau!"; break;
        case 832 : 
            if (gpJeu->getJoueur()->getCoffre(15,26)) {id=839; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==6 
            && gpJeu->getJoueur()->getObjet()==3) {id=833; chercheText();break;}
            texte = "Mon époux est garde à la prison.*C'est un travail à temps plein alors on ne se voit pas beaucoup..."; break;
        case 833 : texte = "???*Qu'as-tu là ???*Laisse-moi examiner ça!"; idsuiv=834; break;
        case 834 : texte = "Lui laisser l'alliance, ok ?**              OUI ?            non  "; idsuiv=836; break;
        case 835 : texte = "Lui laisser l'alliance, ok ?**              oui              NON ?"; idsuiv=837; break;
        case 836 : texte = "L'alliance de mon mari!*Ne me dis pas qu'il est retourné LA voir!!!"; break;
        case 837 : texte = "...*Ca me semble très louche...*Laisse-moi voir ça!"; idsuiv=834; break;
        case 838 : texte = "Tu as troqué l'alliance contre rien."; break;
        case 839 : texte = "Pousse-toi de mon chemin!"; break;
        case 840 : texte = "Ne va pas à la réserve, je n'y ai pas fait le ménage!"; break;
        case 841 : texte = "Un célèbre pirate nommé Ganon D. Roger fut capturé dans cette ville il y a bien longtemps...";
            buffer = "D'après des rumeurs, un descendant de ce pirate serait à Hyrule en ce moment..."; break;
        case 842 : texte = "Tu es ici dans la demeure des 7 sages.*Ce lieu est celui de la méditation et de la connaissance."; break;
        case 843 : texte = "Notre chef, le plus puissant des 7 sages, vient rarement ici. Il préfère rester à méditer dans sa maison au Sud du village."; break;
        case 844 : texte = "Il y a quelques années, nous étions 8 sages. L'un d'entre nous, Agahnim, pensait qu'il était de notre devoir de récupérer la Triforce et de s'en servir dans l'intérêt de tous."; idsuiv=845; break;
        case 845 : texte = "Notre chef s'y opposa catégoriquement. Il disait qu'un tel pouvoir ne devait pas tomber entre les mains des hommes, que les conséquences pourraient être terribles..."; idsuiv=846; break;
        case 846 : texte = "Après ce différent, Agahnim quitta l'ordre. Mais dernièrement, il a réapparu, doté d'étranges pouvoirs...*Nous ne savons hélas pas ce qu'il a en tête."; break;
        case 847 : texte = "Un pirate légendaire est venu en Hyrule il y a longtemps. Il fut capturé à la suite d'un long combat face aux chevaliers hyliens de l'époque."; idsuiv=848; break;
        case 848 : texte = "Le jour de son exécution publique, un homme dans la foule lui demanda où il avait caché son trésor. Le pirate expliqua l'avoir caché dans 4 temples d'Hyrule."; idsuiv=849; break;
        case 849 : texte = "Suite à cette déclaration, de nombreux hommes partir à la recherche de ces trésors, mais aucun ne revint jamais..."; break;
        case 850 : texte = "As-tu rencontré un certain Ganondorf ? *Lorsqu'il était encore enfant, il faillit finir dans l'estomac d'un loup, mais fut sauvé par un ancien membre de notre ordre."; idsuiv=851; break; 
        case 851 : texte = "Depuis il considère son sauveur comme son mentor."; break;
        case 852 : texte = "Notre chef nous demanda d'unir nos pouvoirs pour créer un temple très particulier à l'Est d'ici. Selon lui ce temple permettra de sauver le monde..."; break;
        case 853 : 
            if (gpJeu->getJoueur()->getGemme(182)) {id=854; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>0) {id=855; chercheText();break;}
            texte = "La montagne au Nord du village cache un temple. Au fond de ce temple se trouve un trésor inestimable. Mais... c'est bien trop dangereux d'y aller."; break;
        case 854 : texte = "Je n'en reviens toujours pas que tu aies pu récupérer ce trésor..."; break;
        case 855 : texte = "QUOI ??? TU AS TROUVE LE TRESOR DU TEMPLE !!!"; idsuiv=856; break;
        case 856 : texte = "Incroyable... prends ça, je tiens à te récompenser pour ton exploit!"; break;
        case 857 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>4) {id=864; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==4 
            && gpJeu->getJoueur()->getObjet()==3) {id=858; chercheText();break;}
            texte = "Ca fait longtemps qu'IL ne m'a rien offert..."; break;
        case 858 : texte = "Tu as un bijou pour moi ?*Ca vient de LUI n'est-ce pas ?*Oui ça ne peut venir que de LUI!"; idsuiv=859; break;
        case 859 : texte = "Donner ce bijou ?**              OUI ?            non  "; idsuiv=861; break;
        case 860 : texte = "Donner ce bijou ?**              oui              NON ?"; idsuiv=862; break;
        case 861 : texte = "C'est tellement gentil de sa part...*Peux-tu aller lui porter cette lettre à la prison s'il te plaît ?"; break;
        case 862 : texte = "...*Je LUI dirai !"; break;
        case 863 : texte = "Tu as troqué le bijou contre une lettre."; break;
        case 864 : texte = "Hi! Hi! Hi!"; break;
        case 865 : texte = "Je suis le chef du village et euh... de toute façon ce sont les sages qui commandent ici..."; break;
        case 866 :
            if (gpJeu->getJoueur()->getCoffre(15,27)==12) {id=886; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(15,27)) {id=868; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==7 
            && gpJeu->getJoueur()->getObjet()==11) {id=867; chercheText();break;}
            texte = "Nous sommes fermés au public."; break;
        case 867 : texte = "Nous t'avons longtemps attendu...*Prends le temps de visiter mon opéra..."; break;
        case 868 : texte = "Cet opéra a une longue histoire, prends le temps de la découvrir..."; break;
        case 869 : texte = "Bienvenue à toi visiteur, laisse-moi te conter l'histoire de cet endroit."; buffer="Je suis le fondateur de cet opéra, mais autrefois je n'étais qu'un simple voleur."; break;
        case 870 : texte = "Un jour, un cambriolage a mal tourné, les chevaliers hyliens qui patrouillaient près de la taverne me sont tombés dessus. Je fus condamné et emmené en prison."; break;
        case 871 : texte = "En prison, je trouvai un vieux crâne sous ma couchette. Je m'en servis alors comme accessoire pour réciter des tirades, au grand bonheur de mon compagnon de cellule."; idsuiv=872; break;
        case 872 : texte = "C'est donc en prison que ma vocation pour le théâtre, puis pour l'opéra, débuta."; break;
        case 873 : texte = "Peu de temps avant ma libération, je me fis la promesse sur le vieux crâne de construire le plus somptueux des théâtres avant la sortie de prison de mon compagnon de cellule."; break;
        case 874 : texte = "Une fois libéré, je partis à la recherche d'un terrain où construire. Jusqu'au jour où, poursuivi par des loups, je dus me réfugier aux bois perdus."; idsuiv=875; break;
        case 875 : texte = "C'est alors que je trouvai cette clairière, au fin fond de la forêt, dans un cadre magique, sous l'ombre d'arbres millénaires..."; break;
        case 876 : texte = "Je commençai alors à construire mon opéra. Les plans furent rapidement prêts, mais sans argent pour payer des ouvriers, le travail s'annonçait long et pénible."; idsuiv=877; break;
        case 877 : texte = "Alors que je songeais à renoncer, un étrange personnage vint m'apporter le crâne, et me remémorer ma promesse."; break;
        case 878 : texte = "Après des mois de travail, l'opéra fut achevé. Ce fut le plus bel opéra jamais vu en Hyrule."; break;
        case 879 : texte = "Très vite, de prestigieux artistes venant de tout le pays vinrent se produire ici. J'avais réussi mon rêve et tenu ma promesse."; break;
        case 880 : texte = "Durant la guerre contre Ganon, des contrebandiers profitèrent du désordre pour prospérer."; idsuiv=881; break;
        case 881 : texte = "L'un d'entre eux n'était autre que mon ancien compagnon de cellule, fraîchement sorti de prison, qui me demanda à se servir de l'opéra comme planque."; break;
        case 882 : texte = "Une fois la paix revenue, le roi d'Hyrule voulu mettre fin à la contrebande. Il envoya ses meilleurs hommes traquer les responsables."; idsuiv=883; break;
        case 883 : texte = "Pris de panique de peur de tout perdre à cause de ma complicité, je demandai à mon ancien compagnon de quitter l'opéra, le menaçant de le livrer au roi s'il refusait."; break;
        case 884 : texte = "Forcés de quitter l'opéra, les bandits m'enfermèrent dans leur ancienne planque ainsi que le personnel, avant d'y mettre le feu."; idsuiv=885; break;
        case 885 : texte = "C'est ainsi que je suis mort, emportant avec moi cet opéra, qui fut détruit à jamais..."; break;
        case 886 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>7) {id=893; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==7 
            && gpJeu->getJoueur()->getObjet()==11) {id=887; chercheText();break;}
            texte = "Tu connais mon histoire, n'as-tu rien à me présenter ?"; break;
        case 887 : texte = "J'ai attendu des siècles ta venue pour régler cette vieille dette..."; idsuiv=888; break;
        case 888 : texte = "Faire régler la dette ?**              OUI ?            non  "; idsuiv=890; break;
        case 889 : texte = "Faire régler la dette ?**              oui              NON ?"; idsuiv=891; break;
        case 890 : texte = "Ma vie fut courte, mais passionnante. Rien de tout cela n'aurait été possible sans ton intervention."; buffer="Je tenais à te donner ceci : la scie dont je me suis servi pour construire cet opéra!"; break;
        case 891 : texte = "...*C'est une blague ?"; break;
        case 892 : texte = "Tu as troqué la reconnaissance de dette contre une scie."; break;
        case 893 : texte = "Va maintenant, il est temps pour nous de reposer en paix..."; break;
        case 894 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>1) {id=901; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==1 
            && gpJeu->getJoueur()->getObjet()==11) {id=895; chercheText();break;}
            texte = "En tant que barman, je connais toutes les rumeurs...";
            buffer = "En voilà une : ma couleur préférée serait le jaune...*Mais je t'ai rien dit, ok ?"; break;
        case 895 : texte = "C'est une jolie pierre jaune que tu as là... Tu me l'échanges contre ma meilleure bouteille ?"; idsuiv=896; break;
        case 896 : texte = "Cette gemme jaune contre une bouteille, ok ?**              OUI ?            non  "; idsuiv=898; break;
        case 897 : texte = "Cette gemme jaune contre une bouteille, ok ?**              oui              NON ?"; idsuiv=899; break;
        case 898 : texte = "Ouah! Elle est donc à moi!"; break;
        case 899 : texte = "Tsss... personne ne t'en proposera plus pourtant..."; break;
        case 900 : texte = "Tu as troqué la gemme jaune contre une bouteille de vin."; break;
        case 901 : texte = "Je te sers quelque chose ? Ce sera gratuit pour toi."; break;
        case 902 : 
            if (!gpJeu->getJoueur()->hasObjet(O_OCARINA)) {id=1079; chercheText();break;}
            texte = "Une mélodie est gravée sur la stèle :"; break;
        case 903 : texte = "Tu as appris le chant de l'envol ! *Joue-le à l'extérieur pour te téléporter!"; break;
        case 904 : texte = "Tu as appris le chant du temps inversé ! *Joue-le à l'extérieur pour remonter le temps!"; break;
        case 905 : texte = "Tu as appris le chant du temps accéléré ! *Joue-le à l'extérieur pour voyager vers le futur!"; break;
        case 906 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>5) {id=913; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==5 
            && gpJeu->getJoueur()->getObjet()==3) {id=907; chercheText();break;}
            texte = "Je suis garde à mi-temps dans cette prison. *En dehors des heures de visite je ne suis pas autorisé à te laisser passer."; break;
        case 907 : texte = "Cette lettre est pour moi ? Elle vient sûrement d'ELLE... Donne-la-moi vite!"; idsuiv=908; break;
        case 908 : texte = "Donner cette lettre ?**              OUI ?            non  "; idsuiv=910; break;
        case 909 : texte = "Donner cette lettre ?**              oui              NON ?"; idsuiv=911; break;
        case 910 : texte = "...*...*..."; buffer="Je dois quitter mon poste... c'est euh... une urgence... T'as l'air d'un bon gars, prends ma place. Ah et garde-moi ça :"; break;
        case 911 : texte = "Ce n'est pas pour moi ?*Tant pis..."; break;
        case 912 : texte = "Tu as troqué la lettre contre une alliance."; break;
        case 913 : texte = "Je dois y aller!"; break;
        case 914 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>5) {id=921; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==5 
            && gpJeu->getJoueur()->getObjet()==11) {id=915; chercheText();break;}
            texte = "Je suis un brave innocent arrivé ici par erreur... T'aurais pas quelque chose pour m'aider à filer d'ici ?"; break;
        case 915 : texte = "Une... petite cuillère hein ?"; idsuiv=916; break;
        case 916 : texte = "Donner la cuillère ?**              OUI ?            non  "; idsuiv=918; break;
        case 917 : texte = "Donner la cuillère ?**              oui              NON ?"; idsuiv=919; break;
        case 918 : texte = "Merci... ... ...*Tiens, voilà un cadeau de remerciement...*Ca appartenait à mon ancien compagnon de cellule..."; break;
        case 919 : texte = "Je sens qu'une magnifique possibilité d'évasion à la petite cuillère vient de s'envoler..."; break;
        case 920 : texte = "Tu as troqué la petite cuillère contre un crâne."; break;
        case 921 : texte = "Bon bah... j'ai du boulot hein..."; break;
        case 922 : texte = "Je ne pensais pas que ma mission pouvait échouer... Les chevaliers hyliens ne sont plus très forts, même leur chef commence à faiblir..."; break;
        case 923 : texte = "L'explosion venait de la pièce de droite."; break;
        case 924 : texte = "Ainsi voilà celui qui a pu arrêter le puissant Ganondorf..."; idsuiv=925; break;
        case 925 : texte = "Je suis Agahnim, ancien sage, et mentor de Ganondorf. Quant à toi, tu dois être Link..."; idsuiv=926; break;
        case 926 : texte = "Que cela te plaise ou non, nous allons nous emparer de la Triforce.*Adieu !"; break;
        case 927 : texte = "                   Niveau 1 :                                                                                Temple du Courage"; break;
        case 928 : texte = "                   Niveau 2 :                                                                               Temple de la Sagesse"; break;
        case 929 : texte = "                   Niveau 3 :                                                                                Temple de la Force"; break;
        case 930 : texte = "                   Niveau 4 :                                                                                Ruines des Abysses"; break;
        case 931 : texte = "                   Niveau 5 :                                                                                 Pyramide Fantôme"; break;
        case 932 : texte = "                Grande Pyramide"; break;
        case 933 : texte = "               Temple de la Terre"; break;
        case 934 : texte = "                Temple de l'Air"; break;
        case 935 : texte = "                Temple de l'Eau"; break;
        case 936 : texte = "                 Temple du Feu"; break;
        case 937 : texte = "               Temple des Déesses"; break;
        case 938 : 
            if (gpJeu->getAudio()->isSpecial()) {
            texte = "               Château d'Hyrule"; break;}
            texte = "                 Niveau Final :                                                                               Château d'Hyrule"; break;
        case 939 : texte = "           Seconde Quête - Niveau 1 :                                                                              Casino"; break;
        case 940 : texte = "           Seconde Quête - Niveau 2 :                                                                         Tour des Gemmes"; break;
        case 941 : texte = "         Seconde Quête - Niveau Final :                                                                      Destination Finale"; break;
        
#ifdef __PSP2__
        case 942 : texte = "Tu as trouvé la carte !!!**Appuie sur L pour voir le plan du donjon."; break;
#else
        case 942 : texte = "Tu as trouvé la carte !!!**Appuie sur P pour voir le plan du donjon."; break;
#endif
        case 943 : texte = "Tu as trouvé la boussole !!!**Les coffres et le boss du donjon sont désormais indiqués sur la carte."; break;
        case 944 : texte = "Tu as trouvé la clé du boss !!!**Sers-t'en pour accéder à son repère."; break;
        case 945 : texte = "Tu as trouvé une petite clé.**Sers-t'en pour déverrouiller une porte."; break;
        case 946 : texte = "Tu as trouvé un nouveau coeur !!!**Ta vie maximale augmente d'un coeur !!!"; break;
#ifdef __PSP2__
        case 947 : texte = "Tu as trouvé un arc !!!**Equipe-le en appuyant sur Croix puis sert-en avec Triangle pour attaquer à distance !"; break;
#else
        case 947 : texte = "Tu as trouvé un arc !!!**Equipe-le en appuyant sur Entrée puis sert-en avec X pour attaquer à distance !"; break;
#endif
        case 948 : 
            if (gpJeu->getZone()==47) {id=949; chercheText();break;}
            if (gpJeu->getZone()==48) {id=950; chercheText();break;}
            texte = "Tu as trouvé le Médaillon du Courage !!!"; break;
        case 949 : texte = "Tu as trouvé le Médaillon de la Sagesse !!!"; break;
        case 950 : texte = "Tu as trouvé le Médaillon de la Force !!!"; break;
        case 951 : texte = "Tu as trouvé les Gants de Puissances !!!**Tu peux désormais soulever des rochers !"; break;
        case 952 : 
            if (gpJeu->getJoueur()->hasObjet(O_GANTS)) {id=954; chercheText();break;}
            if (gpJeu->getJoueur()->getExplore(1,16,4)) {id=953; chercheText();break;}
            texte = "J'abandonne, t'as gagné!*Comment as-tu pu défaire la légendaire technique de l'Ultimate LOL ???"; break;
        case 953 : texte = "Tu ne vas pas me laisser m'en sortir comme ça, hein ?*Le code de la salle suivante est 12086... Maintenant va-t-en."; break;
        case 954 : texte = "J'aurais dû rester dans le gang familial..."; break;
        case 955 : texte = "Tu as trouvé la lanterne !!!**Tu peux désormais faire jaillir des flammes !"; break;
        case 956 : texte = "Tu as trouvé les palmes !!!**Tu peux désormais traverser les étendues d'eau !"; break;
        case 957 : 
            if (gpJeu->getJoueur()->getCoffre(3,29)) {id=960; chercheText();break;}
            texte = "???*Comment as-tu pu arriver jusqu'ici ? *Mon animal de compagnie était censé monter la garde!"; idsuiv=958; break;
        case 958 : texte = "...*Tu dis être Link ?*...*Le moment serait-il déjà venu ?"; idsuiv=959; break;
        case 959 : texte = "Les sbires de Ganon ont fini par découvrir mon existence et ont détruit le village où je vivais. Je suis alors venu dans ce temple pour me cacher."; idsuiv=960; break;
        case 960 : texte = "Continue ta quête Link, nous nous reverrons dans la grotte du portail!"; break;
        case 961 : texte = "Tu as trouvé une meilleure tunique !!!**Ta défense augmente d'un point !"; break;
        case 962 : texte = "Tu as trouvé la Clé du Temps !!!**Va vite la montrer aux sages !"; break;
        case 963 : texte = "Tu as trouvé le Marteau Magique !!!**Tu peux désormais aplatir les plots te bloquant le chemin !"; break;
        case 964 : texte = "Tu as trouvé les Gants des Titans !!!**Tu peux désormais soulever les pierres les plus lourdes !!!"; break;
        case 965 : texte = "Tu as trouvé une Gemme Jaune !**C'est un trésor inestimable !"; break;
        case 966 : texte = "Tu as trouvé l'Arc des Fées !!!**Tes flèches ont désormais une puissance phénoménale !!!"; break;
        case 967 : texte = "Tu as trouvé une Gemme Verte !**C'est un trésor inestimable !"; break;
        case 968 : texte = "Tu as trouvé la Baguette de Glace !!!**Tu peux désormais geler les ennemis à distance !!!"; break;
        case 969 : texte = "Tu as trouvé une Gemme Bleue !**C'est un trésor inestimable !"; break;
        case 970 : texte = "Tu as trouvé la Baguette de Feu !!!**Tu peux désormais lancer de puissantes boules de feu !!!"; break;
        case 971 : texte = "Tu as trouvé une Gemme Rouge !**C'est un trésor inestimable !"; break;
        case 972 : texte = "Tu as trouvé un bouclier incroyablement résistant !!!*Ta défense augmente d'un point !"; break;
        case 973 : texte = "Te voilà enfin."; idsuiv=974; break;
        case 974 : texte = "Croyais-tu vraiment pouvoir prendre de vitesse un mage maîtrisant la téléportation ?"; idsuiv=975; break;
        case 975 : texte = "Je dois tout de même te remercier. *Trouver ce temple relève de l'exploit. Ganondorf et moi-même avons passé des mois sans trouver un seul cristal."; idsuiv=976; break;
        case 976 : texte = "Et le jour où enfin, nous en pistions un facilement accessible, tu arrives et terrasses le puissant Ganondorf... *Je dois avouer que je ne m'y attendais pas..."; idsuiv=977; break;
        case 977 : texte = "Toutefois, il semblait évident que nous poursuivions le même objectif, et que tu avais une bonne avance."; idsuiv=978; break;
        case 978 : texte = "Nous avons alors décidé de te laisser trouver le temple pour nous."; idsuiv=979; break;
        case 979 : texte = "Tu t'es bien amusé pendant tout ce temps, mais maintenant c'est notre tour."; idsuiv=980; break;
        case 980 : texte = "Je crois qu'il est grand temps pour toi de disparaître."; break;
        case 981 : texte = "Comment ??? *Tu n'as pas pu vaincre Agahnim ???"; idsuiv=982; break;
        case 982 : texte = "... *Tout n'est pas perdu, il me reste un espoir..."; break;
        case 983 : texte = "Soit le bienvenu Link. *Nous sommes Din, Nayru et Farore, les Déesses fondatrices d'Hyrule."; idsuiv=984; break;
        case 984 : texte = "Tes efforts pour sauver Hyrule t'ont finalement mené jusqu'à nous."; idsuiv=985; break;
        case 985 : texte = "Comme tu l'as peut-être déjà compris, tu ne peux changer le passé. Toutes tes actions n'ont eu pour effet que de mettre en place le présent d'où tu viens."; idsuiv=986; break;
        case 986 : texte = "Ganondorf est venu dans notre temple pour suivre son mentor, et a finalement utilisé la Triforce pour le ramener à la vie."; idsuiv=987; break;
        case 987 : texte = "Il a souhaité obtenir le pouvoir de voyager à sa guise entre le monde des vivants et des morts, mais seuls les démons les plus puissants en sont capables."; idsuiv=988; break;
        case 988 : texte = "Grâce à ses nouveaux pouvoirs, Ganon a pu ramener Agahnim à la vie, mais sa nouvelle nature a pris le dessus sur sa raison."; idsuiv=989; break;
        case 989 : texte = "Il a transformé Agahnim en zombi à sa solde, s'est proclamé seigneur du malin puis est parti conquérir Hyrule."; idsuiv=990; break;
        case 990 : texte = "Le chef du village central a organisé la défense d'Hyrule après s'être proclamé roi. *Il fit forger Excalibur et fit travailler ensemble chevaliers et sages."; idsuiv=991; break;
        case 991 : texte = "Les chevaliers Hyliens furent décimés, mais leur chef, muni d'Excalibur, repoussa Ganon le temps que les sages le scellent à jamais."; idsuiv=992; break;
        case 992 : texte = "Mais tu connais la suite de l'histoire. Utilisant Agahnim, Ganon élimina les descendants des sages et brisa le seau le retenant prisonnier."; idsuiv=993; break;
        case 993 : texte = "Armé d'Excalibur, tu repoussas à plusieurs reprises ses assauts, mais le monde des morts ne suffit pas à le retenir."; idsuiv=994; break;
        case 994 : texte = "Ganon a trouvé la Triforce, mais ce n'est pas le seul trésor que renferme ce temple..."; idsuiv=995; break;
        case 995 : texte = "La Triforce offrant un pouvoir pratiquement illimité à son détenteur, nous lui avons créé un anti Triforce."; idsuiv=996; break;
        case 996 : texte = "Il s'agit de 3 armes d'une puissance exceptionnelle. Si deux d'entre elles s'unissent contre le porteur de la Triforce, elles annuleront son voeu."; idsuiv=997; break;
        case 997 : texte = "L'Epée du Courage te revient de droit. Nous te confions également l'Arc de la Sagesse pour que tu le donnes à la seule personne qui pourra le manier."; idsuiv=998; break;
        case 998 : texte = "Quant au Trident de la Force, nous l'envoyons au dernier élu."; break;
        case 999 : texte = "Tu obtiens l'Epée du Courage !!! *Cette arme de légende dégage une énorme puissance."; break;
        case 1000: texte = "Tu obtiens l'Arc de la Sagesse !!! *Un pouvoir étrange t'empêche de l'utiliser..."; break;
        case 1001: texte = "Le temps est venu Link, nous te renvoyons à ton époque."; break;
        case 1002: texte = "Link! C'est Zelda! Je te parle par télépathie, t'étais injoignable!"; idsuiv=1003; break;
        case 1003: texte = "Ganon est de retour! Il a attaqué le château! *Les gardes ont été changés en monstres sous son contrôle, soit prudent!"; break;
        case 1004: 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_PALAIS) {id=1010; chercheText();break;}
            texte = "La salle du trône est plus au Nord."; break;
        case 1005: 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_ZELDA_PALAIS) {id=1010; chercheText();break;}
            if (gpJeu->getJoueur()->getRubisMax()) {id=1013; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_PALAIS) {id=1007; chercheText();break;}
            texte = "La Princesse n'est pas encore prête à te recevoir."; idsuiv=1006; break; 
        case 1006: texte = "Elle m'a cependant chargé de te dire que des objets à ton intention ont été entreposés dans la réserve."; break;
        case 1007: texte = "La Princesse sera bientôt prête à te recevoir."; break;
        case 1008:
            if (gpJeu->getJoueur()->getRubisMax()) {id=1010; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()<PARLE_GARDE_PALAIS) {id=1004; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_RESERVE) {id=1009; chercheText();break;}
            texte = "Tu as reçu l'autorisation de te rendre à la réserve ? *Très bien, tu peux passer."; break;
        case 1009: texte = "La réserve est plus à l'Est"; break;
        case 1010: texte = "Le château est sous contrôle."; break;
        case 1011: texte = "Tu as trouvé un bouclier !*Ta défense augmente d'un point!"; break;
        case 1012: texte = "Tu as obtenu une bourse pouvant contenir 99 Rubis !"; break;
        case 1013: texte = "La Princesse Zelda t'attend."; break;
        case 1014: texte = "Bonjour Link."; break;
        case 1015: texte = "Euh, Link! *Je suis là!*Ouhou!"; break;
        case 1016: 
            if (gpJeu->getJoueur()->getAvancement()>=PASSAGE_TROUVE) {id=1031; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=ZELDA_SOUS_SOL) {id=1025; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_ZELDA_PALAIS) {id=1019; chercheText();break;}
            texte = "Une chose horrible s'est produite cette nuit, Link..."; idsuiv=1017; break;
        case 1017: texte = "L'Ocarina du Temps que tu as ramené de Termina... *Je le gardais dans une chambre forte du château, mais il vient d'être volé!"; idsuiv=1018; break;
        case 1018: texte = "J'ai fait placer des gardes dans tout Hyrule, le voleur n'a pas pu aller bien loin..."; idsuiv=1019; break;
        case 1019: texte = "J'aimerai que tu te charges de retrouver l'Ocarina. Commence ton enquête par la chambre forte du sous-sol où il se trouvait, je t'y rejoins."; break;
        case 1020: 
            if (gpJeu->getJoueur()->getAvancement()<PARLE_ZELDA_PALAIS) {id=1004; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_CH_FORTE) {id=1010; chercheText();break;}
            texte = "Les chambres fortes sont par ici."; break;
        case 1021: texte = "L'accès à cette chambre forte est strictement interdit."; break;
        case 1022: 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_SOUS_SOL) {id=1023; chercheText();break;}
            texte = "La Princesse vous a chargé d'enquêter sur le vol de l'Ocarina ? *Dans ce cas vous pouvez entrer, il n'y a de toute façon plus rien à garder ici..."; break;
        case 1023: texte = "Je suis resté à garder cette porte toute la nuit. Je suis certain que personne n'a franchi cette porte..."; break;
        case 1024: texte = "C'est ici qu'était gardé l'Ocarina. Le garde a entendu un grand bruit. Le temps qu'il réalise que cela venait de la chambre forte, le coffre avait été vidé."; idsuiv=1025; break;
#ifdef __PSP2__
        case 1025: texte = "Si tu vois quelque chose de louche, mets-toi devant et appuie sur Rond pour me le signaler."; break;
#else
        case 1025: texte = "Si tu vois quelque chose de louche, mets-toi devant et appuie sur ESPACE pour me le signaler."; break;
#endif
        case 1026: texte = "C'est une torche... Tu aurais préféré un lustre au plafond ?"; break;
        case 1027: texte = "Ce coffre contenait l'Ocarina du Temps hier soir encore..."; break;
        case 1028: 
            if (gpJeu->getJoueur()->getAvancement()>=RIDEAUX_REPERES) {id=1030; chercheText();break;}
            texte = "Cette pièce donnait sur les égouts... *Avant de la changer en chambre forte j'ai fait condamner le passage. Les rideaux cachent que cela a été mal fait..."; break;
        case 1029: texte = "C'est euh... un canard de bain. *Ne me demande pas ce que cela peut bien faire ici..."; break;
        case 1030: texte = "Ces rideaux ont l'air de t'intriguer... *Vérifions s'il n'y a rien derrière..."; break;
        case 1031: texte = "Voilà par où a dû passer le voleur! *Qu'attends-tu ? Pars à sa poursuite!"; break;
        case 1032: texte = "J'ai l'impression qu'on m'a oublié... *Voilà que je garde une chambre forte vide et grande ouverte..."; break;
        case 1033: texte = "Le voleur doit être dans cette forêt, tu ne peux pas abandonner maintenant!"; break;
#ifdef __PSP2__
        case 1034: texte = "TUTORIEL : Appuyez sur Croix près d'un objet léger tel qu'un pot pour le soulever. Appuyez une seconde fois pour le lancer."; break;
        case 1035: texte = "TUTORIEL : Appuyez sur Rond près d'un coffre pour l'ouvrir. Un coffre ne s'ouvre que par le bas."; break;
#else
        case 1034: texte = "TUTORIEL : Appuyez sur C près d'un objet léger tel qu'un pot pour le soulever. Appuyez une seconde fois pour le lancer."; break;
        case 1035: texte = "TUTORIEL : Appuyez sur Espace près d'un coffre pour l'ouvrir. Un coffre ne s'ouvre que par le bas."; break;
#endif
        case 1036: texte = "                Château d'Hyrule"; break;
        case 1037: texte = "Ce passage mène aux cachots, tu n'as rien à y faire."; break;
        case 1038: texte = "Ce passage mène à une zone sous très haute sécurité. Même le héros d'Hyrule n'est pas autorisé à y pénétrer."; break;
        case 1039: texte = "Euh... Comment es-tu arrivé là ?"; break;
        case 1040: texte = "Ces escaliers mènent aux chambres fortes."; break;
        case 1041: texte = "La salle du trône est derrière cette porte."; break;
        case 1042: texte = "La salle du trône s'appelle la salle du trône parce qu'elle ne comporte plus qu'un seul trône..."; break;
        case 1043: texte = "La porte de gauche mène à la salle de bal et aux quartiers VIP, alors que la porte du haut mène à la salle à manger et aux cuisines."; break;
        case 1044: texte = "Autrefois je jouais du piano debout, mais avec les années j'ai décidé de me poser."; break;
        case 1045: texte = "Je suis ici comme musicienne, mais les soirs de bal je préfère lâcher la harpe et aller danser."; break;
        case 1046: texte = "J'ai entendu dire qu'un voleur amateur d'instruments de musique est venu au château durant la nuit."; idsuiv=1047; break;
        case 1047: texte = "Heureusement il n'a pas dû voir mon violon."; break;
        case 1048: texte = "Un petit remontant ?**              OUI ?            non  "; break;
        case 1049: texte = "Un petit remontant ?**              oui              NON ?"; break;
        case 1050: texte = "Cuistot au château, c'est pas une sinécure..."; break;
        case 1051: texte = "On dit que les meilleurs cuistots peuvent lire tout en préparant leurs plats. Pour ma part j'y arrive à moitié."; break;
        case 1052: texte = "Je ne sais jamais quoi préparer, il faut que je me dépêche de trouver une idée!"; break;
        case 1053: texte = "Serveuse au château, c'est plutôt un bon job, tranquille et bien payé."; break;
        case 1054: texte = "L'aile Ouest du château est réservée aux VIPs. Et euh... je n'ai pas eu de consignes à ton sujet... un oubli sans doute."; break;
        case 1055: texte = "L'aile Est du château est réservée aux gardes. Désolé mais tu n'as rien à y faire."; break;
        case 1056: texte = "Cette porte mène à la réserve."; break;
        case 1057: texte = "La bibliothèque est un lieu... plutôt calme."; break;
        case 1058: texte = "Tu as obtenu une source d'énergie!*...*C'est pas si mal..."; break;
        case 1059: 
            if (gpJeu->getJoueur()->getAvancement()>=MOT_DE_PASSE_DONNE) {id=1062; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==MOT_DE_PASSE_CONNU) {id=1061; chercheText();break;}
            texte = "L'accès à la salle du trône n'est accordé qu'aux personnes autorisées."; break;
        case 1060: 
            if (gpJeu->getJoueur()->getAvancement()>=MULTIPASSE_UTILISE) {id=1062; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=MULTIPASS) {id=1063; chercheText();break;}
            texte = "L'accès à cette partie du château n'est accordé qu'au personnel de rénovation."; break;
        case 1061: texte = "Tu connais la phrase secrète ?*Je me doutais bien que sous tes airs de lapinet tout gentil se cachait un terrible soldat d'élite de Ganon."; break;
        case 1062: texte = "Tu peux passer."; break;
        case 1063: texte = "Tu as obtenu l'autorisation de t'aventurer dans tout le château ??? *Et bien passe dans ce cas..."; break;
        case 1064: 
            if (gpJeu->getJoueur()->getAvancement()>=MOT_DE_PASSE_CONNU) {id=1070; chercheText();break;}
            texte = "Tu es venu me libérer ? *Je n'avais pas besoin d'aide..."; idsuiv=1065; break;
        case 1065: texte = "Je voulais m'emparer de ce château par la force... Je suis donc entré pour défier Ganon."; idsuiv=1066; break;
        case 1066: texte = "Le combat fut long et difficile... *Mais les gardes de la salle du trône ont finalement réussi à m'arrêter..."; idsuiv=1067; break;
        case 1067: texte = "Quelle poisse, j'aurai bien voulu rencontrer Ganon..."; idsuiv=1068; break;
        case 1068: texte = "Depuis j'ai entendu dire qu'il y avait une phrase secrète à donner aux gardes pour passer. Il faut leur dire ça :"; idsuiv=1069; break;
        case 1069: texte = "Désolé, mais la princesse n'est pas dans ce château!"; idsuiv=1070; break;
        case 1070: texte = "La prochaine fois j'y arriverai."; break;
        case 1071: texte = "!!!*Mais tu es..."; idsuiv=1072; break;
        case 1072: 
            gpJeu->getAudio()->stopSpecial();
            texte = "Un petit lapin rose ! *J'aime le rose !"; idsuiv=1073; break;
        case 1073: texte = "Fais comme chez toi petit lapin rose, je t'autorise à te promener à ta guise dans ce château."; break;
        case 1074: 
            if (gpJeu->getJoueur()->isLapin()) {id=1073; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>6) {id=1078; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==6 
            && gpJeu->getJoueur()->getObjet()==15) {id=1075; chercheText();break;}
            texte = "Tu m'es vaguement familier... *Enfin peu importe, tu saurais pas où je peux trouver une bonne bière ?"; break;
        case 1075: texte = "C'est une bière que tu as là ?*Je te la pique, j'imagine que t'es là pour ça de toute façon."; idsuiv=1076; break;
        case 1076: texte = "Tiens, t'as qu'à prendre ça comme récompense."; break;
        case 1077: texte = "Tu as troqué la bière contre des clous..."; break;
        case 1078: texte = "Je crois que je t'aime bien, t'es un bon gars. *Tu vas me chercher une autre bière ?"; break;
        case 1079: texte = "Une partition est gravée. Si tu avais un instrument de musique tu pourrais essayer de la jouer."; break;
        case 1080: texte = "Tu as... euh... volé l'ocarina ??? *On va dire que c'est pour la bonne cause..."; break;
        case 1081: texte = "A la seconde où il joua l'air à l'ocarina, Link fut ramené à son époque. Il courut alors au palais pour raconter son histoire à la Princesse..."; break;
        case 1082: texte = "Quelle terrible histoire... *Le Royaume d'Hyrule est-il vraiment destiné à tomber aux mains de Ganon ?"; idsuiv=1083; break;
        case 1083: 
            if (gpJeu->getJoueur()->getEpee()==5 && gpJeu->getJoueur()->hasObjet(O_ARC_OR) < 2) {id=1092; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==4 
            && gpJeu->getJoueur()->getObjet()==11) {id=1085; chercheText();break;}
            if (gpJeu->getJoueur()->getEpee()==5 && gpJeu->getJoueur()->getEnnemi(50)) {id=1112; chercheText();break;}
            if (gpJeu->getJoueur()->getEpee()==5) {id=1095; chercheText();break;}
            texte = "Que pouvons-nous faire ? *Si seulement Ganon n'avait jamais trouvé la Triforce..."; break;
        case 1084: texte = "L'Ocarina transporta Link une fois de plus. Le héros d'Hyrule se retrouva alors dans une vaste plaine enneigée..."; break;
        case 1085: texte = "Ce miroir est pour moi ?**              OUI ?            non  "; idsuiv=1087; break;
        case 1086: texte = "Ce miroir est pour moi ?**              oui              NON ?"; idsuiv=1088; break;
        case 1087: texte = "... Tu m'offres un miroir ??? Tu me prends donc pour ce genre de filles qui passent leur temps à se regarder ???"; 
            buffer = "Bon prends quand même ça en remerciement."; break;
        case 1088: texte = "...*Va-t-en vite si tu ne veux pas finir au cachot."; break;
        case 1089: texte = "Tu as troqué le miroir contre une petite cuillère !"; break;
        case 1090: texte = "Tu es dans une zone sous haute sécurité, je vais te demander de partir."; break;
        case 1091: texte = "Tu as trouvé une tunique extrêmement résistante!!!*Ta défense augmente d'un point !"; break;
        case 1092: texte = "Contente de te voir enfin Link!"; idsuiv=1093; break;
        case 1093: texte = "Tu dis que cet arc est pour moi et qu'il peut vaincre Ganon ?*Cool!"; break;
        case 1094: texte = "Tu as remis l'Arc de la Sagesse à la Princesse Zelda."; break;
        case 1095: texte = "Ne t'en fais pas pour moi, je devrais pouvoir me débrouiller désormais."; idsuiv=1096; break;
        case 1096: texte = "Nous devons affronter Ganon, pars devant je te rejoins.*Je dois me repoudrer le nez avant."; break;
        case 1097: texte = "!!! *Ganon a repris forme humaine! *Ce n'est plus un démon il ne pourra plus revenir à la vie, nous avons gagné!"; break;
        case 1098: texte = "???"; break;
        case 1099: texte = "Te voilà enfin Link. *Cette fois la victoire sera mienne, j'ai amélioré mes techniques spécialement pour te vaincre."; break;
        case 1100: texte = "Nous revoilà face à face Link. *J'ai l'impression de sortir d'un long cauchemar..."; idsuiv=1101; break;
        case 1101: texte = "Agahnim avait tort, la Triforce n'aurait jamais dû être trouvée."; idsuiv=1102; break;
        case 1102: texte = "Ecoute-moi bien Link, il y a désormais bien longtemps, Agahnim disparut après avoir quitté l'ordre de sages."; idsuiv=1103; break;
        case 1103: texte = "Le jour où il reparut, il était doté de sombres pouvoirs. En tant que sage, il n'aurait jamais été capable de lancer des boules de feu, sa spécialité c'était les lapins..."; idsuiv=1104; break;
        case 1104: texte = "Je devais trop à Agahnim pour m'opposer à lui, cependant j'ai mené mon enquête tandis que nous cherchions les cristaux magiques."; idsuiv=1105; break;
        case 1105: texte = "Il semblerait qu'il ait obtenu ses pouvoirs d'une entité beaucoup plus dangereuse et puissante que je n'ai jamais pu l'être."; idsuiv=1106; break;
        case 1106: texte = "Il reste en Hyrule des lieux que tu n'as pas explorés et des ennemis que tu n'as pas vaincus. Ta quête n'est peut-être pas encore finie..."; idsuiv=1107; break;
        case 1107: texte = "Tu veux savoir pourquoi je te dis tout ça ? *J'imagine que je ne vais pas pouvoir m'en sortir si facilement après tout ce que j'ai fait..."; idsuiv=1108; break;
        case 1108: texte = "Si j'échoue aujourd'hui, quelqu'un devra venger Agahnim à ma place. *Mais..."; idsuiv=1109; break;
        case 1109: texte = "... en seras-tu capable ?"; break;
        case 1110: texte = "Tu as trouvé la Triforce !!!"; break;
        case 1111: texte = "C'est ainsi que Ganon fut vaincu à jamais. La Triforce fut une nouvelle fois récupérée puis gardée à l'abri au palais. **Cependant, inquiété par les dernières paroles de Ganondorf, Link passa le restant de ses jours à veiller sur Hyrule. ***Fin de la première quête."; break;
        case 1112: texte = "Ganon a repris forme humaine... *est-il toujours notre ennemi ?"; break;
        case 1113: texte = "Prêt pour un dernier duel ?"; break;
        case 1114: 
            if (gpJeu->getMonde()->motifValue(69*16,90*16) == 6380) {texte = "Bienvenue au Casino !"; break;}
            texte = "Bienvenue cher visiteur, les droits d'entrées sont de 10 Ganon d'or, ça te va ?*              OUI ?            non  "; idsuiv=1117; break;
        case 1115: texte = "Bienvenue cher visiteur, les droits d'entrées sont de 10 Ganon d'or, ça te va ?*              oui              NON ?"; idsuiv=1116; break;
        case 1116: texte = "Tant pis."; break;
        case 1117: 
            if (gpJeu->getMonde()->motifValue(69*16,90*16) != 6380 &&
            gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10) {id=1118; chercheText();break;}
            texte = "Bienvenue au Casino !"; break;
        case 1118: texte = "Reviens quand tu auras de l'argent l'ami."; break;
        case 1119: texte = "Nous sommes fermés pour le moment, reviens plus tard."; break;
        case 1120: texte = "Bienvenue au casino familial, veux-tu que je t'explique les règles du jeu pour 5 Ganon d'or?              OUI ?            non  "; idsuiv=1122; break;
        case 1121: texte = "Bienvenue au casino familial, veux-tu que je t'explique les règles du jeu pour 5 Ganon d'or?              oui              NON ?"; idsuiv=1116; break;
        case 1122: 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<5) {id=1118; chercheText();break;}
            texte = "Dans ce casino, les ennemis ne t'enlèvent pas de coeurs mais de l'argent. Chaque attaque te fait perdre un peu plus que la précédente."; idsuiv=1123; break;
        case 1123: texte = "Si tu n'as plus d'argent, tu es mis à la porte. Les clients fauchés ne nous intéressent pas."; idsuiv=1124; break;
        case 1124: texte = "Cependant, en remportant les différents jeux proposés, tu pourras gagner des prix de grandes valeurs."; break;
        case 1125: 
            if (gpJeu->getJoueur()->getCoffre(12,1)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = "Frappe les ennemis pour les arrêter sur un signe. Obtient les 4 signes différents et tu gagneras un prix."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1126: texte = "Veux-tu essayer pour 10 Ganon d'or ?**              OUI ?            non  "; break;
        case 1127: texte = "Veux-tu essayer pour 10 Ganon d'or ?**              oui              NON ?"; idsuiv=1116; break;
        case 1128: texte = "Tu as déjà remporté ce jeu."; break;
        case 1129: texte = "Félicitation !*Voici ton prix :"; break;
        case 1130: texte = "Tu auras sans doute plus de chance la prochaine fois."; break;
        case 1131:
            if (gpJeu->getJoueur()->getCoffre(12,2)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1132; chercheText();break;}
            texte = "Frappe les ennemis pour les arrêter sur un chiffre. Obtiens un 4, un 2 et un 1 et tu gagneras un prix."; 
            buffer="Parle-moi si tu échoues, tu pourras recommencer en conservant les bons chiffres obtenus."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1132: texte = "Veux-tu compléter pour 5 Ganon d'or ?**              OUI ?            non  "; break;
        case 1133: texte = "Veux-tu compléter pour 5 Ganon d'or ?**              oui              NON ?"; idsuiv=1116; break;
        case 1134:
            if (gpJeu->getJoueur()->getCoffre(12,5)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->isTempsVisible()) {id=1135; chercheText();break;}
            texte = "C'est la ligne de départ de la grande course du Casino, tu as 21 secondes pour atteindre l'arrivée."; 
            idsuiv=1126; break;
        case 1135: texte = "Tu perds du temps là, tu sais ?"; break;
        case 1136:
            if (gpJeu->getJoueur()->getCoffre(12,5)) {id=1128; chercheText();break;}
            texte = "C'est la ligne d'arrivée de la grande course du Casino. Va à la ligne de départ si tu veux essayer de battre le record."; break;
        case 1137:
            if (gpJeu->getJoueur()->getCle(12,0)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = "Frappe les ennemis pour les arrêter sur un chiffre et fait plus que moi avec un dé en moins."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1138:
            if (gpJeu->getJoueur()->getCoffre(12,4)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = "Choisis un chiffre, soit 1, soit 6. Je vais lancer 4 dés, si ton chiffre y est c'est gagné, sinon tu paies 10 fois la différence avec le dé le plus proche."; 
            idsuiv=1139; break;
        case 1139: texte = "Veux-tu essayer ?**              OUI ?            non  "; idsuiv=1141; break;
        case 1140: texte = "Veux-tu essayer ?**              oui              NON ?"; idsuiv=1116; break;
        case 1141: texte = "Quel est ton chiffre ?**              UN  ?            six  "; break;
        case 1142: texte = "Quel est ton chiffre ?**              un               SIX ?"; break;
        case 1143:
            if (gpJeu->getJoueur()->getCle(12,1)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = "Frappe les ennemis pour les arrêter sur un chiffre qui sera transmis à une caisse de droite. Puis pousse les caisses pour qu'elles arrivent à 0 sur les dalles."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1144:
            if (gpJeu->getJoueur()->getCoffre(12,3)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) > 1) {id=1145; chercheText();break;}
            texte = "Je te vends une clé pour un prix égal à la somme de tes 4 dés fois le montant du miens."; 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1145:
            tmp = gpJeu->getJoueur()->getCoffre(12,13)-2; os << tmp;
            texte = "Je te vends une petite clé pour "+os.str()+" Ganon d'or, ça te va ?*              OUI ?            non  "; idsuiv=1129; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<tmp) {idsuiv=1118;break;}
            break;
        case 1146:
            tmp = gpJeu->getJoueur()->getCoffre(12,13)-2; os << tmp;
            texte = "Je te vends une petite clé pour "+os.str()+" Ganon d'or, ça te va ?*              oui              NON ?"; idsuiv=1116; break;
            break;
        case 1147:
            if (gpJeu->getJoueur()->getCle(12,2)) {id=1148; chercheText();break;}
            texte = "La salle du coffre est au bout du couloir à gauche. Seuls les meilleurs clients peuvent espérer l'atteindre.";
            break;
        case 1148: 
            if (gpJeu->getJoueur()->getCoeur(11)) {id=1149; chercheText();break;}
            texte = "Tu as ouvert le coffre ?*Tu devrais tenter la salle spéciale désormais."; break;
        case 1149: texte = "Les gens comme toi n'ont rien à faire dans un casino...*Nous sommes ruinés..."; break;
        case 1150: texte = "Bienvenue au Grand Quiz du Casino !"; idsuiv=1151; break;
        case 1151: texte = "Ici c'est moi qui pose les questions, et les mauvaises réponses coûtent chère."; idsuiv=1152; break;
        case 1152: 
            gpJeu->getJoueur()->setCoffre(12,14,0); // ->nb questions posées
            for (int i = 0; i < MAX_QUIZZ; i++) gpJeu->getJoueur()->setCoffre(12,15+i,0);
            tmp = rand()%MAX_QUIZZ; idsuiv = 1154 + tmp*4;
            gpJeu->getJoueur()->setCoffre(12,15+tmp,1);
            texte = "Je ne te demande pas si tu veux jouer, je suis tout de même un boss.*Alors commençons..."; 
            break;
        case 1153: 
            if ((MAX_QUIZZ-gpJeu->getJoueur()->getCoffre(12,14)) > 0) {
                tmp = rand()%(MAX_QUIZZ-gpJeu->getJoueur()->getCoffre(12,14));
                for (int i = 0; i <= tmp; i++) {
                    if (gpJeu->getJoueur()->getCoffre(12,15+i) > 0) {
                        tmp++;
                    }
                } 
                idsuiv=1154+tmp*4;
                gpJeu->getJoueur()->setCoffre(12,15+tmp,1);
            }
            texte = "Question suivante..."; break;
        case 1154: texte = "Ce Casino contenait un total de 6 jeux différents sans compter ce quiz, est-ce vrai ?              VRAI ?            faux  "; idsuiv=1157; break;
        case 1155: texte = "Ce Casino contenait un total de 6 jeux différents sans compter ce quiz, est-ce vrai ?              vrai              FAUX ?"; idsuiv=1156; break;
        case 1156: texte = "Correct! Il y avait 7 jeux, 1 pour la carte, 1 pour la boussole et 5 pour des clés."; break;
        case 1157: texte = "Non! Il y avait 7 jeux, 1 pour la carte, 1 pour la boussole et 5 pour des clés."; break;
        
        case 1158: texte = "Le gars de la maison du café ne boit jamais plus de 16 tasses de café par jour, vrai ?*             VRAI ?            faux  "; idsuiv=1161; break;
        case 1159: texte = "Le gars de la maison du café ne boit jamais plus de 16 tasses de café par jour, vrai ?*             vrai              FAUX ?"; idsuiv=1160; break;
        case 1160: texte = "Correct! Il peut atteindre les 17 tasses!"; break;
        case 1161: texte = "Non! Il peut atteindre les 17 tasses!"; break;
        
        case 1162: texte = "Ce jeu contient un total de 150 gemmes de forces, vrai ?*             VRAI ?            faux  "; idsuiv=1165; break;
        case 1163: texte = "Ce jeu contient un total de 150 gemmes de forces, vrai ?*             vrai              FAUX ?"; idsuiv=1164; break;
        case 1164: texte = "Correct! Il y en a 200."; break;
        case 1165: texte = "Non! Il y en a 200."; break;
        
        case 1166: texte = "Le village central ne contient plus que 7 maisons, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1168; break;
        case 1167: texte = "Le village central ne contient plus que 7 maisons, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1169; break;
        case 1168: texte = "Correct! Les 3 autres sont détruites."; break;
        case 1169: texte = "Non! Il y a 10 maisons dont 3 détruites, soit plus que 7."; break;

        case 1170: 
            tmp = gpJeu->getJoueur()->getMort() + 1; os << tmp;
            texte = "Tu es mort "+os.str()+" fois, est-ce vrai ?**             VRAI ?            faux  "; idsuiv=1173; break;
        case 1171: 
            tmp = gpJeu->getJoueur()->getMort() + 1; os << tmp;
            texte = "Tu es mort "+os.str()+" fois, est-ce vrai ?**             vrai              FAUX ?"; idsuiv=1172; break;
        case 1172: 
            tmp = gpJeu->getJoueur()->getMort(); os << tmp;
            texte = "Correct! Tu es mort "+os.str()+" fois."; break;
        case 1173: 
            tmp = gpJeu->getJoueur()->getMort(); os << tmp;
            texte = "Non! Tu es mort "+os.str()+" fois."; break;
            
        case 1174: texte = "14 mauvaises réponses suffisent obligatoirement à faire perdre n'importe quel joueur, vrai ?*             VRAI ?            faux  "; idsuiv=1176; break;
        case 1175: texte = "14 mauvaises réponses suffisent obligatoirement à faire perdre n'importe quel joueur, vrai ?*             vrai              FAUX ?"; idsuiv=1177; break;
        case 1176: texte = "Correct! 14 mauvaises réponses font perdre au minimum 1050 Ganon d'or sur les 999 transportables."; break;
        case 1177: texte = "Non! 14 mauvaises réponses font perdre au minimum 1050 Ganon d'or sur les 999 transportables."; break;
        
        case 1178: texte = "Je suis le boss le plus cool du jeu, vrai ?**             VRAI ?            faux  "; idsuiv=1180; break;
        case 1179: texte = "Je suis le boss le plus cool du jeu, vrai ?**             vrai              FAUX ?"; idsuiv=1181; break;
        case 1180: texte = "Hé! Hé! On est d'accord."; break;
        case 1181: texte = "... *Je vais te la compter fausse pour le principe..."; break;
        
        case 1182: texte = "Seuls 3 donjons du passé sont obligatoires pour finir le jeu, vrai ? *             VRAI ?            faux  "; idsuiv=1184; break;
        case 1183: texte = "Seuls 3 donjons du passé sont obligatoires pour finir le jeu, vrai ? *             vrai              FAUX ?"; idsuiv=1185; break;
        case 1184: texte = "Correct! Le temple de l'air, le temple du feu et celui des déesses."; break;
        case 1185: texte = "Non! Il n'y en a bien que 3, Le temple de l'air, le temple du feu et celui des Déesses."; break;
        
        case 1186: texte = "Plus de 4000 Ganon d'or sont nécessaires pour obtenir tous les prix de la grosse fée, vrai ?              VRAI ?            faux  "; idsuiv=1189; break;
        case 1187: texte = "Plus de 4000 Ganon d'or sont nécessaires pour obtenir tous les prix de la grosse fée, vrai ?              vrai              FAUX ?"; idsuiv=1188; break;
        case 1188: texte = "Correct! Il n'en faut que 3798."; break;
        case 1189: texte = "Non! 3798 suffisent."; break;
        
        case 1190: texte = "Du temps de Zelda, le palais contenait 80 piliers, vrai ?*             VRAI ?            faux  "; idsuiv=1192; break;
        case 1191: texte = "Du temps de Zelda, le palais contenait 80 piliers, vrai ?*             vrai              FAUX ?"; idsuiv=1193; break;
        case 1192: texte = "Correct! Il y en avait bien 80."; break;
        case 1193: texte = "Non! Il y en avait bien 80."; break;
        
        case 1194: 
            tmp = gpJeu->getJoueur()->getCoffre(12,14) + 1; os << tmp;
            texte = "Tu as déjà répondu à "+os.str()+" de mes questions, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1197; break;
        case 1195: 
            tmp = gpJeu->getJoueur()->getCoffre(12,14) + 1; os << tmp;
            texte = "Tu as déjà répondu à "+os.str()+" de mes questions, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1196; break;
        case 1196: texte = "Correct! Mais maintenant oui."; break;
        case 1197: texte = "Non! Mais maintenant oui."; break;
        
        case 1198: texte = "Tu peux trouver un maximum de 16 quarts de coeurs dans ce jeu, vrai ?*             VRAI ?            faux  "; idsuiv=1200; break;
        case 1199: texte = "Tu peux trouver un maximum de 16 quarts de coeurs dans ce jeu, vrai ?*             vrai              FAUX ?"; idsuiv=1201; break;
        case 1200: texte = "Correct! Il y en a 16 en tout."; break;
        case 1201: texte = "Non! Il y en a 16 en tout."; break;
        
        case 1202: texte = "Une potion bleue coûte l'équivalent de 40 Rubis plus 40 Ganon d'or plus 10 pièces d'or, vrai ?*             VRAI ?            faux  "; idsuiv=1204; break;
        case 1203: texte = "Une potion bleue coûte l'équivalent de 40 Rubis plus 40 Ganon d'or plus 10 pièces d'or, vrai ?*             vrai              FAUX ?"; idsuiv=1205; break;
        case 1204: texte = "Correct! Soit 160 Rubis."; break;
        case 1205: texte = "Non! Cela donne 160 Rubis, soit le prix d'une potion bleue."; break;
        
        case 1206: texte = "Dans la mine, les rails du wagonnet pouvaient se changer à l'aide de 3 leviers, vrai ?*             VRAI ?            faux  "; idsuiv=1209; break;
        case 1207: texte = "Dans la mine, les rails du wagonnet pouvaient se changer à l'aide de 3 leviers, vrai ?*             vrai              FAUX ?"; idsuiv=1208; break;
        case 1208: texte = "Correct! Il n'y en avait que 2."; break;
        case 1209: texte = "Non! Il n'y en avait que 2."; break;
        
        case 1210: texte = "Il fallait trouver 3 poissons différents pour gagner le concours de pêche, vrai ?*             VRAI ?            faux  "; idsuiv=1213; break;
        case 1211: texte = "Il fallait trouver 3 poissons différents pour gagner le concours de pêche, vrai ?*             vrai              FAUX ?"; idsuiv=1212; break;
        case 1212: texte = "Correct! Il en fallait 5."; break;
        case 1213: texte = "Non! Il en fallait 5."; break;
        
        case 1214: texte = "Seule Excalibur permet de renvoyer les projectiles, vrai ?*             VRAI ?            faux  "; idsuiv=1217; break;
        case 1215: texte = "Seule Excalibur permet de renvoyer les projectiles, vrai ?*             vrai              FAUX ?"; idsuiv=1216; break;
        case 1216: texte = "Correct! Ton épée actuelle en est également capable."; break;
        case 1217: texte = "Non! Ton épée actuelle en est également capable."; break;
        
        case 1218: texte = "Zelda est plus grande que toi, est-ce vrai ?**             VRAI ?            faux  "; idsuiv=1221; break;
        case 1219: texte = "Zelda est plus grande que toi, est-ce vrai ?**             vrai              FAUX ?"; idsuiv=1220; break;
        case 1220: texte = "Correct! Tu fais un pixel de plus."; break;
        case 1221: texte = "Non! Tu fais un pixel de plus."; break;
        
        case 1222: texte = "Le donjon 3 contient 3 étages, est-ce vrai ?**             VRAI ?            faux  "; idsuiv=1224; break;
        case 1223: texte = "Le donjon 3 contient 3 étages, est-ce vrai ?**             vrai              FAUX ?"; idsuiv=1225; break;
        case 1224: texte = "Correct! Dont un juste pour le boss."; break;
        case 1225: texte = "Non! 2 étages plus 1 pour le boss, donc 3."; break;
        
        case 1226: texte = "L'incarnation démoniaque de Link est un lapin rose, vrai ?*             VRAI ?            faux  "; idsuiv=1229; break;
        case 1227: texte = "L'incarnation démoniaque de Link est un lapin rose, vrai ?*             vrai              FAUX ?"; idsuiv=1228; break;
        case 1228: texte = "Correct! C'est Oni Link."; break;
        case 1229: texte = "Non! C'est Oni Link."; break;
        
        case 1230: texte = "Tingle n'aurait jamais dû exister, vrai ?**             VRAI ?            faux  "; idsuiv=1232; break;
        case 1231: texte = "Tingle n'aurait jamais dû exister, vrai ?**             vrai              FAUX ?"; idsuiv=1233; break;
        case 1232: texte = "Euh... on s'égare là, mais je vais te la compter juste."; break;
        case 1233: texte = "... *Pour moi si."; break;
        
        case 1234: texte = "Tu veux me donner des Ganon d'or, vrai ?**             VRAI ?            faux  "; idsuiv=1237; break;
        case 1235: texte = "Tu veux me donner des Ganon d'or, vrai ?**             vrai              FAUX ?"; idsuiv=1236; break;
        case 1236: texte = "Correct! Hélas..."; break;
        case 1237: texte = "Merci!"; break;
        
        case 1238: texte = "Les morsures de serpent laissent un demi-coeur peu importe la vie et la défense que tu avais, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1241; break;
        case 1239: texte = "Les morsures de serpent laissent un demi-coeur peu importe la vie et la défense que tu avais, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1240; break;
        case 1240: texte = "Correct! Si tu n'as plus qu'un demi-coeur la morsure ne t'en laisse aucun."; break;
        case 1241: texte = "Non! Si tu n'as plus qu'un demi-coeur la morsure ne t'en laisse aucun."; break;
        
        case 1242: texte = "Le domaine de Link contient 77 touffes d'herbes, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1244; break;
        case 1243: texte = "Le domaine de Link contient 77 touffes d'herbes, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1245; break;
        case 1244: texte = "Correct! Ravi de constater que je ne suis pas le seul à avoir compté!"; break;
        case 1245: texte = "Non! Tu te rends compte que je connais mieux ton domaine que toi ???"; break;
        
        case 1246: texte = "2 à la puissance 12 est plus petit que la racine cubique de 7, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1249; break;
        case 1247: texte = "2 à la puissance 12 est plus petit que la racine cubique de 7, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1248; break;
        case 1248: texte = "Correct! Enfin je crois."; break;
        case 1249: texte = "Non! Ca doit être l'inverse je crois."; break;
        
        case 1250: texte = "Il est possible de finir le jeu en se déplaçant uniquement en moonwalk, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1253; break;
        case 1251: texte = "Il est possible de finir le jeu en se déplaçant uniquement en moonwalk, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1252; break;
        case 1252: texte = "Correct! Enfin ça ne t'empêche pas d'essayer."; break;
        case 1253: texte = "Non! Enfin tu peux toujours essayer..."; break;
        
        case 1254: texte = "C'est dans le passé que tu peux gagner le plus d'argent en battant un ennemi, vrai ?*             VRAI ?            faux  "; idsuiv=1257; break;
        case 1255: texte = "C'est dans le passé que tu peux gagner le plus d'argent en battant un ennemi, vrai ?*             vrai              FAUX ?"; idsuiv=1256; break;
        case 1256: texte = "Correct! C'est dans le présent avec les Rubis rouges."; break;
        case 1257: texte = "Non! C'est dans le présent avec les Rubis rouges."; break;
        
        case 1258: texte = "Ton épée peut vaincre n'importe quel ennemi hors boss en moins de 6 coups, vrai ?*             VRAI ?            faux  "; idsuiv=1261; break;
        case 1259: texte = "Ton épée peut vaincre n'importe quel ennemi hors boss en moins de 6 coups, vrai ?*             vrai              FAUX ?"; idsuiv=1260; break;
        case 1260: texte = "Correct! Certains ennemis ne craignent pas les coups d'épée."; break;
        case 1261: texte = "Non! Certains ennemis ne craignent pas les coups d'épée."; break;
        
        case 1262: texte = "L'énigme du désert comptait 6 pierres, vrai ?**             VRAI ?            faux  "; idsuiv=1264; break;
        case 1263: texte = "L'énigme du désert comptait 6 pierres, vrai ?**             vrai              FAUX ?"; idsuiv=1265; break;
        case 1264: texte = "Correct! Par contre je n'ai jamais trouvé l'ordre..."; break;
        case 1265: texte = "Non! T'as sans doute triché pour la résoudre..."; break;
        
        case 1266: 
            tmp = gpJeu->getJoueur()->getTemps(2); os << tmp;
            texte = "Tu en es à plus de "+os.str()+" heures de jeu, vrai ?**             VRAI ?            faux  "; idsuiv=1268; break;
        case 1267: 
            tmp = gpJeu->getJoueur()->getTemps(2); os << tmp;
            texte = "Tu en es à plus de "+os.str()+" heures de jeu, vrai ?**             vrai              FAUX ?"; idsuiv=1269; break;
        case 1268: texte = "Correct! Ca passe vite hein ?"; break;
        case 1269: texte = "Non! Ca passe vite hein ?"; break;
        
        case 1270: texte = "Les poules du passé sont plus patientes que celles du présent, vrai ?*             VRAI ?            faux  "; idsuiv=1273; break;
        case 1271: texte = "Les poules du passé sont plus patientes que celles du présent, vrai ?*             vrai              FAUX ?"; idsuiv=1272; break;
        case 1272: texte = "Correct! Je vois que tu es connaisseur."; break;
        case 1273: texte = "Non! T'auras qu'à vérifier..."; break;
        
        case 1274: texte = "Il était possible de pêcher 4 poissons différents au Lac Hylia, vrai ?*             VRAI ?            faux  "; idsuiv=1276; break;
        case 1275: texte = "Il était possible de pêcher 4 poissons différents au Lac Hylia, vrai ?*             vrai              FAUX ?"; idsuiv=1277; break;
        case 1276: texte = "Correct! Il y en avait 6 espèces différentes."; break;
        case 1277: texte = "Non! Il y en avait 6 espèces différentes, il était donc possible d'en trouver 4."; break;
        
        case 1278: texte = "Le Père Noël existe, est-ce vrai ?**             VRAI ?            faux  "; idsuiv=1280; break;
        case 1279: texte = "Le Père Noël existe, est-ce vrai ?**             vrai              FAUX ?"; idsuiv=1281; break;
        case 1280: texte = "Correct! Tu l'as d'ailleurs déjà rencontré."; break;
        case 1281: texte = "Non! Tu l'as d'ailleurs déjà rencontré."; break;
        
        case 1282: texte = "Les montagnes du passé contenaient 16 pierres, vrai ?*             VRAI ?            faux  "; idsuiv=1285; break;
        case 1283: texte = "Les montagnes du passé contenaient 16 pierres, vrai ?*             vrai              FAUX ?"; idsuiv=1284; break;
        case 1284: texte = "Correct! Il n'y en avait que 15 bien sûr."; break;
        case 1285: texte = "Non! Il n'y en avait que 15 bien sûr."; break;
        
        case 1286: texte = "Ce Casino contient un total de 42 tapis, vrai ? *             VRAI ?            faux  "; idsuiv=1289; break;
        case 1287: texte = "Ce Casino contient un total de 42 tapis, vrai ? *             vrai              FAUX ?"; idsuiv=1288; break;
        case 1288: texte = "Correct! Il y en a 44."; break;
        case 1289: texte = "Non! Il y en a 44."; break;
        
        case 1290: texte = "Les Gemmes de Force peuvent se troquer contre 5 sortes d'objets différentes, vrai ?*             VRAI ?            faux  "; idsuiv=1292; break;
        case 1291: texte = "Les Gemmes de Force peuvent se troquer contre 5 sortes d'objets différentes, vrai ?*             vrai              FAUX ?"; idsuiv=1293; break;
        case 1292: texte = "Correct! Je vois que tu n'as pas oublié le roc givre."; break;
        case 1293: texte = "Non! Tu as dû oublier le roc givre dans tes comptes."; break;
        
        case 1294: texte = "La tunique verte ne donne qu'un point de défense, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1297; break;
        case 1295: texte = "La tunique verte ne donne qu'un point de défense, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1296; break;
        case 1296: texte = "Correct! La tunique verte est celle de base et ne donne aucun point de défense."; break;
        case 1297: texte = "Non! La tunique verte est celle de base et ne donne aucun point de défense."; break;
        
        case 1298: texte = "La chambre de Zelda contenait 5 miroirs, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1300; break;
        case 1299: texte = "La chambre de Zelda contenait 5 miroirs, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1301; break;
        case 1300: texte = "Correct! Le cinquième lui vient d'ailleurs de toi."; break;
        case 1301: texte = "Non! Le cinquième lui vient d'ailleurs de toi."; break;
        
        case 1302: texte = "La Pyramide du passé contenait 85 salles, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1305; break;
        case 1303: texte = "La Pyramide du passé contenait 85 salles, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1304; break;
        case 1304: texte = "Correct! 84 seulement."; break;
        case 1305: texte = "Non! 84 seulement."; break;
        
        case 1306: texte = "Les flèches de feu sont plus fortes que celles de glace, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1308; break;
        case 1307: texte = "Les flèches de feu sont plus fortes que celles de glace, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1309; break;
        case 1308: texte = "Correct! Les flèches de feu ont une force de 10, celles de glace 7."; break;
        case 1309: texte = "Non! Les flèches de feu ont une force de 10, celles de glace 7."; break;
        
        case 1310: texte = "Les bombes causent autant de dégâts que les coups de marteau, est-ce vrai ?*             VRAI ?            faux  "; idsuiv=1313; break;
        case 1311: texte = "Les bombes causent autant de dégâts que les coups de marteau, est-ce vrai ?*             vrai              FAUX ?"; idsuiv=1312; break;
        case 1312: texte = "Correct! Les bombes ont une force de 5, le marteau 3."; break;
        case 1313: texte = "Non! Les bombes ont une force de 5, le marteau 3."; break;
        
        case 1314: texte = "Quoi ??? Tu m'as vaincu ???**             VRAI ?            vrai  "; break;
        case 1315: texte = "Quoi ??? Tu m'as vaincu ???**             vrai              VRAI ?"; break;
        
        case 1316: texte = "Tu as trouvé le bouclier des Déesses !!!*Ta vie remonte désormais en permanence !!!"; break;
        case 1317: texte = "Sur cette pierre est écrite l'histoire d'Hyrule en hylien ancien :"; idsuiv=1318; break;
        case 1318: texte = "Après que les Déesses Din, Nayru et Farore eurent créé Hyrule, une entité maléfique d'un pouvoir inégalé arriva pour occuper cette terre."; idsuiv=1319; break;
        case 1319: texte = "Malgré leurs grands pouvoirs, les Déesses durent admettre qu'elles ne pourraient pas détruire ce mal."; idsuiv=1320; break;
        case 1320: texte = "...*La suite de l'histoire n'est pas écrite ici. Peut-être sur une autre stèle ?"; break;
        
        case 1321: texte = "Tu as trouvé la tunique des Déesses !!!*Ta magie remonte désormais en permanence !!!"; break;
        case 1322: texte = "Sur cette pierre est écrite l'histoire d'Hyrule en hylien ancien :"; idsuiv=1323; break;
        case 1323: texte = "Din, Nayru et Farore ne purent se résoudre à ne rien faire, et défièrent l'entité démoniaque."; idsuiv=1324; break;
        case 1324: texte = "Après un long combat perdu d'avance, elles durent accepter un compromis et réussirent à disperser le pouvoir de l'entité."; idsuiv=1325; break;
        case 1325: texte = "Pour ce faire, elles durent cependant créer des créatures démoniaques contenant les parcelles du pouvoir de l'entité."; idsuiv=1326; break;
        case 1326: texte = "Ce qui restait de l'entité maléfique fut emprisonné dans une forme humaine, et ne pourra s'en libérer tant que tous les types de monstres n'auront pas été vaincus."; break;
        
        case 1327: texte = "Bienvenue dans ces lieux, souhaites-tu que je t'explique comment fonctionne cet endroit ?*              OUI ?            non  "; idsuiv=1329; break;
        case 1328: texte = "Bienvenue dans ces lieux, souhaites-tu que je t'explique comment fonctionne cet endroit ?*              oui              NON ?"; idsuiv=1332; break;
        case 1329: texte = "Les ennemis de ce donjon sont très particuliers, chacune de leurs attaques te fera perdre 2 fois plus de vie que le coup précédent."; idsuiv=1330; break; 
        case 1330: texte = "Soit donc extrêmement prudent, 7 coups suffiront à t'achever."; idsuiv=1331; break;
        case 1331: texte = "De plus, le nombre d'ennemis que tu as vaincus, ainsi que le nombre de type d'ennemis vaincus sont comptabilisés. Un certain montant sera nécessaire pour ouvrir certaines portes."; idsuiv=1332; break;
        case 1332: texte = "Bonne chance Link, quoi qu'il advienne tout finit ici."; break;
        
        case 1333:
            if (gpJeu->getJoueur()->getCoffre(14,9)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 30 && gpJeu->getJoueur()->getCompteurType() >= 4) {id=1335; chercheText();break;}
            texte = "Elimine au moins 30 ennemis de 4 types différents et je t'ouvrirais cette porte."; break;
        case 1334: texte = "Bonne chance Link."; break;
        case 1335: texte = "Tu as vaincu suffisamment d'ennemis, je t'ouvre..."; break;
        case 1336:
            if (gpJeu->getJoueur()->getCoffre(14,10)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 60 && gpJeu->getJoueur()->getCompteurType() >= 10) {id=1335; chercheText();break;}
            texte = "Elimine au moins 60 ennemis de 10 types différents et je t'ouvrirais cette porte."; break;
        case 1337:
            if (gpJeu->getJoueur()->getCoffre(14,11)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 20 && gpJeu->getJoueur()->getCompteurType() >= 3) {id=1335; chercheText();break;}
            texte = "Elimine au moins 20 ennemis de 3 types différents et je t'ouvrirais cette porte."; break;
        case 1338:
            if (gpJeu->getJoueur()->getCoffre(14,12)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 99 && gpJeu->getJoueur()->getCompteurType() >= 12) {id=1335; chercheText();break;}
            texte = "Elimine au moins 99 ennemis de 12 types différents et je t'ouvrirais cette porte."; break;
        case 1339:
            if (gpJeu->getJoueur()->getCoffre(14,13)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 30 && gpJeu->getJoueur()->getCompteurType() >= 12) {id=1335; chercheText();break;}
            texte = "Elimine au moins 30 ennemis de 12 types différents et je t'ouvrirais cette porte."; break;
        case 1340:
            if (gpJeu->getJoueur()->getCoffre(14,14)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 40 && gpJeu->getJoueur()->getCompteurType() >= 6) {id=1335; chercheText();break;}
            texte = "Elimine au moins 40 ennemis de 6 types différents et je t'ouvrirais cette porte."; break;
        case 1341:
            if (gpJeu->getJoueur()->getCoffre(14,15)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 50 && gpJeu->getJoueur()->getCompteurType() >= 7) {id=1335; chercheText();break;}
            texte = "Elimine au moins 50 ennemis de 7 types différents et je t'ouvrirais cette porte."; break;
#ifdef __PSP2__
        case 1342: texte = "Tu as trouvé le masque d'Oni Link !!! *Maintiens R puis appuie sur L pour te transformer et devenir incroyablement puissant."; break;
#else
        case 1342: texte = "Tu as trouvé le masque d'Oni Link !!! *Utilise 'O' pour te transformer et devenir incroyablement puissant."; break;
#endif
        case 1343: texte = "Félicitations Link! Tu as battu chaque type d'ennemi... C'est incroyable..."; idsuiv=1344; break;
        case 1344: texte = "Je te dois énormément, veux-tu être payé maintenant ?"; idsuiv=1345; break;
        case 1345: texte = "Je vais enfin pouvoir reprendre ma vraie forme, prépare-toi à prendre cher!*Adieu, Héros d'Hyrule!"; break;
        case 1346: 
            if (gpJeu->nbEnnemis()==0) {id=1348; chercheText();break;}
            texte = "Vite Link! Utilise l'Epée des Déesses pour l'achever définitivement!"; break;
        case 1347: 
            if (gpJeu->nbEnnemis()==0) {id=1349; chercheText();break;}
            if (gpJeu->getEnnemi()->getSuivant()->getSpecial(2)<13) {id=1350; chercheText();break;}
            texte = "Pas sur moi andouille..."; break;
        case 1348: texte = "Félicitations Link, rentrons maintenant."; break;
        case 1349: texte = "Justice est faite. Mon maître est enfin vengé."; break;
        case 1350: texte = "Ecarte-toi!"; break;
        case 1351: texte = "Mais qu'est-ce que tu fabriques ?"; break;
        case 1352: texte = "Laisse-moi t'expliquer la raison de notre présence dans le sombre donjon de l'entité sans nom."; idsuiv=1353; break;
        case 1353: texte = "Après ton départ du château qui a suivi ma victoire sur Ganon, Ganondorf m'a remis la Triforce et m'a raconté son histoire."; idsuiv=1354; break;
        case 1354: texte = "Nous sommes rapidement arrivés à la conclusion que l'homme de l'encyclopédie des monstres était hautement louche, alors quand nous avons appris d'un garde que tu étais allé le voir, nous décidâmes de te venir en aide."; idsuiv=1355; break;
        case 1355: texte = "Comme nous le pensions, seule la puissance combinée des 3 Armes des Déesses maniées par les 3 Elus pouvait détruire à jamais ce fléau."; idsuiv=1356; break;
        case 1356: texte = "Quant à Ganondorf, il n'a plus rien à voir avec le monstre que nous connaissions, il n'y a désormais plus de ténèbres en lui et il est digne de confiance."; idsuiv=1357; break;
        case 1357: texte = "Désormais Hyrule est en paix, pour de bon. Les monstres ne réapparaîtront plus, le mal est définitivement vaincu."; idsuiv=1358; break;
        case 1358: texte = "Alors dis-moi Link, que vas-tu faire de tes vacances ?"; break;
        case 1359: texte = "Hyrule était sauvé et toute menace écartée. Après de longues aventures, les trois héros accomplirent leur destinée. **Les trois Déesses revinrent en Hyrule les féliciter, puis repartirent, emportant avec elles la Triforce. **Le puissant Ganondorf devint rapidement chef de la garde et passa le restant de ses jours à protéger le pays contre des ennemis qui ne vinrent jamais."; idsuiv=1360; break;
        case 1360: texte = "La princesse Zelda fut célébrée à travers tout le pays et bien plus loin encore comme étant la souveraine ayant apporté la paix sur le monde. **Quant à Link, préférant fuir la célébrité, il disparut après cette ultime victoire, et nul ne le revit en Hyrule."; break;
        case 1361: texte = "Après les évènements survenus à Termina, la princesse Zelda mit fin à l'exil de Link, annonçant alors au peuple sa victoire sur son alter égo maléfique."; idsuiv=1362; break;
        case 1362: texte = "Mais le chevalier hylien, peinant à assumer son statut de héros, partit vivre en ermite au fond d'une forêt que lui offrit la princesse."; idsuiv=1363; break;
        case 1363: texte = "L'existence de Termina devant rester secrète, la princesse tut les évènements qui s'y étaient déroulés et laissa vivre le peuple ignorant dans une paix illusoire."; idsuiv=1364; break;
        case 1364: texte = "Mais tous deux savaient hélas que, du fond de l'enfer, l'immortel Ganon, tirant son incroyable puissance du voeu"; buffer="originel à la Triforce, rassemblait son armée en vue de son prochain assaut."; idsuiv=1365; break;
        case 1365: texte = "Jusqu'au jour où, après des mois passés à guetter une attaque, un évènement troublant vint mettre fin à cette interminable attente..."; break;
        case 1366: texte = "HO HE !!! *MESSIRE LINK !!!"; break;
#ifdef __PSP2__
        case 1367: texte = "AIDE : Appuie sur Select pour consulter l'aide."; break;
#else
        case 1367: texte = "AIDE : Appuie sur F1 pour consulter l'aide."; break;
#endif
        case 1368: texte = "Reviens me voir quand tu auras une bourse et nous parlerons affaire."; break;
        case 1369: texte = "On a entendu des bruits de bataille, puis plus rien..."; break;
        case 1370: texte = "Que peut-il bien se passer ?"; break;
		case 1371:
            tmp = 0;
            for (int i = 0; i < 9; i++) if (gpJeu->getKeyboard()->getRang(i)) tmp++;
            if (tmp == 9 && gpJeu->getJoueur()->getEnnemi(141)) {id=1372; chercheText();break;}
            texte = "Cette porte mène à la salle cachée. *Obtiens les 9 rangs de la page Records et reviens après avoir obtenu la seconde fin pour y pénétrer.";
            break;
        case 1372: texte = "Tu peux entrer, Héros Légendaire."; break;
        case 1373: texte = "Bienvenue dans la salle cachée de 3T ! *Et félicitation pour y être arrivé !"; idsuiv=1374; break;
        case 1374: texte = "Moi c'est Vincent, j'ai conçu et codé ce jeu."; break;
        case 1375: texte = "Coucou, moi c'est Lobalùz. *J'ai aidé à la conception, fait quelques nouveaux graphismes, testé la plupart des donjons, et corrigé les textes."; break;
        case 1376: texte = "Salut, moi c'est Raiden. J'suis le dessinateur de l'équipe. Je me suis occupé de l'écran titre et des illustrations (... et aussi des nuages sur les maps m'enfin on s'en fout un peu...)."; idsuiv=1377; break;
        case 1377: texte = "Vous pouvez retrouver mes autres dessins sur http://alandar.deviantart.com"; break;
        case 1378: texte = "Des monstres ont coulé ma barque... *Je suis désolé, mais tu vas devoir nager désormais...";break;
    }
}

void Texte::affiche(SDL_Surface* gpScreen, std::string s, int a, int b) {
    for (int i = 0; i < (int)s.length(); i++) {
        afficheLettre(gpScreen, s.at(i),a,b);
        a+=6;
    }
}

void Texte::draw(SDL_Surface* gpScreen) {
    
    if (cadre) drawCadre(gpScreen);
    
    if (id==3 && texte == "Tu as trouvé un quart de coeur !!!") {
        SDL_Rect src; SDL_Rect dst;
        src.x=16*(gpJeu->getJoueur()->nbQuarts()%4);
        if(src.x==0)src.x=16*4;
        src.y=0; src.w=16; src.h=16; dst.x=160-8; dst.y=120-8+16*5;
        SDL_BlitSurface(imageCoeur, &src, gpScreen, &dst);
    }
    
    int a = x+8; int b = y+8;
    for (int i = 0; i < av; i++) {
        afficheLettre(gpScreen, texte.at(i),a,b);
        a+=6;
        if (a > x+w-16) {a=x+8; b+=16;}
    }
    
    if(SDL_GetTicks() > lastAnimTime + vitesse && def && av < (int)texte.length()) {
        lastAnimTime = SDL_GetTicks();
        do av++;
        while (av < (int)texte.length() && texte.at(av-1) == ' ');
        if (texte.at(av-1) != ' ') gpJeu->getAudio()->playSound(0,1);
    }
}

bool Texte::isFinished() {return (av==(int)texte.length());}

int Texte::getId() {return id;}

void Texte::changeId(int i) {
    id=i; idsuiv=0; buffer="";
    chercheText();
    decoupeText();
    if (av>(int)texte.length()) av=(int)texte.length();
}

void Texte::drawCadre(SDL_Surface* gpScreen) {
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=8; src.h=8; src.x = 103; src.y = 100; dst.x = x; dst.y = y;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.y = 109; src.w=8;
    for (int j = 8; j < h-8; j+=16) {
        dst.y = y + j;
        src.x = 103; dst.x = x; src.h=16;
        while (dst.y + src.h > y+h && src.h>0) src.h--;
        if (src.h>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
        src.x = 129; dst.x = x+w-8;
        if (src.h>0)SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.h=8; src.x = 103; src.y = 126; dst.x = x; dst.y = y+h-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

void Texte::setTexte(int idTxt, int vx, int vy, int vw, int vh, bool cadr, bool defil, int vit) {
    if (idTxt == 0) return;
    id = idTxt; 
    idsuiv = 0;
    buffer = "";
    chercheText();
    
    x = vx; y = vy; w = vw; h = vh;
    decoupeText();
        
    def=defil;
    if (def) av = 0;
    else av = texte.length();
    
    cadre = cadr;
    
    vitesse = vit;
}

void Texte::decoupeText() {
    //compte le nombre de caractères possibles et largeur et en hauteur
    int nbcol = (w-16)/6 -1;
    int nblig = (h-16)/16;
    int tailleMax = nbcol * nblig;
    int taille;
    
    //parcours du texte à afficher; à chaque début de mot, 
    //vérifie que le mot peut tenir sur la ligne
    for (int i = 0; i < (int)texte.length(); i++) {
        
        //supprime les espaces isolés en début de ligne
        if (texte.at(i)==' ' && texte.at(i+1)!=' ' && i%nbcol == 0) texte.erase(i,1);
        //recherche du début du prochain mot
        while(texte.at(i)==' ' && i < (int)texte.length()-1) i++;
        
        //saute une ligne si trouve une étoile
        if (texte.at(i)=='*') {
            texte.erase(i,1);//replace(i, 1, " ");
            int nb = (nbcol)-(i%(nbcol));
            for (int j = 0; j < nb; j++) texte.insert(i," ");
            continue;
        }
        
        //si le mot dépasse
        taille = tailleMot(i);
        if ((i%nbcol)+taille>nbcol) {
            if  (i < tailleMax) {
                //si le mot ne tient pas sur une ligne, on le coupe avec des tirets
                if (taille>nbcol) {
                    texte.insert(((i/nbcol)+1)*nbcol-1,"--");
                    i = 1+((i/nbcol)+1)*nbcol;
                }
                //sinon, on ajoute des espaces pour faire commencer le mot à la ligne
                else while((i%nbcol) != 0) {texte.insert(i," "); i++;}
            }
        }
        
    }
    
    // si le texte est trop grand, on le coupe en deux
    if ((int)texte.length() > tailleMax) {
        buffer = texte.substr(tailleMax);
        texte = texte.substr(0, tailleMax);
    }
}

int Texte::tailleMot(int deb) {
    int i = deb;
    int total = 0;
    while (texte.at(i)!=' ') {total++; i++; if (i >= (int)texte.length()) return total;}
    return total;
}

void Texte::afficheLettre(SDL_Surface* gpScreen, char c, int vx, int vy) {
    SDL_Rect src;
    SDL_Rect dst;
    
    int val = (int)c;
    
    dst.x=vx; dst.y=vy;
    src.h=16;src.w=8;
    
    if(val==32) return;
                
    //minuscules a-z
    if(val>=97 && val<=122) {
		src.x=4+16*((val-97)%10); 
		src.y=52+16*((val-97)/10);
	}
	//majuscules A-Z
	else if(val>=65 && val<=90) {src.x=6+16*((val-65)%10); src.y=2+16*((val-65)/10);}
	//chiffres
    else if(val>=48 && val<=57) {src.x=3+16*((val-48)%5); src.y=103+16*((val-48)/5);}
	else {
		switch(val){
			// Caractères spéciaux
			// /
			case 47: src.x=52;src.y=151;break;
			// @ hylien
			case 64: src.x=4;src.y=151;break;
            // + hylien
			case 43: src.x=20;src.y=151;break;
            // = hylien
			case 61: src.x=36;src.y=151;break;
			// ç
			case -25:
			case 231: src.x=148;src.y=34;break;
			// é
			case -23: 
			case 233: src.x=100;src.y=84;break;
			// ê
			case -22:
			case 234: src.x=116;src.y=84;break;
			// è
			case -24:
			case 232: src.x=132;src.y=84;break;
			// ë
			case -21:
			case 235: src.x=132;src.y=151;break;
			// à
			case -32:
			case 224: src.x=148;src.y=84;break;
			// â
			case -30:
			case 226: src.x=148;src.y=103;break;
			// ä
			case -28:
			case 228: src.x=148;src.y=135;break;
			// î
			case -18:
			case 238: src.x=84;src.y=119;break;
			// ï
			case -17:
			case 239: src.x=116;src.y=151;break;
			// û
			case -5:
			case 251: src.x=84;src.y=103;break;
			// ù
			case -7:
			case 249: src.x=148;src.y=151;break;
			// ü
			case -4:
			case 252: src.x=116;src.y=135;break;
			// ö
			case -10:
			case 246: src.x=132;src.y=135;break;
			// ô
			case -12:
			case 244: src.x=148;src.y=119;break;
			
			// Ponctuation
			//ponctuation
			// -
			case 45: src.x=102;src.y=34;break;
			// .
			case 46: src.x=118;src.y=34;break;
			// ,
			case 44: src.x=134;src.y=34;break;
			// !
			case 33: src.x=3;src.y=135;break;
			// ?
			case 63: src.x=19;src.y=135;break;
			// (
			case 40: src.x=35;src.y=135;break;
			// )
			case 41: src.x=51;src.y=135;break;            
			// ' ( avec @ )
			case 39: src.x=67;src.y=135;break;
			// :
			case 58: src.x=83;src.y=135;break;
			// ... ( avec % )
			case 37: src.x=101;src.y=135;break;
			// >
			case 62: src.x=100;src.y=151;break;
			// <
			case 60: src.x=84;src.y=151;break;
		}
	}
    
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

bool Texte::hasNext() {
    return (buffer != "" || idsuiv > 0);
}

bool Texte::suite() {
    if (av < (int)texte.length()) {
        av = texte.length();
        return true;
    }
    if (!hasNext()) {
        gpJeu->getAudio()->playSound(18);
        return gpJeu->finTexte(id);
    }
    if (buffer != "") {
        texte = buffer;
        buffer = "";
    }
    else {
        id = idsuiv;
        idsuiv = 0;
        chercheText();
    }
    decoupeText();
    if (def) av = 0;
    else av = texte.length();
    gpJeu->getAudio()->playSound(17);
    return true;
}
