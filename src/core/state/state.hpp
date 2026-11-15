#pragma once

enum class StateType{
    MainMenu,
    Tutorial,
    Editor,
    Exit
};

class State{
private:
    StateType currentState;

public:
    State() : currentState(StateType::MainMenu) {}
    void setState(StateType newState) { currentState = newState; }
    StateType getState() const { return currentState; }
};