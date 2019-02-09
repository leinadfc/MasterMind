#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include<string>
#include<cstdlib>
#include<random>
#include<chrono>

void set_random_seed ();
int randn (int n);

struct mm_code_maker {


  void init (int i_length, int i_num) {
    length = i_length;
    num = i_num;
  }

  void generate_sequence () {
    for (int i = 0; i < length; i++)
    {
	sequence.push_back (randn (num));
    }
  }

  void give_feedback (const std::vector < int >&attempt, int &black_hits,
		      int &white_hits) {

    std::vector < int >hits_per_int;
    int numbers_attempt = 0;
    int numbers_sequence = 0;
    int hits = 0;
    for (int i = 0; i < num; i++) {
	    for (int j = 0; j < length; j++) {
	       if (attempt[j] == i) {
		       numbers_attempt++;
	       }
	       if (sequence[j] == i) {
		       numbers_sequence++;
	       }
	     }
	    if (numbers_attempt <= numbers_sequence) {
	     hits_per_int.push_back (numbers_attempt);
	    }
	    if (numbers_attempt > numbers_sequence) {
	    hits_per_int.push_back (numbers_sequence);
	    }
	    numbers_attempt = 0;
	    numbers_sequence = 0;
    }

    for (int i = 0; i < hits_per_int.size (); i++) {
	     hits += hits_per_int[i];
    }

    for (int i = 0; i < attempt.size (); i++) {
	     if (attempt[i] == sequence[i]) {
	    black_hits++;
	     }
    }

    white_hits = hits - black_hits;
  }


  std::vector < int >sequence;
  int length;
  int num;

};

struct mm_solver {

  void init (int i_length, int i_num) {
    length = i_length;
    num = i_num;

  }

  void create_attempt (std::vector < int >&attempt) {

    std::string attempt_string;
    std::vector < int >helpfulness;
    std::vector < int >eliminated;
    std::vector < int >possible_atemmpt;
    int white_hits;
    int black_hits;
    int small_eliminated;
    attempt.reserve(length);
    if (((length<=5)&&(num<=4)) || ((length<=3)&&(num<=7))) {
     if (remaining_possibilities.size () == 0) {
      main_list();
      for (int i=0; i<=length; i++){
        for (int j=0; j<=length; j++){
          if (i+j<=length && !(i==length-1 && j==1)){
          poss_black.push_back(i);
          poss_white.push_back(j);
          }
        }
      }
	    for (int i = 0; i < length/2; i++) {
	       attempt.push_back (0);
	     }
       for(int i=attempt.size(); i<length; i++){
         attempt.push_back(1);
       }
    }
    else {

	if (remaining_possibilities.size () == 1) {
	    attempt_string = remaining_possibilities[0];
	 }

	if ((remaining_possibilities.size () != 0)
	&& (remaining_possibilities.size () != 1)) {
	    for (int i = 0; i < mainlist.size (); i++) {
		       for (int j = 0; j < poss_black.size(); j++) {
		          small_eliminated = 0;
		          for (int k = 0; k < remaining_possibilities.size(); k++) {
                give_feedback_fake_2 (remaining_possibilities[k], black_hits,
  					    white_hits, mainlist[i]);
			             if ((black_hits != poss_black[j]) || (white_hits != poss_white[j])) {
			                  small_eliminated++;

			             }
		           }

		           eliminated.push_back (small_eliminated);
		       }
		       int minimum_eliminated = eliminated[0];
		       for (int p = 0; p < eliminated.size (); p++) {
		         if (eliminated[p] < minimum_eliminated) {
               if (eliminated[p]<min_min){
                 min_min=eliminated[p];
                 minimum_eliminated=min_min;
                 p=eliminated.size();
               }
               else {
			              minimum_eliminated = eliminated[p];
                    if (a=0){
                      min_min=minimum_eliminated;
                      a++;
                    }
              }
		        }
		       }
		       helpfulness.push_back (minimum_eliminated);
           eliminated.clear ();
           numbers_fake_sol_2.clear();
	    }
	    int max_helpfulness = helpfulness[0];
	    int max_helpfulness_attempt = 0;
	    for (int i = 0; i < helpfulness.size (); i++) {
		      if (helpfulness[i] > max_helpfulness) {
		          max_helpfulness = helpfulness[i];
		          max_helpfulness_attempt = i;
		      }
	    }

	    attempt_string = mainlist[max_helpfulness_attempt];
    }
	 }
  }
  else{
    if (remaining_possibilities.size()==0) {
      main_list();
      for (int i = 0; i < length/2; i++) {
        attempt.push_back (0);
      }
       for(int i=attempt.size(); i<length; i++){
         attempt.push_back(1);
       }
    }
    if (remaining_possibilities.size () == 1) {
  	    attempt_string = remaining_possibilities[0];
  	 }

    if ((remaining_possibilities.size()!=1) && (remaining_possibilities.size()!=0)) {
    attempt_string=remaining_possibilities[0];
    }
  }
  if (attempt.size()==0){
	  for (int i = 0; i < attempt_string.size (); i++) {
	    int integer = 0;
	    std::string sub_attempt_string;
	    sub_attempt_string.clear ();
	    sub_attempt_string = attempt_string.substr (i, 1);
	    integer = atoi (sub_attempt_string.c_str ());
	    attempt.push_back (integer);
	  }
  }
 }



