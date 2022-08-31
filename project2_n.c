#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define TOTAL_CARDS 52


void quit();
void play_game();
void place_bet();
void initialize_deck();
void shuffle_deck();
void turns();
int hit(int *number);
char *card_face(int n);
int card_num(int n);
char *card_symbol(int n);
void ace(int n1, int n2, int *i1);

int deck[52];
int new_deck[52];

int main()
{
    printf("\t\t\tWelcome to blackjack game\n");
    char * input = (char *)malloc(10 * sizeof(char));
    printf("\vEnter an action\n1.Play to play the game\n2.Help for instructions\n3.Quit to exit: ");
    scanf("%s", input);
    while(strcmp(input, "quit") != 0){
        while(strcmp(input, "play") != 0){
            if(strcmp(input, "help") == 0){
                printf("Type play to start game:\n");
            }else if(strcmp(input, "quit") == 0){
                quit();
            }else{
                printf("Invalid input, enter 'play' to start the game\n");
                scanf("%s", input);
            }
        }
        play_game();
    }
}

void quit(){
    char *ask;
    printf("Are you sure if you want to quit?\n(yes/no)");
    scanf("%c", ask);
    if(strcmp(ask, "yes") == 0){
        exit(0);
    }else{
        printf("Cancelled quit");
        play_game();
    }
}

void play_game(){
    printf("\t\t\tLets start the game\n");
    while(1){
        place_bet();
        initialize_deck();
        shuffle_deck();
        turns();
    }
}

void turns(){
    int crd = 0;

    int a1 = hit(&crd);
    char *card_sym1 = card_symbol(a1);
    char *card_face1 = card_face(a1);
    int card_num1 = card_num(a1);

    printf("You received a %s of %s worth %d\n", card_face1, card_sym1, card_num1);

    int a2 = hit(&crd);
    char *card_sym2 = card_symbol(a2);
    char *card_face2 = card_face(a2);
    int card_num2 = card_num(a2);

    printf("You received a %s of %s worth %d\n", card_face2, card_sym2, card_num2);

    int a3 = hit(&crd);
    char *card_sym3 = card_symbol(a3);
    char *card_face3 = card_face(a3);
    int card_num3 = card_num(a3);

    printf("Dealer has received a %s of %s worth %d\n", card_face3, card_sym3, card_num3);

    int a4 = hit(&crd);
    char *card_sym4 = card_symbol(a4);
    char *card_face4 = card_face(a4);
    int card_num4 = card_num(a4);

    int user_total_pts = card_num1 + card_num2;
    int dealer_total_pts = card_num3;

    ace(card_num1, card_num2, &user_total_pts);

    printf("Your total is %d points and dealers total is %d\n", user_total_pts, dealer_total_pts);
    if(user_total_pts == 21){
        printf("CONGRATS!! You won\n");
    }else{
        char ask[10];
        scanf("%s", ask);
        while(strcmp(ask, "stand") != 0){
            if(strcmp(ask, "hit") == 0){
                int d = hit(&crd);
                char *new_sym = card_symbol(d);
                char *new_fac = card_face(d);
                int new_number = card_num(d);
                user_total_pts += new_number;
                printf("You got %s of %s worth %d\n", new_fac, new_sym, new_number);
                if(user_total_pts < 21){
                    if(new_number == 1){
                        if(user_total_pts+10 == 21){
                            user_total_pts += 10;
                            printf("YOU WON THE GAME\n");
                            break;
                        }
                        else{
                            int ask;
                            printf("You recieved a ACE, choose to make it count as 1 or 11\n");
                            scanf("%d", &ask);
                            if(ask == 11){
                                user_total_pts += 10;
                            }
                        }

                    }
                }else if(user_total_pts == 21){
                    printf("You WON THE GAME!!\n");
                    break;
                }else{
                    printf("You Lost the game with points %d.\n", user_total_pts);
                    break;
                }
            }else if (strcmp(ask, "help") == 0){
                printf("Enter 'hit' to get another card or 'stand' to hold\n");

            }else if (strcmp(ask, "quit") == 0){
                quit();
                printf("Enter 'hit' to get another card or 'stand' to hold\n");
            }else{
                printf("Wrong input, enter again\n");
                printf("Yout total is %d\n", user_total_pts);
                scanf("%s", ask);
            }
        }
    }

    if(user_total_pts < 21){
        printf("The dealer flips a %s of %s of worth %d\n", card_face4, card_sym4, card_num4);
        dealer_total_pts += card_num4;
        if(card_num4 == 1){
            if(dealer_total_pts + 11 < 21){
                dealer_total_pts += 10;
            }
        }

        if (dealer_total_pts >= 16){
            printf("The dealer stands with %d\n", dealer_total_pts);
        }

        while(dealer_total_pts < 16){
            int d = hit(&crd);
            char *new_sym = card_symbol(d);
            char *new_fac = card_face(d);
            int new_number = card_num(d);
            dealer_total_pts += new_number;
            printf("Dealer got %s of %s worth %d\n", new_fac, new_sym, new_number);
            if(dealer_total_pts < 16){
                if(new_number == 1){
                    if(dealer_total_pts + 11 < 21){
                    dealer_total_pts += 10;
                    }
                }
            }else if(dealer_total_pts == 21){
                printf("oops, Dealer got 21\n");
                break;
            }else if(dealer_total_pts > 21){
                printf("dealer lost woth points %d\n", dealer_total_pts);
                break;
            }else{
                printf("dealer stands with %d.\n", dealer_total_pts);
                break;
            }
            printf("Dealer's new total is %d\n", dealer_total_pts);  
        }
        if(dealer_total_pts < user_total_pts){
            printf("You beat dealer!!\n");
        }else if(dealer_total_pts == user_total_pts){
            printf("its a tie\n");
        }else if(dealer_total_pts > user_total_pts && dealer_total_pts <= 21){
            printf("Dealer won\n");
        }
    }
}

