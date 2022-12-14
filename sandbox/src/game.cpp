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
        if (rvl::Input::IsKeyPressedOnce(rvl::Keys::RVL_KEY_A))
            std::cout << "pressed once" << std::endl;        

        if (rvl::Input::IsKeyPressed(rvl::Keys::RVL_KEY_D))
            std::cout << "pressed continiously" << std::endl;        
    }

};

void rvl::OnInit()
{
    rvl::CurrentApp = new Game();
}
