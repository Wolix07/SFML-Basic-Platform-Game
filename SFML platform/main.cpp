#include<iostream>
#include <SFML/Graphics.hpp>
#include <thread>

using namespace std;

class Player
{
public:
    
    sf::RectangleShape rectangle;
    
    Player()
    {
        
        rectangle.setSize(sf::Vector2f(100, 100));
        rectangle.setFillColor(sf::Color::Red);
        rectangle.setPosition(50,400);
        cout<<"DEBUG_LOG_"<<endl;
    }
    
    void drawPlayer(sf::RenderWindow &window)
    {
        sf::CircleShape shape2(200.f);
        window.draw(rectangle);
    }
    
    void setAction(char action)
    {
        switch(action)
        {
            case 'u':
                velocity.y = -speed*3;
                acc = 100;
                break;
            case 'g':
                
                break;
            case 'l':
                velocity.x = -speed;
                break;
            case 'r':
                velocity.x = speed;
                break;
        }
        
    }
    
    void updateVelocity()
    {
        
        
        if (velocity.x > 0)
        {
            velocity.x -= 2;
        }
        else if (velocity.x < 0)
        {
            velocity.x += 2;
        }
    }
    
    void updateJump()
    {
        if(acc > 0)
        {
            velocity.y = -speed*2;
            acc--;
        }
        if (velocity.y < 10)
        {
            velocity.y += 2;
        }
        if(rectangle.getPosition().y == 400)
        {
            cout<<"XD";
        }
    }
    
    void movePlayer(float tickTime)
    {
        //cout<<"ruch"<<endl<<rectangle.getPosition().x<<" "<<velocity.x<<endl<<rectangle.getPosition().y<<" "<<velocity.y<<endl;
        
        if(rectangle.getPosition().y > 400)
        {
            velocity.y = 0;
            rectangle.setPosition(rectangle.getPosition().x, 400);
        }
        
        rectangle.setPosition(sf::Vector2f(rectangle.getPosition().x + velocity.x * tickTime * 50,rectangle.getPosition().y + velocity.y * tickTime * 55));
    }
    
    
private:
    int speed = 10;
    int acc = 0;
    sf::Sprite pSprite;
    sf::Vector2f velocity;

};

class Grenade : Player
{
public:
    sf::CircleShape sGrenade;
    
    Grenade()
    {
        
        sGrenade.setRadius((50.f));
        sGrenade.setFillColor(sf::Color::Blue);
        sGrenade.setPosition(rectangle.getPosition().x, rectangle.getPosition().y);
        
    }
    
    void drawGrenade()//sf::RenderWindow &window)
    {
        cout<<"drawing"<<endl;
        return;
    }
     /*
    void draw( sf::RenderTarget& tgt, sf::RenderStates states) const
    {
        tgt.draw(sGrenade, states) ;
        return;
    }*/
    
};

class Grenade_spell : Grenade
{
public:
    
    Grenade_spell(){}
    
    void grenade_live()//sf::RenderWindow &window)
    {

        unique_ptr<Grenade> pGrenade(new Grenade);
        while(1)
        {
            pGrenade->drawGrenade();
            cout<<"KAPPA_GRANAT"<<endl;
            return;
        }
        return;
    }
    
    
};


int main()
{
    bool move_left, move_right, move_up, move_down, isFinished,grenade;
    move_left = move_right = move_up = move_down = isFinished = grenade = false;
    
    sf::RenderWindow window(sf::VideoMode(1200, 600), "SFML works!");
    
    //window.setFramerateLimit(60);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    
    unique_ptr<Player> myPlayer(new Player);
    
    //unique_ptr<Grenade_spell> grenade_spell(new Grenade_spell);
    
    
    
    //Grenade_spell * taskPtr = new Grenade_spell();
    
    std::thread t2(&Grenade_spell::grenade_live,Grenade_spell());
    
    //Grenade_spell grenade_spell;

    sf::Clock clock;
    
    //test<<<<<<<<<<<
    sf::Vector2f movement(25.0,15.0);
    sf::Clock timer;
    sf::Time tickRate;
    
    
    // Start main loop
    
    //Somewhere in the main loop
    
    
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                    // window closed
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                    // key pressed
                case sf::Event::KeyPressed:
                    
                    break;
                    
                    // we don't process other types of events
                default:
                    break;
            }
            
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && myPlayer->rectangle.getPosition().y == 400)
        {
            move_up = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            move_down = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            move_left = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            move_right = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            grenade = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            isFinished = true;
        }
        
        if(!move_left && !move_right)
        {
            myPlayer->updateVelocity();
        }
        
        if(myPlayer->rectangle.getPosition().y != 400)
        {
            myPlayer->updateJump();
        }
        
        if(grenade)
        {
            //odpalanie
            //grenade_pref->drawGrenade(window);
            grenade = false;
        }
        
        if(move_left)
        {
            myPlayer->setAction('l');
            move_left = false;
        }
        if(move_right)
        {
            myPlayer->setAction('r');
            move_right = false;
        }
        if(move_up)
        {
            myPlayer->setAction('u');
            move_up = false;
        }
        if(move_down)
        {
            myPlayer->setAction('d');
            move_down = false;
        }
        
        
        tickRate = timer.restart();
        myPlayer->movePlayer((float)tickRate.asMilliseconds() / 1000);
        
        
        window.clear();
        window.draw(shape);
        myPlayer->drawPlayer(window);
        window.display();
        
        if(isFinished)
        {
            break;
        }
    }
    
    t2.join();
    return 0;
}
