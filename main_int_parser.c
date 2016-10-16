
// PARSER PRO POVINNOU TRIDU MAIN A POVINNOU FUNKCI RUN (WIP)

int class_main(){ // parser pro povinnou tridu main

     token = lexer(&attr);

     switch (token){

     case CLASS:

         if ((token = lexer(&attr)) == LEX_ERROR) return LEX_ERROR;
         if (token != MAIN) return SYNTAX_ERROR; else                      // vstupnim bodem programu je povinna trida Main
         {
             if ((token = lexer(&attr)) == LEX_ERROR) return LEX_ERROR;
             if (token != LEFT_VINCULUM) return SYNTAX_ERROR; else        // jsme uvnitr mainu "class Main{"
             {
                 if ((token = lexer(&attr)) == LEX_ERROR) return LEX_ERROR;
                 if (token != STATIC) return SYNTAX_ERROR; else       // musi nasledovat funkce run - > static void run
                 {
                     if ((token = lexer(&attr)) == LEX_ERROR) return LEX_ERROR;
                     if (token != VOID) return SYNTAX_ERROR; else
                     {
                         if ((token = lexer(&attr)) == LEX_ERROR) return LEX_ERROR;
                         if (token != RUN) return SYNTAX_ERROR; else
                         {
                            if ((token = lexer(&attr)) == LEX_ERROR) return LEX_ERROR;
                            if (token != LEFT_BRACKET) return SYNTAX_ERROR; else
                            {
                                if ((token = lexer(&attr)) == LEX_ERROR) return LEX_ERROR;
                                if (token != RIGHT_BRACKET) return SYNTAX_ERROR; else
                                {
                                    if ((token = lexer(&attr)) == LEX_ERROR) return LEX_ERROR;
                                    if (token != LEFT_VINCULUM) return SYNTAX_ERROR; else       // jsme uvnitr fce run -> " class Main{ static void run(){ " muze zacit zbytek programu
                                    {
                                        main_body();
                                        main_end();
                                    }

                                }
                            }
                         }
                     }
                 }
             }
         }
     }
     return SYNTAX_ERROR; // pokud program nezacina klicovym slovem class je to syntakticky error
}


// PARSER PRO TELO TRIDY (WIP)

int class_body(){

token = lexer(&attr);

switch (token){

case CLASS: return SYNTAX_ERROR; // pokus o deklarovani tridy uvnitr tridy

case INT: // nasleduje deklarovani promenne typu int

    if ((token = lexer(&attr)) == LEX_ERROR) return LEX_ERROR;
    if (token != ID) return SYNTAX_ERROR; else
    {
       tableInsert(blablabla); // vloz identifikator do tabulky symbolu a podivej se, jestli uz takovy v ramci jedne tridy/fce neexistuje, DOPLNIT!!!!!

       if ((token = lexer(&attr)) == LEX_ERROR) return LEX_ERROR;
       if (token != SEMICOLON && token != EQUAL) return SYNTAX_ERROR; else

       {
           if (token == SEMICOLON) return class_body(); else // deklarace neinicializovaneho intu intu uvnitr tridy/fce probehla v poradku, rekurzivne volame fci
           {
           
           // pokud to nebyl semicolon, jedna se o inicializaci/prirazeni intu 
           
            int_declare_parser(); // volani parseru, ktery overuje syntax inicializace/prirazeni promenne int
            
           }
        }   
      }      
    }
  }     
           

// PARSER PRO INICIALIZACI CELOCISELNE PROMENNE (WIP)

int int_declare_parser(){ // parser ktery kontroluje spravny syntax inicializovania prirazovani hodnot celociselne promenne

    int sign_count = 0; // countery
    int id_count = 0;
    int literal_count = 0;
    int l_bracket_count = 0;
    int r_bracket_count = 0;

    switch (token){

    case SEMICOLON:

     if ( (id_count == 0 && literal_count == 0) || sign_count == 1) return SYNTAX_ERROR; // pokus o nasledujici deklaraci intu:  " int cislo = ; " nebo " int cislo = 1 + ;" je syntakticka chyba

     else if ( (id_count == 1 || literal_count == 1 ) && sign_count == 0) return SYNTAX_OK; break; // inicializace intu probehla v poradku

    case INT_LITERAL:

     literal_count = 1; return int_declare_parser(); break; // nasledovalo cele cislo, rekurzivne volej fci dale a parsuj

    case ID:

     id_count = 1;
     sign_count = 0;

     // NUTNO PODIVAT SE DO TABULKY SYMBOLU A NAJIT TAM DANY IDENTIFIKATOR POKUD SE JEDNA O ID INTU, MUZE SE JEDNAT I O ID FUNKCE KTERA SE NACHAZI ZA PROGRAMEM! DOPLNIT!!!

     tData polozka = tableSearch(blablabla); // podivej se do tabulky na ID, DOPLNIT!!!

     if (polozka.varType == INT_LITERAL) return int_declare_parser(); break; // pokud odpovida typ ID, rekurzivne parsuj dale, DOPLNIT!!!!!

     else return SYNTAX_ERROR; break; // pokud to neni celociselny literal, jedna se o syntakticky error

    case PLUS:
    case MINUS:
    case MUL:
    case DEC:

     sign_count = 1; // signalizuj znamenko

     if (id_count == 0 && literal_count == 0) return SYNTAX_ERROR; break; // pokud se nenachazi pred znamenkem id nebo celociselny literal, je to error

     id_count = 0;
     literal_count == 0;

     else return int_declare_parser(); break; // jinak parsuj dale

    case LEFT_BRACKET:

     l_bracket_count = 1;

     if (id_count == 1 && literal_count == 0 && sign_count == 0) blablabla // jedna se o funkci, zavolej parser parametru a konce funkci, DOPLNIT!!!

     else if (id_count == 0 && literal_count == 1 && sign_count == 0) return SYNTAX_ERROR; break; // jedna se o syntaktickou chybu typu " int cislo = 5( "

     else if (id_count == 0 && literal_count == 0 && sign_count == 1) // mozna platna deklarace uvidime, DOPLNIT!!!

    case RIGHT_BRACKET:

     r_bracket_count = 1;

     if (l_bracket_count == 1) l_bracket_count == 0; return int_declare_parser(); break;

     else return SYNTAX_ERROR; break;

     // DORESIT CO S ARGUMENTAMA VE FCI
    }

}
           
           
