#include "locales.h"

BEGIN_LOCALE(basic, english)

LOCALE_VALUE(BANG_TITLE,                          "Bang!")

LOCALE_VALUE(BUTTON_YES,                          "Yes")
LOCALE_VALUE(BUTTON_NO,                           "No")
LOCALE_VALUE(BUTTON_PLAY,                         "Play")
LOCALE_VALUE(BUTTON_PICK,                         "Discard")
LOCALE_VALUE(BUTTON_UNDO,                         "Undo")
LOCALE_VALUE(BUTTON_CONNECT,                      "Connect")
LOCALE_VALUE(BUTTON_CANCEL,                       "Cancel")
LOCALE_VALUE(BUTTON_CREATE_SERVER,                "Create Server")
LOCALE_VALUE(BUTTON_DELETE,                       "Delete")
LOCALE_VALUE(BUTTON_JOIN,                         "Join")
LOCALE_VALUE(BUTTON_MAKE_LOBBY,                   "Make lobby")
LOCALE_VALUE(BUTTON_START,                        "Start")
LOCALE_VALUE(BUTTON_EXIT,                         "Exit")
LOCALE_VALUE(BUTTON_DISCONNECT,                   "Disconnect")
LOCALE_VALUE(BUTTON_CHAT,                         "Chat")

LOCALE_VALUE(LABEL_USERNAME,                      "Name:")
LOCALE_VALUE(LABEL_NEW_ADDRESS,                   "New address:")

LOCALE_VALUE(ERROR_NO_USERNAME,                   "Specify the user name")
LOCALE_VALUE(ERROR_NO_ADDRESS,                    "Specify an address")
LOCALE_VALUE(ERROR_NO_LOBBY_NAME,                 "Specify a lobby name")
LOCALE_VALUE(ERROR_DISCONNECTED,                  "Disconnected from the server")
LOCALE_VALUE(ERROR_CONNECTION_CANCELED,           "Connection canceled")
LOCALE_VALUE(ERROR_INVALID_ADDRESS,               "Invalid address: {}")
LOCALE_VALUE(ERROR_CREATING_SERVER,               "Error Creating Server")
LOCALE_VALUE(CREATING_SERVER,                     "Creating Server...")
LOCALE_VALUE(CONNECTING_TO,                       "Connecting to {} ...")
LOCALE_VALUE(DIALOG_IMAGE_FILES,                  "Image Files")
LOCALE_VALUE(DIALOG_ALL_FILES,                    "All Files")

LOCALE_VALUE(BUTTON_TOLOBBY,                      "Return To Lobby")

LOCALE_VALUE(GAME_USER_CONNECTED,                 "{} joined")
LOCALE_VALUE(GAME_USER_DISCONNECTED,              "{} left")
LOCALE_VALUE(USERNAME_DISCONNECTED,               "(Disconnected)")
LOCALE_VALUE(UNKNOWN_PLAYER,                      "(unknown player)")
LOCALE_VALUE(UNKNOWN_CARD,                        "(unknown card)")

LOCALE_VALUE(PROMPT_CARD_NO_EFFECT,               "Playing {} would have no effect. Continue?")
LOCALE_VALUE(PROMPT_PASS_DISCARD,                 "You must discard 1 card. Continue?")
LOCALE_VALUE(PROMPT_PASS_DISCARD_PLURAL,          "You must discard {} cards. Continue?")
LOCALE_VALUE(PROMPT_MOVE_BOMB_TO_SELF,            "You're keeping {} on yourself. Continue?")
LOCALE_VALUE(PROMPT_REPLACE,                      "Do you want to play {0} to replace {1}?")
LOCALE_VALUE(PROMPT_TARGET_SELF,                  "Do you want to play {} on yourself?")
LOCALE_VALUE(PROMPT_TARGET_GHOST,                 "{1} is a ghost, playing {0} would have no effect. Continue?")
LOCALE_VALUE(PROMPT_NO_REDRAW,                    "Do you want to play {} without redrawing the card?")
LOCALE_VALUE(PROMPT_BANG_STRENGTH,                "You have to respond with {} Missed! Continue?")
LOCALE_VALUE(PROMPT_NO_BANGS_PLAYED,              "You haven't played any Bang, playing {} would have no effect. Continue?")
LOCALE_VALUE(PROMPT_PLAY_OR_PICK,                 "Play or discard this card?")

