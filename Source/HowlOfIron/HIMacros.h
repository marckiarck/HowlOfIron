#pragma once


#define REMOVE_GAMEPLAY_EFFECT_WITH_TAG(_TAG) \
	FGameplayTagContainer tagContainer = FGameplayTagContainer(); \
	FGameplayTag gameplayTag = FGameplayTag::RequestGameplayTag(_TAG); \
	tagContainer.AddTag(gameplayTag); \
	abilitySystem->RemoveActiveEffectsWithTags(tagContainer)

#define CANCEL_JUMP \
	buttonHUD->SetVisibility(false); \
	widgetref->arrow->SetVisibility(ESlateVisibility::Hidden); \
	targetWall = nullptr; \
	REMOVE_GAMEPLAY_EFFECT_WITH_TAG(FName(TEXT("Werewolf.Ability.Canjump")))

// Game trace channels
#define GAME_TRACE_BUILDING ECC_GameTraceChannel1
#define GAME_TRACE_ENEMY ECC_GameTraceChannel2
#define GAME_TRACE_WALL ECC_GameTraceChannel3
#define GAME_TRACE_SHOOT ECC_GameTraceChannel4
#define GAME_TRACE_ANCHORAGE ECC_GameTraceChannel5
#define GAME_TRACE_WEREWOLF ECC_GameTraceChannel6
#define GAME_TRACE_STEAM ECC_GameTraceChannel7

// Game modes
#if WITH_EDITOR
	# define CHEATS 1
#else
	# define CHEATS 0
#endif

// Collision presets
#define COLLISION_WALL FName(TEXT("Wall"))
#define COLLISION_WEREWOLF FName(TEXT("Werewolf"))
#define COLLISION_JUMPING FName(TEXT("Jumping"))

//Debug colors
#define HIT_COLOR FColor::Red
#define NO_HIT_COLOR FColor::Green

//Tags
#define CHARGED_ATTRIBUTE_TAGS "Data.ChargedAttribute"
#define DETECTION_ATTRIBUTE_TAGS "Data.DetectionAttribute"
#define CAMERA_MOVE_DISABLED_TAG "Character.Input.Block.Camera"
#define MOVE_DISABLED_TAG "Character.Input.Block.Move"
#define DESPAWNED_TAG "Character.State.Despawned"
#define COMBAT_SHOOT_TAG "Data.BT.Shoot"
#define COMBAT_FLEE_TAG "Data.BT.Flee"
#define COMBAT_MOVE_TAG "Data.BT.Move"
#define COMBAT_ALARM_TAG "Data.BT.Alarm"
#define ALERT_TO_PATROL_TAG "Data.BT.AlertToPatrol"
#define STOP_BT_TAG "Data.BT.Stop"
#define SHOOT_COOLDOWN_TAG "Enemy.Ability.Shoot.Cooldown"
#define ABILITY1_COOLDOWN_TAG "Enemy.Ability.Ability1.Cooldown"
#define ABILITY2_COOLDOWN_TAG "Enemy.Ability.Ability2.Cooldown"
#define ABILITY3_COOLDOWN_TAG "Enemy.Ability.Ability3.Cooldown"
#define GRANADE_LAUNCH_TAG "Enemy.Trigger.Granade"
#define ALERT_TAG "Enemy.Trigger.Alert"
#define PATROL_TAG "Enemy.Trigger.Patrol"
#define ENEMY_REINFORCEMENT_TAG "Enemy.Ability.Reinforcement"
#define STUN_TAG "Character.State.Stuned"
#define FLINCH_TAG "Character.State.Flinch"
#define FLYBACK_TAG "Character.State.Flyback"
#define TRIP_TAG "Character.State.Trip"
#define YELLOW_MUTTON_TAG "Enemy.Class.YellowMutton"
#define WHITE_MUTTON_TAG "Enemy.Class.WhiteMutton"
#define GREEN_MUTTON_TAG "Enemy.Class.GreenMutton"
#define MUTTON_TAG "Enemy.Class.Mutton"
#define HUNTER_TAG "Enemy.Class.Hunter"
#define OWLMAN_TAG "Enemy.Class.OwlMan"
#define DEAD_TAG "Character.Ability.Dead"
#define HIGHSTEAM_TAG "Steam.Steamhigh"
#define LOWSTEAM_TAG "Steam.Steamlow"
#define DATA_DETECTION_TAG "Data.Detection.Value"
#define SHOOTING_TAG "Enemy.Ability.Shoot"
#define COMBO_TAG "Werewolf.Ability.Combo.Active"
#define END_COMBO_TAG "Werewolf.Ability.Combo.EndAbility"
#define HIT_TAG "Werewolf.Ability.Combo.Hitted"
#define COMBO_ABILITY_TAG "Werewolf.Ability.Combo.ComboAbility"
#define ENEMY_DISABLE_TAG "Character.State.Disabled"
#define THROW_ENEMY_TAG "Werewolf.Ability.Launch.Trigger"
#define DODGE_TAG "Enemy.Ability.Dodge"
#define REGENEATION_TRIGGER_TAG "Werewolf.Ability.triggerRegeneration"
#define BOSS_TAG "Enemy.Class.Boss"
#define INMUNITY_TAG "Character.State.Immunity"
#define DISABLE_DISTANCE_TAG "Character.State.DistanceDisable"
#define EXECUTION_TAG "Werewolf.Ability.DoingExecution"


