#include<iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

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
        shape2.setPosition(0,0);
        window.draw(shape2);
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
        
    }
    void setPos(float x, float y)
    {
        sGrenade.setPosition(x,y);
    }
    void drawGrenade(sf::RenderWindow &window)
    {
        window.draw(sGrenade);
        return;
    }
    void moveGrenade(float tickTime)
    {
        sGrenade.setPosition(sf::Vector2f(sGrenade.getPosition().x + 20  * tickTime *50 ,sGrenade.getPosition().y));
    }
private:

};

class Enemy : Player
{
public:
    sf::RectangleShape sEnemy;
    Enemy()
    {
        sEnemy.setSize(sf::Vector2f(30, 30));
        sEnemy.setFillColor(sf::Color::Yellow);
    }
    void setPos(float x, float y)
    {
        sEnemy.setPosition(x,y);
    }
    void drawEnemy(sf::RenderWindow &window)
    {
        window.draw(sEnemy);
        return;
    }
private:
    
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
    unique_ptr<Enemy> enemy_pref(new Enemy);
    unique_ptr<Grenade> grenade_spell(new Grenade);
    int num_of_grenades = 10;
    int num_of_enemy = 20;
    float grenades[num_of_grenades][2];
    float enemys[num_of_enemy][2];

    for (int i = 0; i < num_of_grenades; i++)
    {
        grenades[i][1] = 0;
        grenades[i][0] = 0;
    }
    float grenadeCooldown = 0;
    for (int i = 0; i < num_of_enemy; i++)
    {
        enemys[i][1] = 0;
        enemys[i][0] = 0;
    }
    float enemyCooldown = 0;
    //Grenade_spell * taskPtr = new Grenade_spell();
    
    
    
    //Grenade_spell grenade_spell;
    //std::thread t2(&Grenade_spell::grenade_live,Grenade_spell());
    sf::Clock clock;
    
    //test<<<<<<<<<<<
    sf::Vector2f movement(25.0,15.0);
    sf::Clock timer;
    sf::Time tickRate;
    sf::Time grenadecd;
    
    // Start main loop
    
    //Somewhere in the main loop
    
    float xv, yv;
    
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
        enemyCooldown -= (float)grenadecd.asMilliseconds() / 1000;
        if(enemyCooldown <= 0)
        {
            enemyCooldown = 0.5;
            for (int i = 0; i < num_of_enemy; i++)
            {
                if (enemys[i][0] == 0 && enemys[i][1] == 0)
                {
                    //grenade_spell->setPos(grenades[i][0],grenades[i][1]);
                    enemys[i][0] = (rand() % 100) * 4 + 800;
                    enemys[i][1] = (rand() % 100) * 3 + 150;
                    break;
                }
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
        //cout<<<<endl;
        grenadeCooldown -= (float)grenadecd.asMilliseconds() / 1000;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && grenadeCooldown <= 0)
        {
            grenadeCooldown = 1;
            grenadecd = timer.restart();
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
            for (int i = 0; i < num_of_grenades; i++)
            {
                if (grenades[i][0] == 0 && grenades[i][1] == 0)
                {
                    //grenade_spell->setPos(grenades[i][0],grenades[i][1]);
                    grenades[i][0] = myPlayer->rectangle.getPosition().x;
                    grenades[i][1] = myPlayer->rectangle.getPosition().y;
                    break;
                }
            }
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
        for (int i = 0; i < num_of_grenades; i++)
        {
            if (grenades[i][0] != 0 || grenades[i][1] != 0)
            {
                grenade_spell->setPos(grenades[i][0], grenades[i][1]);
                grenade_spell->moveGrenade((float)tickRate.asMilliseconds() / 1000);
                grenades[i][0] = grenade_spell->sGrenade.getPosition().x;
                grenades[i][1] = grenade_spell->sGrenade.getPosition().y;
                if(grenades[i][0] > 1200)
                {
                    grenades[i][0] = 0;
                    grenades[i][1] = 0;
                }
            
                for (int j = 0; j < num_of_enemy; j++)
                {
                    if (enemys[j][0] != 0 || enemys[j][1] != 0)
                    {
                        xv = (enemys[j][0] + 15 - grenades[i][0]+50);
                        yv = (enemys[j][1] + 15 - grenades[i][1]+50);
                        if(sqrt(xv*xv + yv*yv) < 50)
                        {
                            enemys[j][0] = 0;
                            enemys[j][1] = 0;
                        }
                    }
                }
                
                grenade_spell->drawGrenade(window);
            }
            
        }
        for (int i = 0; i < num_of_enemy; i++)
        {
            if (enemys[i][0] != 0 || enemys[i][1] != 0)
            {
                enemy_pref->setPos(enemys[i][0], enemys[i][1]);
                enemy_pref->drawEnemy(window);
            }
            
        }
        myPlayer->drawPlayer(window);
        window.display();
        
        if(isFinished)
        {
            break;
        }
    }
    

    //t2.join();
    
    return 0;
}