void ace(int n1, int n2, int *i1){
    if(n1 == 1 || n2 == 1){
        int ask;
        if(n1 == 1 && n2 == 1){
            n1 = 11;
            n2 = 1;
            *i1 = 12;
            printf("As you recieved 2 'A' one is set to worth 11 and another to 1.\n" );   
        }else if(n1 == 1 && n2 == 1){
            if(n1+n2+10 == 21){
                *i1 = 21;
            }else{
                printf("You have got one ace. choose if you want to make it count 1 or 11.\n");
                scanf("%d", &ask);
                if(ask == 11){
                    *i1 += 10;
                }
            }
        }
    }
}


int card_num(int n){
    int num;
    if(((n % 13)+1)<10){
        num = (n % 13)+1;
    }else{
        num = 10;
    }
    return num;
}

char *card_face(int n){
    n = n % 13 + 1;
    char *face;
    switch(n){
        case 1:
            face = "A";
            break;
        case 2:
            face = "TWO";
            break;
        case 3:
            face = "THREE";
            break;
        case 4:
            face = "FOUR";
            break;
        case 5:
            face = "FIVE";
            break;
        case 6:
            face = "SIX";
            break;
        case 7:
            face = "SEVEN";
            break;
        case 8:
            face = "EIGHT";
            break;
        case 9:
            face = "NINE";
            break;
        case 10:
            face = "TEN";
            break;
        case 11:
            face = "J";
            break;
        case 12:
            face = "Q";
            break;
        case 13:
            face = "K";
            break;
    }
    return face;
}

char *card_symbol(int n){
    n = n % 4;
    switch(n){
        case 1:
            return "Hearts";
            break;
        case 2:
            return "Clubs";
            break;
        case 3:
            return "Diamonds";
            break;
        case 4:
            return "Spades";
            break;
    }
    return 0;
}

void initialize_deck(){
    int i = 0;
    for(i = 0; i < 52; i++){
        deck[i] = i+1;
    } 
}

void shuffle_deck(){
    srand(time(NULL));
    int i;
    for (int i = 0; i < 52; i++){
        new_deck[i] = deck[i];
    }
    i = 0;
    for (i = TOTAL_CARDS - 1; i > 0; i--){
        int j = rand()%(i+1);
        int k = new_deck[i];
        new_deck[i] = new_deck[j];
        new_deck[j] = k;
    }
}

void place_bet(){
    char ask[10];
    int num;
    printf("Enter bet you want to play or quit to exit or help to get instructions: ");
    scanf("%s", ask);
    while(strcmp(ask, "bet") != 0){
        if(strcmp(ask, "help") == 0){
            printf("Enter bet to bet on the cards.\n");
        }else if(strcmp(ask, "quit") == 0){
            quit();
            // place_bet();
        }else{
            printf("Wrong input, enter again.\n");
            // scanf("%s",ask);
        }
    }
    // turns();
}

int hit(int *val){
    int a = new_deck[*val];
    *val += 1;
    return a;
}