LOCALE_VALUE(STATUS_GAME_OVER,                    "Game Over")
LOCALE_VALUE(STATUS_YOUR_TURN,                    "Your turn ... Choose how to draw")
LOCALE_VALUE(STATUS_YOUR_TURN_OTHER,              "{}'s turn")
LOCALE_VALUE(STATUS_CHARACTERCHOICE,              "Choose your character")
LOCALE_VALUE(STATUS_CHARACTERCHOICE_OTHER,        "{} must choose their character")
LOCALE_VALUE(STATUS_PREDRAW,                      "Choose which card to \"Draw!\" for")
LOCALE_VALUE(STATUS_PREDRAW_OTHER,                "{} must choose which card to \"draw!\" for")
LOCALE_VALUE(STATUS_CHECK,                        "Choose which card to \"draw!\" for {0}")
LOCALE_VALUE(STATUS_CHECK_OTHER,                  "{0} must choose which card to \"draw!\" for {1}")
LOCALE_VALUE(STATUS_GENERALSTORE,                 "{0} ... Choose a card")
LOCALE_VALUE(STATUS_GENERALSTORE_OTHER,           "{1} ... {0} must choose a card")
LOCALE_VALUE(STATUS_DISCARD,                      "{0} ... Discard a card")
LOCALE_VALUE(STATUS_DISCARD_OTHER,                "{1} ... {0} must discard a card")
LOCALE_VALUE(STATUS_DISCARD_PASS,                 "Discard a card before passing the turn")
LOCALE_VALUE(STATUS_DISCARD_PASS_OTHER,           "{0} must discard a card before passing the turn")
LOCALE_VALUE(STATUS_DISCARD_PASS_PLURAL,          "Discard {} cards before passing the turn")
LOCALE_VALUE(STATUS_DISCARD_PASS_PLURAL_OTHER,    "{0} must discard {1} cards before passing the turn")
LOCALE_VALUE(STATUS_BANG,                         "{0} ... Respond with Missed or Take damage")
LOCALE_VALUE(STATUS_BANG_STRONG,                  "{0} ... Respond with {1} Missed or Take damage")
LOCALE_VALUE(STATUS_BANG_DAMAGE,                  "{0} ... Respond with Missed or Take {1} damage")
LOCALE_VALUE(STATUS_BANG_DAMAGE_STRONG,           "{0} ... Respond with {1} Missed or Take {2} damage")
LOCALE_VALUE(STATUS_BANG_OTHER,                   "{0} must respond to {1}")
LOCALE_VALUE(STATUS_CARD_AS_BANG,                 "{0} as Bang! ... Respond with Missed or Take damage")
LOCALE_VALUE(STATUS_CARD_AS_BANG_STRONG,          "{0} as Bang! ... Respond with {1} Missed or Take damage")
LOCALE_VALUE(STATUS_CARD_AS_BANG_DAMAGE,          "{0} as Bang! ... Respond with Missed or Take {1} damage")
LOCALE_VALUE(STATUS_CARD_AS_BANG_DAMAGE_STRONG,   "{0} as Bang! ... Respond with {1} Missed or Take {2} damage")
LOCALE_VALUE(STATUS_CARD_AS_BANG_OTHER,           "{0} must respond to {1} as Bang!")
LOCALE_VALUE(STATUS_CARD_AS_GATLING,              "{0} as Gatling ... Respond with Missed or Take damage")
LOCALE_VALUE(STATUS_CARD_AS_GATLING_OTHER,        "{0} must respond to {1} as Gatling")
LOCALE_VALUE(STATUS_INDIANS,                      "{0} ... Respond with Bang or Take damage")
LOCALE_VALUE(STATUS_INDIANS_OTHER,                "{0} must respond to {1}")
LOCALE_VALUE(STATUS_DUEL,                         "{0} ... Respond with Bang or Take damage")
LOCALE_VALUE(STATUS_DUEL_OTHER,                   "{0} must respond to {1}")
LOCALE_VALUE(STATUS_DESTROY,                      "{0} to discard {1} ... You can respond with Escape")
LOCALE_VALUE(STATUS_DESTROY_FROM_HAND,            "{0} to discard a card from you hand ... You can respond with Escape")
LOCALE_VALUE(STATUS_DESTROY_OTHER,                "{1} to discard {0}'s {2}")
LOCALE_VALUE(STATUS_DESTROY_OTHER_FROM_HAND,      "{1} to discard a card from {0}'s hand")
LOCALE_VALUE(STATUS_STEAL,                        "{0} to steal {1} ... You can respond with Escape")
LOCALE_VALUE(STATUS_STEAL_FROM_HAND,              "{0} to steal a card from your hand ... You can respond with Escape")
LOCALE_VALUE(STATUS_STEAL_OTHER,                  "{1} to steal {0}'s {2}")
LOCALE_VALUE(STATUS_STEAL_OTHER_FROM_HAND,        "{1} to steal a card from {0}'s hand")
LOCALE_VALUE(STATUS_DEATH,                        "You must play beer to save yourself")
LOCALE_VALUE(STATUS_DEATH_PLURAL,                 "You must play {} beers to save yourself")
LOCALE_VALUE(STATUS_DEATH_OTHER,                  "{0} must play beer to escape death")
LOCALE_VALUE(STATUS_DEATH_OTHER_PLURAL,           "{0} must play {1} beers to escape death")
LOCALE_VALUE(STATUS_DISCARD_ALL,                  "You are dead! Discard all your cards")
LOCALE_VALUE(STATUS_DISCARD_ALL_OTHER,            "{0} is dead and must discard all their cards")
LOCALE_VALUE(STATUS_DISCARD_HAND,                 "{} ... you must discard your whole hand")
LOCALE_VALUE(STATUS_DISCARD_HAND_OTHER,           "{0} ... {1} must discard their whole hand")
LOCALE_VALUE(STATUS_SHERIFF_KILLED_DEPUTY,        "You killed your deputy! Discard all your cards")
LOCALE_VALUE(STATUS_SHERIFF_KILLED_DEPUTY_OTHER,  "{0} killed their deputy and must discard all their cards")
LOCALE_VALUE(STATUS_BANDIDOS,                     "{0} ... Discard two cards or Take damage")
LOCALE_VALUE(STATUS_BANDIDOS_OTHER,               "{0} must respond to {1}")
LOCALE_VALUE(STATUS_TORNADO,                      "{0} ... Discard a card to draw two")
LOCALE_VALUE(STATUS_TORNADO_OTHER,                "{1} ... {0} must discard a card to draw two")
LOCALE_VALUE(STATUS_POKER,                        "{0} ... Discard a card")
LOCALE_VALUE(STATUS_POKER_OTHER,                  "{1} ... {0} must discard a card")
LOCALE_VALUE(STATUS_POKER_DRAW,                   "{0} ... Choose which cards to draw")
LOCALE_VALUE(STATUS_POKER_DRAW_OTHER,             "{1} ... {0} must choose which cards to draw")
LOCALE_VALUE(STATUS_SAVED,                        "{0} ... Choose whether to draw from the deck or from the hand of {1}")
LOCALE_VALUE(STATUS_SAVED_OTHER,                  "{1} ... {0} must choose whether to draw from the deck or from the hand of {2}")
LOCALE_VALUE(STATUS_ADD_CUBE,                     "Choose which card to put a cube onto")
LOCALE_VALUE(STATUS_ADD_CUBE_OTHER,               "{0} must choose which card to put a cube onto")
LOCALE_VALUE(STATUS_ADD_CUBE_PLURAL,              "Choose which card to put {} cubes onto")
LOCALE_VALUE(STATUS_ADD_CUBE_PLURAL_OTHER,        "{0} must choose which card to put {1} cubes onto")
LOCALE_VALUE(STATUS_ADD_CUBE_FOR,                 "Choose which card to put a cube onto, for {0}")
LOCALE_VALUE(STATUS_ADD_CUBE_FOR_OTHER,           "{0} must choose which card to put a cube onto, for {1}")
LOCALE_VALUE(STATUS_ADD_CUBE_PLURAL_FOR,          "Choose which card to put {1} cubes onto, for {0}")
LOCALE_VALUE(STATUS_ADD_CUBE_PLURAL_FOR_OTHER,    "{0} must choose which card to put {2} cubes onto, for {1}")
LOCALE_VALUE(STATUS_MOVE_BOMB,                    "Choose which player to move {0} onto")
LOCALE_VALUE(STATUS_MOVE_BOMB_OTHER,              "{0} must choose which player to move {1} onto")
LOCALE_VALUE(STATUS_RUST,                         "{0} ... You can respond with Escape")
LOCALE_VALUE(STATUS_RUST_OTHER,                   "{1} against {0}")
LOCALE_VALUE(STATUS_RICOCHET,                     "{0} to discard {1} ... You can respond with Missed")
LOCALE_VALUE(STATUS_RICOCHET_OTHER,               "{1} to discard {0}'s {2}")
LOCALE_VALUE(STATUS_PEYOTE,                       "{0} ... Declare Red or Black")
LOCALE_VALUE(STATUS_PEYOTE_OTHER,                 "{1} ... {0} must declare Red or Black")
LOCALE_VALUE(STATUS_HANDCUFFS,                    "{0} ... Declare a suit")
LOCALE_VALUE(STATUS_HANDCUFFS_OTHER,              "{1} ... {0} must declare a suit")
LOCALE_VALUE(STATUS_KIT_CARLSON,                  "{0} ... Choose which cards to draw")
LOCALE_VALUE(STATUS_KIT_CARLSON_OTHER,            "{1} ... {0} must choose which cards to draw")
LOCALE_VALUE(STATUS_CLAUS_THE_SAINT,              "{0} ... Choose the cards to give to the other players")
LOCALE_VALUE(STATUS_CLAUS_THE_SAINT_OTHER,        "{1} ... {0} must choose the cards to give to the other players")
LOCALE_VALUE(STATUS_VERA_CUSTER,                  "{0} ... Choose which character to copy")
LOCALE_VALUE(STATUS_VERA_CUSTER_OTHER,            "{1} ... {0} must choose which character to copy")
LOCALE_VALUE(STATUS_YOUL_GRINNER,                 "{0} ... Give {1} a card")
LOCALE_VALUE(STATUS_YOUL_GRINNER_OTHER,           "{0} ... {2} must give {1} a card")
LOCALE_VALUE(STATUS_DUTCH_WILL,                   "{0} ... Choose which card to draw")
LOCALE_VALUE(STATUS_DUTCH_WILL_OTHER,             "{1} ... {0} must choose which card to draw")
LOCALE_VALUE(STATUS_THEDALTONS,                   "{0} ... Discard a blue card")
LOCALE_VALUE(STATUS_THEDALTONS_OTHER,             "{0} must discard a blue card")
LOCALE_VALUE(STATUS_CAN_PLAY_CARD,                "You can play {0}")
LOCALE_VALUE(STATUS_CAN_PLAY_CARD_OTHER,          "{0} can play {1}")
LOCALE_VALUE(STATUS_DAMAGING,                     "{0} takes 1 damage for {1}")
LOCALE_VALUE(STATUS_DAMAGING_PLURAL,              "{0} takes {2} damage for {1}")
LOCALE_VALUE(STATUS_DAMAGING_AS_BANG,             "{0} takes 1 damage for {1} as Bang!")
LOCALE_VALUE(STATUS_DAMAGING_AS_BANG_PLURAL,      "{0} takes {2} damage for {1} as Bang!")
LOCALE_VALUE(STATUS_DAMAGING_AS_GATLING,          "{0} takes 1 damage for {1} as Gatling!")
LOCALE_VALUE(STATUS_CAN_PLAY_TUMBLEWEED,          "{0} \"draws!\" {3} for {2} ... You can play {1}")
LOCALE_VALUE(STATUS_CAN_PLAY_TUMBLEWEED_OTHER,    "{0} \"draws!\" {3} for {2} ... {4} can play {1}")
LOCALE_VALUE(STATUS_CAN_PLAY_TUMBLEWEED_FOR,      "{0} \"draws!\" for {2} ... You can play {1}")
LOCALE_VALUE(STATUS_CAN_PLAY_TUMBLEWEED_FOR_OTHER,"{0} \"draws!\" for {2} ... {3} can play {1}")
LOCALE_VALUE(STATUS_SWITCH_CARDS,                 "{0} to switch {1} with {2} ... You can respond with Escape")
LOCALE_VALUE(STATUS_SWITCH_CARDS_OTHER,           "{1} against {0} to switch {2} with {3}")
LOCALE_VALUE(STATUS_LASTWILL,                     "You can play {0} to give up to three cards to a player")
LOCALE_VALUE(STATUS_LASTWILL_OTHER,               "{1} can play {0}")
LOCALE_VALUE(STATUS_NEWIDENTITY,                  "{0} ... Choose which character to switch to")
LOCALE_VALUE(STATUS_NEWIDENTITY_OTHER,            "{1} ... {0} must choose which character to switch to")
LOCALE_VALUE(STATUS_FORCE_PLAY_CARD,              "You must play {0}")
LOCALE_VALUE(STATUS_FORCE_PLAY_CARD_OTHER,        "{0} must play {1}")
LOCALE_VALUE(STATUS_FORCE_EQUIP_CARD,             "You must equip {0}")
LOCALE_VALUE(STATUS_FORCE_EQUIP_CARD_OTHER,       "{0} must equip {1}")
LOCALE_VALUE(STATUS_MULTI_VULTURE_SAM,            "{0} ... you must steal a card from {1}")
LOCALE_VALUE(STATUS_MULTI_VULTURE_SAM_OTHER,      "{0} ... {1} must steal a card from {2}")
LOCALE_VALUE(STATUS_RANCH,                        "{0} ... You may discard any number of cards from the hand to draw the same amount")
LOCALE_VALUE(STATUS_RANCH_OTHER,                  "{0} ... {1} may discard any number of cards from the hand to draw the same amount")
LOCALE_VALUE(STATUS_SGT_BLAZE_LOCOMOTIVE,         "{0} ... You can ignore the effect of the locomotive against a player")
LOCALE_VALUE(STATUS_SGT_BLAZE_LOCOMOTIVE_OTHER,   "{0} ... {1} can ignore the effect of the locomotive against a player")
LOCALE_VALUE(STATUS_CATTLE_TRUCK,                 "{0} ... Choose a card to draw")
LOCALE_VALUE(STATUS_CATTLE_TRUCK_OTHER,           "{1} ... {0} must choose a card to draw")
LOCALE_VALUE(STATUS_DISCARD_TABLE,                "{0} ... Discard a card in play")
LOCALE_VALUE(STATUS_DISCARD_TABLE_OTHER,          "{1} ... {0} must discard a card in play")
LOCALE_VALUE(STATUS_LOUNGE_CAR,                   "{0} ... Give one of the railcars drawn to another player")
LOCALE_VALUE(STATUS_LOUNGE_CAR_OTHER,             "{1} ... {0} must give one of the railcars drawn to another player")
LOCALE_VALUE(STATUS_MAIL_CAR,                     "{0} ... Give one of the cards drawn to another player")
LOCALE_VALUE(STATUS_MAIL_CAR_OTHER,               "{1} ... {0} must give one of the cards drawn to another player")
LOCALE_VALUE(STATUS_MAP,                          "{0} ... Discard one of the cards or Confirm")
LOCALE_VALUE(STATUS_MAP_OTHER,                    "{1} ... {0} must discard on of the cards or confirm")
LOCALE_VALUE(STATUS_MOST_WANTED,                  "{0} ... You can respond with Escape")
LOCALE_VALUE(STATUS_MOST_WANTED_OTHER,            "{1} against {0}")
LOCALE_VALUE(STATUS_TRAIN_ROBBERY,                "{0} ... choose a card")
LOCALE_VALUE(STATUS_TRAIN_ROBBERY_OTHER,          "{1} ... {0} must choose a card")
LOCALE_VALUE(STATUS_TRAIN_ROBBERY_CHOOSE,         "{0} ... Choose between discarding {1} or receiving a Bang")
LOCALE_VALUE(STATUS_TRAIN_ROBBERY_CHOOSE_OTHER,   "{1} ... {0} must choose between discarding {2} or receiving a Bang")

