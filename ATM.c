#include "ATM.h"

TCard CitireDate_Card(FILE *in)
{
	Date_Card date;
	initializareDate_Card(&date); // se initializeaza structura de date
	TCard Card;
	int i;
	fgetc(in);
	for(i = 0; i < 16; i++)
	{
		fscanf(in, "%c", &date.card_number[i]);
	}
	//fscanf(in, "%s", &date.card_number);
	date.card_number[16] = '\0';
	printf("s-a citit numarul cardului: %s\n", date.card_number);
	fgetc(in);
	for(i = 0; i < 4; i++)
	{
		fscanf(in, "%c", &date.pin[i]);
	}
	date.pin[4] = '\0';
	//fscanf(in, "%s", &date.pin);
	fgetc(in);
	for(i = 0; i < 2; i++)
    {
        fscanf(in, "%c", &date.expiry_date.month[i]);
    }
    date.expiry_date.month[2] = '\0';
    fgetc(in);
  for(i = 0; i < 2; i++)
    {
        fscanf(in, "%c", &date.expiry_date.year[i]);
    }
    date.expiry_date.year[2] = '\0';
  /*for(i = 0; i < 2; i++)
    printf("%c", date.expiry_date.month[i]);
  printf("/");
  for(i = 0; i < 2; i++)
    printf("%c", date.expiry_date.year[i]);
  printf("\n");*/
  fgetc(in);
	fscanf(in, "%d", &date.CVV);

	Card = AlocareCard(date);
	if(!Card)
		return Card; // alocarea a esuat
    printf("am citit cardul\n");
	return Card;
}

int main()
{
	FILE *in = fopen("input.in", "r");

	if(in == NULL)
	{
		printf("Nu s-a deschis fisierul input\n");
		return -2;
	}

	FILE *out = fopen("output.out", "w");

	if(out == NULL)
	{
		printf("Nu s-a deschis fisierul output\n");
		return -2;
	}

	int numar_max_carduri;
	int i; // contor
	fscanf(in, "%d", &numar_max_carduri); //citeste numarul maxim de carduri
	TLC listaCarduri;
	int localizare_elemente[numar_max_carduri];
	int nr_curent_carduri = 0;

	for(i = 0; i < numar_max_carduri; i++)
		localizare_elemente[i] = 0;

	for(i = 0; i < numar_max_carduri; i++)
		InserareLC(&listaCarduri);

	do
	{
		char comanda[20];
		fscanf(in, "%s", comanda);
		if(strcmp(comanda, "add_card") == 0)
		{
				TCard Card_aux;
				printf("am intrat aici\n");
				Card_aux = CitireDate_Card(in); //citirea datelor cardului de la tastatura
				int poz = CalcularePozitie(Card_aux->info2.card_number, numar_max_carduri);
				InserareCard(&listaCarduri, Card_aux->info2, poz);
				nr_curent_carduri++;

		}
		else if(strcmp(comanda, "show") == 0)
		{
			char sfarsit_linie;
			sfarsit_linie = fgetc(in);
			printf("sfarsit_linie: %c", sfarsit_linie);
			if(sfarsit_linie == '\n' || sfarsit_linie == '\0' || sfarsit_linie == EOF)
			{
				printf("nu am parametrii\n");
				Afisare(listaCarduri, numar_max_carduri, out, localizare_elemente, nr_curent_carduri);
			}
			else
			{
				printf("am parametrii\n");
				int i;
				char card_number[16];
				for(i = 0; i < 16; i++)
					fscanf(in, "%c", &card_number[i]);
                card_number[16] = '\0';
				printf("card_number: ");
				for(i = 0; i < 16; i++)
					printf("%c", card_number[i]);
				printf("\n");
				TCard card = CautareElement(listaCarduri, card_number, numar_max_carduri);

				if(card == NULL)
					printf("blabla\n");
				else if(card != NULL)
				{
					AfisareCard(card, numar_max_carduri, out);
				}
			}
		}

	}while(fgetc(in) != EOF);

	/*
	for(i = 0; i < numar_max_carduri; i++, listaCarduri = listaCarduri->urm)
	{
		DistrugeCard(&listaCarduri);

	}*/
	free(listaCarduri);
	fclose(in);
	fclose(out);
	return 0;
}
