class Button
{
public:
  Button(int pin)
  {
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);
  }

  typedef void (*Callback)(void);

  bool onButtonDown(Callback callback)
  {
    return _onButton(callback, true);
  }

  bool onButtonUp(Callback callback)
  {
    return _onButton(callback, false);
  }

  void whileButtonDown(Callback callback)
  {
    if (digitalRead(_pin) == HIGH)
    {
      callback();
    }
  }

private:
  int _pin;
  int _lastState;

  bool _onButton(Callback callback, bool onDown)
  {
    int value = digitalRead(_pin);
    int valueToCheck = onDown ? LOW : HIGH;
    if (_lastState != value)
    {
      _lastState = value;
      if (value == valueToCheck)
      {
        callback();
        return true;
      }
    }
    return false;
  }
};


class Light
{
public:
  Light(int pin)
  {
    _pin = pin;
    _currentState = LOW;
    pinMode(_pin, OUTPUT);
  }

  void on()
  {
    _currentState = HIGH;
    digitalWrite(_pin, HIGH);
  }

  void off()
  {
    _currentState = LOW;
    digitalWrite(_pin, LOW);
  }

  void nextState()
  {
    digitalWrite(_pin, 1 - _currentState);
    _currentState = 1 - _currentState;
  }

  void blinkFastForMillis(int time, int blinkTime)
  {
    int times = time / blinkTime;
    for (int i = 0; i < times; i++) {
      delay(blinkTime / 2);
      nextState();
      delay(blinkTime / 2);
      nextState();
    }
  }

private:
  int _pin;
  int _currentState;
};