  void learn (std::vector < int >&attempt, int black_hits, int white_hits) {

    int fake_black_hits;
    int fake_white_hits;
    std::vector < int >small_remaining_possibilities;
    numbers_fake_sol.clear();


    for (int i = 0; i < remaining_possibilities.size (); i++) {
	     give_feedback_fake (remaining_possibilities[i], fake_black_hits,
			 fake_white_hits, attempt);
	     if ((black_hits == fake_black_hits)
	     && (white_hits == fake_white_hits)) {

	        small_remaining_possibilities.push_back (i);
	     }
    }

    if (mainlist.size () == remaining_possibilities.size ()) {
	  remaining_possibilities.clear ();
	   for (int i = 0; i < small_remaining_possibilities.size (); i++) {
	    remaining_possibilities.push_back (mainlist[small_remaining_possibilities[i]]);
	   }
    }
    else {
	     remaining_possibilities.clear ();
	     for (int i = 0; i < small_remaining_possibilities.size (); i++) {
	        remaining_possibilities.push_back (remaining_possibilities[small_remaining_possibilities[i]]);
	     }
    }
  }

  int length;
  int num;
  std::vector < std::string > mainlist;
  std::vector < std::string > remaining_possibilities;
  std::vector<int>numbers_fake_sol;
  std::vector<int>numbers_fake_sol_2;
  std::vector<int>poss_black;
  std::vector<int>poss_white;
  int min_min;
   int a=0;

