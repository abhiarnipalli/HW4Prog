# Who-Wants-to-Win

  At the height of the popularity of “Who wants to be a millionaire”, various versions of the show was
produced in other countries and were also immensely popular. In fact, it is so popular that the planet
“Alpha Centuri” decided to produce their own version of the show, and call it “Who Wants to Win Wads
of Water” (In Alpha Centuri, “Wads of Water” is a slang for “Lots of Money”).

  While they are happy with the general structure of the game, they also want to experiment with various
aspect of the game (number of questions, where is the safety line for the contestants, how does the
lifeline works etc.) And they want to write a program to run some tests and calculate the expected
amount of money that a contestant can win (so they can have enough money to prepare).

For the base case, the rules are as follows.
- The game consists of j questions (where j is a parameter to be provided) (You can assume j > 3).
- The contestant is to answer the questions one at a time.
- At any moment, the contestant can quit.
- If the contestant quits after answering k questions correctly, he/she will win wk dollars (1 ≤ k ≤ j). All the values of w1, w2, … wj are parameters to be provided, with the stipulation that the dollar amount will strictly increases as the number of correct answer increases.
- If a contestant answers a question wrong, the game ends immediately.
  - There will be two numbers 1 ≤ s < t < j. If the contestant answers at least t questions correctly, he/she will receive wt dollars. Otherwise, if the constant answer at least s questions correctly, he/she will receive ws dollars. Otherwise, he/she will receive 0 dollars.
- There are no lifelines available.
- For question k, we will assume the contestant has a probability of pk of answering that question
correctly. (0.25 ≤ pk < 1)

# Task

You are to implement the following function:
pair< vector<float>, vector<int> > WWWWW(vector<float> w, vector<float> p, int s, int t)

This program will return a pair of vectors:
- The first vector contains the expected amount of money won. The i-th entry stores the expected amount of money won after the contestant answer i questions correctly.
- The second vector stores 0 or 1 The (i-1)-th entry stores whether the contestant should quit when he face question i (recall there is no question 0). You must use the dynamic programming algorithm discussed.
