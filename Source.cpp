#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//32c

typedef struct
{
	int liczba;
}DANE;
struct Element
{
	DANE dane;
	struct Element *nast;
};
typedef struct Element ELEMENT;
typedef ELEMENT *ADRES;

void wypiszListe(ADRES lista,int k)
{
	int a = 0;
	while (lista != NULL)
	{
		printf("%d ", lista->dane.liczba);
		lista = lista->nast;
		a++;
		if (a%k == 0)
			printf("\n");
	}
	printf("\n");
}

void dodajDoListyNaKoncu(ADRES *lista, int liczba)
{
	ADRES wsk, ost;
	wsk = (ADRES)malloc(sizeof(ELEMENT));
	wsk->dane.liczba = liczba;
	wsk->nast = NULL;
	if (*lista == NULL)//gdy nie ma listy
		*lista = wsk;
	else {
		ost = *lista;
		while (ost->nast != NULL)
			ost = ost->nast;
		ost->nast = wsk;
	}
}
void czyscListe(ADRES *lista)
{
	ADRES pom = *lista;
	while (pom != NULL)
	{
		*lista = (*lista)->nast;
		free(pom);
		pom = *lista;
	}
}
int elementListy(ADRES lista, int element,int w,int k)
{
	if (element >= w*k)
		element = element % (w*k);
	if (element < 0)
	{
		element = element % (w*k);
		element += w*k;

	}
	for (int i = 0; i < element; i++)
	{
		lista = lista->nast;
	}
	return	lista->dane.liczba;
}


int main()
{
	while (true)
	{
		ADRES lista = NULL;
		ADRES wyniki = NULL;
		ADRES listaTmp = NULL;
		FILE *f;
		srand(time(NULL));
		int liczba, menu = 0;
		f = fopen("abc.txt", "r");
		int w, k;
		while (true)
		{
			printf("1 wczytaj z pliku\n2 wpisz recznie\n3 losowo\n4 wyjdz\n");
			scanf("%d", &menu);
			system("cls");
			if (menu == 1 || menu == 2 || menu == 3 || menu == 4)
				break;
		}
		switch (menu)
		{
		case 1:
			fscanf(f, "%d", &w);
			fscanf(f, "%d", &k);
			for (int i = 0; i < w; i++)
			{
				for (int j = 0; j < k; j++)
				{
					fscanf(f, "%d", &liczba);
					dodajDoListyNaKoncu(&lista, liczba);
				}
			}

			break;
		case 2:

			printf("podaj ilosc wierszy ");
			scanf("%d", &w);
			printf("podaj ilosc kolumn ");
			scanf("%d", &k);

			for (int i = 0; i < w; i++)
			{
				printf("podaj elementy %d wiersza\n", (i + 1));
				for (int j = 0; j < k; j++)
				{
					scanf("%d", &liczba);
					dodajDoListyNaKoncu(&lista, liczba);
				}
			}
			break;
		case 3:
			printf("podaj ilosc wierszy ");
			scanf("%d", &w);
			printf("podaj ilosc kolumn ");
			scanf("%d", &k);
			for (int i = 0; i < w; i++)
			{
				for (int j = 0; j < k; j++)
				{
					liczba = rand() % 10;
					dodajDoListyNaKoncu(&lista, liczba);
				}
			}
			break;
		case 4:
			return 0;
			break;
		}

		int *ruch;
		ruch = (int*)malloc((k) * sizeof(int));
		for (int i = 1; i < k; i++)
		{
			ruch[i] = -1;
		}
		ruch[0] = 0;
		wypiszListe(lista, k);
		int b = 0;
		int wynik = INT_MAX, tmp = 0, dodatkowe = 0;
		while (ruch[0] < w)
		{
			for (int j = 0; j < k; j++)
			{
				dodatkowe += ruch[j];
				b = elementListy(lista, (dodatkowe)*k + j, w, k);
				tmp = tmp + b;
				dodajDoListyNaKoncu(&listaTmp, b);

			}
			//wypiszListe(listaTmp, k);
			if (tmp < wynik)
			{
				czyscListe(&wyniki);
				for (int m = 0; m < k; m++)
				{
					dodajDoListyNaKoncu(&wyniki, elementListy(listaTmp, m, w, k));
				}
				//wypiszListe(listaTmp, k);

				wynik = tmp;
			}

			tmp = 0;
			dodatkowe = 0;
			ruch[k - 1] += 1;
			czyscListe(&listaTmp);
			for (int l = 0; l < k - 1; l++)
			{
				if (ruch[k - 1 - l] == 2)
				{
					ruch[k - 2 - l] += 1;
					ruch[k - 1 - l] = -1;
				}
			}
		}
		printf("wynik = %d\n", wynik);
		wypiszListe(wyniki, k);
		czyscListe(&lista);
		czyscListe(&wyniki);
		fclose(f);
		free(ruch);
	}
	return 0;
}