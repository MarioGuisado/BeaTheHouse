#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
using namespace std;

bool ValidBankroll(int bankroll){
		bool valid = false;
		if(bankroll >= 100 && bankroll <= 10000)
			valid = true;
		return valid;
}
bool ValidBet(int bet, int min_bet){
		bool valid = false;
		if(bet >= min_bet && bet <= 100)
			valid = true;
		return valid;
}
class Game{
	private:
		int games_played, min_bet, actual_bet, bankroll, safebet;
	public:
		Game(int bankroll_){
			games_played = 0;
			min_bet = 1;
			bankroll = bankroll_;
		}
		int GetBankroll(){
			return bankroll;
		}
		int GetMinimumBet(){
			return min_bet;
		}
		void DoubleBet(){
			actual_bet *= 2;
			bankroll -= actual_bet;
		}
		void SelectBet(int bet){
			while(!ValidBet(bet, min_bet)){
				cout << "min = " << min_bet << " / max = " << 100 << endl;
				cin >> bet;
			}
			actual_bet = bet;
			bankroll -= actual_bet;
			safebet = 0;
		}
		void SelectSafeBet(){
			safebet = actual_bet / 2;
		}		
		void TimeToPay(int winner, bool blackjack ){
			if(winner == 1){
				if(blackjack)
					bankroll += actual_bet + ((actual_bet * 3) / 2);
				else
					bankroll += (actual_bet * 2);
				}
			else if(winner == 3)
				bankroll += actual_bet;
		}
		void PaySafeBet(){
			bankroll += safebet + (safebet * 2);
		}
	};
