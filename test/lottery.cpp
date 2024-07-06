/**
 * @author      : alex (alex@mac.local)
 * @file        : lottery
 * @created     : Vineri Feb 02, 2024 19:59:54 EET
 */

#include <algorithm>  // For std::sort
#include <chrono>
#include <iomanip>   // For std::setw
#include <iostream>  // For std::cout, std::cin
#include <random>    // For all random generation stuff
#include <vector>    // For std::vector

class Ball {
 public:
  Ball(int i) { number = i; }

  int getNumber() { return number; }
  bool isRed() { return Red; }

  const bool operator==(int i) { return number == i; }
  const bool operator==(Ball &rhs) { return number == rhs.number; }
  const bool operator<(Ball &rhs) { return number < rhs.number; }
  const bool operator>(Ball &rhs) { return number > rhs.number; }

 protected:
  int number = 0;
  bool Red;
};

class WhiteBall : public Ball {
 public:
  WhiteBall(int i) : Ball(i) { Red = false; }
};

class RedBall : public Ball {
 public:
  RedBall(int i) : Ball(i) { Red = true; }
};

class RandomNumbers {
 public:
  RandomNumbers(int min, int max, int amount) {
    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<int> uid(min, max);

    for (int i = 0; i < amount; i++) {
      int num = uid(re);

      for (int n : numbers) {
        if (n == num) num = uid(re);
      }

      numbers.push_back(num);
    }
  }

  std::vector<int> getNumbers() { return numbers; }

 private:
  std::vector<int> numbers;
};

class Ticket {
 public:
  Ticket() {
    RandomNumbers ticketNums(1, 58, 6);
    numbers = ticketNums.getNumbers();
    std::sort(numbers.begin(), numbers.end());
  }

  void display(void) {
    std::cout << "Ticket:  ";
    for (int i : numbers) {
      std::cout << std::setw(2) << i << " ";
    }
    std::cout << std::endl;
  }

  std::vector<int> getNumbers() { return numbers; }

 private:
  std::vector<int> numbers;
};

class Lottery {
 public:
  Lottery() {
    RandomNumbers RandomWhite(1, 58, 5);
    RandomNumbers RandomRed(1, 34, 1);

    for (int n : RandomWhite.getNumbers()) {
      balls.push_back(new WhiteBall(n));
    }

    std::sort(balls.begin(), balls.end(),
              [](Ball *a, Ball *b) { return *a < *b; });

    balls.push_back(new RedBall(RandomRed.getNumbers()[0]));
  }

  ~Lottery() {
    for (auto ball : balls) {
      delete ball;
    }
  }

  void display(void) {
    std::cout << "Lottery: ";

    for (auto ball : balls) {
      if (ball->isRed())
        std::cout << "Red number: " << ball->getNumber() << std::endl;
      else
        std::cout << std::setw(2) << ball->getNumber() << " ";
    }
  }

  std::vector<Ball *> getBalls() { return balls; }

 private:
  std::vector<Ball *> balls;
};

class Winning {
 public:
  Winning(std::vector<Ticket *> tickets, std::vector<Ball *> balls) {
    for (auto ticket : tickets) {
      int matches = 0;
      bool hasRed = false;

      for (int number : ticket->getNumbers()) {
        for (auto ball : balls) {
          if (*ball == number) {
            matches++;

            if (ball->isRed()) hasRed = true;
          }
        }
      }

      winnsPerTicket.push_back(matches);
      hasRedTicket.push_back(hasRed);
    }
  }

  int getWinnings() {
    for (size_t i = 0; i < winnsPerTicket.size(); i++) {
      std::cout << "Got " << winnsPerTicket[i] << " matches.";

      if (hasRedTicket[i])
        std::cout << " And has got the red ball!" << std::endl;
      else
        std::cout << " But has not got the red ball." << std::endl;
    }

    return 0;
  }

 private:
  std::vector<int> winnsPerTicket;
  std::vector<bool> hasRedTicket;
};

class BlackJack {
  // This is a new class
 public:
  void shuffle() {
    for (int i = 0; i < 52; i++) {
      int j = rand() % 52;
      int temp = cards[i];
      cards[i] = cards[j];
      cards[j] = temp;
    }
  }

  void DisplayCard() {
    int card = rand() % 52;
    int number = card % 13;
    int suit = card / 13;

    std::string suits[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    std::string numbers[13] = {"Ace", "2", "3",  "4",    "5",     "6",   "7",
                               "8",   "9", "10", "Jack", "Queen", "King"};

    std::cout << numbers[number] << " of " << suits[suit] << std::endl;
    sum += number;
  }

 private:
  int cards[52], sum;
  int currentCard;
};

class Game {
 public:
  Game(){};
  ~Game() {
    for (auto ticket : tickets) {
      delete ticket;
    }
  }

  void Menu() {
    int numTic = 0;
    std::cout << "Welcome to the PowerBall Lottery!" << std::endl;
    std::cout << "To play you need to purchase a ticket at $2. More tickets "
                 "increase the odds to win."
              << std::endl;
    std::cout << "How many tickets would you like? " << std::endl;

    do {
      std::cout << "Enter amount of tickets you would like to purchase: ";
      std::cin >> numTic;
      std::cin.sync();

      if ((numTic < 1) || (numTic > 1000000)) {
        std::cout << "Input invalid. Needs to be a number between 1 and 100. "
                     "Please try again"
                  << std::endl;
      }
    } while ((numTic < 1) || (numTic > 1000000));

    createTickets(numTic);

    std::cout << "Your tickets are registered. Thank you for playing the "
                 "PowerBall lottery!"
              << std::endl;
  }

  void Play() {
    std::cout << "Let\'s see this weeks PowerBall lottery numbers!"
              << std::endl;

    lotto.display();

    for (auto ticket : tickets) {
      ticket->display();
    }

    Winning w(tickets, lotto.getBalls());
    w.getWinnings();
  }

  void PlayBlackJack() {
    char answer;
    do {
      std::cout << "Welcome to BlackJack!" << std::endl;
      std::cout << "Would you like to play a game of BlackJack?" << std::endl;
      std::cout << "Enter 'y' for yes or 'n' for no: ";
      std::cin >> answer;
      std::cin.sync();

      if (answer == 'y') {
        std::cout << "Great! Let's play!" << std::endl;
        bj.shuffle();
        bj.DisplayCard();
      } else {
        std::cout << "That's too bad. Maybe next time." << std::endl;
      }
    } while (sum <= 21 && answer == 'y');
  }

 private:
  std::vector<Ticket *> tickets;
  Lottery lotto;
  BlackJack bj;
  int sum;

  void createTickets(int numTic) {
    for (int i = 0; i < numTic; i++) {
      tickets.push_back(new Ticket);
    }
  }
};

int main() {
  std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

  rng.seed(std::random_device()());

  Game game;
  game.Menu();
  game.Play();
  game.PlayBlackJack();

  return 0;
}
