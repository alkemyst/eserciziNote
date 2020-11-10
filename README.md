# What is this
This is a script to generate notes to be written on a staff by students. Notes are generated randomly, but in a way that the same note will not be repeated within two notes of distance.

This set of scrips works under linux (I have ubuntu).

# How to install
Once you cloned this repository, you should run the following installation to make sure everyhting runs smoothly (installing lilypond and also the font I decided to use for the notes)

```
sudo apt install lilypond
mkdir -p ~/.fonts
cp fonts/SourceSerifPro-Regular.otf ~/.fonts
make
```

# How to use
Whenever you want to generate an exercise, just run
```
./generateExercise
```
Two music sheets will be generated, one with an exercise, and another one with its solution. Both will be open in ``evince``, provided that it is installed on your computer. Otherwise you will find two pdf files in the directory, named ``exercise.pdf`` and ``exercise_solution.pdf``.

If you look closely at the bottom of the exercise page, you will find a code (like ``xipi-ceru-jax``). That is generated randomy when the exercise is created and can be used to reproduce exactly the same exercise sheet, with its solutions. In order to do that, just run
```
./generateExercise xipi-ceru-jax
```