class Deck{
	private:
		static const int DIM_DECK = 208; //4 decks
		static const int DIM = 10;
		float DECK[DIM_DECK] = {1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1, 9.1, 10.1, 11.1, 12.1, 13.1, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 
		1.3, 2.3, 3.3, 4.3, 5.3, 6.3, 7.3, 8.3, 9.3, 10.3, 11.3, 12.3, 13.3, 1.4, 2.4, 3.4, 4.4, 5.4, 6.4, 7.4, 8.4, 9.4, 10.4, 11.4, 12.4, 13.4, 1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1, 9.1, 10.1, 11.1, 12.1, 13.1, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2,
		 1.3, 2.3, 3.3, 4.3, 5.3, 6.3, 7.3, 8.3, 9.3, 10.3, 11.3, 12.3, 13.3, 1.4, 2.4, 3.4, 4.4, 5.4, 6.4, 7.4, 8.4, 9.4, 10.4, 11.4, 12.4, 13.4,1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1, 9.1, 10.1, 11.1, 12.1, 13.1, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 
		 1.3, 2.3, 3.3, 4.3, 5.3, 6.3, 7.3, 8.3, 9.3, 10.3, 11.3, 12.3, 13.3, 1.4, 2.4, 3.4, 4.4, 5.4, 6.4, 7.4, 8.4, 9.4, 10.4, 11.4, 12.4, 13.4,1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1, 9.1, 10.1, 11.1, 12.1, 13.1, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2,
		 1.3, 2.3, 3.3, 4.3, 5.3, 6.3, 7.3, 8.3, 9.3, 10.3, 11.3, 12.3, 13.3, 1.4, 2.4, 3.4, 4.4, 5.4, 6.4, 7.4, 8.4, 9.4, 10.4, 11.4, 12.4, 13.4};
		int num_cards, num_house_cards, total, second_total, house_total, second_house_total, actual_card;
		float hand[DIM], house_hand[DIM]; //0.1 = clubs, 0.2 = diamonds, 0.3 = hearts, 0.4 = spades
		bool house_stands, alternative, alternative_house;
	public:
	Deck(){
		num_cards = 0;
		num_house_cards = 0;
		house_stands = false;
		actual_card = 0;
		for(int i = 0; i < DIM; i++){
			hand[i] = 0;
			house_hand[i] = 0;
		}
		srand(time(0));
		int random_pos;
		float aux_card[1];
		for(int i = 0; i < 208; i++){
			random_pos = i + (rand() % (208 - i));
			aux_card[0] = DECK[i];
			DECK[i] = DECK[random_pos];
			DECK[random_pos] = aux_card[0];
		}
	}
	bool CheckSplit(){
		bool split = false;
		int card_1 = hand[0], card_2 = hand[1];
		if(card_1 >= 10 && card_2 >= 10 && card_1 == card_2)
			split = true;
		return split;
	}
	void Restart(){
		num_cards = 0;
		num_house_cards = 0;
		total = 0;
		second_total = 0;
		second_house_total = 0;
		house_stands = false;
	}
	bool PlayerBusts(){
		bool busts = false;
		if(total > 21)
			busts = true;
		return busts;
	}
	int Winner(bool & blackjack){ // Winner = 1 if the player gets paid, 2 if the player has to pay or 3 if it's a draw
		blackjack = false;
		int totals[4];
		totals[0] = 21 - total;
		totals[1] = 21 - second_total;
		totals[2] = 21 - house_total;
		totals[3] = 21 - second_house_total;
		int winner = totals[0], winner2 = totals[2];
		if(totals[1] < winner && totals[1] >= 0)
			winner = totals[1];
		if(totals[3] < winner2 && totals[3] >= 0)
			winner2 = totals[3];
		if(winner2 == winner)
			winner = 3;
		else if(winner2 < winner && winner2 >= 0)
			winner = 2;
		else{
			if(winner == 0)
				blackjack = true;
			winner = 1;
		}
		return winner;
	}	
	int GetTotal(){
		return total;
	}
	bool CheckSafeBetPossibility(){
		bool safe_bet = false;
		if(second_house_total == 11)
			safe_bet = true;
		return safe_bet;
	}	
	void ShowDeck(){
		for(int i = 0; i < 208; i++)
			cout << DECK[i] << " ";					
	}
	void ShowHand(){
		int card;
		float key;
		cout << "\nYour hand is: \n" << endl;
		for(int i = 0; i < num_cards; i++){
			card = hand[i];
			key = hand[i];
			cout << card << " ";
			if((key - card) > 0.1 && ((key - card) < 0.2))
				cout << "Clubs \n" << endl;
		   else if((key - card) > 0.2 && ((key - card) < 0.3))
				cout << "Diamonds \n" << endl;
			else if((key - card) > 0.3 && ((key - card) < 0.4))
				cout << "Hearts \n" << endl;
			else
				cout << "Spades \n" << endl;
		}
	}
	void ShowHouseHand(){
		int card;
		float key;
		cout << "The hand of the house is: \n" << endl;
		for(int i = 0; i < num_house_cards; i++){
			card = house_hand[i];
			key = house_hand[i];
			cout << card << " ";
			if((key - card) > 0.1 && ((key - card) < 0.2))
				cout << "Clubs \n" << endl;
		   else if((key - card) > 0.2 && ((key - card) < 0.3))
				cout << "Diamonds \n" << endl;
			else if((key - card) > 0.3 && ((key - card) < 0.4))
				cout << "Hearts \n" << endl;
			else
				cout << "Spades \n" << endl;
		}	
	}
	void AskCard(){
		hand[num_cards] = DECK[actual_card];
		DECK[actual_card] = 0;
		num_cards++;
		actual_card++;
	}
	bool CheckIfHouseStands(){
		return house_stands;
	}
	void AskHouseCard(){
		if(second_house_total < 17 || (house_total < 17 && second_house_total > 21 )){
			house_hand[num_house_cards] = DECK[actual_card];
			DECK[actual_card] = 0;
			num_house_cards++;
			actual_card++;
		}
		else
			house_stands = true;
	}
	void CalculateTotal(){
		alternative = false;
		total = 0, second_total = 0;
		int card;
		for(int i = 0; i < num_cards; i ++){
			card = hand[i];
			if(card == 11 || card == 12 || card == 13)
				card = 10;
			total += card;
			if(card == 1){
				alternative = true;
				card = 11;
			}
			second_total += card;
		}
	}
	void ShowTotal(){
		cout << "Your total is: " << total << endl;
		if(alternative && second_total < 22)
			cout << "Your alternative total (soft hand) is: " << second_total << endl;
	}
	void CalculateHouseTotal(bool & PaySafeBet){	
		PaySafeBet = false;
		alternative = false;
		house_total = 0, second_house_total = 0;
		int card;
		for(int i = 0; i < num_house_cards; i ++){
			card = house_hand[i];
			if(card == 11 || card == 12 || card == 13)
				card = 10;
			house_total += card;
			if(card == 1){
				alternative = true;
				card = 11;
			}
			second_house_total += card;
		}
		if(house_total == 21 && num_house_cards == 2)
			PaySafeBet = true;
	}
	void ShowHouseTotal(){
		cout << "The house total is: " << house_total << endl;
		if(alternative && second_house_total < 22)
			cout << "The house alternative total (soft hand) is: " << second_house_total << endl;
	}		 
	void InitialHand() {
		for(int i = 0; i < 2; i++){
			hand[i] = DECK[actual_card];
			DECK[actual_card] = 0;
			num_cards++;
			actual_card++;
		}
		house_hand[0] = DECK[actual_card];
		DECK[actual_card] = 0;
		num_house_cards++;
		actual_card++;
		}
};

