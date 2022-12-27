#include "locales.h"

BEGIN_LOCALE(basic, italian)

LOCALE_VALUE(BANG_TITLE,                          "Bang!")

LOCALE_VALUE(BUTTON_YES,                          "Sì")
LOCALE_VALUE(BUTTON_NO,                           "No")
LOCALE_VALUE(BUTTON_PLAY,                         "Gioca")
LOCALE_VALUE(BUTTON_PICK,                         "Scarta")
LOCALE_VALUE(BUTTON_UNDO,                         "Annulla")
LOCALE_VALUE(BUTTON_CONNECT,                      "Connetti")
LOCALE_VALUE(BUTTON_CANCEL,                       "Annulla")
LOCALE_VALUE(BUTTON_CREATE_SERVER,                "Crea Server")
LOCALE_VALUE(BUTTON_DELETE,                       "Elimina")
LOCALE_VALUE(BUTTON_JOIN,                         "Entra")
LOCALE_VALUE(BUTTON_MAKE_LOBBY,                   "Crea lobby")
LOCALE_VALUE(BUTTON_START,                        "Avvia")
LOCALE_VALUE(BUTTON_EXIT,                         "Esci")
LOCALE_VALUE(BUTTON_DISCONNECT,                   "Disconnetti")
LOCALE_VALUE(BUTTON_CHAT,                         "Chat")

LOCALE_VALUE(LABEL_USERNAME,                      "Nome:")
LOCALE_VALUE(LABEL_NEW_ADDRESS,                   "Nuovo indirizzo:")

LOCALE_VALUE(ERROR_NO_USERNAME,                   "Specificare un nome utente")
LOCALE_VALUE(ERROR_NO_ADDRESS,                    "Specificare un indirizzo")
LOCALE_VALUE(ERROR_NO_LOBBY_NAME,                 "Specificare un nome lobby")
LOCALE_VALUE(ERROR_DISCONNECTED,                  "Disconnesso dal server")
LOCALE_VALUE(ERROR_CONNECTION_CANCELED,           "Connessione annullata")
LOCALE_VALUE(ERROR_INVALID_ADDRESS,               "Indirizzo non valido: {}")
LOCALE_VALUE(ERROR_CREATING_SERVER,               "Errore nella creazione del Server")
LOCALE_VALUE(CREATING_SERVER,                     "Creazione del Server...")
LOCALE_VALUE(CONNECTING_TO,                       "In connessione a {} ...")
LOCALE_VALUE(DIALOG_IMAGE_FILES,                  "File Immagine")
LOCALE_VALUE(DIALOG_ALL_FILES,                    "Tutti i File")

LOCALE_VALUE(BUTTON_TOLOBBY,                      "Torna a Lobby")

LOCALE_VALUE(GAME_USER_CONNECTED,                 "{} entra in partita")
LOCALE_VALUE(GAME_USER_DISCONNECTED,              "{} esce dalla partita")
LOCALE_VALUE(USERNAME_DISCONNECTED,               "(Disconnesso)")

LOCALE_VALUE(PROMPT_CARD_NO_EFFECT,               "Giocare {} non avrebbe effetto. Continuare?")
LOCALE_VALUE(PROMPT_PASS_DISCARD,                 "Devi scartare 1 carta. Continuare?")
LOCALE_VALUE(PROMPT_PASS_DISCARD_PLURAL,          "Devi scartare {} carte. Continuare?")
LOCALE_VALUE(PROMPT_MOVE_BOMB_TO_SELF,            "Stai lasciando {} su te stesso. Continuare?")
LOCALE_VALUE(PROMPT_REPLACE,                      "Vuoi giocare {0} per rimpiazzare {1}?")
LOCALE_VALUE(PROMPT_TARGET_SELF,                  "Vuoi giocare {} su te stesso?")
LOCALE_VALUE(PROMPT_NO_REDRAW,                    "Vuoi giocare {} senza ripescare la carta?")
LOCALE_VALUE(PROMPT_BANG_STRENGTH,                "Devi rispondere con {} Mancato! Continuare?")
LOCALE_VALUE(PROMPT_PLAY_OR_PICK,                 "Giocare la carta o scartarla?")

