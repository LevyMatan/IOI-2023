#include <choreography/choreography.h>
#include <vector>

std::vector<int> POSITIONS;
std::vector<int> DANCERS;
int NUM_OF_POSITIONS;
int OFFSET;

/**
 * @brief 
 * 
 */
void update_dancers_array(){
    for (int i = 0; i < NUM_OF_POSITIONS; i++)
    {
        DANCERS[POSITIONS[i]] = i;
    }
}

/**
 * @brief 
 * 
 */
void update_positions_array(){
    for (int i = 0; i < NUM_OF_POSITIONS; i++)
    {
        POSITIONS[DANCERS[i]] = i;
    }
}

/**
 * @brief This procedure is called once at the beginning of the choreography.
 * 
 * @param N The number of dancers.
 * @param P Array of length N describing the initial order of the dancers.
 */
void init(int N, std::vector<int> P) {

    OFFSET = 0;
    NUM_OF_POSITIONS = N;

    for (int i = 0; i < N; i++)
    {
        POSITIONS.push_back(P[i]);
        DANCERS.push_back(i);
    }
    update_dancers_array();
    
    return;
}

/**
 * @brief This procedure adds a move of type 1 to the sequence of moves.
 * 
 * @param K The number of positions each dancer moves to the right. 
 */
void move_right(int K) {
    for (int i = 0; i < NUM_OF_POSITIONS; i++)
    {
        DANCERS[i] = (DANCERS[i] + K) % NUM_OF_POSITIONS;
    }
    update_positions_array();
    return;
}

/**
 * @brief This procedure adds a move of type 2 to the sequence of moves.
 * 
 * @param K The number of positions each dancer moves to the left.
 */
void move_left(int K) {
    for (int i = 0; i < NUM_OF_POSITIONS; i++)
    {
        DANCERS[i] = (DANCERS[i] - K + NUM_OF_POSITIONS) % NUM_OF_POSITIONS;
    }
    update_positions_array();
    return;
}

/**
 * @brief This procedure adds a move of type 3 to the sequence of moves.
 * 
 */
void swap_places() {
    for (int i = 0; i < NUM_OF_POSITIONS/2; i++)
    {
        int temp = POSITIONS[2*i];
        POSITIONS[2*i] = POSITIONS[2*i+1];
        POSITIONS[2*i+1] = temp;
    }
    update_dancers_array();
    
    return;
}

/**
 * @brief This procedure adds a move of type 4 to the sequence of moves.
 * 
 */
void move_around() {
    std::vector<int> temp = POSITIONS;
    for (int i = 0; i < NUM_OF_POSITIONS; i++)
    {
        POSITIONS[temp[i]] = i;
    }
    update_dancers_array();
    return;
}

/**
 * @brief This procedure should return the position of dancer D after performing every move added to the sequence of moves before this call.
 * 
 * @param D an integer representing a dancer.
 * @return int 
 */
int get_position(int D){
       
    return DANCERS[D];
}
