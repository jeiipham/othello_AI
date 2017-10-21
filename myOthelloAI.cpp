// myOthelloAI.cpp

#include <ics46/factory/DynamicFactory.hpp>
#include <iostream>
#include "myOthelloAI.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, jeffrhp1::myOthelloAI, "֎֎  ɷʃ0 ɮ 0|ɷ ֎֎  (Required)");

using namespace std;
bool BLACK; 
int DEPTH = 4;

std::pair<int, int> jeffrhp1::myOthelloAI::chooseMove(const OthelloGameState &state)
{
    BLACK = state.isBlackTurn() ? true : false; 
    gameStateVector validMoves = getValidMoves(state);
    
    int value, index = 0, max = search(*validMoves[0], DEPTH);
    for(int i = 1; i < validMoves.size(); i++)
        if((value = search(*validMoves[i], DEPTH)) > max) 
            { index = i; max = value; }
    
    int moveCount = 0;
    for(int x = 0; x < state.board().width(); x++) 
    for(int y = 0; y < state.board().height(); y++)
        if(state.isValidMove(x,y))  
        {
            if(index == moveCount) return std::pair<int, int> (x,y);
            moveCount++;    
        }

    return std::pair<int, int> (-1,-1);
}

int jeffrhp1::myOthelloAI::search(const OthelloGameState &state, int depth)
{
    if(depth == 0 || state.isGameOver()) return eval(state);
    vector<unique_ptr<OthelloGameState>> validMoves = getValidMoves(state); 
    if(isMyTurn(state)) 
    {
        int value, max = search(*validMoves[0], depth-1);
        for(int i = 1; i < validMoves.size(); i++)
            if((value = search(*validMoves[i], depth-1)) > max) max = value;
        return max;
    }   
    else
    {
        int value, min = search(*validMoves[0], depth-1);
        for(int i = 1; i < validMoves.size(); i++)
            if((value = search(*validMoves[i], depth-1)) < min) min = value;
        return min;       
    } 
}

gameStateVector jeffrhp1::myOthelloAI::getValidMoves(const OthelloGameState &state)
{
    vector<unique_ptr<OthelloGameState>> result; 
    for(int x = 0; x < state.board().width(); x++) 
    for(int y = 0; y < state.board().height(); y++)
            if(state.isValidMove(x,y)) 
            {
                result.push_back(state.clone());
                result.back()->makeMove(x,y);
            }
    return result;
}

bool jeffrhp1::myOthelloAI::isMyTurn(const OthelloGameState &state)
{
    return ( (BLACK && state.isBlackTurn()) || (!BLACK && state.isWhiteTurn()) );
}

//////////////////////////////////////////////////////////////

double jeffrhp1::myOthelloAI::getCoinEval(const OthelloGameState &state)
{
    if(BLACK) 
        return 100*(double)(state.blackScore() - state.whiteScore()) / (state.blackScore() + state.whiteScore());
    else
        return 100*(double)(state.whiteScore() - state.blackScore()) / (state.whiteScore() + state.blackScore());
}

double jeffrhp1::myOthelloAI::getCornerEval(const OthelloGameState &state)
{
    OthelloCell myCell = BLACK ? OthelloCell::black : OthelloCell::white;
    int w = state.board().width()-1, h = state.board().height()-1;
    int myCount = 0, otherCount = 0; 

    OthelloCell corner; 
    if((corner = state.board().cellAt(0,0)) == myCell) myCount++;
    else if(corner != OthelloCell::empty) otherCount++;

    if((corner = state.board().cellAt(w,h)) == myCell) myCount++;
    else if(corner != OthelloCell::empty) otherCount++;
    
    if((corner = state.board().cellAt(w,0)) == myCell) myCount++;
    else if(corner != OthelloCell::empty) otherCount++;

    if((corner = state.board().cellAt(0,h)) == myCell) myCount++;
    else if(corner != OthelloCell::empty) otherCount++;

    return 100*(double)(myCount-otherCount)/(myCount+otherCount);
}

int jeffrhp1::myOthelloAI::eval(const OthelloGameState &state) // scale of 500 or 1000, 100 each evaluation 
{
    double coinEval = getCoinEval(state); 
    double cornerEval = getCornerEval(state);
    return 2*cornerEval + coinEval;
}