LOCALE_VALUE(STATUS_GAME_OVER,                    "Partita Finita")
LOCALE_VALUE(STATUS_YOUR_TURN,                    "Tocca a te ... Scegli come pescare")
LOCALE_VALUE(STATUS_YOUR_TURN_OTHER,              "Tocca a {}")
LOCALE_VALUE(STATUS_CHARACTERCHOICE,              "Scegli il tuo personaggio")
LOCALE_VALUE(STATUS_CHARACTERCHOICE_OTHER,        "{} deve scegliere il personaggio")
LOCALE_VALUE(STATUS_PREDRAW,                      "Scegli per quale carta estrarre")
LOCALE_VALUE(STATUS_PREDRAW_OTHER,                "{} deve scegliere per quale carta estrarre")
LOCALE_VALUE(STATUS_CHECK,                        "Scegli quale carta estrarre per {0}")
LOCALE_VALUE(STATUS_CHECK_OTHER,                  "{0} deve scegliere quale carta estrarre per {1}")
LOCALE_VALUE(STATUS_GENERALSTORE,                 "{0} ... Scegli una carta")
LOCALE_VALUE(STATUS_GENERALSTORE_OTHER,           "{1} ... {0} deve scegliere una carta")
LOCALE_VALUE(STATUS_DISCARD,                      "{0} ... Scarta una carta")
LOCALE_VALUE(STATUS_DISCARD_OTHER,                "{1} ... {0} deve scartare una carta")
LOCALE_VALUE(STATUS_DISCARD_PASS,                 "Scarta una carta prima di passare il turno")
LOCALE_VALUE(STATUS_DISCARD_PASS_OTHER,           "{0} deve scartare una carta prima di passare il turno")
LOCALE_VALUE(STATUS_DISCARD_PASS_PLURAL,          "Scarta {} carte prima di passare il turno")
LOCALE_VALUE(STATUS_DISCARD_PASS_PLURAL_OTHER,    "{0} deve scartare {1} carte prima di passare il turno")
LOCALE_VALUE(STATUS_BANG,                         "{0} ... Rispondi con Mancato o Prendi danno")
LOCALE_VALUE(STATUS_BANG_STRONG,                  "{0} ... Rispondi con {1} Mancato o prendi danno")
LOCALE_VALUE(STATUS_BANG_DAMAGE,                  "{0} ... Rispondi con Mancato o Prendi {1} danni")
LOCALE_VALUE(STATUS_BANG_DAMAGE_STRONG,           "{0} ... Rispondi con {1} Mancato o prendi {2} danni")
LOCALE_VALUE(STATUS_BANG_OTHER,                   "{0} deve rispondere a {1}")
LOCALE_VALUE(STATUS_CARD_AS_BANG,                 "{0} come Bang! ... Rispondi con Mancato o Prendi danno")
LOCALE_VALUE(STATUS_CARD_AS_BANG_STRONG,          "{0} come Bang! ... Rispondi con {1} Mancato o prendi danno")
LOCALE_VALUE(STATUS_CARD_AS_BANG_DAMAGE,          "{0} come Bang! ... Rispondi con Mancato o Prendi {1} danni")
LOCALE_VALUE(STATUS_CARD_AS_BANG_DAMAGE_STRONG,   "{0} come Bang! ... Rispondi con {1} Mancato o prendi {2} danni")
LOCALE_VALUE(STATUS_CARD_AS_BANG_OTHER,           "{0} deve rispondere a {1} come Bang!")
LOCALE_VALUE(STATUS_CARD_AS_GATLING,              "{0} come Gatling ... Rispondi con Mancato o Prendi danno")
LOCALE_VALUE(STATUS_CARD_AS_GATLING_OTHER,        "{0} deve rispondere a {1} come Gatling")
LOCALE_VALUE(STATUS_INDIANS,                      "{0} ... Rispondi con Bang o Prendi danno")
LOCALE_VALUE(STATUS_INDIANS_OTHER,                "{0} deve rispondere a {1}")
LOCALE_VALUE(STATUS_DUEL,                         "{0} ... Rispondi con Bang o Prendi danno")
LOCALE_VALUE(STATUS_DUEL_OTHER,                   "{0} deve rispondere a {1}")
LOCALE_VALUE(STATUS_DESTROY,                      "{0} per scartare {1} ... Puoi rispondere con Fuga")
LOCALE_VALUE(STATUS_DESTROY_FROM_HAND,            "{0} per scartare una carta dalla mano ... Puoi rispondere con Fuga")
LOCALE_VALUE(STATUS_DESTROY_OTHER,                "{1} per scartare {2} di {0}")
LOCALE_VALUE(STATUS_DESTROY_OTHER_FROM_HAND,      "{1} per scartare una carta dalla mano di {0}")
LOCALE_VALUE(STATUS_STEAL,                        "{0} per rubare {1} ... Puoi rispondere con Fuga")
LOCALE_VALUE(STATUS_STEAL_FROM_HAND,              "{0} per rubare una carta dalla mano ... Puoi rispondere con Fuga")
LOCALE_VALUE(STATUS_STEAL_OTHER,                  "{1} per rubare {2} di {0}")
LOCALE_VALUE(STATUS_STEAL_OTHER_FROM_HAND,        "{1} per rubare una carta dalla mano di {0}")
LOCALE_VALUE(STATUS_DEATH,                        "Devi giocare 1 birra per salvarti")
LOCALE_VALUE(STATUS_DEATH_PLURAL,                 "Devi giocare {} birre per salvarti")
LOCALE_VALUE(STATUS_DEATH_OTHER,                  "{0} deve giocare 1 birra per salvarsi")
LOCALE_VALUE(STATUS_DEATH_OTHER_PLURAL,           "{0} deve giocare {1} birre per salvarsi")
LOCALE_VALUE(STATUS_DISCARD_ALL,                  "Sei morto! Scarta tutte le tue carte")
LOCALE_VALUE(STATUS_DISCARD_ALL_OTHER,            "{0} è morto e deve scartare tutte le sue carte")
LOCALE_VALUE(STATUS_SHERIFF_KILLED_DEPUTY,        "Hai ucciso il tuo vice! Scarta tutte le tue carte")
LOCALE_VALUE(STATUS_SHERIFF_KILLED_DEPUTY_OTHER,  "{0} ha ucciso il suo vice e deve scartare tutte le sue carte")
LOCALE_VALUE(STATUS_BANDIDOS,                     "{0} ... Scarta due carte o Prendi danno")
LOCALE_VALUE(STATUS_BANDIDOS_OTHER,               "{0} deve rispondere a {1}")
LOCALE_VALUE(STATUS_TORNADO,                      "{0} ... Scarta una carta per pescarne due")
LOCALE_VALUE(STATUS_TORNADO_OTHER,                "{1} ... {0} deve scartare una carta per pescarne due")
LOCALE_VALUE(STATUS_POKER,                        "{0} ... Scarta una carta")
LOCALE_VALUE(STATUS_POKER_OTHER,                  "{1} ... {0} deve scartare una carta")
LOCALE_VALUE(STATUS_POKER_DRAW,                   "{0} ... Scegli quali carte pescare")
LOCALE_VALUE(STATUS_POKER_DRAW_OTHER,             "{1} ... {0} deve scegliere quale carta pescare")
LOCALE_VALUE(STATUS_SAVED,                        "{0} ... Scegli se pescare dal mazzo o dalla mano di {1}")
LOCALE_VALUE(STATUS_SAVED_OTHER,                  "{1} ... {0} deve scegliere se pescare dal mazzo o dalla mano di {2}")
LOCALE_VALUE(STATUS_ADD_CUBE,                     "Scegli su quale carta mettere un cubetto")
LOCALE_VALUE(STATUS_ADD_CUBE_OTHER,               "{0} deve scegliere su quale carta mettere un cubetto ")
LOCALE_VALUE(STATUS_ADD_CUBE_PLURAL,              "Scegli su quale carta mettere {} cubetti")
LOCALE_VALUE(STATUS_ADD_CUBE_PLURAL_OTHER,        "{0} deve scegliere su quale carta mettere {1} cubetti ")
LOCALE_VALUE(STATUS_ADD_CUBE_FOR,                 "Scegli su quale carta mettere un cubetto, per {0}")
LOCALE_VALUE(STATUS_ADD_CUBE_FOR_OTHER,           "{0} deve scegliere su quale carta mettere un cubetto, per {1}")
LOCALE_VALUE(STATUS_ADD_CUBE_PLURAL_FOR,          "Scegli su quale carta mettere {1} cubetti, per {0}")
LOCALE_VALUE(STATUS_ADD_CUBE_PLURAL_FOR_OTHER,    "{0} deve scegliere su quale carta mettere {2} cubetti, per {1}")
LOCALE_VALUE(STATUS_MOVE_BOMB,                    "Scegli su chi spostare {0}")
LOCALE_VALUE(STATUS_MOVE_BOMB_OTHER,              "{0} deve scegliere su chi spostare {1}")
LOCALE_VALUE(STATUS_RUST,                         "{0} ... Puoi rispondere con Fuga")
LOCALE_VALUE(STATUS_RUST_OTHER,                   "{1} contro {0}")
LOCALE_VALUE(STATUS_RICOCHET,                     "{0} per scartare {1} ... Puoi rispondere con Mancato")
LOCALE_VALUE(STATUS_RICOCHET_OTHER,               "{1} per scartare {2} di {0}")
LOCALE_VALUE(STATUS_PEYOTE,                       "{0} ... Dichiara Rosso o Nero")
LOCALE_VALUE(STATUS_PEYOTE_OTHER,                 "{1} ... {0} deve scegliere Rosso o Nero")
LOCALE_VALUE(STATUS_HANDCUFFS,                    "{0} ... Dichiara un seme")
LOCALE_VALUE(STATUS_HANDCUFFS_OTHER,              "{1} ... {0} deve dichiarare un seme")
LOCALE_VALUE(STATUS_KIT_CARLSON,                  "{0} ... Scegli quali carte pescare")
LOCALE_VALUE(STATUS_KIT_CARLSON_OTHER,            "{1} ... {0} deve scegliere quali carte pescare")
LOCALE_VALUE(STATUS_CLAUS_THE_SAINT_DRAW,         "{0} ... Scegli quali carte pescare")
LOCALE_VALUE(STATUS_CLAUS_THE_SAINT_GIVE,         "{0} ... Scegli quale carta dare a {1}")
LOCALE_VALUE(STATUS_CLAUS_THE_SAINT_DRAW_OTHER,   "{0} deve scegliere quali carte pescare")
LOCALE_VALUE(STATUS_CLAUS_THE_SAINT_GIVE_OTHER,   "{1} ... {0} deve scegliere quale carta dare a {2}")
LOCALE_VALUE(STATUS_CLAUS_THE_SAINT_GIVE_YOU,     "{1} ... {0} deve scegliere quale carta dare a te")
LOCALE_VALUE(STATUS_VERA_CUSTER,                  "{0} ... Scegli quale personaggio copiare")
LOCALE_VALUE(STATUS_VERA_CUSTER_OTHER,            "{1} ... {0} deve scegliere quale personaggio copiare")
LOCALE_VALUE(STATUS_YOUL_GRINNER,                 "{0} ... Dai una carta a {1}")
LOCALE_VALUE(STATUS_YOUL_GRINNER_OTHER,           "{0} ... {2} deve dare una carta a {1}")
LOCALE_VALUE(STATUS_DUTCH_WILL,                   "{0} ... Scegli quale carta pescare")
LOCALE_VALUE(STATUS_DUTCH_WILL_OTHER,             "{1} ... {0} deve scegliere quale carta pescare")
LOCALE_VALUE(STATUS_THEDALTONS,                   "{0} ... Scarta una carta blu")
LOCALE_VALUE(STATUS_THEDALTONS_OTHER,             "{1} ... {0} deve scartare una carta blu")
LOCALE_VALUE(STATUS_CAN_PLAY_CARD,                "Puoi giocare {0}")
LOCALE_VALUE(STATUS_CAN_PLAY_CARD_OTHER,          "{0} Può giocare {1}")
LOCALE_VALUE(STATUS_DAMAGING,                     "{0} prende un danno per {1}")
LOCALE_VALUE(STATUS_DAMAGING_PLURAL,              "{0} prende {2} danni per {1}")
LOCALE_VALUE(STATUS_DAMAGING_AS_BANG,             "{0} prende un danno per {1} come Bang!")
LOCALE_VALUE(STATUS_DAMAGING_AS_BANG_PLURAL,      "{0} prende {2} danni per {1} come Bang!")
LOCALE_VALUE(STATUS_DAMAGING_AS_GATLING,          "{0} prende un danno per {1} come Gatling!")
LOCALE_VALUE(STATUS_CAN_PLAY_TUMBLEWEED,          "{0} estrae {3} per {2} ... Puoi giocare {1}")
LOCALE_VALUE(STATUS_CAN_PLAY_TUMBLEWEED_OTHER,    "{0} estrae {3} per {2} ... {4} può giocare {1}")
LOCALE_VALUE(STATUS_CARD_SHARPER,                 "{0} per scambiare {1} con {2} ... Puoi rispondere con Fuga")
LOCALE_VALUE(STATUS_CARD_SHARPER_OTHER,           "{1} contro {0} per scambiare {2} con {3}")
LOCALE_VALUE(STATUS_LASTWILL,                     "Puoi giocare {0} per dare fino a tre carte a un giocatore")
LOCALE_VALUE(STATUS_LASTWILL_OTHER,               "{1} può giocare {0}")
LOCALE_VALUE(STATUS_NEWIDENTITY,                  "{0} ... Scegli con quale personaggio cambiare")
LOCALE_VALUE(STATUS_NEWIDENTITY_OTHER,            "{1} ... {0} deve scegliere con quale personaggio cambiare")
LOCALE_VALUE(STATUS_FORCE_PLAY_CARD,              "Devi giocare {0}")
LOCALE_VALUE(STATUS_FORCE_PLAY_CARD_OTHER,        "{0} deve giocare {1}")
LOCALE_VALUE(STATUS_FORCE_EQUIP_CARD,             "Devi equipaggiare {0}")
LOCALE_VALUE(STATUS_FORCE_EQUIP_CARD_OTHER,       "{0} deve equipaggiare {1}")
LOCALE_VALUE(STATUS_MULTI_VULTURE_SAM,            "{0} ... devi rubare una carta da {1}")
LOCALE_VALUE(STATUS_MULTI_VULTURE_SAM_OTHER,      "{0} ... {1} deve rubare una carta da {2}")
LOCALE_VALUE(STATUS_RANCH,                        "{0} ... Puoi scartare un qualsiasi numero di carte dalla mano per pescarne altrettante")
LOCALE_VALUE(STATUS_RANCH_OTHER,                  "{0} ... {1} può scartare un qualsiasi numero di carte dalla mano per pescarne altrettante")

