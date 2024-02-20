#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Validates the expression for balanced parentheses and other syntax errors.
 *
 * @param exp The expression string to be validated.
 * @return 1 if the expression is valid, otherwise exits with an error message.
 */
int validar_expresion(const char *exp) {
    int open_parentheses = 0;
    int i;
    for (i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == '(') {
            open_parentheses++;
        } else if (exp[i] == ')') {
            open_parentheses--;
            if (open_parentheses < 0) {
                printf("Error: Los paréntesis no están balanceados. Hay un paréntesis de cierre sin su apertura.\n");
                exit(0);
            }
        }

        if (exp[i] == '(' && i > 0 && exp[i - 1] >= '0' && exp[i - 1] <= '9') {
            printf("Error: Falta un operador antes del paréntesis de apertura.\n");
            exit(0);
        }

        if (exp[i - 1] == ')' && exp[i] >= '0' && exp[i - 1] <= '9') {
            printf("Error: Falta un operador después del paréntesis de cierre.\n");
            exit(0);
        }

        if ((exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') &&
            (exp[i + 1] == '+' || exp[i + 1] == '-' || exp[i + 1] == '*' || exp[i + 1] == '/')) {
            printf("Error: Múltiples operadores seguidos.\n");
            exit(0);
        }

    }

    if (open_parentheses > 0) {
        printf("Error: Los paréntesis no están balanceados. Falta un paréntesis de cierre.\n");
        exit(0);
    }

    char *div_by_zero = strstr(exp, "/0");
    if (div_by_zero != NULL) {
        printf("Error: División por cero.\n");
        exit(0);
    }

    return 1;
}

/**
 * Main function to parse arguments, validate expression, and evaluate it using Python.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 if successful, otherwise returns 1 indicating an error.
 */
int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Error: No se proporcionaron argumentos para evaluar.\n");
        return 1;
    }

    char eval_string[100] = "";
    for (int i = 1; i < argc; i++) {
        strcat(eval_string, argv[i]);
    }

    if (!validar_expresion(eval_string)) {
        printf("Error: Los paréntesis no están balanceados.\n");
        return 1;
    }

    Py_Initialize();
    char python_eval_string[1000] = "print(eval(\"";
    strcat(python_eval_string, eval_string);
    strcat(python_eval_string, "\"))");

    PyRun_SimpleString(python_eval_string);
    Py_Finalize();

    return 0;
}
