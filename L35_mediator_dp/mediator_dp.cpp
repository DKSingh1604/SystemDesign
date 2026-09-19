#include <iostream>
#include <string>
#include <utility>
#include <vector>

class IColleague; // Forward declaration

// 1. Abstract Mediator Interface
class IMediator {
public:
  virtual void registerUser(IColleague *user) = 0;
  virtual void sendAll(IColleague *sender, const std::string &msg) = 0;
  virtual void sendTo(IColleague *sender, const std::string &receiverName,
                      const std::string &msg) = 0;
  virtual ~IMediator() = default;
};

// 2. Abstract Colleague Interface
class IColleague {
protected:
  IMediator *mediator;
  std::string name;

public:
  IColleague(IMediator *m, std::string n) : mediator(m), name(n) {}
  std::string getName() const { return name; }

  virtual void sendAll(const std::string &msg) = 0;
  virtual void sendTo(const std::string &to, const std::string &msg) = 0;
  virtual void receive(const std::string &from, const std::string &msg) = 0;
  virtual ~IColleague() = default;
};

// 3. Concrete Mediator
class ChatMediator : public IMediator {
private:
  std::vector<IColleague *> users;
  // Stores blocked pairs: <MutedUser, MutedBy>
  std::vector<std::pair<std::string, std::string>> mutedPairs;

public:
  void registerUser(IColleague *user) override { users.push_back(user); }

  void muteUser(const std::string &mutedUser, const std::string &mutedBy) {
    mutedPairs.push_back({mutedUser, mutedBy});
  }

  void sendAll(IColleague *sender, const std::string &msg) override {
    for (auto user : users) {
      // Don't send back to the sender
      if (user != sender) {
        user->receive(sender->getName(), msg);
      }
    }
  }

  void sendTo(IColleague *sender, const std::string &receiverName,
              const std::string &msg) override {
    // Check if sender is muted by receiver
    for (const auto &pair : mutedPairs) {
      if (pair.first == sender->getName() && pair.second == receiverName) {
        std::cout << "[System] Message blocked: " << sender->getName()
                  << " is muted by " << receiverName << "\n";
        return;
      }
    }

    for (auto user : users) {
      if (user->getName() == receiverName) {
        user->receive(sender->getName(), msg);
        return;
      }
    }
  }
};

// 4. Concrete Colleague
class User : public IColleague {
public:
  User(IMediator *m, std::string n) : IColleague(m, n) {
    mediator->registerUser(this);
  }

  void sendAll(const std::string &msg) override {
    std::cout << name << " broadcasts: " << msg << "\n";
    mediator->sendAll(this, msg);
  }

  void sendTo(const std::string &to, const std::string &msg) override {
    std::cout << name << " sends to [" << to << "]: " << msg << "\n";
    mediator->sendTo(this, to, msg);
  }

  void receive(const std::string &from, const std::string &msg) override {
    std::cout << name << " received from " << from << ": " << msg << "\n";
  }
};

int main() {
  ChatMediator mediator;

  User alice(&mediator, "Alice");
  User bob(&mediator, "Bob");
  User charlie(&mediator, "Charlie");
  User dave(&mediator, "Dave");

  std::cout << "--- Broadcast Example ---\n";
  alice.sendAll("Hello everyone!");

  std::cout << "\n--- Direct Message Example ---\n";
  bob.sendTo("Alice", "Hi Alice, how are you?");

  std::cout << "\n--- Mute Example ---\n";
  // Charlie mutes Dave
  mediator.muteUser("Dave", "Charlie");

  // Dave tries to send a message to Charlie
  dave.sendTo("Charlie", "Hey Charlie, did you see my message?");

  // Dave sends to someone else
  dave.sendTo("Bob", "Hey Bob, what's up?");

  return 0;
}