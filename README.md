# Howl of Iron


***Howl of Iron*** is a 3rd Person Action Adventure game blending ***HUNT*** & ***COMBAT***. 

The player take control of **Vincent Volk**, a renowned engineer and former Red Gear worker who lived a **hard childhood** and after suffering the **loss** of his loved ones, his **wife** and **daughter** because of carbogenosis, decides to completely dehumanize and **transfer his consciousness** to a ***mechanical werewolf*** with which to **destroy** everything that once harmed him, thus consummating his ***revenge***.

- **Stalk** on your unaware enemies

<img src = "https://user-images.githubusercontent.com/13780925/199088126-d82062e2-f3a0-420a-8826-d96e44cf60b7.png" style="float:left">

- **Fight** in open combat 

<img src = "https://user-images.githubusercontent.com/13780925/199086063-04bbdf0b-829f-4577-a918-ef4133f96586.png" style="float:left">

- **Explore** the steampunk city of Steamfall.

<img src = "https://user-images.githubusercontent.com/13780925/199087715-ce43d640-6369-49f6-8a14-4b53f52f3c31.png" style="float:left">

# About the project
Howl of Iron was developed as master tesis of my games programing master degree. It was developed by 17 students of 4 different master degrees: game programing, game art, game design and production. We developed the game in 9 months using Unreal Engine.

<a href="https://16-gears.itch.io/howl-of-iron">More information about the project</a>

# My contribution to the project

## Combo system
I made the systems that makes posible for any character of unreal to use a combo system just by adding a component. In adition to the internal logic I also developed all the tools that designers will need to customize the combo system as they want.

![CC](https://img.shields.io/badge/Clean_Code-57FF70?style=for-the-badge&logo=c&logoColor=black&labelColor=D8D8D8)
![CH](https://img.shields.io/badge/Queue-57FF70?style=for-the-badge&logo=c&logoColor=black&labelColor=D8D8D8)

![AC](https://img.shields.io/badge/Actor_Component-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![DA](https://img.shields.io/badge/DataAsset-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![DL](https://img.shields.io/badge/Delegates-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![NO](https://img.shields.io/badge/Anim_Notify-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![NS](https://img.shields.io/badge/Notify_State-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)

## Fear/Rage System
In Howl of Iron enemies and player cant get buffs and debuffs based on how enemies get scared as the fight progresses or how violent becomes the character that the player embodies. I made that system and linked it with GAS, the plugin that was used to develop the gameplay abilities used to perform the combat of the video game.

![CC](https://img.shields.io/badge/Clean_Code-57FF70?style=for-the-badge&logo=c&logoColor=black&labelColor=D8D8D8)
![CH](https://img.shields.io/badge/Charged_Heap-57FF70?style=for-the-badge&logo=c&logoColor=black&labelColor=D8D8D8)

![AC](https://img.shields.io/badge/Actor_Component-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![DL](https://img.shields.io/badge/Delegates-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![DA](https://img.shields.io/badge/DataAsset-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)

![GAS](https://img.shields.io/badge/GAS-FFB1A9?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![AS](https://img.shields.io/badge/Ability_System_Component-FFB1A9?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![GE](https://img.shields.io/badge/Gameplay_Effect-FFB1A9?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)


## Gameplay abilities
For the combat and navigation throught the map we used the plagin GAS (Gameplay Ability System). This plugin was used in games like Fortnite and offers a lot of freedom to implement the abilities as you wont. With my team we made the combat abilities, the effects that are applied by the enemies and player in the game and developed our own Gameplay Tasks to give even more freedom to our designers.

![DT](https://img.shields.io/badge/DataTable-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![BP](https://img.shields.io/badge/Blueprints-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)

![GAS](https://img.shields.io/badge/GAS-FFB1A9?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![AS](https://img.shields.io/badge/Ability_System_Component-FFB1A9?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![GA](https://img.shields.io/badge/Gameplay_Ability-FFB1A9?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![GE](https://img.shields.io/badge/Gameplay_Effect-FFB1A9?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![GC](https://img.shields.io/badge/Gameplay_Cue-FFB1A9?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![SET](https://img.shields.io/badge/Attribute_Set-FFB1A9?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![EM](https://img.shields.io/badge/Execution_Calculation-FFB1A9?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)

## Perception system

We create a perception system by our selves. We made it modluar and scalable. The system was based in three elements: 
- A detectable component that made actors in the level to identify them as actors that can be detected to by the perception system.
- A detector component that made an actor detect the actors with a detectable component on them.
- Detections that can be combined to define how the detector actor is going to detect de detectable actors.

We made basic detection such us a detection based on the distance to the detector or a detection that "sees" in cone. By mixing al the simple detections we could create complex detections that made enemies look clever and give the impression of being attentive to their surroundings.

Create new simple detections is easy and doesn't affect the rest of the architecture, making this perception system an scalable and portable.
Also we offered dataassets to make designers easy to create detection packs and assign them to the actors they want.

As we were using GAS we also made the perception system compatible with it. This was very useful when we need to give the enemies a more "scripted" behaviour, like make anamies know where is the player after a cutscene.

![CC](https://img.shields.io/badge/Clean_Code-57FF70?style=for-the-badge&logo=c&logoColor=black&labelColor=D8D8D8)
![SC](https://img.shields.io/badge/Scalable_Code-57FF70?style=for-the-badge&logo=c&logoColor=black&labelColor=D8D8D8)

![AC](https://img.shields.io/badge/Actor_Component-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![DA](https://img.shields.io/badge/DataAsset-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)

![GAS](https://img.shields.io/badge/GAS-FFB1A9?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![GE](https://img.shields.io/badge/Gameplay_Effect-FFB1A9?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![SET](https://img.shields.io/badge/Attribute_Set-FFB1A9?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)

## Enemies AI

Howl of Iron has enemies with complex behaviors that required the use of behavior trees. We made our own tasks decorators and services to give them the behaviour we wanted. We also made tasks to make baheviour trees of unreal compatibles with GAS, we even reworked a decorator provided by GAS plugin to make it work as we wanted. We also had to make nodes to make behavior trees compatible with our systems. For example, we made a service that saves the perception level of the perception system in blackboard variables.

![BT](https://img.shields.io/badge/Behaviour_Tree-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![TSK](https://img.shields.io/badge/Task_Node-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![DCT](https://img.shields.io/badge/Decorator_Node-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![SVC](https://img.shields.io/badge/Service_Node-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)

## Waypoints system

In Howl of iron, when enemies are out of combat, they patrol the level. We made a waypoint system that allowed designers to decide the path that enemies will take. We also add some complex logic to waypoints to make them more versatile and allow enemies to for example, reproduce an animation when reach a waypoint or make enemy wait for the player to go through a trigger to start patrolling. This waypoint system gave rise to a small and scalable condition system that we use throughout the project to check conditions like enemies life or when a cinematic ends.

We used unreal metadata and some editor features to make the system friendly with designers.


![CC](https://img.shields.io/badge/Clean_Code-57FF70?style=for-the-badge&logo=c&logoColor=black&labelColor=D8D8D8)
![SC](https://img.shields.io/badge/Scalable_Code-57FF70?style=for-the-badge&logo=c&logoColor=black&labelColor=D8D8D8)
![OP](https://img.shields.io/badge/Optimal_Algorithms-57FF70?style=for-the-badge&logo=c&logoColor=black&labelColor=D8D8D8)

![BT](https://img.shields.io/badge/Behaviour_Tree-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![MTDT](https://img.shields.io/badge/Metadata-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
![INST](https://img.shields.io/badge/Instanced_Objects-62B5FF?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=D8D8D8)
