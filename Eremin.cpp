#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "testing.h"
#pragma warning (disable:4996)


void deleteBlanks(char str[81]);
void cutString(char str[81], int beginPos, int endPos);
void testDeleteBlanks();
void testCutString();


int main(void)
{
	setlocale(LC_ALL, "Rus");					// Подключение русского алфавита

	// Запуск тестовых драйверов
	//testDeleteBlanks();
	//testCutString();

	int num_of_str;								// Количество строк текста для считывания

	char mass_texts[20][81];					// Массив для хранения строк текста

	int all_strings_empty = 1;					// Изначально считаем, что все строки пустые

	input_printf("Введите количество строк в тексте (2-20): ");
	scanf("%d", &num_of_str);											// Считывание количества строк
	getchar();															// Считывание последующего за числом строк символа перевода строки

	// Проверка количества строк на корректность
	if (num_of_str < 2 || num_of_str > 20)
	{
		error_printf("Введенно некорректное число строк.\n");
		return 0;
	}

	// Считывание строк в массив и удаление из них лишних пробелов
	for (int i = 0; num_of_str > i; i++)
	{
		input_printf("Введите %d строку (0-80): ", i + 1);
		gets_s(mass_texts[i]);
		deleteBlanks(mass_texts[i]);
	}

	// Вывод строк без лишних пробелов
	for (int i = 0; num_of_str > i; i++)
	{
		int there_are_only_white_sep = 1;		// Изначально считаем, что строка пустая

		// Проверка массива на признак пустоты
		for (int j = 0; mass_texts[i][j] != '\0' && there_are_only_white_sep; j++)
		{
			there_are_only_white_sep = isspace(mass_texts[i][j]);
		}

		// Печать строки, если она не пустая
		if (!there_are_only_white_sep)
		{
			printf("%s\n", mass_texts[i]);

			all_strings_empty = 0;				// В тексте есть не пустая строка
		}
	}

	// Печать no solution, если все строки текста пустые
	if (all_strings_empty)
	{
		printf("no solution\n");
	}

	return 0;
}

/*
	Функция, сокращающая строку, включая границы
	\param [in, out] str - строка многострочного текста, в которой будут удаляться элементы начиная с индекса beginPos, заканчивая endPos
	\param [in] begPos - индекс начала подстроки, которая будет удалена
	\param [in] endPos - индекс конца подстроки, которая будет удалена
*/
void cutString(char str[81], int beginPos, int endPos)
{	
	strcpy(str + beginPos, str + endPos + 1);
}

