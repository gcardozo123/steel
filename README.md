# steel

Just a hobby project I'm using to explore CMake and SDL2.

## Building the environment
This project uses [Miniconda](https://docs.conda.io/en/latest/miniconda.html) as a package manager
and [conda devenv](https://github.com/ESSS/conda-devenv). After installing `Miniconda` you need
to install `conda-devenv` on your `base` (root environment) with:

```bash
conda activate base 
conda install conda-devenv
conda deactivate
```

Then in order to create the environment run
```bash
conda devenv
```

on the root of this project. And to activate it, just call:
```bash
conda activate steel
```

## Building the project

On the root of this repository, execute:

```bash
mkdir build
cd build
cmake -G "Visual Studio 15 2017 Win64" ..
cmake --build .
```

Notes: 

1. `"Visual Studio 15 2017 Win64"` just indicates the compiler I'm currently using, feel free to change it,
but it's important to keep the x64 generator platform - in my case `Win64` - there, otherwise you'll run into:

```
fatal error LNK1112: module machine type 'x64' conflicts with target machine type 'X86'
```

2. Inside `build/` there will be a Visual Studio Solution (`steel.sln`) and in order to make sure Visual Studio
is initialized with all the correct environment variables, it's a good idea to open it from the command line with `steel` environment active. I use an alias to make that easier: 

```bash
alias vs="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.exe"
```