int main() {
	cout << "Welcome to: BeaTheHouse!\n An open source software to help you improve your counting-cards skills \n" << 
	 "REMEMBER: \n - The only blackjack variation available -for the moment- is the european one \n - Insurance pays 2 to 1 \n" 
	 << " - Dealer Must Stand on all 17's \n - There are exactly 4 randomly shuffled decks at the beginning of the game, each time you get a card, it will be taken out of the main deck \n" << 
	 " - Have fun " << endl;
	
  int bankroll;
  bool exit = false;
  cout << "\nPlease enter your bankroll: (min 100/ max 10000)" << endl;
  cin >> bankroll;
  
  while(!ValidBankroll(bankroll)){
      cout << "(min 100/ max 10000)" << endl;
		cin >> bankroll;
  }
  
  int initial_bankroll = bankroll;

  Game game(bankroll);
  Deck deck;
  bool blackjack, newgame = true, double_down, safebet;
  int bet, choice, winner;
  
  while(game.GetBankroll() > 0 && !exit){
	  	if(newgame){
		  deck.Restart();
		  cout << "\n-------------------------------------------------------------------------------------\nEnter your bet or 0 to exit:         	minimum bet = " << game.GetMinimumBet() << "     	Actual Bankroll: " << game.GetBankroll() << endl;
		  cin >> bet;
		  if(bet != 0){
		  		double_down = false;
		  		game.SelectBet(bet);
		  		deck.InitialHand();
		  		deck.ShowHand();
		  		deck.ShowHouseHand();
		  		deck.CalculateTotal();
		  		deck.ShowTotal();
		  		deck.CalculateHouseTotal(safebet);
		  		deck.ShowHouseTotal();
		  
		  		if(deck.CheckSafeBetPossibility()){
  					cout << "\nWould you like to make a Safe Bet?: (YES = 1 / NO = 2):\n" << endl;
  					cin >> bet;
  					while(bet != 1 && bet != 2){
  						cout << "\nPlease enter a valid option \n";
  						cin >> bet;
  					}
	   		}
	   	newgame = false;
	  	}
	}
	   if(bet !=0 && !deck.PlayerBusts() && !double_down){
  			cout << endl << "Enter 1 = hit | 2 = stand | 3 = split | 4 = double down \n" << endl;
  			cin >> choice;
  			while(choice < 1 || choice > 4 || (choice == 4 && (deck.GetTotal() < 9 || deck.GetTotal() > 11)) || (choice == 3 && !deck.CheckSplit())){
  				if(choice == 4)
  					cout << "\nDoubling down is only available when your total equals 9, 10 or 11" << endl;
  				else if(choice == 3)
  					cout << "\nSplitting is only available when you are dealt a pair of 10-value cards of the same face/value" << endl;
				cout << "\nPlease select a valid choice :" << endl;
  				cin >> choice;
  			}
  		}
  		if(bet == 0){
  			cout << "\nYour initial bankroll was: " << initial_bankroll << endl << "Your final bankroll is: " << game.GetBankroll() << endl;
			sleep(4);
			exit = true;
		}
		else{
			if(deck.PlayerBusts()){
				newgame = true;
			}
			else if(choice == 1)
				deck.AskCard();
			else if(choice == 2){
				while(!deck.CheckIfHouseStands()){
					deck.AskHouseCard();
					deck.CalculateHouseTotal(safebet);
				}
				if(safebet)
					game.PaySafeBet();
				else{
					winner = deck.Winner(blackjack);
					game.TimeToPay(winner, blackjack);
					newgame = true;
				}
			}
			else if(choice == 3){
				
			}
			else{
				deck.AskCard();
				game.DoubleBet();
				double_down = true;
				choice = 2;
			}
			deck.ShowHand();
			deck.ShowHouseHand();
			deck.CalculateTotal();
			deck.ShowTotal();
			deck.CalculateHouseTotal(safebet);
			deck.ShowHouseTotal();	
		}	
  	}
}

























