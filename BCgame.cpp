/*
this is a bull cow game AI
Bull Cow Game define as follow:
a four digit number is the answer
each digit is 1 ~ 9, no repeat
*/
#include <cstdio>
#include <vector>

typedef struct his{
	int num;
	int A;
	int B;
}His;

using namespace std;

int notValid(int num){
	int temp[4];
	for(int i = 0; i < 4; i++){
		temp[i] = num % 10;
		if(temp[i] == 0){
			return 1;
		}
		num /= 10;
	}
	for(int i = 0; i < 4; i++){
		for(int j = i + 1; j < 4; j++){
			if(temp[i] == temp[j])
				return 1;
		}
	}
	return 0;
}

int countA(int num, int ans){
	int count = 0;
	for(int i = 0; i < 4; i++){
		if((num % 10) == (ans % 10)) count++;
		num /= 10;
		ans /= 10;
	}
	return count;
}

int countB(int num, int ans){
	int count = 0;
	for(int i = 0; i < 4; i++){
		int temp = num;
		int check_digit = ans % 10;
		for(int j = 0; j < 4; j++){
			int temp_digit = temp % 10;
			temp /= 10;
			if(i == j) continue;
			if(temp_digit == check_digit) count++;
		}
		ans /= 10;
	}
	return count;
}

int aux_badguess(int num, int his_num, int his_A, int his_B){
	int _A = countA(num, his_num);
	int _B = countB(num, his_num);
	if(_A < his_A || _B < his_B) return 1;
	if((his_A + his_B != 4) && (_A + _B == 4)) return 1;
	return 0;
}

int badguess(int num, vector<His*> *table){
	int _n = (int)(*table).size();
	//printf("%d\n", _n);
	for(int i = 0; i < _n; i++){
		if(aux_badguess(num, (*table)[i]->num, (*table)[i]->A, (*table)[i]->B)){
			return 1;
		}
	}
	return 0;
}

int guess(int num, vector<His*> *table, int ans){
	int _A = countA(num, ans);
	int _B = countB(num, ans);
	printf("%dA%dB\n", _A, _B);

	if(_A == 4 && _B == 0){
		return 1;
	}
	His *temp = new His;
	temp->num = num;
	temp->A = _A;
	temp->B = _B;

	(*table).push_back(temp);

	return 0;
}

int main(){
	// //char ans[5] = "1234\n";
	int ans = 9136;
	scanf("%d", &ans);
	vector<His*> table;

	// //printf("Please enter a 4 digit numbers\n");
	// //scanf("%s", ans);
	int num; 
	int guess_count = 0;

	printf("I guess 1234.\n");
	guess_count++;
	if(guess(1234, &table, ans)){
		printf("Haha! I win!\n");
		printf("Total guess count: %d\n", guess_count);
		return 0;
	}
	printf("I guess 5678.\n");
	guess_count++;
	if(guess(5678, &table, ans)){
		printf("Haha! I win!\n");
		printf("Total guess count: %d\n", guess_count);
		return 0;
	}
	for(num = 1235; num <= 9876; num++){
		//check if valid number
		if(notValid(num)){
			continue;
		}
		//compair with history guess
		if(badguess(num, &table)){
			continue;
		}
		//try this number
		printf("I guess %d.\n", num);
		guess_count++;
		//check answer, if miss save to history guess
		if(guess(num, &table, ans)){
			printf("Haha! I win!\n");
			printf("Total guess count: %d\n", guess_count);
			break;
		}
	}

	return 0;
}