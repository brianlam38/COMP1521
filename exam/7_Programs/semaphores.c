// Solve the bank withdrawal problem using semaphores.

====================
'ORIGINAL WITHDRAW'
====================

// check balance and return amount withdrawn
int withdraw(Account acct, int howMuch)
{
   if (acct.balance < howMuch) {
      return 0; // can't withdraw
   else {
      acct.balance -= howMuch;
      return howMuch;
   }
}

====================
'SEMAPHORE WITHDRAW'
====================

The idea is we want to be able to make sure the program can run without being interfered / timed-out /
another process jumping in and executing the same code simultaneously.

This ensures that only one process at a time is accessing this account.
Anyone coming along and executes the withdraw() function will be blocked.

// initialise Semaphore value = 1
// If another process comes along and does wait(sem), it will see a value of 0 and will be blocked
init(sem, 1);

int withdraw(Account acct, int howMuch)
{
   int res;
   // set account's Semaphore
   wait(acct.sem);
   if (acct.balance < howMuch) {
      res = 0; // can't withdraw
   else {
      acct.balance -= howMuch;
      res = howMuch;
   }
   // Finished process, indicate
   signal(acct.sem);
   return res;
}