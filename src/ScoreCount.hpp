#ifndef SCORECOUNT_HPP
#define SCORECOUNT_HPP

class score
{
    public:
    void IncreaseCounter(int PlrNum) 
    {
        if (PlrNum == 1) {
            P_OneScore++;
        } else {
            P_TwoScore++;
        }
    }

    void ResetCounter() 
    {
        P_OneScore = 0;
        P_TwoScore = 0;
    }

    int GetScore(int PlrNum) 
    {
        if (PlrNum == 1) {
            return P_OneScore;
        } else {
            return P_TwoScore;
        }
    }
    private:
    int P_OneScore = 0;
    int P_TwoScore = 0;
};

#endif