#define DEFINE_TAG_CONTAINER \
	FGameplayTagContainer tagclass;

#define DEFINED_TAG_CONTAINER \
	tagclass

#define GET_GAMEPLAY_TAG(TAG_NAME) \
	FGameplayTag::RequestGameplayTag(FName(TAG_NAME))

#define ADD_TAG_TO_CONTIANER(TAG_NAME) \
	DEFINED_TAG_CONTAINER.AddTag(GET_GAMEPLAY_TAG(TAG_NAME));

#define COMBAT_TAGS_EXECUTE_MACRO(MACRO_NAME) \
	FE_3(MACRO_NAME, COMBAT_SHOOT_TAG, COMBAT_FLEE_TAG, COMBAT_MOVE_TAG);

#define GET_ENEMY_TAGS(CONATINER_NAME) \
	DEFINE_TAG_CONTAINER \
	FE_6(ADD_TAG_TO_CONTIANER, MUTTON_TAG, GREEN_MUTTON_TAG, WHITE_MUTTON_TAG, YELLOW_MUTTON_TAG,OWLMAN_TAG,HUNTER_TAG); \
	CONATINER_NAME = DEFINED_TAG_CONTAINER;

#define GET_BLOCK_INPUT_TAGS(CONTAINER_NAME) \
	DEFINE_TAG_CONTAINER\
	FE_2(ADD_TAG_TO_CONTIANER, MOVE_DISABLED_TAG, CAMERA_MOVE_DISABLED_TAG); \
	CONTAINER_NAME = DEFINED_TAG_CONTAINER;

#define GET_CLASS_ENEMIES \
FGameplayTagContainer tagClass; \
tagClass.Add()

#define CHECK_HAS_TAG(ABILITY_SYSTEM, TAG_NAME, OUTPUT_BOOLEAN) \
{ \
FGameplayTagContainer abilitySystemTags; \
ABILITY_SYSTEM->GetOwnedGameplayTags(abilitySystemTags); \
if (abilitySystemTags.HasTag(GET_GAMEPLAY_TAG(TAG_NAME))) \
{ \
	OUTPUT_BOOLEAN = true; \
} \
else \
{ \
	OUTPUT_BOOLEAN = false; \
}; \
}


/*
* Patrol macros
*/
#define REMOVE_GAMEPLAY_TAG(TAG_NAME) \
	if (enemyTags.HasTag(GET_GAMEPLAY_TAG(TAG_NAME))) \
	{ \
		enemyAbilitySystem->RemoveLooseGameplayTag(GET_GAMEPLAY_TAG(TAG_NAME)); \
	}


/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

/*
* Voice actors macros
*/

#define RETURNED_FSTRING_MACRO_VARIABLE returnedString_macro /*_macro to avoid override existing variables*/

#define VOICE_ACTORS_CASE(NAME_TYPE, OUTPUT_FSTRING) \
	FString RETURNED_FSTRING_MACRO_VARIABLE; \
 \
	switch (NAME_TYPE) \
	{ \
		VOICE_ACTORS(VOICE_ACTOR_CASE); \
	default: \
		RETURNED_FSTRING_MACRO_VARIABLE = TEXT("_Josh"); \
	} \
\
OUTPUT_FSTRING = RETURNED_FSTRING_MACRO_VARIABLE;


