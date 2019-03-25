#include "ATM.h"

THistory AlocareHistory(Date_Istoric info3)
{
	THistory aux;

	aux = (THistory)malloc(sizeof(History));
	if(aux)
	{
		aux->info3 = info3;
		aux->urm3 = NULL;
	}

	return aux;
}

void AfisareCard(TCard card, int nr_max_carduri, FILE *out)
{
	int j, poz;
		if(card != NULL)
		{
			fprintf(out, "(card_number: ");
			for(j = 0; j < 16; j++)
				if(card->info2.card_number[j] == 0x0c || card->info2.card_number[j] == 0x01)
					break;
				else
					fprintf(out, "%c", card->info2.card_number[j]);
			fprintf(out, ", PIN: ");
			for(j = 0; j < 4; j++)
				if(card->info2.pin[j] == 0x0c || card->info2.pin[j] == 0x01)
					break;
				else
					fprintf(out, "%c", card->info2.pin[j]);
      fprintf(out, ", expiry date: ");
            for(j = 0; j < 2; j++)
				if(card->info2.expiry_date.month[j] == 0x0c || card->info2.expiry_date.month[j] == 0x01)
					break;
				else
					fprintf(out, "%c", card->info2.expiry_date.month[j]);
      fprintf(out, "/");

            for(j = 0; j < 2; j++)
				if(card->info2.expiry_date.year[j] == 0x0c || card->info2.expiry_date.year[j] == 0x01)
					break;
				else
					fprintf(out, "%c", card->info2.expiry_date.year[j]);
			fprintf(out, ", CVV: %d, balance: %d, status: %s, history: [",
			card->info2.CVV, card->info2.balance, card->info2.status);

				//THistory istoric = card->info2.history;

			fprintf(out, "])\n");
		}
	printf("am terminat de afisat\n");
}

int CalcularePozitie(char card_number[16], int nr_max_carduri)
{
	int suma_cifre = 0, i, card_poz = 0;
	for(i = 0; i < 16; i++)
		suma_cifre += card_number[i] - '0';
	card_poz = suma_cifre % nr_max_carduri;
	printf("am calculat pozitia\n");
	return card_poz;
}

TCard CautareElement(TLC listaCarduri, char card_number[16], int nr_max_carduri)
{
	int i, poz;
	poz = CalcularePozitie(card_number, nr_max_carduri);
	printf("pozitie element: %d\n", poz);

	TLC p = listaCarduri;

	for(i = 0; i < poz && p; i++, p = p->urm);
		printf("i: %d\n", i);
	TCard card = p->info;

	if(card == NULL)
	{
		printf("card gol\n");
		return NULL;
	}
	else
		{
			for(; card != NULL; card = card->urm2)
			{
				int ok = 1;
				for(i = 0; i < 16; i++)
					if(card->info2.card_number[i] != card_number[i])
						ok = 0;
				if(ok == 1)
				{
					printf("am gasit card\n");
					return card;
				}
			}
		}
	if(card == NULL)
	{
		printf("nu am gasit element\n");
		return NULL;
	}
}
void InserareCard(ALC listaCarduri, Date_Card Card_aux, int poz)
{
	int i;
	TLC p = *listaCarduri;

	printf("poz: %d\n", poz);
	for(i = 0; p && i < poz; i++, p = p->urm);
	//s-a parcurs lista de carduri listaCarduri
	TCard aux; // a.k.a TLSC
	aux = AlocareCard(Card_aux);
	if(!aux)
	{
		printf("Nu s-a alocat\n");
	}

	if(p->info != NULL)
	{
		aux->urm2 = p->info;
		p->info = aux;
	}
	else if(p->info == NULL)
	{
		p->info = aux;
	}
	printf("am inserat\n");
}


TCard AlocareCard(Date_Card info)
{
	TCard aux;
	aux = (TCard)malloc(sizeof(Card));
	if(aux)
	{
		strcpy(aux->info2.card_number, info.card_number);
		strcpy(aux->info2.pin, info.pin);
		aux->info2.CVV = info.CVV;
		strcpy(aux->info2.expiry_date.month, info.expiry_date.month);
		strcpy(aux->info2.expiry_date.year , info.expiry_date.year);
		aux->info2.balance = 0;
		strcpy(aux->info2.status, "NEW");
		aux->info2.history = NULL;
		aux->urm2 = NULL;
	}
	else if(aux == NULL)
	{
		printf("Nu am alocat card");
	}
	return aux;
}

