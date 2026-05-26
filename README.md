# AI Programming Assignment

in this assignment we were tasked with making AI's with Senses that Detect you either Via Sound or Sight, which i've just named Seeker. Instead of relying on Blueprint graphs the AI logic and perception are implemented natively in C++ Sorry Fredrik (T_T) i can't do Blueprints. The Behavior Tree acts as the state machine to switch between behaviors seamlessly based on Blackboard keys set by the C++ AI Controller

## The Blackboard (The AI's Memory)
Think of the Blackboard as the Seeker's memory notebook. It uses specific keys to remember important things:
* **State (Integer):** What am I doing right now (0 = Patrolling, 1 = Investigating a noise, 2 = Chasing the player!)
* **TargetActor (Object):** Who am I chasing? When the AI sees you it writes your character in this slot
* **TargetLocation (Vector):** Where did I hear that noise? When the AI hears a sound it writes the exact X Y Z coordinates here

## AI Perception (How it finds you)
The AI uses two distinct senses built natively in C++ (UAIPerceptionComponent) to detect you
1. **Sight (Eyes):** when the SightAI range is entered it will Chase the player until the Player hides behind a Wall or the AI loses Sight. They write you down in the TargetActor key and aggressively run toward you
2. **Hearing (Ears):** Jumping is tied to noise so the HearingAI will investigate(move to that location) where the player has Jumped. If the AI hears it they write down where the noise came from in the TargetLocation key

## Behavior Tree Structure (The Flowchart)
The Behavior Tree is a flowchart that tells the Seeker what to do by reading its memory notebook. It uses a Selector node to prioritize actions from left to right:
1. **Chase (Highest Priority):** The AI asks Is TargetActor written in my notebook? If YES it drops everything and runs to you using a Move To task. It will keep running until it loses sight of you
2. **Investigate (Medium Priority):** The AI asks Is TargetLocation written in my notebook? If YES it walks to the exact location of the noise. Once it arrives it uses a custom C++ command (UBTTask_ClearTarget) to completely erase the location from its notebook
3. **Patrol (Lowest Priority):** If the notebook is totally empty the AI is bored. It uses another custom C++ command (UBTTask_FindRandomPatrol) to pick a random spot on the NavMesh floor, walks there, waits for 2 seconds and repeats

## Bonus Features (VG Requirements)
* **Team Alertness:** This feature was built-in from the start! wil the SightAI is chasing it will also Alert the HearingAI of the Players Postion
* **UI Indicators:** To make AI states incredibly clear for the demonstration C++ screen debug messages act as UI indicators. you are being Chased!!! is used by the SightAI and Noise heard is for the HearingAI

## Git LFS Tracking
Binary assets (.uasset and .umap) are strictly tracked using Git LFS keeping the repository lightweight and efficient. Build files are properly ignored using .gitignore