LOCALE_VALUE(ERROR_INVALID_LOBBY,                 "ID lobby non valido")
LOCALE_VALUE(ERROR_PLAYER_IN_LOBBY,               "Giocatore già in una lobby")
LOCALE_VALUE(ERROR_PLAYER_NOT_IN_LOBBY,           "Giocatore non in una lobby")
LOCALE_VALUE(ERROR_PLAYER_NOT_LOBBY_OWNER,        "Non proprietario della lobby")
LOCALE_VALUE(ERROR_USER_NOT_CONTROLLING_PLAYER,   "Giocatore non in gioco")
LOCALE_VALUE(ERROR_USER_CONTROLLING_PLAYER,       "Giocatore già in gioco")
LOCALE_VALUE(ERROR_NOT_ENOUGH_PLAYERS,            "Non ci sono abbastanza giocatori")
LOCALE_VALUE(ERROR_LOBBY_NOT_WAITING,             "Lobby non in attesa")
LOCALE_VALUE(ERROR_LOBBY_NOT_PLAYING,             "Lobby non in gioco")
LOCALE_VALUE(ERROR_LOBBY_NOT_FINISHED,            "Lobby non in partita finita")
LOCALE_VALUE(ERROR_INVALID_REJOIN_TARGET,         "Non puoi entrare in gioco come questo giocatore")
LOCALE_VALUE(ERROR_PLAYER_DOES_NOT_OWN_CARD,      "Carta non tua")
LOCALE_VALUE(ERROR_CARD_NOT_FOUND,                "Carta non trovata")
LOCALE_VALUE(ERROR_INVALID_ACTION,                "Azione non valida")
LOCALE_VALUE(ERROR_NOT_ENOUGH_GOLD,               "Non hai abbastanza pepite")
LOCALE_VALUE(ERROR_NOT_ENOUGH_CUBES,              "Non ci sono abbastanza cubetti")
LOCALE_VALUE(ERROR_NOT_ENOUGH_CUBES_ON,           "Non ci sono abbastanza cubetti su {}")
LOCALE_VALUE(ERROR_CARD_HAS_FULL_CUBES,           "{} ha già 4 cubetti")
LOCALE_VALUE(ERROR_INVALID_TARGETS,               "Target non validi")
LOCALE_VALUE(ERROR_PLAYER_MUST_DRAW,              "Devi pescare")
LOCALE_VALUE(ERROR_PLAYER_MUST_NOT_DRAW,          "Non devi pescare adesso")
LOCALE_VALUE(ERROR_CANT_DISCARD_OWN_BLACK,        "Non puoi scartare le tue carte nere")
LOCALE_VALUE(ERROR_CARD_DISABLED_BY,              "{0} è disabilitata da {1}")
LOCALE_VALUE(ERROR_INVALID_SUIT,                  "Non puoi giocare {1}: seme non valido per {0}")
LOCALE_VALUE(ERROR_CARD_INACTIVE,                 "{} non è attiva in questo turno")
LOCALE_VALUE(ERROR_CANT_EQUIP_CARDS,              "Non si possono equipaggiare carte")
LOCALE_VALUE(ERROR_DUPLICATED_CARD,               "Carta duplicata: {}")
LOCALE_VALUE(ERROR_TARGET_PLAYING_CARD,           "Non puoi bersagliare la stessa carta che stai giocando")
LOCALE_VALUE(ERROR_TARGET_NOT_PLAYER,             "Il target non è un giocatore")
LOCALE_VALUE(ERROR_TARGET_NOT_DEAD,               "Il target non è morto")
LOCALE_VALUE(ERROR_TARGET_DEAD,                   "Il target è morto")
LOCALE_VALUE(ERROR_TARGET_SHERIFF,                "Non puoi giocare questa carta sullo sceriffo")
LOCALE_VALUE(ERROR_TARGET_NOT_SELF,               "Puoi giocare questa carta solo su tè stesso")
LOCALE_VALUE(ERROR_TARGET_SELF,                   "Non puoi giocare questa carta su tè stesso")
LOCALE_VALUE(ERROR_TARGET_NOT_IN_RANGE,           "Target fuori raggio")
LOCALE_VALUE(ERROR_TARGETS_NOT_UNIQUE,            "I target non sono unici")
LOCALE_VALUE(ERROR_TARGETS_NOT_ADJACENT,          "I target non sono adiacenti")
LOCALE_VALUE(ERROR_TARGET_NOT_CARD,               "Questa carta non è bersagliabile")
LOCALE_VALUE(ERROR_TARGET_BLACK_CARD,             "Non puoi bersagliare le carte nere")
LOCALE_VALUE(ERROR_TARGET_NOT_TABLE_CARD,         "Puoi giocare questa carta solo sulle carte sul tavolo")
LOCALE_VALUE(ERROR_TARGET_NOT_HAND_CARD,          "Puoi giocare questa carta solo sulle carte in mano")
LOCALE_VALUE(ERROR_TARGET_NOT_BLUE_CARD,          "Puoi giocare questa carta solo sulle carte blu")
LOCALE_VALUE(ERROR_TARGET_NOT_CLUBS,              "Puoi giocare questa carta solo sulle carte di fiori")
LOCALE_VALUE(ERROR_TARGET_NOT_BANG,               "Puoi giocare questa carta solo sulle carte Bang!")
LOCALE_VALUE(ERROR_TARGET_NOT_MISSED,             "Puoi giocare questa carta solo sulle carte Mancato!")
LOCALE_VALUE(ERROR_TARGET_NOT_BEER,               "Puoi giocare questa carta solo sulle carte Birra")
LOCALE_VALUE(ERROR_TARGET_NOT_BRONCO,             "Puoi giocare questa carta solo su Bronco")
LOCALE_VALUE(ERROR_TARGET_NOT_CUBE_SLOT,          "Questa carta non può contenere cubetti")
LOCALE_VALUE(ERROR_SCENARIO_AT_PLAY,              "{} è in gioco")
LOCALE_VALUE(ERROR_CANT_PLAY_CARD,                "Non puoi giocare {}")
LOCALE_VALUE(ERROR_ONE_BANG_PER_TURN,             "Puoi giocare un solo Bang per turno")
LOCALE_VALUE(ERROR_CANT_SELF_DAMAGE,              "Non puoi toglierti l'ultimo punto vita")
LOCALE_VALUE(ERROR_CANT_HEAL_PAST_FULL_HP,        "Non puoi curarti oltre l'ultimo punto vita")
LOCALE_VALUE(ERROR_NOT_START_OF_TURN,             "Non sei a inizio turno")
LOCALE_VALUE(ERROR_DISCARD_PILE_EMPTY,            "La pila degli scarti è vuota")
LOCALE_VALUE(ERROR_MAX_USAGES,                    "Non puoi giocare {0} più di {1} volte per turno")
LOCALE_VALUE(ERROR_MANDATORY_CARD,                "Sei obblicato a giocare {}")
LOCALE_VALUE(ERROR_TARGET_NOT_UNIQUE,             "I bersagli devono essere unici")