/*
	Функция, удаляющая лишние пробелы в строках
	\param [in, out] str - строка многострочного текста, в которой будут удаляться лишние пробелы
*/
void deleteBlanks(char str[81])
{
	// Массив разделителей без пробела и дефиса
	char mass_separ_without_space_and_hyphen[] = { '!', '\'', '"', ';', ':', '?', '.', ',', '\0' };

	// Массив всех разделителей
	char all_separ[] = { '!', '\'', '"', ';', ':', '?', '-', '.', ',', ' ', '\0' };

	// Массив всех обычных и белых разделителей
	char all_separ_with_white[] = { '!', '\'', '"', ';', ':', '?', '-', '.', ',', ' ', '\t', '\n', '\v', '\f', '\r', '\0' };

	// Массив "белых" разделителей
	char mass_white_sep[] = { '\t', '\n', '\v', '\f', '\r', '\0' };

	// Объявление...
	char* str_pointer = str;			// ...и инициализация указателя на строку
	char* str_begin = str;				// ...и инициализация указателя на начало строки	

	// Пропуск пробелов в начале строки
	if (*str_begin == ' ')
	{
		str_pointer += strspn(str_begin, " ");	// Перевод указателя на первый символ не пробел
	}

	// Проходка по всем элементам строки
	while (str_pointer = strchr(str_pointer, ' '))						// Поиск следующей подстроки из пробелов
	{
		int length_space = strspn(str_pointer, " ");					// Вычисление длины подстроки из пробелов

		char* before_space_symbol_pointer = str_pointer - 1;			// Вычисление указателя на символ, стоящий перед подстрокой из пробелов
		char before_space_symbol = *(before_space_symbol_pointer);		// Запись символа, стоящего перед подстрокой из пробелов

		char* after_space_symbol_pointer = str_pointer + length_space;	// Вычисление указателя на символ, стоящий после подстроки из пробелов
		char after_space_symbol = *(after_space_symbol_pointer);		// Запись символа, стоящего после подстроки из пробелов

		// Объявление и инициализация флага, указывающего, что символ, стоящий перед подстрокой из пробелов является...
		bool before_space_symbol_is_separator = strchr(mass_separ_without_space_and_hyphen, before_space_symbol);	// ...разделителем, но не пробелом или дефисом
		bool before_space_symbol_is_part_of_word = !strchr(all_separ_with_white, before_space_symbol);				// ...частью слова
		bool before_space_symbol_is_white_space = isspace(before_space_symbol);										// ...белым разделителем

		// Объявление и инициализация флага, указывающего, что символ, стоящий после подстроки из пробелов является...
		bool after_space_symbol_is_separator = strchr(mass_separ_without_space_and_hyphen, after_space_symbol);		// ...разделителем, но не пробелом или дефисом
		bool after_space_symbol_is_end_string = after_space_symbol == '\0';											// ...символом конца строки

		// Символ перед подстрокой из пробелов является или разделителем, но не пробелом, или дефисом, или частью слова или белым разделителем
		bool before_space_symbol_is_part_of_word_or_separator_or_white_space = before_space_symbol_is_separator || before_space_symbol_is_part_of_word || before_space_symbol_is_white_space;
		// Символ после подстрокой из пробелов является или разделителем, но не пробелом или дефисом, или символом конца строки
		bool after_space_symbol_is_separator_or_end_string = after_space_symbol_is_separator || after_space_symbol_is_end_string;	

		// Подсчёт индекса...
		int left_edge = str_pointer - str_begin;						// ...левой границы для удаления пробелов (символа, стоящего перед подстрокой из пробелов)
		int right_edge = after_space_symbol_pointer - str_begin - 1;	// ...правой границы для удаления пробелов (символа, стоящего после подстроки из пробелов)

		if (before_space_symbol_is_part_of_word_or_separator_or_white_space && after_space_symbol_is_separator_or_end_string)
		{
			cutString(str, left_edge, right_edge);		// Пробелы между символами удаляются полностью
		}
		else if (right_edge - left_edge != 0)			// Между словами больше одного пробела
		{
			cutString(str, left_edge + 1, right_edge);	// Между символами остаётся один пробел
		}
	}
}

