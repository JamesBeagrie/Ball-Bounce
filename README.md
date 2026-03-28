Hi! Who ever sees this...

This is my attempt at making the ball bouncing in circle that is seen in a lot of instagram videos. And more! If I'm feeling really motivated.

Uses swept collision edge-sphere logic.

I decided to do it a bit differently where it uses swept collision detection based on the algorithm found here: https://www.peroxide.dk/papers/collision/collision.pdf

I'm sorry if the code is a bit janky!

Feel free to use as you would like!

---

Project structure:

Starts in main.cpp, where raylib is set up and the window loop begins.

mathlib.cpp and mathlib.h contain maths stuff like edges and vectors and functions that come with them

ball has the ball that bounces along with calculating collisions between objects etc

---

Compiling guide:

g++ main.cpp mathlib.cpp objectlib.cpp windowlib.cpp ball.cpp object.cpp -o app -lraylib -lopengl32 -lgdi32 -lwinmm

aka, all the .cpp files after g++, in the raylib w64devkit

---

Formatting:

I will try to use this throughout but I won't promise anything!

Apart from variables which I will use CamelCase.

https://lefticus.gitbooks.io/cpp-best-practices/content/03-Style.html

---

Credit:

- Raylib used for basic stuff. (Window, sound, etc.)