LOCALE_VALUE(LOG_GAME_START,                      "La partita è iniziata")
LOCALE_VALUE(LOG_GAME_OVER,                       "La partita è terminata")
LOCALE_VALUE(LOG_DECK_RESHUFFLED,                 "Il mazzo viene rimescolato")
LOCALE_VALUE(LOG_SHOP_RESHUFFLED,                 "Il mazzo dello shop viene rimescolato")
LOCALE_VALUE(LOG_TURN_START,                      "È il turno di {0}")
LOCALE_VALUE(LOG_SOLD_BEER,                       "{0} vende {1}")
LOCALE_VALUE(LOG_DISCARDED_CARD,                  "{0} scarta {2} a {1}")
LOCALE_VALUE(LOG_DISCARDED_SELF_CARD,             "{0} scarta {1}")
LOCALE_VALUE(LOG_DISCARDED_A_CARD_FOR,            "{1} scarta una carta per {0}")
LOCALE_VALUE(LOG_DISCARDED_CARD_FOR,              "{1} scarta {2} per {0}")
LOCALE_VALUE(LOG_DISCARDED_ORANGE_CARD,           "{0} deve scartare {1}")
LOCALE_VALUE(LOG_STOLEN_CARD,                     "{0} ruba {2} di {1}")
LOCALE_VALUE(LOG_STOLEN_CARD_FROM_HAND,           "{0} ruba una carta dalla mano di {1}")
LOCALE_VALUE(LOG_STOLEN_SELF_CARD,                "{0} ripesca {1}")
LOCALE_VALUE(LOG_STOLEN_SELF_CARD_FROM_HAND,      "{0} ripesca una carta dalla mano")
LOCALE_VALUE(LOG_DRAWN_WITH_CHARACTER,            "{1} pesca usando {0}")
LOCALE_VALUE(LOG_DRAWN_FROM_GENERALSTORE,         "{0} pesca {1} per {2}")
LOCALE_VALUE(LOG_PLAYED_CHARACTER,                "{1} gioca l'effetto di {0}")
LOCALE_VALUE(LOG_RESPONDED_WITH_CHARACTER,        "{1} risponde con l'effetto di {0}")
LOCALE_VALUE(LOG_PLAYED_CARD,                     "{1} gioca {0}")
LOCALE_VALUE(LOG_PLAYED_CARD_ON,                  "{1} gioca {0} su {2}")
LOCALE_VALUE(LOG_PLAYED_CARD_STEAL,               "{1} gioca {0} per rubare {3} di {2}")
LOCALE_VALUE(LOG_PLAYED_CARD_STEAL_HAND,          "{1} gioca {0} per rubare una carta dalla mano di {2}")
LOCALE_VALUE(LOG_PLAYED_CARD_STEAL_OWN,           "{1} gioca {0} per ripescare la sua {2}")
LOCALE_VALUE(LOG_PLAYED_CARD_STEAL_OWN_HAND,      "{1} gioca {0} per rubare una carta dalla sua mano")
LOCALE_VALUE(LOG_PLAYED_CARD_DESTROY,             "{1} gioca {0} per scartare {3} di {2}")
LOCALE_VALUE(LOG_PLAYED_CARD_DESTROY_HAND,        "{1} gioca {0} per scartare una carta dalla mano di {2}")
LOCALE_VALUE(LOG_PLAYED_CARD_DESTROY_OWN,         "{1} gioca {0} per scartare la sua {2}")
LOCALE_VALUE(LOG_PLAYED_CARD_AS_BANG_ON,          "{1} gioca {0} come Bang! su {2}")
LOCALE_VALUE(LOG_PLAYED_CARD_AS_GATLING,          "{1} gioca {0} come Gatling")
LOCALE_VALUE(LOG_PLAYED_TABLE_CARD,               "{1} gioca {0} da terra")
LOCALE_VALUE(LOG_EQUIPPED_CARD,                   "{1} equipaggia {0}")
LOCALE_VALUE(LOG_EQUIPPED_CARD_TO,                "{1} equipaggia {0} a {2}")
LOCALE_VALUE(LOG_BOUGHT_CARD,                     "{1} compra e gioca {0}")
LOCALE_VALUE(LOG_BOUGHT_EQUIP,                    "{1} compra ed equipaggia {0}")
LOCALE_VALUE(LOG_BOUGHT_EQUIP_TO,                 "{1} compra ed equipaggia {0} a {2}")
LOCALE_VALUE(LOG_RESPONDED_WITH_CARD,             "{1} risponde con {0}")
LOCALE_VALUE(LOG_RESPONDED_WITH_CARD_AS_MISSED,   "{1} risponde con {0} come Mancato!")
LOCALE_VALUE(LOG_DRAWN_FROM_DECK,                 "{0} pesca dal mazzo")
LOCALE_VALUE(LOG_DRAWN_CARD,                      "{0} pesca {1}")
LOCALE_VALUE(LOG_DRAWN_A_CARD,                    "{0} pesca una carta")
LOCALE_VALUE(LOG_DRAWN_N_CARDS,                   "{0} pesca {1} carte")
LOCALE_VALUE(LOG_DRAWN_CARD_FOR,                  "{0} pesca {1} per {2}")
LOCALE_VALUE(LOG_DRAWN_A_CARD_FOR,                "{0} pesca una carta per {1}")
LOCALE_VALUE(LOG_DRAWN_N_CARDS_FOR,               "{0} pesca {1} carte per {2}")
LOCALE_VALUE(LOG_DRAWN_FROM_DISCARD,              "{0} pesca {1} dalla cima degli scarti")
LOCALE_VALUE(LOG_REVEALED_CARD,                   "{0} rivela {1}")
LOCALE_VALUE(LOG_CHECK_DREW_CARD,                 "{1} estrae {2} per {0}")
LOCALE_VALUE(LOG_TAKEN_DAMAGE,                    "{1} prende 1 danno per {0}")
LOCALE_VALUE(LOG_TAKEN_DAMAGE_PLURAL,             "{1} prende {2} danni per {0}")
LOCALE_VALUE(LOG_TAKEN_DAMAGE_AS_BANG,            "{1} prende un danno per {0} come Bang!")
LOCALE_VALUE(LOG_TAKEN_DAMAGE_AS_BANG_PLURAL,     "{1} prende {2} danni per {0} come Bang!")
LOCALE_VALUE(LOG_TAKEN_DAMAGE_AS_GATLING,         "{1} prende un danno per {0} come Gatling")
LOCALE_VALUE(LOG_HEALED,                          "{0} si cura di 1 punto vita")
LOCALE_VALUE(LOG_HEALED_PLURAL,                   "{0} si cura di {1} punti vita")
LOCALE_VALUE(LOG_PLAYER_KILLED,                   "{0} ha ucciso {1}")
LOCALE_VALUE(LOG_PLAYER_DIED,                     "{0} è morto")
LOCALE_VALUE(LOG_JAIL_BREAK,                      "{} esce di prigione")
LOCALE_VALUE(LOG_SKIP_TURN,                       "{} salta il turno")
LOCALE_VALUE(LOG_CARD_EXPLODES,                   "{} esplode!")
LOCALE_VALUE(LOG_CARD_HAS_EFFECT,                 "Si attiva l'effetto di {}")
LOCALE_VALUE(LOG_CHARACTER_CHOICE,                "{0} ha {1} come personaggio")
LOCALE_VALUE(LOG_DRAWN_SHOP_CARD,                 "Viene rivelata {} dallo shop")
LOCALE_VALUE(LOG_SHERIFF_KILLED_DEPUTY,           "{} ha ucciso il suo vice!")
LOCALE_VALUE(LOG_MOVE_BOMB_ON,                    "{1} sposta {0} su {2}")
LOCALE_VALUE(LOG_GIFTED_CARD,                     "{0} dà {2} a {1}")
LOCALE_VALUE(LOG_GIFTED_A_CARD,                   "{0} dà una carta a {1}")
LOCALE_VALUE(LOG_COPY_CHARACTER,                  "{0} copia l'effetto di {1}")
LOCALE_VALUE(LOG_DRAWN_SCENARIO_CARD,             "Entra in gioco {}")
LOCALE_VALUE(LOG_RECEIVED_N_BANGS_FOR,            "{0} riceve {2} Bang! per {1}")
LOCALE_VALUE(LOG_MANDATORY_CARD,                  "{0} deve giocare {1} nella fase due")
LOCALE_VALUE(LOG_DECLARED_RED,                    "{0} dichiara Rosso per {1}")
LOCALE_VALUE(LOG_DECLARED_BLACK,                  "{0} dichiara Nero per {1}")
LOCALE_VALUE(LOG_DECLARED_CLUBS,                  "{0} dichiara Fiori per {1}")
LOCALE_VALUE(LOG_DECLARED_DIAMONDS,               "{0} dichiara Quadri per {1}")
LOCALE_VALUE(LOG_DECLARED_HEARTS,                 "{0} dichiara Cuori per {1}")
LOCALE_VALUE(LOG_DECLARED_SPADES,                 "{0} dichiara Picche per {1}")
LOCALE_VALUE(LOG_POKER_REVEAL,                    "Viene rivelata {1} per {0}")
LOCALE_VALUE(LOG_POKER_ACE,                       "C'è un Asso, tutte le carte sono scartate")
LOCALE_VALUE(LOG_REVIVE,                          "{0} ritorna in gioco per {1}")
LOCALE_VALUE(LOG_SWAP_CARDS,                      "{0} scambia {2} con {3} di {1}")
LOCALE_VALUE(LOG_PLAYER_IMMUNE_TO_CARD,           "{0} è immune a {1} per {2}")