  void main_list () {
    std::string remainders_string = "";
    std::vector < int >division;
    std::vector < int >flipped_remainders;
    std::vector < int >remainders;
    for (int i = 0; i < (std::pow (num, length) + 0.5) - 1; i++) {
	     if (i == 0) {
	        flipped_remainders.push_back (0);
	     }
	     int divider = i;
	     int remain = 0;
	     while (divider > 0) {
	        remain = divider % num;
	        divider = divider / num;
	        flipped_remainders.push_back (remain);

	    }
	    for (int i = flipped_remainders.size () - 1; i >= 0; i--) {
	    remainders.push_back (flipped_remainders[i]);
	    }
	 for (int i = 0; i < remainders.size (); i++) {
	    remainders_string +=std::to_string (remainders[i]);
   }
	 mainlist.push_back (remainders_string);
   remainders.clear ();
   flipped_remainders.clear ();
   remainders_string.clear ();

 }
   for (int i = 0; i < std::pow (num, length) + 0.5; i++) {
	    if (mainlist[i].size () < length) {
	       int c = length - mainlist[i].size ();
	       mainlist[i].insert (0, c, '0');
	    }
   }
   remaining_possibilities = mainlist;
 }

void give_feedback_fake (std::string fake_sol, int &black_hits,
		int &white_hits, std::vector < int >attempt)  {

    for (int i = 0; i < fake_sol.size (); i++)  {
	     fake_sol[i] -= '0';
    }

    black_hits = 0;
    white_hits = 0;
    std::vector < int >checker;
    int numbers_sequence= 0;
    int numbers_attempt = 0;
    int hits = 0;
    if (numbers_fake_sol.size()==0){
      for (int i=0; i<num; i++){
        numbers_attempt=0;
        for(int j=0; j<attempt.size(); j++){
          if (attempt[j]==i){
            numbers_attempt++;
          }
        }
        numbers_fake_sol.push_back(numbers_attempt);
      }
    }
    for (int i = 0; i < num; i++) {
	     for (int j = 0; j < length; j++) {
	        if (fake_sol[j] == i) {
		          numbers_sequence++;
	        }
	     }
	 if (numbers_sequence <= numbers_fake_sol[i]) {
	    checker.push_back (numbers_sequence);
	 }
   if (numbers_sequence > numbers_fake_sol[i]) {
	    checker.push_back (numbers_fake_sol[i]);
	 }
	numbers_sequence = 0;
 }

 for (int i = 0; i < checker.size (); i++) {
	hits = checker[i] + hits;
 }

 for (int i = 0; i < attempt.size (); i++) {
	if (attempt[i] == fake_sol[i]) {
	  black_hits++;
	}
 }

 white_hits = hits - black_hits;
 }
 void give_feedback_fake_2 (std::string fake_sol, int &black_hits,
   int &white_hits, std::string attempt)  {

   for (int i = 0; i < fake_sol.size (); i++)  {
      fake_sol[i] -= '0';
   }
   for (int i = 0; i < attempt.size (); i++)  {
      attempt[i] -= '0';
   }

   black_hits = 0;
   white_hits = 0;
   std::vector < int >checker;
   int numbers_sequence= 0;
   int numbers_attempt = 0;
   int hits = 0;
   if (numbers_fake_sol_2.size()==0){
     for (int i=0; i<num; i++){
       numbers_attempt=0;
       for(int j=0; j<length; j++){
         if (attempt[j]==i){
           numbers_attempt++;
         }
       }
       numbers_fake_sol_2.push_back(numbers_attempt);
     }
   }
   for (int i = 0; i < num; i++) {
      for (int j = 0; j < length; j++) {
         if (fake_sol[j] == i) {
             numbers_sequence++;
         }
      }
  if (numbers_sequence <= numbers_fake_sol_2[i]) {
     checker.push_back (numbers_sequence);
  }
  if (numbers_sequence > numbers_fake_sol_2[i]) {
     checker.push_back (numbers_fake_sol_2[i]);
  }
 numbers_sequence = 0;
  }

   for (int i = 0; i < checker.size (); i++) {
     hits = checker[i] + hits;
   }

  for (int i = 0; i < attempt.size (); i++) {
    if (attempt[i] == fake_sol[i]) {
      black_hits++;
    }
   }

   white_hits = hits - black_hits;
 }
};

int main () {

  set_random_seed ();

  int length, num;
  std::
    cout << "enter length of sequence and number of possible values:" << std::
    endl;
  std::cin >> length >> num;
  int start_s=clock();

  mm_solver solver;
  solver.init (length, num);

  mm_code_maker maker;
  maker.init (length, num);

  maker.generate_sequence ();

  int black_hits = 0, white_hits = 0;
  /// just some number to limit the number of attempts
  int attempts_limit = 5000;
  int attempts = 0;
  while ((black_hits < length) && (attempts < attempts_limit))
    {
      black_hits = 0, white_hits = 0;
      std::vector < int >attempt;
      solver.create_attempt (attempt);
      /// the solver creates an attempt
      maker.give_feedback (attempt, black_hits, white_hits);
      /// we ask for feedback for the attempt

      /// we print the attempt
      std::cout << "attempt: " << std::endl;
      for (int i = 0; i < attempt.size (); i++)
	{
	  std::cout << attempt[i] << " ";
	}
      std::cout << std::endl;
      /// we print the feedback
      std::
	cout << "black pegs: " << black_hits << " " << " white pegs: " <<
	white_hits << std::endl;
      /// we give the feedback to the solver so that it can learn

      //  solver.gf_once_sequence(attempt);
      solver.learn (attempt, black_hits, white_hits);
      attempts++;
    }
    int stop_s=clock();
 std::cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;


  if (black_hits == length)
    {
      std::
	cout << "the solver has found the sequence in " << attempts <<
	" attempts" << std::endl;
    }
  else
    {
      std::
	cout << "after " << attempts << " attempts still no solution" << std::
	endl;
    }
  std::cout << "the sequence generated by the code maker was:" << std::endl;
  for (int i = 0; i < maker.sequence.size (); i++)
    {
      std::cout << maker.sequence[i] << " ";
    }
  std::cout << std::endl;
  return 0;
}

void set_random_seed () {
  std::srand (std::chrono::system_clock::now().time_since_epoch().count());
}

int randn (int n) {
  return std::rand () % n;
}
