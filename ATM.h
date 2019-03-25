#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char status[7];
	char* operation;
	char card_number[16];
	char sum;
}Date_Istoric;

typedef struct istoric
{
	Date_Istoric info3;
	struct istoric *urm3;
}History, *THistory, **AHistory;

typedef struct
{
	char month[2];
	char year[2];
}Date;

typedef struct date_card
{
	char card_number[16];
	char pin[4];
	Date expiry_date;
	int CVV;
	int balance;
	char status[7];
	THistory history;
}Date_Card;

typedef struct card
{
	Date_Card info2;
	struct card *urm2;
}Card, *TCard, **ACard;

typedef struct carduri
{
	TCard info;
	struct carduri *urm;
}LC, *TLC, **ALC;

THistory AlocareHistory(Date_Istoric info3);
TCard AlocareCard(Date_Card info2);
TLC AlocareLC();

void DistrugeCard(ALC aL);

void initializareDate_Istoric(Date_Istoric *date);
void initializareDate_Card(Date_Card *date);

void InserareCard(ALC listaCarduri, Date_Card Card_aux, int poz);
int InserareLC(TLC *listaCarduri);

int Afisare(TLC, int, FILE*, int[] , int);
void AfisareCard(TCard card, int nr_max_carduri, FILE *out);

int CalcularePozitie(char card_number[16], int nr_max_carduri);

TCard CautareElement(TLC listaCarduri, char card_number[16], int nr_max_carduri);
