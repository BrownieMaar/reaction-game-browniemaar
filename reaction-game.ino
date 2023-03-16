#include "component-utils.h"

class LightScoreBoard
{
public:
    LightScoreBoard(int pin0, int pin1, int pin2, int pin3)
    {
        _light0 = new Light(pin0);
        _light1 = new Light(pin1);
        _light2 = new Light(pin2);
        _light3 = new Light(pin3);
        _score = 0;
    }

    ~LightScoreBoard()
    {
        delete _light0;
        delete _light1;
        delete _light2;
        delete _light3;
    }

    bool addPointAndCheckIfWon()
    {
        switch (_score)
        {
        case 0:
            _light0->on();
            _score++;
            break;

        case 1:
            _light1->on();
            _score++;
            break;

        case 2:
            _light2->on();
            _score++;
            break;

        case 3:
            _light3->on();
            _score++;
            return true;
            break;

        default:
            break;
        }
        return false;
    }

    void setReadyOnOrOff(bool setToOn)
    {
        if (setToOn)
        {
            _light1->on();
            _light2->on();
        }
        else
        {
            _light1->off();
            _light2->off();
        }
    }

    void removePoint()
    {
        switch (_score)
        {
        case 1:
            _light0->off();
            _score--;
            break;

        case 2:
            _light1->off();
            _score--;
            break;

        case 3:
            _light2->off();
            _score--;
            break;

        default:
            break;
        }
    }

    bool checkIfWon()
    {
        if (_score == 4)
        {
            return true;
        }
        return false;
    }
    
    void blink()
    {
        for (int i = 0; i < 6; i++)
        {
            delay(500);
            _light0->off();
            _light1->off();
            _light2->off();
            _light3->off();
            delay(500);
            _light0->on();
            _light1->on();
            _light2->on();
            _light3->on();
        }
        delay(500);
    }

    void reset()
    {
        _light0->off();
        _light1->off();
        _light2->off();
        _light3->off();
        _score = 0;
    }

private:
    Light *_light0;
    Light *_light1;
    Light *_light2;
    Light *_light3;
    int _score;
};

Light mainLight(7);

Button playerA(2);
LightScoreBoard scoreA(3, 4, 5, 6);

Button playerB(12);
LightScoreBoard scoreB(8, 9, 10, 11);

void game()
{
    while (true)
    {
        unsigned long startTime = millis();
        srand(millis());
        int randomTimeToPass = rand() % 10000;
        while (true)
        {
            if (millis() - startTime > randomTimeToPass)
            {
                mainLight.on();
                while (true)
                {
                    if (playerA.onButtonDown([]()
                                             {
                            mainLight.off();
                            if (scoreA.addPointAndCheckIfWon()) {
                                scoreA.blink();
                            }
                            mainLight.blinkFastForMillis(500, 100); }))
                    {
                        break;
                    }
                    if (playerB.onButtonDown([]()
                                             {
                            mainLight.off();
                            if (scoreB.addPointAndCheckIfWon()) {
                                scoreB.blink();
                            }
                            mainLight.blinkFastForMillis(500, 100); }))
                    {
                        break;
                    }
                }
                break;
            }
            if (playerA.onButtonDown([]()
                                     {
                            scoreA.removePoint();
                            delay(500); }))
            {
                break;
            }
            if (playerB.onButtonDown([]()
                                     {
                            scoreB.removePoint();
                            delay(500); }))
            {
                break;
            }
        }
        if (scoreA.checkIfWon() || scoreB.checkIfWon()) {
            scoreA.reset();
            scoreB.reset();
            return;
        }
    }
}

void startAnimation()
{
    mainLight.on();
    delay(50);
    digitalWrite(6, HIGH);
    digitalWrite(8, HIGH);
    delay(50);
    digitalWrite(5, HIGH);
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(4, HIGH);
    digitalWrite(10, HIGH);
    mainLight.off();
    delay(50);
    digitalWrite(3, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(8, LOW);
    delay(50);
    digitalWrite(5, LOW);
    digitalWrite(9, LOW);
    delay(50);
    digitalWrite(4, LOW);
    digitalWrite(10, LOW);
    delay(50);
    digitalWrite(3, LOW);
    digitalWrite(11, LOW);
}

void setup()
{

}

void loop()
{
    startAnimation();
    bool playerAReady = false;
    bool playerBReady = false;
    while (true)
    {
        if (playerA.onButtonDown([]() {}))
        {
            playerAReady = !playerAReady;
            scoreA.setReadyOnOrOff(playerAReady);
        }
        if (playerB.onButtonDown([]() {}))
        {
            playerBReady = !playerBReady;
            scoreB.setReadyOnOrOff(playerBReady);
        }
        if (playerAReady && playerBReady)
        {
            mainLight.blinkFastForMillis(1500, 300);
            scoreA.setReadyOnOrOff(false);
            scoreB.setReadyOnOrOff(false);
            mainLight.blinkFastForMillis(500, 100);
            game();
            break;
        }
    }
}