LOCALE_VALUE(ERROR_INVALID_LOBBY,                 "Invalid Lobby ID")
LOCALE_VALUE(ERROR_PLAYER_IN_LOBBY,               "Player already in a lobby")
LOCALE_VALUE(ERROR_PLAYER_NOT_IN_LOBBY,           "Player not in a lobby")
LOCALE_VALUE(ERROR_PLAYER_NOT_LOBBY_OWNER,        "Not owner of lobby")
LOCALE_VALUE(ERROR_USER_NOT_CONTROLLING_PLAYER,   "Player not in game")
LOCALE_VALUE(ERROR_USER_CONTROLLING_PLAYER,       "Player already in game")
LOCALE_VALUE(ERROR_NOT_ENOUGH_PLAYERS,            "Not enough players")
LOCALE_VALUE(ERROR_LOBBY_NOT_WAITING,             "Lobby not waiting")
LOCALE_VALUE(ERROR_LOBBY_NOT_PLAYING,             "Lobby not playing")
LOCALE_VALUE(ERROR_LOBBY_NOT_FINISHED,            "Lobby not finished")
LOCALE_VALUE(ERROR_INVALID_REJOIN_TARGET,         "You can't enter the game as this player")
LOCALE_VALUE(ERROR_PLAYER_DOES_NOT_OWN_CARD,      "Card is not yours")
LOCALE_VALUE(ERROR_CARD_NOT_FOUND,                "Card not found")
LOCALE_VALUE(ERROR_INVALID_ACTION,                "Invalid action")
LOCALE_VALUE(ERROR_NOT_ENOUGH_GOLD,               "Not enough gold nuggets")
LOCALE_VALUE(ERROR_NOT_ENOUGH_CUBES,              "Not enough cubes")
LOCALE_VALUE(ERROR_NOT_ENOUGH_CUBES_ON,           "Not enough cubes on {}")
LOCALE_VALUE(ERROR_CARD_HAS_FULL_CUBES,           "{} already has 4 cubes")
LOCALE_VALUE(ERROR_INVALID_TARGETS,               "Invalid targets")
LOCALE_VALUE(ERROR_PLAYER_MUST_DRAW,              "You must draw")
LOCALE_VALUE(ERROR_PLAYER_MUST_NOT_DRAW,          "You must not draw now")
LOCALE_VALUE(ERROR_CANT_DISCARD_OWN_BLACK,        "You can't discard your own black cards")
LOCALE_VALUE(ERROR_CARD_DISABLED_BY,              "{0} is disabled by {1}")
LOCALE_VALUE(ERROR_INVALID_SUIT,                  "You can't play {1}: invalid suit for {0}")
LOCALE_VALUE(ERROR_CARD_INACTIVE,                 "{} is inactive in this turn")
LOCALE_VALUE(ERROR_CANT_EQUIP_CARDS,              "You can't equip cards")
LOCALE_VALUE(ERROR_DUPLICATED_CARD,               "Duplicated card: {}")
LOCALE_VALUE(ERROR_TARGET_PLAYING_CARD,           "You can't target the same card you're playing")
LOCALE_VALUE(ERROR_TARGET_NOT_PLAYER,             "Target is not a player")
LOCALE_VALUE(ERROR_TARGET_NOT_DEAD,               "You can't target a live player")
LOCALE_VALUE(ERROR_TARGET_DEAD,                   "You can't target a dead player")
LOCALE_VALUE(ERROR_TARGET_SHERIFF,                "You can't target the sheriff")
LOCALE_VALUE(ERROR_TARGET_NOT_SELF,               "You can only target yourself")
LOCALE_VALUE(ERROR_TARGET_SELF,                   "You can't target yourself")
LOCALE_VALUE(ERROR_TARGET_ORIGIN,                 "You can't target your attacker")
LOCALE_VALUE(ERROR_TARGET_EMPTY_HAND,             "You can't target a player with an empty hand")
LOCALE_VALUE(ERROR_TARGET_EMPTY_TABLE,            "You can't target a player with no cards in play")
LOCALE_VALUE(ERROR_TARGET_EMPTY_CUBES,            "You can't target a player with no cubes")
LOCALE_VALUE(ERROR_TARGET_NOT_IN_RANGE,           "Target out of range")
LOCALE_VALUE(ERROR_TARGETS_NOT_UNIQUE,            "Targets are not unique")
LOCALE_VALUE(ERROR_TARGETS_NOT_ADJACENT,          "Targets are not adjacent")
LOCALE_VALUE(ERROR_TARGET_NOT_CARD,               "This card is not targetable")
LOCALE_VALUE(ERROR_TARGET_BLACK_CARD,             "You can't target black cards")
LOCALE_VALUE(ERROR_TARGET_NOT_SELECTION_CARD,     "You can only target selection cards")
LOCALE_VALUE(ERROR_TARGET_NOT_TABLE_CARD,         "You can only target cards in play")
LOCALE_VALUE(ERROR_TARGET_NOT_HAND_CARD,          "You can only target cards from the hand")
LOCALE_VALUE(ERROR_TARGET_NOT_BLUE_CARD,          "You can only target blue cards")
LOCALE_VALUE(ERROR_TARGET_NOT_TRAIN,              "You can only target railcars")
LOCALE_VALUE(ERROR_TARGET_TRAIN,                  "You can't target railcars")
LOCALE_VALUE(ERROR_TARGET_NOT_BLUE_OR_TRAIN,      "You can only target blue cards or railcars")
LOCALE_VALUE(ERROR_TARGET_NOT_HEARTS,             "You can only target hearts cards")
LOCALE_VALUE(ERROR_TARGET_NOT_DIAMONDS,           "You can only target diamonds cards")
LOCALE_VALUE(ERROR_TARGET_NOT_CLUBS,              "You can only target clubs cards")
LOCALE_VALUE(ERROR_TARGET_NOT_SPADES,             "You can only target spades cards")
LOCALE_VALUE(ERROR_NO_ORIGIN_CARD_SUIT,           "Invalid card suit")
LOCALE_VALUE(ERROR_TARGET_NOT_TWO_TO_NINE,        "You can only target cards ranked 2 to 9")
LOCALE_VALUE(ERROR_TARGET_NOT_TEN_TO_ACE,         "You can only target cards ranked 10 to A")
LOCALE_VALUE(ERROR_TARGET_NOT_BANG,               "You can only target Bang! cards")
LOCALE_VALUE(ERROR_TARGET_NOT_MISSED,             "You can only target Missed! cards")
LOCALE_VALUE(ERROR_TARGET_NOT_BEER,               "You can only target Beer cards")
LOCALE_VALUE(ERROR_TARGET_NOT_CATBALOU_OR_PANIC,  "You can only target Cat Balou or Panic! cards")
LOCALE_VALUE(ERROR_TARGET_NOT_BRONCO,             "You can only target Bronco")
LOCALE_VALUE(ERROR_SCENARIO_AT_PLAY,              "{} is at play")
LOCALE_VALUE(ERROR_CANT_PLAY_CARD,                "You can't play {}")
LOCALE_VALUE(ERROR_ONE_BANG_PER_TURN,             "You can only play one Bang card per turn")
LOCALE_VALUE(ERROR_CANT_SELF_DAMAGE,              "You can't take off the last life point")
LOCALE_VALUE(ERROR_CANT_HEAL_PAST_FULL_HP,        "You can't heal yourself past the last life point")
LOCALE_VALUE(ERROR_NOT_START_OF_TURN,             "It's not the start of your turn")
LOCALE_VALUE(ERROR_DISCARD_PILE_EMPTY,            "The discard pile is empty")
LOCALE_VALUE(ERROR_MAX_USAGES,                    "You can't play {0} more than {1} times per turn")
LOCALE_VALUE(ERROR_MANDATORY_CARD,                "Playing {} is mandatory")
LOCALE_VALUE(ERROR_TARGET_NOT_UNIQUE,             "Targets must be unique")
LOCALE_VALUE(ERROR_CANNOT_REPEAT_CARD,            "You can't play {} twice in a row")
LOCALE_VALUE(ERROR_CANNOT_PLAY_WHILE_EQUIPPING,   "You can't play {} while equipping a card")
LOCALE_VALUE(ERROR_NO_RANGED_TARGET,              "You can't play {0} because {1} has no range limit")
LOCALE_VALUE(ERROR_CANNOT_SKIP_PLAYER,            "You can't skip the effect against {0}")
LOCALE_VALUE(ERROR_TRAIN_NOT_IN_ANY_STATION,      "This railcar is not paired to any station")
LOCALE_VALUE(ERROR_TRAIN_NOT_IN_THIS_STATION,     "This railcar is not paired to this station")

