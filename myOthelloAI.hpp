// myOthelloAI.hpp

#ifndef MYOTHELLOAI_HPP
#define MYOTHELLOAI_HPP

#include "OthelloAI.hpp"
#include <vector>

typedef std::vector<std::unique_ptr<OthelloGameState>> gameStateVector;
 
namespace jeffrhp1
{
   
    class myOthelloAI : public OthelloAI
    {
    public: 
        virtual std::pair<int, int> chooseMove(const OthelloGameState &state);
    
    private:
        int search(const OthelloGameState &state, int depth);  
        int eval(const OthelloGameState &state);
                
        std::vector<int> getValues(const OthelloGameState &state);
        std::vector<std::unique_ptr<OthelloGameState>> getValidMoves(const OthelloGameState &state);
        bool isMyTurn(const OthelloGameState &state);
       
        double getCoinEval(const OthelloGameState &state);
        double getCornerEval(const OthelloGameState &state);
        
    };
}

#endif 
