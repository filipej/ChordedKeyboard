# Chorded Keyboard
A Windows program that simulates a chorded keyboard using a conventional keyboard

## Input
The program uses the F, G, H, J and the space key as inputs and outputs according to the table below.
The "." represents a non-pressed key and the "-" a pressed key.

The keyboard "types" when any key is released, but if the letter takes several keys as inputs, it only requires one to be released. Any released keys after that does nothing until a new key is pressed down. This "should" allow faster typing :)

```
   .....      P  -....
A  ....-      Q  -...-
B  ...-.      R  -..-.
C  ...--      S  -..--
D  ..-..      T  -.-..
E  ..-.-      U  -.-.-
F  ..--.      V  -.--.
G  ..---      W  -.---
H  .-...      X  --...
I  .-..-      Y  --..-
J  .-.-.      Z  --.-.
K  .-.--      Å  --.--
L  .--..      Ä  ---..
M  .--.-      Ö  ---.-
N  .---.      _  ----. (space)
O  .----      .  -----
```
