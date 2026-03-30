//Declaration:

//Libraries:
#include <stdio.h>                      //Работа с файлами
#include <string.h>                     //Работа со строками (strcmp, strcpy)
#include <stdlib.h>                     //Работа с памятью, изменением типов данных
#include <direct.h>                     //Работа с файловой системой

//Macroses pre-proc
#define MAX_PATH 260        //МАКРОСЫ ИЛИ ПРОСТО ПЕРЕМЕННЫМИ СДЕЛАТЬ? <Серега>

// Global variables
const char *LogFile;                    //Указатель на лог-файл
const char *TargetFile;                 //Указатель на файл обфускации
char WorkingDirectory[MAX_PATH];        //Переменная пути домашнего каталога 
char DefaultLogFile[MAX_PATH];          //Путь до лог-файла
char ResultFilePath[MAX_PATH];          //Путь до обфусцированного файла
int MethodCode;                         //Вид обфускации
int code;                               //Глобальный код возврата


//Procedures:
int my_param(char *logfile, char *targetfile, char *method /*локал. перем. "code1" для сохранения значения у глоб. перем. "code"*/)
{   //Процедура инициализации и ввода входных параметров
    /*
    BEGIN
    char *logfile - указатель на лог-файл
    char *targetfile - указатель на обфусцируемый файл
    */
    printf("my_param"); //debug
    if (_getcwd(WorkingDirectory, sizeof(WorkingDirectory)) == NULL) //Получение текущей рабочей директории (где запущена программа)
    {
        code = 1; //Ошибка доступа к каталогу
        return 1; //Завершение
    }
    
   if (logfile == NULL || logfile[0] == '\0') //Проверка пути до файла лога
    {
        snprintf(DefaultLogFile, sizeof(DefaultLogFile), "%s\\obfus_log.txt", WorkingDirectory); //Формирование пути к лог-файлу и запись в буфер DefaultLogFile
        LogFile = DefaultLogFile;
    }
    else
    {
        LogFile = logfile;
    }

    if (targetfile == NULL || targetfile[0] == '\0') //Проверка наличия пути до файла обфускации
    {
        TargetFile = NULL;
    }
    else
    {
        TargetFile = targetfile;
    }

    if (method == NULL || method[0] == '\0') // Проверка, выбран метод не задан
    {
        MethodCode = 0; //Выбор лексической обфускации по умолчанию 
    }
    else
    {
        MethodCode = atoi(method); // Преобразование строки в число

        if (MethodCode < 1 || MethodCode > 3)
        {
            code = 2; //Некорректный пользовательский ввод при выборе метода обфускации
            return 1; //Завершение
        }
    }
    return 0; //Завершение
    printf("end my_param"); //debug
} //END my_param()

int err_hand(void) //Процедура обработки ошибок
{   /*
    BEGIN
    int code - код возврата
    */
    printf("err_hand"); //debug
    switch (code)
    {
        case 1:
            return "Parameter error";           //Сообщить ошибку ввода параметров

        case 2:
            return "File I/O error";            //Сообщить ошибку файловой системы

        case 3:
            return "Memory allocation error";   //Сообщить ошибку доступа к памяти

        case 4:
            return "Source file is empty";      //Сообщить, что файл обфускации пуст

        case 5:
            return "Cannot create result file"; //Сообщить о неудачной попытке создать обфусцированный файл

        default:
            return "Unknown error";             //Сообщить о неизвестной ошибке
    }
    return 0; //Завершить
    printf("end err_hand"); //debug
}//END err_hand()


//Body
int main(void)
{//BEGIN
    printf("main"); //debug
    switch (my_param(char *logfile, char *targetfile, char *method)) //Процедура инициализации
    {
        case 0: 
            switch (my_find_and_read()) //Процедура доступа и чтения файла
            {
                case 0:
                    switch (my_method(0)) //Процедура обфускации
                    {
                        case 0:
                            switch(MethodCode==0) //Определение дополнительных методов обфускации
                            {
                                case 1:
                                    return 0;
                                case 0:
                                    my_method(MethodCode); //Процедура обфускации (дополнительная)
                                    return 0;
                            }

                        case 1:
                            switch (my_msg(err_hand())) //Процедура сообщения пользователю
                            {
                                case 0:
                                    my_finish(); //Процедура завершения
                                    break;
                                case 1:
                                    my_diag(); //Процедура диагностики
                                    my_finish(); //Процедура завершения
                                    break;
                            }
                    }

            case 1:
                switch (my_msg(err_hand())) //Процедура сообщения пользователю
                {
                    case 0:
                        my_finish(); //Процедура завершения
                        break;
                    case 1:
                        my_diag(); //Процедура диагностики
                        my_finish(); //Процедура завершения
                        break;
                }
        }

        case 1:
            switch (my_msg(err_hand())) //Процедура сообщения пользователю
            {
                case 0:
                    my_finish(); //Процедура завершения
                    break;
                case 1:
                    my_diag(); //Процедура диагностики
                    my_finish(); //Процедура завершения
                    break;
            }
    }
    printf("end main"); //debug
}//END main()