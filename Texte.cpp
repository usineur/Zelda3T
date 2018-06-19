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
#ifdef __vita__
    imageButtons = gpJeu->loadImg("data/images/texte/buttons.png");
    SDL_SetColorKey(imageButtons,SDL_SRCCOLORKEY,SDL_MapRGB(imageButtons->format,0,0,255));
#endif
    imageCoeur = gpJeu->loadImg("data/images/menu/coeur.png");
    SDL_SetColorKey(imageCoeur,SDL_SRCCOLORKEY,SDL_MapRGB(imageCoeur->format,0,0,255));
    getTextByLangFunc = &Texte::getTexteEN;
}

Texte::~Texte() {
#ifdef __vita__
    SDL_FreeSurface(imageButtons);
#endif
    SDL_FreeSurface(imageFont);
    SDL_FreeSurface(imageCoeur);
}

void Texte::setTextLanguage(int id){
    switch(id){
        case 2:
            getTextByLangFunc = &Texte::getTexteFR;
            break;
        default:
            getTextByLangFunc = &Texte::getTexteEN;
    }
}

std::string Texte::getTexteEN(int id, std::string s){
    std::string texte = "";
    switch(id) {
        // 0 -> 99 : Carte
        case 0 : 
            texte = "Temple of Courage"; 
            break;
        case 1 : 
            texte = "Temple of Wisdom"; 
            break;
        case 2 : 
            texte = "Temple of Power"; 
            break;
        case 3 : 
            texte = "Abyss Ruins"; 
            break;
        case 4 : 
            texte = "Phantom Pyramid"; 
            break;
        case 5 : 
            texte = "Great Pyramid"; 
            break;
        case 6 : 
            texte = "Temple of Earth"; 
            break;
        case 7 : 
            texte = "Temple of Air"; 
            break;
        case 8 : 
            texte = "Temple of Water"; 
            break;
        case 9 : 
            texte = "Temple of Fire"; 
            break;
        case 10 : 
            texte = "Temple of Goddesses"; 
            break;
        case 11 : 
            texte = "Hyrule Castle"; 
            break;
        case 12 : 
            texte = "Casino"; 
            break;
        case 13 : 
            texte = "Tower of Gem"; 
            break;
        case 14 : 
            texte = "Final Destination"; 
            break;

        // 100 -> 199 : Encyclopedie
        case 100 :
            texte = "MONSTERS " + s;
            break;

        // 200 -> 399 : Generique
        case 200 : 
            texte = "PLAYER SELECT";
            break;
        case 201 :
            texte = "1.";
            break;
        case 202 :
            texte = "2.";
            break;
        case 203 :
            texte = "3.";
            break;
        case 204 :
            texte = "OPTIONS";
            break;
        case 205 :
            texte = "RECORDS";
            break;
        case 206 :
            texte = "OPTIONS";
            break;
        case 207 :
            texte = "MUSIC";
            break;
        case 208 :
            texte = "SOUND";
            break;
        case 209 :
            texte = "RETURN";
            break;
        case 210 :
            texte = "RECORDS";
            break;
        case 211 :
            texte = "BEST TIME : " + s;
            break;
        case 212 :
            texte = "100% RANK";
            break;
        case 213 :
            texte = "ULTIMATE RANK";
            break;
        case 214 :
            texte = "SPEED RANK";
            break;
        case 215 :
            texte = "RETURN";
            break;
        case 216 :
            texte = "ERASE";
            break;
        case 217 :
            texte = "ERASE ?";
            break;
        case 218 :
            texte = "YES";
            break;
        case 219 :
            texte = "NO";
            break;
        case 220 :
            texte = "LOAD";
            break;
        case 221 :
            texte = "ERASE";
            break;
        case 222 :
            texte = "CANCEL";
            break;
        case 223 :
#ifdef __vita__
            texte = "Return to the game: ¾3 - Next: ¾5";
#else
            texte = "Return to the game: Enter - Next: Right";
#endif
            break;
        case 224 :
#ifdef __vita__
            texte = "Read / Open / Speak : ¾2";
#else
            texte = "Read / Open / Speak : Space";
#endif
            break;
        case 225 :
#ifdef __vita__
            texte = "Confirm / Pass text: ¾3";
#else
            texte = "Confirm / Pass text: Enter";
#endif
            break;
        case 226 :
#ifdef __vita__
            texte = "Move Link: Left ¾9";
#else
            texte = "Move Link: Arrows";
#endif
            break;
        case 227 :
#ifdef __vita__
            texte = "Run: Hold R"; 
#else
            texte = "Run: Shift hold or Caps lock"; 
#endif
            break;
        case 228 :
#ifdef __vita__
            texte = "Use sword: ¾4";
#else
            texte = "Use sword: Z or W";
#endif
            break;
        case 229 :
#ifdef __vita__
            texte = "Spin attack: Hold ¾4 then dropped";
#else
            texte = "Spin attack: Z or W hold then dropped";
#endif
            break;
        case 230 :
#ifdef __vita__
            texte = "Item selection: ¾5";
#else
            texte = "Item selection: Enter";
#endif
            break;
        case 231 :
#ifdef __vita__
            texte = "Use selected object: ¾1";
#else
            texte = "Use selected object: X";
#endif
            break;
        case 232 :
#ifdef __vita__
            texte = "Carry: ¾3"; 
#else
            texte = "Carry: C"; 
#endif
            break;
        case 233 :
#ifdef __vita__
            texte = "See the map: L (outside or dungeons)";
#else
            texte = "See the map: P (outside or dungeons)";
#endif
            break;
        case 234 :
#ifdef __vita__
            texte = "See the map: L (in dungeons)";
#else
            texte = "See the map: P (in dungeons)";
#endif
            break;
        case 235 :
#ifdef __vita__
        texte = "See defeated monsters: ¾6"; 
#else
        texte = "See defeated monsters: M"; 
#endif
            break;
        case 236 :
#ifdef __vita__
        texte = "See fishes : ¾8"; 
#else
        texte = "See fishes : L"; 
#endif
            break;
        case 237 :
#ifdef __vita__
        texte = "See barter items : ¾7"; 
#else
        texte = "See barter items : I"; 
#endif
            break;
        case 238 :
#ifdef __vita__
        texte = "Oni Link transformation : L + R"; 
#else
        texte = "Oni Link transformation : O"; 
#endif
            break;
        case 239 :
#ifdef __vita__
            texte = "Look around: Right ¾9";
#else
            texte = "Look around: Ctrl and direction";
#endif
            break;
        case 240 :
#ifdef __vita__
            texte = "";
#else
            texte = "Enlarge / Shrink: Ctrl and Enter";
#endif
            break;
        case 241 :
#ifdef __vita__
            texte = "Save / Quit: Start";
#else
            texte = "Save / Quit: Esc";
#endif
            break;
        case 242 :
            texte = "HELP 1/3";
            break;
        case 243 :
            texte = "HELP 1/2";
            break;
        case 244 :
#ifdef __vita__
            texte = "Use selected object: ¾1";
#else
            texte = "Use selected object: X";
#endif
            break;
        case 245 :
#ifdef __vita__
            texte = "Carry: ¾3"; 
#else
            texte = "Carry: C"; 
#endif
            break;
        case 246 :
#ifdef __vita__
            texte = "See the map: L (outside or dungeons)";
#else
            texte = "See the map: P (outside or dungeons)";
#endif
            break;
        case 247 :
#ifdef __vita__
            texte = "See the map: L (in dungeons)";
#else
            texte = "See the map: P (in dungeons)";
#endif
            break;
        case 248 :
#ifdef __vita__
        texte = "See defeated monsters: ¾6"; 
#else
        texte = "See defeated monsters: M"; 
#endif
            break;
        case 249 :
#ifdef __vita__
        texte = "See fishes : ¾8"; 
#else
        texte = "See fishes : L"; 
#endif
            break;
        case 250 :
#ifdef __vita__
        texte = "See barter items : ¾7"; 
#else
        texte = "See barter items : I"; 
#endif
            break;
        case 251 :
#ifdef __vita__
        texte = "Oni Link transformation : L + R"; 
#else
        texte = "Oni Link transformation : O"; 
#endif
            break;
        case 252 :
            texte = "HELP 2/3";
            break;
        case 253 :
#ifdef __vita__
            texte = "Return to the game: ¾3 - Next: ¾5";
#else
            texte = "Return to the game: Enter - Next: Right";
#endif
            break;
        case 254 :
#ifdef __vita__
            texte = "Look around: Right ¾9";
#else
            texte = "Look around: Ctrl and direction";
#endif
            break;
        case 255 :
            texte = "Enlarge / Shrink: Ctrl and Enter";
            break;
        case 256 :
            texte = "HELP 2/2";
            break;
        case 257 :
#ifdef __vita__
            texte = "Return to the game: ¾3 - Previous: ¾7";
#else
            texte = "Return to the game: Enter - Previous: Left";
#endif
            break;
        case 258 :
            texte = "HELP 3/3";
            break;
        case 259 :
            texte = "BARTER ITEMS";
            break;
        case 260 :
            texte = s + " BAGS OF RICE";
            break;
        case 261 :
            texte = s + " BAG OF RICE";
            break;
        case 262 :
            texte = s + " JARS OF SPICES";
            break;
        case 263 :
            texte = s + " JAR OF SPICES";
            break;
        case 264 :
            texte = s + " BAGS OF OLIVES";
            break;
        case 265 :
            texte = s + " BAG OF OLIVES";
            break;
        case 266 :
            texte = s + " PEARLS";
            break;
        case 267 :
            texte = s + " PEARL";
            break;
        case 268 :
            texte = s + " FEATHERS";
            break;
        case 269 :
            texte = s + " FEATHER";
            break;
        case 270 :
            texte = s + " CHIKENS";
            break;
        case 271 :
            texte = s + " CHICKEN";
            break;
        case 272 :
            texte = s + " TAPESTRIES";
            break;
        case 273 :
            texte = s + " TAPESTRY";
            break;
        case 274 :
            texte = s + " AMULETS";
            break;
        case 275 :
            texte = s + " AMULET";
            break;
        case 276 :
            texte = s + " PERFUMES";
            break;
        case 277 :
            texte = s + " PERFUME";
            break;
        case 278 :
            texte = s + " MAGMA ROCKS";
            break;
        case 279 :
            texte = s + " MAGMA ROCK";
            break;
        case 280 :
            texte = s + " FROSTY ROCKS";
            break;
        case 281 :
            texte = s + " FROSTY ROCK";
            break;
        case 282 :
            texte = s + " PEPPER";
            break;
        case 283 :
            texte = s + " COGWHEEL";
            break;
        case 284 :
            texte = s + " GAUGE";
            break;
        case 285 :
            texte = s + " WHEEL";
            break;
        case 286 :
            texte = s + " ENERGY CORE";
            break;
        case 287 :
            texte = "RANK : Legendary Hero";
            break;
        case 288 :
            texte = "RANK : Hero of Two Worlds";
            break;
        case 289 :
            texte = "RANK : Heros of Hyrule";
            break;
        case 290 :
            texte = "RANK : Hero of Termina";
            break;
        case 291 :
            texte = "RANK : Hero of Time";
            break;
        case 292 :
            texte = "RANK : UNKNOWN";
            break;
        case 293 :
            texte = "100% complete the game.";
            break;
        case 294 :
            texte = "RANG : Legendary Sword Master";
            break;
        case 295 :
            texte = "RANK : Sword Master";
            break;
        case 296 :
            texte = "RANK : Swanky";
            break;
        case 297 :
            texte = "RANK : Bigheaded";
            break;
        case 298 :
            texte = "RANK : Proud";
            break;
        case 299 :
            texte = "RANK : UNKNOWN";
            break;
        case 300 :
            texte = "Complete the game not dead,";
            break;
        case 301 :
            texte = "with 12 hearts at the very most,";
            break;
        case 302 :
            texte = "and without buying a bottle.";
            break;
        case 303 :
            texte = "RANK : Legendary Marathon Runner";
            break;
        case 304 :
            texte = "RANK : Two Worlds Marathon Runner";
            break;
        case 305 :
            texte = "RANK : Hyrule Marathon Runner";
            break;
        case 306 :
            texte = "RANK : Termina Marathon Runner";
            break;
        case 307 :
            texte = "RANK : Marathon Runner of Time";
            break;
        case 308 :
            texte = "Complete the game in less than";
            break;
        case 309 :
            texte = "seven hours.";
            break;
        case 310 :
            texte = "RESULTS :";
            break;
        case 311 :
            texte = "Game time: " + s;
            break;
        case 312 :
            texte = "Dead " + s;
            break;
        case 313 :
            texte = "Pieces of heart: " + s;
            break;
        case 314 :
            texte = "Power Gems: " + s;
            break;
        case 315 :
            texte = "Objects: " + s + " / 139";
            break;
        case 316 :
            texte = "Barter items: " + s + " / 45";
            break;
        case 317 :
            texte = "Fishes: " + s + " / 30";
            break;
        case 318 :
            texte = "Enemies: " + s + " / 100";
            break;
        case 319 :
            texte = "You complete the game with " + s + "%, congratulations!";
            break;
        case 320 :
            texte = "RANK : ";
            break;
        case 321 :
            texte = " - Legendary Sword Master";
            break;
        case 322 :
            texte = " - Sword Master";
            break;
        case 323 :
            texte = " - Proud";
            break;
        case 324 :
            texte = " - Legendary Hero";
            break;
        case 325 :
            texte = " - Hero of Hyrule";
        case 326 :
            texte = " - Hero of Two Worlds";
            break;
        case 327 :
            texte = " - Hero of Time";
            break;
        case 328 :
            texte = " - Perfectionist";
            break;
        case 329 :
            texte = " - Zelda Fan";
            break;
        case 330 :
            texte = " - Keyboard professional";
            break;
        case 331 :
            texte = " - Pad professional";
            break;
        case 332 :
            texte = " - Experienced";
            break;
        case 333 :
            texte = " - Novice";
            break;
        case 334 :
            texte = " - Living dead";
            break;
        case 335 :
            texte = " - Kamikaze";
            break;
        case 336 :
            texte = " - Legendary Marathon Runner";
            break;
        case 337 :
            texte = " - Hyrule Marathon Runner";
            break;
        case 338 :
            texte = " - Two Worlds Marathon Runner";
            break;
        case 339 :
            texte = " - Marathon Runner of Time";
            break;
        case 400 :
            texte = "BOW";
            break;
        case 401 :
            texte = "FAIRY BOW";
            break;
        case 402 :
            texte = "HOOKSHOT";
            break;
        case 403 :
            texte = "BOMBS";
            break;
        case 404 :
            texte = "FIRE ARROWS";
            break;
        case 405 :
            texte = "RED GEMSTONE";
            break;
        case 406 :
            texte = "ANVIL";
            break;
        case 407 :
            texte = "HORSESHOE";
            break;
        case 408 :
            texte = "JEWEL";
            break;
        case 409 :
            texte = "LETTER";
            break;
        case 410 :
            texte = "WEDDING RING";
            break;
        case 411 :
            texte = "HAMMER";
            break;
        case 412 :
            texte = "FIRE ROD";
            break;
        case 413 :
            texte = "ICE ROD";
            break;
        case 414 :
            texte = "LANTERN";
            break;
        case 415 :
            texte = "ICE ARROWS";
            break;
        case 416 :
            texte = "BLUE GEMSTONE";
            break;
        case 417 :
            texte = "OLD BOOT";
            break;
        case 418 :
            texte = "HEAVY HAMMER";
            break;
        case 419 :
            texte = "LITTLE BELL";
            break;
        case 420 :
            texte = "AXE";
            break;
        case 421 :
            texte = "ROPE";
            break;
        case 422 :
            texte = "BRIDGE'S PLAN";
            break;
        case 423 :
            texte = "MAGIC HAMMER";
            break;
        case 424 :
            texte = "OCARINA OF TIME";
            break;
        case 425 :
            texte = "FISHING ROD";
            break;
        case 426 :
            texte = "SUPER FISHING ROD";
            break;
        case 427 :
            texte = "MEGA FISHING ROD";
            break;
        case 428 :
            texte = "LIGHT ARROWS";
            break;
        case 429 :
            texte = "YELLOW GEMSTONE";
            break;
        case 430 :
            texte = "BOTTLE OF WINE";
            break;
        case 431 :
            texte = "GOLD DUST";
            break;
        case 432 :
            texte = "MAGIC MIRROR";
            break;
        case 433 :
            texte = "SPOON";
            break;
        case 434 :
            texte = "SKULL";
            break;
        case 435 :
            texte = "IOU";
            break;
        case 436 : 
            texte = "SAW";
            break;
        case 437 :
            texte = "GREEN GEMSTONE";
            break;
        case 438 :
            texte = "CHART";
            break;
        case 439 : 
            texte = "BROOM";
            break;
        case 440 :
            texte = "MARMELADE POT";
            break;
        case 441 :
            texte = "CROISSANT";
            break;
        case 442 :
            texte = "BEER";
            break;
        case 443 :
            texte = "NAILS";
            break;
        case 444 :
            texte = "EMPTY BOTTLE";
            break;
        case 445 :
            texte = "RED POTION";
            break;
        case 446 :
            texte = "GREEN POTION";
            break;
        case 447 :
            texte = "BLUE POTION";
            break;
        case 448 :
            texte = "EQUIPMENT:";
            break;
        case 449 :
            texte = "LANGUAGE";
            break;
        case 450 :
            texte = "English";
            break;
        
        // 500 -> 599 : Poissons
        case 500 :
            texte = "FISHES " + s;
            break;
        case 501 : 
            texte = "Crawfish"; 
            break;
        case 502 : 
            texte = "Smelt"; 
            break;
        case 503 : 
            texte = "Zebrafish"; 
            break;
        case 504 : 
            texte = "Goby"; 
            break;
        case 505 : 
            texte = "Crab"; 
            break;
        case 506 : 
            texte = "Eel larvae"; 
            break;
        case 507 : 
            texte = "Minnow"; 
            break;
        case 508 : 
            texte = "Goldfish"; 
            break;
        case 509 : 
            texte = "Bleak"; 
            break;
        case 510 : 
            texte = "Gudgeon";
            break;
        case 511 : 
            texte = "Loach"; 
            break;
        case 512 : 
            texte = "Stickleback"; 
            break;
        case 513 : 
            texte = "Ruffe"; 
            break;
        case 514 : 
            texte = "Blenny"; 
            break;
        case 515 : 
            texte = "Magikarp"; 
            break;
        case 516 : 
            texte = "Trout"; 
            break;
        case 517 : 
            texte = "Ayu"; 
            break;
        case 518 : 
            texte = "Black perch"; 
            break;
        case 519 : 
            texte = "Eel"; 
            break;
        case 520 : 
            texte = "Catfish"; 
            break;
        case 521 : 
            texte = "Largemouth"; 
            break;
        case 522 : 
            texte = "Huchen"; 
            break;
        case 523 : 
            texte = "Barbell"; 
            break;
        case 524 : 
            texte = "Lamprey"; 
            break;
        case 525 : 
            texte = "Nase"; 
            break;
        case 526 : 
            texte = "Salmon"; 
            break;
        case 527 : 
            texte = "Sturgeon"; 
            break;
        case 528 :
            texte = "Arctic charr"; 
            break;
        case 529 : 
            texte = "Carp"; 
            break;
        case 530 : 
            texte = "Brown bullhead"; 
            break;

        // 600 -> ? : Texte
        case 600: texte = "Trade item*Talk with the good person to trade it."; break;
        case 601: texte = "You cannot fish here, try to find a pontoon."; break;
        case 602: texte = "You have found a piece of heart!!!"; break;
        case 603: texte = "Collect "; break;
        case 604: texte = " more to have a new heart!!!"; break;
        case 605: texte = "You've gained a new heart !!!"; break;
        case 606: texte = "You really enjoy talking to trees, don't you?"; break;
        case 607: texte = "Link's house**Do not come any closer."; break;
        case 608: texte = "N: To the Kakariko Village"; break;
        case 609: texte = "E : To Hyrule City"; break;
        case 610: texte = "Nothing caught..."; break;
        case 611: texte = "You caught a crawfish!"; break;
        case 612: texte = "You caught a smelt!"; break;
        case 613: texte = "You caught a zebrafish!"; break;
        case 614: texte = "You caught a goby!"; break;
        case 615: texte = "You caught a crab!"; break;
        case 616: texte = "You caught an eel larvae!"; break;
        case 617: texte = "You caught a minnow!"; break;
        case 618: texte = "You caught a goldfish!"; break;
        case 619: texte = "You caught a bleak!"; break;
        case 620: texte = "You caught a gudgeon!"; break;
        case 621: texte = "You caught a loach!"; break;
        case 622: texte = "You caught a stickleback!"; break;
        case 623: texte = "You caught a ruffe!"; break;
        case 624: texte = "You caught a blenny!"; break;
        case 625: texte = "You caught a magikarp!"; break;
        case 626: texte = "It had no effect..."; break;
        case 627: texte = "You caught a trout!*It's a big fish!"; break;
        case 628: texte = "You caught an ayu!*It's a big fish!"; break;
        case 629: texte = "You caught a black perch!*It's a big fish!"; break;
        case 630: texte = "You caught an eel!*It's a big fish!"; break;
        case 631: texte = "You caught a catfish!*It's a big fish!"; break;
        case 632: texte = "You caught a largemouth bass!*It's a big fish!"; break;
        case 633: texte = "You caught a huchen!*It's a big fish!"; break;
        case 634: texte = "You caught a barbell!*It's a big fish!"; break;
        case 635: texte = "You caught a lamprey!*It's a big fish!"; break;
        case 636: texte = "You caught a nase!*It's a big fish!"; break;
        case 637: texte = "You caught a salmon!*This fish is huge!"; break;
        case 638: texte = "You caught a sturgeon!*This fish is huge!"; break;
        case 639: texte = "You caught an arctic charr!*This fish is huge!"; break;
        case 640: texte = "You caught a carp!*This fish is huge!"; break;
        case 641: texte = "You caught a brown bullhead!*This fish is huge!"; break;
        case 642: texte = "You have found a power gem!**Barter it in the city for prices."; break;
        case 643: texte = "Good morning sir Link!*You look dreadful, were you asleep?"; break;
        case 644: texte = "The princess wants to see you urgently at the castle!"; break;
        case 645: texte = "..."; break;
        case 646: texte = "..."; break;
        case 647: texte = "The castle. To the east, don't tell me you've forgotten?"; break;
        case 648: texte = "Hem Hem..."; break;
        case 649: texte = "TUTORIAL : Press ¾2 near someone to talk with him, or near a sign to read it."; break;
        case 650: texte = "TUTORIAL : Press Space near someone to talk with him, or near a sign to read it."; break;
        case 651: texte = "You didn't learn any song."; break;
        case 652: texte = "- SONG OF SOARING*- Do not play"; break;
        case 653: texte = "- Song of Soaring*- DO NOT PLAY"; break;
        case 654: texte = "- SONG OF SOARING*- Inverted Song of Time*- Do not play"; break;
        case 655: texte = "- Song of Soaring*- INVERTED SONG OF TIME*- Do not play"; break;
        case 656: texte = "- Song of Soaring*- Inverted Song of Time*- DO NOT PLAY"; break;
        case 657: texte = "- SONG OF SOARING*- Inverted Song of Time*- Song of Double Time*- Do not play"; break;
        case 658: texte = "- Song of Soaring*- INVERTED SONG OF TIME*- Song of Double Time*- Do not play"; break;
        case 659: texte = "- Song of Soaring*- Inverted Song of Time*- SONG OF DOUBLE TIME*- Do not play"; break;
        case 660: texte = "- Song of Soaring*- Inverted Song of Time*- Song of Double Time*- DO NOT PLAY"; break;
        case 661: texte = "- INVERTED SONG OF TIME*- Do not play"; break;
        case 662: texte = "- Inverted Song of Time*- DO NOT PLAY"; break;
        case 663: texte = "- SONG OF DOUBLE TIME*- Do not play"; break;
        case 664: texte = "- Song of Double Time*- DO NOT PLAY"; break;
        case 665: texte = "- SONG OF SOARING*- Song of Double Time*- Do not play"; break;
        case 666: texte = "- Song of Soaring*- SONG OF DOUBLE TIME*- Do not play"; break;
        case 667: texte = "- Song of Soaring*- Song of Double Time*- DO NOT PLAY"; break;
        case 668: texte = "- INVERTED SONG OF TIME*- Song of Double Time*- Do not play"; break;
        case 669: texte = "- Inverted Song of Time*- SONG OF DOUBLE TIME*- Do not play"; break;
        case 670: texte = "- Inverted Song of Time*- Song of Double Time*- DO NOT PLAY"; break;
        case 671: texte = "No effect..."; break;
        case 672: texte = "Link's estate*Private property"; break;
        case 673: texte = "Hyrule City"; break;
        case 674: texte = "Looks like there are no fish here..."; break;
        case 675: texte = "N: To Hyrule Castle"; break;
        case 676: texte = "The castle is up north, hurry up!"; break;
        case 677: texte = "The castle is on the other side of the bridge, rush up!"; break;
        case 678: texte = "The princess is waiting for you at the castle, northerly from here."; break;
        case 679: texte = "You don't have enough."; break;
        case 680: texte = "Come back if you change your mind."; break;
        case 681: texte = "A cogwheel for a chicken and 100 rupees?**              YES ?            no  "; break;
        case 682: texte = "A cogwheel for a chicken and 100 rupees?**              yes              NO ?"; break;
        case 683: texte = "You got a cogwheel!*Go and give it to the man near of the waterfall!"; break;
        case 684: texte = "A piece of heart for a magma rock and a frosty rock?*              YES ?            no  "; break;
        case 685: texte = "A piece of heart for a magma rock and a frosty rock?*              yes              NO ?"; break;
        case 686: texte = "Sorry, I have nothing in stock anymore."; break;
        case 687: texte = "A wallet able to hold up to 200 rupees for 1 feather and 10 rupees?*              YES ?            no  "; break;
        case 688: texte = "A wallet able to hold up to 200 rupees for 1 feather and 10 rupees?*              yes              NO ?"; break;
        case 689: texte = "You got a regular wallet!*It allows you to hold up to 200 rupees!"; break;
        case 690: texte = "A wallet able to hold up to 500 rubis for a tapestry and 100 rupees?*              YES ?            no  "; break;
        case 691: texte = "A wallet able to hold up to 500 rubis for a tapestry and 100 rupees?*              yes              NO ?"; break;
        case 692: texte = "You got a big wallet!*It allows you to hold up to 500 rupees!!!"; break;
        case 693: texte = "A wallet able to hold up to 999 rupees for 1 amulet, 1 magma rock and 250 rupees?*              YES ?            no  "; break;
        case 694: texte = "A wallet able to hold up to 999 rupees for 1 amulet, 1 magma rock and 250 rupees?*              yes              NO ?"; break;
        case 695: texte = "You got a huge wallet!!!*It allows you to hold up to 999 rupees!!!"; break;
        case 696: texte = "A chicken for 2 bags of rice and 3 bags of olives?**              YES ?            no  "; break;
        case 697: texte = "A chicken for 2 bags of rice and 3 bags of olives?**              yes              NO ?"; break;
        case 698: texte = "You got a chicken!"; break;
        case 699: texte = "You can't carry more..."; break;
        case 700: texte = "A feather for 2 jars of spices and 2 bags of olives ?*              YES ?            no  "; break;
        case 701: texte = "A feather for 2 jars of spices and 2 bags of olives?*              yes              NO ?"; break;
        case 702: texte = "You got a feather!"; break;
        case 703: texte = "A bag of rice for 15 rupees?**              YES ?            no  "; break;
        case 704: texte = "A bag of rice for 15 rupees?**              yes              NO ?"; break;
        case 705: texte = "You got a bag of rice!"; break;
        case 706: texte = "A bag of olives for 10 rupees?**              YES ?            no  "; break;
        case 707: texte = "A bag of olives for 10 rupees?**              yes              NO ?"; break;
        case 708: texte = "You got a bag of olives!"; break;
        case 709: texte = "I feel like I spent my entire life sweeping...*One of these days, I would like to go on a journey..."; break;
        case 710: texte = "Is this a chart you have?*Do you mind giving it to me? I dream of going in a travel to see wonderful things!"; break;
        case 711: texte = "I will give you my broom in return, is it okay with you?*              YES ?            no  "; break;
        case 712: texte = "I will give you my broom in return, is it okay with you?*              yes              NO ?"; break;
        case 713: texte = "Thank you! Take my broom as a reward. It's a first-class broom, it is in my family since centuries, you're making a good deal!"; break;
        case 714: texte = "Oh. If that's so I guess I just have to keep sweeping..."; break;
        case 715: texte = "You traded the chart for a broom!"; break;
        case 716: texte = "So, where am I going?"; break;
        case 717: texte = "Sometimes, in my dream, I eat them spit roasted..."; break;
        case 718: texte = "This town is full of shops of all kinds, too bad I'm interested in none of them..."; break;
        case 719: texte = "Since the return of the peace, princess Zelda made a lot for Hyrule. There wouldn't be such prosperous town without her."; break;
        case 720: texte = "To barter is the only way to get some rare objects, or some ingredients to cook."; break;
        case 721: texte = "My Mom always tells me not to get close the hens... Why?"; break;
        case 722: texte = "The princess insists that we keep watching on the city... But every one know that Ganon is dead..."; break;
        case 723: texte = "I would rather sleep in the castle instead of mounting guard here..."; break;
        case 724: texte = "Life is good in Hyrule since Ganon is not a threat anymore, thanks again Link!"; break;
        case 725: texte = "Since the theft in the castle, the princess doubled the guard... and here I am, again..."; break;
        case 726: texte = "Join up, they said... It's a man's life, they said..."; break;
        case 727: texte = "I heard that a very precious object has been stolen in the castle, and since then the princess would have become an absolute paranoiac..."; break;
        case 728: texte = "I guess it was something she was fond of... A mirror of her collection, probably..."; break;
        case 729: texte = "Zzzzz... Zzzzz..."; break;
        case 730: texte = "N : To Ganon Castle"; break;
        case 731: texte = "The Moon Pearl for a wheel, a gauge, an energy core and 100 Gold Ganon?*              YES ?            no  "; break;
        case 732: texte = "The Moon Pearl for a wheel, a gauge, an energy core and 100 Gold Ganon?*              yes              NO ?"; break;
        case 733: texte = "You got the Moon Pearl!*You regain your normal aspect and the use of your weapons!"; break;
        case 734: texte = "A wallet able to hold up to 200 Gold Ganon for a pearl and 10 Gold Ganon?*              YES ?            no  "; break;
        case 735: texte = "A wallet able to hold up to 200 Gold Ganon for a pearl and 10 Gold Ganon?*              yes              NO ?"; break;
        case 736: texte = "You got a regular wallet!*It allows you to hold up to 200 Gold Ganon!"; break;
        case 737: texte = "A wallet able to hold up to 500 Gold Ganon for an amulet and 100 Gold Ganon?*              YES ?            no  "; break;
        case 738: texte = "A wallet able to hold up to 500 Gold Ganon for an amulet and 100 Gold Ganon?*              yes              NO ?"; break;
        case 739: texte = "You got a big wallet!*It allows you to hold up to 500 Gold Ganon!!!"; break;
        case 740: texte = "A wallet able to hold up to 999 Gold Ganon for a perfume, a frosty rock and 250 Gold Ganon?*              YES ?            no  "; break;
        case 741: texte = "A wallet able to hold up to 999 Gold Ganon for a perfume, a frosty rock and 250 Gold Ganon?*              yes              NO ?"; break;
        case 742: texte = "You got a huge wallet!!!*It allows you to hold up to 999 Gold Ganon!!!"; break;
        case 743: texte = "A wheel for 3 jars of spices?**              YES ?            no  "; break;
        case 744: texte = "A wheel for 3 jars of spices?**              yes              NO ?"; break;
        case 745: texte = "You got a wheel!*...*Awesome..."; break;
        case 746: texte = "A bomb bag for 1 pepper et 3 jars of spices?**              YES ?            no  "; break;
        case 747: texte = "A bomb bag for 1 pepper et 3 jars of spices?**              yes              NO ?"; break;
        case 748: texte = "You got a bomb bag!*You will be able to blow out new ways!"; break;
        case 749: texte = "A magma rock for a tapestry, an amulet and a perfume?*              YES ?            no  "; break;
        case 750: texte = "A magma rock for a tapestry, an amulet and a perfume?*              yes              NO ?"; break;
        case 751: texte = "You got a magma rock!"; break;
        case 752: texte = "A pearl for 5 jars of spices and 5 Gold Ganon? *              YES ?            no  "; break;
        case 753: texte = "A pearl for 5 jars of spices and 5 Gold Ganon? *              yes              NO ?"; break;
        case 754: texte = "You got a pearl!"; break;
        case 755: texte = "A jar of spices for 10 Gold Ganon?**              YES ?            no  "; break;
        case 756: texte = "A jar of spices for 10 Gold Ganon?**              yes              NO ?"; break;
        case 757: texte = "You got a jar of spice!"; break;
        case 758: texte = "He! Heeeee! Heeeeeeee!"; break;
        case 759: texte = "Last night, the barman didn't have beer left...*Ganon turned red with rage and started to destroy everything...*In the end, no one has anything left to drink..."; break;
        case 760: texte = "The destroyed houses were Ganon's opponents' ones..."; break;
        case 761: texte = "The bar is destroyed too, but... ...for other reasons..."; break;
        case 762: texte = "The market place is main attraction of the city, now that the bar is ruined..."; break;
        case 763: texte = "You've got the Moon Pearl?*Well, in view of the result, maybe it wasn't that much of a good deal..."; break;
        case 764: texte = "The Moon Pearl helps you regain a human aspect. A stallholder has one, but it's far too expensive..."; break;
        case 765: texte = "N : Holy Lands - Camping prohibited"; break;
        case 766: texte = "A wallet able to hold up to 200 Gold coins for a chicken and 10 Gold coins?*              YES ?            no  "; break;
        case 767: texte = "A wallet able to hold up to 200 Gold coins for a chicken and 10 Gold coins?*              yes              NO ?"; break;
        case 768: texte = "You got a regular wallet!*It allows you to hold up to 200 Gold coins!"; break;
        case 769: texte = "A wallet able to hold up to 500 Gold coins for a perfume and 100 Gold coins?*              YES ?            no  "; break;
        case 770: texte = "A wallet able to hold up to 500 Gold coins or a perfume and 100 Gold coins?*              yes              NO ?"; break;
        case 771: texte = "You got a big wallet!*It allows you to hold up to 500 Gold coins!!!"; break;
        case 772: texte = "A wallet able to hold up to 999 Gold coins for a tapestry, a magma rock and 250 Gold coins?*              YES ?            no  "; break;
        case 773: texte = "A wallet able to hold up to 999 Gold coins for a tapestry, a magma rock and 250 Gold coins?*              yes              NO ?"; break;
        case 774: texte = "You got a huge wallet!!!*It allows you to hold up to 999 Gold coins!!!"; break;
        case 775: texte = "An amulet for 1 chicken and 2 bags of olives?*              YES ?            no  "; break;
        case 776: texte = "An amulet for 1 chicken and 2 bags of olives?*              yes              NO ?"; break;
        case 777: texte = "You got an amulet!"; break;
        case 778: texte = "A feather for a jar of spices and a bag of olives?*              YES ?            no  "; break;
        case 779: texte = "A feather for a jar of spices and a bag of olives?*              yes              NO ?"; break;
        case 780: texte = "With all these wolves, it's very dangerous to leave the village..."; break;
        case 781: texte = "Your weapon looks like this of the Knights... *Did you ever fight wolves with it?"; break;
        case 782: texte = "I hate hens, but if the wolves manage to get in the village, maybe they won't dare coming close..."; break;
        case 783: texte = "The torchs at the entry of the village keep the wolves away, but they come closer and closer every day..."; break;
        case 784: texte = "The chief of the village had a bar built recently... They say that he would have done this to attract the Hylian Knights so that they would protect us..."; break;
        case 785: texte = "When time is no good, I make marmelades to keep me busy... But in this season, I guess I will have to find another activity..."; break;
        case 786: texte = "Is that a broom you have?*I feel a vocation springing up in me... Will you cede it to me for my last marmelade jar?"; break;
        case 787: texte = "This broom for a marmelade pot?**              YES ?            no  "; break;
        case 788: texte = "This broom for a marmelade pot?**              yes              NO ?"; break;
        case 789: texte = "Great! This will keep my mind away of all the problems of this time, and maybe it will even keep the wolves away of me!"; break;
        case 790: texte = "Sooner or later, I'm sure you will give it to me..."; break;
        case 791: texte = "You traded the broom for a marmelade pot!"; break;
        case 792: texte = "Giving is giving!"; break;
        case 793: texte = "Hyrule Castle"; break;
        case 794: texte = "N : To the graveyard"; break;
        case 795: texte = "Welcome in the castle, Sir Link!"; break;
        case 796: texte = "We were ordered to let you pass."; break;
        case 797: texte = "Ganon Castle"; break;
        case 798: texte = "5 Gold Ganon and we let ya come'n go in the castle?*              YES ?            no  "; break;
        case 799: texte = "5 Gold Ganon and we let ya come'n go in the castle?*              yes              NO ?"; break;
        case 800: texte = "You can go."; break;
        case 801: texte = "MAY THE WAY TO THE TRIFORCE BE OPENED FOR YOU...*SEE APPEAR THE TEMPLE OF THE TRIFORCE!"; break;
        case 802: texte = "W : To Hyrule Castle"; break;
        case 803: texte = "N : To the waterfalls"; break;
        case 804: texte = "E : Entry of the Lost Woods"; break;
        case 805: texte = "You've found a magic crystal!!!"; break;
        case 806: texte = "Again "; break;
        case 807: texte = " left to find!"; break;
        case 808: texte = "Finally you've got them all!!!"; break;
        case 809: texte = "Do you want to save your game?**                    ? YES ?*                      no   "; break;
        case 810: texte = "Do you want to save your game?**                      yes  *                    ? NO  ?"; break;
        case 811: texte = "Game saved."; break;
        case 812: texte = "I'm building an opera here, I don't have time to talk during the break!"; break;
        case 813: texte = "What's more, I've lost my precious star accessory..."; break;
        case 814: texte = "You've found my fetish skull???*I had forgotten it in jail...*Give it back! I will be eternally grateful!"; break;
        case 815: texte = "This skull for my gratefulness, ok?**              YES ?            no  "; break;
        case 816: texte = "This skull for my gratefulness, ok?**              yes              NO ?"; break;
        case 817: texte = "Thank you! I regain all motivation! I will finish this opera!"; break;
        case 818: texte = "After a break..."; break;
        case 819: texte = "Thief..."; break;
        case 820: texte = "You traded the skull for an IOU!"; break;
        case 821: texte = "To be or not to be? that is the question..."; break;
        case 822: texte = "do I say it well ?"; break;
        case 823: texte = "Temple of Courage**Courage, flee!"; break;
        case 824: texte = "Welcome at Tingle's place!"; break;
        case 825: texte = "Temple of Air**Chance of cold!"; break;
        case 826: texte = "S : To Mabe Village"; break;
        case 827: texte = "Mabe Village"; break;
        case 828: texte = "A tapestry for 2 pearls and 5 jars of spices? **              YES ?            no  "; break;
        case 829: texte = "A tapestry for 2 pearls and 5 jars of spices? **              yes              NO ?"; break;
        case 830: texte = "You got a tapestry!"; break;
        case 831: texte = "An amulet for 5 chickens and 5 bags of olives? *              YES ?            no  "; break;
        case 832: texte = "An amulet for 5 chickens and 5 bags of olives? *              yes              NO ?"; break;
        case 833: texte = "A pearl for 2 jars of spices and 2 bags of rice?*              YES ?            no  "; break;
        case 834: texte = "A pearl for 2 jars of spices and 2 bags of rice?*              yes              NO ?"; break;
        case 835: texte = "A bag of rice for a bag of olives and 2 rupees? *              YES ?            no  "; break;
        case 836: texte = "A bag of rice for a bag of olives and 2 rupees? *              yes              NO ?"; break;
        case 837: texte = "The men of the village are all obsessed by the fishing contest...*I wonder who will be the winner..."; break;
        case 838: texte = "You're participating in the fishing contest too?*...*..."; break;
        case 839: texte = "In the end you're just like the others..."; break;
        case 840: texte = "You won the fishing contest?*...*..."; break;
        case 841: texte = "I am your biggest fan!!!"; break;
        case 842: texte = "A fishing stand has just opened at the west of the village...*The owner organizes a great fishing contest to mark the start of his shop."; break;
        case 843: texte = "You are in the contest too? *It's hopeless, I can't find more than three types of fish..."; break;
        case 844: texte = "Since the fishing contest is over, everyone returned to his own business."; break;
        case 845: texte = "Ma e Vi l ge"; break;
        case 846: texte = "Hang-out of the Fearless Knights"; break;
        case 847: texte = "**NB : If we are not here, try the tavern."; break;
        case 848: texte = "A power gem for 2 pearls?**              YES ?            no  "; break;
        case 849: texte = "A power gem for 2 pearls?**              yes              NO ?"; break;
        case 850: texte = "A power gem for 2 feathers?**              YES ?            no  "; break;
        case 851: texte = "A power gem for 2 feathers?**              yes              NO ?"; break;
        case 852: texte = "A power gem for 2 chickens?**              YES ?            no  "; break;
        case 853: texte = "A power gem for 2 chickens?**              yes              NO ?"; break;
        case 854: texte = "A chicken for 1 bag of rice and 2 bags of olives? *              YES ?            no  "; break;
        case 855: texte = "A chicken for 1 bag of rice and 2 bags of olives? *              yes              NO ?"; break;
        case 856: texte = "Beyond Hyrule's South border, a gigantic ocean is said to stand..."; break;
        case 857: texte = "At the mating season the seagulls get over the cliff separating us from the seashore and come in the village."; break;
        case 858: texte = "This village is under the protection of the Hylian Knights, you are safe here."; break;
        case 859: texte = "Yet, since a tavern opened in the neighbouring town, we don't see our protectors around anymore..."; break;
        case 860: texte = "Not here either? But where did I lose it?"; break;
        case 861: texte = "You have found my mother-in-law's vase??? *She makes me look for it everywhere for centuries! *Give it back right away!"; break;
        case 862: texte = "This vase for a stuff I just found, ok?**              YES ?            no  "; break;
        case 863: texte = "This vase for a stuff I just found, ok?**              yes              NO ?"; break;
        case 864: texte = "Wise resolution kid."; break;
        case 865: texte = "Kill him..."; break;
        case 866: texte = "You traded the boot for a hammer!"; break;
        case 867: texte = "You wanna enter my gang?**              YES ?            no  "; break;
        case 868: texte = "You wanna enter my gang?**              yes              NO ?"; break;
        case 869: texte = "Ha! Ha! Ha! *I was kidding! *Pathetic little fool! *Do you realize who you are dealing with?!"; break;
        case 870: texte = "Temple of Wisdom**Only the wise ones will stay away from it."; break;
        case 871: texte = "Boat rental shop"; break;
        case 872: texte = "The boat shop is closed for today, I am about to win the fishing contest, I already have three differents!"; break;
        case 873: texte = "Would you like to rent a boat for 15 rupees?**              YES ?            no  "; break;
        case 874: texte = "Would you like to rent a boat for 15 rupees?**              yes              NO ?"; break;
        case 875: texte = "You can use the boat at the pontoon, have fun, but don't go too far."; break;
        case 876: texte = "(far away voice:) *I told you... DON'T GO TOO FAR!!!!"; break;
        case 877: texte = "Abyss Cave**Thank you to don't come look for the descendant of the wisemen who is not hidding here."; break;
        case 878: texte = "Blacksmith"; break;
        case 879: texte = "Great Pyramid"; break;
        case 880: texte = "HINT 1: The stone the most at the right is the second one. *HINT 2: The stones must all be removed by weight order."; break;
        case 881: texte = "HINT 3: The tail's stones must be removed before the fin's one. *HINT 4: The eye's stone must be the fifth you remove."; break;
        case 882: texte = "HINT 5: The water stones must be removed before the last one of the tail. *HINT 6: The eye's stone must be removed after the fin's one."; break;
        case 883: texte = "HINT 7: The last stone is not the eye. *HINT 8: The 2 stones of the tail must not be removed one after the other."; break;
        case 884: texte = "HINT 9: One of the nine hints is a fake."; break;
        case 885: texte = "N : Rocky Mountains"; break;
        case 886: texte = "Kakariko Village"; break;
        case 887: texte = "The Pegasus boots for a tapestry and a perfume? *              YES ?            no  "; break;
        case 888: texte = "The Pegasus boots for a tapestry and a perfume? *              yes              NO ?"; break;
        case 889: texte = "You got the Pegasus boots! *Hold R to run!"; break;
        case 890: texte = "You got the Pegasus boots! *Hold Shift or press Capslock to run!"; break;
        case 891: texte = "A perfume for 3 feathers and 4 bags of rice? **              YES ?            no  "; break;
        case 892: texte = "A perfume for 3 feathers and 4 bags of rice? **              yes              NO ?"; break;
        case 893: texte = "You got a perfume!"; break;
        case 894: texte = "A bag of olives for 15 rupees?**              YES ?            no  "; break;
        case 895: texte = "A bag of olives for 15 rupees?**              yes              NO ?"; break;
        case 896: texte = "A jar of spices for 20 rupees?**              YES ?            no  "; break;
        case 897: texte = "A jar of spices for 20 rupees?**              yes              NO ?"; break;
        case 898: texte = "The Kakariko Village is a prerequisite for all adventurers willing to climb up the mountain. The less brave ones just reach the saloon..."; break;
        case 899: texte = "Welcome in our village, Link! *Have fun, but don't go too close of the cactus..."; break;
        case 900: texte = "The Pegasus boots make you going much much faster. It's a real advantage in a fight."; break;
        case 901: texte = "You have these boots? *Then you must be pretty strong now..."; break;
        case 902: texte = "A frosty rock for a tapestry, an amulet and a perfume? *              YES ?            no  "; break;
        case 903: texte = "A frosty rock for a tapestry, an amulet and a perfume? *              yes              NO ?"; break;
        case 904: texte = "You got a frosty rock!"; break;
        case 905: texte = "A pearl for a jar of spices and a bag of rice? *              YES ?            no  "; break;
        case 906: texte = "A pearl for a jar of spices and a bag of rice? *              yes              NO ?"; break;
        case 907: texte = "This village is under the protection of the 7 Wise Men. Because of their magic, you have to go pretty far before seeing a wolf..."; break;
        case 908: texte = "You are here in the safer village you could find. Nothing to see withthe hamlet in the center doomed to disappear, or with the west village protected by alcoholics..."; break;
        case 909: texte = "Temple of Time"; break;
        case 910: texte = "Mine Entry"; break;
        case 911: texte = "Temple of Power**Only for sturdy."; break;
        case 912: texte = "I isolated myself from the world to meditate on the meaning of life..."; break;
        case 913: texte = "...but I must admitt I miss some particular things..."; break;
        case 914: texte = "Is this a bottle of wine you have??? *Give it to me! I will give you gold for it!!!"; break;
        case 915: texte = "This bottle for gold, ok ?**              YES ?            no  "; break;
        case 916: texte = "This bottle for gold, ok ?**              yes              NO ?"; break;
        case 917: texte = "I feel I'm getting close of the truth!"; break;
        case 918: texte = "...*I will have to meditate on the meaning of your refusal..."; break;
        case 919: texte = "You traded the bottle for Gold Dust!"; break;
        case 920: texte = "I finally found the meaning of life... -hiccup- !"; break;
        case 921: texte = "Tower of Ice**The way will open when all the power gems are found."; break;
        case 922: texte = "From here I can admire the lake of lava... *In fact, I love all the red and shiny things."; break;
        case 923: texte = "Mmm... it's an amazing gemstone you have here... *Would you give it to me for... a surprise?"; break;
        case 924: texte = "This red gemstone for a surprise, ok?**              YES ?            no  "; break;
        case 925: texte = "This red gemstone for a surprise, ok?**              yes              NO ?"; break;
        case 926: texte = "Thank you! Here is your surprise! I tried to get ride of it for a looong time..."; break;
        case 927: texte = "Too bad for you, no gemstone no surprise."; break;
        case 928: texte = "You traded the red gemstone for an anvil! You can't run nor swim while you have it!"; break;
        case 929: texte = "I feel like I have a great weight off me, and I'm wealthier too, so happy!"; break;
        case 930: texte = "Temple of Fire"; break;
        case 931: texte = "We are talking reindeers."; break;
        case 932: texte = "We ran aground here after crashing into a seagull... *It wouldn't have happened if I had have a horn..."; break;
        case 933: texte = "Oh, I almost forgot: *Ho! Ho! Ho!"; break;
        case 934: texte = "Is this a bell here? It's giving me an idea... Would you give it to me? I don't have pony anymore, but I guess I can find something to thank you..."; break;
        case 935: texte = "This little bell for a gift, ok?**              YES ?            no  "; break;
        case 936: texte = "This little bell for a gift, ok?**              yes              NO ?"; break;
        case 937: texte = "Thank you! Here is your gift: the axe I had to deliver to the local executioner. Happy ?"; break;
        case 938: texte = "... *What is your name, naughty boy?*I strike you off my list."; break;
        case 939: texte = "You traded the little bell for an axe!"; break;
        case 940: texte = "Ho! Ho! Ho!"; break;
        case 941: texte = "That's all very well, but how do I go home?"; break;
        case 942: texte = "TUTORIAL :*A hit on one of these colored sphere switch the stumbling blocks."; break;
        case 943: texte = "You have found a sword!!!*Use it with ¾4, or keep ¾4 holded to charge a spin attack!"; break;
        case 944: texte = "You have found a sword!!!*Use it with the key Z (or W), or keep Z (or W) holded to charge a spin attack!"; break;
        case 945: texte = "TUTORIAL :*Falling in a hole will bring you at the floor below. However, if there is no floor below like here, a fall will make you lose life and will bring at the entry of the area, so be careful!"; break;
        case 946: texte = "TUTORIAL :*During the game, you might see some spots apparently inaccessible, like the platform underneath. You will then have"; break;
        case 947: texte = "to come back later with more equipment to reach it."; break;
        case 948: texte = "@+@+@+@+@+@+@@@+*@=++=@=+@=+@=+=@*+@+@+@+=+="; break;
        case 949: texte = "The guards saw you heading toward the forest, I thought you may have a lead so I ran up..."; break;
        case 950: texte = "Mmm... This stele is written in ancient hylian... I will translate it:"; break;
        case 951: texte = "At the dawn of cataclysm, shall the heroe find this stele. The Pendents of Courage, Wisdom and Power in his possession, his only chance to save the world will arise."; break;
        case 952: texte = "..."; break;
        case 953: texte = "I'm afraid we'll have to forget about the ocarina for a moment...*If this stele says the truth, you have to gather the 3 pendents as soon as possible..."; break;
        case 954: texte = "They are hidden in 3 temples, the nearest is a tower by the waterfalls, north of here... Take this map, it will help you find your way!"; break;
        case 955: texte = "You got the map of Hyrule!**Press L outdoors to see it."; break;
        case 956: texte = "You got the map of Hyrule!**Press P outdoors to see it."; break;
        case 957: texte = "The first pendent is in a tower North of this forest. Leave the forest by the West and head North to arrive in the waterfalls area."; break;
        case 958: texte = "The second pendent is in the temple in the middle of the Lake. You should rent a boat at the Mabe village..."; break;
        case 959: texte = "The last pendent is in a temple surrounded by the mountains, North of the Kakariko Village."; break;
        case 960: texte = "You've found all the pendents ?*Very well, we don't know what is going to happen, so take this sword with you."; break;
        case 961: texte = "You got the Master Sword!!!*You will probably need its power!"; break;
        case 962: texte = "it looks like a teleportation portal, but... ...we have no information about where it goes..."; break;
        case 963: texte = "Try to touch the stele, something will surely happen now that you've got the pendents..."; break;
        case 964: texte = "One last thing:*Monsters are starting to appear everywhere in Hyrule... It's a very bad omen... Be careful."; break;
        case 965: texte = "Hello Link, I don't have many visitors these times..."; break;
        case 966: texte = "Let me improve your shield..."; break;
        case 967: texte = "You got a better shield!!!*Your defense raises by one point!"; break;
        case 968: texte = "Come back to see me if you are hurt, I would take care of your wounds."; break;
        case 969: texte = "You got 10 bags of rice!"; break;
        case 970: texte = "You got 10 jars of spices!"; break;
        case 971: texte = "You got 10 bags of olives!"; break;
        case 972: texte = "To reach the Pyramid, find and write down the 9 hints hidden on the desert's signs, the lift the whale's stones in the right order, and the way will open..."; break;
        case 973: texte = "Cart express: I'm out for the moment, in case of emergency, I am at the saloon.** - The mine employee -"; break;
        case 974: texte = "Cart express : service is provided again!"; break;
        case 975: texte = "Jump on the cart and let me take care of the lever. *Don't worry, it's my job!"; break;
        case 976: texte = "You have found some wooden planks!*You could use them to build a bridge..."; break;
        case 977: texte = "Looks like a good place to build a bridge."; break;
        case 978: texte = "                      Link*                 Heroe of Hyrule*               - Killed by Ganon -"; break;
        case 979: texte = "We are all back together, we can open the portal..."; break;
        case 980: texte = "Be sure to be ready, the ocarina's thief is probably a powerfull creature..."; break;
        case 981: texte = "You took the ocarina back? Congratulations!"; break;
        case 982: texte = "This portal is very special, it leads to an exact place in the past... But we are not able to keep it opened forever, hurry up!"; break;
        case 983: texte = "You got the ocarina? Then we completed the mission our ancestors entrusted us with..."; break;
        case 984: texte = "The portal is finally opened... Hurry Link, you've got to take the ocarina back!"; break;
        case 985: texte = "The Ocarina of Time..."; break;
        case 986: texte = "Go to the Temple of Time, fulfil your destiny!"; break;
        case 987: texte = "When we are all together with the key of Time, we'll open the portal..."; break;
        case 988: texte = "You succeeded... We close the portal now..."; break;
        case 989: texte = "You got a gauge!*...*Awesome..."; break;
        case 990: texte = "Okay I have enough gold, go away."; break;
        case 991: texte = "Gimme 100 Gold Ganon right away if you want a reward, ok ?*              YES ?            no  "; break;
        case 992: texte = "Gimme 100 Gold Ganon right away if you want a reward, ok ?*              yes              NO ?"; break;
        case 993: texte = "You're making me lose my time, sheesh!"; break;
        case 994: texte = "I will increase the number of arrows you can carry with you.*Say thank you !"; break;
        case 995: texte = "I will increase the number of bombs you can carry with you.*I'm too kind with children..."; break;
        case 996: texte = "Give me 999 Gold Ganon if you want a four-star reward, ok?*              YES ?            no  "; break;
        case 997: texte = "Give me 999 Gold Ganon if you want a four-star reward, ok?*              yes              NO ?"; break;
        case 998: texte = "Your account of arrows will now fill up permanently, don't hesitate to shoot anymore."; break;
        case 999: texte = "Your bomb stock restores permanently now, you can blow up freely!"; break;
        case 1000: texte = "Welcome heroe, I will increase your Magic Meter, you may need it."; break;
        case 1001: texte = "Your stock of magic power doubled!"; break;
        case 1002: texte = "Do you want something to drink?"; break;
        case 1003: texte = "According to the gossips, a fairy would hide behind the waterfall...*Absolute poppycock..."; break;
        case 1004: texte = "I'm er... mounting guard in the bar, that's it.*But I would prefer this to be between you and me, ok?"; break;
        case 1005: texte = "Heroe of Hyrule or whatever, don't think you can drink for free."; break;
        case 1006: texte = "It's too risky for you to go in there, you could be seen."; break;
        case 1007: texte = "Choose what you want.*"; break;
        case 1008: texte = "10 arrows for 20 rupees?**              YES ?            no  "; break;
        case 1009: texte = "10 arrows for 20 rupees?**              yes              NO ?"; break;
        case 1010: texte = "5 bombs for 30 rupees?**              YES ?            no  "; break;
        case 1011: texte = "5 bombs for 30 rupees?**              yes              NO ?"; break;
        case 1012: texte = "You need a bag of bomb to buy this."; break;
        case 1013: texte = "You need a bow to buy this."; break;
        case 1014: texte = "You don't need this."; break;
        case 1015: texte = "Thank you."; break;
        case 1016: texte = "A heart for 5 rupees?**              YES ?            no  "; break;
        case 1017: texte = "A heart for 5 rupees?**              yes              NO ?"; break;
        case 1018: texte = "A little magic jar for 15 rupees?**              YES ?            no  "; break;
        case 1019: texte = "A little magic jar for 15 rupees?**              yes              NO ?"; break;
        case 1020: texte = "A big magic jar for 25 rupees?**              YES ?            no  "; break;
        case 1021: texte = "A big magic jar for 25 rupees?**              yes              NO ?"; break;
        case 1022: texte = "I've just arrived in the city, I'm not open yet, come back later."; break;
        case 1023: texte = "If I have a frosty rock?*Yes, that's right."; break;
        case 1024: texte = "I thought no one had power gems, so I wasn't sure whether to open my shop or not, but you helped me decide."; break;
        case 1025: texte = "At your next visit I will be open, you will be able to buy extremly rare items for power gems."; break;
        case 1026: texte = "I let you have it for 30 power gems, ok?**              YES ?            no  "; break;
        case 1027: texte = "I let you have it for 30 power gems, ok?**              yes              NO ?"; break;
        case 1028: texte = "You don't have enough gems.*Look better, they can be found anywhere."; break;
        case 1029: texte = "This detector will help you know whether you have all the power gems in the area you are or not. An essential tool for someone looking for all the gems, it's yours for 20 power gems!"; break;
        case 1030: texte = "The detector for 20 power gems, ok?**              YES ?            no  "; break;
        case 1031: texte = "The detector for 20 power gems, ok?**              yes              NO ?"; break;
        case 1032: texte = "You got the detector!*When you press ¾3, the number of gems in you possession is written in green if you have all the gems of the area."; break;
        case 1033: texte = "You got the detector!*When you press enter, the number of gems in you possession is written in green if you have all the gems of the area."; break;
        case 1034: texte = "An empty bottle for 10 power gems?**              YES ?            no  "; break;
        case 1035: texte = "An empty bottle for 10 power gems?**              yes              NO ?"; break;
        case 1036: texte = "You got a bottle!*You can fill it with potions!"; break;
        case 1037: texte = "An empty bottle for 20 power gems?**              YES ?            no  "; break;
        case 1038: texte = "An empty bottle for 20 power gems?**              yes              NO ?"; break;
        case 1039: texte = "An improvment of your strength for 20 power gems? *              YES ?            no  "; break;
        case 1040: texte = "An improvment of your strength for 20 power gems? *              yes              NO ?"; break;
        case 1041: texte = "Your strength increases by one point!"; break;
        case 1042: texte = "An improvment of your strength for 40 power gems? *              YES ?            no  "; break;
        case 1043: texte = "An improvment of your strength for 40 power gems? *              yes              NO ?"; break;
        case 1044: texte = "An improvment of your defense for 20 power gems? *              YES ?            no  "; break;
        case 1045: texte = "An improvment of your defense for 20 power gems? *              yes              NO ?"; break;
        case 1046: texte = "Your defense increases by one point!"; break;
        case 1047: texte = "An improvment of your defense for 40 power gems? *              YES ?            no  "; break;
        case 1048: texte = "An improvment of your defense for 40 power gems? *              yes              NO ?"; break;
        case 1049: texte = "Mmm... my stock is empty..."; break;
        case 1050: texte = "I guess you've found all the power gems, it's incredible..."; break;
        case 1051: texte = "According to an old legend, when all the power gems are found, a temple hidding a fabulous treasure will open...*We just have to wait..."; break;
        case 1052: texte = "Come back when you have an empty bottle and I will sell you my potions."; break;
        case 1053: texte = "Red potions restore your energy and green potions restore your magic."; break;
        case 1054: texte = "Which one would you like?*                ? RED POTION ?*                  green potion  *                      no one      "; break;
        case 1055: texte = "Which one would you like?*                  red potion  *                ? GREEN POTION ?*                      no one      "; break;
        case 1056: texte = "Which one would you like?*                  red potion  *                  green potion  *                ?     NO ONE     ?"; break;
        case 1057: texte = "A red potion for 60 rupees?**              YES ?            no  "; break;
        case 1058: texte = "A red potion for 60 rupees?**              yes              NO ?"; break;
        case 1059: texte = "A green potion for 40 rupees?**              YES ?            no  "; break;
        case 1060: texte = "A green potion for 40 rupees?**              yes              NO ?"; break;
        case 1061: texte = "You got a red potion!!!**Drink it to restore all your energy!!!"; break;
        case 1062: texte = "You got a green potion!!!**Drink it to restore all your magic!!!"; break;
        case 1063: texte = "You got a blue potion!!!**Drink it to restore your energy and your magic!!!"; break;
        case 1064: texte = "You don't need to drink this potion now."; break;
        case 1065: texte = "                 Already tired?                  ?                 CONTINUE                 ?                   Save and quit                               Quit without saving            "; break;
        case 1066: texte = "                 Already tired?                                    Continue                     ?               SAVE AND QUIT              ?                Quit without saving            "; break;
        case 1067: texte = "                 Already tired?                                    Continue                                     Save and quit                  ?            QUIT WITHOUT SAVING           ?"; break;
        case 1068: texte = "I am the unluckiest man of the country, nothing good ever happen to me..."; break;
        case 1069: texte = "Is this a lucky charm you have?*Give it to me!*Nobody in the world need it more than me!"; break;
        case 1070: texte = "This horseshoe for... nothing, ok?**              YES ?            no  "; break;
        case 1071: texte = "This horseshoe for... nothing, ok?**              yes              NO ?"; break;
        case 1072: texte = "Thank you so much! Maybe I will be lucky now!"; break;
        case 1073: texte = "I'm sorry my friend, but I have nothing to give you in return, unlucky for you."; break;
        case 1074: texte = "... *How unlucky I am..."; break;
        case 1075: texte = "You traded the horseshoe for... his gratitude?"; break;
        case 1076: texte = "In the end I'm a lucky devil."; break;
        case 1077: texte = "I don't have price to put in game anymore, sorry."; break;
        case 1078: texte = "There are "; break;
        case 1079: texte = " prices in these 9 chests, do you want to try your luck for "; break;
        case 1080: texte = " rupees ?*You can open only one chest, ok?*              YES ?            no  "; break;
        case 1081: texte = "There are "; break;
        case 1082: texte = " prices in these 9 chests, do you want to try your luck for "; break;
        case 1083: texte = " rupees ?*You can open only one chest, ok?*              yes              NO ?"; break;
        case 1084: texte = "Choose a chest."; break;
        case 1085: texte = "Hey! You gotta pay to open one of my chests!!!"; break;
        case 1086: texte = "You lose! This chest is empty."; break;
        case 1087: texte = "Good morning Link, you want to cross the bridge to go to the temple?"; break;
        case 1088: texte = "Usually I would just have to turn this lever, but I played with it all last night and well... it brokes."; break;
        case 1089: texte = "I even tought about putting wooden planks to allow the path, but someone stole them during the night..."; break;
        case 1090: texte = "I could fix the lever, but I need a replacement part, and I can't leave my post..."; break;
        case 1091: texte = "I need a cogwheel, they can be found at the marketplace of Hyrule City."; break;
        case 1092: texte = "You know how it works, don't you? Each stallholder offers some products for others, you've got to gather what they want in order to get what you want."; break;
        case 1093: texte = "I will give you the merchandises I already have.*If you want to see what you have in you bag, press ¾7."; break;
        case 1094: texte = "I will give you the merchandises I already have.*If you want to see what you have in you bag, press I."; break;
        case 1095: texte = "I need a cogwheel to fix that lever.*Go find one at the marketplace of Hyrule city if you want to cross the bridge."; break;
        case 1096: texte = "You brought me a cogwheel?*Very well, now it should work."; break;
        case 1097: texte = "The lever is broken again...*At least now the bridge is out...*It will teach me to build exotic bridge"; break;
        case 1098: texte = "A blue potion for 160 rupees?*You will like it...*              YES ?            no  "; break;
        case 1099: texte = "A blue potion for 160 rupees?*You will like it...*              yes              NO ?"; break;
        case 1100: texte = "I'm fond of every thing green and shiny!"; break;
        case 1101: texte = "Don't worry, I'm not going to steal your rupees... *I'm trying to quit."; break;
        case 1102: texte = "It's really beautiful what you have here... *Love it!*I trade it for a chart of an... INESTIMABLE value!"; break;
        case 1103: texte = "This green gemstone for a map, ok?**              YES ?            no  "; break;
        case 1104: texte = "This green gemstone for a map, ok?**              yes              NO ?"; break;
        case 1105: texte = "Thank youuuu!!! Here is your chart, now get lost!"; break;
        case 1106: texte = "Very well... *Watch out for your rupees then!"; break;
        case 1107: texte = "You traded the gemstone for a map!"; break;
        case 1108: texte = "You came to give me some rupees?*How nice of you!"; break;
        case 1109: texte = "The princess wants me to warn her if anything strange happen on the town..."; break;
        case 1110: texte = "This morning I saw a seagull flying strangely... I'm not sure whether I've got to tell her or not..."; break;
        case 1111: texte = "Hello Link, welcome at the fishing stand!"; break;
        case 1112: texte = "To unveil the opening of my stand, I'm organizing a great fishing contest!*You've probably heard about it, all the city participates!"; break;
        case 1113: texte = "To win the contest and the special price, you've got to be the first one to hook 5 different types of fish."; break;
        case 1114: texte = "Do you want to try? The registration fee is 10 Rupees, ok?*              YES ?            no  "; break;
        case 1115: texte = "Do you want to try? The registration fee is 10 Rupees, ok?*              yes              NO ?"; break;
        case 1116: texte = "Excellent, here is a fishing rod, come back when you've caught 5 different types of fish."; break;
        case 1117: texte = "Mmm... Do you want to participate for 5 Rupees? *              YES ?            no  "; break;
        case 1118: texte = "Mmm... Do you want to participate for 5 Rupees? *              yes              NO ?"; break;
        case 1119: texte = "Very well, here is a fishing rod, come back when you've caught 5 different types of fish."; break;
        case 1120: texte = "And for 2 Rupees?**              YES ?            no  "; break;
        case 1121: texte = "And for 2 Rupees?**              yes              NO ?"; break;
        case 1122: texte = "Well, here is a fishing rod, come back when you've caught 5 different types of fish."; break;
        case 1123: texte = "For 1 Rupees ?**              YES ?            no  "; break;
        case 1124: texte = "For 1 Rupees ?**              yes              NO ?"; break;
        case 1125: texte = "Ok, here is a fishing rod, come back when you've caught 5 different types of fish."; break;
        case 1126: texte = "Don't tell me you want to participate for free???*               YEAH ?          no  "; break;
        case 1127: texte = "Don't tell me you want to participate for free???*               yeah            NO ?"; break;
        case 1128: texte = "...*Here is a fishing rod, come back when you've caught 5 different types of fish."; break;
        case 1129: texte = "Go away, enemy of fishermen!"; break;
        case 1130: texte = "You got a fishing rod!*Use it on a pontoon, then bring the fish up pressing ¾1 when the line is moving."; break;
        case 1131: texte = "You got a fishing rod!*Use it on a pontoon, then bring the fish up pressing X when the line is moving."; break;
        case 1132: texte = "Still "; break;
        case 1133: texte = " different fish to find, good luck!"; break;
        case 1134: texte = "Just one more fish to find!"; break;
        case 1135: texte = "You have found 5 fish???*You must be super-fisherman!"; break;
        case 1136: texte = "This means the fishing contest is over, and you are the winner!"; break;
        case 1137: texte = "I guess you want your price now...*Well, as a reward for your victory in the fishing contest: *... ... ..."; break;
        case 1138: texte = "I hire you!"; break;
        case 1139: texte = "There are a lot of other types of fish in Hyrule, I want to list them all by area."; break;
        case 1140: texte = "I will reward you each time you bring me 5 new types of fish.*From now on you can consult the list pressing ¾8."; break;
        case 1141: texte = "I will reward you each time you bring me 5 new types of fish.*From now on you can consult the list pressing L."; break;
        case 1142: texte = "With your current fishing rod, you will unfortunately be able to catch only little fish..."; break;
        case 1143: texte = "Be sure to go fishing every where!*Each fish caught give you some energy, did you notice?"; break;
        case 1144: texte = "Bring me "; break;
        case 1145: texte = " new types of fish for the next reward!"; break;
        case 1146: texte = "Here is your reward for the 10 different types of fish you found:"; break;
        case 1147: texte = "You got a better fishing rod!!!*You'll be able to catch fish of regular size."; break;
        case 1148: texte = "Bring me "; break;
        case 1149: texte = " new types of fish for the next reward!"; break;
        case 1150: texte = "Here is your reward for the 15 different types of fish you found:"; break;
        case 1151: texte = "Bring me "; break;
        case 1152: texte = " new types of fish for the next reward!"; break;
        case 1153: texte = "Here is your reward for the 20 different types of fish you found:"; break;
        case 1154: texte = "You got the better fishing rod!!!*You will be able to catch gigantic fish!"; break;
        case 1155: texte = "Bring me "; break;
        case 1156: texte = " new types of fish for the next reward!"; break;
        case 1157: texte = "Here is your reward for the 25 different types of fish you found:"; break;
        case 1158: texte = "Bring me "; break;
        case 1159: texte = " new types of fish for the next reward!"; break;
        case 1160: texte = "Here is your reward for having found all the different types of fish in Hyrule:"; break;
        case 1161: texte = "YOU ARE FIRED!!!!"; break;
        case 1162: texte = "Finally, all the fish existing in Hyrule are listed, my fisherman guidebook is finished..."; break;
        case 1163: texte = "Good morning Link.*I am the mayor, welcome in the Mabe Village."; break;
        case 1164: texte = "At this time a fishing contest is organized on the town, everybody speaks about nothing but this... *Is that why you came?"; break;
        case 1165: texte = "The fishing contest being over, Mabe Village returns to its usual calmness."; break;
        case 1166: texte = "I am the legendary fisherman!*I like the blue and shiny of the ocean..."; break;
        case 1167: texte = "Why I didn't win the fishing contest?*Well... I'm not interested in that kind of thing.... That's why."; break;
        case 1168: texte = "A blue and shiny gemstone?*I need it!*I trade it for the last thing I hooked!"; break;
        case 1169: texte = "The blue gemstone for his fishing, ok ?**              YES ?            no  "; break;
        case 1170: texte = "The blue gemstone for his fishing, ok ?**              yes              NO ?"; break;
        case 1171: texte = "He-he! You drive a bargain kid."; break;
        case 1172: texte = "This boot was full of wales when I found it, unusual isn't it?"; break;
        case 1173: texte = "You are too nice, but don't worry about me, don't be afraid of defrauding me."; break;
        case 1174: texte = "You traded the blue gemstone for an old boot!*Way to go..."; break;
        case 1175: texte = "If you ever find new blue gemstones, it will be a pleasure to do a deal with you!"; break;
        case 1176: texte = "These days, young men never listen to their elder's advice...*I think this fishing contest will last..."; break;
        case 1177: texte = "Formerly I was a famous fisherman, do you want me to give you some hints?"; break;
        case 1178: texte = "ABOUT THE TYPES OF FISH          ?*About the areas of fishing        *About the bonus                   *Nothing at all                    "; break;
        case 1179: texte = "About the types of fish           *ABOUT THE AREAS OF FISHING       ?*About the bonus                   *Nothing at all                    "; break;
        case 1180: texte = "About the types of fish           *About the areas of fishing        *ABOUT THE BOUNS                  ?*Nothing at all                    "; break;
        case 1181: texte = "About the types of fish           *About the areas of fishing        *About the bonus                   *NOTHING AT ALL                   ?"; break;
        case 1182: texte = "They say that waters in Hyrule provide a habitat for no less than 30 types of fish, but they all have their own area, you will not find them all at the same place."; break;
        case 1183: texte = "There are in Hyrule a lot of spot to fish, but only 6 distinct areas. To find new fish you will have to go fishing in other places."; break;
        case 1184: texte = "If you find a fish already hooked somewhere else, this means you are in the same fishing area."; break;
        case 1185: texte = "Fishing is not only for fun, a fish hooked will give you energy. The quantity of life earned depends of the fish."; break;
        case 1186: texte = "Tsss... youth these days..."; break;
        case 1187: texte = "I spent hours fishing in the lake and could only find 3 different types of fish..."; break;
        case 1188: texte = "We had to go fishing at different places to find more than 3 fish?*If I had known..."; break;
        case 1189: texte = "Do you want something to drink?"; break;
        case 1190: texte = "You need help from the drunk guy there? *Unfortunately for you I can't let him go if he doesn't pay."; break;
        case 1191: texte = "You want to pay it off? It's 10 000 Rupees, ok? *              YES ?            no  "; break;
        case 1192: texte = "You want to pay it off? It's 10 000 Rupees, ok? *              yes              NO ?"; break;
        case 1193: texte = "Of course..."; break;
        case 1194: texte = "Okay, I got another idea: usually I use a frosty rock to prepare my fresh drinks, but I just finished the last one I heritated from my ancestors..."; break;
        case 1195: texte = "If you bring me a new frosty rock, I will consider his debt payed."; break;
        case 1196: texte = "So, you can't find a frosty rock?"; break;
        case 1197: texte = "You got a frosty rock? Impressive..."; break;
        case 1198: texte = "You give me this frosty rock and I'll forget his debt, ok?*              YES ?            no  "; break;
        case 1199: texte = "You give me this frosty rock and I'll forget his debt, ok?*              yes              NO ?"; break;
        case 1200: texte = "I understand, after all it's nothing of your business."; break;
        case 1201: texte = "Thank you!*As promised, the old man can go, he doesn't owe me anything more."; break;
        case 1202: texte = "Let me drink alone! -hiccups- !"; break;
        case 1203: texte = "You went to the mine?*I used to work there...*But because monsters appeared in, the mine is temporarly closed..."; break;
        case 1204: texte = "I would like to help you cross the mine, but the barman doesn't want to let me go if I don't pay. Yet I don't have money anymore, so I can't leave, and I drink to spend the time."; break;
        case 1205: texte = "Someone should really pay off my debt for me... ...* -hiccup- !"; break;
        case 1206: texte = "You want to know where to find a frosty rock? *Mmm... I heard that a guy arrived in Hyrule City lately, and he is about to open a shop of a new kind..."; break;
        case 1207: texte = "Well, I think this guy has got a frosty rock."; break;
        case 1208: texte = "Go and see the guy in the strange shop at Hyrule City, he should have a frosty rock."; break;
        case 1209: texte = "You got a frosty rock???*Give it to the barman, I promise I will help you with the mine!"; break;
        case 1210: texte = "I'm free now... I tought I would have to do the dishes for the rest of the week!*Thank you Link!"; break;
        case 1211: texte = "You can go to the mine, I'll meet you there.** -hiccup- !"; break;
        case 1212: texte = "Welcome in the saloon, make yourself at home Link!"; break;
        case 1213: texte = "While the mine up north is closed, I don't have anything to do but spending my time here..."; break;
        case 1214: texte = "Almost all the men in the village work in the mine north of the village."; break;
        case 1215: texte = "This morning monsters appeared inside so the mine had to close."; break;
        case 1216: texte = "Rice, spices and olives are the basis of the barter in Hyrule, you should always have some with you."; break;
        case 1217: texte = "I am the head of the mine, and the most powerful man in the village, so don't try to look down upon me, boy."; break;
        case 1218: texte = "I am the chief of the village... But actually the chief of the mine is much more influent than me, he hired almost all the village's men."; break;
        case 1219: texte = "The bank is under our surveillance. Nothing to report."; break;
        case 1220: texte = "Welcome in the Hyrule bank. I am specialized in currencies."; break;
        case 1221: texte = "You have nothing interesting, come back if you find gold, I'll give you a good price for it."; break;
        case 1222: texte = "You have some gold coins? With the face of a monster on it... Gold Ganon you say?"; break;
        case 1223: texte = "It's really ugly, but the gold is reusable, let's see..."; break;
        case 1224: texte = " Gold Ganon for "; break;
        case 1225: texte = " Rupees, ok?**              YES ?            no  "; break;
        case 1226: texte = " Gold Ganon for "; break;
        case 1227: texte = " Rupees, ok?**              yes              NO ?"; break;
        case 1228: texte = "Your wallet is full, come back later, I'll buy all that off you."; break;
        case 1229: texte = "It's a deal!"; break;
        case 1230: texte = "You have Gold Coins? I tought this currency didn't exist anymore..."; break;
        case 1231: texte = "I'll give you a good price, let's see..."; break;
        case 1232: texte = " Gold Coins for "; break;
        case 1233: texte = " Rupees, ok?**              YES ?            no  "; break;
        case 1234: texte = " Gold Coins for "; break;
        case 1235: texte = " Rupees, ok?**              yes              NO ?"; break;
        case 1236: texte = "It's a deal!"; break;
        case 1237: texte = "What do you want to sell me?*   - GOLD COINS ?*   - Gold Ganon  *   - Nothing  "; break;
        case 1238: texte = "What do you want to sell me?*   - Gold Coins  *   - GOLD GANON ?*   - Nothing  "; break;
        case 1239: texte = "What do you want to sell me?*   - Gold Coins  *   - Gold Ganon  *   - NOTHING ?"; break;
        case 1240: texte = "I'm here to build a bridge northerly. I'm sure it would be useful some day."; break;
        case 1241: texte = "The problem is... I don't have tools...*What should I do?"; break;
        case 1242: texte = "This hammer looks good...*It could really help me, will you give it to me for a legendary treasure I found when i was an explorer?"; break;
        case 1243: texte = "This hammer for a legendary treasure, ok?**              YES ?            no  "; break;
        case 1244: texte = "This hammer for a legendary treasure, ok?**              yes              NO ?"; break;
        case 1245: texte = "Thank you, you can have this:"; break;
        case 1246: texte = "I think I'll never finish this bridge..."; break;
        case 1247: texte = "You got the Fire Arrows!*These burning arrows use magic and release an incredible power!"; break;
        case 1248: texte = "Looks like I finally got all I need...*I get myself motivated, and I do it!"; break;
        case 1249: texte = "Is that a bridge plan?*I really need that, will you give it to me for a legendary treasure I found when I was an explorer?"; break;
        case 1250: texte = "This plan for a legendary treasure, ok?**              YES ?            no  "; break;
        case 1251: texte = "This plan for a legendary treasure, ok?**              yes              NO ?"; break;
        case 1252: texte = "Thank you, take this gift in return:"; break;
        case 1253: texte = "You got the Ice Arrows!*These freezing arrows use magic and release an incredible power!"; break;
        case 1254: texte = "You've got a saw?*I can't make a bridge without it, will you give it to me for a legendary treasure I found when I was an explorer?"; break;
        case 1255: texte = "This saw for a legendary treasure, ok?**              YES ?            no  "; break;
        case 1256: texte = "This saw for a legendary treasure, ok?**              yes              NO ?"; break;
        case 1257: texte = "Thank you, take this in exchange:"; break;
        case 1258: texte = "You got the Light Arrows!*These arrows use a lot of magic and release an ultimate power!"; break;
        case 1259: texte = "You've got a nail?*I guess it may help, will you give it to me for a bauble?"; break;
        case 1260: texte = "This nail for a bauble, ok?**              YES ?            no  "; break;
        case 1261: texte = "This nail for a bauble, ok?**              yes              NO ?"; break;
        case 1262: texte = "Thank you, I give you that in return:"; break;
        case 1263: texte = "Hello Link, do you remember me?"; break;
        case 1264: texte = "Monsters appeared in Hyrule today, so once again I'll try to list them all, and once again I count on your help."; break;
        case 1265: texte = "Pressing ¾6, you can see the monsters already listed. You just have to kill a monster to add it."; break;
        case 1266: texte = "Pressing M, you can see the monsters already listed. You just have to kill a monster to add it."; break;
        case 1267: texte = "10 Gold Coins"; break;
        case 1268: texte = "40 Rupees"; break;
        case 1269: texte = "20 Gold Ganon"; break;
        case 1270: texte = "I'll owe you "; break;
        case 1271: texte = " for each new monster. Come and see me when you have some time to get your money."; break;
        case 1272: texte = " Gold Coins"; break;
        case 1273: texte = " Rupees"; break;
        case 1274: texte = " Gold Ganon"; break;
        case 1275: texte = "I owe you "; break;
        case 1276: texte = ", do you want to be paid now?*              YES ?            no  "; break;
        case 1277: texte = " Gold Coins"; break;
        case 1278: texte = " Rupees"; break;
        case 1279: texte = " Gold Ganon"; break;
        case 1280: texte = "I owe you "; break;
        case 1281: texte = ", do you want to be paid now?*              yes              NO ?"; break;
        case 1282: texte = "Your account is at 0, I gave you everything."; break;
        case 1283: texte = "Welcome in the Hyrule Bank. I am specialized in currencies."; break;
        case 1284: texte = "You don't have anything interesting, come back if you find some gold or rupees, I'll give you a good price."; break;
        case 1285: texte = "You have some rupees? We haven't used them for ages, but they are still very valuable..."; break;
        case 1286: texte = "Let's see..."; break;
        case 1287: texte = " Rupees for "; break;
        case 1288: texte = " Gold Ganon, ok?**              YES ?            no  "; break;
        case 1289: texte = " Rupees for "; break;
        case 1290: texte = " Gold Ganon, ok?**              yes              NO ?"; break;
        case 1291: texte = "It's a deal!"; break;
        case 1292: texte = "You possess Gold Coins? It's unbelievable that you could find such an ancient money!"; break;
        case 1293: texte = "They contain a lot of gold... *Let's see..."; break;
        case 1294: texte = " Gold Coins for "; break;
        case 1295: texte = " Gold Ganon, ok?**              YES ?            no  "; break;
        case 1296: texte = " Gold Coins for "; break;
        case 1297: texte = " Gold Ganon, ok?**              yes              NO ?"; break;
        case 1298: texte = "It's a deal!"; break;
        case 1299: texte = "What do you want to sell me?*   - GOLD COINS ?*   - Rupees  *   - Nothing  "; break;
        case 1300: texte = "What do you want to sell me?*   - Gold Coins  *   - RUPEES ?*   - Nothing  "; break;
        case 1301: texte = "What do you want to sell me?*   - Gold Coins  *   - Rupees  *   - NOTHING ?"; break;
        case 1302: texte = "It's been a long time since I had so much fun!"; break;
        case 1303: texte = "One of my ancestors wanted to build a bridge, but in the end he just made the plan..."; break;
        case 1304: texte = "I'm from a lineage of incapables, no wonder I suck in every thing I do... On top of that I'm sick, and no one loves me..."; break;
        case 1305: texte = "You have a rope?*Give it to me please, I will give you the heritage of my family, I don't have any descendants anyway..."; break;
        case 1306: texte = "This rope for his heritage, ok?**              YES ?            no  "; break;
        case 1307: texte = "This rope for his heritage, ok?**              yes              NO ?"; break;
        case 1308: texte = "Well...*...Thank you man...*..."; break;
        case 1309: texte = "I knew that, nobody have never given anything anyway..."; break;
        case 1310: texte = "You traded the rope for a bridge's plan."; break;
        case 1311: texte = "...*I would like to be alone just a moment..."; break;
        case 1312: texte = "Good day, you must be Link, I was waiting for you."; break;
        case 1313: texte = "I'm a descendant of the 7 Wise Men. Chased by Ganon's minions, I had to run away and hide here."; break;
        case 1314: texte = "Seeing you here brings hope, I will go in the portal's cave.*Take this, I think it might help you."; break;
        case 1315: texte = "You got a pepper!"; break;
        case 1316: texte = "Good luck Link!"; break;
        case 1317: texte = "Welcome Link, I was waiting for you..."; break;
        case 1318: texte = "I guess you have a lot of questions, allow me to answer you."; break;
        case 1319: texte = "We are in Hyrule, but in a time that is nothing for you but a sad future...*The portal you took allowed you to come here and now, to be the witness of these sad days..."; break;
        case 1320: texte = "You want to know what happened? Ganon attacked the castle, stronger than ever, and you were defeated."; break;
        case 1321: texte = "Before her execution, princess Zelda managed to send her plan to the wise men. She thought the theft of the Ocarina was the turning point of the war, so she ordered that the descendants of the 7 wise men give you the Ocarina back whenever you would arrive by the portal."; break;
        case 1322: texte = "Since you are here, in front of me, this means the day has finally arrived.*However... the ocarina was never found."; break;
        case 1323: texte = "So we drew up another plan. We are going to send you in the past, the night when the ocarina was stolen, and you will catch the thief red-handed."; break;
        case 1324: texte = "Now, we are only 3 descendants remaining, search and find the two others as well as the Key of Time, and we'll open the portal."; break;
        case 1325: texte = "Take this, it will help you in your researches:"; break;
        case 1326: texte = "You got the hookshot!*Use it to jump over ditches!"; break;
        case 1327: texte = "One of them is hidden in a temple, in the middle of the lake."; break;
        case 1328: texte = "The last wise man is hidden nearby the waterfalls."; break;
        case 1329: texte = "The key of time was placed in the Grand Pyramid."; break;
        case 1330: texte = "The wise men are in the cave, the key of time in your possession...*Very well, meet us at the portal's cave, time has come."; break;
        case 1331: texte = "In the Temple of Time is hidden a song that, played with the ocarina, will bring you back at your time."; break;
        case 1332: texte = "Good luck Link, we are all counting on you."; break;
        case 1333: texte = "10 arrows for 10 Gold Ganon?**              YES ?            no  "; break;
        case 1334: texte = "10 arrows for 10 Gold Ganon?**              yes              NO ?"; break;
        case 1335: texte = "5 bombs for 15 Gold Ganon?**              YES ?            no  "; break;
        case 1336: texte = "5 bombs for 15 Gold Ganon?**              yes              NO ?"; break;
        case 1337: texte = "One heart for 4 Gold Ganon?**              YES ?            no  "; break;
        case 1338: texte = "One heart for 4 Gold Ganon?**              yes              NO ?"; break;
        case 1339: texte = "A little magic jar for 8 Gold Ganon?**              YES ?            no  "; break;
        case 1340: texte = "A little magic jar for 8 Gold Ganon?**              yes              NO ?"; break;
        case 1341: texte = "A big magic jar for 16 Gold Ganon? *              YES ?            no  "; break;
        case 1342: texte = "A big magic jar for 16 Gold Ganon? *              yes              NO ?"; break;
        case 1343: texte = "One second is one drip of the coffee pot. Let's hurry it up."; break;
        case 1344: texte = "You want to work for me? The true measure of a man is in the amount of work he does. That's what I always say."; break;
        case 1345: texte = "Run on the moving walkway to charge the dynamo, then stand on the button. This will start up the drip coffee maker. Then come to me to receive your money."; break;
        case 1346: texte = "I don't ask you if you're ready, preparation is the last refuge of the weak.."; break;
        case 1347: texte = "I never drink more than 17 cups of coffee during a day.*But the first one is always the best."; break;
        case 1348: texte = "Blacker than a moonless night, hotter and more bitter than Hell itself... *That is coffee."; break;
        case 1349: texte = "Obviously, we'll take another."; break;
        case 1350: texte = "By the way, I wouldn't put salt in my coffee. The two don't go well, after all."; break;
        case 1351: texte = "This coffee here... It's my own special blend. I call it Godot 107. I'm trying to decide wheter to cut down on the acidity or the bitterness...*That's the only thing I've got on my mind right now..."; break;
        case 1352: texte = "Ha... !*My 6th cup of coffee is staring up at me coldly."; break;
        case 1353: texte = "Godot Blend 102...*... My personal favorite."; break;
        case 1354: texte = "Ha... ! This blend...*Godot Blend 107...*I've decided... It's a little too bitter after all!"; break;
        case 1355: texte = "...*Aaah, bitter!"; break;
        case 1356: texte = "The weak get washed away by the tides of fate, The strong drink it up.*Ha... !*It's bitter today, too... Just like my destiny."; break;
        case 1357: texte = "...My 11th cup.*I've promised to drink no more than 17 during a day. Which means I'm still good 'til the last drop."; break;
        case 1358: texte = "A single drop of milk is all it takes to destroy the pure black magic in the cup!"; break;
        case 1359: texte = "... What bitterness.*You will learn to appreciate the bitterness when you're older."; break;
        case 1360: texte = "You know what my golden rule is?*Chuck out a bad cup of coffee. *You can always get another."; break;
        case 1361: texte = "Ha... !*Then I'd say that gives me time... to enjoy another cup of pure black magic!"; break;
        case 1362: texte = "Two minutes isn't even enough time to brew a good cup o' Joe..."; break;
        case 1363: texte = "...Cup number 17. The last cup.*It seems like the time has come to put an end to this deal."; break;
        case 1364: texte = "I drank my 17 cups, this is a reward"; break;
        case 1365: texte = "You still need money? Here's..."; break;
        case 1366: texte = "Red potions restore your energy and green potions restore your magic."; break;
        case 1367: texte = "Which one do you want?*                ? RED POTION ?*                  green potion  *                      no one      "; break;
        case 1368: texte = "Which one do you want?*                  red potion  *                ? GREEN POTION ?*                      no one      "; break;
        case 1369: texte = "Which one do you want?*                  red potion  *                  green potion  *                ?     NOTHING     ?"; break;
        case 1370: texte = "A red potion for 40 Gold Ganon?**              YES ?            no  "; break;
        case 1371: texte = "A red potion for 40 Gold Ganon?**              yes              NO ?"; break;
        case 1372: texte = "A green potion for 25 Gold Ganon?**              YES ?            no  "; break;
        case 1373: texte = "A green potion for 25 Gold Ganon?**              yes              NO ?"; break;
        case 1374: texte = "My family only knew misfortune for centuries... Even if I would like to help, I have nothing for you."; break;
        case 1375: texte = "I am the most lucky man in the country."; break;
        case 1376: texte = "You don't believe me?*Take this treasure I found this morning wandering around, I will probably find another one tomorrow!"; break;
        case 1377: texte = "You got a precious jewel!"; break;
        case 1378: texte = "How strange, giving you this jewel makes me feel like I've settled an old familial debt..."; break;
        case 1379: texte = "I am the best pastry chef of the country."; break;
        case 1380: texte = "Unfortunately, I have nothing in stock, you can't find anything sweet around here..."; break;
        case 1381: texte = "You have marmelade???*I thought the last ones were out-of-date since centuries! Give it to me, for my special breakfast stock!"; break;
        case 1382: texte = "This marmelade for his stock, ok?**              YES ?            no  "; break;
        case 1383: texte = "This marmelade for his stock, ok?**              yes              NO ?"; break;
        case 1384: texte = "I will have my best breakfast since ages!*Here is what I had put aside:"; break;
        case 1385: texte = "In that case why did you display it? *Show off..."; break;
        case 1386: texte = "You traded the marmelade for a croissant."; break;
        case 1387: texte = "Sooner or later, I guess I will have to find a new job..."; break;
        case 1388: texte = "You look even more broke than I am...*You should go to see the guy in the coffe house, he looks for an employee."; break;
        case 1389: texte = "Also, take this, you'll need it:"; break;
        case 1390: texte = "You got a wallet able to hold up to 99 Gold Ganon!"; break;
        case 1391: texte = "So, how goes your money?"; break;
        case 1392: texte = "Welcome in the Hyrule Bank. I am specialized in currencies."; break;
        case 1393: texte = "You don't have anything interesting, come back if you find precious currencies, I will give you a good price."; break;
        case 1394: texte = "These are rupees you say? Pretty curious."; break;
        case 1395: texte = "It seems to be precious, let's see..."; break;
        case 1396: texte = " Rupees for "; break;
        case 1397: texte = " Gold Coins, ok?**              YES ?            no  "; break;
        case 1398: texte = " Rupees for "; break;
        case 1399: texte = " Gold Coins, ok?**              yes              NO ?"; break;
        case 1400: texte = "It's a deal!"; break;
        case 1401: texte = "You have gold? With a monster head on it... You call that Gold Ganon?"; break;
        case 1402: texte = "It's really ugly, but the gold is reusable, let's see..."; break;
        case 1403: texte = " Gold Ganon for "; break;
        case 1404: texte = " Gold Coins, ok?**              YES ?            no  "; break;
        case 1405: texte = " Gold Ganon for "; break;
        case 1406: texte = " Gold Coins, ok?**              yes              NO ?"; break;
        case 1407: texte = "It's a deal!"; break;
        case 1408: texte = "What do you want to sell me?*   - RUPEES ?*   - Gold Ganon  *   - Nothing  "; break;
        case 1409: texte = "What do you want to sell me?*   - Rupees  *   - GOLD GANON ?*   - Nothing  "; break;
        case 1410: texte = "What do you want to sell me?*   - Rupees  *   - Gold Ganon  *   - NOTHING ?"; break;
        case 1411: texte = "Hello Link, I was waiting for you."; break;
        case 1412: texte = "I am the leader of the 7 Wise Men, and also the most powerful of them. I saw you in my dreams, as well as a very sad future..."; break;
        case 1413: texte = "Your presence here seems to show that I was successful... At least partially..."; break;
        case 1414: texte = "I was the one who created the portal to the future, for you to be the witness of my visions."; break;
        case 1415: texte = "I also built the Temple of Time with the others wise men, so that you would travel as you wish across the times."; break;
        case 1416: texte = "From now on it's up to you. You have to find the 7 magic crystals that will open the way to the legendary Goddesses Temple, and be the first to find and take the Triforce!"; break;
        case 1417: texte = "Shall his path lead the true heroe to the Triforce."; break;
        case 1418: texte = "Don't judge me on my size, I am a first-class blacksmith!"; break;
        case 1419: texte = "But I got admit, I happen to have just arrived here, and I couldn't move all my forge here... So I don't have anything."; break;
        case 1420: texte = "You've carried an anvil with you???*What are you, stupid?"; break;
        case 1421: texte = "I can get you rid of it if you want, I need one. *I would even give you a little reward for your trouble."; break;
        case 1422: texte = "This anvil for a reward, ok?**              YES ?            no  "; break;
        case 1423: texte = "This anvil for a reward, ok?**              yes              NO ?"; break;
        case 1424: texte = "Thank you, there, it's a horseshoe I made some time ago:"; break;
        case 1425: texte = "I only said that to help you..."; break;
        case 1426: texte = " You got a horseshoe!"; break;
        case 1427: texte = "With all these things you brought to me, I can open my forge again!"; break;
        case 1428: texte = "It's a good hammer you have here...*It may be useful in my forge... Will you give it to me? I will reward you with one of my creations."; break;
        case 1429: texte = "This hammer for a reward, ok?**              YES ?            no  "; break;
        case 1430: texte = "This hammer for a reward, ok?**              yes              NO ?"; break;
        case 1431: texte = "Thank you, here is one of my most beautiful creations:"; break;
        case 1432: texte = "As if you knew what to do with this hammer..."; break;
        case 1433: texte = "You got a little bell!"; break;
        case 1434: texte = "You have some Gold Dust?*I will need it to forge new wonderful objects, will you give it to me for a wonderful reward?"; break;
        case 1435: texte = "The Gold Dust for a wonderful reward, ok?**              YES ?            no  "; break;
        case 1436: texte = "The Gold Dust for a wonderful reward, ok?**              yes              NO ?"; break;
        case 1437: texte = "Thank you, take this magic mirror in return! *It was bewitched by the wise men and got some mysterious powers..."; break;
        case 1438: texte = "It was areally good reward though..."; break;
        case 1439: texte = "You got the magic mirror!"; break;
        case 1440: texte = "You sword is really impressive... But I think I could improve it..."; break;
        case 1441: texte = "Do you want me to work on your sword?**              YES ?            no  "; break;
        case 1442: texte = "Do you want me to work on your sword?**              yes              NO ?"; break;
        case 1443: texte = "So give me your sword, it won't be long."; break;
        case 1444: texte = "What a pity, your sword really is fascinating..."; break;
        case 1445: texte = "You entrusted the Master Sword."; break;
        case 1446: texte = "It won't be long, don't worry."; break;
        case 1447: texte = "It's done, here is your sword:"; break;
        case 1448: texte = "The Master Sword was reforge! His power is improved!"; break;
        case 1449: texte = "One day, I will forge a sword as beautiful as yours, word of blacksmith!"; break;
        case 1450: texte = "You shouldn't go too far away from the village by this weather..."; break;
        case 1451: texte = "10 arrows for 5 Gold Coins?**              YES ?            no  "; break;
        case 1452: texte = "10 arrows for 5 Gold Coins?**              yes              NO ?"; break;
        case 1453: texte = "5 bombs for 10 Gold Coins?**              YES ?            no  "; break;
        case 1454: texte = "5 bombs for 10 Gold Coins?**              yes              NO ?"; break;
        case 1455: texte = "One heart for 1 Gold Coins?**              YES ?            no  "; break;
        case 1456: texte = "One heart for 1 Gold Coins?**              yes              NO ?"; break;
        case 1457: texte = "A little magic jar for 3 Gold Coins? *              YES ?            no  "; break;
        case 1458: texte = "A little magic jar for 3 Gold Coins? *              yes              NO ?"; break;
        case 1459: texte = "A big magic jar for Gold Coins? *              YES ?            no  "; break;
        case 1460: texte = "A big magic jar for 6 Gold Coins? *              yes              NO ?"; break;
        case 1461: texte = "You find the book of Mudora!*From now on you understand the ancient Hylian!"; break;
        case 1462: texte = "Hello, I am the chief of the village. *Don't listen to the gossips saying that this village is endangered, and enjoy your time with us."; break;
        case 1463: texte = "Looks like it stopped snowing..."; break;
        case 1464: texte = "Red potions restore your energy and green potions restore your magic."; break;
        case 1465: texte = "Wich one do you want?*                ? RED POTION ?*                  green potion  *                      no one      "; break;
        case 1466: texte = "Wich one do you want?*                  red potion  *                ? GREEN POTION ?*                      no one      "; break;
        case 1467: texte = "Wich one do you want?*                  red potion  *                  green potion  *                ?     NO ONE     ?"; break;
        case 1468: texte = "A red potion for 15 Gold Coins?**              YES ?            no  "; break;
        case 1469: texte = "A red potion for 15 Gold Coins?**              yes              NO ?"; break;
        case 1470: texte = "A green potion for 10 Gold Coins?**              YES ?            no  "; break;
        case 1471: texte = "A green potion for 10 Gold Coins?**              yes              NO ?"; break;
        case 1472: texte = "You look pretty moneyless, you don't even have a wallet?*Here, take this one:"; break;
        case 1473: texte = "You've got a wallet able to hold up to 99 Gold Coins!"; break;
        case 1474: texte = "Hello, I am one of the 7 wise men, in passing through this town."; break;
        case 1475: texte = "The book of Mudora was bewitched to enable anyone having it to speak our language."; break;
        case 1476: texte = "You must come from far away if you don't speak our language... Keep this book, it will help you."; break;
        case 1477: texte = "Hi man, the name is Ganondorf, if you hear anything about the magic crystals, you come and speak to me, got it?"; break;
        case 1478: texte = "I am the head of the hylian knights. *If you don't want any trouble behave yourself, follow Ganondorf's example, he is a good guy."; break;
        case 1479: texte = "This Ganondorf keep treating us to drink... *He really is a good fellow..."; break;
        case 1480: texte = "To drink is very well... but when do we eat?"; break;
        case 1481: texte = "Don't tell me... This smell... It's a croissant!*Give it to me, for my endless friendship!"; break;
        case 1482: texte = "This croissant for his friendship, ok?**              YES ?            no  "; break;
        case 1483: texte = "This croissant for his friendship, ok?**              yes              NO ?"; break;
        case 1484: texte = "Thank you!!!*Take this present in return, it's the symbol of our friendship!"; break;
        case 1485: texte = "... You are declaring war to the Hylian Knight???*Are you out of your mind???"; break;
        case 1486: texte = "You traded the croissant for a beer."; break;
        case 1487: texte = "Hi pal!*Will you drink something with us?"; break;
        case 1488: texte = "If you want a hylian knight to disclose a restricted information, you have to treat him a drink. It's our rule."; break;
        case 1489: texte = "You already know all my informations...*Hic!"; break;
        case 1490: texte = "I have a lot of restricted informations known only by ourselves (and by Ganondorf). A glass of beer is 1 Gold Coin, do we have a deal?"; break;
        case 1491: texte = "An information for 1 Gold Coin, ok?**              YES ?            no  "; break;
        case 1492: texte = "An information for 1 Gold Coin, ok?**              yes              NO ?"; break;
        case 1493: texte = "The Hylian Knights were founded in order to protect the temple of the Goddesses... This temple is supposed to hide a powerful relic called the Triforce..."; break;
        case 1494: texte = "To open the way to the temple of the Godesses, you have to go in the Holy Land, North of here, and stand on the Triforce symbol with the 7 crystals in your possession."; break;
        case 1495: texte = "The 7 magic crystals are hidden every where in Hyrule... And, keep this as a secret, one of them is kept by the legendary hylian knights!"; break;
        case 1496: texte = "Our chief chased him downstairs..."; break;
        case 1497: texte = "What a strenght... he beat us so easily..."; break;
        case 1498: texte = "He is... downstairs...*Be careful... ... my friend."; break;
        case 1499: texte = "He is too strong... The chief won't hold out any longer...*Help him, I'm begging you..."; break;
        case 1500: texte = "Someone ... stop him..."; break;
        case 1501: texte = "Do you intend to be on my way too? So en garde!"; break;
        case 1502: texte = "I failed...*Forgive me master..."; break;
        case 1503: texte = "Thank you for your help Link, without you, Ganondorf would have take the crystal..."; break;
        case 1504: texte = "The order of the Hylian Knight was founded to protect the access to the Temple of the Goddesses, it was our mission to keep the crystal safe. Without this one, the 6 others are useless."; break;
        case 1505: texte = "Unfortunately, with time, the order became weak. And today, we failed."; break;
        case 1506: texte = "Keep the crystal, you seem much more trustworthy than we are..."; break;
        case 1507: texte = "As for Ganondorf... We couldn't have guessed he would betray us... He was almost one of us..."; break;
        case 1508: texte = "He was send to the Supermax prison, north of here... *He shouldn't be any trouble now..."; break;
        case 1509: texte = "I failed against Ganondorf, but don't underestimate me. I am the man who killed a hundred wolves."; break;
        case 1510: texte = "You didn't kill any wolf???*You are a coward!"; break;
        case 1511: texte = "You killed only one wolf???*You are weak!"; break;
        case 1512: texte = "You killed only "; break;
        case 1513: texte = " wolves?*It's not that great..."; break;
        case 1514: texte = "You killed "; break;
        case 1515: texte = " wolves?*Not bad..."; break;
        case 1516: texte = "You killed "; break;
        case 1517: texte = " wolves?*Pretty impressive..."; break;
        case 1518: texte = "You killed 100 wolves?*As many as I did... it's hard to believe..."; break;
        case 1519: texte = "You killed more than a hundred wolves???*Incredible..."; break;
        case 1520: texte = "You really deserve this reward:"; break;
        case 1521: texte = "It's time for me to go back in the training..."; break;
        case 1522: texte = "I will change my hairstyle."; break;
        case 1523: texte = "I will start a diet."; break;
        case 1524: texte = "I won't sell restricted informations anymore."; break;
        case 1525: texte = "I won't spend my days in the tavern."; break;
        case 1526: texte = "I broke my last axe... So I play hangman to kill time, but it's not the same..."; break;
        case 1527: texte = "You have an axe for me???*Give it to me! I trade it for a rope just as effective!"; break;
        case 1528: texte = "This axe for a rope, ok?**              YES ?            no  "; break;
        case 1529: texte = "This axe for a rope, ok?**              yes              NO ?"; break;
        case 1530: texte = "I am so touched...*That's for you:"; break;
        case 1531: texte = "...*It should be punishable by death penalty..."; break;
        case 1532: texte = "You traded the axe for a rope."; break;
        case 1533: texte = "I can't wait to try this axe!"; break;
        case 1534: texte = "Hello, I am the head of this village."; break;
        case 1535: texte = "The Mabe village is like a paradise for tourists, but like a hell for robbers."; break;
        case 1536: texte = "Did you know that famous pirate was captured here when he passed by this town?"; break;
        case 1537: texte = "You find a hammer!"; break;
        case 1538: texte = "My husband is guard at the prison.*It's a full-time job so I don't see him very often..."; break;
        case 1539: texte = "???*What do you have here???*Let me have a look at it!"; break;
        case 1540: texte = "Give her the wedding ring, ok?**              YES ?            no  "; break;
        case 1541: texte = "Give her the wedding ring, ok?**              yes              NO ?"; break;
        case 1542: texte = "It's my husband's wedding ring!*Don't tell me he went to see HER again!!!"; break;
        case 1543: texte = "...*It seems more and more shady...*Gimme that!"; break;
        case 1544: texte = "You traded the wedding ring for nothing."; break;
        case 1545: texte = "Out of my way!"; break;
        case 1546: texte = "Don't go in the storeroom, I didn't do the cleaning!"; break;
        case 1547: texte = "A famous pirate named Ganon D. Roger was captured in this town a long time ago..."; break;
        case 1548: texte = "They say that a descendant of this pirate would live in Hyrule right now..."; break;
        case 1549: texte = "You are in the 7 wise men's residence.*This place is devoted to meditation and knowledge."; break;
        case 1550: texte = "Our chief, the most powerful of the 7 wise men, is barely seen here. He prefers to stay meditating in his house at the South of the Village."; break;
        case 1551: texte = "Some years ago, we were 8 wise men. One of us, Agahnim, thought that it was our duty to take the Triforce and to use it for the sake of everyone."; break;
        case 1552: texte = "Our chief squarely refused. He said that such a power should not fall into the hands of men, that the consequences could be desastrous..."; break;
        case 1553: texte = "After this quarrel, Agahnim left the order. But lately, he reappeared, endowed with strange powers...*We unfortunately do not know what he may have in mind."; break;
        case 1554: texte = "A legendary pirate came in Hyrule long ago. He was captured after a long fighting against the hylian knights of the time."; break;
        case 1555: texte = "The day of his public execution, a man in the crowd asked him where he had hidden his treasure. The pirate explained that it was hidden in 4 temples in Hyrule."; break;
        case 1556: texte = "After this declaration, many men went in search of this treasure but no one ever came back..."; break;
        case 1557: texte = "Did you meet a man named Ganondorf? *When he was just a child he almost ended up in the stomach of a wolf, but he was saved by a former member of our order."; break;
        case 1558: texte = "Since then he considers his saviour as his master."; break;
        case 1559: texte = "Our chief asked us to gather our powers in order to create a very special temple East of here. He says that this temple would save the world..."; break;
        case 1560: texte = "The moutain North of the village hid a temple. Far end of this temple is hidden an incredible treasure. But... it's far to dangerous to go in."; break;
        case 1561: texte = "I still can't believe you were able to find this treasure..."; break;
        case 1562: texte = "WHAT ??? YOU FOUND THE TREASURE OF THE TEMPLE!!!"; break;
        case 1563: texte = "Incredible... take this, I want to reward you for this feat!"; break;
        case 1564: texte = "It's been along time since HE gave me anything..."; break;
        case 1565: texte = "You have a jewel?*It's from HIM, isn't it?*Yes, it can only be from HIM!"; break;
        case 1566: texte = "Give the jewel?**              YES ?            no  "; break;
        case 1567: texte = "Give the jewel?**              yes              NO ?"; break;
        case 1568: texte = "It's so nice of him...*Could you go to the prison and give him this letter please?"; break;
        case 1569: texte = "...*I'll tell HIM!"; break;
        case 1570: texte = "You traded the jewel for a letter."; break;
        case 1571: texte = "He! He! He!"; break;
        case 1572: texte = "I am the chief of the village and er... anyway the wise men are the one in control here..."; break;
        case 1573: texte = "We are closed to the public."; break;
        case 1574: texte = "We waited for you for a long time...*Take the time to visit my opera..."; break;
        case 1575: texte = "This opera has a long story, take your time to discover it..."; break;
        case 1576: texte = "Welcome visitor, allow me to tell you the story of this opera."; break;
        case 1577: texte = "I am the founder of this opera, but formerly I was nothing but a mere thief."; break;
        case 1578: texte = "One day, a burglary went wrong and the hylian knights patrolling near the tavern fell on me. I was punished and sent in prison."; break;
        case 1579: texte = "In prison, I found an old skull under my berth. I used it as an accessory to recite monologues, much to the delight of my cellmate."; break;
        case 1580: texte = "Thus was born my passion for the theatre and then for the opera, in prison."; break;
        case 1581: texte = "Shortly before my release, I made the promise on the old skull to construct the most somptuous of the theatres before my cellmate's release."; break;
        case 1582: texte = "Once free, I went in search of a building land. Until the day when, chased by wolves, I had to take refuge in the Lost Woods."; break;
        case 1583: texte = "That's when I found this glade, at the far end of the forest, in a green setting, protected by the one-thousand-year-old trees..."; break;
        case 1584: texte = "I started to built my opera. The plans were quickly made, but without money to pay workers, it seemed an impossible task."; break;
        case 1585: texte = "When I was thinking of giving up, an odd fellow came and brought me back the skull, and reminded me my promise."; break;
        case 1586: texte = "After months of work, the opera was finished. It was the most beautiful opera ever seen in Hyrule."; break;
        case 1587: texte = "Quickly, prestigious artists coming from all countries came to perform here. I had fufilled my dream and kept my promise."; break;
        case 1588: texte = "During the war against Ganon, many smugglers used the chaos to prosper."; break;
        case 1589: texte = "One of them was none other than my old cellmate, newly released, who asked to use the opera as his hideout."; break;
        case 1590: texte = "With the return of the peace, the King of Hyrule wished to end the smuggling. He sent his best soldiers to chase the culprits."; break;
        case 1591: texte = "I was afraid of losing every thing because of my complicity, I asked my old friend to leave the opera, saying that I would hand him over the king if he refused."; break;
        case 1592: texte = "Obliged to leave the opera, the bandits locked me in their old hideout with the employees, and burned it down."; break;
        case 1593: texte = "This is how I died, along with my opera, that was destroyed forever..."; break;
        case 1594: texte = "You know my story, don't you have anything to show me?"; break;
        case 1595: texte = "I have waited your coming for centuries to settle that old debt..."; break;
        case 1596: texte = "Make him settle his debt?**              YES ?            no  "; break;
        case 1597: texte = "Make him settle his debt?**              yes              NO ?"; break;
        case 1598: texte = "My life was short but exciting. Nothing of it would have been possible without your intervention."; break;
        case 1599: texte = "I wanted to give you this: the saw I used to construct this opera!"; break;
        case 1600: texte = "...*You must be kidding?"; break;
        case 1601: texte = "You traded the IOU for a saw."; break;
        case 1602: texte = "Go now, it is time for us to rest in peace..."; break;
        case 1603: texte = "As the barman, I know all the gossips..."; break;
        case 1604: texte = "Here is one: my favorite color is said to be the yellow...*But I didn't tell you anything, ok?"; break;
        case 1605: texte = "It's a pretty yellow stone you have here... Will you trade it for my best bottle?"; break;
        case 1606: texte = "This yellow gemstone for a bottle, ok?**              YES ?            no  "; break;
        case 1607: texte = "This yellow gemstone for a bottle, ok?**              yes              NO ?"; break;
        case 1608: texte = "Yay! It's mine!"; break;
        case 1609: texte = "Tsss... no one will give you more for it you know..."; break;
        case 1610: texte = "You traded the yellow gemstone for a bottle of wine."; break;
        case 1611: texte = "You want something to drink? It will be free for you."; break;
        case 1612: texte = "A melody is engraved on the stele:"; break;
        case 1613: texte = "You learn the song of soaring!*Play it outside to teleport!"; break;
        case 1614: texte = "You learn the inverted song of time!*Play it outside to go back in time!"; break;
        case 1615: texte = "You learn the song of double time!*Play it outside to travel to the future!"; break;
        case 1616: texte = "I am a part-time guard in this prison. *Outside of the visit hours I'm not allowed to let you pass."; break;
        case 1617: texte = "This letter is for me? It's probably from HER... Give it quickly!"; break;
        case 1618: texte = "Give the letter?**              YES ?            no  "; break;
        case 1619: texte = "Give the letter?**              yes              NO ?"; break;
        case 1620: texte = "...*...*..."; break;
        case 1621: texte = "I have to leave my post... it's er... an emergency... You look like a good guy, take my place. Oh and keep that for me:"; break;
        case 1622: texte = "It's not for me?*Too bad..."; break;
        case 1623: texte = "You traded the letter for a wedding ring."; break;
        case 1624: texte = "I gotta go!"; break;
        case 1625: texte = "I am but a mere innocent arrived here by mistake... You wouldn't have something to help me fly from here?"; break;
        case 1626: texte = "A... spoon huh?"; break;
        case 1627: texte = "Give the spoon?**              YES ?            no  "; break;
        case 1628: texte = "Give the spoon?**              yes              NO ?"; break;
        case 1629: texte = "Thank you... ... ...*There, take this gift as a thanks...*It belonged to my former cellmate..."; break;
        case 1630: texte = "Sounds like a wonderful spoon escape possibility just fled..."; break;
        case 1631: texte = "You traded the spoon for a skull."; break;
        case 1632: texte = "Well... some work has to be done now..."; break;
        case 1633: texte = "I didn't think my mission could fail... The hylian knights aren't very strong, even their chief is getting weaker..."; break;
        case 1634: texte = "The explosion came from the room at the right."; break;
        case 1635: texte = "So here is the man who was able to stop the powerful Ganondorf..."; break;
        case 1636: texte = "I am Agahnim, former wise man, and Ganondorf's mentor. As for you, you must be Link..."; break;
        case 1637: texte = "Like it or not, we are going to take the Triforce.*Farewell!"; break;
        case 1638: texte = "                    Level 1 :                                                                                Temple of Courage"; break;
        case 1639: texte = "                    Level 2 :                                                                                 Temple of Wisdom"; break;
        case 1640: texte = "                    Level 3 :                                                                                  Temple of Power"; break;
        case 1641: texte = "                    Level 4 :                                                                                   Abyss Ruins"; break;
        case 1642: texte = "                    Level 5 :                                                                                 Phantom Pyramid"; break;
        case 1643: texte = "                 Great Pyramid"; break;
        case 1644: texte = "                Temple of Earth"; break;
        case 1645: texte = "                 Temple of Air"; break;
        case 1646: texte = "                Temple of Water"; break;
        case 1647: texte = "                 Temple of Fire"; break;
        case 1648: texte = "               Temple of Goddesses"; break;
        case 1649: texte = "                 Hyrule Castle"; break;
        case 1650: texte = "                   Final Level :                                                                               Hyrule Castle"; break;
        case 1651: texte = "            Second Quest - Level 1 :                                                                               Casino"; break;
        case 1652: texte = "            Second Quest - Level 2 :                                                                            Tower of Gem"; break;
        case 1653: texte = "          Second Quest - Final Level :                                                                        Final Destination"; break;
        case 1654: texte = "You found the map!!!**Press L to see the dungeon map."; break;
        case 1655: texte = "You found the map!!!**Press P to see the dungeon map."; break;
        case 1656: texte = "You found the compass!!!**The Boss and chests are now indicated on the map."; break;
        case 1657: texte = "You found the Boss Key!!!**Use it to open his haunt."; break;
        case 1658: texte = "You found a little key.**Use it to unlock a door."; break;
        case 1659: texte = "You found a new heart!!! **Your amount of life increases by one heart!!!"; break;
        case 1660: texte = "You found a bow!!!**Equip it by pressing entry then use it with ¾1 to attack from a distance!"; break;
        case 1661: texte = "You found a bow!!!**Equip it by pressing entry then use it with X to attack from a distance!"; break;
        case 1662: texte = "You found the Pendant of Courage!!!"; break;
        case 1663: texte = "You found the Pendant of Wisdom!!!"; break;
        case 1664: texte = "You found the Pendant of Power!!!"; break;
        case 1665: texte = "You found the Power Gloves!!!**Now you can lift rocks!"; break;
        case 1666: texte = "I give up, you win!*How could you defeat the Ultimate LOL technique???"; break;
        case 1667: texte = "You won't let me get out of it so easily, huh?*The code in the next room is 12086... Now get lost."; break;
        case 1668: texte = "I should have stayed in the family gang..."; break;
        case 1669: texte = "You found the lantern!!!**Now you can shot up flames!"; break;
        case 1670: texte = "You found the flippers!!!**Now you can cross the water!"; break;
        case 1671: texte = "???*How could you arrive in here? *My pet was supposed to mount guard!"; break;
        case 1672: texte = "...*You are Link, you say?*...*So the time has already come?"; break;
        case 1673: texte = "Ganon's minions discovered my existence and destroyed the village I lived in. That's why I came in this temple to hide."; break;
        case 1674: texte = "Continue your quest Link, I will see you again in the portal's cave!"; break;
        case 1675: texte = "You found a better tunic!!!**Your defense raises by one point!"; break;
        case 1676: texte = "You found the Key of Time!!!**Go quickly show it to the wise men!"; break;
        case 1677: texte = "You found the Magic Hammer!!!**Use it to pound the stakes blocking your way!"; break;
        case 1678: texte = "You found the Titan's Mitt!!!**Now you can lift the heaviest rocks!!!"; break;
        case 1679: texte = "You found a Yellow Gemstone!**It's an inestimable treasure!"; break;
        case 1680: texte = "You found the Fairy Bow!!!**Your arrows are now incredibly powerful!!!"; break;
        case 1681: texte = "You found a Green Gemstone!**It's an inestimable treasure!"; break;
        case 1682: texte = "You found the Ice Rod!!!**Now you can freeze your enemies from a distance!!!"; break;
        case 1683: texte = "You found a Blue Gemstone!**It's an inestimable treasure!"; break;
        case 1684: texte = "You found the Fire Rod!!!**You can now shoot up powerful fire balls!!!"; break;
        case 1685: texte = "You found a Red Gemstone!**It's an inestimable treasure!"; break;
        case 1686: texte = "You found an incredibly tough shield!!!*Your defense raises with one point!"; break;
        case 1687: texte = "Here you are at last."; break;
        case 1688: texte = "Did you really think you could outrun a sorcerer able to teleport?"; break;
        case 1689: texte = "I guess i still have to thank you. *To find this temple is no easy. Ganondorf and I spent months without finding even one crystal."; break;
        case 1690: texte = "And the day when finally, we were about to reach one easily you turned up and brought down the powerful Ganondorf... *I have to admit I wasn't expecting that..."; break;
        case 1691: texte = "However, it seemed obvious that we were working towards the same end, and that you were in advance of us."; break;
        case 1692: texte = "So we decided you would find the temple for us."; break;
        case 1693: texte = "You had fun all this time, but now is our turn."; break;
        case 1694: texte = "It is time for you to disappear."; break;
        case 1695: texte = "What??? *You couldn't possibly defeat Aghanim???"; break;
        case 1696: texte = "... *Hope still remains, I can do something..."; break;
        case 1697: texte = "Welcome Link. *We are Din, Nayru et Farore, the founding Goddesses of Hyrule."; break;
        case 1698: texte = "Your efforts to save Hyrule finally lead you in front of us."; break;
        case 1699: texte = "As you may have undestood already, You cannot change the past. All of your acts had the only effect of preparing the present you come from."; break;
        case 1700: texte = "Ganondorf came to our temple to follow his master, and he finally brought him back to life."; break;
        case 1701: texte = "He wished to be able to travel between life and death, but only the most powerful demons can do that."; break;
        case 1702: texte = "Thanks to his new powers, Ganon was able to bring Aghanim back to life, but his new nature overflew his reason."; break;
        case 1703: texte = "He changed Agahnim into zombi in his pay, proclaimed himself King of Evil and came back to conquer Hyrule."; break;
        case 1704: texte = "The chief of the middle village organized the defense of Hyrule after proclaiming himself King. He had the Master Sword forged and made knights and wise men work together."; break;
        case 1705: texte = "The Hylian Knights were destroyed, but their chief, armed with the Master Sword, beat back Ganon long enough to give the wise men time to seal him forever."; break;
        case 1706: texte = "But you know what happened next. Using Agahnim, Ganon eliminated the wise men's descendents ans broke off the seal."; break;
        case 1707: texte = "With the Master Sword you beat him off several times, but the world of death can't keep him prisoner for long."; break;
        case 1708: texte = "Ganon found the Triforce, but this temple hides some other treasurs..."; break;
        case 1709: texte = "Against the Triforce, able to give an illimited power to the one touching it, we created an anti-Triforce."; break;
        case 1710: texte = "They are 3 weapons with an exceptional power. If two of them unite against the Triforce holder, they will call of his wish."; break;
        case 1711: texte = "The Sword of Courage is rightfully yours. We also entrust you with the Bow of Wisdom, give it to the only one able to handle it."; break;
        case 1712: texte = "As for the Trident of Power, we send it to the last chosen one."; break;
        case 1713: texte = "You got the Sword of Courage!!! *This legendary weapon gives off a tremendous power."; break;
        case 1714: texte = "You got the Bow of Wisdom!!! *A mysterious power prevents you from using it..."; break;
        case 1715: texte = "Time has come Link, we send you back to your era."; break;
        case 1716: texte = "Link! It's Zelda! I'm talking with you by telepathy, you couldn't be reach!"; break;
        case 1717: texte = "Ganon is back! He's attacking the castle! *All of the guards have been changed into monsters under his control, be careful!"; break;
        case 1718: texte = "The throne room is further North."; break;
        case 1719: texte = "The Princess is not ready to receive you yet."; break;
        case 1720: texte = "However, she instructed me to tell that some items have been stored for you in the storeroom."; break;
        case 1721: texte = "The Princess will be ready to see you in a few minutes."; break;
        case 1722: texte = "You got the authorization to go in the storeroom? *Very well, you can go on."; break;
        case 1723: texte = "The storeroom is further East"; break;
        case 1724: texte = "The castle is under control."; break;
        case 1725: texte = "You found a shield!*Your defense raises by one point!"; break;
        case 1726: texte = "You got a wallet able to hold up to 99 Rupees !"; break;
        case 1727: texte = "Princess Zelda is waiting for you."; break;
        case 1728: texte = "Hello Link."; break;
        case 1729: texte = "Er, Link! *I'm here!*Yoo-hoo!"; break;
        case 1730: texte = "Some thing terrible happenned last night, Link..."; break;
        case 1731: texte = "The Ocarina of Time you brought back from Termina... *I kept it in a safety vault here in the castle, but it has been stolen!"; break;
        case 1732: texte = "I send guards everywhere in Hyrule, so I don't think the thief could make his way any far..."; break;
        case 1733: texte = "I would like you to find and bring back the Ocarina. Start your investigation in the safety vault in the basement, I'll meet you there."; break;
        case 1734: texte = "The safety vaults are this way."; break;
        case 1735: texte = "The access to the safety vault is stricly forbidden."; break;
        case 1736: texte = "The Princess instructed you with investigating the Ocarina theft? *In that case you can go. There is nothing left to steal anyway..."; break;
        case 1737: texte = "I was guarding this door last night. I am absolutely sure no one came through it..."; break;
        case 1738: texte = "That's where the Ocarina was kept. The guard heard a big noise. But before he realized it was coming from inside the room, the safe had been cleared out."; break;
        case 1739: texte = "If you see anything suspicious, go in front of it and press ¾2 to point it out to me."; break;
        case 1740: texte = "If you see anything suspicious, go in front of it and press SPACE to point it out to me."; break;
        case 1741: texte = "It's a torch... What were you expecting for? A ceiling chandelier?"; break;
        case 1742: texte = "This safe is the one in which the Ocarina was kept. Until last night..."; break;
        case 1743: texte = "This room used to lead out into the sewer... *Before changing it into a safety vault I had the way sealed off. The curtains are here to hide that it wasn't good work..."; break;
        case 1744: texte = "It's er... a rubber duck. *Don't ask me what it's doing here..."; break;
        case 1745: texte = "These curtains intrigue you apparently... *Let's see what's behind..."; break;
        case 1746: texte = "So that's where the thief came from! *What are you waiting for? Go after him!"; break;
        case 1747: texte = "I feel forgotten... *Here I am, guarding a safety vault empty and wide open..."; break;
        case 1748: texte = "The thief is probably in this forest, you can't give up now!"; break;
        case 1749: texte = "TUTORIAL : Press ¾3 in front of a light object like a jar in order to lift it up. Press a second time to throw it."; break;
        case 1750: texte = "TUTORIAL : Press ¾2 in front of a chest to open it. You can open a chest only if you are down it."; break;
        case 1751: texte = "TUTORIAL : Press C in front of a light object like a jar in order to lift it up. Press a second time to throw it."; break;
        case 1752: texte = "TUTORIAL : Press SPACE in front of a chest to open it. You can open a chest only if you are down it."; break;
        case 1753: texte = "                 Hyrule Castle"; break;
        case 1754: texte = "This way leads to the prison cells, you have nothing to do there."; break;
        case 1755: texte = "This way leads to a very high safety zone. Even the Hero of Hyrule is not allowed to go in."; break;
        case 1756: texte = "Er... How did you arrive here?"; break;
        case 1757: texte = "These stairs lead to the safety vaults."; break;
        case 1758: texte = "The throne room is behind this door."; break;
        case 1759: texte = "The throne room is called the throne room because there is only one throne left..."; break;
        case 1760: texte = "The door left-hand leads to the dancehall and the VIP quarters, and the door up leads to the dinig room and the kitchen."; break;
        case 1761: texte = "In the old days I played the piano standing up, but in the course of time, I decided to sit."; break;
        case 1762: texte = "I'm here as a musician, but the dancing nights I prefer to forget the harp and dance."; break;
        case 1763: texte = "I heard that a musical instrument thief came in the castle last night."; break;
        case 1764: texte = "Fortunately, he didn't see my violin."; break;
        case 1765: texte = "A little tonic ?**              YES ?            no  "; break;
        case 1766: texte = "A little tonic ?**              yes              NO ?"; break;
        case 1767: texte = "Chef in the castle, it's no sinecure..."; break;
        case 1768: texte = "They say the best cooks are able to read and cook at the same time. As for me, I can half-do it."; break;
        case 1769: texte = "I never know what to prepare, I have to find an idea quick!"; break;
        case 1770: texte = "Waitress in the castle, it's a pretty good job, quiet and well-paying."; break;
        case 1771: texte = "The West wing is only for VIPs. And er... I didn't receive any orders about you... an oversight probably."; break;
        case 1772: texte = "The East wing of the castle is only for the guards. Sorry, but you've got nothing to do there."; break;
        case 1773: texte = "This door leads to the storeroom."; break;
        case 1774: texte = "The library is a place... pretty quiet."; break;
        case 1775: texte = "You got a energy core!*...*It's not that bad..."; break;
        case 1776: texte = "The access to the throne room is only allowed to accredited people."; break;
        case 1777: texte = "The access to this part of the castle is reserved to the renovation staff."; break;
        case 1778: texte = "You know the secret phrase?*I knew that under your look of cute little bunny a Ganon's elite soldier was hiding."; break;
        case 1779: texte = "You can go."; break;
        case 1780: texte = "You got the authorization to go everywhere in the castle??? *Well, go through if that's so..."; break;
        case 1781: texte = "You came to free me? *I didn't need your help..."; break;
        case 1782: texte = "I wanted to take this castle by force... So I came to challenge Ganon."; break;
        case 1783: texte = "It was a long and terrible fight... *But the throne room guards finally arrested me..."; break;
        case 1784: texte = "Such a rotten luck, I really wanted to meet Ganon..."; break;
        case 1785: texte = "Since then I heard that there is a secret phrase to give to the guards to pass. You have to tell them this :"; break;
        case 1786: texte = "Sorry, but our princess is in another castle!"; break;
        case 1787: texte = "Next time, I'll do it."; break;
        case 1788: texte = "!!!*Hey, you are..."; break;
        case 1789: texte = "A little pink bunny! *I love pink!"; break;
        case 1790: texte = "Make yourself at home little bunny, I entitle you to wander in the castle as you wish."; break;
        case 1791: texte = "I feel like I met you somewhere... *Anyway, you don't know where I could find a good beer?"; break;
        case 1792: texte = "Is it a beer you have?*I take it, you're here for that anyway, aren't you?"; break;
        case 1793: texte = "Here, you can have that, as a reward."; break;
        case 1794: texte = "You traded the beer for some nails..."; break;
        case 1795: texte = "I think I like you, you're a good boy. *You wouldn't have another beer for me?"; break;
        case 1796: texte = "A score is engraved. If you had an instrument you could try to play it."; break;
        case 1797: texte = "You have... er... stolen the ocarina ??? *Let's say it's for a good cause..."; break;
        case 1798: texte = "At the instant when he played the tune with the ocarina, Link was brought back to his area. He ran to the castle to tell his story to the Princess..."; break;
        case 1799: texte = "What an awful story... *Is the Hyrule Realm really doomed to fall into Ganon's hands?"; break;
        case 1800: texte = "What should we do now? *If only Ganon had never found the Triforce..."; break;
        case 1801: texte = "The Ocarina carried Link once again. The Hero of Hyrule arrived in a vast snow-covered field..."; break;
        case 1802: texte = "Is that mirror for me?**              YES ?            no  "; break;
        case 1803: texte = "Is that mirror for me?**              yes              NO ?"; break;
        case 1804: texte = "... You're giving me a mirror??? Do you think I'm the kind of girl who spends her whole day looking at herself???"; break;
        case 1805: texte = "Oh well, you can have this, as a thanks."; break;
        case 1806: texte = "...*Go away quick if you don't want to end up in a cell."; break;
        case 1807: texte = "You traded the mirror for a spoon!"; break;
        case 1808: texte = "You are in a high safety zone, I will ask you to leave."; break;
        case 1809: texte = "You found an extremly tough tunic!!!*Your defense raises by one point!"; break;
        case 1810: texte = "Happy to see you at last Link!"; break;
        case 1811: texte = "You're telling that this bow is for me and able to defeat Ganon?*Cool!"; break;
        case 1812: texte = "You gave the Bow of Wisdom to the Princess."; break;
        case 1813: texte = "Don't worry about me, I'll be able to make my own way now."; break;
        case 1814: texte = "We have to breast Ganon, you go first, I'll meet you there.*I have to put my make-up on first."; break;
        case 1815: texte = "!!! *Ganon regained his human form! *He is not a demon anymore, he is not able to come back from the dead world, we won!"; break;
        case 1816: texte = "???"; break;
        case 1817: texte = "Here you are at last Link. *This time victory will be mine, I perfected my techniques especially to beat you."; break;
        case 1818: texte = "Once again we face each other Link. *I feel like I get out of a long nightmare..."; break;
        case 1819: texte = "Agahnim was wrong, the Triforce should have never been found."; break;
        case 1820: texte = "Listen to me carefully Link, a long long time ago now, Agahnim disappeared after he left the order of the wisemen."; break;
        case 1821: texte = "The day he came back, he was gifted with very dark power. As a wiseman, he would never have been able to shoot fire ball, his speciality was rabbits..."; break;
        case 1822: texte = "I owed too much to Agahnim to put up to him, but I made inquiry while we were looking for the crystals."; break;
        case 1823: texte = "It seems like he got his powers from an entity far more dangerous and powerful than I never could be"; break;
        case 1824: texte = "There are still in Hyrule places you didn't explored and enemies you didn't fight. Youre quest is not finished yet..."; break;
        case 1825: texte = "You want to know why i'm telling you all of that? *I guess I ain't gonna get out of it that easily, after what I've done..."; break;
        case 1826: texte = "If I fail today, someone will have to avenge Aghanim instead of me. *But..."; break;
        case 1827: texte = "... will you be able to?"; break;
        case 1828: texte = "You have found the Triforce!!!"; break;
        case 1829: texte = "That's how Ganondorf was defeated forever. The Triforce was once again get back and kept safe in the castle. **However, concerned by Ganondorf's last words, Link spent the rest of his life watching over Hyrule. ***End of the First Quest."; break;
        case 1830: texte = "Ganon has recovered a human form... *is he still our enemy?"; break;
        case 1831: texte = "Ready for a last duel?"; break;
        case 1832: texte = "Welcome to the Casino !"; break;
        case 1833: texte = "Welcome dear guest, the entry fee is 10 Golden Ganon, are you okay with that?*              YES ?            no  "; break;
        case 1834: texte = "Welcome dear guest, the entry fee is 10 Golden Ganon, are you okay with that?*              yes              NO ?"; break;
        case 1835: texte = "Too bad."; break;
        case 1836: texte = "Welcome in the Casino!"; break;
        case 1837: texte = "Be back when you have money my friend."; break;
        case 1838: texte = "We are closed for now, come back later."; break;
        case 1839: texte = "Welcome in the family Casino, do you want me to explain you the game rules for 5 Golden Ganon?*              YES ?            no  "; break;
        case 1840: texte = "Welcome in the family Casino, do you want me to explain you the game rules for 5 Golden Ganon?*              yes              NO ?"; break;
        case 1841: texte = "In this casino, enemies won't take you energy but money. Each attack makes you lose a little more life than the last one."; break;
        case 1842: texte = "You don't have a rupee left, you're expeled. We're not interested by broke clients."; break;
        case 1843: texte = "However, if you win the various games in the casino, you will win marvelous prices."; break;
        case 1844: texte = "Strike the enemies to stop them on a mark. Get the 4 different marks and you'll win the price."; break;
        case 1845: texte = "Do you want to try for 10 Golden Ganon?**              YES ?            no  "; break;
        case 1846: texte = "Do you want to try for 10 Golden Ganon?**              yes              NO ?"; break;
        case 1847: texte = "You already won this game."; break;
        case 1848: texte = "Congratulation!*Here is your price:"; break;
        case 1849: texte = "You will probably be more lucky next time."; break;
        case 1850: texte = "Strike the enmies to stop them on a figure. Get a 4, a 2 and a 1 and you'll get the price."; break;
        case 1851: texte = "Talk to me if you fail, you'll just start again with the right numbers you've already found."; break;
        case 1852: texte = "Do you want to complete for 5 Golden Ganon?**              YES ?            no  "; break;
        case 1853: texte = "Do you want to complete for 5 Golden Ganon?**              yes              NO ?"; break;
        case 1854: texte = "This is the Casino Great Race's starting line, you've got 21 seconds to reach the finishing line."; break;
        case 1855: texte = "You're losing time there, you know?"; break;
        case 1856: texte = "This is the Casino Great Race's finishing line. Go to the starting line if you want to break the record."; break;
        case 1857: texte = "Strike the enemies to stop them on a figure and get more than I do with one die less."; break;
        case 1858: texte = "Chose a figure, eather 1, or 6. I will throw 4 dices, if your figure is in, you win, if not, you pay 10 time the difference with the closest dice."; break;
        case 1859: texte = "Do you want to try?**              YES ?            no  "; break;
        case 1860: texte = "Do you want to try?**              yes              NO ?"; break;
        case 1861: texte = "Which figure do you chose?**              ONE  ?            six  "; break;
        case 1862: texte = "Which figure do you chose?**              one               SIX ?"; break;
        case 1863: texte = "Strike the enemy to stop them on a figure that will be handed over to a block on the right. The push the blocks so that they arrive at 0 onto the flagstones."; break;
        case 1864: texte = "I sell you a key for a price equal to the sum of your four dices times the amount of mine."; break;
        case 1865: texte = "I sell you a key for "; break;
        case 1866: texte = " Golden Ganon, are you okay with that?*              YES ?            no  "; break;
        case 1867: texte = "I sell you a key for "; break;
        case 1868: texte = " Golden Ganon, are you okay with that?*              yes              NO ?"; break;
        case 1869: texte = "The Chest room is at the end of the corridor on the left. Only the best customers may hope to reach it."; break;
        case 1870: texte = "Did you open the chest?*Then now you should try the Special Room."; break;
        case 1871: texte = "People like you have got nothing to do in a casino...*We are broke..."; break;
        case 1872: texte = "Welcome to the Casino Great Quiz!"; break;
        case 1873: texte = "Here I'm the one asking questions, and bad answers are expensive."; break;
        case 1874: texte = "I don't ask you if you want to play, I'm a boss after all.*So let's get it started..."; break;
        case 1875: texte = "Next question..."; break;
        case 1876: texte = "This casino houses a total of 6 different games without this quiz, right?*              RIGHT ?          wrong  "; break;
        case 1877: texte = "This casino houses a total of 6 different games without this quiz, right?*              right            WRONG ?"; break;
        case 1878: texte = "Correct! There are 7 games, 1 for the map, 1 for the compass and 5 for the keys."; break;
        case 1879: texte = "No! There are 7 games, 1 for the map, 1 for the compass and 5 for the keys."; break;
        case 1880: texte = "The guy in the cofee house never drinks more than 16 cofeecups a day, right?*             RIGHT ?          wrong  "; break;
        case 1881: texte = "The guy in the cofee house never drinks more than 16 cofeecups a day, right?*             right            WRONG ?"; break;
        case 1882: texte = "Correct! He can go up to 17 cups!"; break;
        case 1883: texte = "No! He can go up to 17 cups!"; break;
        case 1884: texte = "This game contains a total of 150 power gems, right?*             RIGHT ?          wrong  "; break;
        case 1885: texte = "This game contains a total of 150 power gems, right?*             right            WRONG ?"; break;
        case 1886: texte = "Correct! There are 200."; break;
        case 1887: texte = "No! There are 200."; break;
        case 1888: texte = "There are only 7 houses left in the middle village, is that so?*             RIGHT ?          wrong  "; break;
        case 1889: texte = "There are only 7 houses left in the middle village, is that so?*             right            WRONG ?"; break;
        case 1890: texte = "Correct! The 3 others are destroyed."; break;
        case 1891: texte = "No! There are 10 houses, 3 of them are destroyed, so only 7 are left."; break;
        case 1892: texte = "You died "; break;
        case 1893: texte = " times, am I right?**             RIGHT ?          wrong  "; break;
        case 1894: texte = "You died "; break;
        case 1895: texte = " times, am I right?**             right            WRONG ?"; break;
        case 1896: texte = "Correct! You died "; break;
        case 1897: texte = " times."; break;
        case 1898: texte = "No! You died "; break;
        case 1899: texte = " times."; break;
        case 1900: texte = "14 bad answers are enough to make lose any player, right?*             RIGHT ?          wrong  "; break;
        case 1901: texte = "14 bad answers are enough to make lose any player, right?*             right            WRONG ?"; break;
        case 1902: texte = "Correct! 14 bad answer make lose minimum 1050 Golden Ganon out of 999 transportable."; break;
        case 1903: texte = "No! 14 bad answer make lose minimum 1050 Golden Ganon out of 999 transportable."; break;
        case 1904: texte = "I'm the coolest boss in the game, right?**             RIGHT ?          wrong  "; break;
        case 1905: texte = "I'm the coolest boss in the game, right?**             right            WRONG ?"; break;
        case 1906: texte = "Ha! Ha! We agree."; break;
        case 1907: texte = "... *This one is wrong, on principle..."; break;
        case 1908: texte = "Only 3 dungeons in the past are necessary to finish the game, right? *             RIGHT ?          wrong  "; break;
        case 1909: texte = "Only 3 dungeons in the past are necessary to finish the game, right? *             right            WRONG ?"; break;
        case 1910: texte = "Correct! Temple of the air, temple of fire and the Goddesses Temple."; break;
        case 1911: texte = "No! There are 2 indeed, the temple of the air, temple of fire and the Goddesses Temple."; break;
        case 1912: texte = "More than 4000 Golden Ganon are necessary to get all of the fat fairy's prices, right?*            RIGHT ?          wrong  "; break;
        case 1913: texte = "More than 4000 Golden Ganon are necessary to get all of the fat fairy's prices, right?*            right            WRONG ?"; break;
        case 1914: texte = "Correct! 3798 are enough."; break;
        case 1915: texte = "No! 3798 are enough."; break;
        case 1916: texte = "In Zelda's time, the palace had 80 pillars, right?*             RIGHT ?          wrong  "; break;
        case 1917: texte = "In Zelda's time, the palace had 80 pillars, right?*             right            WRONG ?"; break;
        case 1918: texte = "Correct! There were 80 indeed."; break;
        case 1919: texte = "No! There were actually 80."; break;
        case 1920: texte = "You already answered "; break;
        case 1921: texte = " of my questions, is that so?*             RIGHT ?          wrong  "; break;
        case 1922: texte = "You already answered "; break;
        case 1923: texte = " of my questions, is that so?*             right            WRONG ?"; break;
        case 1924: texte = "Correct! But now you did."; break;
        case 1925: texte = "No! But now you did."; break;
        case 1926: texte = "You can find a maximum of 16 pieces of heart in this game, right?*             RIGHT ?          wrong  "; break;
        case 1927: texte = "You can find a maximum of 16 pieces of heart in this game, right?*             right            WRONG?"; break;
        case 1928: texte = "Correct! There are 16 in all."; break;
        case 1929: texte = "No! There are 16 in all."; break;
        case 1930: texte = "A blue potion costs the equivalent of 40 Rupees plus 40 Golden Ganon plus 10 Gold Coins, right?*             RIGHT ?          wrong  "; break;
        case 1931: texte = "A blue potion costs the equivalent of 40 Rupees plus 40 Golden Ganon plus 10 Gold Coins, right?*             right            WRONG ?"; break;
        case 1932: texte = "Correct! That is 160 Rupees."; break;
        case 1933: texte = "No! This equals 160 Rupees, so the price of a blue potion."; break;
        case 1934: texte = "In the mine, the trolley's track could change with 3 levers, right?*             RIGHT ?          wrong  "; break;
        case 1935: texte = "In the mine, the trolley's track could change with 3 levers, right?*             right            WRONG ?"; break;
        case 1936: texte = "Correct! There were 2 only."; break;
        case 1937: texte = "No! There were 2 only."; break;
        case 1938: texte = "You had to find 3 different kinds of fish to win the angling contest, right?*             RIGHT ?          wrong  "; break;
        case 1939: texte = "You had to find 3 different kinds of fish to win the angling contest, right?*             right            WRONG ?"; break;
        case 1940: texte = "Correct! You needed 5."; break;
        case 1941: texte = "No! You needed 5."; break;
        case 1942: texte = "Only the Master Sword is able to throw back the projectiles, right?*             RIGHT ?          wrong  "; break;
        case 1943: texte = "Only the Master Sword is able to throw back the projectiles, right?*             right            WRONG ?"; break;
        case 1944: texte = "Correct! Your current sword can do that too."; break;
        case 1945: texte = "No! Your current sword can do that too."; break;
        case 1946: texte = "Zelda is taller than you, true?**             RIGHT ?          wrong  "; break;
        case 1947: texte = "Zelda is taller than you, true?**             right            WRONG ?"; break;
        case 1948: texte = "Correct! You are a pixel more."; break;
        case 1949: texte = "No! You are a pixel more."; break;
        case 1950: texte = "The dungeon 3 has 3 floors, right?**             RIGHT ?          wrong  "; break;
        case 1951: texte = "The dungeon 3 has 3 floors, right?**             right            WRONG ?"; break;
        case 1952: texte = "Correct! And one only for the boss."; break;
        case 1953: texte = "No! 2 floors plus 1 for the boss, so 3."; break;
        case 1954: texte = "Link's demonic incarnation is a pink bunny, right?*             RIGHT ?          wrong  "; break;
        case 1955: texte = "Link's demonic incarnation is a pink bunny, right?*             right            WRONG ?"; break;
        case 1956: texte = "Correct! It's Oni Link."; break;
        case 1957: texte = "No! It's Oni Link."; break;
        case 1958: texte = "Tingle should never had existed, right?**             RIGHT ?          wrong  "; break;
        case 1959: texte = "Tingle should never had existed, right?**             right            WRONG ?"; break;
        case 1960: texte = "Er... we're wandering from the point there, but I'll say it's okay."; break;
        case 1961: texte = "... *To me, he shouldn't have."; break;
        case 1962: texte = "You want to give me Golden Ganon, right?**             RIGHT ?          wrong  "; break;
        case 1963: texte = "You want to give me Golden Ganon, right?**             right            WRONG ?"; break;
        case 1964: texte = "Correct! Alas..."; break;
        case 1965: texte = "Thanks!"; break;
        case 1966: texte = "Snakes' bites leave you half a heart no matter your life and defense, right?*             RIGHT ?          wrong  "; break;
        case 1967: texte = "Snakes' bites leave you half a heart no matter your life and defense, right?*             right            WRONG ?"; break;
        case 1968: texte = "Correct! If you had only half a heart left, the bite leaves you nothing."; break;
        case 1969: texte = "No! If you had only half a heart left, the bite leaves you nothing."; break;
        case 1970: texte = "Link's property has 77 grass tuft, right?**             RIGHT ?          wrong  "; break;
        case 1971: texte = "Link's property has 77 grass tuft, right?**             right            WRONG ?"; break;
        case 1972: texte = "Correct! Happy to see I'm not the only who have counted them!"; break;
        case 1973: texte = "Non! Do you realize I know your property better than you do???"; break;
        case 1974: texte = "2 to the power of 12 is smaller than the cube root of 7, is that so?*             RIGHT ?          wrong  "; break;
        case 1975: texte = "2 to the power of 12 is smaller than the cube root of 7, is that so?*             right            WRONG ?"; break;
        case 1976: texte = "Correct! Well, I think."; break;
        case 1977: texte = "No! I think it's the other way around."; break;
        case 1978: texte = "It is possible to finish the game moving only in moonwalk, right?*             RIGHT ?          wrong  "; break;
        case 1979: texte = "It is possible to finish the game moving only in moonwalk, right?*             right            WRONG ?"; break;
        case 1980: texte = "Correct! But you can try if you want."; break;
        case 1981: texte = "No! Well, you shall try..."; break;
        case 1982: texte = "It's in the past when you can win the most money by killing an enemy, right?*             RIGHT ?          wrong  "; break;
        case 1983: texte = "It's in the past when you can win the most money by killing an enemy, right*             right            WRONG ?"; break;
        case 1984: texte = "Correct! It's in the present, with red Rupees."; break;
        case 1985: texte = "No! It's in the present, with red Rupees."; break;
        case 1986: texte = "Your sword can defeat any opponent, exept a boss, in less that 6 blows, right?*             RIGHT ?          wrong  "; break;
        case 1987: texte = "Your sword can defeat any opponent, exept a boss, in less that 6 blows, right?*             right            WRONG ?"; break;
        case 1988: texte = "Correct! There are enemies that can't be killed with the sword."; break;
        case 1989: texte = "No! There are enemies that can't be killed with the sword."; break;
        case 1990: texte = "The puzzle in the desert had 6 stones, didn't it?*             RIGHT ?          wrong  "; break;
        case 1991: texte = "The puzzle in the desert had 6 stones, didn't it?*             right           WRONG ?"; break;
        case 1992: texte = "Correct! And I never could find the order..."; break;
        case 1993: texte = "No! You cheated to solve it, I'm sure..."; break;
        case 1994: texte = "You played more than "; break;
        case 1995: texte = " hours, right?**             RIGHT ?          wrong  "; break;
        case 1996: texte = "You played more than "; break;
        case 1997: texte = " hours, right?**             right            WRONG ?"; break;
        case 1998: texte = "Correct! It goes by fast, doesn't it?"; break;
        case 1999: texte = "No! It goes by fast, doesn't it?"; break;
        case 2000: texte = "The hens in the past are more patient than the ones in the present, right?*             RIGHT ?          wrong  "; break;
        case 2001: texte = "The hens in the past are more patient than the ones in the present, right?*             right            WRONG ?"; break;
        case 2002: texte = "Correct! You know your stuff..."; break;
        case 2003: texte = "No! You'll just have to check..."; break;
        case 2004: texte = "It was possible to catch 4 different fishes in the Lake Hylia, right?*             RIGHT ?          wrong  "; break;
        case 2005: texte = "It was possible to catch 4 different fishes in the Lake Hylia, right?*             right            WRONG ?"; break;
        case 2006: texte = "Correct! There were 6 different species."; break;
        case 2007: texte = "No! There were 6 different species, so it was possible to find 4."; break;
        case 2008: texte = "Santa Claus exists, is that true?**             RIGHT ?          wrong  "; break;
        case 2009: texte = "Santa Claus exists, is that true?**             right            WRONG ?"; break;
        case 2010: texte = "Correct! And you met him once."; break;
        case 2011: texte = "No! You met him once."; break;
        case 2012: texte = "In the past, the mountains had a total of 16 stones, right?*             RIGHT ?          wrong  "; break;
        case 2013: texte = "In the past, the mountains had a total of 16 stones, right?*             right            WRONG ?"; break;
        case 2014: texte = "Correct! There were 15 only, obviously."; break;
        case 2015: texte = "No! There were 15 only, obviously."; break;
        case 2016: texte = "There is a total of 42 carpets in this Casino, right? *             RIGHT ?          wrong  "; break;
        case 2017: texte = "There is a total of 42 carpets in this Casino, right? *             right            WRONG ?"; break;
        case 2018: texte = "Correct! There are 44."; break;
        case 2019: texte = "No! There are 44."; break;
        case 2020: texte = "Power gems can be swaped for 5 different type of items, right?*             RIGHT ?          wrong  "; break;
        case 2021: texte = "Power gems can be swaped for 5 different type of items, right?*             right            WRONG ?"; break;
        case 2022: texte = "Correct! I see you did not forget the frosty rock."; break;
        case 2023: texte = "No! You probably forgot the frosty rock."; break;
        case 2024: texte = "The green tunic gives you but one point of defense, right?*             RIGHT ?          wrong  "; break;
        case 2025: texte = "The green tunic gives you but one point of defense, right?*             right            WRONG ?"; break;
        case 2026: texte = "Correct! The green tunic is your first one and gives no point of defense."; break;
        case 2027: texte = "No! The green tunic is your first one and gives no point of defense."; break;
        case 2028: texte = "There were 5 mirrors in Zelda's bedroom, right?*             RIGHT ?          wrong  "; break;
        case 2029: texte = "There were 5 mirrors in Zelda's bedroom, right?*             right            WRONG ?"; break;
        case 2030: texte = "Correct! You gave her the fifth one actually."; break;
        case 2031: texte = "No! In fact you gave her the fifth one."; break;
        case 2032: texte = "The Pyramid in the past had 85 rooms, right?**             RIGHT ?          wrong  "; break;
        case 2033: texte = "The Pyramid in the past had 85 rooms, right?**             right            WRONG ?"; break;
        case 2034: texte = "Correct! 84 only."; break;
        case 2035: texte = "No! 84 only."; break;
        case 2036: texte = "The fire arrows are strongest than the ice ones, right?*             RIGHT ?          wrong  "; break;
        case 2037: texte = "The fire arrows are strongest than the ice ones, right?*             right            WRONG ?"; break;
        case 2038: texte = "Correct! The fire arrows have a strength of 10, the ice ones have 7."; break;
        case 2039: texte = "No! The fire arrows have a strength of 10, the ice ones have 7."; break;
        case 2040: texte = "Bombs cause as many damage as hammer blows, right?*             RIGHT ?          wrong  "; break;
        case 2041: texte = "Bombs cause as many damage as hammer blows, right?*             right            WRONG ?"; break;
        case 2042: texte = "Correct! Bombs have a strength of 5, the hammer of 3."; break;
        case 2043: texte = "No! Bombs have a strength of 5, the hammer of 3."; break;
        case 2044: texte = "What??? You defeated me???**             RIGHT ?          right  "; break;
        case 2045: texte = "What??? You defeated me???**             right            RIGHT ?"; break;
        case 2046: texte = "You have found the Shield of the Goddesses!!!*Now your life comes back constantly!!!"; break;
        case 2047: texte = "On this stone is written the story of Hyrule in ancient Hylian:"; break;
        case 2048: texte = "After the Goddesses Din, Nayru and Farore created Hyrule, an evil entity with an unequaled power came to occupy this land."; break;
        case 2049: texte = "Despite of their great powers, the Goddesses had to accept that they could never destroy this creature."; break;
        case 2050: texte = "...*The continuation of the story is not written here. Maybe on another stone?"; break;
        case 2051: texte = "You have found the Tunic of the Goddesses!!!*Now your magic comes back constantly!!!"; break;
        case 2052: texte = "On this stone is written the story of Hyrule in ancient Hylian:"; break;
        case 2053: texte = "Din, Nayru and Farore could not resolve to do nothing, and they challenged the evil entity."; break;
        case 2054: texte = "After a long and hopeless fight, they had to find a compromise and they managed to scatter the entity's power."; break;
        case 2055: texte = "However, in order to do so, they had to create devilish creatures holding fragments of the entity's power."; break;
        case 2056: texte = "What was left of the evil entity is locked in a human form, and shall not be set free as long as all the devilish creatures are not defeated."; break;
        case 2057: texte = "Welcome among us, do you want me to explain you how does this play work?*              YES ?            no  "; break;
        case 2058: texte = "Welcome among us, do you want me to explain you how does this play work?*              yes              NO ?"; break;
        case 2059: texte = "Enemies in this dungeon are very particular, each of their attack will make you lose twice more than the previous blow."; break;
        case 2060: texte = "Be extremly carefull, 7 blows will be enough to kill you."; break;
        case 2061: texte = "Plus, the number of enemy you kill, as for the number of type of enemy, are counted. A certain amount is needed to open some doors."; break;
        case 2062: texte = "Good luck Link, whatever happens everything end here."; break;
        case 2063: texte = "Eliminateat least 30 enemies of 4 various types and I will open the door."; break;
        case 2064: texte = "Good luck Link."; break;
        case 2065: texte = "You have defeated enough enemies, I shall open..."; break;
        case 2066: texte = "Eliminate at least 60 enemies of 10 various types and I will open the door."; break;
        case 2067: texte = "Eliminate at least 20 enemies de 3 various types and I will open the door."; break;
        case 2068: texte = "Eliminate at least 99 enemies of 12 various types and I will open the door."; break;
        case 2069: texte = "Eliminate at least 30 enemies of 12 various types and I will open the door."; break;
        case 2070: texte = "Eliminate at least 40 enemies of various 6 types and I will open the door."; break;
        case 2071: texte = "Eliminate at least 50 enemies of 7 various types and I will open the door."; break;
        case 2072: texte = "You have found the Mask of Oni Link !!! *Hold R then press L to transform yourself and become incredibly powerful."; break;
        case 2073: texte = "You have found the Mask of Oni Link !!! *Use 'O' to transform yourself and become incredibly powerful."; break;
        case 2074: texte = "Congratulations Link! You've defeated every single type of enemy... It's incredible..."; break;
        case 2075: texte = "I owe you a lot, do you want to be paid now?"; break;
        case 2076: texte = "I'm finally able to take back my original form, be ready to take a lot!*Farewell, Hero of Hyrule!"; break;
        case 2077: texte = "Hurry Link! Use the Sword of the Godesses to finish him off definitely!"; break;
        case 2078: texte = "Not on me, goofy..."; break;
        case 2079: texte = "Congratulations Link, let's go home now."; break;
        case 2080: texte = "Justice has been done. My Master is finally avenged."; break;
        case 2081: texte = "Out of my way!"; break;
        case 2082: texte = "What the hell are you doing?"; break;
        case 2083: texte = "Let me explain you the reason of our presence in the entity with no name's dungeon."; break;
        case 2084: texte = "After your departure from the Castle that followed my victory upon Ganon, Ganondorf gave me back the Triforce and told me his story."; break;
        case 2085: texte = "We quickly came to the conclusion that the man of the monster's encyclopedia was highly suspicious, so when we learned from a guard that you had gone to see him, we decided to come to your help."; break;
        case 2086: texte = "As we thought, only the power of the 3 Weapons of the Goddesses unified and used by the 3 Chosen ones could destroyed this plague forever."; break;
        case 2087: texte = "As for Ganondorf, he has nothing to see now with the monster we knew, there is no darkness in him anymore, and he is trustworthy."; break;
        case 2088: texte = "From now on Hyrule is in peace, for good. Monsters will never reappear again, Evil is definitely defeated."; break;
        case 2089: texte = "So tell me Link, what are you gonna do of your days off?"; break;
        case 2090: texte = "Hyrule was saved and every threat dispeled. After long adventures, the three heroes had accomplished their destiny. **The three Goddesses came back in Hyrule to congratulate them, and then left again, taking the Triforce with them. **The powerful Ganondorf became quickly the new chief of the guards and spent the rest of his days protecting the realm against enemies that never came."; break;
        case 2091: texte = "Princess Zelda was celebrated accross the entire country and far more away as being the sovereign that had brought peace on the world. **Link prefered to fly away from celebrity, he disappeared, and no one ever saw him in Hyrule again."; break;
        case 2092: texte = "After the events that occured in Termina, Princesse Zelda put an end to Link's exil, announcing to the people the victory of the hero on his evil alter-ego."; break;
        case 2093: texte = "But the Hylian knight, unable to accept his status of hero, left to live as an ermit in a forest given to him by the princess."; break;
        case 2094: texte = "The existence of Termina had to be kept secret, therefore the princess hid the events that took place there and let the people living in an illusory peace."; break;
        case 2095: texte = "But both of them perfectly knew that, from the bottom of hell, Ganon the immortal drawed his power from his"; break;
        case 2096: texte = "first wish to the Triforce, and rounded up his army with a view to invade Hyrule."; break;
        case 2097: texte = "Until the day when, after months spent watching out for an attack, an event came up and put an end to this endless waiting..."; break;
        case 2098: texte = "HELLOOO !!! *MY LORD LINK !!!"; break;
        case 2099: texte = "HELP : Press Select to consult the help."; break;
        case 2100: texte = "HELP : Press F1 to consult the help."; break;
        case 2101: texte = "Come back when you'll have a wallet and we'll talk business."; break;
        case 2102: texte = "We heard sounds of battle, and nothing more..."; break;
        case 2103: texte = "What, by all heavens, can have happened?"; break;
        case 2104: texte = "This door leads to a secret room. *Get the 9 ranks in the Records screen and come back after having get the second end to penetrate it."; break;
        case 2105: texte = "You may go in, Legendary Hero."; break;
        case 2106: texte = "Welcome in 3T's hidden room!"; break;
        case 2107: texte = "I am Vincent, I thought and encoded the game."; break;
        case 2108: texte = "Hi, I am Lobalz. *I helped invent the game, made some new graphics, tested the majority of the dungeons, and translated the texts."; break;
        case 2109: texte = "Hello, I am Raiden! *I took care of drawing the illustrations of the game(... and also the clouds on the maps, but who cares actually...)."; break;
        case 2110: texte = "We may find other drawings from me on the following adress : http://alandar.deviantart.com"; break;
        case 2111: texte = "Monsters sank my boat... *I'm sorry, you will have to swim now..."; break;

        default:
            texte = "TEXT ERROR";
    }

    return texte;
}

std::string Texte::getTexteFR(int id, std::string s){
    std::string texte = "";
    switch(id) {
        // 0 -> 99 : Carte
        case 0 : 
            texte = "Temple du Courage"; 
            break;
        case 1 : 
            texte = "Temple de la Sagesse"; 
            break;
        case 2 : 
            texte = "Temple de la Force"; 
            break;
        case 3 : 
            texte = "Ruines des Abysses"; 
            break;
        case 4 : 
            texte = "Pyramide Fantôme"; 
            break;
        case 5 : 
            texte = "Grande Pyramide"; 
            break;
        case 6 : 
            texte = "Temple de la Terre"; 
            break;
        case 7 : 
            texte = "Temple de l'Air"; 
            break;
        case 8 : 
            texte = "Temple de l'Eau"; 
            break;
        case 9 : 
            texte = "Temple du Feu"; 
            break;
        case 10 : 
            texte = "Temple des Déesses"; 
            break;
        case 11 : 
            texte = "Château d'Hyrule"; 
            break;
        case 12 : 
            texte = "Casino"; 
            break;
        case 13 : 
            texte = "Tour des Gemmes"; 
            break;
        case 14 : 
            texte = "Destination Finale"; 
            break;

        // 100 -> 199 : Encyclopedie
        case 100 :
            texte = "MONSTRES " + s;
            break;

        // 200 -> 399 : Generique
        case 200 : 
            texte = "ECRAN DE SELECTION";
            break;
        case 201 :
            texte = "1.";
            break;
        case 202 :
            texte = "2.";
            break;
        case 203 :
            texte = "3.";
            break;
        case 204 :
            texte = "OPTIONS";
            break;
        case 205 :
            texte = "RECORDS";
            break;
        case 206 :
            texte = "OPTIONS";
            break;
        case 207 :
            texte = "MUSIQUE";
            break;
        case 208 :
            texte = "SON";
            break;
        case 209 :
            texte = "RETOUR";
            break;
        case 210 :
            texte = "RECORDS";
            break;
        case 211 :
            texte = "MEILLEUR TEMPS : " + s;
            break;
        case 212 :
            texte = "RANG DES 100%";
            break;
        case 213 :
            texte = "RANG ULTIME";
            break;
        case 214 :
            texte = "RANG DE RAPIDITE";
            break;
        case 215 :
            texte = "RETOUR";
            break;
        case 216 :
            texte = "EFFACER";
            break;
        case 217 :
            texte = "EFFACER ?";
            break;
        case 218 :
            texte = "OUI";
            break;
        case 219 :
            texte = "NON";
            break;
        case 220 :
            texte = "CHARGER";
            break;
        case 221 :
            texte = "EFFACER";
            break;
        case 222 :
            texte = "ANNULER";
            break;
        case 223 :
#ifdef __vita__
            texte = "Retour au jeu : ¾3 - Suite : ¾5";
#else
            texte = "Retour au jeu : Entrée - Suite : Droite";
#endif
            break;
        case 224 :
#ifdef __vita__
            texte = "Lire / Ouvrir / Parler : ¾2";
#else
            texte = "Lire / Ouvrir / Parler : Espace";
#endif
            break;
        case 225 :
#ifdef __vita__
            texte = "Valider / Passer texte : ¾3";
#else
            texte = "Valider / Passer texte : Entrée";
#endif
            break;
        case 226 :
#ifdef __vita__
            texte = "Déplacer Link : ¾9 Gauche";
#else
            texte = "Déplacer Link : Flèches de direction";
#endif
            break;
        case 227 :
#ifdef __vita__
            texte = "Courir : Maintenir R"; 
#else
            texte = "Courir : Shift maintenu ou Capslock"; 
#endif
            break;
        case 228 :
#ifdef __vita__
            texte = "Coup d'épée : ¾4";
#else
            texte = "Coup d'épée : W ou Z";
#endif
            break;
        case 229 :
#ifdef __vita__
            texte = "Attaque Tornade : ¾4 maintenu puis lâché";
#else
            texte = "Attaque Tornade : W ou Z maintenu puis lâché";
#endif
            break;
        case 230 :
#ifdef __vita__
            texte = "Menu de sélection d'objet : ¾5";
#else
            texte = "Menu de sélection d'objet : Entrée";
#endif
            break;
        case 231 :
#ifdef __vita__
            texte = "Utiliser l'objet sélectionné : ¾1";
#else
            texte = "Utiliser l'objet sélectionné : X";
#endif
            break;
        case 232 :
#ifdef __vita__
            texte = "Porter : ¾3"; 
#else
            texte = "Porter : C"; 
#endif
            break;
        case 233 :
#ifdef __vita__
            texte = "Afficher la carte : L (extérieur ou donjons)";
#else
            texte = "Afficher la carte : P (extérieur ou donjons)";
#endif
            break;
        case 234 :
#ifdef __vita__
            texte = "Afficher la carte : L (dans les donjons)";
#else
            texte = "Afficher la carte : P (dans les donjons)";
#endif
            break;
        case 235 :
#ifdef __vita__
        texte = "Afficher les monstres vaincus : ¾6"; 
#else
        texte = "Afficher les monstres vaincus : M"; 
#endif
            break;
        case 236 :
#ifdef __vita__
        texte = "Afficher la liste des poissons péchés : ¾8"; 
#else
        texte = "Afficher la liste des poissons péchés : L"; 
#endif
            break;
        case 237 :
#ifdef __vita__
        texte = "Afficher les items de troc : ¾7"; 
#else
        texte = "Afficher les items de troc : I"; 
#endif
            break;
        case 238 :
#ifdef __vita__
        texte = "Transformation Oni Link : L + R"; 
#else
        texte = "Transformation Oni Link : O"; 
#endif
            break;
        case 239 :
#ifdef __vita__
            texte = "Regarder autour : ¾9 Droite";
#else
            texte = "Regarder autour : Ctrl et direction";
#endif
            break;
        case 240 :
#ifdef __vita__
            texte = "";
#else
            texte = "Agrandir / Rétrécir: Ctrl et Entrée";
#endif
            break;
        case 241 :
#ifdef __vita__
            texte = "Sauvegarder / Quitter : Start";
#else
            texte = "Sauvegarder / Quitter : Echap";
#endif
            break;
        case 242 :
            texte = "AIDE 1/3";
            break;
        case 243 :
            texte = "AIDE 1/2";
            break;
        case 244 :
#ifdef __vita__
            texte = "Utiliser l'objet sélectionné : ¾1";
#else
            texte = "Utiliser l'objet sélectionné : X";
#endif
            break;
        case 245 :
#ifdef __vita__
            texte = "Porter : ¾3"; 
#else
            texte = "Porter : C"; 
#endif
            break;
        case 246 :
#ifdef __vita__
            texte = "Afficher la carte : L (extérieur ou donjons)";
#else
            texte = "Afficher la carte : P (extérieur ou donjons)";
#endif
            break;
        case 247 :
#ifdef __vita__
            texte = "Afficher la carte : L (dans les donjons)";
#else
            texte = "Afficher la carte : P (dans les donjons)";
#endif
            break;
        case 248 :
#ifdef __vita__
        texte = "Afficher les monstres vaincus : ¾6"; 
#else
        texte = "Afficher les monstres vaincus : M"; 
#endif
            break;
        case 249 :
#ifdef __vita__
        texte = "Afficher la liste des poissons péchés : ¾8"; 
#else
        texte = "Afficher la liste des poissons péchés : L"; 
#endif
            break;
        case 250 :
#ifdef __vita__
        texte = "Afficher les items de troc : ¾7"; 
#else
        texte = "Afficher les items de troc : I"; 
#endif
            break;
        case 251 :
#ifdef __vita__
        texte = "Transformation Oni Link : L + R"; 
#else
        texte = "Transformation Oni Link : O"; 
#endif
            break;
        case 252 :
            texte = "AIDE 2/3";
            break;
        case 253 :
#ifdef __vita__
            texte = "Retour au jeu : ¾3 - Suite : ¾5";
#else
            texte = "Retour au jeu : Entrée - Suite : Droite";
#endif
            break;
        case 254 :
#ifdef __vita__
            texte = "Regarder autour : ¾9 Droite";
#else
            texte = "Regarder autour : Ctrl et direction";
#endif
            break;
        case 255 :
            texte = "Agrandir / Rétrécir : Ctrl et Entrée";
            break;
        case 256 :
            texte = "AIDE 2/2";
            break;
        case 257 :
#ifdef __vita__
            texte = "Retour au jeu : ¾3 - Précédent : ¾7";
#else
            texte = "Retour au jeu : Entrée - Précédent : Gauche";
#endif
            break;
        case 258 :
            texte = "AIDE 3/3";
            break;
        case 259 :
            texte = "SAC DE TROC";
            break;
        case 260 :
            texte = s + " SACS DE RIZ";
            break;
        case 261 :
            texte = s + " SAC DE RIZ";
            break;
        case 262 :
            texte = s + " BOCAUX D'EPICES";
            break;
        case 263 :
            texte = s + " BOCAL D'EPICES";
            break;
        case 264 :
            texte = s + " SACS D'OLIVES";
            break;
        case 265 :
            texte = s + " SAC D'OLIVES";
            break;
        case 266 :
            texte = s + " PERLES";
            break;
        case 267 :
            texte = s + " PERLE";
            break;
        case 268 :
            texte = s + " PLUMES";
            break;
        case 269 :
            texte = s + " PLUME";
            break;
        case 270 :
            texte = s + " POULETS";
            break;
        case 271 :
            texte = s + " POULET";
            break;
        case 272 :
            texte = s + " TAPISSERIES";
            break;
        case 273 :
            texte = s + " TAPISSERIE";
            break;
        case 274 :
            texte = s + " AMULETTES";
            break;
        case 275 :
            texte = s + " AMULETTE";
            break;
        case 276 :
            texte = s + " PARFUMS";
            break;
        case 277 :
            texte = s + " PARFUM";
            break;
        case 278 :
            texte = s + " ROCS MAGMA";
            break;
        case 279 :
            texte = s + " ROC MAGMA";
            break;
        case 280 :
            texte = s + " ROCS GIVRE";
            break;
        case 281 :
            texte = s + " ROC GIVRE";
            break;
        case 282 :
            texte = s + " POIVRON";
            break;
        case 283 :
            texte = s + " ROUAGE";
            break;
        case 284 :
            texte = s + " JAUGE";
            break;
        case 285 :
            texte = s + " ROUE";
            break;
        case 286 :
            texte = s + " SOURCE D'ENERGIE";
            break;
        case 287 :
            texte = "RANG : Héros Légendaire";
            break;
        case 288 :
            texte = "RANG : Héros des deux Mondes";
            break;
        case 289 :
            texte = "RANG : Héros d'Hyrule";
            break;
        case 290 :
            texte = "RANG : Héros de Termina";
            break;
        case 291 :
            texte = "RANG : Héros du Temps";
            break;
        case 292 :
            texte = "RANG : INCONNU";
            break;
        case 293 :
            texte = "Finir le jeu à 100%.";
            break;
        case 294 :
            texte = "RANG : Epéiste Légendaire";
            break;
        case 295 :
            texte = "RANG : Maître Epéiste";
            break;
        case 296 :
            texte = "RANG : Frimeur";
            break;
        case 297 :
            texte = "RANG : Crâneur";
            break;
        case 298 :
            texte = "RANG : Orgueilleux";
            break;
        case 299 :
            texte = "RANG : INCONNU";
            break;
        case 300 :
            texte = "Finir le jeu sans mourir,";
            break;
        case 301 :
            texte = "avec 12 coeurs au maximum,";
            break;
        case 302 :
            texte = "et sans flacons.";
            break;
        case 303 :
            texte = "RANG : Marathonien Légendaire";
            break;
        case 304 :
            texte = "RANG : Marathonien des deux Mondes";
            break;
        case 305 :
            texte = "RANG : Marathonien d'Hyrule";
            break;
        case 306 :
            texte = "RANG : Marathonien de Termina";
            break;
        case 307 :
            texte = "RANG : Marathonien du Temps";
            break;
        case 308 :
            texte = "Finir le jeu en moins de sept";
            break;
        case 309 :
            texte = "heures.";
            break;
        case 310 :
            texte = "SCORES :";
            break;
        case 311 :
            texte = "Temps de jeu : " + s;
            break;
        case 312 :
            texte = "Mort " + s;
            break;
        case 313 :
            texte = "1/4 Coeurs : " + s;
            break;
        case 314 :
            texte = "Gemmes force : " + s;
            break;
        case 315 :
            texte = "Objets: " + s + " / 139";
            break;
        case 316 :
            texte = "Objets de troc : " + s + " / 45";
            break;
        case 317 :
            texte = "Poissons : " + s + " / 30";
            break;
        case 318 :
            texte = "Ennemis : " + s + " / 100";
            break;
        case 319 :
            texte = "Tu as fini ce jeu à " + s + "%, félicitation !";
            break;
        case 320 :
            texte = "RANG : ";
            break;
        case 321 :
            texte = " - Epéiste Légendaire";
            break;
        case 322 :
            texte = " - Maître Epéiste";
            break;
        case 323 :
            texte = " - Orgueilleux";
            break;
        case 324 :
            texte = " - Héros Légendaire";
            break;
        case 325 :
            texte = " - Héros d'Hyrule";
        case 326 :
            texte = " - Héros des deux Mondes";
            break;
        case 327 :
            texte = " - Héros du Temps";
            break;
        case 328 :
            texte = " - Perfectionniste";
            break;
        case 329 :
            texte = " - Fan de Zelda";
            break;
        case 330 :
            texte = " - Pro du clavier";
            break;
        case 331 :
            texte = " - Pro du pad";
            break;
        case 332 :
            texte = " - Confirmé";
            break;
        case 333 :
            texte = " - Débutant";
            break;
        case 334 :
            texte = " - Mort-vivant";
            break;
        case 335 :
            texte = " - Kamikaze";
            break;
        case 336 :
            texte = " - Marathonien Légendaire";
            break;
        case 337 :
            texte = " - Marathonien d'Hyrule";
            break;
        case 338 :
            texte = " - Marathonien des deux Mondes";
            break;
        case 339 :
            texte = " - Marathonien du Temps";
            break;
        case 400 :
            texte = "ARC";
            break;
        case 401 :
            texte = "GRAND ARC DES FEES";
            break;
        case 402 :
            texte = "GRAPPIN";
            break;
        case 403 :
            texte = "BOMBES";
            break;
        case 404 :
            texte = "FLECHE DE FEU";
            break;
        case 405 :
            texte = "GEMME ROUGE";
            break;
        case 406 :
            texte = "ENCLUME";
            break;
        case 407 :
            texte = "FER A CHEVAL";
            break;
        case 408 :
            texte = "BIJOU PRECIEUX";
            break;
        case 409 :
            texte = "LETTRE";
            break;
        case 410 :
            texte = "ALLIANCE";
            break;
        case 411 :
            texte = "MARTEAU";
            break;
        case 412 :
            texte = "BAGUETTE DE FEU";
            break;
        case 413 :
            texte = "BAGUETTE DE GLACE";
            break;
        case 414 :
            texte = "LANTERNE";
            break;
        case 415 :
            texte = "FLECHE DE GLACE";
            break;
        case 416 :
            texte = "GEMME BLEUE";
            break;
        case 417 :
            texte = "VIEILLE BOTTE";
            break;
        case 418 :
            texte = "MARTEAU LOURD";
            break;
        case 419 :
            texte = "CLOCHETTE";
            break;
        case 420 :
            texte = "HACHE BARBARE";
            break;
        case 421 :
            texte = "CORDE EXPLICITE";
            break;
        case 422 :
            texte = "PLAN DU PONT";
            break;
        case 423 :
            texte = "MARTEAU MAGIQUE";
            break;
        case 424 :
            texte = "OCARINA DU TEMPS";
            break;
        case 425 :
            texte = "CANNE A PECHE";
            break;
        case 426 :
            texte = "SUPER CANNE A PECHE";
            break;
        case 427 :
            texte = "MEGA CANNE A PECHE";
            break;
        case 428 :
            texte = "FLECHE DE LUMIERE";
            break;
        case 429 :
            texte = "GEMME JAUNE";
            break;
        case 430 :
            texte = "VIN GRAND CRU";
            break;
        case 431 :
            texte = "POUDRE D'OR";
            break;
        case 432 :
            texte = "MIROIR MAGIQUE";
            break;
        case 433 :
            texte = "PETITE CUILLERE";
            break;
        case 434 :
            texte = "CRANE";
            break;
        case 435 :
            texte = "DETTE IMPAYEE";
            break;
        case 436 : 
            texte = "SCIE";
            break;
        case 437 :
            texte = "GEMME VERTE";
            break;
        case 438 :
            texte = "CARTE DE VOYAGE";
            break;
        case 439 : 
            texte = "BALAIS";
            break;
        case 440 :
            texte = "CONFITURE FRAISE";
            break;
        case 441 :
            texte = "CROISSANT";
            break;
        case 442 :
            texte = "BIERE";
            break;
        case 443 :
            texte = "CLOU";
            break;
        case 444 :
            texte = "FLACON VIDE";
            break;
        case 445 :
            texte = "POTION ROUGE";
            break;
        case 446 :
            texte = "POTION VERTE";
            break;
        case 447 :
            texte = "POTION BLEUE";
            break;
        case 448 :
            texte = "EQUIPEMENT :";
            break;
        case 449 :
            texte = "LANGUE";
            break;
        case 450 :
            texte = "Française";
            break;
            
        // 500 -> 599 : Poissons
        case 500 :
            texte = "POISSONS " + s;
            break;
        case 501 : 
            texte = "Ecrevisse"; 
            break;
        case 502 : 
            texte = "Eperlan"; 
            break;
        case 503 : 
            texte = "Poisson-zèbre"; 
            break;
        case 504 : 
            texte = "Gobie"; 
            break;
        case 505 : 
            texte = "Crabe"; 
            break;
        case 506 : 
            texte = "Pibale"; 
            break;
        case 507 : 
            texte = "Vairon"; 
            break;
        case 508 : 
            texte = "Carassin doré"; 
            break;
        case 509 : 
            texte = "Ablette"; 
            break;
        case 510 : 
            texte = "Goujon";
            break;
        case 511 : 
            texte = "Loche"; 
            break;
        case 512 : 
            texte = "Epinoche"; 
            break;
        case 513 : 
            texte = "Grémille"; 
            break;
        case 514 : 
            texte = "Blennie"; 
            break;
        case 515 : 
            texte = "Magicarpe"; 
            break;
        case 516 : 
            texte = "Truite"; 
            break;
        case 517 : 
            texte = "Ayu"; 
            break;
        case 518 : 
            texte = "Perche noire"; 
            break;
        case 519 : 
            texte = "Anguille"; 
            break;
        case 520 : 
            texte = "Poisson-chat"; 
            break;
        case 521 : 
            texte = "Black-bass"; 
            break;
        case 522 : 
            texte = "Huchon"; 
            break;
        case 523 : 
            texte = "Barbeau"; 
            break;
        case 524 : 
            texte = "Lamproie"; 
            break;
        case 525 : 
            texte = "Hotu"; 
            break;
        case 526 : 
            texte = "Saumon"; 
            break;
        case 527 : 
            texte = "Esturgeon"; 
            break;
        case 528 :
            texte = "Omble-chevalier"; 
            break;
        case 529 : 
            texte = "Carpe"; 
            break;
        case 530 : 
            texte = "Silure"; 
            break;

        case 600: texte = "Objet de troc*Parle à la bonne personne pour échanger."; break;
        case 601: texte = "Tu ne peux pas pêcher ici, cherche un ponton."; break;
        case 602: texte = "Tu as trouvé un quart de coeur !!!"; break;
        case 603: texte = "Encore "; break;
        case 604: texte = " et tu gagneras un coeur supplémentaire !!!"; break;
        case 605: texte = "Ton nombre de coeurs vient d'augmenter !!!"; break;
        case 606: texte = "Ca te prend souvent de parler aux arbres ???"; break;
        case 607: texte = "Maison de Link**Ne pas approcher."; break;
        case 608: texte = "N : Vers le village Cocorico"; break;
        case 609: texte = "E : Vers la cité d'Hyrule"; break;
        case 610: texte = "Tu n'as rien attrapé."; break;
        case 611: texte = "Tu as pêché une écrevisse!"; break;
        case 612: texte = "Tu as pêché un éperlan!"; break;
        case 613: texte = "Tu as pêché un poisson zèbre!"; break;
        case 614: texte = "Tu as pêché un gobie!"; break;
        case 615: texte = "Tu as pêché un crabe!"; break;
        case 616: texte = "Tu as pêché une pibale!"; break;
        case 617: texte = "Tu as pêché un vairon!"; break;
        case 618: texte = "Tu as pêché un carassin doré!"; break;
        case 619: texte = "Tu as pêché une ablette!"; break;
        case 620: texte = "Tu as pêché un goujon!"; break;
        case 621: texte = "Tu as pêché une loche!"; break;
        case 622: texte = "Tu as pêché une épinoche!"; break;
        case 623: texte = "Tu as pêché une grémille!"; break;
        case 624: texte = "Tu as pêché une blennie!"; break;
        case 625: texte = "Tu as pêché un magicarpe!"; break;
        case 626: texte = "Mais rien ne se passe..."; break;
        case 627: texte = "Tu as pêché une truite!*C'est un gros poisson!"; break;
        case 628: texte = "Tu as pêché un ayu!*C'est un gros poisson!"; break;
        case 629: texte = "Tu as pêché une perche noire!*C'est un gros poisson!"; break;
        case 630: texte = "Tu as pêché une anguille!*C'est un gros poisson!"; break;
        case 631: texte = "Tu as pêché un poisson-chat!*C'est un gros poisson!"; break;
        case 632: texte = "Tu as pêché un black-bass!*C'est un gros poisson!"; break;
        case 633: texte = "Tu as pêché un huchon!*C'est un gros poisson!"; break;
        case 634: texte = "Tu as pêché un barbeau!*C'est un gros poisson!"; break;
        case 635: texte = "Tu as pêché une lamproie!*C'est un gros poisson!"; break;
        case 636: texte = "Tu as pêché un hotu!*C'est un gros poisson!"; break;
        case 637: texte = "Tu as pêché un saumon!*C'est un poisson énorme!"; break;
        case 638: texte = "Tu as pêché un esturgeon!*C'est un poisson énorme!"; break;
        case 639: texte = "Tu as pêché un omble chevalier!*C'est un poisson énorme!"; break;
        case 640: texte = "Tu as pêché une carpe!*C'est un poisson énorme!"; break;
        case 641: texte = "Tu as pêché un silure!*C'est un poisson énorme!"; break;
        case 642: texte = "Tu as trouvé une gemme de force !**Troque-les en ville contre des prix."; break;
        case 643: texte = "Bonjour Link!*Tu fais une drôle de tête, tu dormais ?"; break;
        case 644: texte = "La princesse veux te voir de toute urgence au château!"; break;
        case 645: texte = "..."; break;
        case 646: texte = "..."; break;
        case 647: texte = "Le château. A l'est d'ici, tu n'as tout de même pas oublié ?"; break;
        case 648: texte = "Hum Hum..."; break;
        case 649: texte = "TUTORIEL : Appuyez sur ¾2 près de quelqu'un pour lui parler, ou près d'une pancarte pour la lire."; break;
        case 650: texte = "TUTORIEL : Appuyez sur Espace près de quelqu'un pour lui parler, ou près d'une pancarte pour la lire."; break;
        case 651: texte = "Tu n'as appris aucun thème."; break;
        case 652: texte = "- CHANT DE L'ENVOL*- Ne rien jouer"; break;
        case 653: texte = "- Chant de l'envol*- NE RIEN JOUER"; break;
        case 654: texte = "- CHANT DE L'ENVOL*- Chant du temps inversé*- Ne rien jouer"; break;
        case 655: texte = "- Chant de l'envol*- CHANT DU TEMPS INVERSE*- Ne rien jouer"; break;
        case 656: texte = "- Chant de l'envol*- Chant du temps inversé*- NE RIEN JOUER"; break;
        case 657: texte = "- CHANT DE L'ENVOL*- Chant du temps inversé*- Chant du temps accéléré*- Ne rien jouer"; break;
        case 658: texte = "- Chant de l'envol*- CHANT DU TEMPS INVERSE*- Chant du temps accéléré*- Ne rien jouer"; break;
        case 659: texte = "- Chant de l'envol*- Chant du temps inversé*- CHANT DU TEMPS ACCELERE*- Ne rien jouer"; break;
        case 660: texte = "- Chant de l'envol*- Chant du temps inversé*- Chant du temps accéléré*- NE RIEN JOUER"; break;
        case 661: texte = "- CHANT DU TEMPS INVERSE*- Ne rien jouer"; break;
        case 662: texte = "- Chant du temps inversé*- NE RIEN JOUER"; break;
        case 663: texte = "- CHANT DU TEMPS ACCELERE*- Ne rien jouer"; break;
        case 664: texte = "- Chant du temps accéléré*- NE RIEN JOUER"; break;
        case 665: texte = "- CHANT DE L'ENVOL*- Chant du temps accéléré*- Ne rien jouer"; break;
        case 666: texte = "- Chant de l'envol*- CHANT DU TEMPS ACCELERE*- Ne rien jouer"; break;
        case 667: texte = "- Chant de l'envol*- Chant du temps accéléré*- NE RIEN JOUER"; break;
        case 668: texte = "- CHANT DU TEMPS INVERSE*- Chant du temps accéléré*- Ne rien jouer"; break;
        case 669: texte = "- Chant du temps inversé*- CHANT DU TEMPS ACCELERE*- Ne rien jouer"; break;
        case 670: texte = "- Chant du temps inversé*- Chant du temps accéléré*- NE RIEN JOUER"; break;
        case 671: texte = "Sans effet..."; break;
        case 672: texte = "Domaine de Link*Propriété privée"; break;
        case 673: texte = "Cité d'Hyrule"; break;
        case 674: texte = "Il n'y a pas l'air d'avoir de poissons ici..."; break;
        case 675: texte = "N : Vers le Château d'Hyrule"; break;
        case 676: texte = "Le château est plus au nord, dépêche-toi!"; break;
        case 677: texte = "Le château est de l'autre côté du pont, hâte-toi!"; break;
        case 678: texte = "La princesse t'attend au château, au nord d'ici."; break;
        case 679: texte = "Tu n'as pas assez."; break;
        case 680: texte = "Reviens si tu changes d'avis."; break;
        case 681: texte = "Un rouage contre un poulet et 100 rubis ?**              OUI ?            non  "; break;
        case 682: texte = "Un rouage contre un poulet et 100 rubis ?**              oui              NON ?"; break;
        case 683: texte = "Tu as obtenu un rouage!*Va vite le donner à l'homme près des cascades!"; break;
        case 684: texte = "Un quart de coeur contre un roc magma et un roc givre ?*              OUI ?            non  "; break;
        case 685: texte = "Un quart de coeur contre un roc magma et un roc givre ?*              oui              NON ?"; break;
        case 686: texte = "Désolé, je n'ai plus rien en stock."; break;
        case 687: texte = "Une bourse pouvant contenir 200 rubis contre une plume et 10 rubis ?*              OUI ?            non  "; break;
        case 688: texte = "Une bourse pouvant contenir 200 rubis contre une plume et 10 rubis ?*              oui              NON ?"; break;
        case 689: texte = "Tu as obtenu une bourse moyenne!*Tu vas pouvoir transporter jusqu'à 200 rubis!"; break;
        case 690: texte = "Une bourse pouvant contenir 500 rubis contre une tapisserie et 100 rubis ?*              OUI ?            non  "; break;
        case 691: texte = "Une bourse pouvant contenir 500 rubis contre une tapisserie et 100 rubis ?*              oui              NON ?"; break;
        case 692: texte = "Tu as obtenu une grande bourse!*Tu vas pouvoir transporter jusqu'à 500 rubis!!!"; break;
        case 693: texte = "Une bourse pouvant contenir 999 rubis contre une amulette, un roc magma et 250 rubis ?*              OUI ?            non  "; break;
        case 694: texte = "Une bourse pouvant contenir 999 rubis contre une amulette, un roc magma et 250 rubis ?*              oui              NON ?"; break;
        case 695: texte = "Tu as obtenu une énorme bourse!!!*Tu vas pouvoir transporter jusqu'à 999 rubis!!!"; break;
        case 696: texte = "Un poulet contre 2 sacs de riz et 3 sacs d'olives ?**              OUI ?            non  "; break;
        case 697: texte = "Un poulet contre 2 sacs de riz et 3 sacs d'olives ?**              oui              NON ?"; break;
        case 698: texte = "Tu as obtenu un poulet!"; break;
        case 699: texte = "Tu ne peux pas en porter plus..."; break;
        case 700: texte = "Une plume contre 2 bocaux d'épices et 2 sacs d'olives ?*              OUI ?            non  "; break;
        case 701: texte = "Une plume contre 2 bocaux d'épices et 2 sacs d'olives ?*              oui              NON ?"; break;
        case 702: texte = "Tu as obtenu une plume!"; break;
        case 703: texte = "Un sac de riz contre 15 rubis ?**              OUI ?            non  "; break;
        case 704: texte = "Un sac de riz contre 15 rubis ?**              oui              NON ?"; break;
        case 705: texte = "Tu as obtenu un sac de riz!"; break;
        case 706: texte = "Un sac d'olives contre 10 rubis ?**              OUI ?            non  "; break;
        case 707: texte = "Un sac d'olives contre 10 rubis ?**              oui              NON ?"; break;
        case 708: texte = "Tu as obtenu un sac d'olives!"; break;
        case 709: texte = "J'ai l'impression d'avoir passé ma vie à balayer...*Un de ces jours je partirai bien en voyage pour changer..."; break;
        case 710: texte = "C'est une carte de voyage que tu as là ? *Tu veux bien me la donner ? Je rêve de faire du tourisme!"; break;
        case 711: texte = "Je t'offre mon balai en échange, tu es d'accord ?*              OUI ?            non  "; break;
        case 712: texte = "Je t'offre mon balai en échange, tu es d'accord ?*              oui              NON ?"; break;
        case 713: texte = "Merci! Voici mon balai en récompense. C'est un très bon balai, il est dans ma famille depuis des siècles, tu fais une affaire!"; break;
        case 714: texte = "J'imagine que je n'ai plus qu'à balayer dans ce cas..."; break;
        case 715: texte = "Tu as troqué la carte de voyage contre un balai!"; break;
        case 716: texte = "Bien, où vais-je partir ?"; break;
        case 717: texte = "Parfois dans mes rêves je les mange à la broche..."; break;
        case 718: texte = "Cette ville regorge de boutiques en tout genre, dommage qu'aucune d'entre elles ne m'intéresse..."; break;
        case 719: texte = "Depuis que la paix est revenue, la princesse Zelda a fait énormément pour Hyrule. Il n'y aurait pas de villes aussi prospères que celle-ci sans elle."; break;
        case 720: texte = "Le troc est le seul moyen de se procurer certains objets rares, ou de quoi faire sa cuisine."; break;
        case 721: texte = "Ma maman me dit toujours de ne pas jouer avec les poules... Pourquoi ?"; break;
        case 722: texte = "La princesse tient à ce que nous assurions la sécurité de la ville... Tout le monde sait pourtant que Ganon est mort..."; break;
        case 723: texte = "Je préférerais dormir au château que monter la garde ici..."; break;
        case 724: texte = "La vie est belle en Hyrule depuis que Ganon n'est plus une menace, merci encore Link!"; break;
        case 725: texte = "Depuis le vol au château, la princesse a doublé la garde... et me revoilà de corvée..."; break;
        case 726: texte = "Engagez-vous... Rengagez-vous qu'ils disaient..."; break;
        case 727: texte = "J'ai entendu dire qu'un objet de valeur a été volé au palais, et depuis la princesse serait devenue complètement parano..."; break;
        case 728: texte = "Ca devait être un objet auquel elle tenait beaucoup... Un miroir de sa collection sans doute..."; break;
        case 729: texte = "Zzzzz... Zzzzz..."; break;
        case 730: texte = "N : Vers le château de Ganon"; break;
        case 731: texte = "La perle de Lune contre une roue, une jauge, une source d'énergie et 100 Ganon d'or ?*              OUI ?            non  "; break;
        case 732: texte = "La perle de Lune contre une roue, une jauge, une source d'énergie et 100 Ganon d'or ?*              oui              NON ?"; break;
        case 733: texte = "Tu as obtenu la perle de Lune!*Tu retrouves ton apparence normale et l'usage de ton équipement!"; break;
        case 734: texte = "Une bourse pouvant contenir 200 Ganon d'or contre une perle et 10 Ganon d'or ?*              OUI ?            non  "; break;
        case 735: texte = "Une bourse pouvant contenir 200 Ganon d'or contre une perle et 10 Ganon d'or ?*              oui              NON ?"; break;
        case 736: texte = "Tu as obtenu une bourse moyenne!*Tu vas pouvoir transporter jusqu'à 200 Ganon d'or!"; break;
        case 737: texte = "Une bourse pouvant contenir 500 Ganon d'or contre une amulette et 100 Ganon d'or ?*              OUI ?            non  "; break;
        case 738: texte = "Une bourse pouvant contenir 500 Ganon d'or contre une amulette et 100 Ganon d'or ?*              oui              NON ?"; break;
        case 739: texte = "Tu as obtenu une grande bourse!*Tu vas pouvoir transporter jusqu'à 500 Ganon d'or!!!"; break;
        case 740: texte = "Une bourse pouvant contenir 999 Ganon d'or contre un parfum, un roc givre et 250 Ganon d'or ?*              OUI ?            non  "; break;
        case 741: texte = "Une bourse pouvant contenir 999 Ganon d'or contre un parfum, un roc givre et 250 Ganon d'or ?*              oui              NON ?"; break;
        case 742: texte = "Tu as obtenu une énorme bourse!!!*Tu vas pouvoir transporter jusqu'à 999 Ganon d'or!!!"; break;
        case 743: texte = "Une roue contre 3 bocaux d'épices ?**              OUI ?            non  "; break;
        case 744: texte = "Une roue contre 3 bocaux d'épices ?**              oui              NON ?"; break;
        case 745: texte = "Tu as obtenu une roue!*...*Super..."; break;
        case 746: texte = "Un sac de bombes contre 1 poivron et 3 bocaux d'épices ?**              OUI ?            non  "; break;
        case 747: texte = "Un sac de bombes contre 1 poivron et 3 bocaux d'épices ?**              oui              NON ?"; break;
        case 748: texte = "Tu as obtenu un sac de bombes!*Tu vas pouvoir déblayer des nouveaux chemins!"; break;
        case 749: texte = "Un roc magma contre une tapisserie, une amulette et un parfum ?*              OUI ?            non  "; break;
        case 750: texte = "Un roc magma contre une tapisserie, une amulette et un parfum ?*              oui              NON ?"; break;
        case 751: texte = "Tu as obtenu un roc magma!"; break;
        case 752: texte = "Des perles contre 5 bocaux d'épices et 5 Ganon d'or ?**              OUI ?            non  "; break;
        case 753: texte = "Des perles contre 5 bocaux d'épices et 5 Ganon d'or ?**              oui              NON ?"; break;
        case 754: texte = "Tu as obtenu des perles!"; break;
        case 755: texte = "Un bocal d'épices contre 10 Ganon d'or ?**              OUI ?            non  "; break;
        case 756: texte = "Un bocal d'épices contre 10 Ganon d'or ?**              oui              NON ?"; break;
        case 757: texte = "Tu as obtenu un bocal d'épices!"; break;
        case 758: texte = "Hi! Hi! Hiiiiiiii!"; break;
        case 759: texte = "L'autre soir le barman n'avait plus de bière...*Ganon est devenu rouge de colère et a tout détruit...*Au final plus personne n'a rien à boire..."; break;
        case 760: texte = "Les maisons détruites étaient celles d'opposants à Ganon..."; break;
        case 761: texte = "Le bar est détruit lui aussi, mais... ...pour d'autres raisons..."; break;
        case 762: texte = "La place du marché est la principale activité de la ville maintenant que le bar a été détruit..."; break;
        case 763: texte = "Tu as obtenu la perle de Lune ?*Enfin vu le résultat c'était peut-être pas une affaire..."; break;
        case 764: texte = "La perle de Lune permet de retrouver une apparence humaine, mais le marchand qui en a une la vend beaucoup trop chère..."; break;
        case 765: texte = "N : Terres Sacrées - Camping interdit"; break;
        case 766: texte = "Une bourse pouvant contenir 200 pièces d'or contre un poulet et 10 pièces d'or ?*              OUI ?            non  "; break;
        case 767: texte = "Une bourse pouvant contenir 200 pièces d'or contre un poulet et 10 pièces d'or ?*              oui              NON ?"; break;
        case 768: texte = "Tu as obtenu une bourse moyenne!*Tu vas pouvoir transporter jusqu'à 200 pièces d'or!"; break;
        case 769: texte = "Une bourse pouvant contenir 500 pièces d'or contre un parfum et 100 pièces d'or ?*              OUI ?            non  "; break;
        case 770: texte = "Une bourse pouvant contenir 500 pièces d'or contre un parfum et 100 pièces d'or ?*              oui              NON ?"; break;
        case 771: texte = "Tu as obtenu une grande bourse!*Tu vas pouvoir transporter jusqu'à 500 pièces d'or!!!"; break;
        case 772: texte = "Une bourse pouvant contenir 999 pièces d'or contre une tapisserie, un roc magma et 250 pièces d'or ?*              OUI ?            non  "; break;
        case 773: texte = "Une bourse pouvant contenir 999 pièces d'or contre une tapisserie, un roc magma et 250 pièces d'or ?*              oui              NON ?"; break;
        case 774: texte = "Tu as obtenu une énorme bourse!!!*Tu vas pouvoir transporter jusqu'à 999 pièces d'or!!!"; break;
        case 775: texte = "Une amulette contre 1 poulet et 2 sacs d'olives ?*              OUI ?            non  "; break;
        case 776: texte = "Une amulette contre 1 poulet et 2 sacs d'olives ?*              oui              NON ?"; break;
        case 777: texte = "Tu as obtenu une amulette!"; break;
        case 778: texte = "Une plume contre un bocal d'épices et un sac d'olives ?*              OUI ?            non  "; break;
        case 779: texte = "Une plume contre un bocal d'épices et un sac d'olives ?*              oui              NON ?"; break;
        case 780: texte = "Avec tous ces loups, quitter le village est devenu très dangereux..."; break;
        case 781: texte = "Tes armes ressemblent à celles des chevaliers...*Tu as déjà affronté des loups avec ?"; break;
        case 782: texte = "Je déteste les poules, mais si les loups pénètrent dans le village, ils n'oseront peut-être pas approcher..."; break;
        case 783: texte = "Les torches aux entrées du village tiennent les loups à l'écart, mais ils approchent de plus en plus chaque jour..."; break;
        case 784: texte = "Le chef du village a fait construire un bar dernièrement... D'après les rumeurs il aurait agit ainsi pour attirer les chevaliers hyliens et nous faire bénéficier de leur protection..."; break;
        case 785: texte = "Quand les choses vont mal, je fais des confitures pour m'occuper... Mais en cette saison il va falloir que je trouve une autre activité..."; break;
        case 786: texte = "Tu as un balai à me proposer ?*Je sens une vocation naître en moi... Tu me le cèdes contre mon dernier pot de confiture ?"; break;
        case 787: texte = "Ce balai contre un pot de confiture, ok ?**              OUI ?            non  "; break;
        case 788: texte = "Ce balai contre un pot de confiture, ok ?**              oui              NON ?"; break;
        case 789: texte = "Cool! Je vais pouvoir me changer les idées, et peut-être même faire fuir les loups avec ce balai!"; break;
        case 790: texte = "Je suis sûre que tu me le donneras tôt ou tard..."; break;
        case 791: texte = "Tu as troqué le balai contre un pot de confiture!"; break;
        case 792: texte = "Donner c'est donner!"; break;
        case 793: texte = "Château d'Hyrule"; break;
        case 794: texte = "N : Vers le cimetière"; break;
        case 795: texte = "Bienvenue au château, Messire Link!"; break;
        case 796: texte = "Nous avons ordre de vous laisser passer."; break;
        case 797: texte = "Château de Ganon"; break;
        case 798: texte = "5 Ganon d'or et nous te laissons aller et venir au château ?*              OUI ?            non  "; break;
        case 799: texte = "5 Ganon d'or et nous te laissons aller et venir au château ?*              oui              NON ?"; break;
        case 800: texte = "Tu peux entrer."; break;
        case 801: texte = "QUE LE CHEMIN DE LA TRIFORCE TE SOIT OUVERT...*VOIS APPARAITRE LE TEMPLE DE LA TRIFORCE!"; break;
        case 802: texte = "O : Vers le Château d'Hyrule"; break;
        case 803: texte = "N : Vers les cascades"; break;
        case 804: texte = "E : Entrée des bois perdus"; break;
        case 805: texte = "Tu as trouvé un cristal magique !!!"; break;
        case 806: texte = "Encore "; break;
        case 807: texte = " à trouver !"; break;
        case 808: texte = "Tu les as enfin tous !!!"; break;
        case 809: texte = "Souhaites-tu sauvegarder ta partie ?**                    ? OUI ?*                      non  "; break;
        case 810: texte = "Souhaites-tu sauvegarder ta partie ?**                      oui  *                    ? NON ?"; break;
        case 811: texte = "Partie sauvegardée."; break;
        case 812: texte = "Je construis un opéra ici, je n'ai pas le temps de bavarder durant la pause!"; break;
        case 813: texte = "En plus j'ai perdu mon accessoire vedette..."; break;
        case 814: texte = "Tu as trouvé mon crâne fétiche ???*Je l'avais oublié en prison...*Rend-le-moi! Je te serais éternellement redevable!"; break;
        case 815: texte = "Ce crâne contre ma gratitude, ok ?**              OUI ?            non  "; break;
        case 816: texte = "Ce crâne contre ma gratitude, ok ?**              oui              NON ?"; break;
        case 817: texte = "Merci! Je retrouve toute ma motivation! Je vais achever cet opéra!"; break;
        case 818: texte = "Après une pause..."; break;
        case 819: texte = "Voleur..."; break;
        case 820: texte = "Tu as troqué le crâne contre une reconnaissance de dette!"; break;
        case 821: texte = "Etre ou ne pas être ? Telle est la question..."; break;
        case 822: texte = "Le ton est bon ?"; break;
        case 823: texte = "Temple du Courage**Courage, fuyez!"; break;
        case 824: texte = "Bienvenue chez Tingle!"; break;
        case 825: texte = "Temple de l'Air**Risque de rhume!"; break;
        case 826: texte = "S : Vers le village des Mouettes"; break;
        case 827: texte = "Village des Mouettes"; break;
        case 828: texte = "Une tapisserie contre 2 perles et 5 bocaux d'épices ?*              OUI ?            non  "; break;
        case 829: texte = "Une tapisserie contre 2 perles et 5 bocaux d'épices ?*              oui              NON ?"; break;
        case 830: texte = "Tu as obtenu une tapisserie!"; break;
        case 831: texte = "Une amulette contre 5 poulets et 5 sacs d'olives ?*              OUI ?            non  "; break;
        case 832: texte = "Une amulette contre 5 poulets et 5 sacs d'olives ?*              oui              NON ?"; break;
        case 833: texte = "Des perles contre 2 bocaux d'épices et 2 sacs de riz ?*              OUI ?            non  "; break;
        case 834: texte = "Des perles contre 2 bocaux d'épices et 2 sacs de riz ?*              oui              NON ?"; break;
        case 835: texte = "Un sac de riz contre 1 sac d'olives et 2 rubis? *              OUI ?            non  "; break;
        case 836: texte = "Un sac de riz contre 1 sac d'olives et 2 rubis? *              oui              NON ?"; break;
        case 837: texte = "Les hommes du village sont tous obnubilés par le concours de pêche...*Je me demande qui gagnera..."; break;
        case 838: texte = "Tu participes au concours de pêche ?*...*..."; break;
        case 839: texte = "Finalement tu es comme tous les autres..."; break;
        case 840: texte = "Tu as gagné le concours de pêche ?*...*..."; break;
        case 841: texte = "Je suis ta plus grande fan!!!"; break;
        case 842: texte = "Un stand de pêche vient d'ouvrir à l'ouest du village...*Le proprio organise un grand concours de pêche pour inaugurer sa boutique."; break;
        case 843: texte = "Tu participes aussi au concours de pêche ? *C'est désespérant, je n'arrive pas à trouver plus de 3 sortes de poissons..."; break;
        case 844: texte = "Depuis que le concours de pêche est fini, chacun est retourné à ses activités."; break;
        case 845: texte = "Vi l ge     Mo  t  s"; break;
        case 846: texte = "Repaire des Preux Chevaliers"; break;
        case 847: texte = "**NB : Si nous ne sommes pas là, passez voir à la taverne."; break;
        case 848: texte = "Une gemme de force contre 2 perles ?**              OUI ?            non  "; break;
        case 849: texte = "Une gemme de force contre 2 perles ?**              oui              NON ?"; break;
        case 850: texte = "Une gemme de force contre 2 plumes ?**              OUI ?            non  "; break;
        case 851: texte = "Une gemme de force contre 2 plumes ?**              oui              NON ?"; break;
        case 852: texte = "Une gemme de force contre 2 poulets ?**              OUI ?            non  "; break;
        case 853: texte = "Une gemme de force contre 2 poulets ?**              oui              NON ?"; break;
        case 854: texte = "Un poulet contre 1 sac de riz et 2 sacs d'olives ? *              OUI ?            non  "; break;
        case 855: texte = "Un poulet contre 1 sac de riz et 2 sacs d'olives ? *              oui              NON ?"; break;
        case 856: texte = "Au-delà de la frontière Sud d'Hyrule, on dit que se dresse un vaste océan..."; break;
        case 857: texte = "A la belle saison des mouettes franchissent les falaises qui nous séparent de la plage et viennent jusqu'à ce village."; break;
        case 858: texte = "Ce village est sous la protection des chevaliers Hyliens, tu es donc en sécurité ici."; break;
        case 859: texte = "Toutefois, depuis qu'une taverne a ouvert dans un village voisin, on ne voit plus beaucoup nos protecteurs dans le coin..."; break;
        case 860: texte = "Pas ici non plus ? Qu'est-ce que j'ai bien pu en faire ?"; break;
        case 861: texte = "Tu as retrouvé le vase de ma belle-mère ??? *Ca fait des semaines qu'elle me force à le chercher partout! *Dépêche-toi de me le rendre!"; break;
        case 862: texte = "Ce vase contre un truc que je viens de trouver, ok ?*              OUI ?            non  "; break;
        case 863: texte = "Ce vase contre un truc que je viens de trouver, ok ?*              oui              NON ?"; break;
        case 864: texte = "Sage décision petit."; break;
        case 865: texte = "Tuez-le..."; break;
        case 866: texte = "Tu as troqué la botte contre un marteau!"; break;
        case 867: texte = "Ca te dirait d'entrer dans mon gang ?**              OUI ?            non  "; break;
        case 868: texte = "Ca te dirait d'entrer dans mon gang ?**              oui              NON ?"; break;
        case 869: texte = "Ha! Ha! Ha! *Je rigolais, tu es brave, mais sot! *Insecte ridicule! *Sais-tu bien qui nous sommes ?"; break;
        case 870: texte = "Temple de la Sagesse**Seuls les sages sauront s'en tenir à l'écart."; break;
        case 871: texte = "Stand de location de barques"; break;
        case 872: texte = "Le stand de barques est fermé pour l'instant, je suis bien parti pour remporter le concours de pêche, j'en ai déjà 3 différents!"; break;
        case 873: texte = "Veux-tu louer une barque pour 15 rubis ?**              OUI ?            non  "; break;
        case 874: texte = "Veux-tu louer une barque pour 15 rubis ?**              oui              NON ?"; break;
        case 875: texte = "Tu peux utiliser la barque au ponton, amuse-toi bien, mais ne t'éloigne pas trop."; break;
        case 876: texte = "(voix lointaine :) *J'ai dit... NE T'ELOIGNE PAS TROP!!!!"; break;
        case 877: texte = "Grotte des Abysses**Merci de ne pas venir chercher le descendant des sages qui n'est pas caché là."; break;
        case 878: texte = "Forgeron"; break;
        case 879: texte = "Grande Pyramide"; break;
        case 880: texte = "INDICE 1 : La pierre la plus à droite est la seconde. *INDICE 2 : Les pierres doivent être ôtées dans l'ordre de leurs poids."; break;
        case 881: texte = "INDICE 3 : Les pierres de la queue doivent être ôtées avant celle de la nageoire. *INDICE 4 : La pierre de l'oeil doit être ôtée en 5ème."; break;
        case 882: texte = "INDICE 5 : Les pierres aquatiques doivent être ôtées avant la dernière de la queue. *INDICE 6 : La pierre de l'oeil doit être ôtée après celle de la nageoire."; break;
        case 883: texte = "INDICE 7 : La dernière pierre n'est pas l'oeil. *INDICE 8 : Les 2 pierres de la queue ne doivent pas être ôtées consécutivement."; break;
        case 884: texte = "INDICE 9 : L'un des 9 indices est faux."; break;
        case 885: texte = "N : Montagnes Rocheuses"; break;
        case 886: texte = "Village Cocorico"; break;
        case 887: texte = "Les bottes de Pégase contre une tapisserie et un parfum ?*              OUI ?            non  "; break;
        case 888: texte = "Les bottes de Pégase contre une tapisserie et un parfum ?*              oui              NON ?"; break;
        case 889: texte = "Tu as obtenu les bottes de Pégase ! *Maintiens R pour courir !"; break;
        case 890: texte = "Tu as obtenu les bottes de Pégase ! *Maintiens Shift ou appuie sur Capslock pour courir !"; break;
        case 891: texte = "Un parfum contre 3 plumes et 4 sacs de riz ? **              OUI ?            non  "; break;
        case 892: texte = "Un parfum contre 3 plumes et 4 sacs de riz ? **              oui              NON ?"; break;
        case 893: texte = "Tu as obtenu un parfum !"; break;
        case 894: texte = "Un sac d'olives contre 15 rubis ?**              OUI ?            non  "; break;
        case 895: texte = "Un sac d'olives contre 15 rubis ?**              oui              NON ?"; break;
        case 896: texte = "Un bocal d'épices contre 20 rubis ?**              OUI ?            non  "; break;
        case 897: texte = "Un bocal d'épices contre 20 rubis ?**              oui              NON ?"; break;
        case 898: texte = "Le village Cocorico est un passage obligé pour les aventuriers qui souhaitent gravir la montagne. Les moins courageux se contentent d'atteindre le saloon..."; break;
        case 899: texte = "Soit le bienvenu au village, Link! *Amuse-toi, mais évite tout de même de trop t'approcher des cactus..."; break;
        case 900: texte = "Les bottes de Pégase permettent de se déplacer beaucoup plus rapidement. Cela donne un réel avantage au combat."; break;
        case 901: texte = "Tu as ces bottes ? *Tu dois être plutôt fort désormais..."; break;
        case 902: texte = "Un roc givre contre une tapisserie, une amulette et un parfum ? *              OUI ?            non  "; break;
        case 903: texte = "Un roc givre contre une tapisserie, une amulette et un parfum ? *              oui              NON ?"; break;
        case 904: texte = "Tu as obtenu un roc givre !"; break;
        case 905: texte = "Des perles contre un bocal d'épices et un sac de riz ? *              OUI ?            non  "; break;
        case 906: texte = "Des perles contre un bocal d'épices et un sac de riz ? *              oui              NON ?"; break;
        case 907: texte = "Ce village est sous la protection des 7 sages. Grâce à leur magie, il faut pas mal s'éloigner avant d'apercevoir les premiers loups..."; break;
        case 908: texte = "Tu es ici au village le plus sûr que tu pourras trouver. Rien à voir avec le hameau du centre voué à disparaître, ni avec le village de l'Est défendu par des alcooliques..."; break;
        case 909: texte = "Temple du Temps"; break;
        case 910: texte = "Entrée de la mine"; break;
        case 911: texte = "Temple de la Force**Réservé aux costauds."; break;
        case 912: texte = "Je me suis isolé du monde pour méditer sur le sens de la vie..."; break;
        case 913: texte = "...mais je dois bien admettre que certaines choses me manquent..."; break;
        case 914: texte = "C'est une bouteille de vin que tu as là ??? *Donne-la-moi! Je te donnerai de l'or en échange !!!"; break;
        case 915: texte = "Cette bouteille contre de l'or, ok ?**              OUI ?            non  "; break;
        case 916: texte = "Cette bouteille contre de l'or, ok ?**              oui              NON ?"; break;
        case 917: texte = "Je sens que j'approche de la vérité !"; break;
        case 918: texte = "...*Je vais devoir méditer sur le sens de ton refus..."; break;
        case 919: texte = "Tu as troqué la bouteille contre de la poudre d'or!"; break;
        case 920: texte = "J'ai enfin trouvé le sens de la vie... Hic!"; break;
        case 921: texte = "Tour de Glace**Le chemin s'ouvrira lorsque toutes les gemmes de force auront été trouvées."; break;
        case 922: texte = "D'ici je peux admirer le lac de lave... *D'ailleurs j'adore tout ce qui est rouge et qui brille."; break;
        case 923: texte = "Mmm... c'est une magnifique gemme que tu as là... *Tu me la donnerais contre... une surprise ?"; break;
        case 924: texte = "Cette gemme rouge contre une surprise, ok ?**              OUI ?            non  "; break;
        case 925: texte = "Cette gemme rouge contre une surprise, ok ?**              oui              NON ?"; break;
        case 926: texte = "Merci! Voilà ta surprise! Depuis le temps que je cherchais à m'en débarrasser..."; break;
        case 927: texte = "Tans pis pour toi, pas de gemme pas de surprise."; break;
        case 928: texte = "Tu as troqué la gemme rouge contre une enclume! Tu ne peux plus courir ni nager jusqu'à ce que tu t'en débarrasses!"; break;
        case 929: texte = "Je me sens plus léger et plus riche, que du bonheur!"; break;
        case 930: texte = "Temple du Feu"; break;
        case 931: texte = "Nous sommes des rennes qui parlent."; break;
        case 932: texte = "Nous avons échoué ici après avoir percuté une mouette... *Tout ça ne serait jamais arrivé si j'avais eu un klaxon..."; break;
        case 933: texte = "Ah oui j'oubliais : *Ho! Ho! Ho!"; break;
        case 934: texte = "C'est une clochette que tu as là ? *Ca me donne une idée... *Tu me la cèderais ? Je n'ai plus de poney, mais je devrais bien trouver de quoi te remercier..."; break;
        case 935: texte = "Cette clochette contre une récompense, ok ?**              OUI ?            non  "; break;
        case 936: texte = "Cette clochette contre une récompense, ok ?**              oui              NON ?"; break;
        case 937: texte = "Merci! Voilà ta récompense : la hache que je devais livrer en cadeau au bourreau du coin. Heureux ?"; break;
        case 938: texte = "... *Quel est ton nom ?*Je te raye de ma liste."; break;
        case 939: texte = "Tu as troqué la clochette contre une hache!"; break;
        case 940: texte = "Ho! Ho! Ho!"; break;
        case 941: texte = "C'est bien gentil, mais comment je rentre moi ?"; break;
        case 942: texte = "TUTORIEL :*Un choc sur une de ces sphères de couleur permute les obstacles levés."; break;
        case 943: texte = "Tu as trouvé une épée !!!*Sert-en avec ¾4, ou maintiens ¾4 enfoncé pour charger une attaque tornade!"; break;
        case 944: texte = "Tu as trouvé une épée !!!*Sert-en avec la touche W (ou Z), ou maintiens W (ou Z) enfoncé pour charger une attaque tornade!"; break;
        case 945: texte = "TUTORIEL :*Tomber dans un trou permet de descendre au niveau inférieur, cependant, s'il n'y a pas de niveau inférieur tel que c'est le cas ici, une chute fait perdre de la vie et renvoie à l'entrée de la zone. Prudence donc!"; break;
        case 946: texte = "TUTORIEL :*Au cours du jeu, vous pourriez être amené à rencontrer des zones apparemment inaccessibles comme la plate-forme en bas. Vous aurez alors"; break;
        case 947: texte = "besoin de revenir plus tard dans le jeu avec un équipement plus fournit pour y accéder."; break;
        case 948: texte = "@+@+@+@+@+@+@@@+*@=++=@=+@=+@=+=@*+@+@+@+=+="; break;
        case 949: texte = "Les gardes t'ont aperçu te diriger vers la forêt, j'ai pensé que tu avais une piste et j'ai accouru..."; break;
        case 950: texte = "Mmm... Cette stèle est en hylien ancien... Je vais te la traduire :"; break;
        case 951: texte = "A l'aube du cataclysme, le héros trouvera cette stèle. Les pendentifs du courage, de la sagesse et de la force en sa possession, l'unique chance de sauver le monde se présentera à lui."; break;
        case 952: texte = "..."; break;
        case 953: texte = "J'ai peur que nous devions laisser tomber cette affaire d'ocarina pour le moment...*Si cette stèle dit vrai, tu dois trouver les 3 pendentifs dans les plus brefs délais..."; break;
        case 954: texte = "Ils sont cachés dans 3 temples, le plus proche est une tour près des cascades au Nord d'ici... Prends cette carte, elle t'aidera à t'orienter!"; break;
        case 955: texte = "Tu as obtenu la carte d'Hyrule!**Appuie sur L à l'extérieur pour la consulter."; break;
        case 956: texte = "Tu as obtenu la carte d'Hyrule!**Appuie sur P à l'extérieur pour la consulter."; break;
        case 957: texte = "Le premier médaillon se trouve dans la tour au Nord de cette forêt, sors de la forêt par l'Ouest puis va au Nord pour arriver dans la zone des cascades."; break;
        case 958: texte = "Le second médaillon se trouve dans le temple au milieu du lac. Tu devras louer une barque près du village des Mouettes..."; break;
        case 959: texte = "Le dernier médaillon est dans un temple dans les montagnes, au Nord du village Cocorico."; break;
        case 960: texte = "Tu as trouvé tous les pendentifs ?*Bien, nous ignorons tout de ce qui va se passer, alors prends cette épée avec toi."; break;
        case 961: texte = "Tu as obtenu Excalibur !!!*Sa puissance devrait t'être utile!"; break;
        case 962: texte = "On dirait un portail de téléportation, mais... ...nous n'avons aucune information quant à sa destination..."; break;
        case 963: texte = "Essaie de toucher la stèle, il va sûrement se passer quelque chose maintenant que tu as les pendentifs..."; break;
        case 964: texte = "Une dernière chose :*Des monstres commencent à apparaître partout en Hyrule... C'est très mauvais signe... Soit prudent."; break;
        case 965: texte = "Bonjour Link, les visiteurs se font rares ces temps-ci..."; break;
        case 966: texte = "Laisse-moi améliorer ton bouclier..."; break;
        case 967: texte = "Tu as obtenu un meilleur bouclier !!!*Ta défense augmente d'un point!"; break;
        case 968: texte = "Viens me voir si tu es blessé, je te soignerai."; break;
        case 969: texte = "Tu as obtenu 10 sacs de riz!"; break;
        case 970: texte = "Tu as obtenu 10 bocaux d'épices!"; break;
        case 971: texte = "Tu as obtenu 10 sacs d'olives!"; break;
        case 972: texte = "Pour ouvrir l'accès à la Pyramide, trouve et note les 9 indices cachés sur des pancartes du désert, puis soulève les pierres de la baleine dans le bon ordre, et le chemin s'ouvrira..."; break;
        case 973: texte = "Chariot express : Je suis absent pour le moment, en cas d'urgence, je suis au saloon.** - L'employé de la mine -"; break;
        case 974: texte = "Chariot express : le service a repris!"; break;
        case 975: texte = "Monte dans le wagonnet et laisse-moi m'occuper du levier. *Ne t'inquiète pas c'est mon métier!"; break;
        case 976: texte = "Tu as trouvé des planches de bois!*Tu pourrais t'en servir pour construire un pont..."; break;
        case 977: texte = "Ca semble être un bon endroit pour construire un pont."; break;
        case 978: texte = "                      Link*                 Héros d'Hyrule*               - Tué par Ganon -"; break;
        case 979: texte = "Nous sommes au complet, nous allons t'ouvrir le portail..."; break;
        case 980: texte = "Prépare-toi bien, le voleur de l'ocarina doit être une créature très puissante..."; break;
        case 981: texte = "Tu as réussi à reprendre l'ocarina ? Félicitation !"; break;
        case 982: texte = "Ce portail est très particulier, il pointe vers un endroit précis du passé... Mais nous ne pourrons pas le maintenir ouvert éternellement, dépêche-toi!"; break;
        case 983: texte = "Tu as l'ocarina ? Nous avons donc accompli la mission confiée par nos ancêtres..."; break;
        case 984: texte = "Le portail est enfin ouvert... Va Link, tu dois reprendre l'ocarina!"; break;
        case 985: texte = "L'Ocarina du Temps..."; break;
        case 986: texte = "Cours au Temple du Temps, accomplit ta destinée!"; break;
        case 987: texte = "Lorsque nous serons au complet et munis de la clé du temps, nous t'ouvrirons le portail..."; break;
        case 988: texte = "Tu as réussi... Nous refermons le portail..."; break;
        case 989: texte = "Tu as obtenu une jauge!*...*Cool..."; break;
        case 990: texte = "Ca va j'ai assez d'or, va-t'en."; break;
        case 991: texte = "Donne-moi vite 100 Ganon d'or si tu veux une récompense, ok ?*              OUI ?            non  "; break;
        case 992: texte = "Donne-moi vite 100 Ganon d'or si tu veux une récompense, ok ?*              oui              NON ?"; break;
        case 993: texte = "Tu me fais perdre mon temps, oust!"; break;
        case 994: texte = "Je vais augmenter le nombre de flèches que tu peux transporter.*Merci qui ?"; break;
        case 995: texte = "Je vais augmenter le nombre de bombes que tu peux transporter.*Je suis trop bonne..."; break;
        case 996: texte = "Donne-moi 999 Ganon d'or si tu veux une super récompense, ok ?*              OUI ?            non  "; break;
        case 997: texte = "Donne-moi 999 Ganon d'or si tu veux une super récompense, ok ?*              oui              NON ?"; break;
        case 998: texte = "Ton nombre de flèches va désormais augmenter en permanence, n'hésite plus à les utiliser."; break;
        case 999: texte = "Ton stock de bombe se restitue désormais en permanence, tu peux exploser sans compter!"; break;
        case 1000: texte = "Bienvenue à toi héros, je vais augmenter ta réserve de magie, ça devrait t'être utile."; break;
        case 1001: texte = "Ta réserve de magie a doublé!"; break;
        case 1002: texte = "Je te sers quelque chose ?"; break;
        case 1003: texte = "D'après les rumeurs, une fée se cacherait derrière une cascade...*Quelle sornette..."; break;
        case 1004: texte = "Je euh... monte la garde dans le bar, oui voilà.*Mais je préfèrerai que ça reste entre nous, ok?"; break;
        case 1005: texte = "Héros d'Hyrule ou pas, ne pense pas boire à l'oeil."; break;
        case 1006: texte = "C'est trop risqué de rentrer ici, on risque de te voir."; break;
        case 1007: texte = "Choisis ce que tu veux.*"; break;
        case 1008: texte = "10 flèches pour 20 rubis ?**              OUI ?            non  "; break;
        case 1009: texte = "10 flèches pour 20 rubis ?**              oui              NON ?"; break;
        case 1010: texte = "5 bombes pour 30 rubis ?**              OUI ?            non  "; break;
        case 1011: texte = "5 bombes pour 30 rubis ?**              oui              NON ?"; break;
        case 1012: texte = "Il te faut un sac de bombes pour acheter ceci."; break;
        case 1013: texte = "Il te faut un arc pour acheter ceci."; break;
        case 1014: texte = "Tu n'as pas besoin de ça."; break;
        case 1015: texte = "Merci."; break;
        case 1016: texte = "Un petit coeur pour 5 rubis ?**              OUI ?            non  "; break;
        case 1017: texte = "Un petit coeur pour 5 rubis ?**              oui              NON ?"; break;
        case 1018: texte = "Une petite fiole de magie pour 15 rubis ?**              OUI ?            non  "; break;
        case 1019: texte = "Une petite fiole de magie pour 15 rubis ?**              oui              NON ?"; break;
        case 1020: texte = "Une grande fiole de magie pour 25 rubis ?**              OUI ?            non  "; break;
        case 1021: texte = "Une grande fiole de magie pour 25 rubis ?**              oui              NON ?"; break;
        case 1022: texte = "Je viens d'arriver dans cette ville, je ne suis pas encore ouvert, reviens plus tard."; break;
        case 1023: texte = "Est-ce que j'ai un roc givre ?*Oui, tout juste."; break;
        case 1024: texte = "Je pensais que personne n'avait de gemmes de force, j'hésitais à ouvrir ma boutique, mais tu m'as décidé."; break;
        case 1025: texte = "Dès ta prochaine visite je serai ouvert, tu pourras acheter des articles rarissimes contre des gemmes."; break;
        case 1026: texte = "Je te le cède pour 30 gemmes de force, ok ?**              OUI ?            non  "; break;
        case 1027: texte = "Je te le cède pour 30 gemmes de force, ok ?**              oui              NON ?"; break;
        case 1028: texte = "Tu n'as pas assez de gemmes.*Cherche mieux, on en trouve partout."; break;
        case 1029: texte = "Ce détecteur permet de voir si tu as trouvé toutes les gemmes de force de ta zone actuelle. Un outil indispensable pour trouver toutes les gemmes, il est à toi contre 20 gemmes de force!"; break;
        case 1030: texte = "Le détecteur pour 20 gemmes de force, ok ?**              OUI ?            non  "; break;
        case 1031: texte = "Le détecteur pour 20 gemmes de force, ok ?**              oui              NON ?"; break;
        case 1032: texte = "Tu as obtenu le détecteur !*Lorsque tu appuies sur ¾3, le nombre de gemmes en ta possession sera écrit en vert si tu les as toutes dans la zone."; break;
        case 1033: texte = "Tu as obtenu le détecteur !*Lorsque tu appuies sur Entrée, le nombre de gemmes en ta possession sera écrit en vert si tu les as toutes dans la zone."; break;
        case 1034: texte = "Une bouteille vide pour 10 gemmes de force ?**              OUI ?            non  "; break;
        case 1035: texte = "Une bouteille vide pour 10 gemmes de force ?**              oui              NON ?"; break;
        case 1036: texte = "Tu as obtenu une bouteille !*Tu vas pouvoir stocker des potions dedans !"; break;
        case 1037: texte = "Une bouteille vide pour 20 gemmes de force ?**              OUI ?            non  "; break;
        case 1038: texte = "Une bouteille vide pour 20 gemmes de force ?**              oui              NON ?"; break;
        case 1039: texte = "Une augmentation de ta force pour 20 gemmes ?**              OUI ?            non  "; break;
        case 1040: texte = "Une augmentation de ta force pour 20 gemmes ?**              oui              NON ?"; break;
        case 1041: texte = "Ta force augmente d'un point!"; break;
        case 1042: texte = "Une augmentation de ta force pour 40 gemmes ?**              OUI ?            non  "; break;
        case 1043: texte = "Une augmentation de ta force pour 40 gemmes ?**              oui              NON ?"; break;
        case 1044: texte = "Une augmentation de ta défense pour 20 gemmes ? *              OUI ?            non  "; break;
        case 1045: texte = "Une augmentation de ta défense pour 20 gemmes ? *              oui              NON ?"; break;
        case 1046: texte = "Ta défense augmente d'un point!"; break;
        case 1047: texte = "Une augmentation de ta défense pour 40 gemmes ? *              OUI ?            non  "; break;
        case 1048: texte = "Une augmentation de ta défense pour 40 gemmes ? *              oui              NON ?"; break;
        case 1049: texte = "Mmm... mon stock est vide..."; break;
        case 1050: texte = "Tu as dû trouver toutes les gemmes de force, c'est incroyable..."; break;
        case 1051: texte = "D'après une vielle légende, quand toutes les gemmes auront été trouvées, un temple gardant un trésor fabuleux s'ouvrira...*Plus qu'à attendre..."; break;
        case 1052: texte = "Reviens me voir lorsque tu auras un flacon vide et je te vendrais des potions."; break;
        case 1053: texte = "Les potions rouges redonnent de l'énergie alors que les potions vertes redonnent de la magie."; break;
        case 1054: texte = "Que désires-tu ?*                ? POTION ROUGE ?*                  potion verte  *                      rien      "; break;
        case 1055: texte = "Que désires-tu ?*                  potion rouge  *                ? POTION VERTE ?*                      rien      "; break;
        case 1056: texte = "Que désires-tu ?*                  potion rouge  *                  potion verte  *                ?     RIEN     ?"; break;
        case 1057: texte = "Une potion rouge pour 60 rubis ?**              OUI ?            non  "; break;
        case 1058: texte = "Une potion rouge pour 60 rubis ?**              oui              NON ?"; break;
        case 1059: texte = "Une potion verte pour 40 rubis ?**              OUI ?            non  "; break;
        case 1060: texte = "Une potion verte pour 40 rubis ?**              oui              NON ?"; break;
        case 1061: texte = "Tu as trouvé une potion rouge !!!**Bois-la pour restaurer toute ton énergie!!!"; break;
        case 1062: texte = "Tu as trouvé une potion verte !!!**Bois-la pour restaurer toute ta magie!!!"; break;
        case 1063: texte = "Tu as trouvé une potion bleue !!!**Bois-la pour restaurer ton énergie et ta magie!!!"; break;
        case 1064: texte = "Tu n'as pas besoin de boire cette potion maintenant."; break;
        case 1065: texte = "                Déjà fatigué ?                  ?                CONTINUER                  ?             Sauvegarder et quitter                        Quitter sans sauvegarder           "; break;
        case 1066: texte = "                Déjà fatigué ?                                   Continuer                     ?          SAUVEGARDER ET QUITTER           ?            Quitter sans sauvegarder           "; break;
        case 1067: texte = "                Déjà fatigué ?                                   Continuer                                Sauvegarder et quitter              ?         QUITTER SANS SAUVEGARDER          ?"; break;
        case 1068: texte = "Je suis l'homme le plus malchanceux du pays, il ne m'arrive jamais rien de bon..."; break;
        case 1069: texte = "C'est un porte-bonheur que tu as là ? *Donne-le-moi! *Personne n'en a autant besoin que moi!"; break;
        case 1070: texte = "Ce fer à cheval contre... rien, ok ?**              OUI ?            non  "; break;
        case 1071: texte = "Ce fer à cheval contre... rien, ok ?**              oui              NON ?"; break;
        case 1072: texte = "Merci mille fois! Je vais peut-être avoir de la chance maintenant!"; break;
        case 1073: texte = "Par contre désolé l'ami, mais je n'ai rien à t'offrir en échange, on dirait que la chance a tourné."; break;
        case 1074: texte = "... *Quelle immonde déveine!"; break;
        case 1075: texte = "Tu as troqué le fer à cheval contre... sa reconnaissance ?"; break;
        case 1076: texte = "Finalement je suis un sacré veinard."; break;
        case 1077: texte = "Je n'ai plus de prix à mettre en jeu, désolé."; break;
        case 1078: texte = "Il y a "; break;
        case 1079: texte = " prix dans ces 9 coffres, tu veux tenter ta chance pour "; break;
        case 1080: texte = " rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?              OUI ?            non  "; break;
        case 1081: texte = "Il y a "; break;
        case 1082: texte = " prix dans ces 9 coffres, tu veux tenter ta chance pour "; break;
        case 1083: texte = " rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?              oui              NON ?"; break;
        case 1084: texte = "Choisis un coffre."; break;
        case 1085: texte = "Hey! Il faut payer pour ouvrir un de mes coffres!!!"; break;
        case 1086: texte = "Perdu! Ce coffre est vide."; break;
        case 1087: texte = "Bonjour Link, tu veux traverser le pont pour accéder au temple ?"; break;
        case 1088: texte = "Habituellement je n'aurais qu'à activer ce levier, mais j'ai joué avec toute la soirée d'hier, et euh... je l'ai cassé."; break;
        case 1089: texte = "J'ai même pensé à mettre des planches en bois pour permettre de passer, mais on m'a volé mes planches la nuit dernière..."; break;
        case 1090: texte = "Je pourrais toujours réparer le levier, mais j'ai besoin d'une pièce de rechange, et je ne peux pas quitter mon poste..."; break;
        case 1091: texte = "J'ai besoin d'un rouage, on en trouve sur la place du marché de la cité d'Hyrule."; break;
        case 1092: texte = "Tu connais le principe, non ? Chaque marchand te propose des marchandises contre d'autres, tu dois réunir ce qu'ils veulent pour obtenir ce que tu veux."; break;
        case 1093: texte = "Je vais te donner les marchandises que j'ai.*Si tu veux consulter ce que tu as déjà, appuie sur ¾7."; break;
        case 1094: texte = "Je vais te donner les marchandises que j'ai.*Si tu veux consulter ce que tu as déjà, appuie sur I."; break;
        case 1095: texte = "Il me faut un rouage pour réparer le levier.*Va en chercher sur la place du marché de la cité d'Hyrule si tu veux franchir le pont."; break;
        case 1096: texte = "Tu as un rouage ?*Bien, ça devrait marcher maintenant."; break;
        case 1097: texte = "Le levier est à nouveau cassé...*Au moins le pont est sorti cette fois...*Ca m'apprendra à construire des ponts excentriques..."; break;
        case 1098: texte = "Une potion bleue pour 160 rubis ?*Tu ne seras pas déçu...*              OUI ?            non  "; break;
        case 1099: texte = "Une potion bleue pour 160 rubis ?*Tu ne seras pas déçu...*              oui              NON ?"; break;
        case 1100: texte = "J'adore tout ce qui est vert et qui brille!"; break;
        case 1101: texte = "Ne t'en fais pas, je ne vais pas te voler de rubis... *J'essaie d'arrêter."; break;
        case 1102: texte = "C'est drôlement beau ce que tu as là... *J'adore!*Je te l'échange contre une carte de voyage d'une valeur... euh... INESTIMABLE!"; break;
        case 1103: texte = "Cette gemme verte contre une carte, ok ?**              OUI ?            non  "; break;
        case 1104: texte = "Cette gemme verte contre une carte, ok ?**              oui              NON ?"; break;
        case 1105: texte = "Merciiii!!! Voilà ta carte de voyage, maintenant du vent!"; break;
        case 1106: texte = "Très bien... *Surveille tes Rubis dans ce cas!"; break;
        case 1107: texte = "Tu as troqué la gemme verte contre une carte!"; break;
        case 1108: texte = "Tu es venu me donner des Rubis ?*Comme c'est gentil!"; break;
        case 1109: texte = "La princesse veut que je la prévienne s'il se passe quelque chose de curieux en ville..."; break;
        case 1110: texte = "Ce matin j'ai vu une mouette qui volait curieusement... j'hésite à lui en parler..."; break;
        case 1111: texte = "Bonjour Link, soit le bienvenu au stand de pêche!"; break;
        case 1112: texte = "Pour inaugurer l'ouverture du stand, j'organise un grand concours de pêche!*Tu as dû en entendre parler, toute la ville participe!"; break;
        case 1113: texte = "Pour remporter le concours et gagner un prix spécial, il faut être le premier à pêcher 5 espèces de poissons différentes."; break;
        case 1114: texte = "Veux-tu participer ? Les droits d'inscriptions sont de 10 Rubis, ok ?*              OUI ?            non  "; break;
        case 1115: texte = "Veux-tu participer ? Les droits d'inscriptions sont de 10 Rubis, ok ?*              oui              NON ?"; break;
        case 1116: texte = "Très bien, voici une canne à pêche, reviens lorsque tu auras pêché 5 poissons différents."; break;
        case 1117: texte = "Mmm... Veux-tu participer pour 5 Rubis ?**              OUI ?            non  "; break;
        case 1118: texte = "Mmm... Veux-tu participer pour 5 Rubis ?**              oui              NON ?"; break;
        case 1119: texte = "Bien, voici une canne à pêche, reviens lorsque tu auras pêché 5 poissons différents."; break;
        case 1120: texte = "Et pour 2 Rubis ?**              OUI ?            non  "; break;
        case 1121: texte = "Et pour 2 Rubis ?**              oui              NON ?"; break;
        case 1122: texte = "Bon, voici une canne à pêche, reviens lorsque tu auras pêché 5 poissons différents."; break;
        case 1123: texte = "Pour 1 Rubis ?**              OUI ?            non  "; break;
        case 1124: texte = "Pour 1 Rubis ?**              oui              NON ?"; break;
        case 1125: texte = "Ok, voici une canne à pêche, reviens lorsque tu auras pêché 5 poissons différents."; break;
        case 1126: texte = "Tu ne veux tout de même pas participer gratuitement ???*               SI ?            non  "; break;
        case 1127: texte = "Tu ne veux tout de même pas participer gratuitement ???*               si              NON ?"; break;
        case 1128: texte = "...*Voici une canne à pêche, reviens lorsque tu auras pêché 5 poissons différents."; break;
        case 1129: texte = "Va-t-en, ennemi de la pêche!"; break;
        case 1130: texte = "Tu as obtenu une canne à pêche!*Utilise-la à un ponton, puis remonte la ligne en appuyant à nouveau sur ¾1 lorsque la ligne bouge."; break;
        case 1131: texte = "Tu as obtenu une canne à pêche!*Utilise-la à un ponton, puis remonte la ligne en appuyant à nouveau sur X lorsque la ligne bouge."; break;
        case 1132: texte = "Encore "; break;
        case 1133: texte = " poissons différents à trouver, bonne chance!"; break;
        case 1134: texte = "Plus qu'un poisson à trouver!"; break;
        case 1135: texte = "Tu as trouvé suffisamment de poissons ???*Tu dois être un super pêcheur!"; break;
        case 1136: texte = "Ca signifie que le concours de pêche est terminé, tu en es le vainqueur!"; break;
        case 1137: texte = "J'imagine que tu vas vouloir ton prix...*Pour te récompenser d'avoir remporter le concours de pêche : *... ... ..."; break;
        case 1138: texte = "Je t'engage!"; break;
        case 1139: texte = "Il y a beaucoup d'autres espèces de poissons à Hyrule, je veux tous les répertorier par région."; break;
        case 1140: texte = "Je te récompenserai tous les 5 nouveaux poissons pêchés.*Tu peux désormais consulter la liste des poissons pêchés en appuyant sur ¾8"; break;
        case 1141: texte = "Je te récompenserai tous les 5 nouveaux poissons pêchés.*Tu peux désormais consulter la liste des poissons pêchés en appuyant sur L"; break;
        case 1142: texte = "Avec ta canne à pêche actuelle, tu ne pourras hélas pêcher que des petits poissons..."; break;
        case 1143: texte = "N'hésite pas à pêcher partout!*Chaque poisson pêché te redonne de la vie, l'avais-tu remarqué ?"; break;
        case 1144: texte = "Encore "; break;
        case 1145: texte = " poissons différents à trouver avant la prochaine récompense!"; break;
        case 1146: texte = "Voici ta récompense pour avoir trouvé 10 poissons différents :"; break;
        case 1147: texte = "Tu as obtenu une meilleure canne à pêche!!!*Tu vas pouvoir attraper des poissons de taille moyenne."; break;
        case 1148: texte = "Encore "; break;
        case 1149: texte = " poissons différents à trouver avant la prochaine récompense!"; break;
        case 1150: texte = "Voici ta récompense pour avoir trouvé 15 poissons différents :"; break;
        case 1151: texte = "Encore "; break;
        case 1152: texte = " poissons différents à trouver avant la prochaine récompense!"; break;
        case 1153: texte = "Voici ta récompense pour avoir trouvé 20 poissons différents :"; break;
        case 1154: texte = "Tu as obtenu la meilleure canne à pêche!!!*Tu vas pouvoir attraper des poissons de taille gigantesque!"; break;
        case 1155: texte = "Encore "; break;
        case 1156: texte = " poissons différents à trouver avant la prochaine récompense!"; break;
        case 1157: texte = "Voici ta récompense pour avoir trouvé 25 poissons différents :"; break;
        case 1158: texte = "Encore "; break;
        case 1159: texte = " poissons différents à trouver avant la prochaine récompense!"; break;
        case 1160: texte = "Voici ta récompense pour avoir trouvé tous les poissons différents :"; break;
        case 1161: texte = "T'ES VIRE !!!!"; break;
        case 1162: texte = "Tous les poissons d'Hyrule sont enfin recensés, mon guide du pêcheur est enfin fini..."; break;
        case 1163: texte = "Bonjour Link.*En temps que maire, je te souhaite la bienvenue au village des Mouettes."; break;
        case 1164: texte = "En ce moment un concours de pêche est organisé en ville, tout le monde ne parle que de ça... *Est-ce la raison de ta venue ?"; break;
        case 1165: texte = "Le concours de pêche étant fini, le village des Mouettes est redevenu un lieu calme."; break;
        case 1166: texte = "Je suis un pêcheur légendaire!*J'aime le côté bleu et brillant de la mer..."; break;
        case 1167: texte = "Pourquoi je n'ai pas remporté le concours de pêche ?*Et bien euh... Ce genre de choses ne m'intéressent pas.... Voilà."; break;
        case 1168: texte = "Une gemme bleue et brillante ?*Il me la faut!*Je te l'échange contre ma dernière pêche!"; break;
        case 1169: texte = "Cette gemme bleue contre sa pêche, ok ?**              OUI ?            non  "; break;
        case 1170: texte = "Cette gemme bleue contre sa pêche, ok ?**              oui              NON ?"; break;
        case 1171: texte = "Hé! Hé! Tu fais une affaire petit."; break;
        case 1172: texte = "Cette botte était remplie d'algues quand je l'ai pêchée, ce n'est pas courant hein ?"; break;
        case 1173: texte = "Tu es trop gentil, mais ne t'en fais pas pour moi, n'ai pas peur de m'arnaquer."; break;
        case 1174: texte = "Tu as troqué la gemme bleue contre une vieille botte!*Bien joué..."; break;
        case 1175: texte = "Si tu trouves d'autres gemmes bleues, ce sera un plaisir de faire à nouveau des affaires avec toi!"; break;
        case 1176: texte = "De nos jours les jeunes n'écoutent plus les conseils des plus âgés...*Je sens que ce concours de pêche va durer..."; break;
        case 1177: texte = "Autrefois j'étais un pêcheur réputé, veux-tu que je te donne quelques astuces ?"; break;
        case 1178: texte = "A PROPOS DES ESPECES DE POISSONS ?*A propos des régions de pêche     *A propos des bonus                *Rien du tout                      "; break;
        case 1179: texte = "A propos des espèces de poissons  *A PROPOS DES REGIONS DE PECHE    ?*A propos des bonus                *Rien du tout                      "; break;
        case 1180: texte = "A propos des espèces de poissons  *A propos des régions de pêche     *A PROPOS DES BONUS               ?*Rien du tout                      "; break;
        case 1181: texte = "A propos des espèces de poissons  *A propos des régions de pêche     *A propos des bonus                *RIEN DU TOUT                     ?"; break;
        case 1182: texte = "On dit que les eaux d'Hyrule abritent pas moins de 30 espèces de poissons, mais ils ont chacun leur propre région, tu ne les trouveras pas tous au même endroit."; break;
        case 1183: texte = "Il y a en Hyrule beaucoup d'endroits où pêcher, mais seulement 6 régions distinctes. Pour trouver de nouveaux poissons tu devras aller pêcher à d'autres endroits."; break;
        case 1184: texte = "Si tu trouves un poisson déjà connu ailleurs, c'est que tu es toujours dans la même région de pêche."; break;
        case 1185: texte = "La pêche ne sert pas uniquement à se divertir, un poisson pêché te redonne de la vie. La quantité de vie gagnée dépend du poisson pêché."; break;
        case 1186: texte = "Tsss... la jeunesse de nos jours..."; break;
        case 1187: texte = "J'ai passé des heures à pêcher au bord du lac, et je n'ai pu trouver que 3 poissons différents..."; break;
        case 1188: texte = "Il fallait aller pêcher à différents endroits pour trouver plus de 3 poissons ?*Si j'avais su..."; break;
        case 1189: texte = "Je te sers quelque chose ?"; break;
        case 1190: texte = "Tu as besoin de l'aide du gars qui picole là-bas ?*Je ne peux toutefois pas le laisser partir sans payer."; break;
        case 1191: texte = "Tu veux régler sa dette ? C'est 10 000 Rubis, ok ?*              OUI ?            non  "; break;
        case 1192: texte = "Tu veux régler sa dette ? C'est 10 000 Rubis, ok ?*              oui              NON ?"; break;
        case 1193: texte = "Evidemment..."; break;
        case 1194: texte = "Je te propose autre chose : j'utilise habituellement un roc givre pour préparer des boissons fraîches, mais je viens d'user le dernier laissé par mes ancêtres..."; break;
        case 1195: texte = "Si tu m'apportes un nouveau roc givre, je veux bien effacer cette dette."; break;
        case 1196: texte = "Alors, tu ne trouves pas de roc givre ?"; break;
        case 1197: texte = "Tu as un roc givre ? Incroyable..."; break;
        case 1198: texte = "Tu me donnes ce roc givre et j'oublie la dette, ok ?*              OUI ?            non  "; break;
        case 1199: texte = "Tu me donnes ce roc givre et j'oublie la dette, ok ?*              oui              NON ?"; break;
        case 1200: texte = "Je comprends, ce ne sont pas tes affaires après tout."; break;
        case 1201: texte = "Merci!*Comme promis, le vieil homme peut partir, il ne me doit plus rien."; break;
        case 1202: texte = "Laisse-moi boire en paix! Hic!"; break;
        case 1203: texte = "Tu viens de la mine ?*J'y travaille habituellement...*Avec l'apparition de monstres la mine a provisoirement fermé..."; break;
        case 1204: texte = "Je pourrais t'aider à traverser la mine, mais le barman ne veut pas me laisser partir sans payer. Or je n'ai plus d'argent, je suis donc coincé ici, et je bois pour passer le temps."; break;
        case 1205: texte = "Il faudrait vraiment que quelqu'un paie ma dette à ma place...*...*Hic!"; break;
        case 1206: texte = "Tu veux savoir où trouver un roc givre ?*Mmm... j'ai entendu dire qu'un gars est arrivé à la cité d'Hyrule dernièrement, et qu'il va ouvrir une boutique d'un nouveau genre..."; break;
        case 1207: texte = "Et bien il me semble que ce gars possède un roc givre."; break;
        case 1208: texte = "Va voir le gars qui tient une boutique bizarre dans la cité d'Hyrule, il doit avoir un roc givre."; break;
        case 1209: texte = "Tu as un roc givre ???*Donne-le vite au barman, je promets de t'aider pour la mine!"; break;
        case 1210: texte = "Je suis libre désormais... Moi qui pensais faire la vaiselle jusqu'à la fin de la semaine!*Merci Link!"; break;
        case 1211: texte = "Tu peux aller à la mine, on se retrouve là-bas.**Hic!"; break;
        case 1212: texte = "Bienvenue au saloon, fais comme chez toi Link!"; break;
        case 1213: texte = "Tant que la mine au Nord reste fermée, je n'ai rien d'autre à faire que de passer mon temps ici..."; break;
        case 1214: texte = "Pratiquement tous les hommes du village travaillent à la mine au Nord du village."; break;
        case 1215: texte = "Ce matin des monstres sont apparus aux alentours et la mine a dû fermer."; break;
        case 1216: texte = "Le riz, les épices et les olives sont les marchandises de base du troc à Hyrule, tu devrais toujours en avoir sur toi."; break;
        case 1217: texte = "Je suis le chef de la mine, et l'homme le plus puissant du village, alors inutile d'essayer de me prendre de haut, fiston."; break;
        case 1218: texte = "Je suis le chef du village... Mais en réalité le chef de la mine a beaucoup plus d'influence que moi, il a embauché pratiquement tous les hommes du village."; break;
        case 1219: texte = "La banque est sous notre surveillance. RAS."; break;
        case 1220: texte = "Bienvenue dans la banque d'Hyrule. Je suis spécialisé en devises."; break;
        case 1221: texte = "Tu n'as rien qui m'intéresse, reviens si tu trouves de l'or, je t'en donnerai un bon prix."; break;
        case 1222: texte = "Tu possèdes des pièces d'or ? Avec une tête de monstre dessus... Des Ganon d'or tu dis ?"; break;
        case 1223: texte = "C'est très laid, mais l'or est récupérable, alors voyons..."; break;
        case 1224: texte = " Ganon d'or contre "; break;
        case 1225: texte = " Rubis, ok ?**              OUI ?            non  "; break;
        case 1226: texte = " Ganon d'or contre "; break;
        case 1227: texte = " Rubis, ok ?**              oui              NON ?"; break;
        case 1228: texte = "Ta bourse est pleine, reviens plus tard, je te rachèterai tout ça."; break;
        case 1229: texte = "Affaire conclue!"; break;
        case 1230: texte = "Tu possèdes des pièces d'or ? Je pensais que cette monnaie avait disparue depuis longtemps..."; break;
        case 1231: texte = "Je vais t'en donner un bon prix, alors voyons..."; break;
        case 1232: texte = " Pièce d'or contre "; break;
        case 1233: texte = " Rubis, ok ?**              OUI ?            non  "; break;
        case 1234: texte = " Pièce d'or contre "; break;
        case 1235: texte = " Rubis, ok ?**              oui              NON ?"; break;
        case 1236: texte = "Affaire conclue!"; break;
        case 1237: texte = "Que veux-tu me vendre ?*   - PIECE D'OR ?*   - Ganon d'or  *   - Rien  "; break;
        case 1238: texte = "Que veux-tu me vendre ?*   - Pièce d'or  *   - GANON D'OR ?*   - Rien  "; break;
        case 1239: texte = "Que veux-tu me vendre ?*   - Pièce d'or  *   - Ganon d'or  *   - RIEN ?"; break;
        case 1240: texte = "Je suis ici pour construire un pont pour se rendre au Nord. Je suis sûr que ça servira un jour."; break;
        case 1241: texte = "L'ennui c'est qu'il me manque des outils...*Comment vais-je faire ?"; break;
        case 1242: texte = "Ce marteau me plait...*Il me serait fort utile, veux-tu me le céder contre un trésor légendaire que j'ai trouvé lorsque j'étais explorateur ?"; break;
        case 1243: texte = "Ce marteau contre un trésor légendaire, ok ?**              OUI ?            non  "; break;
        case 1244: texte = "Ce marteau contre un trésor légendaire, ok ?**              oui              NON ?"; break;
        case 1245: texte = "Merci, prends ceci en échange :"; break;
        case 1246: texte = "Je sens que ce pont ne sera jamais terminé..."; break;
        case 1247: texte = "Tu as obtenu la flèche de feu!*Cette flèche enflammée utilise de la magie et délivre une puissance incroyable!"; break;
        case 1248: texte = "Il semblerait que j'ai enfin tout ce dont j'avais besoin...*Je me motive, puis j'y vais!"; break;
        case 1249: texte = "C'est le plan d'un pont ?*J'en aurais vraiment besoin, veux-tu me le céder contre un trésor légendaire que j'ai trouvé lorsque j'étais explorateur ?"; break;
        case 1250: texte = "Ce plan contre un trésor légendaire, ok ?**              OUI ?            non  "; break;
        case 1251: texte = "Ce plan contre un trésor légendaire, ok ?**              oui              NON ?"; break;
        case 1252: texte = "Merci, prends ce cadeau en échange :"; break;
        case 1253: texte = "Tu as obtenu la flèche de glace!*Cette flèche givrante utilise de la magie et délivre une puissance incroyable!"; break;
        case 1254: texte = "Tu as une scie ?*Je ne pourrais pas faire de pont sans, veux-tu me la céder contre un trésor légendaire que j'ai trouvé lorsque j'étais explorateur ?"; break;
        case 1255: texte = "Cette scie contre un trésor légendaire, ok ?**              OUI ?            non  "; break;
        case 1256: texte = "Cette scie contre un trésor légendaire, ok ?**              oui              NON ?"; break;
        case 1257: texte = "Merci, prends ce présent en échange :"; break;
        case 1258: texte = "Tu as obtenu la flèche de lumière!*Cette flèche utilise beaucoup de magie et délivre une puissance ultime!"; break;
        case 1259: texte = "Tu as un clou ?*Ca peut toujours servir, veux-tu me le céder contre une babiole ?"; break;
        case 1260: texte = "Ce clou contre une babiole, ok ?**              OUI ?            non  "; break;
        case 1261: texte = "Ce clou contre une babiole, ok ?**              oui              NON ?"; break;
        case 1262: texte = "Merci, prends donc ça en échange :"; break;
        case 1263: texte = "Bonjour Link, tu te souviens de moi ?"; break;
        case 1264: texte = "Des monstres sont apparus sur Hyrule aujourd'hui, alors une fois de plus je vais tâcher de tous les répertorier, et une fois de plus je compte sur ton aide."; break;
        case 1265: texte = "En appuyant sur ¾6, tu peux voir les monstres déjà répertorier. Tu n'as qu'à vaincre un monstre pour qu'il soit ajouté."; break;
        case 1266: texte = "En appuyant sur M, tu peux voir les monstres déjà répertorier. Tu n'as qu'à vaincre un monstre pour qu'il soit ajouté."; break;
        case 1267: texte = "10 pièces d'or"; break;
        case 1268: texte = "40 Rubis"; break;
        case 1269: texte = "20 Ganon d'or"; break;
        case 1270: texte = "Je te devrai "; break;
        case 1271: texte = " à chaque monstre ajouté. Passe me voir régulièrement pour chercher ce que je te dois."; break;
        case 1272: texte = " Pièces d'or"; break;
        case 1273: texte = " Rubis"; break;
        case 1274: texte = " Ganon d'or"; break;
        case 1275: texte = "Je te dois "; break;
        case 1276: texte = ", veux-tu être payé maintenant ?*              OUI ?            non  "; break;
        case 1277: texte = " Pièces d'or"; break;
        case 1278: texte = " Rubis"; break;
        case 1279: texte = " Ganon d'or"; break;
        case 1280: texte = "Je te dois "; break;
        case 1281: texte = ", veux-tu être payé maintenant ?*              oui              NON ?"; break;
        case 1282: texte = "Ton compte est à 0, je t'ai tout donné."; break;
        case 1283: texte = "Bienvenue dans la banque d'Hyrule. Je suis spécialisé en devises."; break;
        case 1284: texte = "Tu n'as rien qui m'intéresse, reviens si tu trouves de l'or ou des Rubis, je t'en donnerai un bon prix."; break;
        case 1285: texte = "Tu possèdes des Rubis ? Ca fait longtemps qu'ils ne sont plus utilisés, mais leur valeur reste indéniable..."; break;
        case 1286: texte = "Alors voyons..."; break;
        case 1287: texte = " Rubis contre "; break;
        case 1288: texte = " Ganon d'or, ok ?**              OUI ?            non  "; break;
        case 1289: texte = " Rubis contre "; break;
        case 1290: texte = " Ganon d'or, ok ?**              oui              NON ?"; break;
        case 1291: texte = "Affaire conclue!"; break;
        case 1292: texte = "Tu possèdes des pièces d'or ? C'est incroyable que tu aies pu trouver une monnaie aussi ancienne!"; break;
        case 1293: texte = "Elles contiennent beaucoup d'or... *Alors voyons..."; break;
        case 1294: texte = " Pièce d'or contre "; break;
        case 1295: texte = " Ganon d'or, ok ?**              OUI ?            non  "; break;
        case 1296: texte = " Pièce d'or contre "; break;
        case 1297: texte = " Ganon d'or, ok ?**              oui              NON ?"; break;
        case 1298: texte = "Affaire conclue!"; break;
        case 1299: texte = "Que veux-tu me vendre ?*   - PIECE D'OR ?*   - Rubis  *   - Rien  "; break;
        case 1300: texte = "Que veux-tu me vendre ?*   - Pièce d'or  *   - RUBIS ?*   - Rien  "; break;
        case 1301: texte = "Que veux-tu me vendre ?*   - Pièce d'or  *   - Rubis  *   - RIEN ?"; break;
        case 1302: texte = "Ca faisait longtemps que je ne m'étais pas autant amusé!"; break;
        case 1303: texte = "L'un de mes ancêtres voulait construire un pont, mais il n'a réussit qu'à en faire le plan..."; break;
        case 1304: texte = "Je viens d'une lignée d'incapables, pas étonnant que je sois si nul en tout... En plus je suis malade, et personne ne m'aime..."; break;
        case 1305: texte = "Tu as une corde ?*Donne-la-moi s'il te plaît, je te donnerai l'héritage de ma famille, de toute façon je n'ai pas de descendants..."; break;
        case 1306: texte = "Cette corde contre son héritage, ok ?**              OUI ?            non  "; break;
        case 1307: texte = "Cette corde contre son héritage, ok ?**              oui              NON ?"; break;
        case 1308: texte = "Bon bah...*...Merci hein...*..."; break;
        case 1309: texte = "J'en étais sûr, de toute façon on ne m'a jamais rien donné..."; break;
        case 1310: texte = "Tu as troqué la corde contre le plan d'un pont."; break;
        case 1311: texte = "...*J'aimerais être seul un moment..."; break;
        case 1312: texte = "Bonjour, tu dois être Link, j'attendais ta venue."; break;
        case 1313: texte = "Je suis un descendant des 7 sages. Traqué par les sbires de Ganon, j'ai dû fuir jusqu'ici."; break;
        case 1314: texte = "Te voir ici me redonne espoir, je vais aller prendre place dans la grotte du portail.*Prends ceci, ça devrait t'être utile."; break;
        case 1315: texte = "Tu as obtenu un poivron !"; break;
        case 1316: texte = "Bonne chance Link!"; break;
        case 1317: texte = "Bienvenue Link, je t'attendais..."; break;
        case 1318: texte = "Tu dois avoir beaucoup de questions, laisse-moi y répondre."; break;
        case 1319: texte = "Nous sommes à Hyrule, mais dans ce qui n'est pour toi qu'un triste futur...*Le portail que tu as pris t'a permis de venir ici, pour être témoin de ces sombres jours..."; break;
        case 1320: texte = "Tu veux savoir ce qui s'est passé ? Ganon a attaqué le château, plus fort que jamais, et tu as été vaincu."; break;
        case 1321: texte = "Avant son exécution, la princesse Zelda a réussi à faire parvenir son plan aux sages. Le vol de l'Ocarina du Temps fut selon elle le tournant de cette guerre, elle a donc demandé aux descendants des 7 sages de te remettre l'ocarina lorsque tu arriverais via le portail."; break;
        case 1322: texte = "Le jour est enfin venu puisque tu te tiens désormais face à moi.*Cependant... l'ocarina n'a jamais été retrouvé."; break;
        case 1323: texte = "Nous avons donc mis au point un autre plan. Nous allons t'envoyer dans le passé, la nuit où l'ocarina fut volé, pour que tu surprennes le voleur."; break;
        case 1324: texte = "Nous ne sommes désormais plus que 3 descendants des sages, cherche et trouve les 2 autres ainsi que la clé du temps, et nous t'ouvrirons le portail."; break;
        case 1325: texte = "Prends ceci, ça devrait t'aider dans tes recherches :"; break;
        case 1326: texte = "Tu as obtenu le grappin !*Sers-t'en pour franchir les précipices!"; break;
        case 1327: texte = "L'un d'entre eux se cache au fond d'un donjon, au milieu du lac."; break;
        case 1328: texte = "Le dernier sage se cache vers les cascades."; break;
        case 1329: texte = "La clé du temps se trouve au fond de la Grande Pyramide."; break;
        case 1330: texte = "Les sages sont dans la grotte, la clé du temps est en ta possession...*Très bien, retrouvons-nous à la grotte du portail, le temps est venu."; break;
        case 1331: texte = "Dans le temple du Temps se trouve un air qui, joué par l'ocarina, te ramènera à ton époque."; break;
        case 1332: texte = "Bonne chance Link, nous comptons tous sur toi."; break;
        case 1333: texte = "10 flèches pour 10 Ganon d'or ?**              OUI ?            non  "; break;
        case 1334: texte = "10 flèches pour 10 Ganon d'or ?**              oui              NON ?"; break;
        case 1335: texte = "5 bombes pour 15 Ganon d'or ?**              OUI ?            non  "; break;
        case 1336: texte = "5 bombes pour 15 Ganon d'or ?**              oui              NON ?"; break;
        case 1337: texte = "Un petit coeur pour 4 Ganon d'or ?**              OUI ?            non  "; break;
        case 1338: texte = "Un petit coeur pour 4 Ganon d'or ?**              oui              NON ?"; break;
        case 1339: texte = "Une petite fiole de magie pour 8 Ganon d'or ?**              OUI ?            non  "; break;
        case 1340: texte = "Une petite fiole de magie pour 8 Ganon d'or ?**              oui              NON ?"; break;
        case 1341: texte = "Une grande fiole de magie pour 16 Ganon d'or ? *              OUI ?            non  "; break;
        case 1342: texte = "Une grande fiole de magie pour 16 Ganon d'or ? *              oui              NON ?"; break;
        case 1343: texte = "Chaque seconde est une goutte de plus dans la cafetière, tu me fais perdre mon temps."; break;
        case 1344: texte = "Tu veux bosser pour moi ? La valeur d'un homme se mesure à sa charge de travail, c'est ce que je dis toujours !"; break;
        case 1345: texte = "Cours sur le tapis roulant pour charger la dynamo, puis marche sur l'interrupteur. Cela mettra en marche la cafetière. Après ça viens me voir, et tu auras de l'argent."; break;
        case 1346: texte = "Je ne te demande pas si tu es prêt, la préparation est l'ultime refuge des faibles."; break;
        case 1347: texte = "Je ne bois jamais plus de 17 tasses de café par jour.*Mais la première est toujours la meilleure."; break;
        case 1348: texte = "Plus noir qu'une nuit sans lune, plus brûlant et amer que l'enfer... *Ca, c'est du café."; break;
        case 1349: texte = "Visiblement, on va en prendre une autre pour la route."; break;
        case 1350: texte = "Au fait, ne mets pas de sel dans ton café. J'ai essayé, c'est dégoûtant."; break;
        case 1351: texte = "Ce café... C'est un mélange spécial que j'ai appelé Godot N107. J'hésite entre réduire son acidité et diminuer son amertume... C'est tout ce que j'ai en tête pour l'instant..."; break;
        case 1352: texte = "Ah... !*Ma 6ème tasse de café me regarde d'un air froid."; break;
        case 1353: texte = "Mélange Godot N102...*... Mon préféré."; break;
        case 1354: texte = "Ah... ! Ce mélange...*Du mélange Godot N107...*Il est peut-être un peu trop amer en fin de compte !"; break;
        case 1355: texte = "...*Aaah, amer !"; break;
        case 1356: texte = "Les faibles se font emporter par le flot du destin, les forts arrivent à l'ingurgiter. *Ah... !*Le destin a, aujourd'hui encore, un goût d'amertume."; break;
        case 1357: texte = "Ma 11ème tasse...*Je me suis promis de ne pas dépasser 17 tasses par jour, j'ai donc encore de la marge..."; break;
        case 1358: texte = "Une petite goutte de lait suffit à détruire la noire magie du café !"; break;
        case 1359: texte = "... Quelle amertume.*Tu apprendras à apprécier l'amertume quand tu seras plus grand."; break;
        case 1360: texte = "Tu connais ma règle d'or ?*Jeter la tasse de café qui est imbuvable et en prendre une autre."; break;
        case 1361: texte = "Ah !*En ce cas, le moment est bien choisi... pour une autre tasse de magie noire !"; break;
        case 1362: texte = "Deux minutes ne suffisent pas pour extraire tout l'arôme d'un bon arabica..."; break;
        case 1363: texte = "La 17ème et dernière tasse.*L'heure est venue de classer cette affaire."; break;
        case 1364: texte = "J'ai bu mes 17 tasses, voilà une récompense :"; break;
        case 1365: texte = "Tu as encore besoin d'argent ? En voilà..."; break;
        case 1366: texte = "Les potions rouges redonnent de l'énergie alors que les potions vertes redonnent de la magie."; break;
        case 1367: texte = "Que désires-tu ?*                ? POTION ROUGE ?*                  potion verte  *                      rien      "; break;
        case 1368: texte = "Que désires-tu ?*                  potion rouge  *                ? POTION VERTE ?*                      rien      "; break;
        case 1369: texte = "Que désires-tu ?*                  potion rouge  *                  potion verte  *                ?     RIEN     ?"; break;
        case 1370: texte = "Une potion rouge pour 40 Ganon d'or ?**              OUI ?            non  "; break;
        case 1371: texte = "Une potion rouge pour 40 Ganon d'or ?**              oui              NON ?"; break;
        case 1372: texte = "Une potion verte pour 25 Ganon d'or ?**              OUI ?            non  "; break;
        case 1373: texte = "Une potion verte pour 25 Ganon d'or ?**              oui              NON ?"; break;
        case 1374: texte = "Ma famille n'a connu que malchance sur malchance depuis des siècles...*Même que je le voudrais, je n'aurai rien à t'offrir."; break;
        case 1375: texte = "Je suis l'homme le plus chanceux du pays."; break;
        case 1376: texte = "Tu ne me crois pas ?*Prends ce trésor que j'ai trouvé ce matin en me promenant, j'en trouverai sans doute un nouveau demain!"; break;
        case 1377: texte = "Tu obtiens un bijou précieux !"; break;
        case 1378: texte = "C'est curieux, en te donnant ce bijou j'ai l'étrange impression de régler une vieille dette familiale..."; break;
        case 1379: texte = "Je suis le pâtissier le plus réputé du pays."; break;
        case 1380: texte = "Malheureusement je n'ai plus rien en stock, on ne trouve plus grand chose de sucré depuis longtemps..."; break;
        case 1381: texte = "Tu as de la confiture ???*Je croyais que les dernières étaient périmées depuis des lustres! Donne-la-moi, contre ma réserve spéciale petit déj'!"; break;
        case 1382: texte = "Cette confiture contre sa réserve, ok ?**              OUI ?            non  "; break;
        case 1383: texte = "Cette confiture contre sa réserve, ok ?**              oui              NON ?"; break;
        case 1384: texte = "Je sens que je vais me régaler demain moi! *Voilà ce que je gardais de côté :"; break;
        case 1385: texte = "Dans ce cas pourquoi me l'as-tu présenté ? *Frimeur..."; break;
        case 1386: texte = "Tu as troqué la confiture contre un croissant."; break;
        case 1387: texte = "Tôt ou tard, il va bien falloir que je change de métier tout de même..."; break;
        case 1388: texte = "Tu as l'air encore plus fauché que moi...*Tu devrais voir le gars de la maison du café, il cherche un employé."; break;
        case 1389: texte = "Prends également ça, tu en auras besoin :"; break;
        case 1390: texte = "Tu as obtenu une bourse pouvant contenir 99 Ganon d'or !"; break;
        case 1391: texte = "Alors, comment se portent tes finances ?"; break;
        case 1392: texte = "Bienvenue dans la banque d'Hyrule. Je suis spécialisé en devises."; break;
        case 1393: texte = "Tu n'as rien qui m'intéresse, reviens si tu trouves des devises précieuses, je t'en donnerai un bon prix."; break;
        case 1394: texte = "Ce sont des Rubis dis-tu ? C'est assez curieux."; break;
        case 1395: texte = "Ca a l'air précieux, alors voyons..."; break;
        case 1396: texte = " Rubis contre "; break;
        case 1397: texte = " Pièce d'or, ok ?**              OUI ?            non  "; break;
        case 1398: texte = " Rubis contre "; break;
        case 1399: texte = " Pièce d'or, ok ?**              oui              NON ?"; break;
        case 1400: texte = "Affaire conclue!"; break;
        case 1401: texte = "Tu possèdes de l'or ? Avec une tête de monstre dessus... Des Ganon d'or tu dis ?"; break;
        case 1402: texte = "C'est très laid, mais l'or est récupérable, alors voyons..."; break;
        case 1403: texte = " Ganon d'or contre "; break;
        case 1404: texte = " Pièce d'or, ok ?**              OUI ?            non  "; break;
        case 1405: texte = " Ganon d'or contre "; break;
        case 1406: texte = " Pièce d'or, ok ?**              oui              NON ?"; break;
        case 1407: texte = "Affaire conclue!"; break;
        case 1408: texte = "Que veux-tu me vendre ?*   - RUBIS ?*   - Ganon d'or  *   - Rien  "; break;
        case 1409: texte = "Que veux-tu me vendre ?*   - Rubis  *   - GANON D'OR ?*   - Rien  "; break;
        case 1410: texte = "Que veux-tu me vendre ?*   - Rubis  *   - Ganon d'or  *   - RIEN ?"; break;
        case 1411: texte = "Bonjour Link, je t'attendais."; break;
        case 1412: texte = "Je suis le chef des 7 sages, mais aussi le plus puissant d'entre eux. Je t'ai vu dans mes songes, ainsi qu'un bien triste avenir..."; break;
        case 1413: texte = "Ta présence ici semble indiquer que j'ai réussi... Au moins partiellement..."; break;
        case 1414: texte = "Je suis celui qui a créé le portail vers le futur, dans le but que tu sois témoin de l'objet de mes visions."; break;
        case 1415: texte = "J'ai également construit le temple du Temps avec les autres sages, pour te permettre de voyager à ta guise entre les époques."; break;
        case 1416: texte = "Désormais c'est à toi de jouer. Trouve les 7 cristaux magiques qui t'ouvriront l'accès au légendaire temple des Déesses, et soit le premier à t'emparer de la Triforce!"; break;
        case 1417: texte = "Puisse son chemin mener le héros à la Triforce."; break;
        case 1418: texte = "Ne te fie pas à ma taille, je suis un forgeron de premier ordre."; break;
        case 1419: texte = "Cependant je dois avouer que je viens d'emménager, et je n'étais pas de taille à déménager ma forge jusqu'ici... Donc je n'ai plus rien."; break;
        case 1420: texte = "Tu as transporté une enclume avec toi ???*T'es bête ou quoi ?"; break;
        case 1421: texte = "Je peux t'en délester si tu veux, je pourrais en avoir besoin. *Je te donnerai même une petite récompense pour l'effort."; break;
        case 1422: texte = "Cette enclume contre une récompense, ok ?**              OUI ?            non  "; break;
        case 1423: texte = "Cette enclume contre une récompense, ok ?**              oui              NON ?"; break;
        case 1424: texte = "Merci, voici un fer à cheval que j'avais réalisé il y a quelques temps :"; break;
        case 1425: texte = "Je disais ça pour t'aider..."; break;
        case 1426: texte = "Tu as obtenu un fer à cheval!"; break;
        case 1427: texte = "Avec tout ce que tu m'as apporté, je vais pouvoir réouvrir ma forge!"; break;
        case 1428: texte = "C'est un beau marteau que tu as là...*Il pourrait faire l'affaire pour ma forge... Tu me le cèderais ? Je te récompenserai par une de mes créations."; break;
        case 1429: texte = "Ce marteau contre une récompense, ok ?**              OUI ?            non  "; break;
        case 1430: texte = "Ce marteau contre une récompense, ok ?**              oui              NON ?"; break;
        case 1431: texte = "Merci, voici une de mes plus belles créations :"; break;
        case 1432: texte = "Comme si ce marteau pouvait t'être utile..."; break;
        case 1433: texte = "Tu as obtenu une clochette!"; break;
        case 1434: texte = "Tu as de la poudre d'or ?*J'en aurai besoin pour forger à nouveau des objets exceptionnels, tu me la donnes contre une récompense exceptionnelle ?"; break;
        case 1435: texte = "La poudre d'or contre une récompense, ok ?**              OUI ?            non  "; break;
        case 1436: texte = "La poudre d'or contre une récompense, ok ?**              oui              NON ?"; break;
        case 1437: texte = "Merci, prends ce miroir magique en échange! *Il a été envoûté par les sages et possède un pouvoir mystérieux..."; break;
        case 1438: texte = "Je t'aurais largement dédommagé pourtant..."; break;
        case 1439: texte = "Tu as obtenu le miroir magique!"; break;
        case 1440: texte = "Ton épée est impressionnante... Je devrais toutefois pouvoir l'améliorer..."; break;
        case 1441: texte = "Veux-tu que je reforge ton épée ?**              OUI ?            non  "; break;
        case 1442: texte = "Veux-tu que je reforge ton épée ?**              oui              NON ?"; break;
        case 1443: texte = "Laisse-moi ton épée dans ce cas, ce ne sera pas long."; break;
        case 1444: texte = "Dommage, ton épée est vraiment fascinante..."; break;
        case 1445: texte = "Tu as confié Excalibur."; break;
        case 1446: texte = "Ce ne sera pas long, ne t'inquiète pas."; break;
        case 1447: texte = "C'est prêt, voici ton épée :"; break;
        case 1448: texte = "Excalibur a été reforgée! Sa puissance a bien augmenté!"; break;
        case 1449: texte = "Un jour, je forgerai une épée aussi belle que la tienne, foi de forgeron!"; break;
        case 1450: texte = "Tu ne devrais pas t'éloigner du village par ce temps..."; break;
        case 1451: texte = "10 flèches pour 5 Pièces d'or ?**              OUI ?            non  "; break;
        case 1452: texte = "10 flèches pour 5 Pièces d'or ?**              oui              NON ?"; break;
        case 1453: texte = "5 bombes pour 10 Pièces d'or ?**              OUI ?            non  "; break;
        case 1454: texte = "5 bombes pour 10 Pièces d'or ?**              oui              NON ?"; break;
        case 1455: texte = "Un petit coeur pour 1 Pièce d'or ?**              OUI ?            non  "; break;
        case 1456: texte = "Un petit coeur pour 1 Pièce d'or ?**              oui              NON ?"; break;
        case 1457: texte = "Une petite fiole de magie pour 3 Pièces d'or ? *              OUI ?            non  "; break;
        case 1458: texte = "Une petite fiole de magie pour 3 Pièces d'or ? *              oui              NON ?"; break;
        case 1459: texte = "Une grande fiole de magie pour 6 Pièces d'or ? *              OUI ?            non  "; break;
        case 1460: texte = "Une grande fiole de magie pour 6 Pièces d'or ? *              oui              NON ?"; break;
        case 1461: texte = "Tu as trouvé le livre de Mudora!*Tu comprends désormais le Hylien ancien !"; break;
        case 1462: texte = "Bonjour, je suis le chef de ce village. *N'écoute pas les rumeurs comme quoi ce village serait menacé, et passe du bon temps parmi nous."; break;
        case 1463: texte = "La neige semble s'être arrêtée..."; break;
        case 1464: texte = "Les potions rouges redonnent de l'énergie alors que les potions vertes redonnent de la magie."; break;
        case 1465: texte = "Que désires-tu ?*                ? POTION ROUGE ?*                  potion verte  *                      rien      "; break;
        case 1466: texte = "Que désires-tu ?*                  potion rouge  *                ? POTION VERTE ?*                      rien      "; break;
        case 1467: texte = "Que désires-tu ?*                  potion rouge  *                  potion verte  *                ?     RIEN     ?"; break;
        case 1468: texte = "Une potion rouge pour 15 Pièces d'or ?**              OUI ?            non  "; break;
        case 1469: texte = "Une potion rouge pour 15 Pièces d'or ?**              oui              NON ?"; break;
        case 1470: texte = "Une potion verte pour 10 Pièces d'or ?**              OUI ?            non  "; break;
        case 1471: texte = "Une potion verte pour 10 Pièces d'or ?**              oui              NON ?"; break;
        case 1472: texte = "Tu as l'air bien pauvre, tu n'as même pas de bourse sur toi ?*Prends donc celle-là :"; break;
        case 1473: texte = "Tu as obtenu une bourse pouvant contenir 99 pièces d'or !"; break;
        case 1474: texte = "Bonjour, je suis un des 7 sages, de passage dans le coin."; break;
        case 1475: texte = "Le livre de Mudora a été envoûté pour permettre à quiconque le possède de parler couramment notre langue."; break;
        case 1476: texte = "Tu dois venir de loin pour ne pas parler hylien... Garde ce livre, tu en auras besoin."; break;
        case 1477: texte = "Salut mon gars, moi c'est Ganondorf, si tu découvres quoi que ce soit sur les cristaux magiques, tu viens m'en parler, ça marche ?"; break;
        case 1478: texte = "Je suis le chef des chevaliers hyliens. *Si tu ne veux pas de soucis tiens-toi à carreau, prends exemple sur Ganondorf, c'est un bon gars."; break;
        case 1479: texte = "Ce Ganondorf n'arrête pas de nous payer à boire... *C'est vraiment un type bien..."; break;
        case 1480: texte = "C'est bien beau de boire... mais quand est-ce qu'on mange ?"; break;
        case 1481: texte = "Ne me dis rien... A l'odeur... C'est un croissant !*Donne-le-moi, en échange de mon amitié éternelle!"; break;
        case 1482: texte = "Ce croissant contre son amitié, ok ?**              OUI ?            non  "; break;
        case 1483: texte = "Ce croissant contre son amitié, ok ?**              oui              NON ?"; break;
        case 1484: texte = "Merci!!!*Prends ce cadeau en échange, ce sera le symbole de notre amitié!"; break;
        case 1485: texte = "... Tu déclares la guerre aux chevaliers hyliens ???*T'es fou ou quoi ???"; break;
        case 1486: texte = "Tu as troqué le croissant contre une bière."; break;
        case 1487: texte = "Salut mon pote!*Tu viens boire un coup avec nous ?"; break;
        case 1488: texte = "Si tu veux qu'un chevalier hylien te dévoile une info top secrète, il faut lui payer à boire. C'est notre règle."; break;
        case 1489: texte = "Tu connais déjà toutes mes infos...*Hic!"; break;
        case 1490: texte = "J'ai plein d'infos secrètes connues de nous seuls (et de Ganondorf). Un verre de bière coûte 1 pièce d'or, affaire conclue ?"; break;
        case 1491: texte = "Une info pour 1 pièce d'or, ok ?**              OUI ?            non  "; break;
        case 1492: texte = "Une info pour 1 pièce d'or, ok ?**              oui              NON ?"; break;
        case 1493: texte = "Les chevaliers hyliens auraient été fondés pour protéger le légendaire temple des Déesses... Temple qui cacherait une relique toute puissante appelée Triforce..."; break;
        case 1494: texte = "Pour ouvrir l'accès au temple des Déesses, il faut se rendre sur la terre sacrée, au nord d'ici, et se tenir sur le symbole de la Triforce avec les 7 cristaux magiques en poche."; break;
        case 1495: texte = "Les 7 cristaux magiques sont cachés un peu partout dans Hyrule... Et, garde ça pour toi, l'un d'entre eux est en possession des légendaires chevaliers hyliens!"; break;
        case 1496: texte = "Notre chef l'a poursuivi en bas..."; break;
        case 1497: texte = "Quelle force... nous avons été balayés si vite..."; break;
        case 1498: texte = "Il est... au sous-sol...*Soit prudent... ... mon ami."; break;
        case 1499: texte = "Il est trop fort... Le chef ne tiendra pas longtemps...*Va l'aider, je t'en prie..."; break;
        case 1500: texte = "Il... faut l'arrêter..."; break;
        case 1501: texte = "Tu comptes également te mettre sur mon chemin ? Alors en garde!"; break;
        case 1502: texte = "J'ai échoué...*Pardonnez-moi maître..."; break;
        case 1503: texte = "Merci de ton aide Link, sans toi Ganondorf se serait emparé du cristal..."; break;
        case 1504: texte = "L'ordre des chevaliers a été fondé pour garder l'accès au temple des Déesses, nous avions donc pour mission de cacher ce cristal. Sans celui-ci, les 6 autres ne servent à rien."; break;
        case 1505: texte = "Hélas, avec le temps, l'ordre s'est affaibli. Et aujourd'hui, nous avons échoué."; break;
        case 1506: texte = "Garde le cristal, tu es plus à même de le défendre que nous..."; break;
        case 1507: texte = "Quant à Ganondorf... Jamais nous n'aurions pu deviner qu'il allait nous trahir... Il était pratiquement l'un des nôtres..."; break;
        case 1508: texte = "Il a été conduit à la prison de haute sécurité, un peu au Nord d'ici... *Il ne devrait plus causer de soucis désormais..."; break;
        case 1509: texte = "J'ai échoué contre Ganondorf, mais ne me sous-estime pas pour autant. Je suis l'homme qui a vaincu 100 loups."; break;
        case 1510: texte = "Tu n'as battu aucun loup ???*Mais t'es un lâche!"; break;
        case 1511: texte = "Tu n'as battu qu'un seul loup ???*Mais t'es un faible!"; break;
        case 1512: texte = "Tu as battu seulement "; break;
        case 1513: texte = " loups ?*C'est pas terrible..."; break;
        case 1514: texte = "Tu as battu "; break;
        case 1515: texte = " loups ?*C'est pas mal..."; break;
        case 1516: texte = "Tu as battu "; break;
        case 1517: texte = " loups ?*C'est plutôt impressionnant..."; break;
        case 1518: texte = "Tu as battu 100 loups ?*Autant que moi... c'est dur à croire..."; break;
        case 1519: texte = "Tu as battu plus de 100 loups ???*Incroyable..."; break;
        case 1520: texte = "Tu as bien mérité cette récompense :"; break;
        case 1521: texte = "Il est temps pour moi de reprendre l'entraînement..."; break;
        case 1522: texte = "Je vais changer de coiffure."; break;
        case 1523: texte = "Je vais commencer un régime."; break;
        case 1524: texte = "Je ne vendrai plus d'infos top secrètes."; break;
        case 1525: texte = "Je ne passerai plus mes journées à la taverne."; break;
        case 1526: texte = "J'ai cassé ma dernière hache... Alors je joue au pendu pour tuer le temps, mais c'est pas pareil..."; break;
        case 1527: texte = "Tu as une hache pour moi ???*Donne-la-moi! Je te l'échange contre une corde tout aussi efficace!"; break;
        case 1528: texte = "Cette hache contre une corde, ok ?**              OUI ?            non  "; break;
        case 1529: texte = "Cette hache contre une corde, ok ?**              oui              NON ?"; break;
        case 1530: texte = "Je suis tellement ému...*Voilà pour toi :"; break;
        case 1531: texte = "...*Ca devrait être passible de la peine de mort..."; break;
        case 1532: texte = "Tu as troqué la hache contre une corde."; break;
        case 1533: texte = "Je suis impatient d'essayer cette hache!"; break;
        case 1534: texte = "Bonjour, je suis le chef de ce village."; break;
        case 1535: texte = "Le village des Mouettes est le paradis pour les touristes, mais aussi l'enfer pour les brigands."; break;
        case 1536: texte = "Savais-tu qu'un célèbre pirate avait été capturé lors de son passage dans cette ville ?"; break;
        case 1537: texte = "Tu as trouvé un marteau!"; break;
        case 1538: texte = "Mon époux est garde à la prison.*C'est un travail à temps plein alors on ne se voit pas beaucoup..."; break;
        case 1539: texte = "???*Qu'as-tu là ???*Laisse-moi examiner ça!"; break;
        case 1540: texte = "Lui laisser l'alliance, ok ?**              OUI ?            non  "; break;
        case 1541: texte = "Lui laisser l'alliance, ok ?**              oui              NON ?"; break;
        case 1542: texte = "L'alliance de mon mari!*Ne me dis pas qu'il est retourné LA voir!!!"; break;
        case 1543: texte = "...*Ca me semble très louche...*Laisse-moi voir ça!"; break;
        case 1544: texte = "Tu as troqué l'alliance contre rien."; break;
        case 1545: texte = "Pousse-toi de mon chemin!"; break;
        case 1546: texte = "Ne va pas à la réserve, je n'y ai pas fait le ménage!"; break;
        case 1547: texte = "Un célèbre pirate nommé Ganon D. Roger fut capturé dans cette ville il y a bien longtemps..."; break;
        case 1548: texte = "D'après des rumeurs, un descendant de ce pirate serait à Hyrule en ce moment..."; break;
        case 1549: texte = "Tu es ici dans la demeure des 7 sages.*Ce lieu est celui de la méditation et de la connaissance."; break;
        case 1550: texte = "Notre chef, le plus puissant des 7 sages, vient rarement ici. Il préfère rester à méditer dans sa maison au Sud du village."; break;
        case 1551: texte = "Il y a quelques années, nous étions 8 sages. L'un d'entre nous, Agahnim, pensait qu'il était de notre devoir de récupérer la Triforce et de s'en servir dans l'intérêt de tous."; break;
        case 1552: texte = "Notre chef s'y opposa catégoriquement. Il disait qu'un tel pouvoir ne devait pas tomber entre les mains des hommes, que les conséquences pourraient être terribles..."; break;
        case 1553: texte = "Après ce différent, Agahnim quitta l'ordre. Mais dernièrement, il a réapparu, doté d'étranges pouvoirs...*Nous ne savons hélas pas ce qu'il a en tête."; break;
        case 1554: texte = "Un pirate légendaire est venu en Hyrule il y a longtemps. Il fut capturé à la suite d'un long combat face aux chevaliers hyliens de l'époque."; break;
        case 1555: texte = "Le jour de son exécution publique, un homme dans la foule lui demanda où il avait caché son trésor. Le pirate expliqua l'avoir caché dans 4 temples d'Hyrule."; break;
        case 1556: texte = "Suite à cette déclaration, de nombreux hommes partir à la recherche de ces trésors, mais aucun ne revint jamais..."; break;
        case 1557: texte = "As-tu rencontré un certain Ganondorf ? *Lorsqu'il était encore enfant, il faillit finir dans l'estomac d'un loup, mais fut sauvé par un ancien membre de notre ordre."; break;
        case 1558: texte = "Depuis il considère son sauveur comme son mentor."; break;
        case 1559: texte = "Notre chef nous demanda d'unir nos pouvoirs pour créer un temple très particulier à l'Est d'ici. Selon lui ce temple permettra de sauver le monde..."; break;
        case 1560: texte = "La montagne au Nord du village cache un temple. Au fond de ce temple se trouve un trésor inestimable. Mais... c'est bien trop dangereux d'y aller."; break;
        case 1561: texte = "Je n'en reviens toujours pas que tu aies pu récupérer ce trésor..."; break;
        case 1562: texte = "QUOI ??? TU AS TROUVE LE TRESOR DU TEMPLE !!!"; break;
        case 1563: texte = "Incroyable... prends ça, je tiens à te récompenser pour ton exploit!"; break;
        case 1564: texte = "Ca fait longtemps qu'IL ne m'a rien offert..."; break;
        case 1565: texte = "Tu as un bijou pour moi ?*Ca vient de LUI n'est-ce pas ?*Oui ça ne peut venir que de LUI!"; break;
        case 1566: texte = "Donner ce bijou ?**              OUI ?            non  "; break;
        case 1567: texte = "Donner ce bijou ?**              oui              NON ?"; break;
        case 1568: texte = "C'est tellement gentil de sa part...*Peux-tu aller lui porter cette lettre à la prison s'il te plaît ?"; break;
        case 1569: texte = "...*Je LUI dirai !"; break;
        case 1570: texte = "Tu as troqué le bijou contre une lettre."; break;
        case 1571: texte = "Hi! Hi! Hi!"; break;
        case 1572: texte = "Je suis le chef du village et euh... de toute façon ce sont les sages qui commandent ici..."; break;
        case 1573: texte = "Nous sommes fermés au public."; break;
        case 1574: texte = "Nous t'avons longtemps attendu...*Prends le temps de visiter mon opéra..."; break;
        case 1575: texte = "Cet opéra a une longue histoire, prends le temps de la découvrir..."; break;
        case 1576: texte = "Bienvenue à toi visiteur, laisse-moi te conter l'histoire de cet endroit."; break;
        case 1577: texte = "Je suis le fondateur de cet opéra, mais autrefois je n'étais qu'un simple voleur."; break;
        case 1578: texte = "Un jour, un cambriolage a mal tourné, les chevaliers hyliens qui patrouillaient près de la taverne me sont tombés dessus. Je fus condamné et emmené en prison."; break;
        case 1579: texte = "En prison, je trouvai un vieux crâne sous ma couchette. Je m'en servis alors comme accessoire pour réciter des tirades, au grand bonheur de mon compagnon de cellule."; break;
        case 1580: texte = "C'est donc en prison que ma vocation pour le théâtre, puis pour l'opéra, débuta."; break;
        case 1581: texte = "Peu de temps avant ma libération, je me fis la promesse sur le vieux crâne de construire le plus somptueux des théâtres avant la sortie de prison de mon compagnon de cellule."; break;
        case 1582: texte = "Une fois libéré, je partis à la recherche d'un terrain où construire. Jusqu'au jour où, poursuivi par des loups, je dus me réfugier aux bois perdus."; break;
        case 1583: texte = "C'est alors que je trouvai cette clairière, au fin fond de la forêt, dans un cadre magique, sous l'ombre d'arbres millénaires..."; break;
        case 1584: texte = "Je commençai alors à construire mon opéra. Les plans furent rapidement prêts, mais sans argent pour payer des ouvriers, le travail s'annonçait long et pénible."; break;
        case 1585: texte = "Alors que je songeais à renoncer, un étrange personnage vint m'apporter le crâne, et me remémorer ma promesse."; break;
        case 1586: texte = "Après des mois de travail, l'opéra fut achevé. Ce fut le plus bel opéra jamais vu en Hyrule."; break;
        case 1587: texte = "Très vite, de prestigieux artistes venant de tout le pays vinrent se produire ici. J'avais réussi mon rêve et tenu ma promesse."; break;
        case 1588: texte = "Durant la guerre contre Ganon, des contrebandiers profitèrent du désordre pour prospérer."; break;
        case 1589: texte = "L'un d'entre eux n'était autre que mon ancien compagnon de cellule, fraîchement sorti de prison, qui me demanda à se servir de l'opéra comme planque."; break;
        case 1590: texte = "Une fois la paix revenue, le roi d'Hyrule voulu mettre fin à la contrebande. Il envoya ses meilleurs hommes traquer les responsables."; break;
        case 1591: texte = "Pris de panique de peur de tout perdre à cause de ma complicité, je demandai à mon ancien compagnon de quitter l'opéra, le menaçant de le livrer au roi s'il refusait."; break;
        case 1592: texte = "Forcés de quitter l'opéra, les bandits m'enfermèrent dans leur ancienne planque ainsi que le personnel, avant d'y mettre le feu."; break;
        case 1593: texte = "C'est ainsi que je suis mort, emportant avec moi cet opéra, qui fut détruit à jamais..."; break;
        case 1594: texte = "Tu connais mon histoire, n'as-tu rien à me présenter ?"; break;
        case 1595: texte = "J'ai attendu des siècles ta venue pour régler cette vieille dette..."; break;
        case 1596: texte = "Faire régler la dette ?**              OUI ?            non  "; break;
        case 1597: texte = "Faire régler la dette ?**              oui              NON ?"; break;
        case 1598: texte = "Ma vie fut courte, mais passionnante. Rien de tout cela n'aurait été possible sans ton intervention."; break;
        case 1599: texte = "Je tenais à te donner ceci : la scie dont je me suis servi pour construire cet opéra!"; break;
        case 1600: texte = "...*C'est une blague ?"; break;
        case 1601: texte = "Tu as troqué la reconnaissance de dette contre une scie."; break;
        case 1602: texte = "Va maintenant, il est temps pour nous de reposer en paix..."; break;
        case 1603: texte = "En tant que barman, je connais toutes les rumeurs..."; break;
        case 1604: texte = "En voilà une : ma couleur préférée serait le jaune...*Mais je t'ai rien dit, ok ?"; break;
        case 1605: texte = "C'est une jolie pierre jaune que tu as là... Tu me l'échanges contre ma meilleure bouteille ?"; break;
        case 1606: texte = "Cette gemme jaune contre une bouteille, ok ?**              OUI ?            non  "; break;
        case 1607: texte = "Cette gemme jaune contre une bouteille, ok ?**              oui              NON ?"; break;
        case 1608: texte = "Ouah! Elle est donc à moi!"; break;
        case 1609: texte = "Tsss... personne ne t'en proposera plus pourtant..."; break;
        case 1610: texte = "Tu as troqué la gemme jaune contre une bouteille de vin."; break;
        case 1611: texte = "Je te sers quelque chose ? Ce sera gratuit pour toi."; break;
        case 1612: texte = "Une mélodie est gravée sur la stèle :"; break;
        case 1613: texte = "Tu as appris le chant de l'envol ! *Joue-le à l'extérieur pour te téléporter!"; break;
        case 1614: texte = "Tu as appris le chant du temps inversé ! *Joue-le à l'extérieur pour remonter le temps!"; break;
        case 1615: texte = "Tu as appris le chant du temps accéléré ! *Joue-le à l'extérieur pour voyager vers le futur!"; break;
        case 1616: texte = "Je suis garde à mi-temps dans cette prison. *En dehors des heures de visite je ne suis pas autorisé à te laisser passer."; break;
        case 1617: texte = "Cette lettre est pour moi ? Elle vient sûrement d'ELLE... Donne-la-moi vite!"; break;
        case 1618: texte = "Donner cette lettre ?**              OUI ?            non  "; break;
        case 1619: texte = "Donner cette lettre ?**              oui              NON ?"; break;
        case 1620: texte = "...*...*..."; break;
        case 1621: texte = "Je dois quitter mon poste... c'est euh... une urgence... T'as l'air d'un bon gars, prends ma place. Ah et garde-moi ça :"; break;
        case 1622: texte = "Ce n'est pas pour moi ?*Tant pis..."; break;
        case 1623: texte = "Tu as troqué la lettre contre une alliance."; break;
        case 1624: texte = "Je dois y aller!"; break;
        case 1625: texte = "Je suis un brave innocent arrivé ici par erreur... T'aurais pas quelque chose pour m'aider à filer d'ici ?"; break;
        case 1626: texte = "Une... petite cuillère hein ?"; break;
        case 1627: texte = "Donner la cuillère ?**              OUI ?            non  "; break;
        case 1628: texte = "Donner la cuillère ?**              oui              NON ?"; break;
        case 1629: texte = "Merci... ... ...*Tiens, voilà un cadeau de remerciement...*Ca appartenait à mon ancien compagnon de cellule..."; break;
        case 1630: texte = "Je sens qu'une magnifique possibilité d'évasion à la petite cuillère vient de s'envoler..."; break;
        case 1631: texte = "Tu as troqué la petite cuillère contre un crâne."; break;
        case 1632: texte = "Bon bah... j'ai du boulot hein..."; break;
        case 1633: texte = "Je ne pensais pas que ma mission pouvait échouer... Les chevaliers hyliens ne sont plus très forts, même leur chef commence à faiblir..."; break;
        case 1634: texte = "L'explosion venait de la pièce de droite."; break;
        case 1635: texte = "Ainsi voilà celui qui a pu arrêter le puissant Ganondorf..."; break;
        case 1636: texte = "Je suis Agahnim, ancien sage, et mentor de Ganondorf. Quant à toi, tu dois être Link..."; break;
        case 1637: texte = "Que cela te plaise ou non, nous allons nous emparer de la Triforce.*Adieu !"; break;
        case 1638: texte = "                   Niveau 1 :                                                                                Temple du Courage"; break;
        case 1639: texte = "                   Niveau 2 :                                                                               Temple de la Sagesse"; break;
        case 1640: texte = "                   Niveau 3 :                                                                                Temple de la Force"; break;
        case 1641: texte = "                   Niveau 4 :                                                                                Ruines des Abysses"; break;
        case 1642: texte = "                   Niveau 5 :                                                                                 Pyramide Fantôme"; break;
        case 1643: texte = "                Grande Pyramide"; break;
        case 1644: texte = "               Temple de la Terre"; break;
        case 1645: texte = "                Temple de l'Air"; break;
        case 1646: texte = "                Temple de l'Eau"; break;
        case 1647: texte = "                 Temple du Feu"; break;
        case 1648: texte = "               Temple des Déesses"; break;
        case 1649: texte = "               Château d'Hyrule"; break;
        case 1650: texte = "                 Niveau Final :                                                                               Château d'Hyrule"; break;
        case 1651: texte = "           Seconde Quête - Niveau 1 :                                                                              Casino"; break;
        case 1652: texte = "           Seconde Quête - Niveau 2 :                                                                         Tour des Gemmes"; break;
        case 1653: texte = "         Seconde Quête - Niveau Final :                                                                      Destination Finale"; break;
        case 1654: texte = "Tu as trouvé la carte !!!**Appuie sur L pour voir le plan du donjon."; break;
        case 1655: texte = "Tu as trouvé la carte !!!**Appuie sur P pour voir le plan du donjon."; break;
        case 1656: texte = "Tu as trouvé la boussole !!!**Les coffres et le boss du donjon sont désormais indiqués sur la carte."; break;
        case 1657: texte = "Tu as trouvé la clé du boss !!!**Sers-t'en pour accéder à son repère."; break;
        case 1658: texte = "Tu as trouvé une petite clé.**Sers-t'en pour déverrouiller une porte."; break;
        case 1659: texte = "Tu as trouvé un nouveau coeur !!!**Ta vie maximale augmente d'un coeur !!!"; break;
        case 1660: texte = "Tu as trouvé un arc !!!**Equipe-le en appuyant sur ¾3 puis sert-en avec ¾1 pour attaquer à distance !"; break;
        case 1661: texte = "Tu as trouvé un arc !!!**Equipe-le en appuyant sur Entrée puis sert-en avec X pour attaquer à distance !"; break;
        case 1662: texte = "Tu as trouvé le Médaillon du Courage !!!"; break;
        case 1663: texte = "Tu as trouvé le Médaillon de la Sagesse !!!"; break;
        case 1664: texte = "Tu as trouvé le Médaillon de la Force !!!"; break;
        case 1665: texte = "Tu as trouvé les Gants de Puissances !!!**Tu peux désormais soulever des rochers !"; break;
        case 1666: texte = "J'abandonne, t'as gagné!*Comment as-tu pu défaire la légendaire technique de l'Ultimate LOL ???"; break;
        case 1667: texte = "Tu ne vas pas me laisser m'en sortir comme ça, hein ?*Le code de la salle suivante est 12086... Maintenant va-t-en."; break;
        case 1668: texte = "J'aurais dû rester dans le gang familial..."; break;
        case 1669: texte = "Tu as trouvé la lanterne !!!**Tu peux désormais faire jaillir des flammes !"; break;
        case 1670: texte = "Tu as trouvé les palmes !!!**Tu peux désormais traverser les étendues d'eau !"; break;
        case 1671: texte = "???*Comment as-tu pu arriver jusqu'ici ? *Mon animal de compagnie était censé monter la garde!"; break;
        case 1672: texte = "...*Tu dis être Link ?*...*Le moment serait-il déjà venu ?"; break;
        case 1673: texte = "Les sbires de Ganon ont fini par découvrir mon existence et ont détruit le village où je vivais. Je suis alors venu dans ce temple pour me cacher."; break;
        case 1674: texte = "Continue ta quête Link, nous nous reverrons dans la grotte du portail!"; break;
        case 1675: texte = "Tu as trouvé une meilleure tunique !!!**Ta défense augmente d'un point !"; break;
        case 1676: texte = "Tu as trouvé la Clé du Temps !!!**Va vite la montrer aux sages !"; break;
        case 1677: texte = "Tu as trouvé le Marteau Magique !!!**Tu peux désormais aplatir les plots te bloquant le chemin !"; break;
        case 1678: texte = "Tu as trouvé les Gants des Titans !!!**Tu peux désormais soulever les pierres les plus lourdes !!!"; break;
        case 1679: texte = "Tu as trouvé une Gemme Jaune !**C'est un trésor inestimable !"; break;
        case 1680: texte = "Tu as trouvé l'Arc des Fées !!!**Tes flèches ont désormais une puissance phénoménale !!!"; break;
        case 1681: texte = "Tu as trouvé une Gemme Verte !**C'est un trésor inestimable !"; break;
        case 1682: texte = "Tu as trouvé la Baguette de Glace !!!**Tu peux désormais geler les ennemis à distance !!!"; break;
        case 1683: texte = "Tu as trouvé une Gemme Bleue !**C'est un trésor inestimable !"; break;
        case 1684: texte = "Tu as trouvé la Baguette de Feu !!!**Tu peux désormais lancer de puissantes boules de feu !!!"; break;
        case 1685: texte = "Tu as trouvé une Gemme Rouge !**C'est un trésor inestimable !"; break;
        case 1686: texte = "Tu as trouvé un bouclier incroyablement résistant !!!*Ta défense augmente d'un point !"; break;
        case 1687: texte = "Te voilà enfin."; break;
        case 1688: texte = "Croyais-tu vraiment pouvoir prendre de vitesse un mage maîtrisant la téléportation ?"; break;
        case 1689: texte = "Je dois tout de même te remercier. *Trouver ce temple relève de l'exploit. Ganondorf et moi-même avons passé des mois sans trouver un seul cristal."; break;
        case 1690: texte = "Et le jour où enfin, nous en pistions un facilement accessible, tu arrives et terrasses le puissant Ganondorf... *Je dois avouer que je ne m'y attendais pas..."; break;
        case 1691: texte = "Toutefois, il semblait évident que nous poursuivions le même objectif, et que tu avais une bonne avance."; break;
        case 1692: texte = "Nous avons alors décidé de te laisser trouver le temple pour nous."; break;
        case 1693: texte = "Tu t'es bien amusé pendant tout ce temps, mais maintenant c'est notre tour."; break;
        case 1694: texte = "Je crois qu'il est grand temps pour toi de disparaître."; break;
        case 1695: texte = "Comment ??? *Tu n'as pas pu vaincre Agahnim ???"; break;
        case 1696: texte = "... *Tout n'est pas perdu, il me reste un espoir..."; break;
        case 1697: texte = "Soit le bienvenu Link. *Nous sommes Din, Nayru et Farore, les Déesses fondatrices d'Hyrule."; break;
        case 1698: texte = "Tes efforts pour sauver Hyrule t'ont finalement mené jusqu'à nous."; break;
        case 1699: texte = "Comme tu l'as peut-être déjà compris, tu ne peux changer le passé. Toutes tes actions n'ont eu pour effet que de mettre en place le présent d'où tu viens."; break;
        case 1700: texte = "Ganondorf est venu dans notre temple pour suivre son mentor, et a finalement utilisé la Triforce pour le ramener à la vie."; break;
        case 1701: texte = "Il a souhaité obtenir le pouvoir de voyager à sa guise entre le monde des vivants et des morts, mais seuls les démons les plus puissants en sont capables."; break;
        case 1702: texte = "Grâce à ses nouveaux pouvoirs, Ganon a pu ramener Agahnim à la vie, mais sa nouvelle nature a pris le dessus sur sa raison."; break;
        case 1703: texte = "Il a transformé Agahnim en zombi à sa solde, s'est proclamé seigneur du malin puis est parti conquérir Hyrule."; break;
        case 1704: texte = "Le chef du village central a organisé la défense d'Hyrule après s'être proclamé roi. *Il fit forger Excalibur et fit travailler ensemble chevaliers et sages."; break;
        case 1705: texte = "Les chevaliers Hyliens furent décimés, mais leur chef, muni d'Excalibur, repoussa Ganon le temps que les sages le scellent à jamais."; break;
        case 1706: texte = "Mais tu connais la suite de l'histoire. Utilisant Agahnim, Ganon élimina les descendants des sages et brisa le seau le retenant prisonnier."; break;
        case 1707: texte = "Armé d'Excalibur, tu repoussas à plusieurs reprises ses assauts, mais le monde des morts ne suffit pas à le retenir."; break;
        case 1708: texte = "Ganon a trouvé la Triforce, mais ce n'est pas le seul trésor que renferme ce temple..."; break;
        case 1709: texte = "La Triforce offrant un pouvoir pratiquement illimité à son détenteur, nous lui avons créé un anti Triforce."; break;
        case 1710: texte = "Il s'agit de 3 armes d'une puissance exceptionnelle. Si deux d'entre elles s'unissent contre le porteur de la Triforce, elles annuleront son voeu."; break;
        case 1711: texte = "L'Epée du Courage te revient de droit. Nous te confions également l'Arc de la Sagesse pour que tu le donnes à la seule personne qui pourra le manier."; break;
        case 1712: texte = "Quant au Trident de la Force, nous l'envoyons au dernier élu."; break;
        case 1713: texte = "Tu obtiens l'Epée du Courage !!! *Cette arme de légende dégage une énorme puissance."; break;
        case 1714: texte = "Tu obtiens l'Arc de la Sagesse !!! *Un pouvoir étrange t'empêche de l'utiliser..."; break;
        case 1715: texte = "Le temps est venu Link, nous te renvoyons à ton époque."; break;
        case 1716: texte = "Link! C'est Zelda! Je te parle par télépathie, t'étais injoignable!"; break;
        case 1717: texte = "Ganon est de retour! Il a attaqué le château! *Les gardes ont été changés en monstres sous son contrôle, soit prudent!"; break;
        case 1718: texte = "La salle du trône est plus au Nord."; break;
        case 1719: texte = "La Princesse n'est pas encore prête à te recevoir."; break;
        case 1720: texte = "Elle m'a cependant chargé de te dire que des objets à ton intention ont été entreposés dans la réserve."; break;
        case 1721: texte = "La Princesse sera bientôt prête à te recevoir."; break;
        case 1722: texte = "Tu as reçu l'autorisation de te rendre à la réserve ? *Très bien, tu peux passer."; break;
        case 1723: texte = "La réserve est plus à l'Est"; break;
        case 1724: texte = "Le château est sous contrôle."; break;
        case 1725: texte = "Tu as trouvé un bouclier !*Ta défense augmente d'un point!"; break;
        case 1726: texte = "Tu as obtenu une bourse pouvant contenir 99 Rubis !"; break;
        case 1727: texte = "La Princesse Zelda t'attend."; break;
        case 1728: texte = "Bonjour Link."; break;
        case 1729: texte = "Euh, Link! *Je suis là!*Ouhou!"; break;
        case 1730: texte = "Une chose horrible s'est produite cette nuit, Link..."; break;
        case 1731: texte = "L'Ocarina du Temps que tu as ramené de Termina... *Je le gardais dans une chambre forte du château, mais il vient d'être volé!"; break;
        case 1732: texte = "J'ai fait placer des gardes dans tout Hyrule, le voleur n'a pas pu aller bien loin..."; break;
        case 1733: texte = "J'aimerai que tu te charges de retrouver l'Ocarina. Commence ton enquête par la chambre forte du sous-sol où il se trouvait, je t'y rejoins."; break;
        case 1734: texte = "Les chambres fortes sont par ici."; break;
        case 1735: texte = "L'accès à cette chambre forte est strictement interdit."; break;
        case 1736: texte = "La Princesse vous a chargé d'enquêter sur le vol de l'Ocarina ? *Dans ce cas vous pouvez entrer, il n'y a de toute façon plus rien à garder ici..."; break;
        case 1737: texte = "Je suis resté à garder cette porte toute la nuit. Je suis certain que personne n'a franchi cette porte..."; break;
        case 1738: texte = "C'est ici qu'était gardé l'Ocarina. Le garde a entendu un grand bruit. Le temps qu'il réalise que cela venait de la chambre forte, le coffre avait été vidé."; break;
        case 1739: texte = "Si tu vois quelque chose de louche, mets-toi devant et appuie sur ¾2 pour me le signaler."; break;
        case 1740: texte = "Si tu vois quelque chose de louche, mets-toi devant et appuie sur ESPACE pour me le signaler."; break;
        case 1741: texte = "C'est une torche... Tu aurais préféré un lustre au plafond ?"; break;
        case 1742: texte = "Ce coffre contenait l'Ocarina du Temps hier soir encore..."; break;
        case 1743: texte = "Cette pièce donnait sur les égouts... *Avant de la changer en chambre forte j'ai fait condamner le passage. Les rideaux cachent que cela a été mal fait..."; break;
        case 1744: texte = "C'est euh... un canard de bain. *Ne me demande pas ce que cela peut bien faire ici..."; break;
        case 1745: texte = "Ces rideaux ont l'air de t'intriguer... *Vérifions s'il n'y a rien derrière..."; break;
        case 1746: texte = "Voilà par où a dû passer le voleur! *Qu'attends-tu ? Pars à sa poursuite!"; break;
        case 1747: texte = "J'ai l'impression qu'on m'a oublié... *Voilà que je garde une chambre forte vide et grande ouverte..."; break;
        case 1748: texte = "Le voleur doit être dans cette forêt, tu ne peux pas abandonner maintenant!"; break;
        case 1749: texte = "TUTORIEL : Appuyez sur ¾3 près d'un objet léger tel qu'un pot pour le soulever. Appuyez une seconde fois pour le lancer."; break;
        case 1750: texte = "TUTORIEL : Appuyez sur ¾2 près d'un coffre pour l'ouvrir. Un coffre ne s'ouvre que par le bas."; break;
        case 1751: texte = "TUTORIEL : Appuyez sur C près d'un objet léger tel qu'un pot pour le soulever. Appuyez une seconde fois pour le lancer."; break;
        case 1752: texte = "TUTORIEL : Appuyez sur Espace près d'un coffre pour l'ouvrir. Un coffre ne s'ouvre que par le bas."; break;
        case 1753: texte = "                Château d'Hyrule"; break;
        case 1754: texte = "Ce passage mène aux cachots, tu n'as rien à y faire."; break;
        case 1755: texte = "Ce passage mène à une zone sous très haute sécurité. Même le héros d'Hyrule n'est pas autorisé à y pénétrer."; break;
        case 1756: texte = "Euh... Comment es-tu arrivé là ?"; break;
        case 1757: texte = "Ces escaliers mènent aux chambres fortes."; break;
        case 1758: texte = "La salle du trône est derrière cette porte."; break;
        case 1759: texte = "La salle du trône s'appelle la salle du trône parce qu'elle ne comporte plus qu'un seul trône..."; break;
        case 1760: texte = "La porte de gauche mène à la salle de bal et aux quartiers VIP, alors que la porte du haut mène à la salle à manger et aux cuisines."; break;
        case 1761: texte = "Autrefois je jouais du piano debout, mais avec les années j'ai décidé de me poser."; break;
        case 1762: texte = "Je suis ici comme musicienne, mais les soirs de bal je préfère lâcher la harpe et aller danser."; break;
        case 1763: texte = "J'ai entendu dire qu'un voleur amateur d'instruments de musique est venu au château durant la nuit."; break;
        case 1764: texte = "Heureusement il n'a pas dû voir mon violon."; break;
        case 1765: texte = "Un petit remontant ?**              OUI ?            non  "; break;
        case 1766: texte = "Un petit remontant ?**              oui              NON ?"; break;
        case 1767: texte = "Cuistot au château, c'est pas une sinécure..."; break;
        case 1768: texte = "On dit que les meilleurs cuistots peuvent lire tout en préparant leurs plats. Pour ma part j'y arrive à moitié."; break;
        case 1769: texte = "Je ne sais jamais quoi préparer, il faut que je me dépêche de trouver une idée!"; break;
        case 1770: texte = "Serveuse au château, c'est plutôt un bon job, tranquille et bien payé."; break;
        case 1771: texte = "L'aile Ouest du château est réservée aux VIPs. Et euh... je n'ai pas eu de consignes à ton sujet... un oubli sans doute."; break;
        case 1772: texte = "L'aile Est du château est réservée aux gardes. Désolé mais tu n'as rien à y faire."; break;
        case 1773: texte = "Cette porte mène à la réserve."; break;
        case 1774: texte = "La bibliothèque est un lieu... plutôt calme."; break;
        case 1775: texte = "Tu as obtenu une source d'énergie!*...*C'est pas si mal..."; break;
        case 1776: texte = "L'accès à la salle du trône n'est accordé qu'aux personnes autorisées."; break;
        case 1777: texte = "L'accès à cette partie du château n'est accordé qu'au personnel de rénovation."; break;
        case 1778: texte = "Tu connais la phrase secrète ?*Je me doutais bien que sous tes airs de lapinet tout gentil se cachait un terrible soldat d'élite de Ganon."; break;
        case 1779: texte = "Tu peux passer."; break;
        case 1780: texte = "Tu as obtenu l'autorisation de t'aventurer dans tout le château ??? *Et bien passe dans ce cas..."; break;
        case 1781: texte = "Tu es venu me libérer ? *Je n'avais pas besoin d'aide..."; break;
        case 1782: texte = "Je voulais m'emparer de ce château par la force... Je suis donc entré pour défier Ganon."; break;
        case 1783: texte = "Le combat fut long et difficile... *Mais les gardes de la salle du trône ont finalement réussi à m'arrêter..."; break;
        case 1784: texte = "Quelle poisse, j'aurai bien voulu rencontrer Ganon..."; break;
        case 1785: texte = "Depuis j'ai entendu dire qu'il y avait une phrase secrète à donner aux gardes pour passer. Il faut leur dire ça :"; break;
        case 1786: texte = "Désolé, mais la princesse n'est pas dans ce château!"; break;
        case 1787: texte = "La prochaine fois j'y arriverai."; break;
        case 1788: texte = "!!!*Mais tu es..."; break;
        case 1789: texte = "Un petit lapin rose ! *J'aime le rose !"; break;
        case 1790: texte = "Fais comme chez toi petit lapin rose, je t'autorise à te promener à ta guise dans ce château."; break;
        case 1791: texte = "Tu m'es vaguement familier... *Enfin peu importe, tu saurais pas où je peux trouver une bonne bière ?"; break;
        case 1792: texte = "C'est une bière que tu as là ?*Je te la pique, j'imagine que t'es là pour ça de toute façon."; break;
        case 1793: texte = "Tiens, t'as qu'à prendre ça comme récompense."; break;
        case 1794: texte = "Tu as troqué la bière contre des clous..."; break;
        case 1795: texte = "Je crois que je t'aime bien, t'es un bon gars. *Tu vas me chercher une autre bière ?"; break;
        case 1796: texte = "Une partition est gravée. Si tu avais un instrument de musique tu pourrais essayer de la jouer."; break;
        case 1797: texte = "Tu as... euh... volé l'ocarina ??? *On va dire que c'est pour la bonne cause..."; break;
        case 1798: texte = "A la seconde où il joua l'air à l'ocarina, Link fut ramené à son époque. Il courut alors au palais pour raconter son histoire à la Princesse..."; break;
        case 1799: texte = "Quelle terrible histoire... *Le Royaume d'Hyrule est-il vraiment destiné à tomber aux mains de Ganon ?"; break;
        case 1800: texte = "Que pouvons-nous faire ? *Si seulement Ganon n'avait jamais trouvé la Triforce..."; break;
        case 1801: texte = "L'Ocarina transporta Link une fois de plus. Le héros d'Hyrule se retrouva alors dans une vaste plaine enneigée..."; break;
        case 1802: texte = "Ce miroir est pour moi ?**              OUI ?            non  "; break;
        case 1803: texte = "Ce miroir est pour moi ?**              oui              NON ?"; break;
        case 1804: texte = "... Tu m'offres un miroir ??? Tu me prends donc pour ce genre de filles qui passent leur temps à se regarder ???"; break;
        case 1805: texte = "Bon prends quand même ça en remerciement."; break;
        case 1806: texte = "...*Va-t-en vite si tu ne veux pas finir au cachot."; break;
        case 1807: texte = "Tu as troqué le miroir contre une petite cuillère !"; break;
        case 1808: texte = "Tu es dans une zone sous haute sécurité, je vais te demander de partir."; break;
        case 1809: texte = "Tu as trouvé une tunique extrêmement résistante!!!*Ta défense augmente d'un point !"; break;
        case 1810: texte = "Contente de te voir enfin Link!"; break;
        case 1811: texte = "Tu dis que cet arc est pour moi et qu'il peut vaincre Ganon ?*Cool!"; break;
        case 1812: texte = "Tu as remis l'Arc de la Sagesse à la Princesse Zelda."; break;
        case 1813: texte = "Ne t'en fais pas pour moi, je devrais pouvoir me débrouiller désormais."; break;
        case 1814: texte = "Nous devons affronter Ganon, pars devant je te rejoins.*Je dois me repoudrer le nez avant."; break;
        case 1815: texte = "!!! *Ganon a repris forme humaine! *Ce n'est plus un démon il ne pourra plus revenir à la vie, nous avons gagné!"; break;
        case 1816: texte = "???"; break;
        case 1817: texte = "Te voilà enfin Link. *Cette fois la victoire sera mienne, j'ai amélioré mes techniques spécialement pour te vaincre."; break;
        case 1818: texte = "Nous revoilà face à face Link. *J'ai l'impression de sortir d'un long cauchemar..."; break;
        case 1819: texte = "Agahnim avait tort, la Triforce n'aurait jamais dû être trouvée."; break;
        case 1820: texte = "Ecoute-moi bien Link, il y a désormais bien longtemps, Agahnim disparut après avoir quitté l'ordre de sages."; break;
        case 1821: texte = "Le jour où il reparut, il était doté de sombres pouvoirs. En tant que sage, il n'aurait jamais été capable de lancer des boules de feu, sa spécialité c'était les lapins..."; break;
        case 1822: texte = "Je devais trop à Agahnim pour m'opposer à lui, cependant j'ai mené mon enquête tandis que nous cherchions les cristaux magiques."; break;
        case 1823: texte = "Il semblerait qu'il ait obtenu ses pouvoirs d'une entité beaucoup plus dangereuse et puissante que je n'ai jamais pu l'être."; break;
        case 1824: texte = "Il reste en Hyrule des lieux que tu n'as pas explorés et des ennemis que tu n'as pas vaincus. Ta quête n'est peut-être pas encore finie..."; break;
        case 1825: texte = "Tu veux savoir pourquoi je te dis tout ça ? *J'imagine que je ne vais pas pouvoir m'en sortir si facilement après tout ce que j'ai fait..."; break;
        case 1826: texte = "Si j'échoue aujourd'hui, quelqu'un devra venger Agahnim à ma place. *Mais..."; break;
        case 1827: texte = "... en seras-tu capable ?"; break;
        case 1828: texte = "Tu as trouvé la Triforce !!!"; break;
        case 1829: texte = "C'est ainsi que Ganon fut vaincu à jamais. La Triforce fut une nouvelle fois récupérée puis gardée à l'abri au palais. **Cependant, inquiété par les dernières paroles de Ganondorf, Link passa le restant de ses jours à veiller sur Hyrule. ***Fin de la première quête."; break;
        case 1830: texte = "Ganon a repris forme humaine... *est-il toujours notre ennemi ?"; break;
        case 1831: texte = "Prêt pour un dernier duel ?"; break;
        case 1832: texte = "Bienvenue au Casino !"; break;
        case 1833: texte = "Bienvenue cher visiteur, les droits d'entrées sont de 10 Ganon d'or, ça te va ?*              OUI ?            non  "; break;
        case 1834: texte = "Bienvenue cher visiteur, les droits d'entrées sont de 10 Ganon d'or, ça te va ?*              oui              NON ?"; break;
        case 1835: texte = "Tant pis."; break;
        case 1836: texte = "Bienvenue au Casino !"; break;
        case 1837: texte = "Reviens quand tu auras de l'argent l'ami."; break;
        case 1838: texte = "Nous sommes fermés pour le moment, reviens plus tard."; break;
        case 1839: texte = "Bienvenue au casino familial, veux-tu que je t'explique les règles du jeu pour 5 Ganon d'or?              OUI ?            non  "; break;
        case 1840: texte = "Bienvenue au casino familial, veux-tu que je t'explique les règles du jeu pour 5 Ganon d'or?              oui              NON ?"; break;
        case 1841: texte = "Dans ce casino, les ennemis ne t'enlèvent pas de coeurs mais de l'argent. Chaque attaque te fait perdre un peu plus que la précédente."; break;
        case 1842: texte = "Si tu n'as plus d'argent, tu es mis à la porte. Les clients fauchés ne nous intéressent pas."; break;
        case 1843: texte = "Cependant, en remportant les différents jeux proposés, tu pourras gagner des prix de grandes valeurs."; break;
        case 1844: texte = "Frappe les ennemis pour les arrêter sur un signe. Obtient les 4 signes différents et tu gagneras un prix."; break;
        case 1845: texte = "Veux-tu essayer pour 10 Ganon d'or ?**              OUI ?            non  "; break;
        case 1846: texte = "Veux-tu essayer pour 10 Ganon d'or ?**              oui              NON ?"; break;
        case 1847: texte = "Tu as déjà remporté ce jeu."; break;
        case 1848: texte = "Félicitation !*Voici ton prix :"; break;
        case 1849: texte = "Tu auras sans doute plus de chance la prochaine fois."; break;
        case 1850: texte = "Frappe les ennemis pour les arrêter sur un chiffre. Obtiens un 4, un 2 et un 1 et tu gagneras un prix."; break;
        case 1851: texte = "Parle-moi si tu échoues, tu pourras recommencer en conservant les bons chiffres obtenus."; break;
        case 1852: texte = "Veux-tu compléter pour 5 Ganon d'or ?**              OUI ?            non  "; break;
        case 1853: texte = "Veux-tu compléter pour 5 Ganon d'or ?**              oui              NON ?"; break;
        case 1854: texte = "C'est la ligne de départ de la grande course du Casino, tu as 21 secondes pour atteindre l'arrivée."; break;
        case 1855: texte = "Tu perds du temps là, tu sais ?"; break;
        case 1856: texte = "C'est la ligne d'arrivée de la grande course du Casino. Va à la ligne de départ si tu veux essayer de battre le record."; break;
        case 1857: texte = "Frappe les ennemis pour les arrêter sur un chiffre et fait plus que moi avec un dé en moins."; break;
        case 1858: texte = "Choisis un chiffre, soit 1, soit 6. Je vais lancer 4 dés, si ton chiffre y est c'est gagné, sinon tu paies 10 fois la différence avec le dé le plus proche."; break;
        case 1859: texte = "Veux-tu essayer ?**              OUI ?            non  "; break;
        case 1860: texte = "Veux-tu essayer ?**              oui              NON ?"; break;
        case 1861: texte = "Quel est ton chiffre ?**              UN  ?            six  "; break;
        case 1862: texte = "Quel est ton chiffre ?**              un               SIX ?"; break;
        case 1863: texte = "Frappe les ennemis pour les arrêter sur un chiffre qui sera transmis à une caisse de droite. Puis pousse les caisses pour qu'elles arrivent à 0 sur les dalles."; break;
        case 1864: texte = "Je te vends une clé pour un prix égal à la somme de tes 4 dés fois le montant du miens."; break;
        case 1865: texte = "Je te vends une petite clé pour "; break;
        case 1866: texte = " Ganon d'or, ça te va ?*              OUI ?            non  "; break;
        case 1867: texte = "Je te vends une petite clé pour "; break;
        case 1868: texte = " Ganon d'or, ça te va ?*              oui              NON ?"; break;
        case 1869: texte = "La salle du coffre est au bout du couloir à gauche. Seuls les meilleurs clients peuvent espérer l'atteindre."; break;
        case 1870: texte = "Tu as ouvert le coffre ?*Tu devrais tenter la salle spéciale désormais."; break;
        case 1871: texte = "Les gens comme toi n'ont rien à faire dans un casino...*Nous sommes ruinés..."; break;
        case 1872: texte = "Bienvenue au Grand Quiz du Casino !"; break;
        case 1873: texte = "Ici c'est moi qui pose les questions, et les mauvaises réponses coûtent chère."; break;
        case 1874: texte = "Je ne te demande pas si tu veux jouer, je suis tout de même un boss.*Alors commençons..."; break;
        case 1875: texte = "Question suivante..."; break;
        case 1876: texte = "Ce Casino contenait un total de 6 jeux différents sans compter ce quiz, est-ce vrai ?              VRAI ?            faux  "; break;
        case 1877: texte = "Ce Casino contenait un total de 6 jeux différents sans compter ce quiz, est-ce vrai ?              vrai              FAUX ?"; break;
        case 1878: texte = "Correct! Il y avait 7 jeux, 1 pour la carte, 1 pour la boussole et 5 pour des clés."; break;
        case 1879: texte = "Non! Il y avait 7 jeux, 1 pour la carte, 1 pour la boussole et 5 pour des clés."; break;
        case 1880: texte = "Le gars de la maison du café ne boit jamais plus de 16 tasses de café par jour, vrai ?*             VRAI ?            faux  "; break;
        case 1881: texte = "Le gars de la maison du café ne boit jamais plus de 16 tasses de café par jour, vrai ?*             vrai              FAUX ?"; break;
        case 1882: texte = "Correct! Il peut atteindre les 17 tasses!"; break;
        case 1883: texte = "Non! Il peut atteindre les 17 tasses!"; break;
        case 1884: texte = "Ce jeu contient un total de 150 gemmes de forces, vrai ?*             VRAI ?            faux  "; break;
        case 1885: texte = "Ce jeu contient un total de 150 gemmes de forces, vrai ?*             vrai              FAUX ?"; break;
        case 1886: texte = "Correct! Il y en a 200."; break;
        case 1887: texte = "Non! Il y en a 200."; break;
        case 1888: texte = "Le village central ne contient plus que 7 maisons, est-ce vrai ?*             VRAI ?            faux  "; break;
        case 1889: texte = "Le village central ne contient plus que 7 maisons, est-ce vrai ?*             vrai              FAUX ?"; break;
        case 1890: texte = "Correct! Les 3 autres sont détruites."; break;
        case 1891: texte = "Non! Il y a 10 maisons dont 3 détruites, soit plus que 7."; break;
        case 1892: texte = "Tu es mort "; break;
        case 1893: texte = " fois, est-ce vrai ?**             VRAI ?            faux  "; break;
        case 1894: texte = "Tu es mort "; break;
        case 1895: texte = " fois, est-ce vrai ?**             vrai              FAUX ?"; break;
        case 1896: texte = "Correct! Tu es mort "; break;
        case 1897: texte = " fois."; break;
        case 1898: texte = "Non! Tu es mort "; break;
        case 1899: texte = " fois."; break;
        case 1900: texte = "14 mauvaises réponses suffisent obligatoirement à faire perdre n'importe quel joueur, vrai ?*             VRAI ?            faux  "; break;
        case 1901: texte = "14 mauvaises réponses suffisent obligatoirement à faire perdre n'importe quel joueur, vrai ?*             vrai              FAUX ?"; break;
        case 1902: texte = "Correct! 14 mauvaises réponses font perdre au minimum 1050 Ganon d'or sur les 999 transportables."; break;
        case 1903: texte = "Non! 14 mauvaises réponses font perdre au minimum 1050 Ganon d'or sur les 999 transportables."; break;
        case 1904: texte = "Je suis le boss le plus cool du jeu, vrai ?**             VRAI ?            faux  "; break;
        case 1905: texte = "Je suis le boss le plus cool du jeu, vrai ?**             vrai              FAUX ?"; break;
        case 1906: texte = "Hé! Hé! On est d'accord."; break;
        case 1907: texte = "... *Je vais te la compter fausse pour le principe..."; break;
        case 1908: texte = "Seuls 3 donjons du passé sont obligatoires pour finir le jeu, vrai ? *             VRAI ?            faux  "; break;
        case 1909: texte = "Seuls 3 donjons du passé sont obligatoires pour finir le jeu, vrai ? *             vrai              FAUX ?"; break;
        case 1910: texte = "Correct! Le temple de l'air, le temple du feu et celui des déesses."; break;
        case 1911: texte = "Non! Il n'y en a bien que 3, Le temple de l'air, le temple du feu et celui des Déesses."; break;
        case 1912: texte = "Plus de 4000 Ganon d'or sont nécessaires pour obtenir tous les prix de la grosse fée, vrai ?              VRAI ?            faux  "; break;
        case 1913: texte = "Plus de 4000 Ganon d'or sont nécessaires pour obtenir tous les prix de la grosse fée, vrai ?              vrai              FAUX ?"; break;
        case 1914: texte = "Correct! Il n'en faut que 3798."; break;
        case 1915: texte = "Non! 3798 suffisent."; break;
        case 1916: texte = "Du temps de Zelda, le palais contenait 80 piliers, vrai ?*             VRAI ?            faux  "; break;
        case 1917: texte = "Du temps de Zelda, le palais contenait 80 piliers, vrai ?*             vrai              FAUX ?"; break;
        case 1918: texte = "Correct! Il y en avait bien 80."; break;
        case 1919: texte = "Non! Il y en avait bien 80."; break;
        case 1920: texte = "Tu as déjà répondu à "; break;
        case 1921: texte = " de mes questions, est-ce vrai ?*             VRAI ?            faux  "; break;
        case 1922: texte = "Tu as déjà répondu à "; break;
        case 1923: texte = " de mes questions, est-ce vrai ?*             vrai              FAUX ?"; break;
        case 1924: texte = "Correct! Mais maintenant oui."; break;
        case 1925: texte = "Non! Mais maintenant oui."; break;
        case 1926: texte = "Tu peux trouver un maximum de 16 quarts de coeurs dans ce jeu, vrai ?*             VRAI ?            faux  "; break;
        case 1927: texte = "Tu peux trouver un maximum de 16 quarts de coeurs dans ce jeu, vrai ?*             vrai              FAUX ?"; break;
        case 1928: texte = "Correct! Il y en a 16 en tout."; break;
        case 1929: texte = "Non! Il y en a 16 en tout."; break;
        case 1930: texte = "Une potion bleue coûte l'équivalent de 40 Rubis plus 40 Ganon d'or plus 10 pièces d'or, vrai ?*             VRAI ?            faux  "; break;
        case 1931: texte = "Une potion bleue coûte l'équivalent de 40 Rubis plus 40 Ganon d'or plus 10 pièces d'or, vrai ?*             vrai              FAUX ?"; break;
        case 1932: texte = "Correct! Soit 160 Rubis."; break;
        case 1933: texte = "Non! Cela donne 160 Rubis, soit le prix d'une potion bleue."; break;
        case 1934: texte = "Dans la mine, les rails du wagonnet pouvaient se changer à l'aide de 3 leviers, vrai ?*             VRAI ?            faux  "; break;
        case 1935: texte = "Dans la mine, les rails du wagonnet pouvaient se changer à l'aide de 3 leviers, vrai ?*             vrai              FAUX ?"; break;
        case 1936: texte = "Correct! Il n'y en avait que 2."; break;
        case 1937: texte = "Non! Il n'y en avait que 2."; break;
        case 1938: texte = "Il fallait trouver 3 poissons différents pour gagner le concours de pêche, vrai ?*             VRAI ?            faux  "; break;
        case 1939: texte = "Il fallait trouver 3 poissons différents pour gagner le concours de pêche, vrai ?*             vrai              FAUX ?"; break;
        case 1940: texte = "Correct! Il en fallait 5."; break;
        case 1941: texte = "Non! Il en fallait 5."; break;
        case 1942: texte = "Seule Excalibur permet de renvoyer les projectiles, vrai ?*             VRAI ?            faux  "; break;
        case 1943: texte = "Seule Excalibur permet de renvoyer les projectiles, vrai ?*             vrai              FAUX ?"; break;
        case 1944: texte = "Correct! Ton épée actuelle en est également capable."; break;
        case 1945: texte = "Non! Ton épée actuelle en est également capable."; break;
        case 1946: texte = "Zelda est plus grande que toi, est-ce vrai ?**             VRAI ?            faux  "; break;
        case 1947: texte = "Zelda est plus grande que toi, est-ce vrai ?**             vrai              FAUX ?"; break;
        case 1948: texte = "Correct! Tu fais un pixel de plus."; break;
        case 1949: texte = "Non! Tu fais un pixel de plus."; break;
        case 1950: texte = "Le donjon 3 contient 3 étages, est-ce vrai ?**             VRAI ?            faux  "; break;
        case 1951: texte = "Le donjon 3 contient 3 étages, est-ce vrai ?**             vrai              FAUX ?"; break;
        case 1952: texte = "Correct! Dont un juste pour le boss."; break;
        case 1953: texte = "Non! 2 étages plus 1 pour le boss, donc 3."; break;
        case 1954: texte = "L'incarnation démoniaque de Link est un lapin rose, vrai ?*             VRAI ?            faux  "; break;
        case 1955: texte = "L'incarnation démoniaque de Link est un lapin rose, vrai ?*             vrai              FAUX ?"; break;
        case 1956: texte = "Correct! C'est Oni Link."; break;
        case 1957: texte = "Non! C'est Oni Link."; break;
        case 1958: texte = "Tingle n'aurait jamais dû exister, vrai ?**             VRAI ?            faux  "; break;
        case 1959: texte = "Tingle n'aurait jamais dû exister, vrai ?**             vrai              FAUX ?"; break;
        case 1960: texte = "Euh... on s'égare là, mais je vais te la compter juste."; break;
        case 1961: texte = "... *Pour moi si."; break;
        case 1962: texte = "Tu veux me donner des Ganon d'or, vrai ?**             VRAI ?            faux  "; break;
        case 1963: texte = "Tu veux me donner des Ganon d'or, vrai ?**             vrai              FAUX ?"; break;
        case 1964: texte = "Correct! Hélas..."; break;
        case 1965: texte = "Merci!"; break;
        case 1966: texte = "Les morsures de serpent laissent un demi-coeur peu importe la vie et la défense que tu avais, est-ce vrai ?*             VRAI ?            faux  "; break;
        case 1967: texte = "Les morsures de serpent laissent un demi-coeur peu importe la vie et la défense que tu avais, est-ce vrai ?*             vrai              FAUX ?"; break;
        case 1968: texte = "Correct! Si tu n'as plus qu'un demi-coeur la morsure ne t'en laisse aucun."; break;
        case 1969: texte = "Non! Si tu n'as plus qu'un demi-coeur la morsure ne t'en laisse aucun."; break;
        case 1970: texte = "Le domaine de Link contient 77 touffes d'herbes, est-ce vrai ?*             VRAI ?            faux  "; break;
        case 1971: texte = "Le domaine de Link contient 77 touffes d'herbes, est-ce vrai ?*             vrai              FAUX ?"; break;
        case 1972: texte = "Correct! Ravi de constater que je ne suis pas le seul à avoir compté!"; break;
        case 1973: texte = "Non! Tu te rends compte que je connais mieux ton domaine que toi ???"; break;
        case 1974: texte = "2 à la puissance 12 est plus petit que la racine cubique de 7, est-ce vrai ?*             VRAI ?            faux  "; break;
        case 1975: texte = "2 à la puissance 12 est plus petit que la racine cubique de 7, est-ce vrai ?*             vrai              FAUX ?"; break;
        case 1976: texte = "Correct! Enfin je crois."; break;
        case 1977: texte = "Non! Ca doit être l'inverse je crois."; break;
        case 1978: texte = "Il est possible de finir le jeu en se déplaçant uniquement en moonwalk, est-ce vrai ?*             VRAI ?            faux  "; break;
        case 1979: texte = "Il est possible de finir le jeu en se déplaçant uniquement en moonwalk, est-ce vrai ?*             vrai              FAUX ?"; break;
        case 1980: texte = "Correct! Enfin ça ne t'empêche pas d'essayer."; break;
        case 1981: texte = "Non! Enfin tu peux toujours essayer..."; break;
        case 1982: texte = "C'est dans le passé que tu peux gagner le plus d'argent en battant un ennemi, vrai ?*             VRAI ?            faux  "; break;
        case 1983: texte = "C'est dans le passé que tu peux gagner le plus d'argent en battant un ennemi, vrai ?*             vrai              FAUX ?"; break;
        case 1984: texte = "Correct! C'est dans le présent avec les Rubis rouges."; break;
        case 1985: texte = "Non! C'est dans le présent avec les Rubis rouges."; break;
        case 1986: texte = "Ton épée peut vaincre n'importe quel ennemi hors boss en moins de 6 coups, vrai ?*             VRAI ?            faux  "; break;
        case 1987: texte = "Ton épée peut vaincre n'importe quel ennemi hors boss en moins de 6 coups, vrai ?*             vrai              FAUX ?"; break;
        case 1988: texte = "Correct! Certains ennemis ne craignent pas les coups d'épée."; break;
        case 1989: texte = "Non! Certains ennemis ne craignent pas les coups d'épée."; break;
        case 1990: texte = "L'énigme du désert comptait 6 pierres, vrai ?**             VRAI ?            faux  "; break;
        case 1991: texte = "L'énigme du désert comptait 6 pierres, vrai ?**             vrai              FAUX ?"; break;
        case 1992: texte = "Correct! Par contre je n'ai jamais trouvé l'ordre..."; break;
        case 1993: texte = "Non! T'as sans doute triché pour la résoudre..."; break;
        case 1994: texte = "Tu en es à plus de "; break;
        case 1995: texte = " heures de jeu, vrai ?**             VRAI ?            faux  "; break;
        case 1996: texte = "Tu en es à plus de "; break;
        case 1997: texte = " heures de jeu, vrai ?**             vrai              FAUX ?"; break;
        case 1998: texte = "Correct! Ca passe vite hein ?"; break;
        case 1999: texte = "Non! Ca passe vite hein ?"; break;
        case 2000: texte = "Les poules du passé sont plus patientes que celles du présent, vrai ?*             VRAI ?            faux  "; break;
        case 2001: texte = "Les poules du passé sont plus patientes que celles du présent, vrai ?*             vrai              FAUX ?"; break;
        case 2002: texte = "Correct! Je vois que tu es connaisseur."; break;
        case 2003: texte = "Non! T'auras qu'à vérifier..."; break;
        case 2004: texte = "Il était possible de pêcher 4 poissons différents au Lac Hylia, vrai ?*             VRAI ?            faux  "; break;
        case 2005: texte = "Il était possible de pêcher 4 poissons différents au Lac Hylia, vrai ?*             vrai              FAUX ?"; break;
        case 2006: texte = "Correct! Il y en avait 6 espèces différentes."; break;
        case 2007: texte = "Non! Il y en avait 6 espèces différentes, il était donc possible d'en trouver 4."; break;
        case 2008: texte = "Le Père Noël existe, est-ce vrai ?**             VRAI ?            faux  "; break;
        case 2009: texte = "Le Père Noël existe, est-ce vrai ?**             vrai              FAUX ?"; break;
        case 2010: texte = "Correct! Tu l'as d'ailleurs déjà rencontré."; break;
        case 2011: texte = "Non! Tu l'as d'ailleurs déjà rencontré."; break;
        case 2012: texte = "Les montagnes du passé contenaient 16 pierres, vrai ?*             VRAI ?            faux  "; break;
        case 2013: texte = "Les montagnes du passé contenaient 16 pierres, vrai ?*             vrai              FAUX ?"; break;
        case 2014: texte = "Correct! Il n'y en avait que 15 bien sûr."; break;
        case 2015: texte = "Non! Il n'y en avait que 15 bien sûr."; break;
        case 2016: texte = "Ce Casino contient un total de 42 tapis, vrai ? *             VRAI ?            faux  "; break;
        case 2017: texte = "Ce Casino contient un total de 42 tapis, vrai ? *             vrai              FAUX ?"; break;
        case 2018: texte = "Correct! Il y en a 44."; break;
        case 2019: texte = "Non! Il y en a 44."; break;
        case 2020: texte = "Les Gemmes de Force peuvent se troquer contre 5 sortes d'objets différentes, vrai ?*             VRAI ?            faux  "; break;
        case 2021: texte = "Les Gemmes de Force peuvent se troquer contre 5 sortes d'objets différentes, vrai ?*             vrai              FAUX ?"; break;
        case 2022: texte = "Correct! Je vois que tu n'as pas oublié le roc givre."; break;
        case 2023: texte = "Non! Tu as dû oublier le roc givre dans tes comptes."; break;
        case 2024: texte = "La tunique verte ne donne qu'un point de défense, est-ce vrai ?*             VRAI ?            faux  "; break;
        case 2025: texte = "La tunique verte ne donne qu'un point de défense, est-ce vrai ?*             vrai              FAUX ?"; break;
        case 2026: texte = "Correct! La tunique verte est celle de base et ne donne aucun point de défense."; break;
        case 2027: texte = "Non! La tunique verte est celle de base et ne donne aucun point de défense."; break;
        case 2028: texte = "La chambre de Zelda contenait 5 miroirs, est-ce vrai ?*             VRAI ?            faux  "; break;
        case 2029: texte = "La chambre de Zelda contenait 5 miroirs, est-ce vrai ?*             vrai              FAUX ?"; break;
        case 2030: texte = "Correct! Le cinquième lui vient d'ailleurs de toi."; break;
        case 2031: texte = "Non! Le cinquième lui vient d'ailleurs de toi."; break;
        case 2032: texte = "La Pyramide du passé contenait 85 salles, est-ce vrai ?*             VRAI ?            faux  "; break;
        case 2033: texte = "La Pyramide du passé contenait 85 salles, est-ce vrai ?*             vrai              FAUX ?"; break;
        case 2034: texte = "Correct! 84 seulement."; break;
        case 2035: texte = "Non! 84 seulement."; break;
        case 2036: texte = "Les flèches de feu sont plus fortes que celles de glace, est-ce vrai ?*             VRAI ?            faux  "; break;
        case 2037: texte = "Les flèches de feu sont plus fortes que celles de glace, est-ce vrai ?*             vrai              FAUX ?"; break;
        case 2038: texte = "Correct! Les flèches de feu ont une force de 10, celles de glace 7."; break;
        case 2039: texte = "Non! Les flèches de feu ont une force de 10, celles de glace 7."; break;
        case 2040: texte = "Les bombes causent autant de dégâts que les coups de marteau, est-ce vrai ?*             VRAI ?            faux  "; break;
        case 2041: texte = "Les bombes causent autant de dégâts que les coups de marteau, est-ce vrai ?*             vrai              FAUX ?"; break;
        case 2042: texte = "Correct! Les bombes ont une force de 5, le marteau 3."; break;
        case 2043: texte = "Non! Les bombes ont une force de 5, le marteau 3."; break;
        case 2044: texte = "Quoi ??? Tu m'as vaincu ???**             VRAI ?            vrai  "; break;
        case 2045: texte = "Quoi ??? Tu m'as vaincu ???**             vrai              VRAI ?"; break;
        case 2046: texte = "Tu as trouvé le bouclier des Déesses !!!*Ta vie remonte désormais en permanence !!!"; break;
        case 2047: texte = "Sur cette pierre est écrite l'histoire d'Hyrule en hylien ancien :"; break;
        case 2048: texte = "Après que les Déesses Din, Nayru et Farore eurent créé Hyrule, une entité maléfique d'un pouvoir inégalé arriva pour occuper cette terre."; break;
        case 2049: texte = "Malgré leurs grands pouvoirs, les Déesses durent admettre qu'elles ne pourraient pas détruire ce mal."; break;
        case 2050: texte = "...*La suite de l'histoire n'est pas écrite ici. Peut-être sur une autre stèle ?"; break;
        case 2051: texte = "Tu as trouvé la tunique des Déesses !!!*Ta magie remonte désormais en permanence !!!"; break;
        case 2052: texte = "Sur cette pierre est écrite l'histoire d'Hyrule en hylien ancien :"; break;
        case 2053: texte = "Din, Nayru et Farore ne purent se résoudre à ne rien faire, et défièrent l'entité démoniaque."; break;
        case 2054: texte = "Après un long combat perdu d'avance, elles durent accepter un compromis et réussirent à disperser le pouvoir de l'entité."; break;
        case 2055: texte = "Pour ce faire, elles durent cependant créer des créatures démoniaques contenant les parcelles du pouvoir de l'entité."; break;
        case 2056: texte = "Ce qui restait de l'entité maléfique fut emprisonné dans une forme humaine, et ne pourra s'en libérer tant que tous les types de monstres n'auront pas été vaincus."; break;
        case 2057: texte = "Bienvenue dans ces lieux, souhaites-tu que je t'explique comment fonctionne cet endroit ?*              OUI ?            non  "; break;
        case 2058: texte = "Bienvenue dans ces lieux, souhaites-tu que je t'explique comment fonctionne cet endroit ?*              oui              NON ?"; break;
        case 2059: texte = "Les ennemis de ce donjon sont très particuliers, chacune de leurs attaques te fera perdre 2 fois plus de vie que le coup précédent."; break;
        case 2060: texte = "Soit donc extrêmement prudent, 7 coups suffiront à t'achever."; break;
        case 2061: texte = "De plus, le nombre d'ennemis que tu as vaincus, ainsi que le nombre de type d'ennemis vaincus sont comptabilisés. Un certain montant sera nécessaire pour ouvrir certaines portes."; break;
        case 2062: texte = "Bonne chance Link, quoi qu'il advienne tout finit ici."; break;
        case 2063: texte = "Elimine au moins 30 ennemis de 4 types différents et je t'ouvrirais cette porte."; break;
        case 2064: texte = "Bonne chance Link."; break;
        case 2065: texte = "Tu as vaincu suffisamment d'ennemis, je t'ouvre..."; break;
        case 2066: texte = "Elimine au moins 60 ennemis de 10 types différents et je t'ouvrirais cette porte."; break;
        case 2067: texte = "Elimine au moins 20 ennemis de 3 types différents et je t'ouvrirais cette porte."; break;
        case 2068: texte = "Elimine au moins 99 ennemis de 12 types différents et je t'ouvrirais cette porte."; break;
        case 2069: texte = "Elimine au moins 30 ennemis de 12 types différents et je t'ouvrirais cette porte."; break;
        case 2070: texte = "Elimine au moins 40 ennemis de 6 types différents et je t'ouvrirais cette porte."; break;
        case 2071: texte = "Elimine au moins 50 ennemis de 7 types différents et je t'ouvrirais cette porte."; break;
        case 2072: texte = "Tu as trouvé le masque d'Oni Link !!! *Maintiens R puis appuie sur L pour te transformer et devenir incroyablement puissant."; break;
        case 2073: texte = "Tu as trouvé le masque d'Oni Link !!! *Utilise 'O' pour te transformer et devenir incroyablement puissant."; break;
        case 2074: texte = "Félicitations Link! Tu as battu chaque type d'ennemi... C'est incroyable..."; break;
        case 2075: texte = "Je te dois énormément, veux-tu être payé maintenant ?"; break;
        case 2076: texte = "Je vais enfin pouvoir reprendre ma vraie forme, prépare-toi à prendre cher!*Adieu, Héros d'Hyrule!"; break;
        case 2077: texte = "Vite Link! Utilise l'Epée des Déesses pour l'achever définitivement!"; break;
        case 2078: texte = "Pas sur moi andouille..."; break;
        case 2079: texte = "Félicitations Link, rentrons maintenant."; break;
        case 2080: texte = "Justice est faite. Mon maître est enfin vengé."; break;
        case 2081: texte = "Ecarte-toi!"; break;
        case 2082: texte = "Mais qu'est-ce que tu fabriques ?"; break;
        case 2083: texte = "Laisse-moi t'expliquer la raison de notre présence dans le sombre donjon de l'entité sans nom."; break;
        case 2084: texte = "Après ton départ du château qui a suivi ma victoire sur Ganon, Ganondorf m'a remis la Triforce et m'a raconté son histoire."; break;
        case 2085: texte = "Nous sommes rapidement arrivés à la conclusion que l'homme de l'encyclopédie des monstres était hautement louche, alors quand nous avons appris d'un garde que tu étais allé le voir, nous décidâmes de te venir en aide."; break;
        case 2086: texte = "Comme nous le pensions, seule la puissance combinée des 3 Armes des Déesses maniées par les 3 Elus pouvait détruire à jamais ce fléau."; break;
        case 2087: texte = "Quant à Ganondorf, il n'a plus rien à voir avec le monstre que nous connaissions, il n'y a désormais plus de ténèbres en lui et il est digne de confiance."; break;
        case 2088: texte = "Désormais Hyrule est en paix, pour de bon. Les monstres ne réapparaîtront plus, le mal est définitivement vaincu."; break;
        case 2089: texte = "Alors dis-moi Link, que vas-tu faire de tes vacances ?"; break;
        case 2090: texte = "Hyrule était sauvé et toute menace écartée. Après de longues aventures, les trois héros accomplirent leur destinée. **Les trois Déesses revinrent en Hyrule les féliciter, puis repartirent, emportant avec elles la Triforce. **Le puissant Ganondorf devint rapidement chef de la garde et passa le restant de ses jours à protéger le pays contre des ennemis qui ne vinrent jamais."; break;
        case 2091: texte = "La princesse Zelda fut célébrée à travers tout le pays et bien plus loin encore comme étant la souveraine ayant apporté la paix sur le monde. **Quant à Link, préférant fuir la célébrité, il disparut après cette ultime victoire, et nul ne le revit en Hyrule."; break;
        case 2092: texte = "Après les évènements survenus à Termina, la princesse Zelda mit fin à l'exil de Link, annonçant alors au peuple sa victoire sur son alter égo maléfique."; break;
        case 2093: texte = "Mais le chevalier hylien, peinant à assumer son statut de héros, partit vivre en ermite au fond d'une forêt que lui offrit la princesse."; break;
        case 2094: texte = "L'existence de Termina devant rester secrète, la princesse tut les évènements qui s'y étaient déroulés et laissa vivre le peuple ignorant dans une paix illusoire."; break;
        case 2095: texte = "Mais tous deux savaient hélas que, du fond de l'enfer, l'immortel Ganon, tirant son incroyable puissance du voeu"; break;
        case 2096: texte = "originel à la Triforce, rassemblait son armée en vue de son prochain assaut."; break;
        case 2097: texte = "Jusqu'au jour où, après des mois passés à guetter une attaque, un évènement troublant vint mettre fin à cette interminable attente..."; break;
        case 2098: texte = "HO HE !!! *MESSIRE LINK !!!"; break;
        case 2099: texte = "AIDE : Appuie sur Select pour consulter l'aide."; break;
        case 2100: texte = "AIDE : Appuie sur F1 pour consulter l'aide."; break;
        case 2101: texte = "Reviens me voir quand tu auras une bourse et nous parlerons affaire."; break;
        case 2102: texte = "On a entendu des bruits de bataille, puis plus rien..."; break;
        case 2103: texte = "Que peut-il bien se passer ?"; break;
        case 2104: texte = "Cette porte mène à la salle cachée. *Obtiens les 9 rangs de la page Records et reviens après avoir obtenu la seconde fin pour y pénétrer."; break;
        case 2105: texte = "Tu peux entrer, Héros Légendaire."; break;
        case 2106: texte = "Bienvenue dans la salle cachée de 3T ! *Et félicitation pour y être arrivé !"; break;
        case 2107: texte = "Moi c'est Vincent, j'ai conçu et codé ce jeu."; break;
        case 2108: texte = "Coucou, moi c'est Lobalùz. *J'ai aidé à la conception, fait quelques nouveaux graphismes, testé la plupart des donjons, et corrigé les textes."; break;
        case 2109: texte = "Salut, moi c'est Raiden. J'suis le dessinateur de l'équipe. Je me suis occupé de l'écran titre et des illustrations (... et aussi des nuages sur les maps m'enfin on s'en fout un peu...)."; break;
        case 2110: texte = "Vous pouvez retrouver mes autres dessins sur http://alandar.deviantart.com"; break;
        case 2111: texte = "Des monstres ont coulé ma barque... *Je suis désolé, mais tu vas devoir nager désormais..."; break;
            
        default:
            texte = "ERREUR TEXTE";
    }

    return texte;
}

void Texte::chercheText() {
    ostringstream os;
    ostringstream os2;
    int tmp;
    switch (id) {
        case 1 : texte = (this->*getTextByLangFunc)(600, os.str()); break;
        case 2 : texte = (this->*getTextByLangFunc)(601, os.str()); break;
        case 3 : 
            tmp = 4-(gpJeu->getJoueur()->nbQuarts()%4);
            os << tmp;
            texte = (this->*getTextByLangFunc)(602, os.str());
            if (tmp<4) buffer = (this->*getTextByLangFunc)(603, os.str())+os.str()+(this->*getTextByLangFunc)(604, os.str());
            else buffer = (this->*getTextByLangFunc)(605, os.str());
            break;
        case 4 : texte = (this->*getTextByLangFunc)(606, os.str()); break;
        case 5 : texte = (this->*getTextByLangFunc)(607, os.str()); break;
        case 6 : texte = (this->*getTextByLangFunc)(608, os.str()); break;
        case 7 : texte = (this->*getTextByLangFunc)(609, os.str()); break;
        case 8 : texte = (this->*getTextByLangFunc)(610, os.str()); break;
        case 9 : texte = (this->*getTextByLangFunc)(611, os.str()); break;
        case 10 : texte = (this->*getTextByLangFunc)(612, os.str()); break;
        case 11 : texte = (this->*getTextByLangFunc)(613, os.str()); break;
        case 12 : texte = (this->*getTextByLangFunc)(614, os.str()); break;
        case 13 : texte = (this->*getTextByLangFunc)(615, os.str()); break;
        case 14 : texte = (this->*getTextByLangFunc)(616, os.str()); break;
        case 15 : texte = (this->*getTextByLangFunc)(617, os.str()); break;
        case 16 : texte = (this->*getTextByLangFunc)(618, os.str()); break;
        case 17 : texte = (this->*getTextByLangFunc)(619, os.str()); break;
        case 18 : texte = (this->*getTextByLangFunc)(620, os.str()); break;
        case 19 : texte = (this->*getTextByLangFunc)(621, os.str()); break;
        case 20 : texte = (this->*getTextByLangFunc)(622, os.str()); break;
        case 21 : texte = (this->*getTextByLangFunc)(623, os.str()); break;
        case 22 : texte = (this->*getTextByLangFunc)(624, os.str()); break;
        case 23 : texte = (this->*getTextByLangFunc)(625, os.str()); buffer=(this->*getTextByLangFunc)(626, os.str()); break;
        case 24 : texte = (this->*getTextByLangFunc)(627, os.str()); break;
        case 25 : texte = (this->*getTextByLangFunc)(628, os.str()); break;
        case 26 : texte = (this->*getTextByLangFunc)(629, os.str()); break;
        case 27 : texte = (this->*getTextByLangFunc)(630, os.str()); break;
        case 28 : texte = (this->*getTextByLangFunc)(631, os.str()); break;
        case 29 : texte = (this->*getTextByLangFunc)(632, os.str()); break;
        case 30 : texte = (this->*getTextByLangFunc)(633, os.str()); break;
        case 31 : texte = (this->*getTextByLangFunc)(634, os.str()); break;
        case 32 : texte = (this->*getTextByLangFunc)(635, os.str()); break;
        case 33 : texte = (this->*getTextByLangFunc)(636, os.str()); break;
        case 34 : texte = (this->*getTextByLangFunc)(637, os.str()); break;
        case 35 : texte = (this->*getTextByLangFunc)(638, os.str()); break;
        case 36 : texte = (this->*getTextByLangFunc)(639, os.str()); break;
        case 37 : texte = (this->*getTextByLangFunc)(640, os.str()); break;
        case 38 : texte = (this->*getTextByLangFunc)(641, os.str()); break;
        case 39 : texte = (this->*getTextByLangFunc)(642, os.str()); break;
        case 40 : 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_DEVANT_CHEZ_LINK) {id=44; chercheText();break;}
            texte = (this->*getTextByLangFunc)(643, os.str()); idsuiv=41; break;
        case 41 : texte = (this->*getTextByLangFunc)(644, os.str()); idsuiv=42; break;
        case 42 : texte = (this->*getTextByLangFunc)(645, os.str()); idsuiv=43; break;
        case 43 : texte = (this->*getTextByLangFunc)(646, os.str()); idsuiv=44; break;
        case 44 : texte = (this->*getTextByLangFunc)(647, os.str()); break;
        case 45 : texte = (this->*getTextByLangFunc)(648, os.str()); idsuiv=46; break;
#ifdef __vita__
        case 46 : texte = (this->*getTextByLangFunc)(649, os.str()); break;
#else
        case 46 : texte = (this->*getTextByLangFunc)(650, os.str()); break;
#endif
        case 47 : texte = (this->*getTextByLangFunc)(651, os.str());
            if (gpJeu->getJoueur()->hasMelodie(0)) {id=48; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=57; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=59; chercheText();break;}
            break;
        case 48 : texte = (this->*getTextByLangFunc)(652, os.str());
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=50; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=61; chercheText();break;}
            break;
        case 49 : texte = (this->*getTextByLangFunc)(653, os.str()); break;
        case 50 : texte = (this->*getTextByLangFunc)(654, os.str());
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=53; chercheText();break;}
            break;
        case 51 : texte = (this->*getTextByLangFunc)(655, os.str()); break;
        case 52 : texte = (this->*getTextByLangFunc)(656, os.str()); break;
        case 53 : texte = (this->*getTextByLangFunc)(657, os.str()); break;
        case 54 : texte = (this->*getTextByLangFunc)(658, os.str()); break;
        case 55 : texte = (this->*getTextByLangFunc)(659, os.str()); break;
        case 56 : texte = (this->*getTextByLangFunc)(660, os.str()); break;
        case 57 : texte = (this->*getTextByLangFunc)(661, os.str());
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=64; chercheText();break;}
            break;
        case 58 : texte = (this->*getTextByLangFunc)(662, os.str()); break;
        case 59 : texte = (this->*getTextByLangFunc)(663, os.str()); break;
        case 60 : texte = (this->*getTextByLangFunc)(664, os.str()); break;
        case 61 : texte = (this->*getTextByLangFunc)(665, os.str()); break;
        case 62 : texte = (this->*getTextByLangFunc)(666, os.str()); break;
        case 63 : texte = (this->*getTextByLangFunc)(667, os.str()); break;
        case 64 : texte = (this->*getTextByLangFunc)(668, os.str()); break;
        case 65 : texte = (this->*getTextByLangFunc)(669, os.str()); break;
        case 66 : texte = (this->*getTextByLangFunc)(670, os.str()); break;
        case 67 : texte = (this->*getTextByLangFunc)(671, os.str()); break;
        case 68 : texte = (this->*getTextByLangFunc)(672, os.str()); break;
        case 69 : texte = (this->*getTextByLangFunc)(673, os.str()); break;
        case 70 : texte = (this->*getTextByLangFunc)(674, os.str()); break;
        case 71 : texte = (this->*getTextByLangFunc)(675, os.str()); break;
        case 72 : texte = (this->*getTextByLangFunc)(676, os.str()); break;
        case 73 : texte = (this->*getTextByLangFunc)(677, os.str()); break;
        case 74 : texte = (this->*getTextByLangFunc)(678, os.str()); break;
        case 75 : texte = (this->*getTextByLangFunc)(679, os.str()); break;
        case 76 : texte = (this->*getTextByLangFunc)(680, os.str()); break;
        case 77 : 
            if (gpJeu->getJoueur()->getTroc(M_ROUAGE)>-1) {id=80; chercheText();break;}
            texte = (this->*getTextByLangFunc)(681, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100
            || gpJeu->getJoueur()->getTroc(M_POULET)<1) idsuiv=75;
            break;
        case 78 : texte = (this->*getTextByLangFunc)(682, os.str()); idsuiv=76; break;
        case 79 : texte = (this->*getTextByLangFunc)(683, os.str()); break;
        case 80 : 
            if ((gpJeu->getJoueur()->getCoeur(14) && gpJeu->getZone()==18)
            || (gpJeu->getJoueur()->getCoeur(15) && gpJeu->getZone()==3)) {
                id=82; chercheText();break;}
            texte = (this->*getTextByLangFunc)(684, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)<1) idsuiv=75;
            break;
        case 81 : texte = (this->*getTextByLangFunc)(685, os.str()); idsuiv=76; break;
        case 82 : texte = (this->*getTextByLangFunc)(686, os.str()); break;
        case 83 : 
            if (gpJeu->getJoueur()->getRubisMax()>=200) {id=86; chercheText();break;}
            texte = (this->*getTextByLangFunc)(687, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10
            || gpJeu->getJoueur()->getTroc(M_PLUME)<1) idsuiv=75;
            break;
        case 84 : texte = (this->*getTextByLangFunc)(688, os.str()); idsuiv=76; break;
        case 85 : texte = (this->*getTextByLangFunc)(689, os.str()); break;
        case 86 : 
            if (gpJeu->getJoueur()->getRubisMax()>=500) {id=89; chercheText();break;}
            texte = (this->*getTextByLangFunc)(690, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100
            || gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1) idsuiv=75;
            break;
        case 87 : texte = (this->*getTextByLangFunc)(691, os.str()); idsuiv=76; break;
        case 88 : texte = (this->*getTextByLangFunc)(692, os.str()); break;
        case 89 : 
            if (gpJeu->getJoueur()->getRubisMax()==999) {id=82; chercheText();break;}
            texte = (this->*getTextByLangFunc)(693, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<250
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)<1) idsuiv=75;
            break;
        case 90 : texte = (this->*getTextByLangFunc)(694, os.str()); idsuiv=76; break;
        case 91 : texte = (this->*getTextByLangFunc)(695, os.str()); break;
        case 92 : 
            texte = (this->*getTextByLangFunc)(696, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_RIZ)<2
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<3) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_POULET)>=99) idsuiv=95;
            break;
        case 93 : texte = (this->*getTextByLangFunc)(697, os.str()); idsuiv=76; break;
        case 94 : texte = (this->*getTextByLangFunc)(698, os.str()); break;
        case 95 : texte = (this->*getTextByLangFunc)(699, os.str()); break;
        case 96 : 
            texte = (this->*getTextByLangFunc)(700, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<2
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<2) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PLUME)>=99) idsuiv=95;
            break;
        case 97 : texte = (this->*getTextByLangFunc)(701, os.str()); idsuiv=76; break;
        case 98 : texte = (this->*getTextByLangFunc)(702, os.str()); break;
        case 99 : 
            texte = (this->*getTextByLangFunc)(703, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_RIZ)>=99) idsuiv=95;
            break;
        case 100 : texte = (this->*getTextByLangFunc)(704, os.str()); idsuiv=76; break;
        case 101 : texte = (this->*getTextByLangFunc)(705, os.str()); break;
        case 102 : 
            texte = (this->*getTextByLangFunc)(706, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_OLIVES)>=99) idsuiv=95;
            break;
        case 103 : texte = (this->*getTextByLangFunc)(707, os.str()); idsuiv=76; break;
        case 104 : texte = (this->*getTextByLangFunc)(708, os.str()); break;
        case 105 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>2) {id=112; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==2 
            && gpJeu->getJoueur()->getObjet()==15) {id=106; chercheText();break;}
            texte = (this->*getTextByLangFunc)(709, os.str()); break;
        case 106 : texte = (this->*getTextByLangFunc)(710, os.str()); idsuiv=107; break;
        case 107 : texte = (this->*getTextByLangFunc)(711, os.str()); idsuiv=109; break;
        case 108 : texte = (this->*getTextByLangFunc)(712, os.str()); idsuiv=110; break;
        case 109 : texte = (this->*getTextByLangFunc)(713, os.str()); break;
        case 110 : texte = (this->*getTextByLangFunc)(714, os.str()); break;
        case 111 : texte = (this->*getTextByLangFunc)(715, os.str()); break;
        case 112 : texte = (this->*getTextByLangFunc)(716, os.str()); break;
        case 113 : texte = (this->*getTextByLangFunc)(717, os.str()); break;
        case 114 : texte = (this->*getTextByLangFunc)(718, os.str()); break;
        case 115 : texte = (this->*getTextByLangFunc)(719, os.str()); break;
        case 116 : texte = (this->*getTextByLangFunc)(720, os.str()); break;
        case 117 : texte = (this->*getTextByLangFunc)(721, os.str()); break;
        case 118 : texte = (this->*getTextByLangFunc)(722, os.str()); break;
        case 119 : texte = (this->*getTextByLangFunc)(723, os.str()); break;
        case 120 : texte = (this->*getTextByLangFunc)(724, os.str()); break;
        case 121 : texte = (this->*getTextByLangFunc)(725, os.str()); break;
        case 122 : texte = (this->*getTextByLangFunc)(726, os.str()); break;
        case 123 : texte = (this->*getTextByLangFunc)(727, os.str());
            buffer=(this->*getTextByLangFunc)(728, os.str()); break;
        case 124 : texte = (this->*getTextByLangFunc)(729, os.str()); break;
        case 125 : texte = (this->*getTextByLangFunc)(730, os.str()); break;
        case 126 : 
            if (gpJeu->getJoueur()->hasObjet(O_PERLE)) {id=82; chercheText();break;}
            texte = (this->*getTextByLangFunc)(731, os.str()); 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<100
            || gpJeu->getJoueur()->getTroc(M_ROUE)<1
            || gpJeu->getJoueur()->getTroc(M_JAUGE)<1
            || gpJeu->getJoueur()->getTroc(M_SOURCE_ENERGIE)<1) idsuiv=75;
            break;
        case 127 : texte = (this->*getTextByLangFunc)(732, os.str()); idsuiv=76; break;
        case 128 : texte = (this->*getTextByLangFunc)(733, os.str()); break;
        case 129 : 
            if (gpJeu->getJoueur()->getGanonMax()>=200) {id=132; chercheText();break;}
            texte = (this->*getTextByLangFunc)(734, os.str()); 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10
            || gpJeu->getJoueur()->getTroc(M_PERLES)<1) idsuiv=75;
            break;
        case 130 : texte = (this->*getTextByLangFunc)(735, os.str()); idsuiv=76; break;
        case 131 : texte = (this->*getTextByLangFunc)(736, os.str()); break;
        case 132 : 
            if (gpJeu->getJoueur()->getGanonMax()>=500) {id=135; chercheText();break;}
            texte = (this->*getTextByLangFunc)(737, os.str()); 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<100
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1) idsuiv=75;
            break;
        case 133 : texte = (this->*getTextByLangFunc)(738, os.str()); idsuiv=76; break;
        case 134 : texte = (this->*getTextByLangFunc)(739, os.str()); break;
        case 135 : 
            if (gpJeu->getJoueur()->getGanonMax()==999) {id=82; chercheText();break;}
            texte = (this->*getTextByLangFunc)(740, os.str()); 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<250
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)<1) idsuiv=75;
            break;
        case 136 : texte = (this->*getTextByLangFunc)(741, os.str()); idsuiv=76; break;
        case 137 : texte = (this->*getTextByLangFunc)(742, os.str()); break;
        case 138 : 
            if (gpJeu->getJoueur()->getTroc(M_ROUE)>-1) {id=141; chercheText();break;}
            texte = (this->*getTextByLangFunc)(743, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<3) idsuiv=75;
            break;
        case 139 : texte = (this->*getTextByLangFunc)(744, os.str()); idsuiv=76; break;
        case 140 : texte = (this->*getTextByLangFunc)(745, os.str()); break;
        case 141 : 
            if (gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=82; chercheText();break;}
            texte = (this->*getTextByLangFunc)(746, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_POIVRON)<1
            || gpJeu->getJoueur()->getTroc(M_EPICES)<3) idsuiv=75;
            break;
        case 142 : texte = (this->*getTextByLangFunc)(747, os.str()); idsuiv=76; break;
        case 143 : texte = (this->*getTextByLangFunc)(748, os.str()); break;
        case 144 : 
            texte = (this->*getTextByLangFunc)(749, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)>=99) idsuiv=95;
            break;
        case 145 : texte = (this->*getTextByLangFunc)(750, os.str()); idsuiv=76; break;
        case 146 : texte = (this->*getTextByLangFunc)(751, os.str()); break;
        case 147 : 
            texte = (this->*getTextByLangFunc)(752, os.str()); 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<5
            || gpJeu->getJoueur()->getTroc(M_EPICES)<5) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PERLES)>=99) idsuiv=95;
            break;
        case 148 : texte = (this->*getTextByLangFunc)(753, os.str()); idsuiv=76; break;
        case 149 : texte = (this->*getTextByLangFunc)(754, os.str()); break;
        case 150 : 
            texte = (this->*getTextByLangFunc)(755, os.str()); 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_EPICES)>=99) idsuiv=95;
            break;
        case 151 : texte = (this->*getTextByLangFunc)(756, os.str()); idsuiv=76; break;
        case 152 : texte = (this->*getTextByLangFunc)(757, os.str()); break;
        case 153 : texte = (this->*getTextByLangFunc)(758, os.str()); break;
        case 154 : texte = (this->*getTextByLangFunc)(759, os.str()); break;
        case 155 : texte = (this->*getTextByLangFunc)(760, os.str()); 
            buffer=(this->*getTextByLangFunc)(761, os.str()); break;
        case 156 : texte = (this->*getTextByLangFunc)(762, os.str()); break;
        case 157 : 
            if (gpJeu->getJoueur()->hasObjet(O_PERLE)) texte = (this->*getTextByLangFunc)(763, os.str());
            else texte = (this->*getTextByLangFunc)(764, os.str()); break;
        case 158 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(765, os.str()); break;
        case 159 : 
            if (gpJeu->getJoueur()->getPieceMax()>=200) {id=162; chercheText();break;}
            texte = (this->*getTextByLangFunc)(766, os.str()); 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<10
            || gpJeu->getJoueur()->getTroc(M_POULET)<1) idsuiv=75;
            break;
        case 160 : texte = (this->*getTextByLangFunc)(767, os.str()); idsuiv=76; break;
        case 161 : texte = (this->*getTextByLangFunc)(768, os.str()); break;
        case 162 : 
            if (gpJeu->getJoueur()->getPieceMax()>=500) {id=165; chercheText();break;}
            texte = (this->*getTextByLangFunc)(769, os.str()); 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<100
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            break;
        case 163 : texte = (this->*getTextByLangFunc)(770, os.str()); idsuiv=76; break;
        case 164 : texte = (this->*getTextByLangFunc)(771, os.str()); break;
        case 165 : 
            if (gpJeu->getJoueur()->getPieceMax()==999) {id=82; chercheText();break;}
            texte = (this->*getTextByLangFunc)(772, os.str()); 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<250
            || gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_ROC_MAGMA)<1) idsuiv=75;
            break;
        case 166 : texte = (this->*getTextByLangFunc)(773, os.str()); idsuiv=76; break;
        case 167 : texte = (this->*getTextByLangFunc)(774, os.str()); break;
        case 168 : 
            texte = (this->*getTextByLangFunc)(775, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_POULET)<1
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<2) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_AMULETTE)>=99) idsuiv=95;
            break;
        case 169 : texte = (this->*getTextByLangFunc)(776, os.str()); idsuiv=76; break;
        case 170 : texte = (this->*getTextByLangFunc)(777, os.str()); break;
        case 171 : 
            texte = (this->*getTextByLangFunc)(778, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<1
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PLUME)>=99) idsuiv=95;
            break;
        case 172 : texte = (this->*getTextByLangFunc)(779, os.str()); idsuiv=76; break;
        case 173 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(780, os.str()); break;
        case 174 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(781, os.str()); break;
        case 175 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(782, os.str()); break;
        case 176 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(783, os.str()); break;
        case 177 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(784, os.str()); break;
        case 178 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (!gpJeu->getJoueur()->getPieceMax()) {id=771; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>3) {id=185; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==3 
            && gpJeu->getJoueur()->getObjet()==15) {id=179; chercheText();break;}
            texte = (this->*getTextByLangFunc)(785, os.str()); break;
        case 179 : texte = (this->*getTextByLangFunc)(786, os.str()); idsuiv=180; break;
        case 180 : texte = (this->*getTextByLangFunc)(787, os.str()); idsuiv=182; break;
        case 181 : texte = (this->*getTextByLangFunc)(788, os.str()); idsuiv=183; break;
        case 182 : texte = (this->*getTextByLangFunc)(789, os.str()); break;
        case 183 : texte = (this->*getTextByLangFunc)(790, os.str()); break;
        case 184 : texte = (this->*getTextByLangFunc)(791, os.str()); break;
        case 185 : texte = (this->*getTextByLangFunc)(792, os.str()); break;
        case 186 : texte = (this->*getTextByLangFunc)(793, os.str()); break;
        case 187 : texte = (this->*getTextByLangFunc)(794, os.str()); break;
        case 188 : texte = (this->*getTextByLangFunc)(795, os.str()); break;
        case 189 : texte = (this->*getTextByLangFunc)(796, os.str()); break;
        case 190 : texte = (this->*getTextByLangFunc)(797, os.str()); break;
        case 191 : 
            texte = (this->*getTextByLangFunc)(798, os.str()); 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<5) idsuiv=75;
            break;
        case 192 : texte = (this->*getTextByLangFunc)(799, os.str()); idsuiv=76; break;
        case 193 : texte = (this->*getTextByLangFunc)(800, os.str()); break;
        case 194 : texte = (this->*getTextByLangFunc)(801, os.str()); break;
        case 195 : texte = (this->*getTextByLangFunc)(802, os.str()); break;
        case 196 : texte = (this->*getTextByLangFunc)(803, os.str()); break;
        case 197 : texte = (this->*getTextByLangFunc)(804, os.str()); break;
        case 198 : 
            tmp = 6-(gpJeu->getJoueur()->nbCristaux());
            os << tmp;
            texte = (this->*getTextByLangFunc)(805, os.str());
            if (tmp>0) buffer = (this->*getTextByLangFunc)(806, os.str())+os.str()+(this->*getTextByLangFunc)(807, os.str());
            else buffer = (this->*getTextByLangFunc)(808, os.str());
            break;
        case 199 : texte = (this->*getTextByLangFunc)(809, os.str()); break;
        case 200 : texte = (this->*getTextByLangFunc)(810, os.str()); break;
        case 201 : texte = (this->*getTextByLangFunc)(811, os.str()); break;
        
        case 202 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>6) {id=209; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==6 
            && gpJeu->getJoueur()->getObjet()==11) {id=203; chercheText();break;}
            texte = (this->*getTextByLangFunc)(812, os.str()); 
            buffer=(this->*getTextByLangFunc)(813, os.str()); break;
        case 203 : texte = (this->*getTextByLangFunc)(814, os.str()); idsuiv=204; break;
        case 204 : texte = (this->*getTextByLangFunc)(815, os.str()); idsuiv=206; break;
        case 205 : texte = (this->*getTextByLangFunc)(816, os.str()); idsuiv=207; break;
        case 206 : texte = (this->*getTextByLangFunc)(817, os.str()); buffer=(this->*getTextByLangFunc)(818, os.str()); break;
        case 207 : texte = (this->*getTextByLangFunc)(819, os.str()); break;
        case 208 : texte = (this->*getTextByLangFunc)(820, os.str()); break;
        case 209 : texte = (this->*getTextByLangFunc)(821, os.str()); buffer=(this->*getTextByLangFunc)(822, os.str()); break;
        case 210 : texte = (this->*getTextByLangFunc)(823, os.str()); break;
        case 211 : texte = (this->*getTextByLangFunc)(824, os.str()); break;
        case 212 : texte = (this->*getTextByLangFunc)(825, os.str()); break;
        case 213 : texte = (this->*getTextByLangFunc)(826, os.str()); break;
        case 214 : texte = (this->*getTextByLangFunc)(827, os.str()); break;
        case 215 : 
            texte = (this->*getTextByLangFunc)(828, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_PERLES)<2
            || gpJeu->getJoueur()->getTroc(M_EPICES)<5) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)>=99) idsuiv=95;
            break;
        case 216 : texte = (this->*getTextByLangFunc)(829, os.str()); idsuiv=76; break;
        case 217 : texte = (this->*getTextByLangFunc)(830, os.str()); break;
        case 218 : 
            texte = (this->*getTextByLangFunc)(831, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_POULET)<5
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<5) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_AMULETTE)>=99) idsuiv=95;
            break;
        case 219 : texte = (this->*getTextByLangFunc)(832, os.str()); idsuiv=76; break;
        case 220 : 
            texte = (this->*getTextByLangFunc)(833, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<2
            || gpJeu->getJoueur()->getTroc(M_RIZ)<2) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PERLES)>=99) idsuiv=95;
            break;
        case 221 : texte = (this->*getTextByLangFunc)(834, os.str()); idsuiv=76; break;
        case 222 : 
            texte = (this->*getTextByLangFunc)(835, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<2
            || gpJeu->getJoueur()->getTroc(M_OLIVES)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_RIZ)>=99) idsuiv=95;
            break;
        case 223 : texte = (this->*getTextByLangFunc)(836, os.str()); idsuiv=76; break;
        case 224 : 
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)==0) 
                texte = (this->*getTextByLangFunc)(837, os.str()); 
            else if (gpJeu->getJoueur()->hasObjet(O_POISSONS)==0)
                {texte = (this->*getTextByLangFunc)(838, os.str()); buffer=(this->*getTextByLangFunc)(839, os.str());} 
            else {texte = (this->*getTextByLangFunc)(840, os.str()); buffer=(this->*getTextByLangFunc)(841, os.str());}
            break;
        case 225 : 
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)==0) 
                texte = (this->*getTextByLangFunc)(842, os.str()); 
            else if (gpJeu->getJoueur()->hasObjet(O_POISSONS)==0)
                {texte = (this->*getTextByLangFunc)(843, os.str());} 
            else {texte = (this->*getTextByLangFunc)(844, os.str());}
            break;
        case 226 : texte = (this->*getTextByLangFunc)(845, os.str()); break;
        case 227 : 
            texte = (this->*getTextByLangFunc)(846, os.str());
            if (gpJeu->getJoueur()->getAvancement()<GANON_CAPTURE)
            texte += (this->*getTextByLangFunc)(847, os.str()); break;
        case 228 :
            if (gpJeu->getJoueur()->getGemme(91)) {id=230; chercheText();break;}
            texte = (this->*getTextByLangFunc)(848, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_PERLES)<2) idsuiv=75;
            break;
        case 229 : texte = (this->*getTextByLangFunc)(849, os.str()); idsuiv=76; break;
        case 230 : 
            if (gpJeu->getJoueur()->getGemme(92)) {id=232; chercheText();break;}
            texte = (this->*getTextByLangFunc)(850, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_PLUME)<2) idsuiv=75;
            break;
        case 231 : texte = (this->*getTextByLangFunc)(851, os.str()); idsuiv=76; break;
        case 232 : 
            if (gpJeu->getJoueur()->getGemme(93)) {id=82; chercheText();break;}
            texte = (this->*getTextByLangFunc)(852, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_POULET)<2) idsuiv=75;
            break;
        case 233 : texte = (this->*getTextByLangFunc)(853, os.str()); idsuiv=76; break;
        case 234 : 
            texte = (this->*getTextByLangFunc)(854, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_OLIVES)<2
            || gpJeu->getJoueur()->getTroc(M_RIZ)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_POULET)>=99) idsuiv=95;
            break;
        case 235 : texte = (this->*getTextByLangFunc)(855, os.str()); idsuiv=76; break;
        case 236 : texte = (this->*getTextByLangFunc)(856, os.str()); buffer=(this->*getTextByLangFunc)(857, os.str()); break;
        case 237 : texte = (this->*getTextByLangFunc)(858, os.str()); 
            if (gpJeu->getJoueur()->getAvancement()<GANON_CAPTURE) 
            buffer=(this->*getTextByLangFunc)(859, os.str()); break;
        case 238 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>2) {id=245; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==2 
            && gpJeu->getJoueur()->getObjet()==7) {id=239; chercheText();break;}
            texte = (this->*getTextByLangFunc)(860, os.str()); break;
        case 239 : texte = (this->*getTextByLangFunc)(861, os.str()); idsuiv=240; break;
        case 240 : texte = (this->*getTextByLangFunc)(862, os.str()); idsuiv=242; break;
        case 241 : texte = (this->*getTextByLangFunc)(863, os.str()); idsuiv=243; break;
        case 242 : texte = (this->*getTextByLangFunc)(864, os.str()); break;
        case 243 : texte = (this->*getTextByLangFunc)(865, os.str()); break;
        case 244 : texte = (this->*getTextByLangFunc)(866, os.str()); break;
        case 245 : texte = (this->*getTextByLangFunc)(867, os.str()); idsuiv=247; break;
        case 246 : texte = (this->*getTextByLangFunc)(868, os.str()); idsuiv=243; break;
        case 247 : texte = (this->*getTextByLangFunc)(869, os.str()); break;
        case 248 : texte = (this->*getTextByLangFunc)(870, os.str()); break;
        case 249 : texte = (this->*getTextByLangFunc)(871, os.str()); break;
        case 250 : texte = (this->*getTextByLangFunc)(872, os.str()); break;
        case 251 : 
            if (gpJeu->getJoueur()->hasObjet(O_PALMES)) {id=1378; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_BARQUE)) {id=253; chercheText();break;}
            texte = (this->*getTextByLangFunc)(873, os.str()); idsuiv=253;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75;
            break;
        case 252 : texte = (this->*getTextByLangFunc)(874, os.str()); idsuiv=76; break;
        case 253 : texte = (this->*getTextByLangFunc)(875, os.str()); break;
        case 254 : texte = (this->*getTextByLangFunc)(876, os.str()); break;
        case 255 : texte = (this->*getTextByLangFunc)(877, os.str()); break;
        case 256 : texte = (this->*getTextByLangFunc)(878, os.str()); break;
        case 257 : texte = (this->*getTextByLangFunc)(879, os.str()); break;
        case 258 : texte = (this->*getTextByLangFunc)(880, os.str()); break;
        case 259 : texte = (this->*getTextByLangFunc)(881, os.str()); break;
        case 260 : texte = (this->*getTextByLangFunc)(882, os.str()); break;
        case 261 : texte = (this->*getTextByLangFunc)(883, os.str()); break;
        case 262 : texte = (this->*getTextByLangFunc)(884, os.str()); break;
        case 263 : texte = (this->*getTextByLangFunc)(885, os.str()); break;
        case 264 : texte = (this->*getTextByLangFunc)(886, os.str()); break;
        case 265 : 
            if (gpJeu->getJoueur()->hasObjet(O_BOTTES)) {id=82; chercheText();break;}
            texte = (this->*getTextByLangFunc)(887, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            break;
        case 266 : texte = (this->*getTextByLangFunc)(888, os.str()); idsuiv=76; break;
#ifdef __vita__
        case 267 : texte = (this->*getTextByLangFunc)(889, os.str()); break;
#else
        case 267 : texte = (this->*getTextByLangFunc)(890, os.str()); break;
#endif
        case 268 : 
            texte = (this->*getTextByLangFunc)(891, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_PLUME)<3
            || gpJeu->getJoueur()->getTroc(M_RIZ)<4) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PARFUM)>=99) idsuiv=95;
            break;
        case 269 : texte = (this->*getTextByLangFunc)(892, os.str()); idsuiv=76; break;
        case 270 : texte = (this->*getTextByLangFunc)(893, os.str()); break;
        case 271 : 
            texte = (this->*getTextByLangFunc)(894, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_OLIVES)>=99) idsuiv=95;
            break;
        case 272 : texte = (this->*getTextByLangFunc)(895, os.str()); idsuiv=76; break;
        case 273 : 
            texte = (this->*getTextByLangFunc)(896, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_EPICES)>=99) idsuiv=95;
            break;
        case 274 : texte = (this->*getTextByLangFunc)(897, os.str()); idsuiv=76; break;
        case 275 : texte = (this->*getTextByLangFunc)(898, os.str()); break;
        case 276 : texte = (this->*getTextByLangFunc)(899, os.str()); break;
        case 277 : texte = (this->*getTextByLangFunc)(900, os.str()); 
            if (gpJeu->getJoueur()->hasObjet(O_BOTTES)) buffer=(this->*getTextByLangFunc)(901, os.str()); break;
        case 278 : 
            texte = (this->*getTextByLangFunc)(902, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_TAPISSERIE)<1
            || gpJeu->getJoueur()->getTroc(M_AMULETTE)<1
            || gpJeu->getJoueur()->getTroc(M_PARFUM)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)>=99) idsuiv=95;
            break;
        case 279 : texte = (this->*getTextByLangFunc)(903, os.str()); idsuiv=76; break;
        case 280 : texte = (this->*getTextByLangFunc)(904, os.str()); break;
        case 281 : 
            texte = (this->*getTextByLangFunc)(905, os.str()); 
            if (gpJeu->getJoueur()->getTroc(M_EPICES)<1
            || gpJeu->getJoueur()->getTroc(M_RIZ)<1) idsuiv=75;
            else if (gpJeu->getJoueur()->getTroc(M_PERLES)>=99) idsuiv=95;
            break;
        case 282 : texte = (this->*getTextByLangFunc)(906, os.str()); idsuiv=76; break;
        case 283 : texte = (this->*getTextByLangFunc)(907, os.str()); break;
        case 284 : texte = (this->*getTextByLangFunc)(908, os.str()); break;
        case 285 : texte = (this->*getTextByLangFunc)(909, os.str()); break;
        case 286 : texte = (this->*getTextByLangFunc)(910, os.str()); break;
        case 287 : texte = (this->*getTextByLangFunc)(911, os.str()); break;
        case 288 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>2) {id=295; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==2 
            && gpJeu->getJoueur()->getObjet()==11) {id=289; chercheText();break;}
            texte = (this->*getTextByLangFunc)(912, os.str()); buffer=(this->*getTextByLangFunc)(913, os.str()); break;
        case 289 : texte = (this->*getTextByLangFunc)(914, os.str()); idsuiv=290; break;
        case 290 : texte = (this->*getTextByLangFunc)(915, os.str()); idsuiv=292; break;
        case 291 : texte = (this->*getTextByLangFunc)(916, os.str()); idsuiv=293; break;
        case 292 : texte = (this->*getTextByLangFunc)(917, os.str()); break;
        case 293 : texte = (this->*getTextByLangFunc)(918, os.str()); break;
        case 294 : texte = (this->*getTextByLangFunc)(919, os.str()); break;
        case 295 : texte = (this->*getTextByLangFunc)(920, os.str()); break;
        case 296 : texte = (this->*getTextByLangFunc)(921, os.str()); break;
        case 297 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>1) {id=304; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==1 
            && gpJeu->getJoueur()->getObjet()==3) {id=298; chercheText();break;}
            texte = (this->*getTextByLangFunc)(922, os.str()); break;
        case 298 : texte = (this->*getTextByLangFunc)(923, os.str()); idsuiv=299; break;
        case 299 : texte = (this->*getTextByLangFunc)(924, os.str()); idsuiv=301; break;
        case 300 : texte = (this->*getTextByLangFunc)(925, os.str()); idsuiv=302; break;
        case 301 : texte = (this->*getTextByLangFunc)(926, os.str()); break;
        case 302 : texte = (this->*getTextByLangFunc)(927, os.str()); break;
        case 303 : texte = (this->*getTextByLangFunc)(928, os.str()); break;
        case 304 : texte = (this->*getTextByLangFunc)(929, os.str()); break;
        case 305 : texte = (this->*getTextByLangFunc)(930, os.str()); break;
        case 306 : texte = (this->*getTextByLangFunc)(931, os.str()); break;
        case 307 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>4) {id=314; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==4 
            && gpJeu->getJoueur()->getObjet()==7) {id=308; chercheText();break;}
            texte = (this->*getTextByLangFunc)(932, os.str()); 
            buffer = (this->*getTextByLangFunc)(933, os.str()); break;
        case 308 : texte = (this->*getTextByLangFunc)(934, os.str()); idsuiv=309; break;
        case 309 : texte = (this->*getTextByLangFunc)(935, os.str()); idsuiv=311; break;
        case 310 : texte = (this->*getTextByLangFunc)(936, os.str()); idsuiv=312; break;
        case 311 : texte = (this->*getTextByLangFunc)(937, os.str()); break;
        case 312 : texte = (this->*getTextByLangFunc)(938, os.str()); break;
        case 313 : texte = (this->*getTextByLangFunc)(939, os.str()); break;
        case 314 : texte = (this->*getTextByLangFunc)(940, os.str()); buffer=(this->*getTextByLangFunc)(941, os.str()); break;
        case 315 : texte = (this->*getTextByLangFunc)(942, os.str()); break;
#ifdef __vita__   
        case 316 : texte = (this->*getTextByLangFunc)(943, os.str()); break;
#else     
        case 316 : texte = (this->*getTextByLangFunc)(944, os.str()); break;
#endif
        case 317 : texte = (this->*getTextByLangFunc)(945, os.str()); break;
        case 318 : texte = (this->*getTextByLangFunc)(946, os.str()); buffer=(this->*getTextByLangFunc)(947, os.str()); break;
        case 319 : texte = (this->*getTextByLangFunc)(948, os.str()); break;
        case 320 : texte = (this->*getTextByLangFunc)(949, os.str()); break;
        case 321 : texte = (this->*getTextByLangFunc)(950, os.str()); idsuiv=322; break;
        case 322 : texte = (this->*getTextByLangFunc)(951, os.str()); break;
        case 323 : texte = (this->*getTextByLangFunc)(952, os.str()); buffer=(this->*getTextByLangFunc)(953, os.str()); idsuiv=324; break;
        case 324 : texte = (this->*getTextByLangFunc)(954, os.str()); break;
#ifdef __vita__
        case 325 : texte = (this->*getTextByLangFunc)(955, os.str()); break;
#else
        case 325 : texte = (this->*getTextByLangFunc)(956, os.str()); break;
#endif
        case 326 : 
            if (!gpJeu->getJoueur()->hasMedaillon(0)) {texte = (this->*getTextByLangFunc)(957, os.str()); break;}
            if (!gpJeu->getJoueur()->hasMedaillon(1)) {texte = (this->*getTextByLangFunc)(958, os.str()); break;}
            if (!gpJeu->getJoueur()->hasMedaillon(2)) {texte = (this->*getTextByLangFunc)(959, os.str()); break;}
            if (gpJeu->getJoueur()->getEpee()<2 && !gpJeu->getJoueur()->hasObjet(O_OCARINA)) {id=327; chercheText();break;}
            id=329; chercheText();break;
        case 327 : texte = (this->*getTextByLangFunc)(960, os.str()); break;
        case 328 : texte = (this->*getTextByLangFunc)(961, os.str()); break;
        case 329 : 
            if (gpJeu->getJoueur()->getAvancement() == PORTAIL_F_OUVERT) {texte = (this->*getTextByLangFunc)(962, os.str()); break;}
            texte = (this->*getTextByLangFunc)(963, os.str()); break;
        case 330 : texte = (this->*getTextByLangFunc)(964, os.str()); break;
        case 331 : 
            texte = (this->*getTextByLangFunc)(965, os.str());
            if (gpJeu->getJoueur()->getBouclier()!=1) {idsuiv=333; break;}
            buffer=(this->*getTextByLangFunc)(966, os.str()); break;
        case 332 : texte = (this->*getTextByLangFunc)(967, os.str()); break;
        case 333 : texte = (this->*getTextByLangFunc)(968, os.str()); break;
        case 334 : texte = (this->*getTextByLangFunc)(969, os.str()); break;
        case 335 : texte = (this->*getTextByLangFunc)(970, os.str()); break;
        case 336 : texte = (this->*getTextByLangFunc)(971, os.str()); break;
        case 337 : texte = (this->*getTextByLangFunc)(972, os.str()); break;
        case 338 :
            if (gpJeu->getJoueur()->getAvancement() < GARS_MINE_AIDE) {
                texte = (this->*getTextByLangFunc)(973, os.str()); break;}
            texte = (this->*getTextByLangFunc)(974, os.str()); break;
        case 339 : texte = (this->*getTextByLangFunc)(975, os.str()); break;
        case 340 : texte = (this->*getTextByLangFunc)(976, os.str()); break;
        case 341 : texte = (this->*getTextByLangFunc)(977, os.str()); break;
        case 342 : texte = (this->*getTextByLangFunc)(978, os.str()); break;
        case 343 : texte = (this->*getTextByLangFunc)(979, os.str()); break;
        case 344 : 
            if (gpJeu->getJoueur()->getAvancement() < SAGES_GROTTE) {id=347; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() < PORTAIL_PRE_PRESENT_FERME) {texte = (this->*getTextByLangFunc)(980, os.str()); break;}
            texte = (this->*getTextByLangFunc)(981, os.str()); break;
        case 345 : 
            if (gpJeu->getJoueur()->getAvancement() < SAGES_GROTTE) {id=347; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() < PORTAIL_PRE_PRESENT_FERME) {texte = (this->*getTextByLangFunc)(982, os.str()); break;}
            texte = (this->*getTextByLangFunc)(983, os.str()); break;
        case 346 : 
            if (gpJeu->getJoueur()->getAvancement() < SAGES_GROTTE) {id=347; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement() < PORTAIL_PRE_PRESENT_FERME) {texte = (this->*getTextByLangFunc)(984, os.str()); break;}
            texte = (this->*getTextByLangFunc)(985, os.str()); buffer=(this->*getTextByLangFunc)(986, os.str()); break;
        case 347 : texte = (this->*getTextByLangFunc)(987, os.str()); break;
        case 348 : texte = (this->*getTextByLangFunc)(988, os.str()); break;
        case 349 : texte = (this->*getTextByLangFunc)(989, os.str()); break;
        case 350 :
            if ((gpJeu->getJoueur()->getBombeMax()<30 && gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) 
            || gpJeu->getJoueur()->getFlecheMax()<70)
                {id=351; chercheText();break;}
            if (!gpJeu->getJoueur()->hasObjet(O_RECUP_FLECHE) 
            || !gpJeu->getJoueur()->hasObjet(O_RECUP_BOMBE))
                {id=356; chercheText();break;}
            texte = (this->*getTextByLangFunc)(990, os.str()); break;
            break;
        case 351 : 
            texte = (this->*getTextByLangFunc)(991, os.str()); 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<100) idsuiv=75;
            break;
        case 352 : texte = (this->*getTextByLangFunc)(992, os.str()); idsuiv=353; break;
        case 353 : texte = (this->*getTextByLangFunc)(993, os.str()); break;
        case 354 : texte = (this->*getTextByLangFunc)(994, os.str()); break;
        case 355 : texte = (this->*getTextByLangFunc)(995, os.str()); break;
        case 356 : 
            texte = (this->*getTextByLangFunc)(996, os.str()); 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<999) idsuiv=75;
            break;
        case 357 : texte = (this->*getTextByLangFunc)(997, os.str()); idsuiv=353; break;
        case 358 : texte = (this->*getTextByLangFunc)(998, os.str()); break;
        case 359 : texte = (this->*getTextByLangFunc)(999, os.str()); break;
        case 360 : 
            if (gpJeu->getJoueur()->getMagieMax()>32) {id=333; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1000, os.str()); break;
        case 361 : texte = (this->*getTextByLangFunc)(1001, os.str()); break;
        case 362 : 
            if (gpJeu->getEpoque()==T_PASSE && !gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1002, os.str()); break;
        case 363 : texte = (this->*getTextByLangFunc)(1003, os.str()); break;
        case 364 : texte = (this->*getTextByLangFunc)(1004, os.str()); break;
        case 365 : texte = (this->*getTextByLangFunc)(1005, os.str()); break;
        case 366 : texte = (this->*getTextByLangFunc)(1006, os.str()); break;
        case 367 : 
            if (gpJeu->getEpoque()==T_PASSE && !gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getZone()==84 && gpJeu->getJoueur()->getNbGemmes() == 200 
            && gpJeu->getJoueur()->getGemme() == 0) {id=405; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1007, os.str()); break;
        case 368 : texte = (this->*getTextByLangFunc)(1008, os.str());
            if (!gpJeu->getJoueur()->hasObjet(O_ARC)) {id=373; chercheText(); break;}
            else if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=75; break;
        case 369 : texte = (this->*getTextByLangFunc)(1009, os.str()); break;
        case 370 : texte = (this->*getTextByLangFunc)(1010, os.str());
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=372; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=75; break;
        case 371 : texte = (this->*getTextByLangFunc)(1011, os.str()); break;
        case 372 : texte = (this->*getTextByLangFunc)(1012, os.str()); break;
        case 373 : texte = (this->*getTextByLangFunc)(1013, os.str()); break;
        case 374 : texte = (this->*getTextByLangFunc)(1014, os.str()); break;
        case 375 : texte = (this->*getTextByLangFunc)(1015, os.str()); break;
        case 376 : texte = (this->*getTextByLangFunc)(1016, os.str());
            if (gpJeu->getJoueur()->getVie() + gpJeu->getJoueur()->getBoostVie() >= gpJeu->getJoueur()->getVieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<5) idsuiv=75; break;
        case 377 : texte = (this->*getTextByLangFunc)(1017, os.str()); break;
        case 378 : texte = (this->*getTextByLangFunc)(1018, os.str());
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=75; break;
        case 379 : texte = (this->*getTextByLangFunc)(1019, os.str()); break;
        case 380 : texte = (this->*getTextByLangFunc)(1020, os.str());
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<25) idsuiv=75; break;
        case 381 : texte = (this->*getTextByLangFunc)(1021, os.str()); break;
        case 382 :
            if (gpJeu->getJoueur()->getAvancement()<APPREND_POUR_ROC_GIVRE) {texte = (this->*getTextByLangFunc)(1022, os.str()); break;}
            if (gpJeu->getJoueur()->getAvancement()==APPREND_POUR_ROC_GIVRE 
            && gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)==-1) {
                texte = (this->*getTextByLangFunc)(1023, os.str()); idsuiv=383; break;
            }
            texte = (this->*getTextByLangFunc)(1024, os.str());
            buffer = (this->*getTextByLangFunc)(1025, os.str());
            break;
        case 383 : texte = (this->*getTextByLangFunc)(1026, os.str());
            if (gpJeu->getJoueur()->getGemme()<30) idsuiv=385; break;
        case 384 : texte = (this->*getTextByLangFunc)(1027, os.str()); idsuiv=76; break;
        case 385 : texte = (this->*getTextByLangFunc)(1028, os.str()); break;
        case 386 : texte = (this->*getTextByLangFunc)(1029, os.str()); idsuiv=387; break;
        case 387 : texte = (this->*getTextByLangFunc)(1030, os.str());
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 388 : texte = (this->*getTextByLangFunc)(1031, os.str()); break;
#ifdef __vita__
        case 389 : texte = (this->*getTextByLangFunc)(1032, os.str()); break;
#else
        case 389 : texte = (this->*getTextByLangFunc)(1033, os.str()); break;
#endif
        case 390 : 
            if (gpJeu->getJoueur()->hasBouteille(0)) {id=393; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1034, os.str());
            if (gpJeu->getJoueur()->getGemme()<10) idsuiv=385; break;
        case 391 : texte = (this->*getTextByLangFunc)(1035, os.str()); break;
        case 392 : texte = (this->*getTextByLangFunc)(1036, os.str()); break;
        case 393 : texte = (this->*getTextByLangFunc)(1037, os.str());
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 394 : texte = (this->*getTextByLangFunc)(1038, os.str()); break;
        case 395 : 
            if (gpJeu->getJoueur()->hasObjet(O_BONUS_FORCE)==1) {id=398; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1039, os.str());
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 396 : texte = (this->*getTextByLangFunc)(1040, os.str()); break;
        case 397 : texte = (this->*getTextByLangFunc)(1041, os.str()); break; 
        case 398 : 
            texte = (this->*getTextByLangFunc)(1042, os.str());
            if (gpJeu->getJoueur()->getGemme()<40) idsuiv=385; break;
        case 399 : texte = (this->*getTextByLangFunc)(1043, os.str()); break;
        case 400 : 
            if (gpJeu->getJoueur()->hasObjet(O_BONUS_DEFENSE)==1) {id=403; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1044, os.str());
            if (gpJeu->getJoueur()->getGemme()<20) idsuiv=385; break;
        case 401 : texte = (this->*getTextByLangFunc)(1045, os.str()); break;
        case 402 : texte = (this->*getTextByLangFunc)(1046, os.str()); break; 
        case 403 : 
            texte = (this->*getTextByLangFunc)(1047, os.str());
            if (gpJeu->getJoueur()->getGemme()<40) idsuiv=385; break;
        case 404 : texte = (this->*getTextByLangFunc)(1048, os.str()); break;
        case 405 : texte = (this->*getTextByLangFunc)(1049, os.str()); idsuiv=406; break;
        case 406 : texte = (this->*getTextByLangFunc)(1050, os.str()); idsuiv=407; break;
        case 407 : texte = (this->*getTextByLangFunc)(1051, os.str()); break;
        case 408 : texte = (this->*getTextByLangFunc)(1052, os.str()); break;
        case 409 :
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1053, os.str()); 
            idsuiv=410; break;
        case 410 : texte = (this->*getTextByLangFunc)(1054, os.str()); idsuiv=413; break;
        case 411 : texte = (this->*getTextByLangFunc)(1055, os.str()); 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=374;
            else idsuiv=415; break;
        case 412 : texte = (this->*getTextByLangFunc)(1056, os.str()); break;
        case 413 : texte = (this->*getTextByLangFunc)(1057, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<60) idsuiv=75; break;
        case 414 : texte = (this->*getTextByLangFunc)(1058, os.str()); break;
        case 415 : texte = (this->*getTextByLangFunc)(1059, os.str());
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<40) idsuiv=75; break;
        case 416 : texte = (this->*getTextByLangFunc)(1060, os.str()); break;
        case 417 : texte = (this->*getTextByLangFunc)(1061, os.str()); break;
        case 418 : texte = (this->*getTextByLangFunc)(1062, os.str()); break;
        case 419 : texte = (this->*getTextByLangFunc)(1063, os.str()); break;
        case 420 : texte = (this->*getTextByLangFunc)(1064, os.str()); break;
        case 421 : texte = (this->*getTextByLangFunc)(1065, os.str()); break;
        case 422 : texte = (this->*getTextByLangFunc)(1066, os.str()); break;
        case 423 : texte = (this->*getTextByLangFunc)(1067, os.str()); break;
        case 424 : 
            if (gpJeu->getJoueur()->getCoffre(15,14)) {id=431; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==3 
            && gpJeu->getJoueur()->getObjet()==3) {id=425; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1068, os.str()); break;
        case 425 : texte = (this->*getTextByLangFunc)(1069, os.str()); idsuiv=426; break;
        case 426 : texte = (this->*getTextByLangFunc)(1070, os.str()); idsuiv=428; break;
        case 427 : texte = (this->*getTextByLangFunc)(1071, os.str()); idsuiv=429; break;
        case 428 : texte = (this->*getTextByLangFunc)(1072, os.str()); 
            buffer = (this->*getTextByLangFunc)(1073, os.str()); break;
        case 429 : texte = (this->*getTextByLangFunc)(1074, os.str()); break;
        case 430 : texte = (this->*getTextByLangFunc)(1075, os.str()); break;
        case 431 : texte = (this->*getTextByLangFunc)(1076, os.str()); break;
        case 432 : texte = (this->*getTextByLangFunc)(1077, os.str()); break;
        case 433 : 
            tmp = 4-(gpJeu->getJoueur()->getCoeur(28) + gpJeu->getJoueur()->getGemme(160) 
            + gpJeu->getJoueur()->getGemme(161) + gpJeu->getJoueur()->getGemme(162));
            if (tmp==0) {id=432; chercheText();break;}
            os << tmp; os2 << ((4-tmp+1)*5);
            texte = (this->*getTextByLangFunc)(1078, os.str())+os.str()+(this->*getTextByLangFunc)(1079, os.str())+os2.str()+(this->*getTextByLangFunc)(1080, os.str());
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<(4-tmp+1)*5) idsuiv=75; break;
        case 434 : 
            tmp = 4-(gpJeu->getJoueur()->getCoeur(28) + gpJeu->getJoueur()->getGemme(160) 
            + gpJeu->getJoueur()->getGemme(161) + gpJeu->getJoueur()->getGemme(162));
            os << tmp; os2 << ((4-tmp+1)*5);
            texte = (this->*getTextByLangFunc)(1081, os.str())+os.str()+(this->*getTextByLangFunc)(1082, os.str())+os2.str()+(this->*getTextByLangFunc)(1083, os.str()); break;
        case 435 : texte = (this->*getTextByLangFunc)(1084, os.str()); break;
        case 436 : texte = (this->*getTextByLangFunc)(1085, os.str()); break;
        case 437 : texte = (this->*getTextByLangFunc)(1086, os.str()); break;
        case 438 :
            if (gpJeu->getJoueur()->hasObjet(O_SAC_TROC)) {id=444; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1087, os.str()); idsuiv=439;
            break;
        case 439 : texte = (this->*getTextByLangFunc)(1088, os.str()); 
            buffer=(this->*getTextByLangFunc)(1089, os.str()); idsuiv=440; break;
        case 440 : texte = (this->*getTextByLangFunc)(1090, os.str()); idsuiv=441; break;
        case 441 : texte = (this->*getTextByLangFunc)(1091, os.str()); idsuiv=442; break;
        case 442 : texte = (this->*getTextByLangFunc)(1092, os.str()); idsuiv=443; break;
#ifdef __vita__
        case 443 : texte = (this->*getTextByLangFunc)(1093, os.str()); break;
#else
        case 443 : texte = (this->*getTextByLangFunc)(1094, os.str()); break;
#endif
        case 444 : 
            if (gpJeu->getJoueur()->getTroc(M_ROUAGE)==0) {id=446; chercheText();break;}
            if (gpJeu->getJoueur()->getTroc(M_ROUAGE)>0) {id=445; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1095, os.str()); break;
        case 445 : texte = (this->*getTextByLangFunc)(1096, os.str()); break;
        case 446 : texte = (this->*getTextByLangFunc)(1097, os.str()); break;
        case 447 : 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1098, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<160) idsuiv=75; break;
        case 448 : texte = (this->*getTextByLangFunc)(1099, os.str()); break;
        case 449 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>1) {id=456; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==1 
            && gpJeu->getJoueur()->getObjet()==15) {id=450; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1100, os.str()); 
            buffer = (this->*getTextByLangFunc)(1101, os.str()); break;
        case 450 : texte = (this->*getTextByLangFunc)(1102, os.str()); idsuiv=451; break;
        case 451 : texte = (this->*getTextByLangFunc)(1103, os.str()); idsuiv=453; break;
        case 452 : texte = (this->*getTextByLangFunc)(1104, os.str()); idsuiv=454; break;
        case 453 : texte = (this->*getTextByLangFunc)(1105, os.str()); break;
        case 454 : texte = (this->*getTextByLangFunc)(1106, os.str()); break;
        case 455 : texte = (this->*getTextByLangFunc)(1107, os.str()); break;
        case 456 : texte = (this->*getTextByLangFunc)(1108, os.str()); break;
        case 457 : texte = (this->*getTextByLangFunc)(1109, os.str()); 
            buffer = (this->*getTextByLangFunc)(1110, os.str()); break;
        case 458 :
            // Concours de pêche

            // Possède la canne à pêche
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)) {

                // A attrapé des poissons
                if (gpJeu->getJoueur()->hasObjet(O_POISSONS)) {

                    // Possède la canne à pêche niveau 2
                    if (gpJeu->getJoueur()->hasObjet(O_CANNE)>1) {

                        // Possède bouteille
                        if (gpJeu->getJoueur()->hasBouteille(2)) {

                            // Possède la canne à pêche niveau 3
                            if (gpJeu->getJoueur()->hasObjet(O_CANNE)>2) {

                                // Possède coeur
                                if (gpJeu->getJoueur()->getCoeur(27)) {
                                    if (gpJeu->getJoueur()->hasObjet(O_POISSONS)>1) {
                                        id=500; 
                                        chercheText();
                                        break;
                                    }

                                    // A attrapé plus de 30 poissons
                                    if (gpJeu->getJoueur()->nbPoissons()>=30) {
                                        id=498; 
                                        chercheText();
                                        break;
                                    }

                                    tmp = 30-gpJeu->getJoueur()->nbPoissons(); os << tmp;
                                    texte = (this->*getTextByLangFunc)(1158, os.str())+os.str()+(this->*getTextByLangFunc)(1159, os.str());
                                    break;
                                }

                                // A attrapé plus de 25 poissons
                                if (gpJeu->getJoueur()->nbPoissons()>=25) {
                                    id=496; 
                                    chercheText();
                                    break;
                                }

                                tmp = 25-gpJeu->getJoueur()->nbPoissons(); os << tmp;
                                texte = (this->*getTextByLangFunc)(1155, os.str())+os.str()+(this->*getTextByLangFunc)(1156, os.str());
                                break;
                            }

                            // A attrapé plus de 20 poissons
                            if (gpJeu->getJoueur()->nbPoissons()>=20) {
                                id=493; 
                                chercheText();
                                break;
                            }

                            tmp = 20-gpJeu->getJoueur()->nbPoissons(); os << tmp;
                            texte = (this->*getTextByLangFunc)(1151, os.str())+os.str()+(this->*getTextByLangFunc)(1152, os.str());
                            break;
                        }
                        
                        // A attrapé plus de 15 poissons
                        if (gpJeu->getJoueur()->nbPoissons()>=15) {
                            id=491; 
                            chercheText();
                            break;
                        }

                        tmp = 15-gpJeu->getJoueur()->nbPoissons(); os << tmp;
                        texte = (this->*getTextByLangFunc)(1148, os.str())+os.str()+(this->*getTextByLangFunc)(1149, os.str());
                        break;
                    }

                    // A attrapé plus de 10 poissons
                    if (gpJeu->getJoueur()->nbPoissons()>=10) {
                        id=488; 
                        chercheText();
                        break;
                    }

                    // A attrapé moins de 10 poissons
                    tmp = 10-gpJeu->getJoueur()->nbPoissons(); os << tmp;
                    texte = (this->*getTextByLangFunc)(1144, os.str())+os.str()+(this->*getTextByLangFunc)(1145, os.str());
                    break;
                }
                
                // A attrapé plus de 5 poissons
                if (gpJeu->getJoueur()->nbPoissons()>=5) {
                    id=479; chercheText();
                    break;
                }

                // A attrapé moins de 5 poissons
                tmp = 5-gpJeu->getJoueur()->nbPoissons();
                os << tmp;
                if (tmp > 1) texte = (this->*getTextByLangFunc)(1132, os.str())+os.str()+(this->*getTextByLangFunc)(1133, os.str());
                else texte = (this->*getTextByLangFunc)(1134, os.str()); break;    
                break;
            }
            
            if (gpJeu->getJoueur()->getAvancement() == PARLE_PECHE) {id=460; chercheText();break;}
            gpJeu->getJoueur()->setAvancement(PARLE_PECHE);
            texte = (this->*getTextByLangFunc)(1111, os.str()); idsuiv = 459; break;
        case 459 : texte = (this->*getTextByLangFunc)(1112, os.str()); idsuiv=460; break;
        case 460 : texte = (this->*getTextByLangFunc)(1113, os.str()); idsuiv=461; break;
        case 461 : texte = (this->*getTextByLangFunc)(1114, os.str()); idsuiv=463;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=75; break;
        case 462 : texte = (this->*getTextByLangFunc)(1115, os.str()); idsuiv=464; break;
        case 463 : texte = (this->*getTextByLangFunc)(1116, os.str()); break;
        case 464 : 
            texte = (this->*getTextByLangFunc)(1117, os.str()); idsuiv=466; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<5) idsuiv=75; break;
        case 465 : texte = (this->*getTextByLangFunc)(1118, os.str()); idsuiv=467; break;
        case 466 : texte = (this->*getTextByLangFunc)(1119, os.str()); break;
        case 467 : texte = (this->*getTextByLangFunc)(1120, os.str()); idsuiv=469;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<2) idsuiv=75; break;
        case 468 : texte = (this->*getTextByLangFunc)(1121, os.str()); idsuiv=470; break;
        case 469 : texte = (this->*getTextByLangFunc)(1122, os.str()); break;
        case 470 : texte = (this->*getTextByLangFunc)(1123, os.str()); idsuiv=472;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<1) idsuiv=75; break;
        case 471 : texte = (this->*getTextByLangFunc)(1124, os.str()); idsuiv=473; break;
        case 472 : texte = (this->*getTextByLangFunc)(1125, os.str()); break;
        case 473 : texte = (this->*getTextByLangFunc)(1126, os.str()); idsuiv=475; break;
        case 474 : texte = (this->*getTextByLangFunc)(1127, os.str()); idsuiv=476; break;
        case 475 : texte = (this->*getTextByLangFunc)(1128, os.str()); break;
        case 476 : texte = (this->*getTextByLangFunc)(1129, os.str()); break;
#ifdef __vita__
        case 477 : texte = (this->*getTextByLangFunc)(1130, os.str()); break;
#else
        case 477 : texte = (this->*getTextByLangFunc)(1131, os.str()); break;
#endif
        case 478 : 
            if (gpJeu->getJoueur()->hasObjet(O_POISSONS)) {id=487; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=5) {id=479; chercheText();break;}
            tmp = 5-gpJeu->getJoueur()->nbPoissons();
            os << tmp;
            if (tmp > 1) texte = (this->*getTextByLangFunc)(1132, os.str())+os.str()+(this->*getTextByLangFunc)(1133, os.str());
            else texte = (this->*getTextByLangFunc)(1134, os.str()); break;
        case 479 : texte = (this->*getTextByLangFunc)(1135, os.str()); idsuiv=480; break;
        case 480 : texte = (this->*getTextByLangFunc)(1136, os.str()); idsuiv=481; break;
        case 481 : texte = (this->*getTextByLangFunc)(1137, os.str()); idsuiv=482; break;
        case 482 : texte = (this->*getTextByLangFunc)(1138, os.str()); idsuiv=483; break;
        case 483 : texte = (this->*getTextByLangFunc)(1139, os.str()); idsuiv=484; break;
#ifdef __vita__
        case 484 : texte = (this->*getTextByLangFunc)(1140, os.str()); idsuiv=485; break;
#else
        case 484 : texte = (this->*getTextByLangFunc)(1141, os.str()); idsuiv=485; break;
#endif
        case 485 : texte = (this->*getTextByLangFunc)(1142, os.str()); break;
        case 486 : texte = (this->*getTextByLangFunc)(1143, os.str()); break;
        case 487 :
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)>1) {id=490; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=10) {id=488; chercheText();break;}
            tmp = 10-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = (this->*getTextByLangFunc)(1144, os.str())+os.str()+(this->*getTextByLangFunc)(1145, os.str());
            break;
        case 488 : texte = (this->*getTextByLangFunc)(1146, os.str()); break;
        case 489 : texte = (this->*getTextByLangFunc)(1147, os.str()); break;
        case 490 : 
            if (gpJeu->getJoueur()->hasBouteille(2)) {id=492; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=15) {id=491; chercheText();break;}
            tmp = 15-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = (this->*getTextByLangFunc)(1148, os.str())+os.str()+(this->*getTextByLangFunc)(1149, os.str());
            break;
        case 491 : texte = (this->*getTextByLangFunc)(1150, os.str()); break;
        case 492 : 
            if (gpJeu->getJoueur()->hasObjet(O_CANNE)>2) {id=495; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=20) {id=493; chercheText();break;}
            tmp = 20-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = (this->*getTextByLangFunc)(1151, os.str())+os.str()+(this->*getTextByLangFunc)(1152, os.str());
            break;
        case 493 : texte = (this->*getTextByLangFunc)(1153, os.str()); break;
        case 494 : texte = (this->*getTextByLangFunc)(1154, os.str()); break;
        case 495 : 
            if (gpJeu->getJoueur()->getCoeur(27)) {id=497; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=25) {id=496; chercheText();break;}
            tmp = 25-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = (this->*getTextByLangFunc)(1155, os.str())+os.str()+(this->*getTextByLangFunc)(1156, os.str());
            break;
        case 496 : texte = (this->*getTextByLangFunc)(1157, os.str()); break;
        case 497 : 
            if (gpJeu->getJoueur()->hasObjet(O_POISSONS)>1) {id=500; chercheText();break;}
            if (gpJeu->getJoueur()->nbPoissons()>=30) {id=498; chercheText();break;}
            tmp = 30-gpJeu->getJoueur()->nbPoissons(); os << tmp;
            texte = (this->*getTextByLangFunc)(1158, os.str())+os.str()+(this->*getTextByLangFunc)(1159, os.str());
            break;
        case 498 : texte = (this->*getTextByLangFunc)(1160, os.str()); break;
        case 499 : texte = (this->*getTextByLangFunc)(1161, os.str()); break;
        case 500 : texte = (this->*getTextByLangFunc)(1162, os.str()); break;
        case 501 : texte = (this->*getTextByLangFunc)(1163, os.str()); 
            if (gpJeu->getJoueur()->hasObjet(O_POISSONS)) idsuiv=503; else idsuiv=502; break;
        case 502 : texte = (this->*getTextByLangFunc)(1164, os.str()); break;
        case 503 : texte = (this->*getTextByLangFunc)(1165, os.str()); break;
        case 504 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>1) {id=511; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==1 
            && gpJeu->getJoueur()->getObjet()==7) {id=505; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1166, os.str()); 
            buffer = (this->*getTextByLangFunc)(1167, os.str()); break;
        case 505 : texte = (this->*getTextByLangFunc)(1168, os.str()); idsuiv=506; break;
        case 506 : texte = (this->*getTextByLangFunc)(1169, os.str()); idsuiv=508; break;
        case 507 : texte = (this->*getTextByLangFunc)(1170, os.str()); idsuiv=509; break;
        case 508 : texte = (this->*getTextByLangFunc)(1171, os.str()); buffer=(this->*getTextByLangFunc)(1172, os.str()); break;
        case 509 : texte = (this->*getTextByLangFunc)(1173, os.str()); break;
        case 510 : texte = (this->*getTextByLangFunc)(1174, os.str()); break;
        case 511 : texte = (this->*getTextByLangFunc)(1175, os.str()); break;
        case 512 : 
            if (!gpJeu->getJoueur()->hasObjet(O_CANNE)) texte = (this->*getTextByLangFunc)(1176, os.str());
            else {texte = (this->*getTextByLangFunc)(1177, os.str()); idsuiv=513;} break;
        case 513 : texte = (this->*getTextByLangFunc)(1178, os.str()); idsuiv=517; break;
        case 514 : texte = (this->*getTextByLangFunc)(1179, os.str()); idsuiv=518; break;
        case 515 : texte = (this->*getTextByLangFunc)(1180, os.str()); idsuiv=519; break;
        case 516 : texte = (this->*getTextByLangFunc)(1181, os.str()); idsuiv=520; break;
        case 517 : texte = (this->*getTextByLangFunc)(1182, os.str()); break;
        case 518 : texte = (this->*getTextByLangFunc)(1183, os.str()); 
            buffer=(this->*getTextByLangFunc)(1184, os.str()); break;
        case 519 : texte = (this->*getTextByLangFunc)(1185, os.str()); break;
        case 520 : texte = (this->*getTextByLangFunc)(1186, os.str()); break;
        case 521 : 
            if (!gpJeu->getJoueur()->hasObjet(O_POISSONS)) texte = (this->*getTextByLangFunc)(1187, os.str()); 
            else texte = (this->*getTextByLangFunc)(1188, os.str()); break;
        case 522 :
            if (gpJeu->getJoueur()->getAvancement()==PARLE_GARS_MINE_SALOON) {id=523; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_BARMAN_SALOON
            && gpJeu->getJoueur()->getAvancement()<DETTE_PAYEE) {id=528; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1189, os.str()); break;
        case 523 : texte = (this->*getTextByLangFunc)(1190, os.str()); idsuiv=524; break;
        case 524 : texte = (this->*getTextByLangFunc)(1191, os.str()); idsuiv=75; break;
        case 525 : texte = (this->*getTextByLangFunc)(1192, os.str()); idsuiv=526; break;
        case 526 : texte = (this->*getTextByLangFunc)(1193, os.str()); buffer=(this->*getTextByLangFunc)(1194, os.str()); idsuiv=527; break;
        case 527 : texte = (this->*getTextByLangFunc)(1195, os.str()); break;
        case 528 : 
            if (gpJeu->getJoueur()->getTroc(M_ROC_GIVRE)>0) {id=529; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1196, os.str()); break;
        case 529 : texte = (this->*getTextByLangFunc)(1197, os.str()); idsuiv=530; break;
        case 530 : texte = (this->*getTextByLangFunc)(1198, os.str()); idsuiv=533; break;
        case 531 : texte = (this->*getTextByLangFunc)(1199, os.str()); idsuiv=532; break;
        case 532 : texte = (this->*getTextByLangFunc)(1200, os.str()); break;
        case 533 : texte = (this->*getTextByLangFunc)(1201, os.str()); break;
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
            texte = (this->*getTextByLangFunc)(1202, os.str()); break;
        case 535 : texte = (this->*getTextByLangFunc)(1203, os.str()); idsuiv=536; break;
        case 536 : texte = (this->*getTextByLangFunc)(1204, os.str()); idsuiv=537; break;
        case 537 : texte = (this->*getTextByLangFunc)(1205, os.str()); break;
        case 538 : texte = (this->*getTextByLangFunc)(1206, os.str()); idsuiv=539; break;
        case 539 : texte = (this->*getTextByLangFunc)(1207, os.str()); break;
        case 540 : texte = (this->*getTextByLangFunc)(1208, os.str()); break;
        case 541 : texte = (this->*getTextByLangFunc)(1209, os.str()); break;
        case 542 : texte = (this->*getTextByLangFunc)(1210, os.str()); idsuiv=543; break;
        case 543 : texte = (this->*getTextByLangFunc)(1211, os.str()); break;
        case 544 : texte = (this->*getTextByLangFunc)(1212, os.str()); break;
        case 545 : texte = (this->*getTextByLangFunc)(1213, os.str()); break;
        case 546 : texte = (this->*getTextByLangFunc)(1214, os.str()); buffer=(this->*getTextByLangFunc)(1215, os.str()); break;
        case 547 : texte = (this->*getTextByLangFunc)(1216, os.str()); break;
        case 548 : texte = (this->*getTextByLangFunc)(1217, os.str()); break;
        case 549 : texte = (this->*getTextByLangFunc)(1218, os.str()); break;
        case 550 : texte = (this->*getTextByLangFunc)(1219, os.str()); break;
        case 551 : 
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())==0) idsuiv=552;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>0) idsuiv=553;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())==0) idsuiv=559;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>0) idsuiv=564;
            texte = (this->*getTextByLangFunc)(1220, os.str()); break;
        case 552 : texte = (this->*getTextByLangFunc)(1221, os.str()); break;
        case 553 : texte = (this->*getTextByLangFunc)(1222, os.str()); idsuiv=554; break;
        case 554 : texte = (this->*getTextByLangFunc)(1223, os.str()); idsuiv=555; break;
        case 555 : 
            int g;
            int gmax;
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()>gpJeu->getJoueur()->getRubisMax()-2) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+(this->*getTextByLangFunc)(1224, os.str())+os2.str()+(this->*getTextByLangFunc)(1225, os.str()); idsuiv=558; break;
        case 556 : 
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+(this->*getTextByLangFunc)(1226, os.str())+os2.str()+(this->*getTextByLangFunc)(1227, os.str()); idsuiv=76; break;
        case 557 : texte = (this->*getTextByLangFunc)(1228, os.str()); break;
        case 558 : texte = (this->*getTextByLangFunc)(1229, os.str()); break;
        case 559 : texte = (this->*getTextByLangFunc)(1230, os.str()); idsuiv=560; break;
        case 560 : texte = (this->*getTextByLangFunc)(1231, os.str()); idsuiv=561; break;
        case 561 : 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()>gpJeu->getJoueur()->getRubisMax()-4) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/4);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*4);
            texte = os.str()+(this->*getTextByLangFunc)(1232, os.str())+os2.str()+(this->*getTextByLangFunc)(1233, os.str()); idsuiv=563; break;
        case 562 : 
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getRubisMax()-(gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()))/4);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*4);
            texte = os.str()+(this->*getTextByLangFunc)(1234, os.str())+os2.str()+(this->*getTextByLangFunc)(1235, os.str()); idsuiv=76; break;
        case 563 : texte = (this->*getTextByLangFunc)(1236, os.str()); break;
        case 564 : texte = (this->*getTextByLangFunc)(1237, os.str()); idsuiv=560; break;
        case 565 : texte = (this->*getTextByLangFunc)(1238, os.str()); idsuiv=554; break;
        case 566 : texte = (this->*getTextByLangFunc)(1239, os.str()); idsuiv=76; break;
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
            texte = (this->*getTextByLangFunc)(1240, os.str()); 
            buffer = (this->*getTextByLangFunc)(1241, os.str()); break;
        case 568 : texte = (this->*getTextByLangFunc)(1242, os.str()); idsuiv=569; break;
        case 569 : texte = (this->*getTextByLangFunc)(1243, os.str()); idsuiv=571; break;
        case 570 : texte = (this->*getTextByLangFunc)(1244, os.str()); idsuiv=572; break;
        case 571 : texte = (this->*getTextByLangFunc)(1245, os.str()); break;
        case 572 : texte = (this->*getTextByLangFunc)(1246, os.str()); break;
        case 573 : texte = (this->*getTextByLangFunc)(1247, os.str()); break;
        case 574 : texte = (this->*getTextByLangFunc)(1248, os.str()); break;
        case 575 : texte = (this->*getTextByLangFunc)(1249, os.str()); idsuiv=576; break;
        case 576 : texte = (this->*getTextByLangFunc)(1250, os.str()); idsuiv=578; break;
        case 577 : texte = (this->*getTextByLangFunc)(1251, os.str()); idsuiv=572; break;
        case 578 : texte = (this->*getTextByLangFunc)(1252, os.str()); break;
        case 579 : texte = (this->*getTextByLangFunc)(1253, os.str()); break;
        case 580 : texte = (this->*getTextByLangFunc)(1254, os.str()); idsuiv=581; break;
        case 581 : texte = (this->*getTextByLangFunc)(1255, os.str()); idsuiv=583; break;
        case 582 : texte = (this->*getTextByLangFunc)(1256, os.str()); idsuiv=572; break;
        case 583 : texte = (this->*getTextByLangFunc)(1257, os.str()); break;
        case 584 : texte = (this->*getTextByLangFunc)(1258, os.str()); break;
        case 585 : texte = (this->*getTextByLangFunc)(1259, os.str()); idsuiv=586; break;
        case 586 : texte = (this->*getTextByLangFunc)(1260, os.str()); idsuiv=588; break;
        case 587 : texte = (this->*getTextByLangFunc)(1261, os.str()); idsuiv=572; break;
        case 588 : texte = (this->*getTextByLangFunc)(1262, os.str()); break;
        case 589 : 
            if (gpJeu->getJoueur()->hasObjet(O_ENCYCL)) {id=593; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1263, os.str()); idsuiv=590; break;
        case 590 : texte = (this->*getTextByLangFunc)(1264, os.str()); idsuiv=591; break;
#ifdef __vita__
        case 591 : texte = (this->*getTextByLangFunc)(1265, os.str()); idsuiv=592; break;
#else
        case 591 : texte = (this->*getTextByLangFunc)(1266, os.str()); idsuiv=592; break;
#endif
        case 592 : 
            switch (gpJeu->getEpoque()) {
                case T_PASSE : os<<(this->*getTextByLangFunc)(1267, os.str()); break;
                case T_PRESENT : os<<(this->*getTextByLangFunc)(1268, os.str()); break;
                case T_FUTUR : os<<(this->*getTextByLangFunc)(1269, os.str()); break;
            }
            texte = (this->*getTextByLangFunc)(1270, os.str())+os.str()+(this->*getTextByLangFunc)(1271, os.str()); break;
        case 593 :
            g = gpJeu->getJoueur()->getSolde();
            if (g == 0) {id=595; chercheText();break;}
            switch (gpJeu->getEpoque()) {
                case T_PASSE : os<<(g/4)<<(this->*getTextByLangFunc)(1272, os.str()); break;
                case T_PRESENT : os<<g<<(this->*getTextByLangFunc)(1273, os.str()); break;
                case T_FUTUR : os<<(g/2)<<(this->*getTextByLangFunc)(1274, os.str()); break;
            }
            if (gpJeu->getEpoque() == T_FUTUR 
            && gpJeu->getJoueur()->getGanonMax() == 0) {id=1368; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1275, os.str())+os.str()+(this->*getTextByLangFunc)(1276, os.str()); break;
        case 594 : 
            g = gpJeu->getJoueur()->getSolde();
            switch (gpJeu->getEpoque()) {
                case T_PASSE : os<<(g/4)<<(this->*getTextByLangFunc)(1277, os.str()); break;
                case T_PRESENT : os<<g<<(this->*getTextByLangFunc)(1278, os.str()); break;
                case T_FUTUR : os<<(g/2)<<(this->*getTextByLangFunc)(1279, os.str()); break;
            }
            texte = (this->*getTextByLangFunc)(1280, os.str())+os.str()+(this->*getTextByLangFunc)(1281, os.str()); break;
        case 595 : texte=(this->*getTextByLangFunc)(1282, os.str()); break;
        case 596 : 
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<2) idsuiv=597;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())==0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>1) idsuiv=598;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<2) idsuiv=603;
            if ((gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece())>0 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>1) idsuiv=608;
            texte = (this->*getTextByLangFunc)(1283, os.str()); break;
        case 597 : texte = (this->*getTextByLangFunc)(1284, os.str()); break;
        case 598 : texte = (this->*getTextByLangFunc)(1285, os.str()); idsuiv=599; break;
        case 599 : texte = (this->*getTextByLangFunc)(1286, os.str()); idsuiv=600; break;
        case 600 : 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()==gpJeu->getJoueur()->getGanonMax()) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+(this->*getTextByLangFunc)(1287, os.str())+os2.str()+(this->*getTextByLangFunc)(1288, os.str()); idsuiv=602; break;
        case 601 : 
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+(this->*getTextByLangFunc)(1289, os.str())+os2.str()+(this->*getTextByLangFunc)(1290, os.str()); idsuiv=76; break;
        case 602 : texte = (this->*getTextByLangFunc)(1291, os.str()); break;
        case 603 : texte = (this->*getTextByLangFunc)(1292, os.str()); idsuiv=604; break;
        case 604 : texte = (this->*getTextByLangFunc)(1293, os.str()); idsuiv=605; break;
        case 605 : 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()>gpJeu->getJoueur()->getGanonMax()-2) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+(this->*getTextByLangFunc)(1294, os.str())+os2.str()+(this->*getTextByLangFunc)(1295, os.str()); idsuiv=607; break;
        case 606 : 
            g=gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece();
            gmax = ((gpJeu->getJoueur()->getGanonMax()-(gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()))/2);
            if (g > gmax) g=gmax;
            os << g; os2 << (g*2);
            texte = os.str()+(this->*getTextByLangFunc)(1296, os.str())+os2.str()+(this->*getTextByLangFunc)(1297, os.str()); idsuiv=76; break;
        case 607 : texte = (this->*getTextByLangFunc)(1298, os.str()); break;
        case 608 : texte = (this->*getTextByLangFunc)(1299, os.str()); idsuiv=604; break;
        case 609 : texte = (this->*getTextByLangFunc)(1300, os.str()); idsuiv=599; break;
        case 610 : texte = (this->*getTextByLangFunc)(1301, os.str()); idsuiv=76; break;
        case 611 : texte = (this->*getTextByLangFunc)(1302, os.str()); break;
        case 612 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>6) {id=619; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==6 
            && gpJeu->getJoueur()->getObjet()==7) {id=613; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1303, os.str()); 
            buffer = (this->*getTextByLangFunc)(1304, os.str()); break;
        case 613 : texte = (this->*getTextByLangFunc)(1305, os.str()); idsuiv=614; break;
        case 614 : texte = (this->*getTextByLangFunc)(1306, os.str()); idsuiv=616; break;
        case 615 : texte = (this->*getTextByLangFunc)(1307, os.str()); idsuiv=617; break;
        case 616 : texte = (this->*getTextByLangFunc)(1308, os.str()); break;
        case 617 : texte = (this->*getTextByLangFunc)(1309, os.str()); break;
        case 618 : texte = (this->*getTextByLangFunc)(1310, os.str()); break;
        case 619 : texte = (this->*getTextByLangFunc)(1311, os.str()); break;
        case 620 : 
            if (gpJeu->getJoueur()->getTroc(M_POIVRON)>-1) {id=624; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1312, os.str()); idsuiv=621; break;
        case 621 : texte = (this->*getTextByLangFunc)(1313, os.str()); idsuiv=622; break;
        case 622 : texte = (this->*getTextByLangFunc)(1314, os.str()); break;
        case 623 : texte = (this->*getTextByLangFunc)(1315, os.str()); break;
        case 624 : texte = (this->*getTextByLangFunc)(1316, os.str()); break;
        case 625 : 
            if (gpJeu->getJoueur()->hasObjet(O_GRAPPIN)) {id=635; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1317, os.str()); idsuiv=626; break;
        case 626 : texte = (this->*getTextByLangFunc)(1318, os.str()); idsuiv=627; break;
        case 627 : texte = (this->*getTextByLangFunc)(1319, os.str()); idsuiv=628; break;
        case 628 : texte = (this->*getTextByLangFunc)(1320, os.str()); idsuiv=629; break;
        case 629 : texte = (this->*getTextByLangFunc)(1321, os.str()); idsuiv=630; break;
        case 630 : texte = (this->*getTextByLangFunc)(1322, os.str()); idsuiv=631; break;
        case 631 : texte = (this->*getTextByLangFunc)(1323, os.str()); idsuiv=632; break;
        case 632 : texte = (this->*getTextByLangFunc)(1324, os.str()); idsuiv=633; break;
        case 633 : texte = (this->*getTextByLangFunc)(1325, os.str()); break;
        case 634 : texte = (this->*getTextByLangFunc)(1326, os.str()); break;
        case 635 : 
            if (gpJeu->getJoueur()->getCoffre(3,29)) {
                id=636; 
                if (gpJeu->getJoueur()->getTroc(M_POIVRON)>-1) {
                    id=637; 
                    if (gpJeu->getJoueur()->hasObjet(O_CLE_TEMPS)) {
                        id=638; 
                        if (gpJeu->getJoueur()->getAvancement()>SAGES_GROTTE) {
                            id=639; 
                            if (gpJeu->getJoueur()->hasMelodie(1)) {
                                id=640; 
                                texte = (this->*getTextByLangFunc)(1332, os.str());
                                break;
                            }
                            texte = (this->*getTextByLangFunc)(1331, os.str());
                            break;
                        }
                        
                        texte = (this->*getTextByLangFunc)(1330, os.str());
                        break;
                    }
                    
                    texte = (this->*getTextByLangFunc)(1329, os.str()); 
                    break;
                }

                texte = (this->*getTextByLangFunc)(1328, os.str());
                break;
            }

            texte = (this->*getTextByLangFunc)(1327, os.str()); break;
        case 636 : 
            if (gpJeu->getJoueur()->getTroc(M_POIVRON)>-1) {id=637; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1328, os.str()); break;
        case 637 : 
            if (gpJeu->getJoueur()->hasObjet(O_CLE_TEMPS)) {id=638; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1329, os.str()); break;
        case 638 : 
            if (gpJeu->getJoueur()->getAvancement()>SAGES_GROTTE) {id=639; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1330, os.str()); break;
        case 639 :
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=640; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1331, os.str()); break;
        case 640 : texte = (this->*getTextByLangFunc)(1332, os.str()); break;
        case 641 : texte = (this->*getTextByLangFunc)(1333, os.str());
            if (!gpJeu->getJoueur()->hasObjet(O_ARC)) {id=373; chercheText(); break;}
            else if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10) idsuiv=75; break;
        case 642 : texte = (this->*getTextByLangFunc)(1334, os.str()); break;
        case 643 : texte = (this->*getTextByLangFunc)(1335, os.str());
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=372; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<15) idsuiv=75; break;
        case 644 : texte = (this->*getTextByLangFunc)(1336, os.str()); break;
        case 645 : texte = (this->*getTextByLangFunc)(1337, os.str());
            if (gpJeu->getJoueur()->getVie() + gpJeu->getJoueur()->getBoostVie() >= gpJeu->getJoueur()->getVieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<4) idsuiv=75; break;
        case 646 : texte = (this->*getTextByLangFunc)(1338, os.str()); break;
        case 647 : texte = (this->*getTextByLangFunc)(1339, os.str());
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<8) idsuiv=75; break;
        case 648 : texte = (this->*getTextByLangFunc)(1340, os.str()); break;
        case 649 : texte = (this->*getTextByLangFunc)(1341, os.str());
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<16) idsuiv=75; break;
        case 650 : texte = (this->*getTextByLangFunc)(1342, os.str()); break;
        case 651 : 
            if (gpJeu->getJoueur()->getGanonMax()>0) {
                if (gpJeu->getJoueur()->getCafe()>-1) {
                    id=653; 
                    chercheText(); 
                    break;
                }
                
                texte = (this->*getTextByLangFunc)(1344, os.str()); 
                idsuiv=653;
                break;
            }
            
            texte = (this->*getTextByLangFunc)(1343, os.str()); 
            break;
        case 652 :
            if (gpJeu->getJoueur()->getCafe()>-1) {
                id=653; 
                chercheText(); 
                break;
            }
            
            texte = (this->*getTextByLangFunc)(1344, os.str()); 
            idsuiv=653; 
            break;
        case 653 : 
            if (gpJeu->getJoueur()->getChargeCafe()==-1 
            && gpJeu->getMonde()->motifValue(6*16,8*16)==1005) {
                if (gpJeu->getJoueur()->getCafe()>1) {
                    id=654+gpJeu->getJoueur()->getCafe(); 
                    chercheText(); 
                    break;
                }

                id = 655;
                texte = (this->*getTextByLangFunc)(1347, os.str());
                break;
            }

            if (gpJeu->getJoueur()->getCafe()>=17) {
                id=672; 
                if (gpJeu->getJoueur()->getGemme(173)) {
                    id=673; 
                    texte = (this->*getTextByLangFunc)(1365, os.str()); 
                    break;
                }
                
                texte = (this->*getTextByLangFunc)(1364, os.str()); break;
                break;
            }

            texte = (this->*getTextByLangFunc)(1345, os.str()); 
            idsuiv=654; 
            break;
        case 654 : texte = (this->*getTextByLangFunc)(1346, os.str()); break;
        case 655 : 
            if (gpJeu->getJoueur()->getCafe()>1) {
                id=654+gpJeu->getJoueur()->getCafe(); chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1347, os.str()); break;
        case 656 : texte = (this->*getTextByLangFunc)(1348, os.str()); break;
        case 657 : texte = (this->*getTextByLangFunc)(1349, os.str()); break;
        case 658 : texte = (this->*getTextByLangFunc)(1350, os.str()); break;
        case 659 : texte = (this->*getTextByLangFunc)(1351, os.str()); break;
        case 660 : texte = (this->*getTextByLangFunc)(1352, os.str()); break;
        case 661 : texte = (this->*getTextByLangFunc)(1353, os.str()); break;
        case 662 : texte = (this->*getTextByLangFunc)(1354, os.str()); break;
        case 663 : texte = (this->*getTextByLangFunc)(1355, os.str()); break;
        case 664 : texte = (this->*getTextByLangFunc)(1356, os.str()); break;
        case 665 : texte = (this->*getTextByLangFunc)(1357, os.str()); break;
        case 666 : texte = (this->*getTextByLangFunc)(1358, os.str()); break;
        case 667 : texte = (this->*getTextByLangFunc)(1359, os.str()); break;
        case 668 : texte = (this->*getTextByLangFunc)(1360, os.str()); break;
        case 669 : texte = (this->*getTextByLangFunc)(1361, os.str()); break;
        case 670 : texte = (this->*getTextByLangFunc)(1362, os.str()); break;
        case 671 : texte = (this->*getTextByLangFunc)(1363, os.str()); break;
        case 672 : 
            if (gpJeu->getJoueur()->getGemme(173)) {id=673; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1364, os.str()); break;
        case 673 : texte = (this->*getTextByLangFunc)(1365, os.str()); break;
        case 674 :
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1366, os.str()); 
            idsuiv=675; break;
        case 675 : texte = (this->*getTextByLangFunc)(1367, os.str()); idsuiv=678; break;
        case 676 : texte = (this->*getTextByLangFunc)(1368, os.str()); 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=374;
            else idsuiv=680; break;
        case 677 : texte = (this->*getTextByLangFunc)(1369, os.str()); break;
        case 678 : texte = (this->*getTextByLangFunc)(1370, os.str()); 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<40) idsuiv=75; break;
        case 679 : texte = (this->*getTextByLangFunc)(1371, os.str()); break;
        case 680 : texte = (this->*getTextByLangFunc)(1372, os.str());
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<25) idsuiv=75; break;
        case 681 : texte = (this->*getTextByLangFunc)(1373, os.str()); break;
        case 682 : 
            if (gpJeu->getJoueur()->getCoffre(15,14)) {id=683; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1374, os.str()); break;
        case 683 :
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>=4) {id=685; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1375, os.str()); buffer = (this->*getTextByLangFunc)(1376, os.str()); break;
        case 684 : texte = (this->*getTextByLangFunc)(1377, os.str()); break;
        case 685 : texte = (this->*getTextByLangFunc)(1378, os.str()); break;
        case 686 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>4) {id=693; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==4 
            && gpJeu->getJoueur()->getObjet()==15) {id=687; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1379, os.str()); buffer = (this->*getTextByLangFunc)(1380, os.str()); break;
        case 687 : texte = (this->*getTextByLangFunc)(1381, os.str()); idsuiv=688; break;
        case 688 : texte = (this->*getTextByLangFunc)(1382, os.str()); idsuiv=690; break;
        case 689 : texte = (this->*getTextByLangFunc)(1383, os.str()); idsuiv=691; break;
        case 690 : texte = (this->*getTextByLangFunc)(1384, os.str()); break;
        case 691 : texte = (this->*getTextByLangFunc)(1385, os.str()); break;
        case 692 : texte = (this->*getTextByLangFunc)(1386, os.str()); break;
        case 693 : texte = (this->*getTextByLangFunc)(1387, os.str()); break;
        case 694 :
            if (gpJeu->getJoueur()->getGanonMax() > 0) {id=696; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1388, os.str()); buffer = (this->*getTextByLangFunc)(1389, os.str()); break;
        case 695 : texte = (this->*getTextByLangFunc)(1390, os.str()); break;
        case 696 : texte = (this->*getTextByLangFunc)(1391, os.str()); break;
        case 697 : 
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())<2 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<4) idsuiv=698;
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())<2 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>3) idsuiv=699;
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>1 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())<4) idsuiv=704;
            if ((gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon())>1 
            && (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis())>3) idsuiv=709;
            texte = (this->*getTextByLangFunc)(1392, os.str()); break;
        case 698 : texte = (this->*getTextByLangFunc)(1393, os.str()); break;
        case 699 : texte = (this->*getTextByLangFunc)(1394, os.str()); idsuiv=700; break;
        case 700 : texte = (this->*getTextByLangFunc)(1395, os.str()); idsuiv=701; break;
        case 701 : 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()==gpJeu->getJoueur()->getPieceMax()) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            while (g%4 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*4;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/4);
            texte = os.str()+(this->*getTextByLangFunc)(1396, os.str())+os2.str()+(this->*getTextByLangFunc)(1397, os.str()); idsuiv=703; break;
        case 702 : 
            g=gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis();
            while (g%4 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*4;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/4);
            texte = os.str()+(this->*getTextByLangFunc)(1398, os.str())+os2.str()+(this->*getTextByLangFunc)(1399, os.str()); idsuiv=76; break;
        case 703 : texte = (this->*getTextByLangFunc)(1400, os.str()); break;
        case 704 : texte = (this->*getTextByLangFunc)(1401, os.str()); idsuiv=705; break;
        case 705 : texte = (this->*getTextByLangFunc)(1402, os.str()); idsuiv=706; break;
        case 706 : 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()==gpJeu->getJoueur()->getPieceMax()) {id=557; chercheText();break;}
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+(this->*getTextByLangFunc)(1403, os.str())+os2.str()+(this->*getTextByLangFunc)(1404, os.str()); idsuiv=708; break;
        case 707 : 
            g=gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon();
            if (g%2 != 0) g--;
            gmax = (gpJeu->getJoueur()->getPieceMax()-(gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()))*2;
            if (g > gmax) g=gmax;
            os << g; os2 << (g/2);
            texte = os.str()+(this->*getTextByLangFunc)(1405, os.str())+os2.str()+(this->*getTextByLangFunc)(1406, os.str()); idsuiv=76; break;
        case 708 : texte = (this->*getTextByLangFunc)(1407, os.str()); break;
        case 709 : texte = (this->*getTextByLangFunc)(1408, os.str()); idsuiv=700; break;
        case 710 : texte = (this->*getTextByLangFunc)(1409, os.str()); idsuiv=705; break;
        case 711 : texte = (this->*getTextByLangFunc)(1410, os.str()); idsuiv=76; break;
        case 712 :
            if (gpJeu->getJoueur()->getCoffre(15,22)) {id=717; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1411, os.str()); idsuiv=713; break;
        case 713 : texte = (this->*getTextByLangFunc)(1412, os.str()); idsuiv=714; break;
        case 714 : texte = (this->*getTextByLangFunc)(1413, os.str()); idsuiv=715; break;
        case 715 : texte = (this->*getTextByLangFunc)(1414, os.str()); idsuiv=716; break;
        case 716 : texte = (this->*getTextByLangFunc)(1415, os.str()); idsuiv=717; break;
        case 717 : texte = (this->*getTextByLangFunc)(1416, os.str()); idsuiv=718; break;
        case 718 : texte = (this->*getTextByLangFunc)(1417, os.str()); break;
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
            texte = (this->*getTextByLangFunc)(1418, os.str()); 
            buffer = (this->*getTextByLangFunc)(1419, os.str()); break;
        case 720 : texte = (this->*getTextByLangFunc)(1420, os.str()); buffer = (this->*getTextByLangFunc)(1421, os.str()); idsuiv=721; break;
        case 721 : texte = (this->*getTextByLangFunc)(1422, os.str()); idsuiv=723; break;
        case 722 : texte = (this->*getTextByLangFunc)(1423, os.str()); idsuiv=724; break;
        case 723 : texte = (this->*getTextByLangFunc)(1424, os.str()); break;
        case 724 : texte = (this->*getTextByLangFunc)(1425, os.str()); break;
        case 725 : texte = (this->*getTextByLangFunc)(1426, os.str()); break;
        case 726 : texte = (this->*getTextByLangFunc)(1427, os.str()); break;
        case 727 : texte = (this->*getTextByLangFunc)(1428, os.str()); idsuiv=728; break;
        case 728 : texte = (this->*getTextByLangFunc)(1429, os.str()); idsuiv=730; break;
        case 729 : texte = (this->*getTextByLangFunc)(1430, os.str()); idsuiv=731; break;
        case 730 : texte = (this->*getTextByLangFunc)(1431, os.str()); break;
        case 731 : texte = (this->*getTextByLangFunc)(1432, os.str()); break;
        case 732 : texte = (this->*getTextByLangFunc)(1433, os.str()); break;
        case 733 : texte = (this->*getTextByLangFunc)(1434, os.str()); idsuiv=734; break;
        case 734 : texte = (this->*getTextByLangFunc)(1435, os.str()); idsuiv=736; break;
        case 735 : texte = (this->*getTextByLangFunc)(1436, os.str()); idsuiv=737; break;
        case 736 : texte = (this->*getTextByLangFunc)(1437, os.str()); break;
        case 737 : texte = (this->*getTextByLangFunc)(1438, os.str()); break;
        case 738 : texte = (this->*getTextByLangFunc)(1439, os.str()); break;
        case 739 : 
            if (gpJeu->getJoueur()->getEpee()>2) {id=748; chercheText();break;}
            if (gpJeu->getJoueur()->getEpee()==0) {id=745; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1440, os.str()); idsuiv=740; break;
        case 740 : texte = (this->*getTextByLangFunc)(1441, os.str()); idsuiv=742; break;
        case 741 : texte = (this->*getTextByLangFunc)(1442, os.str()); idsuiv=743; break;
        case 742 : texte = (this->*getTextByLangFunc)(1443, os.str()); break;
        case 743 : texte = (this->*getTextByLangFunc)(1444, os.str()); break;
        case 744 : texte = (this->*getTextByLangFunc)(1445, os.str()); break;
        case 745 : texte = (this->*getTextByLangFunc)(1446, os.str()); break;
        case 746 :
            if (gpJeu->getJoueur()->getEpee()) {id=748; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1447, os.str()); break;
        case 747 : texte = (this->*getTextByLangFunc)(1448, os.str()); break;
        case 748 : texte = (this->*getTextByLangFunc)(1449, os.str()); break;
        case 749 : texte = (this->*getTextByLangFunc)(1450, os.str()); break;
        case 750 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1451, os.str());
            if (!gpJeu->getJoueur()->hasObjet(O_ARC)) {id=373; chercheText(); break;}
            else if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<5) idsuiv=75; break;
        case 751 : texte = (this->*getTextByLangFunc)(1452, os.str()); break;
        case 752 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1453, os.str());
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=372; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<10) idsuiv=75; break;
        case 753 : texte = (this->*getTextByLangFunc)(1454, os.str()); break;
        case 754 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1455, os.str());
            if (gpJeu->getJoueur()->getVie() + gpJeu->getJoueur()->getBoostVie() >= gpJeu->getJoueur()->getVieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<1) idsuiv=75; break;
        case 755 : texte = (this->*getTextByLangFunc)(1456, os.str()); break;
        case 756 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1457, os.str());
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<3) idsuiv=75; break;
        case 757 : texte = (this->*getTextByLangFunc)(1458, os.str()); break;
        case 758 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1459, os.str());
            if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() >= gpJeu->getJoueur()->getMagieMax()) {id=374; chercheText(); break;}
            else if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<6) idsuiv=75; break;
        case 759 : texte = (this->*getTextByLangFunc)(1460, os.str()); break;
        case 760 : texte = (this->*getTextByLangFunc)(1461, os.str()); break;
        case 761 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1462, os.str()); break;
        case 762 : texte = (this->*getTextByLangFunc)(1463, os.str()); break;
        case 763 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1
            && gpJeu->getJoueur()->hasBouteille(3)!=1) {id=408; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1464, os.str()); 
            idsuiv=764; break;
        case 764 : texte = (this->*getTextByLangFunc)(1465, os.str()); idsuiv=767; break;
        case 765 : texte = (this->*getTextByLangFunc)(1466, os.str()); 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=374;
            else idsuiv=769; break;
        case 766 : texte = (this->*getTextByLangFunc)(1467, os.str()); break;
        case 767 : texte = (this->*getTextByLangFunc)(1468, os.str()); 
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<15) idsuiv=75; break;
        case 768 : texte = (this->*getTextByLangFunc)(1469, os.str()); break;
        case 769 : texte = (this->*getTextByLangFunc)(1470, os.str());
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<10) idsuiv=75; break;
        case 770 : texte = (this->*getTextByLangFunc)(1471, os.str()); break;
        case 771 : texte = (this->*getTextByLangFunc)(1472, os.str()); break;
        case 772 : texte = (this->*getTextByLangFunc)(1473, os.str()); break;
        case 773 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1474, os.str()); idsuiv=774; break; 
        case 774 :
            texte =(this->*getTextByLangFunc)(1475, os.str());
            buffer = (this->*getTextByLangFunc)(1476, os.str()); break;
        case 775 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1477, os.str()); break;
        case 776 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1478, os.str()); break;
        case 777 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1479, os.str()); break;
        case 778 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>5) {id=785; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==5 
            && gpJeu->getJoueur()->getObjet()==15) {id=779; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1480, os.str()); break;
        case 779 : texte = (this->*getTextByLangFunc)(1481, os.str()); idsuiv=780; break;
        case 780 : texte = (this->*getTextByLangFunc)(1482, os.str()); idsuiv=782; break;
        case 781 : texte = (this->*getTextByLangFunc)(1483, os.str()); idsuiv=783; break;
        case 782 : texte = (this->*getTextByLangFunc)(1484, os.str()); break;
        case 783 : texte = (this->*getTextByLangFunc)(1485, os.str()); break;
        case 784 : texte = (this->*getTextByLangFunc)(1486, os.str()); break;
        case 785 : texte = (this->*getTextByLangFunc)(1487, os.str()); break;
        case 786 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1488, os.str()); break;
        case 787 :
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->getCoffre(15,23)<3) {id=788; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1489, os.str()); break;
        case 788 : 
            texte = (this->*getTextByLangFunc)(1490, os.str()); idsuiv=789; break;
        case 789 : 
            texte = (this->*getTextByLangFunc)(1491, os.str());
            if (gpJeu->getJoueur()->getPiece() + gpJeu->getJoueur()->getBoostPiece()<1) idsuiv=75; break;
        case 790 : texte = (this->*getTextByLangFunc)(1492, os.str()); idsuiv=76; break;
        case 791 : 
            if (gpJeu->getJoueur()->getCoffre(15,23)>0) {id=792; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1493, os.str()); break;
        case 792 : 
            if (gpJeu->getJoueur()->getCoffre(15,23)>1) {id=793; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1494, os.str()); break;
        case 793 : texte = (this->*getTextByLangFunc)(1495, os.str()); break;
        case 794 : texte = (this->*getTextByLangFunc)(1496, os.str()); break;
        case 795 : texte = (this->*getTextByLangFunc)(1497, os.str()); break;
        case 796 : texte = (this->*getTextByLangFunc)(1498, os.str()); break;
        case 797 : texte = (this->*getTextByLangFunc)(1499, os.str()); break;
        case 798 : texte = (this->*getTextByLangFunc)(1500, os.str()); break;
        case 799 : texte = (this->*getTextByLangFunc)(1501, os.str()); break;
        case 800 : texte = (this->*getTextByLangFunc)(1502, os.str()); break;
        case 801 : texte = (this->*getTextByLangFunc)(1503, os.str()); idsuiv=802; break;
        case 802 : texte = (this->*getTextByLangFunc)(1504, os.str()); idsuiv=803; break;
        case 803 : texte = (this->*getTextByLangFunc)(1505, os.str()); idsuiv=804; break;
        case 804 : texte = (this->*getTextByLangFunc)(1506, os.str()); idsuiv=805; break;
        case 805 : texte = (this->*getTextByLangFunc)(1507, os.str()); idsuiv=806; break;
        case 806 : texte = (this->*getTextByLangFunc)(1508, os.str()); break;
        case 807 : 
            if (gpJeu->getJoueur()->getGemme(178)) {id=816; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1509, os.str()); idsuiv=808; break;
        case 808 : 

            // Quête des loups
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=1) {
                if (g>=2) {
                    if (g>=50) {
                        if (g>=80) {
                            if (g>=100) {
                                if (g>100) {
                                    texte = (this->*getTextByLangFunc)(1519, os.str()); 
                                    idsuiv=815; 
                                    break;
                                }

                                texte = (this->*getTextByLangFunc)(1518, os.str()); 
                                break;
                            }
                            os << g;
                            texte = (this->*getTextByLangFunc)(1516, os.str())+os.str()+(this->*getTextByLangFunc)(1517, os.str()); 
                            break;
                        }
                        os << g;
                        texte = (this->*getTextByLangFunc)(1514, os.str())+os.str()+(this->*getTextByLangFunc)(1515, os.str());
                        break;
                    }
                    os << g;
                    texte = (this->*getTextByLangFunc)(1512, os.str())+os.str()+(this->*getTextByLangFunc)(1513, os.str()); 
                    break;
                }

                texte = (this->*getTextByLangFunc)(1511, os.str());
                break;
            }

            texte = (this->*getTextByLangFunc)(1510, os.str()); 
            break;
        case 809 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=2) {id=810; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1511, os.str()); break;
        case 810 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=50) {id=811; chercheText(); break;}
            os << g;
            texte = (this->*getTextByLangFunc)(1512, os.str())+os.str()+(this->*getTextByLangFunc)(1513, os.str()); break;
        case 811 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=80) {id=812; chercheText(); break;}
            os << g;
            texte = (this->*getTextByLangFunc)(1514, os.str())+os.str()+(this->*getTextByLangFunc)(1515, os.str()); break;
        case 812 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>=100) {id=813; chercheText(); break;}
            os << g;
            texte = (this->*getTextByLangFunc)(1516, os.str())+os.str()+(this->*getTextByLangFunc)(1517, os.str()); break;
        case 813 : 
            g=gpJeu->getJoueur()->nbLoups();
            if (g>100) {id=814; chercheText(); break;}
            texte = (this->*getTextByLangFunc)(1518, os.str()); break;
        case 814 : 
            texte = (this->*getTextByLangFunc)(1519, os.str()); idsuiv=815; break;
        case 815 : texte = (this->*getTextByLangFunc)(1520, os.str()); break;
        case 816 : texte = (this->*getTextByLangFunc)(1521, os.str()); break;
        case 817 : texte = (this->*getTextByLangFunc)(1522, os.str()); break;
        case 818 : texte = (this->*getTextByLangFunc)(1523, os.str()); break;
        case 819 : texte = (this->*getTextByLangFunc)(1524, os.str()); break;
        case 820 : texte = (this->*getTextByLangFunc)(1525, os.str()); break;
        case 821 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)>5) {id=828; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC2)==5 
            && gpJeu->getJoueur()->getObjet()==7) {id=822; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1526, os.str()); break;
        case 822 : texte = (this->*getTextByLangFunc)(1527, os.str()); idsuiv=823; break;
        case 823 : texte = (this->*getTextByLangFunc)(1528, os.str()); idsuiv=825; break;
        case 824 : texte = (this->*getTextByLangFunc)(1529, os.str()); idsuiv=826; break;
        case 825 : texte = (this->*getTextByLangFunc)(1530, os.str()); break;
        case 826 : texte = (this->*getTextByLangFunc)(1531, os.str()); break;
        case 827 : texte = (this->*getTextByLangFunc)(1532, os.str()); break;
        case 828 : texte = (this->*getTextByLangFunc)(1533, os.str()); break;
        case 829 : texte = (this->*getTextByLangFunc)(1534, os.str()); idsuiv=830; break;
        case 830 : texte = (this->*getTextByLangFunc)(1535, os.str()); buffer = (this->*getTextByLangFunc)(1536, os.str()); break;
        case 831 : texte = (this->*getTextByLangFunc)(1537, os.str()); break;
        case 832 : 
            if (gpJeu->getJoueur()->getCoffre(15,26)) {id=839; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==6 
            && gpJeu->getJoueur()->getObjet()==3) {id=833; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1538, os.str()); break;
        case 833 : texte = (this->*getTextByLangFunc)(1539, os.str()); idsuiv=834; break;
        case 834 : texte = (this->*getTextByLangFunc)(1540, os.str()); idsuiv=836; break;
        case 835 : texte = (this->*getTextByLangFunc)(1541, os.str()); idsuiv=837; break;
        case 836 : texte = (this->*getTextByLangFunc)(1542, os.str()); break;
        case 837 : texte = (this->*getTextByLangFunc)(1543, os.str()); idsuiv=834; break;
        case 838 : texte = (this->*getTextByLangFunc)(1544, os.str()); break;
        case 839 : texte = (this->*getTextByLangFunc)(1545, os.str()); break;
        case 840 : texte = (this->*getTextByLangFunc)(1546, os.str()); break;
        case 841 : texte = (this->*getTextByLangFunc)(1547, os.str());
            buffer = (this->*getTextByLangFunc)(1548, os.str()); break;
        case 842 : texte = (this->*getTextByLangFunc)(1549, os.str()); break;
        case 843 : texte = (this->*getTextByLangFunc)(1550, os.str()); break;
        case 844 : texte = (this->*getTextByLangFunc)(1551, os.str()); idsuiv=845; break;
        case 845 : texte = (this->*getTextByLangFunc)(1552, os.str()); idsuiv=846; break;
        case 846 : texte = (this->*getTextByLangFunc)(1553, os.str()); break;
        case 847 : texte = (this->*getTextByLangFunc)(1554, os.str()); idsuiv=848; break;
        case 848 : texte = (this->*getTextByLangFunc)(1555, os.str()); idsuiv=849; break;
        case 849 : texte = (this->*getTextByLangFunc)(1556, os.str()); break;
        case 850 : texte = (this->*getTextByLangFunc)(1557, os.str()); idsuiv=851; break; 
        case 851 : texte = (this->*getTextByLangFunc)(1558, os.str()); break;
        case 852 : texte = (this->*getTextByLangFunc)(1559, os.str()); break;
        case 853 : 
            if (gpJeu->getJoueur()->getGemme(182)) {id=854; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>0) {id=855; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1560, os.str()); break;
        case 854 : texte = (this->*getTextByLangFunc)(1561, os.str()); break;
        case 855 : texte = (this->*getTextByLangFunc)(1562, os.str()); idsuiv=856; break;
        case 856 : texte = (this->*getTextByLangFunc)(1563, os.str()); break;
        case 857 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>4) {id=864; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==4 
            && gpJeu->getJoueur()->getObjet()==3) {id=858; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1564, os.str()); break;
        case 858 : texte = (this->*getTextByLangFunc)(1565, os.str()); idsuiv=859; break;
        case 859 : texte = (this->*getTextByLangFunc)(1566, os.str()); idsuiv=861; break;
        case 860 : texte = (this->*getTextByLangFunc)(1567, os.str()); idsuiv=862; break;
        case 861 : texte = (this->*getTextByLangFunc)(1568, os.str()); break;
        case 862 : texte = (this->*getTextByLangFunc)(1569, os.str()); break;
        case 863 : texte = (this->*getTextByLangFunc)(1570, os.str()); break;
        case 864 : texte = (this->*getTextByLangFunc)(1571, os.str()); break;
        case 865 : texte = (this->*getTextByLangFunc)(1572, os.str()); break;
        case 866 :
            if (gpJeu->getJoueur()->getCoffre(15,27)==12) {id=886; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(15,27)) {id=868; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==7 
            && gpJeu->getJoueur()->getObjet()==11) {id=867; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1573, os.str()); break;
        case 867 : texte = (this->*getTextByLangFunc)(1574, os.str()); break;
        case 868 : texte = (this->*getTextByLangFunc)(1575, os.str()); break;
        case 869 : texte = (this->*getTextByLangFunc)(1576, os.str()); buffer=(this->*getTextByLangFunc)(1577, os.str()); break;
        case 870 : texte = (this->*getTextByLangFunc)(1578, os.str()); break;
        case 871 : texte = (this->*getTextByLangFunc)(1579, os.str()); idsuiv=872; break;
        case 872 : texte = (this->*getTextByLangFunc)(1580, os.str()); break;
        case 873 : texte = (this->*getTextByLangFunc)(1581, os.str()); break;
        case 874 : texte = (this->*getTextByLangFunc)(1582, os.str()); idsuiv=875; break;
        case 875 : texte = (this->*getTextByLangFunc)(1583, os.str()); break;
        case 876 : texte = (this->*getTextByLangFunc)(1584, os.str()); idsuiv=877; break;
        case 877 : texte = (this->*getTextByLangFunc)(1585, os.str()); break;
        case 878 : texte = (this->*getTextByLangFunc)(1586, os.str()); break;
        case 879 : texte = (this->*getTextByLangFunc)(1587, os.str()); break;
        case 880 : texte = (this->*getTextByLangFunc)(1588, os.str()); idsuiv=881; break;
        case 881 : texte = (this->*getTextByLangFunc)(1589, os.str()); break;
        case 882 : texte = (this->*getTextByLangFunc)(1590, os.str()); idsuiv=883; break;
        case 883 : texte = (this->*getTextByLangFunc)(1591, os.str()); break;
        case 884 : texte = (this->*getTextByLangFunc)(1592, os.str()); idsuiv=885; break;
        case 885 : texte = (this->*getTextByLangFunc)(1593, os.str()); break;
        case 886 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>7) {id=893; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==7 
            && gpJeu->getJoueur()->getObjet()==11) {id=887; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1594, os.str()); break;
        case 887 : texte = (this->*getTextByLangFunc)(1595, os.str()); idsuiv=888; break;
        case 888 : texte = (this->*getTextByLangFunc)(1596, os.str()); idsuiv=890; break;
        case 889 : texte = (this->*getTextByLangFunc)(1597, os.str()); idsuiv=891; break;
        case 890 : texte = (this->*getTextByLangFunc)(1598, os.str()); buffer=(this->*getTextByLangFunc)(1599, os.str()); break;
        case 891 : texte = (this->*getTextByLangFunc)(1600, os.str()); break;
        case 892 : texte = (this->*getTextByLangFunc)(1601, os.str()); break;
        case 893 : texte = (this->*getTextByLangFunc)(1602, os.str()); break;
        case 894 : 
            if (!gpJeu->getJoueur()->hasObjet(O_LIVRE)) {id=319; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>1) {id=901; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==1 
            && gpJeu->getJoueur()->getObjet()==11) {id=895; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1603, os.str());
            buffer = (this->*getTextByLangFunc)(1604, os.str()); break;
        case 895 : texte = (this->*getTextByLangFunc)(1605, os.str()); idsuiv=896; break;
        case 896 : texte = (this->*getTextByLangFunc)(1606, os.str()); idsuiv=898; break;
        case 897 : texte = (this->*getTextByLangFunc)(1607, os.str()); idsuiv=899; break;
        case 898 : texte = (this->*getTextByLangFunc)(1608, os.str()); break;
        case 899 : texte = (this->*getTextByLangFunc)(1609, os.str()); break;
        case 900 : texte = (this->*getTextByLangFunc)(1610, os.str()); break;
        case 901 : texte = (this->*getTextByLangFunc)(1611, os.str()); break;
        case 902 : 
            if (!gpJeu->getJoueur()->hasObjet(O_OCARINA)) {id=1079; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1612, os.str()); break;
        case 903 : texte = (this->*getTextByLangFunc)(1613, os.str()); break;
        case 904 : texte = (this->*getTextByLangFunc)(1614, os.str()); break;
        case 905 : texte = (this->*getTextByLangFunc)(1615, os.str()); break;
        case 906 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)>5) {id=913; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC1)==5 
            && gpJeu->getJoueur()->getObjet()==3) {id=907; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1616, os.str()); break;
        case 907 : texte = (this->*getTextByLangFunc)(1617, os.str()); idsuiv=908; break;
        case 908 : texte = (this->*getTextByLangFunc)(1618, os.str()); idsuiv=910; break;
        case 909 : texte = (this->*getTextByLangFunc)(1619, os.str()); idsuiv=911; break;
        case 910 : texte = (this->*getTextByLangFunc)(1620, os.str()); buffer=(this->*getTextByLangFunc)(1621, os.str()); break;
        case 911 : texte = (this->*getTextByLangFunc)(1622, os.str()); break;
        case 912 : texte = (this->*getTextByLangFunc)(1623, os.str()); break;
        case 913 : texte = (this->*getTextByLangFunc)(1624, os.str()); break;
        case 914 : 
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)>5) {id=921; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==5 
            && gpJeu->getJoueur()->getObjet()==11) {id=915; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1625, os.str()); break;
        case 915 : texte = (this->*getTextByLangFunc)(1626, os.str()); idsuiv=916; break;
        case 916 : texte = (this->*getTextByLangFunc)(1627, os.str()); idsuiv=918; break;
        case 917 : texte = (this->*getTextByLangFunc)(1628, os.str()); idsuiv=919; break;
        case 918 : texte = (this->*getTextByLangFunc)(1629, os.str()); break;
        case 919 : texte = (this->*getTextByLangFunc)(1630, os.str()); break;
        case 920 : texte = (this->*getTextByLangFunc)(1631, os.str()); break;
        case 921 : texte = (this->*getTextByLangFunc)(1632, os.str()); break;
        case 922 : texte = (this->*getTextByLangFunc)(1633, os.str()); break;
        case 923 : texte = (this->*getTextByLangFunc)(1634, os.str()); break;
        case 924 : texte = (this->*getTextByLangFunc)(1635, os.str()); idsuiv=925; break;
        case 925 : texte = (this->*getTextByLangFunc)(1636, os.str()); idsuiv=926; break;
        case 926 : texte = (this->*getTextByLangFunc)(1637, os.str()); break;
        case 927 : texte = (this->*getTextByLangFunc)(1638, os.str()); break;
        case 928 : texte = (this->*getTextByLangFunc)(1639, os.str()); break;
        case 929 : texte = (this->*getTextByLangFunc)(1640, os.str()); break;
        case 930 : texte = (this->*getTextByLangFunc)(1641, os.str()); break;
        case 931 : texte = (this->*getTextByLangFunc)(1642, os.str()); break;
        case 932 : texte = (this->*getTextByLangFunc)(1643, os.str()); break;
        case 933 : texte = (this->*getTextByLangFunc)(1644, os.str()); break;
        case 934 : texte = (this->*getTextByLangFunc)(1645, os.str()); break;
        case 935 : texte = (this->*getTextByLangFunc)(1646, os.str()); break;
        case 936 : texte = (this->*getTextByLangFunc)(1647, os.str()); break;
        case 937 : texte = (this->*getTextByLangFunc)(1648, os.str()); break;
        case 938 : 
            if (gpJeu->getAudio()->isSpecial()) {
            texte = (this->*getTextByLangFunc)(1649, os.str()); break;}
            texte = (this->*getTextByLangFunc)(1650, os.str()); break;
        case 939 : texte = (this->*getTextByLangFunc)(1651, os.str()); break;
        case 940 : texte = (this->*getTextByLangFunc)(1652, os.str()); break;
        case 941 : texte = (this->*getTextByLangFunc)(1653, os.str()); break;
        
#ifdef __vita__
        case 942 : texte = (this->*getTextByLangFunc)(1654, os.str()); break;
#else
        case 942 : texte = (this->*getTextByLangFunc)(1655, os.str()); break;
#endif
        case 943 : texte = (this->*getTextByLangFunc)(1656, os.str()); break;
        case 944 : texte = (this->*getTextByLangFunc)(1657, os.str()); break;
        case 945 : texte = (this->*getTextByLangFunc)(1658, os.str()); break;
        case 946 : texte = (this->*getTextByLangFunc)(1659, os.str()); break;
#ifdef __vita__
        case 947 : texte = (this->*getTextByLangFunc)(1660, os.str()); break;
#else
        case 947 : texte = (this->*getTextByLangFunc)(1661, os.str()); break;
#endif
        case 948 : 
            if (gpJeu->getZone()==47) {id=949; chercheText();break;}
            if (gpJeu->getZone()==48) {id=950; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1662, os.str()); break;
        case 949 : texte = (this->*getTextByLangFunc)(1663, os.str()); break;
        case 950 : texte = (this->*getTextByLangFunc)(1664, os.str()); break;
        case 951 : texte = (this->*getTextByLangFunc)(1665, os.str()); break;
        case 952 : 
            if (gpJeu->getJoueur()->hasObjet(O_GANTS)) {id=954; chercheText();break;}
            if (gpJeu->getJoueur()->getExplore(1,16,4)) {id=953; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1666, os.str()); break;
        case 953 : texte = (this->*getTextByLangFunc)(1667, os.str()); break;
        case 954 : texte = (this->*getTextByLangFunc)(1668, os.str()); break;
        case 955 : texte = (this->*getTextByLangFunc)(1669, os.str()); break;
        case 956 : texte = (this->*getTextByLangFunc)(1670, os.str()); break;
        case 957 : 
            if (gpJeu->getJoueur()->getCoffre(3,29)) {id=960; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1671, os.str()); idsuiv=958; break;
        case 958 : texte = (this->*getTextByLangFunc)(1672, os.str()); idsuiv=959; break;
        case 959 : texte = (this->*getTextByLangFunc)(1673, os.str()); idsuiv=960; break;
        case 960 : texte = (this->*getTextByLangFunc)(1674, os.str()); break;
        case 961 : texte = (this->*getTextByLangFunc)(1675, os.str()); break;
        case 962 : texte = (this->*getTextByLangFunc)(1676, os.str()); break;
        case 963 : texte = (this->*getTextByLangFunc)(1677, os.str()); break;
        case 964 : texte = (this->*getTextByLangFunc)(1678, os.str()); break;
        case 965 : texte = (this->*getTextByLangFunc)(1679, os.str()); break;
        case 966 : texte = (this->*getTextByLangFunc)(1680, os.str()); break;
        case 967 : texte = (this->*getTextByLangFunc)(1681, os.str()); break;
        case 968 : texte = (this->*getTextByLangFunc)(1682, os.str()); break;
        case 969 : texte = (this->*getTextByLangFunc)(1683, os.str()); break;
        case 970 : texte = (this->*getTextByLangFunc)(1684, os.str()); break;
        case 971 : texte = (this->*getTextByLangFunc)(1685, os.str()); break;
        case 972 : texte = (this->*getTextByLangFunc)(1686, os.str()); break;
        case 973 : texte = (this->*getTextByLangFunc)(1687, os.str()); idsuiv=974; break;
        case 974 : texte = (this->*getTextByLangFunc)(1688, os.str()); idsuiv=975; break;
        case 975 : texte = (this->*getTextByLangFunc)(1689, os.str()); idsuiv=976; break;
        case 976 : texte = (this->*getTextByLangFunc)(1690, os.str()); idsuiv=977; break;
        case 977 : texte = (this->*getTextByLangFunc)(1691, os.str()); idsuiv=978; break;
        case 978 : texte = (this->*getTextByLangFunc)(1692, os.str()); idsuiv=979; break;
        case 979 : texte = (this->*getTextByLangFunc)(1693, os.str()); idsuiv=980; break;
        case 980 : texte = (this->*getTextByLangFunc)(1694, os.str()); break;
        case 981 : texte = (this->*getTextByLangFunc)(1695, os.str()); idsuiv=982; break;
        case 982 : texte = (this->*getTextByLangFunc)(1696, os.str()); break;
        case 983 : texte = (this->*getTextByLangFunc)(1697, os.str()); idsuiv=984; break;
        case 984 : texte = (this->*getTextByLangFunc)(1698, os.str()); idsuiv=985; break;
        case 985 : texte = (this->*getTextByLangFunc)(1699, os.str()); idsuiv=986; break;
        case 986 : texte = (this->*getTextByLangFunc)(1700, os.str()); idsuiv=987; break;
        case 987 : texte = (this->*getTextByLangFunc)(1701, os.str()); idsuiv=988; break;
        case 988 : texte = (this->*getTextByLangFunc)(1702, os.str()); idsuiv=989; break;
        case 989 : texte = (this->*getTextByLangFunc)(1703, os.str()); idsuiv=990; break;
        case 990 : texte = (this->*getTextByLangFunc)(1704, os.str()); idsuiv=991; break;
        case 991 : texte = (this->*getTextByLangFunc)(1705, os.str()); idsuiv=992; break;
        case 992 : texte = (this->*getTextByLangFunc)(1706, os.str()); idsuiv=993; break;
        case 993 : texte = (this->*getTextByLangFunc)(1707, os.str()); idsuiv=994; break;
        case 994 : texte = (this->*getTextByLangFunc)(1708, os.str()); idsuiv=995; break;
        case 995 : texte = (this->*getTextByLangFunc)(1709, os.str()); idsuiv=996; break;
        case 996 : texte = (this->*getTextByLangFunc)(1710, os.str()); idsuiv=997; break;
        case 997 : texte = (this->*getTextByLangFunc)(1711, os.str()); idsuiv=998; break;
        case 998 : texte = (this->*getTextByLangFunc)(1712, os.str()); break;
        case 999 : texte = (this->*getTextByLangFunc)(1713, os.str()); break;
        case 1000: texte = (this->*getTextByLangFunc)(1714, os.str()); break;
        case 1001: texte = (this->*getTextByLangFunc)(1715, os.str()); break;
        case 1002: texte = (this->*getTextByLangFunc)(1716, os.str()); idsuiv=1003; break;
        case 1003: texte = (this->*getTextByLangFunc)(1717, os.str()); break;
        case 1004: 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_PALAIS) {id=1010; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1718, os.str()); break;
        case 1005: 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_ZELDA_PALAIS) {id=1010; chercheText();break;}
            if (gpJeu->getJoueur()->getRubisMax()) {id=1013; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_PALAIS) {id=1007; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1719, os.str()); idsuiv=1006; break; 
        case 1006: texte = (this->*getTextByLangFunc)(1720, os.str()); break;
        case 1007: texte = (this->*getTextByLangFunc)(1721, os.str()); break;
        case 1008:
            if (gpJeu->getJoueur()->getRubisMax()) {id=1010; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()<PARLE_GARDE_PALAIS) {id=1004; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_RESERVE) {id=1009; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1722, os.str()); break;
        case 1009: texte = (this->*getTextByLangFunc)(1723, os.str()); break;
        case 1010: texte = (this->*getTextByLangFunc)(1724, os.str()); break;
        case 1011: texte = (this->*getTextByLangFunc)(1725, os.str()); break;
        case 1012: texte = (this->*getTextByLangFunc)(1726, os.str()); break;
        case 1013: texte = (this->*getTextByLangFunc)(1727, os.str()); break;
        case 1014: texte = (this->*getTextByLangFunc)(1728, os.str()); break;
        case 1015: texte = (this->*getTextByLangFunc)(1729, os.str()); break;
        case 1016: 
            if (gpJeu->getJoueur()->getAvancement()>=PASSAGE_TROUVE) {id=1031; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=ZELDA_SOUS_SOL) {id=1025; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_ZELDA_PALAIS) {id=1019; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1730, os.str()); idsuiv=1017; break;
        case 1017: texte = (this->*getTextByLangFunc)(1731, os.str()); idsuiv=1018; break;
        case 1018: texte = (this->*getTextByLangFunc)(1732, os.str()); idsuiv=1019; break;
        case 1019: texte = (this->*getTextByLangFunc)(1733, os.str()); break;
        case 1020: 
            if (gpJeu->getJoueur()->getAvancement()<PARLE_ZELDA_PALAIS) {id=1004; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_CH_FORTE) {id=1010; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1734, os.str()); break;
        case 1021: texte = (this->*getTextByLangFunc)(1735, os.str()); break;
        case 1022: 
            if (gpJeu->getJoueur()->getAvancement()>=PARLE_GARDE_SOUS_SOL) {id=1023; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1736, os.str()); break;
        case 1023: texte = (this->*getTextByLangFunc)(1737, os.str()); break;
        case 1024: texte = (this->*getTextByLangFunc)(1738, os.str()); idsuiv=1025; break;
#ifdef __vita__
        case 1025: texte = (this->*getTextByLangFunc)(1739, os.str()); break;
#else
        case 1025: texte = (this->*getTextByLangFunc)(1740, os.str()); break;
#endif
        case 1026: texte = (this->*getTextByLangFunc)(1741, os.str()); break;
        case 1027: texte = (this->*getTextByLangFunc)(1742, os.str()); break;
        case 1028: 
            if (gpJeu->getJoueur()->getAvancement()>=RIDEAUX_REPERES) {id=1030; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1743, os.str()); break;
        case 1029: texte = (this->*getTextByLangFunc)(1744, os.str()); break;
        case 1030: texte = (this->*getTextByLangFunc)(1745, os.str()); break;
        case 1031: texte = (this->*getTextByLangFunc)(1746, os.str()); break;
        case 1032: texte = (this->*getTextByLangFunc)(1747, os.str()); break;
        case 1033: texte = (this->*getTextByLangFunc)(1748, os.str()); break;
#ifdef __vita__
        case 1034: texte = (this->*getTextByLangFunc)(1749, os.str()); break;
        case 1035: texte = (this->*getTextByLangFunc)(1750, os.str()); break;
#else
        case 1034: texte = (this->*getTextByLangFunc)(1751, os.str()); break;
        case 1035: texte = (this->*getTextByLangFunc)(1752, os.str()); break;
#endif
        case 1036: texte = (this->*getTextByLangFunc)(1753, os.str()); break;
        case 1037: texte = (this->*getTextByLangFunc)(1754, os.str()); break;
        case 1038: texte = (this->*getTextByLangFunc)(1755, os.str()); break;
        case 1039: texte = (this->*getTextByLangFunc)(1756, os.str()); break;
        case 1040: texte = (this->*getTextByLangFunc)(1757, os.str()); break;
        case 1041: texte = (this->*getTextByLangFunc)(1758, os.str()); break;
        case 1042: texte = (this->*getTextByLangFunc)(1759, os.str()); break;
        case 1043: texte = (this->*getTextByLangFunc)(1760, os.str()); break;
        case 1044: texte = (this->*getTextByLangFunc)(1761, os.str()); break;
        case 1045: texte = (this->*getTextByLangFunc)(1762, os.str()); break;
        case 1046: texte = (this->*getTextByLangFunc)(1763, os.str()); idsuiv=1047; break;
        case 1047: texte = (this->*getTextByLangFunc)(1764, os.str()); break;
        case 1048: texte = (this->*getTextByLangFunc)(1765, os.str()); break;
        case 1049: texte = (this->*getTextByLangFunc)(1766, os.str()); break;
        case 1050: texte = (this->*getTextByLangFunc)(1767, os.str()); break;
        case 1051: texte = (this->*getTextByLangFunc)(1768, os.str()); break;
        case 1052: texte = (this->*getTextByLangFunc)(1769, os.str()); break;
        case 1053: texte = (this->*getTextByLangFunc)(1770, os.str()); break;
        case 1054: texte = (this->*getTextByLangFunc)(1771, os.str()); break;
        case 1055: texte = (this->*getTextByLangFunc)(1772, os.str()); break;
        case 1056: texte = (this->*getTextByLangFunc)(1773, os.str()); break;
        case 1057: texte = (this->*getTextByLangFunc)(1774, os.str()); break;
        case 1058: texte = (this->*getTextByLangFunc)(1775, os.str()); break;
        case 1059: 
            if (gpJeu->getJoueur()->getAvancement()>=MOT_DE_PASSE_DONNE) {id=1062; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()==MOT_DE_PASSE_CONNU) {id=1061; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1776, os.str()); break;
        case 1060: 
            if (gpJeu->getJoueur()->getAvancement()>=MULTIPASSE_UTILISE) {id=1062; chercheText();break;}
            if (gpJeu->getJoueur()->getAvancement()>=MULTIPASS) {id=1063; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1777, os.str()); break;
        case 1061: texte = (this->*getTextByLangFunc)(1778, os.str()); break;
        case 1062: texte = (this->*getTextByLangFunc)(1779, os.str()); break;
        case 1063: texte = (this->*getTextByLangFunc)(1780, os.str()); break;
        case 1064: 
            if (gpJeu->getJoueur()->getAvancement()>=MOT_DE_PASSE_CONNU) {id=1070; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1781, os.str()); idsuiv=1065; break;
        case 1065: texte = (this->*getTextByLangFunc)(1782, os.str()); idsuiv=1066; break;
        case 1066: texte = (this->*getTextByLangFunc)(1783, os.str()); idsuiv=1067; break;
        case 1067: texte = (this->*getTextByLangFunc)(1784, os.str()); idsuiv=1068; break;
        case 1068: texte = (this->*getTextByLangFunc)(1785, os.str()); idsuiv=1069; break;
        case 1069: texte = (this->*getTextByLangFunc)(1786, os.str()); idsuiv=1070; break;
        case 1070: texte = (this->*getTextByLangFunc)(1787, os.str()); break;
        case 1071: texte = (this->*getTextByLangFunc)(1788, os.str()); idsuiv=1072; break;
        case 1072: 
            gpJeu->getAudio()->stopSpecial();
            texte = (this->*getTextByLangFunc)(1789, os.str()); idsuiv=1073; break;
        case 1073: texte = (this->*getTextByLangFunc)(1790, os.str()); break;
        case 1074: 
            if (gpJeu->getJoueur()->isLapin()) {id=1073; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)>6) {id=1078; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC4)==6 
            && gpJeu->getJoueur()->getObjet()==15) {id=1075; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1791, os.str()); break;
        case 1075: texte = (this->*getTextByLangFunc)(1792, os.str()); idsuiv=1076; break;
        case 1076: texte = (this->*getTextByLangFunc)(1793, os.str()); break;
        case 1077: texte = (this->*getTextByLangFunc)(1794, os.str()); break;
        case 1078: texte = (this->*getTextByLangFunc)(1795, os.str()); break;
        case 1079: texte = (this->*getTextByLangFunc)(1796, os.str()); break;
        case 1080: texte = (this->*getTextByLangFunc)(1797, os.str()); break;
        case 1081: texte = (this->*getTextByLangFunc)(1798, os.str()); break;
        case 1082: texte = (this->*getTextByLangFunc)(1799, os.str()); idsuiv=1083; break;
        case 1083: 
            if (gpJeu->getJoueur()->getEpee()==5 && gpJeu->getJoueur()->hasObjet(O_ARC_OR) < 2) {id=1092; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_TROC3)==4 
            && gpJeu->getJoueur()->getObjet()==11) {id=1085; chercheText();break;}
            if (gpJeu->getJoueur()->getEpee()==5 && gpJeu->getJoueur()->getEnnemi(50)) {id=1112; chercheText();break;}
            if (gpJeu->getJoueur()->getEpee()==5) {id=1095; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1800, os.str()); break;
        case 1084: texte = (this->*getTextByLangFunc)(1801, os.str()); break;
        case 1085: texte = (this->*getTextByLangFunc)(1802, os.str()); idsuiv=1087; break;
        case 1086: texte = (this->*getTextByLangFunc)(1803, os.str()); idsuiv=1088; break;
        case 1087: texte = (this->*getTextByLangFunc)(1804, os.str()); 
            buffer = (this->*getTextByLangFunc)(1805, os.str()); break;
        case 1088: texte = (this->*getTextByLangFunc)(1806, os.str()); break;
        case 1089: texte = (this->*getTextByLangFunc)(1807, os.str()); break;
        case 1090: texte = (this->*getTextByLangFunc)(1808, os.str()); break;
        case 1091: texte = (this->*getTextByLangFunc)(1809, os.str()); break;
        case 1092: texte = (this->*getTextByLangFunc)(1810, os.str()); idsuiv=1093; break;
        case 1093: texte = (this->*getTextByLangFunc)(1811, os.str()); break;
        case 1094: texte = (this->*getTextByLangFunc)(1812, os.str()); break;
        case 1095: texte = (this->*getTextByLangFunc)(1813, os.str()); idsuiv=1096; break;
        case 1096: texte = (this->*getTextByLangFunc)(1814, os.str()); break;
        case 1097: texte = (this->*getTextByLangFunc)(1815, os.str()); break;
        case 1098: texte = (this->*getTextByLangFunc)(1816, os.str()); break;
        case 1099: texte = (this->*getTextByLangFunc)(1817, os.str()); break;
        case 1100: texte = (this->*getTextByLangFunc)(1818, os.str()); idsuiv=1101; break;
        case 1101: texte = (this->*getTextByLangFunc)(1819, os.str()); idsuiv=1102; break;
        case 1102: texte = (this->*getTextByLangFunc)(1820, os.str()); idsuiv=1103; break;
        case 1103: texte = (this->*getTextByLangFunc)(1821, os.str()); idsuiv=1104; break;
        case 1104: texte = (this->*getTextByLangFunc)(1822, os.str()); idsuiv=1105; break;
        case 1105: texte = (this->*getTextByLangFunc)(1823, os.str()); idsuiv=1106; break;
        case 1106: texte = (this->*getTextByLangFunc)(1824, os.str()); idsuiv=1107; break;
        case 1107: texte = (this->*getTextByLangFunc)(1825, os.str()); idsuiv=1108; break;
        case 1108: texte = (this->*getTextByLangFunc)(1826, os.str()); idsuiv=1109; break;
        case 1109: texte = (this->*getTextByLangFunc)(1827, os.str()); break;
        case 1110: texte = (this->*getTextByLangFunc)(1828, os.str()); break;
        case 1111: texte = (this->*getTextByLangFunc)(1829, os.str()); break;
        case 1112: texte = (this->*getTextByLangFunc)(1830, os.str()); break;
        case 1113: texte = (this->*getTextByLangFunc)(1831, os.str()); break;
        case 1114: 
            if (gpJeu->getMonde()->motifValue(69*16,90*16) == 6380) {texte = (this->*getTextByLangFunc)(1832, os.str()); break;}
            texte = (this->*getTextByLangFunc)(1833, os.str()); idsuiv=1117; break;
        case 1115: texte = (this->*getTextByLangFunc)(1834, os.str()); idsuiv=1116; break;
        case 1116: texte = (this->*getTextByLangFunc)(1835, os.str()); break;
        case 1117: 
            if (gpJeu->getMonde()->motifValue(69*16,90*16) != 6380 &&
            gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<10) {id=1118; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1836, os.str()); break;
        case 1118: texte = (this->*getTextByLangFunc)(1837, os.str()); break;
        case 1119: texte = (this->*getTextByLangFunc)(1838, os.str()); break;
        case 1120: texte = (this->*getTextByLangFunc)(1839, os.str()); idsuiv=1122; break;
        case 1121: texte = (this->*getTextByLangFunc)(1840, os.str()); idsuiv=1116; break;
        case 1122: 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<5) {id=1118; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1841, os.str()); idsuiv=1123; break;
        case 1123: texte = (this->*getTextByLangFunc)(1842, os.str()); idsuiv=1124; break;
        case 1124: texte = (this->*getTextByLangFunc)(1843, os.str()); break;
        case 1125: 
            if (gpJeu->getJoueur()->getCoffre(12,1)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1844, os.str()); 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1126: texte = (this->*getTextByLangFunc)(1845, os.str()); break;
        case 1127: texte = (this->*getTextByLangFunc)(1846, os.str()); idsuiv=1116; break;
        case 1128: texte = (this->*getTextByLangFunc)(1847, os.str()); break;
        case 1129: texte = (this->*getTextByLangFunc)(1848, os.str()); break;
        case 1130: texte = (this->*getTextByLangFunc)(1849, os.str()); break;
        case 1131:
            if (gpJeu->getJoueur()->getCoffre(12,2)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1132; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1850, os.str()); 
            buffer=(this->*getTextByLangFunc)(1851, os.str()); 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1132: texte = (this->*getTextByLangFunc)(1852, os.str()); break;
        case 1133: texte = (this->*getTextByLangFunc)(1853, os.str()); idsuiv=1116; break;
        case 1134:
            if (gpJeu->getJoueur()->getCoffre(12,5)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->isTempsVisible()) {id=1135; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1854, os.str()); 
            idsuiv=1126; break;
        case 1135: texte = (this->*getTextByLangFunc)(1855, os.str()); break;
        case 1136:
            if (gpJeu->getJoueur()->getCoffre(12,5)) {id=1128; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1856, os.str()); break;
        case 1137:
            if (gpJeu->getJoueur()->getCle(12,0)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1857, os.str()); 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1138:
            if (gpJeu->getJoueur()->getCoffre(12,4)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1858, os.str()); 
            idsuiv=1139; break;
        case 1139: texte = (this->*getTextByLangFunc)(1859, os.str()); idsuiv=1141; break;
        case 1140: texte = (this->*getTextByLangFunc)(1860, os.str()); idsuiv=1116; break;
        case 1141: texte = (this->*getTextByLangFunc)(1861, os.str()); break;
        case 1142: texte = (this->*getTextByLangFunc)(1862, os.str()); break;
        case 1143:
            if (gpJeu->getJoueur()->getCle(12,1)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 2) {id=1129; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) == 3) {id=1130; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1863, os.str()); 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1144:
            if (gpJeu->getJoueur()->getCoffre(12,3)) {id=1128; chercheText();break;}
            if (gpJeu->getJoueur()->getCoffre(12,13) > 1) {id=1145; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1864, os.str()); 
            if (!gpJeu->getJoueur()->getCoffre(12,13)) idsuiv=1126; break;
        case 1145:
            tmp = gpJeu->getJoueur()->getCoffre(12,13)-2; os << tmp;
            texte = (this->*getTextByLangFunc)(1865, os.str())+os.str()+(this->*getTextByLangFunc)(1866, os.str()); idsuiv=1129; 
            if (gpJeu->getJoueur()->getGanon() + gpJeu->getJoueur()->getBoostGanon()<tmp) {idsuiv=1118;break;}
            break;
        case 1146:
            tmp = gpJeu->getJoueur()->getCoffre(12,13)-2; os << tmp;
            texte = (this->*getTextByLangFunc)(1867, os.str())+os.str()+(this->*getTextByLangFunc)(1868, os.str()); idsuiv=1116; break;
            break;
        case 1147:
            if (gpJeu->getJoueur()->getCle(12,2)) {id=1148; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1869, os.str());
            break;
        case 1148: 
            if (gpJeu->getJoueur()->getCoeur(11)) {id=1149; chercheText();break;}
            texte = (this->*getTextByLangFunc)(1870, os.str()); break;
        case 1149: texte = (this->*getTextByLangFunc)(1871, os.str()); break;
        case 1150: texte = (this->*getTextByLangFunc)(1872, os.str()); idsuiv=1151; break;
        case 1151: texte = (this->*getTextByLangFunc)(1873, os.str()); idsuiv=1152; break;
        case 1152: 
            gpJeu->getJoueur()->setCoffre(12,14,0); // ->nb questions posées
            for (int i = 0; i < MAX_QUIZZ; i++) gpJeu->getJoueur()->setCoffre(12,15+i,0);
            tmp = rand()%MAX_QUIZZ; idsuiv = 1154 + tmp*4;
            gpJeu->getJoueur()->setCoffre(12,15+tmp,1);
            texte = (this->*getTextByLangFunc)(1874, os.str()); 
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
            texte = (this->*getTextByLangFunc)(1875, os.str()); break;
        case 1154: texte = (this->*getTextByLangFunc)(1876, os.str()); idsuiv=1157; break;
        case 1155: texte = (this->*getTextByLangFunc)(1877, os.str()); idsuiv=1156; break;
        case 1156: texte = (this->*getTextByLangFunc)(1878, os.str()); break;
        case 1157: texte = (this->*getTextByLangFunc)(1879, os.str()); break;
        
        case 1158: texte = (this->*getTextByLangFunc)(1880, os.str()); idsuiv=1161; break;
        case 1159: texte = (this->*getTextByLangFunc)(1881, os.str()); idsuiv=1160; break;
        case 1160: texte = (this->*getTextByLangFunc)(1882, os.str()); break;
        case 1161: texte = (this->*getTextByLangFunc)(1883, os.str()); break;
        
        case 1162: texte = (this->*getTextByLangFunc)(1884, os.str()); idsuiv=1165; break;
        case 1163: texte = (this->*getTextByLangFunc)(1885, os.str()); idsuiv=1164; break;
        case 1164: texte = (this->*getTextByLangFunc)(1886, os.str()); break;
        case 1165: texte = (this->*getTextByLangFunc)(1887, os.str()); break;
        
        case 1166: texte = (this->*getTextByLangFunc)(1888, os.str()); idsuiv=1168; break;
        case 1167: texte = (this->*getTextByLangFunc)(1889, os.str()); idsuiv=1169; break;
        case 1168: texte = (this->*getTextByLangFunc)(1890, os.str()); break;
        case 1169: texte = (this->*getTextByLangFunc)(1891, os.str()); break;

        case 1170: 
            tmp = gpJeu->getJoueur()->getMort() + 1; os << tmp;
            texte = (this->*getTextByLangFunc)(1892, os.str())+os.str()+(this->*getTextByLangFunc)(1893, os.str()); idsuiv=1173; break;
        case 1171: 
            tmp = gpJeu->getJoueur()->getMort() + 1; os << tmp;
            texte = (this->*getTextByLangFunc)(1894, os.str())+os.str()+(this->*getTextByLangFunc)(1895, os.str()); idsuiv=1172; break;
        case 1172: 
            tmp = gpJeu->getJoueur()->getMort(); os << tmp;
            texte = (this->*getTextByLangFunc)(1896, os.str())+os.str()+(this->*getTextByLangFunc)(1897, os.str()); break;
        case 1173: 
            tmp = gpJeu->getJoueur()->getMort(); os << tmp;
            texte = (this->*getTextByLangFunc)(1898, os.str())+os.str()+(this->*getTextByLangFunc)(1899, os.str()); break;
            
        case 1174: texte = (this->*getTextByLangFunc)(1900, os.str()); idsuiv=1176; break;
        case 1175: texte = (this->*getTextByLangFunc)(1901, os.str()); idsuiv=1177; break;
        case 1176: texte = (this->*getTextByLangFunc)(1902, os.str()); break;
        case 1177: texte = (this->*getTextByLangFunc)(1903, os.str()); break;
        
        case 1178: texte = (this->*getTextByLangFunc)(1904, os.str()); idsuiv=1180; break;
        case 1179: texte = (this->*getTextByLangFunc)(1905, os.str()); idsuiv=1181; break;
        case 1180: texte = (this->*getTextByLangFunc)(1906, os.str()); break;
        case 1181: texte = (this->*getTextByLangFunc)(1907, os.str()); break;
        
        case 1182: texte = (this->*getTextByLangFunc)(1908, os.str()); idsuiv=1184; break;
        case 1183: texte = (this->*getTextByLangFunc)(1909, os.str()); idsuiv=1185; break;
        case 1184: texte = (this->*getTextByLangFunc)(1910, os.str()); break;
        case 1185: texte = (this->*getTextByLangFunc)(1911, os.str()); break;
        
        case 1186: texte = (this->*getTextByLangFunc)(1912, os.str()); idsuiv=1189; break;
        case 1187: texte = (this->*getTextByLangFunc)(1913, os.str()); idsuiv=1188; break;
        case 1188: texte = (this->*getTextByLangFunc)(1914, os.str()); break;
        case 1189: texte = (this->*getTextByLangFunc)(1915, os.str()); break;
        
        case 1190: texte = (this->*getTextByLangFunc)(1916, os.str()); idsuiv=1192; break;
        case 1191: texte = (this->*getTextByLangFunc)(1917, os.str()); idsuiv=1193; break;
        case 1192: texte = (this->*getTextByLangFunc)(1918, os.str()); break;
        case 1193: texte = (this->*getTextByLangFunc)(1919, os.str()); break;
        
        case 1194: 
            tmp = gpJeu->getJoueur()->getCoffre(12,14) + 1; os << tmp;
            texte = (this->*getTextByLangFunc)(1920, os.str())+os.str()+(this->*getTextByLangFunc)(1921, os.str()); idsuiv=1197; break;
        case 1195: 
            tmp = gpJeu->getJoueur()->getCoffre(12,14) + 1; os << tmp;
            texte = (this->*getTextByLangFunc)(1922, os.str())+os.str()+(this->*getTextByLangFunc)(1923, os.str()); idsuiv=1196; break;
        case 1196: texte = (this->*getTextByLangFunc)(1924, os.str()); break;
        case 1197: texte = (this->*getTextByLangFunc)(1925, os.str()); break;
        
        case 1198: texte = (this->*getTextByLangFunc)(1926, os.str()); idsuiv=1200; break;
        case 1199: texte = (this->*getTextByLangFunc)(1927, os.str()); idsuiv=1201; break;
        case 1200: texte = (this->*getTextByLangFunc)(1928, os.str()); break;
        case 1201: texte = (this->*getTextByLangFunc)(1929, os.str()); break;
        
        case 1202: texte = (this->*getTextByLangFunc)(1930, os.str()); idsuiv=1204; break;
        case 1203: texte = (this->*getTextByLangFunc)(1931, os.str()); idsuiv=1205; break;
        case 1204: texte = (this->*getTextByLangFunc)(1932, os.str()); break;
        case 1205: texte = (this->*getTextByLangFunc)(1933, os.str()); break;
        
        case 1206: texte = (this->*getTextByLangFunc)(1934, os.str()); idsuiv=1209; break;
        case 1207: texte = (this->*getTextByLangFunc)(1935, os.str()); idsuiv=1208; break;
        case 1208: texte = (this->*getTextByLangFunc)(1936, os.str()); break;
        case 1209: texte = (this->*getTextByLangFunc)(1937, os.str()); break;
        
        case 1210: texte = (this->*getTextByLangFunc)(1938, os.str()); idsuiv=1213; break;
        case 1211: texte = (this->*getTextByLangFunc)(1939, os.str()); idsuiv=1212; break;
        case 1212: texte = (this->*getTextByLangFunc)(1940, os.str()); break;
        case 1213: texte = (this->*getTextByLangFunc)(1941, os.str()); break;
        
        case 1214: texte = (this->*getTextByLangFunc)(1942, os.str()); idsuiv=1217; break;
        case 1215: texte = (this->*getTextByLangFunc)(1943, os.str()); idsuiv=1216; break;
        case 1216: texte = (this->*getTextByLangFunc)(1944, os.str()); break;
        case 1217: texte = (this->*getTextByLangFunc)(1945, os.str()); break;
        
        case 1218: texte = (this->*getTextByLangFunc)(1946, os.str()); idsuiv=1221; break;
        case 1219: texte = (this->*getTextByLangFunc)(1947, os.str()); idsuiv=1220; break;
        case 1220: texte = (this->*getTextByLangFunc)(1948, os.str()); break;
        case 1221: texte = (this->*getTextByLangFunc)(1949, os.str()); break;
        
        case 1222: texte = (this->*getTextByLangFunc)(1950, os.str()); idsuiv=1224; break;
        case 1223: texte = (this->*getTextByLangFunc)(1951, os.str()); idsuiv=1225; break;
        case 1224: texte = (this->*getTextByLangFunc)(1952, os.str()); break;
        case 1225: texte = (this->*getTextByLangFunc)(1953, os.str()); break;
        
        case 1226: texte = (this->*getTextByLangFunc)(1954, os.str()); idsuiv=1229; break;
        case 1227: texte = (this->*getTextByLangFunc)(1955, os.str()); idsuiv=1228; break;
        case 1228: texte = (this->*getTextByLangFunc)(1956, os.str()); break;
        case 1229: texte = (this->*getTextByLangFunc)(1957, os.str()); break;
        
        case 1230: texte = (this->*getTextByLangFunc)(1958, os.str()); idsuiv=1232; break;
        case 1231: texte = (this->*getTextByLangFunc)(1959, os.str()); idsuiv=1233; break;
        case 1232: texte = (this->*getTextByLangFunc)(1960, os.str()); break;
        case 1233: texte = (this->*getTextByLangFunc)(1961, os.str()); break;
        
        case 1234: texte = (this->*getTextByLangFunc)(1962, os.str()); idsuiv=1237; break;
        case 1235: texte = (this->*getTextByLangFunc)(1963, os.str()); idsuiv=1236; break;
        case 1236: texte = (this->*getTextByLangFunc)(1964, os.str()); break;
        case 1237: texte = (this->*getTextByLangFunc)(1965, os.str()); break;
        
        case 1238: texte = (this->*getTextByLangFunc)(1966, os.str()); idsuiv=1241; break;
        case 1239: texte = (this->*getTextByLangFunc)(1967, os.str()); idsuiv=1240; break;
        case 1240: texte = (this->*getTextByLangFunc)(1968, os.str()); break;
        case 1241: texte = (this->*getTextByLangFunc)(1969, os.str()); break;
        
        case 1242: texte = (this->*getTextByLangFunc)(1970, os.str()); idsuiv=1244; break;
        case 1243: texte = (this->*getTextByLangFunc)(1971, os.str()); idsuiv=1245; break;
        case 1244: texte = (this->*getTextByLangFunc)(1972, os.str()); break;
        case 1245: texte = (this->*getTextByLangFunc)(1973, os.str()); break;
        
        case 1246: texte = (this->*getTextByLangFunc)(1974, os.str()); idsuiv=1249; break;
        case 1247: texte = (this->*getTextByLangFunc)(1975, os.str()); idsuiv=1248; break;
        case 1248: texte = (this->*getTextByLangFunc)(1976, os.str()); break;
        case 1249: texte = (this->*getTextByLangFunc)(1977, os.str()); break;
        
        case 1250: texte = (this->*getTextByLangFunc)(1978, os.str()); idsuiv=1253; break;
        case 1251: texte = (this->*getTextByLangFunc)(1979, os.str()); idsuiv=1252; break;
        case 1252: texte = (this->*getTextByLangFunc)(1980, os.str()); break;
        case 1253: texte = (this->*getTextByLangFunc)(1981, os.str()); break;
        
        case 1254: texte = (this->*getTextByLangFunc)(1982, os.str()); idsuiv=1257; break;
        case 1255: texte = (this->*getTextByLangFunc)(1983, os.str()); idsuiv=1256; break;
        case 1256: texte = (this->*getTextByLangFunc)(1984, os.str()); break;
        case 1257: texte = (this->*getTextByLangFunc)(1985, os.str()); break;
        
        case 1258: texte = (this->*getTextByLangFunc)(1986, os.str()); idsuiv=1261; break;
        case 1259: texte = (this->*getTextByLangFunc)(1987, os.str()); idsuiv=1260; break;
        case 1260: texte = (this->*getTextByLangFunc)(1988, os.str()); break;
        case 1261: texte = (this->*getTextByLangFunc)(1989, os.str()); break;
        
        case 1262: texte = (this->*getTextByLangFunc)(1990, os.str()); idsuiv=1264; break;
        case 1263: texte = (this->*getTextByLangFunc)(1991, os.str()); idsuiv=1265; break;
        case 1264: texte = (this->*getTextByLangFunc)(1992, os.str()); break;
        case 1265: texte = (this->*getTextByLangFunc)(1993, os.str()); break;
        
        case 1266: 
            tmp = gpJeu->getJoueur()->getTemps(2); os << tmp;
            texte = (this->*getTextByLangFunc)(1994, os.str())+os.str()+(this->*getTextByLangFunc)(1995, os.str()); idsuiv=1268; break;
        case 1267: 
            tmp = gpJeu->getJoueur()->getTemps(2); os << tmp;
            texte = (this->*getTextByLangFunc)(1996, os.str())+os.str()+(this->*getTextByLangFunc)(1997, os.str()); idsuiv=1269; break;
        case 1268: texte = (this->*getTextByLangFunc)(1998, os.str()); break;
        case 1269: texte = (this->*getTextByLangFunc)(1999, os.str()); break;
        
        case 1270: texte = (this->*getTextByLangFunc)(2000, os.str()); idsuiv=1273; break;
        case 1271: texte = (this->*getTextByLangFunc)(2001, os.str()); idsuiv=1272; break;
        case 1272: texte = (this->*getTextByLangFunc)(2002, os.str()); break;
        case 1273: texte = (this->*getTextByLangFunc)(2003, os.str()); break;
        
        case 1274: texte = (this->*getTextByLangFunc)(2004, os.str()); idsuiv=1276; break;
        case 1275: texte = (this->*getTextByLangFunc)(2005, os.str()); idsuiv=1277; break;
        case 1276: texte = (this->*getTextByLangFunc)(2006, os.str()); break;
        case 1277: texte = (this->*getTextByLangFunc)(2007, os.str()); break;
        
        case 1278: texte = (this->*getTextByLangFunc)(2008, os.str()); idsuiv=1280; break;
        case 1279: texte = (this->*getTextByLangFunc)(2009, os.str()); idsuiv=1281; break;
        case 1280: texte = (this->*getTextByLangFunc)(2010, os.str()); break;
        case 1281: texte = (this->*getTextByLangFunc)(2011, os.str()); break;
        
        case 1282: texte = (this->*getTextByLangFunc)(2012, os.str()); idsuiv=1285; break;
        case 1283: texte = (this->*getTextByLangFunc)(2013, os.str()); idsuiv=1284; break;
        case 1284: texte = (this->*getTextByLangFunc)(2014, os.str()); break;
        case 1285: texte = (this->*getTextByLangFunc)(2015, os.str()); break;
        
        case 1286: texte = (this->*getTextByLangFunc)(2016, os.str()); idsuiv=1289; break;
        case 1287: texte = (this->*getTextByLangFunc)(2017, os.str()); idsuiv=1288; break;
        case 1288: texte = (this->*getTextByLangFunc)(2018, os.str()); break;
        case 1289: texte = (this->*getTextByLangFunc)(2019, os.str()); break;
        
        case 1290: texte = (this->*getTextByLangFunc)(2020, os.str()); idsuiv=1292; break;
        case 1291: texte = (this->*getTextByLangFunc)(2021, os.str()); idsuiv=1293; break;
        case 1292: texte = (this->*getTextByLangFunc)(2022, os.str()); break;
        case 1293: texte = (this->*getTextByLangFunc)(2023, os.str()); break;
        
        case 1294: texte = (this->*getTextByLangFunc)(2024, os.str()); idsuiv=1297; break;
        case 1295: texte = (this->*getTextByLangFunc)(2025, os.str()); idsuiv=1296; break;
        case 1296: texte = (this->*getTextByLangFunc)(2026, os.str()); break;
        case 1297: texte = (this->*getTextByLangFunc)(2027, os.str()); break;
        
        case 1298: texte = (this->*getTextByLangFunc)(2028, os.str()); idsuiv=1300; break;
        case 1299: texte = (this->*getTextByLangFunc)(2029, os.str()); idsuiv=1301; break;
        case 1300: texte = (this->*getTextByLangFunc)(2030, os.str()); break;
        case 1301: texte = (this->*getTextByLangFunc)(2031, os.str()); break;
        
        case 1302: texte = (this->*getTextByLangFunc)(2032, os.str()); idsuiv=1305; break;
        case 1303: texte = (this->*getTextByLangFunc)(2033, os.str()); idsuiv=1304; break;
        case 1304: texte = (this->*getTextByLangFunc)(2034, os.str()); break;
        case 1305: texte = (this->*getTextByLangFunc)(2035, os.str()); break;
        
        case 1306: texte = (this->*getTextByLangFunc)(2036, os.str()); idsuiv=1308; break;
        case 1307: texte = (this->*getTextByLangFunc)(2037, os.str()); idsuiv=1309; break;
        case 1308: texte = (this->*getTextByLangFunc)(2038, os.str()); break;
        case 1309: texte = (this->*getTextByLangFunc)(2039, os.str()); break;
        
        case 1310: texte = (this->*getTextByLangFunc)(2040, os.str()); idsuiv=1313; break;
        case 1311: texte = (this->*getTextByLangFunc)(2041, os.str()); idsuiv=1312; break;
        case 1312: texte = (this->*getTextByLangFunc)(2042, os.str()); break;
        case 1313: texte = (this->*getTextByLangFunc)(2043, os.str()); break;
        
        case 1314: texte = (this->*getTextByLangFunc)(2044, os.str()); break;
        case 1315: texte = (this->*getTextByLangFunc)(2045, os.str()); break;
        
        case 1316: texte = (this->*getTextByLangFunc)(2046, os.str()); break;
        case 1317: texte = (this->*getTextByLangFunc)(2047, os.str()); idsuiv=1318; break;
        case 1318: texte = (this->*getTextByLangFunc)(2048, os.str()); idsuiv=1319; break;
        case 1319: texte = (this->*getTextByLangFunc)(2049, os.str()); idsuiv=1320; break;
        case 1320: texte = (this->*getTextByLangFunc)(2050, os.str()); break;
        
        case 1321: texte = (this->*getTextByLangFunc)(2051, os.str()); break;
        case 1322: texte = (this->*getTextByLangFunc)(2052, os.str()); idsuiv=1323; break;
        case 1323: texte = (this->*getTextByLangFunc)(2053, os.str()); idsuiv=1324; break;
        case 1324: texte = (this->*getTextByLangFunc)(2054, os.str()); idsuiv=1325; break;
        case 1325: texte = (this->*getTextByLangFunc)(2055, os.str()); idsuiv=1326; break;
        case 1326: texte = (this->*getTextByLangFunc)(2056, os.str()); break;
        
        case 1327: texte = (this->*getTextByLangFunc)(2057, os.str()); idsuiv=1329; break;
        case 1328: texte = (this->*getTextByLangFunc)(2058, os.str()); idsuiv=1332; break;
        case 1329: texte = (this->*getTextByLangFunc)(2059, os.str()); idsuiv=1330; break; 
        case 1330: texte = (this->*getTextByLangFunc)(2060, os.str()); idsuiv=1331; break;
        case 1331: texte = (this->*getTextByLangFunc)(2061, os.str()); idsuiv=1332; break;
        case 1332: texte = (this->*getTextByLangFunc)(2062, os.str()); break;
        
        case 1333:
            if (gpJeu->getJoueur()->getCoffre(14,9)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 30 && gpJeu->getJoueur()->getCompteurType() >= 4) {id=1335; chercheText();break;}
            texte = (this->*getTextByLangFunc)(2063, os.str()); break;
        case 1334: texte = (this->*getTextByLangFunc)(2064, os.str()); break;
        case 1335: texte = (this->*getTextByLangFunc)(2065, os.str()); break;
        case 1336:
            if (gpJeu->getJoueur()->getCoffre(14,10)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 60 && gpJeu->getJoueur()->getCompteurType() >= 10) {id=1335; chercheText();break;}
            texte = (this->*getTextByLangFunc)(2066, os.str()); break;
        case 1337:
            if (gpJeu->getJoueur()->getCoffre(14,11)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 20 && gpJeu->getJoueur()->getCompteurType() >= 3) {id=1335; chercheText();break;}
            texte = (this->*getTextByLangFunc)(2067, os.str()); break;
        case 1338:
            if (gpJeu->getJoueur()->getCoffre(14,12)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 99 && gpJeu->getJoueur()->getCompteurType() >= 12) {id=1335; chercheText();break;}
            texte = (this->*getTextByLangFunc)(2068, os.str()); break;
        case 1339:
            if (gpJeu->getJoueur()->getCoffre(14,13)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 30 && gpJeu->getJoueur()->getCompteurType() >= 12) {id=1335; chercheText();break;}
            texte = (this->*getTextByLangFunc)(2069, os.str()); break;
        case 1340:
            if (gpJeu->getJoueur()->getCoffre(14,14)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 40 && gpJeu->getJoueur()->getCompteurType() >= 6) {id=1335; chercheText();break;}
            texte = (this->*getTextByLangFunc)(2070, os.str()); break;
        case 1341:
            if (gpJeu->getJoueur()->getCoffre(14,15)) {id=1334; chercheText();break;}
            if (gpJeu->getJoueur()->getCompteurEnn() >= 50 && gpJeu->getJoueur()->getCompteurType() >= 7) {id=1335; chercheText();break;}
            texte = (this->*getTextByLangFunc)(2071, os.str()); break;
#ifdef __vita__
        case 1342: texte = (this->*getTextByLangFunc)(2072, os.str()); break;
#else
        case 1342: texte = (this->*getTextByLangFunc)(2073, os.str()); break;
#endif
        case 1343: texte = (this->*getTextByLangFunc)(2074, os.str()); idsuiv=1344; break;
        case 1344: texte = (this->*getTextByLangFunc)(2075, os.str()); idsuiv=1345; break;
        case 1345: texte = (this->*getTextByLangFunc)(2076, os.str()); break;
        case 1346: 
            if (gpJeu->nbEnnemis()==0) {id=1348; chercheText();break;}
            texte = (this->*getTextByLangFunc)(2077, os.str()); break;
        case 1347: 
            if (gpJeu->nbEnnemis()==0) {id=1349; chercheText();break;}
            if (gpJeu->getEnnemi()->getSuivant()->getSpecial(2)<13) {id=1350; chercheText();break;}
            texte = (this->*getTextByLangFunc)(2078, os.str()); break;
        case 1348: texte = (this->*getTextByLangFunc)(2079, os.str()); break;
        case 1349: texte = (this->*getTextByLangFunc)(2080, os.str()); break;
        case 1350: texte = (this->*getTextByLangFunc)(2081, os.str()); break;
        case 1351: texte = (this->*getTextByLangFunc)(2082, os.str()); break;
        case 1352: texte = (this->*getTextByLangFunc)(2083, os.str()); idsuiv=1353; break;
        case 1353: texte = (this->*getTextByLangFunc)(2084, os.str()); idsuiv=1354; break;
        case 1354: texte = (this->*getTextByLangFunc)(2085, os.str()); idsuiv=1355; break;
        case 1355: texte = (this->*getTextByLangFunc)(2086, os.str()); idsuiv=1356; break;
        case 1356: texte = (this->*getTextByLangFunc)(2087, os.str()); idsuiv=1357; break;
        case 1357: texte = (this->*getTextByLangFunc)(2088, os.str()); idsuiv=1358; break;
        case 1358: texte = (this->*getTextByLangFunc)(2089, os.str()); break;
        case 1359: texte = (this->*getTextByLangFunc)(2090, os.str()); idsuiv=1360; break;
        case 1360: texte = (this->*getTextByLangFunc)(2091, os.str()); break;
        case 1361: texte = (this->*getTextByLangFunc)(2092, os.str()); idsuiv=1362; break;
        case 1362: texte = (this->*getTextByLangFunc)(2093, os.str()); idsuiv=1363; break;
        case 1363: texte = (this->*getTextByLangFunc)(2094, os.str()); idsuiv=1364; break;
        case 1364: texte = (this->*getTextByLangFunc)(2095, os.str()); buffer=(this->*getTextByLangFunc)(2096, os.str()); idsuiv=1365; break;
        case 1365: texte = (this->*getTextByLangFunc)(2097, os.str()); break;
        case 1366: texte = (this->*getTextByLangFunc)(2098, os.str()); break;
#ifdef __vita__
        case 1367: texte = (this->*getTextByLangFunc)(2099, os.str()); break;
#else
        case 1367: texte = (this->*getTextByLangFunc)(2100, os.str()); break;
#endif
        case 1368: texte = (this->*getTextByLangFunc)(2101, os.str()); break;
        case 1369: texte = (this->*getTextByLangFunc)(2102, os.str()); break;
        case 1370: texte = (this->*getTextByLangFunc)(2103, os.str()); break;
		case 1371:
            tmp = 0;
            for (int i = 0; i < 9; i++) if (gpJeu->getKeyboard()->getRang(i)) tmp++;
            if (tmp == 9 && gpJeu->getJoueur()->getEnnemi(141)) {id=1372; chercheText();break;}
            texte = (this->*getTextByLangFunc)(2104, os.str());
            break;
        case 1372: texte = (this->*getTextByLangFunc)(2105, os.str()); break;
        case 1373: texte = (this->*getTextByLangFunc)(2106, os.str()); idsuiv=1374; break;
        case 1374: texte = (this->*getTextByLangFunc)(2107, os.str()); break;
        case 1375: texte = (this->*getTextByLangFunc)(2108, os.str()); break;
        case 1376: texte = (this->*getTextByLangFunc)(2109, os.str()); idsuiv=1377; break;
        case 1377: texte = (this->*getTextByLangFunc)(2110, os.str()); break;
        case 1378: texte = (this->*getTextByLangFunc)(2111, os.str());break;
    }
}

int Texte::afficheCaractere(SDL_Surface* gpScreen, char character, int &i, std::string s, int a, int b) {
    int stringLength = (int)s.length();
    int valCharacter = (int)character;
        
#ifdef __vita__
    // Playstation button
    // ¾1 => Triangle
    // ¾2 => Rond
    // ¾3 => Croix
    // ¾4 => Carré
    // ¾5 => Pad Droite
    // ¾6 => Pad Haut
    // ¾7 => Pad Gauche
    // ¾8 => Pad Bas
    // ¾9 => Stick analogique
    if (valCharacter == 190){
        int buttonIndex = 0;
        char nextCharacter;
        int nextCharacterValue;
        while(i+1 < stringLength) {
            i++;
            nextCharacter = s.at(i);
            nextCharacterValue = (int)nextCharacter;
            if (nextCharacterValue <48 || nextCharacterValue>57){
                i--;
                break;
            }

            buttonIndex+= nextCharacterValue - 48;
        }
        affichePSBouton(gpScreen, buttonIndex, a, b);
        return 14;
    }
    else {
#endif
        afficheLettre(gpScreen, character,a,b);
        return 6;
#ifdef __vita__
    }
#endif
}

void Texte::affiche(SDL_Surface* gpScreen, std::string s, int a, int b) {
    for (int i = 0; i < (int)s.length(); i++) {
        a+=afficheCaractere(gpScreen, s.at(i), i, s, a, b);
    }
}

void Texte::afficheTexteAvecId(SDL_Surface* gpScreen, int id, std::string s, int a, int b) {
    std::string texte = (this->*getTextByLangFunc)(id, s);
    affiche(gpScreen, texte, a, b);
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
        a+=afficheCaractere(gpScreen, texte.at(i), i, texte, a, b);;
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

void Texte::affichePSBouton(SDL_Surface* gpScreen, int index, int vx, int vy) {
    SDL_Surface* img = imageButtons;
    SDL_Rect src;
    SDL_Rect dst;
    
    dst.x=vx; dst.y=vy;
    
    // Playstation button
    // 1 => Triangle
    // 2 => Rond
    // 3 => Croix
    // 4 => Carré
    // 5 => Pad Droite
    // 6 => Pad Haut
    // 7 => Pad Gauche
    // 8 => Pad Bas
    // 9 => Stick analogique
	switch(index){
        case 1: 
            src.x=2;
            src.y=2;
            src.h=16;
            src.w=16;
            break;
        case 2: 
            src.x=22;
            src.y=2;
            src.h=16;
            src.w=16;
            break;
        case 3: 
            src.x=42;
            src.y=2;
            src.h=16;
            src.w=16;
            break;
        case 4: 
            src.x=62;
            src.y=2;
            src.h=16;
            src.w=16;
            break;
        case 5:
            src.x=2;
            src.y=24;
            src.h=12;
            src.w=16;
            dst.y+=2;
            break;
        case 6:
            src.x=24;
            src.y=22;
            src.h=16;
            src.w=12;
            dst.y+=2;
            break;
        case 7:
            src.x=42;
            src.y=24;
            src.h=12;
            src.w=16;
            dst.y+=2;
            break;
        case 8:
            src.x=64;
            src.y=22;
            src.h=16;
            src.w=12;
            dst.y+=2;
            break;
        case 9:
            src.x=2;
            src.y=42;
            src.h=16;
            src.w=16;
            break;
	}
    
    SDL_BlitSurface(img, &src, gpScreen, &dst);
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