#define VOICE_ACTOR_CASE(VOICE_ACTOR) \
	case VOICE_ACTOR: \
	{ \
		RETURNED_FSTRING_MACRO_VARIABLE = TEXT("_"); \
		RETURNED_FSTRING_MACRO_VARIABLE.Append(TEXT(#VOICE_ACTOR)); \
	}; \
	break;

#define VOICE_ACTORS(MACRO_NAME) \
    FE_5(MACRO_NAME, Josh, Ellis, Ivan, Diego, Guille)
	/* Remember put NUM_NAME_TYPES in HIEnemy equals to FE_X */

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

/*
* Debug macros
*/

#define FSTRING_VARIABLE(VARIABLE_NAME) \
	FString VARIABLE_NAME;

#define ARCHIVE_ASSIGN(VARIABLE_NAME) \
	Ar << VARIABLE_NAME;

#define CREATE_FABILITYSYS_STRUCT(ATTRIBUTES_MACRO) \
    struct FAbilitySys \
	{ \
	FString actorName; \
	ATTRIBUTES_MACRO(FSTRING_VARIABLE); \
\
	void Serialize(FArchive& Ar) \
	{ \
		Ar << actorName; \
		ATTRIBUTES_MACRO(ARCHIVE_ASSIGN); \
	}; \
	} DataPack; 

#define COLLECT_DATA_MACRO(ATTRIBUTE) \
    DataPack.ATTRIBUTE = FString::SanitizeFloat(player->HIGetAttributes()->Get##ATTRIBUTE());

#define DRAW_DATA_MACRO(ATTRIBUTE) \
	CanvasContext.Printf(TEXT("{cyan}[%s]{white} == {white}(%s)"), TEXT(#ATTRIBUTE), *DataPack.##ATTRIBUTE);


////////////////////////////////////////////////////////
///////////////////////////////////////////////////////



//Macros for GAS attributes
#define CHARACTER_ATTRIBUTES(MACRO_NAME) \
    FE_6(MACRO_NAME, maxHealth, health, chargedValue, damage1, damage2, speed);

#define WEREWOLF_ATTRIBUTES(MACRO_NAME) \
    FE_4(MACRO_NAME, armour, run, howl, lifesteal);

#define MUTTON_ATTRIBUTES(MACRO_NAME) \
    std::cout << "I'm Mutton\n"; \
    FE_1(MACRO_NAME, fearArmour);


#define HIDECLARE_ATTRIBUTE_CAPTUREDEF(P,T) \
	FProperty* P##T##Property; \
	FGameplayEffectAttributeCaptureDefinition P##T##Def; \

#define HIDEFINE_ATTRIBUTE_CAPTUREDEF(S, P, T, B) \
{ \
	P##T##Property = FindFieldChecked<FProperty>(S::StaticClass(), GET_MEMBER_NAME_CHECKED(S, P)); \
	P##T##Def = FGameplayEffectAttributeCaptureDefinition(P##T##Property, EGameplayEffectAttributeCaptureSource::T, B); \
}


//effect -> new UGameplayEffect
//Operation -> mode of operation if this enum EGameplayModOp
//Attribute -> Attribute to modify operation
//Value -> Value modify
#define  CREATE_GAMEPLAYEFFECT(EFFECT,OPERATION,ATTRIBUTE,VALUE_MAGNITUDE)\
  FGameplayModifierInfo modif = FGameplayModifierInfo();\
  modif.ModifierOp = OPERATION;\
  modif.Attribute = ATTRIBUTE;\
  modif.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(VALUE_MAGNITUDE));\
  EFFECT->Modifiers.Add(modif);





/*
* Inheritance macros
*/
#define MACRO_INHERITANCE(FATHER, MACRO_NAME) \
    FATHER(MACRO_NAME);

#define WEREWOLF_INHERANCE_ATTRIBUTES(MACRO_NAME) \
    MACRO_INHERITANCE(CHARACTER_ATTRIBUTES, MACRO_NAME); \
    MACRO_INHERITANCE(WEREWOLF_ATTRIBUTES, MACRO_NAME); 

#define MUTTON_INHERANCE_ATTRIBUTES(MACRO_NAME) \
    MACRO_INHERITANCE(CHARACTER_ATTRIBUTES, MACRO_NAME); \
    MACRO_INHERITANCE(MUTTON_ATTRIBUTES, MACRO_NAME); 


//Multiparameter Macros

#define EXPAND(X) X
#define  GET_MACRO(Param1, Param2, Param3, Param4, Param5, Param6, NAME, ...) NAME

#define FE_1(MACRO_NAME, X) EXPAND(MACRO_NAME(X))
#define FE_2(MACRO_NAME, X, ...) EXPAND(MACRO_NAME(X) FE_1(MACRO_NAME, __VA_ARGS__))
#define FE_3(MACRO_NAME, X, ...) EXPAND(MACRO_NAME(X) FE_2(MACRO_NAME, __VA_ARGS__))
#define FE_4(MACRO_NAME, X, ...) EXPAND(MACRO_NAME(X) FE_3(MACRO_NAME, __VA_ARGS__))
#define FE_5(MACRO_NAME, X, ...) EXPAND(MACRO_NAME(X) FE_4(MACRO_NAME, __VA_ARGS__))
#define FE_6(MACRO_NAME, X, ...) EXPAND(MACRO_NAME(X) FE_5(MACRO_NAME, __VA_ARGS__))
#define FE_7(MACRO_NAME, X, ...) EXPAND(MACRO_NAME(X) FE_6(MACRO_NAME, __VA_ARGS__))
#define FE_8(MACRO_NAME, X, ...) EXPAND(MACRO_NAME(X) FE_7(MACRO_NAME, __VA_ARGS__))
#define FE_9(MACRO_NAME, X, ...) EXPAND(MACRO_NAME(X) FE_8(MACRO_NAME, __VA_ARGS__))
#define FE_10(MACRO_NAME, X, ...) EXPAND(MACRO_NAME(X) FE_9(MACRO_NAME, __VA_ARGS__))
#define FE_11(MACRO_NAME, X, ...) EXPAND(MACRO_NAME(X) FE_10(MACRO_NAME, __VA_ARGS__))
#define FE_12(MACRO_NAME, X, ...) EXPAND(MACRO_NAME(X) FE_11(MACRO_NAME, __VA_ARGS__))
#define FE_13(MACRO_NAME, X, ...) EXPAND(MACRO_NAME(X) FE_12(MACRO_NAME, __VA_ARGS__))
