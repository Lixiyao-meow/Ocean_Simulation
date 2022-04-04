# Ocean Simulation

### Overview

We present a procedural method for sea surface simulation. Our model is based on a superposition of many different waves generated according to some physical rules to reproduce natural phenomena. More precisely, we choose a wave spectrum approach to create the wave’s main structure and Perlin noise for small scale details. Then, we use a layered BRDF with a diffuse term, a specular term using a microfacet model based on the GGX distribution and a global illumination term, for the rendering procedure to get a satisfying visual result.

