# Creating a New Character
Follow these steps to set up a new character based on the existing enemy framework.

## 1. Blueprint Setup

   1. Create Enemy Blueprint: Right-click on BP_Enemy_Base and select Create Child Blueprint Class. Name this new blueprint after your character.
   2. Create Animation Blueprint: Open the Animation Blueprint folder, right-click on ABP_Enemy, and select Create Child Blueprint Class. Choose your character's skeleton and save it as ABP_[YourEnemyName].

## 2. Configure Mesh and Animation
   1. Assign Skeletal Mesh: Open your new enemy blueprint from BP_Enemy_Base. Navigate to Mesh > Skeletal Mesh Asset and assign the skeletal mesh for your character.
   2. Adjust Mesh: Modify the mesh properties, scale, or orientation as needed to fit your design.
   3. Add Weapon (Optional): Attach a weapon if required by your character. Use existing enemy blueprints with weapons as references.

## 3. Set Up Sockets
   1. Add Weapon Tip Socket Name: Ensure the skeletal mesh has the required sockets for weapon interaction. If adding a weapon tip socket, name it appropriately.
   2. Configure Hand Sockets: For characters needing left and/or right-hand socket positions, add socket names to the mesh and confirm their alignment.

## 4. Set Up Animation Montages and Blendspace
   1. Add Hit React Montage: For a custom hit reaction animation:
      * Locate the desired hit react animation.
      * Right-click, select Create > Create Anim Montage.
      * Follow the naming convention: AM_HitReact_[EnemyName].
   2. Set Character Properties: Define the character’s class, level, and lifespan (duration until the character de-spawns after death).

## 5. Configure Animation Blueprint
   1. Open your animation blueprint from APB_Enemy, and set up the Blend Space:
      * In the Animation folder, right-click and select Animation > Blend Space.
      * Choose the character's skeleton and name it as BS_[AnimationName] (e.g., BS_IdleWalk).
      * Open the blendspace and configure the Horizontal Axis to “Speed”.
      * Add animations to the timeline.
      * Note: If the enemy turns clunkily, increase the Weight Speed to improve responsiveness.
   2. Link Animation to Mesh: Return to the enemy blueprint, select the Mesh component, and set the Anim Class to your ABP_[YourEnemyName] blueprint.