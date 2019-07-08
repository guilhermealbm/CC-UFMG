#include "savings.h"

double SavingsAccount::annual_savings_rate = 0;

SavingsAccount::SavingsAccount(double savings_balance) {
  _savings_balance = savings_balance;
}

double SavingsAccount::calculate_monthly_balance(){
    _savings_balance += (_savings_balance*SavingsAccount::annual_savings_rate)/12;
    return((_savings_balance*SavingsAccount::annual_savings_rate)/12);
}

void SavingsAccount::modify_interest_rate(double novo_valor){
    SavingsAccount::annual_savings_rate = novo_valor;
}