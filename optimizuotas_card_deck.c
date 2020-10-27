/*
Week 2 honour assignment: using struct

By Danielius Lingis
2020-10-27
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {clubs,diamonds,hearts,spades} cdhs;
struct card{ int pips; cdhs suit;};
typedef struct card card;

// calculation of number of pairs
int no_of_pairs(card hand[7])
{
	int pair = 0;
	int i, j;
	
	for (i=0;i<7;i++)
	{
		for(j=0;j<7;j++)
		{
			// cycles through two sets of cards
			// if card values are equal but the cards are not the same
			if(hand[i].pips == hand[j].pips && i != j)
				{
				pair++;	
				}
		}
	}
	//division by two due to double loop
	if(pair/2 >= 2) {return 3;}	// two pairs or more
	else if(pair/2 >=1 && pair/2 <2) {return 2;}	// one pair or more (but less than 2 pairs)
	else if(pair == 0) {return 1;}	// no pairs
	else return 0;
	

}

// calculates three of a kind, four of a kind or full house
int is_tok_fok_or_fullh(card hand[7])
{
	int i,j,k,l,m;
	int a,b,c,d,e;
	
	int three_cntr =0;
	int four_cntr = 0;
	int value_of_three = 0;
	int full_h_cntr =0;
	
	for (i=0;i<7;i++)
	{
		for(j=0;j<7;j++)
		{
			for(k=0;k<7;k++)
			{
				for(l=0;l<7;l++)
				{
				
					for(m=0;m<7;m++)
					{
				
						// assigned to new variables for less occupied space on screen
						a = hand[i].pips;
						b = hand[j].pips;
						c = hand[k].pips;
						d = hand[l].pips;
						e = hand[m].pips;
						// equal values for four of a kind
						int statement_1 = (a == b && a == c && a == d && b == c && b == d && c == d);
						// different indices
						int statement_2 = (i!=j && i!=k && i!=l && i!=m && j!=k && j!=l && j!=m && k!=l && k!=m && l!=m);
						// four of a kind
						if(statement_1 == 1 && statement_2 == 1 )
						{	
							four_cntr++;
						} 
						// three of a kind
						if(a == b && a == c && b == c && i != j && i!=k && j != k)
						{	
							value_of_three = a; // if there is a three of a kind, the value is stored
							three_cntr++;
						}
						if(value_of_three != 0)	// if three of a kind exists, check for full house
							{
							if(d == e && l!=m) 	// check for pair
							{
							// checks that the value of pair isn't equal to the one of three of a kind
								if( d!=value_of_three && e!=value_of_three)
								{
								full_h_cntr++;
								}
							
							}
						}
					}
				}
			}	
		}	
	}
	if(four_cntr > 0) { return 2;}	// four of a kind
	else if ( full_h_cntr > 0)	{return 3;}	// full house
	else if (three_cntr > 0) { return 1;}	// three of a kind
	else return 0;				// none
}

// calculates whether the hand is straight, flush or straight flush
int is_straight_or_flush(card hand[7])
{
	int i,j,k,l,m;
	
	int x,y,z,w,t;
	int a,b,c,d,e;
	
	int str_cntr = 0;
	int flu_cntr = 0;
	int str_flu_cntr = 0;

	for (i=0;i<7;i++)
	{
		for(j=0;j<7;j++)
		{
			for(k=0;k<7;k++)
			{
				for(l=0;l<7;l++)
				{
					for(m=0;m<7;m++)
					{
					a = hand[i].pips+4;
					b = hand[j].pips+3;
					c = hand[k].pips+2;
					d = hand[l].pips+1;
					e = hand[m].pips;
					
					
					x = hand[i].suit;
					y = hand[j].suit;
					z = hand[k].suit;
					w = hand[l].suit;
					t = hand[m].suit;
					
					
					// straight condition
					int statement_1_a = (a == b && a == c && a == d && b == c && b == d && b == e && c == d && a == e  && c == e && d == e);
					// flush condition
					int statement_1_b = (x == y && x == z && x == w && x == t && y == z && y == w && y == t && z == w && z == t && w == t);
					// ace-high straight condition
					int statement_1_c = (hand[i].pips == 1 && hand[j].pips == 10 && hand[k].pips == 11 && hand[l].pips == 12 && hand[m].pips == 13);
					// condition for different indices
					int statement_2 = (i!=j && i!=k && i!=l && j!=k && j!=l && k!=l && i != m && j!=m && k!=m && l!=m);
					
					// ace high straight
					if( statement_1_c == 1 && statement_2 == 1)
						{
						str_cntr++;
						}
					// straight
					if (statement_1_a == 1 && statement_2 == 1)
						{
						str_cntr++;
						}
					// flush
					if (statement_1_b == 1 && statement_2 == 1)
						{
						flu_cntr++;
						}
					// straight flush -> both ace high and other straights
					if((statement_2 == 1 && statement_1_b == 1 && statement_1_a == 1) || (statement_2 == 1 && statement_1_b == 1 && statement_1_c == 1 ))
						{
							str_flu_cntr++;
						}					
					}
				}		
			}	
		}	
	}
	
	if(str_flu_cntr > 0) { return 3;}	// straight flush
	else if (flu_cntr > 0) { return 2;}	// flush
	else if (str_cntr > 0) { return 1;}	//straight
	else return 0;

}


//assigns card values
card assign_values(int pips, cdhs suit)
{
	card c;
	
	c.pips = pips;
	c.suit = suit;
	return c;
}
// swaps two cards
void swap(card *p, card *q)
{
	card tmp;
	
	tmp = *p;
	*p = *q;
	*q = tmp;

}
// shuffles the deck
void shuffle(card deck[])
{
	int i, j;
	for(i=0; i<52; ++i)
		{
			j = rand() % 52;
			swap(&deck[i],&deck[j]);
		}

}
void deal_cards(card deck[], card hand[7])
{
	int card_cnt = 0;
	int i;
	// draws 7 cards
	for (i = 0; i<7;++i)
		{
			hand[i]=deck[card_cnt++];
		}

}
// prints card values
void prn_card_values(card *c_ptr)
{
	int 	pips = c_ptr->pips;
	cdhs 	suit = c_ptr->suit;
	char *suit_name;
	
	if(suit == clubs)
		suit_name = "clubs";
	else if (suit == diamonds)
		suit_name = "diamonds";
	else if (suit == hearts)
		suit_name = "hearts";
	else if (suit == spades)
		suit_name = "spades";
	printf("card: %2d of %s\n",pips, suit_name);
}
void calc_poker_prob(card deck[52])
{
	// initialise poker combination counter
	int no_pair_cntr 		= 0;
	int one_pair_cntr 		= 0;
	int three_of_a_kind_cntr 	= 0;
	int two_pairs_cntr		= 0;
	int four_of_a_kind_cntr	= 0;
	int full_house_cntr		= 0;
	int straight_cntr		= 0;
	int flush_cntr			= 0;
	int straight_flush_cntr 	= 0;
	
	card hand[7];

	// number of deals to do
	// uses double instead of int for conversion
	double DEALS;
 	printf("Enter number of iterations:");
 	scanf("%lf", &DEALS);
 	//printf("%lf", DEALS);
	//DEALS = 100;
		
for(int i = 0; i<DEALS;i++)
	{
	// random number seed and more than one shuffle to get the more randomized deck
	srand(time(0));
	shuffle(deck);
	shuffle(deck);
	shuffle(deck);
	shuffle(deck);
	shuffle(deck);
	shuffle(deck);
	shuffle(deck);
	deal_cards(deck,hand);

	// initialize card hand variables
	int pair 		=0;
	int str_flu		=0;
	int tok_fok_fullh	=0;
	
	
	
	pair		= no_of_pairs(hand);		// check and returns how many pairs does the hand contain
	str_flu	= is_straight_or_flush(hand);	// checks for straight, flush or straight flush 
	tok_fok_fullh	= is_tok_fok_or_fullh(hand);	// check for three of a kind, four of a kind or full house
	

	// sets the hand ranking from highest to lowest in values
	int rank = 0;

	if(str_flu == 3)
		{ rank = 8;}
	else if (tok_fok_fullh == 2) 
		{ rank = 7;}
	else if (tok_fok_fullh == 3)
		{ rank = 6;}
	else if (str_flu == 2)
		{ rank = 5;}
	else if (str_flu == 1)
		{ rank = 4;}
	else if (tok_fok_fullh == 1)
		{ rank = 3;}
	else if (pair == 3)
		{ rank = 2;}
	else if (pair == 2)
		{ rank = 1;}
	else if (pair == 1)
		{ rank = 0;}
		
	// based on rank, chooses what the hand corresponds to		
	switch(rank)	
		{
			case 8: straight_flush_cntr++; break;
			case 7: four_of_a_kind_cntr++; break;
			case 6: full_house_cntr++;	break;
			case 5: flush_cntr++;		break;
			case 4: straight_cntr++;	break;
			case 3: three_of_a_kind_cntr++;break;
			case 2: two_pairs_cntr++;	break;
			case 1: one_pair_cntr++;	break;
			case 0: no_pair_cntr++;	break;
		}
		
	

	}
	
	// calculates experimental probabilities
	double no_pair_prob 		= no_pair_cntr/DEALS;
	double one_pair_prob 		= one_pair_cntr/DEALS;
	double two_pair_prob 		= two_pairs_cntr/DEALS;
	double three_prob		= three_of_a_kind_cntr/DEALS;
	double four_prob		= four_of_a_kind_cntr/DEALS;
	double full_h_prob		= full_house_cntr/DEALS;
	double straight_prob 		= straight_cntr/DEALS;
	double flush_prob		= flush_cntr/DEALS;
	double straight_flush_prob 	= straight_flush_cntr/DEALS;
	
	double prob_sum_exp		= no_pair_prob+one_pair_prob+two_pair_prob+three_prob+four_prob+full_h_prob+straight_prob+flush_prob+straight_flush_prob;
	
	
	// theoretical probabilities
	double prob_high_card 		= 0.17411920;
	double prob_one_pair		= 0.43822546;
	double prob_two_pair		= 0.23495536;
	double prob_three_kind		= 0.04829870;
	double prob_four_kind		= 0.00168067;
	double prob_full_h		= 0.02596102;
	double prob_flush		= 0.03025494;
	double prob_straight		= 0.04619382;
	double prob_str_flu		= 0.00027851+0.00003232;
	
	double prob_sum_theo		= prob_high_card+prob_one_pair+prob_two_pair+prob_three_kind+prob_four_kind+prob_full_h+prob_flush+prob_straight+prob_str_flu;
	
	printf(" Prob. of poker combinations      VS    theory\n");
	printf(" No pairs ---------- %.8f ------- %.4f\n",no_pair_prob,prob_high_card);
	printf(" One pair ---------- %.8f ------- %.4f\n",one_pair_prob,prob_one_pair);
	printf(" Two pairs --------- %.8f ------- %.4f\n",two_pair_prob,prob_two_pair);
	printf(" Three of a kind --- %.8f ------- %.4f\n",three_prob,prob_three_kind);
	printf(" Four of a kind ---- %.8f ------- %.4f\n",four_prob,prob_four_kind); 
	printf(" Full house -------- %.8f ------- %.4f\n",full_h_prob,prob_full_h);
	printf(" Flush ------------- %.8f ------- %.4f\n",flush_prob,prob_flush);
	printf(" Straight ---------- %.8f ------- %.4f\n",straight_prob,prob_straight);
	printf(" Straight flush ---- %.8f ------- %.4f\n",straight_flush_prob,prob_str_flu);
	printf(" Total ------------- %.8f ------- %.4f\n",prob_sum_exp,prob_sum_theo);
}


int main()
{
	cdhs suit;
	int i, pips;
	card deck[52];
	
	for (i=0;i<52;++i) 
		{
			pips = i%13+1;
			if (i<13)
				suit = clubs;
			else if (i<26)
				suit = diamonds;
			else if (i<39)
				suit = hearts;
			else 
				suit = spades;
				
			deck[i]=assign_values(pips,suit);
		}
	calc_poker_prob(deck);

		

	return 0;
}