TLC AlocareLC()
{
	TLC aux;
	aux = (TLC)malloc(sizeof(LC));
	if(aux)
	{
		aux->info = NULL;
		aux->urm = NULL;
	}

	return aux;
}

void initializareDate_Istoric(Date_Istoric *date)
{
	strcpy((*date).card_number, "");
	(*date).operation = NULL;
}

void initializareDate_Card(Date_Card *date)
{
	strcpy((*date).card_number, "");
	strcpy((*date).pin, "");
	strcpy((*date).expiry_date.month, "00");
	strcpy((*date).expiry_date.year, "00");
	(*date).CVV = 0;
	(*date).balance = 0;
	strcpy((*date).status, "NEW");
	(*date).history = NULL;

}

/*void DistrugeCard(ALC aL)
{
  TCard aux;
  while(*aL)
  {
    aux = *aL;
    *aL = aux->urm2;
    free(aux);
  }
}*/


int InserareLC(TLC *listaCarduri)
{
	TLC aux;
	aux = AlocareLC();
	if(!aux)
		return 0;
	if(*listaCarduri == NULL)
		*listaCarduri = aux;
	else
	{
		aux->urm = *(listaCarduri);
		*(listaCarduri) = aux;
	}

	return 1;
}

int Afisare(TLC listaCarduri, int nr_max_carduri, FILE *out, int localizare_elemente[nr_max_carduri], int nr_curent_elemente)
{
	int i, j, k = 0;

	printf("nr curent de carduri: %d\n", nr_curent_elemente);
	if(nr_curent_elemente != 0)
	{

		for(i = 0; i < nr_max_carduri; i++)
			if(localizare_elemente[i] != 0)
			{
			  printf("yyyyyyyy\n");
				k = i;
			}
	}
	else
	{
	    printf("nu am ce sa afisez\n");
		return 0;
	}

    printf("am gasit element %d\n", k);
  printf("xxxxxxxx\n");
	for(i = 0; i <= k; i++, listaCarduri = listaCarduri->urm)
	{
	  printf("am intrat in for\n");
		if(listaCarduri != NULL)
		{
		  printf("for''\n");

			TCard card =  listaCarduri->info; // lista carduri dintr-un LSC
			if(card == NULL)
        printf("ttt\n");
			int poz = CalcularePozitie(card->info2.card_number, nr_max_carduri);
			printf("ccc\n");
			for(; card != NULL; card = card->urm2)
			{
			  printf("for 2\n");
				fprintf(out, "poz%d:[", poz);
				fprintf(out, "(card_number: ");
				for(j = 0; j < 16; j++)
				{
					if(card->info2.card_number[j] == 0x0c || card->info2.card_number[j] == 0x01)
						break;
					else
						fprintf(out, "%c", card->info2.card_number[j]);
				}
				fprintf(out, ", PIN: ");
				for(j = 0; j < 4; j++)
				{
					if(card->info2.pin[j] == 0x0c || card->info2.pin[j] == 0x01)
						break;
					else
						fprintf(out, "%c", card->info2.pin[j]);

        fprintf(out, ", expiry date: ");

        for(j = 0; j < 2; j++)
          if(card->info2.expiry_date.month[j] == 0x0c || card->info2.expiry_date.month[j] == 0x01)
            break;
          else
            fprintf(out, "%c", card->info2.expiry_date.month[j]);
        fprintf(out, "/");

        for(j = 0; j < 2; j++)
          if(card->info2.expiry_date.year[j] == 0x0c || card->info2.expiry_date.year[j] == 0x01)
            break;
          else
            fprintf(out, "%c", card->info2.expiry_date.year[j]);
        fprintf(out, ", CVV: %d, balance: %d, status: %s, history: [",
        card->info2.CVV, card->info2.balance, card->info2.status);

				//THistory istoric = card->info2.history;

				fprintf(out, "])\n");
				fprintf(out, "]");
                }

		}

	}
		printf("am terminat de afisat\n");

	}
	printf("am terminat de afisat\n");
	return 1;
}
