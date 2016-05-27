# Monopoli: il gioco del piccolo capitalista e della banca moralista
A simple and fun Monopoly game (up to 4 players) created as a university project (in collaboration with @mziccard).
The game offers 4 options to customize gameplay:
- `modalita ipoteca`: it is possible to mortgage the land and hotels owned.
- `modalita privatizzata`: it is possible to become a stakeholder for public companies and earn a percentage of their income.
- `modalita legale`: it is possible to skip turns when landing on the court or police stataion square.
- `modalita dado truccato`: the outcome of the dice is always 1. Can be used to debug or try every feature of the game.


## Building
It is suggested to use QtCreator and import the project file `monopoli.pro`.

Otherwise, the project can be compiled with
```
qmake-qt4 monopoli.pro
make
```
