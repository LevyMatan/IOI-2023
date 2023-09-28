#include <choreography/choreography.h>

#include <vector>
namespace choreography_steps_1_2_optimized {
using namespace std;


  class array_index{
    public:
      int value;
      int base;

      array_index(int value, int base){
        this->base = base;
        this->value = value % this->base;
      }

      array_index(int value){
        this->base = 2;
        this->value = value % this->base;
      }

      array_index(){
        this->base = 2;
        this->value = 0;
      }

      // return int value
      operator int() const { return value; }

      // define the `+` operator
      array_index operator+(const array_index& rhs) const {
        array_index result = *this;     // Make a copy of myself.
        result.value += rhs.value;      // Add the value of the other array_index.
        result.value %= this->base;     // Make sure we stay within bounds.
        return result;                  // Return the result.
      }

      // define the `-` operator
      array_index operator-(const array_index& rhs) const {
        array_index result = *this;     // Make a copy of myself.
        result.value = rhs.value;      // Add the value of the other array_index.
        result.value = (result.value + this->base) % this->base;     // Make sure we stay within bounds.
        return result;                  // Return the result.
      }

      void toggle(){
        this->value = (this->value + 1) % this->base;
      }

      void set_value(int value){
        this->value = value % this->base;
      }
      int get_value(){
        return this->value;
      }


  };

  /**
   * @brief g_array is a 2D array of size 2 x N, where N is the number of dancers/positions.
   * Each row of the vector will display the same choreography but in different manner.
   * One row will display the choreography in terms of dancers, the other in terms of positions.
   * That is, in one vector, each cell represent a postion and the value of the cell is the dancer.
   * I.E. g_array[position_array][0] = 1 means that dancer 1 is in position 0.
   * The other row will display the choreography in terms of dancers, where each cell represent
   * a dancer and the value of the cell is its position.
   * I.E. g_array[dancer_array][3] = 7 means that dancer 3 is in position 7.
   * The rows can switch rules between each other.
   * Two indexes are used to keep track of the current row and the other row.
   * dancer_array is an integer of values 0 or 1, the index is pointing to the row of the dancer notation.
   * position_array is an integer of values 0 or 1, the index is pointing to the row of the position notation.
   * They will never hold the same value at the same time.
   * 
   */
  vector<vector<int>> g_array;

  array_index dancer_array(1);
  array_index position_array(0);

  int NUM_OF_POSITIONS;
  int OFFSET;
  bool TOUCHED_POSITION_ARRAY = false;

  /**
   * @brief This procedure is called once at the beginning of the choreography.
   *
   * @param N The number of dancers.
   * @param P Array of length N describing the initial order of the dancers.
   */
  void init(int N, std::vector<int> P) {
    NUM_OF_POSITIONS = N;
    OFFSET = 0;
    g_array.resize(2);
    g_array[dancer_array].resize(N);
    g_array[position_array].resize(N);

    for (int i = 0; i < N; i++) {
      g_array[position_array][i] = P[i];
      g_array[dancer_array][P[i]] = i;
    }

    return;
  }

  void move_right(int K) {
    OFFSET = (OFFSET + K) % NUM_OF_POSITIONS;
    return;
  }

  void move_left(int K) {
    OFFSET = (OFFSET - K + NUM_OF_POSITIONS) % NUM_OF_POSITIONS;
    return;
  }

  /**
   * @brief This procedure adds a move of type 3 to the sequence of moves.
   *
   */
  void swap_places() {
    if(OFFSET){
      vector<int> temp = g_array[position_array];
      for (int i = 0; i < NUM_OF_POSITIONS; i++) {
        g_array[dancer_array][i] = (g_array[dancer_array][i] + OFFSET) % NUM_OF_POSITIONS;
        g_array[position_array][(i + OFFSET) % NUM_OF_POSITIONS] = temp[i];
      }
      OFFSET = 0;
    }
    for (int i = 0; i < NUM_OF_POSITIONS / 2; i++)
    {
      int dancer_2i = g_array[position_array][2 * i];
      int dancer_2i_1 = g_array[position_array][2 * i + 1];
      g_array[position_array][2 * i] = dancer_2i_1;
      g_array[position_array][2 * i + 1] = dancer_2i;

      g_array[dancer_array][dancer_2i] = 2 * i + 1;
      g_array[dancer_array][dancer_2i_1] = 2 * i;
    }
    
    return;
  }

  /**
   * @brief This procedure adds a move of type 4 to the sequence of moves.
   *
   */
  void move_around() {
    if(OFFSET){
      vector<int> temp = g_array[position_array];
      for (int i = 0; i < NUM_OF_POSITIONS; i++) {
        g_array[dancer_array][i] = (g_array[dancer_array][i] + OFFSET) % NUM_OF_POSITIONS;
        g_array[position_array][(i + OFFSET) % NUM_OF_POSITIONS] = temp[i];
      }
      OFFSET = 0;
    }
    dancer_array.toggle();
    position_array.toggle();
    return;
  }

  /**
   * @brief This procedure should return the position of dancer D after performing every move added
   * to the sequence of moves before this call.
   *
   * @param D an integer representing a dancer.
   * @return int
   */
  int get_position(int D) { 

    return (g_array[dancer_array][D] + OFFSET) % NUM_OF_POSITIONS; 
  }

}

namespace choreography_naive {

  std::vector<int> POSITIONS;
  std::vector<int> DANCERS;
  int NUM_OF_POSITIONS;
  int OFFSET;

  /**
   * @brief
   *
   */
  void update_dancers_array() {
    for (int i = 0; i < NUM_OF_POSITIONS; i++) {
      DANCERS[POSITIONS[i]] = i;
    }
  }

  /**
   * @brief
   *
   */
  void update_positions_array() {
    for (int i = 0; i < NUM_OF_POSITIONS; i++) {
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
    NUM_OF_POSITIONS = N;

    for (int i = 0; i < N; i++) {
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
    for (int i = 0; i < NUM_OF_POSITIONS; i++) {
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
    for (int i = 0; i < NUM_OF_POSITIONS; i++) {
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
    for (int i = 0; i < NUM_OF_POSITIONS / 2; i++) {
      int temp = POSITIONS[2 * i];
      POSITIONS[2 * i] = POSITIONS[2 * i + 1];
      POSITIONS[2 * i + 1] = temp;
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
    for (int i = 0; i < NUM_OF_POSITIONS; i++) {
      POSITIONS[temp[i]] = i;
    }
    update_dancers_array();
    return;
  }

  /**
   * @brief This procedure should return the position of dancer D after performing every move added
   * to the sequence of moves before this call.
   *
   * @param D an integer representing a dancer.
   * @return int
   */
  int get_position(int D) { return DANCERS[D]; }

}  // namespace choreography_naive
