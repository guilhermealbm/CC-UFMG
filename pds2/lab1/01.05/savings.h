#ifndef PDS2_SAVINGSACCOUNT_H
#define PDS2_SAVINGSACCOUNT_H

class SavingsAccount {
    private:
    
        double _savings_balance;
        
    public:
    
        static double annual_savings_rate;
    
        SavingsAccount(double savings_balance);
        
        double calculate_monthly_balance();
        static void modify_interest_rate(double novo_valor);
    
};

#endif