LOCALE_VALUE(LOG_GAME_START,                      "Game started")
LOCALE_VALUE(LOG_GAME_OVER,                       "Game over")
LOCALE_VALUE(LOG_DECK_RESHUFFLED,                 "The deck is reshuffled")
LOCALE_VALUE(LOG_SHOP_RESHUFFLED,                 "The shop deck is reshuffled")
LOCALE_VALUE(LOG_TURN_START,                      "It's {0}'s turn")
LOCALE_VALUE(LOG_SOLD_BEER,                       "{0} sells {1}")
LOCALE_VALUE(LOG_DISCARDED_CARD,                  "{0} forces {1} to discard {2}")
LOCALE_VALUE(LOG_DISCARDED_SELF_CARD,             "{0} discards {1}")
LOCALE_VALUE(LOG_DISCARDED_A_CARD_FOR,            "{1} discards a card for {0}")
LOCALE_VALUE(LOG_DISCARDED_CARD_FOR,              "{1} discards {2} for {0}")
LOCALE_VALUE(LOG_DISCARDED_ORANGE_CARD,           "{0} must discard {1}")
LOCALE_VALUE(LOG_STOLEN_CARD,                     "{0} steals {1}'s {2}")
LOCALE_VALUE(LOG_STOLEN_CARD_FROM_HAND,           "{0} steals a card from {1}'s hand")
LOCALE_VALUE(LOG_STOLEN_SELF_CARD,                "{0} redraws {1}")
LOCALE_VALUE(LOG_STOLEN_SELF_CARD_FROM_HAND,      "{0} redraws {1} from their hand")
LOCALE_VALUE(LOG_DRAWN_WITH_CHARACTER,            "{1} draws using {0}")
LOCALE_VALUE(LOG_DRAWN_FROM_GENERALSTORE,         "{0} draws {1} for {2}")
LOCALE_VALUE(LOG_PLAYED_CHARACTER,                "{1} plays {0}'s effect")
LOCALE_VALUE(LOG_RESPONDED_WITH_CHARACTER,        "{1} responds with {0}'s effect")
LOCALE_VALUE(LOG_PLAYED_CARD,                     "{1} plays {0}")
LOCALE_VALUE(LOG_PLAYED_CARD_ON,                  "{1} plays {0} on {2}")
LOCALE_VALUE(LOG_PLAYED_CARD_STEAL,               "{1} plays {0} to steal {3} from {2}")
LOCALE_VALUE(LOG_PLAYED_CARD_STEAL_HAND,          "{1} plays {0} to steal a card from {2}'s hand")
LOCALE_VALUE(LOG_PLAYED_CARD_STEAL_OWN,           "{1} plays {0} to redraw {2}")
LOCALE_VALUE(LOG_PLAYED_CARD_STEAL_OWN_HAND,      "{1} plays {0} to redraw a card from the hand")
LOCALE_VALUE(LOG_PLAYED_CARD_DESTROY,             "{1} plays {0} to discard {3} from {2}")
LOCALE_VALUE(LOG_PLAYED_CARD_DESTROY_HAND,        "{1} plays {0} to discard a card from {2}'s hand")
LOCALE_VALUE(LOG_PLAYED_CARD_DESTROY_OWN,         "{1} plays {0} to discard {2}")
LOCALE_VALUE(LOG_PLAYED_CARD_AS_BANG_ON,          "{1} plays {0} as Bang! on {2}")
LOCALE_VALUE(LOG_PLAYED_CARD_AS_GATLING,          "{1} plays {0} as Gatling")
LOCALE_VALUE(LOG_PLAYED_TABLE_CARD,               "{1} plays {0} from the table")
LOCALE_VALUE(LOG_EQUIPPED_CARD,                   "{1} equips {0}")
LOCALE_VALUE(LOG_EQUIPPED_CARD_TO,                "{1} equips {0} on {2}")
LOCALE_VALUE(LOG_BOUGHT_CARD,                     "{1} buys and plays {0}")
LOCALE_VALUE(LOG_BOUGHT_EQUIP,                    "{1} buys and equips {0}")
LOCALE_VALUE(LOG_BOUGHT_EQUIP_TO,                 "{1} buys and equips {0} to {2}")
LOCALE_VALUE(LOG_RESPONDED_WITH_CARD,             "{1} responds with {0}")
LOCALE_VALUE(LOG_RESPONDED_WITH_CARD_AS_MISSED,   "{1} responds with {0} as Missed!")
LOCALE_VALUE(LOG_DRAWN_FROM_DECK,                 "{0} draws from the deck")
LOCALE_VALUE(LOG_DRAWN_CARD,                      "{0} draws {1}")
LOCALE_VALUE(LOG_DRAWN_A_CARD,                    "{0} draws a card")
LOCALE_VALUE(LOG_DRAWN_N_CARDS,                   "{0} draws {1} cards")
LOCALE_VALUE(LOG_DRAWN_CARD_FOR,                  "{0} draws {1} for {2}")
LOCALE_VALUE(LOG_DRAWN_A_CARD_FOR,                "{0} draws a card for {1}")
LOCALE_VALUE(LOG_DRAWN_N_CARDS_FOR,               "{0} draws {1} cards for {2}")
LOCALE_VALUE(LOG_DRAWN_FROM_DISCARD,              "{0} draws {1} from the top of the discard pile")
LOCALE_VALUE(LOG_REVEALED_CARD,                   "{0} reveals {1}")
LOCALE_VALUE(LOG_CHECK_DREW_CARD,                 "{1} \"draws!\" {2} for {0}")
LOCALE_VALUE(LOG_TAKEN_DAMAGE,                    "{1} takes 1 damage for {0}")
LOCALE_VALUE(LOG_TAKEN_DAMAGE_PLURAL,             "{1} takes {2} damage for {0}")
LOCALE_VALUE(LOG_TAKEN_DAMAGE_AS_BANG,            "{1} takes 1 damage for {0} as Bang!")
LOCALE_VALUE(LOG_TAKEN_DAMAGE_AS_BANG_PLURAL,     "{1} takes {2} damage for {0} as Bang!")
LOCALE_VALUE(LOG_TAKEN_DAMAGE_AS_GATLING,         "{1} takes 1 damage for {0} as Gatling")
LOCALE_VALUE(LOG_HEALED,                          "{0} heals for 1 life point")
LOCALE_VALUE(LOG_HEALED_PLURAL,                   "{0} heals for {1} life points")
LOCALE_VALUE(LOG_PLAYER_KILLED,                   "{0} killed {1}")
LOCALE_VALUE(LOG_PLAYER_DIED,                     "{0} died")
LOCALE_VALUE(LOG_JAIL_BREAK,                      "{} breaks from jail")
LOCALE_VALUE(LOG_SKIP_TURN,                       "{} skips the turn")
LOCALE_VALUE(LOG_CARD_EXPLODES,                   "{} explodes!")
LOCALE_VALUE(LOG_CARD_HAS_EFFECT,                 "{}'s effect is activated")
LOCALE_VALUE(LOG_CHARACTER_CHOICE,                "{0} has {1} as character")
LOCALE_VALUE(LOG_DRAWN_SHOP_CARD,                 "{} gets revealed from the shop")
LOCALE_VALUE(LOG_KILLED_OUTLAW,                   "{} killed an outlaw!")
LOCALE_VALUE(LOG_SHERIFF_KILLED_DEPUTY,           "{} killed the deputy!")
LOCALE_VALUE(LOG_MOVE_BOMB_ON,                    "{1} moves {0} on {2}")
LOCALE_VALUE(LOG_GIFTED_CARD,                     "{0} gives {2} to {1}")
LOCALE_VALUE(LOG_GIFTED_A_CARD,                   "{0} gives {1} a card")
LOCALE_VALUE(LOG_COPY_CHARACTER,                  "{0} copies the effect of {1}")
LOCALE_VALUE(LOG_DRAWN_SCENARIO_CARD,             "{} is active")
LOCALE_VALUE(LOG_RECEIVED_N_BANGS_FOR,            "{0} receives {2} Bang! for {1}")
LOCALE_VALUE(LOG_MANDATORY_CARD,                  "{0} must play {1} in phase two")
LOCALE_VALUE(LOG_DECLARED_RED,                    "{0} declares Red per {1}")
LOCALE_VALUE(LOG_DECLARED_BLACK,                  "{0} declares Black per {1}")
LOCALE_VALUE(LOG_DECLARED_CLUBS,                  "{0} declares Clubs per {1}")
LOCALE_VALUE(LOG_DECLARED_DIAMONDS,               "{0} declares Diamonds per {1}")
LOCALE_VALUE(LOG_DECLARED_HEARTS,                 "{0} declares Hearts per {1}")
LOCALE_VALUE(LOG_DECLARED_SPADES,                 "{0} declares Spades per {1}")
LOCALE_VALUE(LOG_POKER_REVEAL,                    "{1} is revealed for {0}")
LOCALE_VALUE(LOG_POKER_ACE,                       "There is an ace, all cards are discarded")
LOCALE_VALUE(LOG_REVIVE,                          "{0} revives for {1}")
LOCALE_VALUE(LOG_SWAP_CARDS,                      "{0} swaps {2} with {1}'s {3}")
LOCALE_VALUE(LOG_PLAYER_IMMUNE_TO_CARD,           "{0} is immune to {1} for {2}")
LOCALE_VALUE(LOG_DEFLECTED_BANG_TO,               "{1} uses {0} to deflect {2} to {3}")
LOCALE_VALUE(LOG_TRAIN_ADVANCE,                   "The train advances")
LOCALE_VALUE(LOG_PAID_FOR_STATION,                "{1} pays the price for station {0}")
LOCALE_VALUE(LOG_END_OF_LINE,                     "End of the line! The effect of the locomotive is activated")

