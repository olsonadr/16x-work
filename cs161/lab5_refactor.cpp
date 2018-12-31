#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//Calculates the amount of money someone would have with a given interest rate, time, and starting balance, returns this.
float calculateFutureValue(float current_value, float interest_rate, float years) {
	float future_value = current_value*(1 + interest_rate);
	future_value = pow(future_value, years);
	return future_value;
}

float parseInput(string prompt) {	
	bool flag;
	float val, decimal, res;
	string input;
	int i, count;

	do {
		cout << prompt;
		getline(cin, input);

		flag = false;
		int count = 0;
		for(int i=0; i<input.length(); i++){
			if (input[i] < '0' || input[i] > '9') {
				if (input[i] == '.') {
					count++;
					if (count > 1) {
						flag = true;	
					}	
				}
				else {
					flag = true;
				}	
			} 	
		}
	} while (flag);

	for(i = 0; i < input.length(); i++) {
		if (input[i] == '.')
			break;	
	}

	res = 0;
	val = 0;
	
	for(int j = i-1; j >= 0; j--) {
		val = ((int) input[j]) -48;
		res += val * pow(10, (i - 1 - j));
	}
	
	decimal = 0;
	count = 1;
	
	for(int k = i+1; k < input.length(); k++) {
		val = ((int) input[k]) - 48;
		decimal += val * pow(10, (-count));
		count++;
	}
	
	return res + decimal;
}

int main() {
	float current_offer = 0, future_offer = 0, ir = 0, m = 1, n = 0, res, val, decimal;
	string input = "";
	string prompt;
	int i, count;
	bool flag;
	cout << "It looks like you have two offers. Let's calculate which one is worth more." << endl;

	prompt = "Please provide the current offer amount: ";
	current_offer = parseInput(prompt);
	
	prompt = "Please provide the future offer amount: ";
	future_offer = parseInput(prompt);
	
	prompt = "Please provide the interest_rate: ";
	ir = parseInput(prompt);

	do{
		cout << "Please provide the amount of time in years between the current offer and future offer: ";
		getline(cin, input);
		flag = false;
		for(int i=0; i<input.length(); i++){
			if (input[i] < '0' || input[i] > '9') {
				flag = true;	
			}
		}
	} while (flag);
	
	for(int i = (input.length()-1); i >= 0; i--) {
		val = ((int) input[i]) - 48;
		res +=  val * pow(10,(input.length() - i -1));
	}
	n = res;

	float val_current_offer = calculateFutureValue(current_offer,ir,n);	
	float val_future_offer = future_offer/(pow((1+(ir/m)), (n*m))); 
	
	if (val_current_offer > val_future_offer) {
		cout << "Take the current offer" << endl;	
	}
	else if (val_current_offer < val_future_offer) {
		cout << "Take the future offer" << endl;	
	}	
	else {
		cout << "Choose which ever" << endl;	
	}
	
	return 0;	
}
