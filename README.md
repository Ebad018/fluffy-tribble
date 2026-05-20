# AI Programming Assignment

This repository contains an Unreal Engine 5 project demonstrating AI behaviors implemented entirely in C++ and driven by a Behavior Tree, fulfilling all G and VG requirements.

## AI Implementation Overview
Instead of relying on Blueprint graphs, the AI logic and perception are implemented natively in C++ (sorry Fredrick T_T i can't do BP). The Behavior Tree acts as the state machine to switch between behaviors seamlessly based on Blackboard keys set by the C++ AI Controller.

### Perception (Sight & Hearing)
The AI uses `UAIPerceptionComponent` configured with two distinct senses:
1. **Sight:** When the player enters the AI's cone of vision, the AI Controller updates the `TargetActor` blackboard key. This triggers the **Chase** behavior.
2. **Hearing:** When the player jumps, a noise event is dispatched using `UAISense_Hearing`. If the AI hears this, it updates the `TargetLocation` blackboard key with the origin of the sound, triggering the **Investigate** behavior.

### Behavior Tree States
The `BT_EnemyAI` uses a Selector node to prioritize behaviors from left to right:
- **Chase (Highest Priority):** Triggered when `TargetActor` is set (Sight). The AI aggressively moves towards the player until sight is lost.
- **Investigate (Medium Priority):** Triggered when `TargetLocation` is set (Hearing/Lost Sight). The AI moves to the location of the disturbance and then uses a custom C++ task (`UBTTask_ClearTarget`) to clear the location and resume patrolling.
- **Patrol (Lowest Priority):** The default state. The AI uses a custom C++ task (`UBTTask_FindRandomPatrol`) to pick a random reachable point on the NavMesh, walks to it, and waits before picking a new point.

### Bonus Features (VG Requirements)
- **Team Alertness:** This feature was built-in from the start! When the Sight AI spots the player, it automatically broadcasts the player's location to all other AI agents in the level (like the Hearing AI), prompting them to immediately switch into the Investigate state and move to the target location.
- **UI Indicators:** To make AI states incredibly clear for the demonstration, C++ screen debug messages act as UI indicators. A giant red `!!! YOU ARE BEING CHASED !!!` appears when actively detected by sight, and a yellow `? NOISE HEARD - INVESTIGATING ?` appears when the AI detects a sound.

### Custom C++ Classes
- `AAssignAIController`: Manages the AI Perception Component, configures sight and hearing radius, and binds the perception update event to dynamically update the Blackboard.
- `AAssignAICharacter`: The custom pawn class that possesses the AI, configured with specific movement speeds and rotation constraints (`bOrientRotationToMovement = true`, `bUseAccelerationForPaths = true`).
- `UBTTask_FindRandomPatrol`: A Behavior Tree Task node written in C++ that queries the `UNavigationSystemV1` to find a random navigable point within a radius and assigns it to a Blackboard Vector key.
- `UBTTask_ClearTarget`: A utility task to clear a specific Blackboard key, used after the AI finishes investigating a sound or lost sight location to seamlessly drop back into the Patrol state.

## Git LFS Tracking
Binary assets (`.uasset` and `.umap`) are strictly tracked using Git LFS, keeping the repository lightweight and efficient. Build files (`Binaries/`, `Intermediate/`, `Saved/`) are properly ignored using `.gitignore`.