LOCALE_VALUE(lobby_state::waiting,                "In attesa")
LOCALE_VALUE(lobby_state::playing,                "In gioco")
LOCALE_VALUE(lobby_state::finished,               "Partita finita")

LOCALE_VALUE(player_role::sheriff,                      "Sceriffo")
LOCALE_VALUE(player_role::deputy,                       "Vice")
LOCALE_VALUE(player_role::outlaw,                       "Fuorilegge")
LOCALE_VALUE(player_role::renegade,                     "Rinnegato")

LOCALE_VALUE(game_options::expansions,                  "Espansioni")
LOCALE_VALUE(game_options::character_choice,            "Scelta Dei Personaggi")
LOCALE_VALUE(game_options::allow_beer_in_duel,          "Permetti Birra in duello")
LOCALE_VALUE(game_options::quick_discard_all,           "Scarta Tutto Veloce")
LOCALE_VALUE(game_options::scenario_deck_size,          "Carte Scenario")
LOCALE_VALUE(game_options::num_bots,                    "Numero di Bot")
LOCALE_VALUE(game_options::damage_timer,                "Timer di Danno")
LOCALE_VALUE(game_options::escape_timer,                "Timer di Fuga")
LOCALE_VALUE(game_options::tumbleweed_timer,            "Timer di Cespuglio")

LOCALE_VALUE(card_expansion_type::thebullet,            "La Pallottola")
LOCALE_VALUE(card_expansion_type::dodgecity,            "Dodge City")
LOCALE_VALUE(card_expansion_type::valleyofshadows,      "La Valle Delle Ombre")
LOCALE_VALUE(card_expansion_type::wildwestshow,         "Wild West Show")
LOCALE_VALUE(card_expansion_type::goldrush,             "Corsa all'Oro")
LOCALE_VALUE(card_expansion_type::armedanddangerous,    "Armed And Dangerous")
LOCALE_VALUE(card_expansion_type::highnoon,             "Mezzogiorno di Fuoco")
LOCALE_VALUE(card_expansion_type::fistfulofcards,       "Per un Pugno di Carte")
LOCALE_VALUE(card_expansion_type::canyondiablo,         "Canyon Diablo")
LOCALE_VALUE(card_expansion_type::ghostcards,           "Carte Fantasma")

END_LOCALE()