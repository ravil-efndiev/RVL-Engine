# RVL Engine
![](https://github.com/ravil-efndiev/RVL-Engine/blob/main/img/icon.png)
### version alpha 1.4 

RVL Engine is a C++ low-middle level game engine for 2D games (has 3D features that are currently being activelly worked on)

It has a lot of modules such as 2D batch rendering, Graphical 2D tilemap editor, 3D forward rendering, 3D model loading, simple post-processing and indev lighting system
Main game developement pattern used to create games is ECS (Entity-Component-System) and it currently has almost all functionality needed
to make real projects, you can read detailed information on ECS and other parts of an engine in [documentation](https://rvl-engine-docs.web.app/)

## Getting Started

Engine uses CMake build system and almost all needed dependencies are included as submodules, all you need to do to install and run engine
is to clone this repository with ```--recursive``` flag. On Windows you'll probabbly need to recompile engine itself so it compiles as 'lib' static library, but all windows-related information will be evantually written in documentation when I'll port engine to Windows
All game code is written in "sandbox" project, or any other project that has same structure as sandbox, details can be seen in [documentation](https://rvl-engine-docs.web.app/)

## 'Hello, World' program

All you need to do hwen your project is set-up and successfully links to libRVL library is to create so-called 'Game' class taht inherits from 'App' class
This is main class for any RVL application, it will look something like this:

```cpp
class Game : public Rvl::App
{
public:
    Game() : Rvl::App(windowWidth, windowHeight, windowTitle) {}

private:
    void Start() override; 
    void Update() override;
};
```

Here we call App constructor where we pass all our window data (width, height, title)
And decalre two overridden methods: Start, which is called once at the begginning of the program and Update, which is called every frame.

Also to specify that our class is the one which is going to be used we need to implement global 'OnInit' function like this:
```cpp
Rvl::Ref<Rvl::App> Rvl::OnInit() 
{
    return Rvl::App::New<Game>(); 
}
```

don't be confused by all this code, it will become clear later, also there is no actual need to write this function by ourselves, we can just call 
```cpp
RVL_IMPL_INIT(Game)
```
macro that will do it for use automatically

The result of this program will be empty window and text we've written in methods logging into standart output

IMPORTANT NOTE:
RVL_IMPL_INIT macro must be called only once in cpp file where you must include <EntryPoint.hpp> header file,
the look of your program will be something like this:

```cpp
#include <RVL.hpp>
#include <EntryPoint.hpp>

class Game : public Rvl::App
{
public:
    Game() : Rvl::App(windowWidth, windowHeight, windowTitle) {}

private:
    void Start() override 
    {
        RVL_LOG("App has started");
    }
    
    void Update() override
    {
        RVL_LOG("App is in main loop");
    }

};

RVL_IMPL_INIT(Game)
```

assuming that you are doing it in cpp file, if you want to split your game class into header and source files, you must include EntryPoint and RVL_IMPL_INIT only in cpp file.

So now as you've created your very first 'Hello, World' program you should now check documentation in order to understand how to actually make a game with RVL Engine, good luck!

Here you can see some screenshots that can probabbly make you more interested
![](https://github.com/ravil-efndiev/RVL-Engine/blob/main/img/editor.png)
Scene editor
![](https://github.com/ravil-efndiev/RVL-Engine/blob/main/img/2D.png)
2D character prototype with animations and movement
![](https://github.com/ravil-efndiev/RVL-Engine/blob/main/img/tmeditor.png)
2D Tile map editor