LOCALE_VALUE(lobby_state::waiting,                "Waiting")
LOCALE_VALUE(lobby_state::playing,                "Playing")
LOCALE_VALUE(lobby_state::finished,               "Finished")

LOCALE_VALUE(player_role::sheriff,                      "Sheriff")
LOCALE_VALUE(player_role::deputy,                       "Deputy")
LOCALE_VALUE(player_role::outlaw,                       "Outlaw")
LOCALE_VALUE(player_role::renegade,                     "Renegade")

LOCALE_VALUE(game_options::expansions,                  "Expansions")
LOCALE_VALUE(game_options::character_choice,            "Character Choice")
LOCALE_VALUE(game_options::enable_ghost_cards,          "Enable Ghost cards")
LOCALE_VALUE(game_options::allow_beer_in_duel,          "Allow Beer in duel")
LOCALE_VALUE(game_options::quick_discard_all,           "Quick Discard All")
LOCALE_VALUE(game_options::scenario_deck_size,          "Scenario Cards")
LOCALE_VALUE(game_options::num_bots,                    "Number of Bots")
LOCALE_VALUE(game_options::damage_timer,                "Damage Timer")
LOCALE_VALUE(game_options::escape_timer,                "Escape Timer")
LOCALE_VALUE(game_options::bot_play_timer,              "Bot Play Timer")
LOCALE_VALUE(game_options::tumbleweed_timer,            "Tumbleweed Timer")

LOCALE_VALUE(expansion_type::thebullet,                 "The Bullet")
LOCALE_VALUE(expansion_type::dodgecity,                 "Dodge City")
LOCALE_VALUE(expansion_type::valleyofshadows,           "Valley of Shadows")
LOCALE_VALUE(expansion_type::greattrainrobbery,         "The Great Train Robbery")
LOCALE_VALUE(expansion_type::wildwestshow,              "Wild West Show")
LOCALE_VALUE(expansion_type::goldrush,                  "Gold Rush")
LOCALE_VALUE(expansion_type::armedanddangerous,         "Armed And Dangerous")
LOCALE_VALUE(expansion_type::highnoon,                  "High Noon")
LOCALE_VALUE(expansion_type::fistfulofcards,            "Fistful of Cards")
LOCALE_VALUE(expansion_type::canyondiablo,              "Canyon Diablo")

END_LOCALE()