/*
	Тестовый драйвер, проверяющий функцию "удаления" лишних пробелов
*/
void testDeleteBlanks()
{
	printf("TestDeleteBlanks\n\n");

	// Количество тестовых ситуаций
	const int number_tests = 27;

	// Имена тестовых ситуаций
	char tests_names[number_tests][250] =
	{
		{"Разделитель перед подстрокой из пробелов и разделитель после неё, в начале и конце строки нет пробелов."},
		{"Разделитель перед подстрокой из пробелов и часть слова после неё, в начале и конце строки нет пробелов."},
		{"Разделитель перед подстрокой из пробелов и дефис после неё, в начале и конце строки нет пробелов."},
		{"Разделитель перед подстрокой из пробелов и конец строки после неё, в начале строки нет пробелов."},
		{"Разделитель перед подстрокой из пробелов и белый разделитель(не пробел) после неё, в начале и конце строки нет пробелов."},
		{"Дефис перед подстрокой из пробелов и разделитель после неё, в начале и конце строки нет пробелов."},
		{"Дефис перед подстрокой из пробелов и часть слова после неё, в начале и конце строки нет пробелов."},
		{"Дефис перед подстрокой из пробелов и дефис после неё, в начале и конце строки нет пробелов."},
		{"Дефис перед подстрокой из пробелов и конец строки после неё, в начале строки нет пробелов."},
		{"Дефис перед подстрокой из пробелов и белый разделитель(не пробел) после неё, в начале и конце строки нет пробелов."},
		{"Часть слова перед подстрокой из пробелов и разделитель после неё, в начале и конце строки нет пробелов."},
		{"Часть слова перед подстрокой из пробелов и часть слова после неё, в начале и конце строки нет пробелов."},
		{"Часть слова перед подстрокой из пробелов и дефис после неё, в начале и конце строки нет пробелов."},
		{"Часть слова перед подстрокой из пробелов и конец строки после неё, в начале строки нет пробелов."},
		{"Часть слова перед подстрокой из пробелов и белый разделитель(не пробел) после неё, в начале и конце строки нет пробелов."},
		{"Белый разделитель(не пробел) перед подстрокой из пробелов и разделитель после неё, в начале и конце строки нет пробелов."},
		{"Белый разделитель(не пробел) перед подстрокой из пробелов и часть слова после неё, в начале и конце строки нет пробелов."},
		{"Белый разделитель(не пробел) перед подстрокой из пробелов и дефис после неё, в начале и конце строки нет пробелов."},
		{"Белый разделитель(не пробел) перед подстрокой из пробелов и конец строки после неё, в начале строки нет пробелов."},
		{"Белый разделитель(не пробел) перед подстрокой из пробелов и белый разделитель(не пробел) после неё, в начале и конце строки нет пробелов."},
		{"Строка состоит из всех возоможных символов, в начале и конце строки есть пробелы."},
		{"Строка состоит только из белых разделителей, в начале и конце строки есть пробелы."},
		{"Строка изначально абсолютно пустая."},
		{"Строка длинной 80 символов, состоит из всех возможных символов, есть пробелы в начале и конце строки."},
		{"Строка состоит из одних пробелов."},
		{"Строка состоит из различных комбинаций дефисов."},
		{"Строка включает комбинации символов, где есть должны быть пробелы между ними, но их нет."}
	};

	// Многострочные тексты для удаления лишних проблелов
	char string[number_tests][81] =
	{
		{"?                                   \""},
		{";                          road"},
		{"!            -"},
		{"'                                "},
		{":                      \t"},
		{"-                     ."},
		{"-                       man"},
		{"-                   -"},
		{"-                                    "},
		{"-                         \f"},
		{"Car                      ,"},
		{"My                 masterpiece"},
		{"Home                   -"},
		{"Hello                          "},
		{"Goodbye               \n"},
		{"\r                   \""},
		{"\v                        tree"},
		{"\f                                 -"},
		{"\n                              "},
		{"\t                        \f"},
		{"    !  ?   I  , am ;; \n   Semyon  \t -  -   "},
		{"    \t     \n     \v   \f   \r  "},
		{""},
		{"  I  \v , am   Semyon  I  '  am  \t  18 My , gr,oup  -  PrIn  - 166  \n I so happy "},
		{"                                        "},
		{"-   --  -   ---    -   --      -"},
		{"  I ,am   -Semyon  I  !-am   18 My-, gr,oup  --  PrIn  - 166 I so happy "}
	};

	// Ожидаемые результаты для тестовых ситуаций
	const char exp_texts[number_tests][81] =
	{
		{"?\""},
		{"; road"},
		{"! -"},
		{"'"},
		{": \t"},
		{"- ."},
		{"- man"},
		{"- -"},
		{"- "},
		{"- \f"},
		{"Car,"},
		{"My masterpiece"},
		{"Home -"},
		{"Hello"},
		{"Goodbye \n"},
		{"\r\""},
		{"\v tree"},
		{"\f -"},
		{"\n"},
		{"\t \f"},
		{"    !? I, am;; \n Semyon \t - - "},
		{"    \t \n \v \f \r"},
		{""},
		{"  I \v, am Semyon I' am \t 18 My, gr,oup - PrIn - 166 \n I so happy"},
		{"                                        "},
		{"- -- - --- - -- -"},
		{"  I,am -Semyon I!-am 18 My-, gr,oup -- PrIn - 166 I so happy"}
	};

	// Флаг, указывающий на отсутствие непройденных тестовых ситуаций
	int is_ok = 1;

	for (int count = 0; count < number_tests; count++)
	{
		
		deleteBlanks(string[count]);

		if (strcmp(exp_texts[count], string[count]) != 0)
		{
			is_ok = 0;

			printf("Test %d: %s\nExpected: |%s|, Take out: |%s|\n\n", count + 1, tests_names[count], exp_texts[count], string[count]);
		}
		
	}

	// Вывод сообщения, что все тестовые ситуации пройденны успешно
	if (is_ok)
	{
		printf("All is OK\n\n");
	}
}

