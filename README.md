# SimplePhysicsEngine
This physics engine developed by VS2017 was simply implemented based on linear elasticity.
Rect collider and circular collider have beeen implemented so far.

## There some problems:
  1. The speed of convergence is slow (long time jitter)
  2. The speed of performence differs on different devices (has been solved, I'll push up soon)
  3. Sometimes colliders cross and can not separate
  4. No friction
  
## Improvement direction:
  1. better collision detection method
  2. directly adopt impulse theorem to avoid the cross of colliders
  3. joint and other physics properties
  
 I don't have enough time to complete tasks above. Maybe this project will be put it on ice for a while.
 Currently I focus on creating my tiny compiler which will be a huge projects.
