# steel

Hopefully this will become a 2D game framework, but for now it's just a hobby project I'm using to explore CMake, SDL2 and Catch2.


# Inspiration

Similarities are not coincidences, I've been taking a lot of inspiration from:
* [Hazel](https://github.com/TheCherno/Hazel)
* [Halley](https://github.com/amzeratul/halley)
* [Heaps](https://github.com/HeapsIO/heaps)
* [Game Coding Complete 4th edition](https://github.com/kveratis/GameCode4)
* Deepnight [gameBase](https://github.com/deepnight/gameBase) and [deepnightlibs](https://github.com/deepnight/deepnightLibs)
* Tyler Glaiel's [How to make your game run at 60fps](https://medium.com/@tglaiel/how-to-make-your-game-run-at-60fps-24c61210fe75) article

## Building the environment

This project contains submodules, after cloning it, run:
```bash
git submodule update --init --recursive
```

This project uses [Miniconda](https://docs.conda.io/en/latest/miniconda.html) as a package manager
and [conda devenv](https://github.com/ESSS/conda-devenv). After installing `Miniconda` you need
to install `conda-devenv` on your `base` (root environment) with:

```bash
conda activate base 
conda install conda-devenv
conda deactivate
```

Then in order to create the environment run on the root of this project:
```bash
conda devenv
```

And to activate it, just call:
```bash
conda activate steel
```


## Building the project

On the root of this repository, execute:

```bash
build_steel.bat
```

Notes: 

1. Inside `build/` there will be a Visual Studio Solution (`steel.sln`) and in order to make sure Visual Studio
is initialized with all the correct environment variables, it's a good idea to open it from the command line with 
`steel` environment active. I use an alias to make that easier: 

```bash
alias vs="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.exe"
```