/*
	Тестовый драйвер, проверяющий функцию сокращения строки (Переделать тестовые драйверы!)
*/
void testCutString()
{
	printf("TestCutString\n\n");

	// Количество тестовых ситуаций
	const int number_tests = 12;

	// Имена тестовых ситуаций
	char tests_names[number_tests][200] =
	{
		{"Строка длинной 35 символов, удаляется подстрока из середины строки."},
		{"Строка длинной 35 символов, удаляется подстрока от начала строки до середины."},
		{"Строка длинной 35 символов, удаляется подстрока от середины строки до конца."},
		{"Строка длинной 35 символов, удаляется вся строка."},
		{"Строка длинной 35 символов, удаляется вся строка, правая граница удаления на символе с индексом 65."},
		{"Строка длинной 35 символов, удаляется один символ из середины строки."},
		{"Строка максимальной длинны в 80 символов, удаляется подстрока из середины строки."},
		{"Строка максимальной длинны в 80 символов, удаляется подстрока от начала строки до середины."},
		{"Строка максимальной длинны в 80 символов, удаляется подстрока от середины строки до конца."},
		{"Строка максимальной длинны в 80 символов, удаляется вся строка."},
		{"Строка изначально абсоютно пустая, удаляется подстрока из середины строки."},
		{"Строка длинной 35 символов, удаляется один символ из середины строки."}
	};

	// Многострочные тексты для удаления лишних проблелов
	char strings[number_tests][81] =
	{
		{"Tomorrow the weather will be great!"},
		{"Tomorrow the weather will be great!"},
		{"Tomorrow the weather will be great!"},
		{"Tomorrow the weather will be great!"},
		{"Tomorrow the weather will be great!"},
		{"Tomorrow the weather will be great!"},
		{"I was playing in the yard today, it was sunny and the birds were singing loudly."},
		{"I was playing in the yard today, it was sunny and the birds were singing loudly."},
		{"I was playing in the yard today, it was sunny and the birds were singing loudly."},
		{"I was playing in the yard today, it was sunny and the birds were singing loudly."},
		{""},
		{"Tomorrow the weather will be great!"}
	};

	// Индексы начальных позиций
	int begin_pos[number_tests][1] =
	{
		15,
		0,
		20,
		0,
		0,
		16,
		31,
		0,
		31,
		0,
		25,
		15
	};

	// Индексы конечных позиций
	int end_pos[number_tests][1] =
	{
		17,
		12,
		34,
		34,
		65,
		16,
		48,
		32,
		79,
		79,
		68,
		15
	};

	// Ожидаемые результаты для тестовых ситуаций
	const char exp_texts[number_tests][81] =
	{

		{"Tomorrow the weer will be great!"},
		{"weather will be great!"},
		{"Tomorrow the weather"},
		{""},
		{""},
		{"Tomorrow the weaher will be great!"},
		{"I was playing in the yard today the birds were singing loudly."},
		{"it was sunny and the birds were singing loudly."},
		{"I was playing in the yard today"},
		{""},
		{""},
		{"Tomorrow the wether will be great!"}
	};

	// Флаг, указывающий на отсутствие непройденных тестовых ситуаций
	int is_ok = 1;

	for (int count = 0; count < number_tests; count++)
	{
		cutString(strings[count], *begin_pos[count], *end_pos[count]);

		if (strcmp(exp_texts[count], strings[count]) != 0)
		{
			is_ok = 0;

			printf("Test %d: %s\nExpected: |%s|, Take out: |%s|\n\n", count + 1, tests_names[count], exp_texts[count], strings[count]);
		}
		
	}

	// Вывод сообщения, что все тестовые ситуации пройденны успешно
	if (is_ok)
	{
		printf("All is OK\n\n");
	}

}

void func() {
	
}