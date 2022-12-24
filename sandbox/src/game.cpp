#include <RVL.hpp>

class Game : public rvl::RvlApp
{
public:
    Game(/* args */) : RvlApp(800, 600, "rvl game")
    {

    }
    ~Game()
    {

    }

private:
    void Start() override
    {
        std::cout << "start" << std::endl;
    }
    
    void Update() override
    {
        std::cout << "update" << std::endl;        
    }

};

rvl::RvlApp* rvl::CreateApp()
{
    return new Game();
}
